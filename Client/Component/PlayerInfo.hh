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
        };
        Lerp<float> m_CameraX{0};
        Lerp<float> m_CameraY{0};
        Lerp<float> m_Fov{0.1};
        bool m_HasPlayer;
        LoadoutPetal m_Petals[10] = {};
        LoadoutPetal m_SecondaryPetals[10] = {};
        uint32_t m_Inventory[PetalId::kMaxPetals * RarityId::kMaxRarities] = {};
        Entity m_Player;
        Simulation *m_Simulation;

        Entity m_Parent;

        PlayerInfo(Entity, Simulation *);

        void UpdateFromBinary(bc::BinaryCoder &);
    };
}
