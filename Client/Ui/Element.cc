#include <Client/Ui/Element.hh>

#include <Client/Renderer.hh>
#include <Client/Ui/Container.hh>
#include <Shared/Assert.hh>

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
}
