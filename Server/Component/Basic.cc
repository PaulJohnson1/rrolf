#include <Server/Component/Basic.hh>

#include <cstdint>

#include <BinaryCoder/BinaryCoder.hh>
#include <BinaryCoder/NativeTypes.hh>

namespace app::component
{
    Basic::Basic(Entity parent)
        : m_Parent(parent)
    {
    }

    void Basic::Reset()
    {
        m_State = 0;
    }

    void Basic::Write(bc::BinaryCoder &coder, Type entity, bool isCreation)
    {
        uint32_t state = isCreation ? 0b1 : entity.m_State;
        coder.Write<bc::VarUint>(state);

        if (state & 1)
            coder.Write<bc::VarUint>(entity.m_Team);
        if (state & 2)
            coder.Write<bc::VarUint>(entity.m_Flags);
    }

    Entity Basic::Team() const { return m_Team; }
    void Basic::Team(Entity x)
    {
        if (x == m_Team)
            return;
        m_Team = x;
        m_State |= 1;
    }
    uint32_t Basic::Flags() const { return m_Flags; }
    void Basic::Flags(uint32_t x)
    {
        if (x == m_Flags)
            return;
        m_Flags = x;
        m_State |= 1;
    }
}
