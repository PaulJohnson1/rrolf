#include <Client/System/ParticleRender.h>

#include <Client/Game.h>

void rr_system_particle_render_tick(struct rr_game *game, float delta)
{
    for (uint16_t i = 0; i < game->particle_manager.size; ++i)
    {
        struct rr_particle *particle = &game->particle_manager.particles[i];
        rr_renderer_render_particle(game->renderer, particle);
        particle->opacity *= 0.9;
        rr_vector_scale(&particle->velocity, 0.9);
        rr_vector_add(&particle->velocity, &particle->acceleration);
        rr_vector_add(&particle->position[0], &particle->velocity);
        //game->particle_manager.particles[i].size += (20 - game->particle_manager.particles[i].size) * 0.1;
    }
    for (uint16_t i = game->particle_manager.size; i > 0; --i)
    {
        if (game->particle_manager.particles[i - 1].opacity < 0.01)
            rr_particle_delete(&game->particle_manager, &game->particle_manager.particles[i - 1]);
    }
}