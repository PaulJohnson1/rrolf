#pragma once

#include <cstdint>

#include <Entity.hh>

namespace bc
{
    class BinaryCoder;
}

namespace app::component
{
    class Physics
    {
    public:
        Entity m_Parent;

        float m_Radius;

        Physics(Entity);

        void UpdateFromBinary(bc::BinaryCoder &);
    };
}
