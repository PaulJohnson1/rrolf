#include <Client/Ui/Ui.h>

#include <stdlib.h>
#include <string.h>
#include <stdio.h>

#include <Client/Game.h>
#include <Client/Renderer/Renderer.h>

struct text_metadata
{
    char const *text;
    float size;
};

static void text_on_render(struct rr_ui_element *this, struct rr_game *game)
{
    struct text_metadata *data = this->data;
    struct rr_renderer *renderer = game->renderer;
    rr_renderer_scale(renderer, renderer->scale);
    this->abs_width = this->width = rr_renderer_get_text_size(data->text) * this->height;
    rr_renderer_set_text_baseline(renderer, 1);
    rr_renderer_set_text_align(renderer, 1);
    rr_renderer_set_fill(renderer, this->fill);
    rr_renderer_set_stroke(renderer, 0xff222222);
    rr_renderer_set_text_size(renderer, data->size);
    rr_renderer_set_line_width(renderer, data->size * 0.12);
    rr_renderer_stroke_text(renderer, data->text, 0, 0);
    rr_renderer_fill_text(renderer, data->text, 0, 0);
}

struct rr_ui_element *rr_ui_text_init(char const *text, float size, uint32_t fill)
{
    struct rr_ui_element *this = rr_ui_element_init();
    struct text_metadata *data = malloc(sizeof *data);
    this->abs_height = this->height = size;
    this->abs_width = this->width = rr_renderer_get_text_size(text) * this->height;
    this->fill = fill;
    this->height = data->size = size;
    data->text = text;
    this->data = data;
    this->on_render = text_on_render;
    return this;
}