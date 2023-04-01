#pragma once

#include <vector>
// #include <cstdlib>
#include <cmath>

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
            bool m_IsDead = true;
            Entity m_SimulationId; // m_Id is ambiguous with petal data id
            int32_t m_TicksUntilRespawn;
        };

        struct PetalSlot
        {
            uint32_t m_Count;
            std::vector<Petal> m_Petals;
            PetalData m_Data;
            uint32_t m_Rarity;
            float m_ClumpRotation = M_PI * 2 * rand() / RAND_MAX;
        };

        using Type = PlayerInfo;

        Entity m_Parent;
        float m_GlobalRotation = 0.0f;
        uint32_t m_RotationCount = 0;
        uint64_t m_State = 0;
        std::vector<PetalSlot> m_PetalSlots{
            PetalSlot{1,
                      {Petal{true, 0, PETAL_DATA[PetalId::Basic].m_ReloadTicks},
                       Petal{true, 0, PETAL_DATA[PetalId::Basic].m_ReloadTicks},
                       Petal{true, 0, PETAL_DATA[PetalId::Basic].m_ReloadTicks},
                       Petal{true, 0, PETAL_DATA[PetalId::Basic].m_ReloadTicks},
                       Petal{true, 0, PETAL_DATA[PetalId::Basic].m_ReloadTicks}},
                      PETAL_DATA[PetalId::Basic],
                      0},
            PetalSlot{1,
                      {Petal{true, 0, PETAL_DATA[PetalId::Basic].m_ReloadTicks},
                       Petal{true, 0, PETAL_DATA[PetalId::Basic].m_ReloadTicks},
                       Petal{true, 0, PETAL_DATA[PetalId::Basic].m_ReloadTicks},
                       Petal{true, 0, PETAL_DATA[PetalId::Basic].m_ReloadTicks},
                       Petal{true, 0, PETAL_DATA[PetalId::Basic].m_ReloadTicks}},
                      PETAL_DATA[PetalId::Basic],
                      0},
            PetalSlot{1,
                      {Petal{true, 0, PETAL_DATA[PetalId::Basic].m_ReloadTicks},
                       Petal{true, 0, PETAL_DATA[PetalId::Basic].m_ReloadTicks},
                       Petal{true, 0, PETAL_DATA[PetalId::Basic].m_ReloadTicks},
                       Petal{true, 0, PETAL_DATA[PetalId::Basic].m_ReloadTicks},
                       Petal{true, 0, PETAL_DATA[PetalId::Basic].m_ReloadTicks}},
                      PETAL_DATA[PetalId::Basic],
                      0},
            PetalSlot{1,
                      {Petal{true, 0, PETAL_DATA[PetalId::Basic].m_ReloadTicks},
                       Petal{true, 0, PETAL_DATA[PetalId::Basic].m_ReloadTicks},
                       Petal{true, 0, PETAL_DATA[PetalId::Basic].m_ReloadTicks},
                       Petal{true, 0, PETAL_DATA[PetalId::Basic].m_ReloadTicks},
                       Petal{true, 0, PETAL_DATA[PetalId::Basic].m_ReloadTicks}},
                      PETAL_DATA[PetalId::Basic],
                      0},
            PetalSlot{1,
                      {Petal{true, 0, PETAL_DATA[PetalId::Basic].m_ReloadTicks},
                       Petal{true, 0, PETAL_DATA[PetalId::Basic].m_ReloadTicks},
                       Petal{true, 0, PETAL_DATA[PetalId::Basic].m_ReloadTicks},
                       Petal{true, 0, PETAL_DATA[PetalId::Basic].m_ReloadTicks},
                       Petal{true, 0, PETAL_DATA[PetalId::Basic].m_ReloadTicks}},
                      PETAL_DATA[PetalId::Basic],
                      0},
            PetalSlot{1,
                      {Petal{true, 0, PETAL_DATA[PetalId::Basic].m_ReloadTicks},
                       Petal{true, 0, PETAL_DATA[PetalId::Basic].m_ReloadTicks},
                       Petal{true, 0, PETAL_DATA[PetalId::Basic].m_ReloadTicks},
                       Petal{true, 0, PETAL_DATA[PetalId::Basic].m_ReloadTicks},
                       Petal{true, 0, PETAL_DATA[PetalId::Basic].m_ReloadTicks}},
                      PETAL_DATA[PetalId::Basic],
                      0},
            PetalSlot{1,
                      {Petal{true, 0, PETAL_DATA[PetalId::Basic].m_ReloadTicks},
                       Petal{true, 0, PETAL_DATA[PetalId::Basic].m_ReloadTicks},
                       Petal{true, 0, PETAL_DATA[PetalId::Basic].m_ReloadTicks},
                       Petal{true, 0, PETAL_DATA[PetalId::Basic].m_ReloadTicks},
                       Petal{true, 0, PETAL_DATA[PetalId::Basic].m_ReloadTicks}},
                      PETAL_DATA[PetalId::Basic],
                      0},
            PetalSlot{1,
                      {Petal{true, 0, PETAL_DATA[PetalId::Basic].m_ReloadTicks},
                       Petal{true, 0, PETAL_DATA[PetalId::Basic].m_ReloadTicks},
                       Petal{true, 0, PETAL_DATA[PetalId::Basic].m_ReloadTicks},
                       Petal{true, 0, PETAL_DATA[PetalId::Basic].m_ReloadTicks},
                       Petal{true, 0, PETAL_DATA[PetalId::Basic].m_ReloadTicks}},
                      PETAL_DATA[PetalId::Basic],
                      0},
            PetalSlot{1,
                      {Petal{true, 0, PETAL_DATA[PetalId::Basic].m_ReloadTicks},
                       Petal{true, 0, PETAL_DATA[PetalId::Basic].m_ReloadTicks},
                       Petal{true, 0, PETAL_DATA[PetalId::Basic].m_ReloadTicks},
                       Petal{true, 0, PETAL_DATA[PetalId::Basic].m_ReloadTicks},
                       Petal{true, 0, PETAL_DATA[PetalId::Basic].m_ReloadTicks}},
                      PETAL_DATA[PetalId::Basic],
                      0},
            PetalSlot{1,
                      {Petal{true, 0, PETAL_DATA[PetalId::Basic].m_ReloadTicks},
                       Petal{true, 0, PETAL_DATA[PetalId::Basic].m_ReloadTicks},
                       Petal{true, 0, PETAL_DATA[PetalId::Basic].m_ReloadTicks},
                       Petal{true, 0, PETAL_DATA[PetalId::Basic].m_ReloadTicks},
                       Petal{true, 0, PETAL_DATA[PetalId::Basic].m_ReloadTicks}},
                      PETAL_DATA[PetalId::Basic],
                      0},
        };
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