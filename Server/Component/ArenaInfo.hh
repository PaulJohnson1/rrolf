#pragma once

#include <cstdint>

#include <Shared/Entity.hh>

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
    class ArenaInfo
    {
        float m_MapSize = 1650.0f;
        Simulation *m_Simulation;

    public:
        using Type = ArenaInfo;
        
        Entity m_Parent;
        uint64_t m_State = 0;

        ArenaInfo(Entity, Simulation *);
        ~ArenaInfo();

        float MapSize() const;
        void MapSize(float);

        void Reset();

        static void Write(bc::BinaryCoder &, Type const &, bool);
    };
}