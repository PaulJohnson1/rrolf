#pragma once

#include <cstdint>

#include <Client/Entity.hh>

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
        uint32_t m_Flags;

        Basic(Entity);

        void UpdateFromBinary(bc::BinaryCoder &);
    };
}
