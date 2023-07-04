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
        element->h_justify = -1;
        element->x = width;
        element->y = (-element->v_justify) * (outer_spacing);

        width += element->width + inner_spacing;
        if (element->height > height)
            height = element->height;
        rr_ui_container_add_element(c, element);
    }
    height += 2 * outer_spacing;
    width += outer_spacing - inner_spacing;

    c->abs_width = c->width = width;
    c->abs_height = c->height = height;

    struct rr_ui_container_metadata *data = c->data;
    data->type = 1;
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
        element->v_justify = -1;
        element->y = height;
        element->x = (-element->h_justify) * (outer_spacing);

        height += element->height + inner_spacing;
        if (element->width > width)
            width = element->width;
        rr_ui_container_add_element(c, element);
    }
    width += 2 * outer_spacing;
    height += outer_spacing - inner_spacing;

    c->abs_width = c->width = width;
    c->abs_height = c->height = height;

    struct rr_ui_container_metadata *data = c->data;
    data->type = 0;
    data->outer_spacing = outer_spacing;
    data->inner_spacing = inner_spacing;
    va_end(args);
    return c;
}

struct rr_ui_element *rr_ui_set_background(struct rr_ui_element *this, uint32_t bg)
{
    this->fill = bg;
    return this;
}

struct rr_ui_element *rr_ui_set_justify(struct rr_ui_element *c, int8_t h_justify, int8_t v_justify)
{
    c->h_justify = h_justify;
    c->v_justify = v_justify;
    return c;
}

struct rr_ui_element *rr_ui_pad(struct rr_ui_element *c, float pad)
{ 
    c->x -= c->h_justify * pad;
    c->y -= c->v_justify * pad;
    return c;
}

static void rr_ui_h_container_set(struct rr_ui_element *c, float outer_spacing, float inner_spacing)
{
    struct rr_ui_container_metadata *data = c->data;
    float height = 0;
    float width = outer_spacing;
    for (uint32_t i = 0; i < data->size; ++i)
    {
        struct rr_ui_element *element = data->start[i];
        if (element->completely_hidden)
            continue;
        element->x = width;
        element->y = (-element->v_justify) * (outer_spacing);

        width += element->width + inner_spacing;
        if (element->height > height)
            height = element->height;
    }
    height += 2 * outer_spacing;
    width += outer_spacing - inner_spacing;

    c->abs_width = c->width = width;
    c->abs_height = c->height = height;
    if (c->resizeable == 2)
    {
        if (c->container->width > c->width)
            c->width = c->container->width;
    }
}

static void rr_ui_v_container_set(struct rr_ui_element *c, float outer_spacing, float inner_spacing)
{
    struct rr_ui_container_metadata *data = c->data;
    float width = 0;
    float height = outer_spacing;
    for (uint32_t i = 0; i < data->size; ++i)
    {
        struct rr_ui_element *element = data->start[i];
        if (element->completely_hidden)
            continue;
        element->y = height;
        element->x = (-element->h_justify) * (outer_spacing);

        height += element->height + inner_spacing;
        if (element->width > width)
            width = element->width;
    }
    width += 2 * outer_spacing;
    height += outer_spacing - inner_spacing;

    c->abs_width = c->width = width;
    c->abs_height = c->height = height;
    if (c->resizeable == 2)
    {
        if (c->container->height > c->height)
            c->height = c->container->height;
    }
}

void rr_ui_container_refactor(struct rr_ui_element *c)
{ 

    struct rr_ui_container_metadata *data = c->data;
    for (uint64_t i = 0; i < data->size; ++i)
    {
        struct rr_ui_element *element = data->start[i];
        if (element->completely_hidden)
            continue;
        if (element->resizeable)
            rr_ui_container_refactor(element);
    }
    if (c->resizeable == 1)
    {
        if (data->type == 1)
            rr_ui_h_container_set(c, data->outer_spacing, data->inner_spacing);
        else
            rr_ui_v_container_set(c, data->outer_spacing, data->inner_spacing);
    }
}