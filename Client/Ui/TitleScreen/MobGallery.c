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

#include <stdlib.h>
#include <string.h>

#include <Client/Assets/RenderFunctions.h>
#include <Client/Game.h>
#include <Client/InputData.h>
#include <Client/Renderer/Renderer.h>
#include <Client/Simulation.h>
#include <Client/Ui/Engine.h>

#include <Shared/StaticData.h>
#include <Shared/Utilities.h>

struct mob_button_metadata
{
    uint8_t id;
    uint8_t rarity;
    float secondary_animation;
};

static void mob_button_on_event(struct rr_ui_element *this,
                                struct rr_game *game)
{
    struct mob_button_metadata *data = this->data;
    if (data->secondary_animation > 0.999)
        return;
    rr_ui_render_tooltip_above(this, game->mob_tooltips[data->id][data->rarity],
                               game);
}

static void mob_button_animate(struct rr_ui_element *this, struct rr_game *game)
{
    struct mob_button_metadata *data = this->data;
    struct rr_renderer *renderer = game->renderer;
    rr_renderer_scale(renderer, this->abs_width / 60 * renderer->scale);
    rr_renderer_draw_background(renderer, rr_rarity_id_max, 1);
    uint32_t count = game->cache.mob_kills[data->id][data->rarity];
#ifndef RIVET_BUILD
    count = 1;
#endif

    if (this->first_frame)
        data->secondary_animation = count == 0;
    data->secondary_animation =
        rr_lerp(data->secondary_animation, count == 0, 0.2);
    this->completely_hidden = 0;
    rr_renderer_scale(renderer, 1 - data->secondary_animation);
}

static void mob_button_on_render(struct rr_ui_element *this,
                                 struct rr_game *game)
{
    struct rr_renderer *renderer = game->renderer;
    struct mob_button_metadata *data = this->data;
    if (RR_MOB_DATA[data->id].min_rarity > data->rarity)
        return;
    if (data->secondary_animation > 0.999)
        return;
    struct rr_renderer_context_state state;
    rr_renderer_context_state_init(renderer, &state);
    rr_renderer_draw_background(renderer, data->rarity, 1);
    float mob_radius = RR_MOB_DATA[data->id].radius;
    if (mob_radius > 25)
        mob_radius = 25;
    rr_renderer_scale(renderer,
                      0.65 * mob_radius / RR_MOB_DATA[data->id].radius);

    rr_renderer_rotate(renderer, -0.78539816339); // pi / 4;
    rr_renderer_draw_mob(renderer, data->id, 0, 0, 1);
    if (data->id == rr_mob_id_house_centipede)
    {
        rr_renderer_translate(renderer, -2 * RR_MOB_DATA[data->id].radius, 0);
        rr_renderer_draw_mob(renderer, data->id, 0, 0, 1 | 4);
    }

    rr_renderer_context_state_free(renderer, &state);
}

static struct rr_ui_element *mob_button_init(uint8_t id, uint8_t rarity)
{
    struct rr_ui_element *this = rr_ui_element_init();
    struct mob_button_metadata *data = calloc(1, sizeof *data);
    data->id = id;
    data->rarity = rarity;
    this->abs_width = this->abs_height = this->width = this->height = 50;
    this->on_render = mob_button_on_render;
    this->on_event = mob_button_on_event;
    this->animate = mob_button_animate;
    this->data = data;
    return this;
}

static uint8_t mob_container_should_show(struct rr_ui_element *this,
                                         struct rr_game *game)
{
    return game->menu_open == rr_game_menu_gallery && !game->simulation_ready;
}

static void mob_container_animate(struct rr_ui_element *this,
                                  struct rr_game *game)
{
    this->width = this->abs_width;
    this->height = this->abs_height;
    rr_renderer_translate(game->renderer, 0,
                          -(this->y - this->abs_height / 2) * 2 *
                              this->animation * game->renderer->scale);
}

struct rr_ui_element *rr_ui_mob_container_init()
{
    struct rr_ui_element *this = rr_ui_2d_container_init(
        rr_rarity_id_max, rr_mob_id_edmontosaurus + 1, 15, 15);
    for (uint8_t id = 0; id <= rr_mob_id_edmontosaurus; ++id)
        for (uint8_t rarity = 0; rarity < rr_rarity_id_max; ++rarity)
            rr_ui_container_add_element(this, mob_button_init(id, rarity));
    rr_ui_set_background(this, 0x00000000);
    struct rr_ui_element *c = rr_ui_set_background(
        rr_ui_pad(rr_ui_set_justify(
                      rr_ui_v_container_init(
                          rr_ui_container_init(), 10, 10,
                          rr_ui_text_init("Mob Gallery", 24, 0xffffffff),
                          rr_ui_scroll_container_init(this, 400), NULL),
                      -1, 1),
                  10),
        0x40ffffff);
    // rr_ui_container_refactor(c);
    c->x += 60 + 10;
    c->animate = mob_container_animate;
    c->should_show = mob_container_should_show;
    return c;
}

