#pragma once

#include <cstdint>

#include <Client/Ui/Element.hh>
#include <Client/Ui/MobButton.hh>
#include <Client/Ui/LabeledButton.hh>
#include <Client/Ui/PetalButton.hh>

namespace app
{
    class Renderer;
};

namespace app::ui
{
    LabeledButton *CreateRespawnButton(Renderer *);
    PetalButton *CreateLoadoutButton(Renderer *, int32_t);
    PetalButton *CreateSecondaryButton(Renderer *, int32_t);
    MobButton *CreateMobIcon(Renderer *, uint32_t, uint32_t);
}