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

void rr_dragonfly_head_draw(struct rr_renderer *renderer)
{
    rr_renderer_set_fill(renderer, 0xff0c3d52);
    rr_renderer_begin_path(renderer);
    rr_renderer_move_to(renderer, 14.29, 37.18);
    rr_renderer_bezier_curve_to(renderer, 18.51, 39.90, 34.64, 28.26, 41.29,
                                22.94);
    rr_renderer_bezier_curve_to(renderer, 47.95, 17.63, 53.41, 9.09, 54.21,
                                5.27);
    rr_renderer_bezier_curve_to(renderer, 55.01, 1.46, 52.45, -0.17, 46.08,
                                0.06);
    rr_renderer_bezier_curve_to(renderer, 39.71, 0.29, 21.29, 0.46, 16.00,
                                6.65);
    rr_renderer_bezier_curve_to(renderer, 10.70, 12.83, 10.08, 34.46, 14.29,
                                37.18);
    rr_renderer_fill(renderer);
    rr_renderer_set_fill(renderer, 0xff0c3d52);
    rr_renderer_begin_path(renderer);
    rr_renderer_move_to(renderer, 14.29, -37.16);
    rr_renderer_bezier_curve_to(renderer, 18.51, -39.88, 34.64, -28.24, 41.29,
                                -22.93);
    rr_renderer_bezier_curve_to(renderer, 47.95, -17.61, 53.41, -9.07, 54.21,
                                -5.25);
    rr_renderer_bezier_curve_to(renderer, 55.01, -1.44, 52.45, 0.19, 46.08,
                                -0.04);
    rr_renderer_bezier_curve_to(renderer, 39.71, -0.27, 21.29, -0.44, 16.00,
                                -6.63);
    rr_renderer_bezier_curve_to(renderer, 10.70, -12.81, 10.08, -34.44, 14.29,
                                -37.16);
    rr_renderer_fill(renderer);
    rr_renderer_set_fill(renderer, 0xff175f7f);
    rr_renderer_begin_path(renderer);
    rr_renderer_move_to(renderer, 13.78, -36.11);
    rr_renderer_bezier_curve_to(renderer, 31.98, -36.11, 46.73, -19.94, 46.73,
                                -0.00);
    rr_renderer_bezier_curve_to(renderer, 46.73, 19.94, 31.98, 36.11, 13.78,
                                36.11);
    rr_renderer_bezier_curve_to(renderer, -4.42, 36.11, -19.18, 19.94, -19.18,
                                -0.00);
    rr_renderer_bezier_curve_to(renderer, -19.18, -19.94, -4.42, -36.11, 13.78,
                                -36.11);
    rr_renderer_fill(renderer);
    rr_renderer_set_fill(renderer, 0xff1e79a1);
    rr_renderer_begin_path(renderer);
    rr_renderer_move_to(renderer, -6.50, -42.27);
    rr_renderer_bezier_curve_to(renderer, 16.78, -42.27, 35.66, -23.40, 35.66,
                                -0.11);
    rr_renderer_bezier_curve_to(renderer, 35.66, 11.07, 31.21, 21.79, 23.31,
                                29.70);
    rr_renderer_bezier_curve_to(renderer, 15.40, 37.60, 4.68, 42.04, -6.50,
                                42.04);
    rr_renderer_bezier_curve_to(renderer, -29.79, 42.04, -48.66, 23.17, -48.66,
                                -0.11);
    rr_renderer_bezier_curve_to(renderer, -48.66, -23.40, -29.79, -42.27, -6.50,
                                -42.27);
    rr_renderer_fill(renderer);
    rr_renderer_set_fill(renderer, 0xff175f7f);
    rr_renderer_begin_path(renderer);
    rr_renderer_move_to(renderer, -6.51, -47.95);
    rr_renderer_bezier_curve_to(renderer, 19.92, -47.95, 41.34, -26.53, 41.34,
                                -0.11);
    rr_renderer_bezier_curve_to(renderer, 41.34, 12.58, 36.30, 24.75, 27.32,
                                33.72);
    rr_renderer_bezier_curve_to(renderer, 18.35, 42.69, 6.18, 47.73, -6.51,
                                47.73);
    rr_renderer_bezier_curve_to(renderer, -32.93, 47.73, -54.35, 26.31, -54.35,
                                -0.11);
    rr_renderer_bezier_curve_to(renderer, -54.35, -26.53, -32.93, -47.95, -6.51,
                                -47.95);
    rr_renderer_move_to(renderer, -6.51, -35.96);
    rr_renderer_bezier_curve_to(renderer, -26.31, -35.96, -42.36, -19.91,
                                -42.36, -0.11);
    rr_renderer_bezier_curve_to(renderer, -42.36, 19.69, -26.31, 35.74, -6.51,
                                35.74);
    rr_renderer_bezier_curve_to(renderer, 13.29, 35.74, 29.35, 19.69, 29.35,
                                -0.11);
    rr_renderer_bezier_curve_to(renderer, 29.35, -19.91, 13.29, -35.96, -6.51,
                                -35.96);
    rr_renderer_fill(renderer);
    rr_renderer_set_fill(renderer, 0xff1e79a1);
    rr_renderer_begin_path(renderer);
    rr_renderer_move_to(renderer, 13.78, -24.87);
    rr_renderer_bezier_curve_to(renderer, 25.60, -24.87, 35.19, -13.73, 35.19,
                                -0.00);
    rr_renderer_bezier_curve_to(renderer, 35.19, 13.73, 25.60, 24.87, 13.78,
                                24.87);
    rr_renderer_bezier_curve_to(renderer, 1.95, 24.87, -7.63, 13.73, -7.63,
                                -0.00);
    rr_renderer_bezier_curve_to(renderer, -7.63, -13.73, 1.95, -24.87, 13.78,
                                -24.87);
    rr_renderer_fill(renderer);
    rr_renderer_set_fill(renderer, 0xff175f7f);
    rr_renderer_begin_path(renderer);
    rr_renderer_move_to(renderer, -5.79, -6.42);
    rr_renderer_bezier_curve_to(renderer, -2.24, -6.42, 0.63, -3.54, 0.63,
                                0.00);
    rr_renderer_bezier_curve_to(renderer, 0.63, 1.70, -0.05, 3.33, -1.25, 4.54);
    rr_renderer_bezier_curve_to(renderer, -2.45, 5.74, -4.08, 6.42, -5.79,
                                6.42);
    rr_renderer_bezier_curve_to(renderer, -9.33, 6.42, -12.20, 3.54, -12.20,
                                0.00);
    rr_renderer_bezier_curve_to(renderer, -12.20, -3.54, -9.33, -6.42, -5.79,
                                -6.42);
    rr_renderer_fill(renderer);
    rr_renderer_set_fill(renderer, 0xff175f7f);
    rr_renderer_begin_path(renderer);
    rr_renderer_move_to(renderer, 18.87, -5.61);
    rr_renderer_bezier_curve_to(renderer, 12.80, 2.17, 3.40, 6.63, -6.47, 6.41);
    rr_renderer_line_to(renderer, -6.19, -6.43);
    rr_renderer_bezier_curve_to(renderer, -0.37, -6.30, 5.17, -8.93, 8.75,
                                -13.52);
    rr_renderer_fill(renderer);
    rr_renderer_set_fill(renderer, 0xff175f7f);
    rr_renderer_begin_path(renderer);
    rr_renderer_move_to(renderer, 13.63, -15.71);
    rr_renderer_bezier_curve_to(renderer, 17.18, -15.71, 20.05, -12.84, 20.05,
                                -9.29);
    rr_renderer_bezier_curve_to(renderer, 20.05, -7.59, 19.38, -5.96, 18.17,
                                -4.75);
    rr_renderer_bezier_curve_to(renderer, 16.97, -3.55, 15.34, -2.87, 13.63,
                                -2.87);
    rr_renderer_bezier_curve_to(renderer, 10.09, -2.87, 7.22, -5.75, 7.22,
                                -9.29);
    rr_renderer_bezier_curve_to(renderer, 7.22, -12.84, 10.09, -15.71, 13.63,
                                -15.71);
    rr_renderer_fill(renderer);
    rr_renderer_set_fill(renderer, 0xff175f7f);
    rr_renderer_begin_path(renderer);
    rr_renderer_move_to(renderer, 18.88, 5.62);
    rr_renderer_bezier_curve_to(renderer, 12.80, -2.17, 3.40, -6.62, -6.47,
                                -6.41);
    rr_renderer_line_to(renderer, -6.19, 6.43);
    rr_renderer_bezier_curve_to(renderer, -0.37, 6.30, 5.17, 8.93, 8.75, 13.52);
    rr_renderer_fill(renderer);
    rr_renderer_set_fill(renderer, 0xff175f7f);
    rr_renderer_begin_path(renderer);
    rr_renderer_move_to(renderer, 13.64, 15.71);
    rr_renderer_bezier_curve_to(renderer, 17.18, 15.71, 20.05, 12.84, 20.05,
                                9.29);
    rr_renderer_bezier_curve_to(renderer, 20.05, 7.59, 19.38, 5.96, 18.17,
                                4.75);
    rr_renderer_bezier_curve_to(renderer, 16.97, 3.55, 15.34, 2.87, 13.64,
                                2.87);
    rr_renderer_bezier_curve_to(renderer, 10.09, 2.87, 7.22, 5.75, 7.22, 9.29);
    rr_renderer_bezier_curve_to(renderer, 7.22, 12.84, 10.09, 15.71, 13.64,
                                15.71);
    rr_renderer_fill(renderer);
}

