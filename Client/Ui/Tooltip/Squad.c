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
#include <Client/Ui/Engine.h>

#include <Shared/Squad.h>
#include <Shared/Utilities.h>

struct squad_loadout_button_metadata
{
    struct rr_id_rarity_pair *petal;
    uint8_t prev_id;
    uint8_t prev_rarity;
};

static uint8_t squad_loadout_button_should_show(struct rr_ui_element *this,
                                                struct rr_game *game)
{
    struct squad_loadout_button_metadata *data = this->data;
    return data->petal->id;
}

static void squad_loadout_button_animate(struct rr_ui_element *this,
                                         struct rr_game *game)
{
    struct squad_loadout_button_metadata *data = this->data;
    if (data->petal->id != 0)
    {
        data->prev_id = data->petal->id;
        data->prev_rarity = data->petal->rarity;
    }
    rr_renderer_scale(game->renderer, (1 - this->animation));
}

static void squad_loadout_button_on_render(struct rr_ui_element *this,
                                           struct rr_game *game)
{
    struct squad_loadout_button_metadata *data = this->data;
    struct rr_renderer *renderer = game->renderer;
    rr_renderer_scale(renderer, renderer->scale * this->width / 60);
    rr_renderer_draw_background(renderer, data->prev_rarity, 1);
    rr_renderer_draw_static_petal(renderer, data->prev_id, data->prev_rarity,
                                  1);
}

static struct rr_ui_element *
squad_loadout_button_init(struct rr_id_rarity_pair *petal, uint8_t top)
{
    struct rr_ui_element *this = rr_ui_element_init();
    struct squad_loadout_button_metadata *data = malloc(sizeof *data);
    data->petal = petal;
    data->prev_id = 0;
    this->data = data;
    this->abs_width = this->width = top ? 30 : 25;
    this->abs_height = this->height = top ? 30 : 25;
    this->on_render = squad_loadout_button_on_render;
    this->animate = squad_loadout_button_animate;
    this->should_show = squad_loadout_button_should_show;
    return this;
}

static uint8_t dev_text_choose(struct rr_ui_element *this, struct rr_game *game)
{
    struct rr_ui_choose_element_metadata *data = this->data;
    struct rr_squad_member *member = data->data;
    if (member->is_dev)
        return 2;
    if (&game->squad.squad_members[game->squad.squad_pos] == member)
        return 0;
    return 1;
}

static struct rr_ui_element *dev_text_init(struct rr_squad_member *member)
{
    struct rr_ui_element *this = rr_ui_multi_choose_element_init(
        dev_text_choose, rr_ui_text_init("You", 20, 0xffffffff),
        rr_ui_text_init("Player", 20, 0xffffffff),
        rr_ui_text_init("Developer", 20, 0xffffffff), NULL);
    struct rr_ui_choose_element_metadata *data = this->data;
    data->data = member;
    return this;
}

struct rr_ui_element *
rr_ui_squad_player_tooltip_init(struct rr_squad_member *member)
{
    struct rr_ui_element *this = rr_ui_set_justify(
        rr_ui_set_background(
            rr_ui_v_container_init(
                rr_ui_container_init(), 10, 10, dev_text_init(member),
                rr_ui_text_init(member->nickname, 16, 0xffffffff),
                rr_ui_h_container_init(
                    rr_ui_container_init(), 0, 5,
                    squad_loadout_button_init(&member->loadout[0], 1),
                    squad_loadout_button_init(&member->loadout[1], 1),
                    squad_loadout_button_init(&member->loadout[2], 1),
                    squad_loadout_button_init(&member->loadout[3], 1),
                    squad_loadout_button_init(&member->loadout[4], 1),
                    squad_loadout_button_init(&member->loadout[5], 1),
                    squad_loadout_button_init(&member->loadout[6], 1),
                    squad_loadout_button_init(&member->loadout[7], 1),
                    squad_loadout_button_init(&member->loadout[8], 1),
                    squad_loadout_button_init(&member->loadout[9], 1), NULL),
                rr_ui_h_container_init(
                    rr_ui_container_init(), 0, 5,
                    squad_loadout_button_init(&member->loadout[10], 0),
                    squad_loadout_button_init(&member->loadout[11], 0),
                    squad_loadout_button_init(&member->loadout[12], 0),
                    squad_loadout_button_init(&member->loadout[13], 0),
                    squad_loadout_button_init(&member->loadout[14], 0),
                    squad_loadout_button_init(&member->loadout[15], 0),
                    squad_loadout_button_init(&member->loadout[16], 0),
                    squad_loadout_button_init(&member->loadout[17], 0),
                    squad_loadout_button_init(&member->loadout[18], 0),
                    squad_loadout_button_init(&member->loadout[19], 0), NULL),
                NULL),
            0x80000000),
        -1, -1);
    this->poll_events = rr_ui_no_focus;
    rr_ui_link_toggle(this, rr_ui_never_show);
    return this;
}