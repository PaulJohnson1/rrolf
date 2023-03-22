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
        float m_Health = 0.0f;
        float m_MaxHealth = 0.0f;
        float m_Damage = 0.0f;

    public:
        using Type = Life;
        
        Entity m_Parent;
        uint64_t m_State = 0;

        Life(Entity);

        float Health() const;
        float MaxHealth() const;
        float Damage() const;
        void Health(float);
        void MaxHealth(float);
        void Damage(float);

        void operator+=(float);
        void operator-=(float);

        void Reset();

        // clone becuase the struct is small
        static void Write(bc::BinaryCoder &, Life, bool isCreation);
    };
}