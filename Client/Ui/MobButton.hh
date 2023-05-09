#pragma once

#include <cstdint>

#include <Client/Ui/Button.hh>
#include <Client/Util/Lerp.hh>

namespace app::ui
{
    class MobButton : public Button
    {
    public:
        uint32_t m_Position;
        uint32_t m_Id = 0;
        uint32_t m_Rarity = 0;
        
        MobButton(Renderer &, float, uint32_t, uint32_t);

        void Render();
    };
}