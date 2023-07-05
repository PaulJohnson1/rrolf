#include <Client/Ui/Ui.h>

#include <stdio.h>
#include <stdlib.h>
#include <string.h>

#include <Client/Game.h>
#include <Client/InputData.h>
#include <Client/Renderer/Renderer.h>

#include <Shared/pb.h>

struct labeled_button_metadata
{
    uint8_t *toggle;
    char const *text;
};

static void button_on_event(struct rr_ui_element *this, struct rr_game *game)
{
    struct labeled_button_metadata *data = this->data;
    if (game->input_data->mouse_buttons_this_tick & 1 && data->toggle != NULL)
        (*(data->toggle)) ^= 1;
}

static void squad_join_button_on_event(struct rr_ui_element *this,
                                       struct rr_game *game)
{
    struct labeled_button_metadata *data = this->data;
    if (game->input_data->mouse_buttons_this_tick & 1)
    {
        if (!game->socket_ready)
            rr_game_connect_socket(game);
        else
        {
            struct proto_bug encoder;
            proto_bug_init(&encoder, output_packet);
            proto_bug_write_uint8(&encoder, 69, "header");
            rr_websocket_send(&game->socket, encoder.start, encoder.current);
        }
    }
}

static void labeled_button_on_render(struct rr_ui_element *this,
                                     struct rr_game *game)
{
    struct labeled_button_metadata *data = this->data;
    struct rr_renderer *renderer = game->renderer;
    if (game->focused == this)
    {
        renderer->state.filter.amount = 0.2;
    }
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
    rr_renderer_set_text_baseline(renderer, 1);
    rr_renderer_set_text_align(renderer, 1);
    renderer->state.filter.amount = 0;
    rr_renderer_set_fill(renderer, 0xffffffff);
    rr_renderer_set_stroke(renderer, 0xff222222);
    rr_renderer_set_text_size(renderer, this->height / 2);
    rr_renderer_set_line_width(renderer, this->height / 2 * 0.12);
    rr_renderer_begin_path(renderer);
    rr_renderer_stroke_text(renderer, data->text, 0, 0);
    rr_renderer_fill_text(renderer, data->text, 0, 0);
}

struct rr_ui_element *rr_ui_labeled_button_init(char const *text, float height,
                                                uint8_t *toggle)
{
    struct rr_ui_element *this = rr_ui_element_init();
    struct labeled_button_metadata *data = malloc(sizeof *data);
    data->toggle = toggle;
    data->text = text;
    this->data = data;
    this->abs_height = this->height = height;
    this->abs_width = this->width = rr_renderer_get_text_size(text) * height;
    this->on_render = labeled_button_on_render;
    this->on_event = squad_join_button_on_event;
    this->fill = 0xff0000ff;
    return this;
}