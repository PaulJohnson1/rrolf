// Copyright (C) 2024  Paul Johnson

// This program is free software: you can redistribute it and/or modify
// it under the terms of the GNU Affero General Public License as
// published by the Free Software Foundation, either version 3 of the
// License, or (at your option) any later version.

// This program is distributed in the hope that it will be useful,
// but WITHOUT ANY WARRANTY; without even the implied warranty of
// MERCHANTABILITY or FITNESS FOR A PARTICULAR PURPOSE.  See the
// GNU Affero General Public License for more details.

// You should have received a copy of the GNU Affero General Public License
// along with this program.  If not, see <https://www.gnu.org/licenses/>.

#include <Server/UpdateProtocol.h>

#include <assert.h>
#include <inttypes.h>
#include <stdlib.h>
#include <string.h>

#include <Server/Simulation.h>
#include <Server/SpatialHash.h>
#include <Shared/Bitset.h>
#include <Shared/Utilities.h>
#include <Shared/pb.h>

#define entity_alive(sim, id)                                                  \
    (sim->entity_tracker[id] && !rr_bitset_get(sim->deleted_last_tick, id))

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

    uint32_t component_flags = simulation->entity_tracker[id];
    proto_bug_write_uint8(encoder, is_creation, "upcreate");
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
    if (!entity_alive(simulation, entity))
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
        (!rr_bitset_get(rr_simulation_get_drop(captures->simulation, entity)
                            ->can_be_picked_up_by,
                        captures->player_info->squad) ||
         rr_bitset_get(
             rr_simulation_get_drop(captures->simulation, entity)->picked_up_by,
             captures->player_info->squad * RR_SQUAD_MEMBER_COUNT +
                 captures->player_info->squad_pos)))
        return;
    rr_bitset_set(captures->entities_in_view, entity);
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

    if (entity_alive(this, (EntityIdx)player_info->flower_id))
        rr_bitset_set(entities_in_view, (EntityIdx)player_info->flower_id);

    if (!entity_alive(this, player_info->arena))
        rr_component_player_info_set_arena(player_info, 1);
    rr_bitset_set(captures.entities_in_view, player_info->arena);
    rr_bitset_set(captures.entities_in_view, 1);
    struct rr_spatial_hash *shg =
        &rr_simulation_get_arena(this, player_info->arena)->spatial_hash;
    rr_spatial_hash_query(
        shg, captures.view_x, captures.view_y, captures.view_width,
        captures.view_height, &captures,
        rr_simulation_find_entities_in_view_for_each_function);
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
        uint8_t serverside_delete = !entity_alive(captures->simulation, id);
        if (serverside_delete == 0)
        {
            if (rr_simulation_has_drop(captures->simulation, id))
            {
                struct rr_component_drop *drop =
                    rr_simulation_get_drop(captures->simulation, id);
                if (!rr_bitset_get(drop->can_be_picked_up_by,
                                   player_info->squad))
                    serverside_delete = 1;
                else if (rr_bitset_get(drop->picked_up_by,
                                       player_info->squad *
                                               RR_SQUAD_MEMBER_COUNT +
                                           player_info->squad_pos))
                    // 1 = in-place deletion, 2 = suck to player
                    serverside_delete = 2;
            }
        }
        rr_bitset_unset(player_info->entities_in_view, id);
        proto_bug_write_varuint(encoder, id, "entity deletion id");
        proto_bug_write_uint8(encoder, serverside_delete, "deletion type");
    }
}

void rr_simulation_write_binary(struct rr_simulation *this,
                                struct proto_bug *encoder,
                                struct rr_component_player_info *player_info)
{
    uint8_t new_entities_in_view[RR_BITSET_ROUND(RR_MAX_ENTITY_COUNT)] = {0};

    rr_simulation_find_entities_in_view(this, player_info,
                                        &new_entities_in_view[0]);
    for (uint64_t i = 0; i < this->player_info_count; i++)
    {
        EntityIdx p_id = this->player_info_vector[i];
        if (!entity_alive(this, p_id))
            continue;
        struct rr_component_player_info *p_info =
            rr_simulation_get_player_info(this, p_id);
        if (p_info->squad != player_info->squad)
            continue;
        rr_bitset_set(new_entities_in_view, p_id);
        if (entity_alive(this, (EntityIdx)p_info->flower_id) &&
            p_info->arena == player_info->arena)
            rr_bitset_set(new_entities_in_view, (EntityIdx)p_info->flower_id);
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
                            "pinfo id"); // send client's pinfo
    proto_bug_write_uint8(encoder, this->game_over, "game over");
}
#undef entity_alive