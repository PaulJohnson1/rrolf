#include <Client/Ui/MobButton.hh>

#include <string>

#include <Client/Renderer.hh>
#include <Client/Simulation.hh>

#include <Client/Ui/RenderFunctions.hh>
#include <Shared/Entity.hh>

namespace app::ui
{
    MobButton::MobButton(Renderer &ctx, float size, uint32_t id, uint32_t rarity)
        : Button(ctx, size, size), m_Id(id), m_Rarity(rarity)
    {
    }

    void MobButton::Render()
    {
        if (g_Simulation->m_PlayerInfo == NULL_ENTITY)
            return;
        Guard g(&m_Renderer);
        PreRender();

        m_Count = g_Simulation->Get<component::ArenaInfo>(0).m_MobCount[m_Id][m_Rarity];
        if (m_Count == 0)
        {
            m_Showing = false;
            return;
        }

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
        m_Renderer.StrokeText(std::string("x") + std::to_string(m_Count), 0, 0);
        m_Renderer.FillText(std::string("x") + std::to_string(m_Count), 0, 0);
    }

    void MobButton::Idle()
    {
        if (g_Simulation->m_PlayerInfo == NULL_ENTITY)
            return;
        if (g_Simulation->Get<component::ArenaInfo>(0).m_MobCount[m_Id][m_Rarity] != 0)
            m_Showing = true;
    }
}