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

#include <emscripten.h>
#include <stdlib.h>
#include <string.h>

#include <Client/DOM.h>
#include <Client/Game.h>
#include <Client/InputData.h>
#include <Client/Renderer/Renderer.h>

#include <Shared/Binary.h>
#include <Shared/Bitset.h>

struct rr_ui_text_input_metadata
{
    uint32_t *buffer; // 4n method
    char *out;
    uint32_t length;
    uint32_t max_length;
    uint32_t caret_pos;
    uint32_t drag_pos;
    uint8_t dragging;
    uint8_t focused;
};

static void text_input_on_hide(struct rr_ui_element *this, struct rr_game *game)
{
    struct rr_ui_text_input_metadata *data = this->data;
    // rr_dom_element_hide(data->name);
}

static void text_input_on_event(struct rr_ui_element *this,
                                struct rr_game *game)
{
    if (game->input_data->mouse_buttons_down_this_tick & 1)
    {
        struct rr_ui_text_input_metadata *data = this->data;
        data->focused = 1;
        data->dragging = 0;
    }
}

static void text_input_on_render(struct rr_ui_element *this,
                                 struct rr_game *game)
{
    struct rr_renderer_context_state state;
    struct rr_ui_text_input_metadata *data = this->data;
    struct rr_renderer *renderer = game->renderer;
    struct rr_input_data *input = game->input_data;
    struct rr_binary_encoder encoder;
    if (game->is_mobile)
    {
        if (data->focused)
        {
            data->length = EM_ASM_INT(
                {
                    let text = prompt();
                    if (!text)
                        return 0;
                    text = text.slice(0, $1);
                    for (let i = 0; i < text.length; ++i)
                        HEAP32[($0 + i * 4) >> 2] = text.charCodeAt(i);
                    return text.length;
                },
                data->buffer, data->max_length);
        }
        data->focused = 0;
    }
    else
    {
        if (input->mouse_buttons_down_this_tick & 1)
        {
            data->dragging = 0;
            if (!rr_ui_mouse_over(this, game))
                data->focused = 0;
            else if (data->focused)
            {
                float left_x =
                    this->abs_x - this->abs_width * 0.48 * renderer->scale;
                float diff = input->mouse_x - left_x;
                char buf[5];
                for (data->caret_pos = 0; data->caret_pos < data->length;
                     ++data->caret_pos)
                {
                    rr_binary_encoder_init(&encoder, (uint8_t *)buf);
                    rr_binary_encoder_write_utf8(&encoder,
                                                 data->buffer[data->caret_pos]);
                    rr_binary_encoder_write_utf8(&encoder, 0);
                    diff -= rr_renderer_get_text_size(buf) * this->abs_height *
                            0.8 * renderer->scale;
                    if (diff < 0)
                        break;
                }
            }
        }
        else if (input->mouse_buttons & 1 && data->focused)
        {
            float left_x =
                this->abs_x - this->abs_width * 0.48 * renderer->scale;
            float diff = input->mouse_x - left_x;
            char buf[5];
            for (data->drag_pos = 0; data->drag_pos < data->length;
                 ++data->drag_pos)
            {
                rr_binary_encoder_init(&encoder, (uint8_t *)buf);
                rr_binary_encoder_write_utf8(&encoder,
                                             data->buffer[data->drag_pos]);
                rr_binary_encoder_write_utf8(&encoder, 0);
                diff -= rr_renderer_get_text_size(buf) * this->abs_height *
                        0.8 * renderer->scale;
                if (diff < 0)
                    break;
            }
            data->dragging = 1;
        }
        if (data->focused)
        {
            if (rr_bitset_get(input->keys_pressed_this_tick, 8) &&
                data->caret_pos > 0 && !data->dragging)
            {
                for (uint32_t j = data->caret_pos; j < data->length; ++j)
                    data->buffer[j - 1] = data->buffer[j];
                --data->caret_pos;
                --data->length;
            }
            uint8_t ctrl_v = rr_bitset_get(input->keys_pressed, 17) &&
                             rr_bitset_get(input->keys_pressed_this_tick, 'V');
            if (data->dragging &&
                (input->keycodes_length ||
                 rr_bitset_get(input->keys_pressed_this_tick, 8) || ctrl_v))
            {
                data->dragging = 0;
                uint32_t min = data->caret_pos < data->drag_pos
                                   ? data->caret_pos
                                   : data->drag_pos;
                uint32_t len = data->caret_pos + data->drag_pos - 2 * min;
                for (uint32_t j = min + len; j < data->length; ++j)
                    data->buffer[j - len] = data->buffer[j];
                data->length -= len;
                data->caret_pos = min;
            }
            if (input->clipboard != NULL)
            {
                rr_binary_encoder_init(&encoder, (uint8_t *)input->clipboard);
                uint32_t clipboard_len = 0;
                while (rr_binary_encoder_read_utf8(&encoder))
                    ++clipboard_len;
                uint32_t start =
                    data->length + clipboard_len >= data->max_length
                        ? data->max_length
                        : data->length + clipboard_len;
                for (uint32_t j = start; j > data->caret_pos + clipboard_len;
                     --j)
                    data->buffer[j - 1] = data->buffer[j - clipboard_len - 1];

                rr_binary_encoder_init(&encoder, (uint8_t *)input->clipboard);
                data->length = start;
                while (data->caret_pos < data->length)
                {
                    uint32_t character = rr_binary_encoder_read_utf8(&encoder);
                    if (character == 0)
                        break;
                    data->buffer[data->caret_pos++] = character;
                }
            }
            else
                for (uint32_t i = 0; i < input->keycodes_length; ++i)
                {
                    if (data->length >= data->max_length)
                        break;
                    for (uint32_t j = data->length; j > data->caret_pos; --j)
                        data->buffer[j] = data->buffer[j - 1];
                    data->buffer[data->caret_pos++] =
                        input->keycodes_pressed_this_tick[i];
                    // printf("key pressed: %d\n",
                    // input->keycodes_pressed_this_tick[i]);
                    ++data->length;
                }
        }
        if (data->dragging && rr_bitset_get(input->keys_pressed, 17) &&
            rr_bitset_get(input->keys_pressed_this_tick, 'C'))
        {
            // ctrl c
            char out[100];
            uint32_t min = data->caret_pos < data->drag_pos ? data->caret_pos
                                                            : data->drag_pos;
            uint32_t len = data->caret_pos + data->drag_pos - 2 * min;
            rr_binary_encoder_init(&encoder, (uint8_t *)out);
            for (uint32_t i = min; i < min + len; ++i)
                rr_binary_encoder_write_utf8(&encoder, data->buffer[i]);
            rr_binary_encoder_write_utf8(&encoder, 0);
            rr_copy_string(out);
        }
    }
    // printf("text box length is %d %d\n", data->length, data->max_length);
    rr_renderer_scale(renderer, renderer->scale);
    rr_renderer_set_fill(renderer, 0xffffffff);
    rr_renderer_set_stroke(renderer, 0xff222222);
    rr_renderer_set_line_width(renderer, this->height * 0.12);
    rr_renderer_begin_path(renderer);
    rr_renderer_rect(renderer, -this->abs_width / 2, -this->abs_height / 2,
                     this->abs_width, this->abs_height);
    rr_renderer_stroke(renderer);
    rr_renderer_fill(renderer);
    rr_renderer_clip(renderer);
    if (data->dragging)
    {
        uint32_t min =
            data->caret_pos < data->drag_pos ? data->caret_pos : data->drag_pos;
        uint32_t max = data->caret_pos + data->drag_pos - min;
        float start_x = -this->abs_width * 0.48;
        float len = 0;
        char buf[5];
        for (uint32_t i = 0; i < min; ++i)
        {
            rr_binary_encoder_init(&encoder, (uint8_t *)buf);
            rr_binary_encoder_write_utf8(&encoder, data->buffer[i]);
            rr_binary_encoder_write_utf8(&encoder, 0);
            start_x += rr_renderer_get_text_size(buf) * this->abs_height * 0.8;
        }
        for (uint32_t i = min; i < max; ++i)
        {
            rr_binary_encoder_init(&encoder, (uint8_t *)buf);
            rr_binary_encoder_write_utf8(&encoder, data->buffer[i]);
            rr_binary_encoder_write_utf8(&encoder, 0);
            len += rr_renderer_get_text_size(buf) * this->abs_height * 0.8;
        }
        rr_renderer_set_fill(renderer, 0xff8888ff);
        rr_renderer_begin_path(renderer);
        rr_renderer_fill_rect(renderer, start_x, -this->abs_height * 0.48, len,
                              this->abs_height * 0.96);
        rr_renderer_set_fill(renderer, 0xffffffff);
    }
    rr_binary_encoder_init(&encoder, (uint8_t *)data->out);
    for (uint32_t i = 0; i < data->length; ++i)
        rr_binary_encoder_write_utf8(&encoder, data->buffer[i]);
    rr_binary_encoder_write_utf8(&encoder, 0);
    rr_renderer_set_text_size(renderer, this->height * 0.8);
    rr_renderer_set_text_align(renderer, 0);
    rr_renderer_set_text_baseline(renderer, 1);
    rr_renderer_set_line_width(renderer, this->height * 0.8 * 0.12);
    rr_renderer_stroke_text(renderer, data->out, -this->abs_width * 0.48, 0);
    rr_renderer_fill_text(renderer, data->out, -this->abs_width * 0.48, 0);
    if (!data->focused)
        return;
    float caret_x = 0;
    char buf[5];
    for (uint32_t i = 0; i < data->caret_pos; ++i)
    {
        rr_binary_encoder_init(&encoder, (uint8_t *)buf);
        rr_binary_encoder_write_utf8(&encoder, data->buffer[i]);
        rr_binary_encoder_write_utf8(&encoder, 0);
        caret_x += rr_renderer_get_text_size(buf) * this->abs_height * 0.8;
    }
    rr_renderer_set_line_width(renderer, 2);
    rr_renderer_begin_path(renderer);
    rr_renderer_move_to(renderer, -this->abs_width * 0.48 + caret_x,
                        -this->abs_height * 0.48);
    rr_renderer_line_to(renderer, -this->abs_width * 0.48 + caret_x,
                        this->abs_height * 0.48);
    rr_renderer_stroke(renderer);
}

struct rr_ui_element *rr_ui_text_input_init(float w, float h, char *text,
                                            uint32_t max_length)
{
    struct rr_ui_element *element = rr_ui_element_init();
    struct rr_ui_text_input_metadata *data = malloc(sizeof *data);
    memset(data, 0, sizeof *data);
    data->buffer = malloc(sizeof(uint32_t) * max_length);
    data->max_length = max_length;
    data->out = text;
    // data->name = name;
    element->data = data;
    element->abs_width = element->width = w;
    element->abs_height = element->height = h;
    element->on_render = text_input_on_render;
    element->on_event = text_input_on_event;
    // element->on_hide = text_input_on_hide;
    // rr_dom_create_text_element(data->name, 16);
    return element;
}