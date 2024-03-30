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

struct rr_simulation;
struct proto_bug;
RR_CLIENT_ONLY(struct rr_renderer;)
RR_SERVER_ONLY(struct rr_component_player_info;)

struct rr_component_drop
{
    EntityIdx parent_id;
    RR_SERVER_ONLY(int16_t ticks_until_despawn;)
    uint8_t id;
    uint8_t rarity;
    RR_SERVER_ONLY(
        uint8_t can_be_picked_up_by[RR_BITSET_ROUND(RR_SQUAD_COUNT)];)
    RR_SERVER_ONLY(uint8_t picked_up_by[RR_BITSET_ROUND(RR_SQUAD_MEMBER_COUNT *
                                                        RR_SQUAD_COUNT)];)
    RR_SERVER_ONLY(uint8_t protocol_state;)
};

void rr_component_drop_init(struct rr_component_drop *, struct rr_simulation *);
void rr_component_drop_free(struct rr_component_drop *, struct rr_simulation *);

RR_SERVER_ONLY(void rr_component_drop_write(struct rr_component_drop *,
                                            struct proto_bug *, int,
                                            struct rr_component_player_info *);)
RR_CLIENT_ONLY(void rr_component_drop_read(struct rr_component_drop *,
                                           struct proto_bug *);)

RR_DECLARE_PUBLIC_FIELD(drop, uint8_t, id)
RR_DECLARE_PUBLIC_FIELD(drop, uint8_t, rarity)
