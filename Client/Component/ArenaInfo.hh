#pragma once

#include <cstdint>

#include <Client/Entity.hh>

namespace bc
{
    class BinaryCoder;
}

namespace app::component
{
    class ArenaInfo
    {
    public:

        Entity m_Parent;
        float m_MapSize = 500.0f;
        uint32_t m_Color;

        ArenaInfo(Entity);

        void UpdateFromBinary(bc::BinaryCoder &);
    };
}
