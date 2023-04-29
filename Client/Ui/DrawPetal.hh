#pragma once

#include <Client/Renderer.hh>

namespace app::ui
{
    void DrawPetal(Renderer *, uint32_t);
    void DrawPetal(Renderer *, uint32_t, uint32_t);
    void DrawPetalWithBackground(Renderer *, uint32_t, uint32_t);
}