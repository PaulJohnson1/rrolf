#include <Client/Component/Render.hh>

#include <BinaryCoder/BinaryCoder.hh>
#include <BinaryCoder/NativeTypes.hh>

namespace app::component
{
    Render::Render(Entity parent)
        : m_Parent(parent)
    {
    }

    void Render::UpdateFromBinary(bc::BinaryCoder &coder)
    {
        uint32_t updatedFields = coder.Read<bc::VarUint>();

        if (updatedFields & 1)
            m_Color = coder.Read<bc::VarUint>();
    }
}
