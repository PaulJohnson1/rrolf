#include <Client/Renderer.hh>

#include <iostream>
#include <chrono>
#include <thread>
#include <cmath>
#include <string>

#ifndef EMSCRIPTEN
#define SK_GL
#define SK_GANESH
#include <GLFW/glfw3.h>
#include <skia/include/core/SkCanvas.h>
#include <skia/include/core/SkColor.h>
#include <skia/include/core/SkPaint.h>
#include <skia/include/core/SkSurface.h>
#include <skia/include/core/SkColorSpace.h>
#include <skia/include/gpu/gl/GrGLInterface.h>
#include <skia/include/gpu/GrDirectContext.h>
#include <skia/include/gpu/GrBackendSurface.h>
void SkDebugf(const char format[], ...)
{
}
#endif

#include <Client/Ui/Container.hh>
#include <Shared/Assert.hh>

app::Renderer *g_Renderer = nullptr;
app::InputData *g_InputData = nullptr;

namespace app
{
    Guard::Guard(Renderer *renderer)
        : m_Renderer(renderer)
    {
        for (uint64_t i = 0; i < 9; ++i)
            m_CurrentMatrix[i] = m_Renderer->m_Matrix[i];
        m_Renderer->Save();
    }

    Guard::~Guard()
    {
        for (uint64_t i = 0; i < 9; ++i)
            m_Renderer->m_Matrix[i] = m_CurrentMatrix[i];
        m_Renderer->Restore();
    }

    Renderer::~Renderer()
    {
#ifndef EMSCRIPTEN
        if (this != g_Renderer)
        {
            delete m_Canvas;
            delete m_Bitmap;
        }
#endif
    }

    float const *Renderer::GetTransform()
    {
        return m_Matrix;
    }
    
    void Renderer::SetTransform(float a, float b, float c, float d, float e, float f)
    {
        m_Matrix[0] = a;
        m_Matrix[1] = b;
        m_Matrix[2] = c;
        m_Matrix[3] = d;
        m_Matrix[4] = e;
        m_Matrix[5] = f;
        UpdateTransform();
    }

    void Renderer::UpdateTransform()
    {
#ifdef EMSCRIPTEN
        EM_ASM({
            Module.ctxs[$0].setTransform($1, $2, $3, $4, $5, $6);
        },
               m_ContextId, m_Matrix[0], m_Matrix[1], m_Matrix[3], m_Matrix[4], m_Matrix[2], m_Matrix[5]);
#else
        SkMatrix m;
        // float test[9] = { m_Matrix[0], m_Matrix[3], m_Matrix[2], m_Matrix[1], m_Matrix[4], m_Matrix[5], 0, 0, 1}; //idt that works
        float test[9] = { m_Matrix[0], m_Matrix[1], m_Matrix[3], m_Matrix[4], m_Matrix[2], m_Matrix[5], 0, 0, 1}; //idt that works
        
        m.setAffine(test); //test this lol we pray
        m_Canvas->setMatrix(m);
#endif
    }

    void Renderer::ResetTransform()
    {
        m_Matrix[0] = 1;
        m_Matrix[1] = 0;
        m_Matrix[2] = 0;
        m_Matrix[3] = 0;
        m_Matrix[4] = 1;
        m_Matrix[5] = 0;
        m_Matrix[6] = 0;
        m_Matrix[7] = 0;
        m_Matrix[8] = 1;
        UpdateTransform();
    }

    void Renderer::Rotate(float a)
    {
        float cos_a = std::cos(a);
        float sin_a = std::sin(a);
        float original0 = m_Matrix[0];
        float original1 = m_Matrix[1];
        float original3 = m_Matrix[3];
        float original4 = m_Matrix[4];
        m_Matrix[0] = original0 * cos_a + original1 * -sin_a;
        m_Matrix[1] = original0 * sin_a + original1 * cos_a;
        m_Matrix[3] = original3 * cos_a + original4 * -sin_a;
        m_Matrix[4] = original3 * sin_a + original4 * cos_a;
        UpdateTransform();
    }

    void Renderer::Translate(float x, float y)
    {
        m_Matrix[2] += x * m_Matrix[0] + y * m_Matrix[3];
        m_Matrix[5] += x * m_Matrix[1] + y * m_Matrix[4];
        UpdateTransform();
    }

