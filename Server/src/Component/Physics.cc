#include <Component/Physics.hh>

#include <BinaryCoder/BinaryCoder.hh>
#include <BinaryCoder/NativeTypes.hh>

namespace app::component
{
    Physics::Physics(Entity parent)
        : m_Parent(parent)
    {
    }

    void Physics::Reset()
    {
        m_State = 0;
        m_Collisions.clear();
    }

    void Physics::Write(bc::BinaryCoder &coder, Physics physics, bool isCreation)
    {
        uint32_t state = isCreation ? 0b1 : physics.m_State;

        coder.Write<bc::VarUint>(state);

        if (state & 1)
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
        if (m_Radius == r)
            return;
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
}
