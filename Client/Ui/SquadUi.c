#include <Client/Ui/Element.h>

#include <stdlib.h>
#include <stdio.h>

#include <Client/Ui/Engine.h>
#include <Client/Game.h>
#include <Client/Renderer/Renderer.h>

struct squad_container_metadata
{
    uint8_t pos;
};

static void squad_container_on_render(struct rr_ui_element *this, void *_game)
{
    struct rr_game *game = _game;
    struct rr_ui_choose_element_metadata *data = this->misc_data;
    this->hidden = (1 - game->squad_members[data->info].in_use) || (1 - game->socket_ready);
    rr_ui_choose_element_on_render(this, _game);
}

static void flower_icon_on_render(struct rr_ui_element *this, void *_game)
{
    if (this->hidden)
        return;
    struct rr_game *game = _game;
    struct rr_renderer_context_state state;
    struct rr_renderer *renderer = game->renderer;
    rr_renderer_init_context_state(renderer, &state);
    ui_translate(this, renderer);
    rr_renderer_set_stroke(renderer, 0xffcfbb50);
    rr_renderer_set_fill(renderer, 0xffffe763);
    rr_renderer_set_line_width(renderer, 3);
    rr_renderer_begin_path(renderer);
    rr_renderer_arc(renderer, 0, 0, this->width * 0.5);
    rr_renderer_fill(renderer);
    rr_renderer_stroke(renderer);
    rr_renderer_scale(renderer, this->width / 50);
    struct rr_renderer_context_state state1;
    rr_renderer_init_context_state(renderer, &state1);
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
    rr_renderer_arc(renderer, -7 + 3, -5 + 0, 3);
    rr_renderer_fill(renderer);
    rr_renderer_free_context_state(renderer, &state1);

    rr_renderer_init_context_state(renderer, &state1);
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
    rr_renderer_arc(renderer, 7 + 3, -5 + 0, 3);
    rr_renderer_fill(renderer);
    rr_renderer_free_context_state(renderer, &state1);
    rr_renderer_set_stroke(renderer, 0xff222222);
    rr_renderer_set_line_width(renderer, 1.5);
    rr_renderer_set_line_cap(renderer, 1);
    rr_renderer_begin_path(renderer);
    rr_renderer_move_to(renderer, -6, 10);
    rr_renderer_quadratic_curve_to(renderer, 0, 15, 6, 10);
    rr_renderer_stroke(renderer);
    rr_renderer_free_context_state(renderer, &state);
}

static void countdown_text_on_render(struct rr_ui_element *this, void *_game)
{
    struct rr_game *game = _game;
    if (!game->socket_ready || game->ticks_until_game_start == 125)
        return;
    struct rr_renderer *renderer = game->renderer;
    struct rr_renderer_context_state state;
    rr_renderer_init_context_state(renderer, &state);
    char out[16];
    out[sprintf(out, "Starting in %d", 1 + game->ticks_until_game_start / 25)] = 0;
    this->width = rr_renderer_get_text_size(out) * this->height;
    ui_translate(this, renderer);
    rr_renderer_scale(renderer, renderer->scale);
    rr_renderer_set_fill(renderer, 0xff1dd129);
    renderer->state.filter.amount += 0.2;
    rr_renderer_set_stroke(renderer, 0xff1dd129);
    rr_renderer_set_text_size(renderer, this->height);
    rr_renderer_set_line_width(renderer, this->height * 0.12);
    rr_renderer_set_text_align(renderer, 1);
    rr_renderer_set_text_baseline(renderer, 1);

    rr_renderer_stroke_text(renderer, out, 0, 0);
    rr_renderer_fill_text(renderer, out, 0, 0);
    rr_renderer_free_context_state(renderer, &state);
}

static struct rr_ui_element *rr_ui_flower_icon_init(float radius)
{
    struct rr_ui_element *element = rr_ui_element_init();
    element->width = element->height = radius * 2;
    element->on_render = flower_icon_on_render;
    return element;
}

static struct rr_ui_element *rr_ui_countdown_timer_init()
{
    struct rr_ui_element *element = rr_ui_element_init();
    element->height = 16;
    element->width = rr_renderer_get_text_size("Starting in 5") * element->height;
    element->on_render = countdown_text_on_render;
    return element;
}

static struct rr_ui_element *rr_ui_squad_player_container_init(uint8_t spot)
{
    struct rr_ui_element *a = rr_ui_v_container_init(
        rr_ui_container_init(), 10, 10, 2,
        rr_ui_flower_icon_init(25),
        rr_ui_text_init("Flower", 16)
    );
    struct rr_ui_element *b = rr_ui_text_init("Empty", 16);
    struct rr_ui_element *choose = rr_ui_choose_element_init(a, b);
    struct rr_ui_choose_element_metadata *data = choose->misc_data;
    data->info = spot;
    choose->on_render = squad_container_on_render;
    return rr_ui_set_background(
        rr_ui_v_container_init(rr_ui_container_init(), 10, 10, 1,
            choose
        ), 0xff0245ba
    );
}

struct rr_ui_element *rr_ui_squad_container_init()
{
    return rr_ui_set_background(
        rr_ui_v_container_init(rr_ui_container_init(), 15, 15, 3,
            rr_ui_text_init("Squad", 24),
            rr_ui_h_container_init(rr_ui_container_init(), 15, 15, 4,
                rr_ui_squad_player_container_init(0),
                rr_ui_squad_player_container_init(1),
                rr_ui_squad_player_container_init(2),
                rr_ui_squad_player_container_init(3)
            ),
            rr_ui_set_justify(
                rr_ui_countdown_timer_init()
            , 2, 2)
        ), 0xff0459de
    );
}