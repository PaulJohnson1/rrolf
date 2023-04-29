#pragma once

#include <vector>

#include <Client/Ui/Element.hh>

namespace app
{
    class Simulation;
    class Renderer;
    namespace ui
    {
        class Text;
        class Button;
    }
}

namespace app::system
{

    class GameRenderer
    {
    public:
        Simulation &m_Simulation;
        Renderer *m_Renderer;

        GameRenderer(Simulation &, Renderer *);

        void Tick();
        void PostTick();
    };
}
