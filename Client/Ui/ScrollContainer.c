#include <Client/Ui/Ui.h>

#include <stdio.h>
#include <stdlib.h>

#include <Client/Game.h>
#include <Client/InputData.h>
#include <Client/Renderer/Renderer.h>

#include <Shared/Utilities.h>

struct scroll_container_metadata
{
    float y;
    float lerp_y;
};

void scroll_bar_poll_events(struct rr_ui_element *this, struct rr_game *game)
{
    if (this->completely_hidden)
        return;
    rr_ui_element_check_if_focused(this, game);
    if (game->focused != this)
        return;
    struct scroll_container_metadata *data = this->data;
    this->elements.start[0]->poll_events(this->elements.start[0], game);
}

void scroll_bar_on_render(struct rr_ui_element *this, struct rr_game *game)
{
    struct scroll_container_metadata *data = this->data;
    this->abs_width = this->width = this->elements.start[0]->width + 5;
    if (rr_ui_mouse_over(this, game) && game->input_data->scroll_delta != 0)
    {
        struct scroll_container_metadata *data = this->data;
        data->y += game->input_data->scroll_delta * 0.4;
        if (data->y < 0)
            data->y = 0;
        else if (data->y > this->elements.start[0]->abs_height - this->abs_height)
            data->y = this->elements.start[0]->abs_height - this->abs_height;
    }
    data->lerp_y = rr_lerp(data->lerp_y, data->y, 0.2);
    struct rr_renderer *renderer = game->renderer;
    rr_renderer_set_stroke(renderer, 0x80000000);
    rr_renderer_set_line_width(renderer, 3);
    rr_renderer_begin_path(renderer);
    
    rr_renderer_begin_path(renderer);
    rr_renderer_rect(renderer, renderer->scale * (-this->abs_width / 2),
                     renderer->scale * (-this->abs_height / 2),
                     renderer->scale * (this->elements.start[0]->width),
                     renderer->scale * (this->abs_height));
    rr_renderer_clip(renderer);
    rr_renderer_translate(renderer, 0, -data->lerp_y * renderer->scale);
    rr_ui_render_element(this->elements.start[0], game);
}

struct rr_ui_element *rr_ui_scroll_container_init(struct rr_ui_element *c,
                                                  float static_h)
{
    struct rr_ui_element *this = rr_ui_element_init();
    struct scroll_container_metadata *data = malloc(sizeof *data);
    rr_ui_container_add_element(this, c);
    data->y = data->lerp_y = 0;
    c->h_justify = -1;
    c->v_justify = -1;
    this->data = data;
    this->abs_height = this->height = static_h;
    this->abs_width = this->width = c->width + 5; // 5 is the scrollbar width
    this->on_render = scroll_bar_on_render;
    this->poll_events = scroll_bar_poll_events;
    return this;
}