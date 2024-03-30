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
#include <Server/Simulation.h>
#include <Shared/Entity.h>
#include <Shared/Vector.h>

static uint8_t is_close_enough_to_parent(struct rr_simulation *simulation,
                                         EntityIdx seeker, EntityIdx target,
                                         void *captures)
{
    struct rr_component_physical *parent_physical = captures;
    struct rr_component_physical *physical =
        rr_simulation_get_physical(simulation, target);
    return ((physical->x - parent_physical->x) *
                    (physical->x - parent_physical->x) +
                (physical->y - parent_physical->y) *
                    (physical->y - parent_physical->y) <
            1000 * 1000);
}

static uint8_t has_new_target(struct rr_component_ai *ai,
                              struct rr_simulation *simulation)
{
    if (!rr_simulation_entity_alive(simulation, ai->target_entity))
    {
        if (ai->target_entity != RR_NULL_ENTITY)
        {
            ai->target_entity = RR_NULL_ENTITY;
            ai->ai_state = rr_ai_state_idle;
            ai->ticks_until_next_action = rand() % 25 + 25;
        }
        struct rr_component_relations *relations =
            rr_simulation_get_relations(simulation, ai->parent_id);
        if (relations->team == rr_simulation_team_id_mobs)
            ai->target_entity = rr_simulation_find_nearest_enemy(
                simulation, ai->parent_id, 1500, NULL, no_filter);
        else
            ai->target_entity = rr_simulation_find_nearest_enemy(
                simulation, ai->parent_id, 1500,
                rr_simulation_get_physical(simulation, relations->owner),
                is_close_enough_to_parent);
        return ai->target_entity != RR_NULL_ENTITY;
    }
    return 0;
}

static void tick_idle(EntityIdx entity, struct rr_simulation *simulation)
{
    struct rr_component_ai *ai = rr_simulation_get_ai(simulation, entity);
    struct rr_component_physical *physical =
        rr_simulation_get_physical(simulation, entity);

    if (ai->ticks_until_next_action == 0)
    {
        ai->ticks_until_next_action = rand() % 33 + 25;
        ai->ai_state = rr_ai_state_idle_moving;
        rr_component_physical_set_angle(
            physical, physical->angle + (rr_frand() - 0.5) * M_PI);
    }
}

static struct rr_vector predict(struct rr_vector delta,
                                struct rr_vector velocity, float speed)
{
    float distance = rr_vector_get_magnitude(&delta);
    if (speed != 0)
        rr_vector_scale(&velocity, distance / speed);
    else
        rr_vector_set(&velocity, 0, 0);
    rr_vector_add(&delta, &velocity);
    return delta;
}

static void tick_idle_move(EntityIdx entity, struct rr_simulation *simulation)
{
    struct rr_component_ai *ai = rr_simulation_get_ai(simulation, entity);
    struct rr_component_physical *physical =
        rr_simulation_get_physical(simulation, entity);

    struct rr_vector accel;
    rr_vector_from_polar(&accel, RR_PLAYER_SPEED * 0.15, physical->angle);
    rr_vector_add(&physical->acceleration, &accel);
}

static void tick_idle_moving(EntityIdx entity, struct rr_simulation *simulation)
{
    struct rr_component_ai *ai = rr_simulation_get_ai(simulation, entity);
    struct rr_component_physical *physical =
        rr_simulation_get_physical(simulation, entity);

    if (ai->ticks_until_next_action == 0)
    {
        ai->ticks_until_next_action = rand() % 50 + 25;
        ai->ai_state = rr_ai_state_idle;
    }
    struct rr_vector accel;
    rr_vector_from_polar(&accel, RR_PLAYER_SPEED * 0.3, physical->angle);
    rr_vector_add(&physical->acceleration, &accel);
}

static void tick_ai_aggro_ornithomimus(EntityIdx entity,
                                       struct rr_simulation *simulation)
{
    struct rr_component_ai *ai = rr_simulation_get_ai(simulation, entity);
    struct rr_component_physical *physical =
        rr_simulation_get_physical(simulation, entity);
    if (ai->ai_state == rr_ai_state_idle ||
        ai->ai_state == rr_ai_state_idle_moving)
    {
        if (rr_simulation_entity_alive(simulation, ai->target_entity))
        {
            ai->ai_state = rr_ai_state_chasing;
            ai->ticks_until_next_action = 84;
        }
    }

