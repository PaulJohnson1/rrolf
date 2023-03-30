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
}

namespace app::component
{
    class Life
    {
        float m_Health = 1.0f;
        float m_MaxHealth = 1.0f;
        Simulation *m_Simulation;

    public:
        using Type = Life;

        float m_Damage = 0.0f;
        
        Entity m_Parent;
        uint64_t m_State = 0;

        Life(Entity, Simulation *);
        ~Life();

        float Health() const;
        float MaxHealth() const;
        void Health(float);
        void MaxHealth(float);

        void Reset();

        // clone becuase the struct is small
        static void Write(bc::BinaryCoder &, Life, bool isCreation);
    };
}