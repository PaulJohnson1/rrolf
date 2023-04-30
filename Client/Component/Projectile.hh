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
    public:
        Simulation *m_Simulation;

        Entity m_Parent;

        Projectile(Entity, Simulation *);

        void UpdateFromBinary(bc::BinaryCoder &);
    };
}
