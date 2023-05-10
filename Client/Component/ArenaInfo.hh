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
    class Renderer;
    class Simulation;
}

namespace app::component
{
    class ArenaInfo
    {
    public:
        Simulation *m_Simulation;
        float m_MapSize = 1650.0f;
        uint32_t m_MobCount[MobId::kMaxMobs][RarityId::kMaxRarities] = {};
        
        Entity m_Parent;

        ArenaInfo(Entity, Simulation *);

        void UpdateFromBinary(bc::BinaryCoder &);
        void Render(Renderer *);
    };
}
