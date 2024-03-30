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

void rr_t_rex_body_draw(struct rr_renderer *renderer)
{
    rr_renderer_set_fill(renderer, 0xff9a7c55);
    rr_renderer_begin_path(renderer);
    rr_renderer_move_to(renderer, -26.71, -61.57);
    rr_renderer_bezier_curve_to(renderer, 25.76, -61.57, 68.29, -34.01, 68.29,
                                -0.01);
    rr_renderer_bezier_curve_to(renderer, 68.29, 16.32, 58.28, 31.98, 40.47,
                                43.53);
    rr_renderer_bezier_curve_to(renderer, 22.65, 55.07, -1.51, 61.56, -26.71,
                                61.56);
    rr_renderer_bezier_curve_to(renderer, -79.17, 61.56, -121.70, 34.00,
                                -121.70, -0.01);
    rr_renderer_bezier_curve_to(renderer, -121.70, -34.01, -79.17, -61.57,
                                -26.71, -61.57);
    rr_renderer_fill(renderer);
    rr_renderer_set_fill(renderer, 0xff826948);
    rr_renderer_begin_path(renderer);
    rr_renderer_move_to(renderer, -26.72, -69.86);
    rr_renderer_bezier_curve_to(renderer, 32.83, -69.86, 81.09, -38.58, 81.09,
                                0.00);
    rr_renderer_bezier_curve_to(renderer, 81.09, 18.53, 69.74, 36.30, 49.52,
                                49.40);
    rr_renderer_bezier_curve_to(renderer, 29.30, 62.51, 1.88, 69.87, -26.72,
                                69.87);
    rr_renderer_bezier_curve_to(renderer, -86.26, 69.87, -134.52, 38.59,
                                -134.52, 0.00);
    rr_renderer_bezier_curve_to(renderer, -134.52, -38.58, -86.26, -69.86,
                                -26.72, -69.86);
    rr_renderer_move_to(renderer, -26.72, -54.01);
    rr_renderer_bezier_curve_to(renderer, -77.50, -54.01, -118.67, -29.83,
                                -118.67, 0.00);
    rr_renderer_bezier_curve_to(renderer, -118.67, 29.83, -77.50, 54.01, -26.72,
                                54.01);
    rr_renderer_bezier_curve_to(renderer, 24.07, 54.01, 65.24, 29.83, 65.24,
                                0.00);
    rr_renderer_bezier_curve_to(renderer, 65.24, -29.83, 24.07, -54.01, -26.72,
                                -54.01);
    rr_renderer_fill(renderer);
    rr_renderer_set_fill(renderer, 0xff826948);
    rr_renderer_begin_path(renderer);
    rr_renderer_move_to(renderer, 84.69, -49.86);
    rr_renderer_bezier_curve_to(renderer, 112.21, -49.86, 134.52, -27.55,
                                134.52, -0.03);
    rr_renderer_bezier_curve_to(renderer, 134.52, 13.18, 129.27, 25.86, 119.93,
                                35.20);
    rr_renderer_bezier_curve_to(renderer, 110.58, 44.55, 97.91, 49.80, 84.69,
                                49.80);
    rr_renderer_line_to(renderer, 52.47, 49.80);
    rr_renderer_bezier_curve_to(renderer, 24.94, 49.80, 2.63, 27.49, 2.63,
                                -0.03);
    rr_renderer_bezier_curve_to(renderer, 2.63, -27.55, 24.94, -49.86, 52.47,
                                -49.86);
    rr_renderer_fill(renderer);
    rr_renderer_set_fill(renderer, 0xff9a7c55);
    rr_renderer_begin_path(renderer);
    rr_renderer_move_to(renderer, 83.84, -35.85);
    rr_renderer_bezier_curve_to(renderer, 103.62, -35.85, 119.65, -19.81,
                                119.65, -0.03);
    rr_renderer_bezier_curve_to(renderer, 119.65, 9.46, 115.88, 18.57, 109.16,
                                25.29);
    rr_renderer_bezier_curve_to(renderer, 102.45, 32.01, 93.34, 35.78, 83.84,
                                35.78);
    rr_renderer_line_to(renderer, 23.57, 35.78);
    rr_renderer_bezier_curve_to(renderer, 3.80, 35.78, -12.24, 19.75, -12.24,
                                -0.03);
    rr_renderer_bezier_curve_to(renderer, -12.24, -19.81, 3.80, -35.85, 23.57,
                                -35.85);
    rr_renderer_fill(renderer);
    rr_renderer_set_fill(renderer, 0xff826948);
    rr_renderer_begin_path(renderer);
    rr_renderer_move_to(renderer, 60.64, -6.65);
    rr_renderer_bezier_curve_to(renderer, 64.31, -6.65, 67.27, -3.68, 67.27,
                                -0.02);
    rr_renderer_bezier_curve_to(renderer, 67.27, 1.74, 66.58, 3.43, 65.33,
                                4.67);
    rr_renderer_bezier_curve_to(renderer, 64.09, 5.92, 62.40, 6.61, 60.64,
                                6.61);
    rr_renderer_line_to(renderer, 6.31, 6.61);
    rr_renderer_bezier_curve_to(renderer, 2.65, 6.61, -0.32, 3.65, -0.32,
                                -0.02);
    rr_renderer_bezier_curve_to(renderer, -0.32, -3.68, 2.65, -6.65, 6.31,
                                -6.65);
    rr_renderer_fill(renderer);
    rr_renderer_set_fill(renderer, 0xff826948);
    rr_renderer_begin_path(renderer);
    rr_renderer_move_to(renderer, 7.96, -6.65);
    rr_renderer_bezier_curve_to(renderer, 11.63, -6.65, 14.59, -3.68, 14.59,
                                -0.02);
    rr_renderer_bezier_curve_to(renderer, 14.59, 1.74, 13.90, 3.43, 12.65,
                                4.67);
    rr_renderer_bezier_curve_to(renderer, 11.41, 5.92, 9.72, 6.61, 7.96, 6.61);
    rr_renderer_line_to(renderer, -97.01, 6.61);
    rr_renderer_bezier_curve_to(renderer, -100.67, 6.61, -103.64, 3.65, -103.64,
                                -0.02);
    rr_renderer_bezier_curve_to(renderer, -103.64, -3.68, -100.67, -6.65,
                                -97.01, -6.65);
    rr_renderer_fill(renderer);
}

