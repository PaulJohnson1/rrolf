#pragma once

#include <Shared/Entity.h>

#define RR_SPATIAL_HASH_CELL_COUNT (256)
#define RR_SPATIAL_HASH_CELL_MAX_ENTITY_COUNT (RR_MAX_COLLISION_COUNT)

struct rr_simulation;

struct rr_spatial_hash_cell
{
    uint32_t entities_in_use;
    EntityIdx entities[RR_SPATIAL_HASH_CELL_MAX_ENTITY_COUNT];
};

struct rr_spatial_hash
{
    struct rr_spatial_hash_cell cells[RR_SPATIAL_HASH_CELL_COUNT];
    struct rr_simulation *simulation;
    uint32_t query_id;
};

void rr_spatial_hash_init(struct rr_spatial_hash *);
void rr_spatial_hash_insert(struct rr_spatial_hash *, EntityIdx);
void rr_spatial_hash_update(struct rr_spatial_hash *, EntityIdx);
void rr_spatial_hash_query(struct rr_spatial_hash *, float, float, float, float, void *user_captures, void (*)(struct rr_simulation *, EntityIdx, void *));
void rr_spatial_hash_find_possible_collisions(struct rr_spatial_hash *this, void *user_captures, void (*cb)(struct rr_simulation *, EntityIdx, EntityIdx, void *));
void rr_spatial_hash_reset(struct rr_spatial_hash *);
