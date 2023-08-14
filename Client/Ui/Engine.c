#include <Client/Ui/Engine.h>

#include <stdio.h>

#include <Client/Ui/Ui.h>
#include <Shared/Utilities.h>

struct rr_ui_element *rr_ui_h_container_init(struct rr_ui_element *c,
                                             int32_t outer_spacing,
                                             int32_t inner_spacing, ...)
{
    va_list args;
    va_start(args, inner_spacing);
    c->x = c->y = 0;
    float height = 0; // outer spacing
    float width = outer_spacing;
    while (1)
    {
        struct rr_ui_element *element = va_arg(args, struct rr_ui_element *);
        if (element == NULL)
            break;
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
    c->resizeable = rr_ui_h_container;

    struct rr_ui_container_metadata *data = c->data;
    data->outer_spacing = outer_spacing;
    data->inner_spacing = inner_spacing;
    va_end(args);
    return c;
}

struct rr_ui_element *rr_ui_v_container_init(struct rr_ui_element *c,
                                             int32_t outer_spacing,
                                             int32_t inner_spacing, ...)
{
    va_list args;
    va_start(args, inner_spacing);
    c->x = c->y = 0;
    float width = 0; // outer spacing
    float height = outer_spacing;
    while (1)
    {
        struct rr_ui_element *element = va_arg(args, struct rr_ui_element *);
        if (element == NULL)
            break;
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
    c->resizeable = rr_ui_v_container;

    struct rr_ui_container_metadata *data = c->data;
    data->outer_spacing = outer_spacing;
    data->inner_spacing = inner_spacing;
    va_end(args);
    return c;
}

struct rr_ui_element *rr_ui_set_background(struct rr_ui_element *this,
                                           uint32_t bg)
{
    this->fill = bg;
    return this;
}

struct rr_ui_element *rr_ui_set_justify(struct rr_ui_element *c,
                                        int8_t h_justify, int8_t v_justify)
{
    c->h_justify = h_justify;
    c->v_justify = v_justify;
    return c;
}

struct rr_ui_element *rr_ui_h_pad(struct rr_ui_element *c, float pad)
{
    c->x -= c->h_justify * pad;
    return c;
}

struct rr_ui_element *rr_ui_v_pad(struct rr_ui_element *c, float pad)
{
    c->y -= c->v_justify * pad;
    return c;
}

struct rr_ui_element *rr_ui_pad(struct rr_ui_element *c, float pad)
{
    c->x -= c->h_justify * pad;
    c->y -= c->v_justify * pad;
    return c;
}

struct rr_ui_element *rr_ui_justify_all(struct rr_ui_element *c, int8_t pos)
{
    if (c->resizeable == rr_ui_h_container)
        for (uint32_t i = 0; i < c->elements.size; ++i)
            c->elements.start[i]->v_justify = pos;
    else if (c->resizeable == rr_ui_v_container)
        for (uint32_t i = 0; i < c->elements.size; ++i)
            c->elements.start[i]->h_justify = pos;
    return c;
}

void rr_ui_h_container_set(struct rr_ui_element *c)
{
    struct rr_ui_container_metadata *data = c->data;
    float outer_spacing = data->outer_spacing;
    float inner_spacing = data->inner_spacing;
    float height = 0;
    float width = outer_spacing;
    for (uint32_t i = 0; i < c->elements.size; ++i)
    {
        struct rr_ui_element *element = c->elements.start[i];
        element->h_justify = -1;
        element->x = width;
        element->y = (-element->v_justify) * (outer_spacing);
        if (element->completely_hidden || element->width == 0 ||
            element->height == 0)
            continue;

        width += element->width + inner_spacing;
        if (element->height > height)
            height = element->height;
    }
    height += 2 * outer_spacing;
    width += outer_spacing - inner_spacing;

    c->abs_width = width;
    c->abs_height = height;
}

void rr_ui_v_container_set(struct rr_ui_element *c)
{
    struct rr_ui_container_metadata *data = c->data;
    float outer_spacing = data->outer_spacing;
    float inner_spacing = data->inner_spacing;
    float width = 0;
    float height = outer_spacing;
    for (uint32_t i = 0; i < c->elements.size; ++i)
    {
        struct rr_ui_element *element = c->elements.start[i];
        element->v_justify = -1;
        element->y = height;
        element->x = (-element->h_justify) * (outer_spacing);
        if (element->completely_hidden || element->width == 0 ||
            element->height == 0)
            continue;

        height += element->height + inner_spacing;
        if (element->width > width)
            width = element->width;
    }
    width += 2 * outer_spacing;
    height += outer_spacing - inner_spacing;

    c->abs_width = width;
    c->abs_height = height;
}

void rr_ui_choose_container_set(struct rr_ui_element *c)
{
    for (uint32_t i = 0; i < c->elements.size; ++i)
    {
        struct rr_ui_element *element = c->elements.start[i];
        if (element->abs_width > c->abs_width)
            c->abs_width = c->width = element->abs_width;
        if (element->abs_height > c->abs_height)
            c->abs_height = c->height = element->abs_height;
    }
}

void rr_ui_grid_container_set(struct rr_ui_element *c)
{
    struct rr_ui_container_metadata *data = c->data;
    float outer_spacing = data->outer_spacing;
    float inner_spacing = data->inner_spacing;
    uint32_t width = data->width;
    uint32_t count = 0;
    for (uint32_t i = 0; i < c->elements.size; ++i)
    {
        struct rr_ui_element *element = c->elements.start[i];
        element->h_justify = element->v_justify = -1;
        count += 1 - element->completely_hidden;
    }
    uint32_t mod = count % width;
    uint32_t pos = 0;
    float w = 0, h = 0;
    for (uint32_t i = 0; i < c->elements.size; ++i)
    {
        struct rr_ui_element *element = c->elements.start[i];
        w = element->abs_width;
        h = element->abs_height;
        if (count - pos > mod)
            element->x =
                outer_spacing + (pos % data->width) * (w + inner_spacing);
        else
        {
            element->x =
                outer_spacing +
                (pos % data->width + (width - mod) * 0.5) * (w + inner_spacing);
        }
        element->y = outer_spacing + (pos / data->width) * (h + inner_spacing);
        if (element->completely_hidden)
            continue;
        ++pos;
    }
    data->height = (count + (width - 1)) / width;
    c->abs_height = c->height = 2 * outer_spacing +
                                (data->height) * (h + inner_spacing) -
                                inner_spacing;
    c->abs_width = c->width =
        2 * outer_spacing + (data->width) * (h + inner_spacing) - inner_spacing;
}

static void rr_ui_scroll_container_set(struct rr_ui_element *c)
{
    float w = 0;
    for (uint32_t i = 0; i < c->elements.size; ++i)
    {
        struct rr_ui_element *element = c->elements.start[i];
        if (w < element->width)
            w = element->width;
    }
    c->abs_width = c->width = w + 10;
}

void rr_ui_container_refactor(struct rr_ui_element *c, struct rr_game *game)
{
    if (c->elements.size != 0)
    {
        for (uint64_t i = 0; i < c->elements.size; ++i)
        {
            struct rr_ui_element *element = c->elements.start[i];
            element->animation =
                rr_lerp(element->animation, element->should_show(element, game) == 0,
                        0.4 + 0.6 * element->first_frame);
            uint8_t before_hidden = element->completely_hidden;
            element->completely_hidden = element->animation > 0.99;
            if (element->completely_hidden && before_hidden == 0)
                element->on_hide(element, game);
            if (element->completely_hidden)
                continue;
            rr_ui_container_refactor(element, game);
        }
        if (c->resizeable)
        {
            if (c->resizeable == rr_ui_h_container)
                rr_ui_h_container_set(c);
            else if (c->resizeable == rr_ui_v_container)
                rr_ui_v_container_set(c);
            else if (c->resizeable == rr_ui_choose_container)
                rr_ui_choose_container_set(c);
            else if (c->resizeable == rr_ui_grid_container)
                rr_ui_grid_container_set(c);
            else if (c->resizeable == rr_ui_scroll_container)
                rr_ui_scroll_container_set(c);
        }
    }
}
