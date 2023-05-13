#include <Server/Server.hh>

#include <thread>
#include <iostream>
#include <cassert>

#include <curl/curl.h>
#include <libwebsockets.h>

#include <Server/Simulation.hh>
#include <Shared/HttpRequest.hh>

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
        info.user = this;

        m_Server = lws_create_context(&info);
        assert(m_Server);
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
#ifndef RIVET_PRODUCTION_BUILD
            std::cout << (double)timeTaken / 1'000'000.0f << "ms\n";
#endif
            auto sleepTime = std::max(0ns, 40ms - std::chrono::nanoseconds(timeTaken));
            std::this_thread::sleep_for(sleepTime);
        }
    }

    int Server::OnClientEvent(lws *socket, lws_callback_reasons reason, void *user, void *data, size_t size)
    {
        Server *_this = (Server *)lws_context_user(lws_get_context(socket));
        std::cout << "client event reason: " << std::to_string(reason) << '\n';
        switch (reason)
        {
        case LWS_CALLBACK_ESTABLISHED:
        {
#ifdef RIVET_PRODUCTION_BUILD
            char uri[500];
            memset(uri, 0, sizeof(uri));
            lws_hdr_copy(socket, uri, 500, WSI_TOKEN_GET_URI);
            if (!IsSafeJson(uri))
                return 0;
#endif
            Client *client = new Client(socket, _this->m_Simulation);
#ifdef RIVET_PRODUCTION_BUILD
            client->m_Token = std::string(uri);
            char const *rivetToken = getenv("RIVET_LOBBY_TOKEN");
            assert(rivetToken);
            std::cout << "player connected " << client->m_Token << '\n';
            PerformHttpRequest([](std::string const &r)
                               { std::cout << r << '\n'; },
                               "https://matchmaker.api.rivet.gg/v1/players/connected",
                               {{"Authorization", std::string("Bearer ") + rivetToken}},
                               "{\"player_token\":\"" + client->m_Token + "\"}",
                               true);
            // curl_slist *list = nullptr;
            // CURL *curl = curl_easy_init();
            // assert(curl);
            // char header[500] = "Authorization: Bearer ";
            // char uri[500];
            // memset(uri, 0, sizeof(uri));
            // lws_hdr_copy(socket, uri, 500, WSI_TOKEN_GET_URI);
            // std::cout << uri << '\n';
            // client->m_Token = std::string(uri).substr(1);
            // std::string body = "{\"player_token\":\"" + client->m_Token + "\"}";
            // list = curl_slist_append(list, strcat(header, rivetToken));
            // assert(curl_easy_setopt(curl, CURLOPT_HTTPHEADER, list) == CURLE_OK);
            // assert(curl_easy_setopt(curl, CURLOPT_POST, 1) == CURLE_OK);
            // assert(curl_easy_setopt(curl, CURLOPT_POSTFIELDS, body.c_str()) == CURLE_OK);
            // assert(curl_easy_setopt(curl, CURLOPT_URL, "https://matchmaker.api.rivet.gg/v1/players/connected") == CURLE_OK);
            // assert(curl_easy_perform(curl) == CURLE_OK);
            // curl_easy_cleanup(curl);
            // curl_slist_free_all(list);
#endif

            _this->m_Clients.push_back(client);
            break;
        }
        case LWS_CALLBACK_RECEIVE:
            std::cout << "client recieve packet\n";
            break;
        case LWS_CALLBACK_CLOSED:
        {
            std::lock_guard<std::mutex> l(_this->m_Mutex);
#ifdef RIVET_PRODUCTION_BUILD
            // char const *rivetToken = getenv("RIVET_LOBBY_TOKEN");
            // std::cout << "player disconnected " << rivetToken << '\n';
            // curl_slist *list = nullptr;
            // CURL *curl = curl_easy_init();
            // assert(curl);
            // char header[500] = "Authorization: Bearer ";
            // std::string body = "{\"player_token\":\"" + client->m_Token + "\"}";
            // list = curl_slist_append(list, strcat(header, rivetToken));
            // assert(curl_easy_setopt(curl, CURLOPT_HTTPHEADER, list) == CURLE_OK);
            // assert(curl_easy_setopt(curl, CURLOPT_POST, 1) == CURLE_OK);
            // assert(curl_easy_setopt(curl, CURLOPT_POSTFIELDS, body.c_str()) == CURLE_OK);
            // assert(curl_easy_setopt(curl, CURLOPT_URL, "https://matchmaker.api.rivet.gg/v1/players/disconnected") == CURLE_OK);
            // assert(curl_easy_perform(curl) == CURLE_OK);
            // curl_easy_cleanup(curl);
            // curl_slist_free_all(list);
#endif
            break;
        }
        default:
            break;
        }

        return 0;
    }
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
