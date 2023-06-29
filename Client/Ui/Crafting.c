#include <Client/Ui/Element.h>

#include <stdlib.h>
#include <stdio.h>
#include <math.h>

#include <Client/Game.h>
#include <Client/InputData.h>
#include <Client/Renderer/Renderer.h>
#include <Client/Renderer/RenderFunctions.h>

#include <Client/Ui/Engine.h>

#include <Shared/Utilities.h>

struct crafting_ui_metadata
{
    uint8_t prev_id;
};

static void crafting_button_event(struct rr_ui_element *this, uint8_t type, struct rr_game *game, void *_captures)
{
    if (type == 1 && game->crafting_data.success_count == 0 && game->crafting_data.count >= 4) //mouse_down
    {
        float chances[rr_rarity_id_max - 1] = {0.5, 0.4, 0.2, 0.1, 0.05, 0.02};
        uint8_t success = 0;
        while (game->crafting_data.count >= 4)
        {
            if (rr_frand() < chances[game->crafting_data.crafting_rarity])
            {
                success = 1;
                game->crafting_data.count -= 4;   
                game->inventory[game->crafting_data.crafting_id][game->crafting_data.crafting_rarity] -= 4;
                ++game->crafting_data.success_count;
                ++game->inventory[game->crafting_data.crafting_id][game->crafting_data.crafting_rarity + 1];
            }
            else
            {
                uint8_t loss = 1 + (uint8_t) (rr_frand() / 3);
                game->crafting_data.count -= loss;
                game->inventory[game->crafting_data.crafting_id][game->crafting_data.crafting_rarity] -= loss;
            }
        }
        if (success)
            game->crafting_data.count = 0;
        /*
        game->crafting_data.success_count = 0 * game->crafting_data.count >> 2;
        game->inventory[game->crafting_data.crafting_id][game->crafting_data.crafting_rarity] -= 5;
        game->inventory[game->crafting_data.crafting_id][game->crafting_data.crafting_rarity + 1] += game->crafting_data.success_count;
        game->crafting_data.count -= 5;
        */
        //game->crafting_data.crafting_id = 0;
        //game->crafting_data.count = 0;
    }
}

