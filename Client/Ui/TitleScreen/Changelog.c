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

#include <Shared/Utilities.h>

static uint8_t changelog_container_should_show(struct rr_ui_element *this,
                                               struct rr_game *game)
{
    return game->top_ui_open == 2 && !game->simulation_ready;
}

static void changelog_container_animate(struct rr_ui_element *this,
                                        struct rr_game *game)
{
    this->width = this->abs_width;
    this->height = this->abs_height;
    rr_renderer_translate(
        game->renderer, -(this->x + this->abs_width / 2) * 2 * this->animation,
        0);
}

static void inventory_toggle_on_render(struct rr_ui_element *this,
                                       struct rr_game *game)
{
    struct rr_renderer *renderer = game->renderer;
    if (game->focused == this)
        renderer->state.filter.amount = 0.2;
    rr_renderer_scale(renderer, renderer->scale);
    rr_renderer_set_fill(renderer, this->fill);
    renderer->state.filter.amount += 0.2;
    rr_renderer_set_stroke(renderer, this->fill);
    rr_renderer_set_line_width(renderer, 6);
    rr_renderer_set_line_cap(renderer, 1);
    rr_renderer_begin_path(renderer);
    rr_renderer_round_rect(renderer, -this->width / 2, -this->height / 2,
                           this->width, this->height, 6);
    rr_renderer_fill(renderer);
    rr_renderer_stroke(renderer);
}

static void changelog_toggle_button_on_event(struct rr_ui_element *this,
                                             struct rr_game *game)
{
    if (game->pressed != this)
        return;
    if (game->input_data->mouse_buttons_up_this_tick & 1)
    {
        if (game->top_ui_open == 2)
            game->top_ui_open = 0;
        else
            game->top_ui_open = 2;
    }
}

static void changelog_divider_on_render(struct rr_ui_element *this,
                                        struct rr_game *game)
{
    struct rr_renderer *renderer = game->renderer;
    if (this->container->resizeable)
    {
        struct rr_ui_container_metadata *data = this->container->data;
        if (this->abs_width <
            this->container->abs_width - data->outer_spacing * 2)
            this->abs_width =
                this->container->abs_width - data->outer_spacing * 2;
    }
    rr_renderer_scale(renderer, renderer->scale);
    rr_renderer_set_stroke(renderer, this->fill);
    rr_renderer_set_line_width(renderer, this->abs_height / 2);
    rr_renderer_begin_path(renderer);
    rr_renderer_move_to(renderer, -this->abs_width / 2, 0);
    rr_renderer_line_to(renderer, this->abs_width / 2, 0);
    rr_renderer_stroke(renderer);
}

static struct rr_ui_element *changelog_divider_init()
{
    struct rr_ui_element *this = rr_ui_element_init();
    this->abs_height = this->height = 10;
    this->abs_width = this->width = 100;
    rr_ui_set_background(this, 0x40000000);
    this->on_render = changelog_divider_on_render;
    return this;
}

static uint8_t changelog_button_should_show(struct rr_ui_element *this,
                                            struct rr_game *game)
{
    return !game->simulation_ready;
}

struct rr_ui_element *rr_ui_changelog_toggle_button_init()
{
    struct rr_ui_element *this = rr_ui_element_init();
    rr_ui_set_background(this, 0xff888888);
    this->abs_width = this->abs_height = this->width = this->height = 40;
    this->on_event = changelog_toggle_button_on_event;
    this->on_render = inventory_toggle_on_render;
    this->should_show = changelog_button_should_show;
    return this;
}

struct rr_ui_element *rr_ui_changelog_container_init()
{
    struct rr_ui_element *this = rr_ui_pad(
        rr_ui_set_background(
            rr_ui_v_pad(
                rr_ui_set_justify(
                    rr_ui_v_container_init(
                        rr_ui_container_init(), 10, 10,
                        rr_ui_text_init("Changelog", 36, 0xffffffff),
                        rr_ui_scroll_container_init(
                            rr_ui_justify_all(
                                rr_ui_v_container_init(
                                    rr_ui_container_init(), 10, 10,
                                    rr_ui_text_init("7/29/2023", 24,
                                                    0xffffffff),
                                    rr_ui_static_space_init(10),
                                    rr_ui_text_init("Petas now act as one "
                                                    "entity before being shot",
                                                    16, 0xffffffff),
                                    rr_ui_text_init("Buffed peas", 16,
                                                    0xffffffff),
                                    changelog_divider_init(),
                                    rr_ui_text_init("7/28/2023", 24,
                                                    0xffffffff),
                                    rr_ui_static_space_init(10),
                                    rr_ui_text_init("Pteranodon now does not "
                                                    "shoot while chasing",
                                                    16, 0xffffffff),
                                    rr_ui_text_init(
                                        "Death cameras now follows seed and "
                                        "other alive players",
                                        16, 0xffffffff),
                                    changelog_divider_init(),
                                    rr_ui_text_init("7/27/2023", 24,
                                                    0xffffffff),
                                    rr_ui_static_space_init(10),
                                    rr_ui_text_init(
                                        "Create seed. drops from fern", 16,
                                        0xffffffff),
                                    rr_ui_text_init("Change drop rates", 16,
                                                    0xffffffff),
                                    changelog_divider_init(),
                                    rr_ui_text_init("2/13/2023", 24,
                                                    0xffffffff),
                                    rr_ui_static_space_init(10),
                                    rr_ui_text_init(
                                        "We have began working on a new game "
                                        "called rrolf.io",
                                        16, 0xffffffff),
                                    rr_ui_text_init("I heard it's about dinos",
                                                    16, 0xffffffff),
                                    NULL),
                                -1),
                            300),
                        NULL),
                    -1, -1),
                80),
            0x40ffffff),
        10);
    this->animate = changelog_container_animate;
    this->should_show = changelog_container_should_show;
    return this;
}
