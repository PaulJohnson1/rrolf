#pragma once

#include <stdint.h>

#ifndef EMSCRIPTEN
struct lws_context;
struct lws;
#else
#endif

enum rr_websocket_event_type
{
    rr_websocket_event_type_open,
    rr_websocket_event_type_close,
    rr_websocket_event_type_data
};

struct rr_websocket
{
    uint8_t recieved_first_packet;
    void *user_data;
    void (*on_event)(enum rr_websocket_event_type, void *, void *, uint64_t);
#ifndef EMSCRIPTEN
    struct lws_context *socket_context;
    struct lws *socket;
#endif
    uint64_t encryption_key;
};

void rr_websocket_init(struct rr_websocket *);
void rr_websocket_connect_to(struct rr_websocket *, char const *, uint16_t);
void rr_websocket_send(struct rr_websocket *, uint8_t *, uint8_t *);