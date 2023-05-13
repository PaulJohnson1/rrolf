#pragma once

#include <vector>

#include <Client/Ui/Element.hh>

namespace app::ui
{
    class Container : public Element
    {
    public:
        std::vector<Element *> m_Elements;
        bool m_HasBackground = false;
        float m_Padding = 0;
        
        Container(Renderer &);

        virtual void Render() override;
    };
}