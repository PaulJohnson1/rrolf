#pragma once

namespace app
{
    class Simulation;
}

namespace app::system
{
    class MapBoundaries
    {
    public:
        Simulation &m_Simulation;
        
        MapBoundaries(Simulation &);

        void Tick();
        void PostTick();
    };
}
