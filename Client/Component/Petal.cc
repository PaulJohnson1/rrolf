#include <Client/Component/Petal.hh>

#include <iostream>

#include <BinaryCoder/BinaryCoder.hh>
#include <BinaryCoder/NativeTypes.hh>

#include <Client/Simulation.hh>
#include <Client/Renderer.hh>

namespace app::component
{
    Petal::Petal(Entity parent, Simulation *simulation)
        : m_Parent(parent),
          m_Simulation(simulation)
    {
        std::cout << "petal ctor\n";
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
        switch (m_Id)
        {
        case 1:
            ctx->SetFill(0xffcfcfcf);
            ctx->BeginPath();
            ctx->Arc(0, 0, 11.5);
            ctx->Fill();
            ctx->SetFill(0xffffffff);
            ctx->BeginPath();
            ctx->Arc(0, 0, 8.5);
            ctx->Fill();
            break;
        default:
            ctx->SetFill(0xffcfcfcf);
            ctx->BeginPath();
            ctx->Arc(0, 0, 110.5);
            ctx->Fill();
            ctx->SetFill(0xffffffff);
            ctx->BeginPath();
            ctx->Arc(0, 0, 8.5);
            ctx->Fill();
            break;
            break;
        }
    }
}
