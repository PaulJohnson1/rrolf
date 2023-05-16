#include <Client/Game.h>

#include <assert.h>

#ifndef EMSCRIPTEN
#include <libwebsockets.h>
#endif

#include <Client/Renderer/Renderer.h>
#include <Client/InputData.h>
#include <Client/Socket.h>
#include <Client/Simulation.h>
#include <Shared/Utilities.h>
#include <Shared/Encoder.h>

void rr_game_init(struct rr_game *this)
{
    memset(this, 0, sizeof *this);
}

void rr_game_websocket_on_event_function(enum rr_websocket_event_type type, void *data, void *captures, uint64_t size)
{
    struct rr_game *this = captures;
    switch (type)
    {
    case rr_websocket_event_type_open:
        puts("websocket opened");
        break;
    case rr_websocket_event_type_close:
        puts("websocket closed");
        break;
    case rr_websocket_event_type_data:
    {
        rr_log_hex(data, data + size);
        struct rr_encoder encoder;
        rr_encoder_init(&encoder, data);
        switch (rr_encoder_read_uint8(&encoder))
        {
        case 0:
            rr_simulation_read_binary(this->simulation, &encoder);
            break;
        default:
            RR_UNREACHABLE("how'd this happen");
        }
        break;
    }
    default:
        RR_UNREACHABLE("non exhaustive switch expression");
    }
}

void rr_game_tick(struct rr_game *this)
{
    rr_renderer_begin_path(this->renderer);
    rr_renderer_arc(this->renderer, 100 * this->renderer->scale, 100 * this->renderer->scale, 100 * this->renderer->scale);
    rr_renderer_set_fill(this->renderer, 0xffff0000);
    rr_renderer_fill(this->renderer);
    this->socket->user_data = this;
    this->socket->on_event = rr_game_websocket_on_event_function;
#ifndef EMSCRIPTEN
    lws_service(this->socket->socket_context, -1);
#endif
}
