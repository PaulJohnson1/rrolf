#pragma once

#include <Shared/Component/Common.h>
#include <Shared/Entity.h>
#include <Shared/StaticData.h>
#include <Shared/Utilities.h>

struct rr_simulation;
struct proto_bug;
RR_CLIENT_ONLY(struct rr_renderer;)
RR_SERVER_ONLY(struct rr_component_player_info;)

struct rr_component_centipede
{
    EntityIdx parent_id;
    uint8_t is_head;
    RR_SERVER_ONLY(uint8_t protocol_state;)
    RR_SERVER_ONLY(EntityHash child_node;)
    RR_SERVER_ONLY(EntityHash parent_node;)
};

void rr_component_centipede_init(struct rr_component_centipede *,
                                 struct rr_simulation *);
void rr_component_centipede_free(struct rr_component_centipede *,
                                 struct rr_simulation *);

RR_SERVER_ONLY(void rr_component_centipede_write(
                   struct rr_component_centipede *, struct proto_bug *, int,
                   struct rr_component_player_info *);)
RR_CLIENT_ONLY(void rr_component_centipede_read(struct rr_component_centipede *,
                                                struct proto_bug *);)

RR_DECLARE_PUBLIC_FIELD(centipede, uint8_t, is_head)