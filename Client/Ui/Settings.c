#include <Client/Ui/Ui.h>

#include <stdio.h>
#include <stdlib.h>
#include <string.h>

#include <Client/Game.h>
#include <Client/Ui/Engine.h>
#include <Client/Renderer/Renderer.h>

#include <Shared/Utilities.h>

static uint8_t settings_container_animate(struct rr_ui_element *this,
                                        struct rr_game *game)
{
    if (game->top_ui_open != 1 || game->simulation_ready)
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
    this->width = this->abs_width;
    this->height = this->abs_height;
    rr_renderer_translate(game->renderer, -(this->x + this->abs_width / 2) * 2 * this->animation, 0);
    return 1;
}

struct rr_ui_element *rr_ui_settings_container_init()
{
    struct rr_ui_element *this = rr_ui_pad(
        rr_ui_set_background(
            rr_ui_v_pad(
                rr_ui_set_justify(
                    rr_ui_v_container_init(rr_ui_container_init(), 10, 10, 1,
                        rr_ui_text_init("Settings", 24, 0xffffffff)
                    )
                , -1, -1)
            , 80)
        , 0xff999999)
    , 10);
    this->animate = settings_container_animate;
    return this;
}