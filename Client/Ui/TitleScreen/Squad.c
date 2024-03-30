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
#include <Client/DOM.h>
#include <Client/Game.h>
#include <Client/InputData.h>
#include <Client/Renderer/Renderer.h>
#include <Client/Simulation.h>
#include <Client/Ui/Engine.h>

#include <Shared/Api.h>
#include <Shared/Rivet.h>
#include <Shared/Squad.h>
#include <Shared/Utilities.h>
#include <Shared/pb.h>

struct squad_flower_metadata
{
    float mouth;
    struct rr_squad_member *member;
};

struct squad_pos_metadata
{
    uint8_t pos;
};

void render_flower(struct rr_ui_element *element, struct rr_game *game)
{
    struct rr_renderer *renderer = game->renderer;
    struct squad_flower_metadata *data = element->data;
    if (data->member->is_dev)
        rr_renderer_rotate(renderer, -M_PI);
    rr_renderer_scale(renderer, renderer->scale);
    rr_renderer_set_stroke(renderer, 0xffcfbb50);
    rr_renderer_set_fill(renderer, 0xffffe763);
    rr_renderer_set_line_width(renderer, 3);
    rr_renderer_begin_path(renderer);
    rr_renderer_arc(renderer, 0, 0, 25);
    rr_renderer_fill(renderer);
    rr_renderer_stroke(renderer);
    struct rr_renderer_context_state state;
    rr_renderer_context_state_init(renderer, &state);
    rr_renderer_set_fill(renderer, 0xff222222);
    rr_renderer_begin_path(renderer);
    rr_renderer_ellipse(renderer, -7, -5, 3.25, 6.5);
    rr_renderer_fill(renderer);
    rr_renderer_begin_path(renderer);
    rr_renderer_ellipse(renderer, 7, -5, 3.25, 6.5);
    rr_renderer_fill(renderer);
    rr_renderer_begin_path(renderer);
    rr_renderer_ellipse(renderer, -7, -5, 3, 6);
    rr_renderer_ellipse(renderer, 7, -5, 3, 6);
    rr_renderer_clip(renderer);
    rr_renderer_set_fill(renderer, 0xffffffff);
    rr_renderer_begin_path(renderer);
    rr_renderer_arc(renderer, -7 + 3, -5 + 0, 3);
    rr_renderer_fill(renderer);
    rr_renderer_begin_path(renderer);
    rr_renderer_arc(renderer, 7 + 3, -5 + 0, 3);
    rr_renderer_fill(renderer);
    rr_renderer_context_state_free(renderer, &state);
    rr_renderer_set_stroke(renderer, 0xff222222);
    rr_renderer_set_line_width(renderer, 1.5);
    rr_renderer_set_line_cap(renderer, 1);
    rr_renderer_begin_path(renderer);
    rr_renderer_move_to(renderer, -6, 10);
    rr_renderer_quadratic_curve_to(renderer, 0, 5 + data->mouth * 10, 6, 10);
    rr_renderer_stroke(renderer);
}

static void flower_animate(struct rr_ui_element *this, struct rr_game *game)
{
    struct squad_flower_metadata *data = this->data;
    data->mouth = rr_lerp(data->mouth, (data->member->playing), 0.4);
}

static uint8_t choose(struct rr_ui_element *this, struct rr_game *game)
{
    struct rr_ui_choose_element_metadata *data = this->data;
    struct rr_squad_member *member = data->data;
    return member->in_use;
}

static struct rr_ui_element *rr_ui_flower_init(struct rr_squad_member *member,
                                               float size)
{
    struct rr_ui_element *this = rr_ui_element_init();
    struct squad_flower_metadata *data = malloc(sizeof *data);
    data->mouth = 0;
    data->member = member;
    this->data = data;
    this->width = this->abs_width = this->height = this->abs_height = size;

    this->on_render = render_flower;
    this->animate = flower_animate;
    return this;
}

struct squad_loadout_button_metadata
{
    struct rr_id_rarity_pair *petal;
    uint8_t prev_id;
    uint8_t prev_rarity;
};

static uint8_t squad_loadout_button_should_show(struct rr_ui_element *this,
                                                struct rr_game *game)
{
    struct squad_loadout_button_metadata *data = this->data;
    return data->petal->id;
}

