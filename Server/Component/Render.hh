#pragma once

#include <cstdint>

#include <Server/Entity.hh>

namespace bc
{
    class BinaryCoder;
}

namespace app::component
{
    class Render
    {
        uint32_t m_Color = 0x7f00ff00;

    public:
        using Type = Render;
        
        Entity m_Parent;
        uint64_t m_State = 0;

        Render(Entity);

        uint32_t Color() const;
        void Color(uint32_t);

        void Reset();

        // clone becuase the struct is small
        static void Write(bc::BinaryCoder &, Render, bool isCreation);
    };
}