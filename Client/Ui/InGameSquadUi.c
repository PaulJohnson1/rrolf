#include <Client/Ui/Element.h>

#include <stdlib.h>
#include <stdio.h>

#include <Client/Ui/Engine.h>
#include <Client/Game.h>
#include <Client/InputData.h>
#include <Client/Simulation.h>
#include <Client/Renderer/Renderer.h>
#include <Client/Renderer/ComponentRender.h>

struct abandon_game_button_metadata
{
    void (*on_event)(struct rr_ui_element *, uint8_t, struct rr_game *, void *);
};

static void abandon_game_on_event(struct rr_ui_element *this, uint8_t event_type, struct rr_game *game, void *_captures)
{
    if (event_type == 1)
    {
        if (game->socket_ready)
        {
            rr_websocket_disconnect(&game->socket);
            game->socket_ready = 0;
            game->simulation_ready = 0;
            // leave the socket
        }
    }
}

static void abandon_game_button_on_render(struct rr_ui_element *this, void *_game)
{
    if (this->hidden)
        return;
    struct rr_game *game = _game;
    struct rr_renderer *renderer = game->renderer;
    struct abandon_game_button_metadata *data = this->misc_data;
    struct rr_renderer_context_state state;
    rr_renderer_init_context_state(renderer, &state);
    rr_ui_translate(this, renderer);
    rr_renderer_scale(renderer, renderer->scale);
    if (rr_button_is_touching_mouse(this, game))
    {
        if (game->input_data->mouse_buttons_this_tick & 1)
            data->on_event(this, 1, game, NULL);
        if (game->input_data->mouse_buttons & 1)
            renderer->state.filter.amount += 0.2;
    }
    rr_renderer_set_fill(renderer, 0xfff04d0c);
    rr_renderer_set_line_width(renderer, 5);
    renderer->state.filter.amount += 0.2;
    rr_renderer_set_stroke(renderer, 0xfff04d0c);
    rr_renderer_begin_path(renderer);
    rr_renderer_round_rect(renderer, -this->width / 2, -this->height / 2, this->width, this->height, 5);
    rr_renderer_fill(renderer);
    rr_renderer_stroke(renderer);
    renderer->state.filter.amount = 0;
    rr_renderer_set_stroke(renderer, 0xffdddddd);
    rr_renderer_set_line_cap(renderer, 1);
    rr_renderer_begin_path(renderer);
    rr_renderer_move_to(renderer, -8, -8);
    rr_renderer_line_to(renderer, 8, 8);
    rr_renderer_move_to(renderer, 8, -8);
    rr_renderer_line_to(renderer, -8, 8);
    rr_renderer_stroke(renderer);
    rr_renderer_free_context_state(renderer, &state);
}

static void in_game_player_ui_on_render(struct rr_ui_element *this, void *_game)
{
    struct rr_game *game = _game;
    struct rr_renderer *renderer = game->renderer;
    uint8_t pos = *(uint8_t *)&this->misc_data;
    if (game->player_infos[pos] == RR_NULL_ENTITY)
        return;
    struct rr_component_player_info *player_info = rr_simulation_get_player_info(game->simulation, game->player_infos[pos]);
    struct rr_renderer_context_state state;
    rr_renderer_init_context_state(renderer, &state);
    rr_ui_translate(this, renderer);
    rr_renderer_scale(renderer, renderer->scale);
    if (pos == 0)
        rr_renderer_scale(renderer, 1.2);

    rr_renderer_set_stroke(renderer, 0xff222222);
    rr_renderer_set_line_width(renderer, 25);
    rr_renderer_set_line_cap(renderer, 1);
    rr_renderer_begin_path(renderer);
    rr_renderer_move_to(renderer, -100, 0);
    rr_renderer_line_to(renderer, 100, 0);
    rr_renderer_stroke(renderer);
    if (player_info->flower_id != RR_NULL_ENTITY)
    {
        struct rr_component_health *health = rr_simulation_get_health(game->simulation, player_info->flower_id);
        rr_renderer_set_stroke(renderer, 0xff75dd34);
        rr_renderer_set_line_width(renderer, 20);
        rr_renderer_begin_path(renderer);
        rr_renderer_move_to(renderer, -50, 0);
        rr_renderer_line_to(renderer, -50 + 150 * health->health / health->max_health, 0);
        rr_renderer_stroke(renderer);
        rr_renderer_translate(renderer, -100, 0);
        rr_component_flower_render(player_info->flower_id, game);
    }
    rr_renderer_free_context_state(renderer, &state);
}

struct rr_ui_element *rr_ui_abandon_game_button_init()
{
    struct rr_ui_element *element = rr_ui_element_init();
    struct abandon_game_button_metadata *data = calloc(1, sizeof *data);
    element->on_render = abandon_game_button_on_render;
    element->misc_data = data;
    data->on_event = abandon_game_on_event;
    element->width = element->height = 30;
    return element;
}

struct rr_ui_element *rr_ui_in_game_player_ui_init(uint64_t pos)
{
    struct rr_ui_element *element = rr_ui_element_init();
    element->on_render = in_game_player_ui_on_render;
    element->misc_data = (void *)pos;
    element->width = 200;
    element->height = 50;
    if (pos == 0)
    {
        element->width *= 1.2;
        element->height *= 1.2;
    }
    return rr_ui_pad(
        rr_ui_set_justify(
            element, 0, 0),
        50);
}