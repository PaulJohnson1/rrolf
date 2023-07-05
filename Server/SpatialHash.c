#include <Server/SpatialHash.h>

#include <string.h>
#include <math.h>

#include <Shared/SimulationCommon.h>
#include <Shared/Bitset.h>

void rr_spatial_hash_init(struct rr_spatial_hash *this)
{
    memset(this, 0, sizeof *this);
}

void rr_spatial_hash_insert(struct rr_spatial_hash *this, EntityIdx entity)
{
    struct rr_component_physical *physical = rr_simulation_get_physical(this->simulation, entity);

    if (fabsf(physical->x) > RR_ARENA_RADIUS || fabsf(physical->y) > RR_ARENA_RADIUS)
        return;
    // force positions unsigned for a significantly better hash function
    uint32_t x = (uint32_t)(physical->x + RR_ARENA_RADIUS) >> SPATIAL_HASH_GRID_SIZE;
    uint32_t y = (uint32_t)(physical->y + RR_ARENA_RADIUS) >> SPATIAL_HASH_GRID_SIZE;
    struct rr_spatial_hash_cell *cell = &this->cells[x][y];
    cell->entities[cell->entities_in_use++] = entity;
}

void rr_spatial_hash_update(struct rr_spatial_hash *this, EntityIdx entity)
{
}

void rr_spatial_hash_query(struct rr_spatial_hash *this, float fx, float fy, float fw, float fh, void *user_captures, void (*cb)(EntityIdx, void *))
{
    float x = fmaxf(fx + RR_ARENA_RADIUS - fw, 0);
    float y = fmaxf(fy + RR_ARENA_RADIUS - fh, 0);
    // should not take in an entity id like insert does. the reason is so stuff like ai can query a large radius without a viewing entity
    uint32_t s_x = (((uint32_t) (x)) >> SPATIAL_HASH_GRID_SIZE);
    if (s_x >= 3)
        s_x -= 3;
    else
        s_x = 0;

    uint32_t s_y = (((uint32_t) (y)) >> SPATIAL_HASH_GRID_SIZE);
    if (s_y >= 2)
        s_y -= 2;
    else
        s_y = 0;

    uint32_t e_x = (((uint32_t) (x + 2 * fw)) >> SPATIAL_HASH_GRID_SIZE);
    if (e_x < RR_SPATIAL_HASH_GRID_LENGTH - 3)
        e_x += 3;
    else
        e_x = RR_SPATIAL_HASH_GRID_LENGTH - 1;
    
    uint32_t e_y = (((uint32_t) (y + 2 * fh)) >> SPATIAL_HASH_GRID_SIZE);
    if (e_y < RR_SPATIAL_HASH_GRID_LENGTH - 3)
        e_y += 3;
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

void rr_spatial_hash_find_possible_collisions(struct rr_spatial_hash *this, void *user_captures, void (*cb)(struct rr_simulation *, EntityIdx, EntityIdx, void *))
{
    for (uint64_t i = 1; i < RR_SPATIAL_HASH_GRID_LENGTH - 1; ++i)
    {
        for (uint64_t j = 0; j < RR_SPATIAL_HASH_GRID_LENGTH - 1; ++j)
        {
            struct rr_spatial_hash_cell *cell1 = &this->cells[i][j];
            struct rr_spatial_hash_cell *cell2 = &this->cells[i-1][j];
            struct rr_spatial_hash_cell *cell3 = &this->cells[i-1][j+1];
            struct rr_spatial_hash_cell *cell4 = &this->cells[i][j+1];
            struct rr_spatial_hash_cell *cell5 = &this->cells[i+1][j+1];
            struct rr_spatial_hash_cell *cell6 = &this->cells[i+1][j];
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
                
                for (uint32_t l = 0; l < cell5->entities_in_use; ++l)
                    cb(this->simulation, ent1, cell5->entities[l], user_captures);
                
                for (uint32_t l = 0; l < cell6->entities_in_use; ++l)
                    cb(this->simulation, ent1, cell6->entities[l], user_captures);
            }
        }
    }
    //top wall
    for (uint64_t j = 0; j < RR_SPATIAL_HASH_GRID_LENGTH - 1; ++j)
    {
        struct rr_spatial_hash_cell *cell1 = &this->cells[0][j];
        struct rr_spatial_hash_cell *cell4 = &this->cells[0][j+1];
        struct rr_spatial_hash_cell *cell5 = &this->cells[1][j+1];
        struct rr_spatial_hash_cell *cell6 = &this->cells[1][j];
        for (uint32_t k = 0; k < cell1->entities_in_use; ++k)
        {
            EntityIdx ent1 = cell1->entities[k];
            for (uint32_t l = k + 1; l < cell1->entities_in_use; ++l)
                cb(this->simulation, ent1, cell1->entities[l], user_captures);

            for (uint32_t l = 0; l < cell4->entities_in_use; ++l)
                cb(this->simulation, ent1, cell4->entities[l], user_captures);
            
            for (uint32_t l = 0; l < cell5->entities_in_use; ++l)
                cb(this->simulation, ent1, cell5->entities[l], user_captures);
            
            for (uint32_t l = 0; l < cell6->entities_in_use; ++l)
                cb(this->simulation, ent1, cell6->entities[l], user_captures);
        }
    }
    //bottom wall
    for (uint64_t j = 0; j < RR_SPATIAL_HASH_GRID_LENGTH - 1; ++j)
    {
        struct rr_spatial_hash_cell *cell1 = &this->cells[RR_SPATIAL_HASH_GRID_LENGTH - 1][j];
        struct rr_spatial_hash_cell *cell2 = &this->cells[RR_SPATIAL_HASH_GRID_LENGTH - 2][j];
        struct rr_spatial_hash_cell *cell3 = &this->cells[RR_SPATIAL_HASH_GRID_LENGTH - 2][j+1];
        struct rr_spatial_hash_cell *cell4 = &this->cells[RR_SPATIAL_HASH_GRID_LENGTH - 1][j+1];
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
    //right wall
    for (uint64_t j = 1; j < RR_SPATIAL_HASH_GRID_LENGTH - 1; ++j)
    {
        struct rr_spatial_hash_cell *cell1 = &this->cells[RR_SPATIAL_HASH_GRID_LENGTH - 1][j];
        struct rr_spatial_hash_cell *cell3 = &this->cells[RR_SPATIAL_HASH_GRID_LENGTH - 1][j-1];
        struct rr_spatial_hash_cell *cell4 = &this->cells[RR_SPATIAL_HASH_GRID_LENGTH - 1][j+1];
        for (uint32_t k = 0; k < cell1->entities_in_use; ++k)
        {
            EntityIdx ent1 = cell1->entities[k];
            for (uint32_t l = k + 1; l < cell1->entities_in_use; ++l)
                cb(this->simulation, ent1, cell1->entities[l], user_captures);
            
            for (uint32_t l = 0; l < cell3->entities_in_use; ++l)
                cb(this->simulation, ent1, cell3->entities[l], user_captures);

            for (uint32_t l = 0; l < cell4->entities_in_use; ++l)
                cb(this->simulation, ent1, cell4->entities[l], user_captures);
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