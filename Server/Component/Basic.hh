#pragma once

#include <cstdint>
#include <optional>

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
    class Basic
    {
        Entity m_Team;
        uint32_t m_Flags;
        Simulation *m_Simulation;

    public:
        using Type = Basic;
        
        Entity m_Parent;
        Entity m_Owner = 0;
        uint64_t m_State = 0;
        uint64_t m_CreationTick = 0;

        Basic(Entity, Simulation *);
        ~Basic();

        Entity Team() const;
        void Team(Entity);
        uint32_t Flags() const;
        void Flags(uint32_t);

        void Reset();

        static void Write(bc::BinaryCoder &, Type const &, bool);
    };
}