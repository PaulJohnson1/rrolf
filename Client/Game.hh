#pragma once

#include <Client/System/Interpolation.hh>
#include <Client/System/GameRenderer.hh>

#include <cstdint>
namespace app
{
    class Game;
}
extern app::Game *g_Game;

namespace app
{
    class Game
    {
        system::Interpolation m_InterpolationSystem;
        system::GameRenderer m_RendererSystem;
    public:
        bool m_HasHadPlayer = false;
        float m_LastTick;
        float m_TickTime;
        class Simulation *m_Simulation;
        class Socket *m_Socket;
        class Renderer *m_Renderer;
        class InputData *m_InputData;

        struct GameUi
        {
            class ui::Container *m_TitleScreen;
            class ui::Container *m_DeathScreen;
            class ui::Container *m_Loadout;
            class ui::Container *m_Test;
        };
        GameUi m_UiElements;

        Game(class Renderer *, class Simulation *);
        void ReadBinary(uint8_t *);
        void Tick();

        float GetTime();
    };
}