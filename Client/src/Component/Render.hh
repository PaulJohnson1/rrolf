#pragma once

#include <cstdint>

#include <Entity.hh>

namespace bc
{
    class BinaryCoder;
}

namespace app::component
{
    class Render
    {
    public:
        Entity m_Parent;

        uint32_t m_Color;

        Render(Entity);

        void UpdateFromBinary(bc::BinaryCoder &);
    };
}