    switch (ai->ai_state)
    {
    case rr_ai_state_idle:
        tick_idle(entity, simulation);
        break;
    case rr_ai_state_idle_moving:
        tick_idle_moving(entity, simulation);
        break;
    case rr_ai_state_chasing:
    {
        struct rr_component_physical *physical2 =
            rr_simulation_get_physical(simulation, ai->target_entity);

        struct rr_vector delta = {physical2->x, physical2->y};
        struct rr_vector target_pos = {physical->x, physical->y};
        rr_vector_sub(&delta, &target_pos);

        rr_component_physical_set_angle(
            physical, M_PI + rr_vector_theta(&delta) +
                          sinf(ai->ticks_until_next_action * 0.3) * 0.5);
        rr_vector_from_polar(&physical->acceleration, RR_PLAYER_SPEED,
                             physical->angle);
        if (rr_vector_get_magnitude(&delta) > 1000)
        {
            ai->target_entity = RR_NULL_ENTITY;
            ai->ticks_until_next_action = 0;
        }
        if (ai->ticks_until_next_action == 0)
        {
            ai->ai_state = rr_ai_state_idle;
            ai->ticks_until_next_action = 84;
        }
        break;
    }
    default:
        RR_UNREACHABLE("tick_ai_aggro_default reached invalid state");
        break;
    }
}

static void tick_ai_aggro_triceratops(EntityIdx entity,
                                      struct rr_simulation *simulation)
{
    struct rr_component_ai *ai = rr_simulation_get_ai(simulation, entity);
    struct rr_component_physical *physical =
        rr_simulation_get_physical(simulation, entity);

    if (ai->ai_state == rr_ai_state_idle ||
        ai->ai_state == rr_ai_state_idle_moving)
    {
        if (rr_simulation_entity_alive(simulation, ai->target_entity))
        {
            ai->ai_state = rr_ai_state_waiting_to_attack;
            ai->ticks_until_next_action = 25;
        }
    }

    switch (ai->ai_state)
    {
    case rr_ai_state_recovering_after_charge:
    case rr_ai_state_idle:
        tick_idle(entity, simulation);
        break;

    case rr_ai_state_idle_moving:
        tick_idle_moving(entity, simulation);
        break;
    case rr_ai_state_waiting_to_attack:
    {
        if (ai->ticks_until_next_action == 0)
        {
            ai->ai_state = rr_ai_state_attacking;
            ai->ticks_until_next_action = rand() % 25 + 33;
            break;
        }

        struct rr_component_physical *physical2 =
            rr_simulation_get_physical(simulation, ai->target_entity);

        struct rr_vector delta = {physical2->x, physical2->y};
        struct rr_vector target_pos = {physical->x, physical->y};
        rr_vector_sub(&delta, &target_pos);
        struct rr_vector prediction =
            predict(delta, physical2->velocity, ai->has_prediction * 15);
        rr_component_physical_set_angle(physical, rr_vector_theta(&prediction));
        break;
    }
    case rr_ai_state_attacking:
    {
        if (ai->ticks_until_next_action == 0)
        {
            ai->ai_state = rr_ai_state_waiting_to_attack;
            ai->ticks_until_next_action = rand() % 25 + 25;
            break;
        }

        struct rr_vector accel;
        struct rr_component_physical *physical2 =
            rr_simulation_get_physical(simulation, ai->target_entity);

        struct rr_vector delta = {physical2->x, physical2->y};
        struct rr_vector target_pos = {physical->x, physical->y};
        rr_vector_sub(&delta, &target_pos);
        struct rr_vector prediction =
            predict(delta, physical2->velocity, ai->has_prediction * 15);
        float target_angle = rr_vector_theta(&prediction);

        rr_component_physical_set_angle(
            physical, rr_angle_lerp(physical->angle, target_angle, 0.05));

        rr_vector_from_polar(&accel, RR_PLAYER_SPEED * 1.65, physical->angle);
        rr_vector_add(&physical->acceleration, &accel);
        break;
    }
    default:
        break;
    }
}

