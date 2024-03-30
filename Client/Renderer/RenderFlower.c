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

void rr_component_flower_render(EntityIdx entity, struct rr_game *game,
                                struct rr_simulation *simulation)
{
    struct rr_renderer *renderer = game->renderer;
    struct rr_component_physical *physical =
        rr_simulation_get_physical(simulation, entity);
    struct rr_component_flower *flower =
        rr_simulation_get_flower(simulation, entity);
    rr_renderer_add_color_filter(
        renderer, 0xffff0000,
        0.5 * rr_simulation_get_health(simulation, entity)->damage_animation);
    rr_renderer_set_global_alpha(renderer, 1 - physical->deletion_animation);
    rr_renderer_scale(renderer, 1 + physical->deletion_animation * 0.5);
    rr_renderer_set_stroke(renderer, 0xffcfbb50);
    rr_renderer_set_fill(renderer, 0xffffe763);
    rr_renderer_rotate(renderer, physical->lerp_angle);
    rr_renderer_set_line_width(renderer, 3);
    rr_renderer_begin_path(renderer);
    rr_renderer_arc(renderer, 0, 0, physical->radius);
    rr_renderer_fill(renderer);
    rr_renderer_stroke(renderer);
    rr_renderer_scale(renderer, physical->radius / 25);
    struct rr_renderer_context_state state;
    rr_renderer_context_state_init(renderer, &state);
    rr_renderer_set_fill(renderer, 0xff222222);
    rr_renderer_begin_path(renderer);
    rr_renderer_ellipse(renderer, -7, -5, 3.25, 6.5);
    rr_renderer_fill(renderer);
    rr_renderer_begin_path(renderer);
    rr_renderer_ellipse(renderer, 7, -5, 3.25, 6.5);
    rr_renderer_fill(renderer);
    rr_renderer_begin_path(renderer);
    rr_renderer_ellipse(renderer, -7, -5, 3, 6);
    rr_renderer_ellipse(renderer, 7, -5, 3, 6);
    rr_renderer_clip(renderer);
    rr_renderer_set_fill(renderer, 0xffffffff);
    rr_renderer_begin_path(renderer);
    rr_renderer_arc(renderer, -7 + flower->lerp_eye_x, -5 + flower->lerp_eye_y,
                    3);
    rr_renderer_fill(renderer);
    rr_renderer_begin_path(renderer);
    rr_renderer_arc(renderer, 7 + flower->lerp_eye_x, -5 + flower->lerp_eye_y,
                    3);
    rr_renderer_fill(renderer);
    rr_renderer_context_state_free(renderer, &state);
    rr_renderer_set_stroke(renderer, 0xff222222);
    rr_renderer_set_line_width(renderer, 1.5);
    rr_renderer_set_line_cap(renderer, 1);
    rr_renderer_begin_path(renderer);
    rr_renderer_move_to(renderer, -6, 10);
    rr_renderer_quadratic_curve_to(renderer, 0, flower->lerp_mouth, 6, 10);
    rr_renderer_stroke(renderer);
    rr_renderer_set_fill(renderer, 0xffffe763);
    if (flower->lerp_mouth <= 8)
    {
        rr_renderer_context_state_init(renderer, &state);
        rr_renderer_translate(renderer, 0, -flower->lerp_mouth - 7.8);
        rr_renderer_begin_path(renderer);
        rr_renderer_move_to(renderer, -12, 0);
        rr_renderer_line_to(renderer, 12, 0);
        rr_renderer_line_to(renderer, 0, 6);
        rr_renderer_line_to(renderer, -12, 0);
        rr_renderer_fill(renderer);
        rr_renderer_context_state_free(renderer, &state);
    }
    if (flower->face_flags & 8)
    {
        rr_renderer_translate(renderer, 0, -36);
        rr_renderer_draw_petal(renderer, rr_petal_id_crest, 1);
        rr_renderer_translate(renderer, 0, 36);
    }
    if (flower->face_flags & 16)
    {
        rr_renderer_translate(renderer, 0, -15);
        rr_renderer_scale(renderer, 0.625);
        rr_renderer_draw_petal(renderer, rr_petal_id_third_eye, 1);
        rr_renderer_scale(renderer, 1.6);
        rr_renderer_translate(renderer, 0, 15);
    }
    rr_renderer_rotate(renderer, -physical->lerp_angle);
}
