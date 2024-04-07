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
#include <Client/Renderer/Renderer.h>
#include <Client/Simulation.h>

void rr_component_drop_render(EntityIdx entity, struct rr_game *game,
                              struct rr_simulation *simulation)
{
    struct rr_renderer *renderer = game->renderer;
    struct rr_component_physical *physical =
        rr_simulation_get_physical(simulation, entity);
    struct rr_component_drop *drop = rr_simulation_get_drop(simulation, entity);
    if (game->cache.low_performance_mode)
    {
        uint8_t significant_rarity = 0;
        uint8_t petal_count = 0;
        for (uint8_t rarity = 0; rarity < rr_rarity_id_max; ++rarity)
            for (uint8_t id = 1; id < rr_petal_id_max; ++id)
            {
                petal_count += game->inventory[id][rarity];
                if (petal_count >= game->slots_unlocked)
                {
                    significant_rarity = rarity;
                    petal_count = 0;
                    break;
                }
            }

        uint8_t min_rarity = significant_rarity >= 2 ? significant_rarity - 2 : 0;
        if (drop->rarity < min_rarity)
            return;
    }
    if (physical->deletion_type == 2)
    {
        struct rr_component_player_info *player_info = game->player_info;
        rr_renderer_translate(renderer,
                              (player_info->lerp_camera_x - physical->lerp_x) *
                                  physical->deletion_animation,
                              (player_info->lerp_camera_y - physical->lerp_y) *
                                  physical->deletion_animation);
    }
    rr_renderer_rotate(renderer,
                       physical->lerp_angle + physical->lerp_radius * 0.3125);
    rr_renderer_scale(renderer, 1 - physical->deletion_animation);
    rr_renderer_scale(renderer, physical->lerp_radius * 0.04);
    rr_renderer_scale(renderer,
                      1 + sinf(physical->animation_timer * 0.1) * 0.05);
    rr_renderer_draw_background(renderer, drop->rarity, 1);
    rr_renderer_draw_petal_with_name(renderer, drop->id, drop->rarity);
    // rr_renderer_render_static_petal(renderer, drop->id, drop->rarity);
}