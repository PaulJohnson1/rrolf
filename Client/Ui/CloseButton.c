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

#include <Client/Game.h>
#include <Client/InputData.h>
#include <Client/Renderer/Renderer.h>
#include <Client/Ui/Engine.h>

#include <Shared/Utilities.h>

static void close_button_on_render(struct rr_ui_element *this,
                                   struct rr_game *game)
{
    struct rr_renderer *renderer = game->renderer;
    rr_renderer_scale(renderer, renderer->scale);
    if (rr_ui_mouse_over(this, game))
        rr_renderer_add_color_filter(renderer, 0xff000000, 0.2);
    rr_renderer_set_fill(renderer, this->fill);
    rr_renderer_round_rect(renderer, -this->abs_width / 2,
                           -this->abs_height / 2, this->abs_width,
                           this->abs_height, this->abs_height / 4);
    rr_renderer_fill(renderer);
    rr_renderer_set_line_width(renderer, this->abs_width / 6);
    rr_renderer_set_line_cap(renderer, 1);
    rr_renderer_set_stroke(renderer, 0xcfffffff);
    rr_renderer_begin_path(renderer);
    rr_renderer_move_to(renderer, -this->abs_width * 0.25,
                        -this->abs_height * 0.25);
    rr_renderer_line_to(renderer, this->abs_width * 0.25,
                        this->abs_height * 0.25);
    rr_renderer_move_to(renderer, -this->abs_width * 0.25,
                        this->abs_height * 0.25);
    rr_renderer_line_to(renderer, this->abs_width * 0.25,
                        -this->abs_height * 0.25);
    rr_renderer_stroke(renderer);
}

struct rr_ui_element *rr_ui_close_button_init(
    float w, void (*on_event)(struct rr_ui_element *, struct rr_game *))
{
    struct rr_ui_element *this = rr_ui_element_init();
    this->abs_width = this->abs_height = w;
    this->on_event = on_event;
    rr_ui_set_background(this, 0x80fc3434);
    this->on_render = close_button_on_render;
    return this;
}