#pragma once

namespace app
{
    class Simulation;
}

namespace app::system
{
    class DropCollector
    {
    public:
        Simulation &m_Simulation;
        
        DropCollector(Simulation &);

        void Tick();
        void PostTick();
    };
}
