#pragma once

#include <vector>
#include <cstdint>

#include <Client/Ui/Element.hh>

namespace app::ui
{
    class Container;
    template <int32_t innerSpacing, int32_t outerSpacing, int32_t vJustify = 1>
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
            element->m_HJustify = 0;
            element->m_VJustify = vJustify;
            element->m_Y = (1 - vJustify) * (element->m_Height / 2 + outerSpacing);
            width += element->m_Width + innerSpacing;
            if (element->m_Height > height)
                height = element->m_Height;
            c->m_Elements.push_back(element);
        }
        height += 2 * outerSpacing;
        width += outerSpacing - innerSpacing;

        c->m_Width = width;
        c->m_Height = height;
        c->m_Padding = outerSpacing;
        return c;
    }

    template <int32_t innerSpacing, int32_t outerSpacing, int32_t hJustify = 1>
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
            element->m_HJustify = hJustify;
            element->m_VJustify = 0;
            element->m_X = (1 - hJustify) * (element->m_Width / 2 + outerSpacing);
            height += element->m_Height + innerSpacing;
            if (element->m_Width > width)
                width = element->m_Width;
            c->m_Elements.push_back(element);
        }
        width += 2 * outerSpacing;
        height += outerSpacing - innerSpacing;

        c->m_Width = width;
        c->m_Height = height;
        c->m_Padding = outerSpacing;
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
        g_Renderer->m_Container.m_Elements.push_back(c);
        return c;
    }

    template <bool recursive>
    void Resize(Container *c)
    {
        float maxX = 0;
        float maxY = 0;
        float minX = 0;
        float minY = 0;
        float spacing = c->m_Padding;
        float halfWidth = c->m_Width / 2;
        float halfHeight = c->m_Height / 2;
        for (uint64_t i = 0; i < c->m_Elements.size(); ++i)
        {
            Element *element = c->m_Elements[i];
            if (!element->m_Showing)
                continue;
            if (recursive && dynamic_cast<Container *>(element))
                Resize<true>((Container *) element);
            float x = element->m_X + (element->m_HJustify - 1) * halfWidth;
            float y = element->m_Y + (element->m_VJustify - 1) * halfHeight;
            float elemPos = x - element->m_Width / 2 - spacing;
            if (elemPos < minX)
                minX = elemPos;
            elemPos = y - element->m_Height / 2 - spacing;
            if (elemPos < minY)
                minY = elemPos;
            elemPos = x + element->m_Width / 2 + spacing;
            if (elemPos > maxX)
                maxX = elemPos;
            elemPos = y + element->m_Height / 2 + spacing;
            if (elemPos > maxY)
                maxY = elemPos;
        }
        c->m_Width = maxX - minX;
        c->m_Height = maxY - minY;
    }
}