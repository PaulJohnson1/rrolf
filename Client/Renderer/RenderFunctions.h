#pragma once

#include <stdint.h>

struct rr_renderer;
struct rr_game;

void rr_renderer_render_mob(struct rr_renderer *, struct rr_game *, uint8_t,
                            float, float, uint8_t);