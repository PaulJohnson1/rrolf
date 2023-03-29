#include <Server/Component/Physical.hh>

#include <BinaryCoder/BinaryCoder.hh>
#include <BinaryCoder/NativeTypes.hh>

#include <iostream>

namespace app::component
{
    Physical::Physical(Entity parent)
        : m_Parent(parent)
    {
    }

    void Physical::Reset()
    {
        m_State = 0;
        m_Collisions.clear();
    }

    void Physical::Write(bc::BinaryCoder &coder, Physical const &physical, bool isCreation)
    {
        uint32_t state = isCreation ? 0b1111 : physical.m_State;

        coder.Write<bc::VarUint>(state);

        if (state & 1)
            coder.Write<bc::Float32>(physical.m_Radius);
        if (state & 2)
            coder.Write<bc::Float32>(physical.m_X);
        if (state & 4)
            coder.Write<bc::Float32>(physical.m_Y);
        if (state & 8)
            coder.Write<bc::Float32>(physical.m_Angle);
    }

    float Physical::Radius() const { return m_Radius; }
    float Physical::Friction() const { return m_Friction; }
    float Physical::X() const { return m_X; }
    float Physical::Y() const { return m_Y; }
    float Physical::Angle() const { return m_Angle; }

    void Physical::Radius(float r)
    {
        if (m_Radius == r)
            return;
        m_Radius = r;
        m_Mass = r;
        m_State |= 1;
    }

    void Physical::X(float x)
    {
        if (m_X == x)
            return;
        m_X = x;
        m_State |= 2;
    }

    void Physical::Y(float x)
    {
        if (m_Y == x)
            return;
        m_Y = x;
        m_State |= 4;
    }

    void Physical::Angle(float x)
    {
        if (m_Angle == x)
            return;
        m_Angle = x;
        m_State |= 8;
    }

    void Physical::Friction(float f)
    {
        m_Friction = f;
    }
}
