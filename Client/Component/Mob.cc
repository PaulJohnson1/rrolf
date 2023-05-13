#include <Client/Component/Mob.hh>

#include <iostream>
#include <cmath>

#include <BinaryCoder/BinaryCoder.hh>
#include <BinaryCoder/NativeTypes.hh>

#include <Client/Renderer.hh>
#include <Client/Simulation.hh>
#include <Shared/StaticData.hh>

#include <Client/Ui/RenderFunctions.hh>

namespace app::component
{
    Mob::Mob(Entity parent, Simulation *simulation)
        : m_Parent(parent),
          m_Simulation(simulation)
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
        Guard g(ctx);
        Physical physical = m_Simulation->Get<Physical>(m_Parent);

        ctx->Translate(physical.m_X, physical.m_Y);
        float seed = std::sin(m_Simulation->GetTime() / 100);
        float scale = MOB_SCALE_FACTOR[m_Rarity];
        ctx->SetGlobalAlpha(1 - 0.2 * physical.m_ClientDeletionTick);
        ctx->Scale(scale * (1 + physical.m_ClientDeletionTick * 0.1));
        ctx->Rotate(physical.m_Angle);
        ui::DrawMob(ctx, m_Id, m_Simulation->Get<Life>(m_Parent).m_DamageAnimationTick, seed);
    }
}
