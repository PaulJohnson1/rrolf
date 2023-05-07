#include <Client/Ui/MobButton.hh>

#include <string>
#include <cstdint>

#include <Client/Renderer.hh>
#include <Client/Simulation.hh>

#include <Client/Ui/RenderFunctions.hh>

namespace app::ui
{
    MobButton::MobButton(Renderer &ctx, uint32_t id, uint32_t rarity)
        : Button(ctx, 60, 60), m_Id(id), m_Rarity(rarity)
    {
        m_LerpWidth = 0;
    }

    void MobButton::Render()
    {
        Guard g(&m_Renderer);

        m_Renderer.Translate((m_X + (m_HJustify - 1) * m_Container->m_Width / 2) * m_Renderer.m_WindowScale,(m_Y + (m_VJustify - 1) * m_Container->m_Height / 2) * m_Renderer.m_WindowScale); // necessary btw

        m_Renderer.Scale(m_Renderer.m_WindowScale);
        ui::DrawMobWithBackground(&m_Renderer, m_Id, m_Rarity);
    }
}