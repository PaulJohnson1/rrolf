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
    class Petal
    {
        uint32_t m_Id;
        uint32_t m_Rarity;
        Simulation *m_Simulation;

    public:
        using Type = Petal;

        Entity m_Parent;
        uint64_t m_State = 0;

        // for rotation and stuff lol
        uint32_t m_RotationPos = 0;
        float m_InnerAngle = 0; // for clumped petals
        float m_ClumpRadius = 0;

        Petal(Entity, Simulation *);
        ~Petal();

        uint32_t Id() const;
        void Id(uint32_t);
        uint32_t Rarity() const;
        void Rarity(uint32_t);
        bool Shootable() const;
        void Shootable(bool);
        bool Independent() const;
        void Independent(bool);

        void Reset();

        static void Write(bc::BinaryCoder &, Type const &, bool);
    };
}