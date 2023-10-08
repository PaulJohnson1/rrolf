#include <Client/Ui/Ui.h>

#include <string.h>

#include <Client/Ui/Engine.h>
#include <Client/Game.h>
#include <Client/InputData.h>
#include <Client/Simulation.h>
#include <Client/Socket.h>
#include <Shared/pb.h>

static void chat_bar_on_event(struct rr_ui_element *this, struct rr_game *game)
{
    if (game->input_data->mouse_buttons_up_this_tick & 1)
    {
        game->chat.chat_active = 1;
    }
}

static struct rr_ui_element *chat_not_showing_element_init()
{
    struct rr_ui_element *this = rr_ui_set_background(
            rr_ui_h_container_init(rr_ui_container_init(), 10, 0, 
            rr_ui_text_init("Press [Enter] or click here to chat", 14, 0xffffffff),
            NULL
        )
    , 0x80000000);
    this->abs_width = this->width = 300;
    this->resizeable = rr_ui_not_resizeable;
    this->stop_event_propagation = 1;
    this->on_event = chat_bar_on_event;
    return this;
}

static uint8_t chatbar_choose(struct rr_ui_element *this, struct rr_game *game)
{
    return game->chat.chat_active || game->chat.sending[0];
}

struct rr_ui_element *rr_ui_chat_bar_init(struct rr_game *game)
{
    struct rr_ui_element *chatbar = rr_ui_text_input_init(300, 14 / 0.8, game->chat.sending, 64, "_0x4523");
    chatbar->fill = 0x00000000;
    chatbar = rr_ui_set_background(rr_ui_h_container_init(rr_ui_container_init(), 8, 10, 
        rr_ui_text_init("[Squad]", 14, 0xffffcccc),
        chatbar,
        NULL
    ), 0xffffffff);
    struct rr_ui_element *this = rr_ui_choose_element_init(chatbar, chat_not_showing_element_init(), chatbar_choose);
    return this;
}