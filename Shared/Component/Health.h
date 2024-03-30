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

#include <Shared/Component/Common.h>
#include <Shared/Entity.h>
#include <Shared/Utilities.h>

struct rr_simulation;
struct proto_bug;
RR_CLIENT_ONLY(struct rr_renderer;)
RR_SERVER_ONLY(struct rr_component_player_info;)

struct rr_component_health
{
    float health;
    RR_CLIENT_ONLY(float lerp_health;)
    float max_health;
    RR_CLIENT_ONLY(float damage_animation;)
    RR_SERVER_ONLY(float damage;)
    RR_SERVER_ONLY(float secondary_damage;)
    RR_SERVER_ONLY(float damage_reduction;)
    RR_SERVER_ONLY(float poison;)
    RR_SERVER_ONLY(uint16_t poison_ticks;)
    EntityIdx parent_id;
    uint8_t flags;
    RR_SERVER_ONLY(uint8_t protocol_state;)
    RR_CLIENT_ONLY(uint8_t prev_flags;)
    RR_SERVER_ONLY(uint8_t damage_paused;)
};

void rr_component_health_init(struct rr_component_health *,
                              struct rr_simulation *);
void rr_component_health_free(struct rr_component_health *,
                              struct rr_simulation *);

RR_SERVER_ONLY(void rr_component_health_write(
                   struct rr_component_health *, struct proto_bug *, int,
                   struct rr_component_player_info *);)
RR_CLIENT_ONLY(void rr_component_health_read(struct rr_component_health *,
                                             struct proto_bug *);)

RR_DECLARE_PUBLIC_FIELD(health, float, health)
RR_DECLARE_PUBLIC_FIELD(health, float, max_health)
RR_DECLARE_PUBLIC_FIELD(health, uint8_t, flags)
RR_SERVER_ONLY(void rr_component_health_do_damage(struct rr_simulation *,
                                                  struct rr_component_health *,
                                                  EntityIdx, float);)
