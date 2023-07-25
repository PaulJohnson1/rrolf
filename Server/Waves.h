#pragma once

#include <stdint.h>

extern uint8_t get_id_from_wave(uint32_t wave);
extern uint8_t get_rarity_from_wave(uint32_t wave);

extern int should_spawn_at(uint32_t wave, uint8_t id, uint8_t rarity);
