#pragma once

#include <functional>

#include <Client/Ui/Element.hh>

namespace app
{
    class Renderer;
}

namespace app::ui
{
    class Button : public ui::Element
    {
    public:
        bool m_Clicked = false;
        float m_Width = 1.0f;
        float m_Height = 1.0f;
        float m_R = 5.0f;

        Button(Renderer &);
        ~Button();
        bool MouseTouching();
        virtual void Render() const;
        std::function<void()> m_OnMouseOver;
        std::function<void()> m_OnMouseDown;
        std::function<void()> m_OnMouseUp;
    };
}