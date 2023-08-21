#include <Client/Ui/Ui.h>

#include <stdio.h>
#include <stdlib.h>
#include <string.h>

#include <Client/Game.h>
#include <Client/Renderer/Renderer.h>

static void container_on_render(struct rr_ui_element *this,
                                struct rr_game *game)
{
    if (this->h_flex)
    {
        struct rr_ui_container_metadata *data = this->container->data;
        if (this->abs_width <
            this->container->abs_width - data->outer_spacing * 2)
            this->abs_width =
                this->container->abs_width - data->outer_spacing * 2;
    }
    if (this->v_flex)
    {
        struct rr_ui_container_metadata *data = this->container->data;
        if (this->abs_height <
            this->container->abs_height - data->outer_spacing * 2)
            this->abs_height =
                this->container->abs_height - data->outer_spacing * 2;
    }
    if (this->fill != 0x00000000 || game->cache.show_ui_hitbox)
    {
        struct rr_renderer *renderer = game->renderer;
        struct rr_renderer_context_state state2;
        rr_renderer_context_state_init(renderer, &state2);
        rr_renderer_set_fill(renderer, this->fill);
        if (this != game->window)
            rr_renderer_scale(renderer, renderer->scale);
        rr_renderer_begin_path(renderer);
        rr_renderer_round_rect(renderer, -this->abs_width / 2,
                               -this->abs_height / 2, this->abs_width,
                               this->abs_height, 6);
        rr_renderer_fill(renderer);
        if (this->fill >= 0xff000000)
        {
            renderer->state.filter.amount = 0.2;
            rr_renderer_set_stroke(renderer, this->fill);
            rr_renderer_set_line_width(renderer, 6);
            rr_renderer_set_line_cap(renderer, 1);
            rr_renderer_set_line_join(renderer, 1);
            rr_renderer_stroke(renderer);
        }
        if (game->cache.show_ui_hitbox)
        {
            rr_renderer_begin_path(renderer);
            rr_renderer_round_rect(renderer, -this->abs_width / 2,
                                   -this->abs_height / 2, this->abs_width,
                                   this->abs_height, 6);
            rr_renderer_set_stroke(renderer, 0xff000000);
            rr_renderer_set_line_width(renderer, 2);
            rr_renderer_stroke(renderer);
        }
        rr_renderer_context_state_free(renderer, &state2);
    }
    for (uint32_t i = 0; i < this->elements.size; ++i)
        rr_ui_render_element(this->elements.start[i], game);
}

static void container_on_hide(struct rr_ui_element *this, struct rr_game *game)
{
    for (uint32_t i = 0; i < this->elements.size; ++i)
        this->elements.start[i]->on_hide(this->elements.start[i], game);
}

void rr_ui_container_poll_events(struct rr_ui_element *this,
                                 struct rr_game *game)
{
    if (this->completely_hidden)
        return;
    if (this->container != this)
        rr_ui_element_check_if_focused(this, game);
    else
        game->focused = this;
    if (game->focused != this || this->stop_event_propagation)
        return;
    for (uint32_t i = 0; i < this->elements.size; ++i)
        this->elements.start[i]->poll_events(this->elements.start[i], game);
}

struct rr_ui_element *rr_ui_container_add_element(struct rr_ui_element *this,
                                                  struct rr_ui_element *add)
{
    if (++this->elements.size == this->elements.capacity)
    {
        struct rr_ui_element **_new =
            malloc((sizeof *_new) * (this->elements.capacity *= 2));
        memcpy(_new, this->elements.start,
               this->elements.size * (sizeof *_new));
        free(this->elements.start);
        this->elements.start = _new;
    }
    this->elements.start[this->elements.size - 1] = add;
    add->container = this;
    return add;
}

struct rr_ui_element *rr_ui_container_init()
{
    struct rr_ui_element *this = rr_ui_element_init();
    struct rr_ui_container_metadata *data = malloc(sizeof *data);
    this->data = data;
    this->on_render = container_on_render;
    this->poll_events = rr_ui_container_poll_events;
    this->on_hide = container_on_hide;
    return this;
}

struct rr_ui_element *rr_ui_popup_container_init()
{
    struct rr_ui_element *this = rr_ui_container_init();
    this->animate = scale_animate;
    return this;
}

struct rr_ui_element *rr_ui_tooltip_container_init()
{
    struct rr_ui_element *this = rr_ui_container_init();
    this->poll_events = rr_ui_no_focus;
    this->should_show = rr_ui_never_show;
    this->h_justify = this->v_justify = -1;
    return this;
}

struct rr_ui_element *rr_ui_2d_container_init(uint8_t width, uint8_t height,
                                              float outer_spacing,
                                              float inner_spacing)
{
    struct rr_ui_element *this = rr_ui_element_init();
    struct rr_ui_container_metadata *data = malloc(sizeof *data);
    data->width = width;
    data->height = height;
    data->outer_spacing = outer_spacing;
    data->inner_spacing = inner_spacing;
    this->data = data;
    this->on_render = container_on_render;
    this->poll_events = rr_ui_container_poll_events;
    this->resizeable = rr_ui_grid_container;
    return this;
}

struct rr_ui_element *rr_ui_flex_container_init(struct rr_ui_element *left,
                                                struct rr_ui_element *right,
                                                float pad)
{
    struct rr_ui_element *this = rr_ui_container_init();
    struct rr_ui_container_metadata *data = this->data;
    rr_ui_container_add_element(this, left);
    rr_ui_container_add_element(this, right);
    left->h_justify = -1;
    right->h_justify = 1;
    this->abs_width = this->width = left->abs_width + pad + right->abs_width;
    this->abs_height = this->height = left->abs_height > right->abs_height
                                          ? left->abs_height
                                          : right->abs_height;
    this->h_flex = 1;
    this->on_render = container_on_render;
    this->poll_events = rr_ui_container_poll_events;
    return this;
}