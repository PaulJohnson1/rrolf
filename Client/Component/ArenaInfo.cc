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
        component::PlayerInfo &playerInfo = m_Simulation->Get<component::PlayerInfo>(m_Simulation->m_PlayerInfo);
        float alpha = playerInfo.m_Fov * 51;
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

        ctx->ResetTransform();
        float fov = playerInfo.m_Fov;
        ctx->Scale(fov, fov);
        uint32_t adjustedWidth = ctx->m_Width * (1 / fov);
        uint32_t adjustedHeight = ctx->m_Height * (1 / fov);
        uint32_t lineCountX = adjustedWidth / 50;
        uint32_t lineCountY = adjustedHeight / 50;
        ctx->Translate(playerInfo.m_CameraX % 50.0f, playerInfo.m_CameraY % 50.0f);
        for (float i = 0; i < lineCountY; i++)
        {
            ctx->BeginPath();
            ctx->MoveTo(0, i * 50);
            ctx->LineTo(adjustedWidth, i * 50);
            ctx->Stroke();
        }
        for (float i = 0; i < lineCountX; i++)
        {
            ctx->BeginPath();
            ctx->MoveTo(i * 50, 0);
            ctx->LineTo(i * 50, adjustedHeight);
            ctx->Stroke();
        }
    }
}
