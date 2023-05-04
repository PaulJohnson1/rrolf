#pragma once

#include <cstdint>

#include <Shared/Entity.hh>
#include <Shared/StaticData.hh>

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
    class Heal
    {
        Simulation *m_Simulation;

    public:
        using Type = Heal;
        
        Entity m_Parent;
        float m_HealAmount;
        Entity m_Target;
        bool m_Idle;
        uint64_t m_State = 0;

        Heal(Entity, Simulation *);
        ~Heal();

        void Reset();

        static void Write(bc::BinaryCoder &, Type const &, bool);
    };
}