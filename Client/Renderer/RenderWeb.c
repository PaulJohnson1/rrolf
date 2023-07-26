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
    rr_renderer_set_stroke(renderer, 0xffffffff);
    rr_renderer_set_line_cap(renderer, 1);
    rr_renderer_set_line_width(renderer, 0.75);
    rr_renderer_begin_path(renderer);
    rr_renderer_move_to(renderer, 10, 0);
    rr_renderer_line_to(renderer, -10, 0);
    rr_renderer_move_to(renderer, 0, 10);
    rr_renderer_line_to(renderer, 0, -10);
    rr_renderer_move_to(renderer, 7.0710678118654755, 7.0710678118654755);
    rr_renderer_line_to(renderer, -7.0710678118654755, -7.0710678118654755);
    rr_renderer_move_to(renderer, -7.0710678118654755, 7.0710678118654755);
    rr_renderer_line_to(renderer, 7.0710678118654755, -7.0710678118654755);
    rr_renderer_move_to(renderer, 8, 0);
    rr_renderer_quadratic_curve_to(renderer,4.619397662556434, 1.913417161825449, 5.656854249492381, 5.65685424949238);
    rr_renderer_quadratic_curve_to(renderer,1.9134171618254492, 4.619397662556434, 4.898587196589413e-16, 8);
    rr_renderer_quadratic_curve_to(renderer,-1.9134171618254485, 4.619397662556434, -5.65685424949238, 5.656854249492381);
    rr_renderer_quadratic_curve_to(renderer,-4.619397662556434, 1.9134171618254494, -8, 9.797174393178826e-16);
    rr_renderer_quadratic_curve_to(renderer,-4.619397662556434, -1.9134171618254483, -5.6568542494923815, -5.65685424949238);
    rr_renderer_quadratic_curve_to(renderer,-1.9134171618254516, -4.619397662556432, -1.4695761589768238e-15, -8);
    rr_renderer_quadratic_curve_to(renderer,1.91341716182545, -4.619397662556433, 5.656854249492379, -5.6568542494923815);
    rr_renderer_quadratic_curve_to(renderer,4.619397662556432, -1.913417161825452, 8, -1.959434878635765e-15);
    rr_renderer_move_to(renderer, 5, 0);
    rr_renderer_quadratic_curve_to(renderer,2.77163859753386, 1.1480502970952693, 3.5355339059327378, 3.5355339059327373);
    rr_renderer_quadratic_curve_to(renderer,1.1480502970952695, 2.77163859753386, 3.061616997868383e-16, 5);
    rr_renderer_quadratic_curve_to(renderer,-1.1480502970952693, 2.77163859753386, -3.5355339059327373, 3.5355339059327378);
    rr_renderer_quadratic_curve_to(renderer,-2.77163859753386, 1.1480502970952697, -5, 6.123233995736766e-16);
    rr_renderer_quadratic_curve_to(renderer,-2.7716385975338604, -1.148050297095269, -3.5355339059327386, -3.5355339059327373);
    rr_renderer_quadratic_curve_to(renderer,-1.148050297095271, -2.7716385975338595, -9.184850993605148e-16, -5);
    rr_renderer_quadratic_curve_to(renderer,1.14805029709527, -2.77163859753386, 3.535533905932737, -3.5355339059327386);
    rr_renderer_quadratic_curve_to(renderer,2.7716385975338595, -1.148050297095271, 5, -1.2246467991473533e-15);
    rr_renderer_stroke(renderer);
}
