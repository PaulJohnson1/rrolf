#include <Client/Ui/Element.hh>

#include <cassert>

#include <Client/Renderer.hh>
#include <Client/Ui/Container.hh>

namespace app::ui
{
    Element::Element(Renderer &ctx, float w, float h)
        : m_Renderer(ctx),
          m_Container(&ctx.m_Container),
          m_Width(w),
          m_Height(h)
    {
    }

    Element::~Element()
    {
        assert(false);
    }

    void Element::PreRender() 
    {
        m_Renderer.Translate((m_X + (m_HJustify - 1) * m_Container->m_Width / 2) * m_Renderer.m_WindowScale,(m_Y + (m_VJustify - 1) * m_Container->m_Height / 2) * m_Renderer.m_WindowScale); // necessary btw
    }
}
