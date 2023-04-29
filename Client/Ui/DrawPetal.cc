#include <Client/Ui/DrawPetal.hh>
#include <Shared/StaticData.hh>
#include <Client/Renderer.hh>

namespace app::ui
{
    void DrawPetal(Renderer *ctx, uint32_t id)
    {
        switch (id)
        {
        case 0:
            break;
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
        case 2:
            ctx->SetFill(0xffcfcfcf);
            ctx->BeginPath();
            ctx->Arc(0, 0, 8.5);
            ctx->Fill();
            ctx->SetFill(0xffffffff);
            ctx->BeginPath();
            ctx->Arc(0, 0, 5.5);
            ctx->Fill();
            break;
        case 3:
            ctx->SetFill(0xff333333);
            ctx->SetStroke(0xff292929);
            ctx->SetLineWidth(3);
            ctx->SetLineJoin(Renderer::LineJoin::Round);
            ctx->BeginPath();
            ctx->MoveTo(7,0);
            ctx->LineTo(-3.500000476837158,6.062177658081055);
            ctx->LineTo(-3.4999992847442627,-6.062178134918213);
            ctx->LineTo(7,0);
            ctx->Fill();
            ctx->Stroke();
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
        }
    }
    void DrawPetal(Renderer *ctx, uint32_t id, uint32_t rarity)
    {
        uint32_t count = PETAL_DATA[id].m_Count[rarity];
        if (count == 1)
            DrawPetal(ctx, id);
        else
        {
            for (uint32_t i = 0; i < count; ++i)
            {
                ctx->Translate(10,0);
                if (id == 3 && rarity >= 6)
                    ctx->Rotate(M_PI);
                DrawPetal(ctx, id);
                if (id == 3 && rarity >= 6)
                    ctx->Rotate(M_PI);
                ctx->Translate(-10,0);         
                ctx->Rotate(M_PI * 2 / count);
            }
        }
    }
}