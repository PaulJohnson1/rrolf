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
        m_LerpWidth = 0;
    }

    void DynamicButton::Render()
    {
        Guard g(&m_Renderer);
        m_Renderer.Translate(m_HJustify * m_Container->m_Width / 2, m_VJustify * m_Container->m_Height / 2); // necessary btw
        m_Renderer.Translate(m_X * m_Renderer.m_WindowScale, m_Y * m_Renderer.m_WindowScale);
        m_Renderer.Scale(m_Renderer.m_WindowScale);
        m_Renderer.SetFill(m_Fill);
        m_Renderer.SetStroke(m_Stroke);
        m_Renderer.SetLineWidth(m_Width * 0.1);
        m_Renderer.SetLineJoin(Renderer::LineJoin::Round);
        m_Renderer.SetLineCap(Renderer::LineCap::Round);
        m_Renderer.FillRect(-m_Width / 2, -m_Height / 2, m_Width, m_Height);
        m_Renderer.StrokeRect(-m_Width / 2, -m_Height / 2, m_Width, m_Height);
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
            if (g_Simulation->m_PlayerInfo != (Entity)-1 && g_Simulation->HasComponent<component::PlayerInfo>(g_Simulation->m_PlayerInfo))
            {
                component::PlayerInfo &playerInfo = g_Simulation->Get<component::PlayerInfo>(g_Simulation->m_PlayerInfo);
                component::PlayerInfo::LoadoutPetal &usingPos = m_Position < 10 ? playerInfo.m_Petals[m_Position]: playerInfo.m_SecondaryPetals[m_Position - 10];
                uint32_t id = usingPos.m_Id;
                if (id != 0)
                {
                    uint32_t rarity = usingPos.m_Rarity;

                    if (id != m_PrevId || rarity != m_PrevRarity)
                        m_LerpWidth.SetInterpolated(0.0f);
                    
                    m_PrevId = id;
                    m_PrevRarity = rarity;

                    m_LerpWidth = m_Width;
                    usingPos.m_Reload.Tick(0.5);
                    m_LerpWidth.Tick(0.2);
                    m_Renderer.Scale(m_Renderer.m_WindowScale * m_LerpWidth / 60);

                    if (m_Position < 10)
                        ui::DrawLoadoutPetal(&m_Renderer, id, rarity, usingPos.m_Reload);
                    else
                        ui::DrawLoadoutPetal(&m_Renderer, id, rarity, 0.0f);
                    ButtonAction();
                }
                else
                {
                    m_PrevId = 0;
                    m_PrevRarity = 0;
                    m_LerpWidth = 0;
                }
            }
        }
    }
}