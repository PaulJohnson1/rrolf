#include <Server/Simulation.h>

#include <assert.h>
#include <inttypes.h>
#include <math.h>
#include <stdlib.h>
#include <string.h>
#include <sys/time.h>

#include <Server/SpatialHash.h>
#include <Server/System/Ai.h>
#include <Server/System/Centipede.h>
#include <Server/System/CollisionDetection.h>
#include <Server/System/CollisionResolution.h>
#include <Server/System/Drops.h>
#include <Server/System/Health.h>
#include <Server/System/MapBoundary.h>
#include <Server/System/PetalBehavior.h>
#include <Server/System/Respawn.h>
#include <Server/System/Velocity.h>
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
    this->wave_points = get_points_from_wave(1);

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
    uint8_t id = get_id_from_wave(arena->wave);
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

EntityIdx rr_simulation_alloc_mob(struct rr_simulation *this,
                                  enum rr_mob_id mob_id,
                                  enum rr_rarity_id rarity_id,
                                  enum rr_simulation_team_id team_id)
{
    EntityIdx entity = rr_simulation_alloc_entity(this);

    struct rr_component_arena *arena = rr_simulation_get_arena(this, 1);
    if (team_id == rr_simulation_team_id_mobs)
    {
        arena->mob_count++;
        arena->mob_counters[mob_id * rr_rarity_id_max + rarity_id]++;
    }

    struct rr_component_mob *mob = rr_simulation_add_mob(this, entity);
    struct rr_component_physical *physical =
        rr_simulation_add_physical(this, entity);
    struct rr_component_health *health = rr_simulation_add_health(this, entity);
    struct rr_component_relations *relations =
        rr_simulation_add_relations(this, entity);
    struct rr_component_ai *ai = rr_simulation_add_ai(this, entity);
    // init team elsewhere
    rr_component_mob_set_id(mob, mob_id);
    rr_component_mob_set_rarity(mob, rarity_id);
    struct rr_mob_rarity_scale const *rarity_scale =
        RR_MOB_RARITY_SCALING + rarity_id;
    struct rr_mob_data const *mob_data = RR_MOB_DATA + mob_id;
    rr_component_physical_set_radius(physical,
                                     mob_data->radius * rarity_scale->radius);
    physical->friction = 0.8;
    physical->mass = 100.0f * RR_MOB_RARITY_SCALING[rarity_id].damage;
    rr_component_health_set_max_health(health,
                                       mob_data->health * rarity_scale->health);
    rr_component_health_set_health(health,
                                   mob_data->health * rarity_scale->health);
    health->damage = mob_data->damage * rarity_scale->damage;

    rr_component_relations_set_team(relations, team_id);

    switch (mob_id)
    {
    case rr_mob_id_pteranodon:
        ai->ai_aggro_type = rr_ai_aggro_type_pteranodon;
        break;
    case rr_mob_id_triceratops:
        ai->ai_aggro_type = rr_ai_aggro_type_triceratops;
        break;
    case rr_mob_id_fern:
    case rr_mob_id_stump:
        ai->ai_aggro_type = rr_ai_aggro_type_none;
        break;
    case rr_mob_id_trex:
    case rr_mob_id_dakotaraptor:
        ai->ai_aggro_type = rr_ai_aggro_type_t_rex;
        break;
    case rr_mob_id_pachycephalosaurus:
        ai->aggro_type = rr_ai_aggro_type_pachycephalosaurus;
        break;
    case rr_mob_id_spinosaurus_head:
    case rr_mob_id_spinosaurus_body:
    case rr_mob_id_ornithomimus:
        ai->ai_aggro_type = rr_ai_aggro_type_default;
        break;
    default:
        RR_UNREACHABLE("forgot to set ai aggro type");
    };

