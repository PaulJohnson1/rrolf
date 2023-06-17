#pragma once

#include <Shared/Component/Common.h>
#include <Shared/Bitset.h>
#include <Shared/Entity.h>
#include <Shared/Utilities.h>

struct rr_simulation;
struct proto_bug;
RR_CLIENT_ONLY(struct rr_renderer;)

struct rr_component_drop
{
                   EntityIdx parent_id;
                   uint8_t id;
                   uint8_t rarity:7;
    RR_CLIENT_ONLY(uint8_t hidden:1;)
    RR_SERVER_ONLY(uint8_t picked_up_by[RR_BITSET_ROUND(RR_MAX_ENTITY_COUNT)];)
    RR_SERVER_ONLY(uint8_t picked_up_this_tick[RR_BITSET_ROUND(RR_MAX_ENTITY_COUNT)];)
    RR_SERVER_ONLY(int16_t ticks_until_despawn;)
    RR_SERVER_ONLY(uint16_t protocol_state;)
    RR_SERVER_ONLY(EntityIdx inspecting;)
};

void rr_component_drop_init(struct rr_component_drop *, struct rr_simulation *);
void rr_component_drop_free(struct rr_component_drop *, struct rr_simulation *);

RR_SERVER_ONLY(void rr_component_drop_write(struct rr_component_drop *, struct proto_bug *, int);)
RR_CLIENT_ONLY(void rr_component_drop_read(struct rr_component_drop *, struct proto_bug *);)

RR_DECLARE_PUBLIC_FIELD(drop, uint8_t, id)
RR_DECLARE_PUBLIC_FIELD(drop, uint8_t, rarity)