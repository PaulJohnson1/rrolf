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

#include <Server/Simulation.h>
#include <Shared/Entity.h>
#include <Shared/StaticData.h>
#include <Shared/Vector.h>

static void perform_internal_bound_check_custom_grid(
    struct rr_component_arena *arena, float test_x, float test_y, int32_t x,
    int32_t y, struct rr_component_physical *physical)
{
    // add a check for in-wall
    uint32_t size = arena->maze->maze_dim;
    float maze_dim = arena->maze->grid_size;
#define offset(a, b)                                                           \
    ((x + a < 0 || y + b < 0 || x + a >= size || y + b >= size)                \
         ? 0                                                                   \
         : rr_component_arena_get_grid(arena, x + a, y + b)->value)

#define curve_check                                                            \
    {                                                                          \
        struct rr_vector dist = {test_x - cx, test_y - cy};                    \
        if (rr_vector_magnitude_cmp(&dist, maze_dim - physical->radius) ==     \
                1 &&                                                           \
            inverse == 0)                                                      \
        {                                                                      \
            rr_vector_set_magnitude(&dist, maze_dim - physical->radius);       \
            rr_component_physical_set_x(physical, cx + dist.x);                \
            rr_component_physical_set_y(physical, cy + dist.y);                \
            rr_vector_set(&physical->wall_collision, -dist.x, -dist.y);        \
            return;                                                            \
        }                                                                      \
        if (rr_vector_magnitude_cmp(&dist, maze_dim + physical->radius) ==     \
                -1 &&                                                          \
            inverse == 1)                                                      \
        {                                                                      \
            rr_vector_set_magnitude(&dist, maze_dim + physical->radius);       \
            rr_component_physical_set_x(physical, cx + dist.x);                \
            rr_component_physical_set_y(physical, cy + dist.y);                \
            rr_vector_set(&physical->wall_collision, dist.x, dist.y);          \
            return;                                                            \
        }                                                                      \
    }

    if (offset(0, 0) != 1)
    {
        // tile can't be 0 (that would be illegal)
        uint8_t tile = offset(0, 0);
        if (tile == 0)
            return;
        uint8_t left = (tile >> 1) & 1;
        uint8_t top = tile & 1;
        uint8_t inverse = ((tile >> 3) & 1);
        float cx = (x + left) * maze_dim;
        float cy = (y + top) * maze_dim;
        curve_check;
    }
    if (offset(-1, 0) != 1 && test_x - x * maze_dim < physical->radius)
    {
        uint8_t tile = offset(-1, 0);
        if (tile == 0)
        {
            test_x = x * maze_dim + physical->radius;
            rr_component_physical_set_x(physical, test_x);
            rr_component_physical_set_y(physical, test_y);
            rr_vector_set(&physical->wall_collision, 1, 0);
            return;
        }
        else
        {
            uint8_t left = (tile >> 1) & 1;
            uint8_t top = tile & 1;
            uint8_t inverse = ((tile >> 3) & 1);
            float cx = (x - 1 + left) * maze_dim;
            float cy = (y + top) * maze_dim;
            curve_check;
        }
    }
    if (offset(0, -1) != 1 && test_y - y * maze_dim < physical->radius)
    {
        uint8_t tile = offset(0, -1);
        if (tile == 0)
        {
            test_y = y * maze_dim + physical->radius;
            rr_component_physical_set_x(physical, test_x);
            rr_component_physical_set_y(physical, test_y);
            rr_vector_set(&physical->wall_collision, 0, 1);
            return;
        }
        else
        {
            uint8_t left = (tile >> 1) & 1;
            uint8_t top = tile & 1;
            uint8_t inverse = ((tile >> 3) & 1);
            float cx = (x + left) * maze_dim;
            float cy = (y - 1 + top) * maze_dim;
            curve_check;
        }
    }
    if (offset(1, 0) != 1 && (x + 1) * maze_dim - test_x < physical->radius)
    {
        uint8_t tile = offset(1, 0);
        if (tile == 0)
        {
            test_x = (x + 1) * maze_dim - physical->radius;
            rr_component_physical_set_x(physical, test_x);
            rr_component_physical_set_y(physical, test_y);
            rr_vector_set(&physical->wall_collision, -1, 0);
            return;
        }
        else
        {
            uint8_t left = (tile >> 1) & 1;
            uint8_t top = tile & 1;
            uint8_t inverse = ((tile >> 3) & 1);
            float cx = (x + 1 + left) * maze_dim;
            float cy = (y + top) * maze_dim;
            curve_check;
        }
    }
    if (offset(0, 1) != 1 && (y + 1) * maze_dim - test_y < physical->radius)
    {
        uint8_t tile = offset(0, 1);
        if (tile == 0)
        {
            test_y = (y + 1) * maze_dim - physical->radius;
            rr_component_physical_set_x(physical, test_x);
            rr_component_physical_set_y(physical, test_y);
            rr_vector_set(&physical->wall_collision, 0, -1);
            return;
        }
        else
        {
            uint8_t left = (tile >> 1) & 1;
            uint8_t top = tile & 1;
            uint8_t inverse = ((tile >> 3) & 1);
            float cx = (x + left) * maze_dim;
            float cy = (y + 1 + top) * maze_dim;
            curve_check;
        }
    }
    rr_component_physical_set_x(physical, test_x);
    rr_component_physical_set_y(physical, test_y);
#undef offset
#undef curve_check
}

