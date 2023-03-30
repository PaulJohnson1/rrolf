#pragma once

#include <cstdint>

#include <Shared/Entity.hh>
#include <Client/Util/Lerp.hh>

namespace bc
{
    class BinaryCoder;
}

namespace app
{
    class Renderer;
    class Simulation;
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

        uint8_t m_Flags = 0;
        float m_EyeAngle = 0;
        Lerp<float> m_EyeX = Lerp<float>(3.0f);
        Lerp<float> m_EyeY = Lerp<float>(0.0f);
        Simulation *m_Simulation;

        Entity m_Parent;

        Flower(Entity, Simulation *);
        void UpdateFromBinary(bc::BinaryCoder &);
        void Render(Renderer *ctx);
    };
}