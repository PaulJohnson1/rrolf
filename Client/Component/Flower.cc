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
        Guard lock = ctx->AutoSaveRestore();
        component::Physical physical = ctx->m_Simulation.Get<component::Physical>(m_Parent);
        ctx->Translate(physical.m_X, physical.m_Y);
        // draw stroke
        ctx->SetFill(0xffcfbb50);
        ctx->BeginPath();
        ctx->Arc(0, 0, physical.m_Radius + 1.5);
        ctx->Fill();
        // draw fill
        ctx->SetFill(0xffffe763);
        ctx->BeginPath();
        ctx->Arc(0, 0, physical.m_Radius - 1.5);
        ctx->Fill();
        ctx->SetFill(0xff222222);
        ctx->Scale(physical.m_Radius / 25, physical.m_Radius / 25);
        /*
        {
            Renderer::ContextLock lock2 = ctx->AutoSaveRestore();
            {
                Renderer::ContextLock lock3 = ctx->AutoSaveRestore();
                ctx->Scale(1, 2);
                ctx->BeginPath();
                ctx->Arc(-7, -2.5, 3.25);
                Renderer::Path eyePath;
                eyePath.MoveTo(-4,-2.5);
                eyePath.Circle(-7, -2.5, 3);
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
                eyePath.Circle(7, -2.5, 3);
                ctx->ClipPath(eyePath);
                ctx->Scale(1, 0.5f);
                paint.m_Color = 0xffffffff;
                ctx->DrawCircle(7 + m_EyeX, -5 + m_EyeY, 3, paint);
            }
        }
        // draw mouth
        */
        ctx->SetStroke(0xff222222);
        ctx->SetLineWidth(1.5);
        ctx->BeginPath();
        ctx->MoveTo(-6, 10);
        ctx->QuadraticCurveTo(0, 15, 6, 10);
        ctx->Stroke();
    }
}