static void squad_loadout_button_animate(struct rr_ui_element *this,
                                         struct rr_game *game)
{
    struct squad_loadout_button_metadata *data = this->data;
    if (data->petal->id != 0)
    {
        data->prev_id = data->petal->id;
        data->prev_rarity = data->petal->rarity;
    }
    rr_renderer_scale(game->renderer, (1 - this->animation));
}

static void squad_loadout_button_on_render(struct rr_ui_element *this,
                                           struct rr_game *game)
{
    struct squad_loadout_button_metadata *data = this->data;
    struct rr_renderer *renderer = game->renderer;
    rr_renderer_scale(renderer, renderer->scale * this->width / 60);
    rr_renderer_draw_background(renderer, data->prev_rarity, 1);
    rr_renderer_draw_static_petal(renderer, data->prev_id, data->prev_rarity,
                                  1);
}

static struct rr_ui_element *
squad_loadout_button_init(struct rr_id_rarity_pair *petal)
{
    struct rr_ui_element *this = rr_ui_element_init();
    struct squad_loadout_button_metadata *data = malloc(sizeof *data);
    data->petal = petal;
    data->prev_id = 0;
    this->data = data;
    this->abs_width = this->width = 16;
    this->abs_height = this->height = 16;
    this->on_render = squad_loadout_button_on_render;
    this->animate = squad_loadout_button_animate;
    this->should_show = squad_loadout_button_should_show;
    return this;
}

static void background_change_animate(struct rr_ui_element *this,
                                      struct rr_game *game)
{
    struct rr_ui_choose_element_metadata *data = this->data;
    if (data->choose(this, game))
    {
        struct rr_squad_member *member = data->data;
        if (member->playing)
            this->container->fill = 0x4023ff45;
        else
            this->container->fill = 0x40ff4523;
    }
    else
        this->container->fill = 0x40000000;
}

static void squad_container_on_event(struct rr_ui_element *this,
                                     struct rr_game *game)
{
    struct rr_ui_container_metadata *data = this->data;
    struct rr_squad_member *member = data->data;
    if (member->tooltip == NULL)
        return;
    rr_ui_render_tooltip_above(this, member->tooltip, game);
}

static uint8_t kick_player_should_slow(struct rr_ui_element *this,
                                       struct rr_game *game)
{
    struct squad_pos_metadata *data = this->data;
    uint8_t p = data->pos;
    if (game->squad.squad_members[game->squad.squad_pos].is_dev)
        return 1;
    if (game->squad.squad_members[p].is_dev)
        return 0;
    if (p == 0)
        return 0;
    if (!game->squad.squad_private)
        return 0;
    if (game->squad.squad_pos != 0)
        return 0;

    return 1;
}

static void kick_player_on_event(struct rr_ui_element *this,
                                 struct rr_game *game)
{
    if (game->input_data->mouse_buttons_up_this_tick & 1)
    {
        struct squad_pos_metadata *data = this->data;
        struct proto_bug encoder;
        proto_bug_init(&encoder, RR_OUTGOING_PACKET);
        proto_bug_write_uint8(&encoder, rr_serverbound_squad_kick, "header");
        proto_bug_write_uint8(&encoder, data->pos, "kick pos");
        rr_websocket_send(&game->socket, encoder.current - encoder.start);
    }
}

static struct rr_ui_element *kick_player_button_init(uint8_t pos)
{
    struct rr_ui_element *this =
        rr_ui_close_button_init(20, kick_player_on_event);
    this->no_reposition = 1;
    this->should_show = kick_player_should_slow;
    rr_ui_pad(rr_ui_set_justify(this, 1, -1), 5);
    struct squad_pos_metadata *data = malloc(sizeof *data);
    data->pos = pos;
    this->data = data;
    return this;
}

