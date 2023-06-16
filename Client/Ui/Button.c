#include <Client/Ui/Element.h>

#include <math.h>
#include <stdio.h>
#include <stdlib.h>

#include <Client/Game.h>
#include <Client/Socket.h>
#include <Client/InputData.h>
#include <Client/Renderer/Renderer.h>
#include <Client/Renderer/RenderFunctions.h>
#include <Shared/SimulationCommon.h>

#include <Shared/pb.h>
#include <Shared/StaticData.h>

struct button_metadata
{
    uint32_t fill_style;
    float line_width;
    float round_radius;
    void (*on_event)(struct rr_ui_element *, uint8_t, struct rr_game *, void *);
    char *text;
};

uint8_t rr_button_is_touching_mouse(struct rr_ui_element *this, struct rr_game *game)
{
    float *matrix = game->renderer->state.transform_matrix;
    return fabsf(game->input_data->mouse_x - matrix[2]) < this->width * matrix[0] / 2 && fabsf(game->input_data->mouse_y - matrix[5]) < this->height * matrix[4] / 2;
};

static void respawn_button_event(struct rr_ui_element *this, uint8_t type, struct rr_game *game, void *_captures)
{
    if (type == 1) //mouse_down
    {
        struct proto_bug encoder;
        proto_bug_init(&encoder, output_packet);
        proto_bug_write_uint8(&encoder, 1, "header");
        rr_websocket_send(&game->socket, encoder.start, encoder.current);
    }
}

static void find_server_button_event(struct rr_ui_element *this, uint8_t event_type, struct rr_game *game, void *_captures)
{
    if (game->socket_pending)
        return;
    if (event_type == 1)
    {
        if (game->socket_ready)
        {
            struct proto_bug encoder;
            proto_bug_init(&encoder, output_packet);
            proto_bug_write_uint8(&encoder, 69, "header");
            rr_websocket_send(&game->socket, encoder.start, encoder.current);
        }
        else
            rr_game_connect_socket(game);
    }
}

static void button_on_render(struct rr_ui_element *this, void *_game)
{
    if (this->hidden)
        return;
    struct rr_game *game = _game;
    struct rr_renderer *renderer = game->renderer;
    struct button_metadata *data = this->misc_data;
    struct rr_renderer_context_state state;
    rr_renderer_init_context_state(renderer, &state);
    ui_translate(this, renderer);
    rr_renderer_scale(renderer, renderer->scale);
    if (rr_button_is_touching_mouse(this, game))
    {
        if (game->input_data->mouse_buttons_this_tick & 1)
            data->on_event(this, 1, game, NULL);
        if (game->input_data->mouse_buttons & 1)
            renderer->state.filter.amount += 0.2;
    }    
    rr_renderer_set_fill(renderer, data->fill_style);
    rr_renderer_set_line_width(renderer, data->line_width);
    renderer->state.filter.amount += 0.2;
    rr_renderer_set_stroke(renderer, data->fill_style);
    rr_renderer_begin_path(renderer);
    rr_renderer_round_rect(renderer, -this->width / 2, -this->height / 2, this->width, this->height, data->round_radius);
    rr_renderer_fill(renderer);
    rr_renderer_stroke(renderer);
    renderer->state.filter.amount = 0;
    rr_renderer_set_fill(renderer, 0xffffffff);
    rr_renderer_set_stroke(renderer, 0xff000000);
    rr_renderer_set_text_size(renderer, this->height / 2);
    rr_renderer_set_line_width(renderer, this->height / 2 * 0.12);
    rr_renderer_set_text_align(renderer, 1);
    rr_renderer_set_text_baseline(renderer, 1);
    rr_renderer_stroke_text(renderer, data->text, 0, 0);
    rr_renderer_fill_text(renderer, data->text, 0, 0);
    rr_renderer_free_context_state(renderer, &state);
}

static void server_connection_button_on_render(struct rr_ui_element *this, void *_game)
{
    if (this->hidden)
        return;
    struct rr_game *game = _game;
    struct button_metadata *data = this->misc_data;
    data->text = game->socket_pending ? "Connecting..." : game->socket_ready? "Ready" : "Find Server";
    data->fill_style = game->socket_pending ? 0xff777777 : 0xff1dd129;
    button_on_render(this, _game);
}

struct rr_ui_element *rr_ui_button_init()
{
    struct button_metadata *data = malloc(sizeof *data);
    struct rr_ui_element *element = rr_ui_element_init();
    element->on_render = button_on_render;
    element->misc_data = data;
    return element;
}


struct rr_ui_element *rr_ui_find_server_button_init()
{
    struct rr_ui_element *element = rr_ui_button_init();
    struct button_metadata *data = element->misc_data;
    data->on_event = find_server_button_event;
    data->fill_style = 0xff1dd129;
    data->round_radius = 6;
    data->line_width = 6;
    //data->text = "Find server";
    element->width = 140;
    element->height = 40;
    element->on_render = server_connection_button_on_render;
    return element;
}
