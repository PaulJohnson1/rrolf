// Copyright (C) 2024  Paul Johnson

// This program is free software: you can redistribute it and/or modify
// it under the terms of the GNU Affero General Public License as
// published by the Free Software Foundation, either version 3 of the
// License, or (at your option) any later version.

// This program is distributed in the hope that it will be useful,
// but WITHOUT ANY WARRANTY; without even the implied warranty of
// MERCHANTABILITY or FITNESS FOR A PARTICULAR PURPOSE.  See the
// GNU Affero General Public License for more details.

// You should have received a copy of the GNU Affero General Public License
// along with this program.  If not, see <https://www.gnu.org/licenses/>.

#pragma once

#include <Shared/Bitset.h>
#include <Shared/Component/Common.h>
#include <Shared/Entity.h>
#include <Shared/Utilities.h>
#include <Shared/Vector.h>

struct rr_simulation;
struct proto_bug;

RR_SERVER_ONLY(struct rr_component_player_info;)

struct rr_component_physical
{
    struct rr_vector velocity;
    RR_CLIENT_ONLY(struct rr_vector lerp_velocity;)
    RR_SERVER_ONLY(struct rr_vector
                       collision_velocity;) // used for collision resolution
                                            // calcs. bypasses all speed modifie
    RR_SERVER_ONLY(struct rr_vector acceleration;)
    RR_SERVER_ONLY(
        struct rr_vector wall_collision;) // wall collision angle. can be used
                                          // to bounce off walls
    RR_SERVER_ONLY(float mass;)
    RR_SERVER_ONLY(float knockback_scale;)
    RR_SERVER_ONLY(float friction;)
    RR_SERVER_ONLY(float acceleration_scale;)
    RR_SERVER_ONLY(float aggro_range_multiplier;)
    RR_SERVER_ONLY(float slow_resist;)
    RR_SERVER_ONLY(float web_slowdown;)
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
    RR_CLIENT_ONLY(float animation;)       // the actual animation client uses
    RR_CLIENT_ONLY(float animation_timer;) // global timer
    RR_CLIENT_ONLY(float deletion_animation;)
    RR_CLIENT_ONLY(uint8_t on_title_screen;)
    RR_SERVER_ONLY(uint32_t stun_ticks;)
    RR_CLIENT_ONLY(uint8_t deletion_type : 2;)
    RR_CLIENT_ONLY(uint8_t animation_started : 1;)
    RR_SERVER_ONLY(uint8_t protocol_state;)
    EntityIdx parent_id;
    RR_SERVER_ONLY(EntityIdx arena;)
    RR_SERVER_ONLY(uint16_t colliding_with_size;)
    RR_SERVER_ONLY(EntityIdx colliding_with[RR_MAX_COLLISION_COUNT];)
    RR_SERVER_ONLY(uint8_t no_aggro;)
    RR_SERVER_ONLY(uint8_t no_wall_collision;)
    RR_SERVER_ONLY(uint8_t no_collision;)
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
