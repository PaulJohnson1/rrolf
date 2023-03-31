#include <Client/Ui/Element.hh>

#include <cassert>

#include <Client/Renderer.hh>

namespace app::ui
{
    Element::Element(Renderer &ctx)
        : m_Renderer(ctx)
    {
    }

    Element::~Element()
    {
        // something went wrong
        assert(false);
    }
}
