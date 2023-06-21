#include <Client/Ui/Element.h>

#include <string.h>
#include <stdlib.h>

#include <Client/Game.h>
#include <Client/Renderer/Renderer.h>

struct text_metadata
{
    float size;
    char const *text;
    uint32_t fill;
};

static void text_on_render(struct rr_ui_element *this, void *_game)
{
    if (this->hidden)
        return;
    struct rr_game *game = _game;
    struct rr_renderer *renderer = game->renderer;
    struct text_metadata *data = this->misc_data;
    struct rr_renderer_context_state state;
    rr_renderer_init_context_state(renderer, &state);
    ui_translate(this, renderer);
    rr_renderer_scale(renderer, renderer->scale);
    rr_renderer_set_fill(renderer, data->fill);
    rr_renderer_set_stroke(renderer, 0xff000000);
    rr_renderer_set_text_size(renderer, this->height);
    rr_renderer_set_line_width(renderer, this->height * 0.12);
    rr_renderer_set_text_align(renderer, 1);
    rr_renderer_set_text_baseline(renderer, 1);
    rr_renderer_stroke_text(renderer, data->text, 0, 0);
    rr_renderer_fill_text(renderer, data->text, 0, 0);
    rr_renderer_free_context_state(renderer, &state);
}

struct rr_ui_element *rr_ui_text_init(char const *str, float size, uint32_t fill)
{
    struct text_metadata *data = malloc(sizeof *data);
    struct rr_ui_element *element = rr_ui_element_init();
    element->on_render = text_on_render;
    data->text = str;
    element->height = size;
    element->width = rr_renderer_get_text_size(str) * size;
    element->misc_data = data;
    data->fill = fill;

    return element;
}