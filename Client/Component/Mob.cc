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
        Renderer::ContextLock lock = ctx->AutoSaveRestore();
        component::Physical physical = ctx->m_Simulation.Get<component::Physical>(m_Parent);
        switch(m_Id) {
            case 0:
                ctx->DrawCircle(0, 0, physical.m_Radius, paint);
                break;
        
            default:
                assert(false);
        }
    }
}
