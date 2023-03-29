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

    // lucky this isn't c otherwise this would be a name collision
    void Renderer::Tick(app::Renderer *ctx)
    {
        // use bound checking for this one
        if (!m_Simulation.GetOptional<component::ArenaInfo>(0))
            return;
        //ctx->Clear();
        Guard g(ctx);
        ctx->Translate(ctx->m_Width / 2, ctx->m_Height / 2);
        ctx->Scale(ctx->m_Simulation.m_Camera.m_Fov, ctx->m_Simulation.m_Camera.m_Fov);
        ctx->Translate(-ctx->m_Simulation.m_Camera.m_X, -ctx->m_Simulation.m_Camera.m_Y);
        component::ArenaInfo &arena = m_Simulation.Get<component::ArenaInfo>(0);
        arena.Render(ctx);
        m_Simulation.ForEachEntity([&](Entity entity) {
            if (m_Simulation.GetOptional<component::Life>(entity))
                m_Simulation.Get<component::Life>(entity).Render(ctx);
        });
        m_Simulation.ForEachEntity([&](Entity entity) {
            if (m_Simulation.GetOptional<component::Flower>(entity))
                m_Simulation.Get<component::Flower>(entity).Render(ctx);
        });
    }

    void Renderer::PostTick()
    {
    }
}
