#include <Client/Ui/Ui.h>

#include <stdio.h>

#include <Client/DOM.h>
#include <Client/Game.h>
#include <Client/InputData.h>
#include <Client/Ui/Engine.h>

static void rivet_container_on_event(struct rr_ui_element *this,
                                     struct rr_game *game)
{
    if (game->input_data->mouse_buttons_up_this_tick & 1)
        rr_copy_string(&game->rivet_account.uuid[0]);
    else if (!(game->input_data->mouse_buttons & 1))
        rr_ui_render_tooltip_below(this, game->rivet_info_tooltip, game);
}

static void render_link(struct rr_ui_element *element, struct rr_game *game)
{
    rr_renderer_set_fill(game->renderer, -1);
    rr_renderer_begin_path(game->renderer);
    rr_renderer_arc(game->renderer, 0, 0, 10);
    rr_renderer_fill(game->renderer);
}

static void link_rivet_account(struct rr_ui_element *element,
                               struct rr_game *game)
{
    if (game->input_data->mouse_buttons_up_this_tick & 1)
        // TODO: make it display a loading status and disable the click
        // funcitonality
        rr_rivet_link_account(game->rivet_account.token, 0);
}

static struct rr_ui_element *rr_ui_link_init(struct rr_game *game)
{
    struct rr_ui_element *element = rr_ui_element_init();
    element->width = element->abs_width = element->height =
        element->abs_height = 20;
    element->on_render = render_link;
    element->on_event = link_rivet_account;

    return element;
}

static struct rr_ui_element *rr_ui_rivet_init(struct rr_game *game)
{
    struct rr_ui_element *this = rr_ui_h_container_init(
        rr_ui_container_init(), 1, 5,
        rr_ui_text_init(game->rivet_account.name, 15, 0xffffffff),
        rr_ui_text_init(game->rivet_account.account_number, 15, 0xffcccccc),
        NULL);
    this->on_event = rivet_container_on_event;
    this->stop_event_propagation = 1;
    return this;
}

struct rr_ui_element *rr_ui_rivet_container_init(struct rr_game *game)
{
    return rr_ui_set_background(
        rr_ui_h_container_init(
            rr_ui_container_init(), 10, 10, rr_ui_settings_toggle_button_init(),
            rr_ui_changelog_toggle_button_init(),
            rr_ui_set_background(
                rr_ui_h_container_init(
                    rr_ui_container_init(), 5, 0,
                    rr_ui_text_init("discord.gg/kKWAUEbk9T", 15, 0xffffffff),
                    NULL),
                0x40ffffff),
            rr_ui_set_background(
                rr_ui_h_container_init(rr_ui_container_init(), 5, 0,
                                       rr_ui_rivet_init(game), NULL),
                0x40ffffff),
            rr_ui_link_init(game), NULL),
        0x80000000);
}