static void tick_ai_aggro_default(EntityIdx entity,
                                  struct rr_simulation *simulation, float speed)
{
    struct rr_component_ai *ai = rr_simulation_get_ai(simulation, entity);
    struct rr_component_physical *physical =
        rr_simulation_get_physical(simulation, entity);
    if (has_new_target(ai, simulation))
        ai->ai_state = rr_ai_state_attacking;

    switch (ai->ai_state)
    {
    case rr_ai_state_idle:
        tick_idle(entity, simulation);
        break;

    case rr_ai_state_idle_moving:
        tick_idle_moving(entity, simulation);
        break;
    case rr_ai_state_attacking:
    {
        struct rr_vector accel;
        struct rr_component_physical *physical2 =
            rr_simulation_get_physical(simulation, ai->target_entity);

        struct rr_vector delta = {physical2->x, physical2->y};
        struct rr_vector target_pos = {physical->x, physical->y};
        rr_vector_sub(&delta, &target_pos);
        // struct rr_vector prediction = predict(delta, physical2->velocity, 4);
        float target_angle = rr_vector_theta(&delta);

        rr_component_physical_set_angle(
            physical, rr_angle_lerp(physical->angle, target_angle, 0.4));

        rr_vector_from_polar(&accel, speed, physical->angle);
        rr_vector_add(&physical->acceleration, &accel);
        ai->ticks_until_next_action = 2;
        break;
    }
    default:
        break;
    }
}

static void tick_ai_aggro_pteranodon(EntityIdx entity,
                                     struct rr_simulation *simulation)
{
    struct rr_component_ai *ai = rr_simulation_get_ai(simulation, entity);
    struct rr_component_physical *physical =
        rr_simulation_get_physical(simulation, entity);

    if (ai->target_entity == RR_NULL_ENTITY)
        ai->target_entity = rr_simulation_find_nearest_enemy(
            simulation, entity, 1550, NULL, no_filter);
    if (rr_simulation_entity_alive(simulation, ai->target_entity) &&
        (ai->ai_state != rr_ai_state_attacking &&
         ai->ai_state != rr_ai_state_shell_shoot_delay))
    {
        ai->ai_state = rr_ai_state_attacking;
        ai->ticks_until_next_action = 50;
    }

    switch (ai->ai_state)
    {
    case rr_ai_state_idle:
        tick_idle(entity, simulation);
        break;

    case rr_ai_state_idle_moving:
        tick_idle_moving(entity, simulation);
        break;
    case rr_ai_state_attacking:
    {
        struct rr_component_physical *physical2 =
            rr_simulation_get_physical(simulation, ai->target_entity);

        struct rr_vector delta = {physical2->x, physical2->y};
        struct rr_vector target_pos = {physical->x, physical->y};
        rr_vector_sub(&delta, &target_pos);
        struct rr_vector prediction =
            predict(delta, physical2->velocity,
                    ai->has_prediction * 20); // make this less op
        rr_component_physical_set_angle(physical, rr_vector_theta(&prediction));
        float distance = rr_vector_get_magnitude(&delta);
        if (distance > 500)
        {
            struct rr_vector accel;
            rr_vector_from_polar(&accel, RR_PLAYER_SPEED, physical->angle);
            rr_vector_add(&physical->acceleration, &accel);
            ai->ticks_until_next_action = 2;
        }
        else
        {
            ai->ai_state = rr_ai_state_shell_shoot_delay;
            ai->ticks_until_next_action = 50 + rr_frand() * 50;
        }
        break;
    }
    case rr_ai_state_shell_shoot_delay:
    {
        struct rr_component_physical *physical2 =
            rr_simulation_get_physical(simulation, ai->target_entity);

        struct rr_vector delta = {physical2->x, physical2->y};
        struct rr_vector target_pos = {physical->x, physical->y};
        rr_vector_sub(&delta, &target_pos);
        struct rr_vector prediction =
            predict(delta, physical2->velocity,
                    ai->has_prediction * 20); // make this less op
        rr_component_physical_set_angle(physical, rr_vector_theta(&prediction));
        if (ai->ticks_until_next_action == 0)
        {
            ai->ai_state = rr_ai_state_attacking;
            ai->ticks_until_next_action = rand() % 25 + 38;

            struct rr_component_mob *mob =
                rr_simulation_get_mob(simulation, entity);
            // spawn a shell
            EntityIdx petal_id = rr_simulation_alloc_petal(
                simulation, physical->arena, physical->x, physical->y,
                rr_petal_id_shell, mob->rarity, mob->parent_id);
            struct rr_component_physical *physical2 =
                rr_simulation_get_physical(simulation, petal_id);
            struct rr_component_health *health =
                rr_simulation_get_health(simulation, petal_id);
            rr_component_physical_set_angle(physical2, physical->angle);
            rr_component_physical_set_radius(
                physical2, 11 * RR_MOB_RARITY_SCALING[mob->rarity].radius);
            physical2->friction = 0.3f;
            physical2->mass = 5.0f;
            physical2->bearing_angle = physical->angle;
            rr_vector_from_polar(&physical2->acceleration, RR_PLAYER_SPEED * 2,
                                 physical->angle);

            rr_component_petal_set_detached(
                rr_simulation_get_petal(simulation, petal_id), 1);

            rr_component_health_set_max_health(
                health, 10 * RR_MOB_RARITY_SCALING[mob->rarity].health);
            rr_component_health_set_health(health, health->max_health);
            health->damage = 10 * RR_MOB_RARITY_SCALING[mob->rarity].damage;
            rr_simulation_get_petal(simulation, petal_id)->effect_delay = 50;

            struct rr_vector recoil;

            rr_vector_from_polar(&recoil, -RR_PLAYER_SPEED * 0.5,
                                 physical->angle); // recoil
            rr_vector_add(&physical->acceleration, &recoil);
        }
        break;
    }
    default:
        break;
    }
}