    if (mob_id == rr_mob_id_spinosaurus_head)
    {
        // ai->ai_type = rr_ai_type_neutral;
        EntityIdx prev_node = entity;
        struct rr_component_centipede *centipede =
            rr_simulation_add_centipede(this, entity);
        struct rr_vector extension;
        rr_vector_from_polar(&extension, physical->radius * 2, physical->angle);
        EntityIdx new_entity = RR_NULL_ENTITY;
        for (uint64_t i = 0; i < 5; ++i)
        {
            new_entity = rr_simulation_alloc_mob(
                this, rr_mob_id_spinosaurus_body, rarity_id, team_id);
            centipede->child_node = new_entity;
            centipede = rr_simulation_add_centipede(this, new_entity);
            struct rr_component_physical *new_phys =
                rr_simulation_get_physical(this, new_entity);
            rr_component_physical_set_x(new_phys,
                                        physical->x + extension.x * (i + 1));
            rr_component_physical_set_y(new_phys,
                                        physical->y + extension.y * (i + 1));
            centipede->parent_node = entity;
            entity = new_entity;
        }
    }

    return entity;
}

EntityIdx rr_simulation_alloc_entity(struct rr_simulation *this)
{
    for (EntityIdx i = 1; i < RR_MAX_ENTITY_COUNT; i++)
    {
        if (!rr_simulation_has_entity(this, i))
        {
            if (rr_bitset_get_bit(this->recently_deleted, i))
                continue;
            rr_bitset_set(this->entity_tracker, i);
#ifndef NDEBUG
            printf("created with id %d\n", i);
#endif
            return i;
        }
    }

    RR_UNREACHABLE("ran out of entity ids");
}

struct rr_protocol_for_each_function_captures
{
    struct rr_simulation *simulation;
    struct proto_bug *encoder;
    struct rr_component_player_info *player_info;
    uint8_t *entities_in_view;
};

void rr_simulation_write_entity_function(uint64_t _id, void *_captures)
{
    EntityIdx id = _id;
    struct rr_protocol_for_each_function_captures *captures = _captures;
    struct rr_simulation *simulation = captures->simulation;
    struct proto_bug *encoder = captures->encoder;
    struct rr_component_player_info *player_info = captures->player_info;
    uint8_t *new_entities_in_view = captures->entities_in_view;

    proto_bug_write_varuint(encoder, id, "entity update id");

    uint8_t is_creation = 0;

    if (!rr_bitset_get_bit(player_info->entities_in_view, id))
    {
        is_creation = 1;
        rr_bitset_set(player_info->entities_in_view, id);
    }

    uint32_t component_flags = 0;
    if (is_creation)
    {
#define XX(COMPONENT, ID)                                                      \
    component_flags |= rr_simulation_has_##COMPONENT(simulation, id) << ID;
        RR_FOR_EACH_COMPONENT;
#undef XX
    }
    else
    {
#define XX(COMPONENT, ID)                                                      \
    component_flags |= rr_simulation_has_##COMPONENT(simulation, id) << ID;
        RR_FOR_EACH_COMPONENT;
#undef XX
    }

    proto_bug_write_varuint(encoder, component_flags, "entity component flags");
#define XX(COMPONENT, ID)                                                      \
    if (component_flags & (1 << ID))                                           \
        rr_component_##COMPONENT##_write(                                      \
            rr_simulation_get_##COMPONENT(simulation, id), encoder,            \
            is_creation);
    RR_FOR_EACH_COMPONENT;
#undef XX
}

struct rr_simulation_find_entities_in_view_for_each_function_captures
{
    int32_t view_width;
    int32_t view_height;
    int32_t view_x;
    int32_t view_y;
    uint8_t *entities_in_view;
    struct rr_component_player_info *player_info;
    struct rr_simulation *simulation;
};

void rr_simulation_find_entities_in_view_for_each_function(EntityIdx entity,
                                                           void *data)
{
    struct rr_simulation_find_entities_in_view_for_each_function_captures
        *captures = data;
    struct rr_simulation *simulation = captures->simulation;

    if (!rr_simulation_has_entity(simulation, entity))
        return;

    struct rr_component_physical *physical =
        rr_simulation_get_physical(simulation, entity);

    if (physical->x + physical->radius <
            captures->view_x - captures->view_width ||
        physical->x - physical->radius >
            captures->view_x + captures->view_width ||
        physical->y + physical->radius <
            captures->view_y - captures->view_height ||
        physical->y - physical->radius >
            captures->view_y + captures->view_height)
        return;

    rr_bitset_set(captures->entities_in_view, entity);
    if (rr_simulation_has_drop(simulation, entity))
    {
        struct rr_component_drop *drop =
            rr_simulation_get_drop(simulation, entity);
        drop->inspecting = captures->player_info->parent_id;
        if (rr_bitset_get(&drop->picked_up_this_tick[0], drop->inspecting))
            drop->protocol_state |= 4;
        else
            drop->protocol_state &= 3;
    }
}

