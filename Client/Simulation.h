#pragma once

#include <Shared/SimulationCommon.h>

void rr_simulation_entity_create_with_id(struct rr_simulation *, EntityIdx);
void rr_simulation_read_binary(struct rr_simulation *, struct proto_bug *);
void rr_simulation_tick(struct rr_simulation *, float delta);