struct rr_ui_element *squad_player_container_init(struct rr_game_squad *squad,
                                                  uint8_t pos)
{
    struct rr_squad_member *member = &squad->squad_members[pos];
    struct rr_ui_element *b = rr_ui_text_init("Empty", 15, 0xffffffff);
    struct rr_ui_element *loadout = rr_ui_2d_container_init(4, 5, 0, 5);
    for (uint8_t i = 0; i < 20; ++i)
        rr_ui_container_add_element(
            loadout,
            rr_ui_set_justify(squad_loadout_button_init(&member->loadout[i]),
                              -1, -1));
    struct rr_ui_element *top = rr_ui_v_container_init(
        rr_ui_container_init(), 0, 10, rr_ui_flower_init(member, 50),
        rr_ui_text_init(member->nickname, 14, 0xffffffff), NULL);
    rr_ui_v_pad(rr_ui_set_justify(top, 0, -1), 10);
    rr_ui_v_pad(rr_ui_set_justify(loadout, 0, 1), 10);
    top->prevent_on_event = loadout->prevent_on_event = 1;
    struct rr_ui_element *squad_container = rr_ui_container_init();
    squad_container->abs_width = squad_container->width = 120;
    squad_container->abs_height = squad_container->height = 120;
    rr_ui_container_add_element(squad_container, loadout);
    rr_ui_container_add_element(squad_container, top);
    rr_ui_container_add_element(squad_container, kick_player_button_init(pos));
    squad_container->on_event = squad_container_on_event;
    squad_container->resizeable = 0;
    struct rr_ui_container_metadata *d_data = squad_container->data;
    d_data->data = member;
    struct rr_ui_element *this =
        rr_ui_choose_element_init(squad_container, b, choose);
    rr_ui_choose_container_set(this);
    struct rr_ui_choose_element_metadata *data = this->data;
    data->data = member;
    this->animate = background_change_animate;

    return rr_ui_set_background(
        rr_ui_v_container_init(rr_ui_container_init(), 0, 10, this, NULL),
        0x40ffffff);
}

static uint8_t squad_container_should_show(struct rr_ui_element *this,
                                           struct rr_game *game)
{
    struct rr_game_squad *squad = this->data;
    for (uint32_t i = 0; i < RR_SQUAD_MEMBER_COUNT; ++i)
        if (squad->squad_members[i].in_use)
            return 1;
    return 0;
}

struct rr_ui_element *rr_ui_squad_container_init(struct rr_game_squad *squad)
{
    struct rr_ui_element *this = rr_ui_v_container_init(
        rr_ui_container_init(), 0, 10,
        rr_ui_h_container_init(rr_ui_container_init(), 0, 10,
                               squad_player_container_init(squad, 0),
                               squad_player_container_init(squad, 1),
                               squad_player_container_init(squad, 2),
                               squad_player_container_init(squad, 3), NULL),
        rr_ui_set_justify(
            rr_ui_h_container_init(
                rr_ui_container_init(), 0, 0,
                rr_ui_text_init("Code: ", 16, 0xffffffff),
                rr_ui_text_init(squad->squad_code, 16, 0xffffffff), NULL),
            -1, -1),
        NULL);
    this->data = squad;
    this->should_show = squad_container_should_show;
    return this;
}

static void ready_button_animate(struct rr_ui_element *this,
                                 struct rr_game *game)
{
    rr_ui_default_animate(this, game);
    struct rr_ui_labeled_button_metadata *data = this->data;
    if (!game->socket_ready)
        rr_ui_set_background(this, 0x80999999);
    else
        rr_ui_set_background(this, 0x80d4b30c);
}

static void join_button_on_event(struct rr_ui_element *this,
                                 struct rr_game *game)
{
    if (game->input_data->mouse_buttons_up_this_tick & 1)
    {
        if (game->socket_ready)
        {
            struct proto_bug encoder;
            proto_bug_init(&encoder, RR_OUTGOING_PACKET);
            proto_bug_write_uint8(&encoder, rr_serverbound_squad_ready,
                                  "header");
            rr_websocket_send(&game->socket, encoder.current - encoder.start);
        }
    }
}

static void copy_code_on_event(struct rr_ui_element *this, struct rr_game *game)
{
    if (game->input_data->mouse_buttons_up_this_tick & 1)
        if (game->socket_ready)
            rr_copy_string(game->squad.squad_code);
}

static void toggle_private_on_event(struct rr_ui_element *this,
                                    struct rr_game *game)
{
    if (game->input_data->mouse_buttons_up_this_tick & 1)
    {
        if (game->socket_ready && game->squad.squad_private)
        {
            struct proto_bug encoder;
            proto_bug_init(&encoder, RR_OUTGOING_PACKET);
            proto_bug_write_uint8(&encoder, rr_serverbound_private_update,
                                  "header");
            rr_websocket_send(&game->socket, encoder.current - encoder.start);
        }
    }
}

