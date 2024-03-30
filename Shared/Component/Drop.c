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

#include <Shared/Component/Drop.h>

#include <assert.h>
#include <stdio.h>
#include <string.h>

#include <Shared/Entity.h>
#include <Shared/SimulationCommon.h>
#include <Shared/pb.h>

#define FOR_EACH_PUBLIC_FIELD                                                  \
    X(rarity, uint8)                                                           \
    X(id, uint8)

enum
{
    state_flags_id = 0b000001,
    state_flags_rarity = 0b000010,
    state_flags_hidden = 0b000100,
    state_flags_all = 0b000111
};

void rr_component_drop_init(struct rr_component_drop *this,
                            struct rr_simulation *simulation)
{
    memset(this, 0, sizeof *this);
}

void rr_component_drop_free(struct rr_component_drop *this,
                            struct rr_simulation *simulation)
{
}

#ifdef RR_SERVER
void rr_component_drop_write(struct rr_component_drop *this,
                             struct proto_bug *encoder, int is_creation,
                             struct rr_component_player_info *client)
{
    uint64_t state = this->protocol_state | (state_flags_all * is_creation);

    proto_bug_write_varuint(encoder, state, "drop component state");
#define X(NAME, TYPE) RR_ENCODE_PUBLIC_FIELD(NAME, TYPE);
    FOR_EACH_PUBLIC_FIELD
#undef X
}

RR_DEFINE_PUBLIC_FIELD(drop, uint8_t, id)
RR_DEFINE_PUBLIC_FIELD(drop, uint8_t, rarity)
#endif

#ifdef RR_CLIENT
void rr_component_drop_read(struct rr_component_drop *this,
                            struct proto_bug *encoder)
{
    uint64_t state = proto_bug_read_varuint(encoder, "drop component state");
#define X(NAME, TYPE) RR_DECODE_PUBLIC_FIELD(NAME, TYPE);
    FOR_EACH_PUBLIC_FIELD
#undef X
}
#endif
