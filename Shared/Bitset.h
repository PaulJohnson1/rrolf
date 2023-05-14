#pragma once

#include <stdint.h>

int rr_bitset_get_bit(uint8_t *arr, uint64_t pos);
int rr_bitset_get(uint8_t *arr, uint64_t pos);
void rr_bitset_set(uint8_t *arr, uint64_t pos);
void rr_bitset_unset(uint8_t *arr, uint64_t pos);