static void join_code_on_event(struct rr_ui_element *this, struct rr_game *game)
{
    if (game->input_data->mouse_buttons_up_this_tick & 1)
    {
        if (game->socket_pending)
            return;
        game->socket_pending = 1;
#ifdef RIVET_BUILD
        {
            if (game->socket_ready)
                rr_websocket_disconnect(&game->socket, game);
            char server[16] = {0};
            char *link = server;
            char *code = game->connect_code;
            while (*code != 0 && *code != '-')
                *link++ = *code++;
            rr_api_get_server_alias(server, game);
        }
#endif
        struct proto_bug encoder2;
        proto_bug_init(&encoder2, RR_OUTGOING_PACKET);
        proto_bug_write_uint8(&encoder2, rr_serverbound_squad_join, "header");
        proto_bug_write_uint8(&encoder2, 1, "join type");
        char *code = game->connect_code;
        while (*code != 0 && *code != '-')
            ++code;
        ++code;
        proto_bug_write_string(&encoder2, code, 7, "connect link");

        rr_websocket_queue_send(&game->socket,
                                encoder2.current - encoder2.start);
        game->connect_code[0] = 0;
    }
}

static void squad_join_button_on_event(struct rr_ui_element *this,
                                       struct rr_game *game)
{
    struct rr_ui_labeled_button_metadata *data = this->data;
    if (game->input_data->mouse_buttons_up_this_tick & 1)
    {
        if (game->socket_ready)
        {
            struct proto_bug encoder2;
            proto_bug_init(&encoder2, RR_OUTGOING_PACKET);
            proto_bug_write_uint8(&encoder2, rr_serverbound_squad_join,
                                  "header");
            proto_bug_write_uint8(&encoder2, 0, "join type");

            rr_websocket_send(&game->socket, encoder2.current - encoder2.start);
        }
    }
}

static void squad_create_button_on_event(struct rr_ui_element *this,
                                         struct rr_game *game)
{
    struct rr_ui_labeled_button_metadata *data = this->data;
    if (game->input_data->mouse_buttons_up_this_tick & 1)
    {
        if (game->socket_ready)
        {
            struct proto_bug encoder2;
            proto_bug_init(&encoder2, RR_OUTGOING_PACKET);
            proto_bug_write_uint8(&encoder2, rr_serverbound_squad_join,
                                  "header");
            proto_bug_write_uint8(&encoder2, 2, "join type");

            rr_websocket_send(&game->socket, encoder2.current - encoder2.start);
        }
    }
}

static uint8_t copy_button_should_show(struct rr_ui_element *this,
                                       struct rr_game *game)
{
    return !game->socket_error;
}

struct rr_ui_element *rr_ui_squad_button_init()
{
    struct rr_ui_element *this = rr_ui_labeled_button_init("Find Squad", 36, 0);
    this->animate = ready_button_animate;
    this->on_event = squad_join_button_on_event;
    return this;
}

struct rr_ui_element *rr_ui_create_squad_button_init()
{
    struct rr_ui_element *this =
        rr_ui_labeled_button_init("Create Squad", 36, 0);
    this->animate = ready_button_animate;
    this->on_event = squad_create_button_on_event;
    return this;
}

struct rr_ui_element *rr_ui_join_button_init()
{
    struct rr_ui_element *this = rr_ui_labeled_button_init("Enter Game", 36, 0);
    this->animate = ready_button_animate;
    this->on_event = join_button_on_event;
    return this;
}

struct rr_ui_element *rr_ui_copy_squad_code_button_init()
{
    struct rr_ui_element *this = rr_ui_labeled_button_init("Copy Code", 24, 0);
    this->animate = ready_button_animate;
    this->on_event = copy_code_on_event;
    this->should_show = copy_button_should_show;
    return this;
}

struct rr_ui_element *rr_ui_join_squad_code_button_init()
{
    struct rr_ui_element *this = rr_ui_labeled_button_init("Join", 24, 0);
    rr_ui_set_background(this, 0x80d4b30c);
    this->on_event = join_code_on_event;
    return this;
}

struct rr_ui_element *rr_ui_toggle_private_button_init(struct rr_game *game)
{
    struct rr_ui_element *this =
        rr_ui_toggle_box_init(&game->squad.squad_private);
    this->on_event = toggle_private_on_event;
    return this;
}
