#include <Client/Ui/Ui.h>

#include <stdio.h>
#include <stdlib.h>

#include <Client/Game.h>
#include <Client/InputData.h>
#include <Client/Renderer/RenderFunctions.h>
#include <Client/Renderer/Renderer.h>
#include <Client/Ui/Engine.h>
#include <Shared/Utilities.h>

void render_flower(uint8_t is_frown, struct rr_ui_element *element,
                   struct rr_game *game)
{
    struct rr_renderer_context_state state;
    struct rr_renderer *renderer = game->renderer;
    rr_renderer_scale(renderer, renderer->scale);
    rr_renderer_set_stroke(renderer, 0xffcfbb50);
    rr_renderer_set_fill(renderer, 0xffffe763);
    rr_renderer_set_line_width(renderer, 3);
    rr_renderer_begin_path(renderer);
    rr_renderer_arc(renderer, 0, 0, element->width * 0.5);
    rr_renderer_fill(renderer);
    rr_renderer_stroke(renderer);
    rr_renderer_scale(renderer, element->width / 50);
    struct rr_renderer_context_state state1;
    rr_renderer_context_state_init(renderer, &state1);
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
    rr_renderer_context_state_free(renderer, &state1);

    rr_renderer_context_state_init(renderer, &state1);
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
    rr_renderer_context_state_free(renderer, &state1);
    rr_renderer_set_stroke(renderer, 0xff222222);
    rr_renderer_set_line_width(renderer, 1.5);
    rr_renderer_set_line_cap(renderer, 1);
    rr_renderer_begin_path(renderer);
    rr_renderer_move_to(renderer, -6, 10);
    rr_renderer_quadratic_curve_to(renderer, 0, is_frown ? 4 : 15, 6, 10);
    rr_renderer_stroke(renderer);
    rr_renderer_context_state_free(renderer, &state);
}

static void render_flower_frown(struct rr_ui_element *element,
                                struct rr_game *game)
{
    render_flower(1, element, game);
}

static void render_flower_not_frown(struct rr_ui_element *element,
                                    struct rr_game *game)
{
    render_flower(0, element, game);
}

struct rr_ui_element *rr_ui_flower_init(uint8_t frowning, float size)
{
    struct rr_ui_element *element = rr_ui_element_init();
    element->width = element->abs_width = element->height =
        element->abs_height = size;

    if (frowning)
        element->on_render = render_flower_frown;
    else
        element->on_render = render_flower_not_frown;

    return element;
}

static uint8_t choose(struct rr_ui_element *this, struct rr_game *game)
{
    struct rr_ui_choose_element_metadata *data = this->data;
    struct rr_game_squad_client *member = data->data;
    return member->in_use;
}

struct squad_loadout_button_metadata
{
    struct rr_game_loadout_petal *petal;
    uint8_t prev_id;
    uint8_t prev_rarity;
};

static uint8_t squad_loadout_button_should_show(struct rr_ui_element *this,
                                                struct rr_game *game)
{
    struct squad_loadout_button_metadata *data = this->data;
    return data->petal->id;
}

static void squad_loadout_button_animate(struct rr_ui_element *this,
                                         struct rr_game *game)
{
    struct squad_loadout_button_metadata *data = this->data;
    if (data->petal->id != 0)
        data->prev_id = data->petal->id;
    data->prev_rarity = data->petal->rarity;
    rr_renderer_scale(game->renderer, (1 - this->animation));
}

static void squad_loadout_button_on_render(struct rr_ui_element *this,
                                           struct rr_game *game)
{
    struct squad_loadout_button_metadata *data = this->data;
    struct rr_renderer *renderer = game->renderer;
    rr_renderer_scale(renderer, renderer->scale * this->width / 60);
    rr_renderer_render_background(renderer, data->prev_rarity);
    rr_renderer_draw_image(
        renderer, &game->static_petals[data->prev_id][data->prev_rarity]);
}

static struct rr_ui_element *
squad_loadout_button_init(struct rr_game_loadout_petal *petal)
{
    struct rr_ui_element *this = rr_ui_element_init();
    struct squad_loadout_button_metadata *data = malloc(sizeof *data);
    data->petal = petal;
    data->prev_id = 0;
    this->data = data;
    this->abs_width = this->width = 15;
    this->abs_height = this->height = 15;
    this->on_render = squad_loadout_button_on_render;
    this->animate = squad_loadout_button_animate;
    this->should_show = squad_loadout_button_should_show;
    return this;
}

static uint8_t should_be_ready(struct rr_ui_element *choose,
                               struct rr_game *game)
{
    return ((struct rr_game_squad_client
                 *)((struct rr_ui_choose_element_metadata *)choose->data)
                ->data)
        ->ready;
}

static struct rr_ui_element *
rr_ui_player_init(struct rr_game_squad_client *player)
{
    struct rr_ui_element *choose_container = rr_ui_choose_element_init(
        rr_ui_flower_init(0, 50), rr_ui_flower_init(1, 50), should_be_ready);
    ((struct rr_ui_choose_element_metadata *)choose_container->data)->data =
        player;
    return choose_container;
}

