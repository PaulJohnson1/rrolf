#include <Client/Ui/Element.h>

#include <stdlib.h>
#include <stdio.h>

#include <Client/Ui/Engine.h>
#include <Client/Game.h>
#include <Client/Renderer/Renderer.h>

struct squad_container_metadata
{
    uint8_t pos;
};

static void squad_container_on_render(struct rr_ui_element *this, void *_game)
{
    struct rr_game *game = _game;
    struct rr_ui_choose_element_metadata *data = this->misc_data;
    this->hidden = 1 - game->squad_members[data->info].in_use;
    rr_ui_choose_element_on_render(this, _game);
}

struct rr_ui_element *rr_ui_squad_container_init(uint8_t spot)
{
    struct rr_ui_element *a = rr_ui_v_container_init(
        rr_ui_container_init(), 10, 10, 2,
        rr_ui_flower_icon_init(25),
        rr_ui_text_init("Flower", 16)
    );
    struct rr_ui_element *b = rr_ui_text_init("Empty", 16);
    struct rr_ui_element *choose = rr_ui_choose_element_init(a, b);
    struct rr_ui_choose_element_metadata *data = choose->misc_data;
    data->info = spot;
    choose->on_render = squad_container_on_render;
    return rr_ui_set_background(
        rr_ui_v_container_init(rr_ui_container_init(), 10, 10, 1,
            choose
        ), 0xff0245ba
    );
}