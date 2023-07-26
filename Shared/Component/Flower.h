#pragma once

#include <Shared/Component/Common.h>
#include <Shared/Entity.h>
#include <Shared/Utilities.h>

struct rr_simulation;
struct proto_bug;
RR_CLIENT_ONLY(struct rr_renderer;)

struct rr_component_flower
{
    EntityIdx parent_id;
    uint8_t face_flags;
    RR_SERVER_ONLY(uint8_t protocol_state;)
    float eye_angle;
    RR_CLIENT_ONLY(float eye_x;)
    RR_CLIENT_ONLY(float lerp_eye_x;)
    RR_CLIENT_ONLY(float eye_y;)
    RR_CLIENT_ONLY(float lerp_eye_y;)
    RR_CLIENT_ONLY(float lerp_mouth;)
};

void rr_component_flower_init(struct rr_component_flower *,
                              struct rr_simulation *);
void rr_component_flower_free(struct rr_component_flower *,
                              struct rr_simulation *);

RR_SERVER_ONLY(void rr_component_flower_write(struct rr_component_flower *,
                                              struct proto_bug *, int);)
RR_CLIENT_ONLY(void rr_component_flower_read(struct rr_component_flower *,
                                             struct proto_bug *);)

RR_DECLARE_PUBLIC_FIELD(flower, uint8_t, face_flags)
RR_DECLARE_PUBLIC_FIELD(flower, uint8_t, client_id)
RR_DECLARE_PUBLIC_FIELD(flower, float, eye_angle)