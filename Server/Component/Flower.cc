#include <Server/Component/Flower.hh>

#include <cstdint>
#include <iostream>

#include <BinaryCoder/BinaryCoder.hh>
#include <BinaryCoder/NativeTypes.hh>

#include <Server/Simulation.hh>
#include <Server/Component/Basic.hh>
#include <Server/Component/PlayerInfo.hh>

namespace app::component
{
    Flower::Flower(Entity parent, Simulation *simulation)
        : m_Parent(parent),
          m_Simulation(simulation)
    {
    }

    Flower::~Flower()
    {
        Basic &basic = m_Simulation->Get<Basic>(m_Parent);
        if (basic.m_Owner != NULL_ENTITY)
        {
            PlayerInfo &playerInfo = m_Simulation->Get<PlayerInfo>(basic.m_Owner);
            playerInfo.HasPlayer(false);
        
            for (uint64_t i = 0; i < playerInfo.m_SlotCount; i++)
            {
                PlayerInfo::PetalSlot &petalSlot = playerInfo.m_PetalSlots[i];
                for (uint64_t j = 0; j < petalSlot.m_Petals.size(); j++)
                    petalSlot.m_Petals[j].m_TicksUntilRespawn = petalSlot.m_Data->m_ReloadTicks;
            }
        }
    }

    void Flower::Reset()
    {
        m_State = 0;
    }

    void Flower::Write(bc::BinaryCoder &coder, Type const &entity, bool isCreation)
    {
        uint32_t state = isCreation ? 0b11 : entity.m_State;
        coder.Write<bc::VarUint>(state);

        if (state & 1)
            coder.Write<bc::Uint8>(entity.m_FaceFlags);
        if (state & 2)
            coder.Write<bc::Float32>(entity.m_EyeAngle);
    }

    uint8_t Flower::FaceFlags() const
    {
        return m_FaceFlags;
    }

    float Flower::EyeAngle() const
    {
        return m_EyeAngle;
    }

    void Flower::FaceFlags(uint8_t v)
    {
        if (v == m_FaceFlags)
            return;
        m_FaceFlags = v;
        m_State |= 1 << 0;
    }

    void Flower::EyeAngle(float v)
    {
        if (v == m_EyeAngle)
            return;
        m_EyeAngle = v;
        m_State |= 1 << 1;
    }
}
