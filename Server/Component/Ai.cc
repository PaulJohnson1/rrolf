#include <Server/Component/Ai.hh>

#include <cstdint>

#include <BinaryCoder/BinaryCoder.hh>
#include <BinaryCoder/NativeTypes.hh>

namespace app::component
{
    Ai::Ai(Entity parent)
        : m_Parent(parent)
    {
    }

    void Ai::Reset()
    {
        m_State = 0;
    }

    void Ai::Write(bc::BinaryCoder &coder, Type entity, bool isCreation)
    {
        coder.Write<bc::VarUint>(0);
    }
}
