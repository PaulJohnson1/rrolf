#pragma once

#include <stdint.h>

extern uint32_t get_points_from_wave(uint32_t);
extern uint8_t get_id_from_wave(uint32_t);
extern uint8_t get_rarity_from_wave(uint32_t);

extern int should_spawn_at(uint32_t, uint8_t, uint8_t);
