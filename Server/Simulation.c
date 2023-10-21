#include <Server/Simulation.h>

#include <assert.h>
#include <inttypes.h>
#include <math.h>
#include <stdlib.h>
#include <string.h>
#include <sys/time.h>

#include <Server/EntityAllocation.h>
#include <Server/EntityDetection.h>
#include <Server/SpatialHash.h>
#include <Server/System/System.h>
#include <Server/Waves.h>
#include <Shared/Bitset.h>
#include <Shared/Utilities.h>
#include <Shared/pb.h>

static void set_respawn_zone(struct rr_component_arena *arena, uint32_t x, uint32_t y, uint32_t w, uint32_t h)
{
    float dim = arena->grid_size;
    arena->respawn_zone.x = 2 * x * dim;
    arena->respawn_zone.y = 2 * y * dim;
    arena->respawn_zone.w = 2 * w * dim;
    arena->respawn_zone.h = 2 * h * dim;
}

static void set_special_zone(uint8_t biome, uint8_t (*fun)(), uint32_t x, uint32_t y, uint32_t w, uint32_t h)
{
    x *= 2;
    y *= 2;
    w *= 2;
    h *= 2;
    uint32_t dim = RR_MAZES[biome].maze_dim;
    for (uint32_t Y = 0; Y < h; ++Y)
        for (uint32_t X = 0; X < w; ++X)
            RR_MAZES[biome].maze[(Y+y)*dim+(X+x)].spawn_function = fun;
}

#define SPAWN_ZONE_X 19
#define SPAWN_ZONE_Y 15
#define SPAWN_ZONE_W 3
#define SPAWN_ZONE_H 1

uint8_t ornitho_zone() { return rr_frand() > 0.5 ? rr_mob_id_ornithomimus : rr_mob_id_fern; }
uint8_t rex_zone() { return rr_mob_id_trex; }
uint8_t ankylo_zone() { return rr_frand() > 0.2 ? rr_mob_id_ankylosaurus : rr_mob_id_tree; }
uint8_t trike_pachy_zone() { return rr_frand() > 0.4 ? rr_mob_id_pachycephalosaurus : rr_mob_id_triceratops; }
uint8_t ptera_meteor_zone() { return rr_frand() > 0.01 ? rr_mob_id_pteranodon : rr_mob_id_meteor; }
uint8_t patchy_zone() { return rr_mob_id_pachycephalosaurus; }
uint8_t edmonto_zone() { return rr_mob_id_edmontosaurus; }
uint8_t dako_zone() { return rr_mob_id_dakotaraptor; }
uint8_t quetz_zone() { return rr_mob_id_quetzalcoatlus; }

