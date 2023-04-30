#include <Client/Component/Petal.hh>

#include <BinaryCoder/BinaryCoder.hh>
#include <BinaryCoder/NativeTypes.hh>

#include <Client/Simulation.hh>
#include <Client/Renderer.hh>
#include <Client/Ui/DrawPetal.hh>

namespace app::component
{
    Petal::Petal(Entity parent, Simulation *simulation)
        : m_Parent(parent),
          m_Simulation(simulation),
          m_RandomRotation(rand() * M_PI * 2 / RAND_MAX)
    {
    }

    void Petal::UpdateFromBinary(bc::BinaryCoder &coder)
    {
        uint32_t updatedFields = coder.Read<bc::VarUint>();

        if (updatedFields & 1)
            m_Id = coder.Read<bc::VarUint>();
        if (updatedFields & 2)
            m_Rarity = coder.Read<bc::VarUint>();
    }

    void Petal::Render(Renderer *ctx)
    {
        Guard g(ctx);
        component::Physical physical = m_Simulation->Get<component::Physical>(m_Parent);
        ctx->Translate(physical.m_X, physical.m_Y);
        if (!m_Simulation->HasComponent<component::Projectile>(m_Parent))
        {   
            component::Basic basic = m_Simulation->Get<component::Basic>(m_Parent);
            ctx->Rotate((m_Simulation->GetTime() - basic.m_CreationTime) / 1000 + m_RandomRotation);
        }
        else
            ctx->Rotate(physical.m_Angle);
        ui::DrawPetal(ctx, m_Id);
    }
}
