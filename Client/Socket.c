#include <Client/Socket.h>

#include <stdio.h>
#include <string.h>

#ifndef EMSCRIPTEN
#include <libwebsockets.h>
#else
#include <emscripten.h>
#endif

#include <Shared/Crypto.h>

uint8_t output_packet[128 * 1024] = {0};

#ifdef EMSCRIPTEN
void rr_on_socket_event_emscripten(struct rr_websocket *this, enum rr_websocket_event_type type, void *data, uint64_t data_size)
{
    this->on_event(type, data, this->user_data, data_size);
}
#else
int rr_on_socket_event_lws(struct lws *wsi, enum lws_callback_reasons reason, void *user, void *in, size_t size)
{
    struct rr_websocket *this = lws_context_user(lws_get_context(wsi));

    switch (reason)
    {
    case LWS_CALLBACK_CLIENT_ESTABLISHED:
        this->on_event(rr_websocket_event_type_open, NULL, this->user_data, 0);
        break;
    case LWS_CALLBACK_CLIENT_RECEIVE:
        this->on_event(rr_websocket_event_type_data, in, this->user_data, size);
        break;
    case LWS_CALLBACK_CLIENT_CLOSED:
        this->on_event(rr_websocket_event_type_close, NULL, this->user_data, 0);
        break;
    case LWS_CALLBACK_CLIENT_CONNECTION_ERROR:
        fputs((char *)in, stderr);
        puts("");
        abort();
        break;
    }
    return 0;
}
#endif

void rr_websocket_init(struct rr_websocket *this)
{
    memset(this, 0, sizeof *this);
}

void rr_websocket_connect_to(struct rr_websocket *this, char const *host, uint16_t port)
{
    static uint8_t incoming_data[1024 * 1024];
#ifdef EMSCRIPTEN
    EM_ASM({
        setTimeout(function() {
            let string = "";
            while (Module.HEAPU8[$1])
                string += String.fromCharCode(Module.HEAPU8[$1++]);
            console.log("connecting to socket", string);
            if (window.socket)
                window.socket.close();
            let socket = window.socket = new WebSocket("ws://" + string + ':' + $2);
            socket.binaryType = "arraybuffer";
            socket.onopen = function()
            {
                Module._rr_on_socket_event_emscripten($0, 0, 0, 0);
            };
            socket.onclose = function()
            {
                Module._rr_on_socket_event_emscripten($0, 1, 0, 0);
            };
            socket.onmessage = async function(event)
            {
                Module.HEAPU8.set(new Uint8Array(event.data), $3);
                Module._rr_on_socket_event_emscripten($0, 2, $3, new Uint8Array(event.data).length);
            };
        }, 0);
    }, this, host, port, &incoming_data[0]);
#else
    struct lws_context_creation_info info;
    struct lws_protocols protocols[2] = {
        {"g", rr_on_socket_event_lws, 0, 0},
        {NULL, NULL, 0, 0}
    };
    memset(&info, 0, sizeof info);
    protocols[0].callback = rr_on_socket_event_lws;
    protocols[0].name = "g";

	info.port = CONTEXT_PORT_NO_LISTEN;
	info.protocols = protocols;
	info.gid = -1;
	info.uid = -1;
    info.user = this;
    info.pt_serv_buf_size = 1024 * 1024;
    
    this->socket_context = lws_create_context(&info);

    struct lws_client_connect_info connection_info;
    memset(&connection_info, 0, sizeof connection_info);
    connection_info.context = this->socket_context;
    connection_info.address = host;
    connection_info.port = port;
    connection_info.host = lws_canonical_hostname(this->socket_context);
    connection_info.origin = "ggez";
    connection_info.protocol = "g";
    this->socket = lws_client_connect_via_info(&connection_info);

#endif
}

void rr_websocket_send(struct rr_websocket *this, uint8_t *start, uint8_t *end)
{
    rr_encrypt(start, end - start, this->serverbound_encryption_key);
    this->serverbound_encryption_key = rr_get_hash(rr_get_hash(this->serverbound_encryption_key));
#ifndef EMSCRIPTEN
lws_write(this->socket, start, end - start, LWS_WRITE_BINARY);
#else
EM_ASM({
    window.socket.send(Module.HEAPU8.subarray($0, $1));
}, start, end);
#endif
}