#include <Server/Simulation.h>

#include <assert.h>
#include <inttypes.h>
#include <math.h>
#include <stdlib.h>
#include <string.h>
#include <sys/time.h>

#include <Server/EntityAllocation.h>
#include <Server/SpatialHash.h>
#include <Server/System/System.h>
#include <Server/Waves.h>
#include <Shared/Bitset.h>
#include <Shared/Utilities.h>
#include <Shared/pb.h>

static void set_respawn_zone(struct rr_spawn_zone *zone, uint32_t x, uint32_t y, uint32_t w, uint32_t h)
{
    zone->x = x * RR_MAZE_GRID_SIZE;
    zone->y = y * RR_MAZE_GRID_SIZE;
    zone->w = w * RR_MAZE_GRID_SIZE;
    zone->h = h * RR_MAZE_GRID_SIZE;
}
static void set_special_zone(uint8_t biome, uint8_t id, uint32_t x, uint32_t y, uint32_t w, uint32_t h)
{
    struct rr_maze_grid (*grid)[RR_MAZE_DIM] = biome == 0 ? RR_MAZE_HELL_CREEK : RR_MAZE_HELL_CREEK;
    for (uint32_t Y = 0; Y < h; ++Y)
        for (uint32_t X = 0; X < h; ++X)
        {
            grid[Y+y][X+x].is_special = 1;
            grid[Y+y][X+x].special_id = id;
        }
}
#define SPAWN_ZONE_X 36
#define SPAWN_ZONE_Y 20
#define SPAWN_ZONE_W 4
#define SPAWN_ZONE_H 2
void rr_simulation_init(struct rr_simulation *this)
{
    memset(this, 0, sizeof *this);
    EntityIdx id = rr_simulation_alloc_entity(this);
    struct rr_component_arena *arena =
        rr_simulation_add_arena(this, id);
    //rr_component_arena_set_radius(arena_component, RR_ARENA_LENGTH);
    arena->grid = &RR_MAZE_HELL_CREEK[0][0];
    arena->maze_dim = RR_MAZE_DIM;
    arena->grid_size = RR_MAZE_GRID_SIZE;
    rr_component_arena_spatial_hash_init(arena, this);
    set_respawn_zone(&arena->respawn_zone, SPAWN_ZONE_X, SPAWN_ZONE_Y, SPAWN_ZONE_W, SPAWN_ZONE_H);
    //set_special_zone(0, rr_mob_id_tree, 40, 40, 8, 8);
    //printf("simulation size: %lu\n", sizeof *this);
    //printf("spatial hash size: %lu\n", sizeof *this->grid);

#define XX(COMPONENT, ID)                                                      \
    //printf(#COMPONENT);                                                        \
    printf(" size is %lu\n", sizeof *this->COMPONENT##_components);
    RR_FOR_EACH_COMPONENT;
#undef XX
}

static void spawn_mob(struct rr_simulation *this, uint32_t grid_x, uint32_t grid_y)
{
    struct rr_component_arena *arena = rr_simulation_get_arena(this, 1);
    struct rr_maze_grid *grid = rr_component_arena_get_grid(arena, grid_x, grid_y);
    uint8_t id;
    if (grid->is_special)
        id = grid->special_id;
    else
        id = get_spawn_id(this->biome, grid);
    uint8_t rarity = get_spawn_rarity(grid->difficulty);
    if (!should_spawn_at(id, rarity))
        return;
    struct rr_vector pos = {(grid_x + rr_frand()) * RR_MAZE_GRID_SIZE, (grid_y + rr_frand()) * RR_MAZE_GRID_SIZE};
    EntityIdx mob_id = rr_simulation_alloc_mob(this, 1, pos.x, pos.y, id, rarity,
                                               rr_simulation_team_id_mobs);
    rr_simulation_get_mob(this, mob_id)->zone = grid;
    grid->grid_points += RR_MOB_DIFFICULTY_COEFFICIENTS[id];
}

#ifdef RIVET_BUILD
#define GRID_MOB_LIMIT(DIFFICULTY, PLAYER_COUNT) \
    (10 - (DIFFICULTY) * 0.08) * ((PLAYER_COUNT + 1) * 0.5) + 4
#else
#define GRID_MOB_LIMIT(DIFFICULTY, PLAYER_COUNT) \
    10
#endif

static void count_flower_vicinity(EntityIdx entity, void *_simulation)
{
    struct rr_simulation *this = _simulation;
    struct rr_component_arena *arena = rr_simulation_get_arena(this, 1);
    struct rr_component_physical *physical = rr_simulation_get_physical(this, entity);
    uint32_t sx = rr_fclamp(physical->x - 1250, 0, arena->grid_size * arena->maze_dim) / arena->grid_size;
    uint32_t sy = rr_fclamp(physical->y - 1250, 0, arena->grid_size * arena->maze_dim) / arena->grid_size;
    uint32_t ex = rr_fclamp(physical->x + 1250, 0, arena->grid_size * arena->maze_dim) / arena->grid_size;
    uint32_t ey = rr_fclamp(physical->y + 1250, 0, arena->grid_size * arena->maze_dim) / arena->grid_size;
    for (uint32_t x = sx; x <= ex; ++x)
        for (uint32_t y = sy; y <= ey; ++y)
            ++rr_component_arena_get_grid(arena, x, y)->player_count;
}

static void despawn_mob(EntityIdx entity, void *_simulation)
{
    struct rr_simulation *this = _simulation;
    struct rr_component_arena *arena = rr_simulation_get_arena(this, 1);
    struct rr_component_physical *physical = rr_simulation_get_physical(this, entity);
    if (rr_component_arena_get_grid(arena, physical->x / arena->grid_size, physical->y / arena->grid_size)->player_count == 0)
    {
        rr_simulation_request_entity_deletion(this, entity);
    }
}

static void tick_wave(struct rr_simulation *this)
{
    struct rr_component_arena *arena = rr_simulation_get_arena(this, 1);
    for (uint32_t i = 0; i < RR_MAZE_DIM * RR_MAZE_DIM; ++i)
        arena->grid[i].player_count = 0;
    rr_simulation_for_each_flower(this, this, count_flower_vicinity);
    rr_simulation_for_each_mob(this, this, despawn_mob);
    for (uint32_t grid_x = 0; grid_x < RR_MAZE_DIM; ++grid_x)
    {
        for (uint32_t grid_y = 0; grid_y < RR_MAZE_DIM; ++grid_y)
        {
            //if (grid_y == SPAWN_ZONE_Y && (grid_x >= SPAWN_ZONE_X && grid_x < SPAWN_ZONE_W + SPAWN_ZONE_X))
                //grid_y += SPAWN_ZONE_H;
            struct rr_maze_grid *grid = rr_component_arena_get_grid(arena, grid_x, grid_y);
            if (grid->player_count == 0)
                continue;
            if (grid->value == 0 || (grid->value & 8))
                continue;
            if (grid->grid_points >= GRID_MOB_LIMIT(grid->difficulty, grid->player_count))
                continue;
            if (rand() % 25 == 0)
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
    this->animation_length = 0;
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
    return this->entity_tracker[(EntityIdx) hash] && this->entity_hash_tracker[(EntityIdx) hash] == (hash >> 16);
}

EntityHash rr_simulation_get_entity_hash(struct rr_simulation *this, EntityIdx id)
{
    return ((uint32_t)(this->entity_hash_tracker[id]) << 16) | id;
}