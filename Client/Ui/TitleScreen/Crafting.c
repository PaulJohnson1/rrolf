#include <Client/Ui/Ui.h>

#include <math.h>
#include <stdlib.h>
#include <string.h>

#include <Client/Game.h>
#include <Client/InputData.h>
#include <Client/Assets/RenderFunctions.h>
#include <Client/Renderer/RenderFunctions.h>
#include <Client/Renderer/Renderer.h>
#include <Client/Simulation.h>
#include <Client/Ui/Engine.h>
#include <Shared/Api.h>
#include <Shared/Binary.h>
#include <Shared/StaticData.h>
#include <Shared/Utilities.h>

#define PETALS_PER_CRAFT 5

struct crafting_ring_metadata
{
    float angle;
    float v_angle;
};

struct crafting_ring_button_metadata
{
    uint32_t count;
    float secondary_animation;
    uint8_t pos;
    uint8_t prev_id;
    uint8_t prev_rarity;
};

struct crafting_inventory_button_metadata
{
    uint8_t id;
    uint8_t rarity;
    uint32_t count;
    float secondary_animation;
};

struct server_response
{
    int64_t count;
    int rarity;
    int id;
};

struct craft_captures
{
    struct rr_game_crafting_data craft;
    struct rr_game *game;
};

void rr_api_on_craft_result(char *bin, void *_captures)
{
    // parse format of type delta_xp|id:rarity:count,id:rarity:count
    // and if it's the same id:rarity as the petal that is being crafted, reset
    // the animation and set the success count
    struct craft_captures *captures = _captures;
    struct rr_game *game = captures->game;
    // struct rr_game_crafting_data *craft = &captures->craft;
    struct rr_game_crafting_data *craft = &game->crafting_data;

    craft->animation = 0;

    struct rr_binary_encoder decoder;
    rr_binary_encoder_init(&decoder, (uint8_t *) bin);
    
    uint8_t id = rr_binary_encoder_read_uint8(&decoder);
    while (id)
    {
        uint8_t rarity = rr_binary_encoder_read_uint8(&decoder);
        uint32_t fails = rr_binary_encoder_read_varuint(&decoder);
        game->inventory[id][rarity] -= fails;
        game->crafting_data.count -= fails;
        uint32_t successes = rr_binary_encoder_read_varuint(&decoder);
        game->inventory[id][rarity + 1] += successes;
        game->crafting_data.success_count = successes;
        id = rr_binary_encoder_read_uint8(&decoder);
    }
    game->cache.experience += rr_binary_encoder_read_float64(&decoder);
    free(bin);
}

static void craft_button_on_event(struct rr_ui_element *this,
                                  struct rr_game *game)
{
    if (game->pressed != this)
        return;
    if (game->input_data->mouse_buttons_up_this_tick & 1 &&
        game->crafting_data.animation == 0)
    {
        if (game->crafting_data.success_count == 0 &&
            game->crafting_data.count >= PETALS_PER_CRAFT &&
            game->crafting_data.crafting_id != 0 &&
            game->crafting_data.crafting_rarity < rr_rarity_id_ultra)
        {
            game->crafting_data.success_count = 0;
            game->crafting_data.animation = 200000;
            char petal_data[100] = {0};
            snprintf(
                petal_data, 90, "%d:%d:%d", game->crafting_data.crafting_id,
                game->crafting_data.crafting_rarity, game->crafting_data.count);
            static struct craft_captures c;
            c.game = game;
            memcpy(&c.craft, &game->crafting_data, sizeof c.craft);
            rr_api_craft_petals(game->rivet_account.uuid,
                                game->rivet_account.token, petal_data, &c);
        }
    }
}

static uint8_t crafting_ring_should_show(struct rr_ui_element *this,
                                         struct rr_game *game)
{
    return game->crafting_data.success_count == 0 ||
           game->crafting_data.animation != 0;
}

