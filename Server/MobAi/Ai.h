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

void tick_ai_passive_meteor(EntityIdx, struct rr_simulation *);

void tick_ai_neutral_triceratops(EntityIdx, struct rr_simulation *);
void tick_ai_neutral_trex(EntityIdx, struct rr_simulation *);
void tick_ai_neutral_pteranodon(EntityIdx, struct rr_simulation *);
void tick_ai_neutral_ornithomimus(EntityIdx, struct rr_simulation *);
void tick_ai_neutral_ankylosaurus(EntityIdx, struct rr_simulation *);
void tick_ai_neutral_quetzalcoaltus(EntityIdx, struct rr_simulation *);

void tick_ai_aggro_triceratops(EntityIdx, struct rr_simulation *);
void tick_ai_aggro_trex(EntityIdx, struct rr_simulation *);
void tick_ai_aggro_pteranodon(EntityIdx, struct rr_simulation *);
void tick_ai_aggro_pachycephalosaurus(EntityIdx, struct rr_simulation *);
void tick_ai_aggro_ornithomimus(EntityIdx, struct rr_simulation *);
void tick_ai_aggro_ankylosaurus(EntityIdx, struct rr_simulation *);
void tick_ai_aggro_quetzalcoaltus(EntityIdx, struct rr_simulation *);
