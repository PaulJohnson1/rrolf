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

#include <Shared/Entity.h>
#include <Shared/StaticData.h>

#define SPATIAL_HASH_GRID_SIZE (1024)
#define RR_SPATIAL_HASH_GRID_LENGTH                                            \
    (((RR_ARENA_LENGTH + SPATIAL_HASH_GRID_SIZE - 1) / SPATIAL_HASH_GRID_SIZE))
#define RR_SPATIAL_HASH_CELL_MAX_ENTITY_COUNT (2048)

struct rr_simulation;

struct rr_spatial_hash_cell
{
    uint32_t entities_in_use;
    EntityIdx entities[RR_SPATIAL_HASH_CELL_MAX_ENTITY_COUNT];
};

struct rr_spatial_hash
{
    struct rr_spatial_hash_cell *cells;
    struct rr_simulation *simulation;
    uint32_t size;
};

void rr_spatial_hash_init(struct rr_spatial_hash *, struct rr_simulation *,
                          float);
void rr_spatial_hash_insert(struct rr_spatial_hash *, EntityIdx);
void rr_spatial_hash_update(struct rr_spatial_hash *, EntityIdx);
void rr_spatial_hash_query(struct rr_spatial_hash *, float, float, float, float,
                           void *, void (*)(EntityIdx, void *));
void rr_spatial_hash_find_possible_collisions(struct rr_spatial_hash *, void *,
                                              void (*)(struct rr_simulation *,
                                                       EntityIdx, EntityIdx,
                                                       void *));
void rr_spatial_hash_reset(struct rr_spatial_hash *);