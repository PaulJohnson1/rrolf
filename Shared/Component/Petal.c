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

#include <Shared/Component/Petal.h>

#include <stdlib.h>
#include <string.h>

#include <Shared/Entity.h>
#include <Shared/SimulationCommon.h>
#include <Shared/pb.h>

#ifdef RR_SERVER
#include <math.h>

#include <Server/EntityAllocation.h>
#include <Server/Simulation.h>
#include <Shared/Utilities.h>
#endif

#define FOR_EACH_PUBLIC_FIELD                                                  \
    X(rarity, uint8)                                                           \
    X(id, uint8)                                                               \
    X(detached, uint8)

enum
{
    state_flags_rarity = 0b000001,
    state_flags_id = 0b000010,
    state_flags_detached = 0b000100,
    state_flags_all = 0b000111
};

void rr_component_petal_init(struct rr_component_petal *this,
                             struct rr_simulation *simulation)
{
    memset(this, 0, sizeof *this);
    RR_SERVER_ONLY(this->spin_ccw = 1 - 2 * (rand() & 1);)
}

void rr_component_petal_free(struct rr_component_petal *this,
                             struct rr_simulation *simulation)
{
#ifdef RR_SERVER
    if (this->id != rr_petal_id_web || this->detached == 0)
        return;
    EntityIdx id = rr_simulation_alloc_entity(simulation);
    struct rr_component_physical *physical =
        rr_simulation_add_physical(simulation, id);
    struct rr_component_relations *relations =
        rr_simulation_add_relations(simulation, id);
    struct rr_component_web *web = rr_simulation_add_web(simulation, id);
    struct rr_component_physical *petal_phys =
        rr_simulation_get_physical(simulation, this->parent_id);
    rr_component_physical_set_x(physical, petal_phys->x);
    rr_component_physical_set_y(physical, petal_phys->y);
    rr_component_physical_set_radius(
        physical, RR_PETAL_RARITY_SCALE[this->rarity].web_radius);
    rr_component_physical_set_angle(physical, rr_frand() * 2 * M_PI);
    physical->mass = 1;
    physical->friction = 0;
    physical->arena = petal_phys->arena;
    web->ticks_until_death = 125;
    web->slow_factor = 0.05 + powf(0.56, this->rarity);
    relations->team =
        rr_simulation_get_relations(simulation, this->parent_id)->team;
    rr_component_relations_set_owner(relations,
        rr_simulation_get_relations(simulation, this->parent_id)->owner);
    rr_component_relations_update_root_owner(simulation, relations);
#endif
}

#ifdef RR_SERVER
void rr_component_petal_write(struct rr_component_petal *this,
                              struct proto_bug *encoder, int is_creation,
                              struct rr_component_player_info *client)
{
    uint64_t state = this->protocol_state | (state_flags_all * is_creation);
    proto_bug_write_varuint(encoder, state, "petal component state");
#define X(NAME, TYPE) RR_ENCODE_PUBLIC_FIELD(NAME, TYPE);
    FOR_EACH_PUBLIC_FIELD
#undef X
}

RR_DEFINE_PUBLIC_FIELD(petal, uint8_t, id)
RR_DEFINE_PUBLIC_FIELD(petal, uint8_t, rarity)
RR_DEFINE_PUBLIC_FIELD(petal, uint8_t, detached)
#endif

#ifdef RR_CLIENT
void rr_component_petal_read(struct rr_component_petal *this,
                             struct proto_bug *encoder)
{
    uint64_t state = proto_bug_read_varuint(encoder, "petal component state");
#define X(NAME, TYPE) RR_DECODE_PUBLIC_FIELD(NAME, TYPE);
    FOR_EACH_PUBLIC_FIELD
#undef X
}
#endif