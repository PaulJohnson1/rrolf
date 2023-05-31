#pragma once

#include <stdint.h>

#if defined(RR_CLIENT) && defined(EMSCRIPTEN) && !defined(NDEBUG)
inline void rr_encrypt(uint8_t *start, uint64_t size, uint64_t key) __attribute__((always_inline));
inline void rr_decrypt(uint8_t *start, uint64_t size, uint64_t key) __attribute__((always_inline));
#else
void rr_encrypt(uint8_t *start, uint64_t size, uint64_t key);
void rr_decrypt(uint8_t *start, uint64_t size, uint64_t key);
#endif
uint64_t rr_get_rand();
uint64_t rr_get_hash(uint64_t);
