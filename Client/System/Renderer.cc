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
        app::Renderer::ContextLock lock0 = ctx->AutoSaveRestore();
        ctx->Translate(ctx->m_Width / 2, ctx->m_Height / 2);
        ctx->Scale(m_Simulation.m_Camera.m_Fov, m_Simulation.m_Camera.m_Fov);
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
            app::Renderer::ContextLock lock1 = ctx->AutoSaveRestore();
            ctx->Translate(physical.m_X, physical.m_Y);
            app::Renderer::Paint paint;
            // draw stroke
            paint.m_Color = 0xffcfbb50;
            ctx->DrawCircle(0, 0, physical.m_Radius + 1.5, paint);
            // draw fill
            paint.m_Color = 0xffffe763;
            ctx->DrawCircle(0, 0, physical.m_Radius - 1.5, paint);
            // draw eye outlines
            paint.m_Color = 0xff222222;
            ctx->Scale(physical.m_Radius / 25,physical.m_Radius / 25);
            {
                app::Renderer::ContextLock lock2 = ctx->AutoSaveRestore();
                {
                    app::Renderer::ContextLock lock3 = ctx->AutoSaveRestore();
                    ctx->Scale(1, 2);
                    ctx->DrawCircle(-7, -2.5, 3, paint);
                    app::Renderer::Path eye1Path;
                    eye1Path.Arc(-7, -2.5, 3, 0, M_PI_2);
                    ctx->ClipPath(eye1Path);
                    ctx->Scale(1, 0.5f);
                    paint.m_Color = 0xffffffff;
                    ctx->DrawCircle(-5.5, -2.5, 2, paint);
                }
                paint.m_Color = 0xff222222;
                {
                    app::Renderer::ContextLock lock4 = ctx->AutoSaveRestore();
                    ctx->Scale(1, 2);
                    ctx->DrawCircle(7, -2.5, 3, paint);
                }
            }
            // draw mouth
            app::Renderer::Path mouth = {};
            mouth.MoveTo(-6, 10);
            mouth.QuadTo(0, 15, 6, 10);
            paint.m_Style = app::Renderer::Paint::Style::Stroke;
            paint.m_Cap = app::Renderer::Paint::Cap::Round;
            paint.m_StrokeWidth = 1.5; //3.0f / 2
            ctx->DrawPath(mouth, paint);
        });
    }

    void Renderer::PostTick()
    {
    }
}