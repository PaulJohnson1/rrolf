#include <Client/Ui/Element.hh>
#include <Client/Ui/Container.hh>


#include <cassert>

#include <Client/Renderer.hh>

namespace app::ui
{
    Element::Element(Renderer &ctx, float w, float h)
        : m_Renderer(ctx)
        , m_Container(&ctx.m_Container)
        , m_Width(w)
        , m_Height(h)
    {
    }

    Element::~Element()
    {
        // something went wrong
        assert(false);
    }
}
