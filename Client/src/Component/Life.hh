#pragma once

#include <cstdint>

#include <Entity.hh>

namespace bc
{
    class BinaryCoder;
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
    };
}