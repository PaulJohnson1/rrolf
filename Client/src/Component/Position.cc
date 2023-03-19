#include <Component/Position.hh>

#include <BinaryCoder/BinaryCoder.hh>
#include <BinaryCoder/NativeTypes.hh>

namespace app::component
{
    Position::Position(Entity parent)
        : m_Parent(parent)
    {
    }

    void Position::UpdateFromBinary(bc::BinaryCoder &coder)
    {
        uint32_t updatedFields = coder.Read<bc::VarUint>();

        if (updatedFields & 1)
            m_X = coder.Read<bc::Float32>();
        if (updatedFields & 2)
            m_Y = coder.Read<bc::Float32>();
        if (updatedFields & 4)
            m_Angle = coder.Read<bc::Float32>();
    }
}
