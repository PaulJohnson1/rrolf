#pragma once

#include <cstdint>

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
        Lerp<float> m_CameraX{0};
        Lerp<float> m_CameraY{0};
        Lerp<float> m_Fov{0.1};
        bool m_HasPlayer;
        Entity m_Player;
        Simulation *m_Simulation;

        Entity m_Parent;

        PlayerInfo(Entity, Simulation *);

        void UpdateFromBinary(bc::BinaryCoder &);
    };
}
