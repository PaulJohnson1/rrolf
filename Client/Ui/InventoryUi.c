#include <Client/Ui/Ui.h>

#include <stdio.h>
#include <stdlib.h>
#include <string.h>

#include <Client/Game.h>
#include <Client/InputData.h>
#include <Client/Renderer/RenderFunctions.h>
#include <Client/Renderer/Renderer.h>

#include <Client/Ui/Engine.h>

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
    if (game->input_data->mouse_buttons_this_tick & 1)
    {
        if (data->count == 0)
            return;
        for (uint8_t i = 0; i < 20; ++i)
        {
            if (game->loadout[i].id == 0)
            {
                game->loadout[i].id = data->id;
                game->loadout[i].rarity = data->rarity;
                game->protocol_state |= 1 << i;
                return;
            }
        }
    }
    else
    {
        struct rr_ui_element *tooltip =
            game->petal_tooltips[data->id][data->rarity];
        tooltip->hidden = &game->true_ptr;
        tooltip->x =
            (this->abs_x / game->renderer->scale - tooltip->abs_width / 2);
        tooltip->y = (this->abs_y / game->renderer->scale -
                      (tooltip->abs_height + this->abs_height / 2 + 10));
        if (tooltip->x < 10)
            tooltip->x = 10;
        if (tooltip->y < 10)
            tooltip->y = 10;
    }
}

static uint8_t inventory_button_animate(struct rr_ui_element *this,
                                        struct rr_game *game)
{
    struct inventory_button_metadata *data = this->data;
    uint32_t count = game->inventory[data->id][data->rarity];
    for (uint32_t i = 0; i < 20; ++i)
    {
        if (game->loadout[i].id == data->id &&
            game->loadout[i].rarity == data->rarity)
            --count;
    }
    data->count = count;
    if (count == 0)
    {
        if (this->first_frame == 1)
        {
            this->completely_hidden = 1;
            this->animation = 1;
            return 0;
        }
        this->animation = rr_lerp(this->animation, 1, 0.15);
        if (this->animation > 0.99)
        {
            this->animation = 1;
            this->completely_hidden = 1;
            return 0;
        }
    }
    else
    {
        this->completely_hidden = 0;
        this->animation = rr_lerp(this->animation, 0, 0.15);
    }
    this->width = this->abs_width * (1 - this->animation);
    this->height = this->abs_height * (1 - this->animation);
    rr_renderer_scale(game->renderer, (1 - this->animation));
    return 1;
}

static void inventory_button_on_render(struct rr_ui_element *this,
                                       struct rr_game *game)
{
    struct inventory_button_metadata *data = this->data;
    struct rr_renderer *renderer = game->renderer;
    rr_renderer_scale(renderer, renderer->scale * this->width / 60);
    struct rr_renderer_context_state state;
    rr_renderer_init_context_state(renderer, &state);
    rr_renderer_render_background(renderer, data->rarity);
    rr_renderer_draw_image(renderer,
                           &game->static_petals[data->id][data->rarity]);
    rr_renderer_free_context_state(renderer, &state);

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
    rr_ui_set_justify(this, -1, -1);
    this->on_render = inventory_button_on_render;
    this->animate = inventory_button_animate;
    this->on_event = inventory_button_on_event;
    return this;
}

struct rr_ui_element *rr_ui_inventory_container_init()
{
    struct rr_ui_element *this = rr_ui_2d_container_init(5, 6, 15, 15);
    for (uint8_t rarity = rr_rarity_id_ultra; rarity != 255; --rarity)
        for (uint8_t id = 1; id < rr_petal_id_max; ++id)
            rr_ui_container_add_element(
                this,
                rr_ui_set_justify(inventory_button_init(id, rarity), -1, -1));
    this->fill = 0x00000000;
    return this;
}