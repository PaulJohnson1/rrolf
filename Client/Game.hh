#pragma once

#include <Renderer.hh>

namespace app
{
    class Game
    {
    public:
        class Simulation *m_Simulation;
        class Socket *m_Socket;
        Renderer m_Renderer;

        Game();
        ~Game();

        Game(Game const &) = delete;
        Game(Game &&) = delete;
        Game &operator=(Game const &) = delete;
        Game &operator=(Game &&) = delete;
    };
}