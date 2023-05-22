#pragma once

#include <Shared/Component/Common.h>
#include <Shared/Entity.h>
#include <Shared/Utilities.h>

struct rr_simulation;
struct rr_encoder;
RR_CLIENT_ONLY(struct rr_renderer;)

struct rr_component_petal
{
                   EntityIdx parent_id;
                   uint8_t id;
                   uint8_t rarity;
                   uint32_t rotation_pos;
    RR_SERVER_ONLY(uint64_t protocol_state;)
};

void rr_component_petal_init(struct rr_component_petal *);
void rr_component_petal_free(struct rr_component_petal *);

RR_SERVER_ONLY(void rr_component_petal_write(struct rr_component_petal *, struct rr_encoder *, int is_creation);)
RR_CLIENT_ONLY(void rr_component_petal_read(struct rr_component_petal *, struct rr_encoder *);)

RR_DECLARE_PUBLIC_FIELD(petal, uint8_t, id)
RR_DECLARE_PUBLIC_FIELD(petal, uint8_t, rarity)