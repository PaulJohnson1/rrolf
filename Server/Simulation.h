#pragma once

#include <Shared/SimulationCommon.h>

void rr_simulation_write_binary(struct rr_simulation *, struct proto_bug *,
                                struct rr_component_player_info *);

EntityIdx rr_simulation_alloc_entity(struct rr_simulation *);
EntityIdx rr_simulation_alloc_mob(struct rr_simulation *, enum rr_mob_id,
                                  enum rr_rarity_id,
                                  enum rr_simulation_team_id);
void rr_simulation_request_entity_deletion(struct rr_simulation *, EntityIdx);
void rr_simulation_tick(struct rr_simulation *);