void rr_t_rex_head_draw(struct rr_renderer *renderer)
{
    rr_renderer_set_fill(renderer, 0xff826948);
    rr_renderer_begin_path(renderer);
    rr_renderer_move_to(renderer, 43.46, -38.24);
    rr_renderer_bezier_curve_to(renderer, 64.57, -38.24, 81.69, -21.12, 81.69,
                                -0.00);
    rr_renderer_bezier_curve_to(renderer, 81.69, 10.14, 77.66, 19.87, 70.49,
                                27.04);
    rr_renderer_bezier_curve_to(renderer, 63.32, 34.21, 53.60, 38.24, 43.46,
                                38.24);
    rr_renderer_line_to(renderer, 18.73, 38.24);
    rr_renderer_bezier_curve_to(renderer, -2.39, 38.24, -19.51, 21.12, -19.51,
                                -0.00);
    rr_renderer_bezier_curve_to(renderer, -19.51, -21.12, -2.39, -38.24, 18.73,
                                -38.24);
    rr_renderer_fill(renderer);
    rr_renderer_set_fill(renderer, 0xff9a7c55);
    rr_renderer_begin_path(renderer);
    rr_renderer_move_to(renderer, -22.97, -50.75);
    rr_renderer_bezier_curve_to(renderer, 5.60, -50.75, 28.77, -28.03, 28.77,
                                -0.01);
    rr_renderer_bezier_curve_to(renderer, 28.77, 13.45, 23.32, 26.36, 13.61,
                                35.88);
    rr_renderer_bezier_curve_to(renderer, 3.91, 45.39, -9.25, 50.74, -22.97,
                                50.74);
    rr_renderer_bezier_curve_to(renderer, -51.55, 50.74, -74.71, 28.02, -74.71,
                                -0.01);
    rr_renderer_bezier_curve_to(renderer, -74.71, -28.03, -51.55, -50.75,
                                -22.97, -50.75);
    rr_renderer_fill(renderer);
    rr_renderer_set_fill(renderer, 0xff826948);
    rr_renderer_begin_path(renderer);
    rr_renderer_move_to(renderer, -22.98, -57.59);
    rr_renderer_bezier_curve_to(renderer, 9.45, -57.59, 35.74, -31.81, 35.74,
                                -0.00);
    rr_renderer_bezier_curve_to(renderer, 35.74, 15.27, 29.55, 29.92, 18.54,
                                40.72);
    rr_renderer_bezier_curve_to(renderer, 7.53, 51.52, -7.40, 57.59, -22.98,
                                57.59);
    rr_renderer_bezier_curve_to(renderer, -55.40, 57.59, -81.69, 31.81, -81.69,
                                -0.00);
    rr_renderer_bezier_curve_to(renderer, -81.69, -31.81, -55.40, -57.59,
                                -22.98, -57.59);
    rr_renderer_move_to(renderer, -22.98, -41.61);
    rr_renderer_bezier_curve_to(renderer, -46.58, -41.61, -65.71, -22.98,
                                -65.71, -0.00);
    rr_renderer_bezier_curve_to(renderer, -65.71, 22.98, -46.58, 41.61, -22.98,
                                41.61);
    rr_renderer_bezier_curve_to(renderer, 0.62, 41.61, 19.76, 22.98, 19.76,
                                -0.00);
    rr_renderer_bezier_curve_to(renderer, 19.76, -22.98, 0.62, -41.61, -22.98,
                                -41.61);
    rr_renderer_fill(renderer);
    rr_renderer_set_fill(renderer, 0xff9a7c55);
    rr_renderer_begin_path(renderer);
    rr_renderer_move_to(renderer, 44.84, -22.78);
    rr_renderer_bezier_curve_to(renderer, 57.42, -22.78, 67.61, -12.58, 67.61,
                                0.00);
    rr_renderer_bezier_curve_to(renderer, 67.61, 6.04, 65.21, 11.83, 60.94,
                                16.10);
    rr_renderer_bezier_curve_to(renderer, 56.67, 20.38, 50.88, 22.78, 44.84,
                                22.78);
    rr_renderer_line_to(renderer, 3.26, 22.78);
    rr_renderer_bezier_curve_to(renderer, -9.31, 22.78, -19.51, 12.58, -19.51,
                                0.00);
    rr_renderer_bezier_curve_to(renderer, -19.51, -12.58, -9.31, -22.78, 3.26,
                                -22.78);
    rr_renderer_fill(renderer);
    rr_renderer_set_fill(renderer, 0xff9a7c55);
    rr_renderer_begin_path(renderer);
    rr_renderer_move_to(renderer, 3.25, 32.84);
    rr_renderer_bezier_curve_to(renderer, -1.55, 26.59, 2.46, 19.27, 12.21,
                                16.48);
    rr_renderer_bezier_curve_to(renderer, 21.97, 13.70, 33.77, 16.51, 38.58,
                                22.75);
    rr_renderer_bezier_curve_to(renderer, 24.58, 21.96, 11.21, 25.78, 3.25,
                                32.84);
    rr_renderer_fill(renderer);
    rr_renderer_set_fill(renderer, 0xff826948);
    rr_renderer_begin_path(renderer);
    rr_renderer_move_to(renderer, 11.61, 46.48);
    rr_renderer_bezier_curve_to(renderer, 7.66, 41.35, 10.96, 35.33, 18.98,
                                33.04);
    rr_renderer_bezier_curve_to(renderer, 27.00, 30.75, 36.71, 33.05, 40.66,
                                38.18);
    rr_renderer_bezier_curve_to(renderer, 29.16, 37.58, 18.20, 40.71, 11.61,
                                46.48);
    rr_renderer_fill(renderer);
    rr_renderer_set_fill(renderer, 0xff9a7c55);
    rr_renderer_begin_path(renderer);
    rr_renderer_move_to(renderer, 3.25, -32.84);
    rr_renderer_bezier_curve_to(renderer, -1.55, -26.59, 2.46, -19.27, 12.21,
                                -16.48);
    rr_renderer_bezier_curve_to(renderer, 21.97, -13.70, 33.77, -16.51, 38.58,
                                -22.75);
    rr_renderer_bezier_curve_to(renderer, 24.58, -21.96, 11.21, -25.78, 3.25,
                                -32.84);
    rr_renderer_fill(renderer);
    rr_renderer_set_fill(renderer, 0xff826948);
    rr_renderer_begin_path(renderer);
    rr_renderer_move_to(renderer, 11.61, -46.48);
    rr_renderer_bezier_curve_to(renderer, 7.66, -41.34, 10.96, -35.33, 18.98,
                                -33.03);
    rr_renderer_bezier_curve_to(renderer, 27.00, -30.74, 36.71, -33.05, 40.66,
                                -38.18);
    rr_renderer_bezier_curve_to(renderer, 29.16, -37.58, 18.20, -40.71, 11.61,
                                -46.48);
    rr_renderer_fill(renderer);
    rr_renderer_set_fill(renderer, 0xff826948);
    rr_renderer_begin_path(renderer);
    rr_renderer_move_to(renderer, -24.95, 21.11);
    rr_renderer_bezier_curve_to(renderer, -16.46, 11.31, -4.15, 5.68, 8.80,
                                5.65);
    rr_renderer_line_to(renderer, 8.83, 19.00);
    rr_renderer_bezier_curve_to(renderer, -0.26, 19.02, -8.90, 22.98, -14.86,
                                29.85);
    rr_renderer_fill(renderer);
    rr_renderer_set_fill(renderer, 0xff826948);
    rr_renderer_begin_path(renderer);
    rr_renderer_move_to(renderer, 8.89, 5.59);
    rr_renderer_bezier_curve_to(renderer, 12.56, 5.59, 15.53, 8.56, 15.53,
                                12.22);
    rr_renderer_bezier_curve_to(renderer, 15.53, 13.98, 14.83, 15.67, 13.58,
                                16.92);
    rr_renderer_bezier_curve_to(renderer, 12.34, 18.16, 10.65, 18.86, 8.89,
                                18.86);
    rr_renderer_bezier_curve_to(renderer, 5.22, 18.86, 2.25, 15.89, 2.25,
                                12.22);
    rr_renderer_bezier_curve_to(renderer, 2.25, 8.56, 5.22, 5.59, 8.89, 5.59);
    rr_renderer_fill(renderer);
    rr_renderer_set_fill(renderer, 0xff826948);
    rr_renderer_begin_path(renderer);
    rr_renderer_move_to(renderer, -19.86, 18.86);
    rr_renderer_bezier_curve_to(renderer, -16.20, 18.86, -13.23, 21.83, -13.23,
                                25.50);
    rr_renderer_bezier_curve_to(renderer, -13.23, 27.26, -13.93, 28.95, -15.17,
                                30.19);
    rr_renderer_bezier_curve_to(renderer, -16.42, 31.44, -18.10, 32.14, -19.86,
                                32.14);
    rr_renderer_bezier_curve_to(renderer, -23.53, 32.14, -26.50, 29.16, -26.50,
                                25.50);
    rr_renderer_bezier_curve_to(renderer, -26.50, 21.83, -23.53, 18.86, -19.86,
                                18.86);
    rr_renderer_fill(renderer);
    rr_renderer_set_fill(renderer, 0xff826948);
    rr_renderer_begin_path(renderer);
    rr_renderer_move_to(renderer, -24.95, -21.11);
    rr_renderer_bezier_curve_to(renderer, -16.46, -11.31, -4.15, -5.68, 8.80,
                                -5.65);
    rr_renderer_line_to(renderer, 8.83, -19.00);
    rr_renderer_bezier_curve_to(renderer, -0.26, -19.02, -8.90, -22.98, -14.86,
                                -29.85);
    rr_renderer_fill(renderer);
    rr_renderer_set_fill(renderer, 0xff826948);
    rr_renderer_begin_path(renderer);
    rr_renderer_move_to(renderer, 8.89, -5.59);
    rr_renderer_bezier_curve_to(renderer, 12.56, -5.59, 15.53, -8.56, 15.53,
                                -12.22);
    rr_renderer_bezier_curve_to(renderer, 15.53, -13.98, 14.83, -15.67, 13.58,
                                -16.92);
    rr_renderer_bezier_curve_to(renderer, 12.34, -18.16, 10.65, -18.86, 8.89,
                                -18.86);
    rr_renderer_bezier_curve_to(renderer, 5.22, -18.86, 2.25, -15.89, 2.25,
                                -12.22);
    rr_renderer_bezier_curve_to(renderer, 2.25, -8.56, 5.22, -5.59, 8.89,
                                -5.59);
    rr_renderer_fill(renderer);
    rr_renderer_set_fill(renderer, 0xff826948);
    rr_renderer_begin_path(renderer);
    rr_renderer_move_to(renderer, -19.86, -18.86);
    rr_renderer_bezier_curve_to(renderer, -16.20, -18.86, -13.23, -21.83,
                                -13.23, -25.50);
    rr_renderer_bezier_curve_to(renderer, -13.23, -27.26, -13.93, -28.95,
                                -15.17, -30.19);
    rr_renderer_bezier_curve_to(renderer, -16.42, -31.44, -18.10, -32.14,
                                -19.86, -32.14);
    rr_renderer_bezier_curve_to(renderer, -23.53, -32.14, -26.50, -29.16,
                                -26.50, -25.50);
    rr_renderer_bezier_curve_to(renderer, -26.50, -21.83, -23.53, -18.86,
                                -19.86, -18.86);
    rr_renderer_fill(renderer);
}

