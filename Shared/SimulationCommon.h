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
#include <Shared/Component/Relations.h>
#include <Shared/Component/Web.h>
#include <Shared/Entity.h>
#include <Shared/Utilities.h>

#ifdef RR_SERVER
#include <Shared/Vector.h>
struct rr_spatial_hash;

struct rr_simulation_animation
{
    uint8_t type;
    uint8_t length;
    struct rr_vector points[16];
};
#endif

enum rr_simulation_team_id
{
    rr_simulation_team_id_mobs,
    rr_simulation_team_id_players
};

struct rr_simulation
{
    uint16_t entity_tracker[RR_MAX_ENTITY_COUNT];
    uint8_t pending_deletions[RR_BITSET_ROUND(RR_MAX_ENTITY_COUNT)];
    RR_SERVER_ONLY(uint8_t deleted_last_tick[RR_BITSET_ROUND(RR_MAX_ENTITY_COUNT)];)

#define XX(COMPONENT, ID)                                                      \
    struct rr_component_##COMPONENT                                            \
        COMPONENT##_components[RR_MAX_ENTITY_COUNT];                           \
    EntityIdx COMPONENT##_vector[RR_MAX_ENTITY_COUNT];                         \
    EntityIdx COMPONENT##_count;
    RR_FOR_EACH_COMPONENT;
#undef XX
    RR_SERVER_ONLY(uint32_t wave_points;)
    RR_SERVER_ONLY(uint32_t special_wave_id;)
    RR_SERVER_ONLY(struct rr_simulation_animation animations[512];)
    RR_SERVER_ONLY(uint32_t animation_length;)
    RR_CLIENT_ONLY(uint8_t updated_this_tick;)
    uint8_t game_over;
    uint8_t biome;
};

void rr_simulation_init(struct rr_simulation *);
int rr_simulation_has_entity(struct rr_simulation *, EntityIdx);
void rr_simulation_request_entity_deletion(struct rr_simulation *, EntityIdx);
void rr_simulation_for_each_entity(struct rr_simulation *, void *,
                                   void (*)(EntityIdx, void *));
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
                                            void (*)(EntityIdx, void *));
RR_FOR_EACH_COMPONENT
#undef XX
