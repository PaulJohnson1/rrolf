#pragma once

#include <vector>
#include <cstdint>

#include <Client/Ui/Element.hh>
#include <Client/Ui/Container.hh>
#include <Client/Renderer.hh>

namespace app::ui
{
    template <int32_t innerSpacing, int32_t outerSpacing>
    Container *MakeHContainer(std::vector<Element *> elements)
    {
        Container *c = new Container(*g_Renderer);
        c->m_X = 0;
        c->m_Y = 0;
        float width = outerSpacing;
        float height = 0;
        for (uint64_t i = 0; i < elements.size(); i++)
        {
            ui::Element *element = elements[i];
            element->m_X = width + element->m_Width / 2;
            element->m_Container = c;
            width += element->m_Width + innerSpacing;
            if (element->m_Height > height)
                height = element->m_Height;
            c->m_Elements.push_back(element);
        }
        height += 2 * outerSpacing;
        width += outerSpacing - innerSpacing;

        c->m_Width = width;
        c->m_Height = height;
        for (uint64_t i = 0; i < elements.size(); i++)
        {
            elements[i]->m_Y = c->m_Height / 2;
        }
        return c;
    }

    template <int32_t innerSpacing, int32_t outerSpacing>
    Container *MakeVContainer(std::vector<Element *> elements)
    {
        Container *c = new Container(*g_Renderer);
        c->m_X = 0;
        c->m_Y = 0;
        float width = 0;
        float height = outerSpacing;
        for (uint64_t i = 0; i < elements.size(); i++)
        {
            ui::Element *element = elements[i];
            element->m_Y = height + element->m_Height / 2;
            element->m_Container = c;
            height += element->m_Height + innerSpacing;
            if (element->m_Width > width)
                width = element->m_Width;
            c->m_Elements.push_back(element);
        }
        width += 2 * outerSpacing;
        height += outerSpacing - innerSpacing;

        c->m_Width = width;
        c->m_Height = height;
        for (uint64_t i = 0; i < elements.size(); i++)
        {
            elements[i]->m_X = c->m_Width / 2;
        }
        return c;
    }

    template <int32_t HAlign, int32_t VAlign>
    Container *SetJustify(Container *c)
    {
        c->m_HJustify = HAlign;
        c->m_VJustify = VAlign;
        c->m_X = (1 - HAlign) * c->m_Width / 2;
        c->m_Y = (1 - VAlign) * c->m_Height / 2;
        return c;
    }

    template <int32_t pad>
    Container *HPad(Container *c)
    {
        if (c->m_HJustify == 2)
            c->m_X -= pad;
        else
            c->m_X += pad;
        return c;
    }

    template <int32_t pad>
    Container *VPad(Container *c)
    {
        if (c->m_VJustify == 2)
            c->m_Y -= pad;
        else
            c->m_Y += pad;
        return c;
    }

    template <uint32_t color>
    Container *AddBackground(Container *c)
    {
        c->m_HasBackground = true;
        c->m_Fill = color;
        return c;
    }
    
    Container *Add(Container *c)
    {
        for (uint64_t i = 0; i < c->m_Elements.size(); i++)
        {
            ui::Element *element = c->m_Elements[i];
            element->m_X -= c->m_Width / 2;
            element->m_Y -= c->m_Height / 2;
        }
        g_Renderer->m_Container.m_Elements.push_back(c);
        return c;
    }
}