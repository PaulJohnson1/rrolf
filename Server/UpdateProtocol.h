#pragma once

struct rr_simulation;
struct proto_bug;
struct rr_component_player_info;

void rr_simulation_write_binary(struct rr_simulation *, struct proto_bug *,
                                struct rr_component_player_info *);