static void perform_internal_bound_check(struct rr_component_arena *arena,
                                         float test_x, float test_y,
                                         struct rr_component_physical *physical)
{
    int32_t x = test_x / arena->maze->grid_size;
    int32_t y = test_y / arena->maze->grid_size;
    perform_internal_bound_check_custom_grid(arena, test_x, test_y, x, y,
                                             physical);
}

static float reverse_lerp(float test, float start, float end)
{
    if (start == end)
        return 1;

    float proj = (test - start) / (end - start);
    if (proj > 1 || proj < 0)
        proj = 1;
    return proj;
}

static uint32_t min_of_4(float *arr)
{
    uint32_t min = 0;
    if (arr[1] < arr[min])
        min = 1;
    if (arr[2] < arr[min])
        min = 2;
    if (arr[3] < arr[min])
        min = 3;
    return min;
}

static void system_velocity(EntityIdx id, void *simulation)
{
    struct rr_component_physical *physical =
        rr_simulation_get_physical(simulation, id);
    rr_vector_scale(&physical->velocity, physical->friction);
    physical->acceleration_scale *=
        rr_lerp(physical->web_slowdown, 1, physical->slow_resist);
    if (physical->stun_ticks > 0)
    {
        if (!rr_simulation_has_petal(simulation, id))
            physical->acceleration_scale = 0;
        --physical->stun_ticks;
    }
    struct rr_vector accel = {
        physical->acceleration.x * physical->acceleration_scale,
        physical->acceleration.y * physical->acceleration_scale};
    rr_vector_add(&physical->velocity, &accel);
    physical->acceleration_scale = physical->web_slowdown = 1;
    struct rr_vector vel = {physical->velocity.x, physical->velocity.y};
    rr_vector_add(&vel, &physical->collision_velocity);
    if (rr_simulation_has_flower(simulation, id))
    {
        if (physical->acceleration.x != 0.0f ||
            physical->acceleration.y != 0.0f)
        {
            rr_component_flower_set_eye_angle(
                rr_simulation_get_flower(simulation, id),
                rr_vector_theta(&physical->acceleration));
        }
    }
    rr_vector_set(&physical->acceleration, 0, 0);
    rr_vector_set(&physical->wall_collision, 0, 0);
    struct rr_component_arena *arena =
        rr_simulation_get_arena(simulation, physical->arena);
    if (rr_vector_magnitude_cmp(&vel, arena->maze->grid_size) == 1)
        rr_vector_set_magnitude(&vel, arena->maze->grid_size);
    float before_x = physical->x;
    float before_y = physical->y;
    float now_x = rr_fclamp(before_x + vel.x, physical->radius,
                            arena->maze->maze_dim * arena->maze->grid_size -
                                physical->radius);
    float now_y = rr_fclamp(before_y + vel.y, physical->radius,
                            arena->maze->maze_dim * arena->maze->grid_size -
                                physical->radius);

    if (rr_simulation_has_web(simulation, id) ||
        (rr_simulation_has_petal(simulation, id) &&
         rr_simulation_get_petal(simulation, id)->id != rr_petal_id_egg &&
         rr_simulation_get_petal(simulation, id)->id != rr_petal_id_seed))
    {
        rr_component_physical_set_x(physical, before_x + vel.x);
        rr_component_physical_set_y(physical, before_y + vel.y);
        return;
    }
    int32_t before_grid_x = floorf(before_x / arena->maze->grid_size);
    int32_t now_grid_x = floorf(now_x / arena->maze->grid_size);
    int32_t before_grid_y = floorf(before_y / arena->maze->grid_size);
    int32_t now_grid_y = floorf(now_y / arena->maze->grid_size);
#define grid(a, b)                                                             \
    ((before_grid_x + a < 0 || before_grid_y + b < 0 ||                        \
      before_grid_x + a >= arena->maze->maze_dim ||                            \
      before_grid_y + b >= arena->maze->maze_dim)                              \
         ? 0                                                                   \
         : rr_component_arena_get_grid(arena, before_grid_x + a,               \
                                       before_grid_y + b)                      \
               ->value)
    if (before_grid_x == now_grid_x && before_grid_y == now_grid_y)
        perform_internal_bound_check(arena, now_x, now_y, physical);
    else
    {
        float border_phase[4];
        border_phase[0] = reverse_lerp(before_grid_x * arena->maze->grid_size,
                                       before_x, now_x);
        border_phase[1] = reverse_lerp(
            (before_grid_x + 1) * arena->maze->grid_size, before_x, now_x);
        border_phase[2] = reverse_lerp(before_grid_y * arena->maze->grid_size,
                                       before_y, now_y);
        border_phase[3] = reverse_lerp(
            (before_grid_y + 1) * arena->maze->grid_size, before_y, now_y);
        // if (passes_behind_borders) fclamp(x and y)
        uint32_t phase = min_of_4(border_phase);
        // printf("phase is %d\n", phase);
        if (grid(0, 0) != 1)
        {
            uint8_t tile = grid(0, 0);
            uint8_t left = (tile >> 1) & 1;
            uint8_t top = tile & 1;
            uint8_t inverse = ((tile >> 3) & 1) ^ 1;
            uint8_t illegal_hor = (top ^ inverse) | 2;
            uint8_t illegal_ver = (left ^ inverse);
            if (phase == illegal_hor || phase == illegal_ver)
            {
                now_x = rr_fclamp(now_x, before_grid_x * arena->maze->grid_size,
                                  (before_grid_x + 1) * arena->maze->grid_size);
                now_y = rr_fclamp(now_y, before_grid_y * arena->maze->grid_size,
                                  (before_grid_y + 1) * arena->maze->grid_size);
                perform_internal_bound_check_custom_grid(
                    arena, now_x, now_y, before_grid_x, before_grid_y,
                    physical);
            }
            else
            {
                int32_t hor = phase < 2 ? ((phase & 1) * 2) - 1 : 0;
                int32_t ver = phase >= 2 ? ((phase & 1) * 2) - 1 : 0;
                if (grid(hor, ver) == 0)
                {
                    if (hor)
                        now_x = rr_fclamp(
                            now_x,
                            before_grid_x * arena->maze->grid_size +
                                physical->radius,
                            (before_grid_x + 1) * arena->maze->grid_size -
                                physical->radius);
                    else
                        now_y = rr_fclamp(
                            now_y,
                            before_grid_y * arena->maze->grid_size +
                                physical->radius,
                            (before_grid_y + 1) * arena->maze->grid_size -
                                physical->radius);
                    rr_component_physical_set_x(physical, now_x);
                    rr_component_physical_set_y(physical, now_y);
                }
                perform_internal_bound_check_custom_grid(
                    arena, now_x, now_y, before_grid_x + hor,
                    before_grid_y + ver, physical);
            }
        }
        else
        {
            int32_t hor = phase < 2 ? ((phase & 1) * 2) - 1 : 0;
            int32_t ver = phase >= 2 ? ((phase & 1) * 2) - 1 : 0;
            if (grid(hor, ver) == 0)
            {
                if (hor)
                    now_x =
                        rr_fclamp(now_x,
                                  before_grid_x * arena->maze->grid_size +
                                      physical->radius,
                                  (before_grid_x + 1) * arena->maze->grid_size -
                                      physical->radius);
                else
                    now_y =
                        rr_fclamp(now_y,
                                  before_grid_y * arena->maze->grid_size +
                                      physical->radius,
                                  (before_grid_y + 1) * arena->maze->grid_size -
                                      physical->radius);
                rr_component_physical_set_x(physical, now_x);
                rr_component_physical_set_y(physical, now_y);
            }
            perform_internal_bound_check_custom_grid(
                arena, now_x, now_y, before_grid_x + hor, before_grid_y + ver,
                physical);
        }
    }
}

void rr_system_velocity_tick(struct rr_simulation *simulation)
{
    rr_simulation_for_each_physical(simulation, simulation, system_velocity);
}
