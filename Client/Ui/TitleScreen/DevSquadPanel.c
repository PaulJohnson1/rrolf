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
    if (game->menu_open != rr_game_menu_dev_squad_panel ||
        (game->cache.hide_ui && game->simulation_ready))
        return 0;
    if (game->is_dev)
        return 1;
    for (uint32_t i = 0; i < RR_SQUAD_COUNT; ++i)
        for (uint32_t j = 0; j < RR_SQUAD_MEMBER_COUNT; ++j)
            if (game->other_squads[i].squad_members[j].in_use)
                return 1;
    return 0;
}

static uint8_t dev_squad_panel_button_should_show(struct rr_ui_element *this,
                                                  struct rr_game *game)
{
    return 1;
}

static uint8_t dev_tools_should_show(struct rr_ui_element *this, struct rr_game *game)
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
    rr_renderer_scale(renderer, 0.15);
    rr_renderer_translate(renderer, -100.00, -84.00);
    rr_renderer_set_fill(renderer, 0xffffffff);
    rr_renderer_begin_path(renderer);
    rr_renderer_move_to(renderer, 40.77, 1.58);
    rr_renderer_bezier_curve_to(renderer, 12.74, 11.58, 16.20, 51.19, 45.64, 57.32);
    rr_renderer_bezier_curve_to(renderer, 56.48, 59.58, 71.85, 50.99, 76.38, 40.14);
    rr_renderer_bezier_curve_to(renderer, 85.72, 17.79, 63.32, -6.47, 40.77, 1.58);
    rr_renderer_move_to(renderer, 137.04, 3.80);
    rr_renderer_bezier_curve_to(renderer, 113.70, 16.07, 117.62, 49.75, 143.19, 56.64);
    rr_renderer_bezier_curve_to(renderer, 155.32, 59.91, 169.86, 53.40, 175.24, 42.30);
    rr_renderer_bezier_curve_to(renderer, 187.77, 16.42, 162.15, -9.40, 137.04, 3.80);
    rr_renderer_move_to(renderer, 90.00, 42.00);
    rr_renderer_bezier_curve_to(renderer, 82.08, 44.80, 74.50, 53.07, 72.28, 61.35);
    rr_renderer_bezier_curve_to(renderer, 64.68, 89.55, 99.54, 109.74, 120.18, 89.10);
    rr_renderer_bezier_curve_to(renderer, 142.02, 67.26, 119.21, 31.67, 90.00, 42.00);
    rr_renderer_move_to(renderer, 18.25, 62.37);
    rr_renderer_bezier_curve_to(renderer, 5.77, 73.64, 0.00, 87.98, 0.00, 107.72);
    rr_renderer_bezier_curve_to(renderer, 0.00, 122.18, 4.60, 124.72, 37.13, 128.17);
    rr_renderer_line_to(renderer, 45.80, 129.09);
    rr_renderer_line_to(renderer, 48.17, 122.14);
    rr_renderer_bezier_curve_to(renderer, 51.42, 112.60, 58.89, 102.16, 66.64, 96.32);
    rr_renderer_line_to(renderer, 73.10, 91.44);
    rr_renderer_line_to(renderer, 69.52, 84.20);
    rr_renderer_bezier_curve_to(renderer, 67.06, 79.24, 65.93, 74.26, 65.93, 68.40);
    rr_renderer_bezier_curve_to(renderer, 65.93, 59.92, 65.90, 59.86, 62.10, 61.30);
    rr_renderer_bezier_curve_to(renderer, 55.37, 63.86, 41.17, 63.03, 34.62, 59.69);
    rr_renderer_bezier_curve_to(renderer, 26.52, 55.56, 25.62, 55.71, 18.25, 62.37);
    rr_renderer_move_to(renderer, 164.62, 59.87);
    rr_renderer_bezier_curve_to(renderer, 158.74, 63.02, 144.46, 63.80, 137.95, 61.32);
    rr_renderer_bezier_curve_to(renderer, 134.18, 59.89, 134.15, 59.94, 134.15, 68.97);
    rr_renderer_bezier_curve_to(renderer, 134.15, 75.72, 133.20, 79.78, 130.45, 84.69);
    rr_renderer_line_to(renderer, 126.75, 91.32);
    rr_renderer_line_to(renderer, 132.55, 95.45);
    rr_renderer_bezier_curve_to(renderer, 140.10, 100.83, 148.51, 112.38, 151.67, 121.74);
    rr_renderer_line_to(renderer, 154.18, 129.18);
    rr_renderer_line_to(renderer, 163.63, 128.18);
    rr_renderer_bezier_curve_to(renderer, 195.66, 124.79, 200.00, 122.24, 200.00, 106.79);
    rr_renderer_bezier_curve_to(renderer, 200.00, 76.28, 181.00, 51.09, 164.62, 59.87);
    rr_renderer_move_to(renderer, 71.14, 99.77);
    rr_renderer_bezier_curve_to(renderer, 57.59, 109.76, 51.86, 122.06, 51.07, 142.90);
    rr_renderer_line_to(renderer, 50.45, 159.18);
    rr_renderer_line_to(renderer, 55.78, 161.71);
    rr_renderer_bezier_curve_to(renderer, 74.25, 170.48, 125.66, 170.52, 144.06, 161.79);
    rr_renderer_line_to(renderer, 149.23, 159.34);
    rr_renderer_line_to(renderer, 149.23, 145.72);
    rr_renderer_bezier_curve_to(renderer, 149.23, 124.79, 142.76, 109.99, 129.28, 100.08);
    rr_renderer_line_to(renderer, 123.10, 95.53);
    rr_renderer_line_to(renderer, 115.49, 99.30);
    rr_renderer_bezier_curve_to(renderer, 105.43, 104.27, 94.52, 104.25, 84.38, 99.23);
    rr_renderer_line_to(renderer, 76.90, 95.53);
    rr_renderer_line_to(renderer, 71.14, 99.77);
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
    rr_ui_render_tooltip_below(this, game->squads_tooltip, game);
    game->cursor = rr_game_cursor_pointer;
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
    if (game->input_data->mouse_buttons_up_this_tick & 1)
    {
        puts("edmonto summon");
        struct proto_bug encoder;
        proto_bug_init(&encoder, RR_OUTGOING_PACKET);
        proto_bug_write_uint8(&encoder, 255, "qv");
        proto_bug_write_uint8(&encoder, rr_serverbound_dev_summon, "header");
        proto_bug_write_uint8(&encoder, rand() % rr_mob_id_ant, "id");
        proto_bug_write_uint8(&encoder, rr_rarity_id_ultimate, "rarity");

        rr_websocket_send(&game->socket, encoder.current - encoder.start);
    }
    game->cursor = rr_game_cursor_pointer;
}

