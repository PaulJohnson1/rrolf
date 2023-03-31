#include <Client/System/GameRenderer.hh>

#include <cmath>
#include <iostream>

#include <Client/Renderer.hh>
#include <Client/Simulation.hh>

namespace app::system
{
    GameRenderer::GameRenderer(Simulation &simulation)
        : m_Simulation(simulation)
    {
    }

    void GameRenderer::Tick(app::Renderer *ctx)
    {
        Guard g(ctx);
        if (m_Simulation.Get<component::PlayerInfo>(m_Simulation.m_PlayerInfo).m_HasPlayer)
        {    // stuff
            component::PlayerInfo &playerInfo = m_Simulation.Get<component::PlayerInfo>(m_Simulation.m_PlayerInfo);
            ctx->Translate(ctx->m_Width / 2, ctx->m_Height / 2);
            ctx->Scale(playerInfo.m_Fov, playerInfo.m_Fov);
            ctx->Translate(-playerInfo.m_CameraX, -playerInfo.m_CameraY);
            component::ArenaInfo &arena = m_Simulation.Get<component::ArenaInfo>(0);
            arena.Render(ctx);
            m_Simulation.ForEachEntity([&](Entity entity) {
                if (m_Simulation.HasComponent<component::Life>(entity))
                    m_Simulation.Get<component::Life>(entity).Render(ctx);
            });
            m_Simulation.ForEachEntity([&](Entity entity) {
                if (m_Simulation.HasComponent<component::Mob>(entity))
                    m_Simulation.Get<component::Mob>(entity).Render(ctx);
            });
            m_Simulation.ForEachEntity([&](Entity entity) {
                if (m_Simulation.HasComponent<component::Flower>(entity))
                    m_Simulation.Get<component::Flower>(entity).Render(ctx);
            });
        }
        else 
        {
            // we need some Button class
            // we need a `Ui` directory for all the classes
            // such as buttons and text input fields
            // and then a ui components vector for all the components rendered
            // we will need a base UiElement class that has a Render function on it ok is ui component in /component dir or ui dir

            ctx->SetFill(0xfff0f000);
            ctx->FillRect(0, 0, ctx->m_Width, ctx->m_Height);
        }
    }

    void GameRenderer::PostTick()
    {
    }
}
