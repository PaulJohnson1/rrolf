#include <Component/Render.hh>

#include <cstdint>

#include <BinaryCoder/BinaryCoder.hh>
#include <BinaryCoder/NativeTypes.hh>

namespace app::component
{
    Render::Render(Entity parent)
        : m_Parent(parent)
    {
    }

    void Render::Reset()
    {
        m_State = 0;
    }

    void Render::Write(bc::BinaryCoder &coder, Render entity, bool isCreation)
    {
        uint32_t state = isCreation ? 0b1 : entity.m_State;
        coder.Write<bc::VarUint>(state);

        if (state & 1)
            coder.Write<bc::VarUint>(entity.m_Color);
    }

    uint32_t Render::Color() const
    {
        return m_Color;
    }

    void Render::Color(uint32_t v)
    {
        if (v == m_Color)
            return;
        m_Color = v;
        m_State |= 1;
    }
}
