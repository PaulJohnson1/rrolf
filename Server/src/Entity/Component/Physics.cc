#include <Entity/Component/Physics.hh>

#include <BinaryCoder/BinaryCoder.hh>
#include <BinaryCoder/NativeTypes.hh>

Physics::Physics(float r)
{
    m_Radius = r;
}
Physics::Physics(float r, float f, float m)
{
    m_Radius = r;
    m_Friction = f;
    m_Mass = m;
}

void Physics::Write(bc::BinaryCoder &coder, Physics physics)
{
    coder.Write<bc::VarUint>(physics.m_State);

    if (physics.m_State & 1)
        coder.Write<bc::Float32>(physics.m_Radius);
}

float Physics::Radius() const
{
    return m_Radius;
}
float Physics::Friction() const
{
    return m_Friction;
}
float Physics::Mass() const
{
    return m_Mass;
}

void Physics::Radius(float r)
{
    if (m_Radius == r) return;
    m_Radius = r;
    m_State |= 1;
}
void Physics::Friction(float f)
{
    m_Friction = f;
} 
void Physics::Mass(float m)
{
    m_Mass = m;
}
