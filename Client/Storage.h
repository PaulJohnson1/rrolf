#pragma once

struct rr_game;

char *rr_local_storage_get(char *);

void rr_local_storage_set(char *, char *);

void rr_storage_layout_save(struct rr_game *);