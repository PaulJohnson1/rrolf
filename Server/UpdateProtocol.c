#include <Server/UpdateProtocol.h>

#include <assert.h>
#include <inttypes.h>
#include <stdlib.h>
#include <string.h>

#include <Server/Simulation.h>
#include <Shared/Bitset.h>
#include <Shared/Utilities.h>
#include <Shared/pb.h>

struct rr_protocol_for_each_function_captures
{
    struct rr_simulation *simulation;
    struct proto_bug *encoder;
    struct rr_component_player_info *player_info;
    uint8_t *entities_in_view;
};

static void rr_simulation_write_entity_function(uint64_t _id, void *_captures)
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
#define XX(COMPONENT, ID)                                                      \
    component_flags |= rr_simulation_has_##COMPONENT(simulation, id) << ID;
    RR_FOR_EACH_COMPONENT;
#undef XX

    proto_bug_write_varuint(encoder, component_flags, "entity component flags");
#define XX(COMPONENT, ID)                                                      \
    if (component_flags & (1 << ID))                                           \
        rr_component_##COMPONENT##_write(                                      \
            rr_simulation_get_##COMPONENT(simulation, id), encoder,            \
            is_creation, player_info);
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

static void
rr_simulation_find_entities_in_view_for_each_function(EntityIdx entity,
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
    if (rr_simulation_has_drop(simulation, entity) &&
        rr_bitset_get(
            rr_simulation_get_drop(captures->simulation, entity)->picked_up_by,
            captures->player_info->client_id))
        return;
    rr_bitset_set(captures->entities_in_view, entity);
    return;
}

static void rr_simulation_find_entities_in_view(
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

static void rr_simulation_write_entity_deletions_function(uint64_t _id,
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
        uint8_t out_of_view =
            rr_simulation_has_entity(captures->simulation, id) == 0;
        if (!out_of_view)
            if (rr_simulation_has_drop(captures->simulation, id) &&
                     rr_bitset_get(
                         rr_simulation_get_drop(captures->simulation, id)
                             ->picked_up_by,
                         player_info->client_id))
                out_of_view = 2;
        rr_bitset_unset(player_info->entities_in_view, id);
        proto_bug_write_varuint(encoder, id, "entity deletion id");
        proto_bug_write_uint8(encoder, out_of_view, "deletion type");
    }
}

static void write_animation_function(struct rr_simulation *simulation,
                                     struct proto_bug *encoder, uint32_t pos)
{
    struct rr_simulation_animation *animation = &simulation->animations[pos];
    proto_bug_write_uint8(encoder, animation->type, "ani type");
    proto_bug_write_uint8(encoder, animation->length, "ani length");
    for (uint32_t i = 0; i < animation->length; ++i)
    {
        proto_bug_write_float32(encoder, animation->points[i].x, "ani x");
        proto_bug_write_float32(encoder, animation->points[i].y, "ani y");
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
    proto_bug_write_varuint(encoder, this->animation_length, "ani count");
    for (uint32_t i = 0; i < this->animation_length; ++i)
        write_animation_function(this, encoder, i);
    proto_bug_write_varuint(encoder, player_info->parent_id,
                            "pinfo id"); // send client's pinfo
    proto_bug_write_uint8(encoder, this->game_over, "game over");
}