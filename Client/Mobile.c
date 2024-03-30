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

#include <Client/Mobile.h>

#include <Client/Game.h>
#include <Client/InputData.h>
#include <Client/Renderer/Renderer.h>
#include <Client/Socket.h>
#include <Shared/pb.h>

static uint8_t joystick_press = 255;
static uint8_t attack_press = 255;
static uint8_t defend_press = 255;

static void draw_mobile_joystick(struct rr_game *this,
                                 struct proto_bug *encoder)
{
    struct rr_renderer *renderer = this->renderer;
    struct rr_renderer_context_state state;
    rr_renderer_context_state_init(renderer, &state);
    rr_renderer_translate(renderer, 200 * renderer->scale,
                          renderer->height / 2);
    rr_renderer_scale(renderer, renderer->scale);
    rr_renderer_set_fill(renderer, 0x80000000);
    rr_renderer_begin_path(renderer);
    rr_renderer_arc(renderer, 0, 0, 100);
    rr_renderer_fill(renderer);
    float cx = 200 * renderer->scale;
    float cy = renderer->height / 2;
    if (joystick_press != 255 &&
        this->input_data->touches[joystick_press].active)
    {
        struct rr_input_touch *touch =
            &this->input_data->touches[joystick_press];
        struct rr_vector delta = {touch->touch_x - cx, touch->touch_y - cy};
        if (rr_vector_magnitude_cmp(&delta, 100 * renderer->scale) == 1)
            rr_vector_set_magnitude(&delta, 100 * renderer->scale);
        rr_renderer_set_fill(renderer, 0x80ffffff);
        rr_renderer_begin_path(renderer);
        rr_renderer_arc(renderer, delta.x, delta.y, 15);
        rr_renderer_fill(renderer);
        proto_bug_write_float32(encoder, delta.x, "mouse x");
        proto_bug_write_float32(encoder, delta.y, "mouse y");
    }
    else
    {
        joystick_press = 255;
        for (uint8_t i = 0; i < 16; ++i)
        {
            if (this->input_data->touches[i].active != 1)
                continue;
            struct rr_input_touch *touch = &this->input_data->touches[i];
            float x = touch->touch_x;
            float y = touch->touch_y;
            if ((x - cx) * (x - cx) + (y - cy) * (y - cy) <
                100 * 100 * renderer->scale * renderer->scale)
            {
                joystick_press = i;
                break;
            }
        }
        proto_bug_write_float32(encoder, 0, "mouse x");
        proto_bug_write_float32(encoder, 0, "mouse y");
    }
    rr_renderer_context_state_free(renderer, &state);
}

static uint8_t draw_mobile_attack_button(struct rr_game *this)
{
    struct rr_renderer *renderer = this->renderer;
    struct rr_renderer_context_state state;
    rr_renderer_context_state_init(renderer, &state);
    rr_renderer_translate(renderer, renderer->width - 250 * renderer->scale,
                          renderer->height / 2);
    rr_renderer_scale(renderer, renderer->scale);
    rr_renderer_set_fill(renderer, 0x80000000);
    rr_renderer_begin_path(renderer);
    rr_renderer_arc(renderer, 0, 0, 100);
    rr_renderer_fill(renderer);
    float cx = renderer->width - 250 * renderer->scale;
    float cy = renderer->height / 2;
    rr_renderer_context_state_free(renderer, &state);
    if (attack_press != 255 && this->input_data->touches[attack_press].active)
    {
        return 1;
    }
    else
    {
        attack_press = 255;
        for (uint8_t i = 0; i < 16; ++i)
        {
            if (this->input_data->touches[i].active != 1)
                continue;
            struct rr_input_touch *touch = &this->input_data->touches[i];
            float x = touch->touch_x;
            float y = touch->touch_y;
            if ((x - cx) * (x - cx) + (y - cy) * (y - cy) <
                100 * 100 * renderer->scale * renderer->scale)
            {
                attack_press = i;
                break;
            }
        }
        return 0;
    }
}

static uint8_t draw_mobile_defend_button(struct rr_game *this)
{
    struct rr_renderer *renderer = this->renderer;
    struct rr_renderer_context_state state;
    rr_renderer_context_state_init(renderer, &state);
    rr_renderer_translate(renderer, renderer->width - 100 * renderer->scale,
                          renderer->height / 2 + 100 * renderer->scale);
    rr_renderer_scale(renderer, renderer->scale);
    rr_renderer_set_fill(renderer, 0x80000000);
    rr_renderer_begin_path(renderer);
    rr_renderer_arc(renderer, 0, 0, 50);
    rr_renderer_fill(renderer);
    float cx = renderer->width - 100 * renderer->scale;
    float cy = renderer->height / 2 + 100 * renderer->scale;
    rr_renderer_context_state_free(renderer, &state);
    if (defend_press != 255 && this->input_data->touches[defend_press].active)
    {
        return 1;
    }
    else
    {
        defend_press = 255;
        for (uint8_t i = 0; i < 16; ++i)
        {
            if (this->input_data->touches[i].active != 1)
                continue;
            struct rr_input_touch *touch = &this->input_data->touches[i];
            float x = touch->touch_x;
            float y = touch->touch_y;
            if ((x - cx) * (x - cx) + (y - cy) * (y - cy) <
                50 * 50 * renderer->scale * renderer->scale)
            {
                defend_press = i;
                break;
            }
        }
        return 0;
    }
}

void rr_write_serverbound_packet_mobile(struct rr_game *this)
{
    struct proto_bug encoder;
    proto_bug_init(&encoder, RR_OUTGOING_PACKET);
    proto_bug_write_uint8(&encoder, rr_serverbound_input, "header");
    uint8_t is_attack = draw_mobile_attack_button(this);
    uint8_t is_defend = draw_mobile_defend_button(this);
    proto_bug_write_uint8(&encoder,
                          (1 << 6) | (is_attack << 4) | (is_defend << 5),
                          "movement kb flags");
    draw_mobile_joystick(this, &encoder);
    rr_websocket_send(&this->socket, encoder.current - encoder.start);
    return;
}
