#pragma once

#include <cstdint>

#include <Client/Ui/Button.hh>
#include <Client/Util/Lerp.hh>

namespace app::ui
{
    class MobButton : public Button
    {
    public:
        bool m_UseGlobalPosition = false;
        uint32_t m_Position;
        Lerp<float> m_LerpWidth = Lerp<float>(0.0f);
        uint32_t m_Id = 0;
        uint32_t m_Rarity = 0;
        
        MobButton(Renderer &, uint32_t, uint32_t);

        void Render();
    };
}