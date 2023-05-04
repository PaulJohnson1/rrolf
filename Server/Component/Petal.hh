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
        bool m_Detached = false;
        uint32_t m_RotationPos = 0;
        uint32_t m_Slot = 0;
        uint32_t m_InnerPos = 0;
        float m_ClumpRadius = 0;
        float m_InnerAngle = 0;
        uint64_t m_State = 0;

        Petal(Entity, Simulation *);
        ~Petal();

        uint32_t Id() const;
        void Id(uint32_t);
        uint32_t Rarity() const;
        void Rarity(uint32_t);

        void Reset();

        static void Write(bc::BinaryCoder &, Type const &, bool);
    };
}