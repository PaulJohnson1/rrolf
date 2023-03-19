#pragma once

#include <cstdint>

namespace bc
{
    class BinaryCoder;
}

namespace app::component
{
    class Physics
    {
        float m_Radius;
        float m_Friction = 0.9;
        float m_Mass = 1;

    public:
        Vector m_Velocity;
        Vector m_Acceleration;

        using Type = Physics;

        uint16_t m_State;
        Physics() = default;
        float Radius() const;
        float Friction() const;
        float Mass() const;
        void Radius(float);
        void Friction(float);
        void Mass(float);

        static void Write(bc::BinaryCoder &coder, Type, bool isCreation);
    };
}
