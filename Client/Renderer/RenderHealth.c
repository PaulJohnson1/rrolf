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

#include <Client/Assets/RenderFunctions.h>
#include <Client/Game.h>
#include <Client/Renderer/Renderer.h>
#include <Client/Simulation.h>
#include <Shared/StaticData.h>

void rr_component_health_render(EntityIdx entity, struct rr_game *game,
                                struct rr_simulation *simulation)
{
    struct rr_renderer *renderer = game->renderer;
    struct rr_component_physical *physical =
        rr_simulation_get_physical(simulation, entity);
    struct rr_component_health *health =
        rr_simulation_get_health(simulation, entity);
    if (health->flags & 1 || rr_simulation_has_petal(simulation, entity))
        return;
    rr_renderer_set_global_alpha(renderer, 1 - physical->deletion_animation);
    rr_renderer_scale(renderer, 1 + physical->deletion_animation * 0.5);
    if (rr_simulation_has_flower(simulation, entity))
    {
        struct rr_component_relations *relations =
            rr_simulation_get_relations(simulation, entity);

        if (relations->owner == game->player_info->parent_id)
            if (health->lerp_health / health->max_health > 0.99)
                return;
    }

    float length = 40;

    if (rr_simulation_has_mob(simulation, entity))
    {
        struct rr_component_mob *mob =
            rr_simulation_get_mob(simulation, entity);
        if (!rr_simulation_has_centipede(simulation, entity) ||
            rr_simulation_get_centipede(simulation, entity)->is_head)
        {
            length += mob->rarity * 5;
            // mob rarity
            rr_renderer_translate(renderer, length, 7);
            rr_renderer_draw_rarity_name(renderer, mob->rarity, 14, -1, 1);

            // mob name
            rr_renderer_translate(renderer, -2 * length, -14);
            rr_renderer_draw_mob_name(renderer, mob->id, 12, 1, -1);
            rr_renderer_translate(renderer, length, 7);
        }
    }
    else if (rr_simulation_has_flower(simulation, entity) &&
             physical->deletion_animation == 0)
    {
        struct rr_component_flower *flower =
            rr_simulation_get_flower(simulation, entity);
        rr_renderer_set_fill(renderer, 0xffffffff);
        rr_renderer_set_stroke(renderer, 0xff000000);
        rr_renderer_set_text_size(renderer, 12);
        rr_renderer_set_text_align(renderer, 0);
        rr_renderer_set_text_baseline(renderer, 0);
        rr_renderer_stroke_text(renderer, flower->nickname, -length, -18);
        rr_renderer_fill_text(renderer, flower->nickname, -length, -18);
        rr_renderer_set_text_align(renderer, 2);
        rr_renderer_set_text_baseline(renderer, 2);
        char out[16];
        sprintf(out, "Lvl %d", flower->level);
        rr_renderer_stroke_text(renderer, out, length, 18);
        rr_renderer_fill_text(renderer, out, length, 18);
    }
    // the health bar
    rr_renderer_set_line_cap(renderer, 1);
    rr_renderer_set_stroke(renderer, 0xff222222);
    rr_renderer_set_line_width(renderer, 10);
    rr_renderer_begin_path(renderer);
    rr_renderer_move_to(renderer, -length, 0);
    rr_renderer_line_to(renderer, length, 0);
    rr_renderer_stroke(renderer);

    rr_renderer_set_stroke(renderer, 0xff75dd34);
    rr_renderer_set_line_width(renderer, 7);
    rr_renderer_begin_path(renderer);
    rr_renderer_move_to(renderer, -length, 0);
    rr_renderer_line_to(
        renderer,
        -length + 2 * length * health->lerp_health / health->max_health, 0);
    rr_renderer_stroke(renderer);
}
