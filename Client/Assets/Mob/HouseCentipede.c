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

void rr_house_centipede_head_draw(struct rr_renderer *renderer)
{
    rr_renderer_set_fill(renderer, 0xff85734a);
    rr_renderer_begin_path(renderer);
    rr_renderer_move_to(renderer, -58.70, -25.20);
    rr_renderer_bezier_curve_to(renderer, -44.77, -25.20, -33.48, -13.91,
                                -33.48, 0.02);
    rr_renderer_bezier_curve_to(renderer, -33.48, 6.71, -36.13, 13.13, -40.86,
                                17.86);
    rr_renderer_bezier_curve_to(renderer, -45.59, 22.59, -52.01, 25.25, -58.70,
                                25.25);
    rr_renderer_bezier_curve_to(renderer, -72.63, 25.25, -83.92, 13.95, -83.92,
                                0.02);
    rr_renderer_bezier_curve_to(renderer, -83.92, -13.91, -72.63, -25.20,
                                -58.70, -25.20);
    rr_renderer_fill(renderer);
    rr_renderer_set_fill(renderer, 0xff9d8756);
    rr_renderer_begin_path(renderer);
    rr_renderer_move_to(renderer, -58.70, -17.97);
    rr_renderer_bezier_curve_to(renderer, -48.76, -17.97, -40.70, -9.92, -40.70,
                                0.02);
    rr_renderer_bezier_curve_to(renderer, -40.70, 4.79, -42.60, 9.37, -45.97,
                                12.75);
    rr_renderer_bezier_curve_to(renderer, -49.35, 16.12, -53.92, 18.02, -58.70,
                                18.02);
    rr_renderer_bezier_curve_to(renderer, -68.63, 18.02, -76.69, 9.96, -76.69,
                                0.02);
    rr_renderer_bezier_curve_to(renderer, -76.69, -9.92, -68.63, -17.97, -58.70,
                                -17.97);
    rr_renderer_fill(renderer);
    rr_renderer_set_fill(renderer, 0xff695a3a);
    rr_renderer_begin_path(renderer);
    rr_renderer_move_to(renderer, 75.41, -84.79);
    rr_renderer_bezier_curve_to(renderer, 57.12, -31.80, 5.01, 1.84, -50.81,
                                -3.29);
    rr_renderer_line_to(renderer, -49.92, -12.94);
    rr_renderer_bezier_curve_to(renderer, 1.45, -8.22, 49.41, -39.18, 66.25,
                                -87.95);
    rr_renderer_fill(renderer);
    rr_renderer_set_fill(renderer, 0xff695a3a);
    rr_renderer_begin_path(renderer);
    rr_renderer_move_to(renderer, -51.04, -12.84);
    rr_renderer_bezier_curve_to(renderer, -48.52, -13.53, -45.91, -12.04,
                                -45.22, -9.52);
    rr_renderer_bezier_curve_to(renderer, -44.89, -8.31, -45.05, -7.02, -45.68,
                                -5.93);
    rr_renderer_bezier_curve_to(renderer, -46.30, -4.84, -47.33, -4.04, -48.54,
                                -3.71);
    rr_renderer_bezier_curve_to(renderer, -51.06, -3.01, -53.66, -4.50, -54.36,
                                -7.02);
    rr_renderer_bezier_curve_to(renderer, -55.05, -9.54, -53.56, -12.15, -51.04,
                                -12.84);
    rr_renderer_fill(renderer);
    rr_renderer_set_fill(renderer, 0xff695a3a);
    rr_renderer_begin_path(renderer);
    rr_renderer_move_to(renderer, 64.10, -116.56);
    rr_renderer_bezier_curve_to(renderer, 56.51, -120.26, 47.38, -118.33, 41.94,
                                -111.87);
    rr_renderer_line_to(renderer, 48.98, -105.94);
    rr_renderer_bezier_curve_to(renderer, 51.70, -109.17, 56.27, -110.13, 60.07,
                                -108.28);
    rr_renderer_fill(renderer);
    rr_renderer_set_fill(renderer, 0xff695a3a);
    rr_renderer_begin_path(renderer);
    rr_renderer_move_to(renderer, 41.94, -111.87);
    rr_renderer_bezier_curve_to(renderer, 36.79, -105.76, 36.92, -96.80, 42.24,
                                -90.85);
    rr_renderer_line_to(renderer, 49.14, -97.01);
    rr_renderer_bezier_curve_to(renderer, 46.89, -99.53, 46.84, -103.33, 49.01,
                                -105.91);
    rr_renderer_fill(renderer);
    rr_renderer_set_fill(renderer, 0xff695a3a);
    rr_renderer_begin_path(renderer);
    rr_renderer_move_to(renderer, 76.17, -100.96);
    rr_renderer_bezier_curve_to(renderer, 74.69, -107.74, 70.22, -113.50, 64.01,
                                -116.62);
    rr_renderer_line_to(renderer, 59.87, -108.34);
    rr_renderer_bezier_curve_to(renderer, 63.58, -106.48, 66.24, -103.04, 67.13,
                                -98.99);
    rr_renderer_fill(renderer);
    rr_renderer_set_fill(renderer, 0xff695a3a);
    rr_renderer_begin_path(renderer);
    rr_renderer_move_to(renderer, 73.26, -79.57);
    rr_renderer_bezier_curve_to(renderer, 76.62, -86.28, 77.60, -93.93, 76.04,
                                -101.27);
    rr_renderer_line_to(renderer, 66.99, -99.34);
    rr_renderer_bezier_curve_to(renderer, 68.12, -94.06, 67.42, -88.55, 64.99,
                                -83.72);
    rr_renderer_fill(renderer);
    rr_renderer_set_fill(renderer, 0xff695a3a);
    rr_renderer_begin_path(renderer);
    rr_renderer_move_to(renderer, 49.34, -90.87);
    rr_renderer_bezier_curve_to(renderer, 50.97, -92.81, 50.72, -95.70, 48.79,
                                -97.33);
    rr_renderer_bezier_curve_to(renderer, 47.86, -98.11, 46.65, -98.50, 45.44,
                                -98.39);
    rr_renderer_bezier_curve_to(renderer, 44.23, -98.29, 43.11, -97.71, 42.33,
                                -96.78);
    rr_renderer_bezier_curve_to(renderer, 40.70, -94.84, 40.95, -91.95, 42.88,
                                -90.32);
    rr_renderer_bezier_curve_to(renderer, 44.82, -88.69, 47.71, -88.94, 49.34,
                                -90.87);
    rr_renderer_fill(renderer);
    rr_renderer_set_fill(renderer, 0xff695a3a);
    rr_renderer_begin_path(renderer);
    rr_renderer_move_to(renderer, 75.41, 84.78);
    rr_renderer_bezier_curve_to(renderer, 57.12, 31.80, 5.01, -1.85, -50.81,
                                3.29);
    rr_renderer_line_to(renderer, -49.92, 12.94);
    rr_renderer_bezier_curve_to(renderer, 1.45, 8.21, 49.41, 39.18, 66.25,
                                87.95);
    rr_renderer_fill(renderer);
    rr_renderer_set_fill(renderer, 0xff695a3a);
    rr_renderer_begin_path(renderer);
    rr_renderer_move_to(renderer, -51.04, 12.83);
    rr_renderer_bezier_curve_to(renderer, -48.52, 13.53, -45.92, 12.04, -45.22,
                                9.52);
    rr_renderer_bezier_curve_to(renderer, -44.89, 8.31, -45.05, 7.02, -45.68,
                                5.92);
    rr_renderer_bezier_curve_to(renderer, -46.30, 4.83, -47.33, 4.03, -48.54,
                                3.70);
    rr_renderer_bezier_curve_to(renderer, -51.06, 3.01, -53.67, 4.50, -54.36,
                                7.02);
    rr_renderer_bezier_curve_to(renderer, -55.05, 9.54, -53.56, 12.14, -51.04,
                                12.83);
    rr_renderer_fill(renderer);
    rr_renderer_set_fill(renderer, 0xff695a3a);
    rr_renderer_begin_path(renderer);
    rr_renderer_move_to(renderer, 64.10, 116.56);
    rr_renderer_bezier_curve_to(renderer, 56.51, 120.26, 47.38, 118.33, 41.94,
                                111.87);
    rr_renderer_line_to(renderer, 48.98, 105.93);
    rr_renderer_bezier_curve_to(renderer, 51.70, 109.16, 56.27, 110.13, 60.06,
                                108.28);
    rr_renderer_fill(renderer);
    rr_renderer_set_fill(renderer, 0xff695a3a);
    rr_renderer_begin_path(renderer);
    rr_renderer_move_to(renderer, 41.94, 111.87);
    rr_renderer_bezier_curve_to(renderer, 36.79, 105.76, 36.92, 96.80, 42.24,
                                90.85);
    rr_renderer_line_to(renderer, 49.14, 97.01);
    rr_renderer_bezier_curve_to(renderer, 46.89, 99.53, 46.83, 103.32, 49.01,
                                105.91);
    rr_renderer_fill(renderer);
    rr_renderer_set_fill(renderer, 0xff695a3a);
    rr_renderer_begin_path(renderer);
    rr_renderer_move_to(renderer, 76.17, 100.95);
    rr_renderer_bezier_curve_to(renderer, 74.69, 107.74, 70.22, 113.50, 64.01,
                                116.61);
    rr_renderer_line_to(renderer, 59.87, 108.34);
    rr_renderer_bezier_curve_to(renderer, 63.57, 106.48, 66.24, 103.04, 67.12,
                                98.99);
    rr_renderer_fill(renderer);
    rr_renderer_set_fill(renderer, 0xff695a3a);
    rr_renderer_begin_path(renderer);
    rr_renderer_move_to(renderer, 73.26, 79.57);
    rr_renderer_bezier_curve_to(renderer, 76.62, 86.28, 77.60, 93.93, 76.04,
                                101.27);
    rr_renderer_line_to(renderer, 66.99, 99.34);
    rr_renderer_bezier_curve_to(renderer, 68.12, 94.05, 67.42, 88.55, 64.99,
                                83.72);
    rr_renderer_fill(renderer);
    rr_renderer_set_fill(renderer, 0xff695a3a);
    rr_renderer_begin_path(renderer);
    rr_renderer_move_to(renderer, 49.34, 90.87);
    rr_renderer_bezier_curve_to(renderer, 50.97, 92.81, 50.72, 95.70, 48.78,
                                97.33);
    rr_renderer_bezier_curve_to(renderer, 47.85, 98.11, 46.65, 98.49, 45.44,
                                98.39);
    rr_renderer_bezier_curve_to(renderer, 44.23, 98.29, 43.11, 97.70, 42.33,
                                96.78);
    rr_renderer_bezier_curve_to(renderer, 40.70, 94.84, 40.95, 91.95, 42.88,
                                90.32);
    rr_renderer_bezier_curve_to(renderer, 44.82, 88.69, 47.71, 88.94, 49.34,
                                90.87);
    rr_renderer_fill(renderer);
}

