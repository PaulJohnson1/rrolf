#pragma once

#include <set>

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
    struct PlayerPetal
    {
        int32_t m_TicksUntilRespawn;
        bool m_IsDead = true;
        Entity m_SimulationId = 0; // m_Id is ambiguous with petal data id
    };
    class PetalSlot
    {
        uint32_t m_Id;
        uint32_t m_Rarity;
        float m_AverageCooldown = 0.0f;
        float m_AverageHealth = 0.0f;
    public:
        using Type = PetalSlot;
        uint64_t m_State = 0;
        std::vector<PlayerPetal> m_Petals;

        PetalSlot(uint32_t i, uint32_t r)
            : m_Id(i),
                m_Rarity(r)
        {
            m_Petals = {PETAL_DATA[i].m_Count[r], PlayerPetal{PETAL_DATA[i].m_ReloadTicks, true}};
        }

        PetalSlot(PetalSlot const &o)
            : m_Id(o.m_Id),
                m_Rarity(o.m_Rarity),
                m_Petals(o.m_Petals)
        {
        }
        PetalSlot(PetalSlot &&o)
            : m_Id(o.m_Id),
                m_Rarity(o.m_Rarity),
                m_Petals(o.m_Petals)
        {
            m_State = 15;
        }
        PetalSlot &operator=(PetalSlot const &o)
        {
            m_Id = o.m_Id;
            m_Rarity = o.m_Rarity;
            m_Petals = o.m_Petals;
            m_State = 15;

            return *this;
        }
        PetalSlot &operator=(PetalSlot &&o)
        {
            m_Id = o.m_Id;
            m_Rarity = o.m_Rarity;
            m_Petals = o.m_Petals;
            m_State = 15;

            return *this;
        }

        uint32_t Id() const;
        void Id(uint32_t);
        uint32_t Rarity() const;
        void Rarity(uint32_t);
        void Cooldown(float);
        void Health(float);

        void Reset();

        static void Write(bc::BinaryCoder &, Type const &, bool);
    };
    class PlayerInfo
    {
        bool m_HasPlayer;
        Entity m_Player = NULL_ENTITY;
        float m_Fov = 0.9f;
        float m_CameraX = 0.0f;
        float m_CameraY = 0.0f;
        Simulation *m_Simulation;
        uint32_t m_SlotCount = 5;

        PetalSlot m_PetalSlots[10] = {
            PetalSlot(PetalId::Basic, RarityId::Common),
            PetalSlot(PetalId::Light, RarityId::Common),
            PetalSlot(PetalId::Stinger, RarityId::Common),
            PetalSlot(PetalId::Missile, RarityId::Common),
            PetalSlot(PetalId::Pollen, RarityId::Common),
            PetalSlot(PetalId::Leaf, RarityId::Ultra),
            PetalSlot(PetalId::Rose, RarityId::Ultra),
            PetalSlot(PetalId::Missile, RarityId::Ultra),
            PetalSlot(PetalId::Missile, RarityId::Ultra),
            PetalSlot(PetalId::Missile, RarityId::Ultra)
        };
        PetalSlot m_SecondarySlots[10] = {
            PetalSlot(PetalId::Stinger, RarityId::Ultra),
            PetalSlot(PetalId::None, RarityId::Common),
            PetalSlot(PetalId::None, RarityId::Common),
            PetalSlot(PetalId::None, RarityId::Common),
            PetalSlot(PetalId::None, RarityId::Common),
            PetalSlot(PetalId::None, RarityId::Common),
            PetalSlot(PetalId::None, RarityId::Common),
            PetalSlot(PetalId::None, RarityId::Common),
            PetalSlot(PetalId::None, RarityId::Common),
            PetalSlot(PetalId::None, RarityId::Common),
        };
    public:


        using Type = PlayerInfo;

        Entity m_Parent;
        float m_GlobalRotation = 0.0f;
        uint32_t m_RotationCount = 0;
        uint64_t m_State = 0;
        uint8_t m_MouseButton = 0;
        uint32_t m_Inventory[PetalId::kMaxPetals * RarityId::kMaxRarities] = {};
        std::set<Entity> m_EntitiesInView;
        std::vector<Entity> m_PendingDropPickups = {};

        PlayerInfo(Entity, Simulation *);
        ~PlayerInfo();

        float Fov() const;
        float CameraX() const;
        float CameraY() const;
        bool HasPlayer() const;
        Entity Player() const;
        uint32_t SlotCount() const;
        void Fov(float);
        void CameraX(float);
        void CameraY(float);
        void HasPlayer(bool);
        void Player(Entity);
        void SlotCount(uint32_t);

        PetalSlot const &PrimaryPetal(uint32_t) const;
        PetalSlot &PrimaryPetal(uint32_t);

        PetalSlot const &SecondaryPetal(uint32_t) const;
        PetalSlot &SecondaryPetal(uint32_t);

        void Reset();

        static void Write(bc::BinaryCoder &, Type const &, bool);
    };
}