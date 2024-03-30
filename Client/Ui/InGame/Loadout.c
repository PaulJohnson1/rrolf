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
#include <stdio.h>
#include <stdlib.h>
#include <string.h>

#include <Client/Assets/RenderFunctions.h>
#include <Client/Game.h>
#include <Client/InputData.h>
#include <Client/Renderer/Renderer.h>

#include <Client/Ui/Engine.h>

#include <Shared/SimulationCommon.h>
#include <Shared/Utilities.h>
#include <Shared/pb.h>

struct loadout_button_metadata
{
    uint8_t pos;
    uint8_t prev_id;
    uint8_t prev_rarity;
    float secondary_animation;
    float lerp_cd;
};

static void loadout_button_on_event(struct rr_ui_element *this,
                                    struct rr_game *game)
{
    struct loadout_button_metadata *data = this->data;
    if ((game->input_data->mouse_buttons_up_this_tick & 1) &&
        game->pressed == this)
    {
        game->cache.loadout[data->pos].id = 0;
        game->cache.loadout[data->pos].rarity = 0;
    }
    else
    {
        if (game->cache.loadout[data->pos].id == 0)
            return;
        rr_ui_render_tooltip_above(
            this, game->petal_tooltips[data->prev_id][data->prev_rarity], game);
    }
}

static void petal_switch_button_event(struct rr_ui_element *this,
                                      struct rr_game *game)
{
    struct loadout_button_metadata *data = this->data;
    if (game->input_data->mouse_buttons_up_this_tick & 1 &&
        game->pressed == this) // mouse_down
    {
        struct proto_bug encoder;
        proto_bug_init(&encoder, RR_OUTGOING_PACKET);
        proto_bug_write_uint8(&encoder, rr_serverbound_petal_switch, "header");
        proto_bug_write_uint8(&encoder, (data->pos % 10) + 1, "petal switch");
        proto_bug_write_uint8(&encoder, 0, "petal switch");
        rr_websocket_send(&game->socket, encoder.current - encoder.start);
    }
    else
    {
        struct rr_component_player_info *player_info = game->player_info;
        struct rr_component_player_info_petal_slot *slot =
            data->pos < 10 ? &player_info->slots[data->pos]
                           : &player_info->secondary_slots[data->pos - 10];
        uint8_t id = slot->id;
        uint8_t rarity = slot->rarity;
        if (id == 0)
            return;
        rr_ui_render_tooltip_above(this, game->petal_tooltips[id][rarity],
                                   game);
    }
}

static uint8_t
title_screen_loadout_button_should_show(struct rr_ui_element *this,
                                        struct rr_game *game)
{
    struct loadout_button_metadata *data = this->data;
    return !game->simulation_ready && data->pos % 10 < game->slots_unlocked;
}

static void title_screen_loadout_button_animate(struct rr_ui_element *this,
                                                struct rr_game *game)
{
    struct loadout_button_metadata *data = this->data;
    if (this->completely_hidden)
        return;
    struct rr_renderer *renderer = game->renderer;
    this->width = this->abs_width * (1 - this->animation);
    this->height = this->abs_height * (1 - this->animation);
    rr_renderer_scale(game->renderer, (1 - this->animation));
    rr_renderer_scale(renderer, renderer->scale * this->width / 60);
    rr_renderer_draw_background(renderer, rr_rarity_id_max + 1, 1);
    uint8_t id = game->cache.loadout[data->pos].id;
    uint8_t rarity = game->cache.loadout[data->pos].rarity;
    data->secondary_animation =
        rr_lerp(data->secondary_animation, id == 0, 0.2);
    if (id != 0)
    {
        data->prev_id = id;
        data->prev_rarity = rarity;
    }
    rr_renderer_scale(game->renderer, (1 - data->secondary_animation));
}

static uint8_t loadout_button_should_show(struct rr_ui_element *this,
                                          struct rr_game *game)
{
    if (!game->simulation_ready)
        return 0;
    struct rr_component_player_info *player_info = game->player_info;
    struct loadout_button_metadata *data = this->data;
    return player_info->slot_count > data->pos % 10;
}

static uint8_t secondary_loadout_should_show(struct rr_ui_element *this,
                                             struct rr_game *game)
{
    return this->elements.start[0]->should_show(this->elements.start[0], game);
}

