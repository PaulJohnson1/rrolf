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
        if (ctx->m_Simulation.GetOptional<component::Flower>(m_Parent)) {
            Renderer::ContextLock lock = ctx->AutoSaveRestore();
            component::Physical physical = ctx->m_Simulation.Get<component::Physical>(m_Parent);
            Renderer::Paint paint;
            ctx->Translate(physical.m_X, physical.m_Y);
            //draw hp
            paint.m_Cap = Renderer::Paint::Cap::Round;
            paint.m_Style = Renderer::Paint::Style::Stroke;
            paint.m_Color = 0xff222222;
            paint.m_StrokeWidth = 7;
            ctx->DrawLine(-40, physical.m_Radius + 30, 40, physical.m_Radius + 30, paint);
            paint.m_Color = 0xff75dd34;
            paint.m_StrokeWidth = 5;
            ctx->DrawLine(-40, physical.m_Radius + 30, -40 + 80.0f * m_Health / m_MaxHealth, physical.m_Radius + 30, paint);
        }
    }
}
