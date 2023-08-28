#pragma once

#include <stdint.h>

struct rr_maze_grid;

extern uint32_t get_spawn_rarity(float);
extern uint8_t get_spawn_id(uint8_t, struct rr_maze_grid *);

extern int should_spawn_at(uint8_t, uint8_t);
