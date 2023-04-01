#pragma once

#include <cstdint>
#include <map>
#include <string>
#include <cassert>

#ifndef EMSCRIPTEN
#include <skia/include/core/SkPath.h>
#include <skia/include/core/SkPaint.h>
#include <skia/include/core/SkMatrix.h>
class SkCanvas;
#endif

#include <Client/Ui/Element.hh>

namespace app
{
    class Renderer;
}

extern app::Renderer *g_Renderer;

namespace ui
{
    class Element;
}

namespace app
{
    class Renderer;
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
        using T = void (*)();
#ifndef EMSCRIPTEN
        SkCanvas *m_Canvas;
        SkPath m_CurrentPath;
        SkPaint m_FillPaint;
        SkPaint m_StrokePaint;
#endif
        float m_Matrix[9] = {
            1, 0, 0,  // s s x !!REMEMBER: CANVAS2D IS s s s s x y SO ORDER MATTERS ITS 0 1 3 4 2 5
            0, 1, 0,  // s s y
            0, 0, 1}; // 0 0 1

        friend class Guard;

        // state
        void Save();
        void Restore();

    public:
        std::vector<ui::Element *> m_UiElements;

        T m_OnRender;

        float m_Width;
        float m_Height;
        float m_MouseX = 0.0f;
        float m_MouseY = 0.0f;
        uint8_t m_MouseState = 0;
        uint8_t m_MouseButton = 0;
        std::map<uint8_t, uint8_t> m_KeysPressed{};

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
            // Round
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

        Renderer(T onRender)
            : m_OnRender(onRender)
        {
            assert(!g_Renderer);
            g_Renderer = this;
#ifndef EMSCRIPTEN
            m_StrokePaint.setAntiAlias(true);
            m_FillPaint.setAntiAlias(true);
#endif
        }

        void Initialize();
        void SetSize(int32_t width, int32_t height);

        // matrix
        void ResetTransform();
        void UpdateTransform();
        void SetTransform(float, float, float, float, float, float);
        void Rotate(float);
        void Translate(float, float);
        void Scale(float, float);

        // style
        void SetFill(uint32_t);
        void SetStroke(uint32_t);
        void SetLineWidth(float);
        void SetLineCap(LineCap);
        void SetTextSize(float);
        void SetTextAlign(TextAlign);
        void SetTextBaseline(TextBaseline);
        void SetGlobalAlpha(float);

        // path
        void BeginPath();
        void MoveTo(float, float);
        void LineTo(float, float);
        void QuadraticCurveTo(float, float, float, float);
        void Arc(float, float, float);
        void FillRect(float, float, float, float);
        void StrokeRect(float, float, float, float);
        void Rect(float, float, float, float);
        void RoundRect(float, float, float, float, float);
        void FillText(std::string const &, float, float);
        void StrokeText(std::string const &, float, float);
        void Clip();

        // render
        void Stroke();
        void Fill();

        void Render()
        {
            m_OnRender();
            for (uint64_t i = 0; i < m_UiElements.size(); i++)
            {
                ui::Element *element = m_UiElements[i];
                if (element->m_Showing)
                    element->Render();
            }
        }
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

#ifdef EMSCRIPTEN
#include <emscripten.h>

extern "C"
{
    void __Renderer_KeyEvent(uint8_t op, int32_t key);
    void __Renderer_Render(int32_t width, int32_t height);
    void __Renderer_MouseEvent(float x, float y, uint8_t state, uint8_t button);
}
#else
void GlfwKeyCallback(GLFWwindow *window, int key, int scancode, int action, int mods)
{
    if (action == GLFW_PRESS)
        g_Renderer->m_KeysPressed[key] = 1;
    else if (action == GLFW_RELEASE)
        g_Renderer->m_KeysPressed[key] = 0;
}
#endif
