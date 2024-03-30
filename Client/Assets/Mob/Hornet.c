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

void rr_hornet_head_draw(struct rr_renderer *renderer)
{
    rr_renderer_set_fill(renderer, 0xff6c5c0d);
    rr_renderer_begin_path(renderer);
    rr_renderer_move_to(renderer, -8.34, 1.63);
    rr_renderer_bezier_curve_to(renderer, -8.34, 15.80, 2.47, 27.29, 15.80,
                                27.29);
    rr_renderer_bezier_curve_to(renderer, 29.14, 27.29, 39.95, 15.80, 39.95,
                                1.63);
    rr_renderer_bezier_curve_to(renderer, 24.10, 5.90, 7.50, 5.90, -8.34, 1.63);
    rr_renderer_fill(renderer);
    rr_renderer_set_fill(renderer, 0xff6c5c0d);
    rr_renderer_begin_path(renderer);
    rr_renderer_move_to(renderer, -8.34, -2.71);
    rr_renderer_bezier_curve_to(renderer, -8.34, -16.89, 2.47, -28.38, 15.80,
                                -28.38);
    rr_renderer_bezier_curve_to(renderer, 29.14, -28.38, 39.95, -16.89, 39.95,
                                -2.71);
    rr_renderer_bezier_curve_to(renderer, 24.10, -6.99, 7.50, -6.99, -8.34,
                                -2.71);
    rr_renderer_fill(renderer);
    rr_renderer_set_fill(renderer, 0xffcdb124);
    rr_renderer_begin_path(renderer);
    rr_renderer_move_to(renderer, -29.55, 48.33);
    rr_renderer_bezier_curve_to(renderer, -56.53, 48.33, -78.40, 26.45, -78.40,
                                -0.54);
    rr_renderer_bezier_curve_to(renderer, -78.40, -13.50, -73.26, -25.93,
                                -64.10, -35.09);
    rr_renderer_bezier_curve_to(renderer, -54.93, -44.25, -42.51, -49.40,
                                -29.55, -49.40);
    rr_renderer_bezier_curve_to(renderer, -2.57, -49.40, 19.30, -27.53, 19.30,
                                -0.54);
    rr_renderer_bezier_curve_to(renderer, 19.30, 26.45, -2.57, 48.33, -29.55,
                                48.33);
    rr_renderer_fill(renderer);
    rr_renderer_set_fill(renderer, 0xffa68e1a);
    rr_renderer_begin_path(renderer);
    rr_renderer_move_to(renderer, -29.55, 54.91);
    rr_renderer_bezier_curve_to(renderer, -60.17, 54.91, -84.99, 30.08, -84.99,
                                -0.54);
    rr_renderer_bezier_curve_to(renderer, -84.99, -15.25, -79.15, -29.36,
                                -68.75, -39.76);
    rr_renderer_bezier_curve_to(renderer, -58.35, -50.16, -44.25, -56.00,
                                -29.55, -56.00);
    rr_renderer_bezier_curve_to(renderer, 1.08, -56.00, 25.90, -31.17, 25.90,
                                -0.54);
    rr_renderer_bezier_curve_to(renderer, 25.90, 30.08, 1.08, 54.91, -29.55,
                                54.91);
    rr_renderer_move_to(renderer, -29.55, 41.02);
    rr_renderer_bezier_curve_to(renderer, -6.60, 41.02, 12.00, 22.41, 12.00,
                                -0.54);
    rr_renderer_bezier_curve_to(renderer, 12.00, -23.50, -6.60, -42.10, -29.55,
                                -42.10);
    rr_renderer_bezier_curve_to(renderer, -52.49, -42.10, -71.09, -23.50,
                                -71.09, -0.54);
    rr_renderer_bezier_curve_to(renderer, -71.09, 22.41, -52.49, 41.02, -29.55,
                                41.02);
    rr_renderer_fill(renderer);
    rr_renderer_set_fill(renderer, 0xff262626);
    rr_renderer_begin_path(renderer);
    rr_renderer_move_to(renderer, 74.56, 76.72);
    rr_renderer_bezier_curve_to(renderer, 80.32, 68.89, 60.09, 49.02, 29.38,
                                32.34);
    rr_renderer_bezier_curve_to(renderer, -1.34, 15.66, -30.90, 8.49, -36.66,
                                16.32);
    rr_renderer_bezier_curve_to(renderer, -22.36, 16.47, 1.79, 24.75, 25.49,
                                37.62);
    rr_renderer_bezier_curve_to(renderer, 49.19, 50.49, 68.26, 65.68, 74.56,
                                76.72);
    rr_renderer_fill(renderer);
    rr_renderer_set_fill(renderer, 0xff262626);
    rr_renderer_begin_path(renderer);
    rr_renderer_move_to(renderer, 70.12, 76.19);
    rr_renderer_bezier_curve_to(renderer, 72.03, 77.23, 74.23, 77.18, 75.04,
                                76.08);
    rr_renderer_bezier_curve_to(renderer, 75.43, 75.55, 75.44, 74.85, 75.07,
                                74.12);
    rr_renderer_bezier_curve_to(renderer, 74.70, 73.40, 73.97, 72.71, 73.06,
                                72.21);
    rr_renderer_bezier_curve_to(renderer, 71.15, 71.18, 68.95, 71.23, 68.14,
                                72.33);
    rr_renderer_bezier_curve_to(renderer, 67.33, 73.43, 68.22, 75.16, 70.12,
                                76.19);
    rr_renderer_fill(renderer);
    rr_renderer_set_fill(renderer, 0xff262626);
    rr_renderer_begin_path(renderer);
    rr_renderer_move_to(renderer, -34.20, 19.55);
    rr_renderer_bezier_curve_to(renderer, -32.29, 20.58, -30.09, 20.53, -29.28,
                                19.43);
    rr_renderer_bezier_curve_to(renderer, -28.89, 18.91, -28.88, 18.20, -29.25,
                                17.48);
    rr_renderer_bezier_curve_to(renderer, -29.63, 16.75, -30.35, 16.07, -31.26,
                                15.57);
    rr_renderer_bezier_curve_to(renderer, -33.17, 14.53, -35.38, 14.59, -36.19,
                                15.69);
    rr_renderer_bezier_curve_to(renderer, -37.00, 16.78, -36.11, 18.51, -34.20,
                                19.55);
    rr_renderer_fill(renderer);
    rr_renderer_set_fill(renderer, 0xff262626);
    rr_renderer_begin_path(renderer);
    rr_renderer_move_to(renderer, 69.83, 75.95);
    rr_renderer_bezier_curve_to(renderer, 76.15, 67.36, 58.17, 47.84, 29.67,
                                32.37);
    rr_renderer_bezier_curve_to(renderer, 1.17, 16.90, -27.05, 11.32, -33.37,
                                19.92);
    rr_renderer_bezier_curve_to(renderer, 2.40, 35.71, 37.87, 54.97, 69.83,
                                75.95);
    rr_renderer_fill(renderer);
    rr_renderer_set_fill(renderer, 0xff262626);
    rr_renderer_begin_path(renderer);
    rr_renderer_move_to(renderer, 72.03, 75.33);
    rr_renderer_bezier_curve_to(renderer, 77.73, 67.58, 58.72, 48.46, 29.58,
                                32.64);
    rr_renderer_bezier_curve_to(renderer, 0.43, 16.82, -27.82, 10.27, -33.52,
                                18.03);
    rr_renderer_bezier_curve_to(renderer, -17.41, 20.94, 3.70, 29.02, 24.10,
                                40.10);
    rr_renderer_bezier_curve_to(renderer, 44.49, 51.17, 62.06, 64.08, 72.03,
                                75.33);
    rr_renderer_fill(renderer);
    rr_renderer_set_fill(renderer, 0xff262626);
    rr_renderer_begin_path(renderer);
    rr_renderer_move_to(renderer, 74.56, -76.72);
    rr_renderer_bezier_curve_to(renderer, 80.32, -68.89, 60.09, -49.02, 29.38,
                                -32.34);
    rr_renderer_bezier_curve_to(renderer, -1.34, -15.66, -30.90, -8.49, -36.66,
                                -16.32);
    rr_renderer_bezier_curve_to(renderer, -22.35, -16.47, 1.80, -24.75, 25.49,
                                -37.62);
    rr_renderer_bezier_curve_to(renderer, 49.19, -50.49, 68.26, -65.68, 74.56,
                                -76.72);
    rr_renderer_fill(renderer);
    rr_renderer_set_fill(renderer, 0xff262626);
    rr_renderer_begin_path(renderer);
    rr_renderer_move_to(renderer, 70.12, -76.19);
    rr_renderer_bezier_curve_to(renderer, 72.03, -77.23, 74.24, -77.18, 75.05,
                                -76.08);
    rr_renderer_bezier_curve_to(renderer, 75.43, -75.55, 75.44, -74.85, 75.07,
                                -74.12);
    rr_renderer_bezier_curve_to(renderer, 74.70, -73.40, 73.98, -72.71, 73.06,
                                -72.22);
    rr_renderer_bezier_curve_to(renderer, 71.15, -71.18, 68.95, -71.23, 68.14,
                                -72.33);
    rr_renderer_bezier_curve_to(renderer, 67.33, -73.43, 68.22, -75.16, 70.12,
                                -76.19);
    rr_renderer_fill(renderer);
    rr_renderer_set_fill(renderer, 0xff262626);
    rr_renderer_begin_path(renderer);
    rr_renderer_move_to(renderer, -34.20, -19.55);
    rr_renderer_bezier_curve_to(renderer, -32.29, -20.58, -30.09, -20.53,
                                -29.28, -19.43);
    rr_renderer_bezier_curve_to(renderer, -28.89, -18.91, -28.88, -18.20,
                                -29.25, -17.48);
    rr_renderer_bezier_curve_to(renderer, -29.62, -16.75, -30.35, -16.07,
                                -31.26, -15.57);
    rr_renderer_bezier_curve_to(renderer, -33.17, -14.54, -35.37, -14.59,
                                -36.18, -15.69);
    rr_renderer_bezier_curve_to(renderer, -37.00, -16.78, -36.11, -18.51,
                                -34.20, -19.55);
    rr_renderer_fill(renderer);
    rr_renderer_set_fill(renderer, 0xff262626);
    rr_renderer_begin_path(renderer);
    rr_renderer_move_to(renderer, 69.83, -75.95);
    rr_renderer_bezier_curve_to(renderer, 76.15, -67.36, 58.17, -47.84, 29.67,
                                -32.37);
    rr_renderer_bezier_curve_to(renderer, 1.17, -16.90, -27.05, -11.32, -33.37,
                                -19.92);
    rr_renderer_bezier_curve_to(renderer, 2.40, -35.71, 37.88, -54.97, 69.83,
                                -75.95);
    rr_renderer_fill(renderer);
    rr_renderer_set_fill(renderer, 0xff262626);
    rr_renderer_begin_path(renderer);
    rr_renderer_move_to(renderer, 72.03, -75.33);
    rr_renderer_bezier_curve_to(renderer, 77.73, -67.58, 58.72, -48.46, 29.58,
                                -32.64);
    rr_renderer_bezier_curve_to(renderer, 0.43, -16.82, -27.82, -10.27, -33.51,
                                -18.03);
    rr_renderer_bezier_curve_to(renderer, -17.41, -20.94, 3.70, -29.02, 24.10,
                                -40.10);
    rr_renderer_bezier_curve_to(renderer, 44.49, -51.17, 62.06, -64.08, 72.03,
                                -75.33);
    rr_renderer_fill(renderer);
}

