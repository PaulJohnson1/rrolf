#pragma once

namespace app
{
    class Simulation;
    class Renderer;
}

namespace app::system
{
    class GameRenderer
    {
    public:
        Simulation &m_Simulation;

        GameRenderer(Simulation &);

        void Tick(app::Renderer *);
        void PostTick();
    };
}
