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
    this->abs_width = this->width = data->a->abs_width > data->b->abs_width
                                        ? data->a->abs_width
                                        : data->b->abs_width;
    this->abs_height = this->height = data->a->abs_height > data->b->abs_height
                                          ? data->a->abs_height
                                          : data->b->abs_height;
    if (data->choose(this, game))
        rr_ui_render_element(data->a, game);
    else
        rr_ui_render_element(data->b, game);
}

struct rr_ui_element *rr_ui_choose_element_init(
    struct rr_ui_element *a, struct rr_ui_element *b,
    uint8_t (*choose)(struct rr_ui_element *, struct rr_game *))
{
    struct rr_ui_element *this = rr_ui_element_init();
    struct rr_ui_choose_element_metadata *data = malloc(sizeof *data);
    data->a = a;
    data->b = b;
    a->container = b->container = this;
    data->choose = choose;
    this->data = data;
    this->abs_width = this->width =
        a->abs_width > b->abs_width ? a->abs_width : b->abs_width;
    this->abs_height = this->height =
        a->abs_height > b->abs_height ? a->abs_height : b->abs_height;
    this->on_render = choose_element_on_render;
    return this;
}