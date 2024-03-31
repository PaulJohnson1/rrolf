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

#include <assert.h>
#include <math.h>
#include <stdlib.h>

#include <Server/EntityAllocation.h>
#include <Server/EntityDetection.h>
#include <Server/MobAi/Ai.h>
#include <Server/Simulation.h>
#include <Shared/Entity.h>
#include <Shared/Vector.h>

static void system_for_each(EntityIdx entity, void *simulation)
{
    struct rr_simulation *this = simulation;

    if (rr_simulation_has_centipede(this, entity) &&
        rr_simulation_get_centipede(this, entity)->parent_node !=
            RR_NULL_ENTITY)
        return;
    if (rr_simulation_has_arena(this, entity))
        return;

    struct rr_component_ai *ai = rr_simulation_get_ai(this, entity);
    struct rr_component_mob *mob = rr_simulation_get_mob(this, entity);
    struct rr_component_physical *physical =
        rr_simulation_get_physical(this, entity);
    if (!rr_simulation_entity_alive(simulation, ai->target_entity) &&
        ai->target_entity != RR_NULL_ENTITY)
    {
        ai->target_entity = RR_NULL_ENTITY;
        ai->ai_state = rr_ai_state_idle;
        ai->ticks_until_next_action = 25;
    }
    if (physical->stun_ticks > 0)
        return;
    struct rr_component_relations *relations =
        rr_simulation_get_relations(this, entity);
    if (ai->target_entity != RR_NULL_ENTITY)
    {
        struct rr_component_physical *t_physical =
            rr_simulation_get_physical(this, ai->target_entity);
        struct rr_vector diff = {physical->x - t_physical->x,
                                 physical->y - t_physical->y};
        if (rr_vector_magnitude_cmp(&diff, 2000) == 1)
        {
            ai->target_entity = RR_NULL_ENTITY;
            ai->ai_state = rr_ai_state_idle;
            ai->ticks_until_next_action = 25;
        }
    }
    if (mob->player_spawned)
        if (tick_summon_return_to_owner(entity, this))
            return;

    switch (mob->id)
    {
    case rr_mob_id_fern:
    case rr_mob_id_tree:
        break;
    case rr_mob_id_triceratops:
        tick_ai_neutral_triceratops(entity, this);
        break;
    case rr_mob_id_trex:
        tick_ai_aggro_trex(entity, this);
        break;
    case rr_mob_id_meteor:
        tick_ai_passive_meteor(entity, this);
        break;
    case rr_mob_id_pteranodon:
        tick_ai_aggro_pteranodon(entity, this);
        break;
    case rr_mob_id_dakotaraptor:
        tick_ai_aggro_default(entity, this,
                              RR_PLAYER_SPEED * (1.5 - mob->rarity * 0.05));
        break;
    case rr_mob_id_pachycephalosaurus:
        tick_ai_aggro_pachycephalosaurus(entity, this);
        break;
    case rr_mob_id_ornithomimus:
        tick_ai_neutral_ornithomimus(entity, this);
        break;
    case rr_mob_id_ankylosaurus:
        tick_ai_neutral_ankylosaurus(entity, this);
        break;
    case rr_mob_id_quetzalcoatlus:
        tick_ai_aggro_quetzalcoaltus(entity, this);
        break;
    case rr_mob_id_edmontosaurus:
        tick_ai_neutral_default(entity, this, RR_PLAYER_SPEED);
        break;
    case rr_mob_id_hornet:
        tick_ai_aggro_default(entity, this, RR_PLAYER_SPEED + 0.25);
        break;
    case rr_mob_id_honeybee:
        tick_ai_neutral_default(entity, this, RR_PLAYER_SPEED + 0.25);
        break;
    case rr_mob_id_ant:
        tick_ai_neutral_default(entity, this, RR_PLAYER_SPEED * 3);
        break;
    case rr_mob_id_dragonfly:
        tick_ai_aggro_default(entity, this, RR_PLAYER_SPEED + 0.25);
        break;
    case rr_mob_id_spider:
        tick_ai_aggro_default(entity, this, RR_PLAYER_SPEED + 0.5);
        break;
    default:
        tick_ai_passive_default(entity, this);
        break;
    }
    --ai->ticks_until_next_action;
}

void rr_system_ai_tick(struct rr_simulation *simulation)
{
    rr_simulation_for_each_ai(simulation, simulation, system_for_each);
}
