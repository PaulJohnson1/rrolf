#pragma once

#include <Shared/Component/Arena.h>
#include <Shared/Component/Flower.h>
#include <Shared/Component/Physical.h>
#include <Shared/Component/PlayerInfo.h>
#include <Shared/Encoder.h>
#include <Shared/Entity.h>

struct rr_simulation
{
    uint8_t entity_tracker[RR_MAX_ENTITY_COUNT >> 3];
    RR_SERVER_ONLY(EntityIdx arena;) // maybe we can assume it's 1 if ths is messy

#define XX(COMPONENT, ID) \
    uint8_t COMPONENT##_tracker[RR_MAX_ENTITY_COUNT >> 3];
    RR_FOR_EACH_COMPONENT;
#undef XX

#define XX(COMPONENT, ID) \
    struct rr_component_##COMPONENT COMPONENT##_components[RR_MAX_ENTITY_COUNT];
    RR_FOR_EACH_COMPONENT;
#undef XX
};

void rr_simulation_init(struct rr_simulation *);

void rr_simulation_free_entity(struct rr_simulation *, EntityIdx);
int rr_simulation_has_entity(struct rr_simulation *, EntityIdx);

void rr_simulation_for_each_entity(struct rr_simulation *, void *, void (*cb)(EntityIdx, void *));

#define XX(COMPONENT, ID)                                                                              \
    int rr_simulation_has_##COMPONENT(struct rr_simulation *, EntityIdx);                              \
    struct rr_component_##COMPONENT *rr_simulation_add_##COMPONENT(struct rr_simulation *, EntityIdx); \
    struct rr_component_##COMPONENT *rr_simulation_get_##COMPONENT(struct rr_simulation *, EntityIdx);
RR_FOR_EACH_COMPONENT
#undef XX
