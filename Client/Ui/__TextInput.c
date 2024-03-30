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

static uint32_t charlen(char *a)
{
    char *b = a;
    uint32_t len = 0;
    while (*b)
    {
        while ((unsigned char)*b >= 128)
            ++b;
        ++b;
        ++len;
    }
    return len;
}

static uint32_t charsize(uint32_t c)
{
    return c < 128 ? 1 : c < 128 << 7 ? 2 : c < 128 << 14 ? 3 : 4;
}

static void strinject(char *bufstart, char *seq, uint32_t utf8pos, uint32_t max)
{
    uint32_t injsize = charlen(seq);
    char *temp = alloca(max + injsize);
    memset(temp, 0, sizeof *temp);
    struct rr_binary_encoder reader;
    rr_binary_encoder_init(&reader, (uint8_t *)bufstart);
    for (uint32_t n = 0; n < utf8pos; ++n)
    {
        if (*reader.at == 0)
            break;
        uint8_t *at = reader.at;
        rr_binary_encoder_read_utf8(&reader);
        if (reader.at >= (uint8_t *)bufstart + max)
            *at = 0;
    }
    memcpy(temp, bufstart, reader.at - reader.start);
    memcpy(temp + (reader.at - reader.start), seq, injsize);
    memcpy(temp + (reader.at - reader.start) + injsize, reader.at,
           max - (reader.at - reader.start));
    memset(bufstart, 0, max);
    struct rr_binary_encoder writer;
    rr_binary_encoder_init(&writer, (uint8_t *)bufstart);
    rr_binary_encoder_init(&reader, (uint8_t *)temp);
    while (1)
    {
        uint32_t c = rr_binary_encoder_read_utf8(&reader);
        if (c == 0 || writer.at - writer.start + charsize(c) + 1 > max)
            break;
        rr_binary_encoder_write_utf8(&writer, c);
    }
    rr_binary_encoder_write_utf8(&writer, 0);
}

static void strremv(char *bufstart, uint32_t utf8pos, uint32_t rem_len,
                    uint32_t max)
{
    if (rem_len > utf8pos)
        rem_len = utf8pos;
    struct rr_binary_encoder reader;
    rr_binary_encoder_init(&reader, (uint8_t *)bufstart);
    for (uint32_t n = 0; n < utf8pos - rem_len; ++n)
    {
        if (*reader.at == 0)
            break;
        rr_binary_encoder_read_utf8(&reader);
    }
    char *s = (char *)reader.at;
    for (uint32_t n = utf8pos - rem_len; n < utf8pos; ++n)
    {
        if (*reader.at == 0)
            break;
        rr_binary_encoder_read_utf8(&reader);
    }
    char *e = (char *)reader.at;
    char *temp = alloca(max);
    memset(temp, 0, sizeof *temp);
    memcpy(temp, bufstart, s - e + max);
    memcpy(bufstart, temp, s - bufstart);
    memcpy(s, temp + (e - bufstart), max - (e - bufstart));
}

static void text_input_on_event(struct rr_ui_element *this,
                                struct rr_game *game)
{
    struct rr_ui_text_input_metadata *data = this->data;
    uint8_t mouse_over = rr_ui_mouse_over(this, game);
    if (game->input_data->mouse_buttons_up_this_tick & 1)
        data->focused = mouse_over;
}

