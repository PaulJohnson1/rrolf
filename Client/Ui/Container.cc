#include <Client/Ui/Element.hh>
#include <Client/Ui/Container.hh>

#include <cassert>

#include <Client/Renderer.hh>

namespace app::ui
{
    Container::Container(Renderer &ctx)
    :   Element(ctx,0,0)
    {
    }
    void Container::Render()
    {
        Guard g(&m_Renderer);
        m_Renderer.Translate(m_HJustify * m_Container->m_Width / 2, m_VJustify * m_Container->m_Height / 2); //necessary btw
        m_Renderer.Translate(m_X * m_Renderer.m_WindowScale, m_Y * m_Renderer.m_WindowScale);
        if (m_HasBackground)
        {
            Guard g(&m_Renderer);
            m_Renderer.Scale(m_Renderer.m_WindowScale, m_Renderer.m_WindowScale);
            m_Renderer.SetFill(m_Fill);
            m_Renderer.SetStroke(m_Stroke);
            m_Renderer.BeginPath();
            m_Renderer.FillRect(-m_Width / 2, -m_Height / 2, m_Width, m_Height);
        }
        for (uint64_t i = 0; i < m_Elements.size(); i++)
        {
            ui::Element *element = m_Elements[i];
            if (element->m_Showing)
                element->Render();
        }
    }
}