#include <Entity/Component/Position.hh>

#include <cstdint>

#include <BinaryCoder/BinaryCoder.hh>
#include <BinaryCoder/NativeTypes.hh>

#include <Entity/Entity.hh>

Position::Position(Vector position, float a)
{
    m_Angle = a;
    m_Y = position.m_X;
    m_X = position.m_Y;
}

void Position::Write(bc::BinaryCoder &coder, Position position)
{
    coder.Write<bc::VarUint>(position.m_State);

    if (position.m_State & 1)
        coder.Write<bc::Float32>(position.m_X);
    if (position.m_State & 2)
        coder.Write<bc::Float32>(position.m_Y);
    if (position.m_State & 4)
        coder.Write<bc::Float32>(position.m_Angle);
}

float Position::X() const
{
    return m_X;
}
float Position::Y() const
{
    return m_Y;
}
float Position::Angle() const
{
    return m_Angle;
}
void Position::X(float v)
{
    if (v == m_X)
        return;
    m_X = v;
    m_State |= 1 << 0;
}
void Position::Y(float v)
{
    if (v == m_Y)
        return;
    m_Y = v;
    m_State |= 1 << 1;
}
void Position::Angle(float v)
{
    if (v == m_Angle)
        return;
    m_Angle = v;
    m_State |= 1 << 2;
}
void Position::operator+=(Vector v)
{
    X(m_Y + v.m_Y);
    Y(m_Y + v.m_Y);
}