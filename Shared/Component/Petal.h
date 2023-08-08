#pragma once

#include <Shared/Component/Common.h>
#include <Shared/Entity.h>
#include <Shared/StaticData.h>
#include <Shared/Utilities.h>

struct rr_simulation;
struct proto_bug;
RR_CLIENT_ONLY(struct rr_renderer;)
RR_SERVER_ONLY(struct rr_component_player_info;)

struct rr_component_petal
{
    EntityIdx parent_id;
    RR_SERVER_ONLY(int8_t spin_ccw;)
    uint8_t detached;
    uint8_t id;
    uint8_t rarity;
    RR_SERVER_ONLY(uint16_t protocol_state;)
    RR_SERVER_ONLY(int32_t effect_delay;)
};

void rr_component_petal_init(struct rr_component_petal *,
                             struct rr_simulation *);
void rr_component_petal_free(struct rr_component_petal *,
                             struct rr_simulation *);

RR_SERVER_ONLY(void rr_component_petal_write(
                   struct rr_component_petal *, struct proto_bug *, int,
                   struct rr_component_player_info *);)
RR_CLIENT_ONLY(void rr_component_petal_read(struct rr_component_petal *,
                                            struct proto_bug *);)

RR_DECLARE_PUBLIC_FIELD(petal, uint8_t, id)
RR_DECLARE_PUBLIC_FIELD(petal, uint8_t, rarity)
RR_DECLARE_PUBLIC_FIELD(petal, uint8_t, detached)