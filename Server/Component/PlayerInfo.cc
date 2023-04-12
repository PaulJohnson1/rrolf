#include <Server/Component/PlayerInfo.hh>

#include <cstdint>

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
    }

    void PlayerInfo::Write(bc::BinaryCoder &coder, Type const &entity, bool isCreation)
    {
        uint32_t state = isCreation ? 0b11111 : entity.m_State;
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
        
        coder.Write<bc::VarUint>(entity.m_PetalSlots.size());
        for (uint64_t i = 0; i < entity.m_PetalSlots.size(); ++i)
        {
            coder.Write<bc::VarUint>(entity.m_PetalSlots[i].m_Data.m_Id);
            coder.Write<bc::VarUint>(entity.m_PetalSlots[i].m_Rarity);
        }
    }

    float PlayerInfo::Fov() const { return m_Fov; }
    float PlayerInfo::CameraX() const { return m_CameraX; }
    float PlayerInfo::CameraY() const { return m_CameraY; }
    bool PlayerInfo::HasPlayer() const { return m_HasPlayer; }
    Entity PlayerInfo::Player() const { return m_Player; }

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
}
