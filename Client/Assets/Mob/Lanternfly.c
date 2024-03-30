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

#include <Client/Assets/Render.h>

#include <Client/Renderer/Renderer.h>

void rr_lanternfly_wing1_draw(struct rr_renderer *renderer)
{
    rr_renderer_set_fill(renderer, 0xff8d7968);
    rr_renderer_begin_path(renderer);
    rr_renderer_move_to(renderer, -109.14, -0.51);
    rr_renderer_bezier_curve_to(renderer, -109.42, 24.86, -88.78, 48.39, -55.02,
                                61.18);
    rr_renderer_bezier_curve_to(renderer, -21.27, 73.97, 20.45, 74.07, 54.34,
                                61.44);
    rr_renderer_bezier_curve_to(renderer, 88.24, 48.80, 109.14, 25.37, 109.14,
                                0.00);
    rr_renderer_fill(renderer);
    rr_renderer_set_fill(renderer, 0xff8d7968);
    rr_renderer_begin_path(renderer);
    rr_renderer_move_to(renderer, 91.56, 15.10);
    rr_renderer_bezier_curve_to(renderer, 101.27, 15.10, 109.14, 7.23, 109.14,
                                -2.48);
    rr_renderer_bezier_curve_to(renderer, 109.14, -7.15, 107.28, -11.62, 103.99,
                                -14.92);
    rr_renderer_bezier_curve_to(renderer, 100.69, -18.22, 96.22, -20.07, 91.56,
                                -20.07);
    rr_renderer_bezier_curve_to(renderer, 81.85, -20.07, 73.98, -12.20, 73.98,
                                -2.48);
    rr_renderer_bezier_curve_to(renderer, 73.98, 7.23, 81.85, 15.10, 91.56,
                                15.10);
    rr_renderer_fill(renderer);
    rr_renderer_set_fill(renderer, 0xff8d7968);
    rr_renderer_begin_path(renderer);
    rr_renderer_move_to(renderer, -91.55, 15.10);
    rr_renderer_bezier_curve_to(renderer, -81.84, 15.10, -73.97, 7.23, -73.97,
                                -2.48);
    rr_renderer_bezier_curve_to(renderer, -73.97, -7.15, -75.82, -11.62, -79.12,
                                -14.92);
    rr_renderer_bezier_curve_to(renderer, -82.42, -18.22, -86.89, -20.07,
                                -91.55, -20.07);
    rr_renderer_bezier_curve_to(renderer, -101.26, -20.07, -109.13, -12.20,
                                -109.13, -2.48);
    rr_renderer_bezier_curve_to(renderer, -109.13, 7.23, -101.26, 15.10, -91.55,
                                15.10);
    rr_renderer_fill(renderer);
    rr_renderer_set_fill(renderer, 0xff8d7968);
    rr_renderer_begin_path(renderer);
    rr_renderer_move_to(renderer, 91.70, -2.49);
    rr_renderer_line_to(renderer, 91.70, -20.07);
    rr_renderer_line_to(renderer, -91.69, -20.07);
    rr_renderer_line_to(renderer, -91.69, -2.49);
    rr_renderer_fill(renderer);
    rr_renderer_set_fill(renderer, 0xffa38c78);
    rr_renderer_begin_path(renderer);
    rr_renderer_move_to(renderer, -91.99, -2.92);
    rr_renderer_bezier_curve_to(renderer, -92.24, 17.61, -74.90, 36.65, -46.54,
                                47.00);
    rr_renderer_bezier_curve_to(renderer, -18.19, 57.35, 16.87, 57.43, 45.35,
                                47.21);
    rr_renderer_bezier_curve_to(renderer, 73.83, 36.99, 91.39, 18.04, 91.39,
                                -2.49);
    rr_renderer_fill(renderer);
    rr_renderer_set_fill(renderer, 0xff34393a);
    rr_renderer_begin_path(renderer);
    rr_renderer_move_to(renderer, 10.97, 26.29);
    rr_renderer_bezier_curve_to(renderer, 3.95, 26.29, -1.73, 20.60, -1.73,
                                13.58);
    rr_renderer_bezier_curve_to(renderer, -1.73, 10.21, -0.40, 6.98, 1.99,
                                4.60);
    rr_renderer_bezier_curve_to(renderer, 4.37, 2.21, 7.60, 0.87, 10.97, 0.87);
    rr_renderer_bezier_curve_to(renderer, 17.99, 0.87, 23.67, 6.56, 23.67,
                                13.58);
    rr_renderer_bezier_curve_to(renderer, 23.67, 20.60, 17.99, 26.29, 10.97,
                                26.29);
    rr_renderer_fill(renderer);
    rr_renderer_set_fill(renderer, 0xff34393a);
    rr_renderer_begin_path(renderer);
    rr_renderer_move_to(renderer, -12.09, 51.70);
    rr_renderer_bezier_curve_to(renderer, -19.11, 51.70, -24.80, 46.01, -24.80,
                                38.99);
    rr_renderer_bezier_curve_to(renderer, -24.80, 35.62, -23.46, 32.39, -21.08,
                                30.01);
    rr_renderer_bezier_curve_to(renderer, -18.69, 27.62, -15.46, 26.29, -12.09,
                                26.29);
    rr_renderer_bezier_curve_to(renderer, -5.08, 26.29, 0.61, 31.97, 0.61,
                                38.99);
    rr_renderer_bezier_curve_to(renderer, 0.61, 46.01, -5.08, 51.70, -12.09,
                                51.70);
    rr_renderer_fill(renderer);
    rr_renderer_set_fill(renderer, 0xff34393a);
    rr_renderer_begin_path(renderer);
    rr_renderer_move_to(renderer, -50.61, 37.61);
    rr_renderer_bezier_curve_to(renderer, -57.63, 37.61, -63.32, 31.92, -63.32,
                                24.90);
    rr_renderer_bezier_curve_to(renderer, -63.32, 21.53, -61.98, 18.30, -59.59,
                                15.92);
    rr_renderer_bezier_curve_to(renderer, -57.21, 13.54, -53.98, 12.20, -50.61,
                                12.20);
    rr_renderer_bezier_curve_to(renderer, -43.60, 12.20, -37.91, 17.89, -37.91,
                                24.90);
    rr_renderer_bezier_curve_to(renderer, -37.91, 31.92, -43.60, 37.61, -50.61,
                                37.61);
    rr_renderer_fill(renderer);
}

