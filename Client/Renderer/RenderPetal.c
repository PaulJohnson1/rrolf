#include <Client/Renderer/ComponentRender.h>

#include <Client/Simulation.h>
#include <Client/Renderer/Renderer.h>

#include <Client/Renderer/RenderFunctions.h>

void rr_component_petal_render(EntityIdx entity, struct rr_simulation *simulation, struct rr_renderer *renderer)
{
    struct rr_component_physical *physical = rr_simulation_get_physical(simulation, entity);
    struct rr_component_petal *petal = rr_simulation_get_petal(simulation, entity);
    renderer->state.filter.color = 0xffff0000;
    renderer->state.filter.amount = physical->lerp_server_animation_tick * 0.08;
    rr_renderer_translate(renderer, physical->lerp_x, physical->lerp_y);
    rr_renderer_rotate(renderer, physical->lerp_angle);
    if (rr_simulation_get_health(simulation, entity)->health == 0)
    {
        rr_renderer_set_global_alpha(renderer, (physical->lerp_server_animation_tick) * 0.2);
        rr_renderer_scale(renderer, 1 + (6 - physical->lerp_server_animation_tick) * 0.15);
    }
    if (rr_simulation_get_relations(simulation, entity)->team == rr_simulation_team_id_mobs)
    {
        rr_renderer_scale(renderer, RR_MOB_RARITY_SCALING[petal->rarity].radius);
    }
    rr_renderer_render_petal(renderer, petal->id);
}