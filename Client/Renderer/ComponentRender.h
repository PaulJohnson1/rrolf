#pragma once

#include <Shared/Entity.h>

struct rr_simulation;
struct rr_renderer;

void rr_component_drop_render(EntityIdx, struct rr_simulation *, struct rr_renderer *);
void rr_component_flower_render(EntityIdx, struct rr_simulation *, struct rr_renderer *);
void rr_component_health_render(EntityIdx, struct rr_simulation *, struct rr_renderer *);
void rr_component_mob_render(EntityIdx, struct rr_simulation *, struct rr_renderer *, float, float);
void rr_component_petal_render(EntityIdx, struct rr_simulation *, struct rr_renderer *);