    void Renderer::Scale(float x, float y)
    {
        m_Matrix[0] *= x;
        m_Matrix[1] *= y;
        m_Matrix[3] *= x;
        m_Matrix[4] *= y;
        UpdateTransform();
    }

    void Renderer::Scale(float s)
    {
        Scale(s, s);
    }

    void Renderer::Save()
    {
#ifndef EMSCRIPTEN
        m_Canvas->save();
#else
        EM_ASM({
            Module.ctxs[$0].save();
        },
               m_ContextId);
#endif
    }

    void Renderer::Restore()
    {
#ifndef EMSCRIPTEN
        m_Canvas->restore();
#else
        EM_ASM({
            Module.ctxs[$0].restore();
        },
               m_ContextId);
#endif
    }

    void Renderer::SetSize(int32_t width, int32_t height)
    {
#ifdef EMSCRIPTEN
        m_Width = width;
        m_Height = height;
        EM_ASM({
            Module.ctxs[$0].canvas.width = $1;
            Module.ctxs[$0].canvas.height = $2;
        },
               m_ContextId, width, height);
#else
        RROLF_ASSERT(false, "setsize not implemented");
#endif
    }

    void Renderer::SetFill(uint32_t c)
    {
#ifdef EMSCRIPTEN
        EM_ASM({Module.ctxs[$0].fillStyle = `rgba(${$1 >> 16 & 255}, ${$1 >> 8 & 255}, ${$1 & 255}, ${($1 >> 24 & 255) / 255})` }, m_ContextId, c);
#else
        m_FillPaint.setColor(c);
#endif
    }

    void Renderer::SetFill(uint32_t c, float h)
    {
        uint8_t red = (uint8_t)(((c >> 16) & 255) * h);
        uint8_t green = (uint8_t)(((c >> 8) & 255) * h);
        uint8_t blue = (uint8_t)(((c >> 0) & 255) * h);
        SetFill(((c >> 24 & 255) << 24) | (red << 16) | (green << 8) | blue);
    }

    void Renderer::SetStroke(uint32_t c)
    {
#ifdef EMSCRIPTEN
        EM_ASM({Module.ctxs[$0].strokeStyle = `rgba(${$1 >> 16 & 255}, ${$1 >> 8 & 255}, ${$1 & 255}, ${($1 >> 24 & 255) / 255})` }, m_ContextId, c);
#else
        m_StrokePaint.setColor(c);
#endif
    }

    void Renderer::SetStroke(uint32_t c, float h)
    {
        uint8_t red = (uint8_t)(((c >> 16) & 255) * h);
        uint8_t green = (uint8_t)(((c >> 8) & 255) * h);
        uint8_t blue = (uint8_t)(((c >> 0) & 255) * h);
        SetStroke(((c >> 24 & 255) << 24) | (red << 16) | (green << 8) | blue);
    }

    void Renderer::SetLineWidth(float w)
    {
#ifdef EMSCRIPTEN
        EM_ASM({
            Module.ctxs[$0].lineWidth = $1;
        },
               m_ContextId, w);
#else
        m_StrokePaint.setStrokeWidth(w);
#endif
    }

    void Renderer::SetLineCap(LineCap l)
    {
#ifdef EMSCRIPTEN
        EM_ASM({
            if ($1 == 0)
                Module.ctxs[$0].lineCap = 'butt';
            else if ($1 == 1)
                Module.ctxs[$0].lineCap = 'round';
            else
                Module.ctxs[$0].lineCap = 'square';
        },
               m_ContextId, l);
#else
        switch (l)
        {
        case LineCap::Butt:
            m_StrokePaint.setStrokeCap(SkPaint::kButt_Cap);
            break;
        case LineCap::Round:
            m_StrokePaint.setStrokeCap(SkPaint::kRound_Cap);
            break;
        case LineCap::Square:
            m_StrokePaint.setStrokeCap(SkPaint::kSquare_Cap);
        default:
            RROLF_ASSERT(false, "invalid argument for setlinecap");
        };
#endif
    }

