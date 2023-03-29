#include <Client/Component/Physical.hh>

#include <BinaryCoder/BinaryCoder.hh>
#include <BinaryCoder/NativeTypes.hh>

namespace app::component
{
    Physical::Physical(Entity parent)
        : m_Parent(parent)
    {
    }

    void Physical::UpdateFromBinary(bc::BinaryCoder &coder)
    {
        uint32_t updatedFields = coder.Read<bc::VarUint>();

        if (updatedFields & 1)
            m_RadiusDestination = coder.Read<bc::Float32>();
        if (updatedFields & 2)
           m_XDestination = coder.Read<bc::Float32>();
        if (updatedFields & 4)
            m_YDestination = coder.Read<bc::Float32>();
        if (updatedFields & 8)
            m_AngleDestination = coder.Read<bc::Float32>();
    }
}
