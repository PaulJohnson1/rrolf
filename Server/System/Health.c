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

#include <math.h>
#include <stdio.h>
#include <string.h>

#include <Server/EntityDetection.h>
#include <Server/Simulation.h>
#include <Shared/Bitset.h>

struct colliding_with_captures
{
    struct rr_simulation *simulation;
    struct rr_component_health *health;
};

static void system_default_idle_heal(EntityIdx entity, void *captures)
{
    struct rr_simulation *this = captures;
    struct rr_component_health *health = rr_simulation_get_health(this, entity);
    struct rr_component_physical *physical =
        rr_simulation_get_physical(this, entity);

    // heal 0.5% of max hp per second (0.0002 is 0.01 / 25)
    if (health->poison_ticks > 0)
    {
        --health->poison_ticks;
        rr_component_health_set_health(health, health->health - health->poison);
    }
    else
        health->poison = 0;
    // if (health->health > 0)
    //{
    // rr_component_health_set_health(health, health->health +
    //                                            health->max_health * 0.0002);
    if (health->damage_paused > 0)
        health->damage_paused -= 1;
    //}
    if (health->health == 0)
        rr_simulation_request_entity_deletion(this, entity);
}

struct lightning_captures
{
    EntityIdx *chain;
    uint32_t length;
    float curr_x;
    float curr_y;
};

static uint8_t lightning_filter(struct rr_simulation *simulation,
                                EntityIdx seeker, EntityIdx target,
                                void *captures)
{
    if (seeker == target)
        return 0;
    struct lightning_captures *chain = captures;
    for (uint32_t i = 0; i < chain->length; ++i)
    {
        if (chain->chain[i] == target)
            return 0;
    }
    return 1;
}

static void lightning_petal_system(struct rr_simulation *simulation,
                                   struct rr_component_petal *petal,
                                   EntityIdx first)
{
    struct rr_component_physical *petal_physical =
        rr_simulation_get_physical(simulation, petal->parent_id);
    struct rr_component_physical *first_physical =
        rr_simulation_get_physical(simulation, first);
    struct rr_component_relations *relations =
        rr_simulation_get_relations(simulation, petal->parent_id);
    struct rr_simulation_animation *animation =
        &simulation->animations[simulation->animation_length++];
    animation->type = rr_animation_type_lightningbolt;
    EntityIdx chain[16] = {petal->parent_id, first};
    animation->points[0].x = petal_physical->x;
    animation->points[0].y = petal_physical->y;
    animation->points[1].x = first_physical->x;
    animation->points[1].y = first_physical->y;
    uint32_t chain_amount = petal->rarity + 1;
    float damage =
        rr_simulation_get_health(simulation, petal->parent_id)->damage * 0.5;
    EntityIdx target = RR_NULL_ENTITY;
    struct lightning_captures captures = {chain, 2, first_physical->x,
                                          first_physical->y};
    for (; captures.length < chain_amount + 1; ++captures.length)
    {
        target = rr_simulation_find_nearest_enemy_custom_pos(
            simulation, petal->parent_id, captures.curr_x, captures.curr_y, 400,
            &captures, lightning_filter);
        if (target == RR_NULL_ENTITY)
            break;
        if (rr_simulation_has_ai(simulation, target))
        {
            struct rr_component_ai *ai =
                rr_simulation_get_ai(simulation, target);
            if (ai->target_entity == RR_NULL_ENTITY)
                ai->target_entity = relations->owner;
        }
        struct rr_component_physical *physical =
            rr_simulation_get_physical(simulation, target);
        struct rr_component_health *health =
            rr_simulation_get_health(simulation, target);
        rr_component_health_do_damage(simulation, health, petal->parent_id,
                                      damage);
        health->damage_paused = 5;
        physical->stun_ticks = 4;
        chain[captures.length] = target;
        animation->points[captures.length].x = physical->x;
        animation->points[captures.length].y = physical->y;
        captures.curr_x = physical->x;
        captures.curr_y = physical->y;
    }
    animation->length = captures.length;
    rr_simulation_request_entity_deletion(simulation, petal->parent_id);
}

