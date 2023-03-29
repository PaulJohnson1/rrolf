#pragma once

#include <cstdint>

#include <Shared/Entity.hh>

namespace bc
{
    class BinaryCoder;
}

namespace app::component
{
    class Ai
    {
    public:
        Entity m_Parent;

        Ai(Entity);

        void UpdateFromBinary(bc::BinaryCoder &);
    };
}
