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
    class Projectile
    {
        Simulation *m_Simulation;

    public:
        using Type = Projectile;

        Entity m_Parent;
        uint64_t m_State = 0;

        uint32_t m_TicksUntilDeath;
        bool m_Detached;

        Projectile(Entity, Simulation *);

        void Reset();

        static void Write(bc::BinaryCoder &, Type const &, bool);
    };
}