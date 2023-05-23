#pragma once

#include <Shared/Component/Common.h>
#include <Shared/Entity.h>
#include <Shared/Utilities.h>

struct rr_simulation;
struct rr_encoder;
RR_CLIENT_ONLY(struct rr_renderer;)

struct rr_component_health
{
                   EntityIdx parent_id;
                   float health;
                   float max_health;
    RR_SERVER_ONLY(float damage;)
    RR_CLIENT_ONLY(float lerp_health;)
    RR_SERVER_ONLY(uint64_t protocol_state;)
};

void rr_component_health_init(struct rr_component_health *);
void rr_component_health_free(struct rr_component_health *);

RR_SERVER_ONLY(void rr_component_health_write(struct rr_component_health *, struct rr_encoder *, int is_creation);)
RR_CLIENT_ONLY(void rr_component_health_read(struct rr_component_health *, struct rr_encoder *);)

RR_DECLARE_PUBLIC_FIELD(health, float, health)
RR_DECLARE_PUBLIC_FIELD(health, float, max_health)