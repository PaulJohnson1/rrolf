#pragma once

#include <cstdint>
#include <vector>

#include <Shared/Entity.hh>
#include <Shared/StaticData.hh>
#include <Client/Util/Lerp.hh>

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
    class LoadoutPetal
    {
    public:
        uint32_t m_Id = 0;
        uint32_t m_Rarity = 0;
        Lerp<float> m_Cooldown = Lerp<float>(0.0f);
        float m_Health = 0.0f;

        LoadoutPetal() {}

        void UpdateFromBinary(bc::BinaryCoder &);
    };
    class PlayerInfo
    {
    public:
        bool m_HasPlayer;
        Entity m_Player;
        uint32_t m_SlotCount = 0;
        Lerp<float> m_CameraX{0};
        Lerp<float> m_CameraY{0};
        Lerp<float> m_Fov{0.1};
        LoadoutPetal m_Petals[10] = {};
        LoadoutPetal m_SecondaryPetals[10] = {};
        uint32_t m_Inventory[PetalId::kMaxPetals * RarityId::kMaxRarities] = {};
        Simulation *m_Simulation;

        Entity m_Parent;

        PlayerInfo(Entity, Simulation *);

        void UpdateFromBinary(bc::BinaryCoder &);
    };
}
