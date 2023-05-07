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
    class PlayerInfo
    {
    public:
        struct LoadoutPetal
        {
            uint32_t m_Id;
            uint32_t m_Rarity;
            float m_Health;
            Lerp<float> m_Reload = Lerp<float>(0.0f);
        };
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
