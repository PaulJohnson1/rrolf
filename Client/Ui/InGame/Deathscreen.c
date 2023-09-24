#include <Client/Ui/Ui.h>

#include <Client/Ui/Engine.h>

#include <Client/Game.h>
#include <Client/InputData.h>
#include <Client/Simulation.h>

static void abandon_game_event(struct rr_ui_element *this, struct rr_game *game)
{
    if (game->input_data->mouse_buttons_up_this_tick & 1)
    {
        struct proto_bug encoder;
        proto_bug_init(&encoder, output_packet);
        proto_bug_write_uint8(&encoder, RR_SERVERBOUND_SQUAD_READY, "header");
        rr_websocket_send(&game->socket, encoder.current - encoder.start);
        game->simulation_ready = 0;
        game->joined_squad = 0;
    }
}

static uint8_t waiting_respawn(struct rr_ui_element *this, struct rr_game *game)
{
    return game->simulation_ready &&
           game->player_info->flower_id == RR_NULL_ENTITY &&
           !game->simulation->game_over;
}

static uint8_t game_over(struct rr_ui_element *this, struct rr_game *game)
{
    return game->simulation_ready && game->simulation->game_over;
}

struct rr_ui_element *rr_ui_waiting_respawn_screen_init()
{
    struct rr_ui_element *this = rr_ui_v_container_init(
        rr_ui_container_init(), 10, 10,
        rr_ui_text_init("You Died", 48, 0xffffffff),
        rr_ui_static_space_init(100),
        rr_ui_text_init("You will respawn next wave", 24, 0xffffffff), NULL);
    this->should_show = waiting_respawn;
    return this;
}

struct rr_ui_element *rr_ui_finished_game_screen()
{
    struct rr_ui_element *leave_game =
        rr_ui_labeled_button_init("Leave game", 36, NULL);
    leave_game->on_event = abandon_game_event;
    struct rr_ui_element *this = rr_ui_v_container_init(
        rr_ui_container_init(), 10, 10,
        rr_ui_text_init("You Died", 48, 0xffffffff), leave_game, NULL);
    this->should_show = game_over;
    return this;
}