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
    class ArenaInfo
    {
        float m_MapSize = 1650.0f;
        Simulation *m_Simulation;

        uint32_t m_Wave = 0;
        uint32_t m_MobCount[MobId::kMaxMobs][RarityId::kMaxRarities] = {};

    public:
        using Type = ArenaInfo;
        
        Entity m_Parent;
        uint32_t m_TotalMobCount = 0;
        uint64_t m_State = 0;

        ArenaInfo(Entity, Simulation *);
        ~ArenaInfo();

        float MapSize() const;
        uint32_t Wave() const;
        uint32_t MobCount(uint32_t, uint32_t) const;
        void MapSize(float);
        void Wave(uint32_t);
        void IncrWave();

        void IncrMobCount(uint32_t, uint32_t);
        void DecrMobCount(uint32_t, uint32_t);

        void Reset();

        static void Write(bc::BinaryCoder &, Type const &, bool);
    };
}