#include <System/Renderer.hh>

#include <cmath>
#include <iostream>

#include <Renderer.hh>
#include <Simulation.hh>

namespace app::system
{
    Renderer::Renderer(Simulation &simulation)
        : m_Simulation(simulation)
    {
    }

    // lucky this isn't c otherwise this would be a name collision
    void Renderer::Tick(app::Renderer *ctx)
    {
        ctx->Clear();
        ctx->Save();
        ctx->Translate(ctx->m_Width / 2, ctx->m_Height / 2);
        ctx->Scale(m_Simulation.m_Camera.m_Fov, m_Simulation.m_Camera.m_Fov);
        ctx->Translate(-m_Simulation.m_Camera.m_X, -m_Simulation.m_Camera.m_Y);
        m_Simulation.ForEachEntity([&](Entity entity)
        {
            if (!m_Simulation.GetOptional<component::Render>(entity))
                return;
            component::Physical physical = m_Simulation.Get<component::Physical>(entity);

            app::Renderer::Paint paint;
            paint.m_AntiAliased = true;
            paint.m_Red = 0xff;

            ctx->DrawCircle(physical.m_X, physical.m_Y, physical.m_Radius, paint);
        });
        ctx->Restore();
    }

    void Renderer::PostTick()
    {
    }
}
