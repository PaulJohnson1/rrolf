#pragma once

#include <string>

#include <Client/Ui/Element.hh>

namespace app::ui
{
    class Text : public Element
    {
    public:
        std::string m_Text;
        float m_TextSize = 100.0f;

        Text(Renderer &);

        virtual ~Text();

        virtual void Render() const;
    };
}
