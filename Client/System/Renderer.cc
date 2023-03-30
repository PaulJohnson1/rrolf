#include <Client/System/Renderer.hh>

#include <cmath>
#include <iostream>

#include <Client/Renderer.hh>
#include <Client/Simulation.hh>

namespace app::system
{
    Renderer::Renderer(Simulation &simulation)
        : m_Simulation(simulation)
    {
    }

    void Renderer::Tick(app::Renderer *ctx)
    {
        Guard g(ctx);
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

    void Renderer::PostTick()
    {
    }
}
