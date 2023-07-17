#include <Client/Ui/Ui.h>

#include <stdlib.h>
#include <string.h>

#include <Client/Game.h>
#include <Client/InputData.h>
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
};

static void mob_button_on_event(struct rr_ui_element *this,
                                struct rr_game *game)
{
    struct mob_button_metadata *data = this->data;
    rr_ui_render_tooltip_above(this, game->mob_tooltips[data->id][data->rarity],
                               game);
}

static void wave_text_on_render(struct rr_ui_element *this,
                                struct rr_game *game)
{
    struct rr_component_arena *arena =
        rr_simulation_get_arena(game->simulation, 1);
    struct rr_renderer *renderer = game->renderer;
    struct text_metadata *data = this->data;
    char out[12];
    out[sprintf(out, "Wave %d", arena->wave)] = 0;
    this->width = rr_renderer_get_text_size((char const *)&out);

    struct rr_renderer_context_state state;
    rr_renderer_context_state_init(renderer, &state);
    rr_renderer_scale(renderer, renderer->scale);
    rr_renderer_set_fill(renderer, 0xffffffff);
    rr_renderer_set_stroke(renderer, 0xff000000);
    rr_renderer_set_text_size(renderer, this->abs_height);
    rr_renderer_set_line_width(renderer, this->abs_height * 0.12);
    rr_renderer_set_text_align(renderer, 1);
    rr_renderer_set_text_baseline(renderer, 1);
    rr_renderer_stroke_text(renderer, (char const *)&out, 0, 0);
    rr_renderer_fill_text(renderer, (char const *)&out, 0, 0);
    rr_renderer_context_state_free(renderer, &state);
}

static uint8_t mob_button_should_show(struct rr_ui_element *this, struct rr_game *game)
{
    if (!game->simulation_ready)
        return 0;
    struct mob_button_metadata *data = this->data;
    struct rr_component_arena *arena = rr_simulation_get_arena(game->simulation, 1);
    return arena->mob_counters[data->id * rr_rarity_id_max + data->rarity];
}

static void mob_button_on_render(struct rr_ui_element *this, struct rr_game *game)
{
    struct rr_renderer *renderer = game->renderer;
    struct mob_button_metadata *data = this->data;
    struct rr_renderer_context_state state;
    rr_renderer_context_state_init(renderer, &state);
    rr_renderer_scale(renderer, this->abs_width / 60 * renderer->scale);
    rr_renderer_render_background(renderer, data->rarity);
    float mob_radius = RR_MOB_DATA[data->id].radius;
    if (mob_radius > 25)
        mob_radius = 25;
    rr_renderer_scale(renderer, this->abs_width * 0.01 * mob_radius /
                                    RR_MOB_DATA[data->id].radius);

    rr_renderer_rotate(renderer, -0.78539816339); // pi / 4;
    rr_renderer_render_mob(renderer, game, data->id, 0);

    rr_renderer_context_state_free(renderer, &state);
    rr_renderer_scale(renderer, this->abs_width / 60 * renderer->scale);
    struct rr_component_arena *arena = rr_simulation_get_arena(game->simulation, 1);
    uint32_t count = arena->mob_counters[data->id * rr_rarity_id_max + data->rarity];
    if (count <= 1)
        return;
    rr_renderer_translate(renderer, 25, -25);
    rr_renderer_rotate(renderer, 0.5);
    rr_renderer_set_fill(renderer, 0xffffffff);
    rr_renderer_set_stroke(renderer, 0xff222222);
    rr_renderer_set_text_align(renderer, 1);
    rr_renderer_set_text_baseline(renderer, 1);
    rr_renderer_set_text_size(renderer, 18);
    rr_renderer_set_line_width(renderer, 18 * 0.12);

    char out[12];
    out[sprintf(&out[0], "x%d", count)] = 0;
    rr_renderer_stroke_text(renderer, (char const *)&out, 0, 0);
    rr_renderer_fill_text(renderer, (char const *)&out, 0, 0);
}

static void wave_bar_on_render(struct rr_ui_element *this, struct rr_game *game)
{
    struct rr_component_arena *arena =
        rr_simulation_get_arena(game->simulation, 1);
    struct rr_renderer_context_state state;
    struct rr_renderer *renderer = game->renderer;
    float capac = 15 * 25;
    rr_renderer_context_state_init(renderer, &state);
    rr_renderer_set_stroke(renderer, 0xff222222);
    rr_renderer_set_line_width(renderer, 15);
    rr_renderer_set_line_cap(renderer, 1);
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

static struct rr_ui_element *mob_button_init(uint8_t id, uint8_t rarity)
{
    struct rr_ui_element *element = rr_ui_element_init();
    struct mob_button_metadata *data = calloc(1, sizeof *data);
    data->id = id;
    data->rarity = rarity;
    element->abs_width = element->abs_height = element->width =
        element->height = 50;
    element->on_render = mob_button_on_render;
    element->on_event = mob_button_on_event;
    element->should_show = mob_button_should_show;
    element->data = data;
    return element;
}

static void wave_text_function(struct rr_ui_element *this, struct rr_game *game)
{
    struct rr_component_arena *arena =
        rr_simulation_get_arena(game->simulation, 1);
    struct dynamic_text_metadata *data = this->data;
    data->text[sprintf(data->text, "Wave %d", arena->wave)] = 0;
}

static struct rr_ui_element *wave_bar_init()
{
    struct rr_ui_element *element = rr_ui_element_init();
    element->abs_width = element->width = 200;
    element->abs_height = element->height = 15;
    element->on_render = wave_bar_on_render;
    return element;
}

struct rr_ui_element *rr_ui_wave_container_init()
{
    struct rr_ui_element *outer_container =
        rr_ui_h_container_init(rr_ui_container_init(), 10, 10, 0);
    for (uint8_t i = 0; i < rr_mob_id_max; ++i)
    {
        struct rr_ui_element *inner_container =
            rr_ui_v_container_init(rr_ui_container_init(), 0, -30, 0);
        for (uint8_t j = 0; j < rr_rarity_id_max; ++j)
        {
            rr_ui_container_add_element(inner_container, mob_button_init(i, j));
        }
        inner_container->width = inner_container->abs_width;
        inner_container->height = inner_container->abs_height;
        rr_ui_v_container_set(inner_container);
        rr_ui_container_add_element(outer_container, inner_container);
    }
    rr_ui_h_container_set(outer_container);
    outer_container->width = outer_container->abs_width;
    outer_container->height = outer_container->abs_height;
    return rr_ui_set_justify(
        rr_ui_v_container_init(
            rr_ui_container_init(), 10, 10, 3,
            rr_ui_dynamic_text_init(36, 0xffffffff, wave_text_function),
            wave_bar_init(),
            outer_container),
        0, -1);
}
