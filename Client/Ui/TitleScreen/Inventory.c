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
#include <Client/Assets/RenderFunctions.h>
#include <Client/Renderer/Renderer.h>

#include <Client/Ui/Engine.h>

#include <Shared/Utilities.h>

struct inventory_button_metadata
{
    uint8_t id;
    uint8_t rarity;
    uint32_t count;
};

static void inventory_button_on_event(struct rr_ui_element *this,
                                      struct rr_game *game)
{
    struct inventory_button_metadata *data = this->data;
    if (game->input_data->mouse_buttons_up_this_tick & 1 &&
        game->pressed == this)
    {
        if (data->count == 0)
            return;
        for (uint8_t i = 0; i < game->slots_unlocked; ++i)
        {
            if (game->cache.loadout[i].id == 0)
            {
                game->cache.loadout[i].id = data->id;
                game->cache.loadout[i].rarity = data->rarity;
                return;
            }
        }
        for (uint8_t i = 10; i < 10 + game->slots_unlocked; ++i)
        {
            if (game->cache.loadout[i].id == 0)
            {
                game->cache.loadout[i].id = data->id;
                game->cache.loadout[i].rarity = data->rarity;
                return;
            }
        }
    }
    else
        rr_ui_render_tooltip_above(this, game->petal_tooltips[data->id][data->rarity], game);
}

static uint8_t inventory_button_should_show(struct rr_ui_element *this,
                                            struct rr_game *game)
{
    struct inventory_button_metadata *data = this->data;
    data->count = rr_game_get_adjusted_inventory_count(game, data->id, data->rarity);
    return data->count;
}

static uint8_t inventory_container_should_show(struct rr_ui_element *this,
                                               struct rr_game *game)
{
    return game->menu_open == rr_game_menu_inventory && !game->simulation_ready;
}

static void inventory_container_animate(struct rr_ui_element *this,
                                        struct rr_game *game)
{
    this->width = this->abs_width;
    this->height = this->abs_height;
    rr_renderer_translate(game->renderer, 0,
                          -(this->y - this->abs_height / 2) * 2 *
                              this->animation * game->renderer->scale);
}

static void inventory_button_on_render(struct rr_ui_element *this,
                                       struct rr_game *game)
{
    struct inventory_button_metadata *data = this->data;
    struct rr_renderer *renderer = game->renderer;
    rr_renderer_scale(renderer, renderer->scale * this->width / 60);
    struct rr_renderer_context_state state;
    rr_renderer_context_state_init(renderer, &state);
    rr_renderer_draw_background(renderer, data->rarity, 1);
    rr_renderer_draw_petal_with_name(renderer, data->id,
                                             data->rarity);
    rr_renderer_context_state_free(renderer, &state);
    if (data->count <= 1)
        return;
    rr_renderer_translate(renderer, 25, -25);
    rr_renderer_rotate(renderer, 0.5);
    rr_renderer_set_fill(renderer, 0xffffffff);
    rr_renderer_set_stroke(renderer, 0xff222222);
    rr_renderer_set_text_align(renderer, 1);
    rr_renderer_set_text_baseline(renderer, 1);
    rr_renderer_set_text_size(renderer, 18);
    rr_renderer_set_line_width(renderer, 18 * 0.12);

    char out[12];
    sprintf(&out[0], "x%d", data->count);
    rr_renderer_stroke_text(renderer, (char const *)&out, 0, 0);
    rr_renderer_fill_text(renderer, (char const *)&out, 0, 0);
}

static struct rr_ui_element *inventory_button_init(uint8_t id, uint8_t rarity)
{
    struct rr_ui_element *this = rr_ui_element_init();
    struct inventory_button_metadata *data = malloc(sizeof *data);
    data->id = id;
    data->rarity = rarity;
    this->data = data;
    this->abs_width = this->width = 50;
    this->abs_height = this->height = 50;
    this->on_render = inventory_button_on_render;
    this->should_show = inventory_button_should_show;
    this->on_event = inventory_button_on_event;
    this->animate = rr_ui_scale_animate;
    return this;
}

