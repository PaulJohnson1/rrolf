#include <Server/Component/Drop.hh>

#include <BinaryCoder/BinaryCoder.hh>
#include <BinaryCoder/NativeTypes.hh>

#include <Server/Simulation.hh>
#include <iostream>
namespace app::component
{
    Drop::Drop(Entity parent, Simulation *simulation)
        : m_Parent(parent),
          m_Simulation(simulation)
    {
    }

    Drop::~Drop()
    {
    }

    void Drop::Reset()
    {
        m_State = 4;
    }

    void Drop::Write(bc::BinaryCoder &coder, Type const &entity, bool isCreation)
    {
        uint32_t state = isCreation ? 0b11 : entity.m_State;
        coder.Write<bc::VarUint>(state);

        if (state & 1)
            coder.Write<bc::VarUint>(entity.m_Id);
        if (state & 2)
            coder.Write<bc::VarUint>(entity.m_Rarity);

        coder.Write<bc::Uint8>(entity.m_PickedUp);
    }

    uint32_t Drop::Id() const { return m_Id; }
    uint32_t Drop::Rarity() const { return m_Rarity; }

    void Drop::Id(uint32_t v)
    {
        if (v == m_Id)
            return;
        m_Id = v;
        m_State |= 1;
    }

    void Drop::Rarity(uint32_t v)
    {
        if (v == m_Rarity)
            return;
        m_Rarity = v;
        m_State |= 2;
    }
}
