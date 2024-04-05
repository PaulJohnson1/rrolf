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

#include <Client/Ui/Ui.h>

#include <stdio.h>
#include <stdlib.h>
#include <string.h>

#include <Client/DOM.h>
#include <Client/Game.h>
#include <Client/InputData.h>
#include <Client/Renderer/Renderer.h>
#include <Client/Ui/Engine.h>

#include <Shared/Utilities.h>

static uint8_t github_button_should_show(struct rr_ui_element *this,
                                          struct rr_game *game)
{
    return !game->simulation_ready;
}

static void github_toggle_button_on_render(struct rr_ui_element *this,
                                            struct rr_game *game)
{
    struct rr_renderer *renderer = game->renderer;
    if (game->focused == this)
        renderer->state.filter.amount = 0.2;
    rr_renderer_scale(renderer, renderer->scale);
    rr_renderer_set_fill(renderer, this->fill);
    renderer->state.filter.amount += 0.2;
    rr_renderer_begin_path(renderer);
    rr_renderer_round_rect(renderer, -this->abs_width / 2,
                           -this->abs_height / 2, this->abs_width,
                           this->abs_height, 6);
    rr_renderer_fill(renderer);
    rr_renderer_scale(renderer, 0.9);
    rr_renderer_translate(renderer, -16, -16);
    rr_renderer_set_fill(renderer, 0xffffffff);
    rr_renderer_begin_path(renderer);
    rr_renderer_move_to(renderer, 16, 0);
    rr_renderer_bezier_curve_to(renderer, 7.16, 0, 0, 7.16, 0,
                                16);
    rr_renderer_bezier_curve_to(renderer, 0, 23.08, 4.58, 29.06, 10.94,
                                31.18);
    rr_renderer_bezier_curve_to(renderer, 11.74, 31.32, 12.04, 30.84, 12.04,
                                30.42);
    rr_renderer_bezier_curve_to(renderer, 12.04, 30.04, 12.02, 28.78, 12.02,
                                27.44);
    rr_renderer_bezier_curve_to(renderer, 8, 28.18, 6.96, 26.46, 6.64,
                                25.56);
    rr_renderer_bezier_curve_to(renderer, 6.46, 25.1, 5.68, 23.68, 5,
                                23.3);
    rr_renderer_bezier_curve_to(renderer, 4.44, 23, 3.64, 22.26, 4.98,
                                22.24);
    rr_renderer_bezier_curve_to(renderer, 6.24, 22.22, 7.14, 23.4, 7.44,
                                23.88);
    rr_renderer_bezier_curve_to(renderer, 8.88, 26.3, 11.18, 25.62, 12.1,
                                25.2);
    rr_renderer_bezier_curve_to(renderer, 12.24, 24.16, 12.66, 23.46, 13.12,
                                23.06);
    rr_renderer_bezier_curve_to(renderer, 9.56, 22.66, 5.84, 21.28, 5.84,
                                15.16);
    rr_renderer_bezier_curve_to(renderer, 5.84, 13.42, 6.46, 11.98, 7.48,
                                10.86);
    rr_renderer_bezier_curve_to(renderer, 7.32, 10.46, 6.76, 8.82, 7.64,
                                6.62);
    rr_renderer_bezier_curve_to(renderer, 7.64, 6.62, 8.98, 6.2, 12.04,
                                8.26);
    rr_renderer_bezier_curve_to(renderer, 13.32, 7.9, 14.68, 7.72, 16.04,
                                7.72);
    rr_renderer_bezier_curve_to(renderer, 17.4, 7.72, 18.76, 7.9, 20.04,
                                8.26);
    rr_renderer_bezier_curve_to(renderer, 23.1, 6.18, 24.44, 6.62, 24.44,
                                6.62);
    rr_renderer_bezier_curve_to(renderer, 25.32, 8.82, 24.76, 10.46, 24.6,
                                10.86);
    rr_renderer_bezier_curve_to(renderer, 25.62, 11.98, 26.24, 13.4, 26.24,
                                15.16);
    rr_renderer_bezier_curve_to(renderer, 26.24, 21.3, 22.5, 22.66, 18.94,
                                23.06);
    rr_renderer_bezier_curve_to(renderer, 19.52, 23.56, 20.02, 24.52, 20.02,
                                26.02);
    rr_renderer_bezier_curve_to(renderer, 20.02, 28.16, 20, 29.88, 20,
                                30.42);
    rr_renderer_bezier_curve_to(renderer, 20, 30.84, 20.3, 31.34, 21.1,
                                31.18);
    rr_renderer_bezier_curve_to(renderer, 27.42, 29.06, 32, 23.06, 32,
                                16);
    rr_renderer_bezier_curve_to(renderer, 32, 7.16, 24.84, 0, 16,
                                0);
    rr_renderer_fill(renderer);
}

static void github_toggle_button_on_event(struct rr_ui_element *this,
                                           struct rr_game *game)
{
    if (game->input_data->mouse_buttons_up_this_tick & 1)
    {
        if (game->pressed != this)
            return;
        rr_page_open("https://github.com/maxnest0x0/rysteria");
    }
    else
        rr_ui_render_tooltip_below(this, game->github_tooltip, game);
}

struct rr_ui_element *rr_ui_github_toggle_button_init()
{
    struct rr_ui_element *this = rr_ui_element_init();
    rr_ui_set_background(this, 0x80888888);
    this->abs_width = this->abs_height = this->width = this->height = 40;
    this->on_event = github_toggle_button_on_event;
    this->on_render = github_toggle_button_on_render;
    this->should_show = github_button_should_show;
    return this;
}
