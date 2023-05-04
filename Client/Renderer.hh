#pragma once

#include <cassert>
#include <cstdint>
#include <map>
#include <string>

#ifndef EMSCRIPTEN
#include <GLFW/glfw3.h>
#include <skia/include/core/SkPath.h>
#include <skia/include/core/SkPaint.h>
#include <skia/include/core/SkMatrix.h>
#include <skia/include/core/SkBitmap.h>
#include <skia/include/core/SkCanvas.h>
#else
#include <emscripten.h>
#endif

#include <Client/Ui/Element.hh>
#include <Client/Ui/Container.hh>

namespace app
{
    class Renderer;
    class InputData;
}

extern app::Renderer *g_Renderer;
extern app::InputData *g_InputData;
namespace app
{
    class Renderer;
    class InputData
    {
    public:
        float m_MouseX = 0.0f;
        float m_MouseY = 0.0f;
        // order: left right middle
        uint8_t m_MouseButtons = 0;
        uint8_t m_State = 0;
        std::map<uint8_t, uint8_t> m_KeysPressed{};
        InputData()
        {
            g_InputData = this;
        }
    };
    class Guard
    {
        float m_CurrentMatrix[9];
        Renderer *m_Renderer;

    public:
        Guard(Renderer *);
        Guard(Renderer const &) = delete;
        Guard(Renderer &&) = delete;
        Renderer &operator=(Renderer const &) = delete;
        Renderer &operator=(Renderer &&) = delete;
        ~Guard();
    };
    // template <typename T = >
    class Renderer
    {
        float m_Matrix[9] = {
            1, 0, 0,  // s s x !!REMEMBER: CANVAS2D IS s s s s x y SO ORDER MATTERS ITS 0 1 3 4 2 5
            0, 1, 0,  // s s y
            0, 0, 1}; // 0 0 1

        friend class Guard;

        // state
        void Save();
        void Restore();

    public:
#ifndef EMSCRIPTEN
        SkCanvas *m_Canvas;
        SkPath m_CurrentPath;
        SkPaint m_FillPaint;
        SkPaint m_StrokePaint;
        SkBitmap *m_Bitmap;
#endif

        float m_Width;
        float m_Height;
        float m_WindowScale;
        uint8_t m_ContextId = 0;
        ui::Container m_Container;

        enum class LineCap
        {
            Butt,
            Round,
            Square
        };
        enum class LineJoin
        {
            Bevel,
            Miter,
            Round
        };
        enum class TextAlign
        {
            Left,
            Center,
            Right
        };
        enum class TextBaseline
        {
            Top,
            Middle,
            Bottom
        };

        Renderer()
            : m_Container(*this)
        {
            m_Width = 1920;
            m_Height = 1080;
#ifndef EMSCRIPTEN
            m_StrokePaint.setAntiAlias(true);
            m_FillPaint.setAntiAlias(true);
            if (g_Renderer == nullptr)
                g_Renderer = this;
            else
            {
                m_Bitmap = new SkBitmap;
                m_Bitmap->allocN32Pixels(m_Width, m_Height);
                m_Canvas = new SkCanvas(*m_Bitmap);
            }
#else
            m_ContextId = EM_ASM_INT({ return Module.addCtx(); });
            if (m_ContextId == 0)
            {
                assert(!g_Renderer);
                g_Renderer = this;
            }
#endif
        }

        Renderer(int32_t width, int32_t height)
            : m_Container(*this)
        {
            m_Width = width;
            m_Height = height;
#ifndef EMSCRIPTEN
            m_StrokePaint.setAntiAlias(true);
            m_FillPaint.setAntiAlias(true);
            if (g_Renderer == nullptr)
                g_Renderer = this;
            else
            {
                m_Bitmap = new SkBitmap;
                m_Bitmap->allocN32Pixels(width, height);
                m_Canvas = new SkCanvas(*m_Bitmap);
            }
#else
            m_ContextId = EM_ASM_INT({ return Module.addCtx(); });
            if (m_ContextId == 0)
            {
                assert(!g_Renderer);
                g_Renderer = this;
            }
            SetSize(width, height);
#endif
        }

        ~Renderer();

        void SetSize(int32_t width, int32_t height);

        // matrix
        float const *GetTransform();
        void ResetTransform();
        void UpdateTransform();
        void SetTransform(float, float, float, float, float, float);
        void Rotate(float);
        void Translate(float, float);
        void Scale(float, float);
        void Scale(float);

        // style
        void SetGlobalAlpha(float);
        void SetFill(uint32_t);
        void SetFill(uint32_t, float); // darken
        void SetStroke(uint32_t);
        void SetStroke(uint32_t, float);
        void SetLineWidth(float);
        void SetLineCap(LineCap);
        void SetLineJoin(LineJoin);
        void SetTextSize(float);
        void SetTextAlign(TextAlign);
        void SetTextBaseline(TextBaseline);

        // path
        void BeginPath();
        void MoveTo(float, float);
        void LineTo(float, float);
        void QuadraticCurveTo(float, float, float, float);
        void BezierCurveTo(float, float, float, float, float, float);
        void Arc(float, float, float);
        void Arc(float, float, float, float, float);
        void FillRect(float, float, float, float);
        void StrokeRect(float, float, float, float);
        void Rect(float, float, float, float);
        void RoundRect(float, float, float, float, float);
        void FillText(std::string const &, float, float);
        void StrokeText(std::string const &, float, float);
        void Clip();

        void DrawImage(Renderer const &);

        float GetTextLength(std::string const &);

        // render
        void Stroke();
        void Fill();
    };

    class Path2D
    {
#ifdef EMSCRIPTEN
        uint32_t m_Index;
#else
        SkPath m_Path;
#endif

    public:
        Path2D();
        ~Path2D();

        void MoveTo(float, float);
        void LineTo(float, float);
        void ArcTo(float, float, float);
        void QuadTo(float, float, float, float);
    };
}