void rr_t_rex_leg1_draw(struct rr_renderer *renderer)
{
    rr_renderer_set_fill(renderer, 0xff826948);
    rr_renderer_begin_path(renderer);
    rr_renderer_move_to(renderer, 23.81, -69.44);
    rr_renderer_bezier_curve_to(renderer, 27.60, -71.16, 32.01, -71.88, 38.38,
                                -72.46);
    rr_renderer_bezier_curve_to(renderer, 44.74, -73.04, 54.91, -73.65, 61.99,
                                -72.94);
    rr_renderer_bezier_curve_to(renderer, 69.07, -72.23, 79.10, -69.47, 80.88,
                                -68.21);
    rr_renderer_bezier_curve_to(renderer, 82.66, -66.94, 74.47, -66.09, 72.67,
                                -65.34);
    rr_renderer_bezier_curve_to(renderer, 70.87, -64.58, 70.11, -64.19, 70.07,
                                -63.65);
    rr_renderer_bezier_curve_to(renderer, 70.03, -63.11, 70.31, -63.17, 72.42,
                                -62.09);
    rr_renderer_bezier_curve_to(renderer, 74.53, -61.02, 83.11, -58.53, 82.73,
                                -57.19);
    rr_renderer_bezier_curve_to(renderer, 82.34, -55.86, 75.93, -55.69, 70.12,
                                -54.08);
    rr_renderer_bezier_curve_to(renderer, 64.31, -52.47, 54.53, -49.98, 47.88,
                                -47.52);
    rr_renderer_bezier_curve_to(renderer, 41.23, -45.07, 34.44, -41.55, 30.24,
                                -39.37);
    rr_renderer_bezier_curve_to(renderer, 26.04, -37.20, 25.18, -32.92, 22.67,
                                -34.48);
    rr_renderer_bezier_curve_to(renderer, 20.16, -36.04, 16.37, -44.12, 15.19,
                                -48.73);
    rr_renderer_bezier_curve_to(renderer, 14.02, -53.34, 14.20, -58.70, 15.64,
                                -62.15);
    rr_renderer_bezier_curve_to(renderer, 17.07, -65.60, 20.02, -67.72, 23.81,
                                -69.44);
    rr_renderer_fill(renderer);
    rr_renderer_set_fill(renderer, 0xff9a7c55);
    rr_renderer_begin_path(renderer);
    rr_renderer_move_to(renderer, 26.64, -65.18);
    rr_renderer_bezier_curve_to(renderer, 29.82, -66.58, 34.37, -67.50, 39.64,
                                -68.22);
    rr_renderer_bezier_curve_to(renderer, 44.91, -68.94, 53.51, -69.49, 58.26,
                                -69.50);
    rr_renderer_bezier_curve_to(renderer, 63.00, -69.50, 66.82, -68.84, 68.10,
                                -68.24);
    rr_renderer_bezier_curve_to(renderer, 69.38, -67.64, 66.34, -66.85, 65.94,
                                -65.91);
    rr_renderer_bezier_curve_to(renderer, 65.55, -64.97, 65.29, -63.56, 65.73,
                                -62.62);
    rr_renderer_bezier_curve_to(renderer, 66.18, -61.68, 67.86, -60.92, 68.62,
                                -60.25);
    rr_renderer_bezier_curve_to(renderer, 69.38, -59.57, 71.16, -59.09, 70.28,
                                -58.55);
    rr_renderer_bezier_curve_to(renderer, 69.41, -58.01, 66.99, -57.88, 63.36,
                                -57.00);
    rr_renderer_bezier_curve_to(renderer, 59.73, -56.11, 53.56, -54.92, 48.49,
                                -53.22);
    rr_renderer_bezier_curve_to(renderer, 43.42, -51.52, 37.07, -48.57, 32.93,
                                -46.79);
    rr_renderer_bezier_curve_to(renderer, 28.79, -45.01, 25.77, -41.91, 23.66,
                                -42.53);
    rr_renderer_bezier_curve_to(renderer, 21.54, -43.15, 20.75, -47.61, 20.24,
                                -50.49);
    rr_renderer_bezier_curve_to(renderer, 19.73, -53.36, 19.51, -57.36, 20.58,
                                -59.80);
    rr_renderer_bezier_curve_to(renderer, 21.64, -62.25, 23.47, -63.77, 26.64,
                                -65.18);
    rr_renderer_fill(renderer);
    rr_renderer_set_fill(renderer, 0xff9a7c55);
    rr_renderer_begin_path(renderer);
    rr_renderer_move_to(renderer, -42.66, 9.34);
    rr_renderer_bezier_curve_to(renderer, -21.94, 9.34, -5.14, 25.81, -5.14,
                                46.14);
    rr_renderer_bezier_curve_to(renderer, -5.14, 55.90, -9.09, 65.26, -16.13,
                                72.16);
    rr_renderer_bezier_curve_to(renderer, -23.16, 79.06, -32.71, 82.94, -42.66,
                                82.94);
    rr_renderer_bezier_curve_to(renderer, -63.38, 82.94, -80.18, 66.46, -80.18,
                                46.14);
    rr_renderer_bezier_curve_to(renderer, -80.18, 25.81, -63.38, 9.34, -42.66,
                                9.34);
    rr_renderer_fill(renderer);
    rr_renderer_set_fill(renderer, 0xff826948);
    rr_renderer_begin_path(renderer);
    rr_renderer_move_to(renderer, -42.66, 4.38);
    rr_renderer_bezier_curve_to(renderer, -19.14, 4.38, -0.08, 23.07, -0.08,
                                46.14);
    rr_renderer_bezier_curve_to(renderer, -0.08, 57.22, -4.57, 67.84, -12.55,
                                75.67);
    rr_renderer_bezier_curve_to(renderer, -20.54, 83.51, -31.37, 87.91, -42.66,
                                87.91);
    rr_renderer_bezier_curve_to(renderer, -66.18, 87.91, -85.25, 69.21, -85.25,
                                46.14);
    rr_renderer_bezier_curve_to(renderer, -85.25, 23.07, -66.18, 4.38, -42.66,
                                4.38);
    rr_renderer_move_to(renderer, -42.66, 15.97);
    rr_renderer_bezier_curve_to(renderer, -59.78, 15.97, -73.66, 29.48, -73.66,
                                46.14);
    rr_renderer_bezier_curve_to(renderer, -73.66, 62.81, -59.78, 76.32, -42.66,
                                76.32);
    rr_renderer_bezier_curve_to(renderer, -25.55, 76.32, -11.67, 62.81, -11.67,
                                46.14);
    rr_renderer_bezier_curve_to(renderer, -11.67, 29.48, -25.55, 15.97, -42.66,
                                15.97);
    rr_renderer_fill(renderer);
}

