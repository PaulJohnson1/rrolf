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

#include <Shared/Component/Centipede.h>

#include <string.h>

#include <Shared/Entity.h>
#include <Shared/SimulationCommon.h>
#include <Shared/pb.h>

#define FOR_EACH_PUBLIC_FIELD                                                  \
    X(is_head, float32) 

enum
{
    state_flags_is_head = 0b000001,
    state_flags_all = 0b000001
};

void rr_component_centipede_init(struct rr_component_centipede *this,
                                 struct rr_simulation *simulation)
{
    memset(this, 0, sizeof *this);
}

#ifdef RR_SERVER
#include <Server/Simulation.h>
#endif

void rr_component_centipede_free(struct rr_component_centipede *this,
                                 struct rr_simulation *simulation)
{
#ifdef RR_SERVER
    if (rr_simulation_entity_alive(simulation, this->parent_node))
    {
        struct rr_component_centipede *parent_node =
            rr_simulation_get_centipede(simulation, this->parent_node);
        parent_node->child_node = RR_NULL_ENTITY;
    }
    if (rr_simulation_entity_alive(simulation, this->child_node))
    {
        struct rr_component_centipede *child_node =
            rr_simulation_get_centipede(simulation, this->child_node);
        child_node->parent_node = RR_NULL_ENTITY;
    }
#endif
}


#ifdef RR_SERVER
void rr_component_centipede_write(struct rr_component_centipede *this,
                                  struct proto_bug *encoder, int is_creation,
                                  struct rr_component_player_info *client)
{
    uint64_t state = this->protocol_state | (state_flags_all * is_creation);
    proto_bug_write_varuint(encoder, state, "centipede component state");
#define X(NAME, TYPE) RR_ENCODE_PUBLIC_FIELD(NAME, TYPE);
    FOR_EACH_PUBLIC_FIELD
#undef X
}

RR_DEFINE_PUBLIC_FIELD(centipede, uint8_t, is_head)
#endif

#ifdef RR_CLIENT
void rr_component_centipede_read(struct rr_component_centipede *this,
                                 struct proto_bug *encoder)
{
    uint64_t state =
        proto_bug_read_varuint(encoder, "centipede component state");
#define X(NAME, TYPE) RR_DECODE_PUBLIC_FIELD(NAME, TYPE);
    FOR_EACH_PUBLIC_FIELD
#undef X
}
#endif