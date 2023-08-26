#pragma once

#include <stdint.h>

struct rr_spawn_zone;

extern uint32_t get_spawn_rarity(float);
extern uint8_t get_spawn_id(uint8_t, struct rr_spawn_zone *);

extern int should_spawn_at(uint8_t, uint8_t);
