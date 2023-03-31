#pragma once

#include <Client/Ui/Element.hh>

namespace app
{
    class Simulation;
    class Renderer;
    namespace ui
    {
        class Text;
        class Button;
    }
}

namespace app::system
{
    class DeathScreen final : public ui::Element
    {
        ui::Text *m_DeathLabel;
        ui::Text *m_RespawnButtonTextLabel;
        ui::Button *m_RespawnButton;
        class GameRenderer &m_GameRenderer;
    public:
        DeathScreen(class GameRenderer &);
        ~DeathScreen();

        void Render() const override;
    };

    class GameRenderer
    {
    public:
        Simulation &m_Simulation;
        Renderer *m_Renderer;
        DeathScreen m_DeathScreen;

        GameRenderer(Simulation &, Renderer *);

        void Tick();
        void PostTick();
    };
}
