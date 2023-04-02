#include <Server/Component/Life.hh>

#include <cstdint>

#include <BinaryCoder/BinaryCoder.hh>
#include <BinaryCoder/NativeTypes.hh>

#include <Server/Simulation.hh>

namespace app::component
{
    Life::Life(Entity parent, Simulation *simulation)
        : m_Parent(parent),
          m_Simulation(simulation)
    {
    }

    Life::~Life()
    {
    }

    void Life::Reset()
    {
        m_State = 0;
    }

    void Life::Write(bc::BinaryCoder &coder, Type const &entity, bool isCreation)
    {
        if (entity.m_Simulation->HasComponent<component::Petal>(entity.m_Parent))
        {
            coder.Write<bc::VarUint>(0);
            return;
        }
        uint32_t state = isCreation ? 0b11 : entity.m_State;
        coder.Write<bc::VarUint>(state);

        if (state & 1)
            coder.Write<bc::Float32>(entity.m_Health);
        if (state & 2)
            coder.Write<bc::Float32>(entity.m_MaxHealth);
    }

    float Life::Health() const { return m_Health; }
    float Life::MaxHealth() const { return m_MaxHealth; }

    void Life::Health(float v)
    {
        if (v < 0)
            v = 0;
        else if (v > m_MaxHealth)
            v = m_MaxHealth;
        if (v == m_Health)
            return;
        m_Health = v;
        m_State |= 1 << 0;
    }

    void Life::MaxHealth(float v)
    {
        if (v == m_MaxHealth)
            return;
        float fraction = v / m_MaxHealth;
        m_MaxHealth = v;
        m_Health *= fraction;
        m_State |= 1 << 1;
    }
}
