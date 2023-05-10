#include <Server/Component/PlayerInfo.hh>

#include <iostream>

#include <BinaryCoder/BinaryCoder.hh>
#include <BinaryCoder/NativeTypes.hh>

#include <Server/Simulation.hh>

namespace app::component
{
    PlayerInfo::PlayerInfo(Entity parent, Simulation *simulation)
        : m_Parent(parent),
          m_Simulation(simulation)
    {
    }

    PlayerInfo::~PlayerInfo()
    {
    }

    void PlayerInfo::Reset()
    {
        m_State = 0;
        for (uint64_t i = 0; i < m_SlotCount; ++i)
        {
            m_PetalSlots[i].Reset();
            m_SecondarySlots[i].Reset();
        }
    }

    void PlayerInfo::Write(bc::BinaryCoder &coder, Type const &entity, bool isCreation)
    {
        uint64_t state = isCreation ? 0b1111111 : entity.m_State;
        coder.Write<bc::VarUint>(state);

        if (state & 1)
            coder.Write<bc::Float32>(entity.m_Fov);
        if (state & 2)
            coder.Write<bc::Float32>(entity.m_CameraX);
        if (state & 4)
            coder.Write<bc::Float32>(entity.m_CameraY);
        if (state & 8)
            coder.Write<bc::Uint8>(entity.m_HasPlayer);
        if (state & 16)
            coder.Write<bc::VarUint>(entity.m_Player);
        if (state & 32)
            coder.Write<bc::VarUint>(entity.m_SlotCount);
        if (state & 64)
        {
            for (uint64_t i = 0; i < entity.m_SlotCount; ++i)
                coder.Write<PetalSlot>(entity.m_PetalSlots[i], isCreation);
            for (uint64_t i = 0; i < entity.m_SlotCount; ++i)
                coder.Write<PetalSlot>(entity.m_SecondarySlots[i], isCreation);
        }
        for (uint64_t i = 0; i < PetalId::kMaxPetals * RarityId::kMaxRarities; ++i)
            coder.Write<bc::VarUint>(entity.m_Inventory[i]);
    }

    float PlayerInfo::Fov() const { return m_Fov; }
    float PlayerInfo::CameraX() const { return m_CameraX; }
    float PlayerInfo::CameraY() const { return m_CameraY; }
    bool PlayerInfo::HasPlayer() const { return m_HasPlayer; }
    Entity PlayerInfo::Player() const { return m_Player; }
    uint32_t PlayerInfo::SlotCount() const { return m_SlotCount; }

    void PlayerInfo::Fov(float v)
    {
        if (v == m_Fov)
            return;
        m_Fov = v;
        m_State |= 1;
    }

    void PlayerInfo::CameraX(float v)
    {
        if (v == m_CameraX)
            return;
        m_CameraX = v;
        m_State |= 2;
    }

    void PlayerInfo::CameraY(float v)
    {
        if (v == m_CameraY)
            return;
        m_CameraY = v;
        m_State |= 4;
    }

    void PlayerInfo::HasPlayer(bool v)
    {
        if (v == m_HasPlayer)
            return;
        m_HasPlayer = v;
        m_State |= 8;
    }

    void PlayerInfo::Player(Entity v)
    {
        if (v == m_Player)
            return;
        m_Player = v;
        m_State |= 16;
    }

    void PlayerInfo::SlotCount(uint32_t v)
    {
        if (v == m_SlotCount)
            return;
        if (v > m_SlotCount)
        {
            for (uint64_t i = m_SlotCount; i < v; ++i)
            {
                m_PetalSlots[i].m_State = 15; 
                m_SecondarySlots[i].m_State = 15;
            }
            std::cout << "lol it worked? maybe\n";
        }
        m_SlotCount = v;
        m_State |= 32;
    }

    PetalSlot const &PlayerInfo::PrimaryPetal(uint32_t v) const { return m_PetalSlots[v]; };
    PetalSlot &PlayerInfo::PrimaryPetal(uint32_t v) { return m_PetalSlots[v]; };

    PetalSlot const &PlayerInfo::SecondaryPetal(uint32_t v) const { return m_SecondarySlots[v]; };
    PetalSlot &PlayerInfo::SecondaryPetal(uint32_t v) { return m_SecondarySlots[v]; };

    void PetalSlot::Reset()
    {
        m_State = 0;
    }

    void PetalSlot::Write(bc::BinaryCoder &coder, Type const &entity, bool isCreation)
    {
        uint64_t state = isCreation ? 0b1111 : entity.m_State;
        coder.Write<bc::VarUint>(state);

        if (state & 1)
            coder.Write<bc::VarUint>(entity.m_Id);
        if (state & 2)
            coder.Write<bc::VarUint>(entity.m_Rarity);
        if (state & 4)
            coder.Write<bc::Float32>(entity.m_AverageCooldown);
        if (state & 8)
            coder.Write<bc::Float32>(entity.m_AverageHealth);
    }

    uint32_t PetalSlot::Id() const { return m_Id; }
    uint32_t PetalSlot::Rarity() const { return m_Rarity; }

    void PetalSlot::Id(uint32_t v)
    {
        if (m_Id == v)
            return;
        m_Id = v;
        m_State |= 1;
        m_PlayerInfo->m_State |= 64;
    }

    void PetalSlot::Rarity(uint32_t v)
    {
        if (m_Rarity == v)
            return;
        m_Rarity = v;
        m_State |= 2;
        m_PlayerInfo->m_State |= 64;
    }

    void PetalSlot::Cooldown(float v)
    {
        if (v == m_AverageCooldown)
            return;
        m_AverageCooldown = v;
        m_State |= 4;
        m_PlayerInfo->m_State |= 64;
    }


    void PetalSlot::Health(float v)
    {
        if (v == m_AverageHealth)
            return;
        m_AverageHealth = v;
        m_State |= 8;
        m_PlayerInfo->m_State |= 64;
    }
}
