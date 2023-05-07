#pragma once

#include <cstdint>

#include <Client/Ui/Button.hh>
#include <Client/Util/Lerp.hh>

namespace app::ui
{
    class PetalButton : public Button
    {
    public:
        bool m_UseGlobalPosition = false;
        uint32_t m_Position;
        float m_ActualWidth = 0.0f;
        Lerp<float> m_GlobalX = Lerp<float>(0.0f);
        Lerp<float> m_GlobalY = Lerp<float>(0.0f);
        Lerp<float> m_LerpWidth = Lerp<float>(0.0f);
        uint32_t m_PrevId = 0;
        uint32_t m_PrevRarity = 0;
        
        PetalButton(Renderer &, float, uint32_t);

        void Render();
    };
}