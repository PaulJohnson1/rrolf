#pragma once

#include <stdint.h>

// May return any number that is 0, 1, 2, 4, 8, 16, 32, 64, 128.
int rr_bitset_get_bit(uint8_t *, uint64_t);

// Will only ever return 1 or 0. (takes one more instuction than rr_bitset_get_bit)
int rr_bitset_get(uint8_t *, uint64_t);
void rr_bitset_set(uint8_t *, uint64_t);
void rr_bitset_unset(uint8_t *, uint64_t);
void rr_bitset_for_each_bit(uint8_t *start, uint8_t *end, void *, void (*cb)(uint64_t, void *));
