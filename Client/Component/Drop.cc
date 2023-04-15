#include <Client/Component/Drop.hh>

#include <iostream>
#include <cmath>

#include <BinaryCoder/BinaryCoder.hh>
#include <BinaryCoder/NativeTypes.hh>

#include <Client/Renderer.hh>
#include <Client/Simulation.hh>
#include <Shared/StaticData.hh>
#include <Client/Simulation.hh>
#include <Client/Ui/DrawPetal.hh>

namespace app::component
{
    Drop::Drop(Entity parent, Simulation *simulation)
        : m_Parent(parent), m_Simulation(simulation)
    {
    }

    void Drop::UpdateFromBinary(bc::BinaryCoder &coder)
    {
        uint32_t updatedFields = coder.Read<bc::VarUint>();

        if (updatedFields & 1)
            m_Id = coder.Read<bc::VarUint>();
        if (updatedFields & 2)
            m_Rarity = coder.Read<bc::VarUint>();
    }

    void Drop::Render(Renderer *ctx)
    {
        component::Physical physical = m_Simulation->Get<component::Physical>(m_Parent);
        component::Basic basic = m_Simulation->Get<component::Basic>(m_Parent);
        Guard g(ctx);
        ctx->Translate(physical.m_X, physical.m_Y);
        ctx->Scale(physical.m_Radius / 25, physical.m_Radius / 25);
        ctx->Rotate(physical.m_Radius + 0.1);
        float sc = 0.05 * std::sin((m_Simulation->GetTime() - basic.m_CreationTime) * 0.01) + 1;
        ctx->Scale(sc, sc);
        ctx->BeginPath();
        ctx->SetFill(RARITY_COLORS[m_Rarity]);
        ctx->SetStroke(RARITY_COLORS[m_Rarity], 0.64);
        ctx->SetLineWidth(10);
        ctx->SetLineCap(Renderer::LineCap::Round);
        ctx->SetLineJoin(Renderer::LineJoin::Round);
        ctx->StrokeRect(-25,-25,50,50);
        ctx->FillRect(-25,-25,50,50);
        ctx->SetFill(0xffffffff);
        ctx->SetStroke(0xff000000);
        ctx->SetTextSize(14);
        ctx->SetLineWidth(1.68); 
        ctx->SetTextAlign(Renderer::TextAlign::Center);
        ctx->SetTextBaseline(Renderer::TextBaseline::Middle);
        ctx->BeginPath();
        ctx->StrokeText(PETAL_NAMES[m_Id], 0, 15);
        ctx->FillText(PETAL_NAMES[m_Id], 0, 15);
        ctx->Translate(0,-10);
        ui::DrawPetal(ctx, m_Id);
    }
}