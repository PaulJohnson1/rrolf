#pragma once

#include <stdint.h>

struct rr_game;

extern char storage_buf1[8 * 1024];
extern char storage_buf2[8 * 1024];

void rr_local_storage_store_bytes(char *, void const *, uint64_t);
uint32_t rr_local_storage_get_bytes(char *, void *);
// void rr_storage_layout_save(struct rr_game *);

uint32_t rr_local_storage_get_string(char *);
void rr_local_storage_store_string(char *, char *);

void rr_game_cache_data(struct rr_game *);
void rr_game_cache_load(struct rr_game *);
