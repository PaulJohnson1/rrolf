#pragma once

#include <stdint.h>

struct rr_renderer;

void rr_renderer_render_petal(struct rr_renderer *, uint8_t);
void rr_renderer_render_mob(struct rr_renderer *, uint8_t);