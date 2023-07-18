#pragma once

#include <Shared/Component/Common.h>
#include <Shared/Entity.h>
#include <Shared/Utilities.h>

struct rr_simulation;
struct proto_bug;
RR_CLIENT_ONLY(struct rr_renderer;)

struct rr_component_arena
{
    // points to u32 of rarity_id_max * mob_id_max
    uint32_t *mob_counters;
    RR_SERVER_ONLY(uint32_t mob_count);
    EntityIdx parent_id;
    uint16_t wave_tick;
    RR_SERVER_ONLY(uint16_t protocol_state;)
    uint16_t wave;
    float radius;
};

void rr_component_arena_init(struct rr_component_arena *,
                             struct rr_simulation *);
void rr_component_arena_free(struct rr_component_arena *,
                             struct rr_simulation *);

RR_SERVER_ONLY(void rr_component_arena_write(struct rr_component_arena *,
                                             struct proto_bug *, int);)
RR_CLIENT_ONLY(void rr_component_arena_read(struct rr_component_arena *,
                                            struct proto_bug *);)

RR_DECLARE_PUBLIC_FIELD(arena, float, radius)
RR_DECLARE_PUBLIC_FIELD(arena, uint16_t, wave_tick)
RR_DECLARE_PUBLIC_FIELD(arena, uint16_t, wave)