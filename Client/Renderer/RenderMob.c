#include <Client/Renderer/ComponentRender.h>

#include <Client/Simulation.h>
#include <Client/Renderer/Renderer.h>
#include <Shared/StaticData.h>

#include <Client/Renderer/RenderFunctions.h>

void rr_component_mob_render(EntityIdx entity, struct rr_simulation *simulation, struct rr_renderer *renderer)
{
    struct rr_component_physical *physical = rr_simulation_get_physical(simulation, entity);
    struct rr_component_mob *mob = rr_simulation_get_mob(simulation, entity);
    rr_renderer_translate(renderer, physical->lerp_x, physical->lerp_y);
    rr_renderer_rotate(renderer, physical->lerp_angle);
    rr_renderer_scale(renderer, RR_MOB_RARITY_SCALING[mob->id].radius);
    rr_renderer_render_mob(renderer, rr_simulation_get_mob(simulation, entity)->id);
}