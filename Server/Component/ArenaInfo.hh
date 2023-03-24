#pragma once

#include <cstdint>

#include <Server/Entity.hh>

namespace bc
{
    class BinaryCoder;
}

namespace app::component
{
    class ArenaInfo
    {
        float m_MapSize = 750.0f;

    public:
        using Type = ArenaInfo;
        
        Entity m_Parent;
        uint64_t m_State = 0;

        ArenaInfo(Entity);

        float MapSize() const;
        void MapSize(float);

        void Reset();

        static void Write(bc::BinaryCoder &, Type, bool isCreation);
    };
}