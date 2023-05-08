#include <Server/Server.hh>

#include <thread>
#include <iostream>

#include <curl/curl.h>

#include <Server/Simulation.hh>

namespace app
{
    Server::Server()
        : m_Simulation(*this)
    {
        lws_context_creation_info info;
        lws_protocols protocol;
        memset(&info, 0, sizeof(info));
        memset(&protocol, 0, sizeof(protocol));

        protocol.name = "game";
            protocol.callback = &Server::OnClientEvent;

        info.port = 8000;
        info.protocols = &protocol;
        info.gid = -1;
        info.uid = -1;

        m_Server = lws_create_context(&info);
    }

    void Server::Tick()
    {
        m_Simulation.Tick();
    }

    void Server::Run()
    {
        using namespace std::chrono_literals;
        while (true)
        {
            auto start = std::chrono::steady_clock::now();
            lws_service(m_Server, -1);
            Tick();
            auto end = std::chrono::steady_clock::now();
            auto timeTaken = std::chrono::duration_cast<std::chrono::nanoseconds>(end - start).count();
            std::cout << (double)timeTaken / 1'000'000.0f << "ms\n";
            auto sleepTime = std::max(0ns, 40ms - std::chrono::nanoseconds(timeTaken));
            std::this_thread::sleep_for(sleepTime);
        }
    }

    int Server::OnClientEvent(lws *socket, lws_callback_reasons reason, void *user, void *data, size_t size)
    {
        switch (reason)
        {
        case LWS_CALLBACK_ESTABLISHED:
            std::cout << "client connected\n";
            break;
        case LWS_CALLBACK_RECEIVE:
            std::cout << "client recieve packet\n";
            break;
        case LWS_CALLBACK_CLOSED:
            std::cout << "client closed\n";
            break;
        default:
            break;
        }

        return 0;
    }

    //     void Server::OnClientConnect(websocketpp::connection_hdl hdl)
    //     {
    // #ifdef RIVET_PRODUCTION_BUILD
    //         char const *rivetToken = getenv("RIVET_LOBBY_TOKEN");
    //         assert(rivetToken);
    //         std::cout << "player connected " << rivetToken << '\n';
    //         curl_slist *list = nullptr;
    //         CURL *curl = curl_easy_init();
    //         assert(curl);
    //         char header[500] = "Authorization: Bearer ";
    //         std::string body = "{\"player_token\":\"" + m_Server.get_con_from_hdl(hdl)->get_uri()->get_resource().substr(1) + "\"}";
    //         list = curl_slist_append(list, strcat(header, rivetToken));
    //         assert(curl_easy_setopt(curl, CURLOPT_HTTPHEADER, list) == CURLE_OK);
    //         assert(curl_easy_setopt(curl, CURLOPT_POST, 1) == CURLE_OK);
    //         assert(curl_easy_setopt(curl, CURLOPT_POSTFIELDS, body.c_str()) == CURLE_OK);
    //         assert(curl_easy_setopt(curl, CURLOPT_URL, "https://matchmaker.api.rivet.gg/v1/players/connected") == CURLE_OK);
    //         assert(curl_easy_perform(curl) == CURLE_OK);
    //         curl_easy_cleanup(curl);
    //         curl_slist_free_all(list);
    // #endif

    //         m_Clients.push_back(new Client(hdl, m_Simulation));
    //     }

    //     void Server::OnClientDisconnect(websocketpp::connection_hdl hdl)
    //     {
    //         std::lock_guard<std::mutex> l(m_Mutex);
    //         for (uint64_t i = 0; i < m_Clients.size(); i++)
    //             if (m_Clients[i]->GetHdl().lock() == hdl.lock())
    //             {
    //                 delete m_Clients[i];
    //                 m_Clients.erase(m_Clients.begin() + i);
    //                 return;
    //             }

    //         std::cout << "something went wrong\n";
    //     }

    //     void Server::OnMessage(websocketpp::connection_hdl hdl, WebSocketServer::message_ptr message)
    //     {
    //         for (uint64_t i = 0; i < m_Clients.size(); i++)
    //             if (m_Clients[i]->GetHdl().lock() == hdl.lock())
    //                 m_Clients[i]->ReadPacket((uint8_t *)message->get_raw_payload().c_str(), message->get_raw_payload().size());
    //     }
}
