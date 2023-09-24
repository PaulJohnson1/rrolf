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
        rr_renderer_add_color_filter(renderer, 0xffffff63, 0.3);
    rr_renderer_add_color_filter(renderer, 0xffff0000, 0.5 * health->damage_animation);
    rr_renderer_set_global_alpha(renderer, 1 - physical->deletion_animation);
    rr_renderer_scale(renderer, 1 + physical->deletion_animation * 0.5);
    rr_renderer_rotate(renderer, physical->lerp_angle);
    rr_renderer_scale(renderer, RR_MOB_RARITY_SCALING[mob->rarity].radius);
    if (physical->animation_timer > 2 * M_PI)
        physical->animation_timer = fmod(physical->animation_timer, 2 * M_PI);

    uint8_t use_cache = ((health->damage_animation < 0.1) | game->cache.low_performance_mode) & 1;
    uint8_t is_friendly =
        (rr_simulation_get_relations(simulation, entity)->team !=
         rr_simulation_team_id_mobs)
        << 1;
    uint8_t is_centi_head = 4 - ((rr_simulation_has_centipede(simulation, entity) && rr_simulation_get_centipede(simulation, entity)->is_head) << 2);
    rr_renderer_draw_mob(renderer, mob->id, physical->animation_timer,
                           physical->turning_animation - physical->lerp_angle,
                           use_cache | is_friendly | is_centi_head);
}
