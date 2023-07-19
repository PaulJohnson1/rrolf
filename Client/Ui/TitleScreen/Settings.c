#include <Client/Ui/Ui.h>

#include <stdio.h>
#include <stdlib.h>
#include <string.h>

#include <Client/Game.h>
#include <Client/InputData.h>
#include <Client/Renderer/Renderer.h>
#include <Client/Ui/Engine.h>

#include <Shared/Utilities.h>

static uint8_t settings_container_should_show(struct rr_ui_element *this,
                                              struct rr_game *game)
{
    return game->top_ui_open == 1;
}

static void settings_container_animate(struct rr_ui_element *this,
                                       struct rr_game *game)
{
    this->width = this->abs_width;
    this->height = this->abs_height;
    rr_renderer_translate(
        game->renderer, -(this->x + this->abs_width / 2) * 2 * this->animation,
        0);
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

void settings_toggle_button_on_event(struct rr_ui_element *this,
                                     struct rr_game *game)
{
    if (game->input_data->mouse_buttons_up_this_tick & 1)
    {
        if (game->top_ui_open == 1)
            game->top_ui_open = 0;
        else
            game->top_ui_open = 1;
    }
}

struct rr_ui_element *rr_ui_settings_toggle_button_init()
{
    struct rr_ui_element *this = rr_ui_element_init();
    this->fill = 0xff888888;
    this->abs_width = this->abs_height = this->width = this->height = 40;
    this->on_event = settings_toggle_button_on_event;
    this->on_render = inventory_toggle_on_render;
    return this;
}

struct rr_ui_element *rr_ui_settings_container_init(struct rr_game *game)
{
    struct rr_ui_element *this = rr_ui_pad(
        rr_ui_set_background(
            rr_ui_v_pad(
                rr_ui_set_justify(
                    rr_ui_v_container_init(
                        rr_ui_container_init(), 10, 10, 6,
                        rr_ui_text_init("Settings", 24, 0xffffffff),
                        rr_ui_set_justify(
                            rr_ui_h_container_init(
                                rr_ui_container_init(), 5, 10, 2,
                                rr_ui_h_slider_init(150, 20,
                                                    &game->settings.map_props),
                                rr_ui_text_init("map props", 12,
                                                0xffffffff)),
                            -1, -1),
                        rr_ui_set_justify(
                            rr_ui_h_container_init(
                                rr_ui_container_init(), 5, 10, 2,
                                rr_ui_toggle_box_init(&game->settings.use_mouse),
                                rr_ui_text_init("Mouse movement", 15,
                                                0xffffffff)),
                            -1, -1),
                        rr_ui_set_justify(
                            rr_ui_h_container_init(
                                rr_ui_container_init(), 5, 10, 2,
                                rr_ui_toggle_box_init(&game->settings.screen_shake),
                                rr_ui_text_init("Screen shake", 15,
                                                0xffffffff)),
                            -1, -1),
                        rr_ui_set_justify(
                            rr_ui_h_container_init(
                                rr_ui_container_init(), 5, 10, 2,
                                rr_ui_toggle_box_init(
                                    &game->settings.displaying_debug_information),
                                rr_ui_text_init("Show debug info", 15,
                                                0xffffffff)),
                            -1, -1),
                        rr_ui_set_justify(
                            rr_ui_h_container_init(
                                rr_ui_container_init(), 5, 10, 2,
                                rr_ui_toggle_box_init(&game->settings.show_ui_hitbox),
                                rr_ui_text_init("Show ui hitboxes", 15,
                                                0xffffffff)),
                            -1, -1)),
                    -1, -1),
                80),
            0x40ffffff),
        10);
    this->animate = settings_container_animate;
    this->should_show = settings_container_should_show;
    return this;
}