#pragma once

#include <cstdint>

#include <Client/Ui/Button.hh>
#include <Client/Util/Lerp.hh>

namespace app::ui
{
    class DynamicButton : public Button
    {
    public:
        uint32_t m_Position;
        bool m_UseGlobalPosition = false;
        Lerp<float> m_GlobalX = Lerp<float>(0.0f);
        Lerp<float> m_GlobalY = Lerp<float>(0.0f);
        
        DynamicButton(Renderer &, float, uint32_t);

        void Render();
    };
}