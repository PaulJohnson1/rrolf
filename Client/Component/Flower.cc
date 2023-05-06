#include <Client/Component/Flower.hh>

#include <BinaryCoder/BinaryCoder.hh>
#include <BinaryCoder/NativeTypes.hh>

#include <Client/Simulation.hh>
#include <Client/Renderer.hh>

namespace app::component
{
    Flower::Flower(Entity parent, Simulation *simulation)
        : m_Parent(parent),
          m_Simulation(simulation)
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
        Physical physical = m_Simulation->Get<Physical>(m_Parent);

        ctx->SetGlobalAlpha(1 - 0.2 * physical.m_ClientDeletionTick);

        ctx->Translate(physical.m_X, physical.m_Y);

        ctx->Scale(1 + physical.m_ClientDeletionTick * 0.1);
        // draw stroke
        ctx->BeginPath();
        ctx->Arc(0, 0, physical.m_Radius + 1.5);
        ctx->SetFill(0xffcfbb50);
        ctx->Fill();
        // draw fill
        ctx->BeginPath();
        ctx->Arc(0, 0, physical.m_Radius - 1.5);
        ctx->SetFill(0xffffe763);
        ctx->Fill();
        ctx->Scale(physical.m_Radius / 25);
        {
            Guard g(ctx);
            ctx->SetFill(0xff222222);
            ctx->Scale(1, 2);
            ctx->BeginPath();
            ctx->Arc(-7, -2.5, 3.25);
            ctx->Fill();
            ctx->BeginPath();
            ctx->Arc(-7, -2.5, 3);
            ctx->Clip();
            ctx->Scale(1, 0.5);
            ctx->SetFill(0xffffffff);
            ctx->BeginPath();
            ctx->Arc(-7 + m_EyeX, -5 + m_EyeY, 3);
            ctx->Fill();
        }
        {
            Guard g(ctx);
            ctx->SetFill(0xff222222);
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
        // draw mouth
        ctx->SetStroke(0xff222222);
        ctx->SetLineWidth(1.5);
        ctx->BeginPath();
        ctx->MoveTo(-6, 10);
        ctx->QuadraticCurveTo(0, 15, 6, 10);
        ctx->Stroke();
    }
}
