#include <Client/Ui/Element.h>

#include <stdlib.h>
#include <string.h>

#include <Client/Game.h>
#include <Client/Renderer/Renderer.h>

#include <Shared/Utilities.h>

static void default_on_render(struct rr_ui_element *this, void *_captures)
{
    if (this->hidden)
        return;
    //does nothing
    return;
}

void ui_translate(struct rr_ui_element *this, struct rr_renderer *renderer)
{
    this->lerp_x = rr_lerp(this->lerp_x, this->x, 0.2);
    this->lerp_y = rr_lerp(this->lerp_y, this->y, 0.2);
    rr_renderer_translate(renderer, (this->lerp_x + (this->h_justify - 1) * this->container->width / 2) * renderer->scale, 
    (this->lerp_y + (this->v_justify - 1) * this->container->height / 2) * renderer->scale); // necessary btw
}

void rr_ui_choose_element_on_render(struct rr_ui_element *this, void *_game)
{
    struct rr_ui_choose_element_metadata *data = this->misc_data;
    struct rr_game *game = _game;
    if (this->hidden)
        data->b->on_render(data->b, _game);
    else
        data->a->on_render(data->a, _game);
}

struct rr_ui_element *rr_ui_element_init()
{
    struct rr_ui_element *element = malloc(sizeof *element);
    memset(element, 0, sizeof *element);
    element->h_justify = 1;
    element->v_justify = 1;
    return element;
}

struct rr_ui_element *rr_ui_static_space_init(float s)
{
    struct rr_ui_element *element = rr_ui_element_init();
    element->width = element->height = s;
    element->on_render = default_on_render;
    return element;
}

struct rr_ui_element *rr_ui_choose_element_init(struct rr_ui_element *a, struct rr_ui_element *b)
{
    struct rr_ui_element *element = rr_ui_element_init();
    struct rr_ui_choose_element_metadata *data = malloc(sizeof *data);
    data->a = a;
    data->b = b;
    element->misc_data = data;
    element->width = a->width > b->width ? a->width : b->width;
    element->height = a->height > b->height ? a->height : b->height;
    element->on_render = rr_ui_choose_element_on_render;
    element->hidden = rand() & 1;
    return element;
}