#pragma once

#include <cstdint>
#include <vector>

#include <Shared/Entity.hh>
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
        std::vector<LoadoutPetal> m_Petals = {};
        Entity m_Player;
        Simulation *m_Simulation;

        Entity m_Parent;

        PlayerInfo(Entity, Simulation *);

        void UpdateFromBinary(bc::BinaryCoder &);
    };
}
