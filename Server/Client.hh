#pragma once

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

        Client(websocketpp::connection_hdl, Simulation &);
        ~Client();

        websocketpp::connection_hdl GetHdl();

        void BroadcastUpdate();
        void Tick();
        void SendPacket(bc::BinaryCoder coder) const;
        void ReadPacket(uint8_t *data, size_t);
    };
}