static void crafting_ring_petal_on_event(struct rr_ui_element *this,
                                         struct rr_game *game)
{
    struct crafting_ring_button_metadata *data = this->data;
    if (game->input_data->mouse_buttons_up_this_tick & 1 &&
        game->pressed == this)
    {
        game->crafting_data.count = game->crafting_data.success_count = 0;
        game->crafting_data.crafting_id = game->crafting_data.crafting_rarity =
            0;
    }
    else if (data->count > 0)
        rr_ui_render_tooltip_above(
            this,
            game->petal_tooltips[game->crafting_data.crafting_id]
                                [game->crafting_data.crafting_rarity],
            game);
}

static void crafting_result_container_on_event(struct rr_ui_element *this,
                                               struct rr_game *game)
{
    if (game->input_data->mouse_buttons_up_this_tick & 1)
    {
        if (game->pressed != this)
            return;
        game->crafting_data.count = game->crafting_data.success_count = 0;
        game->crafting_data.crafting_id = game->crafting_data.crafting_rarity =
            0;
    }
    else if (game->crafting_data.success_count > 0)
        rr_ui_render_tooltip_above(
            this,
            game->petal_tooltips[game->crafting_data.crafting_id]
                                [game->crafting_data.crafting_rarity + 1],
            game);
}

static void crafting_ring_petal_animate(struct rr_ui_element *this,
                                        struct rr_game *game)
{
    struct crafting_ring_button_metadata *data = this->data;
    data->count = (game->crafting_data.count + data->pos) / PETALS_PER_CRAFT;
    if (this->first_frame)
        data->secondary_animation = data->count == 0;
    data->secondary_animation = rr_lerp(
        data->secondary_animation,
        data->count == 0 || data->prev_id != game->crafting_data.crafting_id ||
            data->prev_rarity != game->crafting_data.crafting_rarity,
        0.4);

    rr_renderer_scale(game->renderer, game->renderer->scale * this->width / 60);
    rr_renderer_draw_background(game->renderer, rr_rarity_id_max, 1);
    if (game->crafting_data.crafting_id != 0)
    {
        data->prev_id = game->crafting_data.crafting_id;
        data->prev_rarity = game->crafting_data.crafting_rarity;
    }
    rr_renderer_scale(game->renderer, (1 - data->secondary_animation));
    rr_renderer_rotate(game->renderer, data->secondary_animation * M_PI * 2);
}

