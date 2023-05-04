#pragma once

#include <Shared/Entity.hh>

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

        void MissileTarget(Entity);
        void ProjectileDetach(Entity);
    };
}
