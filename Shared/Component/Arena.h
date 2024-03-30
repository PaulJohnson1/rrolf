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
RR_SERVER_ONLY(struct rr_maze_declaration;)

#ifdef RR_SERVER
#include <Server/SpatialHash.h>
#include <Shared/StaticData.h>
#endif

struct rr_component_arena
{
    RR_SERVER_ONLY(struct rr_spawn_zone respawn_zone;)
    EntityIdx parent_id;
    uint8_t biome;
    RR_SERVER_ONLY(uint8_t protocol_state;)
    RR_SERVER_ONLY(uint8_t first_squad_to_enter;)
    RR_SERVER_ONLY(uint8_t player_entered;)
    RR_SERVER_ONLY(EntityIdx mob_count;)
    RR_SERVER_ONLY(struct rr_maze_declaration *maze;)
    RR_SERVER_ONLY(struct rr_spatial_hash spatial_hash;)
};

void rr_component_arena_init(struct rr_component_arena *,
                             struct rr_simulation *);
void rr_component_arena_free(struct rr_component_arena *,
                             struct rr_simulation *);

RR_SERVER_ONLY(void rr_component_arena_spatial_hash_init(
                   struct rr_component_arena *, struct rr_simulation *);)
RR_SERVER_ONLY(struct rr_maze_grid *rr_component_arena_get_grid(
                   struct rr_component_arena *, uint32_t, uint32_t);)
RR_SERVER_ONLY(void rr_component_arena_write(
                   struct rr_component_arena *, struct proto_bug *, int,
                   struct rr_component_player_info *);)
RR_CLIENT_ONLY(void rr_component_arena_read(struct rr_component_arena *,
                                            struct proto_bug *);)

RR_DECLARE_PUBLIC_FIELD(arena, uint8_t, biome)