static void loadout_button_animate(struct rr_ui_element *this,
                                   struct rr_game *game)
{
    if (this->completely_hidden)
        return;
    struct rr_component_player_info *player_info = game->player_info;
    struct loadout_button_metadata *data = this->data;
    struct rr_renderer *renderer = game->renderer;
    this->width = this->abs_width * (1 - this->animation);
    this->height = this->abs_height * (1 - this->animation);
    rr_renderer_scale(game->renderer, (1 - this->animation));
    rr_renderer_scale(renderer, renderer->scale * this->width / 60);
    rr_renderer_draw_background(renderer, rr_rarity_id_max + 1, 1);
    struct rr_component_player_info_petal_slot *slot =
        data->pos < 10 ? &player_info->slots[data->pos]
                       : &player_info->secondary_slots[data->pos - 10];
    uint8_t id = slot->id;
    uint8_t rarity = slot->rarity;
    data->secondary_animation = rr_lerp(
        data->secondary_animation,
        id != data->prev_id || rarity != data->prev_rarity || id == 0, 0.2);
    if (id != 0)
    {
        data->prev_id = id;
        data->prev_rarity = rarity;
    }
    if (data->lerp_cd < slot->client_cooldown)
        data->lerp_cd = slot->client_cooldown * (1.0f / 255);
    else
        data->lerp_cd =
            rr_lerp(data->lerp_cd, slot->client_cooldown * (1.0f / 255), 0.2);
    rr_renderer_scale(game->renderer, (1 - data->secondary_animation));
}

static void title_screen_loadout_button_on_render(struct rr_ui_element *this,
                                                  struct rr_game *game)
{
    struct loadout_button_metadata *data = this->data;
    struct rr_renderer *renderer = game->renderer;
    rr_renderer_draw_background(renderer, data->prev_rarity, 1);
    rr_renderer_draw_petal_with_name(renderer, data->prev_id,
                                     data->prev_rarity);
}

static void loadout_button_on_render(struct rr_ui_element *this,
                                     struct rr_game *game)
{
    struct loadout_button_metadata *data = this->data;
    struct rr_renderer *renderer = game->renderer;
    float pct = data->lerp_cd * data->lerp_cd * (3 - 2 * data->lerp_cd);
    rr_renderer_draw_background(renderer, data->prev_rarity, 1);
    if (data->pos < 10)
    {
        rr_renderer_set_fill(renderer, 0x40000000);
        rr_renderer_begin_path(renderer);
        rr_renderer_move_to(renderer, 0, 0);
        rr_renderer_partial_arc(renderer, 0, 0, 90, -M_PI / 2 - pct * M_PI * 10,
                                -M_PI / 2 - pct * M_PI * 8, 0);
        rr_renderer_fill(renderer);
    }
    rr_renderer_draw_petal_with_name(renderer, data->prev_id,
                                     data->prev_rarity);
}

struct rr_ui_element *rr_ui_title_screen_loadout_button_init(uint8_t pos)
{
    struct rr_ui_element *this = rr_ui_element_init();
    struct loadout_button_metadata *data = malloc(sizeof *data);
    data->pos = pos;
    data->prev_id = 0;
    data->prev_rarity = 0;
    data->secondary_animation = 1;
    this->data = data;
    this->abs_width = this->width = pos < 10 ? 60 : 50;
    this->abs_height = this->height = pos < 10 ? 60 : 50;
    this->on_render = title_screen_loadout_button_on_render;
    this->animate = title_screen_loadout_button_animate;
    this->should_show = title_screen_loadout_button_should_show;
    this->on_event = loadout_button_on_event;
    return this;
}

struct rr_ui_element *rr_ui_loadout_button_init(uint8_t pos)
{
    struct rr_ui_element *this = rr_ui_element_init();
    struct loadout_button_metadata *data = malloc(sizeof *data);
    data->pos = pos;
    data->prev_id = 0;
    data->prev_rarity = 0;
    data->secondary_animation = 1;
    data->lerp_cd = 0;
    this->data = data;
    this->abs_width = this->width = pos < 10 ? 60 : 50;
    this->abs_height = this->height = pos < 10 ? 60 : 50;
    this->on_render = loadout_button_on_render;
    this->animate = loadout_button_animate;
    this->should_show = loadout_button_should_show;
    this->on_event = petal_switch_button_event;
    return this;
}

struct rr_ui_element *rr_ui_secondary_loadout_button_init(uint8_t pos)
{
    struct rr_ui_element *this = rr_ui_loadout_button_init(pos + 10);
    char *text = pos == 0   ? "[1]"
                 : pos == 1 ? "[2]"
                 : pos == 2 ? "[3]"
                 : pos == 3 ? "[4]"
                 : pos == 4 ? "[5]"
                 : pos == 5 ? "[6]"
                 : pos == 6 ? "[7]"
                 : pos == 7 ? "[8]"
                 : pos == 8 ? "[9]"
                            : "[0]";
    struct rr_ui_element *c =
        rr_ui_v_container_init(rr_ui_container_init(), 0, 10, this,
                               rr_ui_text_init(text, 14, 0xffffffff), NULL);
    c->should_show = secondary_loadout_should_show;
    return c;
}