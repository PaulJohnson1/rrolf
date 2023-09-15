#pragma once

#include <Shared/SimulationCommon.h>

void rr_simulation_tick(struct rr_simulation *);

uint8_t rr_simulation_entity_alive(struct rr_simulation *, EntityIdx); //stricter version