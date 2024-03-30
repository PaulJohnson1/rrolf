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

#include <Server/System/System.h>

#include <stdlib.h>

#include <Server/Simulation.h>

struct drop_pick_up_captures
{
    struct rr_simulation *simulation;
    EntityIdx self;
};

static void drop_pick_up(EntityIdx entity, void *_captures)
{
    struct drop_pick_up_captures *captures = _captures;
    struct rr_simulation *this = captures->simulation;
    EntityIdx drop_id = captures->self;
    struct rr_component_drop *drop = rr_simulation_get_drop(this, drop_id);

    struct rr_component_relations *flower_relations =
        rr_simulation_get_relations(this, entity);
    if (!rr_simulation_entity_alive(this, flower_relations->owner))
        return;

    struct rr_component_player_info *player_info =
        rr_simulation_get_player_info(this, flower_relations->owner);
    if (!rr_bitset_get(drop->can_be_picked_up_by, player_info->squad))
        return;
    if (rr_bitset_get(drop->picked_up_by,
                      player_info->squad * RR_SQUAD_MEMBER_COUNT +
                          player_info->squad_pos))
        return;
    struct rr_component_physical *physical =
        rr_simulation_get_physical(this, drop_id);

    struct rr_component_physical *flower_physical =
        rr_simulation_get_physical(this, entity);

    struct rr_vector delta = {physical->x - flower_physical->x,
                              physical->y - flower_physical->y};
    if (rr_vector_magnitude_cmp(
            &delta,
            physical->radius + player_info->modifiers.drop_pickup_radius) == 1)
        return;
    if (player_info->drops_this_tick_size >= 8)
        return;
    rr_bitset_set(drop->picked_up_by,
                  player_info->squad * RR_SQUAD_MEMBER_COUNT +
                      player_info->squad_pos);

    ++player_info
          ->collected_this_run[drop->id * rr_rarity_id_max + drop->rarity];
    rr_component_player_info_set_update_loot(player_info);
    player_info->drops_this_tick[player_info->drops_this_tick_size].id =
        drop->id;
    player_info->drops_this_tick[player_info->drops_this_tick_size].rarity =
        drop->rarity;
    ++player_info->drops_this_tick_size;
}

static void drop_despawn_tick(EntityIdx entity, void *_captures)
{
    struct rr_simulation *this = _captures;
    struct rr_component_drop *drop = rr_simulation_get_drop(this, entity);
    struct rr_component_physical *physical =
        rr_simulation_get_physical(this, entity);
    if (drop->ticks_until_despawn == 0)
    {
        rr_simulation_request_entity_deletion(this, entity);
        return;
    }
    --drop->ticks_until_despawn;
    if (drop->ticks_until_despawn > 25 * 10 * (drop->rarity + 1) - 10)
        return;
    struct drop_pick_up_captures captures;
    captures.self = entity;
    captures.simulation = this;
    rr_simulation_for_each_flower(this, &captures, drop_pick_up);
}

void rr_system_drops_tick(struct rr_simulation *this)
{
    rr_simulation_for_each_drop(this, this, drop_despawn_tick);
}
