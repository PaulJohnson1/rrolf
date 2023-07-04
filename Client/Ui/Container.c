#include <Client/Ui/Ui.h>

#include <stdlib.h>
#include <string.h>
#include <stdio.h>

#include <Client/Game.h>
#include <Client/Renderer/Renderer.h>

static void container_on_render(struct rr_ui_element *this, struct rr_game *game)
{
    if (this->fill != 0x00000000)
    {
        struct rr_renderer *renderer = game->renderer;
        struct rr_renderer_context_state state2;
        rr_renderer_init_context_state(renderer, &state2);
        rr_renderer_set_fill(renderer, this->fill);
        rr_renderer_scale(renderer, renderer->scale);
        rr_renderer_begin_path(renderer);
        rr_renderer_round_rect(renderer, -this->abs_width / 2, -this->abs_height / 2, this->abs_width, this->abs_height, 6);
        rr_renderer_fill(renderer);
        if (this->fill >= 0xff000000)
        {
            renderer->state.filter.amount = 0.2;
            rr_renderer_set_stroke(renderer, this->fill);
            rr_renderer_set_line_width(renderer, 6);
            rr_renderer_set_line_cap(renderer, 1);
            rr_renderer_set_line_join(renderer, 1);
            rr_renderer_stroke(renderer);
        }
        rr_renderer_free_context_state(renderer, &state2);
    }
    struct rr_ui_container_metadata *data = this->data;
    for (uint32_t i = 0; i < data->size; ++i)
        rr_ui_render_element(data->start[i], game);
}

static void container_2d_on_render(struct rr_ui_element *this, struct rr_game *game)
{
    
    struct rr_ui_container_metadata *data = this->data;
    float outer_spacing = data->outer_spacing;
    float inner_spacing = data->inner_spacing;
    //positioning
    uint32_t pos = 0;
    float h = 0;
    for (uint32_t i = 0; i < data->size; ++i)
    {
        struct rr_ui_element *element = data->start[i];
        if (element->completely_hidden)
            continue;
        element->x = outer_spacing + (pos % data->width) * (element->abs_width + inner_spacing);
        element->y = outer_spacing + (pos / data->width) * (element->abs_height + inner_spacing);
        h = element->abs_height;
        ++pos;
    }
    this->abs_height = this->height = 2 * outer_spacing + ((pos + (data->width - 1)) / data->width) * (h + inner_spacing) - inner_spacing;
    this->abs_width = this->width = 2 * outer_spacing + (data->width) * (h + inner_spacing) - inner_spacing;
    if (this->fill != 0x00000000)
    {
        struct rr_renderer *renderer = game->renderer;
        struct rr_renderer_context_state state2;
        rr_renderer_init_context_state(renderer, &state2);
        rr_renderer_set_fill(renderer, this->fill);
        rr_renderer_scale(renderer, renderer->scale);
        rr_renderer_begin_path(renderer);
        rr_renderer_round_rect(renderer, -this->abs_width / 2, -this->abs_height / 2, this->abs_width, this->abs_height, 6);
        rr_renderer_fill(renderer);
        if (this->fill > 0xff000000)
        {
            renderer->state.filter.amount = 0.2;
            rr_renderer_set_stroke(renderer, this->fill);
            rr_renderer_set_line_width(renderer, 6);
            rr_renderer_set_line_cap(renderer, 1);
            rr_renderer_set_line_join(renderer, 1);
            rr_renderer_stroke(renderer);
        }
        rr_renderer_free_context_state(renderer, &state2);
    }
    for (uint32_t i = 0; i < data->size; ++i)
        rr_ui_render_element(data->start[i], game);
}

static void container_poll_events(struct rr_ui_element *this, struct rr_game *game)
{
    if (this->completely_hidden)
        return;
    rr_ui_element_check_if_focused(this, game);
    if (game->focused != this)
        return;
    struct rr_ui_container_metadata *data = this->data;
    for (uint32_t i = 0; i < data->size; ++i)
       data->start[i]->poll_events(data->start[i], game);
}


struct rr_ui_element *rr_ui_container_add_element(struct rr_ui_element *this, struct rr_ui_element *add)
{
    struct rr_ui_container_metadata *data = this->data;
    if (++data->size == data->capacity)
    {
        struct rr_ui_element **_new = malloc((sizeof *_new) * (data->capacity *= 2));
        memcpy(_new, data->start, data->size * (sizeof *_new));
        free(data->start);
        data->start = _new;
    }
    data->start[data->size - 1] = add;
    add->container = this;
    return add;
}

struct rr_ui_element *rr_ui_container_init()
{
    struct rr_ui_element *this = rr_ui_element_init();
    struct rr_ui_container_metadata *data = malloc(sizeof *data);
    data->size = 0;
    data->capacity = 2;
    data->start = malloc(sizeof (*data->start) * data->capacity);
    this->data = data;
    this->on_render = container_on_render;
    this->poll_events = container_poll_events;
    this->resizeable = 1; //shows that it is resizeable
    return this; 
}

struct rr_ui_element *rr_ui_flex_container_init()
{
    struct rr_ui_element *this = rr_ui_element_init();
    struct rr_ui_container_metadata *data = malloc(sizeof *data);
    data->size = 0;
    data->capacity = 2;
    data->start = malloc(sizeof (*data->start) * data->capacity);
    this->data = data;
    this->on_render = container_on_render;
    this->poll_events = container_poll_events;
    this->resizeable = 1; //shows that it is resizeable and fits the size of its container
    return this; 
}

struct rr_ui_element *rr_ui_2d_container_init(uint8_t width, uint8_t height, float outer_spacing, float inner_spacing)
{
    struct rr_ui_element *this = rr_ui_element_init();
    struct rr_ui_container_metadata *data = malloc(sizeof *data);
    data->size = 0;
    data->capacity = 2;
    data->start = malloc(sizeof (*data->start) * data->capacity);
    data->width = width;
    data->height = height;
    data->outer_spacing = outer_spacing;
    data->inner_spacing = inner_spacing;
    this->data = data;
    this->on_render = container_2d_on_render;
    this->poll_events = container_poll_events;
    this->resizeable = 0; //shows that it is NOT resizeable
    return this; 
}