void rr_simulation_init(struct rr_simulation *this)
{
    memset(this, 0, sizeof *this);
    EntityIdx id = rr_simulation_alloc_entity(this);
    struct rr_component_arena *arena =
        rr_simulation_add_arena(this, id);
    //rr_component_arena_set_radius(arena_component, RR_ARENA_LENGTH);
    arena->biome = RR_GLOBAL_BIOME; //CHANGE
    rr_component_arena_spatial_hash_init(arena, this);
    set_respawn_zone(arena, SPAWN_ZONE_X, SPAWN_ZONE_Y, SPAWN_ZONE_W, SPAWN_ZONE_H);
    set_special_zone(rr_biome_id_hell_creek, ornitho_zone, 11, 11, 2, 2);
    set_special_zone(rr_biome_id_hell_creek, ptera_meteor_zone, 13, 23, 4, 3);
    set_special_zone(rr_biome_id_hell_creek, edmonto_zone, 19, 3, 3, 2);
    set_special_zone(rr_biome_id_hell_creek, dako_zone, 7, 7, 1, 3);
    set_special_zone(rr_biome_id_hell_creek, rex_zone, 0, 29, 4, 1);
    set_special_zone(rr_biome_id_hell_creek, trike_pachy_zone, 6, 23, 2, 2);
    set_special_zone(rr_biome_id_hell_creek, ankylo_zone, 4, 16, 4, 1);
    set_special_zone(rr_biome_id_hell_creek, patchy_zone, 7, 4, 2, 1);
    set_special_zone(rr_biome_id_hell_creek, quetz_zone, 11, 0, 3, 2);
#define XX(COMPONENT, ID)                                                      \
    //printf(#COMPONENT);                                                        \
    printf(" size is %lu\n", sizeof *this->COMPONENT##_components);
    RR_FOR_EACH_COMPONENT;
#undef XX
}

struct too_close_captures
{
    struct rr_simulation *simulation;
    float x;
    float y;
    float closest_dist;
    uint8_t done;
};

static void too_close_cb(EntityIdx potential, void *_captures)
{
    struct too_close_captures *captures = _captures;
    if (captures->done)
        return;
    struct rr_simulation *simulation = captures->simulation;
    if (!rr_simulation_has_mob(simulation, potential) && !rr_simulation_has_flower(simulation, potential) || rr_simulation_has_arena(simulation, potential))
        return;
    if (rr_simulation_get_relations(simulation, potential)->team == rr_simulation_team_id_mobs)
        return;
    if (rr_simulation_get_health(simulation, potential)->health == 0)
        return;
    struct rr_component_physical *t_physical = rr_simulation_get_physical(simulation, potential);
    struct rr_vector delta = {captures->x - t_physical->x, captures->y - t_physical->y};
    float dist = rr_vector_get_magnitude(&delta);
    if (dist > captures->closest_dist)
        return;
    captures->done = 1;
}

static int too_close(struct rr_simulation *this, float x, float y, float r)
{
    struct too_close_captures shg_captures = {this, x, y, r, 0};
    struct rr_spatial_hash *shg = &rr_simulation_get_arena(this, 1)->spatial_hash;
    rr_spatial_hash_query(shg, x, y, r, r, &shg_captures, too_close_cb);
    return shg_captures.done;
}

static void spawn_mob(struct rr_simulation *this, uint32_t grid_x, uint32_t grid_y)
{
    struct rr_component_arena *arena = rr_simulation_get_arena(this, 1);
    struct rr_maze_grid *grid = rr_component_arena_get_grid(arena, grid_x, grid_y);
    uint8_t id;
    if (grid->spawn_function)
        id = grid->spawn_function();
    else
        id = get_spawn_id(RR_GLOBAL_BIOME, grid);
    uint8_t rarity = get_spawn_rarity(grid->difficulty);
    if (!should_spawn_at(id, rarity))
        return;
    for (uint32_t n = 0; n < 10; ++n)
    {
        struct rr_vector pos = {(grid_x + rr_frand() * 2) * arena->grid_size, (grid_y + rr_frand() * 2) * arena->grid_size};
        if (too_close(this, pos.x, pos.y, RR_MOB_DATA[id].radius * RR_MOB_RARITY_SCALING[rarity].radius + 250))
            continue;
        EntityIdx mob_id = rr_simulation_alloc_mob(this, 1, pos.x, pos.y, id, rarity,
                                                rr_simulation_team_id_mobs);
        rr_simulation_get_mob(this, mob_id)->zone = grid;
        grid->grid_points += RR_MOB_DIFFICULTY_COEFFICIENTS[id];
        break;
    }
}

#define GRID_MOB_LIMIT(DIFFICULTY, PLAYER_COUNT) \
    (1 - (DIFFICULTY) * 0.014) * (((PLAYER_COUNT) > 4 ? 4 : (PLAYER_COUNT)) * 8) + 15

static void count_flower_vicinity(EntityIdx entity, void *_simulation)
{
    struct rr_simulation *this = _simulation;
    struct rr_component_arena *arena = rr_simulation_get_arena(this, 1);
    struct rr_component_physical *physical = rr_simulation_get_physical(this, entity);
#ifdef RIVET_BUILD
#define FOV 2500
#else
#define FOV 20000
#endif
    uint32_t sx = rr_fclamp(physical->x - FOV, 0, arena->grid_size * arena->maze_dim) / arena->grid_size;
    uint32_t sy = rr_fclamp(physical->y - FOV, 0, arena->grid_size * arena->maze_dim) / arena->grid_size;
    uint32_t ex = rr_fclamp(physical->x + FOV, 0, arena->grid_size * arena->maze_dim) / arena->grid_size;
    uint32_t ey = rr_fclamp(physical->y + FOV, 0, arena->grid_size * arena->maze_dim) / arena->grid_size;
#undef FOV
    for (uint32_t x = sx; x <= ex; ++x)
        for (uint32_t y = sy; y <= ey; ++y)
            ++rr_component_arena_get_grid(arena, x, y)->player_count;
}

static void despawn_mob(EntityIdx entity, void *_simulation)
{
    struct rr_simulation *this = _simulation;
    struct rr_component_physical *physical = rr_simulation_get_physical(this, entity);
    if (physical->arena != 1)
        return;
    if (rr_simulation_has_arena(this, entity))
        return;
    struct rr_component_arena *arena = rr_simulation_get_arena(this, 1);
    if (rr_component_arena_get_grid(arena, physical->x / arena->grid_size, physical->y / arena->grid_size)->player_count == 0)
    {
        struct rr_component_mob *mob = rr_simulation_get_mob(this, entity);
        if (--mob->ticks_to_despawn == 0)
        {
            mob->no_drop = 1;
            rr_simulation_request_entity_deletion(this, entity);
            return;
        }
    }
    else
        rr_simulation_get_mob(this, entity)->ticks_to_despawn = 120 * 25;
}

static void tick_wave(struct rr_simulation *this)
{
    struct rr_component_arena *arena = rr_simulation_get_arena(this, 1);
    for (uint32_t i = 0; i < arena->maze_dim * arena->maze_dim; ++i)
        arena->grid[i].player_count = 0;
    rr_simulation_for_each_flower(this, this, count_flower_vicinity);
    rr_simulation_for_each_mob(this, this, despawn_mob);
    for (uint32_t grid_x = 0; grid_x < arena->maze_dim; grid_x += 2)
    {
        for (uint32_t grid_y = 0; grid_y < arena->maze_dim; grid_y += 2)
        {
            //if (grid_y == SPAWN_ZONE_Y && (grid_x >= SPAWN_ZONE_X && grid_x < SPAWN_ZONE_W + SPAWN_ZONE_X))
                //grid_y += SPAWN_ZONE_H;
            struct rr_maze_grid *grid = rr_component_arena_get_grid(arena, grid_x, grid_y);
            if (grid->player_count == 0 || grid->value == 0 || (grid->value & 8))
                continue;
            if (grid->grid_points >= GRID_MOB_LIMIT(grid->difficulty, grid->player_count))
                continue;
            //if (grid->spawn_function != NULL)
                //time *= 4;
            uint32_t time = 360 - (20 * (grid->player_count > 6 ? 6 : grid->player_count));
            if (rand() % time == 0)
                spawn_mob(this, grid_x, grid_y);
        }
    }
}

#define RR_TIME_BLOCK_(_, CODE)                                                 \
    {                                                                          \
        struct timeval start; \
        struct timeval end; \
        gettimeofday(&start, NULL); \
        CODE;                                                                  \
        gettimeofday(&end, NULL); \
        uint64_t elapsed_time = (end.tv_sec - start.tv_sec) * 1000000 + (end.tv_usec - start.tv_usec); \
        if (elapsed_time > 3000) \
        { \
            printf(_ " took %lu microseconds with %d entities\n", elapsed_time, this->physical_count); \
        } \
    };

#define RR_TIME_BLOCK(_, CODE)                                                 \
    {                                                                          \
        CODE;                                                                  \
    };

void rr_simulation_tick(struct rr_simulation *this)
{
    rr_simulation_create_component_vectors(this);
    //printf("server has %d entities\n", this->physical_count);
    //fputs("part 1\n", stderr);
    RR_TIME_BLOCK("collision_detection",
                  { rr_system_collision_detection_tick(this); });
    RR_TIME_BLOCK("ai", { rr_system_ai_tick(this); });
    RR_TIME_BLOCK("drops", { rr_system_drops_tick(this); });
    //fputs("part 2\n", stderr);
    RR_TIME_BLOCK("petal_behavior", { rr_system_petal_behavior_tick(this); });
    RR_TIME_BLOCK("collision_resolution",
                  { rr_system_collision_resolution_tick(this); });
    RR_TIME_BLOCK("web", { rr_system_web_tick(this); });
    //fputs("part 3\n", stderr);
    RR_TIME_BLOCK("velocity", { rr_system_velocity_tick(this); });
    RR_TIME_BLOCK("centipede", { rr_system_centipede_tick(this); });
    RR_TIME_BLOCK("health", { rr_system_health_tick(this); });
    RR_TIME_BLOCK("camera", { rr_system_camera_tick(this); });
    tick_wave(this);
    //fputs("part 4\n", stderr);
    memcpy(this->deleted_last_tick, this->pending_deletions, sizeof this->pending_deletions);
    memset(this->pending_deletions, 0, sizeof this->pending_deletions);
    rr_bitset_for_each_bit(
        this->deleted_last_tick,
        this->deleted_last_tick + (RR_BITSET_ROUND(RR_MAX_ENTITY_COUNT)), this,
        __rr_simulation_pending_deletion_free_components);
    rr_bitset_for_each_bit(this->deleted_last_tick,
                           this->deleted_last_tick +
                               (RR_BITSET_ROUND(RR_MAX_ENTITY_COUNT)),
                           this, __rr_simulation_pending_deletion_unset_entity);
}

int rr_simulation_entity_alive(struct rr_simulation *this, EntityHash hash)
{
    return this->entity_tracker[(EntityIdx) hash] && this->entity_hash_tracker[(EntityIdx) hash] == (hash >> 16) && !rr_bitset_get(this->deleted_last_tick, (EntityIdx) hash);
}

EntityHash rr_simulation_get_entity_hash(struct rr_simulation *this, EntityIdx id)
{
    return ((uint32_t)(this->entity_hash_tracker[id]) << 16) | id;
}
