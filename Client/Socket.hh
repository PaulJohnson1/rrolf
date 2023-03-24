#ifdef WASM_BUILD
#include <emscripten.h>
#else
#include <websocketpp/config/asio_client.hpp>
#include <websocketpp/client.hpp>
#endif

#include <functional>
#include <string>

namespace bc
{
    class BinaryCoder;
}

namespace app
{
    class Socket
    {
#ifndef WASM_BUILD
        typedef websocketpp::client<websocketpp::config::asio_client> Client;
        Client m_WebSocketClient;
        Client::connection_ptr m_ConnectionPointer;        
#endif

    public:
        std::function<void(uint8_t *)> m_OnMessage;
        std::function<void()> m_OnOpen;
        std::function<void()> m_OnClose;

        std::string m_Url;

        Socket(std::string, std::function<void()>, std::function<void()>, std::function<void(uint8_t *)>);

        void OnMessage();
        void OnClose();
        void OnOpen();
        void SendPacket(uint8_t *, size_t);
        void Connect();
    };
}