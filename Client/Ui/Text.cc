#include <Client/Ui/Text.hh>

#include <cassert>
#include <string>

#include <Client/Renderer.hh>

namespace app::ui
{
    Text::Text(Renderer &ctx)
        : Element(ctx),
          m_TextAlign(Renderer::TextAlign::Center),
          m_TextBaseline(Renderer::TextBaseline::Middle)
    {
    }

    Text::~Text()
    {
        assert(false); //oops
    }

    void Text::Render() const
    {
        //Guard g(m_Renderer);
        m_Renderer.SetTextAlign(m_TextAlign);
        m_Renderer.SetTextBaseline(m_TextBaseline);
        m_Renderer.SetTextSize(m_TextSize);
        m_Renderer.SetLineWidth(m_LineWidth);
        m_Renderer.SetStroke(m_Stroke);
        m_Renderer.SetFill(m_Fill);
        m_Renderer.StrokeText(m_Text, m_X, m_Y);
        m_Renderer.FillText(m_Text, m_X, m_Y);
    }
}
