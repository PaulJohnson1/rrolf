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

#include <Client/Game.h>
#include <Client/InputData.h>
#include <Client/Renderer/Renderer.h>
#include <Client/Ui/Engine.h>

#include <Shared/Rivet.h>
#include <Shared/Utilities.h>

char const *regions[3] = {"Closest", "Atlanta", "Frankfurt"};

uint8_t selected = 0;

static void region_button_on_event(struct rr_ui_element *this,
                                   struct rr_game *game)
{
    if (game->input_data->mouse_buttons_up_this_tick & 1)
    {
        selected = (selected + 1) % 3;
    }
}

static void region_button_on_render(struct rr_ui_element *this,
                                    struct rr_game *game)
{
    struct rr_renderer *renderer = game->renderer;
    if (rr_ui_mouse_over(this, game))
        rr_renderer_add_color_filter(renderer, 0xff000000, 0.2);

    rr_renderer_scale(renderer, renderer->scale);
    rr_renderer_set_fill(renderer, 0x80555555);
    rr_renderer_begin_path(renderer);
    rr_renderer_round_rect(renderer, -this->abs_width / 2,
                           -this->abs_height / 2, this->abs_width,
                           this->abs_height, 6);
    rr_renderer_fill(renderer);
    rr_renderer_set_text_baseline(renderer, 1);
    rr_renderer_set_text_align(renderer, 1);
    renderer->state.filter.amount = 0;
    rr_renderer_set_fill(renderer, 0xffffffff);
    rr_renderer_set_stroke(renderer, 0xff222222);
    rr_renderer_set_text_size(renderer, this->abs_height / 2);
    rr_renderer_set_line_width(renderer, this->abs_height / 2 * 0.12);
    rr_renderer_begin_path(renderer);
    rr_renderer_stroke_text(renderer, regions[selected], 0, 0);
    rr_renderer_fill_text(renderer, regions[selected], 0, 0);
}

static struct rr_ui_element *region_toggle_button_init()
{
    struct rr_ui_element *this = rr_ui_element_init();
    this->abs_width = this->width = 70;
    this->abs_height = this->height = 25;
    this->on_render = region_button_on_render;
    this->on_event = region_button_on_event;
    return this;
}

static void region_join_button_on_event(struct rr_ui_element *this,
                                        struct rr_game *game)
{
    if (game->socket_pending)
        return;
    if (game->input_data->mouse_buttons_up_this_tick & 1)
    {
#ifdef RIVET_BUILD
        game->socket_pending = 1;
        switch (selected)
        {
        case 0:
            rr_rivet_lobbies_find(game, NULL);
            break;
        case 1:
            rr_rivet_lobbies_find(game, "lnd-atl");
            break;
        case 2:
            rr_rivet_lobbies_find(game, "lnd-fra");
            break;
        }
#endif
    }
}

static void region_join_button_on_render(struct rr_ui_element *this,
                                         struct rr_game *game)
{
    struct rr_renderer *renderer = game->renderer;
    if (rr_ui_mouse_over(this, game))
        rr_renderer_add_color_filter(renderer, 0xff000000, 0.2);

    rr_renderer_scale(renderer, renderer->scale);
    rr_renderer_set_fill(renderer, 0x80555555);
    rr_renderer_begin_path(renderer);
    rr_renderer_round_rect(renderer, -this->abs_width / 2,
                           -this->abs_height / 2, this->abs_width,
                           this->abs_height, 6);
    rr_renderer_fill(renderer);
    rr_renderer_set_text_baseline(renderer, 1);
    rr_renderer_set_text_align(renderer, 1);
    renderer->state.filter.amount = 0;
    rr_renderer_set_fill(renderer, 0xffffffff);
    rr_renderer_set_stroke(renderer, 0xff222222);
    rr_renderer_set_text_size(renderer, this->abs_height / 2);
    rr_renderer_set_line_width(renderer, this->abs_height / 2 * 0.12);
    rr_renderer_begin_path(renderer);
    rr_renderer_stroke_text(renderer, "Join", 0, 0);
    rr_renderer_fill_text(renderer, "Join", 0, 0);
}

static struct rr_ui_element *region_join_button_init()
{
    struct rr_ui_element *this = rr_ui_element_init();
    this->abs_width = this->width = 50;
    this->abs_height = this->height = 25;
    this->on_render = region_join_button_on_render;
    this->on_event = region_join_button_on_event;
    return this;
}

static uint8_t settings_container_should_show(struct rr_ui_element *this,
                                              struct rr_game *game)
{
    return game->menu_open == rr_game_menu_settings;
}

static void settings_container_animate(struct rr_ui_element *this,
                                       struct rr_game *game)
{
    this->width = this->abs_width;
    this->height = this->abs_height;
    rr_renderer_translate(
        game->renderer, -(this->x + this->abs_width / 2) * 2 * this->animation,
        0);
}

