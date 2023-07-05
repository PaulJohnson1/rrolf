#include <Client/Ui/Ui.h>

#include <stdio.h>
#include <stdlib.h>
#include <string.h>

#include <Client/Game.h>
#include <Client/InputData.h>
#include <Client/Renderer/RenderFunctions.h>
#include <Client/Renderer/Renderer.h>

#include <Client/Ui/Engine.h>

#include <Shared/SimulationCommon.h>
#include <Shared/Utilities.h>
#include <Shared/pb.h>

struct loadout_button_metadata
{
    uint8_t pos;
    uint8_t prev_id;
    uint8_t prev_rarity;
};

static void loadout_button_on_event(struct rr_ui_element *this,
                                    struct rr_game *game)
{
    struct loadout_button_metadata *data = this->data;
    if (game->input_data->mouse_buttons_this_tick & 1)
    {
        game->loadout[data->pos].id = 0;
        game->loadout[data->pos].rarity = 0;
        game->protocol_state |= 1 << data->pos;
    }
    else
    {
        if (game->loadout[data->pos].id == 0)
            return;
        struct rr_ui_element *tooltip =
            game->petal_tooltips[data->prev_id][data->prev_rarity];
        tooltip->hidden =
            this == game->focused ? &game->true_ptr : &game->false_ptr;
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

static void petal_switch_button_event(struct rr_ui_element *this,
                                      struct rr_game *game)
{
    struct loadout_button_metadata *data = this->data;
    if (game->input_data->mouse_buttons_this_tick & 1) // mouse_down
    {
        struct proto_bug encoder;
        proto_bug_init(&encoder, output_packet);
        proto_bug_write_uint8(&encoder, 2, "header");
        proto_bug_write_uint8(&encoder, data->pos % 10, "petal switch");
        rr_websocket_send(&game->socket, encoder.start, encoder.current);
    }
    else
    {
        struct rr_component_player_info *player_info = game->player_info;
        struct rr_component_player_info_petal_slot *slot =
            data->pos < 10 ? &player_info->slots[data->pos]
                           : &player_info->secondary_slots[data->pos - 10];
        uint8_t id = slot->id;
        uint8_t rarity = slot->rarity;
        if (id == 0)
            return;
        struct rr_ui_element *tooltip = game->petal_tooltips[id][rarity];
        tooltip->hidden =
            this == game->focused ? &game->true_ptr : &game->false_ptr;
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

static uint8_t title_screen_loadout_button_animate(struct rr_ui_element *this,
                                                   struct rr_game *game)
{
    struct loadout_button_metadata *data = this->data;
    struct rr_renderer *renderer = game->renderer;
    rr_renderer_scale(renderer, renderer->scale * this->width / 60);
    rr_renderer_render_background(renderer, 255);
    uint8_t id = game->loadout[data->pos].id;
    uint8_t rarity = game->loadout[data->pos].rarity;
    if (id == 0)
    {
        if (this->first_frame == 1)
        {
            this->animation = 1;
            return 0;
        }
        this->animation = rr_lerp(this->animation, 1, 0.25);
        if (this->animation > 0.99)
        {
            this->animation = 1;
            return 0;
        }
    }
    else
    {
        data->prev_id = id;
        data->prev_rarity = rarity;
        this->completely_hidden = 0;
        this->animation = rr_lerp(this->animation, 0, 0.5);
    }
    rr_renderer_scale(game->renderer, (1 - this->animation));
    return 1;
}

static uint8_t loadout_button_animate(struct rr_ui_element *this,
                                      struct rr_game *game)
{
    if (game->player_info == 0)
        return 0;
    struct rr_component_player_info *player_info = game->player_info;
    struct loadout_button_metadata *data = this->data;
    struct rr_renderer *renderer = game->renderer;
    rr_renderer_scale(renderer, renderer->scale * this->width / 60);
    rr_renderer_render_background(renderer, 255);
    struct rr_component_player_info_petal_slot *slot =
        data->pos < 10 ? &player_info->slots[data->pos]
                       : &player_info->secondary_slots[data->pos - 10];
    uint8_t id = slot->id;
    uint8_t rarity = slot->rarity;
    if (id == 0)
    {
        if (this->first_frame == 1)
        {
            this->animation = 1;
            return 0;
        }
        this->animation = rr_lerp(this->animation, 1, 0.25);
        if (this->animation > 0.99)
        {
            this->animation = 1;
            return 0;
        }
    }
    else
    {
        if (id != data->prev_id || rarity != data->prev_rarity)
            this->animation = 1;
        data->prev_id = id;
        data->prev_rarity = rarity;
        this->completely_hidden = 0;
        this->animation = rr_lerp(this->animation, 0, 0.5);
    }
    rr_renderer_scale(game->renderer, (1 - this->animation));
    return 1;
}

static void loadout_button_on_render(struct rr_ui_element *this,
                                     struct rr_game *game)
{
    struct loadout_button_metadata *data = this->data;
    struct rr_renderer *renderer = game->renderer;
    rr_renderer_render_background(renderer, data->prev_rarity);
    rr_renderer_draw_image(
        renderer, &game->static_petals[data->prev_id][data->prev_rarity]);
}

struct rr_ui_element *rr_ui_title_screen_loadout_button_init(uint8_t pos)
{
    struct rr_ui_element *this = rr_ui_element_init();
    struct loadout_button_metadata *data = malloc(sizeof *data);
    data->pos = pos;
    data->prev_id = 0;
    data->prev_rarity = 0;
    this->data = data;
    this->abs_width = this->width = pos < 10 ? 60 : 50;
    this->abs_height = this->height = pos < 10 ? 60 : 50;
    this->on_render = loadout_button_on_render;
    this->animate = title_screen_loadout_button_animate;
    this->on_event = loadout_button_on_event;
    return this;
}

struct rr_ui_element *rr_ui_loadout_button_init(uint8_t pos)
{
    struct rr_ui_element *this = rr_ui_element_init();
    struct loadout_button_metadata *data = malloc(sizeof *data);
    data->pos = pos;
    data->prev_id = 0;
    data->prev_rarity = 0;
    this->data = data;
    this->abs_width = this->width = pos < 10 ? 60 : 50;
    this->abs_height = this->height = pos < 10 ? 60 : 50;
    this->on_render = loadout_button_on_render;
    this->animate = loadout_button_animate;
    this->on_event = petal_switch_button_event;
    return this;
}