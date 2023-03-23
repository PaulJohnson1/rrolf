#pragma once

namespace app
{
    class Simulation;
    class Renderer;
}

namespace app::system
{
    class Renderer
    {
    public:
        Simulation &m_Simulation;

        Renderer(Simulation &);

        void Tick(app::Renderer *);
        void PostTick();
    };
}
