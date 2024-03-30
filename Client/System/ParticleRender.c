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

#include <Client/System/ParticleRender.h>

#include <Client/Game.h>

void rr_system_particle_render_tick(struct rr_game *game, float delta)
{
    for (uint16_t i = 0; i < game->particle_manager.size; ++i)
    {
        struct rr_simulation_animation *particle =
            &game->particle_manager.particles[i];
        rr_renderer_render_particle(game->renderer, particle);
        particle->opacity *= 0.9;
        if (particle->type != rr_animation_type_lightningbolt)
        {
            rr_vector_scale(&particle->velocity, 0.9);
            rr_vector_add(&particle->velocity, &particle->acceleration);
            particle->x += particle->velocity.x;
            particle->y += particle->velocity.y;
        }
    }
    for (uint16_t i = game->particle_manager.size; i > 0; --i)
    {
        if (game->particle_manager.particles[i - 1].opacity < 0.01)
            rr_particle_delete(&game->particle_manager,
                               &game->particle_manager.particles[i - 1]);
    }
}