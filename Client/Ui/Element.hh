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
        int32_t m_HJustify = 0; //1 for mid 2 for right
        int32_t m_VJustify = 0; //1 for mid 2 for bottom
        float m_X = 0.0f;
        float m_Y = 0.0f;
        float m_Width = 1.0f;
        float m_Height = 1.0f;
        float m_LineWidth = 1.0f;
        uint32_t m_Fill = 0xffffffff;
        uint32_t m_Stroke = 0xff222222;
        class Container *m_Container;

        Element(Renderer &, float, float);
        virtual ~Element();
        virtual void Render()
        {
        };
    };
}
