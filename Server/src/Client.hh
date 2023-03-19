#pragma once

#include <websocketpp/server.hpp>
#include <Vector.hh>

class Simulation;

class Camera
{
public:
    float m_Fov = 1;
    Vector m_Position{0.0f, 0.0f};
    std::vector<uint16_t> m_EntitiesInView;

    Camera() = default;
};

class Client
{
    Simulation &m_Simulation;
    websocketpp::connection_hdl m_Hdl;

public:
    Camera m_Camera;

    Client(websocketpp::connection_hdl, Simulation &);
    ~Client();

    websocketpp::connection_hdl GetHdl();

    void BroadcastUpdate();
    void Tick();
};