static void tick_ai_aggro_pachycephalosaurus(EntityIdx entity,
                                             struct rr_simulation *simulation)
{
    struct rr_component_ai *ai = rr_simulation_get_ai(simulation, entity);
    struct rr_component_physical *physical =
        rr_simulation_get_physical(simulation, entity);
    if (has_new_target(ai, simulation))
        ai->ai_state = rr_ai_state_waiting_to_attack;

    switch (ai->ai_state)
    {
    case rr_ai_state_recovering_after_charge:
    case rr_ai_state_idle:
        tick_idle(entity, simulation);
        break;

    case rr_ai_state_idle_moving:
        tick_idle_moving(entity, simulation);
        break;
    case rr_ai_state_waiting_to_attack:
    {
        if (ai->ticks_until_next_action == 0)
        {
            ai->ai_state = rr_ai_state_attacking;
            ai->ticks_until_next_action = rand() % 25 + 33;
            break;
        }

        struct rr_component_physical *physical2 =
            rr_simulation_get_physical(simulation, ai->target_entity);

        struct rr_vector delta = {physical2->x, physical2->y};
        struct rr_vector target_pos = {physical->x, physical->y};
        rr_vector_sub(&delta, &target_pos);
        struct rr_vector prediction =
            predict(delta, physical2->velocity, ai->has_prediction * 15);
        rr_component_physical_set_angle(physical, rr_vector_theta(&prediction));
        break;
    }
    case rr_ai_state_attacking:
    {
        if (ai->ticks_until_next_action == 0)
        {
            ai->ai_state = rr_ai_state_waiting_to_attack;
            ai->ticks_until_next_action = rand() % 25 + 25;
            break;
        }

        struct rr_vector accel;

        rr_vector_from_polar(&accel, RR_PLAYER_SPEED * 1.65, physical->angle);
        rr_vector_add(&physical->acceleration, &accel);
        break;
    }
    default:
        break;
    }
}

static void tick_ai_aggro_ankylosaurus(EntityIdx entity,
                                       struct rr_simulation *simulation)
{
    struct rr_component_ai *ai = rr_simulation_get_ai(simulation, entity);
    struct rr_component_physical *physical =
        rr_simulation_get_physical(simulation, entity);

    if (ai->ai_state == rr_ai_state_idle ||
        ai->ai_state == rr_ai_state_idle_moving)
    {
        if (rr_simulation_entity_alive(simulation, ai->target_entity))
        {
            ai->ai_state = rr_ai_state_chasing;
            ai->ticks_until_next_action = 25;
        }
    }

