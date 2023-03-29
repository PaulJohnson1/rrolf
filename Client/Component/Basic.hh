#pragma once

#include <cstdint>

#include <Shared/Entity.hh>

namespace bc
{
    class BinaryCoder;
}

namespace app::component
{
    class Basic
    {
    public:
        Entity m_Parent;

        Entity m_Team;
        uint32_t m_Flags = 0;

        Basic(Entity);

        void UpdateFromBinary(bc::BinaryCoder &);
    };
}
