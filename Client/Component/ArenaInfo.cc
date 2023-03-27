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
        Renderer::ContextLock lock = ctx->AutoSaveRestore();
        Renderer::Paint paint;
        paint.m_Color = 0xff51983c;
        ctx->DrawCircle(0, 0, m_MapSize, paint);
        Renderer::Path arenaPath;
        arenaPath.MoveTo(0, 0);
        arenaPath.Circle(0, 0, m_MapSize);
        ctx->ClipPath(arenaPath);
        paint.m_Style = Renderer::Paint::Style::Stroke;
        paint.m_StrokeWidth = 1;
        uint8_t alpha = (uint8_t)(ctx->m_Simulation.m_Camera.m_Fov * 51);
        paint.m_Color = alpha << 24 | 0x000000;
        int32_t size = (int32_t)(m_MapSize * 0.02);
        for (int32_t posX = -size; posX <= size; ++posX)
            ctx->DrawLine(posX * 50, -m_MapSize, posX * 50, m_MapSize, paint);
        for (int32_t posY = -size; posY <= size; ++posY)
            ctx->DrawLine(-m_MapSize, posY * 50, m_MapSize, posY * 50, paint);
    }
}
