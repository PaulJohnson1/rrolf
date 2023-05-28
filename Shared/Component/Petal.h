#pragma once

#include <Shared/Component/Common.h>
#include <Shared/Entity.h>
#include <Shared/StaticData.h>
#include <Shared/Utilities.h>

struct rr_simulation;
struct proto_bug;
RR_CLIENT_ONLY(struct rr_renderer;)

struct rr_component_petal
{
                   EntityIdx parent_id;
    RR_SERVER_ONLY(int8_t spin_ccw;)
                   uint8_t detached;
                   uint8_t id;
                   uint8_t rarity;
                   uint8_t outer_pos;
                   uint8_t inner_pos;
                   uint32_t rotation_pos;
    RR_SERVER_ONLY(struct rr_petal_data const *petal_data;)
    RR_SERVER_ONLY(uint64_t protocol_state;)
};

void rr_component_petal_init(struct rr_component_petal *);
void rr_component_petal_free(struct rr_component_petal *, struct rr_simulation *);

RR_SERVER_ONLY(void rr_component_petal_write(struct rr_component_petal *, struct proto_bug *, int);)
RR_CLIENT_ONLY(void rr_component_petal_read(struct rr_component_petal *, struct proto_bug *);)

RR_DECLARE_PUBLIC_FIELD(petal, uint8_t, id)
RR_DECLARE_PUBLIC_FIELD(petal, uint8_t, rarity)