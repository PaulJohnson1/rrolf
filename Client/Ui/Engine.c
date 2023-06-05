#include <Client/Ui/Engine.h>

struct rr_ui_element *rr_ui_make_v_container(uint8_t h_justify, float outer_spacing, float inner_spacing, uint32_t count, ...)
{
    va_list args;
    va_start(args, count);
    struct rr_ui_element *c = rr_ui_init_container();
    c->x = c->y = 0;
    float width = 0; //outer spacing
    float height = outer_spacing;
    for (uint32_t i = 0; i < count; ++i)
    {
        struct rr_ui_element *element = va_arg(args, struct rr_ui_element *);
        element->y = height + element->height / 2;
        element->container = c;
        element->h_justify = h_justify;
        element->v_justify = 0;
        element->x = (1 - h_justify) * (element->width / 2 + outer_spacing);
        height += element->height + inner_spacing;
        if (element->width > width)
            width = element->width;
        rr_ui_container_add_element(c, element);
    }
    width += 2 * outer_spacing;
    height += outer_spacing - inner_spacing;

    c->width = width;
    c->height = height;
    //c->m_Padding = outerSpacing;
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