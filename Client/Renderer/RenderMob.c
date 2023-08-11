#include <Client/Renderer/ComponentRender.h>

#include <math.h>

#include <Client/Game.h>
#include <Client/Renderer/Renderer.h>
#include <Client/Simulation.h>
#include <Shared/StaticData.h>

#include <Client/Renderer/RenderFunctions.h>

void rr_component_mob_render(EntityIdx entity, struct rr_game *game)
{
    struct rr_simulation *simulation = game->simulation;
    struct rr_renderer *renderer = game->renderer;
    struct rr_component_physical *physical =
        rr_simulation_get_physical(simulation, entity);
    struct rr_component_mob *mob = rr_simulation_get_mob(simulation, entity);
    if (rr_simulation_get_relations(simulation, entity)->team ==
        rr_simulation_team_id_players)
        rr_renderer_add_color_filter(renderer, 0xffabab00, 0.5);
    rr_renderer_add_color_filter(renderer, 0xffff0000,
                                 physical->lerp_server_animation_tick * 0.08);

    rr_renderer_rotate(renderer, physical->lerp_angle);
    rr_renderer_scale(renderer, RR_MOB_RARITY_SCALING[mob->rarity].radius);
    if (rr_simulation_get_health(simulation, entity)->health == 0)
    {
        rr_renderer_set_global_alpha(
            renderer, (physical->lerp_server_animation_tick) * 0.2);
        rr_renderer_scale(
            renderer, 1 + (6 - physical->lerp_server_animation_tick) * 0.15);
        if ((rr_simulation_get_relations(simulation, entity)->team ==
                rr_simulation_team_id_mobs || mob->id == rr_mob_id_meteor) &&
            !mob->counted_as_killed)
        {
            mob->counted_as_killed = 1;
            ++game->cache.mob_kills[mob->id][mob->rarity];
            /*
            for (uint32_t i = 0; i < 128; ++i)
            {
                struct rr_particle *particle = rr_particle_alloc(&game->particle_manager, 0);
                float angle = rr_frand() * 2 * M_PI;
                float dist = rr_frand() * 50;
                rr_vector_from_polar(&particle->velocity, rr_frand() * 10 + 5, angle);
                rr_vector_set(&particle->position, physical->lerp_x + cosf(angle) * dist, physical->lerp_y + sinf(angle) * dist);
                particle->size = 4 + rr_frand() * 2;
                particle->opacity = 0.8;
                particle->color = 0xffab3423;
            }
            */
        }
    }
    if (mob->id == rr_mob_id_meteor)
    {
        struct rr_particle *particle = rr_particle_alloc(&game->particle_manager, 0);
        float angle = rr_vector_theta(&physical->lerp_velocity) + M_PI - 0.5 + rr_frand();
        float dist = rr_frand() * 50;
        rr_vector_from_polar(&particle->velocity, rr_frand() * 10 + 5, angle);
        rr_vector_set(&particle->position, physical->lerp_x + cosf(angle) * dist, physical->lerp_y + sinf(angle) * dist);
        particle->size = (4 + rr_frand() * 2) * RR_MOB_RARITY_SCALING[mob->rarity].radius;
        particle->opacity = 0.8;
        particle->color = 0xffab3423;
    }
    if (physical->animation > 2 * M_PI)
        physical->animation = fmod(physical->animation, 2 * M_PI);
    float sinusoid_animation = sinf(physical->animation);

    uint8_t use_cache =
        physical->lerp_server_animation_tick < 0.5 ||
        rr_simulation_get_health(simulation, entity)->health == 0;
    uint8_t is_friendly =
        (rr_simulation_get_relations(simulation, entity)->team !=
         rr_simulation_team_id_mobs)
        << 1;
    rr_renderer_render_mob(renderer, game, mob->id, sinusoid_animation,
                           physical->turning_animation - physical->lerp_angle,
                           use_cache | is_friendly);
}
