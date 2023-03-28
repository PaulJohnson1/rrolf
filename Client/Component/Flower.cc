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
        Guard g(ctx);
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
        ctx->Scale(physical.m_Radius / 25, physical.m_Radius / 25);
        {
            Guard g(ctx);
            {
                ctx->SetFill(0xff222222);
                Guard g(ctx);
                ctx->Scale(1, 2);
                ctx->BeginPath();
                ctx->Arc(-7, -2.5, 3.25);
                ctx->Fill();
                ctx->BeginPath();
                ctx->Arc(-7, -2.5, 3);
                ctx->Clip();
                ctx->Scale(1, 0.5f);
                ctx->SetFill(0xffffffff);
                ctx->BeginPath();
                ctx->Arc(-7 + m_EyeX, -5 + m_EyeY, 3);
                ctx->Fill();
            }
            {
                ctx->SetFill(0xff222222);
                Guard g(ctx);
                ctx->Scale(1, 2);
                ctx->BeginPath();
                ctx->Arc(7, -2.5, 3.25);
                ctx->Fill();
                ctx->BeginPath();
                ctx->Arc(7, -2.5, 3);
                ctx->Clip();
                ctx->Scale(1, 0.5f);
                ctx->SetFill(0xffffffff);
                ctx->BeginPath();
                ctx->Arc(7 + m_EyeX, -5 + m_EyeY, 3);
                ctx->Fill();
            }
        }
        // draw mouth
        ctx->SetStroke(0xff222222);
        ctx->SetLineWidth(1.5);
        ctx->BeginPath();
        ctx->MoveTo(-6, 10);
        ctx->QuadraticCurveTo(0, 15, 6, 10);
        ctx->Stroke();
    }
}
