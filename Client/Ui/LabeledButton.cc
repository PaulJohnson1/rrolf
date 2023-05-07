#include <Client/Ui/LabeledButton.hh>

#include <iostream>
#include <string>
#include <cmath>

#include <Client/Renderer.hh>

namespace app::ui
{
    LabeledButton::LabeledButton(Renderer &ctx, float w, float h, std::string const &label, float textSize)
        : Button(ctx, w, h),
          m_Label(label),
          m_TextSize(textSize)
    {
    }

    void LabeledButton::Render()
    {
        Guard g(&m_Renderer);
        m_Renderer.Translate((m_HJustify - 1) * m_Container->m_Width / 2, (m_VJustify - 1) * m_Container->m_Height / 2); // necessary btw
        m_Renderer.Translate(m_X * m_Renderer.m_WindowScale, m_Y * m_Renderer.m_WindowScale);
        m_Renderer.Scale(m_Renderer.m_WindowScale);
        m_Renderer.RoundRect(-m_Width / 2, -m_Height / 2, m_Width, m_Height, m_R);
        m_Renderer.SetFill(m_Fill);
        m_Renderer.SetStroke(m_Stroke);
        m_Renderer.SetLineWidth(m_LineWidth);
        m_Renderer.Stroke();
        m_Renderer.Fill();
        // text
        m_Renderer.SetTextAlign(Renderer::TextAlign::Center);
        m_Renderer.SetTextBaseline(Renderer::TextBaseline::Middle);
        m_Renderer.SetTextSize(m_TextSize);
        m_Renderer.SetLineWidth(m_TextSize * 0.12);
        m_Renderer.SetStroke(0xff000000);
        m_Renderer.SetFill(0xffffffff);
        m_Renderer.StrokeText(m_Label, 0, 0);
        m_Renderer.FillText(m_Label, 0, 0);
        ButtonAction();
    }
}