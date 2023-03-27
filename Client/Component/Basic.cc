#include <Client/Component/Basic.hh>

#include <BinaryCoder/BinaryCoder.hh>
#include <BinaryCoder/NativeTypes.hh>

namespace app::component
{
    Basic::Basic(Entity parent)
        : m_Parent(parent)
    {
    }

    void Basic::UpdateFromBinary(bc::BinaryCoder &coder)
    {
        uint32_t updatedFields = coder.Read<bc::VarUint>();

        if (updatedFields & 1)
            m_Team = coder.Read<bc::VarUint>();
        if (updatedFields & 2)
            m_Flags = coder.Read<bc::VarUint>();
    }
}
