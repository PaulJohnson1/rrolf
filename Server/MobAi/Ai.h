#pragma once

#include <stdlib.h>

#include <Shared/Entity.h>
#include <Shared/Vector.h>

struct rr_simulation;
struct rr_component_ai;

uint8_t has_new_target(struct rr_component_ai *, struct rr_simulation *);
uint8_t ai_is_passive(struct rr_component_ai *);
struct rr_vector predict(struct rr_vector, struct rr_vector, float);
void tick_idle(EntityIdx, struct rr_simulation *);

void tick_idle_move_default(EntityIdx, struct rr_simulation *);
void tick_idle_move_sinusoid(EntityIdx, struct rr_simulation *, float);
uint8_t tick_summon_return_to_owner(EntityIdx, struct rr_simulation *);

void tick_ai_passive_default(EntityIdx, struct rr_simulation *);
void tick_ai_neutral_default(EntityIdx, struct rr_simulation *, float);
void tick_ai_aggro_default(EntityIdx, struct rr_simulation *, float);

void tick_ai_neutral_triceratops(EntityIdx, struct rr_simulation *);
void tick_ai_neutral_ornithomimus(EntityIdx, struct rr_simulation *);

void tick_ai_aggro_pteranodon(EntityIdx, struct rr_simulation *);
void tick_ai_aggro_pachycephalosaurus(EntityIdx, struct rr_simulation *);
void tick_ai_aggro_ankylosaurus(EntityIdx, struct rr_simulation *);
void tick_ai_aggro_quetzalcoaltus(EntityIdx, struct rr_simulation *);