void rr_t_rex_leg2_draw(struct rr_renderer *renderer)
{
    rr_renderer_set_fill(renderer, 0xff826948);
    rr_renderer_begin_path(renderer);
    rr_renderer_move_to(renderer, 23.81, 69.40);
    rr_renderer_bezier_curve_to(renderer, 27.60, 71.12, 32.01, 71.83, 38.37,
                                72.42);
    rr_renderer_bezier_curve_to(renderer, 44.74, 73.00, 54.90, 73.60, 61.99,
                                72.89);
    rr_renderer_bezier_curve_to(renderer, 69.07, 72.18, 79.10, 69.43, 80.88,
                                68.16);
    rr_renderer_bezier_curve_to(renderer, 82.66, 66.89, 74.47, 66.05, 72.67,
                                65.29);
    rr_renderer_bezier_curve_to(renderer, 70.87, 64.53, 70.11, 64.14, 70.07,
                                63.60);
    rr_renderer_bezier_curve_to(renderer, 70.03, 63.06, 70.31, 63.13, 72.42,
                                62.05);
    rr_renderer_bezier_curve_to(renderer, 74.53, 60.97, 83.11, 58.48, 82.72,
                                57.15);
    rr_renderer_bezier_curve_to(renderer, 82.34, 55.81, 75.93, 55.65, 70.12,
                                54.04);
    rr_renderer_bezier_curve_to(renderer, 64.31, 52.43, 54.52, 49.93, 47.88,
                                47.48);
    rr_renderer_bezier_curve_to(renderer, 41.23, 45.03, 34.44, 41.50, 30.24,
                                39.33);
    rr_renderer_bezier_curve_to(renderer, 26.04, 37.15, 25.18, 32.88, 22.67,
                                34.44);
    rr_renderer_bezier_curve_to(renderer, 20.16, 35.99, 16.37, 44.07, 15.19,
                                48.68);
    rr_renderer_bezier_curve_to(renderer, 14.02, 53.29, 14.20, 58.65, 15.64,
                                62.10);
    rr_renderer_bezier_curve_to(renderer, 17.07, 65.56, 20.02, 67.68, 23.81,
                                69.40);
    rr_renderer_fill(renderer);
    rr_renderer_set_fill(renderer, 0xff9a7c55);
    rr_renderer_begin_path(renderer);
    rr_renderer_move_to(renderer, 26.64, 65.13);
    rr_renderer_bezier_curve_to(renderer, 29.82, 66.53, 34.37, 67.45, 39.64,
                                68.17);
    rr_renderer_bezier_curve_to(renderer, 44.91, 68.89, 53.51, 69.45, 58.26,
                                69.45);
    rr_renderer_bezier_curve_to(renderer, 63.00, 69.46, 66.82, 68.79, 68.10,
                                68.20);
    rr_renderer_bezier_curve_to(renderer, 69.38, 67.60, 66.34, 66.80, 65.94,
                                65.87);
    rr_renderer_bezier_curve_to(renderer, 65.55, 64.93, 65.28, 63.52, 65.73,
                                62.58);
    rr_renderer_bezier_curve_to(renderer, 66.18, 61.63, 67.86, 60.88, 68.62,
                                60.20);
    rr_renderer_bezier_curve_to(renderer, 69.38, 59.52, 71.16, 59.05, 70.28,
                                58.51);
    rr_renderer_bezier_curve_to(renderer, 69.41, 57.97, 66.99, 57.84, 63.36,
                                56.95);
    rr_renderer_bezier_curve_to(renderer, 59.73, 56.06, 53.56, 54.88, 48.49,
                                53.18);
    rr_renderer_bezier_curve_to(renderer, 43.42, 51.47, 37.07, 48.53, 32.93,
                                46.74);
    rr_renderer_bezier_curve_to(renderer, 28.79, 44.96, 25.77, 41.87, 23.65,
                                42.49);
    rr_renderer_bezier_curve_to(renderer, 21.54, 43.10, 20.75, 47.56, 20.24,
                                50.44);
    rr_renderer_bezier_curve_to(renderer, 19.73, 53.32, 19.51, 57.31, 20.58,
                                59.76);
    rr_renderer_bezier_curve_to(renderer, 21.64, 62.21, 23.47, 63.73, 26.64,
                                65.13);
    rr_renderer_fill(renderer);
    rr_renderer_set_fill(renderer, 0xff9a7c55);
    rr_renderer_begin_path(renderer);
    rr_renderer_move_to(renderer, -42.66, -82.90);
    rr_renderer_bezier_curve_to(renderer, -21.94, -82.90, -5.14, -66.42, -5.14,
                                -46.10);
    rr_renderer_bezier_curve_to(renderer, -5.14, -36.34, -9.09, -26.98, -16.13,
                                -20.08);
    rr_renderer_bezier_curve_to(renderer, -23.16, -13.17, -32.71, -9.30, -42.66,
                                -9.30);
    rr_renderer_bezier_curve_to(renderer, -63.38, -9.30, -80.18, -25.77, -80.18,
                                -46.10);
    rr_renderer_bezier_curve_to(renderer, -80.18, -66.42, -63.38, -82.90,
                                -42.66, -82.90);
    rr_renderer_fill(renderer);
    rr_renderer_set_fill(renderer, 0xff826948);
    rr_renderer_begin_path(renderer);
    rr_renderer_move_to(renderer, -42.66, -87.86);
    rr_renderer_bezier_curve_to(renderer, -19.14, -87.86, -0.08, -69.16, -0.08,
                                -46.10);
    rr_renderer_bezier_curve_to(renderer, -0.08, -35.02, -4.57, -24.40, -12.55,
                                -16.56);
    rr_renderer_bezier_curve_to(renderer, -20.54, -8.73, -31.37, -4.33, -42.66,
                                -4.33);
    rr_renderer_bezier_curve_to(renderer, -66.18, -4.33, -85.25, -23.03, -85.25,
                                -46.10);
    rr_renderer_bezier_curve_to(renderer, -85.25, -69.16, -66.18, -87.86,
                                -42.66, -87.86);
    rr_renderer_move_to(renderer, -42.66, -76.27);
    rr_renderer_bezier_curve_to(renderer, -59.78, -76.27, -73.66, -62.76,
                                -73.66, -46.10);
    rr_renderer_bezier_curve_to(renderer, -73.66, -29.43, -59.78, -15.92,
                                -42.66, -15.92);
    rr_renderer_bezier_curve_to(renderer, -25.55, -15.92, -11.67, -29.43,
                                -11.67, -46.10);
    rr_renderer_bezier_curve_to(renderer, -11.67, -62.76, -25.55, -76.27,
                                -42.66, -76.27);
    rr_renderer_fill(renderer);
}

