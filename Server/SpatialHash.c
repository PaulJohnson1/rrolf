#include <Server/SpatialHash.h>

#include <math.h>
#include <string.h>

#include <Shared/Bitset.h>
#include <Shared/SimulationCommon.h>

void rr_spatial_hash_init(struct rr_spatial_hash *this)
{
    memset(this, 0, sizeof *this);
}

void rr_spatial_hash_insert(struct rr_spatial_hash *this, EntityIdx entity)
{
    struct rr_component_physical *physical =
        rr_simulation_get_physical(this->simulation, entity);

    if (physical->x < physical->radius || physical->y < physical->radius) //add other checks
        return;
    // force positions unsigned for a significantly better hash function
    uint32_t x = physical->x / SPATIAL_HASH_GRID_SIZE;
    uint32_t y = physical->y / SPATIAL_HASH_GRID_SIZE;
    struct rr_spatial_hash_cell *cell = &this->cells[x][y];
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
    uint32_t s_x = (((uint32_t)(x)) / SPATIAL_HASH_GRID_SIZE);
    if (s_x > 0)
        s_x -= 1;
    else
        s_x = 0;

    uint32_t s_y = (((uint32_t)(y)) / SPATIAL_HASH_GRID_SIZE);
    if (s_y > 0)
        s_y -= 1;
    else
        s_y = 0;

    uint32_t e_x = (((uint32_t)(x + 2 * fw)) / SPATIAL_HASH_GRID_SIZE);
    if (e_x < RR_SPATIAL_HASH_GRID_LENGTH - 1)
        e_x += 1;
    else
        e_x = RR_SPATIAL_HASH_GRID_LENGTH - 1;

    uint32_t e_y = (((uint32_t)(y + 2 * fh)) / SPATIAL_HASH_GRID_SIZE);
    if (e_y < RR_SPATIAL_HASH_GRID_LENGTH - 1)
        e_y += 1;
    else
        e_y = RR_SPATIAL_HASH_GRID_LENGTH - 1;

    for (uint32_t y = s_y; y <= e_y; y++)
        for (uint32_t x = s_x; x <= e_x; x++)
        {
            struct rr_spatial_hash_cell *cell = &this->cells[x][y];
            for (uint64_t i = 0; i < cell->entities_in_use; i++)
            {
                cb(cell->entities[i], user_captures);
            }
        }
}

void rr_spatial_hash_find_possible_collisions(
    struct rr_spatial_hash *this, void *user_captures,
    void (*cb)(struct rr_simulation *, EntityIdx, EntityIdx, void *))
{
    for (uint64_t x = 0; x < RR_SPATIAL_HASH_GRID_LENGTH; ++x)
    {
        for (uint64_t y = 0; y < RR_SPATIAL_HASH_GRID_LENGTH; ++y)
        {
            struct rr_spatial_hash_cell *cell = &this->cells[x][y];
            for (uint64_t i = 0; i < cell->entities_in_use; ++i)
            {
                for (uint64_t j = i + 1; j < cell->entities_in_use; ++j)
                    cb(this->simulation, cell->entities[i], cell->entities[j], user_captures);
                if (x > 0)
                {
                    struct rr_spatial_hash_cell *adj = &this->cells[x-1][y];
                    for (uint64_t j = 0; j < adj->entities_in_use; ++j)
                        cb(this->simulation, cell->entities[i], adj->entities[j], user_captures);
                    if (y > 0)
                    {
                        struct rr_spatial_hash_cell *adj = &this->cells[x-1][y-1];
                        for (uint64_t j = 0; j < adj->entities_in_use; ++j)
                            cb(this->simulation, cell->entities[i], adj->entities[j], user_captures);
                    }
                }
                if (y > 0)
                {
                    struct rr_spatial_hash_cell *adj = &this->cells[x][y-1];
                    for (uint64_t j = 0; j < adj->entities_in_use; ++j)
                        cb(this->simulation, cell->entities[i], adj->entities[j], user_captures);
                    if (x < RR_SPATIAL_HASH_GRID_LENGTH - 1)
                    {
                        struct rr_spatial_hash_cell *adj = &this->cells[x+1][y-1];
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
    for (uint64_t i = 0; i < RR_SPATIAL_HASH_GRID_LENGTH; i++)
        for (uint64_t j = 0; j < RR_SPATIAL_HASH_GRID_LENGTH; j++)
            this->cells[i][j].entities_in_use = 0;
    // memset(&this->cells, 0, sizeof this->cells);
}