// Copyright (C) 2024  Paul Johnson

// This program is free software: you can redistribute it and/or modify
// it under the terms of the GNU Affero General Public License as
// published by the Free Software Foundation, either version 3 of the
// License, or (at your option) any later version.

// This program is distributed in the hope that it will be useful,
// but WITHOUT ANY WARRANTY; without even the implied warranty of
// MERCHANTABILITY or FITNESS FOR A PARTICULAR PURPOSE.  See the
// GNU Affero General Public License for more details.

// You should have received a copy of the GNU Affero General Public License
// along with this program.  If not, see <https://www.gnu.org/licenses/>.

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
