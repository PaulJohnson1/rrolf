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
            if (!m_Simulation.GetOptional<component::Flower>(entity))
                return;
            component::Physical physical = m_Simulation.Get<component::Physical>(entity);
            component::Render renderInfo = m_Simulation.Get<component::Render>(entity);
            component::Flower flowerInfo = m_Simulation.Get<component::Flower>(entity);
            app::Renderer::ContextLock lock1 = ctx->AutoSaveRestore();
            ctx->Translate(physical.m_X, physical.m_Y);
            app::Renderer::Paint paint;
            // draw stroke
            paint.m_Color = 0xffcfbb50;
            ctx->DrawCircle(0, 0, physical.m_Radius + 1.5, paint);
            // draw fill
            paint.m_Color = 0xffffe763;
            ctx->DrawCircle(0, 0, physical.m_Radius - 1.5, paint);
            // draw hp (separate for each entity type)
            paint.m_Cap = app::Renderer::Paint::Cap::Round;
            paint.m_Style = app::Renderer::Paint::Style::Stroke;
            paint.m_Color = 0xff222222;
            paint.m_StrokeWidth = 7;
            ctx->DrawLine(-40, physical.m_Radius + 30, 40, physical.m_Radius + 30, paint);
            paint.m_Color = 0xff75dd34;
            paint.m_StrokeWidth = 5;
            ctx->DrawLine(-40, physical.m_Radius + 30, 40, physical.m_Radius + 30, paint);
            // draw eye outlines
            paint.m_Style = app::Renderer::Paint::Style::Fill;
            paint.m_Color = 0xff222222;
            ctx->Scale(physical.m_Radius / 25,physical.m_Radius / 25);
            {
                app::Renderer::ContextLock lock2 = ctx->AutoSaveRestore();
                {
                    app::Renderer::ContextLock lock3 = ctx->AutoSaveRestore();
                    ctx->Scale(1, 2);
                    ctx->DrawCircle(-7, -2.5, 3.25, paint);
                    app::Renderer::Path eyePath;
                    eyePath.MoveTo(-4,-2.5);
                    eyePath.Arc(-7, -2.5, 3, 0, M_PI * 2);
                    ctx->ClipPath(eyePath);
                    ctx->Scale(1, 0.5f);
                    paint.m_Color = 0xffffffff;
                    ctx->DrawCircle(-7 + flowerInfo.m_EyeX, -5 + flowerInfo.m_EyeY, 3, paint);
                }
                paint.m_Color = 0xff222222;
                {
                    app::Renderer::ContextLock lock4 = ctx->AutoSaveRestore();
                    ctx->Scale(1, 2);
                    ctx->DrawCircle(7, -2.5, 3.25, paint);
                    app::Renderer::Path eyePath;
                    eyePath.MoveTo(10,-2.5);
                    eyePath.Arc(7, -2.5, 3, 0, M_PI * 2);
                    ctx->ClipPath(eyePath);
                    ctx->Scale(1, 0.5f);
                    paint.m_Color = 0xffffffff;
                    ctx->DrawCircle(7 + flowerInfo.m_EyeX, -5 + flowerInfo.m_EyeY, 3, paint);
                }
            }
            // draw mouth
            paint.m_Color = 0xff222222;
            app::Renderer::Path mouth = {};
            mouth.MoveTo(-6, 10);
            mouth.QuadTo(0, 15, 6, 10);
            paint.m_Style = app::Renderer::Paint::Style::Stroke;
            paint.m_StrokeWidth = 1.5; //3.0f / 2
            ctx->DrawPath(mouth, paint);
        });
    }

    void Renderer::PostTick()
    {
    }
}
