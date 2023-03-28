#pragma once

#include <cstdint>

#include <Shared/Entity.hh>

namespace bc
{
    class BinaryCoder;
}

namespace app::component
{
    class Mob
    {
        uint8_t m_Id;
        uint8_t m_Rarity;

    public:
        class BabyAnt
        {
        public:
        
        };

        using Type = Mob;
        
        Entity m_Parent;
        uint64_t m_State = 0;

        Mob(Entity);

        uint8_t Id() const;
        void Id(uint8_t);
        uint8_t Rarity() const;
        void Rarity(uint8_t);

        void Reset();

        static void Write(bc::BinaryCoder &, Type, bool isCreation);
    };
}