void rr_t_rex_tail_draw(struct rr_renderer *renderer)
{
    rr_renderer_set_fill(renderer, 0xff826948);
    rr_renderer_begin_path(renderer);
    rr_renderer_move_to(renderer, 61.13, 52.17);
    rr_renderer_line_to(renderer, -120.35, 16.27);
    rr_renderer_line_to(renderer, -120.35, -16.27);
    rr_renderer_line_to(renderer, 61.13, -52.17);
    rr_renderer_fill(renderer);
    rr_renderer_set_fill(renderer, 0xff826948);
    rr_renderer_begin_path(renderer);
    rr_renderer_move_to(renderer, 74.55, -53.70);
    rr_renderer_bezier_curve_to(renderer, 108.77, -53.70, 136.51, -29.66,
                                136.51, -0.00);
    rr_renderer_bezier_curve_to(renderer, 136.51, 14.24, 129.98, 27.90, 118.36,
                                37.97);
    rr_renderer_bezier_curve_to(renderer, 106.74, 48.04, 90.98, 53.70, 74.55,
                                53.70);
    rr_renderer_bezier_curve_to(renderer, 40.33, 53.70, 12.59, 29.66, 12.59,
                                -0.00);
    rr_renderer_bezier_curve_to(renderer, 12.59, -29.66, 40.33, -53.70, 74.55,
                                -53.70);
    rr_renderer_fill(renderer);
    rr_renderer_set_fill(renderer, 0xff826948);
    rr_renderer_begin_path(renderer);
    rr_renderer_move_to(renderer, 74.57, -37.18);
    rr_renderer_bezier_curve_to(renderer, 98.25, -37.18, 117.45, -20.54, 117.45,
                                -0.01);
    rr_renderer_bezier_curve_to(renderer, 117.45, 9.85, 112.93, 19.30, 104.89,
                                26.27);
    rr_renderer_bezier_curve_to(renderer, 96.85, 33.24, 85.94, 37.16, 74.57,
                                37.16);
    rr_renderer_bezier_curve_to(renderer, 50.88, 37.16, 31.68, 20.51, 31.68,
                                -0.01);
    rr_renderer_bezier_curve_to(renderer, 31.68, -20.54, 50.88, -37.18, 74.57,
                                -37.18);
    rr_renderer_fill(renderer);
    rr_renderer_set_fill(renderer, 0xff826948);
    rr_renderer_begin_path(renderer);
    rr_renderer_move_to(renderer, -117.59, -16.41);
    rr_renderer_bezier_curve_to(renderer, -107.14, -16.41, -98.67, -9.06,
                                -98.67, -0.01);
    rr_renderer_bezier_curve_to(renderer, -98.67, 4.34, -100.66, 8.51, -104.21,
                                11.59);
    rr_renderer_bezier_curve_to(renderer, -107.76, 14.67, -112.57, 16.39,
                                -117.59, 16.39);
    rr_renderer_bezier_curve_to(renderer, -128.04, 16.39, -136.51, 9.05,
                                -136.51, -0.01);
    rr_renderer_bezier_curve_to(renderer, -136.51, -9.06, -128.04, -16.41,
                                -117.59, -16.41);
    rr_renderer_fill(renderer);
    rr_renderer_set_fill(renderer, 0xff826948);
    rr_renderer_begin_path(renderer);
    rr_renderer_move_to(renderer, 63.12, 35.81);
    rr_renderer_line_to(renderer, -120.06, -0.01);
    rr_renderer_line_to(renderer, 63.12, -35.82);
    rr_renderer_fill(renderer);
    rr_renderer_set_fill(renderer, 0xff9a7c55);
    rr_renderer_begin_path(renderer);
    rr_renderer_move_to(renderer, 74.57, -37.18);
    rr_renderer_bezier_curve_to(renderer, 98.25, -37.18, 117.45, -20.54, 117.45,
                                -0.01);
    rr_renderer_bezier_curve_to(renderer, 117.45, 9.85, 112.93, 19.30, 104.89,
                                26.27);
    rr_renderer_bezier_curve_to(renderer, 96.85, 33.24, 85.94, 37.16, 74.57,
                                37.16);
    rr_renderer_bezier_curve_to(renderer, 50.88, 37.16, 31.68, 20.51, 31.68,
                                -0.01);
    rr_renderer_bezier_curve_to(renderer, 31.68, -20.54, 50.88, -37.18, 74.57,
                                -37.18);
    rr_renderer_fill(renderer);
    rr_renderer_set_fill(renderer, 0xff9a7c55);
    rr_renderer_begin_path(renderer);
    rr_renderer_move_to(renderer, 63.12, 35.81);
    rr_renderer_line_to(renderer, -120.06, -0.01);
    rr_renderer_line_to(renderer, 63.12, -35.82);
    rr_renderer_fill(renderer);
    rr_renderer_set_fill(renderer, 0xff826948);
    rr_renderer_begin_path(renderer);
    rr_renderer_move_to(renderer, 76.13, -6.62);
    rr_renderer_bezier_curve_to(renderer, 79.79, -6.62, 82.76, -3.65, 82.76,
                                0.01);
    rr_renderer_bezier_curve_to(renderer, 82.76, 1.77, 82.06, 3.46, 80.81,
                                4.70);
    rr_renderer_bezier_curve_to(renderer, 79.57, 5.94, 77.88, 6.64, 76.13,
                                6.64);
    rr_renderer_line_to(renderer, -121.45, 6.64);
    rr_renderer_bezier_curve_to(renderer, -125.11, 6.64, -128.08, 3.67, -128.08,
                                0.01);
    rr_renderer_bezier_curve_to(renderer, -128.08, -3.65, -125.11, -6.62,
                                -121.45, -6.62);
    rr_renderer_fill(renderer);
}