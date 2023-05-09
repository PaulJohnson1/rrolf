#pragma once

#include <cstdint>

#include <Shared/Entity.hh>
#include <Client/Renderer.hh>

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
    class Drop
    {
    public:
        uint8_t m_Id = 0;
        uint8_t m_Rarity = 0;
        bool m_PickedUp;
        Simulation *m_Simulation;

        Entity m_Parent;

        Drop(Entity, Simulation *);

        void UpdateFromBinary(bc::BinaryCoder &);
        void Render(Renderer *);
    };
}