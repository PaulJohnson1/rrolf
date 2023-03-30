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
    class Basic
    {
    public:
        Entity m_Team;
        uint32_t m_Flags = 0;
        Simulation *m_Simulation;

        Entity m_Parent;

        Basic(Entity, Simulation *);

        void UpdateFromBinary(bc::BinaryCoder &);
    };
}
