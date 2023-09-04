#include <Client/Ui/Ui.h>

#include <math.h>
#include <stdio.h>
#include <stdlib.h>

#include <Client/Game.h>
#include <Client/Simulation.h>
#include <Client/Assets/RenderFunctions.h>
#include <Client/Renderer/Renderer.h>
#include <Shared/StaticData.h>

struct rr_renderer minimap;

static void minimap_on_render(struct rr_ui_element *this,
                                 struct rr_game *game)
{
    struct rr_renderer *renderer = game->renderer;
    struct rr_component_player_info *player_info = game->player_info;
    float a = renderer->height / 1080;
    float b = renderer->width / 1920;

    float s1 = (renderer->scale = b < a ? a : b);
    double scale = player_info->lerp_camera_fov * 0.25;
    double midX =
        (player_info->lerp_camera_x / RR_ARENA_LENGTH - 0.5) * this->abs_width;
    double midY =
        (player_info->lerp_camera_y / RR_ARENA_LENGTH - 0.5) * this->abs_height;
    double W = renderer->width / scale / RR_ARENA_LENGTH * this->abs_width;
    double H = renderer->height / scale / RR_ARENA_LENGTH * this->abs_height;
    rr_renderer_scale(renderer, renderer->scale);
    rr_renderer_begin_path(renderer);
    rr_renderer_rect(renderer, midX - W / 2, midY - H / 2, W, H);
    rr_renderer_clip(renderer);
    rr_renderer_draw_image(renderer, &minimap);
    rr_renderer_set_fill(renderer, 0xff0000ff);
    rr_renderer_set_global_alpha(renderer, 0.8);
    rr_renderer_begin_path(renderer);
    rr_renderer_arc(renderer, midX, midY, 3);
    rr_renderer_fill(renderer);
    rr_renderer_set_fill(renderer, 0xffff00ff);
    for (uint32_t i = 1; i < RR_SQUAD_MEMBER_COUNT; ++i)
    {
        if (game->player_infos[i] == RR_NULL_ENTITY)
            break;
        player_info = rr_simulation_get_player_info(game->simulation, game->player_infos[i]);
        rr_renderer_begin_path(renderer);
        rr_renderer_arc(renderer, this->abs_width * (player_info->camera_x / RR_ARENA_LENGTH
        - 0.5), this->abs_height * (player_info->camera_y / RR_ARENA_LENGTH - 0.5), 3);
        rr_renderer_fill(renderer);
    }
}

struct rr_ui_element *rr_ui_minimap_init(struct rr_game *game)
{
    uint32_t s = 4;
    struct rr_ui_element *this = rr_ui_element_init();
    rr_renderer_init(&minimap);
    rr_renderer_set_dimensions(&minimap, RR_MAZE_DIM * s, RR_MAZE_DIM * s);
    rr_renderer_set_fill(&minimap, 0xffffffff);
    for (uint32_t x = 0; x < RR_MAZE_DIM; ++x)
        for (uint32_t y = 0; y < RR_MAZE_DIM; ++y)
        {
            //rr_renderer_set_fill(&minimap, 0xffffffff);
            uint8_t at = RR_MAZE_HELL_CREEK[y][x].value;
            if (at == 1)
            {
                rr_renderer_begin_path(&minimap);
                rr_renderer_fill_rect(&minimap, x * s, y * s, s, s);
            }
            else if (at != 0)
            {
                uint8_t left = (at >> 1) & 1;
                uint8_t top = at & 1;
                uint8_t inverse = (at >> 3) & 1;
                rr_renderer_begin_path(&minimap);
                rr_renderer_move_to(&minimap, (x + inverse ^ left) * s, (y + inverse ^ top) * s);
                float start_angle = 0;
                if (top == 0 && left == 1)
                    start_angle = M_PI / 2;
                else if (top == 1 && left == 1)
                    start_angle = M_PI;
                else if (top == 1 && left == 0)
                    start_angle = M_PI * 3 / 2;
                rr_renderer_partial_arc(&minimap, (x + left) * s, (y + top) * s, s, start_angle, start_angle + M_PI / 2, 0);
                rr_renderer_fill(&minimap);
            }
            continue;
            rr_renderer_set_fill(&minimap, 0xffff0000);
            rr_renderer_set_text_size(&minimap, s / 2.5);
            char a[16];
            a[sprintf(a, "%d,%d", x % 10, y % 10)] = 0;
            rr_renderer_set_text_align(&minimap, 1);
            rr_renderer_set_text_baseline(&minimap, 1);
            rr_renderer_fill_text(&minimap, a, (x + 0.5) * s, (y + 0.5) * s);
        }
    
    this->abs_width = this->width = this->abs_height = this->height = minimap.width;
    this->on_render = minimap_on_render;
    return this;
}