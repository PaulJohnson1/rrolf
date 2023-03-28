#include <Client/Component/Mob.hh>

#include <Client/Renderer.hh>
#include <Client/Simulation.hh>

#include <BinaryCoder/BinaryCoder.hh>
#include <BinaryCoder/NativeTypes.hh>

namespace app::component
{
    Mob::Mob(Entity parent)
        : m_Parent(parent)
    {
    }

    void Mob::UpdateFromBinary(bc::BinaryCoder &coder)
    {
        uint32_t updatedFields = coder.Read<bc::VarUint>();

        if (updatedFields & 1)
            m_Id = coder.Read<bc::VarUint>();
        if (updatedFields & 2)
            m_Rarity = coder.Read<bc::VarUint>();
    }

    void Mob::Render(Renderer *ctx)
    {
    }
}
