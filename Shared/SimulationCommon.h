#pragma once

#include <Shared/Component/Ai.h>
#include <Shared/Component/Arena.h>
#include <Shared/Component/Centipede.h>
#include <Shared/Component/Drop.h>
#include <Shared/Component/Flower.h>
#include <Shared/Component/Health.h>
#include <Shared/Component/Mob.h>
#include <Shared/Component/Petal.h>
#include <Shared/Component/Physical.h>
#include <Shared/Component/PlayerInfo.h>
#include <Shared/Component/Projectile.h>
#include <Shared/Component/Relations.h>
#include <Shared/Component/Web.h>
#include <Shared/Entity.h>
#include <Shared/Utilities.h>

#ifdef RR_SERVER
struct rr_spatial_hash;
#endif

enum rr_simulation_team_id
{
    rr_simulation_team_id_mobs,
    rr_simulation_team_id_players
};

struct rr_simulation
{
    uint8_t entity_tracker[RR_BITSET_ROUND(RR_MAX_ENTITY_COUNT)];
    uint8_t pending_deletions[RR_BITSET_ROUND(RR_MAX_ENTITY_COUNT)];
    RR_SERVER_ONLY(
        uint8_t recently_deleted[RR_BITSET_ROUND(RR_MAX_ENTITY_COUNT)];)

#define XX(COMPONENT, ID)                                                      \
    uint8_t COMPONENT##_tracker[RR_BITSET_ROUND(RR_MAX_ENTITY_COUNT)];
    RR_FOR_EACH_COMPONENT;
#undef XX

#define XX(COMPONENT, ID)                                                      \
    struct rr_component_##COMPONENT COMPONENT##_components[RR_MAX_ENTITY_COUNT]; \
    EntityIdx COMPONENT##_vector[RR_MAX_ENTITY_COUNT];                           \
    EntityIdx COMPONENT##_count;
    RR_FOR_EACH_COMPONENT;
#undef XX

    RR_SERVER_ONLY(struct rr_spatial_hash *grid;)
    RR_SERVER_ONLY(uint32_t wave_points;)
    uint8_t game_over;
};

void rr_simulation_init(struct rr_simulation *);
int rr_simulation_has_entity(struct rr_simulation *, EntityIdx);
void rr_simulation_request_entity_deletion(struct rr_simulation *, EntityIdx);
void rr_simulation_for_each_entity(struct rr_simulation *, void *,
                                   void (*cb)(EntityIdx, void *));
void rr_simulation_create_component_vectors(struct rr_simulation *);

// internal use
void __rr_simulation_pending_deletion_free_components(uint64_t, void *);
void __rr_simulation_pending_deletion_unset_entity(uint64_t, void *);

#define XX(COMPONENT, ID)                                                      \
    uint8_t rr_simulation_has_##COMPONENT(struct rr_simulation *, EntityIdx);  \
    struct rr_component_##COMPONENT *rr_simulation_add_##COMPONENT(            \
        struct rr_simulation *, EntityIdx);                                    \
    struct rr_component_##COMPONENT *rr_simulation_get_##COMPONENT(            \
        struct rr_simulation *, EntityIdx);                                    \
    void rr_simulation_for_each_##COMPONENT(struct rr_simulation *, void *,    \
                                            void (*cb)(EntityIdx, void *));
RR_FOR_EACH_COMPONENT
#undef XX
