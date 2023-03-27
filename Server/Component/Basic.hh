#pragma once

#include <cstdint>

#include <Server/Entity.hh>

namespace bc
{
    class BinaryCoder;
}

namespace app::component
{
    class Basic
    {
        Entity m_Team;
        uint32_t m_Flags;

    public:
        using Type = Basic;
        
        Entity m_Parent;
        uint64_t m_State = 0;

        Basic(Entity);

        Entity Team() const;
        void Team(Entity);
        uint32_t Flags() const;
        void Flags(uint32_t);

        void Reset();

        static void Write(bc::BinaryCoder &, Type, bool isCreation);
    };
}