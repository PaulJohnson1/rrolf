#pragma once

#include <cstdint>

#include <Shared/Entity.hh>

namespace bc
{
    class BinaryCoder;
}

namespace app
{
    class Simulation;
}

namespace app::component
{
    class Ai
    {
    public:
        Simulation *m_Simulation;

        Entity m_Parent;

        Ai(Entity, Simulation *);

        void UpdateFromBinary(bc::BinaryCoder &);
    };
}
