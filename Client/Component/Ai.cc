#include <Client/Component/Ai.hh>

#include <BinaryCoder/BinaryCoder.hh>
#include <BinaryCoder/NativeTypes.hh>

namespace app::component
{
    Ai::Ai(Entity parent)
        : m_Parent(parent)
    {
    }

    void Ai::UpdateFromBinary(bc::BinaryCoder &coder)
    {
        coder.Read<bc::VarUint>();
    }
}
