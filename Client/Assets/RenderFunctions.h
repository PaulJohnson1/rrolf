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

#pragma once

#include <stdint.h>

struct rr_renderer;

void rr_renderer_draw_petal(struct rr_renderer *, uint8_t, uint8_t);
void rr_renderer_draw_static_petal(struct rr_renderer *, uint8_t, uint8_t,
                                   uint8_t);
void rr_renderer_draw_petal_with_name(struct rr_renderer *, uint8_t, uint8_t);
void rr_renderer_draw_background(struct rr_renderer *, uint8_t, uint8_t);

void rr_renderer_draw_mob(struct rr_renderer *, uint8_t, float, float, uint8_t);

void rr_renderer_draw_petal_name(struct rr_renderer *, uint8_t, float, int8_t,
                                 int8_t);
void rr_renderer_draw_mob_name(struct rr_renderer *, uint8_t, float, int8_t,
                               int8_t);
void rr_renderer_draw_rarity_name(struct rr_renderer *, uint8_t, float, int8_t,
                                  int8_t);

void rr_renderer_draw_tile_hell_creek(struct rr_renderer *, uint8_t);
void rr_renderer_draw_tile_garden(struct rr_renderer *, uint8_t);
void rr_renderer_draw_prop(struct rr_renderer *, uint8_t);
void rr_renderer_draw_web(struct rr_renderer *);

void rr_renderer_petal_cache_init();
void rr_renderer_background_cache_init();
void rr_renderer_text_cache_init();
void rr_renderer_mob_cache_init();
void rr_renderer_tiles_init();