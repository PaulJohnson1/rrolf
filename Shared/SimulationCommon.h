#pragma once

#include <Shared/Component/Ai.h>
#include <Shared/Component/Arena.h>
#include <Shared/Component/Centipede.h>
#include <Shared/Component/Flower.h>
#include <Shared/Component/Health.h>
#include <Shared/Component/Mob.h>
#include <Shared/Component/Petal.h>
#include <Shared/Component/Physical.h>
#include <Shared/Component/PlayerInfo.h>
#include <Shared/Component/Projectile.h>
#include <Shared/Component/Relations.h>
#include <Shared/Entity.h>
#include <Shared/Utilities.h>

#ifdef RR_SERVER
#include <Server/SpatialHash.h>
#endif

struct rr_simulation
{
    uint8_t entity_tracker[RR_MAX_ENTITY_COUNT >> 3];
    RR_SERVER_ONLY(uint8_t pending_deletions[RR_MAX_ENTITY_COUNT >> 3]);
    RR_SERVER_ONLY(EntityIdx arena;)
    RR_CLIENT_ONLY(EntityIdx player_info);

#define XX(COMPONENT, ID) \
    uint8_t COMPONENT##_tracker[RR_MAX_ENTITY_COUNT >> 3];
    RR_FOR_EACH_COMPONENT;
#undef XX

#define XX(COMPONENT, ID) \
    struct rr_component_##COMPONENT COMPONENT##_components[RR_MAX_ENTITY_COUNT];
    RR_FOR_EACH_COMPONENT;
#undef XX

    RR_SERVER_ONLY(struct hshg spatial_hash_grid;)
};

void rr_simulation_init(struct rr_simulation *);

void rr_simulation_free_entity(struct rr_simulation *, EntityIdx);
int rr_simulation_has_entity(struct rr_simulation *, EntityIdx);

void rr_simulation_for_each_entity(struct rr_simulation *, void *, void (*cb)(EntityIdx, void *));

#define XX(COMPONENT, ID)                                                                              \
    uint8_t rr_simulation_has_##COMPONENT(struct rr_simulation *, EntityIdx);                          \
    struct rr_component_##COMPONENT *rr_simulation_add_##COMPONENT(struct rr_simulation *, EntityIdx); \
    struct rr_component_##COMPONENT *rr_simulation_get_##COMPONENT(struct rr_simulation *, EntityIdx);
RR_FOR_EACH_COMPONENT
#undef XX