    if (ai->ai_state == rr_ai_state_attacking)
        physical->knockback_scale = 3.0f;
    else
        physical->knockback_scale = 1.0f;

    switch (ai->ai_state)
    {
    case rr_ai_state_recovering_after_charge:
    case rr_ai_state_idle:
        tick_idle(entity, simulation);
        break;
    case rr_ai_state_idle_moving:
        tick_idle_moving(entity, simulation);
        break;
    case rr_ai_state_chasing:
    {
        struct rr_vector accel;
        struct rr_component_physical *physical2 =
            rr_simulation_get_physical(simulation, ai->target_entity);

        struct rr_vector delta = {physical2->x, physical2->y};
        struct rr_vector target_pos = {physical->x, physical->y};
        rr_vector_sub(&delta, &target_pos);
        // struct rr_vector prediction = predict(delta, physical2->velocity, 4);
        float target_angle = rr_vector_theta(&delta);

        rr_component_physical_set_angle(
            physical, rr_angle_lerp(physical->angle, target_angle, 0.4));

        rr_vector_from_polar(&accel, RR_PLAYER_SPEED * 0.85, physical->angle);
        rr_vector_add(&physical->acceleration, &accel);
        ai->ticks_until_next_action = 2;
        if (rr_vector_magnitude_cmp(&delta, 450) == -1)
        {
            ai->ai_state = rr_ai_state_waiting_to_attack;
            ai->ticks_until_next_action = 25;
        }
        break;
    }
    case rr_ai_state_waiting_to_attack:
    {
        if (ai->ticks_until_next_action == 0)
        {
            ai->ai_state = rr_ai_state_attacking;
            ai->ticks_until_next_action = rand() % 25 + 33;
            break;
        }

        struct rr_component_physical *physical2 =
            rr_simulation_get_physical(simulation, ai->target_entity);

        struct rr_vector delta = {physical2->x, physical2->y};
        struct rr_vector target_pos = {physical->x, physical->y};
        rr_vector_sub(&delta, &target_pos);
        struct rr_vector prediction =
            predict(delta, physical2->velocity, ai->has_prediction * 15);
        rr_component_physical_set_angle(
            physical, rr_vector_theta(&prediction) +
                          sinf(ai->ticks_until_next_action) * 0.2);
        break;
    }
    case rr_ai_state_attacking:
    {
        if (ai->ticks_until_next_action == 0)
        {
            ai->ai_state = rr_ai_state_waiting_to_attack;
            ai->ticks_until_next_action = rand() % 25 + 25;
            break;
        }

        struct rr_vector accel;
        struct rr_component_physical *physical2 =
            rr_simulation_get_physical(simulation, ai->target_entity);

        struct rr_vector delta = {physical2->x, physical2->y};
        struct rr_vector target_pos = {physical->x, physical->y};
        rr_vector_sub(&delta, &target_pos);
        struct rr_vector prediction =
            predict(delta, physical2->velocity, ai->has_prediction * 15);
        float target_angle = rr_vector_theta(&prediction);

        rr_component_physical_set_angle(physical, M_PI + target_angle);

        rr_vector_from_polar(&accel, RR_PLAYER_SPEED * 1.65, target_angle);
        rr_vector_add(&physical->acceleration, &accel);
        break;
    }
    default:
        break;
    }
}

static void tick_ai_aggro_meteor(EntityIdx entity,
                                 struct rr_simulation *simulation)
{
    struct rr_component_ai *ai = rr_simulation_get_ai(simulation, entity);
    struct rr_component_physical *physical =
        rr_simulation_get_physical(simulation, entity);

    switch (ai->ai_state)
    {
    case rr_ai_state_idle:
        ai->ai_state = rr_ai_state_idle_moving;
        float angle = rr_frand() * 2 * M_PI;
        rr_vector_from_polar(&physical->acceleration, RR_PLAYER_SPEED * 0.2,
                             angle);
        break;
    case rr_ai_state_idle_moving:
    {
        float angle = rr_vector_theta(&physical->velocity);
        struct rr_vector position = {physical->x, physical->y};
        if (rr_vector_get_magnitude(&position) >= 3924392) // fix
        {
            float tangent = rr_vector_theta(&position);
            angle = tangent - (M_PI - (tangent - angle));
        }
        rr_vector_from_polar(&physical->acceleration, RR_PLAYER_SPEED * 0.2,
                             angle);
        rr_vector_from_polar(&physical->velocity, 3, angle);
        rr_component_physical_set_angle(physical, physical->angle + 0.1);
        ai->ticks_until_next_action = 10;
        break;
    }
    default:
        break;
    }
}

