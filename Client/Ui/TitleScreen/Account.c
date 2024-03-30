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

static uint8_t account_container_should_show(struct rr_ui_element *this,
                                             struct rr_game *game)
{
    return game->menu_open == rr_game_menu_account && !game->simulation_ready;
}

static uint8_t account_button_should_show(struct rr_ui_element *this,
                                          struct rr_game *game)
{
    if (game->account_linked == 0 && !game->simulation_ready)
    {
        rr_ui_render_tooltip_right(this, game->link_reminder_tooltip, game);
    }
    return !game->simulation_ready;
}

static void account_container_animate(struct rr_ui_element *this,
                                      struct rr_game *game)
{
    this->width = this->abs_width;
    this->height = this->abs_height;
    rr_renderer_translate(
        game->renderer, -(this->x + this->abs_width / 2) * 2 * this->animation,
        0);
}

static void account_toggle_button_on_render(struct rr_ui_element *this,
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
    rr_renderer_scale(renderer, 0.025);
    rr_renderer_set_fill(renderer, 0xffffffff);
    rr_renderer_begin_path(renderer);
    rr_renderer_move_to(renderer, 211.43, -3.40);
    rr_renderer_bezier_curve_to(renderer, 157.31, 44.35, 85.45, 73.66, 6.27,
                                73.66);
    rr_renderer_bezier_curve_to(renderer, -74.10, 73.66, -147.13, 43.40,
                                -201.50, -5.76);
    rr_renderer_bezier_curve_to(renderer, -327.95, 27.33, -406.19, 140.31,
                                -406.19, 275.28);
    rr_renderer_line_to(renderer, -406.19, 344.06);
    rr_renderer_bezier_curve_to(renderer, -406.19, 505.03, 406.20, 505.03,
                                406.20, 344.06);
    rr_renderer_line_to(renderer, 406.20, 275.28);
    rr_renderer_bezier_curve_to(renderer, 406.19, 143.86, 331.98, 32.77, 211.43,
                                -3.40);
    rr_renderer_move_to(renderer, 6.27, 24.73);
    rr_renderer_bezier_curve_to(renderer, 146.43, 24.73, 260.36, -84.71, 260.36,
                                -219.91);
    rr_renderer_bezier_curve_to(renderer, 260.36, -355.11, 146.67, -464.78,
                                6.27, -464.78);
    rr_renderer_bezier_curve_to(renderer, -133.66, -464.78, -247.59, -355.11,
                                -247.59, -219.91);
    rr_renderer_bezier_curve_to(renderer, -247.59, -84.70, -133.66, 24.73, 6.27,
                                24.73);
    rr_renderer_fill(renderer);
}

static void account_toggle_button_on_event(struct rr_ui_element *this,
                                           struct rr_game *game)
{
    if (game->input_data->mouse_buttons_up_this_tick & 1)
    {
        if (game->pressed != this)
            return;
        if (game->menu_open == rr_game_menu_account)
            game->menu_open = rr_game_menu_none;
        else
            game->menu_open = rr_game_menu_account;
    }
    else
        rr_ui_render_tooltip_below(this, game->account_tooltip, game);
}

struct rr_ui_element *rr_ui_account_toggle_button_init()
{
    struct rr_ui_element *this = rr_ui_element_init();
    rr_ui_set_background(this, 0x80888888);
    this->abs_width = this->abs_height = this->width = this->height = 40;
    this->on_event = account_toggle_button_on_event;
    this->on_render = account_toggle_button_on_render;
    this->should_show = account_button_should_show;
    return this;
}

