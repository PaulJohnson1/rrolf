#pragma once

#include <cstdint>

#include <Shared/Entity.hh>

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

        uint32_t m_Color = 0;
        uint32_t m_AnimationTick = 0;

        Render(Entity);

        void UpdateFromBinary(bc::BinaryCoder &);
    };
}
