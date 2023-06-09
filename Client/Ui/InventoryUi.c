#include <Client/Ui/Element.h>

#include <stdlib.h>
#include <stdio.h>

#include <Client/Game.h>
#include <Client/Simulation.h>
#include <Client/Renderer/Renderer.h>
#include <Client/Renderer/RenderFunctions.h>
#include <Client/Ui/Engine.h>

#include <Shared/StaticData.h>

struct inventory_button_metadata
{
    uint8_t id;
    uint8_t rarity;
    float lerp_width;
    float count;
};

static void inventory_container_on_render(struct rr_ui_element *this, void *_game)
{
    struct rr_game *game = _game;
    struct rr_renderer_context_state state;
    struct rr_ui_container_metadata *data = this->misc_data;
    rr_renderer_init_context_state(game->renderer, &state);
    ui_translate(this, game->renderer);
    //if (this->container != this)
        //rr_renderer_fill_rect(game->renderer, -this->width / 2, -this->height / 2, this->width, this->height);
    for (uint32_t i = 0; i < data->elements.size; ++i)
        if(data->elements.elements[i]->hidden == 0)
            data->elements.elements[i]->on_render(data->elements.elements[i], game);
    rr_renderer_free_context_state(game->renderer, &state);
}

static void inventory_button_on_render(struct rr_ui_element *this, void *_game)
{
    struct rr_game *game = _game;
    struct rr_renderer *renderer = game->renderer;
    struct inventory_button_metadata *data = this->misc_data;
    if (game->simulation->player_info == RR_NULL_ENTITY)
        return;
    uint32_t count = rr_simulation_get_player_info(game->simulation, game->simulation->player_info)->inv[data->id][data->rarity];
    if (count == 0)
        return;
    struct rr_renderer_context_state state;
    struct rr_renderer_context_state state2;
    rr_renderer_init_context_state(renderer, &state);
    rr_renderer_set_fill(renderer, RR_RARITY_COLORS[data->rarity]);
    rr_renderer_set_line_width(renderer, this->width * 0.1);
    renderer->state.filter.amount = 0.2;
    rr_renderer_set_stroke(renderer, RR_RARITY_COLORS[data->rarity]);
    ui_translate(this, renderer);
    rr_renderer_scale(renderer, renderer->scale);

    rr_renderer_init_context_state(renderer, &state2);
    rr_renderer_begin_path(renderer);
    rr_renderer_round_rect(renderer, -this->width / 2, -this->height / 2, this->width, this->height, 5);
    rr_renderer_fill(renderer);
    rr_renderer_stroke(renderer);
    rr_renderer_clip(renderer);

    rr_renderer_scale(renderer, this->width * 0.02);
    
    renderer->state.filter.amount = 0;
    rr_renderer_render_static_petal(renderer, data->id, data->rarity);
    rr_renderer_free_context_state(renderer, &state2);
    renderer->state.filter.amount = 0;

    rr_renderer_translate(renderer, 20, -20);
    rr_renderer_rotate(renderer, 0.5);
    rr_renderer_set_fill(renderer, 0xffffffff);
    rr_renderer_set_stroke(renderer, 0xff222222);
    rr_renderer_set_text_align(renderer, 1);
    rr_renderer_set_text_baseline(renderer, 1);
    rr_renderer_set_text_size(renderer, 15);
    rr_renderer_set_line_width(renderer, 15 * 0.12);

    char out[12];
    sprintf(&out[0], "x%d", count);
    rr_renderer_stroke_text(renderer, (char const *) &out, 0, 0);
    rr_renderer_fill_text(renderer, (char const *) &out, 0, 0);
    
    rr_renderer_free_context_state(renderer, &state);
}

static struct rr_ui_element *rr_ui_inventory_button_init(uint8_t id, uint8_t rarity)
{
    struct rr_ui_element *element = rr_ui_element_init();
    struct inventory_button_metadata *data = malloc(sizeof *data);
    data->id = id;
    data->rarity = rarity;
    data->count = 0;
    element->width = element->height = 50;
    element->lerp_x = element->x = rarity * 60 + 35;
    element->lerp_y = element->y = (id - 1) * 60 + 35;
    element->h_justify = 0;
    element->v_justify = 0;
    element->on_render = inventory_button_on_render;
    element->misc_data = data;
    return element;
}

struct rr_ui_element *rr_ui_inventory_container_init()
{
    struct rr_ui_element *element = rr_ui_container_init();
    element->on_render = inventory_container_on_render;
    for (uint8_t id = 1; id < rr_petal_id_max; ++id)
        for (uint8_t rarity = 0; rarity < rr_rarity_id_max; ++rarity)
            rr_ui_container_add_element(element, rr_ui_inventory_button_init(id, rarity));

    element->width = (rr_rarity_id_max) * 60 + 10;
    element->height = (rr_petal_id_max - 1) * 60 + 10;

    return element;
}