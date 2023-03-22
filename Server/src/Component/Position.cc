#include <Component/Position.hh>

#include <cstdint>

#include <BinaryCoder/BinaryCoder.hh>
#include <BinaryCoder/NativeTypes.hh>

namespace app::component
{
    Position::Position(Entity parent)
        : m_Parent(parent)
    {
    }

    void Position::Reset()
    {
        m_State = 0;
    }

    void Position::Write(bc::BinaryCoder &coder, Position position, bool isCreation)
    {
        uint32_t state = isCreation ? 0b111 : position.m_State;
        coder.Write<bc::VarUint>(state);

        if (state & 1)
            coder.Write<bc::Float32>(position.m_X);
        if (state & 2)
            coder.Write<bc::Float32>(position.m_Y);
        if (state & 4)
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
}
