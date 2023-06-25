#include <Client/Ui/Element.h>

#include <stdlib.h>

#include <Client/Game.h>
#include <Client/Renderer/Renderer.h>

static void container_on_render(struct rr_ui_element *this, void *_game)
{
    if (this->hidden)
        return;
    struct rr_game *game = _game;
    struct rr_renderer_context_state state;
    struct rr_renderer_context_state state2;
    struct rr_ui_container_metadata *data = this->misc_data;
    struct rr_renderer *renderer = game->renderer;
    rr_renderer_init_context_state(renderer, &state);
    ui_translate(this, renderer);
    if (data->fill_color != 0x00000000)
    {
        rr_renderer_init_context_state(renderer, &state2);
        rr_renderer_set_fill(renderer, data->fill_color);
        rr_renderer_scale(renderer, renderer->scale);
        rr_renderer_begin_path(renderer);
        rr_renderer_round_rect(renderer, -this->width / 2, -this->height / 2, this->width, this->height, 6);
        rr_renderer_fill(renderer);
        if (data->fill_color > 0xff000000)
        {
            renderer->state.filter.amount = 0.2;
            rr_renderer_set_stroke(renderer, data->fill_color);
            rr_renderer_set_line_width(renderer, 6);
            rr_renderer_set_line_cap(renderer, 1);
            rr_renderer_set_line_join(renderer, 1);
            rr_renderer_stroke(renderer);
        }
        rr_renderer_free_context_state(renderer, &state2);
    }
    for (uint32_t i = 0; i < data->elements.size; ++i)
        data->elements.elements[i]->on_render(data->elements.elements[i], game);
    rr_renderer_free_context_state(renderer, &state);
}

struct rr_ui_element *rr_ui_container_add_element(struct rr_ui_element *this, struct rr_ui_element *add)
{
    struct rr_ui_container_metadata *data = this->misc_data;
    data->elements.elements[data->elements.size++] = add;
    add->container = this;
    return add;
}

struct rr_ui_element *rr_ui_container_init()
{
    struct rr_ui_element *element = rr_ui_element_init();
    struct rr_ui_container_metadata *data = malloc(sizeof *data);
    data->elements.size = 0;
    element->misc_data = data;
    element->on_render = container_on_render;
    element->container_flags |= 1;
    return element;
}

struct rr_ui_element *rr_ui_flex_container_init()
{
    struct rr_ui_element *element = rr_ui_container_init();
    element->container_flags |= 2;
    return element;
}