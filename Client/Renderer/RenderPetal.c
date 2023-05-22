#include <Client/Renderer/ComponentRender.h>

#include <Client/Simulation.h>
#include <Client/Renderer/Renderer.h>

#include <Client/Renderer/RenderFunctions.h>

void rr_component_petal_render(EntityIdx entity, struct rr_simulation *simulation, struct rr_renderer *renderer)
{
    struct rr_component_physical *physical = rr_simulation_get_physical(simulation, entity);
    rr_renderer_translate(renderer, physical->lerp_x, physical->lerp_y);
    rr_renderer_rotate(renderer, physical->angle);
    rr_renderer_render_petal(renderer, rr_simulation_get_petal(simulation, entity)->id);
}