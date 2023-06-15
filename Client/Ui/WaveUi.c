#include <Client/Ui/Element.h>

#include <stdlib.h>
#include <string.h>

#include <Client/Game.h>
#include <Client/Simulation.h>
#include <Client/Renderer/Renderer.h>

#include <Shared/Utilities.h>

static void wave_bar_on_render(struct rr_ui_element *this, void *_game)
{
    if (this->hidden)
        return;
    struct rr_game *game = _game;
    if (!game->simulation_ready)
        return;
    struct rr_component_arena *arena = rr_simulation_get_arena(game->simulation, 1);
    struct rr_renderer_context_state state;
    struct rr_renderer *renderer = game->renderer;
    rr_renderer_init_context_state(renderer, &state);
    rr_renderer_set_stroke(renderer, 0xff666666);
    rr_renderer_set_line_width(renderer, 15);
    rr_renderer_set_line_cap(renderer, 1);
    ui_translate(this, renderer);
    rr_renderer_scale(renderer, renderer->scale);
    rr_renderer_begin_path(renderer);
    rr_renderer_move_to(renderer, -100, 0);
    rr_renderer_line_to(renderer, 100, 0);
    rr_renderer_stroke(renderer);
    rr_renderer_set_stroke(renderer, 0xff999999);
    rr_renderer_set_line_width(renderer, 12);
    rr_renderer_begin_path(renderer);
    rr_renderer_move_to(renderer, -100, 0);
    rr_renderer_line_to(renderer, -100 + 2 * arena->wave_tick, 0);
    rr_renderer_stroke(renderer);
    rr_renderer_free_context_state(renderer, &state);
}
struct rr_ui_element *rr_ui_wave_ui_init()
{
    struct rr_ui_element *element = rr_ui_element_init();
    element->width = 200;
    element->height = 15;
    element->on_render = wave_bar_on_render;
    return element;
}