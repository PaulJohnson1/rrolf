#pragma once

#include <stdint.h>

void rr_encrypt(uint8_t *start, uint64_t size, uint64_t key);
void rr_decrypt(uint8_t *start, uint64_t size, uint64_t key);
uint64_t rr_get_rand();
uint64_t rr_get_hash(uint64_t);
