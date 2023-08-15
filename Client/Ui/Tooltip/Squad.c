#include <Client/Ui/Ui.h>

#include <stdio.h>
#include <string.h>
#include <stdlib.h>

#include <Client/Game.h>
#include <Client/InputData.h>
#include <Client/Assets/RenderFunctions.h>
#include <Client/Renderer/Renderer.h>
#include <Client/Ui/Engine.h>

#include <Shared/Utilities.h>

struct squad_loadout_button_metadata
{
    struct rr_game_loadout_petal *petal;
    uint8_t prev_id;
    uint8_t prev_rarity;
};

static uint8_t squad_loadout_button_should_show(struct rr_ui_element *this,
                                                struct rr_game *game)
{
    struct squad_loadout_button_metadata *data = this->data;
    return data->petal->id;
}

static void squad_loadout_button_animate(struct rr_ui_element *this,
                                         struct rr_game *game)
{
    struct squad_loadout_button_metadata *data = this->data;
    if (data->petal->id != 0)
    {
        data->prev_id = data->petal->id;
        data->prev_rarity = data->petal->rarity;
    }
    rr_renderer_scale(game->renderer, (1 - this->animation));
}

static void squad_loadout_button_on_render(struct rr_ui_element *this,
                                           struct rr_game *game)
{
    struct squad_loadout_button_metadata *data = this->data;
    struct rr_renderer *renderer = game->renderer;
    rr_renderer_scale(renderer, renderer->scale * this->width / 60);
    rr_renderer_draw_background(renderer, data->prev_rarity, 1);
    rr_renderer_draw_static_petal(renderer, data->prev_id, data->prev_rarity, 1);
}

static struct rr_ui_element *
squad_loadout_button_init(struct rr_game_loadout_petal *petal, uint8_t top)
{
    struct rr_ui_element *this = rr_ui_element_init();
    struct squad_loadout_button_metadata *data = malloc(sizeof *data);
    data->petal = petal;
    data->prev_id = 0;
    this->data = data;
    this->abs_width = this->width = top ? 30 : 25;
    this->abs_height = this->height = top ? 30 : 25;
    this->on_render = squad_loadout_button_on_render;
    this->animate = squad_loadout_button_animate;
    this->should_show = squad_loadout_button_should_show;
    return this;
}

static void wave_spawn_at(struct rr_ui_element *this, struct rr_game *game)
{
    struct rr_ui_dynamic_text_metadata *data = this->data;
    struct rr_game_squad_client *client = data->data;
    data->text[sprintf(data->text, "Spawn on wave %d",
                       client->requested_start_wave)] = 0;
}

static struct rr_ui_element *
wave_spawn_element_init(struct rr_game_squad_client *member)
{
    struct rr_ui_element *this =
        rr_ui_dynamic_text_init(12, 0xffffffff, wave_spawn_at);
    struct rr_ui_dynamic_text_metadata *data = this->data;
    data->data = member;
    return this;
}

static uint8_t dev_text_choose(struct rr_ui_element *this, struct rr_game *game)
{
    struct rr_ui_choose_element_metadata *data = this->data;
    struct rr_game_squad_client *member = data->data;
    if (member->ready & 2)
        return 0;
    return 1;
}

static struct rr_ui_element *dev_text_init(struct rr_game_squad_client *member)
{
    struct rr_ui_element *this = rr_ui_choose_element_init(rr_ui_text_init("Player", 20, 0xffffffff), rr_ui_text_init("Developer", 20, 0xffffffff), dev_text_choose);
    struct rr_ui_choose_element_metadata *data = this->data;
    data->data = member;
    return this;
}

struct rr_ui_element *rr_ui_squad_player_tooltip_init(struct rr_game *game, uint8_t pos)
{
    struct rr_game_squad_client *member = &game->squad_members[pos];
    struct rr_ui_element *this = rr_ui_set_justify(
        rr_ui_set_background(
            rr_ui_v_container_init(rr_ui_container_init(), 10, 10,
                dev_text_init(member),
                rr_ui_text_init(&member->name[0], 16, 0xffffffff),
                wave_spawn_element_init(member),
                rr_ui_h_container_init(rr_ui_container_init(), 0, 5, 
                    squad_loadout_button_init(&member->loadout[0], 1),
                    squad_loadout_button_init(&member->loadout[1], 1),
                    squad_loadout_button_init(&member->loadout[2], 1),
                    squad_loadout_button_init(&member->loadout[3], 1),
                    squad_loadout_button_init(&member->loadout[4], 1),
                    squad_loadout_button_init(&member->loadout[5], 1),
                    squad_loadout_button_init(&member->loadout[6], 1),
                    squad_loadout_button_init(&member->loadout[7], 1),
                    squad_loadout_button_init(&member->loadout[8], 1),
                    squad_loadout_button_init(&member->loadout[9], 1),
                    NULL
                ),
                rr_ui_h_container_init(rr_ui_container_init(), 0, 5, 
                    squad_loadout_button_init(&member->loadout[10], 0),
                    squad_loadout_button_init(&member->loadout[11], 0),
                    squad_loadout_button_init(&member->loadout[12], 0),
                    squad_loadout_button_init(&member->loadout[13], 0),
                    squad_loadout_button_init(&member->loadout[14], 0),
                    squad_loadout_button_init(&member->loadout[15], 0),
                    squad_loadout_button_init(&member->loadout[16], 0),
                    squad_loadout_button_init(&member->loadout[17], 0),
                    squad_loadout_button_init(&member->loadout[18], 0),
                    squad_loadout_button_init(&member->loadout[19], 0),
                    NULL
                ),
                NULL
            )
        , 0x80000000)
    , -1, -1);
    this->poll_events = rr_ui_no_focus;
    rr_ui_link_toggle(this, rr_ui_never_show);
    return this;
}