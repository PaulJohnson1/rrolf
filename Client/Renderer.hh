#pragma once

#include <cstdint>
#include <map>

#ifndef EMSCRIPTEN
#include <skia/include/core/SkPath.h>
#include <skia/include/core/SkPaint.h>
#include <skia/include/core/SkMatrix.h>
class SkCanvas;
#endif

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
    
    class Path2D
    {
#ifdef EMSCRIPTEN
        uint32_t m_Id;
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

    class Renderer
    {
#ifndef EMSCRIPTEN
        SkCanvas *m_Canvas;
        SkPath m_CurrentPath;
        SkPaint m_FillPaint;
        SkPaint m_StrokePaint;
#endif
        float m_Matrix[9] = {
            1, 0, 0, //s s x !!REMEMBER: CANVAS2D IS s s s s x y SO ORDER MATTERS ITS 0 1 3 4 2 5
            0, 1, 0, //s s y
            0, 0, 1};//0 0 1

        friend Guard;

        // state
        void Save();
        void Restore();

    public:
        class Simulation &m_Simulation;

        int32_t m_Width;
        int32_t m_Height;
        std::map<uint8_t, uint8_t> m_KeysPressed{};

        enum class LineCap {
            Butt,
            Round,
            Square
        };
        enum class LineJoin {
            Bevel,
            Miter,
            // Round
        };

        Renderer(Simulation &);

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

        // path
        void BeginPath();
        void MoveTo(float, float);
        void LineTo(float, float);
        void QuadraticCurveTo(float, float, float, float);
        void Arc(float, float, float);
        
        // render
        void Stroke();
        void Fill();
        // void BezierCurveTo(float, float, float, float, float, float);

        void Render();
        [[nodiscard]] Guard AutoSaveRestore();
    };
} //the old path2d impl worked somewhat
