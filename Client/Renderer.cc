#include <Client/Renderer.hh>
#include <Client/Ui/Container.hh>

#include <iostream>
#include <chrono>
#include <thread>
#include <cassert>
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

app::Renderer *g_Renderer = nullptr;
app::Mouse *g_Mouse = nullptr;

namespace app
{
    Guard::Guard(Renderer *renderer)
        : m_Renderer(renderer)
    {
        m_CurrentMatrix[0] = m_Renderer->m_Matrix[0];
        m_CurrentMatrix[1] = m_Renderer->m_Matrix[1];
        m_CurrentMatrix[2] = m_Renderer->m_Matrix[2];
        m_CurrentMatrix[3] = m_Renderer->m_Matrix[3];
        m_CurrentMatrix[4] = m_Renderer->m_Matrix[4];
        m_CurrentMatrix[5] = m_Renderer->m_Matrix[5];
        m_CurrentMatrix[6] = m_Renderer->m_Matrix[6];
        m_CurrentMatrix[7] = m_Renderer->m_Matrix[7];
        m_CurrentMatrix[8] = m_Renderer->m_Matrix[8];
        m_Renderer->Save();
    }

    Guard::~Guard()
    {
        m_Renderer->m_Matrix[0] = m_CurrentMatrix[0];
        m_Renderer->m_Matrix[1] = m_CurrentMatrix[1];
        m_Renderer->m_Matrix[2] = m_CurrentMatrix[2];
        m_Renderer->m_Matrix[3] = m_CurrentMatrix[3];
        m_Renderer->m_Matrix[4] = m_CurrentMatrix[4];
        m_Renderer->m_Matrix[5] = m_CurrentMatrix[5];
        m_Renderer->m_Matrix[6] = m_CurrentMatrix[6];
        m_Renderer->m_Matrix[7] = m_CurrentMatrix[7];
        m_Renderer->m_Matrix[8] = m_CurrentMatrix[8];
        m_Renderer->Restore();
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
        m.set9(m_Matrix);
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
        m_Matrix[2] += x * (m_Matrix[0] + m_Matrix[3]);
        m_Matrix[5] += y * (m_Matrix[1] + m_Matrix[4]);
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

    void Renderer::Save()
    {
#ifndef EMSCRIPTEN
        m_Canvas->save();
#else
        EM_ASM({
            Module.ctxs[$0].save();
        }, m_ContextId);
#endif
    }

    void Renderer::Restore()
    {
#ifndef EMSCRIPTEN
        m_Canvas->restore();
#else
        EM_ASM({
            Module.ctxs[$0].restore();
        }, m_ContextId);
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
        }, m_ContextId, width, height);
#else
        assert(false);
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

    void Renderer::SetStroke(uint32_t c)
    {
#ifdef EMSCRIPTEN
        EM_ASM({Module.ctxs[$0].strokeStyle = `rgba(${$1 >> 16 & 255}, ${$1 >> 8 & 255}, ${$1 & 255}, ${($1 >> 24 & 255) / 255})` }, m_ContextId, c);
#else
        m_StrokePaint.setColor(c);
#endif
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
        // TODO later
        assert(false);
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
        assert(false);
#endif
    }

    void Renderer::SetTextSize(float size)
    {
#ifdef EMSCRIPTEN
        EM_ASM({ Module.ctxs[$0].font = $1 + "px Ubuntu"; }, m_ContextId, size);
#else
        assert(false);
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
        assert(false);
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
        assert(false);
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
        // TODO later
        assert(false);
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

    void Renderer::Arc(float x, float y, float r)
    {
#ifdef EMSCRIPTEN
        EM_ASM({ Module.ctxs[$0].arc($1, $2, $3, 0, 6.283185307179586); }, m_ContextId, x, y, r);
#else
        m_CurrentPath.addCircle(x, y, r);
#endif
    }

    void Renderer::FillRect(float x, float y, float w, float h)
    {
#ifdef EMSCRIPTEN
        EM_ASM({ Module.ctxs[$0].fillRect($1, $2, $3, $4); }, m_ContextId, x, y, w, h);
#else
        assert(false);
#endif
    }

    void Renderer::StrokeRect(float x, float y, float w, float h)
    {
#ifdef EMSCRIPTEN
        EM_ASM({ Module.ctxs[$0].strokeRect($1, $2, $3, $4); }, m_ContextId, x, y, w, h);
#else
        assert(false);
#endif
    }

    void Renderer::Rect(float x, float y, float w, float h)
    {
#ifdef EMSCRIPTEN
        EM_ASM({ Module.ctxs[$0].rect($1, $2, $3, $4); }, m_ContextId, x, y, w, h);
#else
        assert(false);
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
        assert(false);
#endif
    }

    void Renderer::StrokeText(std::string const &string, float x, float y)
    {
#ifdef EMSCRIPTEN
        EM_ASM({ $1 = Module.ReadCstr($1); Module.ctxs[$0].strokeText($1, $2, $3); }, m_ContextId, string.c_str(), x, y);
#else
        assert(false);
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

    float Renderer::GetTextLength(std::string const &str)
    {
#ifdef EMSCRIPTEN
        return EM_ASM_INT({ $1 = Module.ReadCstr($1); return Module.ctxs[$0].measureText($1).width; }, m_ContextId, str.c_str());
#else
        return -1000000.0;
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
