#pragma once

#include <stdint.h>

int rr_bitset_get_bit(uint8_t *, uint64_t);
int rr_bitset_get(uint8_t *, uint64_t);
void rr_bitset_set(uint8_t *, uint64_t);
void rr_bitset_unset(uint8_t *, uint64_t);
void rr_bitset_for_each_bit(uint8_t *start, uint8_t *end, void *, void (*cb)(uint64_t, void *));
void rr_bitset_for_each_bit_old(uint8_t *start, uint8_t *end, void *, void (*cb)(uint64_t, void *));
