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

#include <Server/MobAi/Ai.h>

#include <math.h>

#include <Server/EntityDetection.h>
#include <Server/Simulation.h>

void tick_ai_neutral_default(EntityIdx entity, struct rr_simulation *simulation,
                             float speed)
{
    struct rr_component_ai *ai = rr_simulation_get_ai(simulation, entity);
    struct rr_component_physical *physical =
        rr_simulation_get_physical(simulation, entity);
    if (rr_simulation_entity_alive(simulation, ai->target_entity) &&
        ai_is_passive(ai))
    {
        ai->ai_state = rr_ai_state_attacking;
        ai->ticks_until_next_action = 25;
    }

    switch (ai->ai_state)
    {
    case rr_ai_state_idle:
        tick_idle(entity, simulation);
        break;

    case rr_ai_state_idle_moving:
        tick_idle_move_default(entity, simulation);
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

void tick_ai_neutral_triceratops(EntityIdx entity,
                                 struct rr_simulation *simulation)
{
    struct rr_component_ai *ai = rr_simulation_get_ai(simulation, entity);
    struct rr_component_physical *physical =
        rr_simulation_get_physical(simulation, entity);

    if (rr_simulation_entity_alive(simulation, ai->target_entity) &&
        ai_is_passive(ai))
    {
        ai->ai_state = rr_ai_state_waiting_to_attack;
        ai->ticks_until_next_action = 18;
    }

    switch (ai->ai_state)
    {
    case rr_ai_state_idle:
        tick_idle(entity, simulation);
        break;

    case rr_ai_state_idle_moving:
        tick_idle_move_default(entity, simulation);
        break;
    case rr_ai_state_waiting_to_attack:
    {
        if (ai->ticks_until_next_action == 0)
        {
            ai->ai_state = rr_ai_state_attacking;
            ai->ticks_until_next_action = rand() % 25 + 63;
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
            ai->ticks_until_next_action = rand() % 12 + 12;
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
            physical, rr_angle_lerp(physical->angle, target_angle, 0.25));

        rr_vector_from_polar(&accel, RR_PLAYER_SPEED * 1.3, physical->angle);
        rr_vector_add(&physical->acceleration, &accel);
        break;
    }
    default:
        break;
    }
}

void tick_ai_neutral_ornithomimus(EntityIdx entity,
                                  struct rr_simulation *simulation)
{
    struct rr_component_ai *ai = rr_simulation_get_ai(simulation, entity);
    struct rr_component_physical *physical =
        rr_simulation_get_physical(simulation, entity);

    if (rr_simulation_entity_alive(simulation, ai->target_entity) &&
        ai_is_passive(ai))
    {
        ai->ai_state = rr_ai_state_attacking;
        ai->ticks_until_next_action = -1;
    }

    switch (ai->ai_state)
    {
    case rr_ai_state_idle:
        tick_idle(entity, simulation);
        break;

    case rr_ai_state_idle_moving:
        tick_idle_move_default(entity, simulation);
        break;
    case rr_ai_state_attacking:
    {
        struct rr_vector accel;
        struct rr_component_physical *physical2 =
            rr_simulation_get_physical(simulation, ai->target_entity);

        struct rr_vector delta = {physical2->x, physical2->y};
        struct rr_vector target_pos = {physical->x, physical->y};
        rr_vector_sub(&delta, &target_pos);
        if (rr_simulation_get_mob(simulation, entity)->rarity >=
            rr_rarity_id_exotic)
            physical->bearing_angle = rr_vector_theta(&delta);
        else
            physical->bearing_angle = rr_vector_theta(&delta) + M_PI;

        tick_idle_move_sinusoid(entity, simulation, RR_PLAYER_SPEED);
        break;
    }
    default:
        break;
    }
}

void tick_ai_neutral_ankylosaurus(EntityIdx entity,
                                  struct rr_simulation *simulation)
{
    struct rr_component_ai *ai = rr_simulation_get_ai(simulation, entity);
    struct rr_component_physical *physical =
        rr_simulation_get_physical(simulation, entity);
    if (rr_simulation_entity_alive(simulation, ai->target_entity) &&
        ai_is_passive(ai))
    {
        ai->ai_state = rr_ai_state_attacking;
        ai->ticks_until_next_action = 10;
    }
    physical->knockback_scale = 1;

    switch (ai->ai_state)
    {
    case rr_ai_state_idle:
        tick_idle(entity, simulation);
        break;

    case rr_ai_state_idle_moving:
        tick_idle_move_default(entity, simulation);
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

        rr_component_physical_set_angle(physical, target_angle);

        rr_vector_from_polar(&accel, RR_PLAYER_SPEED * 1.1, physical->angle);
        rr_vector_add(&physical->acceleration, &accel);
        ai->ticks_until_next_action = 10;
        if (rr_vector_magnitude_cmp(&delta, 100 + physical->radius) == -1)
        {
            ai->ai_state = (rr_simulation_get_mob(simulation, entity)->rarity >=
                                rr_rarity_id_exotic &&
                            rr_frand() < 0.2)
                               ? rr_ai_state_exotic_special
                               : rr_ai_state_charging;
            ai->ticks_until_next_action = 25;
        }
        break;
    }
    case rr_ai_state_charging:
    {
        physical->knockback_scale = 25;
        struct rr_vector accel;
        struct rr_component_physical *physical2 =
            rr_simulation_get_physical(simulation, ai->target_entity);

        struct rr_vector delta = {physical2->x, physical2->y};
        struct rr_vector target_pos = {physical->x, physical->y};
        rr_vector_sub(&delta, &target_pos);
        float target_angle = rr_vector_theta(&delta);

        rr_component_physical_set_angle(physical, target_angle);

        rr_vector_from_polar(&accel, RR_PLAYER_SPEED * 1.8, physical->angle);
        rr_vector_add(&physical->acceleration, &accel);
        if (ai->ticks_until_next_action == 0)
        {
            ai->ticks_until_next_action = 10;
            ai->ai_state = rr_ai_state_attacking;
        }
        break;
    }
    case rr_ai_state_exotic_special:
    {
        physical->knockback_scale = 125;
        struct rr_vector accel;
        struct rr_component_physical *physical2 =
            rr_simulation_get_physical(simulation, ai->target_entity);

        struct rr_vector delta = {physical2->x, physical2->y};
        struct rr_vector target_pos = {physical->x, physical->y};
        rr_vector_sub(&delta, &target_pos);
        float target_angle = rr_vector_theta(&delta);

        rr_component_physical_set_angle(physical, target_angle + M_PI);

        rr_vector_from_polar(&accel, RR_PLAYER_SPEED * 3.0, physical->angle);
        rr_vector_add(&physical->acceleration, &accel);
        if (ai->ticks_until_next_action == 0)
        {
            ai->ticks_until_next_action = 10;
            ai->ai_state = rr_ai_state_attacking;
        }
        break;
    }
    default:
        break;
    }
}