    void Renderer::SetLineJoin(LineJoin l)
    {
#ifdef EMSCRIPTEN
        EM_ASM({
            if ($1 == 0)
                Module.ctxs[$0].lineJoin = 'bevel';
            else if ($1 == 1)
                Module.ctxs[$0].lineJoin = 'miter';
            else
                Module.ctxs[$0].lineJoin = 'round';
        },
               m_ContextId, l);
#else
        // TODO later
        switch (l)
        {
        case LineJoin::Bevel:
            m_StrokePaint.setStrokeJoin(SkPaint::kBevel_Join);
            break;
        case LineJoin::Miter:
            m_StrokePaint.setStrokeJoin(SkPaint::kMiter_Join);
            break;
        case LineJoin::Round:
            m_StrokePaint.setStrokeJoin(SkPaint::kRound_Join);
            break;
        default:
            RROLF_ASSERT(false, "invalid argument for setlinejoin");
        };
#endif
    }

    void Renderer::SetTextSize(float size)
    {
#ifdef EMSCRIPTEN
        EM_ASM({ Module.ctxs[$0].font = $1 + "px Ubuntu"; }, m_ContextId, size);
#else
        // TODO: implement
#endif
    }

    void Renderer::SetTextAlign(TextAlign l)
    {
#ifdef EMSCRIPTEN
        EM_ASM({
            if ($1 == 0)
                Module.ctxs[$0].textAlign = 'left';
            else if ($1 == 1)
                Module.ctxs[$0].textAlign = 'center';
            else
                Module.ctxs[$0].textAlign = 'right';
        },
               m_ContextId, l);
#else
        // TODO later
#endif
    }

    void Renderer::SetTextBaseline(TextBaseline l)
    {
#ifdef EMSCRIPTEN
        EM_ASM({
            if ($1 == 0)
                Module.ctxs[$0].textBaseline = 'top';
            else if ($1 == 1)
                Module.ctxs[$0].textBaseline = 'middle';
            else
                Module.ctxs[$0].textBaseline = 'bottom';
        },
               m_ContextId, l);
#else
        // TODO later
#endif
    }

    void Renderer::SetGlobalAlpha(float a)
    {
#ifdef EMSCRIPTEN
        EM_ASM({
            Module.ctxs[$0].globalAlpha = $1;
        },
               m_ContextId, a);
#else
        RROLF_ASSERT(false, "setglobalalpha not implemented for skia build");
#endif
    }

    void Renderer::BeginPath()
    {
#ifdef EMSCRIPTEN
        EM_ASM({ Module.ctxs[$0].beginPath(); }, m_ContextId);
#else
        m_CurrentPath = SkPath{};
#endif
    }

    void Renderer::MoveTo(float x, float y)
    {
#ifdef EMSCRIPTEN
        EM_ASM({ Module.ctxs[$0].moveTo($1, $2); }, m_ContextId, x, y);
#else
        m_CurrentPath.moveTo(x, y);
#endif
    }

    void Renderer::LineTo(float x, float y)
    {
#ifdef EMSCRIPTEN
        EM_ASM({ Module.ctxs[$0].lineTo($1, $2); }, m_ContextId, x, y);
#else
        m_CurrentPath.lineTo(x, y);
#endif
    }

    void Renderer::QuadraticCurveTo(float x1, float y1, float x, float y)
    {
#ifdef EMSCRIPTEN
        EM_ASM({ Module.ctxs[$0].quadraticCurveTo($1, $2, $3, $4); }, m_ContextId, x1, y1, x, y);
#else
        m_CurrentPath.quadTo(x1, y1, x, y);
#endif
    }
    void Renderer::BezierCurveTo(float x1, float y1, float x2, float y2, float x, float y)
    {
#ifdef EMSCRIPTEN
        EM_ASM({ Module.ctxs[$0].bezierCurveTo($1, $2, $3, $4, $5, $6); }, m_ContextId, x1, y1, x2, y2, x, y);
#else
        m_CurrentPath.quadTo(x1, y1, x, y);
#endif
    }

    void Renderer::Arc(float x, float y, float r, float sa, float ea)
    {
#ifdef EMSCRIPTEN
        EM_ASM({ Module.ctxs[$0].arc($1, $2, $3, $4, $5); }, m_ContextId, x, y, r, sa, ea);
#else
        m_CurrentPath.addCircle(x, y, r);
#endif
    }

    void Renderer::Arc(float x, float y, float r)
    {
        Arc(x, y, r, 0, M_PI * 2);
    }

    void Renderer::FillRect(float x, float y, float w, float h)
    {
#ifdef EMSCRIPTEN
        EM_ASM({ Module.ctxs[$0].fillRect($1, $2, $3, $4); }, m_ContextId, x, y, w, h);
#else
        m_Canvas->drawRect(SkRect::MakeXYWH(x, y, w, h), m_FillPaint);
#endif
    }

