#pragma once

#include <stdint.h>

#include <Shared/Entity.h>

struct rr_simulation;

EntityIdx rr_simulation_find_nearest_enemy(struct rr_simulation *, EntityIdx, float, void *, uint8_t (*)(struct rr_simulation *, EntityIdx, EntityIdx, void *));
EntityIdx rr_simulation_find_nearest_enemy_custom_pos(struct rr_simulation *, EntityIdx, float, float, float, void *, uint8_t (*)(struct rr_simulation *, EntityIdx, EntityIdx, void *));

EntityIdx rr_simulation_find_nearest_friend(struct rr_simulation *, EntityIdx, float, void *, uint8_t (*)(struct rr_simulation *, EntityIdx, EntityIdx, void *));
EntityIdx rr_simulation_find_nearest_friend_custom_pos(struct rr_simulation *, EntityIdx, float, float, float, void *, uint8_t (*)(struct rr_simulation *, EntityIdx, EntityIdx, void *));

uint8_t no_filter(struct rr_simulation *, EntityIdx, EntityIdx, void *);