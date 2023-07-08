#include <Client/Ui/Ui.h>

#include <stdio.h>
#include <stdlib.h>
#include <string.h>

#include <Client/Game.h>
#include <Client/Renderer/Renderer.h>

static void choose_element_on_render(struct rr_ui_element *this,
                                     struct rr_game *game)
{
    struct rr_ui_choose_element_metadata *data = this->data;
    rr_ui_render_element(this->elements.start[data->choose(this, game)], game);
}

struct rr_ui_element *rr_ui_choose_element_init(
    struct rr_ui_element *a, struct rr_ui_element *b,
    uint8_t (*choose)(struct rr_ui_element *, struct rr_game *))
{
    struct rr_ui_element *this = rr_ui_element_init();
    struct rr_ui_choose_element_metadata *data = malloc(sizeof *data);
    data->choose = choose;
    this->data = data;
    this->resizeable = rr_ui_choose_container;
    rr_ui_container_add_element(this, b);
    rr_ui_container_add_element(this, a);
    this->on_render = choose_element_on_render;
    return this;
}