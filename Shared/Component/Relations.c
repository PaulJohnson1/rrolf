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

#include <Shared/Component/Relations.h>

#include <string.h>

#include <Shared/Entity.h>
#include <Shared/SimulationCommon.h>
#include <Shared/pb.h>

#define FOR_EACH_PUBLIC_FIELD                                                  \
    X(owner, varuint)                                                          \
    X(team, varuint)

enum
{
    state_flags_team = 0b000001,
    state_flags_owner = 0b000010,
    state_flags_all = 0b000011
};

void rr_component_relations_init(struct rr_component_relations *this,
                                 struct rr_simulation *simulation)
{
    memset(this, 0, sizeof *this);
}

void rr_component_relations_free(struct rr_component_relations *this,
                                 struct rr_simulation *simulation)
{
}

#ifdef RR_SERVER
#include <Server/Simulation.h>

void rr_component_relations_update_root_owner(struct rr_simulation *simulation, struct rr_component_relations *this)
{
    if (this->owner == RR_NULL_ENTITY)
        return;
    if (!rr_simulation_has_entity(simulation, this->owner))
        return;
    if (!rr_simulation_has_relations(simulation, this->owner))
    {
        this->root_owner = this->owner;
        return;
    }
    struct rr_component_relations *root = rr_simulation_get_relations(simulation, this->owner);
    if (root->root_owner == RR_NULL_ENTITY)
        this->root_owner = rr_simulation_get_entity_hash(simulation, root->parent_id);
    else
        this->root_owner = root->root_owner;
}
void rr_component_relations_write(struct rr_component_relations *this,
                                  struct proto_bug *encoder, int is_creation,
                                  struct rr_component_player_info *client)
{
    uint64_t state = this->protocol_state | (state_flags_all * is_creation);
    proto_bug_write_varuint(encoder, state, "relations component state");
#define X(NAME, TYPE) RR_ENCODE_PUBLIC_FIELD(NAME, TYPE);
    FOR_EACH_PUBLIC_FIELD
#undef X
}

RR_DEFINE_PUBLIC_FIELD(relations, EntityHash, owner)
RR_DEFINE_PUBLIC_FIELD(relations, uint32_t, team)
#endif

#ifdef RR_CLIENT
void rr_component_relations_read(struct rr_component_relations *this,
                                 struct proto_bug *encoder)
{
    uint64_t state =
        proto_bug_read_varuint(encoder, "relations component state");
#define X(NAME, TYPE) RR_DECODE_PUBLIC_FIELD(NAME, TYPE);
    FOR_EACH_PUBLIC_FIELD
#undef X
}
#endif