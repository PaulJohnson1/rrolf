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
    struct rr_spatial_hash_cell *cell = &this->cells[(x >> SPATIAL_HASH_GRID_SIZE) % RR_SPATIAL_HASH_GRID_LENGTH][(y >> SPATIAL_HASH_GRID_SIZE) % RR_SPATIAL_HASH_GRID_LENGTH];
    cell->entities[cell->entities_in_use++] = entity;
}

void rr_spatial_hash_update(struct rr_spatial_hash *this, EntityIdx entity)
{
}

void rr_spatial_hash_query(struct rr_spatial_hash *this, float fx, float fy, float fw, float fh, void *user_captures, void (*cb)(struct rr_simulation *, EntityIdx, void *))
{
    uint32_t x = fx + RR_ARENA_RADIUS;
    uint32_t y = fy + RR_ARENA_RADIUS;
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
            struct rr_spatial_hash_cell *cell = &this->cells[x][y];
            for (uint64_t i = 0; i < cell->entities_in_use; i++)
            {
                struct rr_component_physical *physical = rr_simulation_get_physical(this->simulation, cell->entities[i]);
                cb(this->simulation, physical->parent_id, user_captures);
            }
        }
}

void rr_spatial_hash_find_possible_collisions(struct rr_spatial_hash *this, void *user_captures, void (*cb)(struct rr_simulation *, EntityIdx, EntityIdx, void *))
{
    for (uint64_t i = 0; i < RR_SPATIAL_HASH_GRID_LENGTH - 1; ++i)
    {
        for (uint64_t j = 0; j < RR_SPATIAL_HASH_GRID_LENGTH - 1; ++j)
        {
            struct rr_spatial_hash_cell *cell1 = &this->cells[i][j];
            struct rr_spatial_hash_cell *cell2 = &this->cells[i][j+1];
            struct rr_spatial_hash_cell *cell3 = &this->cells[i+1][j];
            struct rr_spatial_hash_cell *cell4 = &this->cells[i+1][j+1];
            for (uint32_t k = 0; k < cell1->entities_in_use; ++k)
            {
                EntityIdx ent1 = cell1->entities[k];
                for (uint32_t l = k + 1; l < cell1->entities_in_use; ++l)
                    cb(this->simulation, ent1, cell1->entities[l], user_captures);
                
                for (uint32_t l = 0; l < cell2->entities_in_use; ++l)
                    cb(this->simulation, ent1, cell2->entities[l], user_captures);
                
                for (uint32_t l = 0; l < cell3->entities_in_use; ++l)
                    cb(this->simulation, ent1, cell3->entities[l], user_captures);

                for (uint32_t l = 0; l < cell4->entities_in_use; ++l)
                    cb(this->simulation, ent1, cell4->entities[l], user_captures);
            }
        }
    }
}

void rr_spatial_hash_reset(struct rr_spatial_hash *this)
{
    for (uint64_t i = 0; i < RR_SPATIAL_HASH_GRID_LENGTH; i++)
        for (uint64_t j = 0; j < RR_SPATIAL_HASH_GRID_LENGTH; j++)
            this->cells[i][j].entities_in_use = 0;
    //memset(&this->cells, 0, sizeof this->cells);
}
