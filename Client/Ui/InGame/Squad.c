#include <Client/Ui/Ui.h>

#include <stdlib.h>

#include <Client/Game.h>
#include <Client/Simulation.h>
#include <Client/Renderer/Renderer.h>
#include <Client/Renderer/ComponentRender.h>
#include <Client/Ui/Engine.h>

#include <Shared/Vector.h>

struct player_hud_metadata
{
    uint8_t pos;
};

static uint8_t player_hud_should_show(struct rr_ui_element *this, struct rr_game *game)
{
    if (!game->simulation_ready)
        return 0;   
    struct player_hud_metadata *data = this->data;
    if (game->player_infos[data->pos] == RR_NULL_ENTITY)
        return 0;
    return 1;
}

static void player_hud_on_render(struct rr_ui_element *this, struct rr_game *game)
{
    struct player_hud_metadata *data = this->data;
    struct rr_renderer *renderer = game->renderer;
    rr_renderer_scale(renderer, renderer->scale);
    struct rr_component_player_info *player_info = rr_simulation_get_player_info(game->simulation, game->player_infos[data->pos]);
    if (player_info->flower_id == RR_NULL_ENTITY)
    {

    }
    else
    {
        struct rr_component_health *health = rr_simulation_get_health(game->simulation, player_info->flower_id);
        float length = this->abs_width / 2;
        rr_renderer_set_line_cap(renderer, 1);
        rr_renderer_set_stroke(renderer, 0xff222222);
        rr_renderer_set_line_width(renderer, 25);
        rr_renderer_begin_path(renderer);
        rr_renderer_move_to(renderer, -length, 0);
        rr_renderer_line_to(renderer, length, 0);
        rr_renderer_stroke(renderer);

        rr_renderer_set_stroke(renderer, 0xff75dd34);
        rr_renderer_set_line_width(renderer, 20);
        rr_renderer_begin_path(renderer);
        rr_renderer_move_to(renderer, -length / 2, 0);
        rr_renderer_line_to(
            renderer,
            -length / 2 + 1.5 * length * health->lerp_health / health->max_health, 0);
        rr_renderer_stroke(renderer);
        rr_renderer_translate(renderer, -length, 0);
        rr_renderer_scale(renderer, this->abs_height / 50);
        rr_component_flower_render(player_info->flower_id, game);
        if (data->pos != 0 && game->player_info != NULL)
        {
            struct rr_component_physical *physical = rr_simulation_get_physical(game->simulation, player_info->parent_id);
            struct rr_vector vector = {physical->x - game->player_info->camera_x, physical->y - game->player_info->camera_y};
            rr_renderer_rotate(renderer, rr_vector_theta(&vector));
            rr_renderer_translate(renderer, this->abs_height * 0.55, 0);
            rr_renderer_set_line_cap(renderer, 1);
            rr_renderer_set_stroke(renderer, 0xff222222);
            rr_renderer_set_fill(renderer, 0xffffffff);
            rr_renderer_set_line_join(renderer, 1);
            rr_renderer_set_line_width(renderer, 1);
            rr_renderer_begin_path(renderer);
            rr_renderer_move_to(renderer, 0, -5);
            rr_renderer_line_to(renderer, 6, 0);
            rr_renderer_line_to(renderer, 0, 5);
            rr_renderer_line_to(renderer, 0, -5);
            rr_renderer_fill(renderer);
            rr_renderer_stroke(renderer);
        }
    }
}

struct rr_ui_element *rr_ui_in_game_player_hud_init(uint8_t pos)
{
    struct rr_ui_element *this = rr_ui_element_init();
    struct player_hud_metadata *data = malloc(sizeof *data);
    data->pos = pos;
    this->data = data;
    this->should_show = player_hud_should_show;
    this->on_render = player_hud_on_render;
    this->abs_height = this->height = pos ? 50 : 60;
    this->abs_width = this->width = pos ? 150 : 180;
    return rr_ui_set_justify(this, -1, -1);
}