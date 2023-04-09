#pragma once

#include <Client/Ui/Button.hh>
#include <Client/Ui/Element.hh>

#include <string>

namespace app::ui
{
    class LabeledButton: public Button
    {
    public:
        std::string m_Label = "@@UNINITIALIZED STRING@@";
        float m_TextSize;
        LabeledButton(Renderer &, float, float, std::string const &, float);
        ~LabeledButton();
        virtual void Render() override;
    };
}