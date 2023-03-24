#include <Client/Component/Life.hh>

#include <BinaryCoder/BinaryCoder.hh>
#include <BinaryCoder/NativeTypes.hh>

namespace app::component
{
    Life::Life(Entity parent)
        : m_Parent(parent)
    {
    }

    void Life::UpdateFromBinary(bc::BinaryCoder &coder)
    {
        uint32_t updatedFields = coder.Read<bc::VarUint>();

        if (updatedFields & 1)
            m_Health = coder.Read<bc::Float32>();
        if (updatedFields & 2)
            m_MaxHealth = coder.Read<bc::Float32>();
        if (updatedFields & 4)
            m_Damage = coder.Read<bc::Float32>();
    }
}
