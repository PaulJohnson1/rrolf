#include <Client/Socket.hh>

#include <iostream>

static uint8_t g_MessageData[1024*1024];
#ifdef EMSCRIPTEN
extern "C"
{
    void OnMessage(app::Socket *socket)
    {
        socket->OnMessage();
    }
    void OnOpen(app::Socket *socket)
    {
        socket->OnOpen();
    }
    void OnClose(app::Socket *socket)
    {
        socket->OnClose();
    }
}
#endif

namespace app
{
    Socket::Socket(std::string url, std::function<void()> OnOpen, std::function<void()> OnClose, std::function<void(uint8_t *)> OnMessage)
        : m_Url(url),
          m_OnOpen(OnOpen),
          m_OnClose(OnClose),
          m_OnMessage(OnMessage)
    {
    }

    void Socket::OnOpen()
    {
        m_OnOpen();
    }

    void Socket::OnClose()
    {
        m_OnClose();
    }

    void Socket::OnMessage()
    {
        m_OnMessage(g_MessageData);
    }

    void Socket::SendPacket(uint8_t *data, size_t size)
    {
#ifdef EMSCRIPTEN
        EM_ASM({
            const data = new Uint8Array($1);
            for (let i = 0; i < $1; i++)
                data[i] = HEAPU8[$0 + i];
            window.socket.send(data);
        }, data, (uint32_t)size);
#else
        m_WebSocketClient.send(m_ConnectionPointer->get_handle(), (void *)data, size, websocketpp::frame::opcode::binary);
#endif
    }

    void Socket::Connect()
    {
#ifdef EMSCRIPTEN
        EM_ASM({
            let string = "";
            for (let i = $2; i < $2 + $3; i++)
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
                Module.HEAPU8.set(new Uint8Array(event.data), $1);
                Module._OnMessage($0);
            };
        }, this, g_MessageData, m_Url.c_str(), m_Url.size());
#else
        m_WebSocketClient.init_asio();
        m_WebSocketClient.set_access_channels(websocketpp::log::alevel::none);
        websocketpp::lib::error_code error;
        m_ConnectionPointer = m_WebSocketClient.get_connection("ws://localhost:8000", error);
        assert(!error);
        m_ConnectionPointer->set_close_handler([&](websocketpp::connection_hdl hdl)
                                               { OnClose(); });
        m_ConnectionPointer->set_open_handler([&](websocketpp::connection_hdl hdl)
                                              { OnOpen(); });
        m_ConnectionPointer->set_message_handler([&](websocketpp::connection_hdl hdl, Client::message_ptr m)
                                                 { m_OnMessage((uint8_t *)m->get_raw_payload().c_str()); });

        m_WebSocketClient.connect(m_ConnectionPointer);
        m_WebSocketClient.run();
#endif
    }
}
