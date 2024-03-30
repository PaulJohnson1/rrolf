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
#include <Client/Ui/Engine.h>

struct text_input_metadata
{
    char *name;
    char *text;
    uint8_t max;
};

static void text_input_on_hide(struct rr_ui_element *this, struct rr_game *game)
{
    struct text_input_metadata *data = this->data;
    rr_dom_element_hide(data->name);
}

static void text_input_on_render(struct rr_ui_element *this,
                                 struct rr_game *game)
{
    struct rr_renderer_context_state state;
    struct text_input_metadata *data = this->data;
    struct rr_renderer *renderer = game->renderer;
    rr_dom_element_show(data->name);
    rr_dom_element_update_position(data->name, this->abs_x, this->abs_y,
                                   this->abs_width * renderer->scale *
                                       renderer->state.transform_matrix[0],
                                   this->abs_height * renderer->scale *
                                       renderer->state.transform_matrix[4]);
    rr_dom_retrieve_text(data->name, data->text, data->max);
    rr_renderer_scale(renderer, renderer->scale);
    if (this->fill)
    {
        rr_renderer_set_fill(renderer, this->fill);
        rr_renderer_set_stroke(renderer, 0xff222222);
        rr_renderer_set_line_width(renderer, this->height * 0.12);
        rr_renderer_begin_path(renderer);
        rr_renderer_fill_rect(renderer, -this->width / 2, -this->height / 2,
                              this->width, this->height);
        rr_renderer_stroke_rect(renderer, -this->width / 2, -this->height / 2,
                                this->width, this->height);
    }
    if (game->is_mobile)
    {
        if (rr_ui_mouse_over(this, game) &&
            (game->input_data->mouse_buttons_down_this_tick & 1))
        {
            EM_ASM(
                {
                    const element = document.getElementById(UTF8ToString($0));
                    element.value = prompt();
                },
                data->name);
        }
    }
    return;
}

struct rr_ui_element *rr_ui_text_input_init(float w, float h, char *text,
                                            uint32_t max_length, char *name)
{
    struct rr_ui_element *this = rr_ui_element_init();
    struct text_input_metadata *data = malloc(sizeof *data);
    memset(data, 0, sizeof *data);

    data->max = max_length;
    data->text = text;
    data->name = name;
    this->data = data;
    rr_ui_set_background(this, 0xffffffff);
    this->abs_width = this->width = w;
    this->abs_height = this->height = h;
    this->on_render = text_input_on_render;
    this->on_hide = text_input_on_hide;
    this->animate = rr_ui_instant_hide_animate;
    rr_dom_create_text_element(data->name, 16);
    return this;
}