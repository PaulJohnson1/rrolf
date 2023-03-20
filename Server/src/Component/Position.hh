#pragma once

#include <cstdint>

#include <Entity.hh>
#include <Vector.hh>

namespace bc
{
    class BinaryCoder;
}

namespace app::component
{
    class Position
    {
        float m_X = 0.0f;
        float m_Y = 0.0f;
        float m_Angle = 0.0f;

    public:
        using Type = Position;

        uint64_t m_State = 0;
        Entity m_Parent;

        Position(Entity);

        float X() const;
        float Y() const;
        float Angle() const;
        void X(float);
        void Y(float);
        void Angle(float);

        void Reset();

        // clone becuase the struct is small
        static void Write(bc::BinaryCoder &, Position, bool);
    };
}
