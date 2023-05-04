#pragma once

#include <cstdint>

#include <Shared/Entity.hh>

namespace bc
{
    class BinaryCoder;
}

namespace app
{
    class Simulation;
    class Renderer;
}

namespace app::component
{
    class Petal
    {
    public:
        uint32_t m_Id;
        uint32_t m_Rarity;
        float m_RandomRotation;
        Simulation *m_Simulation;

        Entity m_Parent;

        Petal(Entity, Simulation *);

        void UpdateFromBinary(bc::BinaryCoder &);
        void Render(Renderer *);
    };
}
