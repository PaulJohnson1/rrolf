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

#include <Client/Renderer/ComponentRender.h>

#include <math.h>

#include <Client/Assets/RenderFunctions.h>
#include <Client/Game.h>
#include <Client/InputData.h>
#include <Client/Renderer/Renderer.h>
#include <Client/Simulation.h>
#include <Shared/Crypto.h>

void render_background(struct rr_component_player_info *player_info,
                       struct rr_game *this)
{
    if (player_info->arena == 0)
        return;
    struct rr_renderer *renderer = this->renderer;
    double scale = player_info->lerp_camera_fov * renderer->scale;
    double leftX = player_info->lerp_camera_x - renderer->width / (2 * scale);
    double rightX = player_info->lerp_camera_x + renderer->width / (2 * scale);
    double topY = player_info->lerp_camera_y - renderer->height / (2 * scale);
    double bottomY =
        player_info->lerp_camera_y + renderer->height / (2 * scale);

#define GRID_SIZE (512.0f)
    double newLeftX = floorf(leftX / GRID_SIZE) * GRID_SIZE;
    double newTopY = floorf(topY / GRID_SIZE) * GRID_SIZE;
    // rr_renderer_scale(renderer, scale);
    for (; newLeftX < rightX; newLeftX += GRID_SIZE)
    {
        for (double currY = newTopY; currY < bottomY; currY += GRID_SIZE)
        {
            uint32_t tile_index =
                rr_get_hash((uint32_t)(((newLeftX + 8192) / GRID_SIZE + 1) *
                                       ((currY + 8192) / GRID_SIZE + 2))) %
                3;
            struct rr_renderer_context_state state;
            rr_renderer_context_state_init(renderer, &state);
            rr_renderer_translate(renderer, newLeftX + GRID_SIZE / 2,
                                  currY + GRID_SIZE / 2);
            rr_renderer_scale(renderer, (GRID_SIZE + 2) / 256);
            if (this->selected_biome == 0)
                rr_renderer_draw_tile_hell_creek(renderer, tile_index);
            else
                rr_renderer_draw_tile_garden(renderer, tile_index);
            rr_renderer_context_state_free(renderer, &state);
        }
    }

#undef GRID_SIZE
    struct rr_component_arena *arena =
        rr_simulation_get_arena(this->simulation, player_info->arena);
    float grid_size = RR_MAZES[arena->biome].grid_size;
    uint32_t maze_dim = RR_MAZES[arena->biome].maze_dim;
    struct rr_maze_grid *grid = RR_MAZES[arena->biome].maze;
    rr_renderer_set_fill(renderer, 0xff000000);
    rr_renderer_set_global_alpha(renderer, 0.5f);
    int32_t nx = floorf(leftX / grid_size);
    int32_t ny = floorf(topY / grid_size);
    for (; nx < rightX / grid_size; ++nx)
        for (int32_t currY = ny; currY < bottomY / grid_size; ++currY)
        {
            rr_renderer_set_fill(renderer, 0xff000000);
            uint8_t tile =
                (nx < 0 || currY < 0 || nx >= maze_dim || currY >= maze_dim)
                    ? 0
                    : grid[currY * maze_dim + nx].value;
            if (tile != 1)
            {
                rr_renderer_begin_path(renderer);
                if (tile == 0)
                    rr_renderer_fill_rect(renderer, nx * grid_size,
                                          currY * grid_size, grid_size,
                                          grid_size);
                else
                {
                    uint8_t left = (tile >> 1) & 1;
                    uint8_t top = tile & 1;
                    uint8_t inverse = 1 - ((tile >> 3) & 1);
                    rr_renderer_move_to(renderer,
                                        (nx + inverse ^ left) * grid_size,
                                        (currY + inverse ^ top) * grid_size);
                    float start_angle = 0;
                    if (top == 0 && left == 1)
                        start_angle = M_PI / 2;
                    else if (top == 1 && left == 1)
                        start_angle = M_PI;
                    else if (top == 1 && left == 0)
                        start_angle = M_PI * 3 / 2;
                    rr_renderer_partial_arc(renderer, (nx + left) * grid_size,
                                            (currY + top) * grid_size,
                                            grid_size, start_angle,
                                            start_angle + M_PI / 2, 0);
                    rr_renderer_fill(renderer);
                }
            }
        }
}

void rr_component_arena_render(EntityIdx entity, struct rr_game *this,
                               struct rr_simulation *simulation)
{
    struct rr_renderer_context_state state2;
    struct rr_component_player_info *player_info = this->player_info;

    struct rr_component_arena *arena =
        rr_simulation_get_arena(this->simulation, player_info->arena);
    rr_renderer_context_state_init(this->renderer, &state2);
    render_background(player_info, this);

    rr_renderer_context_state_free(this->renderer, &state2);
}