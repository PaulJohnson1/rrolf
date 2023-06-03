#include <Server/Simulation.h>

#include <assert.h>
#include <string.h>
#include <stdlib.h>
#include <math.h>
#include <sys/time.h>

#include <Server/System/Ai.h>
#include <Server/System/Centipede.h>
#include <Server/System/CollisionDetection.h>
#include <Server/System/CollisionResolution.h>
#include <Server/System/Health.h>
#include <Server/System/MapBoundary.h>
#include <Server/System/PetalBehavior.h>
#include <Server/System/Velocity.h>
#include <Server/SpatialHash.h>
#include <Shared/Bitset.h>
#include <Shared/pb.h>

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
    rr_static_data_init();
    // this->hshg = hshg_create(64, 16);
    // assert(this->hshg);
    // this->hshg->update = rr_simulation_tick;
    // hshg_set_size(this->hshg, RR_MAX_ENTITY_COUNT + 1);
    this->grid = malloc(sizeof *this->grid);
    rr_spatial_hash_init(this->grid);
    this->grid->simulation = this;
    this->arena = rr_simulation_alloc_entity(this);
    struct rr_component_arena *comp = rr_simulation_add_arena(this, this->arena);
    rr_component_arena_set_radius(comp, 1650.0f);
    // for (uint32_t i = 0; i < 25; i++)
    // {
    // EntityIdx mob_id = rr_simulation_alloc_mob(this, rr_mob_id_centipede_head, rr_rarity_id_common);
    // struct rr_component_physical *physical = rr_simulation_get_physical(this, mob_id);
    // physical->mass = 100.0f;
    // }
    // rr_simulation_for_each_centipede(this, this, move_up_temp_test);
}

