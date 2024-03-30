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

#include <Shared/Entity.h>

struct rr_game;
struct rr_simulation;
struct rr_component_player_info;

void rr_component_arena_render(EntityIdx, struct rr_game *,
                               struct rr_simulation *);
void rr_component_drop_render(EntityIdx, struct rr_game *,
                              struct rr_simulation *);
void rr_component_flower_render(EntityIdx, struct rr_game *,
                                struct rr_simulation *);
void rr_component_health_render(EntityIdx, struct rr_game *,
                                struct rr_simulation *);
void rr_component_mob_render(EntityIdx, struct rr_game *,
                             struct rr_simulation *);
void rr_component_petal_render(EntityIdx, struct rr_game *,
                               struct rr_simulation *);
void rr_component_web_render(EntityIdx, struct rr_game *,
                             struct rr_simulation *);

void render_background(struct rr_component_player_info *, struct rr_game *);
