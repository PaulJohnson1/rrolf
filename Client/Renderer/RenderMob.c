#include <Client/Renderer/ComponentRender.h>

#include <math.h>

#include <Client/Game.h>
#include <Client/Renderer/Renderer.h>
#include <Client/Simulation.h>
#include <Shared/StaticData.h>

#include <Client/Assets/RenderFunctions.h>

void rr_component_mob_render(EntityIdx entity, struct rr_game *game, struct rr_simulation *simulation)
{
    struct rr_renderer *renderer = game->renderer;
    struct rr_component_physical *physical =
        rr_simulation_get_physical(simulation, entity);
    struct rr_component_mob *mob = rr_simulation_get_mob(simulation, entity);
    struct rr_component_health *health = rr_simulation_get_health(simulation, entity);
    if (rr_simulation_get_relations(simulation, entity)->team ==
        rr_simulation_team_id_players)
        rr_renderer_add_color_filter(renderer, 0xff9323d3, 0.5);
    rr_renderer_add_color_filter(renderer, 0xffff0000, 0.5 * health->damage_animation);
    rr_renderer_set_global_alpha(renderer, 1 - physical->deletion_animation);
    rr_renderer_scale(renderer, 1 + physical->deletion_animation * 0.5);
    rr_renderer_rotate(renderer, physical->lerp_angle);
    rr_renderer_scale(renderer, RR_MOB_RARITY_SCALING[mob->rarity].radius);
    if (mob->id == rr_mob_id_meteor)
    {
        struct rr_particle *particle = rr_particle_alloc(&game->particle_manager, 0);
        float angle = rr_vector_theta(&physical->lerp_velocity) + M_PI - 0.5 + rr_frand();
        float dist = rr_frand() * 50;
        rr_vector_from_polar(&particle->velocity, (rr_frand() * 5 + 5) * RR_MOB_RARITY_SCALING[mob->rarity].radius, angle);
        rr_vector_set(&particle->position[0], physical->lerp_x + cosf(angle) * dist, physical->lerp_y + sinf(angle) * dist);
        particle->size = (4 + rr_frand() * 2) * RR_MOB_RARITY_SCALING[mob->rarity].radius;
        particle->opacity = 0.8;
        particle->color = 0xffab3423;
    }
    if (physical->animation > 2 * M_PI)
        physical->animation = fmod(physical->animation, 2 * M_PI);
    float sinusoid_animation = sinf(physical->animation);

    uint8_t use_cache = health->damage_animation < 0.1;
    uint8_t is_friendly =
        (rr_simulation_get_relations(simulation, entity)->team !=
         rr_simulation_team_id_mobs)
        << 1;
    rr_renderer_draw_mob(renderer, mob->id, sinusoid_animation,
                           physical->turning_animation - physical->lerp_angle,
                           use_cache | is_friendly);
}
