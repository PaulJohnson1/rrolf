#include <Client/Component/Flower.hh>
#include <Client/Renderer.hh>
#include <Client/Simulation.hh>

#include <BinaryCoder/BinaryCoder.hh>
#include <BinaryCoder/NativeTypes.hh>

namespace app::component
{
    Flower::Flower(Entity parent)
        : m_Parent(parent)
    {
    }

    void Flower::UpdateFromBinary(bc::BinaryCoder &coder)
    {
        uint32_t updatedFields = coder.Read<bc::VarUint>();

        if (updatedFields & 1)
            m_Flags = coder.Read<bc::Uint8>();
        if (updatedFields & 2)
            m_EyeAngle = coder.Read<bc::Float32>();
    }
    void Flower::Render(Renderer *ctx)
    {
        Renderer::ContextLock lock = ctx->AutoSaveRestore();
        component::Physical physical = ctx->m_Simulation.Get<component::Physical>(m_Parent);
        Renderer::Paint paint;
        ctx->Translate(physical.m_X, physical.m_Y);
        // draw stroke
        paint.m_Color = 0xffcfbb50;
        ctx->DrawCircle(0, 0, physical.m_Radius + 1.5, paint);
        // draw fill
        paint.m_Color = 0xffffe763;
        ctx->DrawCircle(0, 0, physical.m_Radius - 1.5, paint);
        paint.m_Color = 0xff222222;
        ctx->Scale(physical.m_Radius / 25,physical.m_Radius / 25);
        {
            Renderer::ContextLock lock2 = ctx->AutoSaveRestore();
            {
                Renderer::ContextLock lock3 = ctx->AutoSaveRestore();
                ctx->Scale(1, 2);
                ctx->DrawCircle(-7, -2.5, 3.25, paint);
                Renderer::Path eyePath;
                eyePath.MoveTo(-4,-2.5);
                eyePath.Arc(-7, -2.5, 3, 0, M_PI * 2);
                ctx->ClipPath(eyePath);
                ctx->Scale(1, 0.5f);
                paint.m_Color = 0xffffffff;
                ctx->DrawCircle(-7 + m_EyeX, -5 + m_EyeY, 3, paint);
            }
            paint.m_Color = 0xff222222;
            {
                Renderer::ContextLock lock4 = ctx->AutoSaveRestore();
                ctx->Scale(1, 2);
                ctx->DrawCircle(7, -2.5, 3.25, paint);
                Renderer::Path eyePath;
                eyePath.MoveTo(10,-2.5);
                eyePath.Arc(7, -2.5, 3, 0, M_PI * 2);
                ctx->ClipPath(eyePath);
                ctx->Scale(1, 0.5f);
                paint.m_Color = 0xffffffff;
                ctx->DrawCircle(7 + m_EyeX, -5 + m_EyeY, 3, paint);
            }
        }
        // draw mouth
        paint.m_Color = 0xff222222;
        Renderer::Path mouth = {};
        mouth.MoveTo(-6, 10);
        mouth.QuadTo(0, 15, 6, 10);
        paint.m_Style = Renderer::Paint::Style::Stroke;
        paint.m_StrokeWidth = 1.5; //3.0f / 2
        ctx->DrawPath(mouth, paint);
    }
}
