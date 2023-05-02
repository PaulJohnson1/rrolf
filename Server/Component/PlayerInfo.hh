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
            PetalData &m_Data;
            std::vector<Petal> m_Petals;

            PetalSlot(uint32_t r, PetalData &d, std::vector<Petal> p)
                : m_Rarity(r),
                  m_Data(d),
                  m_Petals(p)
            {
            }

            PetalSlot(PetalSlot const &o)
                : m_Rarity(o.m_Rarity),
                  m_Data(o.m_Data),
                  m_Petals(o.m_Petals)
            {
            }
            PetalSlot(PetalSlot &&o)
                : m_Rarity(o.m_Rarity),
                  m_Data(o.m_Data),
                  m_Petals(o.m_Petals)
            {
            }
            PetalSlot &operator=(PetalSlot const &o)
            {
                m_Rarity = o.m_Rarity;
                m_Data = o.m_Data;
                m_Petals = o.m_Petals;

                return *this;
            }
            PetalSlot &operator=(PetalSlot &&o)
            {
                m_Rarity = o.m_Rarity;
                m_Data = o.m_Data;
                m_Petals = o.m_Petals;

                return *this;
            }
        };

        static PetalSlot MakePetal(uint32_t id, uint32_t rarity)
        {
            return PetalSlot{rarity,
                             PETAL_DATA[id],
                             {PETAL_DATA[id].m_Count[rarity], Petal{PETAL_DATA[id].m_ReloadTicks, true}}};
        };
        void ChangePetal(uint32_t pos, uint32_t id, uint32_t rarity)
        {
            PetalSlot &toChange = pos < 10 ? m_PetalSlots[pos] : m_SecondarySlots[pos - 10];
            toChange.m_Rarity = rarity;
            toChange.m_Petals.clear();
            for (uint64_t i = 0; i < PETAL_DATA[id].m_Count[rarity]; ++i)
                toChange.m_Petals.push_back(Petal{PETAL_DATA[id].m_ReloadTicks});
            // toChange.m_Petals = {PETAL_DATA[id].m_Count[rarity], Petal{PETAL_DATA[id].m_ReloadTicks}};
            toChange.m_Data = PETAL_DATA[id]; // MIGHT HAVE A MEM LEAK HERE
        };

        using Type = PlayerInfo;

        Entity m_Parent;
        float m_GlobalRotation = 0.0f;
        uint32_t m_RotationCount = 0;
        uint64_t m_State = 0;
        uint8_t m_MouseButton = 0;
        uint32_t m_SlotCount = 7;
        PetalSlot m_PetalSlots[10] = {
            MakePetal(PetalId::Pollen, RarityId::Ultra),
            MakePetal(PetalId::Missile, RarityId::Mythic),
            MakePetal(PetalId::Stinger, RarityId::Legendary),
            MakePetal(PetalId::Stinger, RarityId::Mythic),
            MakePetal(PetalId::Stinger, RarityId::Common),
            MakePetal(PetalId::Light, RarityId::Epic),
            MakePetal(PetalId::Basic, RarityId::Rare),
            MakePetal(PetalId::None, RarityId::kMaxRarities),
            MakePetal(PetalId::None, RarityId::kMaxRarities),
            MakePetal(PetalId::None, RarityId::kMaxRarities),
        };
        PetalSlot m_SecondarySlots[10] = {
            MakePetal(PetalId::Stinger, RarityId::Ultra),
            MakePetal(PetalId::None, RarityId::kMaxRarities),
            MakePetal(PetalId::None, RarityId::kMaxRarities),
            MakePetal(PetalId::None, RarityId::kMaxRarities),
            MakePetal(PetalId::None, RarityId::kMaxRarities),
            MakePetal(PetalId::None, RarityId::kMaxRarities),
            MakePetal(PetalId::None, RarityId::kMaxRarities),
            MakePetal(PetalId::None, RarityId::kMaxRarities),
            MakePetal(PetalId::None, RarityId::kMaxRarities),
            MakePetal(PetalId::None, RarityId::kMaxRarities),
        };
        uint32_t m_Inventory[PetalId::kMaxPetals * RarityId::kMaxRarities] = {};
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