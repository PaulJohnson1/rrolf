#pragma once

#include <cstdint>

namespace app
{
    class Renderer;
}

namespace app::ui
{
    class Element
    {
    protected:
        Renderer &m_Renderer;

    public:
        bool m_Showing = true;
        float m_X = 0.0f;
        float m_Y = 0.0f;
        float m_LineWidth = 1.0f;
        uint32_t m_Fill = 0xffffffff;
        uint32_t m_Stroke = 0xff000000;

        Element(Renderer &);
        virtual ~Element();

        virtual void Render() const = 0;
    };
}
