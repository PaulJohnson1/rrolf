#pragma once

#include <mutex>

#include <websocketpp/server.hpp>

#include <Shared/Entity.hh>
#include <Server/Vector.hh>

namespace bc
{
    class BinaryCoder;
}

namespace app
{
    class Simulation;

    class Client
    {
        Simulation &m_Simulation;
        websocketpp::connection_hdl m_Hdl;
        Vector m_PlayerAcceleration{0, 0};

    public:
        Entity m_PlayerInfo;
        std::mutex m_Mutex;

        Client(websocketpp::connection_hdl, Simulation &);
        ~Client();

        websocketpp::connection_hdl const &GetHdl();

        void ConstructPlayer();
        void BroadcastUpdate();
        void Tick();
        void SendPacket(bc::BinaryCoder coder) const;
        void ReadPacket(uint8_t *data, size_t);
    };
}
