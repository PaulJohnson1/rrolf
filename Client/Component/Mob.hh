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
    class Mob
    {
    public:
        Entity m_Parent;

        uint8_t m_Id;
        uint8_t m_Rarity;

        Mob(Entity);

        void UpdateFromBinary(bc::BinaryCoder &);
        void Render(Renderer *ctx);
    };
}