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
    class Mob
    {
        uint32_t m_Id;
        uint32_t m_Rarity;
        Simulation *m_Simulation;

    public:
        using Type = Mob;
        
        Entity m_Parent;
        uint64_t m_State = 0;

        Mob(Entity, Simulation *);
        ~Mob();

        uint32_t Id() const;
        void Id(uint32_t);
        uint32_t Rarity() const;
        void Rarity(uint32_t);

        void Reset();

        static void Write(bc::BinaryCoder &, Type const &, bool);
    };
}