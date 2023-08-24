#pragma once

#include <stdint.h>

struct rr_renderer;

void rr_renderer_draw_petal(struct rr_renderer *, uint8_t, uint8_t);
void rr_renderer_draw_static_petal(struct rr_renderer *, uint8_t, uint8_t, uint8_t);
void rr_renderer_draw_petal_with_name(struct rr_renderer *, uint8_t, uint8_t);
void rr_renderer_draw_background(struct rr_renderer *, uint8_t, uint8_t);

void rr_renderer_draw_mob(struct rr_renderer *, uint8_t, float, float, uint8_t);

void rr_renderer_draw_petal_name(struct rr_renderer *, uint8_t, float, int8_t, int8_t);
void rr_renderer_draw_mob_name(struct rr_renderer *, uint8_t, float, int8_t, int8_t);
void rr_renderer_draw_rarity_name(struct rr_renderer *, uint8_t, float, int8_t, int8_t);

void rr_renderer_draw_tile_hell_creek(struct rr_renderer *, uint8_t);
void rr_renderer_draw_tile_ocean(struct rr_renderer *, uint8_t);
void rr_renderer_draw_prop(struct rr_renderer *, uint8_t);
void rr_renderer_draw_web(struct rr_renderer *);

void rr_renderer_petal_cache_init();
void rr_renderer_background_cache_init();
void rr_renderer_text_cache_init();
void rr_renderer_mob_cache_init();
void rr_renderer_tiles_init();