static void crafting_ring_petal_on_render(struct rr_ui_element *this,
                                          struct rr_game *game)
{
    struct crafting_ring_button_metadata *data = this->data;
    struct rr_renderer *renderer = game->renderer;
    struct rr_renderer_context_state state;
    rr_renderer_context_state_init(renderer, &state);
    rr_renderer_draw_background(renderer, data->prev_rarity, 1);
    rr_renderer_draw_petal_with_name(renderer, data->prev_id,
                                             data->prev_rarity);
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

static struct rr_ui_element *crafting_ring_petal_init(uint8_t pos)
{
    struct rr_ui_element *this = rr_ui_element_init();
    struct crafting_ring_button_metadata *data = malloc(sizeof *data);
    data->pos = pos;
    data->prev_id = data->prev_rarity = 0;
    data->secondary_animation = 0;
    this->data = data;
    this->abs_width = this->width = 60;
    this->abs_height = this->height = 60;
    this->animate = crafting_ring_petal_animate;
    this->on_render = crafting_ring_petal_on_render;
    this->on_event = crafting_ring_petal_on_event;
    return this;
}

static void crafting_ring_on_render(struct rr_ui_element *this,
                                    struct rr_game *game)
{
    struct crafting_ring_metadata *data = this->data;
    if (game->crafting_data.animation != 0)
        data->v_angle = 0.1;
    data->angle += data->v_angle;
    data->v_angle *= 0.8;
    struct rr_renderer_context_state state;
    for (uint32_t i = 0; i < this->elements.size; ++i)
    {
        rr_renderer_context_state_init(game->renderer, &state);
        rr_renderer_translate(
            game->renderer,
            game->renderer->scale *
                cosf(i * 2 * M_PI / this->elements.size + data->angle) * 120,
            game->renderer->scale *
                sinf(i * 2 * M_PI / this->elements.size + data->angle) * 120);
        rr_ui_render_element(this->elements.start[i], game);
        rr_renderer_context_state_free(game->renderer, &state);
    }
}
static struct rr_ui_element *crafting_ring_init()
{
    struct rr_ui_element *this = rr_ui_element_init();
    struct crafting_ring_metadata *data = malloc(sizeof *data);
    memset(data, 0, sizeof *data);
    this->data = data;
    this->abs_width = this->width = 300;
    this->abs_height = this->height = 300;
    this->on_render = crafting_ring_on_render;
    for (uint32_t i = 0; i < PETALS_PER_CRAFT; ++i)
        rr_ui_container_add_element(this, crafting_ring_petal_init(i));
    this->poll_events = rr_ui_container_poll_events;
    this->should_show = crafting_ring_should_show;
    return this;
}

static uint8_t crafting_result_container_should_show(struct rr_ui_element *this,
                                                     struct rr_game *game)
{
    return game->crafting_data.success_count &&
           game->crafting_data.animation == 0;
}

static void crafting_result_container_on_render(struct rr_ui_element *this,
                                                struct rr_game *game)
{
    struct rr_renderer *renderer = game->renderer;
    struct rr_renderer_context_state state;
    rr_renderer_scale(renderer, renderer->scale);
    rr_renderer_context_state_init(renderer, &state);
    rr_renderer_draw_background(renderer,
                                  game->crafting_data.crafting_rarity + 1, 1);
    rr_renderer_draw_petal_with_name(
        renderer, game->crafting_data.crafting_id,
        game->crafting_data.crafting_rarity + 1);
    rr_renderer_context_state_free(renderer, &state);
    if (game->crafting_data.success_count <= 1)
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
    out[sprintf(&out[0], "x%d", game->crafting_data.success_count)] = 0;
    rr_renderer_stroke_text(renderer, (char const *)&out, 0, 0);
    rr_renderer_fill_text(renderer, (char const *)&out, 0, 0);
}

static struct rr_ui_element *crafting_result_container_init()
{
    struct rr_ui_element *this = rr_ui_element_init();
    this->abs_width = this->width = 60;
    this->abs_height = this->height = 60;
    this->on_render = crafting_result_container_on_render;
    this->on_event = crafting_result_container_on_event;
    this->should_show = crafting_result_container_should_show;
    return this;
}

static struct rr_ui_element *crafting_button_init()
{
    struct rr_ui_element *this = rr_ui_labeled_button_init("Craft", 36, NULL);
    this->on_event = craft_button_on_event;
    return this;
}

static void crafting_chance_text_animate(struct rr_ui_element *this,
                                         struct rr_game *game)
{
    struct rr_ui_text_metadata *data = this->data;
    if (game->crafting_data.crafting_id == 0)
    {
        data->text = "Chance: --%";
        this->fill = 0xff888888;
        return;
    }
    this->fill = RR_RARITY_COLORS[game->crafting_data.crafting_rarity + 1];
    switch (game->crafting_data.crafting_rarity)
    {
    case rr_rarity_id_common:
        data->text = "Chance: 50%";
        break;
    case rr_rarity_id_unusual:
        data->text = "Chance: 30%";
        break;
    case rr_rarity_id_rare:
        data->text = "Chance: 15%";
        break;
    case rr_rarity_id_epic:
        data->text = "Chance: 5%";
        break;
    case rr_rarity_id_legendary:
        data->text = "Chance: 3%";
        break;
    case rr_rarity_id_mythic:
        data->text = "Chance: 1%";
        break;
    }
}

static struct rr_ui_element *crafting_chance_text_init()
{
    struct rr_ui_element *this = rr_ui_text_init("Chance: --%", 14, 0xff888888);
    this->animate = crafting_chance_text_animate;
    return this;
}

static void crafting_xp_text_animate(struct rr_ui_element *this,
                                     struct rr_game *game)
{
    struct rr_ui_text_metadata *data = this->data;
    if (game->crafting_data.crafting_id == 0)
    {
        data->text = "? xp per craft";
        this->fill = 0xff888888;
        return;
    }
    this->fill = RR_RARITY_COLORS[game->crafting_data.crafting_rarity];
    switch (game->crafting_data.crafting_rarity)
    {
    case rr_rarity_id_common:
        data->text = "1 xp per craft";
        break;
    case rr_rarity_id_unusual:
        data->text = "8 xp per craft";
        break;
    case rr_rarity_id_rare:
        data->text = "60 xp per craft";
        break;
    case rr_rarity_id_epic:
        data->text = "750 xp per craft";
        break;
    case rr_rarity_id_legendary:
        data->text = "2500 xp per craft";
        break;
    case rr_rarity_id_mythic:
        data->text = "1000000 xp per craft";
        break;
    }
}

static struct rr_ui_element *crafting_xp_text_init()
{
    struct rr_ui_element *this =
        rr_ui_text_init("? xp per craft", 14, 0xff888888);
    this->animate = crafting_xp_text_animate;
    return this;
}

static void crafting_inventory_button_animate(struct rr_ui_element *this,
                                              struct rr_game *game)
{
    struct crafting_inventory_button_metadata *data = this->data;
    int32_t count = game->inventory[data->id][data->rarity];
    for (uint32_t i = 0; i < 20; ++i)
    {
        if (game->cache.loadout[i].id == data->id &&
            game->cache.loadout[i].rarity == data->rarity)
        {
            if (count > 0)
                --count;
            else
                game->cache.loadout[i].id = 0;
        }
    }
    if (data->id == game->crafting_data.crafting_id)
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
    data->count = count;
    if (this->first_frame)
        data->secondary_animation = count == 0;

