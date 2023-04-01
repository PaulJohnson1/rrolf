#include <Server/Component/Mob.hh>

#include <BinaryCoder/BinaryCoder.hh>
#include <BinaryCoder/NativeTypes.hh>

#include <Server/Simulation.hh>

namespace app::component
{
    Mob::Mob(Entity parent, Simulation *simulation)
        : m_Parent(parent),
          m_Simulation(simulation)
    {
    }

    Mob::~Mob()
    {
    }

    void Mob::Reset()
    {
        m_State = 0;
    }

    void Mob::Write(bc::BinaryCoder &coder, Type const &entity, bool isCreation)
    {
        uint32_t state = isCreation ? 0b11 : entity.m_State;
        coder.Write<bc::VarUint>(state);

        if (state & 1)
            coder.Write<bc::VarUint>(entity.m_Id);
        if (state & 2)
            coder.Write<bc::VarUint>(entity.m_Rarity);
    }

    uint32_t Mob::Id() const { return m_Id; }
    uint32_t Mob::Rarity() const { return m_Rarity; }

    void Mob::Id(uint32_t v)
    {
        if (v == m_Id)
            return;
        m_Id = v;
        m_State |= 1;
    }

    void Mob::Rarity(uint32_t v)
    {
        if (v == m_Rarity)
            return;
        m_Rarity = v;
        Life &life = m_Simulation->Get<Life>(m_Parent);
        m_Simulation->Get<component::Physical>(m_Parent).Radius(MOB_DATA[m_Id].m_BaseSize * MOB_SCALE_FACTOR[m_Rarity]);
        life.Health(MOB_DATA[m_Id].m_BaseHealth * MOB_SCALE_FACTOR[m_Rarity]);
        life.MaxHealth(MOB_DATA[m_Id].m_BaseHealth * MOB_SCALE_FACTOR[m_Rarity]);
        life.m_Damage = MOB_DATA[m_Id].m_BaseDamage * MOB_DAMAGE_FACTOR[m_Rarity];
        m_State |= 2;
    }
}
