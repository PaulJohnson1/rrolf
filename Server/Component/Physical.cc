#include <Server/Component/Physical.hh>

#include <BinaryCoder/BinaryCoder.hh>
#include <BinaryCoder/NativeTypes.hh>

#include <Server/Simulation.hh>

namespace app::component
{
    Physical::Physical(Entity parent, Simulation *simulation)
        : m_Parent(parent),
          m_Simulation(simulation)
    {
    }

    Physical::~Physical()
    {
        m_DeletionTick = 0;
    }

    void Physical::Reset()
    {
        m_State = 0;
        m_Collisions.clear();
    }

    void Physical::Write(bc::BinaryCoder &coder, Type const &entity, bool isCreation)
    {
        uint32_t state = isCreation ? 0b11111 : entity.m_State;

        coder.Write<bc::VarUint>(state);

        if (state & 1)
            coder.Write<bc::Float32>(entity.m_Radius);
        if (state & 2)
            coder.Write<bc::Float32>(entity.m_X);
        if (state & 4)
            coder.Write<bc::Float32>(entity.m_Y);
        if (state & 8)
            coder.Write<bc::Float32>(entity.m_Angle);
        if (state & 16)
            coder.Write<bc::VarUint>(entity.m_DeletionTick);
    }

    float Physical::Radius() const { return m_Radius; }
    float Physical::X() const { return m_X; }
    float Physical::Y() const { return m_Y; }
    float Physical::Angle() const { return m_Angle; }
    uint32_t Physical::DeletionTick() const { return m_DeletionTick; }

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

    void Physical::DeletionTick(uint32_t v)
    {
        ++m_DeletionTick;
        m_State |= 16;
    }
}
