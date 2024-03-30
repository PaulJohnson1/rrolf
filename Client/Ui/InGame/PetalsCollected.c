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

#include <Client/Assets/RenderFunctions.h>
#include <Client/Game.h>
#include <Client/InputData.h>
#include <Client/Renderer/Renderer.h>
#include <Client/Simulation.h>

#include <Client/Ui/Engine.h>

#include <Shared/Utilities.h>

struct collected_button_metadata
{
    uint8_t id;
    uint8_t rarity;
};

static void collected_button_on_event(struct rr_ui_element *this,
                                      struct rr_game *game)
{
    struct collected_button_metadata *data = this->data;
    rr_ui_render_tooltip_above(
        this, game->petal_tooltips[data->id][data->rarity], game);
}

static uint8_t collected_button_should_show(struct rr_ui_element *this,
                                            struct rr_game *game)
{
    if (!game->simulation_ready)
        return 0;
    struct collected_button_metadata *data = this->data;
    return game->player_info
        ->collected_this_run[data->id * rr_rarity_id_max + data->rarity];
}

static void collected_button_on_render(struct rr_ui_element *this,
                                       struct rr_game *game)
{
    struct collected_button_metadata *data = this->data;
    struct rr_renderer *renderer = game->renderer;
    rr_renderer_scale(renderer, renderer->scale * this->width / 60);
    struct rr_renderer_context_state state;
    rr_renderer_context_state_init(renderer, &state);
    rr_renderer_draw_background(renderer, data->rarity, 1);
    rr_renderer_draw_petal_with_name(renderer, data->id, data->rarity);
    rr_renderer_context_state_free(renderer, &state);
    if (game->player_info->collected_this_run[data->id * rr_rarity_id_max +
                                              data->rarity] == 1)
        return;
    rr_renderer_translate(renderer, 25, -25);
    rr_renderer_rotate(renderer, 0.5);
    rr_renderer_set_fill(renderer, 0xffffffff);
    rr_renderer_set_stroke(renderer, 0xff222222);
    rr_renderer_set_text_align(renderer, 1);
    rr_renderer_set_text_baseline(renderer, 1);
    rr_renderer_set_text_size(renderer, 18);
    rr_renderer_set_line_width(renderer, 18 * 0.12);

    char out[12];
    sprintf(&out[0], "x%d",
            game->player_info->collected_this_run[data->id * rr_rarity_id_max +
                                                  data->rarity]);
    rr_renderer_stroke_text(renderer, (char const *)&out, 0, 0);
    rr_renderer_fill_text(renderer, (char const *)&out, 0, 0);
}

static struct rr_ui_element *collected_button_init(uint8_t id, uint8_t rarity)
{
    struct rr_ui_element *this = rr_ui_element_init();
    struct collected_button_metadata *data = malloc(sizeof *data);
    data->id = id;
    data->rarity = rarity;
    this->data = data;
    this->abs_width = this->width = 50;
    this->abs_height = this->height = 50;
    this->on_render = collected_button_on_render;
    this->should_show = collected_button_should_show;
    this->on_event = collected_button_on_event;
    return this;
}

static uint8_t loot_container_should_show(struct rr_ui_element *this,
                                          struct rr_game *game)
{
    return game->simulation_ready &&
           (game->simulation->game_over ||
            game->player_info->flower_id == RR_NULL_ENTITY);
}

struct rr_ui_element *rr_ui_loot_container_init()
{
    struct rr_ui_element *this = rr_ui_2d_container_init(4, 6, 15, 15);
    for (uint8_t rarity = rr_rarity_id_max - 1; rarity != 255; --rarity)
        for (uint8_t id = 1; id < rr_petal_id_max; ++id)
            rr_ui_container_add_element(this,
                                        collected_button_init(id, rarity));
    rr_ui_set_background(this, 0x00000000);
    struct rr_ui_element *c = rr_ui_set_background(
        rr_ui_pad(rr_ui_set_justify(
                      rr_ui_v_container_init(
                          rr_ui_container_init(), 10, 10,
                          rr_ui_text_init("Collected this run", 24, 0xffffffff),
                          rr_ui_scroll_container_init(this, 500), NULL),
                      1, 0),
                  20),
        0x40ffffff);
    c->should_show = loot_container_should_show;
    c->animate = rr_ui_instant_hide_animate;
    return c;
}