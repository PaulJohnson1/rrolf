#pragma once

#include <mutex>
#ifdef RIVET_PRODUCTION_BUILD
#include <string>
#endif

#include <libwebsockets.h>

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
        Vector m_PlayerAcceleration{0, 0};

    public:
        Entity m_PlayerInfo;
        lws *m_Socket;
#ifdef RIVET_PRODUCTION_BUILD
        std::string m_Token;
#endif

        Client(lws *, Simulation &);
        ~Client();

        void ConstructPlayer();
        void BroadcastUpdate();
        void Tick();
        void SendPacket(bc::BinaryCoder coder) const;
        void ReadPacket(uint8_t *data, size_t);
    };
}
