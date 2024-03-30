// Copyright (C) 2024  Paul Johnson

// This program is free software: you can redistribute it and/or modify
// it under the terms of the GNU Affero General Public License as
// published by the Free Software Foundation, either version 3 of the
// License, or (at your option) any later version.

// This program is distributed in the hope that it will be useful,
// but WITHOUT ANY WARRANTY; without even the implied warranty of
// MERCHANTABILITY or FITNESS FOR A PARTICULAR PURPOSE.  See the
// GNU Affero General Public License for more details.

// You should have received a copy of the GNU Affero General Public License
// along with this program.  If not, see <https://www.gnu.org/licenses/>.

#include <Client/Ui/Ui.h>

#include <stdlib.h>

#include <Client/Game.h>
#include <Client/Renderer/Renderer.h>

struct level_bar_metadata
{
    double lerp_xp;
    uint32_t level;
};

void level_bar_on_render(struct rr_ui_element *this, struct rr_game *game)
{
    struct level_bar_metadata *data = this->data;
    struct rr_renderer *renderer = game->renderer;
    rr_renderer_scale(renderer, renderer->scale);
    double xp = game->cache.experience;
    uint32_t next_level = 2;
    while (xp >= xp_to_reach_level(next_level))
    {
        xp -= xp_to_reach_level(next_level);
        ++next_level;
    }
    if (data->lerp_xp == 0 && data->level == 0)
    {
        data->lerp_xp = xp;
        data->level = next_level - 1;
    }
    else if (data->level > next_level - 1)
    {
        data->lerp_xp = xp;
        data->level = next_level - 1;
    }
    else
    {
        if (data->level == next_level - 1)
        {
            data->lerp_xp = rr_lerp(data->lerp_xp, xp, 15 * game->lerp_delta);
        }
        else
        {
            data->lerp_xp =
                rr_lerp(data->lerp_xp, xp_to_reach_level(data->level + 1),
                        15 * game->lerp_delta);
            if (data->lerp_xp >= xp_to_reach_level(data->level + 1) * 0.995)
            {
                ++data->level;
                data->lerp_xp = 0;
            }
        }
    }
    double ratio = data->lerp_xp / xp_to_reach_level(data->level + 1);
    rr_renderer_set_stroke(renderer, 0xff222222);
    rr_renderer_set_line_cap(renderer, 1);
    rr_renderer_set_line_width(renderer, this->abs_height);
    rr_renderer_begin_path(renderer);
    rr_renderer_move_to(renderer, this->abs_height / 2 - this->abs_width / 2,
                        0);
    rr_renderer_line_to(renderer, this->abs_width / 2 - this->abs_height / 2,
                        0);
    rr_renderer_stroke(renderer);
    rr_renderer_set_stroke(renderer, 0xff75dd34);
    rr_renderer_set_line_width(renderer, this->abs_height * 0.8);
    rr_renderer_begin_path(renderer);
    rr_renderer_move_to(renderer, this->abs_height / 2 - this->abs_width / 2,
                        0);
    rr_renderer_line_to(renderer,
                        this->abs_height / 2 - this->abs_width / 2 +
                            (this->abs_width - this->abs_height) * ratio,
                        0);
    rr_renderer_stroke(renderer);
    rr_renderer_set_stroke(renderer, 0xff222222);
    rr_renderer_set_fill(renderer, 0xffffffff);
    rr_renderer_set_text_size(renderer, this->abs_height * 0.5);
    rr_renderer_set_text_align(renderer, 1);
    rr_renderer_set_text_baseline(renderer, 1);
    rr_renderer_set_line_width(renderer, this->abs_height * 0.5 * 0.12);
    char out[16];
    sprintf(out, "Level %d", data->level);
    rr_renderer_begin_path(renderer);
    rr_renderer_stroke_text(renderer, out, 0, 0);
    rr_renderer_fill_text(renderer, out, 0, 0);
    // printf("%.0f %d\n", xp, next_level - 1);
}

struct rr_ui_element *rr_ui_level_bar_init(float width)
{
    struct rr_ui_element *this = rr_ui_element_init();
    struct level_bar_metadata *data = malloc(sizeof *data);
    data->lerp_xp = data->level = 0;
    this->data = data;
    this->on_render = level_bar_on_render;
    this->abs_width = this->width = width;
    this->abs_height = this->height = 40;
    return this;
}
