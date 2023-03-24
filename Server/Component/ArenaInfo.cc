#include <Server/Component/ArenaInfo.hh>

#include <cstdint>

#include <BinaryCoder/BinaryCoder.hh>
#include <BinaryCoder/NativeTypes.hh>

namespace app::component
{
    ArenaInfo::ArenaInfo(Entity parent)
        : m_Parent(parent)
    {
    }

    void ArenaInfo::Reset()
    {
        m_State = 0;
    }

    void ArenaInfo::Write(bc::BinaryCoder &coder, Type entity, bool isCreation)
    {
        uint32_t state = isCreation ? 0b1 : entity.m_State;
        coder.Write<bc::VarUint>(state);

        if (state & 1)
            coder.Write<bc::VarUint>(entity.m_MapSize);
    }

    float ArenaInfo::MapSize() const
    {
        return m_MapSize;
    }

    void ArenaInfo::MapSize(float v)
    {
        if (v == m_MapSize)
            return;
        m_MapSize = v;
        m_State |= 1;
    }
}
