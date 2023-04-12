#pragma once

#include <string>
#include <cstdint>

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
        Renderer::TextBaseline m_TextBaseline;

        Text(Renderer &, std::string const &, uint32_t, float);

        virtual void Render();
    };
}
