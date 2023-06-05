#include <Client/Ui/Element.h>

#include <stdlib.h>

#include <Client/Game.h>
#include <Client/Renderer/Renderer.h>

static void container_on_render(struct rr_ui_element *this, void *_game)
{
    struct rr_game *game = _game;
    struct rr_renderer_context_state state;
    rr_renderer_init_context_state(game->renderer, &state);
    ui_translate(this, game->renderer);
    //if (this->container != this)
        //rr_renderer_fill_rect(game->renderer, -this->width / 2, -this->height / 2, this->width, this->height);
    for (uint32_t i = 0; i < this->elements.size; ++i)
        if(this->elements.elements[i]->hidden == 0)
            this->elements.elements[i]->on_render(this->elements.elements[i], game);
    rr_renderer_free_context_state(game->renderer, &state);
}

void rr_ui_container_add_element(struct rr_ui_element *this, struct rr_ui_element *add)
{
    this->elements.elements[this->elements.size++] = add;
    add->container = this;
}

struct rr_ui_element *rr_ui_init_container()
{
    struct rr_ui_element *element = rr_ui_init_element();
    struct rr_ui_container_metadata *data = malloc(sizeof *data);
    element->misc_data = data;
    element->on_render = container_on_render;
    return element;
}