void rr_simulation_find_entities_in_view(
    struct rr_simulation *this, struct rr_component_player_info *player_info,
    uint8_t *entities_in_view)
{
    struct rr_simulation_find_entities_in_view_for_each_function_captures
        captures;
    memset(&captures, 0, sizeof captures);
    captures.view_width = (int32_t)(1280.0f / player_info->camera_fov);
    captures.view_height = (int32_t)(720.0f / player_info->camera_fov);
    captures.view_x = (int32_t)player_info->camera_x;
    captures.view_y = (int32_t)player_info->camera_y;
    captures.entities_in_view = entities_in_view;
    captures.player_info = player_info;
    captures.simulation = this;

    rr_bitset_set(entities_in_view, player_info->parent_id);
    // don't add the player into the view if it is null (player died lmfao skill
    // issue)
    if (player_info->flower_id != RR_NULL_ENTITY)
        rr_bitset_set(entities_in_view, player_info->flower_id);

    rr_bitset_set(captures.entities_in_view, 1);
    rr_simulation_for_each_physical(
        this, &captures, rr_simulation_find_entities_in_view_for_each_function);
}

void rr_simulation_write_entity_deletions_function(uint64_t _id,
                                                   void *_captures)
{
    EntityIdx id = _id;
    struct rr_protocol_for_each_function_captures *captures = _captures;
    struct rr_component_player_info *player_info = captures->player_info;
    struct proto_bug *encoder = captures->encoder;
    uint8_t *new_entities_in_view = captures->entities_in_view;

    if (!rr_bitset_get_bit(new_entities_in_view, id))
    {
        // deletion spotted!
        rr_bitset_unset(player_info->entities_in_view, id);
        proto_bug_write_varuint(encoder, id, "entity deletion id");
    }
}

void rr_simulation_write_binary(struct rr_simulation *this,
                                struct proto_bug *encoder,
                                struct rr_component_player_info *player_info)
{
    uint8_t new_entities_in_view[RR_BITSET_ROUND(RR_MAX_ENTITY_COUNT)];
    memset(new_entities_in_view, 0,
           (RR_BITSET_ROUND(RR_MAX_ENTITY_COUNT)) *
               (sizeof *new_entities_in_view));

    rr_simulation_find_entities_in_view(this, player_info,
                                        &new_entities_in_view[0]);
    for (uint64_t i = 0; i < RR_MAX_ENTITY_COUNT; i++)
        if (rr_bitset_get_bit(this->player_info_tracker, i))
        {
            rr_bitset_set(new_entities_in_view, i);
            struct rr_component_player_info *p_info =
                rr_simulation_get_player_info(this, i);
            if (p_info->flower_id != RR_NULL_ENTITY)
                rr_bitset_set(new_entities_in_view, p_info->flower_id);
        }

    struct rr_protocol_for_each_function_captures captures;
    captures.simulation = this;
    captures.encoder = encoder;
    captures.player_info = player_info;
    captures.entities_in_view = new_entities_in_view;

    rr_bitset_for_each_bit(&player_info->entities_in_view[0],
                           &player_info->entities_in_view[0] +
                               (RR_BITSET_ROUND(RR_MAX_ENTITY_COUNT)),
                           &captures,
                           rr_simulation_write_entity_deletions_function);
    proto_bug_write_varuint(
        encoder, RR_NULL_ENTITY,
        "entity deletion id"); // null terminate deletion list

    rr_bitset_for_each_bit(new_entities_in_view,
                           new_entities_in_view +
                               (RR_BITSET_ROUND(RR_MAX_ENTITY_COUNT)),
                           &captures, rr_simulation_write_entity_function);
    proto_bug_write_varuint(encoder, RR_NULL_ENTITY,
                            "entity update id"); // null terminate update list
    proto_bug_write_varuint(encoder, player_info->parent_id,
                            "pinfo id");         // send client's pinfo
    proto_bug_write_uint8(encoder, this->game_over, "game over");
}

