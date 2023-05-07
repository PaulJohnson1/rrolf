#include <Client/Ui/MobButton.hh>

#include <string>
#include <cstdint>

#include <Client/Renderer.hh>
#include <Client/Simulation.hh>

#include <Client/Ui/RenderFunctions.hh>

namespace app::ui
{
    MobButton::MobButton(Renderer &ctx, float size, uint32_t id, uint32_t rarity)
        : Button(ctx, size, size), m_Id(id), m_Rarity(rarity)
    {
    }

    void MobButton::Render()
    {
        Guard g(&m_Renderer);
        PreRender();

        m_Renderer.Scale(m_Renderer.m_WindowScale);
        m_Renderer.Scale(m_Width / 50);
        ui::DrawMobWithBackground(&m_Renderer, m_Id, m_Rarity);
        m_Renderer.Translate(25,-25);
        m_Renderer.Rotate(0.5);
        m_Renderer.SetTextAlign(Renderer::TextAlign::Center);
        m_Renderer.SetTextBaseline(Renderer::TextBaseline::Middle);
        m_Renderer.SetTextSize(14);
        m_Renderer.SetLineWidth(14 * 0.12);
        m_Renderer.SetFill(0xffffffff);
        m_Renderer.SetStroke(0xff222222);
        m_Renderer.StrokeText("x2", 0, 0);
        m_Renderer.FillText("x2", 0, 0);
    }
}