#include <Server/Simulation.h>

#include <assert.h>
#include <string.h>

#include <Server/System/Velocity.h>
#include <Shared/Bitset.h>

// will change later probably
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
    struct rr_encoder *encoder;
    struct rr_component_player_info *player_info;
    uint8_t *entities_in_view;
};

void rr_simulation_write_entity_function(uint64_t _id, void *_captures)
{
    EntityIdx id = _id;
    struct rr_protocol_for_each_function_captures *captures = _captures;
    struct rr_simulation *simulation = captures->simulation;
    struct rr_encoder *encoder = captures->encoder;
    struct rr_component_player_info *player_info = captures->player_info;
    uint8_t *new_entities_in_view = captures->entities_in_view;

    rr_encoder_write_varuint(encoder, id);

    int is_creation = 0;

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

    rr_encoder_write_varuint(encoder, component_flags);
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
    if (player_info->player_id != RR_NULL_ENTITY)
        rr_bitset_set(entities_in_view, player_info->player_id);

    rr_simulation_for_each_entity(this, &captures, rr_simulation_find_entities_in_view_for_each_function);
}

void rr_simulation_write_entity_deletions_function(uint64_t _id, void *_captures)
{
    EntityIdx id = _id;
    struct rr_protocol_for_each_function_captures *captures = _captures;
    struct rr_component_player_info *player_info = captures->player_info;
    struct rr_encoder *encoder = captures->encoder;
    uint8_t *new_entities_in_view = captures->entities_in_view;

    if (!rr_bitset_get_bit(new_entities_in_view, id))
    {
        // deletion spotted!
        rr_bitset_unset(player_info->entities_in_view, id);
        rr_encoder_write_varuint(encoder, id);
    }
}

void rr_simulation_write_binary(struct rr_simulation *this, struct rr_encoder *encoder, struct rr_component_player_info *player_info)
{
    uint8_t new_entities_in_view[RR_MAX_ENTITY_COUNT >> 3];
    memset(new_entities_in_view, 0, (RR_MAX_ENTITY_COUNT >> 3) * (sizeof *new_entities_in_view));

    rr_simulation_find_entities_in_view(this, player_info, &new_entities_in_view[0]);

    struct rr_protocol_for_each_function_captures captures;
    captures.simulation = this;
    captures.encoder = encoder;
    captures.player_info = player_info;
    captures.entities_in_view = new_entities_in_view;

    rr_bitset_for_each_bit(&player_info->entities_in_view[0], &player_info->entities_in_view[0] + (RR_MAX_ENTITY_COUNT >> 3), &captures, rr_simulation_write_entity_deletions_function);
    rr_encoder_write_uint8(encoder, RR_NULL_ENTITY); // null terminate deletion list

    rr_bitset_for_each_bit(new_entities_in_view, new_entities_in_view + (RR_MAX_ENTITY_COUNT >> 3), &captures, rr_simulation_write_entity_function);
    rr_encoder_write_uint8(encoder, RR_NULL_ENTITY); // null terminate update list
}

void rr_simulation_tick_entity_resetter_function(EntityIdx entity, void *captures)
{
    struct rr_simulation *this = captures;
#define XX(COMPONENT, ID)                            \
    if (rr_simulation_has_##COMPONENT(this, entity)) \
        rr_simulation_get_##COMPONENT(this, entity)->protocol_state = 0;
    RR_FOR_EACH_COMPONENT
#undef XX
}

void rr_simulation_tick(struct rr_simulation *this)
{
    rr_simulation_for_each_entity(this, this, rr_simulation_tick_entity_resetter_function);
    rr_system_velocity_tick(this);
}