//#define RR_TIME_BLOCK(LABEL, CODE)                                                                 \
    {                                                                                              \
                                                                                                   \
        struct timeval start;                                                                      \
        struct timeval end;                                                                        \
        gettimeofday(&start, NULL);                                                                \
        CODE;                                                                                      \
        gettimeofday(&end, NULL);                                                                  \
        long elapsed_time = (end.tv_sec - start.tv_sec) * 1000000 + (end.tv_usec - start.tv_usec); \
        printf(LABEL " took \t\t\t%lu time\n", elapsed_time);                                      \
    }
#define RR_TIME_BLOCK(_, CODE)                                                 \
    {                                                                          \
        CODE;                                                                  \
    };

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
    uint32_t mob_count = rand() % 3 + 3; // random for some variety
    struct rr_vector central_position = find_position_away_from_players(this);
    struct rr_component_arena *arena = rr_simulation_get_arena(this, 1);

    uint8_t id = get_id_from_wave(arena->wave);
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

        uint8_t id = get_id_from_wave(arena->wave);
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

static void tick_wave(struct rr_simulation *this)
{
    uint8_t any_alive = 0;

    for (uint32_t i = 0; i < sizeof this->flower_tracker; ++i)
        if (this->flower_tracker[i])
        {
            any_alive = 1;
            break;
        }

    if (!any_alive)
        this->game_over = 1;

    struct rr_component_arena *arena = rr_simulation_get_arena(this, 1);

    uint32_t wave_length = ((arena->wave < 3 ? arena->wave : 3) * 15);
    uint32_t spawn_time = 1;
    uint32_t after_wave_time = 1;
    // idle spawning
    if (arena->wave_tick <= (wave_length * 25 * spawn_time))
    {
        if (arena->wave_tick % 18 == 0)
            spawn_random_mob(this);

        for (uint64_t i = 0; i < 5; i++)
            if (arena->wave_tick == (wave_length * 25 * spawn_time) * i / 5)
                spawn_mob_cluster(this);
        
        if (arena->wave_tick == (wave_length * 25 * spawn_time))
            spawn_mob_swarm(this);
    }
    else if (arena->wave_tick >=
                 wave_length * 25 * (spawn_time + after_wave_time) ||
             arena->mob_count <= 10)
    {
        printf("wave %d done\n", arena->wave);
        rr_component_arena_set_wave(arena, arena->wave + 1);
        arena->wave_tick = 0;
        this->wave_points = get_points_from_wave(arena->wave);
        RR_TIME_BLOCK("respawn", { rr_system_respawn_tick(this); });
    }
    rr_component_arena_set_wave_tick(arena, arena->wave_tick + 1);
}

struct count_mob_captures
{
    struct rr_simulation *simulation;
    uint64_t *count;
};

static void count_mobs(EntityIdx a, void *b)
{
    struct count_mob_captures *c = b;
    struct rr_component_relations *r = rr_simulation_get_relations(c->simulation, a);
    if (r->team != rr_simulation_team_id_players)
        ++*c->count;
}

void rr_simulation_tick(struct rr_simulation *this)
{
    RR_TIME_BLOCK("collision_detection",
                  { rr_system_collision_detection_tick(this); });
    RR_TIME_BLOCK("ai", { rr_system_ai_tick(this); });
    RR_TIME_BLOCK("drops", { rr_system_drops_tick(this); });
    RR_TIME_BLOCK("petal_behavior", { rr_system_petal_behavior_tick(this); });
    RR_TIME_BLOCK("collision_resolution",
                  { rr_system_collision_resolution_tick(this); });
    RR_TIME_BLOCK("velocity", { rr_system_velocity_tick(this); });
    RR_TIME_BLOCK("centipede", { rr_system_centipede_tick(this); });
    RR_TIME_BLOCK("map_boundary", { rr_system_map_boundary_tick(this); });
    RR_TIME_BLOCK("health", { rr_system_health_tick(this); });

    struct count_mob_captures captures;
    captures.simulation = this;
    if (!this->game_over)
    {
        /*
        uint64_t count;
        captures.count = &count;
        do {
            tick_wave(this);
            count = 0;
            rr_simulation_for_each_mob(this, &captures, count_mobs);
        } while (count < 9);
        */
       tick_wave(this);
    }
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