static void crafting_ui_on_render(struct rr_ui_element *this, void *_game)
{
    if (this->hidden)
        return;
    struct rr_game *game = _game;
    struct rr_renderer *renderer = game->renderer;
    struct button_metadata *data = this->misc_data;
    struct rr_renderer_context_state state;
    struct rr_renderer_context_state state1;
    rr_renderer_init_context_state(renderer, &state);
    ui_translate(this, renderer);
    rr_renderer_scale(renderer, renderer->scale);
    if (game->crafting_data.success_count == 0)
    {
        for (uint8_t i = 0; i < 4; ++i)
        {
            rr_renderer_init_context_state(renderer, &state1);
            float angle = M_PI * i * 0.5;
            rr_renderer_translate(renderer, cosf(angle) * 100, sinf(angle) * 100);
            rr_renderer_set_fill(renderer, 0xa0999999);
            rr_renderer_begin_path(renderer);
            rr_renderer_round_rect(renderer, -30, -30, 60, 60, 6);
            rr_renderer_fill(renderer);
            if (game->crafting_data.crafting_id != 0 && ((game->crafting_data.count + (3 - i)) >> 2) > 0)
            {
                float *matrix = game->renderer->state.transform_matrix;
                uint8_t pressed = 0;
                if (fabsf(game->input_data->mouse_x - matrix[2]) < 60 * matrix[0] / 2 && fabsf(game->input_data->mouse_y - matrix[5]) < 60 * matrix[4] / 2)
                {
                    pressed = 1;
                    renderer->state.filter.amount = 0.2;
                }

                rr_renderer_render_background(renderer, game, game->crafting_data.crafting_rarity);
                
                rr_renderer_draw_image(renderer, &game->static_petals[game->crafting_data.crafting_id][game->crafting_data.crafting_rarity]);

                rr_renderer_translate(renderer, 20, -20);
                rr_renderer_rotate(renderer, 0.5);
                rr_renderer_set_fill(renderer, 0xffffffff);
                rr_renderer_set_stroke(renderer, 0xff222222);
                rr_renderer_set_text_align(renderer, 1);
                rr_renderer_set_text_baseline(renderer, 1);
                rr_renderer_set_text_size(renderer, 12);
                rr_renderer_set_line_width(renderer, 12 * 0.12);

                char out[12];
                sprintf(&out[0], "x%d", (game->crafting_data.count + (3 - i)) >> 2);
                rr_renderer_stroke_text(renderer, (char const *) &out, 0, 0);
                rr_renderer_fill_text(renderer, (char const *) &out, 0, 0);
                //manual check for a mouse collision
                if (pressed)
                {
                    if (game->input_data->mouse_buttons_this_tick & 1)
                    {
                        game->crafting_data.crafting_id = 0;
                        game->crafting_data.count = 0;
                    }
                }
            }
            rr_renderer_free_context_state(renderer, &state1);
        }
    }
    else
    {
        float *matrix = game->renderer->state.transform_matrix;
        uint8_t pressed = fabsf(game->input_data->mouse_x - matrix[2]) < 60 * matrix[0] / 2 && fabsf(game->input_data->mouse_y - matrix[5]) < 60 * matrix[4] / 2;
        rr_renderer_init_context_state(renderer, &state1);
        rr_renderer_render_background(renderer, game, game->crafting_data.crafting_rarity + 1);
                
        rr_renderer_draw_image(renderer, &game->static_petals[game->crafting_data.crafting_id][game->crafting_data.crafting_rarity + 1]);
        rr_renderer_free_context_state(renderer, &state1);
        rr_renderer_translate(renderer, 20, -20);
        rr_renderer_rotate(renderer, 0.5);
        rr_renderer_set_fill(renderer, 0xffffffff);
        rr_renderer_set_stroke(renderer, 0xff222222);
        rr_renderer_set_text_align(renderer, 1);
        rr_renderer_set_text_baseline(renderer, 1);
        rr_renderer_set_text_size(renderer, 12);
        rr_renderer_set_line_width(renderer, 12 * 0.12);

        char out[12];
        sprintf(&out[0], "x%d", game->crafting_data.success_count);
        rr_renderer_stroke_text(renderer, (char const *) &out, 0, 0);
        rr_renderer_fill_text(renderer, (char const *) &out, 0, 0);
        if (pressed && game->input_data->mouse_buttons_this_tick & 1)
        {
            game->crafting_data.crafting_id = 0;
            game->crafting_data.count = 0;
            game->crafting_data.success_count = 0;
        }
    }
    rr_renderer_free_context_state(renderer, &state);
}

struct rr_ui_element *rr_ui_crafting_button_init()
{
    struct rr_ui_element *element = rr_ui_button_init();
    struct button_metadata *data = element->misc_data;
    data->on_event = crafting_button_event;
    data->fill_style = 0xff1dd129;
    data->round_radius = 6;
    data->line_width = 6;
    data->text = "Craft";
    element->width = 120;
    element->height = 40;
    return element;
}

static struct rr_ui_element *rr_ui_crafting_spots_init()
{
    struct rr_ui_element *element = rr_ui_element_init();
    element->width = 300;
    element->height = 300;
    element->on_render = crafting_ui_on_render;
    return element;
}

struct rr_ui_element *rr_ui_crafting_ui_init()
{
    struct rr_ui_element *element = rr_ui_set_background(
                rr_ui_v_container_init(rr_ui_container_init(), 15, 15, 2, 
                    rr_ui_h_container_init(rr_ui_container_init(), 0, 30, 2,
                        rr_ui_crafting_spots_init(),
                        rr_ui_crafting_button_init()
                    ),
                    rr_ui_scroll_container_init(rr_ui_crafting_inventory_container_init(), 400, 0x0000000)
                )
    , 0xffa9e245);
    return element;
}