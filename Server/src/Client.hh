#pragma once

#include <optional>

#include <websocketpp/server.hpp>

#include <Entity.hh>
#include <Vector.hh>

namespace bc
{
    class BinaryCoder;
}

namespace app
{
    class Simulation;

    class Camera
    {
    public:
        float m_Fov = 1;
        float m_X = 0;
        float m_Y = 0;
        std::vector<Entity> m_EntitiesInView;

        Camera() = default;
    };

    class Client
    {
        Simulation &m_Simulation;
        websocketpp::connection_hdl m_Hdl;

    public:
        std::optional<Entity> m_Player;
        Camera m_Camera;

        Client(websocketpp::connection_hdl, Simulation &);
        ~Client();

        websocketpp::connection_hdl GetHdl();

        void BroadcastUpdate();
        void Tick();
        void SendPacket(bc::BinaryCoder const &coder) const;
    };
}
