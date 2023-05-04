#pragma once

#include <Client/Renderer.hh>

namespace app::ui
{
    uint32_t DamageColor(uint32_t, uint32_t);
    void DrawPetal(Renderer *, uint32_t, uint32_t);
    void DrawStaticPetal(Renderer *, uint32_t, uint32_t);
    void DrawPetalWithBackground(Renderer *, uint32_t, uint32_t);
    void DrawLoadoutPetal(Renderer *, uint32_t, uint32_t, float);

    void DrawMob(Renderer *, uint32_t, uint32_t, float);
}