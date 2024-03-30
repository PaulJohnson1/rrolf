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

#include <Client/Game.h>
#include <Client/InputData.h>
#include <Client/Renderer/Renderer.h>

#include <Shared/Utilities.h>

struct scroll_container_metadata
{
    float y;
    float lerp_y;
    uint8_t scroll_focus;
};

static void scroll_container_poll_events(struct rr_ui_element *this,
                                         struct rr_game *game)
{
    if (this->completely_hidden)
        return;
    rr_ui_element_check_if_focused(this, game);
    if (game->focused != this)
        return;
    struct scroll_container_metadata *data = this->data;
    this->elements.start[0]->poll_events(this->elements.start[0], game);
}

static void scroll_container_on_render(struct rr_ui_element *this,
                                       struct rr_game *game)
{
    struct scroll_container_metadata *data = this->data;
    if (rr_ui_mouse_over(this, game) && game->input_data->scroll_delta != 0)
    {
        struct scroll_container_metadata *data = this->data;
        data->y += game->input_data->scroll_delta * 0.4;
        if (data->y > this->elements.start[0]->abs_height - this->abs_height)
            data->y = this->elements.start[0]->abs_height - this->abs_height;
        if (data->y < 0)
            data->y = 0;
    }
    data->lerp_y = rr_lerp(data->lerp_y, data->y, 0.2);
    struct rr_renderer *renderer = game->renderer;
    rr_renderer_set_stroke(renderer, 0x80000000);
    rr_renderer_set_line_width(renderer, 5);
    rr_renderer_set_line_cap(renderer, 1);
    if (this->elements.start[0]->abs_height > this->abs_height)
    {
        struct rr_renderer_context_state state;
        rr_renderer_context_state_init(renderer, &state);
        float height = this->abs_height * this->abs_height /
                       this->elements.start[0]->abs_height;
        float y = data->lerp_y * (this->abs_height - height) /
                  (this->elements.start[0]->abs_height - this->abs_height);
        rr_renderer_translate(renderer,
                              renderer->scale * (this->abs_width / 2 - 5),
                              renderer->scale * (y - this->abs_height / 2));
        rr_renderer_scale(renderer, renderer->scale);
        rr_renderer_begin_path(renderer);
        rr_renderer_move_to(renderer, 0, 0);
        rr_renderer_line_to(renderer, 0, height);
        rr_renderer_stroke(renderer);
        // scrollbar
        float x = renderer->state.transform_matrix[2];
        y = renderer->state.transform_matrix[5];
        if ((game->input_data->mouse_buttons & 1) &&
            fabsf(x - game->input_data->mouse_x) < 7.5 &&
            game->input_data->mouse_y > y &&
            game->input_data->mouse_y < y + height * renderer->scale)
        {
            data->scroll_focus = 1;
        }
        else if (data->scroll_focus &&
                 game->input_data->mouse_buttons_up_this_tick & 1)
        {
            data->scroll_focus = 0;
            game->block_ui_input = 1;
        }

        if (data->scroll_focus)
        {
            data->y +=
                (game->input_data->mouse_y - game->input_data->prev_mouse_y) /
                (this->abs_height - height) *
                (this->elements.start[0]->abs_height - this->abs_height);
            if (data->y >
                this->elements.start[0]->abs_height - this->abs_height)
                data->y =
                    this->elements.start[0]->abs_height - this->abs_height;
            if (data->y < 0)
                data->y = 0;
        }
        rr_renderer_context_state_free(renderer, &state);
    }
    rr_renderer_begin_path(renderer);
    rr_renderer_rect(renderer, renderer->scale * (-this->abs_width / 2),
                     renderer->scale * (-this->abs_height / 2),
                     renderer->scale * (this->elements.start[0]->width),
                     renderer->scale * (this->abs_height));
    rr_renderer_clip(renderer);
    rr_renderer_translate(renderer, 0, -data->lerp_y * renderer->scale);
    rr_ui_render_element(this->elements.start[0], game);
}

struct rr_ui_element *rr_ui_scroll_container_init(struct rr_ui_element *c,
                                                  float static_h)
{
    struct rr_ui_element *this = rr_ui_element_init();
    struct scroll_container_metadata *data = malloc(sizeof *data);
    rr_ui_container_add_element(this, c);
    data->y = data->lerp_y = 0;
    data->scroll_focus = 0;
    c->h_justify = -1;
    c->v_justify = -1;
    this->data = data;
    this->abs_height = this->height = static_h;
    this->abs_width = this->width = c->width + 10; // 5 is the scrollbar width
    this->on_render = scroll_container_on_render;
    this->poll_events = scroll_container_poll_events;
    this->resizeable = rr_ui_scroll_container;
    return this;
}
