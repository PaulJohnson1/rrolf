#include <vector>

#include <websocketpp/config/asio_no_tls.hpp>
#include <websocketpp/server.hpp>

#include <Server/Client.hh>
#include <Server/Simulation.hh>

namespace
{
    typedef websocketpp::server<websocketpp::config::asio> WebSocketServer;
}

namespace app
{
    class Server
    {
        uint32_t m_TickCount = 0;
        std::vector<Client *> m_Clients;

    public:
        Simulation m_Simulation;
        WebSocketServer m_Server;

        Server();

        void Run();
        void OnClientConnect(websocketpp::connection_hdl);
        void OnClientDisconnect(websocketpp::connection_hdl);
        void OnMessage(websocketpp::connection_hdl, WebSocketServer::message_ptr);
        void Tick();
    };
}
