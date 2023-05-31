#include <string.h>

#include <Server/SpatialHash.h>
#include <Shared/SimulationCommon.h>
#include <Shared/Bitset.h>

#define SPATIAL_HASH_GRID_SIZE 8
#define HASH_FUNCTION(X, Y) (Y + 73 * X)

void rr_spatial_hash_init(struct rr_spatial_hash *this)
{
    memset(this, 0, sizeof *this);
}

void rr_spatial_hash_insert(struct rr_spatial_hash *this, EntityIdx entity)
{
    struct rr_component_physical *physical = rr_simulation_get_physical(this->simulation, entity);
    // force positions unsigned for a significantly better hash function
    uint32_t x = (uint32_t)(physical->x + 8192.0f);
    uint32_t y = (uint32_t)(physical->y + 8192.0f);
    uint32_t w = (uint32_t)(physical->radius);
    uint32_t h = w;

    uint32_t s_x = ((x - w) >> SPATIAL_HASH_GRID_SIZE);
    uint32_t s_y = ((y - h) >> SPATIAL_HASH_GRID_SIZE);
    uint32_t e_x = ((x + w) >> SPATIAL_HASH_GRID_SIZE);
    uint32_t e_y = ((y + h) >> SPATIAL_HASH_GRID_SIZE);

    for (uint32_t y = s_y; y <= e_y; y++)
        for (uint32_t x = s_x; x <= e_x; x++)
        {
            uint32_t hash = HASH_FUNCTION(x, y) % RR_SPATIAL_HASH_CELL_COUNT;
            struct rr_spatial_hash_cell *cell = this->cells + hash;
            if (cell->entities_in_use >= RR_SPATIAL_HASH_CELL_MAX_ENTITY_COUNT)
                continue;
            cell->entities[cell->entities_in_use] = entity;
            cell->entities_in_use++;
        }
}

void rr_spatial_hash_query(struct rr_spatial_hash *this, float fx, float fy, float fw, float fh, void *user_captures, void (*cb)(struct rr_simulation *, EntityIdx, void *))
{
    uint32_t x = fx + 8192.0f;
    uint32_t y = fy + 8192.0f;
    uint32_t w = fw;
    uint32_t h = fh;
    // should not take in an entity id like insert does. the reason is so stuff like ai can query a large radius without a viewing entity
    uint32_t s_x = ((x - w) >> SPATIAL_HASH_GRID_SIZE);
    uint32_t s_y = ((y - h) >> SPATIAL_HASH_GRID_SIZE);
    uint32_t e_x = ((x + w) >> SPATIAL_HASH_GRID_SIZE);
    uint32_t e_y = ((y + h) >> SPATIAL_HASH_GRID_SIZE);

    for (uint32_t y = s_y; y <= e_y; y++)
        for (uint32_t x = s_x; x <= e_x; x++)
        {
            uint32_t hash = HASH_FUNCTION(x, y) % RR_SPATIAL_HASH_CELL_COUNT;
            struct rr_spatial_hash_cell *cell = this->cells + hash;
            for (uint64_t i = 0; i < cell->entities_in_use; i++)
            {
                struct rr_component_physical *physical = rr_simulation_get_physical(this->simulation, cell->entities[i]);
                if (physical->query_id != this->query_id)
                {
                    physical->query_id = this->query_id;
                    cb(this->simulation, physical->parent_id, user_captures);
                }
            }
        }

    this->query_id++;
}

void rr_spatial_hash_find_possible_collisions(struct rr_spatial_hash *this, void *user_captures, void (*cb)(struct rr_simulation *, EntityIdx, EntityIdx, void *))
{
    for (uint64_t i = 0; i < RR_SPATIAL_HASH_CELL_COUNT; i++)
    {
        struct rr_spatial_hash_cell *cell = this->cells + i;
        for (uint64_t j = 0; j < cell->entities_in_use; j++)
        {
            EntityIdx a = cell->entities[j];
            for (uint64_t k = j + 1; k < cell->entities_in_use; k++)
            {
                EntityIdx b = cell->entities[k];
                cb(this->simulation, a, b, user_captures);
            }
        }
    }
}

void rr_spatial_hash_reset(struct rr_spatial_hash *this)
{
    memset(&this->cells, 0, sizeof this->cells);
}
