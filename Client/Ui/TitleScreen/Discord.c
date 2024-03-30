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

static uint8_t discord_button_should_show(struct rr_ui_element *this,
                                          struct rr_game *game)
{
    return !game->simulation_ready;
}

static void discord_toggle_button_on_render(struct rr_ui_element *this,
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
    rr_renderer_scale(renderer, 0.1);
    rr_renderer_set_fill(renderer, 0xffffffff);
    rr_renderer_begin_path(renderer);
    rr_renderer_move_to(renderer, 88.86, -79.40);
    rr_renderer_bezier_curve_to(renderer, 72.29, -87.16, 54.57, -92.79, 36.04,
                                -96.00);
    rr_renderer_bezier_curve_to(renderer, 33.77, -91.89, 31.11, -86.35, 29.28,
                                -81.95);
    rr_renderer_bezier_curve_to(renderer, 9.58, -84.92, -9.93, -84.92, -29.26,
                                -81.95);
    rr_renderer_bezier_curve_to(renderer, -31.09, -86.35, -33.81, -91.89,
                                -36.10, -96.00);
    rr_renderer_bezier_curve_to(renderer, -54.65, -92.79, -72.39, -87.14,
                                -88.96, -79.36);
    rr_renderer_bezier_curve_to(renderer, -122.38, -28.85, -131.44, 20.40,
                                -126.91, 68.96);
    rr_renderer_bezier_curve_to(renderer, -104.74, 85.51, -83.26, 95.57, -62.14,
                                102.15);
    rr_renderer_bezier_curve_to(renderer, -56.92, 94.97, -52.27, 87.34, -48.26,
                                79.30);
    rr_renderer_bezier_curve_to(renderer, -55.90, 76.40, -63.21, 72.82, -70.11,
                                68.67);
    rr_renderer_bezier_curve_to(renderer, -68.28, 67.31, -66.49, 65.89, -64.76,
                                64.43);
    rr_renderer_bezier_curve_to(renderer, -22.63, 84.13, 23.13, 84.13, 64.75,
                                64.43);
    rr_renderer_bezier_curve_to(renderer, 66.51, 65.89, 68.30, 67.31, 70.11,
                                68.67);
    rr_renderer_bezier_curve_to(renderer, 63.18, 72.84, 55.85, 76.42, 48.22,
                                79.32);
    rr_renderer_bezier_curve_to(renderer, 52.23, 87.34, 56.86, 94.99, 62.10,
                                102.17);
    rr_renderer_bezier_curve_to(renderer, 83.24, 95.59, 104.74, 85.53, 126.91,
                                68.96);
    rr_renderer_bezier_curve_to(renderer, 132.23, 12.67, 117.83, -36.13, 88.86,
                                -79.40);
    rr_renderer_move_to(renderer, -42.53, 39.09);
    rr_renderer_bezier_curve_to(renderer, -55.17, 39.09, -65.54, 27.29, -65.54,
                                12.91);
    rr_renderer_bezier_curve_to(renderer, -65.54, -1.46, -55.39, -13.29, -42.53,
                                -13.29);
    rr_renderer_bezier_curve_to(renderer, -29.66, -13.29, -19.29, -1.48, -19.51,
                                12.91);
    rr_renderer_bezier_curve_to(renderer, -19.49, 27.29, -29.66, 39.09, -42.53,
                                39.09);
    rr_renderer_move_to(renderer, 42.53, 39.09);
    rr_renderer_bezier_curve_to(renderer, 29.88, 39.09, 19.51, 27.29, 19.51,
                                12.91);
    rr_renderer_bezier_curve_to(renderer, 19.51, -1.46, 29.66, -13.29, 42.53,
                                -13.29);
    rr_renderer_bezier_curve_to(renderer, 55.39, -13.29, 65.76, -1.48, 65.54,
                                12.91);
    rr_renderer_bezier_curve_to(renderer, 65.54, 27.29, 55.39, 39.09, 42.53,
                                39.09);
    rr_renderer_fill(renderer);
}

static void discord_toggle_button_on_event(struct rr_ui_element *this,
                                           struct rr_game *game)
{
    if (game->input_data->mouse_buttons_up_this_tick & 1)
    {
        if (game->pressed != this)
            return;
        rr_page_open("https://discord.gg/GY922fftAg");
    }
    else
        rr_ui_render_tooltip_below(this, game->discord_tooltip, game);
}

struct rr_ui_element *rr_ui_discord_toggle_button_init()
{
    struct rr_ui_element *this = rr_ui_element_init();
    rr_ui_set_background(this, 0x80888888);
    this->abs_width = this->abs_height = this->width = this->height = 40;
    this->on_event = discord_toggle_button_on_event;
    this->on_render = discord_toggle_button_on_render;
    this->should_show = discord_button_should_show;
    return this;
}