void rr_hornet_thorax_draw(struct rr_renderer *renderer)
{
    rr_renderer_set_fill(renderer, 0xff363636);
    rr_renderer_begin_path(renderer);
    rr_renderer_move_to(renderer, 0.00, -42.13);
    rr_renderer_bezier_curve_to(renderer, 23.88, -42.13, 43.24, -23.27, 43.24,
                                -0.00);
    rr_renderer_bezier_curve_to(renderer, 43.24, 11.17, 38.68, 21.89, 30.58,
                                29.79);
    rr_renderer_bezier_curve_to(renderer, 22.47, 37.69, 11.47, 42.13, 0.00,
                                42.13);
    rr_renderer_bezier_curve_to(renderer, -23.88, 42.13, -43.24, 23.26, -43.24,
                                -0.00);
    rr_renderer_bezier_curve_to(renderer, -43.24, -23.27, -23.88, -42.13, 0.00,
                                -42.13);
    rr_renderer_fill(renderer);
    rr_renderer_set_fill(renderer, 0xff262626);
    rr_renderer_begin_path(renderer);
    rr_renderer_move_to(renderer, 0.00, -47.80);
    rr_renderer_bezier_curve_to(renderer, 27.10, -47.80, 49.07, -26.40, 49.07,
                                -0.00);
    rr_renderer_bezier_curve_to(renderer, 49.07, 12.68, 43.90, 24.84, 34.70,
                                33.80);
    rr_renderer_bezier_curve_to(renderer, 25.49, 42.77, 13.01, 47.80, 0.00,
                                47.80);
    rr_renderer_bezier_curve_to(renderer, -27.10, 47.80, -49.06, 26.40, -49.06,
                                -0.00);
    rr_renderer_bezier_curve_to(renderer, -49.06, -26.40, -27.10, -47.80, 0.00,
                                -47.80);
    rr_renderer_move_to(renderer, 0.00, -33.71);
    rr_renderer_bezier_curve_to(renderer, -19.31, -33.71, -34.97, -18.62,
                                -34.97, -0.00);
    rr_renderer_bezier_curve_to(renderer, -34.97, 18.61, -19.31, 33.71, 0.00,
                                33.71);
    rr_renderer_bezier_curve_to(renderer, 19.31, 33.71, 34.97, 18.61, 34.97,
                                -0.00);
    rr_renderer_bezier_curve_to(renderer, 34.97, -18.62, 19.31, -33.71, 0.00,
                                -33.71);
    rr_renderer_fill(renderer);
}

