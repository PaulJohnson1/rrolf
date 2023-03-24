#pragma once

namespace app
{
    class Simulation;
}

namespace app::system
{
    class Velocity
    {
    public:
        Simulation &m_Simulation;
        Velocity(Simulation &);

        void Tick();
        void PostTick();
    };
}