struct rr_ui_element *
rr_ui_squad_player_container_init(struct rr_game_squad_client *member)
{
    struct rr_ui_element *b = rr_ui_text_init("Empty", 15, 0xffffffff);
    struct rr_ui_element *loadout = rr_ui_2d_container_init(4, 5, 0, 2);
    for (uint8_t i = 0; i < 20; ++i)
        rr_ui_container_add_element(
            loadout,
            rr_ui_set_justify(squad_loadout_button_init(&member->loadout[i]),
                              -1, -1));
    // manually set the size if we want it to stay constant
    loadout->abs_width = loadout->width = 2 * 10 + (15 + 5) * 5 - 10;
    loadout->abs_height = loadout->height = 2 * 10 + (15 + 5) * 4 - 10;
    struct rr_ui_element *a = rr_ui_v_container_init(
        rr_ui_container_init(), 0, 10, 3, rr_ui_player_init(member),
        rr_ui_text_init(&member->name[0], 18, 0xffffffff), loadout);
    struct rr_ui_element *this = rr_ui_choose_element_init(a, b, choose);
    struct rr_ui_choose_element_metadata *data = this->data;
    data->data = member;

    return rr_ui_set_background(
        rr_ui_v_container_init(rr_ui_container_init(), 10, 10, 1, this),
        0x40ffffff);
}

static void squad_countdown(struct rr_ui_element *this, struct rr_game *game)
{
    struct dynamic_text_metadata *data = this->data;
    if (game->ticks_until_game_start == 125)
        data->text[0] = 0;
    else
        data->text[sprintf(data->text, "Starting in %d",
                           game->ticks_until_game_start / 25)] = 0;
}

struct rr_ui_element *rr_ui_countdown_init(struct rr_game *game)
{
    return rr_ui_dynamic_text_init(18, 0xffffffff, squad_countdown);
}

struct info_metadata
{
    struct rr_ui_element *question_mark;
    struct rr_ui_element *tooltip;
};

static void info_data_on_event(struct rr_ui_element *this, struct rr_game *game)
{
    rr_ui_render_tooltip_above(this, game->squad_info_tooltip, game);
}

static void render_info(struct rr_ui_element *element, struct rr_game *game)
{
    rr_renderer_begin_path(game->renderer);
    rr_renderer_set_line_width(game->renderer, 2.0f);
    rr_renderer_set_stroke(game->renderer, 0x40000000);
    rr_renderer_arc(game->renderer, 0.0f, 0.0f, 10.0f);
    rr_renderer_stroke(game->renderer);
    // the ? text element
    struct info_metadata *data = element->data;

    data->question_mark->on_render(data->question_mark, game);
}

struct rr_ui_element *rr_ui_info_init()
{
    struct rr_ui_element *element = rr_ui_element_init();
    element->data = malloc(sizeof(struct info_metadata));
    struct info_metadata *data = element->data;
    data->question_mark = rr_ui_text_init("?", 18, 0xffffffff);

    element->abs_width = element->abs_height = element->width =
        element->height = 20;

    element->on_render = render_info;
    element->on_event = info_data_on_event;
    return element;
}

static void labeled_button_poll_events(struct rr_ui_element *this, struct rr_game *game)
{
    struct labeled_button_metadata *data = this->data;
    if (game->socket_pending)
    {
        this->fill = 0xff999999;
        data->text = "Finding...";
    }
    else
    {
        rr_ui_element_check_if_focused(this, game);
        this->fill = 0xffd4b30c;
        if (game->socket_ready)
            data->text = "Find Squad";
        else
        {
            data->text = "Find Squad";
            this->fill = 0xffd4b30c;
        }
    }
}

static void join_button_on_event(struct rr_ui_element *this, struct rr_game *game)
{
    if (game->input_data->mouse_buttons_up_this_tick & 1)
    {
        if (game->socket_ready)
        {
            struct proto_bug encoder;
            proto_bug_init(&encoder, output_packet);
            proto_bug_write_uint8(&encoder, 69, "header");
            rr_websocket_send(&game->socket, encoder.start, encoder.current);
        }
        else if (!game->socket_pending)
        {
            rr_game_connect_socket(game);
        }
    }
}

static void squad_join_button_on_event(struct rr_ui_element *this,
                                       struct rr_game *game)
{
    struct labeled_button_metadata *data = this->data;
    if (game->input_data->mouse_buttons_up_this_tick & 1)
    {
        if (!game->socket_pending)
        {
            if (game->socket_ready)
                rr_websocket_disconnect(&game->socket, game);
            rr_game_connect_socket(game);
        }
    }
}

struct rr_ui_element *rr_ui_squad_button_init()
{
    struct rr_ui_element *this = rr_ui_labeled_button_init("Find Squad", 36, 0);
    this->fill = 0xffd4b30c;
    this->poll_events = labeled_button_poll_events;
    this->on_event = squad_join_button_on_event;
    return this;
}

struct rr_ui_element *rr_ui_join_button_init()
{
    struct rr_ui_element *this = rr_ui_labeled_button_init("Join", 36, 0);
    //this->poll_events = labeled_button_poll_events;
    this->on_event = join_button_on_event;
    return this;
}
