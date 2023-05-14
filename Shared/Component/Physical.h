#pragma once

#include <Shared/Component/Common.h>
#include <Shared/Entity.h>
#include <Shared/Vector.h>
#include <Shared/Utilities.h>

struct rr_simulation;
struct rr_encoder;

// check if there's rr_component_physical_set function before setting a field
struct rr_component_physical
{
                   EntityIdx parent_id;
                   float radius;
    RR_CLIENT_ONLY(float lerp_radius;)
                   float x;
    RR_CLIENT_ONLY(float lerp_x;)
                   float y;
    RR_CLIENT_ONLY(float lerp_y;)
                   float angle;
    RR_CLIENT_ONLY(float lerp_angle;)
    RR_SERVER_ONLY(float friction;)
    RR_SERVER_ONLY(float restitution;)
    RR_SERVER_ONLY(float mass;)
                   uint32_t deletion_tick;
    RR_SERVER_ONLY(uint32_t query_id;)
    RR_SERVER_ONLY(EntityIdx *colliding_with_start;)
    RR_SERVER_ONLY(EntityIdx *colliding_with_end;)
    RR_SERVER_ONLY(EntityIdx *colliding_with_end_of_storage;)
    RR_SERVER_ONLY(uint64_t protocol_state;)
    RR_SERVER_ONLY(struct rr_vector velocity;)
    RR_SERVER_ONLY(struct rr_vector acceleration;)
};

void rr_component_physical_init(struct rr_component_physical *);
void rr_component_physical_free(struct rr_component_physical *);

RR_SERVER_ONLY(void rr_component_physical_write(struct rr_component_physical *, struct rr_encoder *, int is_creation);)
RR_CLIENT_ONLY(void rr_component_physical_read(struct rr_component_physical *, struct rr_encoder *);)

RR_DECLARE_PUBLIC_FIELD(physical, float, x)
RR_DECLARE_PUBLIC_FIELD(physical, float, y)
RR_DECLARE_PUBLIC_FIELD(physical, float, angle)
RR_DECLARE_PUBLIC_FIELD(physical, float, radius)
RR_DECLARE_PUBLIC_FIELD(physical, uint32_t, deletion_tick)