static void render_link(struct rr_ui_element *this, struct rr_game *game)
{
    struct rr_renderer *renderer = game->renderer;
    if (rr_ui_mouse_over(this, game))
        rr_renderer_add_color_filter(renderer, 0xff000000, 0.2);
    rr_renderer_scale(renderer, renderer->scale);
    rr_renderer_set_fill(renderer, 0x80888888);
    renderer->state.filter.amount += 0.2;
    rr_renderer_begin_path(renderer);
    rr_renderer_round_rect(renderer, -this->abs_width / 2,
                           -this->abs_height / 2, this->abs_width,
                           this->abs_height, 6);
    rr_renderer_fill(renderer);
    rr_renderer_scale(renderer, 0.85);
    rr_renderer_set_fill(renderer, 0xffffffff);
    rr_renderer_begin_path(renderer);
    rr_renderer_move_to(renderer, 14.60, -10.21);
    rr_renderer_line_to(renderer, 10.52, -14.24);
    rr_renderer_bezier_curve_to(renderer, 8.71, -16.02, 5.78, -16.03, 3.97,
                                -14.26);
    rr_renderer_line_to(renderer, -0.55, -9.85);
    rr_renderer_bezier_curve_to(renderer, -2.36, -8.08, -2.37, -5.20, -0.57,
                                -3.42);
    rr_renderer_line_to(renderer, 2.02, -5.91);
    rr_renderer_bezier_curve_to(renderer, 1.75, -6.70, 2.08, -7.60, 2.72,
                                -8.23);
    rr_renderer_line_to(renderer, 5.60, -11.04);
    rr_renderer_bezier_curve_to(renderer, 6.51, -11.92, 7.97, -11.92, 8.87,
                                -11.03);
    rr_renderer_line_to(renderer, 11.32, -8.61);
    rr_renderer_bezier_curve_to(renderer, 12.22, -7.72, 12.22, -6.28, 11.31,
                                -5.39);
    rr_renderer_line_to(renderer, 8.43, -2.59);
    rr_renderer_bezier_curve_to(renderer, 7.82, -1.99, 6.82, -1.67, 6.05,
                                -1.87);
    rr_renderer_line_to(renderer, 3.51, 0.61);
    rr_renderer_bezier_curve_to(renderer, 5.32, 2.39, 8.24, 2.40, 10.06, 0.63);
    rr_renderer_line_to(renderer, 14.58, -3.78);
    rr_renderer_bezier_curve_to(renderer, 16.39, -5.55, 16.40, -8.43, 14.60,
                                -10.21);
    rr_renderer_move_to(renderer, -1.97, 5.95);
    rr_renderer_bezier_curve_to(renderer, -1.76, 6.72, -2.10, 7.72, -2.72,
                                8.33);
    rr_renderer_line_to(renderer, -5.41, 10.96);
    rr_renderer_bezier_curve_to(renderer, -6.33, 11.86, -7.83, 11.85, -8.74,
                                10.94);
    rr_renderer_line_to(renderer, -11.24, 8.48);
    rr_renderer_bezier_curve_to(renderer, -12.16, 7.58, -12.15, 6.10, -11.23,
                                5.21);
    rr_renderer_line_to(renderer, -8.54, 2.58);
    rr_renderer_bezier_curve_to(renderer, -7.88, 1.94, -6.94, 1.62, -6.12,
                                1.89);
    rr_renderer_line_to(renderer, -3.52, -0.68);
    rr_renderer_bezier_curve_to(renderer, -5.36, -2.49, -8.35, -2.50, -10.19,
                                -0.70);
    rr_renderer_line_to(renderer, -14.56, 3.56);
    rr_renderer_bezier_curve_to(renderer, -16.40, 5.37, -16.41, 8.30, -14.58,
                                10.11);
    rr_renderer_line_to(renderer, -10.42, 14.22);
    rr_renderer_bezier_curve_to(renderer, -8.59, 16.03, -5.60, 16.04, -3.75,
                                14.24);
    rr_renderer_line_to(renderer, 0.61, 9.98);
    rr_renderer_bezier_curve_to(renderer, 2.45, 8.17, 2.46, 5.24, 0.63, 3.43);
    rr_renderer_line_to(renderer, -1.97, 5.95);
    rr_renderer_move_to(renderer, -4.81, 4.78);
    rr_renderer_bezier_curve_to(renderer, -4.20, 5.39, -3.20, 5.40, -2.57,
                                4.78);
    rr_renderer_line_to(renderer, 4.88, -2.63);
    rr_renderer_bezier_curve_to(renderer, 5.50, -3.25, 5.51, -4.25, 4.89,
                                -4.87);
    rr_renderer_bezier_curve_to(renderer, 4.28, -5.48, 3.28, -5.48, 2.66,
                                -4.87);
    rr_renderer_line_to(renderer, -4.80, 2.54);
    rr_renderer_bezier_curve_to(renderer, -5.42, 3.16, -5.42, 4.16, -4.81,
                                4.78);
    rr_renderer_fill(renderer);
}

static void link_rivet_account(struct rr_ui_element *this, struct rr_game *game)
{
    if (game->input_data->mouse_buttons_up_this_tick & 1)
    { // TODO: make it display a loading status and disable the click
        // funcitonality
        rr_rivet_link_account(game->rivet_account.token,
                              game->rivet_account.api_password, 0);
    }
    else if (!(game->input_data->mouse_buttons & 1))
        rr_ui_render_tooltip_right(this, game->link_account_tooltip, game);
}

static struct rr_ui_element *link_account_button_init(struct rr_game *game)
{
    struct rr_ui_element *this = rr_ui_element_init();
    this->width = this->abs_width = this->height = this->abs_height = 35;
    this->on_render = render_link;
    this->on_event = link_rivet_account;

    return this;
}

static uint8_t linked_account(struct rr_ui_element *this, struct rr_game *game)
{
    return !game->account_linked;
}

static void copy_uuid(struct rr_ui_element *this, struct rr_game *game)
{
    if (game->input_data->mouse_buttons_up_this_tick & 1)
        rr_copy_string(game->rivet_account.uuid);
}

// clang-format off
struct rr_ui_element *rr_ui_account_container_init(struct rr_game *game)
{
    struct rr_ui_element *uuid = rr_ui_text_init(game->rivet_account.uuid, 15, 0xffffffff);
    uuid->on_event = copy_uuid;
    struct rr_ui_element *this = rr_ui_pad(
        rr_ui_set_background(
            rr_ui_v_pad(
                rr_ui_set_justify(
                    rr_ui_v_container_init(
                        rr_ui_container_init(), 10, 5,
                        rr_ui_text_init("Account", 24, 0xffffffff),
                        rr_ui_static_space_init(10),
                        rr_ui_h_container_init(rr_ui_container_init(), 0, 0, 
                            rr_ui_text_init("Account Name: ", 15, 0xffffffff),
                            rr_ui_text_init(game->rivet_account.name, 15, 0xffffffff),
                            rr_ui_text_init(game->rivet_account.account_number, 15, 0xffcccccc),
                            NULL
                        ),
                        uuid,
                        rr_ui_static_space_init(10),
                        rr_ui_choose_element_init(
                            rr_ui_flex_container_init(
                                rr_ui_v_container_init(rr_ui_container_init(), 0, 5, 
                                    rr_ui_text_init("Progress on guest accounts", 15, 0xffffffff),
                                    rr_ui_text_init("will be lost after 4 months.", 15, 0xffffffff),
                                    NULL
                                ),
                                link_account_button_init(game),
                                10
                            ),
                            rr_ui_text_init("Logged in", 20, 0xffffffff),
                            linked_account
                        ),
                        NULL
                    ), -1, -1
                ), 50
            ), 0x40ffffff
        ), 10
    );
    this->animate = account_container_animate;
    this->should_show = account_container_should_show;
    return this;
}
// clang-format on
