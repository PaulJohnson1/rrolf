#include <websocketpp/config/asio_no_tls.hpp>

#include <vector>

#include <websocketpp/server.hpp>

#include <Client.hh>
#include <Simulation.hh>

namespace
{
    typedef websocketpp::server<websocketpp::config::asio> WebSocketServer;
}

class Server
{
    uint32_t m_TickCount = 0;
    WebSocketServer m_Server;
    std::vector<Client *> m_Clients;

public:
    Simulation m_Simulation;
    Server();

    void Run();
    void OnClientConnect(websocketpp::connection_hdl);
    void OnClientDisconnect(websocketpp::connection_hdl);
    void Tick();
};
