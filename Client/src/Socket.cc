#include <Socket.hh>

#include <iostream>

#ifdef WASM_BUILD
extern "C"
{
    void OnMessage(app::Socket *socket, uint8_t *message)
    {
        // std::cout << "template <typename T> " << (void *)message << '\n';
        socket->m_OnMessage(message);
    }
    void OnOpen(app::Socket *socket)
    {
        // socket->m_OnOpen();
    }
    void OnClose(app::Socket *socket)
    {
        // socket->m_OnClose();
    }
}
#endif

namespace app
{
    Socket::Socket(std::string url)
        : m_Url(url)
    {
    }

    void Socket::Connect()
    {
#ifdef WASM_BUILD
        EM_ASM({
            let string = "";
            for (let i = $1; i < $1 + $2; i++)
                string += String.fromCharCode(Module.HEAPU8[i]);
            console.log("connecting to socket", string);
            let socket = window.socket = new WebSocket(string);
            socket.binaryType = "arraybuffer";
            socket.onopen = function()
            {
                Module._OnOpen($0);
            };
            socket.onmessage = function(event)
            {
                const data = event.data;
                const buffer = Module._malloc(data.length);
                Module.HEAPU8.set(data, buffer);
                Module._OnMessage($0, buffer);
                Module._free(buffer);
            };
        },
               this, m_Url.c_str(), m_Url.size());
#else
        m_WebSocketClient.init_asio();
        m_WebSocketClient.set_access_channels(websocketpp::log::alevel::none);
        websocketpp::lib::error_code error;
        m_ConnectionPointer = m_WebSocketClient.get_connection("ws://localhost:8000", error);
        assert(!error);
        m_ConnectionPointer->set_close_handler([&](websocketpp::connection_hdl hdl)
                                               { m_OnClose(); });
        m_ConnectionPointer->set_open_handler([&](websocketpp::connection_hdl hdl)
                                              { m_OnOpen(); });
        m_ConnectionPointer->set_message_handler([&](websocketpp::connection_hdl hdl, Client::message_ptr m)
                                                 { m_OnMessage((uint8_t *)m->get_raw_payload().c_str()); });

        m_WebSocketClient.connect(m_ConnectionPointer);
        m_WebSocketClient.run();
#endif
    }
}
