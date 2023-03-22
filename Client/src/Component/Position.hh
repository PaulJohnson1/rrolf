#pragma once

#include <cstdint>

#include <Entity.hh>

namespace bc
{
    class BinaryCoder;
}

namespace app::component
{
    class Position
    {
    public:
        Entity m_Parent;
        float m_X = 0;
        float m_Y = 0;
        float m_Angle = 0;
        float m_XDestination = 0;
        float m_YDestination = 0;

        Position(Entity);

        void UpdateFromBinary(bc::BinaryCoder &);
    };
}
