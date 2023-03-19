#pragma once

#include <cstdint>
#include <Vector.hh>

namespace bc
{
    class BinaryCoder;
}

class Entity;

namespace app::component
{
    class Position
    {
        float m_X;
        float m_Y;
        float m_Angle;

    public:
        using Type = Position;

        uint16_t m_State;

        Position(Vector, float);

        float X() const;
        float Y() const;
        float Angle() const;
        void X(float);
        void Y(float);
        void Angle(float);

        void operator+=(Vector v);

        // clone becuase the struct is small
        static void Write(bc::BinaryCoder &, Position, bool isCreation);
    };
}
