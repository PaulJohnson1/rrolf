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
    float lerp_width;
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

static void mob_button_on_render(struct rr_ui_element *this,
                                 struct rr_game *game)
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
    rr_renderer_scale(renderer, 0.65 * mob_radius /
                                    RR_MOB_DATA[data->id].radius);

    rr_renderer_rotate(renderer, -0.78539816339); // pi / 4;
    rr_renderer_render_mob(renderer, game, data->id, 0, 0);

    rr_renderer_context_state_free(renderer, &state);
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
    element->data = data;
    return element;
}

static uint8_t mob_container_should_show(struct rr_ui_element *this,
                                         struct rr_game *game)
{
    return game->bottom_ui_open == 2 && !game->simulation_ready;
}

static void mob_container_animate(struct rr_ui_element *this,
                                  struct rr_game *game)
{
    this->width = this->abs_width;
    this->height = this->abs_height;
    rr_renderer_translate(game->renderer, 0,
                          -(this->y - this->abs_height / 2) * 2 *
                              this->animation);
}

struct rr_ui_element *rr_ui_mob_container_init()
{
    struct rr_ui_element *this =
        rr_ui_2d_container_init(rr_rarity_id_max, 6, 15, 15);
    for (uint8_t id = 0; id < rr_mob_id_max; ++id)
        for (uint8_t rarity = 0; rarity < rr_rarity_id_max; ++rarity)
            rr_ui_container_add_element(this, mob_button_init(id, rarity));
    this->fill = 0x00000000;
    struct rr_ui_element *c = rr_ui_set_background(
        rr_ui_pad(rr_ui_set_justify(
                      rr_ui_v_container_init(
                          rr_ui_container_init(), 10, 10,
                          rr_ui_text_init("Mob Gallery", 24, 0xffffffff),
                          rr_ui_scroll_container_init(this, 400),
                          NULL),
                      -1, 1),
                  20),
        0x40ffffff);
    c->x += 60 + 20;
    c->animate = mob_container_animate;
    c->should_show = mob_container_should_show;
    return c;
}

static void mob_toggle_toggle_on_render(struct rr_ui_element *this,
                                        struct rr_game *game)
{
    struct rr_renderer *renderer = game->renderer;
    if (game->focused == this)
        renderer->state.filter.amount = 0.2;
    rr_renderer_scale(renderer, renderer->scale);
    rr_renderer_set_fill(renderer, this->fill);
    renderer->state.filter.amount += 0.2;
    rr_renderer_set_stroke(renderer, this->fill);
    rr_renderer_set_line_width(renderer, 6);
    rr_renderer_begin_path(renderer);
    rr_renderer_round_rect(renderer, -this->width / 2, -this->height / 2,
                           this->width, this->height, 6);
    rr_renderer_fill(renderer);
    rr_renderer_stroke(renderer);
}

void mob_toggle_toggle_button_on_event(struct rr_ui_element *this,
                                       struct rr_game *game)
{
    if (game->pressed != this)
        return;
    if (game->input_data->mouse_buttons_up_this_tick & 1)
    {
        if (game->bottom_ui_open == 2)
            game->bottom_ui_open = 0;
        else
            game->bottom_ui_open = 2;
    }
}

struct rr_ui_element *rr_ui_mob_gallery_toggle_button_init()
{
    struct rr_ui_element *this = rr_ui_element_init();
    this->fill = 0xff56a2b3;
    this->abs_width = this->abs_height = this->width = this->height = 60;
    this->on_event = mob_toggle_toggle_button_on_event;
    this->on_render = mob_toggle_toggle_on_render;
    return this;
}