void rr_house_centipede_body_draw(struct rr_renderer *renderer)
{
    rr_renderer_set_fill(renderer, 0xff85734a);
    rr_renderer_begin_path(renderer);
    rr_renderer_move_to(renderer, -26.23, 0.00);
    rr_renderer_bezier_curve_to(renderer, -26.23, -14.49, -14.49, -26.23, -0.00,
                                -26.23);
    rr_renderer_bezier_curve_to(renderer, 6.96, -26.23, 13.63, -23.47, 18.55,
                                -18.55);
    rr_renderer_bezier_curve_to(renderer, 23.47, -13.63, 26.23, -6.96, 26.23,
                                0.00);
    rr_renderer_bezier_curve_to(renderer, 26.23, 14.49, 14.49, 26.23, -0.00,
                                26.23);
    rr_renderer_bezier_curve_to(renderer, -14.49, 26.23, -26.23, 14.49, -26.23,
                                0.00);
    rr_renderer_fill(renderer);
    rr_renderer_set_fill(renderer, 0xff9d8756);
    rr_renderer_begin_path(renderer);
    rr_renderer_move_to(renderer, -18.72, -0.00);
    rr_renderer_bezier_curve_to(renderer, -18.72, -10.34, -10.34, -18.72, -0.00,
                                -18.72);
    rr_renderer_bezier_curve_to(renderer, 4.96, -18.72, 9.72, -16.75, 13.23,
                                -13.24);
    rr_renderer_bezier_curve_to(renderer, 16.74, -9.73, 18.72, -4.97, 18.72,
                                -0.00);
    rr_renderer_bezier_curve_to(renderer, 18.72, 10.33, 10.34, 18.71, -0.00,
                                18.71);
    rr_renderer_bezier_curve_to(renderer, -10.34, 18.71, -18.72, 10.33, -18.72,
                                -0.00);
    rr_renderer_fill(renderer);
}

