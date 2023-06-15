#include <Client/Ui/Element.h>

#include <stdlib.h>
#include <string.h>

#include <Client/Game.h>
#include <Client/Simulation.h>
#include <Client/Renderer/Renderer.h>
#include <Client/Renderer/RenderFunctions.h>

#include <Shared/Utilities.h>
#include <Shared/StaticData.h>

struct mob_button_metadata
{
    uint8_t id;
    uint8_t rarity;
    float lerp_width;
};

static void mob_button_on_render(struct rr_ui_element *this, void *_game)
{
    if (this->hidden)
        return;
    struct rr_game *game = _game;
    struct rr_renderer *renderer = game->renderer;
    struct mob_button_metadata *data = this->misc_data;
    struct rr_renderer_context_state state;
    rr_renderer_init_context_state(renderer, &state);
    rr_renderer_scale(renderer, this->width / 60);
    rr_renderer_render_background(renderer, data->rarity);
    float mob_radius = RR_MOB_DATA[data->id].radius;
    if (mob_radius > 25)
        mob_radius = 25;
    rr_renderer_scale(renderer, this->width * 0.01 * mob_radius / RR_MOB_DATA[data->id].radius);
    
    rr_renderer_rotate(renderer, -0.78539816339); // pi / 4;
    rr_renderer_render_mob(renderer, data->id, 0);
    
    rr_renderer_free_context_state(renderer, &state);
}

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
    rr_renderer_line_to(renderer, -100 + 0.4 * arena->wave_tick, 0);
    rr_renderer_stroke(renderer);
    rr_renderer_free_context_state(renderer, &state);
}

struct rr_ui_element *rr_ui_mob_button_init(uint8_t id, uint8_t rarity)
{
    struct rr_ui_element *element = rr_ui_element_init();
    struct mob_button_metadata *data = malloc(sizeof *data);
    data->id = id;
    data->rarity = rarity;
    element->width = element->height = 60;
    element->on_render = mob_button_on_render;
    element->misc_data = data;
    return element;
}

struct rr_ui_element *rr_ui_wave_ui_init()
{
    struct rr_ui_element *element = rr_ui_element_init();
    element->width = 200;
    element->height = 15;
    element->on_render = wave_bar_on_render;
    return element;
}