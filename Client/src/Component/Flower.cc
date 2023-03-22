#include <Component/Flower.hh>

#include <BinaryCoder/BinaryCoder.hh>
#include <BinaryCoder/NativeTypes.hh>

namespace app::component
{
    Flower::Flower(Entity parent)
        : m_Parent(parent)
    {
    }

    void Flower::UpdateFromBinary(bc::BinaryCoder &coder)
    {
        uint32_t updatedFields = coder.Read<bc::VarUint>();

        if (updatedFields & 1)
            m_Flags = coder.Read<bc::Uint8>();
        if (updatedFields & 2)
            m_EyeAngle = coder.Read<bc::Float32>();
    }
}