static void tick_ai_aggro_quetzalcoatlus(EntityIdx entity,
                                         struct rr_simulation *simulation)
{
    struct rr_component_ai *ai = rr_simulation_get_ai(simulation, entity);
    struct rr_component_physical *physical =
        rr_simulation_get_physical(simulation, entity);

    if (has_new_target(ai, simulation))
        ai->ai_state = rr_ai_state_waiting_to_attack;

    switch (ai->ai_state)
    {
    case rr_ai_state_recovering_after_charge:
    case rr_ai_state_idle:
        tick_idle(entity, simulation);
        break;
    case rr_ai_state_idle_moving:
        tick_idle_moving(entity, simulation);
        break;
    case rr_ai_state_waiting_to_attack:
    {
        if (ai->ticks_until_next_action == 0)
        {
            ai->ai_state = rr_ai_state_attacking;
            ai->ticks_until_next_action = 2;
            break;
        }

        if (ai->target_entity == RR_NULL_ENTITY)
        {
            ai->ai_state = rr_ai_state_idle_moving;
            ai->ticks_until_next_action = 25;
            break;
        }

        struct rr_component_physical *physical2 =
            rr_simulation_get_physical(simulation, ai->target_entity);

        struct rr_vector delta = {physical2->x, physical2->y};
        struct rr_vector target_pos = {physical->x, physical->y};
        rr_vector_sub(&delta, &target_pos);
        rr_component_physical_set_angle(physical, rr_vector_theta(&delta));
        break;
    }
    case rr_ai_state_attacking:
    {
        if (ai->ticks_until_next_action == 0)
        {
            ai->ai_state = rr_ai_state_waiting_to_attack;
            ai->ticks_until_next_action = rand() % 12 + 18;
            break;
        }

        if (ai->target_entity == RR_NULL_ENTITY)
        {
            ai->ai_state = rr_ai_state_idle_moving;
            ai->ticks_until_next_action = 25;
            break;
        }

        struct rr_vector accel;
        struct rr_component_physical *physical2 =
            rr_simulation_get_physical(simulation, ai->target_entity);

        struct rr_vector delta = {physical2->x, physical2->y};
        struct rr_vector target_pos = {physical->x, physical->y};
        rr_vector_sub(&delta, &target_pos);
        float target_angle = rr_vector_theta(&delta);

        rr_component_physical_set_angle(physical, target_angle);

        rr_vector_from_polar(&accel, RR_PLAYER_SPEED * 22.5, target_angle);
        rr_vector_add(&physical->acceleration, &accel);
        break;
    }
    default:
        break;
    }
}

static void tick_ai_aggro_edmontosaurus(EntityIdx entity,
                                        struct rr_simulation *simulation)
{
    struct rr_component_ai *ai = rr_simulation_get_ai(simulation, entity);
    struct rr_component_physical *physical =
        rr_simulation_get_physical(simulation, entity);

    if (ai->ai_state == rr_ai_state_idle ||
        ai->ai_state == rr_ai_state_idle_moving)
    {
        if (rr_simulation_entity_alive(simulation, ai->target_entity))
        {
            ai->ai_state = rr_ai_state_attacking;
            ai->ticks_until_next_action = 25;
        }
    }