void rr_lanternfly_abdomen_draw(struct rr_renderer *renderer)
{
    rr_renderer_set_fill(renderer, 0xffa42312);
    rr_renderer_begin_path(renderer);
    rr_renderer_move_to(renderer, -0.00, 68.72);
    rr_renderer_bezier_curve_to(renderer, -50.94, 68.72, -92.23, 37.95, -92.23,
                                -0.00);
    rr_renderer_bezier_curve_to(renderer, -92.23, -18.23, -82.52, -35.70,
                                -65.22, -48.59);
    rr_renderer_bezier_curve_to(renderer, -47.92, -61.48, -24.46, -68.72, -0.00,
                                -68.72);
    rr_renderer_bezier_curve_to(renderer, 50.94, -68.72, 92.23, -37.95, 92.23,
                                -0.00);
    rr_renderer_bezier_curve_to(renderer, 92.23, 37.95, 50.94, 68.72, -0.00,
                                68.72);
    rr_renderer_fill(renderer);
    rr_renderer_set_fill(renderer, 0xffc23523);
    rr_renderer_begin_path(renderer);
    rr_renderer_move_to(renderer, -0.00, 50.06);
    rr_renderer_bezier_curve_to(renderer, -39.38, 50.06, -71.31, 27.64, -71.31,
                                -0.00);
    rr_renderer_bezier_curve_to(renderer, -71.31, -13.28, -63.80, -26.01,
                                -50.42, -35.40);
    rr_renderer_bezier_curve_to(renderer, -37.05, -44.78, -18.91, -50.06, -0.00,
                                -50.06);
    rr_renderer_bezier_curve_to(renderer, 39.38, -50.06, 71.31, -27.65, 71.31,
                                -0.00);
    rr_renderer_bezier_curve_to(renderer, 71.31, 27.64, 39.38, 50.06, -0.00,
                                50.06);
    rr_renderer_fill(renderer);
}

void rr_lanternfly_leg_draw(struct rr_renderer *renderer)
{
    rr_renderer_set_fill(renderer, 0xff0e1113);
    rr_renderer_begin_path(renderer);
    rr_renderer_move_to(renderer, -20.52, 48.13);
    rr_renderer_bezier_curve_to(renderer, 7.17, 28.26, 22.17, -4.86, 18.81,
                                -38.78);
    rr_renderer_line_to(renderer, -3.36, -36.59);
    rr_renderer_bezier_curve_to(renderer, -0.79, -10.59, -12.28, 14.80, -33.51,
                                30.02);
    rr_renderer_fill(renderer);
    rr_renderer_set_fill(renderer, 0xff0e1113);
    rr_renderer_begin_path(renderer);
    rr_renderer_move_to(renderer, -29.81, 27.97);
    rr_renderer_bezier_curve_to(renderer, -35.54, 29.99, -38.55, 36.28, -36.52,
                                42.01);
    rr_renderer_bezier_curve_to(renderer, -35.55, 44.76, -33.53, 47.01, -30.89,
                                48.27);
    rr_renderer_bezier_curve_to(renderer, -28.26, 49.53, -25.24, 49.69, -22.49,
                                48.72);
    rr_renderer_bezier_curve_to(renderer, -16.76, 46.69, -13.75, 40.41, -15.78,
                                34.68);
    rr_renderer_bezier_curve_to(renderer, -17.80, 28.95, -24.08, 25.95, -29.81,
                                27.97);
    rr_renderer_fill(renderer);
}