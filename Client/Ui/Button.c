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

#include <Shared/pb.h>

static void button_on_event(struct rr_ui_element *this, struct rr_game *game)
{
    struct rr_ui_labeled_button_metadata *data = this->data;
    if (game->input_data->mouse_buttons_up_this_tick & 1 &&
        data->toggle != NULL)
        (*(data->toggle)) ^= 1;
}

static void labeled_button_on_render(struct rr_ui_element *this,
                                     struct rr_game *game)
{
    struct rr_ui_labeled_button_metadata *data = this->data;
    struct rr_renderer *renderer = game->renderer;
    if (rr_ui_mouse_over(this, game))
        rr_renderer_add_color_filter(renderer, 0xff000000, 0.2);

    this->abs_width =
        15 + rr_renderer_get_text_size(data->text) * this->abs_height / 2;
    if (this->abs_width < this->abs_height)
        this->abs_width = this->abs_height;
    rr_renderer_scale(renderer, renderer->scale);
    rr_renderer_set_fill(renderer, this->fill);
    rr_renderer_set_line_width(renderer, this->abs_height / 8);
    rr_renderer_begin_path(renderer);
    rr_renderer_round_rect(renderer, -this->abs_width / 2,
                           -this->abs_height / 2, this->abs_width,
                           this->abs_height, 6);
    rr_renderer_fill(renderer);
    if (this->fill >= 0xff000000)
    {
        rr_renderer_add_color_filter(renderer, 0xff000000, 0.2);
        rr_renderer_set_stroke(renderer, this->fill);
        rr_renderer_stroke(renderer);
    }
    rr_renderer_set_text_baseline(renderer, 1);
    rr_renderer_set_text_align(renderer, 1);
    renderer->state.filter.amount = 0;
    rr_renderer_set_fill(renderer, 0xffffffff);
    rr_renderer_set_stroke(renderer, 0xff222222);
    rr_renderer_set_text_size(renderer, this->abs_height / 2);
    rr_renderer_set_line_width(renderer, this->abs_height / 2 * 0.12);
    rr_renderer_begin_path(renderer);
    rr_renderer_stroke_text(renderer, data->text, 0, 0);
    rr_renderer_fill_text(renderer, data->text, 0, 0);
}

struct rr_ui_element *rr_ui_labeled_button_init(char *text, float height,
                                                uint8_t *toggle)
{
    struct rr_ui_element *this = rr_ui_element_init();
    struct rr_ui_labeled_button_metadata *data = malloc(sizeof *data);
    data->toggle = toggle;
    data->text = text;
    this->data = data;
    this->abs_height = this->height = height;
    this->abs_width = this->width =
        15 + rr_renderer_get_text_size(text) * height / 2;
    this->on_render = labeled_button_on_render;
    this->on_event = button_on_event;
    rr_ui_set_background(this, 0xff000000);
    return this;
}