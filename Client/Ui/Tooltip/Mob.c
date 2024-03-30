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

#include <Client/Assets/RenderFunctions.h>
#include <Client/Game.h>
#include <Client/Renderer/Renderer.h>
#include <Client/Ui/Engine.h>

#include <Shared/StaticData.h>
#include <Shared/Utilities.h>

static void inventory_button_on_render(struct rr_ui_element *this,
                                       struct rr_game *game)
{
    struct rr_id_rarity_pair *data = this->data;
    struct rr_renderer *renderer = game->renderer;
    rr_renderer_scale(renderer, renderer->scale * this->width / 60);
    rr_renderer_draw_background(renderer, data->rarity, 1);
    rr_renderer_draw_petal_with_name(renderer, data->id, data->rarity);
}

static struct rr_ui_element *tooltip_petal_icon_init(uint8_t id, uint8_t rarity)
{
    struct rr_ui_element *this = rr_ui_element_init();
    struct rr_id_rarity_pair *data = malloc(sizeof *data);
    data->id = id;
    data->rarity = rarity;
    this->data = data;
    this->abs_width = this->abs_height = this->width = this->height = 40;
    this->on_render = inventory_button_on_render;
    return this;
}

struct rr_ui_element *rr_ui_mob_tooltip_init(uint8_t id, uint8_t rarity)
{
    char *hp = malloc((sizeof *hp) * 16);
    rr_sprintf(hp,
               RR_MOB_DATA[id].health * RR_MOB_RARITY_SCALING[rarity].health);
    char *dmg = malloc((sizeof *dmg) * 16);
    rr_sprintf(dmg,
               RR_MOB_DATA[id].damage * RR_MOB_RARITY_SCALING[rarity].damage);
    struct rr_ui_element *this = rr_ui_set_background(
        rr_ui_v_container_init(
            rr_ui_tooltip_container_init(), 10, 5,
            rr_ui_set_justify(rr_ui_text_init(RR_MOB_NAMES[id], 24, 0xffffffff),
                              -1, -1),
            rr_ui_set_justify(rr_ui_text_init(RR_RARITY_NAMES[rarity], 16,
                                              RR_RARITY_COLORS[rarity]),
                              -1, -1),
            rr_ui_static_space_init(10),
            rr_ui_set_justify(rr_ui_h_container_init(
                                  rr_ui_container_init(), 0, 0,
                                  rr_ui_text_init("Health: ", 12, 0xff44ff44),
                                  rr_ui_text_init(hp, 12, 0xffffffff), NULL),
                              -1, 0),
            rr_ui_set_justify(rr_ui_h_container_init(
                                  rr_ui_container_init(), 0, 0,
                                  rr_ui_text_init("Damage: ", 12, 0xffff4444),
                                  rr_ui_text_init(dmg, 12, 0xffffffff), NULL),
                              -1, 0),
            NULL),
        0x80000000);
    if (id == rr_mob_id_pteranodon)
    {
        char *extra = malloc((sizeof *extra) * 8);
        rr_sprintf(extra, 5 * RR_MOB_RARITY_SCALING[rarity].health);
        rr_ui_container_add_element(
            this, rr_ui_set_justify(
                      rr_ui_h_container_init(
                          rr_ui_container_init(), 0, 0,
                          rr_ui_text_init("Shell health: ", 12, 0xff44ff44),
                          rr_ui_text_init(extra, 12, 0xffffffff), NULL),
                      -1, 0));
        extra = malloc((sizeof *extra) * 8);
        rr_sprintf(extra, 10 * RR_MOB_RARITY_SCALING[rarity].damage);
        rr_ui_container_add_element(
            this, rr_ui_set_justify(
                      rr_ui_h_container_init(
                          rr_ui_container_init(), 0, 0,
                          rr_ui_text_init("Shell damage: ", 12, 0xffff4444),
                          rr_ui_text_init(extra, 12, 0xffffffff), NULL),
                      -1, 0));
    }
    else if (id == rr_mob_id_edmontosaurus)
    {
        char *extra = malloc((sizeof *extra) * 8);
        rr_sprintf(extra, 10 * RR_MOB_RARITY_SCALING[rarity].damage);
        rr_ui_container_add_element(
            this, rr_ui_set_justify(
                      rr_ui_h_container_init(
                          rr_ui_container_init(), 0, 0,
                          rr_ui_text_init("Damage reduction: ", 12, 0xff666666),
                          rr_ui_text_init(extra, 12, 0xffffffff), NULL),
                      -1, 0));
    }
    rr_ui_container_add_element(this, rr_ui_static_space_init(10));
    for (uint8_t i = 0; i < 4; ++i)
    {
        if (RR_MOB_DATA[id].loot[i].id == 0)
            break;
        uint8_t p_id = RR_MOB_DATA[id].loot[i].id;
        float seed = RR_MOB_DATA[id].loot[i].seed;
        struct rr_ui_element *temp =
            rr_ui_h_container_init(rr_ui_container_init(), 0, 10, NULL);
        uint64_t cap = rarity >= rr_rarity_id_exotic ? rarity - 1 : rarity;
        uint8_t min_rar = RR_PETAL_DATA[p_id].min_rarity;
        for (uint8_t r = min_rar + 1; r <= cap + 1; ++r)
        {

            double end = r == cap + 1 ? 1 : RR_DROP_RARITY_COEFFICIENTS[r];
            double start = RR_DROP_RARITY_COEFFICIENTS[r - 1];
            if (cap < min_rar)
                end = 1;
            float chance = pow(1 - (1 - end) * seed,
                               RR_MOB_LOOT_RARITY_COEFFICIENTS[rarity]) -
                           pow(1 - (1 - start) * seed,
                               RR_MOB_LOOT_RARITY_COEFFICIENTS[rarity]);
            if (chance * 100 < 0.01)
                continue;
            char *d = malloc((sizeof *d) * 16);
            float pct = 100 * chance;
            if (pct > 1)
                sprintf(d, "%.1f%%", pct);
            else if (pct > 0.1)
                sprintf(d, "%.2f%%", pct);
            else if (pct > 0.01)
                sprintf(d, "%.3f%%", pct);
            rr_ui_container_add_element(
                temp, rr_ui_v_container_init(
                          rr_ui_container_init(), 0, 5,
                          tooltip_petal_icon_init(p_id, r - 1),
                          rr_ui_text_init(d, 11, 0xffffffff), NULL));
        }
        rr_ui_h_container_set(temp);
        temp->width = temp->abs_width;
        temp->height = temp->abs_height;
        rr_ui_container_add_element(this, rr_ui_set_justify(temp, -1, -1));
    }
    rr_ui_set_justify(this, -1, -1);
    rr_ui_v_container_set(this);
    return this;
}