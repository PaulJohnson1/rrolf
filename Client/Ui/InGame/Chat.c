#include <Client/Ui/Ui.h>

#include <string.h>

#include <Client/Ui/Engine.h>
#include <Client/Game.h>
#include <Client/InputData.h>
#include <Client/Simulation.h>
#include <Client/Socket.h>
#include <Shared/Bitset.h>
#include <Shared/pb.h>

static void chat_bar_on_event(struct rr_ui_element *this, struct rr_game *game)
{
    if (game->input_data->mouse_buttons_up_this_tick & 1)
    {
        game->chat.chat_active = 1;
    }
}

static void chat_bar_animate(struct rr_ui_element *this, struct rr_game *game)
{
    rr_ui_default_animate(this, game);
    if (game->chat.chat_active)
    {
        this->fill = 0xffffffff;
        this->stroke = 0xff222222;
    }
    else
        this->fill = 0x80000000;
    if (rr_bitset_get(game->input_data->keys_pressed_this_tick, 13))
    {
        if (game->chat.chat_active)
        {
            if (game->chat.sending[0] != 0)
            {
                struct proto_bug encoder;
                proto_bug_init(&encoder, output_packet);
                proto_bug_write_uint8(&encoder, rr_serverbound_chat, "header");
                proto_bug_write_string(&encoder, game->chat.sending, 64, "chat");
                rr_websocket_send(&game->socket, encoder.current - encoder.start);
            }
            memset(game->chat.sending, 0, sizeof game->chat.sending);
        }
        game->chat.chat_active ^= 1;
    }
};

static uint8_t chatbar_choose(struct rr_ui_element *this, struct rr_game *game)
{
    return game->chat.chat_active || game->chat.sending[0];
}

static void chatbar_animate(struct rr_ui_element *this, struct rr_game *game)
{
    struct rr_ui_text_input_metadata *data = this->data;
    data->focused = game->chat.chat_active;
}

static void chatbar_on_event(struct rr_ui_element *this, struct rr_game *game)
{
    uint8_t mouse_over = rr_ui_mouse_over(this, game);
    if (game->input_data->mouse_buttons_up_this_tick & 1)
        game->chat.chat_active = mouse_over;
}

static struct rr_ui_element *rr_ui_chat_text_init(struct rr_game_chat_message *message)
{
    return rr_ui_set_justify(
        rr_ui_h_container_init(rr_ui_container_init(), 0, 10, 
            rr_ui_text_init(message->sender_name, 16, 0xffffffcf), 
            rr_ui_text_init(message->message, 16, 0xffffffff),
            NULL
        ),
    -1, -1);
}

struct rr_ui_element *rr_ui_message_box_init(struct rr_game *game)
{
    return rr_ui_v_container_init(rr_ui_container_init(), 0, 10,
        rr_ui_chat_text_init(&game->chat.messages[0]),
        rr_ui_chat_text_init(&game->chat.messages[1]),
        rr_ui_chat_text_init(&game->chat.messages[2]),
        rr_ui_chat_text_init(&game->chat.messages[3]),
        rr_ui_chat_text_init(&game->chat.messages[4]),
        rr_ui_chat_text_init(&game->chat.messages[5]),
        rr_ui_chat_text_init(&game->chat.messages[6]),
        rr_ui_chat_text_init(&game->chat.messages[7]),
        rr_ui_chat_text_init(&game->chat.messages[8]),
        rr_ui_chat_text_init(&game->chat.messages[9]),
        NULL
    );
}

struct rr_ui_element *rr_ui_chat_bar_init(struct rr_game *game)
{
    struct rr_ui_element *chatbar = rr_ui_text_input_init(200, 14, game->chat.sending, 64, "_0x4523");
    chatbar->animate = chatbar_animate;
    chatbar->on_event = chatbar_on_event;
    struct rr_ui_element *text = rr_ui_set_justify(rr_ui_text_init("Press [Enter] or click here to chat", 14, 0xffffffff), -1, -1);
    text->prevent_on_event = 1;
    chatbar->fill = 0xff222222;
    chatbar->stroke = 0xffffffff;
    struct rr_ui_element *this = rr_ui_set_background(
        rr_ui_h_container_init(rr_ui_container_init(), 10, 0, 
        rr_ui_choose_element_init(
            rr_ui_flex_container_init(
                rr_ui_text_init("[Squad]", 14, 0xffffffff),
                chatbar,
                10
            ),
            text,
            chatbar_choose
        ),
        NULL)
    , 0x80000000);
    this->animate = chat_bar_animate;
    this->on_event = chat_bar_on_event;
    this->elements.start[0]->on_event = this->on_event;
    return rr_ui_v_container_init(rr_ui_container_init(), 10, 10,
        rr_ui_set_justify(rr_ui_message_box_init(game), -1, -1),
        this,
        NULL
    );
}
