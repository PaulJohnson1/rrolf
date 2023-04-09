#include <Client/Component/Drop.hh>

#include <iostream>
#include <cmath>

#include <BinaryCoder/BinaryCoder.hh>
#include <BinaryCoder/NativeTypes.hh>

#include <Client/Renderer.hh>
#include <Client/Simulation.hh>
#include <Shared/StaticData.hh>
#include <Client/Simulation.hh>

namespace app::component
{
    Drop::Drop(Entity parent, Simulation *simulation)
        : m_Parent(parent)
        , m_Simulation(simulation)
        , m_Renderer({})
    {
        m_Renderer.SetSize(80, 80);
    }

    void Drop::UpdateFromBinary(bc::BinaryCoder &coder)
    {
        uint32_t updatedFields = coder.Read<bc::VarUint>();

        if (updatedFields & 1)
            m_Id = coder.Read<bc::VarUint>();
        if (updatedFields & 2)
            m_Rarity = coder.Read<bc::VarUint>();
        
        m_Renderer.ResetTransform();
        m_Renderer.Translate(40,40);
        m_Renderer.SetFill(RARITY_COLORS[m_Rarity]);
        m_Renderer.SetStroke(RARITY_COLORS[m_Rarity], 0.64);
        m_Renderer.SetLineJoin(Renderer::LineJoin::Round);
        m_Renderer.SetLineCap(Renderer::LineCap::Round);
        m_Renderer.SetLineWidth(60 * 0.2);
        m_Renderer.BeginPath();
        m_Renderer.StrokeRect(-30,-30,60,60);
        m_Renderer.FillRect(-30,-30,60,60);
        m_Renderer.SetFill(0xffffffff);
        m_Renderer.SetStroke(0xff000000);
        m_Renderer.SetTextSize(14);
        m_Renderer.SetLineWidth(14 * 0.12);
        m_Renderer.SetTextAlign(Renderer::TextAlign::Center);
        m_Renderer.SetTextBaseline(Renderer::TextBaseline::Middle);
        m_Renderer.BeginPath();
        m_Renderer.StrokeText("Basic", 0, 20);
        m_Renderer.FillText("Basic", 0, 20);
        m_Renderer.Translate(0,-5);
        switch (m_Id)
        {
        case 1:
            m_Renderer.SetFill(0xffcfcfcf);
            m_Renderer.BeginPath();
            m_Renderer.Arc(0, 0, 11.5);
            m_Renderer.Fill();
            m_Renderer.SetFill(0xffffffff);
            m_Renderer.BeginPath();
            m_Renderer.Arc(0, 0, 8.5);
            m_Renderer.Fill();
            break;
        case 2:
            m_Renderer.SetFill(0xffcfcfcf);
            m_Renderer.BeginPath();
            m_Renderer.Arc(0, 0, 8.5);
            m_Renderer.Fill();
            m_Renderer.SetFill(0xffffffff);
            m_Renderer.BeginPath();
            m_Renderer.Arc(0, 0, 5.5);
            m_Renderer.Fill();
            break;
        default:
            m_Renderer.SetFill(0xffcfcfcf);
            m_Renderer.BeginPath();
            m_Renderer.Arc(0, 0, 11.5);
            m_Renderer.Fill();
            m_Renderer.SetFill(0xffffffff);
            m_Renderer.BeginPath();
            m_Renderer.Arc(0, 0, 8.5);
            m_Renderer.Fill();
            break;
        }
    }

    void Drop::Render(Renderer *ctx)
    {
        component::Physical physical = m_Simulation->Get<component::Physical>(m_Parent);
        Guard g(ctx);
        ctx->Translate(physical.m_X, physical.m_Y);
        ctx->Scale(physical.m_Radius / 60, physical.m_Radius / 60);
        ctx->DrawImage(m_Renderer);
    }
}