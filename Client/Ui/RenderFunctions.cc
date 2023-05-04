#include <Client/Ui/RenderFunctions.hh>
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
        case PetalId::Rose:
            ctx->SetFill(DamageColor(0xffcf78a3, dTick));
            ctx->BeginPath();
            ctx->Arc(0, 0, 11.5);
            ctx->Fill();
            ctx->SetFill(DamageColor(0xffff94c9, dTick));
            ctx->BeginPath();
            ctx->Arc(0, 0, 8.5);
            ctx->Fill();
            break;
        case PetalId::Leaf:
            ctx->SetStroke(DamageColor(0xff2e933c, dTick));
            ctx->SetFill(DamageColor(0xff39b54a, dTick));
            ctx->SetLineWidth(3);
            ctx->SetLineCap(Renderer::LineCap::Round);
            ctx->BeginPath();
            ctx->MoveTo(-15,0);
            ctx->LineTo(-20,0);
            ctx->Stroke();
            ctx->BeginPath();
            ctx->MoveTo(-15,0);
            ctx->BezierCurveTo(-10,-12,5,-12,15,0);
            ctx->BezierCurveTo(5,12,-10,12,-15,0);
            ctx->Fill();
            ctx->Stroke();
            ctx->BeginPath();
            ctx->MoveTo(-9,0);
            ctx->QuadraticCurveTo(0,-1.5,7.5,0);
            ctx->Stroke();
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
            else if (id == PetalId::Leaf)
                ctx->Rotate(-1);
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
                    if (id == PetalId::Stinger && rarity >= RarityId::Ultra)
                        ctx->Rotate(M_PI);
                    else if (id == PetalId::Missile)
                        ctx->Rotate(1);
                    else if (id == PetalId::Leaf)
                        ctx->Rotate(-1);
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
    void DrawLoadoutPetal(Renderer *ctx, uint32_t id, uint32_t rarity, float reload)
    {
        reload = reload * reload * (3 - 2 * reload); //slerp
        Guard g(ctx);
        ctx->BeginPath();
        ctx->SetFill(RARITY_COLORS[rarity]);
        ctx->SetStroke(RARITY_COLORS[rarity], 0.8);
        ctx->SetLineWidth(12);
        ctx->SetLineCap(Renderer::LineCap::Round);
        ctx->SetLineJoin(Renderer::LineJoin::Round);
        ctx->StrokeRect(-30,-30,60,60);
        ctx->FillRect(-30,-30,60,60);
        ctx->Rect(-30,-30,60,60);
        ctx->Clip();
        ctx->Translate(0,-5);
        if (reload != 0)
        {
            ctx->SetFill(0x40000000);
            ctx->BeginPath();
            ctx->MoveTo(0,0);
            ctx->Arc(0, 0, 50, -M_PI_2 + -11.5 * reload * M_PI, -M_PI_2 -9.5 * reload * M_PI);
        }
        ctx->Fill();
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

    void DrawMob(Renderer *ctx, uint32_t id, uint32_t dTick, float seed)
    {
        switch(id)
        {
            case MobId::BabyAnt:
            ctx->SetFill(ui::DamageColor(0xff454545, dTick));
            ctx->SetStroke(ui::DamageColor(0xff292929, dTick));
            ctx->SetLineWidth(7);
            ctx->SetLineCap(Renderer::LineCap::Round);
            ctx->BeginPath();
            ctx->MoveTo(0, -7);
            ctx->QuadraticCurveTo(11, -10 + seed, 22, -5 + seed);
            ctx->Stroke();
            ctx->BeginPath();
            ctx->MoveTo(0, 7);
            ctx->QuadraticCurveTo(11, 10 - seed, 22, 5 - seed);
            ctx->Stroke();
            ctx->BeginPath();
            ctx->Arc(0, 0, 17.5);
            ctx->Fill();
            ctx->SetFill(ui::DamageColor(0xff555555, dTick));
            ctx->BeginPath();
            ctx->Arc(0, 0, 10.5);
            ctx->Fill();
            break;
        case MobId::WorkerAnt:
            ctx->SetFill(0xff454545);
            ctx->SetStroke(0xff292929);
            ctx->SetLineWidth(7);
            ctx->SetLineCap(Renderer::LineCap::Round);
            ctx->BeginPath();
            ctx->Arc(-16,0,13.5);
            ctx->Fill();
            ctx->SetFill(0xff555555);
            ctx->BeginPath();
            ctx->Arc(-16,0,6.5);
            ctx->Fill();
            ctx->SetFill(0xff454545);
            ctx->SetStroke(0xff292929);
            ctx->SetLineWidth(7);
            ctx->SetLineCap(Renderer::LineCap::Round);
            ctx->BeginPath();
            ctx->MoveTo(0,-7);
            ctx->QuadraticCurveTo(11,-10 + seed,22,-5 + seed);
            ctx->Stroke();
            ctx->BeginPath();
            ctx->MoveTo(0,7);
            ctx->QuadraticCurveTo(11,10 - seed,22,5 - seed);
            ctx->Stroke();
            ctx->BeginPath();
            ctx->Arc(0,0,17.5);
            ctx->Fill();
            ctx->SetFill(0xff555555);
            ctx->BeginPath();
            ctx->Arc(0,0,10.5);
            ctx->Fill();
            break;
        case MobId::Hornet:
            ctx->SetFill(0xff333333);
            ctx->SetStroke(0xff333333);
            ctx->SetLineWidth(5);
            ctx->SetLineCap(Renderer::LineCap::Round);
            ctx->SetLineJoin(Renderer::LineJoin::Round);
            ctx->BeginPath();
            ctx->MoveTo(-47,0);
            ctx->LineTo(-25,-6);
            ctx->LineTo(-25,6);
            ctx->LineTo(-47,0);
            ctx->Fill();
            ctx->Stroke();
            ctx->SetFill(0xffffd363);
            ctx->BeginPath();
            ctx->Ellipse(0,0,30,20);
            ctx->Fill();
            ctx->SetFill(0xff333333);
            {
                Guard g(ctx);
                ctx->Clip();
                ctx->BeginPath();
                ctx->FillRect(-30,-20,10,40);
                ctx->FillRect(-10,-20,10,40);
                ctx->FillRect(10,-20,10,40);
            }
            ctx->SetStroke(0xffd3ad46);
            ctx->SetLineWidth(5);
            ctx->BeginPath();
            ctx->Ellipse(0,0,30,20);
            ctx->Stroke();
            ctx->SetStroke(0xff333333);
            ctx->SetLineWidth(3);
            ctx->BeginPath();
            ctx->MoveTo(25,5);
            ctx->QuadraticCurveTo(40,10,50,15);
            ctx->QuadraticCurveTo(40,5,25,5);
            ctx->Fill();
            ctx->Stroke();
            ctx->BeginPath();
            ctx->MoveTo(25,-5);
            ctx->QuadraticCurveTo(40,-10,50,-15);
            ctx->QuadraticCurveTo(40,-5,25,-5);
            ctx->Fill();
            ctx->Stroke();
            break;
        }
    }
}