static struct rr_ui_element *summon_mob_button_init()
{
    struct rr_ui_element *element = rr_ui_labeled_button_init("Summon", 30, 0);
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
    struct rr_ui_element *dev_tools = rr_ui_v_container_init(
        rr_ui_container_init(), 10, 10, summon_mob_button_init(),
        rr_ui_h_container_init(rr_ui_container_init(), 0, 10,
                               rr_ui_text_init("Speed:", 20, 0xffffffff),
                               speed_slider_init(game), NULL),
        NULL);
    dev_tools->should_show = dev_tools_should_show;
    struct rr_ui_element *inner = rr_ui_v_container_init(
        rr_ui_container_init(), 10, 10, NULL);
    for (uint32_t i = 0; i < RR_SQUAD_COUNT; ++i)
        rr_ui_container_add_element(
            inner, rr_ui_squad_container_init(&game->other_squads[i]));
    struct rr_ui_element *this =
        // clang-format off
    rr_ui_pad(
        rr_ui_set_background(
            rr_ui_v_pad(
                rr_ui_set_justify(
                    rr_ui_v_container_init(
                        rr_ui_container_init(), 10, 10,
                        rr_ui_text_init("Squads", 24, 0xffffffff),
                        dev_tools,
                        rr_ui_scroll_container_init(inner, 322),
                        NULL),
                    -1, -1),
                50),
            0x40ffffff),
        10);
    // clang-format on
    this->animate = dev_squad_panel_container_animate;
    this->should_show = dev_squad_panel_container_should_show;
    return this;
}
