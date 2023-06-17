#include <Client/Ui/Engine.h>

#include <stdio.h>

struct rr_ui_element *rr_ui_h_container_init(struct rr_ui_element *c, float outer_spacing, float inner_spacing, uint32_t count, ...)
{
    va_list args;
    va_start(args, count);
    c->x = c->y = 0;
    float height = 0; //outer spacing
    float width = outer_spacing;
    for (uint32_t i = 0; i < count; ++i)
    {
        struct rr_ui_element *element = va_arg(args, struct rr_ui_element *);

        element->container = c;
        element->h_justify = 0;
    
        element->lerp_x = element->x = width + element->width / 2;
        element->lerp_y = element->y = (1 - element->v_justify) * (element->height / 2 + outer_spacing);

        width += element->width + inner_spacing;
        if (element->height > height)
            height = element->height;
        rr_ui_container_add_element(c, element);
    }
    height += 2 * outer_spacing;
    width += outer_spacing - inner_spacing;

    c->width = width;
    c->height = height;

    struct rr_ui_container_metadata *data = c->misc_data;
    data->is_horizontal = 1;
    data->outer_spacing = outer_spacing;
    data->inner_spacing = inner_spacing;
    va_end(args);
    return c;
}

struct rr_ui_element *rr_ui_v_container_init(struct rr_ui_element *c, float outer_spacing, float inner_spacing, uint32_t count, ...)
{
    va_list args;
    va_start(args, count);
    c->x = c->y = 0;
    float width = 0; //outer spacing
    float height = outer_spacing;
    for (uint32_t i = 0; i < count; ++i)
    {
        struct rr_ui_element *element = va_arg(args, struct rr_ui_element *);

        element->container = c;
        element->v_justify = 0;

        element->y = height + element->height / 2;
        element->x = (1 - element->h_justify) * (element->width / 2 + outer_spacing);

        height += element->height + inner_spacing;
        if (element->width > width)
            width = element->width;
        rr_ui_container_add_element(c, element);
    }
    width += 2 * outer_spacing;
    height += outer_spacing - inner_spacing;

    c->width = width;
    c->height = height;
    struct rr_ui_container_metadata *data = c->misc_data;
    data->is_horizontal = 0;
    data->outer_spacing = outer_spacing;
    data->inner_spacing = inner_spacing;
    va_end(args);
    return c;
}

struct rr_ui_element *rr_ui_set_justify(struct rr_ui_element *c, uint8_t h_justify, uint8_t v_justify)
{
    c->h_justify = h_justify;
    c->v_justify = v_justify;
    c->x = (1 - h_justify) * c->width / 2;
    c->y = (1 - v_justify) * c->height / 2;
    return c;
}

struct rr_ui_element *rr_ui_pad(struct rr_ui_element *c, float pad)
{ 
    c->x += (1 - c->h_justify) * pad;
    c->y += (1 - c->v_justify) * pad;
    return c;
}

struct rr_ui_element *rr_ui_set_background(struct rr_ui_element *c, uint32_t color)
{ 
    ((struct rr_ui_container_metadata *) c->misc_data)->fill_color = color;
    return c;
}

static void rr_ui_h_container_set(struct rr_ui_element *c, float outer_spacing, float inner_spacing)
{
    struct rr_ui_container_metadata *data = c->misc_data;
    float height = 0;
    float width = outer_spacing;
    for (uint32_t i = 0; i < data->elements.size; ++i)
    {
        struct rr_ui_element *element = data->elements.elements[i];
    
        element->lerp_x = element->x = width + element->width / 2;
        element->lerp_y = element->y = (1 - element->v_justify) * (element->height / 2 + outer_spacing);

        width += element->width + inner_spacing;
        if (element->height > height)
            height = element->height;
    }
    height += 2 * outer_spacing;
    width += outer_spacing - inner_spacing;

    c->width = width;
    c->height = height;
}

static void rr_ui_v_container_set(struct rr_ui_element *c, float outer_spacing, float inner_spacing)
{
    struct rr_ui_container_metadata *data = c->misc_data;
    float width = 0;
    float height = outer_spacing;
    for (uint32_t i = 0; i < data->elements.size; ++i)
    {
        struct rr_ui_element *element = data->elements.elements[i];

        element->y = height + element->height / 2;
        element->x = (1 - element->h_justify) * (element->width / 2 + outer_spacing);

        height += element->height + inner_spacing;
        if (element->width > width)
            width = element->width;
    }
    width += 2 * outer_spacing;
    height += outer_spacing - inner_spacing;

    c->width = width;
    c->height = height;
}

void rr_ui_container_refactor(struct rr_ui_element *c)
{
    struct rr_ui_container_metadata *data = c->misc_data;
    float max_x = 0;
    float max_y = 0;
    float min_x = 0;
    float min_y = 0;
    float spacing = data->outer_spacing; //FIX
    float halfWidth = c->width / 2;
    float halfHeight = c->height / 2;
    for (uint64_t i = 0; i < data->elements.size; ++i)
    {
        struct rr_ui_element *element = data->elements.elements[i];
        if (element->is_resizable_container)
        {
            struct rr_ui_container_metadata *element_data = (element->misc_data);
            if (element_data->is_horizontal)
                rr_ui_h_container_set(element, element_data->outer_spacing, element_data->inner_spacing);
            else
                rr_ui_v_container_set(element, element_data->outer_spacing, element_data->inner_spacing);

            rr_ui_container_refactor(element);
        }
        float x = element->x + (element->h_justify - 1) * halfWidth;
        float y = element->y + (element->v_justify - 1) * halfHeight;
        float elem_pos = x - element->width / 2 - spacing;
        if (elem_pos < min_x)
            min_x = elem_pos;
        elem_pos = y - element->height / 2 - spacing;
        if (elem_pos < min_y)
            min_y = elem_pos;
        elem_pos = x + element->width / 2 + spacing;
        if (elem_pos > max_x)
            max_x = elem_pos;
        elem_pos = y + element->height / 2 + spacing;
        if (elem_pos > max_y)
            max_y = elem_pos;
    }
    c->width = max_x - min_x;
    c->height = max_y - min_y;
}