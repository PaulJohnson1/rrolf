#pragma once

#include <Shared/Component/Common.h>
#include <Shared/Entity.h>
#include <Shared/Utilities.h>

struct rr_simulation;
struct proto_bug;
RR_CLIENT_ONLY(struct rr_renderer;)
RR_SERVER_ONLY(struct rr_component_player_info;)

struct rr_component_mob
{
    EntityIdx parent_id;
    uint8_t id;
    uint8_t rarity;
    RR_CLIENT_ONLY(uint8_t counted_as_killed;)
    RR_SERVER_ONLY(uint32_t protocol_state;)
};

void rr_component_mob_init(struct rr_component_mob *, struct rr_simulation *);
void rr_component_mob_free(struct rr_component_mob *, struct rr_simulation *);

RR_SERVER_ONLY(void rr_component_mob_write(struct rr_component_mob *,
                                           struct proto_bug *, int, struct rr_component_player_info *);)
RR_CLIENT_ONLY(void rr_component_mob_read(struct rr_component_mob *,
                                          struct proto_bug *);)

RR_DECLARE_PUBLIC_FIELD(mob, uint8_t, id)
RR_DECLARE_PUBLIC_FIELD(mob, uint8_t, rarity)