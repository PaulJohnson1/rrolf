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

#include <math.h>
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
#include <Shared/pb.h>

#define PETALS_PER_CRAFT 5

struct crafting_ring_metadata
{
    float angle;
    float v_angle;
};

struct crafting_ring_button_metadata
{
    uint32_t count;
    float secondary_animation;
    uint8_t pos;
    uint8_t prev_id;
    uint8_t prev_rarity;
};

struct crafting_inventory_button_metadata
{
    uint8_t id;
    uint8_t rarity;
    uint32_t count;
    float secondary_animation;
};

struct craft_captures
{
    struct rr_game_crafting_data craft;
    struct rr_game *game;
};

static void craft_button_on_event(struct rr_ui_element *this,
                                  struct rr_game *game)
{
    if (game->pressed != this || !game->logged_in || !game->socket_ready)
        return;
    if (game->input_data->mouse_buttons_up_this_tick & 1 &&
        game->crafting_data.animation == 0)
    {
        if (game->crafting_data.success_count == 0 &&
            game->crafting_data.count >= PETALS_PER_CRAFT &&
            game->crafting_data.crafting_id != 0 &&
            game->crafting_data.crafting_rarity < rr_rarity_id_max - 1)
        {
            game->crafting_data.success_count = 0;
            game->crafting_data.animation = 50;
            struct proto_bug encoder;
            proto_bug_init(&encoder, RR_OUTGOING_PACKET);
            proto_bug_write_uint8(&encoder, rr_serverbound_petals_craft,
                                  "header");
            proto_bug_write_uint8(&encoder, game->crafting_data.crafting_id,
                                  "craft id");
            proto_bug_write_uint8(&encoder, game->crafting_data.crafting_rarity,
                                  "craft rarity");
            proto_bug_write_varuint(&encoder, game->crafting_data.count,
                                    "craft count");
            rr_websocket_send(&game->socket, encoder.current - encoder.start);
        }
    }
}

static uint8_t crafting_ring_should_show(struct rr_ui_element *this,
                                         struct rr_game *game)
{
    return game->crafting_data.success_count == 0 ||
           game->crafting_data.animation != 0;
}

static void crafting_ring_petal_on_event(struct rr_ui_element *this,
                                         struct rr_game *game)
{
    if (game->crafting_data.crafting_id == 0)
        return;
    struct crafting_ring_button_metadata *data = this->data;
    if (game->input_data->mouse_buttons_up_this_tick & 1 &&
        game->pressed == this && game->crafting_data.animation == 0)
    {
        game->crafting_data.count = game->crafting_data.success_count = 0;
        game->crafting_data.crafting_id = game->crafting_data.crafting_rarity =
            0;
    }
    else if (data->count > 0)
        rr_ui_render_tooltip_above(
            this,
            game->petal_tooltips[game->crafting_data.crafting_id]
                                [game->crafting_data.crafting_rarity],
            game);
}

static void crafting_result_container_on_event(struct rr_ui_element *this,
                                               struct rr_game *game)
{
    if (game->input_data->mouse_buttons_up_this_tick & 1)
    {
        if (game->pressed != this)
            return;
        game->crafting_data.count = game->crafting_data.success_count = 0;
        game->crafting_data.crafting_id = game->crafting_data.crafting_rarity =
            0;
    }
    else if (game->crafting_data.success_count > 0)
        rr_ui_render_tooltip_above(
            this,
            game->petal_tooltips[game->crafting_data.crafting_id]
                                [game->crafting_data.crafting_rarity + 1],
            game);
}

static void crafting_ring_petal_animate(struct rr_ui_element *this,
                                        struct rr_game *game)
{
    struct crafting_ring_button_metadata *data = this->data;
    data->count = (game->crafting_data.count + data->pos) / PETALS_PER_CRAFT;
    if (this->first_frame)
        data->secondary_animation = data->count == 0;
    data->secondary_animation = rr_lerp(
        data->secondary_animation,
        data->count == 0 || data->prev_id != game->crafting_data.crafting_id ||
            data->prev_rarity != game->crafting_data.crafting_rarity,
        0.4);

