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
        ctx->Clear();
        ctx->Save();
        ctx->Translate(ctx->m_Width / 2, ctx->m_Height / 2);
        //ctx->Scale(m_Simulation.m_Camera.m_Fov, m_Simulation.m_Camera.m_Fov);
        ctx->Translate(-m_Simulation.m_Camera.m_X, -m_Simulation.m_Camera.m_Y);
        component::ArenaInfo &arena = m_Simulation.Get<component::ArenaInfo>(0);
        app::Renderer::Paint mapPaint;
        mapPaint.m_Color = 0xff51983c;
        ctx->DrawCircle(0, 0, arena.m_MapSize, mapPaint);
        m_Simulation.ForEachEntity([&](Entity entity)
        {
            if (!m_Simulation.GetOptional<component::Render>(entity))
                return;
            component::Physical physical = m_Simulation.Get<component::Physical>(entity);
            component::Render renderInfo = m_Simulation.Get<component::Render>(entity);
            ctx->Save();
            ctx->Translate(physical.m_X, physical.m_Y);
            app::Renderer::Paint paint;
            paint.m_Color = 0xffcfbb50;

            ctx->DrawCircle(0, 0, physical.m_Radius + 1.5, paint);

            paint.m_Color = 0xffffe763;

            ctx->DrawCircle(0, 0, physical.m_Radius - 1.5, paint);
            paint.m_Color = 0xff000000;
            ctx->Scale(physical.m_Radius,2 * physical.m_Radius);
            ctx->Translate(0,-0.1);
            ctx->DrawCircle(-0.28, 0, 0.12, paint);
            ctx->DrawCircle(0.28, 0, 0.12, paint);
            ctx->Scale(1, 0.5);
            // 10 down 0 0 0 5 6 0 QCto
            ctx->Restore();
        });
        ctx->Restore();
    }

    void Renderer::PostTick()
    {
    }
}
