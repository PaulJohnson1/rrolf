#include <Client/Ui/Ui.h>

#include <Client/Ui/Engine.h>

#include <Client/Game.h>
#include <Client/InputData.h>
#include <Client/Simulation.h>
#include <Client/Socket.h>
#include <Shared/pb.h>

static void continue_to_squad_event(struct rr_ui_element *this, struct rr_game *game)
{
    if (game->input_data->mouse_buttons_up_this_tick & 1)
    {
        struct proto_bug encoder;
        proto_bug_init(&encoder, output_packet);
        proto_bug_write_uint8(&encoder, RR_SERVERBOUND_SQUAD_READY, "header");
        rr_websocket_send(&game->socket, encoder.current - encoder.start);
    }
}

static uint8_t game_over(struct rr_ui_element *this, struct rr_game *game)
{
    return game->simulation_ready && game->player_info->flower_id == RR_NULL_ENTITY;
}

static uint8_t game_ready(struct rr_ui_element *this, struct rr_game *game)
{
    return game->simulation_ready;
}

struct rr_ui_element *rr_ui_finished_game_screen_init()
{
    struct rr_ui_element *leave_game =
        rr_ui_labeled_button_init("Continue", 36, NULL);
    leave_game->on_event = continue_to_squad_event;
    struct rr_ui_element *this = rr_ui_v_container_init(
        rr_ui_container_init(), 10, 10,
        rr_ui_text_init("You Died", 48, 0xffffffff), leave_game, NULL);
    this->should_show = game_over;
    return this;
}

static void abandon_game_button_on_render(struct rr_ui_element *this, struct rr_game *game)
{
    struct rr_renderer *renderer = game->renderer;
    rr_renderer_scale(renderer, renderer->scale);
    if (rr_ui_mouse_over(this, game))
        rr_renderer_add_color_filter(renderer, 0xff000000, 0.2);
    rr_renderer_set_fill(renderer, this->fill);
    rr_renderer_round_rect(renderer, -this->abs_width / 2, -this->abs_height / 2, this->abs_width, this->abs_height, this->abs_height / 4);
    rr_renderer_fill(renderer);
    rr_renderer_set_line_width(renderer, this->abs_width / 6);
    rr_renderer_set_line_cap(renderer, 1);
    rr_renderer_set_stroke(renderer, 0xcfffffff);
    rr_renderer_begin_path(renderer);
    rr_renderer_move_to(renderer, -this->abs_width * 0.25, -this->abs_height * 0.25);
    rr_renderer_line_to(renderer, this->abs_width * 0.25, this->abs_height * 0.25);
    rr_renderer_move_to(renderer, -this->abs_width * 0.25, this->abs_height * 0.25);
    rr_renderer_line_to(renderer, this->abs_width * 0.25, -this->abs_height * 0.25);
    rr_renderer_stroke(renderer);
}

static void abandon_game_event(struct rr_ui_element *this, struct rr_game *game)
{
    continue_to_squad_event(this, game);
    rr_ui_render_tooltip_below(this, game->abandon_game_tooltip, game);
}

struct rr_ui_element *rr_ui_abandon_game_button_init(float w)
{
    struct rr_ui_element *this = rr_ui_element_init();
    this->on_event = abandon_game_event;
    this->should_show = game_ready;
    this->abs_width = this->abs_height = w;
    this->fill = 0x80fc3434;
    this->on_render = abandon_game_button_on_render;
    return this;
}