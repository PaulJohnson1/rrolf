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
    class Life
    {
    public:
        Entity m_Parent;

        float m_Health;
        float m_MaxHealth;
        float m_Damage;

        Life(Entity);
        void UpdateFromBinary(bc::BinaryCoder &);
        void Render(Renderer *ctx);
    };
}