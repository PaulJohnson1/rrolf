#include <Client/Renderer/ComponentRender.h>

#include <Client/Simulation.h>
#include <Client/Renderer/Renderer.h>

void rr_component_health_render(EntityIdx entity, struct rr_simulation *simulation, struct rr_renderer *renderer)
{
    struct rr_component_physical *physical = rr_simulation_get_physical(simulation, entity);
    struct rr_component_health *health = rr_simulation_get_health(simulation, entity);
    rr_renderer_translate(renderer, physical->x, physical->y + physical->radius + 30);
    float length = 40;
    rr_renderer_set_line_cap(renderer, 1);
    rr_renderer_set_stroke(renderer, 0xff222222);
    rr_renderer_set_line_width(renderer, 10);
    rr_renderer_begin_path(renderer);
    rr_renderer_move_to(renderer, -length, 0);
    rr_renderer_line_to(renderer, length, 0);
    rr_renderer_stroke(renderer);

    rr_renderer_set_stroke(renderer, 0xff75dd34);
    rr_renderer_set_line_width(renderer, 7);
    rr_renderer_begin_path(renderer);
    rr_renderer_move_to(renderer, -length, 0);
    rr_renderer_line_to(renderer, -length + 2 * length * health->health / health->max_health, 0);
    rr_renderer_stroke(renderer);
}