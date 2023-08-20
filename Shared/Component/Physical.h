#pragma once

#include <Shared/Bitset.h>
#include <Shared/Component/Common.h>
#include <Shared/Entity.h>
#include <Shared/Utilities.h>
#include <Shared/Vector.h>

#ifdef RR_CLIENT
#include <Client/Game.h>
#endif

struct rr_simulation;
struct proto_bug;

RR_SERVER_ONLY(struct rr_component_player_info;)

struct rr_component_physical
{
    struct rr_vector velocity;
    RR_CLIENT_ONLY(struct rr_vector lerp_velocity;)
    RR_SERVER_ONLY(struct rr_vector acceleration;)
    RR_SERVER_ONLY(float mass;)
    RR_SERVER_ONLY(float knockback_scale;)
    RR_SERVER_ONLY(float friction;)
    RR_SERVER_ONLY(float acceleration_scale;)
    float angle;
    RR_SERVER_ONLY(float bearing_angle;)
    RR_CLIENT_ONLY(float lerp_angle;)
    RR_CLIENT_ONLY(float turning_animation;)
    float x;
    RR_CLIENT_ONLY(float lerp_x;)
    float y;
    RR_CLIENT_ONLY(float lerp_y;)
    float radius;
    RR_CLIENT_ONLY(float lerp_radius;)
    RR_CLIENT_ONLY(float animation;)
    RR_CLIENT_ONLY(float deletion_animation;)
    RR_SERVER_ONLY(uint32_t stun_ticks;)
    RR_CLIENT_ONLY(uint8_t deletion_type;)
    RR_CLIENT_ONLY(uint8_t animation_started : 1;)
    RR_SERVER_ONLY(uint8_t webbed : 1;)
    RR_SERVER_ONLY(uint8_t protocol_state;)
    EntityIdx parent_id;
    RR_SERVER_ONLY(uint16_t colliding_with_size;)
    RR_SERVER_ONLY(EntityIdx colliding_with[RR_MAX_COLLISION_COUNT];)
};

void rr_component_physical_init(struct rr_component_physical *,
                                struct rr_simulation *);
void rr_component_physical_free(struct rr_component_physical *,
                                struct rr_simulation *);

RR_SERVER_ONLY(void rr_component_physical_write(
                   struct rr_component_physical *, struct proto_bug *, int,
                   struct rr_component_player_info *);)
RR_CLIENT_ONLY(void rr_component_physical_read(struct rr_component_physical *,
                                               struct proto_bug *);)

RR_DECLARE_PUBLIC_FIELD(physical, float, x)
RR_DECLARE_PUBLIC_FIELD(physical, float, y)
RR_DECLARE_PUBLIC_FIELD(physical, float, angle)
RR_DECLARE_PUBLIC_FIELD(physical, float, radius)
