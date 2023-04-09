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
        float m_R = 0.0f;

        Button(Renderer &, float, float);
        ~Button();
        bool MouseTouching();
        void ButtonAction();
        virtual void Render() override;
        std::function<void()> m_OnMouseOver;
        std::function<void()> m_OnMouseDown;
        std::function<void()> m_OnMouseMove;
        std::function<void()> m_OnMouseUp;
    };
}