#pragma once

namespace app
{
    class Simulation;
}

namespace app::system
{
    class Damage
    {
    public:
        Simulation &m_Simulation;
        
        Damage(Simulation &);

        void Tick();
        void PostTick();
    };
}
