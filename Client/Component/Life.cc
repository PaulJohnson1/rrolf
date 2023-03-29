#include <Client/Component/Life.hh>
#include <Client/Renderer.hh>
#include <Client/Simulation.hh>

#include <BinaryCoder/BinaryCoder.hh>
#include <BinaryCoder/NativeTypes.hh>

namespace app::component
{
    Life::Life(Entity parent)
        : m_Parent(parent)
    {
    }

    void Life::UpdateFromBinary(bc::BinaryCoder &coder)
    {
        uint32_t updatedFields = coder.Read<bc::VarUint>();

        if (updatedFields & 1)
            m_Health = coder.Read<bc::Float32>();
        if (updatedFields & 2)
            m_MaxHealth = coder.Read<bc::Float32>();
        if (updatedFields & 4)
            m_Damage = coder.Read<bc::Float32>();
    }
    void Life::Render(Renderer *ctx)
    {
        Guard g(ctx);
        component::Physical physical = ctx->m_Simulation.Get<component::Physical>(m_Parent);
        ctx->Translate(physical.m_X, physical.m_Y);
        //draw hp
        ctx->SetLineCap(Renderer::LineCap::Round);
        ctx->SetStroke(0xff222222);
        ctx->SetLineWidth(7);
        ctx->BeginPath();
        ctx->MoveTo(-40, physical.m_Radius + 30);
        ctx->LineTo(40, physical.m_Radius + 30);
        ctx->Stroke();
        ctx->SetStroke(0xff75dd34);
        ctx->SetLineWidth(5);
        ctx->BeginPath();
        ctx->MoveTo(-40, physical.m_Radius + 30);
        ctx->LineTo(-40 + 80 * m_Health / m_MaxHealth, physical.m_Radius + 30);
        ctx->Stroke();        
    }
}
