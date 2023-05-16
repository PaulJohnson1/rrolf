#pragma once

#include <Shared/SimulationCommon.h>

void rr_simulation_enitty_create_with_id(struct rr_simulation *, EntityIdx);
void rr_simulation_read_binary(struct rr_simulation *, struct rr_encoder *);
void rr_simulation_tick(struct rr_simulation *);