static void settings_toggle_button_on_render(struct rr_ui_element *this,
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
    rr_renderer_scale(renderer, 1.2);
    rr_renderer_set_fill(renderer, 0xffffffff);
    rr_renderer_begin_path(renderer);
    rr_renderer_move_to(renderer, 12.00, 1.62);
    rr_renderer_line_to(renderer, 12.00, -1.62);
    rr_renderer_bezier_curve_to(renderer, 10.35, -2.20, 9.31, -2.37, 8.78,
                                -3.64);
    rr_renderer_bezier_curve_to(renderer, 8.25, -4.91, 8.88, -5.77, 9.63,
                                -7.34);
    rr_renderer_line_to(renderer, 7.34, -9.63);
    rr_renderer_bezier_curve_to(renderer, 5.78, -8.89, 4.91, -8.25, 3.64,
                                -8.78);
    rr_renderer_bezier_curve_to(renderer, 2.37, -9.31, 2.20, -10.36, 1.62,
                                -12.00);
    rr_renderer_line_to(renderer, -1.62, -12.00);
    rr_renderer_bezier_curve_to(renderer, -2.20, -10.37, -2.37, -9.31, -3.64,
                                -8.78);
    rr_renderer_bezier_curve_to(renderer, -4.91, -8.25, -5.77, -8.88, -7.34,
                                -9.63);
    rr_renderer_line_to(renderer, -9.63, -7.34);
    rr_renderer_bezier_curve_to(renderer, -8.88, -5.78, -8.25, -4.91, -8.78,
                                -3.64);
    rr_renderer_bezier_curve_to(renderer, -9.31, -2.37, -10.37, -2.20, -12.00,
                                -1.62);
    rr_renderer_line_to(renderer, -12.00, 1.62);
    rr_renderer_bezier_curve_to(renderer, -10.37, 2.20, -9.31, 2.37, -8.78,
                                3.64);
    rr_renderer_bezier_curve_to(renderer, -8.25, 4.92, -8.90, 5.80, -9.63,
                                7.34);
    rr_renderer_line_to(renderer, -7.34, 9.63);
    rr_renderer_bezier_curve_to(renderer, -5.78, 8.88, -4.91, 8.25, -3.64,
                                8.78);
    rr_renderer_bezier_curve_to(renderer, -2.37, 9.31, -2.20, 10.36, -1.62,
                                12.00);
    rr_renderer_line_to(renderer, 1.62, 12.00);
    rr_renderer_bezier_curve_to(renderer, 2.20, 10.36, 2.37, 9.31, 3.64, 8.78);
    rr_renderer_bezier_curve_to(renderer, 4.91, 8.25, 5.76, 8.88, 7.34, 9.63);
    rr_renderer_line_to(renderer, 9.63, 7.34);
    rr_renderer_bezier_curve_to(renderer, 8.88, 5.78, 8.25, 4.91, 8.78, 3.64);
    rr_renderer_bezier_curve_to(renderer, 9.31, 2.37, 10.37, 2.20, 12.00, 1.62);
    rr_renderer_arc(renderer, 0, 0, 4);
    rr_renderer_fill(renderer);
}

static void settings_toggle_button_on_event(struct rr_ui_element *this,
                                            struct rr_game *game)
{
    if (game->input_data->mouse_buttons_up_this_tick & 1)
    {
        if (game->pressed != this)
            return;
        if (game->menu_open == rr_game_menu_settings)
            game->menu_open = rr_game_menu_none;
        else
            game->menu_open = rr_game_menu_settings;
    }
    else
        rr_ui_render_tooltip_below(this, game->settings_tooltip, game);
}

struct rr_ui_element *rr_ui_settings_toggle_button_init()
{
    struct rr_ui_element *this = rr_ui_element_init();
    rr_ui_set_background(this, 0x80888888);
    this->abs_width = this->abs_height = this->width = this->height = 40;
    this->on_event = settings_toggle_button_on_event;
    this->on_render = settings_toggle_button_on_render;
    return this;
}

struct rr_ui_element *rr_ui_settings_container_init(struct rr_game *game)
{
    struct rr_ui_element *this = rr_ui_pad(
        rr_ui_set_background(
            rr_ui_v_pad(
                rr_ui_set_justify(
                    rr_ui_v_container_init(
                        rr_ui_container_init(), 10, 10,
                        rr_ui_text_init("Settings", 24, 0xffffffff),
                        rr_ui_set_justify(
                            rr_ui_h_container_init(
                                rr_ui_container_init(), 5, 5,
                                rr_ui_text_init("Region:", 15, 0xffffffff),
                                region_toggle_button_init(),
                                region_join_button_init(), NULL),
                            -1, -1),
                        rr_ui_set_justify(
                            rr_ui_h_container_init(
                                rr_ui_container_init(), 5, 10,
                                rr_ui_toggle_box_init(&game->cache.use_mouse),
                                rr_ui_text_init("Mouse movement", 15,
                                                0xffffffff),
                                NULL),
                            -1, -1),
                        rr_ui_set_justify(
                            rr_ui_h_container_init(
                                rr_ui_container_init(), 5, 10,
                                rr_ui_toggle_box_init(
                                    &game->cache.screen_shake),
                                rr_ui_text_init("Screen shake", 15, 0xffffffff),
                                NULL),
                            -1, -1),
                        rr_ui_set_justify(
                            rr_ui_h_container_init(
                                rr_ui_container_init(), 5, 10,
                                rr_ui_toggle_box_init(
                                    &game->cache.displaying_debug_information),
                                rr_ui_text_init("Show debug info", 15,
                                                0xffffffff),
                                NULL),
                            -1, -1),
                        rr_ui_set_justify(
                            rr_ui_h_container_init(
                                rr_ui_container_init(), 5, 10,
                                rr_ui_toggle_box_init(&game->cache.tint_petals),
                                rr_ui_text_init("Tint petals", 15, 0xffffffff),
                                NULL),
                            -1, -1),
                        rr_ui_set_justify(
                            rr_ui_h_container_init(
                                rr_ui_container_init(), 5, 10,
                                rr_ui_toggle_box_init(
                                    &game->cache.low_performance_mode),
                                rr_ui_text_init("Low performance mode", 15,
                                                0xffffffff),
                                NULL),
                            -1, -1),
                        NULL),
                    -1, -1),
                50),
            0x40ffffff),
        10);
    this->animate = settings_container_animate;
    this->should_show = settings_container_should_show;
    return this;
}