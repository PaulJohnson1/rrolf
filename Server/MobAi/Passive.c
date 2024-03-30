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

void tick_ai_passive_default(EntityIdx entity, struct rr_simulation *simulation)
{
    struct rr_component_ai *ai = rr_simulation_get_ai(simulation, entity);
    struct rr_component_physical *physical =
        rr_simulation_get_physical(simulation, entity);

    switch (ai->ai_state)
    {
    case rr_ai_state_idle:
        tick_idle(entity, simulation);
        break;

    case rr_ai_state_idle_moving:
        tick_idle_move_default(entity, simulation);
        break;
    default:
        break;
    }
}

void tick_ai_passive_meteor(EntityIdx entity, struct rr_simulation *simulation)
{
    struct rr_component_ai *ai = rr_simulation_get_ai(simulation, entity);
    struct rr_component_physical *physical =
        rr_simulation_get_physical(simulation, entity);

    switch (ai->ai_state)
    {
    case rr_ai_state_idle:
        physical->bearing_angle = rr_frand() * M_PI * 2;
        ai->ai_state = rr_ai_state_idle_moving;
        break;
    case rr_ai_state_idle_moving:
        ai->ticks_until_next_action = 10;
        struct rr_vector normal = {physical->wall_collision.x,
                                   physical->wall_collision.y};
        if (rr_vector_get_magnitude(&normal) != 0)
        {
            float angle = rr_vector_theta(&normal);
            physical->bearing_angle =
                (2 * angle - (M_PI + physical->bearing_angle));
        }

        rr_vector_from_polar(&physical->acceleration, RR_PLAYER_SPEED * 0.15,
                             physical->bearing_angle);
        rr_component_physical_set_angle(physical, physical->angle + 0.1);
        break;
    default:
        break;
    }
}