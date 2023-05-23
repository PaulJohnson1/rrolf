#pragma once

#include <stdint.h>

void spn_encrypt(uint8_t *start, uint64_t size, uint64_t key);
void spn_decrypt(uint8_t *start, uint64_t size, uint64_t key);
uint64_t spn_get_rand();
uint64_t spn_get_hash(uint64_t);