    void Renderer::StrokeRect(float x, float y, float w, float h)
    {
#ifdef EMSCRIPTEN
        EM_ASM({ Module.ctxs[$0].strokeRect($1, $2, $3, $4); }, m_ContextId, x, y, w, h);
#else
        // TODO: later
#endif
    }

    void Renderer::Rect(float x, float y, float w, float h)
    {
#ifdef EMSCRIPTEN
        EM_ASM({ Module.ctxs[$0].rect($1, $2, $3, $4); }, m_ContextId, x, y, w, h);
#else
        // TODO: later
#endif
    }

    void Renderer::RoundRect(float x, float y, float w, float h, float r)
    {
        BeginPath();
        MoveTo(x + r, y);
        LineTo(x + w - r, y);
        QuadraticCurveTo(x + w, y, x + w, y + r);
        LineTo(x + w, y + h - r);
        QuadraticCurveTo(x + w, y + h, x + w - r, y + h);
        LineTo(x + r, y + h);
        QuadraticCurveTo(x, y + h, x, y + h - r);
        LineTo(x, y + r);
        QuadraticCurveTo(x, y, x + r, y);
    }

    void Renderer::FillText(std::string const &string, float x, float y)
    {
#ifdef EMSCRIPTEN
        EM_ASM({ $1 = Module.ReadCstr($1); Module.ctxs[$0].fillText($1, $2, $3); }, m_ContextId, string.c_str(), x, y);
#else
        // TODO: later
#endif
    }

    void Renderer::StrokeText(std::string const &string, float x, float y)
    {
#ifdef EMSCRIPTEN
        EM_ASM({ $1 = Module.ReadCstr($1); Module.ctxs[$0].strokeText($1, $2, $3); }, m_ContextId, string.c_str(), x, y);
#else
        // TODO: later
#endif
    }

    void Renderer::Clip()
    {
#ifdef EMSCRIPTEN
        EM_ASM({ Module.ctxs[$0].clip(); }, m_ContextId);
#else
        m_Canvas->clipPath(m_CurrentPath, true);
#endif
    }

    void Renderer::Fill()
    {
#ifdef EMSCRIPTEN
        EM_ASM({ Module.ctxs[$0].fill(); }, m_ContextId);
#else
        m_FillPaint.setStyle(SkPaint::kFill_Style);
        m_Canvas->drawPath(m_CurrentPath, m_FillPaint);
#endif
    }

    void Renderer::Stroke()
    {
#ifdef EMSCRIPTEN
        EM_ASM({ Module.ctxs[$0].stroke(); }, m_ContextId);
#else
        m_StrokePaint.setStyle(SkPaint::kStroke_Style);
        m_Canvas->drawPath(m_CurrentPath, m_StrokePaint);
#endif
    }

    void Renderer::DrawImage(Renderer const &ctx)
    {
#ifdef EMSCRIPTEN
        EM_ASM({
            Module.ctxs[$0].drawImage(Module.ctxs[$1].canvas, $2, $3);
        },
               m_ContextId, ctx.m_ContextId, -ctx.m_Width / 2, -ctx.m_Height / 2);
#else
        // TODO: later
#endif
    }
    float Renderer::GetTextLength(std::string const &str)
    {
#ifdef EMSCRIPTEN
        return EM_ASM_INT({ $1 = Module.ReadCstr($1); return Module.ctxs[$0].measureText($1).width; }, m_ContextId, str.c_str());
#else
        // TODO: later
        return 0;
#endif
    }

    Path2D::Path2D()
    {
#ifdef EMSCRIPTEN
        m_Index = EM_ASM_INT({ return Module.addPath(); });
#endif
    }

    void Path2D::MoveTo(float x, float y)
    {
#ifdef EMSCRIPTEN
        EM_ASM({ Module.paths[$0].moveTo($1, $2); }, m_Index, x, y);
#else
        m_Path.moveTo(x, y);
#endif
    }

    void Path2D::LineTo(float x, float y)
    {
#ifdef EMSCRIPTEN
        EM_ASM({ Module.paths[$0].lineTo($1, $2); }, m_Index, x, y);
#else
        m_Path.lineTo(x, y);
#endif
    }
}
