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
        
        Container(Renderer &);

        virtual void Render() override;
    };
}