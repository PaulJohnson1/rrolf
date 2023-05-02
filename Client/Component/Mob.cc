#include <Client/Component/Mob.hh>

#include <iostream>
#include <cmath>

#include <BinaryCoder/BinaryCoder.hh>
#include <BinaryCoder/NativeTypes.hh>

#include <Client/Renderer.hh>
#include <Client/Simulation.hh>
#include <Shared/StaticData.hh>

#include <Client/Ui/DrawPetal.hh>

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
        component::Physical physical = m_Simulation->Get<component::Physical>(m_Parent);
        uint32_t dTick = m_Simulation->Get<component::Life>(m_Parent).m_DamageAnimationTick;

        ctx->SetGlobalAlpha(1 - 0.2 * physical.m_DeletionTick);

        ctx->Translate(physical.m_X, physical.m_Y);
        ctx->Scale(1 + physical.m_DeletionTick * 0.1);
        
        float scale = MOB_SCALE_FACTOR[m_Rarity];
        ctx->Scale(scale);
        ctx->Rotate(physical.m_Angle);
        float seed = std::sin(m_Simulation->GetTime() / 100);
        ctx->SetFill(ui::DamageColor(0xff454545, dTick));
        ctx->SetStroke(ui::DamageColor(0xff292929, dTick));
        ctx->SetLineWidth(7);
        ctx->SetLineCap(Renderer::LineCap::Round);
        ctx->BeginPath();
        ctx->MoveTo(0, -7);
        ctx->QuadraticCurveTo(11, -10 + seed, 22, -5 + seed);
        ctx->Stroke();
        ctx->BeginPath();
        ctx->MoveTo(0, 7);
        ctx->QuadraticCurveTo(11, 10 - seed, 22, 5 - seed);
        ctx->Stroke();
        ctx->BeginPath();
        ctx->Arc(0, 0, 17.5);
        ctx->Fill();
        ctx->SetFill(ui::DamageColor(0xff555555, dTick));
        ctx->BeginPath();
        ctx->Arc(0, 0, 10.5);
        ctx->Fill();
    }
}
