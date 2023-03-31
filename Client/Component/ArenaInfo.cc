#include <Client/Component/ArenaInfo.hh>

#include <cassert>

#include <BinaryCoder/BinaryCoder.hh>
#include <BinaryCoder/NativeTypes.hh>

#include <Client/Simulation.hh>
#include <Client/Renderer.hh>
#include <Client/Simulation.hh>

namespace app::component
{
    ArenaInfo::ArenaInfo(Entity parent, Simulation *simulation)
        : m_Parent(parent),
          m_Simulation(simulation)
    {
    }

    void ArenaInfo::UpdateFromBinary(bc::BinaryCoder &coder)
    {
        uint32_t updatedFields = coder.Read<bc::VarUint>();

        if (updatedFields & 1)
            m_MapSize = coder.Read<bc::VarUint>();
    }
    void ArenaInfo::Render(Renderer *ctx)
    {
        Guard g(ctx);
        ctx->SetFill(0xff20a464);
        ctx->BeginPath();
        ctx->Arc(0, 0, m_MapSize * 2);
        ctx->Fill();
        assert(m_Simulation); // sometimes it's nullptr somehow
        float alpha = m_Simulation->Get<component::PlayerInfo>(m_Simulation->m_PlayerInfo).m_Fov * 51;
        ctx->SetStroke((uint32_t)(alpha) << 24);
        ctx->SetFill((uint32_t)(alpha) << 24);
        ctx->BeginPath();
        ctx->Arc(0, 0, m_MapSize * 2);
        ctx->Fill();
        ctx->SetFill(0xff20a464);
        ctx->BeginPath();
        ctx->Arc(0, 0, m_MapSize);
        ctx->Fill();
        ctx->SetLineWidth(1);
        ctx->SetStroke((uint32_t)(alpha) << 24);

        /*
        // refactored
        ctx->ResetTransform();
        float fov = m_Simulation->m_Camera.m_Fov;
        ctx->Scale(fov, fov);
        uint32_t lineCountX = ctx->m_Width * (1 / fov) / 50;
        uint32_t lineCountY = ctx->m_
        for (float i = 0; i < lienCountX; i++)
        {
            ctx->BeginPath();
            ctx->MoveTo(i * 50, 0);
            ctx->LineTo(i * 50, )
        }
        */
        int32_t size = (int32_t)(2 * m_MapSize * 0.02); //gg refa
        for (int32_t posX = -size; posX <= size; ++posX)
        {
            ctx->BeginPath();
            ctx->MoveTo(posX * 50, -2 * m_MapSize);
            ctx->LineTo(posX * 50, 2 * m_MapSize);
            ctx->Stroke();
        }
        for (int32_t posY = -size; posY <= size; ++posY)
        {
            ctx->BeginPath();
            ctx->MoveTo(-2 * m_MapSize, posY * 50);
            ctx->LineTo(2 * m_MapSize, posY * 50);
            ctx->Stroke();
        }
    }
}
