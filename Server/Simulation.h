#pragma once

#include <Shared/Component/Physical.h>
#include <Shared/Component/PlayerInfo.h>
#include <Shared/Encoder.h>
#include <Shared/Entity.h>

#include <Server/SpatialHash.h>

// spatial hashing wil go in a different collisiion detection system (ecs) :(

struct rr_simulation
{
    // bitset
    uint8_t entity_tracker[MAX_ENTITY_COUNT >> 3];
    // uint8_t entity_tracker[MAX_ENTITY_COUNT];

#define XX(COMPONENT, ID) \
    uint8_t COMPONENT##_tracker[MAX_ENTITY_COUNT >> 3];
    FOR_EACH_COMPONENT;
#undef XX

#define XX(COMPONENT, ID) \
    struct rr_component_##COMPONENT COMPONENT##_components[MAX_ENTITY_COUNT];
    FOR_EACH_COMPONENT;
#undef XX
};

void rr_simulation_init(struct rr_simulation *);

EntityIdx rr_simulation_alloc_entity(struct rr_simulation *);
int rr_simulation_has_entity(struct rr_simulation *, EntityIdx);
void rr_simulation_free_entity(struct rr_simulation *, EntityIdx);

void rr_simulation_write_binary(struct rr_simulation *, struct rr_encoder *, struct rr_component_player_info *);
void rr_simulation_tick(struct rr_simulation *);

#define XX(COMPONENT, ID)                                                                              \
    int rr_simulation_has_##COMPONENT(struct rr_simulation *, EntityIdx);                              \
    struct rr_component_##COMPONENT *rr_simulation_add_##COMPONENT(struct rr_simulation *, EntityIdx); \
    struct rr_component_##COMPONENT *rr_simulation_get_##COMPONENT(struct rr_simulation *, EntityIdx);
FOR_EACH_COMPONENT;
#undef XX

void rr_simulation_for_each_entity(struct rr_simulation *, void *, void (*cb)(EntityIdx, void *));
