#pragma once

#include <cstdint>
#include <Vector.hh>

namespace bc
{
    class BinaryCoder;
}

class Entity;

class Position
{
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
    static void Write(bc::BinaryCoder &, Position);

private:
    float m_X;
    float m_Y;
    float m_Angle;
};
