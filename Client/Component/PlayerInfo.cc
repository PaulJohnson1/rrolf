#include <Client/Component/PlayerInfo.hh>

#include <BinaryCoder/BinaryCoder.hh>
#include <BinaryCoder/NativeTypes.hh>

#include <Client/Simulation.hh>

namespace app::component
{
    PlayerInfo::PlayerInfo(Entity parent, Simulation *simulation)
        : m_Parent(parent),
          m_Simulation(simulation)
    {
        m_Simulation->m_PlayerInfo = parent;
    }

    void PlayerInfo::UpdateFromBinary(bc::BinaryCoder &coder)
    {
        uint32_t updatedFields = coder.Read<bc::VarUint>();

        if (updatedFields & 1)
            m_Fov = coder.Read<bc::Float32>();
        if (updatedFields & 2)
            m_CameraX = coder.Read<bc::Float32>();
        if (updatedFields & 4)
            m_CameraY = coder.Read<bc::Float32>();
        if (updatedFields & 8)
            m_HasPlayer = coder.Read<bc::Uint8>();
        if (updatedFields & 16)
            m_Player = coder.Read<bc::VarUint>();
        if (updatedFields & 32)
            m_SlotCount = coder.Read<bc::VarUint>();
        for (uint64_t i = 0; i < m_SlotCount; ++i)
        {
            m_Petals[i].UpdateFromBinary(coder);
        }
        for (uint64_t i = 0; i < m_SlotCount; ++i)
        {
            m_SecondaryPetals[i].UpdateFromBinary(coder);
        }
        for (uint64_t i = 0; i < PetalId::kMaxPetals * RarityId::kMaxRarities; ++i)
        {
            m_Inventory[i] = coder.Read<bc::VarUint>();
        }
    }

    void LoadoutPetal::UpdateFromBinary(bc::BinaryCoder &coder)
    {
        uint32_t updatedFields = coder.Read<bc::VarUint>();
        if (updatedFields & 1)
            m_Id = coder.Read<bc::VarUint>();
        if (updatedFields & 2)
            m_Rarity = coder.Read<bc::VarUint>();
        if (updatedFields & 4)
        {
            float oldCd = coder.Read<bc::Float32>();
            if ((float) m_Cooldown > oldCd)
                m_Cooldown.SetInterpolated(oldCd);
            m_Cooldown = oldCd;
        }
        if (updatedFields & 8)
            m_Health = coder.Read<bc::Float32>();
    }
}
