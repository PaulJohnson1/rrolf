#pragma once

#include <cstdint>

#include <Shared/Entity.hh>

namespace bc
{
    class BinaryCoder;
}
namespace app
{
    class Renderer;
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

        float m_EyeX = 3.0f;
        float m_EyeXDestination = 3.0f;

        float m_EyeY = 0.0f;
        float m_EyeYDestination = 0.0f;

        Flower(Entity);
        void UpdateFromBinary(bc::BinaryCoder &);
        void Render(Renderer *ctx);
    };
}