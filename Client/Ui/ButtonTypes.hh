#pragma once

#include <cstdint>

#include <Client/Ui/Element.hh>
#include <Client/Ui/DynamicButton.hh>
#include <Client/Ui/LabeledButton.hh>

namespace app
{
    class Renderer;
};

namespace app::ui
{
    LabeledButton *CreateRespawnButton(Renderer *);
    DynamicButton *CreateLoadoutButton(Renderer *, int32_t);
    DynamicButton *CreateSecondaryButton(Renderer *, int32_t);
}