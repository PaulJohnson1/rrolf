#pragma once

#include <vector>

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
    class PlayerInfo
    {
        bool m_HasPlayer;
        Entity m_Player = (Entity)-1;
        float m_Fov = 0.9f;
        float m_CameraX = 0.0f;
        float m_CameraY = 0.0f;
        Simulation *m_Simulation;

    public:
        struct Petal
        {
            int32_t m_TicksUntilRespawn;
            bool m_IsDead = true;
            Entity m_SimulationId = 0; // m_Id is ambiguous with petal data id
        };

        struct PetalSlot
        {
            uint32_t m_Rarity;
            std::vector<Petal> m_Petals;
            PetalData m_Data;
        };

        using Type = PlayerInfo;

        Entity m_Parent;
        float m_GlobalRotation = 0.0f;
        uint32_t m_RotationCount = 0;
        uint64_t m_State = 0;
        uint8_t m_MouseButton = 0;
        std::vector<PetalSlot> m_PetalSlots{
            PetalSlot{0,
                      {PETAL_DATA[PetalId::Basic].m_Count[0], Petal{PETAL_DATA[PetalId::Basic].m_ReloadTicks}},
                      PETAL_DATA[PetalId::Basic]},
            PetalSlot{0,
                      {PETAL_DATA[PetalId::Basic].m_Count[0], Petal{PETAL_DATA[PetalId::Basic].m_ReloadTicks}},
                      PETAL_DATA[PetalId::Basic]},
            PetalSlot{0,
                      {PETAL_DATA[PetalId::Basic].m_Count[0], Petal{PETAL_DATA[PetalId::Basic].m_ReloadTicks}},
                      PETAL_DATA[PetalId::Basic]},
            PetalSlot{0,
                      {PETAL_DATA[PetalId::Basic].m_Count[0], Petal{PETAL_DATA[PetalId::Basic].m_ReloadTicks}},
                      PETAL_DATA[PetalId::Basic]},
            PetalSlot{0,
                      {PETAL_DATA[PetalId::Basic].m_Count[0], Petal{PETAL_DATA[PetalId::Basic].m_ReloadTicks}},
                      PETAL_DATA[PetalId::Basic]},
            PetalSlot{0,
                      {PETAL_DATA[PetalId::Basic].m_Count[0], Petal{PETAL_DATA[PetalId::Basic].m_ReloadTicks}},
                      PETAL_DATA[PetalId::Basic]},
            PetalSlot{0,
                      {PETAL_DATA[PetalId::Basic].m_Count[0], Petal{PETAL_DATA[PetalId::Basic].m_ReloadTicks}},
                      PETAL_DATA[PetalId::Basic]},
            PetalSlot{0,
                      {PETAL_DATA[PetalId::Basic].m_Count[0], Petal{PETAL_DATA[PetalId::Basic].m_ReloadTicks}},
                      PETAL_DATA[PetalId::Basic]},
            PetalSlot{
                0,
                {PETAL_DATA[PetalId::Basic].m_Count[0], Petal{PETAL_DATA[PetalId::Basic].m_ReloadTicks}},
                PETAL_DATA[PetalId::Basic]}};
        std::vector<Entity> m_EntitiesInView;

        PlayerInfo(Entity, Simulation *);
        ~PlayerInfo();

        float Fov() const;
        float CameraX() const;
        float CameraY() const;
        bool HasPlayer() const;
        Entity Player() const;
        void Fov(float);
        void CameraX(float);
        void CameraY(float);
        void HasPlayer(bool);
        void Player(Entity);

        void Reset();

        static void Write(bc::BinaryCoder &, Type const &, bool);
    };
}