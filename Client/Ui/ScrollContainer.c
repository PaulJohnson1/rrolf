#include <Client/Ui/Element.h>

#include <stdlib.h>
#include <stdio.h>

#include <Client/Game.h>
#include <Client/InputData.h>
#include <Client/Renderer/Renderer.h>
#include <Client/Ui/Engine.h>

#include <Shared/Utilities.h>

struct scroll_container_metadata
{
    float current_y;
    float lerp_current_y;
    struct rr_ui_element *containing;
    uint32_t background;
};

static void scroll_container_on_render(struct rr_ui_element *this, void *_game)
{
    if (this->hidden)
        return;
    struct rr_game *game = _game;
    struct rr_renderer *renderer = game->renderer;
    struct scroll_container_metadata *data = this->misc_data;
    struct rr_renderer_context_state state;
    rr_renderer_init_context_state(renderer, &state);
    ui_translate(this, renderer);
    if (rr_button_is_touching_mouse(this, game))
    {
        data->current_y += game->input_data->scroll_delta * 0.1;
        if (data->current_y < 0)
            data->current_y = 0;
        else if (data->current_y > data->containing->height - this->height)
            data->current_y = data->containing->height - this->height;
    }
    data->lerp_current_y = rr_lerp(data->lerp_current_y, data->current_y, 0.1);
    if (data->background != 0x12345678)
    {
        struct rr_renderer_context_state state2;
        rr_renderer_init_context_state(renderer, &state2);
        rr_renderer_scale(renderer, renderer->scale);
        rr_renderer_set_fill(renderer, data->background);
        rr_renderer_begin_path(renderer);
        rr_renderer_round_rect(renderer, -this->width / 2, -this->height / 2, this->width, this->height, 6);
        rr_renderer_fill(renderer);
        rr_renderer_clip(renderer);
        {
            struct rr_renderer_context_state state3;
            rr_renderer_init_context_state(renderer, &state3);
            rr_renderer_translate(renderer, 0, -data->lerp_current_y);
            rr_renderer_scale(renderer, 1 / renderer->scale);
            data->containing->on_render(data->containing, game);
            rr_renderer_free_context_state(renderer, &state3);        
        }
        renderer->state.filter.amount = 0.2;
        rr_renderer_set_stroke(renderer, data->background);
        rr_renderer_set_line_width(renderer, 12);
        rr_renderer_set_line_cap(renderer, 1);
        rr_renderer_set_line_join(renderer, 1);
        rr_renderer_begin_path(renderer);
        rr_renderer_round_rect(renderer, -this->width / 2, -this->height / 2, this->width, this->height, 6);
        rr_renderer_stroke(renderer);
        rr_renderer_translate(renderer, 0, data->lerp_current_y);
        rr_renderer_set_stroke(renderer, 0xa0000000);
        rr_renderer_set_line_cap(renderer, 1);
        rr_renderer_set_line_width(renderer, 10);
        rr_renderer_begin_path(renderer);
        rr_renderer_move_to(renderer, this->width / 2 - 15, -this->height / 2 + 20);
        rr_renderer_line_to(renderer, this->width / 2 - 15, -this->height / 2 + (this->height - 30) * (this->height - 30) / data->containing->height + 20);
        rr_renderer_stroke(renderer);
        rr_renderer_free_context_state(renderer, &state2);
    }
    rr_renderer_free_context_state(renderer, &state);
}

struct rr_ui_element *rr_ui_scroll_container_init(struct rr_ui_element *element, float height, uint32_t background)
{
    float pad = 10;
    struct rr_ui_element *this = rr_ui_element_init();
    struct scroll_container_metadata *data = malloc(sizeof *data);
    element->container = this;
    rr_ui_set_justify(
        element
    , 0, 0);
    data->current_y = 0;
    data->containing = element;
    data->background = background;
    this->misc_data = data;
    this->width = pad + element->width + 10 + pad;
    this->height = height;
    this->on_render = scroll_container_on_render;
    return this;
}
