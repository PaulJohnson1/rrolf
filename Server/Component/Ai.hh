#pragma once

#include <cstdint>

#include <Shared/Entity.hh>

namespace bc
{
    class BinaryCoder;
}

namespace app::component
{
    class Ai
    {
    public:
        using Type = Ai;
        
        Entity m_Parent;
        Entity m_Target;

        enum class AiState
        {
            Idle,
            IdleMoving,
            Target
        };

        AiState m_AiState = AiState::Idle;
        uint32_t m_TicksUntilNextAction = 10;
        uint64_t m_State = 0;

        Ai(Entity);

        void Reset();

        static void Write(bc::BinaryCoder &, Type, bool isCreation);
    };
}