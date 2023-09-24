#pragma once

#include <Shared/SimulationCommon.h>

#define RR_BASE_PLAYER_SPEED 2.5

void rr_simulation_tick(struct rr_simulation *);

uint8_t rr_simulation_entity_alive(struct rr_simulation *, EntityIdx);