void rr_dragonfly_thorax_draw(struct rr_renderer *renderer)
{
    rr_renderer_set_fill(renderer, 0xff1e79a1);
    rr_renderer_begin_path(renderer);
    rr_renderer_move_to(renderer, 0.00, -43.74);
    rr_renderer_bezier_curve_to(renderer, 30.04, -43.74, 54.39, -24.16, 54.39,
                                0.00);
    rr_renderer_bezier_curve_to(renderer, 54.39, 11.60, 48.66, 22.73, 38.46,
                                30.94);
    rr_renderer_bezier_curve_to(renderer, 28.26, 39.14, 14.43, 43.75, 0.00,
                                43.75);
    rr_renderer_bezier_curve_to(renderer, -30.04, 43.75, -54.39, 24.16, -54.39,
                                0.00);
    rr_renderer_bezier_curve_to(renderer, -54.39, -24.16, -30.04, -43.74, 0.00,
                                -43.74);
    rr_renderer_fill(renderer);
    rr_renderer_set_fill(renderer, 0xff175f7f);
    rr_renderer_begin_path(renderer);
    rr_renderer_move_to(renderer, 0.00, -49.64);
    rr_renderer_bezier_curve_to(renderer, 34.09, -49.64, 61.72, -27.42, 61.72,
                                0.00);
    rr_renderer_bezier_curve_to(renderer, 61.72, 13.17, 55.22, 25.79, 43.64,
                                35.10);
    rr_renderer_bezier_curve_to(renderer, 32.07, 44.41, 16.37, 49.64, 0.00,
                                49.64);
    rr_renderer_bezier_curve_to(renderer, -34.09, 49.64, -61.72, 27.42, -61.72,
                                0.00);
    rr_renderer_bezier_curve_to(renderer, -61.72, -27.42, -34.09, -49.64, 0.00,
                                -49.64);
    rr_renderer_move_to(renderer, 0.00, -37.20);
    rr_renderer_bezier_curve_to(renderer, -27.22, -37.20, -49.28, -20.54,
                                -49.28, 0.00);
    rr_renderer_bezier_curve_to(renderer, -49.28, 20.54, -27.22, 37.20, 0.00,
                                37.20);
    rr_renderer_bezier_curve_to(renderer, 27.22, 37.20, 49.28, 20.54, 49.28,
                                0.00);
    rr_renderer_bezier_curve_to(renderer, 49.28, -20.54, 27.22, -37.20, 0.00,
                                -37.20);
    rr_renderer_fill(renderer);
}

