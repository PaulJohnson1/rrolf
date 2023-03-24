#pragma once

namespace app
{
    class Simulation;
}

namespace app::system
{
    class Interpolation
    {
    public:
        Simulation &m_Simulation;

        Interpolation(Simulation &);

        void Tick();
        void PostTick();
    };
}