    switch (ai->ai_state)
    {
    case rr_ai_state_idle:
        tick_idle(entity, simulation);
        break;

    case rr_ai_state_idle_moving:
        tick_idle_moving(entity, simulation);
        break;
    case rr_ai_state_attacking:
    {
        ai->ticks_until_next_action = 25;
        if (ai->target_entity == RR_NULL_ENTITY)
        {
            ai->ai_state = rr_ai_state_idle_moving;
            break;
        }

        struct rr_vector accel;
        struct rr_component_physical *physical2 =
            rr_simulation_get_physical(simulation, ai->target_entity);

        struct rr_vector delta = {physical2->x, physical2->y};
        struct rr_vector target_pos = {physical->x, physical->y};
        rr_vector_sub(&delta, &target_pos);
        float target_angle = rr_vector_theta(&delta);

        rr_component_physical_set_angle(physical, target_angle);

        rr_vector_from_polar(&accel, RR_PLAYER_SPEED * 1.25, physical->angle);
        rr_vector_add(&physical->acceleration, &accel);
        break;
    }
    default:
        break;
    }
}

static void tick_ai_aggro_hornet(EntityIdx entity,
                                 struct rr_simulation *simulation)
{
    struct rr_component_ai *ai = rr_simulation_get_ai(simulation, entity);
    struct rr_component_physical *physical =
        rr_simulation_get_physical(simulation, entity);

    if (has_new_target(ai, simulation))
        ai->ai_state = rr_ai_state_waiting_to_attack;

    switch (ai->ai_state)
    {
    case rr_ai_state_recovering_after_charge:
    case rr_ai_state_idle:
        tick_idle(entity, simulation);
        break;
    case rr_ai_state_idle_moving:
        tick_idle_moving(entity, simulation);
        break;
    case rr_ai_state_waiting_to_attack:
    {
        ai->ticks_until_next_action = 10;

        if (ai->target_entity == RR_NULL_ENTITY)
        {
            ai->ai_state = rr_ai_state_idle_moving;
            ai->ticks_until_next_action = 25;
            break;
        }

        struct rr_component_physical *physical2 =
            rr_simulation_get_physical(simulation, ai->target_entity);

        struct rr_vector delta = {physical2->x, physical2->y};
        struct rr_vector target_pos = {physical->x, physical->y};
        rr_vector_sub(&delta, &target_pos);
        rr_component_physical_set_angle(physical, rr_vector_theta(&delta));
        rr_vector_from_polar(&physical->acceleration, RR_PLAYER_SPEED,
                             physical->angle);
        if (rr_vector_magnitude_cmp(&delta, physical->radius + 250) == -1)
        {
            ai->ai_state = rr_ai_state_attacking;
            ai->ticks_until_next_action = 50;
            rr_component_physical_set_angle(physical, physical->angle + M_PI);
        }
        break;
    }
    case rr_ai_state_attacking:
    {
        if (ai->ticks_until_next_action == 0)
        {
            ai->ai_state = rr_ai_state_waiting_to_attack;
            ai->ticks_until_next_action = 20;
            break;
        }

        if (ai->target_entity == RR_NULL_ENTITY)
        {
            ai->ai_state = rr_ai_state_idle_moving;
            ai->ticks_until_next_action = 25;
            break;
        }

        rr_vector_from_polar(&physical->acceleration, -RR_PLAYER_SPEED * 1.5,
                             physical->angle);
        break;
    }
    default:
        break;
    }
}

