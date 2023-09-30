#include <Client/Ui/Ui.h>

#include <stdio.h>

#include <Client/DOM.h>
#include <Client/Game.h>
#include <Client/InputData.h>
#include <Client/Ui/Engine.h>

static void rivet_container_on_event(struct rr_ui_element *this,
                                     struct rr_game *game)
{
    if (game->input_data->mouse_buttons_up_this_tick & 1)
        rr_copy_string(&game->rivet_account.uuid[0]);
    else if (!(game->input_data->mouse_buttons & 1))
        rr_ui_render_tooltip_below(this, game->rivet_info_tooltip, game);
}

static void render_link(struct rr_ui_element *this, struct rr_game *game)
{
    if (rr_ui_mouse_over(this, game))
        rr_renderer_add_color_filter(game->renderer, 0xff000000, 0.2);
    rr_renderer_scale(game->renderer, game->renderer->scale);
    rr_renderer_set_fill(game->renderer, 0x80ffffff);
    rr_renderer_begin_path(game->renderer);
    rr_renderer_round_rect(game->renderer, -this->abs_width / 2,
                           -this->abs_height / 2, this->abs_width,
                           this->abs_height, 6);
    rr_renderer_fill(game->renderer);
}

static void link_rivet_account(struct rr_ui_element *this, struct rr_game *game)
{
    if (game->input_data->mouse_buttons_up_this_tick & 1)
    { // TODO: make it display a loading status and disable the click
        // funcitonality
        rr_rivet_link_account(game->rivet_account.token, 0);
    }
    else if (!(game->input_data->mouse_buttons & 1))
        rr_ui_render_tooltip_below(this, game->link_account_tooltip, game);
}

static struct rr_ui_element *rr_ui_link_init(struct rr_game *game)
{
    struct rr_ui_element *this = rr_ui_element_init();
    this->width = this->abs_width = this->height = this->abs_height = 30;
    this->on_render = render_link;
    this->on_event = link_rivet_account;

    return this;
}

static struct rr_ui_element *rr_ui_rivet_init(struct rr_game *game)
{
    struct rr_ui_element *this = rr_ui_h_container_init(
        rr_ui_container_init(), 1, 5,
        rr_ui_text_init(game->rivet_account.name, 15, 0xffffffff),
        rr_ui_text_init(game->rivet_account.account_number, 15, 0xffcccccc),
        NULL);
    this->on_event = rivet_container_on_event;
    this->stop_event_propagation = 1;
    return this;
}

static void abandon_game_event(struct rr_ui_element *this, struct rr_game *game)
{
    if (game->input_data->mouse_buttons_up_this_tick & 1)
    {
        struct proto_bug encoder;
        proto_bug_init(&encoder, output_packet);
        proto_bug_write_uint8(&encoder, RR_SERVERBOUND_SQUAD_READY, "header");
        rr_websocket_send(&game->socket, encoder.current - encoder.start);
    }    
    rr_ui_render_tooltip_below(this, game->abandon_game_tooltip, game);
}

static uint8_t simulation_ready(struct rr_ui_element *this, struct rr_game *game)
{
    return game->simulation_ready;
}

struct rr_ui_element *rr_ui_rivet_container_init(struct rr_game *game)
{
    return rr_ui_h_container_init(
        rr_ui_container_init(), 10, 10, rr_ui_settings_toggle_button_init(),
        rr_ui_set_background(
            rr_ui_h_container_init(
                rr_ui_container_init(), 5, 0,
                rr_ui_text_init("discord.gg/kKWAUEbk9T", 15, 0xffffffff), NULL),
        0x40ffffff),
        rr_ui_set_background(
            rr_ui_h_container_init(rr_ui_container_init(), 5,
                0, rr_ui_rivet_init(game),
                NULL),
        0x40ffffff),
        rr_ui_link_init(game), 
        rr_ui_link_toggle(rr_ui_close_button_init(30, abandon_game_event), simulation_ready),
    NULL);
}
