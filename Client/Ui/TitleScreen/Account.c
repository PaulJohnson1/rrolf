#include <Client/Ui/Ui.h>

#include <stdio.h>
#include <stdlib.h>
#include <string.h>

#include <Client/Game.h>
#include <Client/InputData.h>
#include <Client/Renderer/Renderer.h>
#include <Client/Ui/Engine.h>

#include <Shared/Utilities.h>

static uint8_t account_container_should_show(struct rr_ui_element *this,
                                              struct rr_game *game)
{
    return game->menu_open == rr_game_menu_account && !game->simulation_ready;
}

static uint8_t account_button_should_show(struct rr_ui_element *this,
                                              struct rr_game *game)
{
    return !game->simulation_ready;
}

static void account_container_animate(struct rr_ui_element *this,
                                       struct rr_game *game)
{
    this->width = this->abs_width;
    this->height = this->abs_height;
    rr_renderer_translate(
        game->renderer, -(this->x + this->abs_width / 2) * 2 * this->animation,
        0);
}

static void account_toggle_button_on_render(struct rr_ui_element *this,
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
    rr_renderer_round_rect(renderer, -this->abs_width / 2, -this->abs_height / 2,
                           this->abs_width, this->abs_height, 6);
    rr_renderer_fill(renderer);
}

static void account_toggle_button_on_event(struct rr_ui_element *this,
                                            struct rr_game *game)
{
    if (game->input_data->mouse_buttons_up_this_tick & 1)
    {
        if (game->pressed != this)
            return;
        if (game->menu_open == rr_game_menu_account)
            game->menu_open = rr_game_menu_none;
        else
            game->menu_open = rr_game_menu_account;
    }
    else
        rr_ui_render_tooltip_below(this, game->account_tooltip, game);
}

struct rr_ui_element *rr_ui_account_toggle_button_init()
{
    struct rr_ui_element *this = rr_ui_element_init();
    this->fill = 0x80888888;
    this->abs_width = this->abs_height = this->width = this->height = 40;
    this->on_event = account_toggle_button_on_event;
    this->on_render = account_toggle_button_on_render;
    this->should_show = account_button_should_show;
    return this;
}

struct rr_ui_element *rr_ui_account_container_init(struct rr_game *game)
{
    struct rr_ui_element *this = rr_ui_pad(
        rr_ui_set_background(
            rr_ui_v_pad(
                rr_ui_set_justify(
                    rr_ui_v_container_init(
                        rr_ui_container_init(), 10, 5,
                        rr_ui_text_init("Account", 24, 0xffffffff),
                        rr_ui_static_space_init(10),
                        rr_ui_h_container_init(rr_ui_container_init(), 0, 0, 
                            rr_ui_text_init("Account Name: ", 15, 0xffffffff),
                            rr_ui_text_init(game->rivet_account.name, 15, 0xffffffff),
                            rr_ui_text_init(game->rivet_account.account_number, 15, 0xffcccccc),
                            NULL
                        ),
                        rr_ui_text_init(game->rivet_account.uuid, 15, 0xffffffff),
                        rr_ui_static_space_init(10),
                        rr_ui_text_init("Progress on unlinked accounts", 15, 0xffffffff),
                        rr_ui_text_init("will be lost after 4 months.", 15, 0xffffffff),
                        NULL
                    ), -1, -1
                ), 50
            ), 0x40ffffff
        ), 10
    );
    this->animate = account_container_animate;
    this->should_show = account_container_should_show;
    return this;
}