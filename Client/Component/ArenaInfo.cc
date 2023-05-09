#include <Client/Component/ArenaInfo.hh>


#include <BinaryCoder/BinaryCoder.hh>
#include <BinaryCoder/NativeTypes.hh>

#include <Client/Simulation.hh>
#include <Client/Renderer.hh>
#include <Client/Simulation.hh>
#include <Shared/Assert.hh>

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
        PlayerInfo &playerInfo = m_Simulation->Get<PlayerInfo>(m_Simulation->m_PlayerInfo);
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

        float a = g_Renderer->m_Height / 1080;
        float b = g_Renderer->m_Width / 1920;
        float windowScale = b < a ? a : b;
        float scale = playerInfo.m_Fov * windowScale;
        float leftX = playerInfo.m_CameraX - ctx->m_Width / (2 * scale); 
        float rightX = playerInfo.m_CameraX + ctx->m_Width / (2 * scale); 
        float topY = playerInfo.m_CameraY - ctx->m_Height / (2 * scale); 
        float bottomY = playerInfo.m_CameraY + ctx->m_Height / (2 * scale); 
        float newLeftX = ceilf(leftX / 50) * 50;
        float newTopY = ceilf(topY / 50) * 50;
        for (; newLeftX < rightX; newLeftX += 50)
        {
            ctx->BeginPath();
            ctx->MoveTo(newLeftX, topY);
            ctx->LineTo(newLeftX, bottomY);
            ctx->Stroke();
        }
        for (; newTopY < bottomY; newTopY += 50)
        {
            ctx->BeginPath();
            ctx->MoveTo(leftX, newTopY);
            ctx->LineTo(rightX, newTopY);
            ctx->Stroke();
        }
    }
}
