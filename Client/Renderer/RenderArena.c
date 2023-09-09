#include <Client/Renderer/ComponentRender.h>

#include <math.h>

#include <Client/Game.h>
#include <Client/Assets/RenderFunctions.h>
#include <Client/Renderer/Renderer.h>
#include <Client/Simulation.h>
#include <Shared/Crypto.h>

static void render_background(struct rr_component_player_info *player_info,
                              struct rr_game *this, uint32_t prop_amount)
{
    if (player_info->arena == 0)
        return;
    if (this->cache.low_performance_mode)
        return;
    float a = this->renderer->height / 1080;
    float b = this->renderer->width / 1920;

    float s1 = (this->renderer->scale = b < a ? a : b);
    double scale = player_info->lerp_camera_fov * this->renderer->scale;
    double leftX =
        player_info->lerp_camera_x - this->renderer->width / (2 * scale);
    double rightX =
        player_info->lerp_camera_x + this->renderer->width / (2 * scale);
    double topY =
        player_info->lerp_camera_y - this->renderer->height / (2 * scale);
    double bottomY =
        player_info->lerp_camera_y + this->renderer->height / (2 * scale);

#define GRID_SIZE (512.0f)
    double newLeftX = floorf(leftX / GRID_SIZE) * GRID_SIZE;
    double newTopY = floorf(topY / GRID_SIZE) * GRID_SIZE;
    //rr_renderer_scale(this->renderer, scale);
    for (; newLeftX < rightX; newLeftX += GRID_SIZE)
    {
        for (double currY = newTopY; currY < bottomY; currY += GRID_SIZE)
        {
            uint32_t tile_index = rr_get_hash((uint32_t)(((newLeftX + 8192) / GRID_SIZE + 1) *
                                             ((currY + 8192) / GRID_SIZE + 2))) % 3;
            struct rr_renderer_context_state state;
            rr_renderer_context_state_init(this->renderer, &state);
            rr_renderer_translate(this->renderer, newLeftX + GRID_SIZE / 2,
                                  currY + GRID_SIZE / 2);
            rr_renderer_scale(this->renderer, (GRID_SIZE) / 256);
            if (this->selected_biome == 0)
                rr_renderer_draw_tile_hell_creek(this->renderer, tile_index);
            else
                rr_renderer_draw_tile_garden(this->renderer, tile_index);
            rr_renderer_context_state_free(this->renderer, &state);
        }
    }

#define render_map_feature                                                     \
    struct rr_renderer_context_state state;                                    \
    float theta = ((double)(uint32_t)(rr_get_hash(i + 200000))) /              \
                  ((double)UINT32_MAX) * (M_PI * 2);                           \
    float distance = sqrtf(((double)(uint32_t)(rr_get_hash(i + 300000))) /     \
                           ((double)UINT32_MAX)) *                             \
                     RR_ARENA_LENGTH - 50;                                     \
    float rotation = ((double)(uint32_t)(rr_get_hash(i + 400000))) /           \
                     ((double)UINT32_MAX) * (M_PI * 2);                        \
    float x = distance * sinf(theta);                                          \
    float y = distance * cosf(theta);                                          \
    if (x < leftX - (selected_feature == 8 ? 400 : 100))                       \
        continue;                                                              \
    if (x > rightX + (selected_feature == 8 ? 400 : 100))                      \
        continue;                                                              \
    if (y < topY - (selected_feature == 8 ? 400 : 100))                        \
        continue;                                                              \
    if (y > bottomY + (selected_feature == 8 ? 400 : 100))                     \
        continue;                                                              \
    rr_renderer_context_state_init(this->renderer, &state);                    \
    rr_renderer_translate(this->renderer, x, y);                               \
    rr_renderer_rotate(this->renderer, rotation);                              \
    rr_renderer_scale(this->renderer, 0.3);                                    \
    rr_renderer_draw_prop(this->renderer, selected_feature);                   \
    rr_renderer_context_state_free(this->renderer, &state);