static void system_for_each(EntityIdx entity, void *simulation)
{
    struct rr_simulation *this = simulation;

    if (rr_simulation_has_centipede(this, entity) &&
        rr_simulation_get_centipede(this, entity)->parent_node !=
            RR_NULL_ENTITY)
        return;
    if (rr_simulation_has_arena(this, entity))
        return;
    if (rr_simulation_get_health(this, entity)->health < 0.0001f)
        return;

    struct rr_component_ai *ai = rr_simulation_get_ai(this, entity);
    struct rr_component_mob *mob = rr_simulation_get_mob(this, entity);
    struct rr_component_physical *physical =
        rr_simulation_get_physical(this, entity);
    if (physical->stun_ticks > 0)
        return;
    struct rr_component_relations *relations =
        rr_simulation_get_relations(this, entity);
    if (ai->target_entity != RR_NULL_ENTITY &&
        !rr_simulation_entity_alive(simulation, ai->target_entity))
    {
        ai->target_entity = RR_NULL_ENTITY;
        ai->ai_state = rr_ai_state_idle;
        ai->ticks_until_next_action = 25;
    }
    if (ai->target_entity != RR_NULL_ENTITY)
    {
        struct rr_component_physical *t_physical =
            rr_simulation_get_physical(this, ai->target_entity);
        struct rr_vector diff = {physical->x - t_physical->x,
                                 physical->y - t_physical->y};
        if (rr_vector_get_magnitude(&diff) > 2000)
        {
            ai->target_entity = RR_NULL_ENTITY;
            ai->ai_state = rr_ai_state_idle;
            ai->ticks_until_next_action = 25;
        }
    }
    if (mob->player_spawned)
    {
        if (!rr_simulation_entity_alive(simulation, relations->owner))
        {
            rr_simulation_request_entity_deletion(simulation, entity);
            return;
        }
        struct rr_component_physical *flower_physical =
            rr_simulation_get_physical(this, relations->owner);
        float dx = flower_physical->x - physical->x;
        float dy = flower_physical->y - physical->y;
        if ((ai->ai_state == rr_ai_state_returning_to_owner &&
             dx * dx + dy * dy >
                 (250 + physical->radius) * (250 + physical->radius)))
        {
            struct rr_vector accel = {dx, dy};
            rr_vector_set_magnitude(&accel, RR_PLAYER_SPEED * 1.2);
            rr_vector_add(&physical->acceleration, &accel);
            rr_component_physical_set_angle(physical, rr_vector_theta(&accel));
            ai->target_entity = RR_NULL_ENTITY;
            return;
        }
        else if (dx * dx + dy * dy >
                 (1000 + physical->radius) * (1000 + physical->radius))
        {
            ai->ai_state = rr_ai_state_returning_to_owner;
            struct rr_vector accel = {dx, dy};
            rr_vector_set_magnitude(&accel, RR_PLAYER_SPEED * 1.2);
            rr_vector_add(&physical->acceleration, &accel);
            rr_component_physical_set_angle(physical, rr_vector_theta(&accel));
            ai->target_entity = RR_NULL_ENTITY;
            return;
        }
        else if (ai->ai_state == rr_ai_state_returning_to_owner)
        {
            ai->ai_state = rr_ai_state_idle;
            ai->ticks_until_next_action = rand() % 25 + 25;
        }
    }

    switch (mob->id)
    {
    case rr_mob_id_fern:
    case rr_mob_id_tree:
        break;
    case rr_mob_id_ant:
    case rr_mob_id_ornithomimus:
        tick_ai_aggro_ornithomimus(entity, this);
        break;
    case rr_mob_id_triceratops:
        tick_ai_aggro_triceratops(entity, this);
        break;
    case rr_mob_id_pachycephalosaurus:
        tick_ai_aggro_pachycephalosaurus(entity, this);
        break;
    case rr_mob_id_honeybee:
    case rr_mob_id_trex:
        tick_ai_aggro_default(entity, this, RR_PLAYER_SPEED * 0.95);
        break;
    case rr_mob_id_dakotaraptor:
        tick_ai_aggro_default(entity, this, RR_PLAYER_SPEED * 1.5);
        break;
    case rr_mob_id_dragonfly:
        tick_ai_aggro_default(entity, this, RR_PLAYER_SPEED * 1.6);
        break;
    case rr_mob_id_spider:
        tick_ai_aggro_default(entity, this, RR_PLAYER_SPEED * 1.5);
        break;
    case rr_mob_id_pteranodon:
        tick_ai_aggro_pteranodon(entity, this);
        break;
    case rr_mob_id_ankylosaurus:
        tick_ai_aggro_ankylosaurus(entity, this);
        break;
    case rr_mob_id_meteor:
        tick_ai_aggro_meteor(entity, this);
        break;
    case rr_mob_id_quetzalcoatlus:
        tick_ai_aggro_quetzalcoatlus(entity, this);
        break;
    case rr_mob_id_edmontosaurus:
        tick_ai_aggro_edmontosaurus(entity, this);
        break;
    case rr_mob_id_hornet:
        tick_ai_aggro_hornet(entity, this);
        break;
    default:
        RR_UNREACHABLE("invalid ai aggro type state");
        break;
    }
    ai->ticks_until_next_action--;
}

void rr_system_ai_tick(struct rr_simulation *simulation)
{
    rr_simulation_for_each_ai(simulation, simulation, system_for_each);
}
