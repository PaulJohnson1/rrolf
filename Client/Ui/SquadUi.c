#include <Client/Ui/Ui.h>

#include <stdlib.h>
#include <stdio.h>

#include <Client/Ui/Engine.h>
#include <Client/Game.h>
#include <Client/Renderer/Renderer.h>
#include <Client/Renderer/RenderFunctions.h>

#include <Shared/Utilities.h>

static uint8_t choose(struct rr_ui_element *this, struct rr_game *game)
{
    struct rr_ui_choose_element_metadata *data = this->data;
    struct rr_game_squad_client *member = data->data;
    return member->in_use;
}

struct squad_loadout_button_metadata
{
    struct rr_game_loadout_petal *petal;
    uint8_t prev_id;
    uint8_t prev_rarity;
};

static uint8_t squad_loadout_button_animate(struct rr_ui_element *this, struct rr_game *game)
{
    struct squad_loadout_button_metadata *data = this->data;
    if (data->petal->id == 0)
    {
        if (this->first_frame == 1)
        {
            this->completely_hidden = 1;
            this->animation = 1;
            return 0;
        }
        this->animation = rr_lerp(this->animation, 1, 0.25);
        if (this->animation > 0.99)
        {
            this->animation = 1;
            this->completely_hidden = 1;
            return 0;
        }
    }
    else
    {
        data->prev_id = data->petal->id;
        data->prev_rarity = data->petal->rarity;
        this->completely_hidden = 0;
        this->animation = rr_lerp(this->animation, 0, 0.5);
    }
    rr_renderer_scale(game->renderer, (1 - this->animation));
    return 1;
}

static void squad_loadout_button_on_render(struct rr_ui_element *this, struct rr_game *game)
{
    struct squad_loadout_button_metadata *data = this->data;
    struct rr_renderer *renderer = game->renderer;
    rr_renderer_scale(renderer, renderer->scale * this->width / 60);
    rr_renderer_render_background(renderer, data->prev_rarity);
    rr_renderer_draw_image(renderer, &game->static_petals[data->prev_id][data->prev_rarity]);
}

static struct rr_ui_element *squad_loadout_button_init(struct rr_game_loadout_petal *petal)
{
    struct rr_ui_element *this = rr_ui_element_init();
    struct squad_loadout_button_metadata *data = malloc(sizeof *data);
    data->petal = petal;
    data->prev_id = 0;
    this->data = data;
    this->abs_width = this->width = 15;
    this->abs_height = this->height = 15;
    this->on_render = squad_loadout_button_on_render;
    this->animate = squad_loadout_button_animate;
    return this;
}

static uint8_t should_be_ready(struct rr_ui_element *choose, struct rr_game *game)
{
    return ((struct rr_game_squad_client *)((struct rr_ui_choose_element_metadata *)choose->data)->data)->ready;
}

static struct rr_ui_element *rr_ui_player_init(struct rr_game_squad_client *player)
{
    struct rr_ui_element *choose_container = rr_ui_choose_element_init(
        rr_ui_text_init("Ready", 20, 0xff00ff00),
        rr_ui_text_init("Waiting", 15, 0xffcccccc),
        should_be_ready);
    ((struct rr_ui_choose_element_metadata *)choose_container->data)->data = player;
    return choose_container;
}

struct rr_ui_element *squad_player_container_init(struct rr_game_squad_client *member)
{
    struct rr_ui_element *b = rr_ui_text_init("Empty", 15, 0xffffffff);
    struct rr_ui_element *loadout = rr_ui_2d_container_init(5, 4, 10, 5);
    for (uint8_t i = 0; i < 20; ++i)
        rr_ui_container_add_element(loadout, rr_ui_set_justify(squad_loadout_button_init(&member->loadout[i]), -1, -1));
    // manually set the size if we want it to stay constant
    loadout->abs_width = loadout->width = 2 * 10 + (15 + 5) * 5 - 10;
    loadout->abs_height = loadout->height = 2 * 10 + (15 + 5) * 4 - 10;
    struct rr_ui_element *a = rr_ui_v_container_init(rr_ui_container_init(), 0, 10, 3,
                                                     rr_ui_text_init("player name (todo)", 18, 0xffffffff),
                                                     rr_ui_player_init(member),
                                                     loadout);
    struct rr_ui_element *this = rr_ui_choose_element_init(a, b, choose);
    struct rr_ui_choose_element_metadata *data = this->data;
    data->data = member;

    return rr_ui_set_background(rr_ui_v_container_init(rr_ui_container_init(), 10, 10, 1, this), 0xff0000ff);
}