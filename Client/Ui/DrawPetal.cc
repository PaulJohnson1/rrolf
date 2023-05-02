#include <Client/Ui/DrawPetal.hh>
#include <Shared/StaticData.hh>
#include <Client/Renderer.hh>

#include <iostream>

namespace app::ui
{
    uint32_t DamageColor(uint32_t c, uint32_t tick)
    {
        if (tick == 0)
            return c;
        else if (tick >= 10)
            return 0xffcccccc;
        else
        {
            float mixIn = (float) tick * 0.05;
            uint8_t red = (uint8_t)(((c >> 16) & 255) * (1-mixIn)) + (uint8_t)(mixIn * 255);
            uint8_t green = (uint8_t)(((c >> 8) & 255) * (1-mixIn));
            uint8_t blue = (uint8_t)(((c >> 0) & 255) * (1-mixIn));
            return (((c >> 24 & 255) << 24) | (red << 16) | (green << 8) | blue);
        }
    }
    void DrawPetal(Renderer *ctx, uint32_t id, uint32_t dTick)
    {
        switch (id)
        {
        case 0:
            break;
        case PetalId::Basic:
            ctx->SetFill(DamageColor(0xffcfcfcf, dTick));
            ctx->BeginPath();
            ctx->Arc(0, 0, 11.5);
            ctx->Fill();
            ctx->SetFill(DamageColor(0xffffffff, dTick));
            ctx->BeginPath();
            ctx->Arc(0, 0, 8.5);
            ctx->Fill();
            break;
        case PetalId::Light:
            ctx->SetFill(DamageColor(0xffcfcfcf, dTick));
            ctx->BeginPath();
            ctx->Arc(0, 0, 8.5);
            ctx->Fill();
            ctx->SetFill(DamageColor(0xffffffff, dTick));
            ctx->BeginPath();
            ctx->Arc(0, 0, 5.5);
            ctx->Fill();
            break;
        case PetalId::Stinger:
            ctx->SetFill(DamageColor(0xff333333, dTick));
            ctx->SetStroke(DamageColor(0xff292929, dTick));
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
        case PetalId::Missile:
            ctx->SetFill(DamageColor(0xff333333, dTick));
            ctx->SetStroke(DamageColor(0xff333333, dTick));
            ctx->SetLineWidth(5);
            ctx->SetLineJoin(Renderer::LineJoin::Round);
            ctx->SetLineCap(Renderer::LineCap::Round);
            ctx->BeginPath();
            ctx->MoveTo(11,0);
            ctx->LineTo(-11,-6);
            ctx->LineTo(-11,6);
            ctx->LineTo(11,0);
            ctx->Fill();
            ctx->Stroke();
            break;
        case PetalId::Pollen:
            ctx->SetFill(DamageColor(0xffcfbb50, dTick));
            ctx->BeginPath();
            ctx->Arc(0, 0, 8.5);
            ctx->Fill();
            ctx->SetFill(DamageColor(0xffffe763, dTick));
            ctx->BeginPath();
            ctx->Arc(0, 0, 5.5);
            ctx->Fill();
            break;
        default:
            ctx->SetFill(DamageColor(0xffcfcfcf, dTick));
            ctx->BeginPath();
            ctx->Arc(0, 0, 110.5);
            ctx->Fill();
            ctx->SetFill(DamageColor(0xffffffff, dTick));
            ctx->BeginPath();
            ctx->Arc(0, 0, 8.5);
            ctx->Fill();
            std::cout << id << '\n';
            break;
        }
    }

    void DrawStaticPetal(Renderer *ctx, uint32_t id, uint32_t rarity)
    {
        uint32_t count = PETAL_DATA[id].m_Count[rarity];
        if (count == 1)
        {
            Guard g(ctx);
            if (id == PetalId::Missile)
                ctx->Rotate(1);
            DrawPetal(ctx, id, 0);
        }
        else
        {
            float radius = PETAL_DATA[id].m_ClumpRadius != 0? PETAL_DATA[id].m_ClumpRadius: 10;
            for (uint32_t i = 0; i < count; ++i)
            {
                {
                    Guard g(ctx);
                    ctx->Translate(radius,0);
                    if (id == PetalId::Stinger && rarity == RarityId::Ultra)
                        ctx->Rotate(M_PI);
                    else if (id == PetalId::Missile)
                        ctx->Rotate(1);
                    DrawPetal(ctx, id, 0);     
                }   
                ctx->Rotate(M_PI * 2 / count);
            }
        }
    }

    void DrawPetalWithBackground(Renderer *ctx, uint32_t id, uint32_t rarity)
    {
        Guard g(ctx);
        ctx->BeginPath();
        ctx->SetFill(RARITY_COLORS[rarity]);
        ctx->SetStroke(RARITY_COLORS[rarity], 0.8);
        ctx->SetLineWidth(6);
        ctx->SetLineCap(Renderer::LineCap::Round);
        ctx->SetLineJoin(Renderer::LineJoin::Round);
        ctx->FillRect(-30,-30,60,60);
        ctx->StrokeRect(-30,-30,60,60);
        ctx->Translate(0,-5);
        ui::DrawStaticPetal(ctx, id, rarity);
        ctx->SetFill(0xffffffff);
        ctx->SetStroke(0xff000000);
        ctx->SetTextSize(14);
        ctx->SetLineWidth(1.68); 
        ctx->SetTextAlign(Renderer::TextAlign::Center);
        ctx->SetTextBaseline(Renderer::TextBaseline::Middle);
        ctx->BeginPath();
        ctx->StrokeText(PETAL_NAMES[id], 0, 20);
        ctx->FillText(PETAL_NAMES[id], 0, 20);
    }
}