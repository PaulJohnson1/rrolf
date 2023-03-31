#include <Client/System/GameRenderer.hh>

#include <cmath>
#include <iostream>

#include <Client/Renderer.hh>
#include <Client/Simulation.hh>

#include <Client/Ui/Text.hh>
#include <Client/Ui/Button.hh>

#include <BinaryCoder/BinaryCoder.hh>
#include <BinaryCoder/NativeTypes.hh>

namespace app::system
{
    DeathScreen::DeathScreen(GameRenderer &gameRenderer)
        : ui::Element(*gameRenderer.m_Renderer),
          m_GameRenderer(gameRenderer),
          m_DeathLabel(new ui::Text(*gameRenderer.m_Renderer)),
          m_RespawnButtonTextLabel(new ui::Text(*gameRenderer.m_Renderer)),
          m_RespawnButton(new ui::Button(*gameRenderer.m_Renderer))
    {
        m_DeathLabel->m_Text = "You died";
        m_RespawnButtonTextLabel->m_Text = "Respawn";
        m_DeathLabel->m_TextSize = 60;
        m_RespawnButtonTextLabel->m_TextSize = 20;

        m_RespawnButton->m_OnMouseOver = [&]()
        {
            std::cout << "button is hovered\n";
        };
        m_RespawnButton->m_OnMouseDown = [&]()
        {
            m_RespawnButton->m_Clicked = true;
            std::cout << "button is pressed down\n";
        };
        m_RespawnButton->m_OnMouseUp = [&]()
        {
            m_RespawnButton->m_Clicked = false;
            std::cout << "button is pressed up\nrespawning\n";
            static uint8_t outgoingInputPacket[20];
            bc::BinaryCoder coder{outgoingInputPacket};
            coder.Write<bc::Uint8>(0);
            m_GameRenderer->m_Simulation->m_Socket->SendPacket(coder.Data(), coder.At());;
        };
    }

    DeathScreen::~DeathScreen()
    {
    }

    void DeathScreen::Render() const
    {
        m_DeathLabel->m_X = m_Renderer.m_Width / 2;
        m_DeathLabel->m_Y = m_Renderer.m_Height / 2 - 120;
        m_RespawnButtonTextLabel->m_X = m_Renderer.m_Width / 2;
        m_RespawnButtonTextLabel->m_Y = m_Renderer.m_Height / 2 + 120;
        m_RespawnButton->m_X = m_Renderer.m_Width / 2;
        m_RespawnButton->m_Y = m_Renderer.m_Height / 2;
        m_RespawnButton->m_Width = 200;
        m_RespawnButton->m_Height = 100;
        m_DeathLabel->Render();
        m_RespawnButtonTextLabel->Render();
        if (m_RespawnButton->m_Showing && m_RespawnButton->MouseTouching())
        {
            switch (m_Renderer.m_MouseState)
            {
            case 0:
                if (m_RespawnButton->m_Clicked)
                    m_RespawnButton->m_OnMouseUp();
                break;
            case 1:
                m_RespawnButton->m_OnMouseDown();
                break;
            case 2:
                m_RespawnButton->m_OnMouseOver();
                break;
            default:
                break;
            }
        }
        m_RespawnButton->Render();
    }

    GameRenderer::GameRenderer(Simulation &simulation, Renderer *renderer)
        : m_Simulation(simulation),
          m_Renderer(renderer),
          m_DeathScreen(*this)
    {
        m_Renderer->m_UiElements.push_back(&m_DeathScreen);
    }

    void GameRenderer::Tick()
    {
        Guard g(m_Renderer);
        if (m_Simulation.Get<component::PlayerInfo>(m_Simulation.m_PlayerInfo).m_HasPlayer)
        {
            m_DeathScreen.m_Showing = false;
            component::PlayerInfo &playerInfo = m_Simulation.Get<component::PlayerInfo>(m_Simulation.m_PlayerInfo);
            m_Renderer->Translate(m_Renderer->m_Width / 2, m_Renderer->m_Height / 2);
            m_Renderer->Scale(playerInfo.m_Fov, playerInfo.m_Fov);
            m_Renderer->Translate(-playerInfo.m_CameraX, -playerInfo.m_CameraY);
            component::ArenaInfo &arena = m_Simulation.Get<component::ArenaInfo>(0);
            arena.Render(m_Renderer);
            m_Simulation.ForEachEntity([&](Entity entity)
                                       {
                if (m_Simulation.HasComponent<component::Life>(entity))
                    m_Simulation.Get<component::Life>(entity).Render(m_Renderer); });
            m_Simulation.ForEachEntity([&](Entity entity)
                                       {
                if (m_Simulation.HasComponent<component::Mob>(entity))
                    m_Simulation.Get<component::Mob>(entity).Render(m_Renderer); });
            m_Simulation.ForEachEntity([&](Entity entity)
                                       {
                if (m_Simulation.HasComponent<component::Flower>(entity))
                    m_Simulation.Get<component::Flower>(entity).Render(m_Renderer); });
        }
        else
        {
            // m_Renderer->SetFill(0xfff0f000);
            // m_Renderer->FillRect(0, 0, m_Renderer->m_Width, m_Renderer->m_Height);
            m_DeathScreen.m_Showing = true;
        }
    }

    void GameRenderer::PostTick()
    {
    }
}