void rr_hornet_abdomen_draw(struct rr_renderer *renderer)
{
    rr_renderer_set_fill(renderer, 0xff262626);
    rr_renderer_begin_path(renderer);
    rr_renderer_move_to(renderer, -45.24, 20.06);
    rr_renderer_line_to(renderer, -89.83, -4.81);
    rr_renderer_line_to(renderer, -45.24, -29.69);
    rr_renderer_fill(renderer);
    rr_renderer_set_fill(renderer, 0xff262626);
    rr_renderer_begin_path(renderer);
    rr_renderer_move_to(renderer, -45.24, 29.14);
    rr_renderer_line_to(renderer, -89.83, 4.27);
    rr_renderer_line_to(renderer, -45.24, -20.61);
    rr_renderer_fill(renderer);
    rr_renderer_set_fill(renderer, 0xff262626);
    rr_renderer_begin_path(renderer);
    rr_renderer_move_to(renderer, -86.04, -5.70);
    rr_renderer_bezier_curve_to(renderer, -82.17, -5.70, -79.03, -3.27, -79.03,
                                -0.28);
    rr_renderer_bezier_curve_to(renderer, -79.03, 1.16, -79.77, 2.54, -81.08,
                                3.56);
    rr_renderer_bezier_curve_to(renderer, -82.40, 4.57, -84.18, 5.14, -86.04,
                                5.14);
    rr_renderer_bezier_curve_to(renderer, -89.91, 5.14, -93.05, 2.72, -93.05,
                                -0.28);
    rr_renderer_bezier_curve_to(renderer, -93.05, -3.27, -89.91, -5.70, -86.04,
                                -5.70);
    rr_renderer_fill(renderer);
    rr_renderer_set_fill(renderer, 0xffcdb124);
    rr_renderer_begin_path(renderer);
    rr_renderer_move_to(renderer, 13.37, -42.64);
    rr_renderer_bezier_curve_to(renderer, 51.67, -42.64, 82.72, -23.43, 82.72,
                                0.28);
    rr_renderer_bezier_curve_to(renderer, 82.72, 11.66, 75.41, 22.57, 62.41,
                                30.62);
    rr_renderer_bezier_curve_to(renderer, 49.40, 38.67, 31.76, 43.19, 13.37,
                                43.19);
    rr_renderer_bezier_curve_to(renderer, -24.93, 43.19, -55.98, 23.98, -55.98,
                                0.28);
    rr_renderer_bezier_curve_to(renderer, -55.98, -23.43, -24.93, -42.64, 13.37,
                                -42.64);
    rr_renderer_fill(renderer);
    rr_renderer_set_fill(renderer, 0xff262626);
    rr_renderer_begin_path(renderer);
    rr_renderer_move_to(renderer, 3.23, 44.24);
    rr_renderer_bezier_curve_to(renderer, -14.56, 44.24, -28.98, 24.57, -28.98,
                                0.30);
    rr_renderer_bezier_curve_to(renderer, -28.98, -23.97, -14.56, -43.65, 3.23,
                                -43.65);
    rr_renderer_bezier_curve_to(renderer, -10.22, -36.81, -19.14, -19.29,
                                -19.14, 0.30);
    rr_renderer_bezier_curve_to(renderer, -19.14, 19.88, -10.22, 37.40, 3.23,
                                44.24);
    rr_renderer_fill(renderer);
    rr_renderer_set_fill(renderer, 0xff262626);
    rr_renderer_begin_path(renderer);
    rr_renderer_move_to(renderer, -15.90, 44.24);
    rr_renderer_bezier_curve_to(renderer, -31.74, 44.24, -44.57, 24.57, -44.57,
                                0.30);
    rr_renderer_bezier_curve_to(renderer, -44.57, -23.97, -31.74, -43.65,
                                -15.90, -43.65);
    rr_renderer_bezier_curve_to(renderer, -27.87, -36.81, -35.81, -19.29,
                                -35.81, 0.30);
    rr_renderer_bezier_curve_to(renderer, -35.81, 19.88, -27.87, 37.40, -15.90,
                                44.24);
    rr_renderer_fill(renderer);
    rr_renderer_set_fill(renderer, 0xff262626);
    rr_renderer_begin_path(renderer);
    rr_renderer_move_to(renderer, -5.26, -41.90);
    rr_renderer_line_to(renderer, -14.99, -30.63);
    rr_renderer_line_to(renderer, -19.49, -16.54);
    rr_renderer_line_to(renderer, -22.11, 2.61);
    rr_renderer_line_to(renderer, -37.47, 2.05);
    rr_renderer_line_to(renderer, -34.85, -19.92);
    rr_renderer_line_to(renderer, -29.60, -37.95);
    rr_renderer_line_to(renderer, -17.99, -45.84);
    rr_renderer_fill(renderer);
    rr_renderer_set_fill(renderer, 0xff262626);
    rr_renderer_begin_path(renderer);
    rr_renderer_move_to(renderer, -5.26, 42.49);
    rr_renderer_line_to(renderer, -14.99, 31.22);
    rr_renderer_line_to(renderer, -19.49, 17.14);
    rr_renderer_line_to(renderer, -22.11, -2.02);
    rr_renderer_line_to(renderer, -37.47, -1.45);
    rr_renderer_line_to(renderer, -34.85, 20.52);
    rr_renderer_line_to(renderer, -29.60, 38.55);
    rr_renderer_line_to(renderer, -17.99, 46.44);
    rr_renderer_fill(renderer);
    rr_renderer_set_fill(renderer, 0xff262626);
    rr_renderer_begin_path(renderer);
    rr_renderer_move_to(renderer, 43.97, 45.59);
    rr_renderer_bezier_curve_to(renderer, 24.59, 45.59, 8.88, 25.07, 8.88,
                                -0.25);
    rr_renderer_bezier_curve_to(renderer, 8.88, -25.57, 24.59, -46.10, 43.97,
                                -46.10);
    rr_renderer_bezier_curve_to(renderer, 29.32, -38.96, 19.60, -20.68, 19.60,
                                -0.25);
    rr_renderer_bezier_curve_to(renderer, 19.60, 20.18, 29.32, 38.46, 43.97,
                                45.59);
    rr_renderer_fill(renderer);
    rr_renderer_set_fill(renderer, 0xff262626);
    rr_renderer_begin_path(renderer);
    rr_renderer_move_to(renderer, 23.13, 45.59);
    rr_renderer_bezier_curve_to(renderer, 5.88, 45.59, -8.10, 25.07, -8.10,
                                -0.25);
    rr_renderer_bezier_curve_to(renderer, -8.10, -25.57, 5.88, -46.10, 23.13,
                                -46.10);
    rr_renderer_bezier_curve_to(renderer, 10.09, -38.96, 1.44, -20.68, 1.44,
                                -0.25);
    rr_renderer_bezier_curve_to(renderer, 1.44, 20.18, 10.09, 38.46, 23.13,
                                45.59);
    rr_renderer_fill(renderer);
    rr_renderer_set_fill(renderer, 0xff262626);
    rr_renderer_begin_path(renderer);
    rr_renderer_move_to(renderer, 34.72, -44.27);
    rr_renderer_line_to(renderer, 24.12, -32.52);
    rr_renderer_line_to(renderer, 19.22, -17.82);
    rr_renderer_line_to(renderer, 16.36, 2.16);
    rr_renderer_line_to(renderer, -0.36, 1.58);
    rr_renderer_line_to(renderer, 2.49, -21.35);
    rr_renderer_line_to(renderer, 8.20, -40.16);
    rr_renderer_line_to(renderer, 20.85, -48.39);
    rr_renderer_fill(renderer);
    rr_renderer_set_fill(renderer, 0xff262626);
    rr_renderer_begin_path(renderer);
    rr_renderer_move_to(renderer, 34.72, 43.77);
    rr_renderer_line_to(renderer, 24.12, 32.01);
    rr_renderer_line_to(renderer, 19.22, 17.32);
    rr_renderer_line_to(renderer, 16.36, -2.67);
    rr_renderer_line_to(renderer, -0.36, -2.08);
    rr_renderer_line_to(renderer, 2.49, 20.85);
    rr_renderer_line_to(renderer, 8.20, 39.66);
    rr_renderer_line_to(renderer, 20.85, 47.88);
    rr_renderer_fill(renderer);
    rr_renderer_set_fill(renderer, 0xffa68e1a);
    rr_renderer_begin_path(renderer);
    rr_renderer_move_to(renderer, 13.37, -53.25);
    rr_renderer_bezier_curve_to(renderer, 57.07, -53.25, 92.50, -29.28, 92.50,
                                0.27);
    rr_renderer_bezier_curve_to(renderer, 92.50, 14.47, 84.16, 28.08, 69.32,
                                38.11);
    rr_renderer_bezier_curve_to(renderer, 54.48, 48.15, 34.35, 53.79, 13.37,
                                53.79);
    rr_renderer_bezier_curve_to(renderer, -30.34, 53.79, -65.76, 29.83, -65.76,
                                0.27);
    rr_renderer_bezier_curve_to(renderer, -65.76, -29.28, -30.34, -53.25, 13.37,
                                -53.25);
    rr_renderer_move_to(renderer, 13.37, -39.35);
    rr_renderer_bezier_curve_to(renderer, -22.66, -39.35, -51.87, -21.61,
                                -51.87, 0.27);
    rr_renderer_bezier_curve_to(renderer, -51.87, 22.16, -22.66, 39.90, 13.37,
                                39.90);
    rr_renderer_bezier_curve_to(renderer, 49.40, 39.90, 78.60, 22.16, 78.60,
                                0.27);
    rr_renderer_bezier_curve_to(renderer, 78.60, -21.61, 49.40, -39.35, 13.37,
                                -39.35);
    rr_renderer_fill(renderer);
}

