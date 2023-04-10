#include <Client/Ui/Button.hh>

#include <cassert>
#include <iostream>

#include <Client/Renderer.hh>

#include <cmath>

namespace app::ui
{
    Button::Button(Renderer &ctx, float w, float h)
        : Element(ctx, w, h)
    {
    }

    Button::~Button()
    {
        assert(false);
    }
    bool Button::MouseTouching()
    {
        const float *matrix = m_Renderer.GetTransform();
        return std::abs(g_InputData->m_MouseX - matrix[2]) < m_Width * matrix[0] / 2 && std::abs(g_InputData->m_MouseY - matrix[5]) < m_Height * matrix[4] / 2;
    }
    void Button::ButtonAction()
    {
        if (MouseTouching())
        {
            switch (g_InputData->m_MouseState)
            {
            case 0:
                if (m_Clicked)
                {
                    m_OnMouseUp();
                    m_Clicked = false;
                }
                else
                    m_OnMouseOver();
                break;
            case 1:
                if (!m_Clicked)
                {
                    m_OnMouseDown();
                    m_Clicked = true;
                }
                break;
            case 2:
                m_OnMouseMove();
            default:
                break;
            }
        }
        else if (m_Clicked)
        {
            if (g_InputData->m_MouseState == 2)
                m_OnMouseMove();
            else if (g_InputData->m_MouseState == 0)
            {
                m_OnMouseUp();
                m_Clicked = false;
            }
        }
    }
    void Button::Render()
    {
        Guard g(&m_Renderer);
        m_Renderer.Translate(m_HJustify * m_Container->m_Width / 2, m_VJustify * m_Container->m_Height / 2); //necessary btw
        m_Renderer.Translate(m_X * m_Renderer.m_WindowScale, m_Y * m_Renderer.m_WindowScale);
        m_Renderer.Scale(m_Renderer.m_WindowScale, m_Renderer.m_WindowScale);
        m_Renderer.RoundRect(-m_Width / 2, -m_Height / 2, m_Width, m_Height, m_R);
        m_Renderer.SetFill(m_Fill);
        m_Renderer.SetStroke(m_Stroke);
        m_Renderer.SetLineWidth(m_LineWidth);
        m_Renderer.Stroke();
        m_Renderer.Fill();
        ButtonAction();
    }
}