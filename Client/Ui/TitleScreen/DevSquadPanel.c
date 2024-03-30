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

#include <Shared/Utilities.h>
#include <Shared/pb.h>

static uint8_t dev_squad_panel_container_should_show(struct rr_ui_element *this,
                                                     struct rr_game *game)
{
    return game->is_dev && game->menu_open == rr_game_menu_dev_squad_panel;
}

static uint8_t dev_squad_panel_button_should_show(struct rr_ui_element *this,
                                                  struct rr_game *game)
{
    return game->is_dev;
}

static void dev_squad_panel_container_animate(struct rr_ui_element *this,
                                              struct rr_game *game)
{
    this->width = this->abs_width;
    this->height = this->abs_height;
    rr_renderer_translate(
        game->renderer, -(this->x + this->abs_width / 2) * 2 * this->animation,
        0);
}

static void dev_squad_panel_toggle_button_on_render(struct rr_ui_element *this,
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

static void dev_squad_panel_toggle_button_on_event(struct rr_ui_element *this,
                                                   struct rr_game *game)
{
    if (game->input_data->mouse_buttons_up_this_tick & 1)
    {
        if (game->pressed != this)
            return;
        if (game->menu_open == rr_game_menu_dev_squad_panel)
            game->menu_open = rr_game_menu_none;
        else
            game->menu_open = rr_game_menu_dev_squad_panel;
    }
}

struct rr_ui_element *rr_ui_dev_panel_toggle_button_init()
{
    struct rr_ui_element *this = rr_ui_element_init();
    rr_ui_set_background(this, 0x80888888);
    this->abs_width = this->abs_height = this->width = this->height = 40;
    this->should_show = dev_squad_panel_button_should_show;
    this->on_event = dev_squad_panel_toggle_button_on_event;
    this->on_render = dev_squad_panel_toggle_button_on_render;
    return this;
}

static void summon_edmonto(struct rr_ui_element *this, struct rr_game *game)
{
    if (!(game->input_data->mouse_buttons_up_this_tick & 1))
        return;
    puts("edmonto summon");
    struct proto_bug encoder;
    proto_bug_init(&encoder, RR_OUTGOING_PACKET);
    proto_bug_write_uint8(&encoder, rr_serverbound_dev_summon, "header");
    proto_bug_write_uint8(&encoder, rand() % rr_mob_id_ant, "id");
    proto_bug_write_uint8(&encoder, rr_rarity_id_ultimate, "rarity");

    rr_websocket_send(&game->socket, encoder.current - encoder.start);
}

static struct rr_ui_element *summon_mob_button_init()
{
    struct rr_ui_element *element = rr_ui_labeled_button_init("Summon", 20, 0);
    element->fill = 0x80ffffff;
    element->on_event = summon_edmonto;
    element->animate = rr_ui_default_animate;

    return element;
}

static struct rr_ui_element *speed_slider_init(struct rr_game *game)
{
    struct rr_ui_element *element =
        rr_ui_h_slider_init(100, 20, &game->developer_cheats.speed_percent, 1);
    game->developer_cheats.speed_percent = 0.05;

    return element;
}

struct rr_ui_element *rr_ui_dev_panel_container_init(struct rr_game *game)
{
    struct rr_ui_element *inner = rr_ui_v_container_init(
        rr_ui_container_init(), 10, 10, summon_mob_button_init(),
        rr_ui_set_justify(
            rr_ui_h_container_init(rr_ui_container_init(), 0, 10,
                                   rr_ui_text_init("Speed:", 20, 0xffffffff),
                                   speed_slider_init(game), NULL),
            -1, -1),
        NULL);
    for (uint32_t i = 0; i < RR_SQUAD_COUNT; ++i)
        rr_ui_container_add_element(
            inner, rr_ui_squad_container_init(&game->other_squads[i]));
    struct rr_ui_element *this =
        // clang-format off
    rr_ui_pad(
        rr_ui_set_background(
            rr_ui_v_pad(
                rr_ui_set_justify(
                    rr_ui_scroll_container_init(
                        rr_ui_set_background(
                            inner
                        , 0x40ffffff)
                    , 400),
                    -1, -1),
                50),
            0x40ffffff),
        10);
    // clang-format on
    this->animate = dev_squad_panel_container_animate;
    this->should_show = dev_squad_panel_container_should_show;
    return this;
}