void rr_hornet_leg_draw(struct rr_renderer *renderer)
{
    rr_renderer_set_fill(renderer, 0xff262626);
    rr_renderer_begin_path(renderer);
    rr_renderer_move_to(renderer, 35.89, -7.20);
    rr_renderer_bezier_curve_to(renderer, 39.86, -7.20, 43.09, -3.97, 43.09,
                                0.00);
    rr_renderer_bezier_curve_to(renderer, 43.09, 1.91, 42.33, 3.74, 40.98,
                                5.09);
    rr_renderer_bezier_curve_to(renderer, 39.63, 6.44, 37.80, 7.20, 35.89,
                                7.20);
    rr_renderer_line_to(renderer, -35.89, 7.20);
    rr_renderer_bezier_curve_to(renderer, -39.87, 7.20, -43.09, 3.98, -43.09,
                                0.00);
    rr_renderer_bezier_curve_to(renderer, -43.09, -3.97, -39.87, -7.20, -35.89,
                                -7.20);
    rr_renderer_fill(renderer);
}

void rr_hornet_wing_draw(struct rr_renderer *renderer)
{
    rr_renderer_set_fill(renderer, 0x99c6831c);
    rr_renderer_begin_path(renderer);
    rr_renderer_move_to(renderer, 0.00, 29.42);
    rr_renderer_bezier_curve_to(renderer, -43.43, 29.42, -78.64, 16.25, -78.64,
                                0.00);
    rr_renderer_bezier_curve_to(renderer, -78.64, -7.80, -70.36, -15.28, -55.61,
                                -20.80);
    rr_renderer_bezier_curve_to(renderer, -40.86, -26.32, -20.86, -29.42, 0.00,
                                -29.42);
    rr_renderer_bezier_curve_to(renderer, 43.44, -29.42, 78.65, -16.25, 78.65,
                                0.00);
    rr_renderer_bezier_curve_to(renderer, 78.65, 16.25, 43.44, 29.42, 0.00,
                                29.42);
    rr_renderer_fill(renderer);
}