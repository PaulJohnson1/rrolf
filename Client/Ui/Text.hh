#pragma once

#include <string>

#include <Client/Ui/Element.hh>
#include <Client/Renderer.hh>

namespace app::ui
{
    class Text : public Element
    {
    public:
        std::string m_Text = "@@@@UNINITIALIZED STRING@@@@";
        float m_TextSize = 100.0f;
        Renderer::TextAlign m_TextAlign;
        Renderer::TextBaseLine m_TextBaseLine;

        Text(Renderer &);

        virtual ~Text();

        virtual void Render() const;
    };
}
