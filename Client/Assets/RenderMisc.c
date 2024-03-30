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

#include <Client/Assets/RenderFunctions.h>

#include <stdlib.h>

#include <Client/Assets/Render.h>
#include <Client/Renderer/Renderer.h>

#define TILES_SIZE 3
#define PROP_SIZE 2

struct rr_renderer_spritesheet background_tiles;

static void asset_web_draw(struct rr_renderer *renderer)
{
    rr_renderer_scale(renderer, 10);
    rr_renderer_set_stroke(renderer, 0xffffffff);
    rr_renderer_set_line_cap(renderer, 1);
    rr_renderer_set_line_width(renderer, 0.75);
    rr_renderer_begin_path(renderer);
    rr_renderer_move_to(renderer, 10, 0);
    rr_renderer_line_to(renderer, -10, 0);
    rr_renderer_move_to(renderer, 0, 10);
    rr_renderer_line_to(renderer, 0, -10);
    rr_renderer_move_to(renderer, 7.0710678118654755, 7.0710678118654755);
    rr_renderer_line_to(renderer, -7.0710678118654755, -7.0710678118654755);
    rr_renderer_move_to(renderer, -7.0710678118654755, 7.0710678118654755);
    rr_renderer_line_to(renderer, 7.0710678118654755, -7.0710678118654755);
    rr_renderer_move_to(renderer, 8, 0);
    rr_renderer_quadratic_curve_to(renderer, 4.619397662556434,
                                   1.913417161825449, 5.656854249492381,
                                   5.65685424949238);
    rr_renderer_quadratic_curve_to(renderer, 1.9134171618254492,
                                   4.619397662556434, 4.898587196589413e-16, 8);
    rr_renderer_quadratic_curve_to(renderer, -1.9134171618254485,
                                   4.619397662556434, -5.65685424949238,
                                   5.656854249492381);
    rr_renderer_quadratic_curve_to(renderer, -4.619397662556434,
                                   1.9134171618254494, -8,
                                   9.797174393178826e-16);
    rr_renderer_quadratic_curve_to(renderer, -4.619397662556434,
                                   -1.9134171618254483, -5.6568542494923815,
                                   -5.65685424949238);
    rr_renderer_quadratic_curve_to(renderer, -1.9134171618254516,
                                   -4.619397662556432, -1.4695761589768238e-15,
                                   -8);
    rr_renderer_quadratic_curve_to(renderer, 1.91341716182545,
                                   -4.619397662556433, 5.656854249492379,
                                   -5.6568542494923815);
    rr_renderer_quadratic_curve_to(renderer, 4.619397662556432,
                                   -1.913417161825452, 8,
                                   -1.959434878635765e-15);
    rr_renderer_move_to(renderer, 5, 0);
    rr_renderer_quadratic_curve_to(renderer, 2.77163859753386,
                                   1.1480502970952693, 3.5355339059327378,
                                   3.5355339059327373);
    rr_renderer_quadratic_curve_to(renderer, 1.1480502970952695,
                                   2.77163859753386, 3.061616997868383e-16, 5);
    rr_renderer_quadratic_curve_to(renderer, -1.1480502970952693,
                                   2.77163859753386, -3.5355339059327373,
                                   3.5355339059327378);
    rr_renderer_quadratic_curve_to(renderer, -2.77163859753386,
                                   1.1480502970952697, -5,
                                   6.123233995736766e-16);
    rr_renderer_quadratic_curve_to(renderer, -2.7716385975338604,
                                   -1.148050297095269, -3.5355339059327386,
                                   -3.5355339059327373);
    rr_renderer_quadratic_curve_to(renderer, -1.148050297095271,
                                   -2.7716385975338595, -9.184850993605148e-16,
                                   -5);
    rr_renderer_quadratic_curve_to(renderer, 1.14805029709527,
                                   -2.77163859753386, 3.535533905932737,
                                   -3.5355339059327386);
    rr_renderer_quadratic_curve_to(renderer, 2.7716385975338595,
                                   -1.148050297095271, 5,
                                   -1.2246467991473533e-15);
    rr_renderer_stroke(renderer);
    rr_renderer_scale(renderer, 0.1);
}

void rr_renderer_draw_tile_hell_creek(struct rr_renderer *renderer, uint8_t pos)
{
    render_sprite_from_cache(renderer, &background_tiles, pos);
}

void rr_renderer_draw_tile_garden(struct rr_renderer *renderer, uint8_t pos)
{
    render_sprite_from_cache(renderer, &background_tiles, TILES_SIZE + pos);
}

void rr_renderer_draw_prop(struct rr_renderer *renderer, uint8_t pos)
{
    render_sprite_from_cache(renderer, &background_tiles, 2 * TILES_SIZE + pos);
}

void rr_renderer_draw_web(struct rr_renderer *renderer)
{
    render_sprite_from_cache(renderer, &background_tiles,
                             2 * TILES_SIZE + PROP_SIZE);
}

void rr_renderer_tiles_init()
{
    rr_renderer_spritesheet_init(
        &background_tiles, NULL, 256, 256, rr_hc_tile_1_draw, 256, 256,
        rr_hc_tile_2_draw, 256, 256, rr_hc_tile_3_draw, 256, 256,
        rr_ga_tile_1_draw, 256, 256, rr_ga_tile_2_draw, 256, 256,
        rr_ga_tile_3_draw, 800, 800, rr_prop_fern_draw, 800, 800,
        rr_prop_moss_draw, 250, 250, asset_web_draw, 0);
}
