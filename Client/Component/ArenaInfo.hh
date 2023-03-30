#pragma once

#include <cstdint>

#include <Shared/Entity.hh>

namespace bc
{
    class BinaryCoder;
}

namespace app
{
    class Renderer;
    class Simulation;
}

namespace app::component
{
    class ArenaInfo
    {
    public:
        Simulation *m_Simulation;
        float m_MapSize = 1650.0f;
        uint32_t m_Color = 0;
        
        Entity m_Parent;

        ArenaInfo(Entity, Simulation *);

        void UpdateFromBinary(bc::BinaryCoder &);
        void Render(Renderer *ctx);
    };
}
