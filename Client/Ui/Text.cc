#include <Client/Ui/Text.hh>

#include <string>

#include <Client/Renderer.hh>

namespace app::ui
{
    Text::Text(Renderer &ctx, std::string const &text, uint32_t fill, float size)
        : Element(ctx, 0, size),
          m_TextAlign(Renderer::TextAlign::Center),
          m_TextBaseline(Renderer::TextBaseline::Middle),
          m_Text(text),
          m_TextSize(size)
    {
        m_Fill = fill;
        ctx.SetTextSize(size);
        m_Width = ctx.GetTextLength(text);
    }

    void Text::Render()
    {
        Guard g(&m_Renderer);
        m_Renderer.Translate((m_HJustify - 1) * m_Container->m_Width / 2, (m_VJustify - 1) * m_Container->m_Height / 2); // necessary btw
        m_Renderer.Translate(m_X * m_Renderer.m_WindowScale, m_Y * m_Renderer.m_WindowScale);
        m_Renderer.SetTextAlign(m_TextAlign);
        m_Renderer.SetTextBaseline(m_TextBaseline);
        m_Renderer.SetTextSize(m_TextSize);
        m_Renderer.SetLineWidth(m_TextSize * 0.12);
        m_Renderer.SetStroke(m_Stroke);
        m_Renderer.SetFill(m_Fill);
        m_Renderer.StrokeText(m_Text, m_X, m_Y);
        m_Renderer.FillText(m_Text, m_X, m_Y);
    }
}
