#pragma once

namespace app
{
    class Simulation;
}

namespace app::system
{
    class Petal
    {
    public:
        Simulation &m_Simulation;
        
        Petal(Simulation &);

        void Tick();
        void PostTick();
    };
}
