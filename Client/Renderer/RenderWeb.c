#include <Client/Renderer/ComponentRender.h>

#include <math.h>

#include <Client/Game.h>
#include <Client/Renderer/Renderer.h>
#include <Client/Simulation.h>
#include <Shared/StaticData.h>

#include <Client/Renderer/RenderFunctions.h>

void rr_component_web_render(EntityIdx entity, struct rr_game *game)
{
    struct rr_simulation *simulation = game->simulation;
    struct rr_renderer *renderer = game->renderer;
    struct rr_component_physical *physical =
        rr_simulation_get_physical(simulation, entity);
    rr_renderer_set_global_alpha(
            renderer, 0.5 - (physical->lerp_server_animation_tick) * 0.1);
    rr_renderer_scale(
        renderer, 1 + (6 - physical->lerp_server_animation_tick) * 0.15);
    rr_renderer_rotate(renderer, physical->lerp_angle);
    rr_renderer_scale(renderer, physical->lerp_radius * 0.1);
    rr_renderer_draw_image(renderer, &game->asset_web);
}
