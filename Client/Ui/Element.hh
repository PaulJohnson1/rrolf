#pragma once

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

        Element(Renderer &);
        virtual ~Element();

        virtual void Render() const = 0;
    };
}