static void damage_effect(struct rr_simulation *simulation, EntityIdx target,
                          EntityIdx attacker)
{
    if (rr_simulation_has_ai(simulation, target))
    {
        struct rr_component_ai *ai = rr_simulation_get_ai(simulation, target);
        if (ai->target_entity == RR_NULL_ENTITY)
        {
            if (rr_simulation_has_petal(simulation, attacker))
            {
                struct rr_component_relations *relations =
                    rr_simulation_get_relations(simulation, attacker);
                ai->target_entity = relations->owner;
            }
            else
                ai->target_entity =
                    rr_simulation_get_entity_hash(simulation, attacker);
        }
    }
    if (rr_simulation_has_mob(simulation, attacker))
    {
        struct rr_component_mob *mob =
            rr_simulation_get_mob(simulation, attacker);
        if (mob->id == rr_mob_id_pachycephalosaurus &&
            mob->rarity >= rr_rarity_id_exotic)
        {
            struct rr_component_physical *physical =
                rr_simulation_get_physical(simulation, target);
            physical->stun_ticks = 25;
        }
    }
    else if (rr_simulation_has_petal(simulation, attacker))
    {
        struct rr_component_petal *petal =
            rr_simulation_get_petal(simulation, attacker);
        if (petal->id == rr_petal_id_beak)
        {
            struct rr_component_physical *physical =
                rr_simulation_get_physical(simulation, target);
            physical->stun_ticks =
                25 *
                (1 + sqrtf(RR_PETAL_RARITY_SCALE[petal->rarity].heal) / 3) *
                (1 - physical->slow_resist);
        }
        else if (petal->id == rr_petal_id_lightning)
        {
            lightning_petal_system(simulation, petal, target);
        }
        else if (petal->id == rr_petal_id_mandible)
        {
            struct rr_component_health *health =
                rr_simulation_get_health(simulation, target);
            if (health->health > 0 && health->health * 2 < health->max_health)
                rr_component_health_do_damage(
                    simulation, health, attacker,
                    50 * RR_PETAL_DATA[petal->id].scale[petal->rarity].damage);
        }
    }
}

static void colliding_with_function(uint64_t i, void *_captures)
{
    struct colliding_with_captures *captures = _captures;
    struct rr_simulation *this = captures->simulation;
    EntityIdx entity1 = captures->health->parent_id;
    EntityIdx entity2 = i;
    if (!rr_simulation_has_health(this, entity2))
        return;
    struct rr_component_relations *relations1 =
        rr_simulation_get_relations(this, entity1);
    struct rr_component_relations *relations2 =
        rr_simulation_get_relations(this, entity2);
    if (relations1->team == relations2->team)
        return;
    struct rr_component_health *health1 = captures->health;
    struct rr_component_health *health2 =
        rr_simulation_get_health(this, entity2);
    struct rr_component_physical *physical1 =
        rr_simulation_get_physical(this, entity1);
    struct rr_component_physical *physical2 =
        rr_simulation_get_physical(this, entity2);
    if (health2->health == 0)
        return;
    uint8_t bypass = rr_simulation_has_petal(this, entity1) ||
                     rr_simulation_has_petal(this, entity2);
    uint8_t byp2 = (rr_simulation_has_mob(this, entity1) &&
                    rr_simulation_has_mob(this, entity2));
    if (health1->damage_paused == 0 || bypass)
    {
        damage_effect(this, entity1, entity2);
        rr_component_health_do_damage(this, health1, entity2, health2->damage);
        health1->damage_paused = byp2 ? 3 : 8;
    }
    if (health2->damage_paused == 0 || bypass)
    {
        damage_effect(this, entity2, entity1);
        rr_component_health_do_damage(this, health2, entity1, health1->damage);
        health2->damage_paused = byp2 ? 3 : 8;
    }
}

static void system_for_each_function(EntityIdx entity, void *_captures)
{
    struct rr_simulation *this = _captures;
    // all health has physical

    struct rr_component_physical *physical =
        rr_simulation_get_physical(this, entity);
    struct rr_component_health *health = rr_simulation_get_health(this, entity);

    if (health->health == 0)
        return;

    struct colliding_with_captures captures;
    captures.health = health;
    captures.simulation = this;

    for (uint32_t i = 0; i < physical->colliding_with_size; ++i)
        colliding_with_function(physical->colliding_with[i], &captures);
}

void rr_system_health_tick(struct rr_simulation *this)
{
    rr_simulation_for_each_health(this, this, system_default_idle_heal);
    rr_simulation_for_each_health(this, this, system_for_each_function);
}
