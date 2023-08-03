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
#include <Server/System/MapBoundary.h>
#include <Server/System/PetalBehavior.h>
#include <Server/System/Respawn.h>
#include <Server/System/Velocity.h>
#include <Server/System/Web.h>
#include <Server/Waves.h>
#include <Shared/Bitset.h>
#include <Shared/Utilities.h>
#include <Shared/pb.h>

void rr_simulation_init(struct rr_simulation *this)
{
    memset(this, 0, sizeof *this);
    this->grid = malloc(sizeof *this->grid);
    rr_spatial_hash_init(this->grid);
    this->grid->simulation = this;
    rr_simulation_alloc_entity(this);
    struct rr_component_arena *arena_component =
        rr_simulation_add_arena(this, 1);
    rr_component_arena_set_radius(arena_component, RR_ARENA_RADIUS);
    rr_component_arena_set_wave(arena_component, 1);

    printf("simulation size: %lu\n", sizeof *this);

#define XX(COMPONENT, ID)                                                      \
    printf(#COMPONENT);                                                        \
    printf(" size is %lu\n", sizeof *this->COMPONENT##_components);
    RR_FOR_EACH_COMPONENT;
#undef XX
}

static void spawn_random_mob(struct rr_simulation *this)
{
    struct rr_component_arena *arena = rr_simulation_get_arena(this, 1);
    uint8_t id = get_id_from_wave(arena->wave, this->special_wave_id);
    uint8_t rarity = get_rarity_from_wave(arena->wave);
    if (!should_spawn_at(arena->wave, id, rarity))
        return;
    if (RR_MOB_DIFFICULTY_COEFFICIENTS[id] > this->wave_points)
        return;
    this->wave_points -= RR_MOB_DIFFICULTY_COEFFICIENTS[id]; 
    EntityIdx mob_id =
        rr_simulation_alloc_mob(this, id, rarity, rr_simulation_team_id_mobs);
    struct rr_component_physical *physical =
        rr_simulation_get_physical(this, mob_id);
    float distance = sqrt(rr_frand()) * arena->radius;
    float angle = rr_frand() * M_PI * 2.0f;
    rr_component_physical_set_x(physical, cos(angle) * distance);
    rr_component_physical_set_y(physical, sin(angle) * distance);
}

#define RR_TIME_BLOCK(_, CODE)                                                 \
    { CODE; };

static void rr_simulation_pending_deletion_free_components(uint64_t id,
                                                           void *_simulation)
{
    struct rr_simulation *simulation = _simulation;
    if (rr_simulation_has_physical(simulation, id))
    {
        struct rr_component_physical *physical =
            rr_simulation_get_physical(simulation, id);
        if (physical->has_deletion_animation)
        {
            __rr_simulation_pending_deletion_free_components(id, _simulation);
            rr_bitset_unset(simulation->pending_deletions, id);
            rr_component_physical_set_server_animation_tick(physical, 5);
            physical->ticked_animation = 1;
        }
        else if (physical->server_animation_tick != 0 &&
                 physical->ticked_animation == 0)
        {
            rr_bitset_unset(simulation->pending_deletions, id);
            rr_component_physical_set_server_animation_tick(
                physical, physical->server_animation_tick - 1);
            physical->ticked_animation = 1;
        }
        if (rr_simulation_has_health(simulation, id))
            rr_component_health_set_health(rr_simulation_get_health(simulation, id), 0);
    }
    else
    {
        __rr_simulation_pending_deletion_free_components(id, _simulation);
    }
}

struct simulation_id
{
    struct rr_simulation *simulation;
    struct rr_vector test_position;
    uint8_t invalid;
};

// TODO: make it work
static void position_finder(EntityIdx id, void *_captures)
{
    struct simulation_id *captures = _captures;
    struct rr_component_physical *physical =
        rr_simulation_get_physical(captures->simulation, id);

    struct rr_vector delta = {physical->x, physical->y};
    rr_vector_sub(&delta, &captures->test_position);

    if (delta.x * delta.x + delta.y * delta.y < 500 * 500)
        captures->invalid = 1;
}

static struct rr_vector
find_position_away_from_players(struct rr_simulation *this)
{
    struct simulation_id captures;
    captures.simulation = this;
    do
    {
        float distance = sqrt(rr_frand()) * 1650.0f;
        float angle = rr_frand() * M_PI * 2;
        struct rr_vector r = {distance * cosf(angle), distance * sinf(angle)};
        captures.test_position = r;
        captures.invalid = 0;
        rr_simulation_for_each_flower(this, &captures, position_finder);
    } while (captures.invalid);

    return captures.test_position;
}

// spawn 4-8 of some mob type in around the same position, avoid players
static void spawn_mob_cluster(struct rr_simulation *this)
{
    uint32_t mob_count = rand() % 3 + 2; // random for some variety
    struct rr_vector central_position = find_position_away_from_players(this);
    struct rr_component_arena *arena = rr_simulation_get_arena(this, 1);

    uint8_t id = get_id_from_wave(arena->wave, this->special_wave_id);
    for (uint64_t i = 0; i < mob_count; ++i)
    {
        uint8_t rarity = get_rarity_from_wave(arena->wave);
        if (!should_spawn_at(arena->wave, id, rarity))
            continue;
        if (RR_MOB_DIFFICULTY_COEFFICIENTS[id] > this->wave_points)
            return;
        this->wave_points -= RR_MOB_DIFFICULTY_COEFFICIENTS[id];
        struct rr_vector delta = {rand() % 200 - 100, rand() % 200 - 100};
        // mob position = delta + central_postiion;

        EntityIdx mob_id = rr_simulation_alloc_mob(this, id, rarity,
                                                   rr_simulation_team_id_mobs);
        struct rr_component_physical *physical =
            rr_simulation_get_physical(this, mob_id);
        rr_component_physical_set_x(physical, central_position.x + delta.x);
        rr_component_physical_set_y(physical, central_position.y + delta.y);
    }
}

// spawn maybe like 50 mobs UNIFORM DIST, NOT CLUSTERED or spawn 12 clusters
static void spawn_mob_swarm(struct rr_simulation *this)
{
    uint32_t mob_attempts = 0;
    while (mob_attempts < 100 && this->wave_points > 2) {
        ++mob_attempts;
        struct rr_vector position = find_position_away_from_players(this);
        struct rr_component_arena *arena = rr_simulation_get_arena(this, 1);

        uint8_t id = get_id_from_wave(arena->wave, this->special_wave_id);
        uint8_t rarity = get_rarity_from_wave(arena->wave);
        if (!should_spawn_at(arena->wave, id, rarity))
            continue;
        if (RR_MOB_DIFFICULTY_COEFFICIENTS[id] > this->wave_points)
            return;
        this->wave_points -= RR_MOB_DIFFICULTY_COEFFICIENTS[id];
        EntityIdx mob_id = rr_simulation_alloc_mob(this, id, rarity,
                                                   rr_simulation_team_id_mobs);
        struct rr_component_physical *physical =
            rr_simulation_get_physical(this, mob_id);
        rr_component_physical_set_x(physical, position.x);
        rr_component_physical_set_y(physical, position.y);
    }
}

#define SPECIAL_WAVE_COUNT 3

static void tick_wave(struct rr_simulation *this)
{
    if (this->flower_count == 0)
        this->game_over = 1;

    struct rr_component_arena *arena = rr_simulation_get_arena(this, 1);

    uint32_t wave_length = ((arena->wave < 3 ? arena->wave : 3) * 15);
    uint32_t spawn_time = 1;
    uint32_t after_wave_time = 1;
    // idle spawning
    if (arena->wave_tick <= (wave_length * 25 * spawn_time))
    {
        if (arena->wave_tick % 36 == 0)
            spawn_random_mob(this);

        for (uint64_t i = 0; i < 4; i++)
            if (arena->wave_tick + 1 == (wave_length * 25 * spawn_time) * i / 4)
                spawn_mob_cluster(this);
        
        if (arena->wave_tick == (wave_length * 25 * spawn_time))
            spawn_mob_swarm(this);
    }
    else if (arena->wave_tick >=
                 wave_length * 25 * (spawn_time + after_wave_time) ||
             arena->mob_count <= 10)
    {
        rr_component_arena_set_wave(arena, arena->wave + 1);
        arena->wave_tick = 0;
        this->wave_points = get_points_from_wave(arena->wave, this->player_info_count);
        RR_TIME_BLOCK("respawn", { rr_system_respawn_tick(this); });
        if (rr_frand() > 0.2496843483753245)
            this->special_wave_id = 0;
        else
            this->special_wave_id = 1 + (rr_frand() * SPECIAL_WAVE_COUNT);
    }
    rr_component_arena_set_wave_tick(arena, arena->wave_tick + 1);
}

void rr_simulation_tick(struct rr_simulation *this)
{
    rr_simulation_create_component_vectors(this);
    //printf("%d %d %d\n", this->physical_count, this->mob_count, this->health_count);
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
    RR_TIME_BLOCK("map_boundary", { rr_system_map_boundary_tick(this); });
    RR_TIME_BLOCK("health", { rr_system_health_tick(this); });
    RR_TIME_BLOCK("camera", { rr_system_camera_tick(this); });
    
    if (!this->game_over)
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
