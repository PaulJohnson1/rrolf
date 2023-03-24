#pragma once

namespace app
{
    class Simulation;
}

namespace app::system
{
    class CollisionResolver
    {
    public:
        Simulation &m_Simulation;
        
        CollisionResolver(Simulation &);

        void Tick();
        void PostTick();
    };
}