static void spawn_random_mob(struct rr_simulation *this)
{
    // promote to double for accuracy, demote to float once finished
    float r = ((double)rand() / (double)RAND_MAX);
    uint8_t id = rr_mob_id_centipede_head;
    if (r -= 0.45, r < 0)
        id = rr_mob_id_baby_ant;
    else if (r -= 0.45, r < 0)
        id = rr_mob_id_worker_ant;
    EntityIdx mob_id = rr_simulation_alloc_mob(this, id, rr_rarity_id_epic);
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
    float distance = sqrt((float)rand() / (float)RAND_MAX) * 1650.0f;
    float angle = (float)rand() / (float)RAND_MAX * M_PI * 2.0f;
    rr_component_physical_set_x(physical, cos(angle) * distance);
    rr_component_physical_set_y(physical, sin(angle) * distance);
    physical->radius = mob_data->radius * rarity_scale->radius;
    physical->friction = 0.9;
    physical->mass = 100.0f;
    rr_component_health_set_max_health(health, mob_data->health * rarity_scale->health);
    rr_component_health_set_health(health, mob_data->health * rarity_scale->health);
    health->damage = mob_data->damage * rarity_scale->damage;
    switch (mob_id)
    {
    case rr_mob_id_centipede_head:
    case rr_mob_id_worker_ant:
        ai->ai_type = rr_ai_type_neutral;
        break;
    case rr_mob_id_centipede_body:
    case rr_mob_id_baby_ant:
        ai->ai_type = rr_ai_type_passive;
        break;
    default:
        RR_UNREACHABLE("forgot to set ai type");
    };

    if (mob_id == rr_mob_id_centipede_head)
    {
        ai->ai_type = rr_ai_type_neutral;
        EntityIdx prev_node = entity;
        struct rr_component_centipede *centipede = rr_simulation_add_centipede(this, entity);
        struct rr_vector extension;
        rr_vector_from_polar(&extension, physical->radius * 2, physical->angle);
        EntityIdx new_entity = RR_NULL_ENTITY;
        for (uint64_t i = 0; i < 5; ++i)
        {
            new_entity = rr_simulation_alloc_mob(this, rr_mob_id_centipede_body, rarity_id);
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
            rr_bitset_set(this->entity_tracker, i);
            printf("created with id %d\n", i);
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
        if (rr_bitset_get_bit(new_entities_in_view, id))
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
    struct rr_simulation *simulation;
};

void rr_simulation_find_entities_in_view_for_each_function(EntityIdx entity, void *data)
{
    struct rr_simulation_find_entities_in_view_for_each_function_captures *captures = data;
    struct rr_simulation *simulation = captures->simulation;

    if (!rr_simulation_has_physical(simulation, entity))
        return;
    struct rr_component_physical *physical = rr_simulation_get_physical(simulation, entity);

    if (physical->x + physical->radius < captures->view_x - captures->view_width ||
        physical->x - physical->radius > captures->view_x + captures->view_width ||
        physical->y + physical->radius < captures->view_y - captures->view_height ||
        physical->y - physical->radius > captures->view_y + captures->view_height)
        return;

    rr_bitset_set(captures->entities_in_view, entity);
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
    captures.simulation = this;

    rr_bitset_set(entities_in_view, player_info->parent_id);
    // don't add the player into the view if it is null (player died lmfao skill issue)
    if (player_info->flower_id != RR_NULL_ENTITY)
        rr_bitset_set(entities_in_view, player_info->flower_id);

    rr_bitset_set(captures.entities_in_view, this->arena);
    rr_simulation_for_each_entity(this, &captures, rr_simulation_find_entities_in_view_for_each_function);
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

    struct rr_protocol_for_each_function_captures captures;
    captures.simulation = this;
    captures.encoder = encoder;
    captures.player_info = player_info;
    captures.entities_in_view = new_entities_in_view;

    rr_bitset_for_each_bit(&player_info->entities_in_view[0], &player_info->entities_in_view[0] + (RR_BITSET_ROUND(RR_MAX_ENTITY_COUNT)), &captures, rr_simulation_write_entity_deletions_function);
    proto_bug_write_varuint(encoder, RR_NULL_ENTITY, "entity deletion id"); // null terminate deletion list

    rr_bitset_for_each_bit(new_entities_in_view, new_entities_in_view + (RR_BITSET_ROUND(RR_MAX_ENTITY_COUNT)), &captures, rr_simulation_write_entity_function);
    proto_bug_write_varuint(encoder, RR_NULL_ENTITY, "entity update id"); // null terminate update list
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

void rr_simulation_tick(struct rr_simulation *this)
{
    RR_TIME_BLOCK("collision_detection", { rr_system_collision_detection_tick(this); });
    RR_TIME_BLOCK("ai", { rr_system_ai_tick(this); });
    RR_TIME_BLOCK("collision_resolution", { rr_system_collision_resolution_tick(this); });
    RR_TIME_BLOCK("petal_behavior", { rr_system_petal_behavior_tick(this); });
    RR_TIME_BLOCK("velocity", { rr_system_velocity_tick(this); });
    RR_TIME_BLOCK("centipede", { rr_system_centipede_tick(this); });
    RR_TIME_BLOCK("map_boundary", { rr_system_map_boundary_tick(this); });
    RR_TIME_BLOCK("health", { rr_system_health_tick(this); });
    // delete pending deletions
    RR_TIME_BLOCK("deletions", {
        rr_bitset_for_each_bit(this->pending_deletions, this->pending_deletions + (RR_BITSET_ROUND(RR_MAX_ENTITY_COUNT)), this, __rr_simulation_pending_deletion_free_components);
        rr_bitset_for_each_bit(this->pending_deletions, this->pending_deletions + (RR_BITSET_ROUND(RR_MAX_ENTITY_COUNT)), this, __rr_simulation_pending_deletion_unset_entity);
        memset(this->pending_deletions, 0, RR_BITSET_ROUND(RR_MAX_ENTITY_COUNT) * sizeof *this->pending_deletions);
    });

        for (uint32_t i = 0; i < 100; i++)
        spawn_random_mob(this);
}
