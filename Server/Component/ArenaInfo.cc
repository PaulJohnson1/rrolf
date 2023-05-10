#include <Server/Component/ArenaInfo.hh>

#include <cstdint>

#include <BinaryCoder/BinaryCoder.hh>
#include <BinaryCoder/NativeTypes.hh>

#include <Server/Simulation.hh>

namespace app::component
{
    ArenaInfo::ArenaInfo(Entity parent, Simulation *simulation)
        : m_Parent(parent),
          m_Simulation(simulation)
    {
    }

    ArenaInfo::~ArenaInfo()
    {
    }

    void ArenaInfo::Reset()
    {
        m_State = 0;
    }

    void ArenaInfo::Write(bc::BinaryCoder &coder, Type const &entity, bool isCreation)
    {
        uint32_t state = isCreation ? 0b11 : entity.m_State;
        coder.Write<bc::VarUint>(state);

        if (state & 1)
            coder.Write<bc::VarUint>(entity.m_MapSize);
        if (state & 2)
            for (uint32_t id = 0; id < MobId::kMaxMobs; ++id)
                for (uint32_t rar = 0; rar < RarityId::kMaxRarities; ++rar)
                    coder.Write<bc::VarUint>(entity.m_MobCount[id][rar]);
    }

    float ArenaInfo::MapSize() const
    {
        return m_MapSize;
    }

    void ArenaInfo::MapSize(float v)
    {
        if (v == m_MapSize)
            return;
        m_MapSize = v;
        m_State |= 1;
    }

    uint32_t ArenaInfo::MobCount(uint32_t id, uint32_t rarity) const 
    {
        return m_MobCount[id][rarity];
    }

    void ArenaInfo::IncrMobCount(uint32_t id, uint32_t rarity) 
    {
        ++m_MobCount[id][rarity];
        m_State |= 2;
    }

    void ArenaInfo::DecrMobCount(uint32_t id, uint32_t rarity) 
    {
        --m_MobCount[id][rarity];
        m_State |= 2;
    }
}
