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

#include <Client/System/Interpolation.h>

#include <math.h>

#include <Shared/Entity.h>
#include <Shared/SimulationCommon.h>
#include <Shared/Vector.h>

struct function_captures
{
    float delta;
    struct rr_simulation *simulation;
};

void system_interpolation_for_each_function(EntityIdx entity, void *_captures)
{
    struct function_captures *captures = _captures;
    struct rr_simulation *this = captures->simulation;
    float delta = captures->delta;
    if (rr_simulation_has_physical(this, entity))
    {
        struct rr_component_physical *physical =
            rr_simulation_get_physical(this, entity);
        if (physical->lerp_x == 0)
            physical->lerp_x = physical->x;
        if (physical->lerp_y == 0)
            physical->lerp_y = physical->y;

        physical->velocity.x = physical->x - physical->lerp_x;
        physical->velocity.y = physical->y - physical->lerp_y;

        physical->lerp_x = rr_lerp(physical->lerp_x, physical->x, 10 * delta);
        physical->lerp_y = rr_lerp(physical->lerp_y, physical->y, 10 * delta);
        physical->lerp_velocity.x =
            rr_lerp(physical->lerp_velocity.x, physical->velocity.x, 5 * delta);
        physical->lerp_velocity.y =
            rr_lerp(physical->lerp_velocity.y, physical->velocity.y, 5 * delta);
        if (physical->lerp_angle == 0)
            physical->lerp_angle = physical->angle;

        physical->lerp_radius =
            rr_lerp(physical->lerp_radius, physical->radius, 10 * delta);
        physical->lerp_angle =
            rr_angle_lerp(physical->lerp_angle, physical->angle, 10 * delta);
        if (rr_simulation_has_mob(this, entity))
        {
            if (physical->turning_animation == 0)
                physical->turning_animation = physical->angle;

            physical->lerp_radius =
                rr_lerp(physical->lerp_radius, physical->radius, 10 * delta);
            physical->lerp_angle = rr_angle_lerp(physical->lerp_angle,
                                                 physical->angle, 10 * delta);
            physical->turning_animation = rr_angle_lerp(
                physical->turning_animation, physical->angle, 6 * delta);

            physical->animation_timer +=
                (2 * (physical->parent_id % 2) - 1) * delta *
                (fmin(rr_vector_get_magnitude(&physical->lerp_velocity), 20) *
                     0.5 +
                 1) *
                2;
        }
        else
            physical->animation_timer += 0.5;
    }

    if (rr_simulation_has_flower(this, entity))
    {
        struct rr_component_flower *flower =
            rr_simulation_get_flower(this, entity);
        struct rr_component_physical *physical =
            rr_simulation_get_physical(this, entity);
        flower->eye_x = cosf(flower->eye_angle - physical->angle) * 3;
        flower->eye_y = sinf(flower->eye_angle - physical->angle) * 3;
        if (flower->lerp_eye_x == 0)
            flower->lerp_eye_x = flower->eye_x;
        if (flower->lerp_eye_y == 0)
            flower->lerp_eye_y = flower->eye_y;
        if (flower->lerp_mouth == 0)
            flower->lerp_mouth = 15;
        flower->lerp_eye_x =
            rr_lerp(flower->lerp_eye_x, flower->eye_x, 20 * delta);
        flower->lerp_eye_y =
            rr_lerp(flower->lerp_eye_y, flower->eye_y, 20 * delta);
        if (flower->face_flags & 1)
            flower->lerp_mouth = rr_lerp(flower->lerp_mouth, 5, 20 * delta);
        else if (flower->face_flags & 2)
            flower->lerp_mouth = rr_lerp(flower->lerp_mouth, 8, 20 * delta);
        else
            flower->lerp_mouth = rr_lerp(flower->lerp_mouth, 15, 20 * delta);
    }

    if (rr_simulation_has_player_info(this, entity))
    {
        struct rr_component_player_info *player_info =
            rr_simulation_get_player_info(this, entity);
        if (player_info->lerp_camera_fov == 0)
            player_info->lerp_camera_fov = player_info->camera_fov;
        if (player_info->lerp_camera_x == 0)
            player_info->lerp_camera_x = player_info->camera_x;
        if (player_info->lerp_camera_y == 0)
            player_info->lerp_camera_y = player_info->camera_y;
        player_info->lerp_camera_fov = rr_lerp(
            player_info->lerp_camera_fov, player_info->camera_fov, 15 * delta);
        player_info->lerp_camera_x = rr_lerp(player_info->lerp_camera_x,
                                             player_info->camera_x, 10 * delta);
        player_info->lerp_camera_y = rr_lerp(player_info->lerp_camera_y,
                                             player_info->camera_y, 10 * delta);
    }

    if (rr_simulation_has_health(this, entity))
    {
        struct rr_component_health *health =
            rr_simulation_get_health(this, entity);
        health->damage_animation =
            rr_lerp(health->damage_animation, 0, 5 * delta);
        if (health->flags & 2)
        {
            if (health->damage_animation < 0.25)
                health->damage_animation = 1;
        }
        if (health->lerp_health == 0)
            health->lerp_health = health->health;
        health->lerp_health =
            rr_lerp(health->lerp_health, health->health, 25 * delta);
    }
}

void rr_system_interpolation_tick(struct rr_simulation *simulation, float delta)
{
    struct function_captures captures;
    captures.simulation = simulation;
    captures.delta = delta;
    rr_simulation_for_each_entity(simulation, &captures,
                                  system_interpolation_for_each_function);
    simulation->updated_this_tick = 0;
}
