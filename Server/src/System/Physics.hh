#pragma once

namespace app
{
    class Simulation;
}

namespace app::system
{
    class Physics
    {
        Simulation &m_Simulation;
    public:
        Physics(Simulation &);

        void Tick();
    };
}
