#pragma once

#include <cstdint>

#include <Entity.hh>

namespace bc
{
    class BinaryCoder;
}

namespace app::component
{
    class Flower
    {
    public:
        enum class m_eFlags : uint8_t
        {
            Attack = 1,
            Defend = 2,
            Poison = 4,
            Dandelion = 8,
            Antennae = 16,
            Cutter = 32
        };


        Entity m_Parent;
        uint8_t m_Flags;
        float m_EyeAngle;

        Flower(Entity);
        void UpdateFromBinary(bc::BinaryCoder &);
    };
}