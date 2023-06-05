#include <Client/Ui/Element.h>

#include <stdlib.h>
#include <string.h>

#include <Client/Game.h>
#include <Client/Renderer/Renderer.h>

static void default_on_render(struct rr_ui_element *this, void *_captures)
{
    //does nothing
    return;
}

void ui_translate(struct rr_ui_element *this, struct rr_renderer *renderer)
{
    rr_renderer_translate(renderer, (this->x + (this->h_justify - 1) * this->container->width / 2) * renderer->scale, (this->y + (this->v_justify - 1) * this->container->height / 2) * renderer->scale); // necessary btw
}


struct rr_ui_element *rr_ui_init_element()
{
    struct rr_ui_element *element = malloc(sizeof *element);
    memset(element, 0, sizeof *element);
    element->h_justify = 1;
    element->v_justify = 1;
    return element;
}

