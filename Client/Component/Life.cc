#include <Client/Component/Life.hh>
#include <Client/Component/Mob.hh>
#include <Client/Renderer.hh>
#include <Client/Simulation.hh>

#include <BinaryCoder/BinaryCoder.hh>
#include <BinaryCoder/NativeTypes.hh>

#include <Shared/StaticData.hh>

#include <Client/Simulation.hh>

namespace app::component
{
    Life::Life(Entity parent, Simulation *simulation)
        : m_Parent(parent),
          m_Simulation(simulation)
    {
    }

    void Life::UpdateFromBinary(bc::BinaryCoder &coder)
    {
        uint32_t updatedFields = coder.Read<bc::VarUint>();

        if (updatedFields & 1)
        {
            float old = m_Health.Destination();
            m_Health = coder.Read<bc::Float32>();
            if (m_Health.Destination() < old)
                m_DamageAnimationTick = 12;
        }
        if (updatedFields & 2)
            m_MaxHealth = coder.Read<bc::Float32>();
    }
    void Life::Render(Renderer *ctx)
    {
        if (m_MaxHealth == 0) return;
        Guard g(ctx);
        component::Physical &physical = m_Simulation->Get<component::Physical>(m_Parent);
        ctx->Translate(physical.m_X, physical.m_Y + physical.m_Radius + 30);
        if (m_Simulation->HasComponent<component::Mob>(m_Parent) && m_Simulation->Get<component::Mob>(m_Parent).m_Rarity == 6)
            ctx->Translate(0, 75);
        float length = 40;
        
        // mob rarity render
        if (m_Simulation->HasComponent<component::Mob>(m_Parent))
        {
            component::Mob &mob = m_Simulation->Get<component::Mob>(m_Parent);
            length += 5 * mob.m_Rarity;
            ctx->SetTextBaseline(Renderer::TextBaseline::Top);
            ctx->SetTextAlign(Renderer::TextAlign::Right);
            ctx->SetTextSize(14);
            ctx->SetLineWidth(1.68);
            ctx->SetFill(RARITY_COLORS[mob.m_Rarity]);
            ctx->SetStroke(0xff000000);
            ctx->BeginPath();
            ctx->StrokeText(RARITY_NAMES[mob.m_Rarity], length, 5);
            ctx->FillText(RARITY_NAMES[mob.m_Rarity], length, 5);
            ctx->SetTextSize(16);
            ctx->SetLineWidth(1.92);
            ctx->SetTextBaseline(Renderer::TextBaseline::Bottom);
            ctx->SetTextAlign(Renderer::TextAlign::Left);
            ctx->BeginPath();
            ctx->SetFill(0xffffffff);
            ctx->StrokeText(MOB_NAMES[mob.m_Id], -length, -6.5);
            ctx->FillText(MOB_NAMES[mob.m_Id], -length, -6.5);
        }
        // draw hp
        ctx->SetLineCap(Renderer::LineCap::Round);

        // outline
        ctx->SetStroke(0xff222222);
        ctx->SetLineWidth(10);
        ctx->BeginPath();
        ctx->MoveTo(-length, 0);
        ctx->LineTo(length, 0);
        ctx->Stroke();

        // red animation
        ctx->SetStroke(0xffdd3434);
        ctx->SetLineWidth(6);
        ctx->BeginPath();
        ctx->MoveTo(-length, 0);
        ctx->LineTo(-length + 2 * length * m_HealthRedAnimation / m_MaxHealth, 0);
        ctx->Stroke();

        // green
        ctx->SetStroke(0xff75dd34);
        ctx->SetLineWidth(7);
        ctx->BeginPath();
        ctx->MoveTo(-length, 0);
        ctx->LineTo(-length + 2 * length * m_Health / m_MaxHealth, 0);
        ctx->Stroke();
    }
}
