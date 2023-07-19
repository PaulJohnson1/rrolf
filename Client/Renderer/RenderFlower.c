#include <Client/Renderer/ComponentRender.h>

#include <Client/Game.h>
#include <Client/Renderer/Renderer.h>
#include <Client/Simulation.h>

void rr_component_flower_render(EntityIdx entity, struct rr_game *game)
{
    struct rr_simulation *simulation = game->simulation;
    struct rr_renderer *renderer = game->renderer;
    struct rr_component_physical *physical =
        rr_simulation_get_physical(simulation, entity);
    struct rr_component_flower *flower =
        rr_simulation_get_flower(simulation, entity);
    renderer->state.filter.color = 0xffff0000;
    renderer->state.filter.amount = physical->lerp_server_animation_tick * 0.08;
    if (rr_simulation_get_health(simulation, entity)->health == 0)
    {
        rr_renderer_set_global_alpha(
            renderer, (physical->lerp_server_animation_tick) * 0.2);
        rr_renderer_scale(
            renderer, 1 + (6 - physical->lerp_server_animation_tick) * 0.15);
    }
    rr_renderer_set_stroke(renderer, 0xffcfbb50);
    rr_renderer_set_fill(renderer, 0xffffe763);
    rr_renderer_rotate(renderer, physical->lerp_angle);
    rr_renderer_set_line_width(renderer, 3);
    rr_renderer_begin_path(renderer);
    rr_renderer_arc(renderer, 0, 0, physical->radius);
    rr_renderer_fill(renderer);
    rr_renderer_stroke(renderer);
    rr_renderer_scale(renderer, physical->radius / 25);
    struct rr_renderer_context_state state;
    rr_renderer_context_state_init(renderer, &state);
    rr_renderer_set_fill(renderer, 0xff222222);
    rr_renderer_scale2(renderer, 1, 2);
    rr_renderer_begin_path(renderer);
    rr_renderer_arc(renderer, -7, -2.5, 3.25);
    rr_renderer_fill(renderer);
    rr_renderer_begin_path(renderer);
    rr_renderer_arc(renderer, -7, -2.5, 3);
    rr_renderer_clip(renderer);
    rr_renderer_scale2(renderer, 1, 0.5);
    rr_renderer_set_fill(renderer, 0xffffffff);
    rr_renderer_begin_path(renderer);
    rr_renderer_arc(renderer, -7 + flower->lerp_eye_x, -5 + flower->lerp_eye_y,
                    3);
    rr_renderer_fill(renderer);
    rr_renderer_context_state_free(renderer, &state);

    rr_renderer_context_state_init(renderer, &state);
    rr_renderer_set_fill(renderer, 0xff222222);
    rr_renderer_scale2(renderer, 1, 2);
    rr_renderer_begin_path(renderer);
    rr_renderer_arc(renderer, 7, -2.5, 3.25);
    rr_renderer_fill(renderer);
    rr_renderer_begin_path(renderer);
    rr_renderer_arc(renderer, 7, -2.5, 3);
    rr_renderer_clip(renderer);
    rr_renderer_scale2(renderer, 1, 0.5);
    rr_renderer_set_fill(renderer, 0xffffffff);
    rr_renderer_begin_path(renderer);
    rr_renderer_arc(renderer, 7 + flower->lerp_eye_x, -5 + flower->lerp_eye_y,
                    3);
    rr_renderer_fill(renderer);
    rr_renderer_context_state_free(renderer, &state);
    rr_renderer_set_stroke(renderer, 0xff222222);
    rr_renderer_set_line_width(renderer, 1.5);
    rr_renderer_set_line_cap(renderer, 1);
    rr_renderer_begin_path(renderer);
    rr_renderer_move_to(renderer, -6, 10);
    rr_renderer_quadratic_curve_to(renderer, 0, flower->lerp_mouth, 6, 10);
    rr_renderer_stroke(renderer);
}
