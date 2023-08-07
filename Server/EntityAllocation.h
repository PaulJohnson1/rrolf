#pragma once

#include <Shared/SimulationCommon.h>

EntityIdx rr_simulation_alloc_entity(struct rr_simulation *);
EntityIdx rr_simulation_alloc_petal(struct rr_simulation *, float, float, uint8_t, uint8_t, EntityIdx);
EntityIdx rr_simulation_alloc_mob(struct rr_simulation *, float, float, enum rr_mob_id,
                                  enum rr_rarity_id,
                                  enum rr_simulation_team_id);
EntityIdx rr_simulation_alloc_player(EntityIdx, struct rr_simulation *);