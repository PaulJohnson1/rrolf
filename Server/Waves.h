#pragma once

#include <stdint.h>

struct rr_maze_grid;

uint32_t get_spawn_rarity(float);
uint8_t get_spawn_id(uint8_t, struct rr_maze_grid *);

float get_spawn_time(struct rr_maze_grid *);
int should_spawn_at(uint8_t, uint8_t);