static void mob_toggle_toggle_on_render(struct rr_ui_element *this,
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
    rr_renderer_set_fill(renderer, 0xffffffff);
    rr_renderer_begin_path(renderer);
    rr_renderer_move_to(renderer, 5.129797, -6.181861999999999);
    rr_renderer_bezier_curve_to(renderer, 9.787628, -5.012302499999999,
                                13.053443999999999, -0.8250733999999991,
                                13.053443999999999, 3.977348000000001);
    rr_renderer_line_to(renderer, 7.816154599999999, 3.977348000000001);
    rr_renderer_bezier_curve_to(renderer, 7.816154599999999, 1.5761372000000011,
                                6.183246699999999, -0.5174773999999989,
                                3.8543320999999993, -1.102256999999999);
    rr_renderer_fill(renderer);
    rr_renderer_set_fill(renderer, 0xffffffff);
    rr_renderer_begin_path(renderer);
    rr_renderer_move_to(renderer, 13.05348, 3.9773309999999995);
    rr_renderer_bezier_curve_to(renderer, 13.05348, 8.5169485,
                                9.715734300000001, 12.36589, 5.2218226,
                                13.008453);
    rr_renderer_line_to(renderer, 4.4773005, 7.801467499999999);
    rr_renderer_bezier_curve_to(renderer, 6.3802031, 7.529380399999999,
                                7.7935389, 5.899585299999999, 7.7935389,
                                3.9773307999999994);
    rr_renderer_fill(renderer);
    rr_renderer_set_fill(renderer, 0xffffffff);
    rr_renderer_begin_path(renderer);
    rr_renderer_move_to(renderer, -5.8325309999999995, -3.813497999999999);
    rr_renderer_bezier_curve_to(
        renderer, -2.7042712999999994, -6.225471999999999, 1.3472423000000004,
        -7.092741499999999, 5.188749000000001, -6.172722299999999);
    rr_renderer_line_to(renderer, 3.9631459000000016, -1.055261999999999);
    rr_renderer_bezier_curve_to(
        renderer, 1.6687676000000016, -1.604751999999999, -0.7510397999999983,
        -1.0867675849999991, -2.619423099999999, 0.35380900000000093);
    rr_renderer_fill(renderer);
    rr_renderer_set_fill(renderer, 0xffffffff);
    rr_renderer_begin_path(renderer);
    rr_renderer_move_to(renderer, -12.398027, 6.553243999999999);
    rr_renderer_bezier_curve_to(
        renderer, -11.405954900000001, 2.403478999999999, -9.029213500000001,
        -1.2842632000000007, -5.659765000000001, -3.901815000000001);
    rr_renderer_line_to(renderer, -2.4345320000000013, 0.2498725999999989);
    rr_renderer_bezier_curve_to(
        renderer, -4.859928000000002, 2.1340392999999986, -6.570753000000002,
        4.788549599999999, -7.284866000000001, 7.775631299999999);
    rr_renderer_fill(renderer);
    rr_renderer_set_fill(renderer, 0xffffffff);
    rr_renderer_begin_path(renderer);
    rr_renderer_move_to(renderer, 2.144086999999999, 10.398014000000003);
    rr_renderer_bezier_curve_to(renderer, 2.144086999999999, 8.958911800000003,
                                3.310707299999999, 7.792293500000003,
                                4.749807499999999, 7.792293500000003);
    rr_renderer_bezier_curve_to(renderer, 5.440885699999999, 7.792293500000003,
                                6.103660699999999, 8.066822000000004,
                                6.592329199999999, 8.555492350000003);
    rr_renderer_bezier_curve_to(renderer, 7.080997639999999, 9.044158880000003,
                                7.355526149999999, 9.706932050000002,
                                7.355526149999999, 10.398014050000004);
    rr_renderer_bezier_curve_to(renderer, 7.355526149999999, 11.837112450000005,
                                6.188905849999999, 13.003730750000004,
                                4.74980755, 13.003730750000004);
    rr_renderer_bezier_curve_to(renderer, 3.31070725, 13.003730750000004,
                                2.14408705, 11.837112450000005, 2.14408705,
                                10.398014050000004);
    rr_renderer_fill(renderer);
    rr_renderer_set_fill(renderer, 0xffffffff);
    rr_renderer_begin_path(renderer);
    rr_renderer_move_to(renderer, -7.2126920000000005, 20.278889999999997);
    rr_renderer_bezier_curve_to(renderer, -11.605316, 17.172551499999997,
                                -13.6448867, 11.691307999999998, -12.3513,
                                6.469136999999996);
    rr_renderer_line_to(renderer, -7.2434385, 7.734407199999996);
    rr_renderer_bezier_curve_to(renderer, -8.0160463, 10.853402899999995,
                                -6.7978914, 14.127130199999996, -4.1743543,
                                15.982420199999996);
    rr_renderer_fill(renderer);
    rr_renderer_set_fill(renderer, 0xffffffff);
    rr_renderer_begin_path(renderer);
    rr_renderer_move_to(renderer, 14.323692000000001, 20.247031999999997);
    rr_renderer_bezier_curve_to(renderer, 7.855304400000001, 24.786785,
                                -0.7640979999999988, 24.787334299999998,
                                -7.233065, 20.248405290999997);
    rr_renderer_line_to(renderer, -4.2134517, 15.944797290999997);
    rr_renderer_bezier_curve_to(renderer, 0.44304029999999983,
                                19.212009290999998, 6.6474583, 19.211616291,
                                11.3035353, 15.943809284399997);
    rr_renderer_fill(renderer);
    rr_renderer_set_fill(renderer, 0xffffffff);
    rr_renderer_begin_path(renderer);
    rr_renderer_move_to(renderer, -23.9192935, -5.6444399999999995);
    rr_renderer_bezier_curve_to(renderer, -21.1909009, -16.098416,
                                -11.928569499999998, -23.52515,
                                -1.1314934999999977, -23.916184);
    rr_renderer_bezier_curve_to(
        renderer, 9.665581500000002, -24.307217050000002, 19.440880500000002,
        -17.569959700000002, 22.918351500000004, -7.340739000000003);
    rr_renderer_bezier_curve_to(
        renderer, 26.395818100000003, 2.8884799999999977, 22.752057400000005,
        14.187605999999999, 13.953736500000003, 20.458111);
    rr_renderer_line_to(renderer, 10.896249000000003, 16.168067999999998);
    rr_renderer_bezier_curve_to(
        renderer, 17.800118600000005, 11.247726499999999, 20.659303,
        2.381530999999999, 17.930604000000002, -5.645134000000002);
    rr_renderer_bezier_curve_to(
        renderer, 15.201905300000004, -13.671798000000003, 7.531423000000002,
        -18.958389000000004, -0.9408269999999987, -18.651553);
    rr_renderer_bezier_curve_to(renderer, -9.413075999999998, -18.34471687,
                                -16.681041, -12.517107, -18.821956999999998,
                                -4.314081);
    rr_renderer_fill(renderer);
    rr_renderer_set_fill(renderer, 0xffffffff);
    rr_renderer_begin_path(renderer);
    rr_renderer_move_to(renderer, -9.885905, 7.993946000000001);
    rr_renderer_bezier_curve_to(renderer, -16.663037, 7.982112809000001,
                                -22.530467, 3.283201000000001,
                                -24.022855999999997, -3.3275799999999993);
    rr_renderer_line_to(renderer, -18.778270999999997, -4.511549499999999);
    rr_renderer_bezier_curve_to(renderer, -17.838542739999998,
                                -0.34887349999999895, -14.143938999999996,
                                2.609937200000001, -9.876514999999996,
                                2.6173892000000007);
    rr_renderer_fill(renderer);
    rr_renderer_set_fill(renderer, 0xffffffff);
    rr_renderer_begin_path(renderer);
    rr_renderer_move_to(renderer, -24.2526495, -4.465878);
    rr_renderer_bezier_curve_to(renderer, -24.2526495, -5.9049783, -23.086029,
                                -7.0715985, -21.6469297, -7.0715985);
    rr_renderer_bezier_curve_to(renderer, -20.955850100000003, -7.0715985,
                                -20.293075, -6.797068100000001, -19.8044076,
                                -6.30840155);
    rr_renderer_bezier_curve_to(renderer, -19.3157406, -5.8197331100000005,
                                -19.041210200000002, -5.15695805,
                                -19.041210200000002, -4.46587795);
    rr_renderer_bezier_curve_to(
        renderer, -19.041210200000002, -3.0267795500000005, -20.2078305,
        -1.8601593500000004, -21.646929800000002, -1.8601593500000004);
    rr_renderer_bezier_curve_to(renderer, -23.0860291, -1.8601593500000004,
                                -24.2526496, -3.0267796500000004, -24.2526496,
                                -4.46587795);
    rr_renderer_fill(renderer);
}

void mob_toggle_toggle_button_on_event(struct rr_ui_element *this,
                                       struct rr_game *game)
{
    if (game->input_data->mouse_buttons_up_this_tick & 1)
    {
        if (game->pressed != this)
            return;
        if (game->menu_open == rr_game_menu_gallery)
            game->menu_open = rr_game_menu_none;
        else
            game->menu_open = rr_game_menu_gallery;
    }
    else
        rr_ui_render_tooltip_right(this, game->gallery_tooltip, game);
}

struct rr_ui_element *rr_ui_mob_gallery_toggle_button_init()
{
    struct rr_ui_element *this = rr_ui_element_init();
    rr_ui_set_background(this, 0x80888888);
    this->abs_width = this->abs_height = this->width = this->height = 60;
    this->on_event = mob_toggle_toggle_button_on_event;
    this->on_render = mob_toggle_toggle_on_render;
    return this;
}