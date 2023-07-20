#pragma once

#include <stdint.h>

struct rr_renderer;
struct rr_game;

void rr_renderer_render_petal(struct rr_renderer *, uint8_t);
void rr_renderer_render_static_petal(struct rr_renderer *, uint8_t, uint8_t);
void rr_renderer_render_mob(struct rr_renderer *, struct rr_game *, uint8_t,
                            float animation, float animation_value);
void rr_renderer_render_background(struct rr_renderer *, uint8_t);
void rr_renderer_render_petal_with_background(struct rr_renderer *, struct rr_game *, uint8_t, uint8_t);
