#include <Client/Renderer/ComponentRender.h>

#include <Client/Simulation.h>
#include <Client/Renderer/Renderer.h>

void rr_component_petal_render(EntityIdx entity, struct rr_simulation *simulation, struct rr_renderer *renderer)
{
    struct rr_component_physical *physical = rr_simulation_get_physical(simulation, entity);
    rr_renderer_translate(renderer, physical->x, physical->y);
    rr_renderer_begin_path(renderer);
    rr_renderer_arc(renderer, 0, 0, physical->radius + 1.5);
    rr_renderer_set_fill(renderer, 0xffcfbb50);
    rr_renderer_fill(renderer);
}