#include <Client/Ui/Text.hh>

#include <cassert>
#include <string>

#include <Client/Renderer.hh>

namespace app::ui
{
    Text::Text(Renderer &ctx)
        : Element(ctx)
    {
    }

    Text::~Text()
    {
        assert(false);
    }

    void Text::Render() const
    {
        // gotta edit the html for that do it just go to florr lol
        // let me add setTextSize
        // somewhere in the frontend html you wiill find it
        // https://github.com/PaulJohnson1/wiux/
        // actually hm maybe idk did you import the ubuntu text file btw ubuntu font
        m_Renderer.SetTextSize(m_TextSize);
        m_Renderer.FillText(m_Text, m_X, m_Y);
    }
}
