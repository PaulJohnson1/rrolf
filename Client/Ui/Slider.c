#include <Client/Ui/Ui.h>

#include <stdio.h>
#include <stdlib.h>

#include <Client/Game.h>
#include <Client/InputData.h>
#include <Client/Ui/Engine.h>

#include <Shared/Utilities.h>

struct rr_ui_slider_metadata
{
    float *value;
    uint8_t dragging;
};

static void h_slider_on_render(struct rr_ui_element *this, struct rr_game *game)
{
    struct rr_renderer *renderer = game->renderer;
    struct rr_ui_slider_metadata *data = this->data;

    // Render the slider track
    rr_renderer_scale(renderer, renderer->scale);
    rr_renderer_set_line_width(renderer, this->abs_height / 6);
    rr_renderer_set_fill(renderer, this->fill);
    rr_renderer_set_line_cap(renderer, 1);
    renderer->state.filter.amount = 0.2;
    rr_renderer_set_stroke(renderer, this->fill);

    rr_renderer_begin_path(renderer);
    rr_renderer_move_to(renderer, -(this->abs_width - this->abs_height) / 2, 0);
    rr_renderer_line_to(renderer, (this->abs_width - this->abs_height) / 2, 0);
    rr_renderer_stroke(renderer);
    float offset = (this->abs_width - this->abs_height) * (*data->value - 0.5);
    rr_renderer_begin_path(renderer);
    rr_renderer_arc(renderer, offset, 0, this->abs_height / 2);
    rr_renderer_fill(renderer);
    if (rr_ui_mouse_over(this, game) &&
        game->input_data->mouse_buttons_down_this_tick & 1)
    {
        data->dragging = 1;
    }
    else if (game->input_data->mouse_buttons_up_this_tick & 1 && data->dragging)
    {
        data->dragging = 0;
        game->block_ui_input = 1;
    }
    if (data->dragging)
    {
        float real_x = (game->input_data->mouse_x -
                        (this->abs_x - (this->abs_width - this->abs_height) /
                                           2 * renderer->scale)) /
                       ((this->abs_width - this->abs_height) * renderer->scale);
        *data->value = rr_fclamp(real_x, 0, 1);
    }
}

struct rr_ui_element *rr_ui_h_slider_init(float width, float height,
                                          float *value)
{
    struct rr_ui_element *this = rr_ui_element_init();
    struct rr_ui_slider_metadata *data = malloc(sizeof *data);
    data->value = value;
    data->dragging = 0;
    this->data = data;
    this->abs_width = this->width = width;
    this->abs_height = this->height = height;
    this->on_render = h_slider_on_render;
    this->fill = 0xff666666;
    return this;
}
