#include <Server/Simulation.h>

#include <assert.h>
#include <inttypes.h>
#include <math.h>
#include <stdlib.h>
#include <string.h>
#include <sys/time.h>

#include <Server/EntityAllocation.h>
#include <Server/SpatialHash.h>
#include <Server/System/Ai.h>
#include <Server/System/Camera.h>
#include <Server/System/Centipede.h>
#include <Server/System/CollisionDetection.h>
#include <Server/System/CollisionResolution.h>
#include <Server/System/Drops.h>
#include <Server/System/Health.h>
#include <Server/System/PetalBehavior.h>
#include <Server/System/Respawn.h>
#include <Server/System/Velocity.h>
#include <Server/System/Web.h>
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
    struct rr_maze_grid (*grid)[48] = biome == 0 ? RR_MAZE_HELL_CREEK : RR_MAZE_HELL_CREEK;
    for (uint32_t Y = 0; Y < h; ++Y)
        for (uint32_t X = 0; X < h; ++X)
        {
            grid[Y+y][X+x].is_special = 1;
            grid[Y+y][X+x].special_id = id;
        }
}
#define SPAWN_ZONE_X 14
#define SPAWN_ZONE_Y 38
#define SPAWN_ZONE_W 5
#define SPAWN_ZONE_H 3
void rr_simulation_init(struct rr_simulation *this)
{
    memset(this, 0, sizeof *this);
    this->grid = malloc(sizeof *this->grid);
    rr_spatial_hash_init(this->grid);
    this->grid->simulation = this;
    EntityIdx id = rr_simulation_alloc_entity(this);
    struct rr_component_arena *arena_component =
        rr_simulation_add_arena(this, id);
    rr_component_arena_set_radius(arena_component, RR_ARENA_LENGTH);
    set_respawn_zone(&this->respawn_zone, SPAWN_ZONE_X, SPAWN_ZONE_Y, SPAWN_ZONE_W, SPAWN_ZONE_H);
    set_special_zone(0, rr_mob_id_tree, 40, 40, 8, 8);
    printf("simulation size: %lu\n", sizeof *this);

#define XX(COMPONENT, ID)                                                      \
    printf(#COMPONENT);                                                        \
    printf(" size is %lu\n", sizeof *this->COMPONENT##_components);
    RR_FOR_EACH_COMPONENT;
#undef XX
}

static void rr_simulation_pending_deletion_free_components(uint64_t id,
                                                           void *_simulation)
{
    struct rr_simulation *simulation = _simulation;
    __rr_simulation_pending_deletion_free_components(id, simulation);
}

static struct rr_vector
find_position_away_from_players(struct rr_simulation *this)
{
    struct rr_vector ret;
    uint8_t invalid = 1;
    while (invalid)
    {
        //float rad = sqrtf(rr_frand()) * RR_ARENA_LENGTH;
        //float angle = rr_frand() * 2 * M_PI;
        ret.x = rr_frand() * RR_ARENA_LENGTH;//rad * cosf(angle);
        ret.y = rr_frand() * RR_ARENA_LENGTH;//rad * sinf(angle);
        invalid = 0;
        for (uint16_t i = 0; i < this->flower_count; ++i)
        {
            struct rr_component_physical *physical =
                rr_simulation_get_physical(this, this->flower_vector[i]);
            struct rr_vector delta = {ret.x - physical->x, ret.y - physical->y};
            if (rr_vector_get_magnitude(&delta) < 500)
            {
                invalid = 1;
                break;
            }
        }
    }
    return ret;
}

static void spawn_mob(struct rr_simulation *this, uint32_t grid_x, uint32_t grid_y)
{
    struct rr_maze_grid *grid = &(RR_MAZE_HELL_CREEK[grid_y][grid_x]);
    struct rr_component_arena *arena = rr_simulation_get_arena(this, 1);
    uint8_t id;
    if (grid->is_special)
        id = grid->special_id;
    else
        id = get_spawn_id(this->biome, grid);
    uint8_t rarity = get_spawn_rarity(grid->difficulty);
    if (!should_spawn_at(id, rarity))
        return;
    struct rr_vector pos = {(grid_x + rr_frand()) * RR_MAZE_GRID_SIZE, (grid_y + rr_frand()) * RR_MAZE_GRID_SIZE};
    EntityIdx mob_id = rr_simulation_alloc_mob(this, pos.x, pos.y, id, rarity,
                                               rr_simulation_team_id_mobs);
    rr_simulation_get_mob(this, mob_id)->zone = grid;
    ++grid->mob_count;
}



#define RR_TIME_BLOCK(_, CODE)                                                 \
    {                                                                          \
        CODE;                                                                  \
    };

#define GRID_MOB_LIMIT 2

static void tick_wave(struct rr_simulation *this)
{
    for (uint32_t grid_x = 0; grid_x < RR_MAZE_DIM; ++grid_x)
    {
        if (grid_x == SPAWN_ZONE_X)
            grid_x += SPAWN_ZONE_W;
        for (uint32_t grid_y = 0; grid_y < RR_MAZE_DIM; ++grid_y)
        {
            if (grid_y == SPAWN_ZONE_Y)
                grid_y += SPAWN_ZONE_H;
            if (RR_MAZE_HELL_CREEK[grid_y][grid_x].value != 1)
                continue;
            if (RR_MAZE_HELL_CREEK[grid_y][grid_x].mob_count >= GRID_MOB_LIMIT)
                continue;
            if (rand() % 75 == 0)
                spawn_mob(this, grid_x, grid_y);
        }
    }
}

void rr_simulation_tick(struct rr_simulation *this)
{
    this->animation_length = 0;
    rr_simulation_create_component_vectors(this);
    // printf("%d %d %d\n", this->physical_count, this->mob_count,
    // this->health_count);
    RR_TIME_BLOCK("collision_detection",
                  { rr_system_collision_detection_tick(this); });
    RR_TIME_BLOCK("ai", { rr_system_ai_tick(this); });
    RR_TIME_BLOCK("drops", { rr_system_drops_tick(this); });
    RR_TIME_BLOCK("petal_behavior", { rr_system_petal_behavior_tick(this); });
    RR_TIME_BLOCK("collision_resolution",
                  { rr_system_collision_resolution_tick(this); });
    RR_TIME_BLOCK("web", { rr_system_web_tick(this); });
    RR_TIME_BLOCK("velocity", { rr_system_velocity_tick(this); });
    RR_TIME_BLOCK("centipede", { rr_system_centipede_tick(this); });
    RR_TIME_BLOCK("health", { rr_system_health_tick(this); });
    RR_TIME_BLOCK("camera", { rr_system_camera_tick(this); });

    tick_wave(this);
    // delete pending deletions
    rr_bitset_for_each_bit(
        this->pending_deletions,
        this->pending_deletions + (RR_BITSET_ROUND(RR_MAX_ENTITY_COUNT)), this,
        rr_simulation_pending_deletion_free_components);
    memset(this->recently_deleted, 0,
           RR_BITSET_ROUND(RR_MAX_ENTITY_COUNT) *
               sizeof *this->recently_deleted);
    rr_bitset_for_each_bit(this->pending_deletions,
                           this->pending_deletions +
                               (RR_BITSET_ROUND(RR_MAX_ENTITY_COUNT)),
                           this, __rr_simulation_pending_deletion_unset_entity);
    memset(this->pending_deletions, 0,
           RR_BITSET_ROUND(RR_MAX_ENTITY_COUNT) *
               sizeof *this->pending_deletions);
}
