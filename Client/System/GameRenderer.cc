#include <Client/System/GameRenderer.hh>

#include <cmath>
#include <iostream>

#include <Client/Renderer.hh>
#include <Client/Socket.hh>
#include <Client/Simulation.hh>
#include <Client/Ui/Text.hh>
#include <Client/Ui/Button.hh>

#include <BinaryCoder/BinaryCoder.hh>
#include <BinaryCoder/NativeTypes.hh>

namespace app::system
{

    GameRenderer::GameRenderer(Simulation &simulation, Renderer *renderer)
        : m_Simulation(simulation),
          m_Renderer(renderer)
    {
    }

    void GameRenderer::Tick()
    {
        Guard g(m_Renderer);
        m_Renderer->ResetTransform();
        m_Renderer->SetFill(0xff000000);
        m_Renderer->FillRect(0, 0, m_Renderer->m_Width, m_Renderer->m_Height);
        component::PlayerInfo &playerInfo = m_Simulation.Get<component::PlayerInfo>(m_Simulation.m_PlayerInfo);
        m_Renderer->Translate(m_Renderer->m_Width / 2, m_Renderer->m_Height / 2);
        m_Renderer->Scale(playerInfo.m_Fov * m_Renderer->m_WindowScale, playerInfo.m_Fov * m_Renderer->m_WindowScale);
        m_Renderer->Translate(-playerInfo.m_CameraX, -playerInfo.m_CameraY);
        component::ArenaInfo &arena = m_Simulation.Get<component::ArenaInfo>(0);
        arena.Render(m_Renderer);
        m_Simulation.ForEachEntity([&](Entity entity)
                                   {
            if (m_Simulation.HasComponent<component::Drop>(entity))
                m_Simulation.Get<component::Drop>(entity).Render(m_Renderer); });
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
            if (m_Simulation.HasComponent<component::Petal>(entity))
                    m_Simulation.Get<component::Petal>(entity).Render(m_Renderer); });
        m_Simulation.ForEachEntity([&](Entity entity)
                                   {
            if (m_Simulation.HasComponent<component::Flower>(entity))
                m_Simulation.Get<component::Flower>(entity).Render(m_Renderer); });
    }

    void GameRenderer::PostTick()
    {
    }
}
