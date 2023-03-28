#include <Client/Component/ArenaInfo.hh>
#include <Client/Renderer.hh>
#include <Client/Simulation.hh>

#include <BinaryCoder/BinaryCoder.hh>
#include <BinaryCoder/NativeTypes.hh>

namespace app::component
{
    ArenaInfo::ArenaInfo(Entity parent)
        : m_Parent(parent)
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
        
        ctx->SetFill(0xff51983c);
        ctx->BeginPath();
        ctx->Arc(0, 0, m_MapSize);
        ctx->Fill();
        ctx->Clip();
        ctx->SetLineWidth(1);
        float alpha = ctx->m_Simulation.m_Camera.m_Fov * 51;
        ctx->SetStroke((uint32_t)(alpha) << 24);
        int32_t size = (int32_t)(m_MapSize * 0.02);
        for (int32_t posX = -size; posX <= size; ++posX)
        {
            ctx->BeginPath();
            ctx->MoveTo(posX * 50, -m_MapSize);
            ctx->LineTo(posX * 50, m_MapSize);
            ctx->Stroke();
        }
        for (int32_t posY = -size; posY <= size; ++posY)
        {
            ctx->BeginPath();
            ctx->MoveTo(-m_MapSize, posY * 50);
            ctx->LineTo(m_MapSize, posY * 50);
            ctx->Stroke();
        }
    }
}
