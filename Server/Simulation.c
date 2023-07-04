#include <Server/Simulation.h>

#include <assert.h>
#include <string.h>
#include <stdlib.h>
#include <math.h>
#include <sys/time.h>
#include <inttypes.h>

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
#include <Server/SpatialHash.h>
#include <Shared/Bitset.h>
#include <Shared/pb.h>
#include <Shared/Utilities.h>

void move_up_temp_test(EntityIdx entity, void *_captures)
{
    struct rr_simulation *this = _captures;
    struct rr_component_physical *physical = rr_simulation_get_physical(this, entity);
    rr_component_physical_set_x(physical, 1000);
    rr_component_physical_set_y(physical, 0);
}

static void spawn_random_mob(struct rr_simulation *this);

void rr_simulation_init(struct rr_simulation *this)
{
    memset(this, 0, sizeof *this);
    this->grid = malloc(sizeof *this->grid);
    rr_spatial_hash_init(this->grid);
    this->grid->simulation = this;
    this->arena = rr_simulation_alloc_entity(this);
    struct rr_component_arena *arena_component = rr_simulation_add_arena(this, this->arena);
    rr_component_arena_set_radius(arena_component, RR_ARENA_RADIUS);
    rr_component_arena_set_wave(arena_component, 1);

    printf("simulation size: %lu\n", sizeof *this);

#define XX(COMPONENT, ID) \
    printf(#COMPONENT);   \
    printf(" size is %lu\n", sizeof *this->COMPONENT##_components);
    RR_FOR_EACH_COMPONENT;
#undef XX
}

static void spawn_random_mob(struct rr_simulation *this)
{
    float rarity_seed = rr_frand();
    uint8_t rarity = 0;
    for (; rarity < rr_rarity_id_max - 1; ++rarity)
        if (powf(RR_DROP_RARITY_COEFFICIENTS[rarity + 1], powf(1.25, rr_simulation_get_arena(this, 1)->wave)) > rarity_seed)
            break;
    // float r = rr_frand();
    // uint8_t id = rr_mob_id_pteranodon;
    // if (r -= 0.2, r < 0)
    //     id = rr_mob_id_triceratops;
    // else if (r -= 0.2, r < 0)
    //     id = rr_mob_id_trex;
    // else if (r -= 0.25, r < 0)
    //     id = rr_mob_id_stump;
    // else if (r -= 0.15, r < 0)
    //     id = rr_mob_id_spinosaurus_head;
    // uint8_t id = rr_mob_id_stump;
    uint8_t id = rand() % rr_mob_id_max;
    if (id == rr_mob_id_spinosaurus_body)
        id = rr_mob_id_stump;
    if (id == rr_mob_id_spinosaurus_head)
        id = rr_mob_id_stump;
    EntityIdx mob_id = rr_simulation_alloc_mob(this, id, rarity);
}

EntityIdx rr_simulation_alloc_mob(struct rr_simulation *this, enum rr_mob_id mob_id, enum rr_rarity_id rarity_id)
{
    EntityIdx entity = rr_simulation_alloc_entity(this);

    struct rr_component_mob *mob = rr_simulation_add_mob(this, entity);
    struct rr_component_physical *physical = rr_simulation_add_physical(this, entity);
    struct rr_component_health *health = rr_simulation_add_health(this, entity);
    struct rr_component_relations *relations = rr_simulation_add_relations(this, entity);
    struct rr_component_ai *ai = rr_simulation_add_ai(this, entity);
    // init team elsewhere
    rr_component_mob_set_id(mob, mob_id);
    rr_component_mob_set_rarity(mob, rarity_id);
    struct rr_mob_rarity_scale const *rarity_scale = RR_MOB_RARITY_SCALING + rarity_id;
    struct rr_mob_data const *mob_data = RR_MOB_DATA + mob_id;
    float distance = sqrt(rr_frand()) * rr_simulation_get_arena(this, 1)->radius;
    float angle = rr_frand() * M_PI * 2.0f;
    rr_component_physical_set_x(physical, cos(angle) * distance);
    rr_component_physical_set_y(physical, sin(angle) * distance);
    rr_component_physical_set_radius(physical, mob_data->radius * rarity_scale->radius);
    physical->friction = 0.9;
    physical->mass = 100.0f * RR_MOB_RARITY_SCALING[rarity_id].damage;
    rr_component_health_set_max_health(health, mob_data->health * rarity_scale->health);
    rr_component_health_set_health(health, mob_data->health * rarity_scale->health);
    health->damage = mob_data->damage * rarity_scale->damage;

    rr_component_relations_set_team(relations, rr_simulation_team_id_mobs);
    switch (mob_id)
    {
    case rr_mob_id_stump:
        rr_component_physical_set_angle(physical, rr_frand() * M_PI * 2);
        ai->ai_type = rr_ai_type_static;
        break;
    case rr_mob_id_pteranodon:
    case rr_mob_id_dakotaraptor:
    case rr_mob_id_trex:
        ai->ai_type = rr_ai_type_aggressive;
        break;
    case rr_mob_id_spinosaurus_head:
        ai->ai_type = rr_ai_type_neutral;

    case rr_mob_id_spinosaurus_body:
    case rr_mob_id_triceratops:
        ai->ai_type = rr_ai_type_passive;
        break;
    default:
        RR_UNREACHABLE("forgot to set ai type");
    };

    switch (mob_id)
    {
    case rr_mob_id_pteranodon:
        ai->ai_aggro_type = rr_ai_aggro_type_pteranodon;
        break;
    case rr_mob_id_spinosaurus_head:
    case rr_mob_id_stump:
    case rr_mob_id_trex:
    case rr_mob_id_spinosaurus_body:
    case rr_mob_id_triceratops:
    case rr_mob_id_dakotaraptor:
        ai->ai_aggro_type = rr_ai_aggro_type_default;
        break;
    default:
        RR_UNREACHABLE("forgot to set ai aggro type");
    };

    if (mob_id == rr_mob_id_spinosaurus_head)
    {
        ai->ai_type = rr_ai_type_neutral;
        EntityIdx prev_node = entity;
        struct rr_component_centipede *centipede = rr_simulation_add_centipede(this, entity);
        struct rr_vector extension;
        rr_vector_from_polar(&extension, physical->radius * 2, physical->angle);
        EntityIdx new_entity = RR_NULL_ENTITY;
        for (uint64_t i = 0; i < 5; ++i)
        {
            new_entity = rr_simulation_alloc_mob(this, rr_mob_id_spinosaurus_body, rarity_id);
            centipede->child_node = new_entity;
            centipede = rr_simulation_add_centipede(this, new_entity);
            struct rr_component_physical *new_phys = rr_simulation_get_physical(this, new_entity);
            rr_component_physical_set_x(new_phys, physical->x + extension.x * (i + 1));
            rr_component_physical_set_y(new_phys, physical->y + extension.y * (i + 1));
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
#define XX(COMPONENT, ID) \
    component_flags |= rr_simulation_has_##COMPONENT(simulation, id) << ID;
        RR_FOR_EACH_COMPONENT;
#undef XX
    }
    else
    {
#define XX(COMPONENT, ID)                                                                   \
    component_flags |= (rr_simulation_has_##COMPONENT(simulation, id) &&                    \
                        rr_simulation_get_##COMPONENT(simulation, id)->protocol_state != 0) \
                       << ID;
        RR_FOR_EACH_COMPONENT;
#undef XX
    }

    proto_bug_write_varuint(encoder, component_flags, "entity component flags");
#define XX(COMPONENT, ID)            \
    if (component_flags & (1 << ID)) \
        rr_component_##COMPONENT##_write(rr_simulation_get_##COMPONENT(simulation, id), encoder, is_creation);
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

void rr_simulation_find_entities_in_view_for_each_function(EntityIdx entity, void *data)
{
    struct rr_simulation_find_entities_in_view_for_each_function_captures *captures = data;
    struct rr_simulation *simulation = captures->simulation;

    if (!rr_simulation_has_entity(simulation, entity))
        return;

    struct rr_component_physical *physical = rr_simulation_get_physical(simulation, entity);

    if (physical->x + physical->radius < captures->view_x - captures->view_width ||
        physical->x - physical->radius > captures->view_x + captures->view_width ||
        physical->y + physical->radius < captures->view_y - captures->view_height ||
        physical->y - physical->radius > captures->view_y + captures->view_height)
        return;

    rr_bitset_set(captures->entities_in_view, entity);
    if (rr_simulation_has_drop(simulation, entity))
    {
        struct rr_component_drop *drop = rr_simulation_get_drop(simulation, entity);
        drop->inspecting = captures->player_info->parent_id;
        if (rr_bitset_get(&drop->picked_up_this_tick[0], drop->inspecting))
            drop->protocol_state |= 4;
        else
            drop->protocol_state &= 3;
    }
}

void rr_simulation_find_entities_in_view(struct rr_simulation *this, struct rr_component_player_info *player_info, uint8_t *entities_in_view)
{
    struct rr_simulation_find_entities_in_view_for_each_function_captures captures;
    memset(&captures, 0, sizeof captures);
    captures.view_width = (int32_t)(1280.0f / player_info->camera_fov);
    captures.view_height = (int32_t)(720.0f / player_info->camera_fov);
    captures.view_x = (int32_t)player_info->camera_x;
    captures.view_y = (int32_t)player_info->camera_y;
    captures.entities_in_view = entities_in_view;
    captures.player_info = player_info;
    captures.simulation = this;

    rr_bitset_set(entities_in_view, player_info->parent_id);
    // don't add the player into the view if it is null (player died lmfao skill issue)
    if (player_info->flower_id != RR_NULL_ENTITY)
        rr_bitset_set(entities_in_view, player_info->flower_id);

    rr_bitset_set(captures.entities_in_view, this->arena);
    rr_simulation_for_each_physical(this, &captures, rr_simulation_find_entities_in_view_for_each_function);
}

void rr_simulation_write_entity_deletions_function(uint64_t _id, void *_captures)
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

void rr_simulation_write_binary(struct rr_simulation *this, struct proto_bug *encoder, struct rr_component_player_info *player_info)
{
    uint8_t new_entities_in_view[RR_BITSET_ROUND(RR_MAX_ENTITY_COUNT)];
    memset(new_entities_in_view, 0, (RR_BITSET_ROUND(RR_MAX_ENTITY_COUNT)) * (sizeof *new_entities_in_view));

    rr_simulation_find_entities_in_view(this, player_info, &new_entities_in_view[0]);
    for (uint64_t i = 0; i < RR_MAX_ENTITY_COUNT; i++)
        if (rr_bitset_get_bit(this->player_info_tracker, i))
        {
            rr_bitset_set(new_entities_in_view, i);
            struct rr_component_player_info *p_info = rr_simulation_get_player_info(this, i);
            if (p_info->flower_id != RR_NULL_ENTITY)
                rr_bitset_set(new_entities_in_view, p_info->flower_id);
        }

    struct rr_protocol_for_each_function_captures captures;
    captures.simulation = this;
    captures.encoder = encoder;
    captures.player_info = player_info;
    captures.entities_in_view = new_entities_in_view;

    rr_bitset_for_each_bit(&player_info->entities_in_view[0], &player_info->entities_in_view[0] + (RR_BITSET_ROUND(RR_MAX_ENTITY_COUNT)), &captures, rr_simulation_write_entity_deletions_function);
    proto_bug_write_varuint(encoder, RR_NULL_ENTITY, "entity deletion id"); // null terminate deletion list

    rr_bitset_for_each_bit(new_entities_in_view, new_entities_in_view + (RR_BITSET_ROUND(RR_MAX_ENTITY_COUNT)), &captures, rr_simulation_write_entity_function);
    proto_bug_write_varuint(encoder, RR_NULL_ENTITY, "entity update id"); // null terminate update list
    proto_bug_write_varuint(encoder, player_info->parent_id, "pinfo id"); // send client's pinfo
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
#define RR_TIME_BLOCK(_, CODE) \
    {                          \
        CODE;                  \
    };

static void mob_counter(EntityIdx i, void *a)
{
    EntityIdx *count = a;
    ++*count;
}

static void rr_simulation_pending_deletion_free_components(uint64_t id, void *_simulation)
{
    struct rr_simulation *simulation = _simulation;
    if (rr_simulation_has_physical(simulation, id))
    {
        struct rr_component_physical *physical = rr_simulation_get_physical(simulation, id);
        if (physical->has_deletion_animation)
        {
            __rr_simulation_pending_deletion_free_components(id, _simulation);
            rr_bitset_unset(simulation->pending_deletions, id);
            rr_component_physical_set_server_animation_tick(physical, 5);
            physical->ticked_animation = 1;
        }
        else if (physical->server_animation_tick != 0 && physical->ticked_animation == 0)
        {
            rr_bitset_unset(simulation->pending_deletions, id);
            rr_component_physical_set_server_animation_tick(physical, physical->server_animation_tick - 1);
            physical->ticked_animation = 1;
        }
    }
    else
    {
        __rr_simulation_pending_deletion_free_components(id, _simulation);
    }
}

void rr_simulation_tick(struct rr_simulation *this)
{
    RR_TIME_BLOCK("collision_detection", { rr_system_collision_detection_tick(this); });
    RR_TIME_BLOCK("ai", { rr_system_ai_tick(this); });
    RR_TIME_BLOCK("drops", { rr_system_drops_tick(this); });
    RR_TIME_BLOCK("petal_behavior", { rr_system_petal_behavior_tick(this); });
    RR_TIME_BLOCK("velocity", { rr_system_velocity_tick(this); });
    RR_TIME_BLOCK("collision_resolution", { rr_system_collision_resolution_tick(this); });
    RR_TIME_BLOCK("centipede", { rr_system_centipede_tick(this); });
    RR_TIME_BLOCK("map_boundary", { rr_system_map_boundary_tick(this); });
    RR_TIME_BLOCK("health", { rr_system_health_tick(this); });

    if (!this->game_over)
    {
        int any_alive = 0;

        for (uint32_t i = 0; i < sizeof this->flower_tracker; ++i)
            if (this->flower_tracker[i])
            {
                any_alive = 1;
                break;
            }

        if (!any_alive)
            this->game_over = 1;

        struct rr_component_arena *arena = rr_simulation_get_arena(this, 1);
        // end of wave
        if (arena->wave_tick == 15 * 25)
        {
            arena->wave_tick = 0;
            rr_component_arena_set_wave(arena, arena->wave + 1);
            RR_TIME_BLOCK("respawn", { rr_system_respawn_tick(this); });
        }
        rr_component_arena_set_wave_tick(arena, arena->wave_tick + 1);
        EntityIdx mobs_in_use = 0;
        rr_simulation_for_each_mob(this, &mobs_in_use, mob_counter);
        if (mobs_in_use <= 200 && arena ->wave_tick % 8 == 0)
            spawn_random_mob(this);
    }

    // delete pending deletions
    rr_bitset_for_each_bit(this->pending_deletions, this->pending_deletions + (RR_BITSET_ROUND(RR_MAX_ENTITY_COUNT)), this, rr_simulation_pending_deletion_free_components);
    memset(this->recently_deleted, 0, RR_BITSET_ROUND(RR_MAX_ENTITY_COUNT) * sizeof *this->recently_deleted);
    rr_bitset_for_each_bit(this->pending_deletions, this->pending_deletions + (RR_BITSET_ROUND(RR_MAX_ENTITY_COUNT)), this, __rr_simulation_pending_deletion_unset_entity);
    memset(this->pending_deletions, 0, RR_BITSET_ROUND(RR_MAX_ENTITY_COUNT) * sizeof *this->pending_deletions);
}
