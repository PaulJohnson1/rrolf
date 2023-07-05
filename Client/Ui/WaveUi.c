#include <Client/Ui/Element.h>

#include <stdlib.h>
#include <string.h>

#include <Client/Game.h>
#include <Client/Renderer/RenderFunctions.h>
#include <Client/Renderer/Renderer.h>
#include <Client/Simulation.h>
#include <Client/Ui/Engine.h>

#include <Shared/StaticData.h>
#include <Shared/Utilities.h>

struct mob_button_metadata
{
    uint8_t id;
    uint8_t rarity;
    float lerp_width;
};

static void wave_text_on_render(struct rr_ui_element *this, void *_game)
{
    if (this->hidden)
        return;
    struct rr_game *game = _game;
    if (!game->simulation_ready)
        return;
    struct rr_component_arena *arena =
        rr_simulation_get_arena(game->simulation, 1);
    struct rr_renderer *renderer = game->renderer;
    struct text_metadata *data = this->misc_data;
    char out[12];
    out[sprintf(out, "Wave %d", arena->wave)] = 0;
    this->width = rr_renderer_get_text_size((char const *)&out);

    struct rr_renderer_context_state state;
    rr_renderer_context_state_init(renderer, &state);
    rr_ui_translate(this, renderer);
    rr_renderer_scale(renderer, renderer->scale);
    rr_renderer_set_fill(renderer, 0xffffffff);
    rr_renderer_set_stroke(renderer, 0xff000000);
    rr_renderer_set_text_size(renderer, this->height);
    rr_renderer_set_line_width(renderer, this->height * 0.12);
    rr_renderer_set_text_align(renderer, 1);
    rr_renderer_set_text_baseline(renderer, 1);
    rr_renderer_stroke_text(renderer, (char const *)&out, 0, 0);
    rr_renderer_fill_text(renderer, (char const *)&out, 0, 0);
    rr_renderer_context_state_free(renderer, &state);
}

static void mob_button_on_render(struct rr_ui_element *this, void *_game)
{
    if (this->hidden)
        return;
    struct rr_game *game = _game;
    struct rr_renderer *renderer = game->renderer;
    struct mob_button_metadata *data = this->misc_data;
    struct rr_renderer_context_state state;
    rr_renderer_context_state_init(renderer, &state);
    rr_renderer_scale(renderer, this->width / 60);
    rr_renderer_render_background(renderer, game, data->rarity);
    float mob_radius = RR_MOB_DATA[data->id].radius;
    if (mob_radius > 25)
        mob_radius = 25;
    rr_renderer_scale(renderer, this->width * 0.01 * mob_radius /
                                    RR_MOB_DATA[data->id].radius);

    rr_renderer_rotate(renderer, -0.78539816339); // pi / 4;
    rr_renderer_render_mob(renderer, game, data->id, 0);

    rr_renderer_context_state_free(renderer, &state);
}

static void wave_bar_on_render(struct rr_ui_element *this, void *_game)
{
    if (this->hidden)
        return;
    struct rr_game *game = _game;
    if (!game->simulation_ready)
        return;
    struct rr_component_arena *arena =
        rr_simulation_get_arena(game->simulation, 1);
    struct rr_renderer_context_state state;
    struct rr_renderer *renderer = game->renderer;
    float capac = 15 * 5 * 25;
    rr_renderer_context_state_init(renderer, &state);
    rr_renderer_set_stroke(renderer, 0xff222222);
    rr_renderer_set_line_width(renderer, 15);
    rr_renderer_set_line_cap(renderer, 1);
    rr_ui_translate(this, renderer);
    rr_renderer_scale(renderer, renderer->scale);
    rr_renderer_begin_path(renderer);
    rr_renderer_move_to(renderer, -100, 0);
    rr_renderer_line_to(renderer, 100, 0);
    rr_renderer_stroke(renderer);
    rr_renderer_set_stroke(renderer, 0xff75dd34);
    rr_renderer_set_line_width(renderer, 12);
    rr_renderer_begin_path(renderer);
    rr_renderer_move_to(renderer, -100, 0);
    float pct = (arena->wave_tick / capac) > 1 ? 1 : arena->wave_tick / capac;
    rr_renderer_line_to(renderer, -100 + 200 * (pct), 0);
    rr_renderer_stroke(renderer);
    if (arena->wave_tick > capac)
    {
        pct = (arena->wave_tick * 0.5 / capac - 0.5);
        rr_renderer_set_stroke(renderer, 0xffbfeb2f);
        rr_renderer_set_line_width(renderer, 9);
        rr_renderer_begin_path(renderer);
        rr_renderer_move_to(renderer, -100, 0);
        rr_renderer_line_to(renderer, -100 + 200 * (pct), 0);
        rr_renderer_stroke(renderer);
    }
    rr_renderer_context_state_free(renderer, &state);
}

static struct rr_ui_element *rr_ui_mob_button_init(uint8_t id, uint8_t rarity)
{
    struct rr_ui_element *element = rr_ui_element_init();
    struct mob_button_metadata *data = calloc(1, sizeof *data);
    data->id = id;
    data->rarity = rarity;
    element->width = element->height = 60;
    element->on_render = mob_button_on_render;
    element->misc_data = data;
    return element;
}

static struct rr_ui_element *rr_ui_wave_bar_init()
{
    struct rr_ui_element *element = rr_ui_element_init();
    element->width = 200;
    element->height = 15;
    element->on_render = wave_bar_on_render;
    return element;
}

static struct rr_ui_element *rr_ui_wave_text_init(float size)
{
    struct rr_ui_element *element = rr_ui_element_init();
    element->height = size;
    element->on_render = wave_text_on_render;
    return element;
}

struct rr_ui_element *rr_ui_wave_container_init()
{
    return rr_ui_set_justify(
        rr_ui_v_container_init(rr_ui_container_init(), 10, 10, 2,
                               rr_ui_wave_text_init(36), rr_ui_wave_bar_init()),
        1, 1);
}
