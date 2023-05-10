#pragma once

#include <vector>

#include <Client/Ui/Element.hh>

namespace app::ui
{
    class Container : public Element
    {
    public:
        struct UiTemplate
        {
            bool m_IsHorizontal = true;
            float m_InnerSpacing = 0.0f;
            float m_OuterSpacing = 0.0f;
        };
        std::vector<Element *> m_Elements;
        bool m_HasBackground = false;
        float m_Padding = 0;

        UiTemplate m_Template;
        
        Container(Renderer &);

        virtual void Render() override;
        virtual void Idle() override;
    };
}