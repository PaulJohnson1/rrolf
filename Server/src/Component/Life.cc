#include <Component/Life.hh>

#include <cstdint>

#include <BinaryCoder/BinaryCoder.hh>
#include <BinaryCoder/NativeTypes.hh>

namespace app::component
{
    Life::Life(Entity parent)
        : m_Parent(parent)
    {
    }

    void Life::Reset()
    {
        m_State = 0;
    }

    void Life::Write(bc::BinaryCoder &coder, Life life, bool isCreation)
    {
        uint32_t state = isCreation ? 0b111 : life.m_State;
        coder.Write<bc::VarUint>(state);

        if (state & 1)
            coder.Write<bc::Float32>(life.m_Health);
        if (state & 2)
            coder.Write<bc::Float32>(life.m_MaxHealth);
        if (state & 4)
            coder.Write<bc::Float32>(life.m_Damage);
    }

    float Life::Health() const
    {
        return m_Health;
    }
    
    float Life::MaxHealth() const
    {
        return m_MaxHealth;
    }

    float Life::Damage() const
    {
        return m_Damage;
    }

    void Life::Health(float v)
    {
        if (v == m_Health)
            return;
        m_Health = v;
        m_State |= 1 << 0;
    }

    void Life::MaxHealth(float v)
    {
        if (v == m_MaxHealth)
            return;
        m_MaxHealth = v;
        m_State |= 1 << 1;
    }

    void Life::Damage(float v)
    {
        if (v == m_Damage)
            return;
        m_Damage = v;
        m_State |= 1 << 2;
    }

    void Life::operator+=(float v)
    {
        if (v == 0)
            return;
        m_Health += v;
        if (m_Health > m_MaxHealth) m_Health = m_MaxHealth;
        m_State |= 1 << 0;
    }

    void Life::operator-=(float v)
    {
        if (v == 0)
            return;
        m_Health -= v;
        if (m_Health < 0) m_Health = 0;
        m_State |= 1 << 0;
    }
}
