#pragma once

#include <stdint.h>

inline void rr_encrypt(uint8_t *start, uint64_t size, uint64_t key) __attribute__((always_inline));
inline void rr_decrypt(uint8_t *start, uint64_t size, uint64_t key) __attribute__((always_inline));
uint64_t rr_get_rand();
uint64_t rr_get_hash(uint64_t);
