#pragma once

namespace app
{
    class Simulation;
}

namespace app::system
{
    class PetalBehavior
    {
    public:
        Simulation &m_Simulation;
        
        PetalBehavior(Simulation &);

        void Tick();
        void PostTick();
    };
}