    rr_renderer_scale(game->renderer, game->renderer->scale * this->width / 60);
    rr_renderer_draw_background(game->renderer, rr_rarity_id_max, 1);
    if (game->crafting_data.crafting_id != 0)
    {
        data->prev_id = game->crafting_data.crafting_id;
        data->prev_rarity = game->crafting_data.crafting_rarity;
    }
    rr_renderer_scale(game->renderer, (1 - data->secondary_animation));
    rr_renderer_rotate(game->renderer, data->secondary_animation * M_PI * 2);
}

static void crafting_ring_petal_on_render(struct rr_ui_element *this,
                                          struct rr_game *game)
{
    struct crafting_ring_button_metadata *data = this->data;
    struct rr_renderer *renderer = game->renderer;
    struct rr_renderer_context_state state;
    rr_renderer_context_state_init(renderer, &state);
    rr_renderer_draw_background(renderer, data->prev_rarity, 1);
    rr_renderer_draw_petal_with_name(renderer, data->prev_id,
                                     data->prev_rarity);
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

static struct rr_ui_element *crafting_ring_petal_init(uint8_t pos)
{
    struct rr_ui_element *this = rr_ui_element_init();
    struct crafting_ring_button_metadata *data = malloc(sizeof *data);
    data->pos = pos;
    data->prev_id = data->prev_rarity = 0;
    data->secondary_animation = 0;
    this->data = data;
    this->abs_width = this->width = 60;
    this->abs_height = this->height = 60;
    this->animate = crafting_ring_petal_animate;
    this->on_render = crafting_ring_petal_on_render;
    this->on_event = crafting_ring_petal_on_event;
    return this;
}

static void crafting_ring_on_render(struct rr_ui_element *this,
                                    struct rr_game *game)
{
    struct crafting_ring_metadata *data = this->data;
    if (game->crafting_data.animation != 0)
        data->v_angle = 0.1;
    data->angle += data->v_angle;
    data->v_angle *= 0.8;
    struct rr_renderer_context_state state;
    for (uint32_t i = 0; i < this->elements.size; ++i)
    {
        rr_renderer_context_state_init(game->renderer, &state);
        rr_renderer_translate(
            game->renderer,
            game->renderer->scale *
                cosf(i * 2 * M_PI / this->elements.size + data->angle) * 120,
            game->renderer->scale *
                sinf(i * 2 * M_PI / this->elements.size + data->angle) * 120);
        rr_ui_render_element(this->elements.start[i], game);
        rr_renderer_context_state_free(game->renderer, &state);
    }
}
static struct rr_ui_element *crafting_ring_init()
{
    struct rr_ui_element *this = rr_ui_element_init();
    struct crafting_ring_metadata *data = malloc(sizeof *data);
    memset(data, 0, sizeof *data);
    this->data = data;
    this->abs_width = this->width = 300;
    this->abs_height = this->height = 300;
    this->on_render = crafting_ring_on_render;
    for (uint32_t i = 0; i < PETALS_PER_CRAFT; ++i)
        rr_ui_container_add_element(this, crafting_ring_petal_init(i));
    this->poll_events = rr_ui_container_poll_events;
    this->should_show = crafting_ring_should_show;
    this->animate = rr_ui_scale_animate;
    return this;
}

static uint8_t crafting_result_container_should_show(struct rr_ui_element *this,
                                                     struct rr_game *game)
{
    return game->crafting_data.success_count &&
           game->crafting_data.animation == 0 &&
           game->crafting_data.crafting_id != 0;
}

static void crafting_result_container_on_render(struct rr_ui_element *this,
                                                struct rr_game *game)
{
    struct rr_renderer *renderer = game->renderer;
    struct rr_renderer_context_state state;
    rr_renderer_scale(renderer, renderer->scale);
    rr_renderer_context_state_init(renderer, &state);
    rr_renderer_draw_background(renderer,
                                game->crafting_data.crafting_rarity + 1, 1);
    rr_renderer_draw_petal_with_name(renderer, game->crafting_data.crafting_id,
                                     game->crafting_data.crafting_rarity + 1);
    rr_renderer_context_state_free(renderer, &state);
    if (game->crafting_data.success_count <= 1)
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
    sprintf(&out[0], "x%d", game->crafting_data.success_count);
    rr_renderer_stroke_text(renderer, (char const *)&out, 0, 0);
    rr_renderer_fill_text(renderer, (char const *)&out, 0, 0);
}

static struct rr_ui_element *crafting_result_container_init()
{
    struct rr_ui_element *this = rr_ui_element_init();
    this->abs_width = this->width = 60;
    this->abs_height = this->height = 60;
    this->on_render = crafting_result_container_on_render;
    this->on_event = crafting_result_container_on_event;
    this->should_show = crafting_result_container_should_show;
    return this;
}

static struct rr_ui_element *crafting_button_init()
{
    struct rr_ui_element *this = rr_ui_labeled_button_init("Craft", 36, NULL);
    this->on_event = craft_button_on_event;
    rr_ui_set_background(this, 0xfffcfc8c);
    return this;
}

static void crafting_chance_text_animate(struct rr_ui_element *this,
                                         struct rr_game *game)
{
    struct rr_ui_text_metadata *data = this->data;
    if (game->crafting_data.crafting_id == 0)
    {
        data->text = "Chance: --%";
        rr_ui_set_background(this, 0xff888888);
        return;
    }
    this->fill = RR_RARITY_COLORS[game->crafting_data.crafting_rarity + 1];
    static char text[100] = {0};
    double chance =
        100 *
        (1 + game->failed_crafts[game->crafting_data.crafting_id]
                                [game->crafting_data.crafting_rarity]) *
        RR_CRAFT_CHANCES[game->crafting_data.crafting_rarity];
    snprintf(text, 99, "Chance: %0.3f%%", chance > 100 ? 100 : chance);
    data->text = text;
}

static struct rr_ui_element *crafting_chance_text_init()
{
    struct rr_ui_element *this = rr_ui_text_init("Chance: --%", 14, 0xff888888);
    this->animate = crafting_chance_text_animate;
    return this;
}

static void crafting_xp_text_animate(struct rr_ui_element *this,
                                     struct rr_game *game)
{
    struct rr_ui_text_metadata *data = this->data;
    if (game->crafting_data.crafting_id == 0)
    {
        data->text = "? xp per craft";
        rr_ui_set_background(this, 0xff888888);
        return;
    }
    this->fill = RR_RARITY_COLORS[game->crafting_data.crafting_rarity];
    switch (game->crafting_data.crafting_rarity)
    {
    case rr_rarity_id_common:
        data->text = "1 xp per craft";
        break;
    case rr_rarity_id_unusual:
        data->text = "8 xp per craft";
        break;
    case rr_rarity_id_rare:
        data->text = "60 xp per craft";
        break;
    case rr_rarity_id_epic:
        data->text = "750 xp per craft";
        break;
    case rr_rarity_id_legendary:
        data->text = "25k xp per craft";
        break;
    case rr_rarity_id_mythic:
        data->text = "1m xp per craft";
        break;
    case rr_rarity_id_exotic:
        data->text = "25m xp per craft";
        break;
    }
}

static struct rr_ui_element *crafting_xp_text_init()
{
    struct rr_ui_element *this =
        rr_ui_text_init("? xp per craft", 14, 0xff888888);
    this->animate = crafting_xp_text_animate;
    return this;
}

static void crafting_inventory_button_animate(struct rr_ui_element *this,
                                              struct rr_game *game)
{
    struct crafting_inventory_button_metadata *data = this->data;
    uint32_t count = data->count =
        rr_game_get_adjusted_inventory_count(game, data->id, data->rarity);
    if (this->first_frame)
        data->secondary_animation = count == 0;

