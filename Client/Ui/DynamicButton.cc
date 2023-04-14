#include <Client/Ui/DynamicButton.hh>

#include <iostream>
#include <string>
#include <cstdint>

#include <Client/Renderer.hh>
#include <Client/Ui/DrawPetal.hh>
#include <Client/Simulation.hh>
#include <Shared/StaticData.hh>

namespace app::ui
{
    DynamicButton::DynamicButton(Renderer &ctx, float w, uint32_t pos)
        : Button(ctx, w, w), m_Position(pos)
    {
    }

    void DynamicButton::Render()
    {
        Guard g(&m_Renderer);
        m_Renderer.Translate(m_HJustify * m_Container->m_Width / 2, m_VJustify * m_Container->m_Height / 2); // necessary btw
        m_Renderer.Translate(m_X * m_Renderer.m_WindowScale, m_Y * m_Renderer.m_WindowScale);
        m_Renderer.Scale(m_Renderer.m_WindowScale, m_Renderer.m_WindowScale);
        m_Renderer.RoundRect(-m_Width / 2, -m_Height / 2, m_Width, m_Height, m_R);
        m_Renderer.SetFill(m_Fill);
        m_Renderer.SetStroke(m_Stroke);
        m_Renderer.SetLineWidth(m_Width * 0.2);
        m_Renderer.SetLineJoin(Renderer::LineJoin::Round);
        m_Renderer.SetLineCap(Renderer::LineCap::Round);
        m_Renderer.Stroke();
        m_Renderer.Fill();
        if (!m_UseGlobalPosition)
        {
            const float *matrix = m_Renderer.GetTransform();
            m_GlobalX = matrix[2];
            m_GlobalY = matrix[5];
        }
        m_GlobalX.Tick(0.2);
        m_GlobalY.Tick(0.2);
        {
            Guard g(&m_Renderer);
            m_Renderer.ResetTransform();
            m_Renderer.Translate(m_GlobalX, m_GlobalY);
            m_Renderer.Scale(m_Renderer.m_WindowScale, m_Renderer.m_WindowScale);
            m_Renderer.BeginPath();
            m_Renderer.RoundRect(-m_Width / 2, -m_Height / 2, m_Width, m_Height, m_R); 
            m_Renderer.SetLineWidth(m_Width * 0.2);
            if (g_Simulation->HasComponent<component::PlayerInfo>(g_Simulation->m_PlayerInfo))
            {
                component::PlayerInfo &playerInfo = g_Simulation->Get<component::PlayerInfo>(g_Simulation->m_PlayerInfo);
                uint32_t id = playerInfo.m_Petals[m_Position].m_Id;
                uint32_t rarity = playerInfo.m_Petals[m_Position].m_Rarity;
                m_Renderer.SetFill(RARITY_COLORS[rarity]);
                m_Renderer.SetStroke(RARITY_COLORS[rarity], 0.64);
                m_Renderer.Stroke();
                m_Renderer.Fill();
                DrawPetal(&m_Renderer, id);
            }
            else 
            {
                m_Renderer.SetFill(m_Fill);
                m_Renderer.SetStroke(m_Stroke);
                m_Renderer.Stroke();
                m_Renderer.Fill();
            }
            ButtonAction();
        }
    }
}