#include <Client/Component/Drop.hh>

#include <cmath>

#include <BinaryCoder/BinaryCoder.hh>
#include <BinaryCoder/NativeTypes.hh>

#include <Client/Renderer.hh>
#include <Client/Simulation.hh>
#include <Shared/StaticData.hh>
#include <Client/Simulation.hh>

#include <Client/Ui/RenderFunctions.hh>

namespace app::component
{
    Drop::Drop(Entity parent, Simulation *simulation)
        : m_Parent(parent), m_Simulation(simulation)
    {
    }

    void Drop::UpdateFromBinary(bc::BinaryCoder &coder)
    {
        uint32_t updatedFields = coder.Read<bc::VarUint>();

        if (updatedFields & 1)
            m_Id = coder.Read<bc::VarUint>();
        if (updatedFields & 2)
            m_Rarity = coder.Read<bc::VarUint>();
        if (updatedFields & 4)
            m_PickedUp = coder.Read<bc::Uint8>();  
    }

    void Drop::Render(Renderer *ctx)
    {
        Physical physical = m_Simulation->Get<Physical>(m_Parent);
        Basic basic = m_Simulation->Get<Basic>(m_Parent);
        Guard g(ctx);
        ctx->Translate(physical.m_X, physical.m_Y);
        float radius = physical.m_Radius * (1 - physical.m_ClientDeletionTick * 0.2);
        ctx->Scale(radius / 25, radius / 25);
        ctx->Rotate(radius + 0.1);
        float sc = 0.05 * std::sin((m_Simulation->GetTime() - basic.m_CreationTime) * 0.01) + 1;
        ctx->Scale(sc);
        ui::DrawPetalWithBackground(ctx, m_Id, m_Rarity);
    }
}