    data->secondary_animation =
        rr_lerp(data->secondary_animation, count == 0, 0.2);
    rr_renderer_scale(game->renderer, game->renderer->scale * this->width / 60);
    rr_renderer_draw_background(game->renderer, rr_rarity_id_max, 1);
    rr_renderer_scale(game->renderer, (1 - data->secondary_animation));
}

static void crafting_inventory_button_on_event(struct rr_ui_element *this,
                                               struct rr_game *game)
{
    struct crafting_inventory_button_metadata *data = this->data;
    uint32_t count = data->count;
    if (game->crafting_data.crafting_id == data->id &&
        game->crafting_data.crafting_rarity == data->rarity)
        count += game->crafting_data.count;
    if (game->input_data->mouse_buttons_up_this_tick & 1 &&
        game->pressed == this && game->crafting_data.animation == 0)
    {
        if (count < PETALS_PER_CRAFT || data->rarity == rr_rarity_id_max - 1)
            return;
        if (game->crafting_data.crafting_id != data->id ||
            game->crafting_data.crafting_rarity != data->rarity)
        {
            game->crafting_data.crafting_id = data->id;
            game->crafting_data.crafting_rarity = data->rarity;
            game->crafting_data.count = 0;
            game->crafting_data.success_count = 0;
        }
        if (rr_bitset_get(game->input_data->keys_pressed, 16))
            game->crafting_data.count += data->count;
        else if (data->count > PETALS_PER_CRAFT)
            game->crafting_data.count += PETALS_PER_CRAFT;
        else
            game->crafting_data.count += data->count;
        if (data->count > 0)
            data->secondary_animation = 0.4;
    }
    else if (data->count > 0)
        rr_ui_render_tooltip_above(
            this, game->petal_tooltips[data->id][data->rarity], game);
}

static void crafting_container_animate(struct rr_ui_element *this,
                                       struct rr_game *game)
{
    this->width = this->abs_width;
    this->height = this->abs_height;
    rr_renderer_translate(game->renderer, 0,
                          -(this->y - this->abs_height / 2) * 2 *
                              this->animation * game->renderer->scale);
}

static void crafting_inventory_button_on_render(struct rr_ui_element *this,
                                                struct rr_game *game)
{
    struct crafting_inventory_button_metadata *data = this->data;
    if (data->secondary_animation > 0.999)
        return;
    struct rr_renderer *renderer = game->renderer;
    struct rr_renderer_context_state state;
    rr_renderer_context_state_init(renderer, &state);
    uint32_t count = data->count;
    if (game->crafting_data.crafting_id == data->id &&
        game->crafting_data.crafting_rarity == data->rarity)
        count += game->crafting_data.count;
    if (count < 5)
        rr_renderer_draw_background(renderer, rr_rarity_id_max + 2, 1);
    else
        rr_renderer_draw_background(renderer, data->rarity, 1);
    rr_renderer_draw_petal_with_name(renderer, data->id, data->rarity);
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

struct rr_ui_element *crafting_inventory_button_init(uint8_t id, uint8_t rarity)
{
    struct rr_ui_element *this = rr_ui_element_init();
    struct crafting_inventory_button_metadata *data = malloc(sizeof *data);
    data->id = id;
    data->rarity = rarity;
    data->count = 0;
    data->secondary_animation = 0;
    this->data = data;
    this->abs_width = this->width = 50;
    this->abs_height = this->height = 50;
    this->on_render = crafting_inventory_button_on_render;
    this->should_show = rr_ui_always_show;
    this->on_event = crafting_inventory_button_on_event;
    this->animate = crafting_inventory_button_animate;
    return this;
}

static uint8_t crafting_container_should_show(struct rr_ui_element *this,
                                              struct rr_game *game)
{
    return game->menu_open == rr_game_menu_crafting && !game->simulation_ready;
}

struct rr_ui_element *rr_ui_crafting_container_init()
{
    struct rr_ui_element *this =
        rr_ui_2d_container_init(rr_rarity_id_max, 6, 15, 15);
    for (uint8_t id = 1; id < rr_petal_id_max; ++id)
        for (uint8_t rarity = 0; rarity < rr_rarity_id_max; ++rarity)
            rr_ui_container_add_element(
                this, crafting_inventory_button_init(id, rarity));
    rr_ui_set_background(this, 0x00000000);
    struct rr_ui_element *craft = rr_ui_container_init();
    rr_ui_container_add_element(craft, crafting_ring_init());
    rr_ui_container_add_element(craft, crafting_result_container_init());
    craft->abs_width = craft->width = 300;
    craft->abs_height = craft->height = 300;
    struct rr_ui_element *c = rr_ui_set_background(
        rr_ui_pad(
            rr_ui_set_justify(
                rr_ui_v_container_init(
                    rr_ui_container_init(), 10, 10,
                    rr_ui_text_init("Crafting", 24, 0xffffffff),
                    rr_ui_h_container_init(
                        rr_ui_container_init(), 0, 25,
                        rr_ui_v_container_init(rr_ui_container_init(), 0, 10,
                                               rr_ui_static_space_init(38),
                                               crafting_button_init(),
                                               crafting_chance_text_init(),
                                               crafting_xp_text_init(), NULL),
                        craft, NULL),
                    rr_ui_scroll_container_init(this, 300), NULL),
                -1, 1),
            10),
        0x40ffffff);
    c->x += 60 + 10;
    c->animate = crafting_container_animate;
    c->should_show = crafting_container_should_show;
    return c;
}

static void crafting_toggle_on_render(struct rr_ui_element *this,
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
    rr_renderer_move_to(renderer, -24.73884514, -4.406824);
    rr_renderer_bezier_curve_to(renderer, -24.73884514, -7.9466647,
                                -21.86923714, -10.816272600000001, -18.32939614,
                                -10.816272600000001);
    rr_renderer_bezier_curve_to(renderer, -16.62950504, -10.816272600000001,
                                -14.99923604, -10.140993940000001, -13.79723154,
                                -8.938989500000002);
    rr_renderer_bezier_curve_to(renderer, -12.59522714, -7.736984100000002,
                                -11.91994754, -6.106716000000002, -11.91994754,
                                -4.406824000000002);
    rr_renderer_bezier_curve_to(renderer, -11.91994754, -0.866983300000002,
                                -14.78955554, 2.002624599999998, -18.32939614,
                                2.002624599999998);
    rr_renderer_bezier_curve_to(renderer, -21.86923714, 2.002624599999998,
                                -24.738845140000002, -0.8669834000000018,
                                -24.738845140000002, -4.406824000000002);
    rr_renderer_fill(renderer);
    rr_renderer_set_fill(renderer, 0xffffffff);
    rr_renderer_begin_path(renderer);
    rr_renderer_move_to(renderer, -17.7677164, 17.25197);
    rr_renderer_bezier_curve_to(renderer, -17.7677164, 13.7121293,
                                -14.898108400000002, 10.8425195, -11.3582678,
                                10.8425195);
    rr_renderer_bezier_curve_to(renderer, -9.6583758, 10.8425195, -8.0281086,
                                11.517801, -6.8261032, 12.7198045);
    rr_renderer_bezier_curve_to(renderer, -5.6240978, 13.9218118, -4.9488182,
                                15.5520799, -4.9488182, 17.25197);
    rr_renderer_bezier_curve_to(renderer, -4.9488182, 20.7918107,
                                -7.818426199999999, 23.6614205, -11.3582678,
                                23.6614205);
    rr_renderer_bezier_curve_to(renderer, -14.8981085, 23.6614205, -17.7677164,
                                20.7918107, -17.7677164, 17.25197);
    rr_renderer_fill(renderer);
    rr_renderer_set_fill(renderer, 0xffffffff);
    rr_renderer_begin_path(renderer);
    rr_renderer_move_to(renderer, -6.41076, -17.7716537);
    rr_renderer_bezier_curve_to(renderer, -6.41076, -21.3114944, -3.541152,
                                -24.181102300000003, -0.0013113999999996295,
                                -24.181102300000003);
    rr_renderer_bezier_curve_to(
        renderer, 1.6985806000000003, -24.181102300000003, 3.3288487000000004,
        -23.505823100000004, 4.5308541, -22.303818300000003);
    rr_renderer_bezier_curve_to(renderer, 5.7328576, -21.101813600000003,
                                6.4081372000000005, -19.471545300000002,
                                6.4081372000000005, -17.7716537);
    rr_renderer_bezier_curve_to(
        renderer, 6.4081372000000005, -14.231812500000002, 3.5385292000000006,
        -11.362204700000001, -0.0013113999999996295, -11.362204700000001);
    rr_renderer_bezier_curve_to(renderer, -3.5411520999999997,
                                -11.362204700000001, -6.41076, -14.2318127,
                                -6.41076, -17.7716537);
    rr_renderer_fill(renderer);
    rr_renderer_set_fill(renderer, 0xffffffff);
    rr_renderer_begin_path(renderer);
    rr_renderer_move_to(renderer, 11.918636, -4.215223000000002);
    rr_renderer_bezier_curve_to(renderer, 11.918636, -7.755063700000002,
                                14.788242, -10.624671600000003, 18.3280827,
                                -10.624671600000003);
    rr_renderer_bezier_curve_to(renderer, 20.0279767, -10.624671600000003,
                                21.6582447, -9.949392000000003, 22.8602482,
                                -8.747386600000002);
    rr_renderer_bezier_curve_to(renderer, 24.0622517, -7.545383100000002,
                                24.7375332, -5.915115000000002, 24.7375332,
                                -4.215223000000003);
    rr_renderer_bezier_curve_to(renderer, 24.7375332, -0.6753823000000025,
                                21.867923400000002, 2.1942255999999976,
                                18.328082700000003, 2.1942255999999976);
    rr_renderer_bezier_curve_to(
        renderer, 14.788242000000004, 2.1942255999999976, 11.918636000000003,
        -0.6753824000000024, 11.918636000000003, -4.215223000000003);
    rr_renderer_fill(renderer);
    rr_renderer_set_fill(renderer, 0xffffffff);
    rr_renderer_begin_path(renderer);
    rr_renderer_move_to(renderer, 4.946193999999998, 17.25197);
    rr_renderer_bezier_curve_to(renderer, 4.946193999999998, 13.7121293,
                                7.8158037999999985, 10.8425195,
                                11.355644499999999, 10.8425195);
    rr_renderer_bezier_curve_to(renderer, 13.055534599999998, 10.8425195,
                                14.685802699999998, 11.517801,
                                15.887806199999998, 12.7198045);
    rr_renderer_bezier_curve_to(renderer, 17.089813499999998, 13.9218118,
                                17.765091199999997, 15.5520799,
                                17.765091199999997, 17.25197);
    rr_renderer_bezier_curve_to(renderer, 17.765091199999997, 20.7918107,
                                14.895485199999996, 23.6614205,
                                11.355644499999997, 23.6614205);
    rr_renderer_bezier_curve_to(renderer, 7.815803799999997, 23.6614205,
                                4.946193999999997, 20.7918107,
                                4.946193999999997, 17.25197);
    rr_renderer_fill(renderer);
    rr_renderer_set_fill(renderer, 0xffffffff);
    rr_renderer_begin_path(renderer);
    rr_renderer_move_to(renderer, -14.709308, -12.572641);
    rr_renderer_bezier_curve_to(renderer, -12.9862827, -14.3609577, -10.9515823,
                                -15.820073700000002, -8.705057499999999,
                                -16.878386);
    rr_renderer_line_to(renderer, -5.857448899999999, -10.833644399999999);
    rr_renderer_bezier_curve_to(renderer, -7.369045599999999, -10.1215482,
                                -8.7381137, -9.1397672, -9.897469899999999,
                                -7.936480999999999);
    rr_renderer_fill(renderer);
    rr_renderer_set_fill(renderer, 0xffffffff);
    rr_renderer_begin_path(renderer);
    rr_renderer_move_to(renderer, -17.9825335, 11.287284999999997);
    rr_renderer_bezier_curve_to(renderer, -19.1592904, 9.100616599999997,
                                -19.927422099999998, 6.717681999999997,
                                -20.249235199999998, 4.255422699999997);
    rr_renderer_line_to(renderer, -13.624016799999998, 3.389518849999997);
    rr_renderer_bezier_curve_to(
        renderer, -13.407481229999998, 5.046274249999997, -12.890635499999998,
        6.6496545499999975, -12.098843599999999, 8.120975649999997);
    rr_renderer_fill(renderer);
    rr_renderer_set_fill(renderer, 0xffffffff);
    rr_renderer_begin_path(renderer);
    rr_renderer_move_to(renderer, 3.6377750000000013, 21.710464);
    rr_renderer_bezier_curve_to(
        renderer, 1.1950355000000012, 22.151286600000002, -1.3076156999999986,
        22.142951500000002, -3.747366399999999, 21.685878276);
    rr_renderer_line_to(renderer, -2.517509899999999, 15.121222976);
    rr_renderer_bezier_curve_to(renderer, -0.875900699999999, 15.428771496,
                                0.8080345000000011, 15.434375276,
                                2.4516561000000014, 15.137767318);
    rr_renderer_fill(renderer);
    rr_renderer_set_fill(renderer, 0xffffffff);
    rr_renderer_begin_path(renderer);
    rr_renderer_move_to(renderer, 14.503703999999999, -12.361691);
    rr_renderer_bezier_curve_to(renderer, 12.836688899999999, -14.1881042,
                                10.857028999999999, -15.684033900000001,
                                8.663459699999999, -16.7748723);
    rr_renderer_line_to(renderer, 5.8911913999999985, -10.890056299999998);
    rr_renderer_bezier_curve_to(
        renderer, 7.368980299999999, -10.135965039999999, 8.700363099999999,
        -9.104503299999998, 9.818450799999999, -7.847493799999998);
    rr_renderer_fill(renderer);
    rr_renderer_set_fill(renderer, 0xffffffff);
    rr_renderer_begin_path(renderer);
    rr_renderer_move_to(renderer, 17.607044000000002, 11.099696999999999);
    rr_renderer_bezier_curve_to(renderer, 18.720905100000003, 8.915870599999998,
                                19.4407156, 6.542876999999999, 19.7316396,
                                4.095542999999999);
    rr_renderer_line_to(renderer, 13.300742800000002, 3.288555239999999);
    rr_renderer_bezier_curve_to(renderer, 13.116790470000002, 4.945367939999999,
                                12.645683000000002, 6.552364439999999,
                                11.910053000000001, 8.03232964);
    rr_renderer_fill(renderer);
}

void crafting_toggle_button_on_event(struct rr_ui_element *this,
                                     struct rr_game *game)
{
    if (game->input_data->mouse_buttons_up_this_tick & 1)
    {
        if (game->pressed != this)
            return;
        if (game->menu_open == rr_game_menu_crafting)
            game->menu_open = rr_game_menu_none;
        else
            game->menu_open = rr_game_menu_crafting;
    }
    else
        rr_ui_render_tooltip_right(this, game->craft_tooltip, game);
}

struct rr_ui_element *rr_ui_crafting_toggle_button_init()
{
    struct rr_ui_element *this = rr_ui_element_init();
    rr_ui_set_background(this, 0x80888888);
    this->abs_width = this->abs_height = this->width = this->height = 60;
    this->on_event = crafting_toggle_button_on_event;
    this->on_render = crafting_toggle_on_render;
    return this;
}
