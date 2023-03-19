#include <Component/Physics.hh>

#include <BinaryCoder/BinaryCoder.hh>
#include <BinaryCoder/NativeTypes.hh>

namespace app::component
{
    Physics::Physics(Entity parent)
        : m_Parent(parent)
    {
    }

    void Physics::UpdateFromBinary(bc::BinaryCoder &coder)
    {
        uint32_t updatedFields = coder.Read<bc::VarUint>();

        if (updatedFields & 1)
            m_Radius = coder.Read<bc::Float32>();
    }
}
