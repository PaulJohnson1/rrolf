#include <vector>
#include <mutex>

#include <libwebsockets.h>

#include <Server/Client.hh>
#include <Server/Simulation.hh>

namespace app
{
    class Server
    {
        friend Client;
        uint32_t m_TickCount = 0;

    public:
        lws_context *m_Server;
        std::mutex m_Mutex;
        Simulation m_Simulation;
        std::vector<Client *> m_Clients;

        Server();

        void Run();
        static int OnClientEvent(lws *, lws_callback_reasons, void *, void *, size_t);
        void Tick();
    };
}
