#include <Client/Ui/Ui.h>

#include <math.h>
#include <stdio.h>
#include <stdlib.h>

#include <Client/Game.h>
#include <Client/Simulation.h>
#include <Client/Assets/RenderFunctions.h>
#include <Client/Renderer/Renderer.h>
#include <Shared/StaticData.h>

struct rr_renderer minimaps[2];

#define DRAW_MINIMAP(renderer, grid, maze_dim) \
    {\
        rr_renderer_init(renderer); \
        float s = floorf(this->abs_width / maze_dim);\
        rr_renderer_set_dimensions(renderer, s * maze_dim, s * maze_dim); \
        rr_renderer_set_fill(renderer, 0xffffffff); \
        for (uint32_t x = 0; x < maze_dim; ++x)\
            for (uint32_t y = 0; y < maze_dim; ++y)\
            {\
                uint8_t at = grid[y][x].value;\
                if (at == 1)\
                {\
                    rr_renderer_begin_path(renderer);\
                    rr_renderer_fill_rect(renderer, x * s, y * s, s, s);\
                }\
                else if (at != 0)\
                {\
                    uint8_t left = (at >> 1) & 1;\
                    uint8_t top = at & 1;\
                    uint8_t inverse = (at >> 3) & 1;\
                    rr_renderer_begin_path(renderer);\
                    rr_renderer_move_to(renderer, (x + inverse ^ left) * s, (y + inverse ^ top) * s);\
                    float start_angle = 0;\
                    if (top == 0 && left == 1)\
                        start_angle = M_PI / 2;\
                    else if (top == 1 && left == 1)\
                        start_angle = M_PI;\
                    else if (top == 1 && left == 0)\
                        start_angle = M_PI * 3 / 2;\
                    rr_renderer_partial_arc(renderer, (x + left) * s, (y + top) * s, s, start_angle, start_angle + M_PI / 2, 0);\
                    rr_renderer_fill(renderer);\
                }\
            }\
    }

static void minimap_on_render(struct rr_ui_element *this,
                                 struct rr_game *game)
{
    if (!game->simulation_ready)
        return;
    struct rr_renderer *renderer = game->renderer;
    struct rr_component_player_info *player_info = game->player_info;
    float a = renderer->height / 1080;
    float b = renderer->width / 1920;

    float s1 = (renderer->scale = b < a ? a : b);
    double scale = player_info->lerp_camera_fov * 0.25;
    uint8_t main_arena = player_info->arena == 1;
    float grid_size = main_arena ? RR_MAZE_GRID_SIZE : RR_BURRON_GRID_SIZE; 
    uint32_t maze_dim = main_arena ? RR_MAZE_DIM : RR_BURROW_MAZE_DIM;
    double midX =
        (player_info->lerp_camera_x / (grid_size * maze_dim) - 0.5) * this->abs_width;
    double midY =
        (player_info->lerp_camera_y / (grid_size * maze_dim) - 0.5) * this->abs_height;
    double W = renderer->width / scale / (grid_size * maze_dim) * this->abs_width;
    double H = renderer->height / scale / (grid_size * maze_dim) * this->abs_height;
    rr_renderer_scale(renderer, renderer->scale);
    rr_renderer_begin_path(renderer);
    rr_renderer_rect(renderer, midX - W / 2, midY - H / 2, W, H);
    //rr_renderer_clip(renderer);
    struct rr_renderer *minimap = &minimaps[1 - main_arena];
    rr_renderer_scale(renderer, this->abs_width / minimap->width);
    rr_renderer_draw_image(renderer, minimap);
    rr_renderer_scale(renderer, minimap->width / this->abs_width);
    rr_renderer_set_fill(renderer, 0xff0000ff);
    rr_renderer_set_global_alpha(renderer, 0.8);
    rr_renderer_begin_path(renderer);
    rr_renderer_arc(renderer, midX, midY, 1.5);
    rr_renderer_fill(renderer);
    rr_renderer_set_fill(renderer, 0xffff00ff);
    for (uint32_t i = 1; i < RR_SQUAD_MEMBER_COUNT; ++i)
    {
        if (game->player_infos[i] == RR_NULL_ENTITY)
            break;
        player_info = rr_simulation_get_player_info(game->simulation, game->player_infos[i]);
        if (player_info->arena != game->player_info->arena)
            continue;
        rr_renderer_begin_path(renderer);
        rr_renderer_arc(renderer, this->abs_width * (player_info->camera_x / (grid_size * maze_dim)
        - 0.5), this->abs_height * (player_info->camera_y / (grid_size * maze_dim) - 0.5), 1.5);
        rr_renderer_fill(renderer);
    }
}

struct rr_ui_element *rr_ui_minimap_init(struct rr_game *game)
{
    struct rr_ui_element *this = rr_ui_element_init();
    
    this->abs_width = this->width = this->abs_height = this->height = 150;
    this->on_render = minimap_on_render;
    DRAW_MINIMAP(&minimaps[0], RR_MAZE_HELL_CREEK, RR_MAZE_DIM)
    DRAW_MINIMAP(&minimaps[1], RR_MAZE_BURROW, RR_BURROW_MAZE_DIM)
    return this;
}