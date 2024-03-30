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

#include <Server/SpatialHash.h>

#include <math.h>
#include <stdlib.h>
#include <string.h>

#include <Shared/Bitset.h>
#include <Shared/SimulationCommon.h>

#define spatial_hash_get(x,y) &this->cells[(x)*this->size+(y)]
void rr_spatial_hash_init(struct rr_spatial_hash *this, struct rr_simulation *simulation, float size)
{
    memset(this, 0, sizeof *this);
    this->size = (size + SPATIAL_HASH_GRID_SIZE - 0.1) / SPATIAL_HASH_GRID_SIZE;
    this->simulation = simulation;
    this->cells = calloc(sizeof (struct rr_spatial_hash_cell), this->size * this->size);
}

void rr_spatial_hash_insert(struct rr_spatial_hash *this, EntityIdx entity)
{
    struct rr_component_physical *physical =
        rr_simulation_get_physical(this->simulation, entity);

    // force positions unsigned for a significantly better hash function
    uint32_t x = rr_fclamp(physical->x, physical->radius, this->size * SPATIAL_HASH_GRID_SIZE - physical->radius) / SPATIAL_HASH_GRID_SIZE;
    uint32_t y = rr_fclamp(physical->y, physical->radius, this->size * SPATIAL_HASH_GRID_SIZE - physical->radius) / SPATIAL_HASH_GRID_SIZE;
    struct rr_spatial_hash_cell *cell = spatial_hash_get(x,y);
    cell->entities[cell->entities_in_use++] = entity;
}

void rr_spatial_hash_update(struct rr_spatial_hash *this, EntityIdx entity) {}

void rr_spatial_hash_query(struct rr_spatial_hash *this, float fx, float fy,
                           float fw, float fh, void *user_captures,
                           void (*cb)(EntityIdx, void *))
{
    float x = fmaxf(fx - fw, 0);
    float y = fmaxf(fy - fh, 0);
    // should not take in an entity id like insert does. the reason is so stuff
    // like ai can query a large radius without a viewing entity
    uint32_t s_x = rr_fclamp((fx - fw - SPATIAL_HASH_GRID_SIZE) / SPATIAL_HASH_GRID_SIZE, 0, this->size - 1);

    uint32_t s_y = rr_fclamp((fy - fh - SPATIAL_HASH_GRID_SIZE) / SPATIAL_HASH_GRID_SIZE, 0, this->size - 1);

    uint32_t e_x = rr_fclamp((fx + fw + SPATIAL_HASH_GRID_SIZE) / SPATIAL_HASH_GRID_SIZE, 0, this->size - 1);

    uint32_t e_y = rr_fclamp((fy + fh + SPATIAL_HASH_GRID_SIZE) / SPATIAL_HASH_GRID_SIZE, 0, this->size - 1);

    for (uint32_t y = s_y; y <= e_y; y++)
        for (uint32_t x = s_x; x <= e_x; x++)
        {
            struct rr_spatial_hash_cell *cell = spatial_hash_get(x,y);
            for (uint64_t i = 0; i < cell->entities_in_use; i++)
                cb(cell->entities[i], user_captures);
        }
}

void rr_spatial_hash_find_possible_collisions(
    struct rr_spatial_hash *this, void *user_captures,
    void (*cb)(struct rr_simulation *, EntityIdx, EntityIdx, void *))
{
    for (uint64_t x = 0; x < this->size; ++x)
    {
        for (uint64_t y = 0; y < this->size; ++y)
        {
            struct rr_spatial_hash_cell *cell = spatial_hash_get(x,y);
            for (uint64_t i = 0; i < cell->entities_in_use; ++i)
            {
                for (uint64_t j = i + 1; j < cell->entities_in_use; ++j)
                    cb(this->simulation, cell->entities[i], cell->entities[j], user_captures);
                if (x > 0)
                {
                    struct rr_spatial_hash_cell *adj = spatial_hash_get(x-1,y);
                    for (uint64_t j = 0; j < adj->entities_in_use; ++j)
                        cb(this->simulation, cell->entities[i], adj->entities[j], user_captures);
                    if (y > 0)
                    {
                        struct rr_spatial_hash_cell *adj = spatial_hash_get(x-1,y-1);
                        for (uint64_t j = 0; j < adj->entities_in_use; ++j)
                            cb(this->simulation, cell->entities[i], adj->entities[j], user_captures);
                    }
                }
                if (y > 0)
                {
                    struct rr_spatial_hash_cell *adj = spatial_hash_get(x,y-1);
                    for (uint64_t j = 0; j < adj->entities_in_use; ++j)
                        cb(this->simulation, cell->entities[i], adj->entities[j], user_captures);
                    if (x + 1 < this->size)
                    {
                        struct rr_spatial_hash_cell *adj = spatial_hash_get(x+1,y-1);
                        for (uint64_t j = 0; j < adj->entities_in_use; ++j)
                            cb(this->simulation, cell->entities[i], adj->entities[j], user_captures);
                    }
                }
            }
        }
    }
}

void rr_spatial_hash_reset(struct rr_spatial_hash *this)
{
    for (uint64_t i = 0; i < this->size; i++)
        for (uint64_t j = 0; j < this->size; j++)
            this->cells[i*this->size+j].entities_in_use = 0;
    // memset(&this->cells, 0, sizeof this->cells);
}