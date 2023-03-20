#pragma once

#include <cstdint>

class SkCanvas;

namespace app
{
    class Simulation;

    class Renderer
    {
#ifndef WASM_BUILD
        SkCanvas *m_Canvas;
#endif
        Simulation &m_Simulation;

    public:
        class Paint
        {
        public:
            enum class Style : uint8_t
            {
                Fill,
                Stroke,
                FillAndStroke
            };

            enum class Cap : uint8_t
            {
                Butt,
                Round,
                Square
            };

            enum class Join : uint8_t
            {
                Mitter,
                Round,
                Bevel
            };

            Style m_Style = Style::Fill;
            Join m_Join = Join::Round;
            Cap m_Cap = Cap::Butt;
            bool m_AntiAliased = false;
            uint8_t m_Alpha = 0xff;
            uint8_t m_Red = 0x00;
            uint8_t m_Blue = 0x00;
            uint8_t m_Green = 0x00;
            float m_StrokeWidth = 1;
        };

        Renderer(Simulation &);

        void Initialize();
        void Render();
        void Translate(float, float);
        void Scale(float, float);
        void DrawCircle(float, float, float, Paint const &);
        void Save();
        void Restore();
        void Clear();
    };
}