static void text_input_on_render(struct rr_ui_element *this,
                                 struct rr_game *game)
{
    struct rr_input_data *input = game->input_data;
    struct rr_ui_text_input_metadata *data = this->data;
    struct rr_renderer *renderer = game->renderer;
    struct rr_binary_encoder encoder;
    rr_renderer_scale(renderer, renderer->scale);
    data->size = strlen(data->buffer);
    if (data->focused)
    {
        char a[5] = {0};
        for (uint32_t i = 0; i < input->keycodes_length; ++i)
        {
            ((uint32_t *)a)[0] = input->keycodes_pressed_this_tick[i];
            strinject(data->buffer, a, data->caret_pos, data->max_size);
            if (data->caret_pos < strlen(data->buffer))
                ++data->caret_pos;
        }
        if (rr_bitset_get(input->keys_pressed_this_tick, 8))
        {
            strremv(data->buffer, data->caret_pos, 1, data->max_size);
            if (data->caret_pos > 0)
                --data->caret_pos;
        }
        if (rr_bitset_get(input->keys_pressed_this_tick, 37))
            if (data->caret_pos > 0)
                --data->caret_pos;
        if (rr_bitset_get(input->keys_pressed_this_tick, 39))
            if (data->caret_pos < strlen(data->buffer))
                ++data->caret_pos;
    }
    if ((game->input_data->mouse_buttons_down_this_tick & 1) && data->focused)
    {
        float left_x = this->abs_x - this->abs_width * 0.48 * renderer->scale;
        float diff = input->mouse_x - left_x;
        char buf[5];
        for (data->caret_pos = 0; data->caret_pos < strlen(data->buffer);
             ++data->caret_pos)
        {
            rr_binary_encoder_init(&encoder, (uint8_t *)buf);
            rr_binary_encoder_write_utf8(&encoder,
                                         data->buffer[data->caret_pos]);
            rr_binary_encoder_write_utf8(&encoder, 0);
            diff -= rr_renderer_get_text_size(buf) * this->abs_height *
                    renderer->scale;
            if (diff < 0)
                break;
        }
    }
    rr_renderer_begin_path(renderer);
    rr_renderer_rect(renderer, -this->width / 2, -this->height / 2, this->width,
                     this->height);
    rr_renderer_clip(renderer);
    rr_binary_encoder_init(&encoder, (uint8_t *)data->buffer);
    for (uint32_t i = 0; i < data->caret_pos; ++i)
    {
        if (*encoder.at == 0)
            break;
        rr_binary_encoder_read_utf8(&encoder);
    }
    char repl = *encoder.at;
    *encoder.at = 0;
    float text_length =
        rr_renderer_get_text_size(data->buffer) * this->abs_height;
    data->relative_x =
        rr_fclamp(this->abs_width * 0.96 - text_length, -1000, 0);
    *encoder.at = repl;
    rr_renderer_translate(renderer, data->relative_x - this->abs_width * 0.48,
                          0); // positive is left
    rr_renderer_set_text_baseline(renderer, 1);
    rr_renderer_set_text_align(renderer, 0);
    rr_renderer_set_fill(renderer, this->fill);
    rr_renderer_set_stroke(renderer, this->stroke);
    rr_renderer_set_text_size(renderer, this->abs_height);
    rr_renderer_set_line_width(renderer, this->abs_height * 0.12);
    rr_renderer_stroke_text(renderer, data->buffer, 0, 0);
    rr_renderer_fill_text(renderer, data->buffer, 0, 0);
    if (data->focused)
    {
        rr_renderer_set_stroke(renderer, this->fill);
        rr_renderer_begin_path(renderer);
        rr_renderer_move_to(renderer, text_length, -this->abs_height * 0.5);
        rr_renderer_line_to(renderer, text_length, this->abs_height * 0.5);
        rr_renderer_stroke(renderer);
    }
    if (game->is_mobile)
    {
        if (rr_ui_mouse_over(this, game) &&
            (game->input_data->mouse_buttons_down_this_tick & 1))
        {
            EM_ASM(
                {
                    const str = prompt();
                    const arr =
                        new TextEncoder().encode(str + '/x00').slice(0, $1);
                    HEAPU8.set(arr, $0);
                },
                data->buffer, data->size);
        }
    }
}

struct rr_ui_element *rr__ui_text_input_init(float w, float h, char *text,
                                             uint8_t max_length, char *name)
{
    struct rr_ui_element *this = rr_ui_element_init();
    struct rr_ui_text_input_metadata *data = malloc(sizeof *data);
    memset(data, 0, sizeof *data);
    data->max_size = max_length;
    data->buffer = text;
    this->data = data;
    this->abs_width = this->width = w;
    this->abs_height = this->height = h;
    this->on_render = text_input_on_render;
    this->on_event = text_input_on_event;
    this->animate = rr_ui_instant_hide_animate;
    this->fill = 0xff222222;
    this->stroke = 0xffffffff;
    return this;
}