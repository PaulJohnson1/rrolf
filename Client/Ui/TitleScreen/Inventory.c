#include <Client/Ui/Ui.h>

#include <stdio.h>
#include <stdlib.h>
#include <string.h>

#include <Client/Game.h>
#include <Client/InputData.h>
#include <Client/Renderer/RenderFunctions.h>
#include <Client/Renderer/Renderer.h>

#include <Client/Ui/Engine.h>

#include <Shared/Api.h>
#include <Shared/Utilities.h>

struct inventory_button_metadata
{
    uint8_t id;
    uint8_t rarity;
    uint32_t count;
};

static void inventory_button_on_event(struct rr_ui_element *this,
                                      struct rr_game *game)
{
    struct inventory_button_metadata *data = this->data;
    if (game->input_data->mouse_buttons_up_this_tick & 1 &&
        game->pressed == this)
    {
        if (data->count == 0)
            return;
        for (uint8_t i = 0; i < game->cache.slots_unlocked; ++i)
        {
            if (game->cache.loadout[i].id == 0)
            {
                game->cache.loadout[i].id = data->id;
                game->cache.loadout[i].rarity = data->rarity;
                return;
            }
        }
        for (uint8_t i = 10; i < 10 + game->cache.slots_unlocked; ++i)
        {
            if (game->cache.loadout[i].id == 0)
            {
                game->cache.loadout[i].id = data->id;
                game->cache.loadout[i].rarity = data->rarity;
                return;
            }
        }
    }
    else
        rr_ui_render_tooltip_above(
            this, game->petal_tooltips[data->id][data->rarity], game);
}

static uint8_t inventory_button_should_show(struct rr_ui_element *this,
                                            struct rr_game *game)
{
    struct inventory_button_metadata *data = this->data;
    int32_t count = game->inventory[data->id][data->rarity];
    for (uint32_t i = 0; i < 20; ++i)
    {
        if (game->cache.loadout[i].id == data->id &&
            game->cache.loadout[i].rarity == data->rarity)
        {
            if (count > 0)
                --count;
            else
                game->cache.loadout[i].id = game->cache.loadout[i].rarity = 0;
        }
    }
    if (data->id == game->crafting_data.crafting_id)
    {
        if (data->rarity == game->crafting_data.crafting_rarity)
        {
            if (count >= game->crafting_data.count)
                count -= game->crafting_data.count;
            else
            {
                game->crafting_data.count = count;
                count = 0;
            }
        }
        // else if (data->rarity == game->crafting_data.crafting_rarity + 1)
        //  count -= game->crafting_data.success_count;
    }
    data->count = count;
    return count;
}

static uint8_t inventory_container_should_show(struct rr_ui_element *this,
                                               struct rr_game *game)
{
    return game->bottom_ui_open == 1 && !game->simulation_ready;
}

static void inventory_container_animate(struct rr_ui_element *this,
                                        struct rr_game *game)
{
    this->width = this->abs_width;
    this->height = this->abs_height;
    rr_renderer_translate(game->renderer, 0,
                          -(this->y - this->abs_height / 2) * 2 *
                              this->animation);
}

static void inventory_button_on_render(struct rr_ui_element *this,
                                       struct rr_game *game)
{
    struct inventory_button_metadata *data = this->data;
    struct rr_renderer *renderer = game->renderer;
    rr_renderer_scale(renderer, renderer->scale * this->width / 60);
    struct rr_renderer_context_state state;
    rr_renderer_context_state_init(renderer, &state);
    rr_renderer_render_background(renderer, data->rarity);
    rr_renderer_render_petal_with_background(renderer, game, data->id,
                                             data->rarity);
    rr_renderer_context_state_free(renderer, &state);
    if (data->count <= 1)
        return;
    rr_renderer_translate(renderer, 25, -25);
    rr_renderer_rotate(renderer, 0.5);
    rr_renderer_set_fill(renderer, 0xffffffff);
    rr_renderer_set_stroke(renderer, 0xff222222);
    rr_renderer_set_text_align(renderer, 1);
    rr_renderer_set_text_baseline(renderer, 1);
    rr_renderer_set_text_size(renderer, 18);
    rr_renderer_set_line_width(renderer, 18 * 0.12);

    char out[12];
    out[sprintf(&out[0], "x%d", data->count)] = 0;
    rr_renderer_stroke_text(renderer, (char const *)&out, 0, 0);
    rr_renderer_fill_text(renderer, (char const *)&out, 0, 0);
}

static struct rr_ui_element *inventory_button_init(uint8_t id, uint8_t rarity)
{
    struct rr_ui_element *this = rr_ui_element_init();
    struct inventory_button_metadata *data = malloc(sizeof *data);
    data->id = id;
    data->rarity = rarity;
    this->data = data;
    this->abs_width = this->width = 50;
    this->abs_height = this->height = 50;
    this->on_render = inventory_button_on_render;
    this->should_show = inventory_button_should_show;
    this->on_event = inventory_button_on_event;
    return this;
}

struct rr_ui_element *rr_ui_inventory_container_init()
{
    float test = 0;

    struct rr_ui_element *this = rr_ui_2d_container_init(5, 6, 15, 15);
    for (uint8_t rarity = rr_rarity_id_max - 1; rarity != 255; --rarity)
        for (uint8_t id = 1; id < rr_petal_id_max; ++id)
            rr_ui_container_add_element(this,
                                        inventory_button_init(id, rarity));
    this->fill = 0x00000000;
    struct rr_ui_element *c = rr_ui_set_background(
        rr_ui_pad(
            rr_ui_set_justify(rr_ui_v_container_init(
                                  rr_ui_container_init(), 10, 10,
                                  rr_ui_text_init("Inventory", 24, 0xffffffff),
                                  rr_ui_scroll_container_init(this, 400), NULL),
                              -1, 1),
            20),
        0x40ffffff);
    c->x += 60 + 20;
    c->animate = inventory_container_animate;
    c->should_show = inventory_container_should_show;
    return c;
}

static void inventory_toggle_on_render(struct rr_ui_element *this,
                                       struct rr_game *game)
{
    struct rr_renderer *renderer = game->renderer;
    if (game->focused == this)
        renderer->state.filter.amount = 0.2;
    rr_renderer_scale(renderer, renderer->scale);
    rr_renderer_set_fill(renderer, this->fill);
    renderer->state.filter.amount += 0.2;
    rr_renderer_set_stroke(renderer, this->fill);
    rr_renderer_set_line_width(renderer, 6);
    rr_renderer_begin_path(renderer);
    rr_renderer_round_rect(renderer, -this->width / 2, -this->height / 2,
                           this->width, this->height, 6);
    rr_renderer_fill(renderer);
    rr_renderer_stroke(renderer);
}

void inventory_toggle_button_on_event(struct rr_ui_element *this,
                                      struct rr_game *game)
{
    if (game->pressed != this)
        return;
    if (game->input_data->mouse_buttons_up_this_tick & 1)
    {
        if (game->bottom_ui_open == 1)
            game->bottom_ui_open = 0;
        else
        {
            game->bottom_ui_open = 1;
            rr_api_get_petals(game->rivet_account.uuid,
                              game->rivet_account.token, game);
        }
    }
}

struct rr_ui_element *rr_ui_inventory_toggle_button_init()
{
    struct rr_ui_element *this = rr_ui_element_init();
    this->fill = 0xffe34545;
    this->abs_width = this->abs_height = this->width = this->height = 60;
    this->on_event = inventory_toggle_button_on_event;
    this->on_render = inventory_toggle_on_render;
    return this;
}
