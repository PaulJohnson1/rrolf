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

enum rr_ai_state
{
    rr_ai_state_idle,
    rr_ai_state_idle_moving,
    rr_ai_state_charging,
    rr_ai_state_attacking,

    rr_ai_state_waiting_to_attack,
    rr_ai_state_exotic_special,

    rr_ai_state_returning_to_owner
};

struct rr_component_ai
{
    RR_SERVER_ONLY(uint32_t ticks_until_next_action;)
    RR_SERVER_ONLY(EntityHash target_entity;)
    EntityIdx parent_id;
    RR_SERVER_ONLY(enum rr_ai_state ai_state;)
    RR_SERVER_ONLY(uint8_t protocol_state;)
    RR_SERVER_ONLY(uint8_t has_prediction;)
};

void rr_component_ai_init(struct rr_component_ai *, struct rr_simulation *);
void rr_component_ai_free(struct rr_component_ai *, struct rr_simulation *);

RR_SERVER_ONLY(void rr_component_ai_write(struct rr_component_ai *,
                                          struct proto_bug *, int,
                                          struct rr_component_player_info *);)
RR_CLIENT_ONLY(void rr_component_ai_read(struct rr_component_ai *,
                                         struct proto_bug *);)
