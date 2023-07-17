#pragma once

#include <stdint.h>

struct rr_game;

extern uint8_t storage_result[4 * 1024];

uint32_t rr_local_storage_get(char *);

void rr_local_storage_store_string(char *, char *);
void rr_local_storage_store_chunk(char *, char *, uint32_t);
void rr_local_storage_store_bytes(char *, void const *bytes, uint64_t size);
void rr_local_storage_get_bytes(char *, void *bytes);
void rr_storage_layout_save(struct rr_game *);