#include <Client/Ui/Element.h>

#include <stdlib.h>

#include <Client/Game.h>
#include <Client/InputData.h>
#include <Client/Renderer/Renderer.h>
#include <Client/Renderer/RenderFunctions.h>

struct paired_button_metadata
{
    struct rr_ui_element *pair;
};

static void paired_button_on_render(struct rr_ui_element *this, void *_game)
{
    if (this->hidden)
        return;
    struct rr_game *game = _game;
    struct rr_renderer *renderer = game->renderer;
    struct paired_button_metadata *data = this->misc_data;
    struct rr_renderer_context_state state;
    rr_renderer_init_context_state(renderer, &state);
    rr_renderer_set_fill(renderer, 0xff999999);
    rr_renderer_set_line_width(renderer, 6);
    renderer->state.filter.amount = 0.2;
    rr_renderer_set_stroke(renderer, 0xff999999);
    ui_translate(this, renderer);
    rr_renderer_scale(renderer, renderer->scale);
    if (rr_button_is_touching_mouse(this, game))
    {
        if (game->input_data->mouse_buttons_this_tick & 1)
        {
            data->pair->hidden = 0;
            data->pair->y *= -1;
        }
    }    
    rr_renderer_begin_path(renderer);
    rr_renderer_round_rect(renderer, -this->width / 2, -this->height / 2, this->width, this->height, 6);
    rr_renderer_fill(renderer);
    rr_renderer_stroke(renderer);
    rr_renderer_free_context_state(renderer, &state);
    data->pair->container = this->container;
    data->pair->x = data->pair->width / 2 + 30 + this->width; //manual padding
    data->pair->on_render(data->pair, _game);
}

struct rr_ui_element *rr_ui_paired_button_init(struct rr_ui_element *pair)
{
    struct rr_ui_element *element = rr_ui_element_init();
    struct paired_button_metadata *data = malloc(sizeof *data);
    data->pair = pair;
    element->width = 60;
    element->height = 60;
    element->misc_data = data;
    element->on_render = paired_button_on_render;
    return element;
}
