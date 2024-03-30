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

#include <stdint.h>

#include <Client/Simulation.h>

#include <Shared/Vector.h>

struct rr_renderer;

struct rr_particle_manager
{
    struct rr_simulation_animation particles[16384];
    uint32_t size;
};

struct rr_simulation_animation *rr_particle_alloc(struct rr_particle_manager *,
                                                  uint8_t);
void rr_particle_delete(struct rr_particle_manager *,
                        struct rr_simulation_animation *);
void rr_renderer_render_particle(struct rr_renderer *,
                                 struct rr_simulation_animation *);