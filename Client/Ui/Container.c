#include <Client/Ui/Element.h>

#include <stdlib.h>

#include <Client/Game.h>
#include <Client/Renderer/Renderer.h>

static void container_on_render(struct rr_ui_element *this, void *_game)
{
    struct rr_game *game = _game;
    struct rr_renderer_context_state state;
    struct rr_ui_container_metadata *data = this->misc_data;
    rr_renderer_init_context_state(game->renderer, &state);
    ui_translate(this, game->renderer);
    //if (this->container != this)
        //rr_renderer_fill_rect(game->renderer, -this->width / 2, -this->height / 2, this->width, this->height);
    for (uint32_t i = 0; i < data->elements.size; ++i)
        if(data->elements.elements[i]->hidden == 0)
            data->elements.elements[i]->on_render(data->elements.elements[i], game);
    rr_renderer_free_context_state(game->renderer, &state);
}

struct rr_ui_element *rr_ui_container_add_element(struct rr_ui_element *this, struct rr_ui_element *add)
{
    struct rr_ui_container_metadata *data = this->misc_data;
    data->elements.elements[data->elements.size++] = add;
    add->container = this;
    return add;
}

struct rr_ui_element *rr_ui_init_container()
{
    struct rr_ui_element *element = rr_ui_init_element();
    struct rr_ui_container_metadata *data = malloc(sizeof *data);
    data->elements.size = 0;
    element->misc_data = data;
    element->on_render = container_on_render;
    return element;
}