void rr_house_centipede_leg_draw(struct rr_renderer *renderer)
{
    rr_renderer_set_fill(renderer, 0xff695a3a);
    rr_renderer_begin_path(renderer);
    rr_renderer_move_to(renderer, -4.70, 8.52);
    rr_renderer_bezier_curve_to(renderer, -5.63, 5.54, -3.97, 2.36, -0.99,
                                1.43);
    rr_renderer_line_to(renderer, 42.70, -12.23);
    rr_renderer_bezier_curve_to(renderer, 44.13, -12.68, 45.68, -12.54, 47.01,
                                -11.85);
    rr_renderer_bezier_curve_to(renderer, 48.34, -11.15, 49.34, -9.95, 49.79,
                                -8.52);
    rr_renderer_bezier_curve_to(renderer, 50.72, -5.54, 49.05, -2.36, 46.07,
                                -1.43);
    rr_renderer_line_to(renderer, 2.38, 12.23);
    rr_renderer_bezier_curve_to(renderer, -0.60, 13.16, -3.77, 11.50, -4.70,
                                8.52);
    rr_renderer_fill(renderer);
    rr_renderer_set_fill(renderer, 0xff695a3a);
    rr_renderer_begin_path(renderer);
    rr_renderer_move_to(renderer, -49.96, -6.89);
    rr_renderer_bezier_curve_to(renderer, -49.13, -9.90, -46.02, -11.66, -43.01,
                                -10.83);
    rr_renderer_line_to(renderer, 1.15, 1.35);
    rr_renderer_bezier_curve_to(renderer, 2.59, 1.75, 3.82, 2.71, 4.56, 4.01);
    rr_renderer_bezier_curve_to(renderer, 5.29, 5.31, 5.48, 6.86, 5.08, 8.30);
    rr_renderer_bezier_curve_to(renderer, 4.25, 11.31, 1.14, 13.07, -1.87,
                                12.24);
    rr_renderer_line_to(renderer, -46.02, 0.06);
    rr_renderer_bezier_curve_to(renderer, -49.03, -0.77, -50.80, -3.88, -49.96,
                                -6.89);
    rr_renderer_fill(renderer);
    rr_renderer_set_fill(renderer, 0xff9d8756);
    rr_renderer_begin_path(renderer);
    rr_renderer_move_to(renderer, -37.34, -9.32);
    rr_renderer_line_to(renderer, -26.40, -6.28);
    rr_renderer_line_to(renderer, -29.43, 4.66);
    rr_renderer_line_to(renderer, -40.38, 1.63);
    rr_renderer_fill(renderer);
    rr_renderer_set_fill(renderer, 0xff9d8756);
    rr_renderer_begin_path(renderer);
    rr_renderer_move_to(renderer, -15.45, -3.25);
    rr_renderer_line_to(renderer, -4.50, -0.22);
    rr_renderer_line_to(renderer, -7.54, 10.73);
    rr_renderer_line_to(renderer, -18.48, 7.69);
    rr_renderer_fill(renderer);
}