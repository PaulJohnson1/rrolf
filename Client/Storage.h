#pragma once

#include <stdint.h>

struct rr_game;

extern uint8_t storage_result[16 * 1024];

void rr_local_storage_store_bytes(char *, void const *, uint64_t);
uint32_t rr_local_storage_get_bytes(char *, void *);
// void rr_storage_layout_save(struct rr_game *);

void rr_local_storage_store_id_rarity(char *, uint32_t *, uint8_t, uint8_t);
void rr_local_storage_get_id_rarity(char *, uint32_t *, uint8_t, uint8_t);

void rr_local_storage_store(struct rr_game *);
void rr_local_storage_retrieve(struct rr_game *);