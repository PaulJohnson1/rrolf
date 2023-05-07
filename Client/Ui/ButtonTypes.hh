#pragma once

#include <cstdint>

#include <Client/Ui/Element.hh>
#include <Client/Ui/PetalButton.hh>
#include <Client/Ui/LabeledButton.hh>

namespace app
{
    class Renderer;
};

namespace app::ui
{
    LabeledButton *CreateRespawnButton(Renderer *);
    PetalButton *CreateLoadoutButton(Renderer *, int32_t);
    PetalButton *CreateSecondaryButton(Renderer *, int32_t);
}