void rr_dragonfly_abdomen_draw(struct rr_renderer *renderer)
{
    rr_renderer_set_fill(renderer, 0xff175f7f);
    rr_renderer_begin_path(renderer);
    rr_renderer_move_to(renderer, 57.10, -36.55);
    rr_renderer_bezier_curve_to(renderer, 77.29, -36.55, 93.65, -20.18, 93.65,
                                0.00);
    rr_renderer_bezier_curve_to(renderer, 93.65, 9.69, 89.80, 18.99, 82.94,
                                25.84);
    rr_renderer_bezier_curve_to(renderer, 76.09, 32.70, 66.79, 36.55, 57.10,
                                36.55);
    rr_renderer_line_to(renderer, -57.10, 36.55);
    rr_renderer_bezier_curve_to(renderer, -77.29, 36.55, -93.65, 20.18, -93.65,
                                0.00);
    rr_renderer_bezier_curve_to(renderer, -93.65, -20.18, -77.29, -36.55,
                                -57.10, -36.55);
    rr_renderer_fill(renderer);
    rr_renderer_set_fill(renderer, 0xff1e79a1);
    rr_renderer_begin_path(renderer);
    rr_renderer_move_to(renderer, 24.05, -27.18);
    rr_renderer_bezier_curve_to(renderer, 39.06, -27.18, 51.23, -15.01, 51.23,
                                0.00);
    rr_renderer_bezier_curve_to(renderer, 51.23, 7.21, 48.37, 14.12, 43.27,
                                19.22);
    rr_renderer_bezier_curve_to(renderer, 38.17, 24.32, 31.26, 27.18, 24.05,
                                27.18);
    rr_renderer_line_to(renderer, -56.96, 27.18);
    rr_renderer_bezier_curve_to(renderer, -71.97, 27.18, -84.13, 15.01, -84.13,
                                0.00);
    rr_renderer_bezier_curve_to(renderer, -84.13, -15.01, -71.97, -27.18,
                                -56.96, -27.18);
    rr_renderer_fill(renderer);
    rr_renderer_set_fill(renderer, 0xff175f7f);
    rr_renderer_begin_path(renderer);
    rr_renderer_move_to(renderer, -34.62, -27.18);
    rr_renderer_bezier_curve_to(renderer, -19.63, -27.18, -7.49, -15.03, -7.49,
                                -0.04);
    rr_renderer_line_to(renderer, -7.49, 0.05);
    rr_renderer_bezier_curve_to(renderer, -7.49, 7.24, -10.34, 14.14, -15.43,
                                19.23);
    rr_renderer_bezier_curve_to(renderer, -20.52, 24.32, -27.42, 27.18, -34.62,
                                27.18);
    rr_renderer_bezier_curve_to(renderer, -49.60, 27.18, -61.75, 15.03, -61.75,
                                0.05);
    rr_renderer_line_to(renderer, -61.75, -0.04);
    rr_renderer_bezier_curve_to(renderer, -61.75, -15.03, -49.60, -27.18,
                                -34.62, -27.18);
    rr_renderer_fill(renderer);
    rr_renderer_set_fill(renderer, 0xff1e79a1);
    rr_renderer_begin_path(renderer);
    rr_renderer_move_to(renderer, -23.06, -27.18);
    rr_renderer_bezier_curve_to(renderer, -8.07, -27.18, 4.08, -15.03, 4.08,
                                -0.04);
    rr_renderer_line_to(renderer, 4.08, 0.05);
    rr_renderer_bezier_curve_to(renderer, 4.08, 7.24, 1.22, 14.14, -3.87,
                                19.23);
    rr_renderer_bezier_curve_to(renderer, -8.96, 24.32, -15.86, 27.18, -23.06,
                                27.18);
    rr_renderer_bezier_curve_to(renderer, -38.04, 27.18, -50.19, 15.03, -50.19,
                                0.05);
    rr_renderer_line_to(renderer, -50.19, -0.04);
    rr_renderer_bezier_curve_to(renderer, -50.19, -15.03, -38.04, -27.18,
                                -23.06, -27.18);
    rr_renderer_fill(renderer);
    rr_renderer_set_fill(renderer, 0xff175f7f);
    rr_renderer_begin_path(renderer);
    rr_renderer_move_to(renderer, 3.67, -27.18);
    rr_renderer_bezier_curve_to(renderer, 18.66, -27.18, 30.81, -15.03, 30.81,
                                -0.04);
    rr_renderer_line_to(renderer, 30.81, 0.05);
    rr_renderer_bezier_curve_to(renderer, 30.81, 7.24, 27.95, 14.14, 22.86,
                                19.23);
    rr_renderer_bezier_curve_to(renderer, 17.77, 24.32, 10.87, 27.18, 3.67,
                                27.18);
    rr_renderer_bezier_curve_to(renderer, -11.31, 27.18, -23.46, 15.03, -23.46,
                                0.05);
    rr_renderer_line_to(renderer, -23.46, -0.04);
    rr_renderer_bezier_curve_to(renderer, -23.46, -15.03, -11.31, -27.18, 3.67,
                                -27.18);
    rr_renderer_fill(renderer);
    rr_renderer_set_fill(renderer, 0xff1e79a1);
    rr_renderer_begin_path(renderer);
    rr_renderer_move_to(renderer, 47.15, -27.18);
    rr_renderer_bezier_curve_to(renderer, 62.16, -27.18, 74.33, -15.01, 74.33,
                                0.00);
    rr_renderer_bezier_curve_to(renderer, 74.33, 7.21, 71.47, 14.12, 66.37,
                                19.22);
    rr_renderer_bezier_curve_to(renderer, 61.28, 24.32, 54.36, 27.18, 47.15,
                                27.18);
    rr_renderer_line_to(renderer, 15.29, 27.18);
    rr_renderer_bezier_curve_to(renderer, 0.28, 27.18, -11.89, 15.01, -11.89,
                                0.00);
    rr_renderer_bezier_curve_to(renderer, -11.89, -15.01, 0.28, -27.18, 15.29,
                                -27.18);
    rr_renderer_fill(renderer);
    rr_renderer_set_fill(renderer, 0xff175f7f);
    rr_renderer_begin_path(renderer);
    rr_renderer_move_to(renderer, 43.10, -27.18);
    rr_renderer_bezier_curve_to(renderer, 58.08, -27.18, 70.23, -15.03, 70.23,
                                -0.04);
    rr_renderer_line_to(renderer, 70.23, 0.05);
    rr_renderer_bezier_curve_to(renderer, 70.23, 7.24, 67.37, 14.15, 62.28,
                                19.23);
    rr_renderer_bezier_curve_to(renderer, 57.19, 24.32, 50.29, 27.18, 43.10,
                                27.18);
    rr_renderer_bezier_curve_to(renderer, 28.11, 27.18, 15.96, 15.03, 15.96,
                                0.05);
    rr_renderer_line_to(renderer, 15.96, -0.04);
    rr_renderer_bezier_curve_to(renderer, 15.96, -15.03, 28.11, -27.18, 43.10,
                                -27.18);
    rr_renderer_fill(renderer);
    rr_renderer_set_fill(renderer, 0xff1e79a1);
    rr_renderer_begin_path(renderer);
    rr_renderer_move_to(renderer, 54.66, -27.18);
    rr_renderer_bezier_curve_to(renderer, 69.65, -27.18, 81.79, -15.03, 81.79,
                                -0.04);
    rr_renderer_line_to(renderer, 81.79, 0.05);
    rr_renderer_bezier_curve_to(renderer, 81.79, 7.24, 78.94, 14.15, 73.85,
                                19.23);
    rr_renderer_bezier_curve_to(renderer, 68.76, 24.32, 61.86, 27.18, 54.66,
                                27.18);
    rr_renderer_bezier_curve_to(renderer, 39.68, 27.18, 27.53, 15.03, 27.53,
                                0.05);
    rr_renderer_line_to(renderer, 27.53, -0.04);
    rr_renderer_bezier_curve_to(renderer, 27.53, -15.03, 39.68, -27.18, 54.66,
                                -27.18);
    rr_renderer_fill(renderer);
}

