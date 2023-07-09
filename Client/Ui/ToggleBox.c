#include <Client/Ui/Ui.h>

#include <stdio.h>
#include <stdlib.h>
#include <string.h>

#include <Client/Game.h>
#include <Client/InputData.h>
#include <Client/Renderer/Renderer.h>

void toggle_box_on_event(struct rr_ui_element *this, struct rr_game *game)
{
    if (game->input_data->mouse_buttons_up_this_tick & 1)
        *((uint8_t *) this->data) ^= 1;
}

void toggle_box_render(struct rr_ui_element *this, struct rr_game *game)
{
    struct rr_renderer *renderer = game->renderer;
    rr_renderer_scale(renderer, renderer->scale);
    if (*((uint8_t *) this->data))
        rr_renderer_set_fill(renderer, 0xffbbbbbb);
    else
        rr_renderer_set_fill(renderer, 0xff666666);
    rr_renderer_set_stroke(renderer, 0xff444444);
    rr_renderer_set_line_width(renderer, 6);
    rr_renderer_begin_path(renderer);
    rr_renderer_round_rect(renderer, -this->abs_width / 2, -this->abs_height / 2,
                           this->abs_width, this->abs_height, 6);
    rr_renderer_fill(renderer);
    rr_renderer_stroke(renderer);
}

struct rr_ui_element *rr_ui_toggle_box_init(uint8_t *pointer)
{
    struct rr_ui_element *this = rr_ui_element_init();
    this->data = pointer;
    this->abs_width = this->abs_height = this->width = this->height = 30;
    this->on_event = toggle_box_on_event;
    this->on_render = toggle_box_render;
    return this;
}
