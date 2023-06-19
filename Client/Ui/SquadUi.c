#include <Client/Ui/Element.h>

#include <stdlib.h>
#include <stdio.h>

#include <Client/Ui/Engine.h>
#include <Client/Game.h>
#include <Client/Renderer/Renderer.h>
#include <Client/Renderer/RenderFunctions.h>

struct squad_container_metadata
{
    uint8_t pos;
};

struct squad_petal_metadata
{
    uint8_t client;
    uint8_t row;
    uint8_t col;
    uint8_t prev_id;
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
    rr_renderer_scale(renderer, renderer->scale);
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
    sprintf(&out[0], "Starting in %d", 1 + game->ticks_until_game_start / 25);
    this->width = rr_renderer_get_text_size((char const *) &out) * this->height;
    ui_translate(this, renderer);
    rr_renderer_scale(renderer, renderer->scale);
    rr_renderer_set_fill(renderer, 0xff1dd129);
    renderer->state.filter.amount += 0.2;
    rr_renderer_set_stroke(renderer, 0xff1dd129);
    rr_renderer_set_text_size(renderer, this->height);
    rr_renderer_set_line_width(renderer, this->height * 0.12);
    rr_renderer_set_text_align(renderer, 1);
    rr_renderer_set_text_baseline(renderer, 1);

    rr_renderer_stroke_text(renderer, (char const *) &out, 0, 0);
    rr_renderer_fill_text(renderer, (char const *) &out, 0, 0);
    rr_renderer_free_context_state(renderer, &state);
}

static void squad_loadout_button_on_render(struct rr_ui_element *this, void *_game)
{
    if (this->hidden)
        return;
    struct rr_game *game = _game;
    struct rr_renderer *renderer = game->renderer;
    struct squad_petal_metadata *data = this->misc_data;
    struct rr_renderer_context_state state;

    uint8_t pos = data->row * 5 + data->col;
    uint8_t id = game->squad_members[data->client].loadout[pos].id;
    uint8_t rarity = game->squad_members[data->client].loadout[pos].rarity;
    if (id == 0)
    {
        this->animation_timer += 10;
        if (this->animation_timer >= 100)
        {
            this->animation_timer = 100;
            return;
        }
    }
    else
    {
        data->prev_id = id;
        this->animation_timer -= 10;
        if (this->animation_timer <= 0)
            this->animation_timer = 0;
    }
    rr_renderer_init_context_state(renderer, &state);
    ui_translate(this, renderer);
    rr_renderer_scale(renderer, renderer->scale * (1 - this->animation_timer / 100));

    rr_renderer_scale(renderer, this->width / 60);
    rr_renderer_render_background(renderer, rarity);
    rr_renderer_draw_image(renderer, &game->static_petals[data->prev_id][rarity]);
    
    rr_renderer_free_context_state(renderer, &state);
}

static struct rr_ui_element *rr_ui_flower_icon_init(float radius)
{
    struct rr_ui_element *element = rr_ui_element_init();
    element->width = element->height = radius * 2;
    element->on_render = flower_icon_on_render;
    return element;
}

static struct rr_ui_element *rr_ui_squad_loadout_icon_init(uint8_t client, uint8_t row, uint8_t col)
{
    struct rr_ui_element *element = rr_ui_element_init();
    struct squad_petal_metadata *data = malloc(sizeof *data);
    data->client = client;
    data->row = row;
    data->col = col;
    element->misc_data = data;
    element->width = element->height = 15;
    element->on_render = squad_loadout_button_on_render;
    return element;
}

static struct rr_ui_element *rr_ui_countdown_timer_init()
{
    struct rr_ui_element *element = rr_ui_element_init();
    element->height = 16;
    element->width = rr_renderer_get_text_size((char const *) "Starting in 5") * element->height;
    element->on_render = countdown_text_on_render;
    return element;
}

static struct rr_ui_element *rr_ui_squad_player_container_init(uint8_t spot)
{
    struct rr_ui_element *a = rr_ui_v_container_init(
        rr_ui_container_init(), 10, 10, 3,
        rr_ui_flower_icon_init(25),
        rr_ui_text_init("Flower", 16),
        rr_ui_v_container_init(rr_ui_container_init(), 0, 5, 4,
            rr_ui_h_container_init(rr_ui_container_init(), 0, 5, 5,
                rr_ui_squad_loadout_icon_init(spot, 0, 0),
                rr_ui_squad_loadout_icon_init(spot, 0, 1),
                rr_ui_squad_loadout_icon_init(spot, 0, 2),
                rr_ui_squad_loadout_icon_init(spot, 0, 3),
                rr_ui_squad_loadout_icon_init(spot, 0, 4)
            ),
            rr_ui_h_container_init(rr_ui_container_init(), 0, 5, 5,
                rr_ui_squad_loadout_icon_init(spot, 1, 0),
                rr_ui_squad_loadout_icon_init(spot, 1, 1),
                rr_ui_squad_loadout_icon_init(spot, 1, 2),
                rr_ui_squad_loadout_icon_init(spot, 1, 3),
                rr_ui_squad_loadout_icon_init(spot, 1, 4)
            ),
            rr_ui_h_container_init(rr_ui_container_init(), 0, 5, 5,
                rr_ui_squad_loadout_icon_init(spot, 2, 0),
                rr_ui_squad_loadout_icon_init(spot, 2, 1),
                rr_ui_squad_loadout_icon_init(spot, 2, 2),
                rr_ui_squad_loadout_icon_init(spot, 2, 3),
                rr_ui_squad_loadout_icon_init(spot, 2, 4)
            ),
            rr_ui_h_container_init(rr_ui_container_init(), 0, 5, 5,
                rr_ui_squad_loadout_icon_init(spot, 3, 0),
                rr_ui_squad_loadout_icon_init(spot, 3, 1),
                rr_ui_squad_loadout_icon_init(spot, 3, 2),
                rr_ui_squad_loadout_icon_init(spot, 3, 3),
                rr_ui_squad_loadout_icon_init(spot, 3, 4)
            )
        )
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