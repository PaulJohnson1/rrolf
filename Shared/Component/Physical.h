#pragma once

#include <Shared/Component/Common.h>
#include <Shared/Bitset.h>
#include <Shared/Entity.h>
#include <Shared/Vector.h>
#include <Shared/Utilities.h>

#ifdef RR_CLIENT
#include <Client/Game.h>
#endif

struct rr_simulation;
struct proto_bug;

// check if there's rr_component_physical_set function before setting a field
struct rr_component_physical
{
    RR_SERVER_ONLY(struct rr_vector velocity;)
    RR_SERVER_ONLY(struct rr_vector acceleration;)
    RR_SERVER_ONLY(uint64_t protocol_state;)
                   uint32_t deletion_tick;
    RR_SERVER_ONLY(float mass;)
    RR_SERVER_ONLY(float restitution;)
    RR_SERVER_ONLY(float friction;)
                   float angle;
    RR_CLIENT_ONLY(float lerp_angle;)
                   float x;
    RR_CLIENT_ONLY(float lerp_x;)
                   float y;
    RR_CLIENT_ONLY(float lerp_y;)
                   float radius;
    RR_CLIENT_ONLY(float lerp_radius;)
                   EntityIdx parent_id;
    RR_SERVER_ONLY(uint8_t collisions[RR_BITSET_ROUND(RR_MAX_ENTITY_COUNT)];)
};

void rr_component_physical_init(struct rr_component_physical *);
void rr_component_physical_free(struct rr_component_physical *, struct rr_simulation *);

RR_SERVER_ONLY(void rr_component_physical_write(struct rr_component_physical *, struct proto_bug *, int is_creation);)
RR_CLIENT_ONLY(void rr_component_physical_read(struct rr_component_physical *, struct proto_bug *);)

RR_DECLARE_PUBLIC_FIELD(physical, float, x)
RR_DECLARE_PUBLIC_FIELD(physical, float, y)
RR_DECLARE_PUBLIC_FIELD(physical, float, angle)
RR_DECLARE_PUBLIC_FIELD(physical, float, radius)
RR_DECLARE_PUBLIC_FIELD(physical, uint32_t, deletion_tick)
