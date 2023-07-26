#pragma once

#include <Shared/Component/Common.h>
#include <Shared/Entity.h>
#include <Shared/StaticData.h>
#include <Shared/Utilities.h>

struct rr_simulation;
struct proto_bug;
RR_CLIENT_ONLY(struct rr_renderer;)

struct rr_component_web
{
    EntityIdx parent_id;
    RR_SERVER_ONLY(int16_t ticks_until_death;)

    RR_SERVER_ONLY(uint32_t protocol_state;)
};

void rr_component_web_init(struct rr_component_web *,
                                  struct rr_simulation *);
void rr_component_web_free(struct rr_component_web *,
                                  struct rr_simulation *);

RR_SERVER_ONLY(void rr_component_web_write(
                   struct rr_component_web *, struct proto_bug *, int);)
RR_CLIENT_ONLY(void rr_component_web_read(
                   struct rr_component_web *, struct proto_bug *);)