    data->secondary_animation =
        rr_lerp(data->secondary_animation, count == 0, 0.2);
    rr_renderer_scale(game->renderer, game->renderer->scale * this->width / 60);
    rr_renderer_draw_background(game->renderer, rr_rarity_id_max, 1);
    rr_renderer_scale(game->renderer, (1 - data->secondary_animation));
}

static void crafting_inventory_button_on_event(struct rr_ui_element *this,
                                               struct rr_game *game)
{
    struct crafting_inventory_button_metadata *data = this->data;
    if (game->input_data->mouse_buttons_up_this_tick & 1 &&
        game->pressed == this)
    {
        if (game->inventory[data->id][data->rarity] < PETALS_PER_CRAFT ||
            game->crafting_data.success_count > 0 ||
            data->rarity == rr_rarity_id_max - 1)
            return;
        if (game->crafting_data.crafting_id != data->id ||
            game->crafting_data.crafting_rarity != data->rarity)
        {
            game->crafting_data.crafting_id = data->id;
            game->crafting_data.crafting_rarity = data->rarity;
            game->crafting_data.count = 0;
            game->crafting_data.success_count = 0;
        }
        if (rr_bitset_get(game->input_data->keys_pressed, 16))
            game->crafting_data.count += data->count;
        else if (data->count > PETALS_PER_CRAFT)
            game->crafting_data.count += PETALS_PER_CRAFT;
        else
            game->crafting_data.count += data->count;
    }
    else if (data->count > 0)
        rr_ui_render_tooltip_above(
            this, game->petal_tooltips[data->id][data->rarity], game);
}

static void crafting_container_animate(struct rr_ui_element *this,
                                       struct rr_game *game)
{
    this->width = this->abs_width;
    this->height = this->abs_height;
    rr_renderer_translate(game->renderer, 0,
                          -(this->y - this->abs_height / 2) * 2 *
                              this->animation);
}

static void crafting_inventory_button_on_render(struct rr_ui_element *this,
                                                struct rr_game *game)
{
    struct crafting_inventory_button_metadata *data = this->data;
    if (data->secondary_animation > 0.999)
        return;
    struct rr_renderer *renderer = game->renderer;
    struct rr_renderer_context_state state;
    rr_renderer_context_state_init(renderer, &state);
    rr_renderer_draw_background(renderer, data->rarity, 1);
    rr_renderer_draw_petal_with_name(renderer, data->id,
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

struct rr_ui_element *crafting_inventory_button_init(uint8_t id, uint8_t rarity)
{
    struct rr_ui_element *this = rr_ui_element_init();
    struct crafting_inventory_button_metadata *data = malloc(sizeof *data);
    data->id = id;
    data->rarity = rarity;
    data->count = 0;
    data->secondary_animation = 0;
    this->data = data;
    this->abs_width = this->width = 50;
    this->abs_height = this->height = 50;
    this->on_render = crafting_inventory_button_on_render;
    this->should_show = rr_ui_always_show;
    this->on_event = crafting_inventory_button_on_event;
    this->animate = crafting_inventory_button_animate;
    return this;
}

static uint8_t crafting_container_should_show(struct rr_ui_element *this,
                                              struct rr_game *game)
{
    return game->bottom_ui_open == 3 && !game->simulation_ready;
}

struct rr_ui_element *rr_ui_crafting_container_init()
{
    struct rr_ui_element *this =
        rr_ui_2d_container_init(rr_rarity_id_max, 6, 15, 15);
    for (uint8_t id = 1; id < rr_petal_id_max; ++id)
        for (uint8_t rarity = 0; rarity < rr_rarity_id_max; ++rarity)
            rr_ui_container_add_element(
                this, crafting_inventory_button_init(id, rarity));
    this->fill = 0x00000000;
    struct rr_ui_element *craft = rr_ui_container_init();
    rr_ui_container_add_element(craft, crafting_ring_init());
    rr_ui_container_add_element(craft, crafting_result_container_init());
    craft->abs_width = craft->width = 300;
    craft->abs_height = craft->height = 300;
    struct rr_ui_element *c = rr_ui_set_background(
        rr_ui_pad(
            rr_ui_set_justify(
                rr_ui_v_container_init(
                    rr_ui_container_init(), 10, 10,
                    rr_ui_text_init("Crafting", 24, 0xffffffff),
                    rr_ui_h_container_init(
                        rr_ui_container_init(), 0, 25,
                        rr_ui_v_container_init(
                            rr_ui_container_init(), 0, 10,
                            rr_ui_static_space_init(14),
                            rr_ui_text_init(
                                "                                   ", 14,
                                0x00000000),
                            crafting_button_init(), crafting_chance_text_init(),
                            crafting_xp_text_init(), NULL),
                        craft, NULL),
                    rr_ui_scroll_container_init(this, 300), NULL),
                -1, 1),
            20),
        0x40ffffff);
    c->x += 60 + 20;
    c->animate = crafting_container_animate;
    c->should_show = crafting_container_should_show;
    return c;
}

static void crafting_toggle_on_render(struct rr_ui_element *this,
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

void crafting_toggle_button_on_event(struct rr_ui_element *this,
                                     struct rr_game *game)
{
    if (game->pressed != this)
        return;
    if (game->input_data->mouse_buttons_up_this_tick & 1)
    {
        if (game->bottom_ui_open == 3)
            game->bottom_ui_open = 0;
        else
            game->bottom_ui_open = 3;
    }
}

struct rr_ui_element *rr_ui_crafting_toggle_button_init()
{
    struct rr_ui_element *this = rr_ui_element_init();
    this->fill = 0xffe34545;
    this->abs_width = this->abs_height = this->width = this->height = 60;
    this->on_event = crafting_toggle_button_on_event;
    this->on_render = crafting_toggle_on_render;
    return this;
}
