#pragma once

#include <Shared/SimulationCommon.h>

void rr_simulation_tick(struct rr_simulation *);

int rr_simulation_entity_alive(struct rr_simulation *, EntityHash); //stricter version

EntityHash rr_simulation_get_entity_hash(struct rr_simulation *, EntityIdx);