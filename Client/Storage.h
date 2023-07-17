#pragma once

#include <stdint.h>

struct rr_game;

extern uint8_t storage_result[4 * 1024];

void rr_local_storage_store_bytes(char *, void const *bytes, uint64_t size);
void rr_local_storage_get_bytes(char *, void *bytes);
// void rr_storage_layout_save(struct rr_game *);