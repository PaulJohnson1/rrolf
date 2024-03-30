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

#include <Client/Assets/RenderFunctions.h>

#include <math.h>

#include <Client/Renderer/Renderer.h>
#include <Shared/StaticData.h>

struct rr_renderer text_cache;

float PETAL_TEXT_LENGTHS[rr_petal_id_max];
float RARITY_TEXT_LENGTHS[rr_rarity_id_max];
float MOB_TEXT_LENGTHS[rr_mob_id_max];

void rr_renderer_draw_petal_name(struct rr_renderer *renderer, uint8_t id,
                                 float size, int8_t h, int8_t v)
{
    rr_renderer_scale(renderer, size / 10);
    float width = PETAL_TEXT_LENGTHS[id];
    rr_renderer_draw_clipped_image(renderer, &text_cache, 2 + width / 2,
                                   id * 14, width + 4, 14, h * width / 2,
                                   v * 10.0f / 2);
    rr_renderer_scale(renderer, 10 / size);
}

void rr_renderer_draw_mob_name(struct rr_renderer *renderer, uint8_t id,
                               float size, int8_t h, int8_t v)
{
    rr_renderer_scale(renderer, size / 10);
    float width = MOB_TEXT_LENGTHS[id];
    rr_renderer_draw_clipped_image(renderer, &text_cache, 2 + width / 2,
                                   (id + rr_petal_id_max) * 14, width + 4, 10,
                                   h * width / 2, v * 10 / 2);
    rr_renderer_scale(renderer, 10 / size);
}

void rr_renderer_draw_rarity_name(struct rr_renderer *renderer, uint8_t id,
                                  float size, int8_t h, int8_t v)
{
    rr_renderer_scale(renderer, size / 10);
    float width = RARITY_TEXT_LENGTHS[id];
    rr_renderer_draw_clipped_image(renderer, &text_cache, 2 + width / 2,
                                   (id + rr_petal_id_max + rr_mob_id_max) * 14,
                                   width + 4, 10, h * width / 2, v * 10 / 2);
    rr_renderer_scale(renderer, 10 / size);
}

void rr_renderer_text_cache_init()
{
    if (!(text_cache.context_id))
        rr_renderer_init(&text_cache);
    rr_renderer_set_dimensions(
        &text_cache, 256,
        14 * (rr_petal_id_max + rr_mob_id_max + rr_rarity_id_max));
    rr_renderer_set_transform(&text_cache, 1, 0, 2, 0, 1, 2);
    rr_renderer_set_fill(&text_cache, 0xffffffff);
    rr_renderer_set_stroke(&text_cache, 0xff222222);
    rr_renderer_set_text_size(&text_cache, 10);
    rr_renderer_set_line_width(&text_cache, 1.2);
    for (uint8_t i = 0; i < rr_petal_id_max; ++i)
    {
        PETAL_TEXT_LENGTHS[i] =
            rr_renderer_get_text_size(RR_PETAL_NAMES[i]) * 10;
        rr_renderer_stroke_text(&text_cache, RR_PETAL_NAMES[i], 0, 0);
        rr_renderer_fill_text(&text_cache, RR_PETAL_NAMES[i], 0, 0);
        rr_renderer_translate(&text_cache, 0, 14);
    }
    for (uint8_t i = 0; i < rr_mob_id_max; ++i)
    {
        MOB_TEXT_LENGTHS[i] = rr_renderer_get_text_size(RR_MOB_NAMES[i]) * 10;
        rr_renderer_stroke_text(&text_cache, RR_MOB_NAMES[i], 0, 0);
        rr_renderer_fill_text(&text_cache, RR_MOB_NAMES[i], 0, 0);
        rr_renderer_translate(&text_cache, 0, 14);
    }
    for (uint8_t i = 0; i < rr_rarity_id_max; ++i)
    {
        rr_renderer_set_fill(&text_cache, RR_RARITY_COLORS[i]);
        RARITY_TEXT_LENGTHS[i] =
            rr_renderer_get_text_size(RR_RARITY_NAMES[i]) * 10;
        rr_renderer_stroke_text(&text_cache, RR_RARITY_NAMES[i], 0, 0);
        rr_renderer_fill_text(&text_cache, RR_RARITY_NAMES[i], 0, 0);
        rr_renderer_translate(&text_cache, 0, 14);
    }
}