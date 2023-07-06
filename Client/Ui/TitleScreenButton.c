#include <Client/Ui/Ui.h>

#include <stdio.h>
#include <stdlib.h>
#include <string.h>

#include <Client/Game.h>
#include <Client/InputData.h>
#include <Client/Renderer/Renderer.h>

#include <Shared/pb.h>

static void inventory_toggle_on_render(struct rr_ui_element *this,
                                     struct rr_game *game)
{
    struct rr_renderer *renderer = game->renderer;
    if (game->focused == this)
    {
        renderer->state.filter.amount = 0.2;
    }
    rr_renderer_scale(renderer, renderer->scale);
    rr_renderer_set_fill(renderer, this->fill);
    renderer->state.filter.amount += 0.2;
    rr_renderer_set_stroke(renderer, this->fill);
    rr_renderer_set_line_width(renderer, 6);
    rr_renderer_begin_path(renderer);
    rr_renderer_round_rect(renderer, -this->width / 2, -this->height / 2,
                           this->width, this->height, 6);
    rr_renderer_fill(renderer);
    rr_renderer_stroke(renderer);
}

void inventory_toggle_button_on_event(struct rr_ui_element *this, struct rr_game *game)
{
    if (game->input_data->mouse_buttons_this_tick & 1)
    {
        if (game->ui_open == 1)
            game->ui_open = 0;
        else
            game->ui_open = 1;
    }
}

struct rr_ui_element *rr_ui_inventory_toggle_button_init()
{
    struct rr_ui_element *this = rr_ui_element_init();
    this->fill = 0xffff0000;
    this->abs_width = this->abs_height = this->width = this->height = 60;
    this->on_event = inventory_toggle_button_on_event;
    this->on_render = inventory_toggle_on_render;
    return this;
}