struct rr_ui_element *rr_ui_inventory_container_init()
{
    float test = 0;

    struct rr_ui_element *this = rr_ui_2d_container_init(5, 6, 15, 15);
    for (uint8_t rarity = rr_rarity_id_max - 1; rarity != 255; --rarity)
        for (uint8_t id = 1; id < rr_petal_id_max; ++id)
            rr_ui_container_add_element(this, inventory_button_init(id, rarity));
    rr_ui_set_background(this, 0x00000000);
    struct rr_ui_element *c = rr_ui_set_background(
        rr_ui_pad(
            rr_ui_set_justify(rr_ui_v_container_init(
                                  rr_ui_container_init(), 10, 10,
                                  rr_ui_text_init("Inventory", 24, 0xffffffff),
                                  rr_ui_scroll_container_init(this, 400),
                                  NULL
                            ),
                              -1, 1),
            10),
        0x40ffffff);
    c->x += 60 + 10;
    c->animate = inventory_container_animate;
    c->should_show = inventory_container_should_show;
    return c;
}

static void inventory_toggle_on_render(struct rr_ui_element *this,
                                       struct rr_game *game)
{
    struct rr_renderer *renderer = game->renderer;
    if (game->focused == this)
        renderer->state.filter.amount = 0.2;
    rr_renderer_scale(renderer, renderer->scale);
    rr_renderer_set_fill(renderer, this->fill);
    renderer->state.filter.amount += 0.2;
    rr_renderer_set_stroke(renderer, this->fill);
    rr_renderer_set_line_width(renderer, 6);
    rr_renderer_begin_path(renderer);
    rr_renderer_round_rect(renderer, -this->width / 2, -this->height / 2,
                           this->width, this->height, 6);
    rr_renderer_fill(renderer);
    rr_renderer_scale(renderer, 0.8);
    rr_renderer_set_fill(renderer, 0xffffffff);
    rr_renderer_begin_path(renderer);
    rr_renderer_move_to(renderer, 23.33446, -2.6127010000000013);
    rr_renderer_bezier_curve_to(renderer, 24.2073886, 7.090080999999998, 18.967551, 16.315945, 10.187094, 20.536078999999997);
    rr_renderer_bezier_curve_to(renderer, 1.4066340000000004, 24.756217499999998, -9.070863000000001, 23.0845447, -16.102187999999998, 16.341662999999997);
    rr_renderer_bezier_curve_to(renderer, -23.133512399999997, 9.598777399999996, -25.242334999999997, -0.7995510000000046, -21.393474499999996, -9.748982000000002);
    rr_renderer_bezier_curve_to(renderer, -17.544613299999995, -18.698411500000002, -8.546193999999996, -24.319875000000003, 1.1846275000000048, -23.8539005);
    rr_renderer_line_to(renderer, 0.8613395400000048, -17.102770900000003);
    rr_renderer_bezier_curve_to(renderer, -6.054159159999995, -17.433930000000004, -12.449156459999996, -13.438868100000004, -15.184465459999997, -7.078686900000003);
    rr_renderer_bezier_curve_to(renderer, -17.919774059999998, -0.7185069000000031, -16.421075859999995, 6.6713780999999965, -11.424054159999997, 11.463412099999998);
    rr_renderer_bezier_curve_to(renderer, -6.427032459999997, 16.2554424, 1.019115840000003, 17.443465099999997, 7.2592118400000025, 14.444300499999997);
    rr_renderer_bezier_curve_to(renderer, 13.499308840000001, 11.445132099999997, 17.22315534, 4.888497499999998, 16.602782840000003, -2.007077500000001);
    rr_renderer_fill(renderer);
    rr_renderer_set_fill(renderer, 0xffffffff);
    rr_renderer_begin_path(renderer);
    rr_renderer_move_to(renderer, -3.2152230000000017, -17.1968503);
    rr_renderer_line_to(renderer, 5.144357999999999, -16.939632420000002);
    rr_renderer_line_to(renderer, 7.9553797999999984, -16.750656130000003);
    rr_renderer_line_to(renderer, 10.519684199999999, -16.438320160000004);
    rr_renderer_line_to(renderer, 13.832020199999999, -15.939632420000004);
    rr_renderer_line_to(renderer, 14.393700039999999, -13.750656120000004);
    rr_renderer_line_to(renderer, 15.204723739999999, -11.002624520000005);
    rr_renderer_line_to(renderer, 15.832020189999998, -7.627296520000005);
    rr_renderer_line_to(renderer, 16.643043889999998, -1.2519685200000055);
    rr_renderer_line_to(renderer, 23.346458889999997, -2.2598420200000056);
    rr_renderer_line_to(renderer, 22.955379939999997, -5.750656220000005);
    rr_renderer_line_to(renderer, 21.018372039999996, -16.501312220000003);
    rr_renderer_line_to(renderer, 20.393700099999997, -18.501312220000003);
    rr_renderer_line_to(renderer, 19.393700099999997, -20.188976220000004);
    rr_renderer_line_to(renderer, 18.018371999999996, -21.627296620000003);
    rr_renderer_line_to(renderer, 16.393700099999997, -22.564304290000003);
    rr_renderer_line_to(renderer, 14.097115099999996, -23.070866050000003);
    rr_renderer_line_to(renderer, 0.45669409999999644, -23.87664038);
    rr_renderer_fill(renderer);
    rr_renderer_set_fill(renderer, 0xffffffff);
    rr_renderer_begin_path(renderer);
    rr_renderer_move_to(renderer, -14.692233, 15.376137);
    rr_renderer_bezier_curve_to(renderer, -16.0932187, 3.514208, -8.009691, -7.385411999999999, 3.7481050000000007, -9.488343);
    rr_renderer_line_to(renderer, 5.0527315, -2.1939876000000007);
    rr_renderer_bezier_curve_to(renderer, -2.8447465000000003, -0.7814910000000006, -8.2742895, 6.5395654, -7.333275499999999, 14.5069874);
    rr_renderer_fill(renderer);
    rr_renderer_set_fill(renderer, 0xffffffff);
    rr_renderer_begin_path(renderer);
    rr_renderer_move_to(renderer, 1.8865219999999994, -8.334557);
    rr_renderer_bezier_curve_to(renderer, 3.2485195999999994, -9.8537497, 5.5841844, -9.9811806, 7.103377999999999, -8.619183);
    rr_renderer_bezier_curve_to(renderer, 7.832919799999999, -7.96512836, 8.272758199999998, -7.0480522, 8.3261334, -6.069702599999999);
    rr_renderer_bezier_curve_to(renderer, 8.379512459999999, -5.0913528999999995, 8.0420567, -4.1318687999999995, 7.38800016, -3.402326999999999);
    rr_renderer_bezier_curve_to(renderer, 6.026004459999999, -1.8831352999999993, 3.69033776, -1.7557052999999991, 2.17114616, -3.1177028999999994);
    rr_renderer_bezier_curve_to(renderer, 0.6519544600000002, -4.4797005, 0.5245244600000001, -6.8153653, 1.8865220600000001, -8.334556899999999);
    rr_renderer_fill(renderer);
}

void inventory_toggle_button_on_event(struct rr_ui_element *this,
                                      struct rr_game *game)
{
    if (game->input_data->mouse_buttons_up_this_tick & 1)
    {
        if (game->pressed != this)
            return;
        if (game->menu_open == rr_game_menu_inventory)
            game->menu_open = rr_game_menu_none;
        else
            game->menu_open = rr_game_menu_inventory;
    }
    else
        rr_ui_render_tooltip_right(this, game->inventory_tooltip, game);
}

struct rr_ui_element *rr_ui_inventory_toggle_button_init()
{
    struct rr_ui_element *this = rr_ui_element_init();
    rr_ui_set_background(this, 0x80888888);
    this->abs_width = this->abs_height = this->width = this->height = 60;
    this->on_event = inventory_toggle_button_on_event;
    this->on_render = inventory_toggle_on_render;
    return this;
}
