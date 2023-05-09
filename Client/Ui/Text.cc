#include <Client/Ui/Text.hh>

#include <string>

#include <Client/Renderer.hh>

namespace app::ui
{
    Text::Text(Renderer &ctx, std::string const &text, uint32_t fill, float size)
        : Element(ctx, 0, size),
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
        PreRender();

        m_Renderer.Scale(m_Renderer.m_WindowScale);
        m_Renderer.SetTextAlign(Renderer::TextAlign::Center);
        m_Renderer.SetTextBaseline(Renderer::TextBaseline::Middle);
        m_Renderer.SetTextSize(m_TextSize);
        m_Renderer.SetLineWidth(m_TextSize * 0.12);
        m_Renderer.SetStroke(m_Stroke);
        m_Renderer.SetFill(m_Fill);
        m_Renderer.StrokeText(m_Text, 0, 0);
        m_Renderer.FillText(m_Text, 0, 0);
    }
}
