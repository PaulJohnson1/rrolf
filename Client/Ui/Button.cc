#include <Client/Ui/Button.hh>

#include <cassert>

#include <Client/Renderer.hh>

#include <cmath>

namespace app::ui
{
    Button::Button(Renderer &ctx)
        : Element(ctx)
    {
    }

    Button::~Button()
    {
        assert(false);
    }

    bool Button::MouseTouching()
    {
        return std::abs(m_Renderer.m_MouseX - m_X) < m_Width / 2 && std::abs(m_Renderer.m_MouseY - m_Y) < m_Height / 2;
    }
    void Button::Render() const
    {
        m_Renderer.RoundRect(m_X - m_Width / 2, m_Y - m_Height / 2, m_Width, m_Height, m_R);
        m_Renderer.SetFill(m_Fill);
        m_Renderer.SetStroke(m_Stroke);
        m_Renderer.SetLineWidth(m_LineWidth);
        m_Renderer.Fill();
        m_Renderer.Stroke();
    }
}