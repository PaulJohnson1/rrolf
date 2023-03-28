#include <Server/Component/Mob.hh>

#include <cstdint>

#include <BinaryCoder/BinaryCoder.hh>
#include <BinaryCoder/NativeTypes.hh>

namespace app::component
{
    Mob::Mob(Entity parent)
        : m_Parent(parent)
    {
    }

    void Mob::Reset()
    {
        m_State = 0;
    }

    void Mob::Write(bc::BinaryCoder &coder, Type entity, bool isCreation)
    {
        uint32_t state = isCreation ? 0b1 : entity.m_State;
        coder.Write<bc::VarUint>(state);

        if (state & 1)
            coder.Write<bc::VarUint>(entity.m_Id);
        if (state & 2)
            coder.Write<bc::VarUint>(entity.m_Rarity);
    }

    uint8_t Mob::Id() const { return m_Id; }
    uint8_t Mob::Rarity() const { return m_Rarity; }
    
    void Mob::Id(uint8_t v)
    {
        if (v == m_Id)
            return;
        m_Id = v;
        m_State |= 1;
    }
 
    void Mob::Rarity(uint8_t v)
    {
        if (v == m_Rarity)
            return;
        m_Rarity = v;
        m_State |= 2;
    }
}
