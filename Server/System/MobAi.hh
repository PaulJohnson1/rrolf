#pragma once

#include <Shared/Entity.hh>

namespace app
{
    class Simulation;
}

namespace app::system
{
    class MobAi
    {
        void TickIdle(Entity);
    public:
        Simulation &m_Simulation;
        Entity m_Target;
          
        MobAi(Simulation &);

        void Tick();
        void PostTick();
    };
}
