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

#include <Shared/Component/Arena.h>

#include <stdlib.h>
#include <string.h>

#include <Shared/Entity.h>
#include <Shared/SimulationCommon.h>
#include <Shared/StaticData.h>
#include <Shared/pb.h>

#ifdef RR_SERVER
#include <math.h>

#include <Shared/Utilities.h>
#endif

#define FOR_EACH_PUBLIC_FIELD                                                  \
    X(biome, uint8)

enum
{
    state_flags_biome = 0b000001,
    state_flags_all = 0b000001
};


void rr_component_arena_init(struct rr_component_arena *this,
                             struct rr_simulation *simulation)
{
    memset(this, 0, sizeof *this);
}

void rr_component_arena_free(struct rr_component_arena *this,
                             struct rr_simulation *simulation)
{
#ifdef RR_SERVER
    if (rr_simulation_has_mob(simulation, this->parent_id))
    {
        struct rr_component_physical *this_physical = rr_simulation_get_physical(simulation, this->parent_id);
        for (uint32_t i = 0; i < simulation->physical_count; ++i)
        {
            struct rr_component_physical *physical = rr_simulation_get_physical(simulation, simulation->physical_vector[i]);
            if (physical->arena != this->parent_id)
                continue;
            physical->arena = 1;
            rr_component_physical_set_x(physical, this_physical->x);
            rr_component_physical_set_y(physical, this_physical->y);
            float angle = rr_frand() * M_PI * 2;
            float v = rr_frand() * 5;
            physical->velocity.x = cosf(angle) * v;
            physical->velocity.y = sinf(angle) * v;
        }
    }
    free(this->spatial_hash.cells);
#endif
}

#ifdef RR_SERVER
#include <Shared/StaticData.h>

void rr_component_arena_spatial_hash_init(struct rr_component_arena *this, struct rr_simulation *simulation)
{
    this->maze = &RR_MAZES[this->biome];
    rr_spatial_hash_init(&this->spatial_hash, simulation, this->maze->maze_dim * this->maze->grid_size);
}

struct rr_maze_grid *rr_component_arena_get_grid(struct rr_component_arena *this, uint32_t x, uint32_t y)
{
    return &this->maze->maze[y * this->maze->maze_dim + x];
}

void rr_component_arena_write(struct rr_component_arena *this,
                              struct proto_bug *encoder, int is_creation,
                              struct rr_component_player_info *client)
{
    uint64_t state = this->protocol_state | (state_flags_all * is_creation);

    proto_bug_write_varuint(encoder, state, "arena component state");
#define X(NAME, TYPE) RR_ENCODE_PUBLIC_FIELD(NAME, TYPE);
    FOR_EACH_PUBLIC_FIELD
}

RR_DEFINE_PUBLIC_FIELD(arena, uint8_t, biome)
#endif

#ifdef RR_CLIENT
void rr_component_arena_read(struct rr_component_arena *this,
                             struct proto_bug *encoder)
{
    uint64_t state = proto_bug_read_varuint(encoder, "arena component state");
#define X(NAME, TYPE) RR_DECODE_PUBLIC_FIELD(NAME, TYPE);
    FOR_EACH_PUBLIC_FIELD
#undef X
}
#endif
