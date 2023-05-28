#pragma once

#include <Shared/Component/Common.h>
#include <Shared/Entity.h>
#include <Shared/Utilities.h>

struct rr_simulation;
struct proto_bug;
RR_CLIENT_ONLY(struct rr_renderer;)

enum rr_ai_state
{
    rr_ai_state_idle,
    rr_ai_state_idle_moving
};

struct rr_component_ai
{
                   EntityIdx parent_id;
    RR_SERVER_ONLY(uint32_t ticks_until_next_action;)
    RR_SERVER_ONLY(enum rr_ai_state ai_state;)
    RR_SERVER_ONLY(uint64_t protocol_state;)
};

void rr_component_ai_init(struct rr_component_ai *);
void rr_component_ai_free(struct rr_component_ai *, struct rr_simulation *);

RR_SERVER_ONLY(void rr_component_ai_write(struct rr_component_ai *, struct proto_bug *, int);)
RR_CLIENT_ONLY(void rr_component_ai_read(struct rr_component_ai *, struct proto_bug *);)