    rr_renderer_set_global_alpha(this->renderer, 0.75f);

    // draw background features
    for (uint64_t i = 0; i < prop_amount; ++i)
    {
        uint64_t selected_feature = rr_get_hash(i) % 2;

        render_map_feature
    }

#undef GRID_SIZE
#undef render_map_feature
    uint8_t main_arena = player_info->arena == 1;
    float grid_size = main_arena ? RR_MAZE_GRID_SIZE : RR_BURRON_GRID_SIZE; 
    uint32_t maze_dim = main_arena ? RR_MAZE_DIM : RR_BURROW_MAZE_DIM;
    struct rr_maze_grid *grid = main_arena ? &RR_MAZE_HELL_CREEK[0][0] : &RR_MAZE_BURROW[0][0];
    rr_renderer_set_fill(this->renderer, 0xff000000);
    rr_renderer_set_global_alpha(this->renderer, 0.5f);
    int32_t nx = floorf(leftX / grid_size);
    int32_t ny = floorf(topY / grid_size);
    for (; nx < rightX / grid_size; ++nx)
        for (int32_t currY = ny; currY < bottomY / grid_size; ++currY)
        {
            uint8_t tile = (nx < 0 || currY < 0 || nx >= maze_dim || currY >= maze_dim) ? 0 : grid[currY*maze_dim+nx].value;
            if (tile != 1)
            {
                if (tile == 0)
                {
                    rr_renderer_begin_path(this->renderer);
                    rr_renderer_fill_rect(this->renderer, nx * grid_size, currY * grid_size, grid_size, grid_size);
                }
                else
                {
                    uint8_t left = (tile >> 1) & 1;
                    uint8_t top = tile & 1;
                    uint8_t inverse = 1 - ((tile >> 3) & 1);
                    rr_renderer_begin_path(this->renderer);
                    rr_renderer_move_to(this->renderer, (nx + inverse ^ left) * grid_size, (currY + inverse ^ top) * grid_size);
                    float start_angle = 0;
                    if (top == 0 && left == 1)
                        start_angle = M_PI / 2;
                    else if (top == 1 && left == 1)
                        start_angle = M_PI;
                    else if (top == 1 && left == 0)
                        start_angle = M_PI * 3 / 2;
                    rr_renderer_partial_arc(this->renderer, (nx + left) * grid_size, (currY + top) * grid_size, grid_size, start_angle, start_angle + M_PI / 2, 0);
                    rr_renderer_fill(this->renderer);
                }
            }
        }
}

void rr_component_arena_render(EntityIdx entity, struct rr_game *this, struct rr_simulation *simulation)
{
    struct rr_renderer_context_state state2;
    struct rr_component_player_info *player_info = this->player_info;

    uint32_t alpha = (uint32_t)(player_info->lerp_camera_fov * 51)
                        << 24;
    rr_renderer_context_state_init(this->renderer, &state2);
    rr_renderer_set_transform(this->renderer, 1, 0, 0, 0, 1, 0);
    rr_renderer_set_fill(this->renderer, 0xff45230a);
    rr_renderer_fill_rect(this->renderer, 0, 0, this->renderer->width,
                            this->renderer->height);
    rr_renderer_set_fill(this->renderer, alpha);
    rr_renderer_fill_rect(this->renderer, 0, 0, this->renderer->width,
                            this->renderer->height);
    rr_renderer_context_state_free(this->renderer, &state2);
    rr_renderer_context_state_init(this->renderer, &state2);

    struct rr_component_arena *arena =
        rr_simulation_get_arena(this->simulation, 1);

    rr_renderer_set_line_width(this->renderer, 1.0f);
    rr_renderer_set_stroke(this->renderer, alpha);
    rr_renderer_set_global_alpha(this->renderer, 1);
    render_background(player_info, this, this->cache.map_props * 750);

    rr_renderer_context_state_free(this->renderer, &state2);
}