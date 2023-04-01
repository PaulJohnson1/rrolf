#include <Server/Component/Petal.hh>

#include <BinaryCoder/BinaryCoder.hh>
#include <BinaryCoder/NativeTypes.hh>

#include <Server/Simulation.hh>

namespace app::component
{
    Petal::Petal(Entity parent, Simulation *simulation)
        : m_Parent(parent),
          m_Simulation(simulation)
    {
    }

    Petal::~Petal()
    {
    }

    void Petal::Reset()
    {
        m_State = 0;
    }

    void Petal::Write(bc::BinaryCoder &coder, Type entity, bool isCreation)
    {
        uint32_t state = isCreation ? 0b11 : entity.m_State;
        coder.Write<bc::VarUint>(state);

        if (state & 1)
            coder.Write<bc::VarUint>(entity.m_Id);
        if (state & 2)
            coder.Write<bc::VarUint>(entity.m_Rarity);
    }

    uint32_t Petal::Id() const { return m_Id; }
    uint32_t Petal::Rarity() const { return m_Rarity; }

    void Petal::Id(uint32_t v)
    {
        if (v == m_Id)
            return;
        m_Id = v;
        m_State |= 1;
    }

    void Petal::Rarity(uint32_t v)
    {
        if (v == m_Rarity)
            return;
        m_Rarity = v;
        Life &life = m_Simulation->Get<Life>(m_Parent);
        life.Health(PETAL_DATA[m_Id].m_BaseHealth * PETAL_SCALE_FACTOR[m_Rarity]);
        life.MaxHealth(PETAL_DATA[m_Id].m_BaseHealth * PETAL_SCALE_FACTOR[m_Rarity]);
        m_State |= 2;
    }
}