void rr_dragonfly_wing_draw(struct rr_renderer *renderer)
{
    rr_renderer_set_fill(renderer, 0x7fd9d9d9);
    rr_renderer_begin_path(renderer);
    rr_renderer_move_to(renderer, 47.13, -87.78);
    rr_renderer_bezier_curve_to(renderer, 66.97, -84.59, 76.91, -43.79, 69.33,
                                3.35);
    rr_renderer_bezier_curve_to(renderer, 61.75, 50.49, 39.53, 86.13, 19.69,
                                82.94);
    rr_renderer_bezier_curve_to(renderer, -0.15, 79.75, -10.09, 38.95, -2.51,
                                -8.20);
    rr_renderer_bezier_curve_to(renderer, 5.07, -55.34, 27.29, -90.97, 47.13,
                                -87.78);
    rr_renderer_move_to(renderer, 45.36, -76.78);
    rr_renderer_bezier_curve_to(renderer, 31.60, -78.99, 15.09, -47.49, 8.49,
                                -6.43);
    rr_renderer_bezier_curve_to(renderer, 1.89, 34.64, 7.70, 69.72, 21.46,
                                71.93);
    rr_renderer_bezier_curve_to(renderer, 35.22, 74.15, 51.73, 42.65, 58.33,
                                1.58);
    rr_renderer_bezier_curve_to(renderer, 64.93, -39.48, 59.12, -74.57, 45.36,
                                -76.78);
    rr_renderer_fill(renderer);
    rr_renderer_set_fill(renderer, 0x7fefefef);
    rr_renderer_begin_path(renderer);
    rr_renderer_move_to(renderer, 21.43, 71.93);
    rr_renderer_bezier_curve_to(renderer, 35.15, 74.14, 51.64, 42.64, 58.25,
                                1.57);
    rr_renderer_bezier_curve_to(renderer, 64.87, -39.49, 59.11, -74.57, 45.39,
                                -76.78);
    rr_renderer_bezier_curve_to(renderer, 31.67, -78.98, 15.18, -47.48, 8.57,
                                -6.41);
    rr_renderer_bezier_curve_to(renderer, 1.95, 34.65, 7.71, 69.73, 21.43,
                                71.93);
    rr_renderer_fill(renderer);
    rr_renderer_set_fill(renderer, 0x7fd9d9d9);
    rr_renderer_begin_path(renderer);
    rr_renderer_move_to(renderer, -48.38, -77.97);
    rr_renderer_bezier_curve_to(renderer, -29.24, -81.72, -6.48, -47.89, 2.44,
                                -2.40);
    rr_renderer_bezier_curve_to(renderer, 11.37, 43.09, 3.09, 83.01, -16.06,
                                86.76);
    rr_renderer_bezier_curve_to(renderer, -35.20, 90.51, -57.96, 56.68, -66.89,
                                11.19);
    rr_renderer_bezier_curve_to(renderer, -75.81, -34.30, -67.53, -74.22,
                                -48.38, -77.97);
    rr_renderer_move_to(renderer, -46.30, -67.35);
    rr_renderer_bezier_curve_to(renderer, -59.58, -64.75, -64.04, -30.52,
                                -56.27, 9.11);
    rr_renderer_bezier_curve_to(renderer, -48.49, 48.73, -31.42, 78.74, -18.14,
                                76.14);
    rr_renderer_bezier_curve_to(renderer, -4.86, 73.54, -0.40, 39.30, -8.17,
                                -0.32);
    rr_renderer_bezier_curve_to(renderer, -15.95, -39.94, -33.02, -69.96,
                                -46.30, -67.35);
    rr_renderer_fill(renderer);
    rr_renderer_set_fill(renderer, 0x7fefefef);
    rr_renderer_begin_path(renderer);
    rr_renderer_move_to(renderer, -18.15, 76.16);
    rr_renderer_bezier_curve_to(renderer, -4.91, 73.56, -0.47, 39.33, -8.23,
                                -0.30);
    rr_renderer_bezier_curve_to(renderer, -16.00, -39.93, -33.02, -69.95,
                                -46.26, -67.35);
    rr_renderer_bezier_curve_to(renderer, -59.50, -64.75, -63.94, -30.52,
                                -56.18, 9.11);
    rr_renderer_bezier_curve_to(renderer, -48.42, 48.74, -31.39, 78.75, -18.15,
                                76.16);
    rr_renderer_fill(renderer);
}