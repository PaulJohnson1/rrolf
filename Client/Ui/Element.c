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

static void default_function(struct rr_ui_element *this, struct rr_game *game)
{
    return; // does nothing
}

static void default_on_event(struct rr_ui_element *this, struct rr_game *game)
{
    return; // does nothing
}

void rr_ui_default_animate(struct rr_ui_element *this, struct rr_game *game)
{
    this->width = this->abs_width * (1 - this->completely_hidden);
    this->height = this->abs_height * (1 - this->completely_hidden);
    rr_renderer_set_global_alpha(game->renderer,
                                 game->renderer->state.global_alpha *
                                     (1 - this->animation));
}

void rr_ui_scale_animate(struct rr_ui_element *this, struct rr_game *game)
{
    this->width = this->abs_width * (1 - this->animation);
    this->height = this->abs_height * (1 - this->animation);
    rr_renderer_scale(game->renderer, (1 - this->animation));
}

void rr_ui_instant_hide_animate(struct rr_ui_element *this,
                                struct rr_game *game)
{
    this->width = this->abs_width * (1 - this->animation);
    this->height = this->abs_height * (1 - this->animation);
    rr_renderer_scale(game->renderer, (1 - this->animation));
    if (!this->should_show(this, game))
        this->animation = 1;
}

void rr_ui_render_element(struct rr_ui_element *this, struct rr_game *game)
{
    struct rr_renderer_context_state state;
    rr_renderer_context_state_init(game->renderer, &state);
    // fix ugly code later
    if (this->container == this)
        rr_renderer_translate(game->renderer, game->renderer->width / 2,
                              game->renderer->height / 2);
    else if (this->container == game->window)
        rr_renderer_translate(
            game->renderer,
            (this->x +
             (this->h_justify) *
                 (this->container->abs_width / 2 / game->renderer->scale -
                  this->width / 2 - (this->abs_width - this->width) / 2)) *
                game->renderer->scale,
            (this->y +
             (this->v_justify) *
                 (this->container->abs_height / 2 / game->renderer->scale -
                  this->height / 2 - (this->abs_height - this->height) / 2)) *
                game->renderer->scale); // necessary btw
    else
        rr_renderer_translate(
            game->renderer,
            (this->x + (this->h_justify) *
                           (this->container->abs_width / 2 - this->width / 2 -
                            (this->abs_width - this->width) / 2)) *
                game->renderer->scale,
            (this->y + (this->v_justify) *
                           (this->container->abs_height / 2 - this->height / 2 -
                            (this->abs_height - this->height) / 2)) *
                game->renderer->scale); // necessary btw
    this->abs_x = game->renderer->state.transform_matrix[2];
    this->abs_y = game->renderer->state.transform_matrix[5];

    this->animate(this, game);
    if (this->completely_hidden == 0)
        this->on_render(this, game);
    this->first_frame = 0;
    rr_renderer_context_state_free(game->renderer, &state);
}

void rr_ui_render_tooltip_above(struct rr_ui_element *this,
                                struct rr_ui_element *tooltip,
                                struct rr_game *game)
{
    rr_ui_container_refactor(tooltip, game);
    tooltip->should_show = rr_ui_always_show;
    tooltip->x = (this->abs_x / game->renderer->scale - tooltip->abs_width / 2);
    tooltip->y = (this->abs_y / game->renderer->scale -
                  (tooltip->abs_height + this->height / 2 + 10));
    if (tooltip->x < 10)
        tooltip->x = 10;
    else if (tooltip->x > game->renderer->width / game->renderer->scale - 10 -
                              tooltip->abs_width)
        tooltip->x = game->renderer->width / game->renderer->scale - 10 -
                     tooltip->abs_width;
    if (tooltip->y < 10)
        tooltip->y = 10;
}

void rr_ui_render_tooltip_below(struct rr_ui_element *this,
                                struct rr_ui_element *tooltip,
                                struct rr_game *game)
{
    rr_ui_container_refactor(tooltip, game);
    tooltip->should_show = rr_ui_always_show;
    tooltip->x = (this->abs_x / game->renderer->scale - tooltip->abs_width / 2);
    tooltip->y =
        (this->abs_y / game->renderer->scale + (this->height / 2 + 10));
    if (tooltip->x < 10)
        tooltip->x = 10;
    else if (tooltip->x > game->renderer->width / game->renderer->scale - 10 -
                              tooltip->abs_width)
        tooltip->x = game->renderer->width / game->renderer->scale - 10 -
                     tooltip->abs_width;
    if (tooltip->y > game->renderer->height - tooltip->abs_height - 10)
        tooltip->y = game->renderer->height - tooltip->abs_height - 10;
}

void rr_ui_render_tooltip_right(struct rr_ui_element *this,
                                struct rr_ui_element *tooltip,
                                struct rr_game *game)
{
    rr_ui_container_refactor(tooltip, game);
    tooltip->should_show = rr_ui_always_show;
    tooltip->x = (this->abs_x / game->renderer->scale + this->width / 2 + 10);
    tooltip->y =
        (this->abs_y / game->renderer->scale - tooltip->abs_height / 2);
}

uint8_t rr_ui_mouse_over(struct rr_ui_element *this, struct rr_game *game)
{
    return fabsf(game->input_data->mouse_x - this->abs_x) <
               this->width * game->renderer->scale / 2 &&
           fabsf(game->input_data->mouse_y - this->abs_y) <
               this->height * game->renderer->scale / 2;
}

void rr_ui_element_check_if_focused(struct rr_ui_element *this,
                                    struct rr_game *game)
{
    if (rr_ui_mouse_over(this, game))
    {
        game->focused = this;
        if (game->input_data->mouse_buttons_down_this_tick & 1)
            game->pressed = this;
    }
    else if (game->focused == this)
        game->focused = NULL;
}

uint8_t rr_ui_always_show(struct rr_ui_element *this, struct rr_game *game)
{
    return 1;
}

uint8_t rr_ui_never_show(struct rr_ui_element *this, struct rr_game *game)
{
    return 0;
}

void rr_ui_no_focus(struct rr_ui_element *this, struct rr_game *game)
{
    this->should_show = rr_ui_never_show;
}

struct rr_ui_element *rr_ui_element_init()
{
    struct rr_ui_element *this = malloc(sizeof *this);
    memset(this, 0, sizeof *this);
    this->first_frame = 1;
    this->on_render = default_function;
    this->on_hide = default_function;
    this->on_event = default_on_event; // null on_event
    this->should_show = rr_ui_always_show;
    this->poll_events = rr_ui_element_check_if_focused;
    this->animate = rr_ui_default_animate;
    this->resizeable = rr_ui_not_resizeable;
    this->elements.size = 0;
    this->elements.capacity = 1;
    this->elements.start =
        malloc(sizeof(*this->elements.start) * this->elements.capacity);
    return this;
}

struct rr_ui_element *rr_ui_static_space_init(float s)
{
    struct rr_ui_element *this = rr_ui_element_init();
    this->abs_height = this->abs_width = this->width = this->height = s;
    return this;
}

struct rr_ui_element *rr_ui_link_toggle(
    struct rr_ui_element *this,
    uint8_t (*should_show)(struct rr_ui_element *, struct rr_game *))
{
    this->should_show = should_show;
    return this;
}
