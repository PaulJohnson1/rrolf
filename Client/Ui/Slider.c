#include <stdio.h>

#include <Client/Game.h>
#include <Client/InputData.h>
#include <Client/Ui/Engine.h>

struct rr_ui_slider_metadata
{
    float *value;
    int dragging;
    // float drag_offset;
};

static void h_slider_on_render(struct rr_ui_element *this, struct rr_game *game)
{
    struct rr_renderer *renderer = game->renderer;
    struct rr_ui_slider_metadata *data = this->data;

    // Render the slider track
    rr_renderer_scale(renderer, renderer->scale);
    rr_renderer_set_fill(renderer, this->fill);
    rr_renderer_begin_path(renderer);
    rr_renderer_round_rect(renderer, -this->abs_width / 2,
                           -this->abs_height / 2, this->abs_width,
                           this->abs_height, 5);
    rr_renderer_fill(renderer);

    // Render the slider thumb
    // float thumb_pos = (this->abs_width * game->renderer->scale) *
    // *data->value; rr_renderer_set_fill(renderer, 0xffffffff);
    // rr_renderer_begin_path(renderer);
    // rr_renderer_arc(renderer, thumb_pos - this->abs_height, 0,
    //                 this->abs_height);
    // rr_renderer_fill(renderer);
    // Render the slider thumb
    float thumb_pos =
        (this->abs_width - this->abs_height) * *data->value / 2; // * 2 - 1;
    rr_renderer_set_fill(renderer, 0xffffffff);
    rr_renderer_begin_path(renderer);
    rr_renderer_arc(renderer, thumb_pos, 0, 10);
    rr_renderer_fill(renderer);
}

static void h_slider_on_event(struct rr_ui_element *this, struct rr_game *game)
{
    struct rr_ui_slider_metadata *data = this->data;
    if (game->input_data->mouse_buttons_down_this_tick & 1)
    {
        // Calculate the new value based on the mouse position
        float mouse_x = game->input_data->mouse_x / game->renderer->scale;
        float thumb_pos =
            (this->abs_width * game->renderer->scale) * *data->value;
        // if (mouse_x >= thumb_pos && mouse_x <= thumb_pos + this->abs_height)
        // {
        data->dragging = 1;
        // data->drag_offset = 0; // mouse_x - thumb_pos;
        // }
    }
    else if (game->input_data->mouse_buttons_up_this_tick & 1)
    {
        data->dragging = 0;
    }
    if (data->dragging)
    {
        // Update the value based on the mouse position
        float mouse_x = game->input_data->mouse_x / game->renderer->scale;
        float thumb_pos = mouse_x - this->abs_x;
        *data->value = thumb_pos / this->abs_width;
        if (*data->value < -1)
            *data->value = -1;
        if (*data->value > 1)
            *data->value = 1;
        *data->value = *data->value + 0.5;
        // float new_value = (thumb_pos / (this->abs_width - this->abs_height))
        // *
        //                       (data->max_value - data->min_value) +
        //                   data->min_value;
        // if (new_value < data->min_value)
        //     new_value = data->min_value;
        // else if (new_value > data->max_value)
        //     new_value = data->max_value;
        // *data->value = new_value;
    }
}

struct rr_ui_element *rr_ui_h_slider_init(float width, float height,
                                          float *value)
{
    struct rr_ui_element *this = rr_ui_element_init();
    struct rr_ui_slider_metadata *data = malloc(sizeof *data);
    data->value = value;
    this->data = data;
    this->abs_width = this->width = width;
    this->abs_height = this->height = height;
    this->on_render = h_slider_on_render;
    this->on_event = h_slider_on_event;
    this->fill = 0xffcccccc;
    return this;
}

// struct rr_ui_element *rr_ui_v_slider_init(float width, float height,
//                                           float min_value, float max_value,
//                                           float *value);

// static void v_slider_on_render(struct rr_ui_element *this,
//                                struct rr_game *game);
// static void v_slider_on_event(struct rr_ui_element *this, struct rr_game
// *game);

// struct rr_ui_element *rr_ui_v_slider_init(float width, float height,
//                                           float min_value, float max_value,
//                                           float *value)
// {
//     struct rr_ui_element *this = rr_ui_element_init();
//     struct rr_ui_slider_metadata *data = malloc(sizeof *data);
//     data->min_value = min_value;
//     data->max_value = max_value;
//     data->value = value;
//     this->data = data;
//     this->abs_width = this->width = width;
//     this->abs_height = this->height = height;
//     this->on_render = v_slider_on_render;
//     this->on_event = v_slider_on_event;
//     this->fill = 0xffcccccc;
//     return this;
// }

// static void v_slider_on_render(struct rr_ui_element *this, struct rr_game
// *game)
// {
//     struct rr_renderer *renderer = game->renderer;
//     struct rr_ui_slider_metadata *data = this->data;

//     // Render the slider track
//     rr_renderer_scale(renderer, renderer->scale);
//     rr_renderer_set_fill(renderer, this->fill);
//     rr_renderer_begin_path(renderer);
//     rr_renderer_round_rect(renderer, -this->abs_width / 2,
//                            -this->abs_height / 2, this->abs_width,
//                            this->abs_height, this->abs_width / 2);
//     rr_renderer_fill(renderer);

//     // Render the slider thumb
//     float thumb_pos = (this->abs_height - this->abs_width) *
//                       (*data->value - data->min_value) /
//                       (data->max_value - data->min_value);
//     rr_renderer_set_fill(renderer, 0xffffffff);
//     rr_renderer_begin_path(renderer);
//     rr_renderer_round_rect(renderer, -this->abs_width / 2,
//                            thumb_pos - this->abs_width / 2, this->abs_width,
//                            this->abs_width, this->abs_width / 2);
//     rr_renderer_fill(renderer);
// }

// static void v_slider_on_event(struct rr_ui_element *this, struct rr_game
// *game)
// {
//     struct rr_ui_slider_metadata *data = this->data;
//     if (game->input_data->mouse_buttons_down_this_tick & 1)
//     {
//         // Calculate the new value based on the mouse position
//         float mouse_y = game->input_data->mouse_y / game->renderer->scale;
//         float thumb_pos = (this->abs_height - this->abs_width) *
//                           (*data->value - data->min_value) /
//                           (data->max_value - data->min_value);
//         if (mouse_y >= thumb_pos && mouse_y <= thumb_pos + this->abs_width)
//         {
//             data->dragging = 1;
//             data->drag_offset = mouse_y - thumb_pos;
//         }
//     }
//     else if (game->input_data->mouse_buttons_up_this_tick & 1)
//     {
//         data->dragging = 0;
//     }
//     if (data->dragging)
//     {
//         // Update the value based on the mouse position
//         float mouse_y = game->input_data->mouse_y / game->renderer->scale;
//         float thumb_pos = mouse_y - data->drag_offset;
//         float new_value = (thumb_pos / (this->abs_height - this->abs_width))
//         *
//                               (data->max_value - data->min_value) +
//                           data->min_value;
//         if (new_value < data->min_value)
//             new_value = data->min_value;
//         else if (new_value > data->max_value)
//             new_value = data->max_value;
//         *data->value = new_value;
//     }
// }
