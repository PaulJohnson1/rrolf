#pragma once

#include <Shared/Entity.h>
#include <Shared/StaticData.h>

#define SPATIAL_HASH_GRID_SIZE (512)
#define RR_SPATIAL_HASH_GRID_LENGTH                                            \
    (((RR_ARENA_LENGTH + SPATIAL_HASH_GRID_SIZE - 1) / SPATIAL_HASH_GRID_SIZE))
#define RR_SPATIAL_HASH_CELL_MAX_ENTITY_COUNT (256)

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

void rr_spatial_hash_init(struct rr_spatial_hash *, struct rr_simulation *, uint32_t);
void rr_spatial_hash_insert(struct rr_spatial_hash *, EntityIdx);
void rr_spatial_hash_update(struct rr_spatial_hash *, EntityIdx);
void rr_spatial_hash_query(struct rr_spatial_hash *, float, float, float, float,
                           void *, void (*)(EntityIdx, void *));
void rr_spatial_hash_find_possible_collisions(
    struct rr_spatial_hash *, void *,
    void (*)(struct rr_simulation *, EntityIdx, EntityIdx, void *));
void rr_spatial_hash_reset(struct rr_spatial_hash *);