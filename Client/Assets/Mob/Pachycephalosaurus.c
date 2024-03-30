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

void rr_pachycephalosaurus_body_draw(struct rr_renderer *renderer)
{
    rr_renderer_set_fill(renderer, 0xffb29f84);
    rr_renderer_begin_path(renderer);
    rr_renderer_move_to(renderer, -20.55, -65.46);
    rr_renderer_bezier_curve_to(renderer, 39.29, -65.46, 87.80, -36.15, 87.80,
                                -0.01);
    rr_renderer_bezier_curve_to(renderer, 87.80, 17.35, 76.39, 34.00, 56.07,
                                46.27);
    rr_renderer_bezier_curve_to(renderer, 35.75, 58.55, 8.19, 65.44, -20.55,
                                65.44);
    rr_renderer_bezier_curve_to(renderer, -80.39, 65.44, -128.90, 36.14,
                                -128.90, -0.01);
    rr_renderer_bezier_curve_to(renderer, -128.90, -36.15, -80.39, -65.46,
                                -20.55, -65.46);
    rr_renderer_fill(renderer);
    rr_renderer_set_fill(renderer, 0xff9f8e76);
    rr_renderer_begin_path(renderer);
    rr_renderer_move_to(renderer, -20.56, -74.28);
    rr_renderer_bezier_curve_to(renderer, 47.35, -74.28, 102.41, -41.02, 102.41,
                                -0.00);
    rr_renderer_bezier_curve_to(renderer, 102.41, 19.70, 89.45, 38.59, 66.39,
                                52.52);
    rr_renderer_bezier_curve_to(renderer, 43.33, 66.45, 12.05, 74.28, -20.56,
                                74.28);
    rr_renderer_bezier_curve_to(renderer, -88.47, 74.28, -143.52, 41.02,
                                -143.52, -0.00);
    rr_renderer_bezier_curve_to(renderer, -143.52, -41.02, -88.47, -74.28,
                                -20.56, -74.28);
    rr_renderer_move_to(renderer, -20.56, -57.42);
    rr_renderer_bezier_curve_to(renderer, -79.16, -57.42, -126.66, -31.71,
                                -126.66, -0.00);
    rr_renderer_bezier_curve_to(renderer, -126.66, 31.71, -79.16, 57.42, -20.56,
                                57.42);
    rr_renderer_bezier_curve_to(renderer, 38.04, 57.42, 85.55, 31.71, 85.55,
                                -0.00);
    rr_renderer_bezier_curve_to(renderer, 85.55, -31.71, 38.04, -57.42, -20.56,
                                -57.42);
    rr_renderer_fill(renderer);
    rr_renderer_set_fill(renderer, 0xff9f8e76);
    rr_renderer_begin_path(renderer);
    rr_renderer_move_to(renderer, 93.78, -49.74);
    rr_renderer_bezier_curve_to(renderer, 121.25, -49.74, 143.52, -27.46,
                                143.52, 0.01);
    rr_renderer_bezier_curve_to(renderer, 143.52, 13.20, 138.28, 25.86, 128.95,
                                35.18);
    rr_renderer_bezier_curve_to(renderer, 119.62, 44.51, 106.97, 49.75, 93.78,
                                49.75);
    rr_renderer_line_to(renderer, 61.60, 49.75);
    rr_renderer_bezier_curve_to(renderer, 34.13, 49.75, 11.86, 27.48, 11.86,
                                0.01);
    rr_renderer_bezier_curve_to(renderer, 11.86, -27.46, 34.13, -49.74, 61.60,
                                -49.74);
    rr_renderer_fill(renderer);
    rr_renderer_set_fill(renderer, 0xffb29f84);
    rr_renderer_begin_path(renderer);
    rr_renderer_move_to(renderer, 92.92, -35.74);
    rr_renderer_bezier_curve_to(renderer, 112.67, -35.74, 128.68, -19.74,
                                128.68, 0.01);
    rr_renderer_bezier_curve_to(renderer, 128.68, 9.49, 124.91, 18.58, 118.20,
                                25.29);
    rr_renderer_bezier_curve_to(renderer, 111.50, 31.99, 102.41, 35.76, 92.92,
                                35.76);
    rr_renderer_line_to(renderer, 32.76, 35.76);
    rr_renderer_bezier_curve_to(renderer, 13.02, 35.76, -2.99, 19.75, -2.99,
                                0.01);
    rr_renderer_bezier_curve_to(renderer, -2.99, -19.74, 13.02, -35.74, 32.76,
                                -35.74);
    rr_renderer_fill(renderer);
    rr_renderer_set_fill(renderer, 0xff9f8e76);
    rr_renderer_begin_path(renderer);
    rr_renderer_move_to(renderer, 17.98, -8.51);
    rr_renderer_bezier_curve_to(renderer, 22.68, -8.51, 26.50, -4.69, 26.50,
                                0.01);
    rr_renderer_bezier_curve_to(renderer, 26.50, 2.27, 25.60, 4.44, 24.00,
                                6.04);
    rr_renderer_bezier_curve_to(renderer, 22.41, 7.64, 20.24, 8.53, 17.98,
                                8.53);
    rr_renderer_line_to(renderer, -100.26, 8.53);
    rr_renderer_bezier_curve_to(renderer, -104.96, 8.53, -108.78, 4.72, -108.78,
                                0.01);
    rr_renderer_bezier_curve_to(renderer, -108.78, -4.69, -104.96, -8.51,
                                -100.26, -8.51);
    rr_renderer_fill(renderer);
}

void rr_pachycephalosaurus_head_draw(struct rr_renderer *renderer)
{
    rr_renderer_set_fill(renderer, 0xff9f8e76);
    rr_renderer_begin_path(renderer);
    rr_renderer_move_to(renderer, 56.39, -31.14);
    rr_renderer_bezier_curve_to(renderer, 73.58, -31.14, 87.52, -17.20, 87.52,
                                -0.01);
    rr_renderer_bezier_curve_to(renderer, 87.52, 8.25, 84.24, 16.17, 78.40,
                                22.00);
    rr_renderer_bezier_curve_to(renderer, 72.57, 27.84, 64.65, 31.12, 56.39,
                                31.12);
    rr_renderer_line_to(renderer, 10.80, 31.12);
    rr_renderer_bezier_curve_to(renderer, -6.39, 31.12, -20.32, 17.18, -20.32,
                                -0.01);
    rr_renderer_bezier_curve_to(renderer, -20.32, -17.20, -6.39, -31.14, 10.80,
                                -31.14);
    rr_renderer_fill(renderer);
    rr_renderer_set_fill(renderer, 0xffb29f84);
    rr_renderer_begin_path(renderer);
    rr_renderer_move_to(renderer, 56.28, -16.24);
    rr_renderer_bezier_curve_to(renderer, 65.25, -16.24, 72.52, -8.97, 72.52,
                                0.00);
    rr_renderer_bezier_curve_to(renderer, 72.52, 4.31, 70.81, 8.44, 67.76,
                                11.48);
    rr_renderer_bezier_curve_to(renderer, 64.72, 14.53, 60.59, 16.24, 56.28,
                                16.24);
    rr_renderer_line_to(renderer, -4.11, 16.24);
    rr_renderer_bezier_curve_to(renderer, -13.08, 16.24, -20.35, 8.97, -20.35,
                                0.00);
    rr_renderer_bezier_curve_to(renderer, -20.35, -8.97, -13.08, -16.24, -4.11,
                                -16.24);
    rr_renderer_fill(renderer);
    rr_renderer_set_fill(renderer, 0xffb29f84);
    rr_renderer_begin_path(renderer);
    rr_renderer_move_to(renderer, 11.23, -33.83);
    rr_renderer_bezier_curve_to(renderer, 5.61, -27.58, 12.16, -18.43, 25.85,
                                -13.39);
    rr_renderer_bezier_curve_to(renderer, 39.54, -8.35, 55.19, -9.33, 60.80,
                                -15.58);
    rr_renderer_bezier_curve_to(renderer, 42.84, -19.68, 25.80, -25.95, 11.23,
                                -33.83);
    rr_renderer_fill(renderer);
    rr_renderer_set_fill(renderer, 0xff9f8e76);
    rr_renderer_begin_path(renderer);
    rr_renderer_move_to(renderer, 13.90, -48.55);
    rr_renderer_bezier_curve_to(renderer, 8.28, -42.30, 14.83, -33.15, 28.52,
                                -28.11);
    rr_renderer_bezier_curve_to(renderer, 42.21, -23.07, 57.86, -24.05, 63.47,
                                -30.30);
    rr_renderer_bezier_curve_to(renderer, 45.51, -34.40, 28.47, -40.68, 13.90,
                                -48.55);
    rr_renderer_fill(renderer);
    rr_renderer_set_fill(renderer, 0xffb29f84);
    rr_renderer_begin_path(renderer);
    rr_renderer_move_to(renderer, 11.23, 33.83);
    rr_renderer_bezier_curve_to(renderer, 5.61, 27.58, 12.16, 18.43, 25.85,
                                13.39);
    rr_renderer_bezier_curve_to(renderer, 39.54, 8.35, 55.19, 9.33, 60.80,
                                15.58);
    rr_renderer_bezier_curve_to(renderer, 42.84, 19.68, 25.80, 25.96, 11.23,
                                33.83);
    rr_renderer_fill(renderer);
    rr_renderer_set_fill(renderer, 0xff9f8e76);
    rr_renderer_begin_path(renderer);
    rr_renderer_move_to(renderer, 13.90, 48.55);
    rr_renderer_bezier_curve_to(renderer, 8.28, 42.30, 14.83, 33.15, 28.52,
                                28.11);
    rr_renderer_bezier_curve_to(renderer, 42.21, 23.07, 57.86, 24.05, 63.47,
                                30.30);
    rr_renderer_bezier_curve_to(renderer, 45.51, 34.40, 28.47, 40.68, 13.90,
                                48.55);
    rr_renderer_fill(renderer);
    rr_renderer_set_fill(renderer, 0xffb2a593);
    rr_renderer_begin_path(renderer);
    rr_renderer_move_to(renderer, -15.41, 61.37);
    rr_renderer_bezier_curve_to(renderer, -50.04, 61.37, -78.11, 33.90, -78.11,
                                0.01);
    rr_renderer_bezier_curve_to(renderer, -78.11, -16.26, -71.50, -31.87,
                                -59.75, -43.38);
    rr_renderer_bezier_curve_to(renderer, -47.99, -54.88, -32.04, -61.35,
                                -15.41, -61.35);
    rr_renderer_bezier_curve_to(renderer, 19.22, -61.35, 47.29, -33.88, 47.29,
                                0.01);
    rr_renderer_bezier_curve_to(renderer, 47.29, 33.90, 19.22, 61.37, -15.41,
                                61.37);
    rr_renderer_fill(renderer);
    rr_renderer_set_fill(renderer, 0xffb2a593);
    rr_renderer_begin_path(renderer);
    rr_renderer_move_to(renderer, -64.95, 22.11);
    rr_renderer_bezier_curve_to(renderer, -77.42, 22.11, -87.52, 12.21, -87.52,
                                0.01);
    rr_renderer_bezier_curve_to(renderer, -87.52, -5.85, -85.14, -11.47, -80.91,
                                -15.62);
    rr_renderer_bezier_curve_to(renderer, -76.68, -19.76, -70.94, -22.09,
                                -64.95, -22.09);
    rr_renderer_bezier_curve_to(renderer, -52.48, -22.09, -42.38, -12.20,
                                -42.38, 0.01);
    rr_renderer_bezier_curve_to(renderer, -42.38, 12.21, -52.48, 22.11, -64.95,
                                22.11);
    rr_renderer_fill(renderer);
    rr_renderer_set_fill(renderer, 0xffcfc1ad);
    rr_renderer_begin_path(renderer);
    rr_renderer_move_to(renderer, 15.97, 30.69);
    rr_renderer_bezier_curve_to(renderer, -1.36, 47.63, -29.46, 47.63, -46.80,
                                30.69);
    rr_renderer_quadratic_curve_to(renderer, -60.30, 17.49, -69.41, -0.00);
    rr_renderer_quadratic_curve_to(renderer, -60.30, -17.49, -46.80, -30.69);
    rr_renderer_bezier_curve_to(renderer, -29.46, -47.64, -1.36, -47.64, 15.97,
                                -30.69);
    rr_renderer_bezier_curve_to(renderer, 33.30, -13.74, 33.30, 13.74, 15.97,
                                30.69);
    rr_renderer_fill(renderer);
    rr_renderer_set_fill(renderer, 0xffb2a593);
    rr_renderer_begin_path(renderer);
    rr_renderer_move_to(renderer, -81.55, 14.94);
    rr_renderer_line_to(renderer, -63.01, 39.69);
    rr_renderer_line_to(renderer, -63.01, 15.75);
    rr_renderer_fill(renderer);
    rr_renderer_set_fill(renderer, 0xffb2a593);
    rr_renderer_begin_path(renderer);
    rr_renderer_move_to(renderer, -81.55, -14.92);
    rr_renderer_line_to(renderer, -63.01, -39.66);
    rr_renderer_line_to(renderer, -63.01, -15.73);
    rr_renderer_fill(renderer);
    rr_renderer_set_fill(renderer, 0xffb2a593);
    rr_renderer_begin_path(renderer);
    rr_renderer_move_to(renderer, -68.48, -18.67);
    rr_renderer_bezier_curve_to(renderer, -57.96, -18.67, -49.44, -10.32,
                                -49.44, -0.01);
    rr_renderer_bezier_curve_to(renderer, -49.44, 4.94, -51.44, 9.69, -55.01,
                                13.19);
    rr_renderer_bezier_curve_to(renderer, -58.58, 16.69, -63.43, 18.65, -68.48,
                                18.65);
    rr_renderer_bezier_curve_to(renderer, -78.99, 18.65, -87.52, 10.30, -87.52,
                                -0.01);
    rr_renderer_bezier_curve_to(renderer, -87.52, -10.32, -78.99, -18.67,
                                -68.48, -18.67);
    rr_renderer_move_to(renderer, -68.48, -6.47);
    rr_renderer_bezier_curve_to(renderer, -72.25, -6.47, -75.32, -3.58, -75.32,
                                -0.01);
    rr_renderer_bezier_curve_to(renderer, -75.32, 3.56, -72.25, 6.45, -68.48,
                                6.45);
    rr_renderer_bezier_curve_to(renderer, -64.70, 6.45, -61.64, 3.56, -61.64,
                                -0.01);
    rr_renderer_bezier_curve_to(renderer, -61.64, -3.58, -64.70, -6.47, -68.48,
                                -6.47);
    rr_renderer_fill(renderer);
    rr_renderer_set_fill(renderer, 0xffb2a593);
    rr_renderer_begin_path(renderer);
    rr_renderer_move_to(renderer, -55.38, 18.93);
    rr_renderer_bezier_curve_to(renderer, -46.56, 18.93, -39.41, 25.94, -39.41,
                                34.59);
    rr_renderer_bezier_curve_to(renderer, -39.41, 38.75, -41.09, 42.73, -44.09,
                                45.67);
    rr_renderer_bezier_curve_to(renderer, -47.08, 48.60, -51.15, 50.25, -55.38,
                                50.25);
    rr_renderer_bezier_curve_to(renderer, -64.20, 50.25, -71.35, 43.24, -71.35,
                                34.59);
    rr_renderer_bezier_curve_to(renderer, -71.35, 25.94, -64.20, 18.93, -55.38,
                                18.93);
    rr_renderer_move_to(renderer, -55.38, 28.73);
    rr_renderer_bezier_curve_to(renderer, -58.78, 28.73, -61.54, 31.36, -61.54,
                                34.59);
    rr_renderer_bezier_curve_to(renderer, -61.54, 37.83, -58.78, 40.45, -55.38,
                                40.45);
    rr_renderer_bezier_curve_to(renderer, -51.98, 40.45, -49.22, 37.83, -49.22,
                                34.59);
    rr_renderer_bezier_curve_to(renderer, -49.22, 31.36, -51.98, 28.73, -55.38,
                                28.73);
    rr_renderer_fill(renderer);
    rr_renderer_set_fill(renderer, 0xffb2a593);
    rr_renderer_begin_path(renderer);
    rr_renderer_move_to(renderer, -55.38, -50.24);
    rr_renderer_bezier_curve_to(renderer, -46.56, -50.24, -39.41, -43.23,
                                -39.41, -34.58);
    rr_renderer_bezier_curve_to(renderer, -39.41, -30.42, -41.09, -26.44,
                                -44.09, -23.50);
    rr_renderer_bezier_curve_to(renderer, -47.08, -20.56, -51.15, -18.91,
                                -55.38, -18.91);
    rr_renderer_bezier_curve_to(renderer, -64.20, -18.91, -71.35, -25.93,
                                -71.35, -34.58);
    rr_renderer_bezier_curve_to(renderer, -71.35, -43.23, -64.20, -50.24,
                                -55.38, -50.24);
    rr_renderer_move_to(renderer, -55.38, -41.61);
    rr_renderer_bezier_curve_to(renderer, -59.44, -41.61, -62.72, -38.46,
                                -62.72, -34.58);
    rr_renderer_bezier_curve_to(renderer, -62.72, -30.69, -59.44, -27.54,
                                -55.38, -27.54);
    rr_renderer_bezier_curve_to(renderer, -51.33, -27.54, -48.04, -30.69,
                                -48.04, -34.58);
    rr_renderer_bezier_curve_to(renderer, -48.04, -38.46, -51.33, -41.61,
                                -55.38, -41.61);
    rr_renderer_fill(renderer);
    rr_renderer_set_fill(renderer, 0xffcfc1ad);
    rr_renderer_begin_path(renderer);
    rr_renderer_move_to(renderer, -61.42, 6.90);
    rr_renderer_bezier_curve_to(renderer, -65.32, 10.71, -71.64, 10.71, -75.54,
                                6.90);
    rr_renderer_quadratic_curve_to(renderer, -78.58, 3.93, -80.63, -0.00);
    rr_renderer_quadratic_curve_to(renderer, -78.58, -3.93, -75.54, -6.90);
    rr_renderer_bezier_curve_to(renderer, -71.64, -10.71, -65.32, -10.71,
                                -61.42, -6.90);
    rr_renderer_bezier_curve_to(renderer, -57.52, -3.09, -57.52, 3.09, -61.42,
                                6.90);
    rr_renderer_fill(renderer);
    rr_renderer_set_fill(renderer, 0xffcfc1ad);
    rr_renderer_begin_path(renderer);
    rr_renderer_move_to(renderer, -49.63, 39.87);
    rr_renderer_bezier_curve_to(renderer, -52.61, 42.78, -57.46, 42.78, -60.44,
                                39.87);
    rr_renderer_quadratic_curve_to(renderer, -62.77, 37.60, -64.34, 34.59);
    rr_renderer_quadratic_curve_to(renderer, -62.77, 31.58, -60.44, 29.31);
    rr_renderer_bezier_curve_to(renderer, -57.46, 26.39, -52.61, 26.39, -49.63,
                                29.31);
    rr_renderer_bezier_curve_to(renderer, -46.64, 32.22, -46.64, 36.95, -49.63,
                                39.87);
    rr_renderer_fill(renderer);
    rr_renderer_set_fill(renderer, 0xffcfc1ad);
    rr_renderer_begin_path(renderer);
    rr_renderer_move_to(renderer, -49.63, -29.30);
    rr_renderer_bezier_curve_to(renderer, -52.61, -26.39, -57.46, -26.39,
                                -60.44, -29.30);
    rr_renderer_quadratic_curve_to(renderer, -62.77, -31.58, -64.34, -34.59);
    rr_renderer_quadratic_curve_to(renderer, -62.77, -37.59, -60.44, -39.87);
    rr_renderer_bezier_curve_to(renderer, -57.46, -42.78, -52.61, -42.78,
                                -49.63, -39.87);
    rr_renderer_bezier_curve_to(renderer, -46.64, -36.95, -46.64, -32.22,
                                -49.63, -29.30);
    rr_renderer_fill(renderer);
}

void rr_pachycephalosaurus_leg1_draw(struct rr_renderer *renderer)
{
    rr_renderer_set_fill(renderer, 0xff9f8e76);
    rr_renderer_begin_path(renderer);
    rr_renderer_move_to(renderer, 47.98, -74.86);
    rr_renderer_bezier_curve_to(renderer, 43.11, -80.94, 39.66, -89.84, 41.45,
                                -91.76);
    rr_renderer_bezier_curve_to(renderer, 43.24, -93.68, 53.49, -89.65, 58.74,
                                -86.38);
    rr_renderer_bezier_curve_to(renderer, 63.99, -83.12, 69.05, -77.35, 72.95,
                                -72.17);
    rr_renderer_bezier_curve_to(renderer, 76.86, -66.98, 82.56, -58.08, 82.17,
                                -55.26);
    rr_renderer_bezier_curve_to(renderer, 81.79, -52.44, 76.35, -52.00, 70.65,
                                -55.26);
    rr_renderer_bezier_curve_to(renderer, 64.95, -58.53, 52.85, -68.77, 47.98,
                                -74.86);
    rr_renderer_fill(renderer);
    rr_renderer_set_fill(renderer, 0xff9f8e76);
    rr_renderer_begin_path(renderer);
    rr_renderer_move_to(renderer, 81.76, -58.17);
    rr_renderer_bezier_curve_to(renderer, 79.14, -61.98, 75.36, -65.19, 69.64,
                                -69.40);
    rr_renderer_bezier_curve_to(renderer, 63.92, -73.60, 54.60, -80.00, 47.45,
                                -83.39);
    rr_renderer_bezier_curve_to(renderer, 40.31, -86.78, 29.19, -89.90, 26.77,
                                -89.72);
    rr_renderer_bezier_curve_to(renderer, 24.35, -89.53, 31.66, -84.04, 32.93,
                                -82.28);
    rr_renderer_bezier_curve_to(renderer, 34.21, -80.53, 34.71, -79.73, 34.44,
                                -79.19);
    rr_renderer_bezier_curve_to(renderer, 34.17, -78.65, 33.94, -78.87, 31.31,
                                -79.06);
    rr_renderer_bezier_curve_to(renderer, 28.69, -79.24, 19.10, -81.79, 18.70,
                                -80.30);
    rr_renderer_bezier_curve_to(renderer, 18.30, -78.81, 24.31, -74.98, 28.91,
                                -70.12);
    rr_renderer_bezier_curve_to(renderer, 33.51, -65.26, 41.39, -57.28, 46.30,
                                -51.13);
    rr_renderer_bezier_curve_to(renderer, 51.22, -44.99, 54.93, -36.94, 58.41,
                                -33.26);
    rr_renderer_bezier_curve_to(renderer, 61.89, -29.59, 63.90, -29.04, 67.18,
                                -29.08);
    rr_renderer_bezier_curve_to(renderer, 70.46, -29.13, 75.05, -30.62, 78.08,
                                -33.54);
    rr_renderer_bezier_curve_to(renderer, 81.11, -36.45, 84.74, -42.45, 85.35,
                                -46.56);
    rr_renderer_bezier_curve_to(renderer, 85.96, -50.66, 84.38, -54.37, 81.76,
                                -58.17);
    rr_renderer_fill(renderer);
    rr_renderer_set_fill(renderer, 0xffb29f84);
    rr_renderer_begin_path(renderer);
    rr_renderer_move_to(renderer, 76.62, -55.74);
    rr_renderer_bezier_curve_to(renderer, 74.40, -58.90, 70.60, -62.38, 66.00,
                                -66.09);
    rr_renderer_bezier_curve_to(renderer, 61.40, -69.79, 53.54, -75.25, 49.03,
                                -77.98);
    rr_renderer_bezier_curve_to(renderer, 44.52, -80.70, 40.51, -82.26, 38.95,
                                -82.43);
    rr_renderer_bezier_curve_to(renderer, 37.38, -82.60, 39.82, -80.09, 39.66,
                                -78.98);
    rr_renderer_bezier_curve_to(renderer, 39.50, -77.86, 38.94, -76.36, 37.98,
                                -75.72);
    rr_renderer_bezier_curve_to(renderer, 37.01, -75.08, 34.99, -75.33, 33.88,
                                -75.12);
    rr_renderer_bezier_curve_to(renderer, 32.77, -74.91, 30.80, -75.48, 31.32,
                                -74.46);
    rr_renderer_bezier_curve_to(renderer, 31.84, -73.44, 34.07, -71.94, 37.01,
                                -69.01);
    rr_renderer_bezier_curve_to(renderer, 39.95, -66.09, 45.29, -61.62, 48.99,
                                -56.90);
    rr_renderer_bezier_curve_to(renderer, 52.68, -52.18, 56.36, -44.33, 59.16,
                                -40.71);
    rr_renderer_bezier_curve_to(renderer, 61.96, -37.09, 63.25, -35.61, 65.77,
                                -35.18);
    rr_renderer_bezier_curve_to(renderer, 68.29, -34.74, 72.03, -36.10, 74.29,
                                -38.10);
    rr_renderer_bezier_curve_to(renderer, 76.55, -40.10, 78.92, -44.21, 79.31,
                                -47.16);
    rr_renderer_bezier_curve_to(renderer, 79.70, -50.10, 78.84, -52.59, 76.62,
                                -55.74);
    rr_renderer_fill(renderer);
    rr_renderer_set_fill(renderer, 0xffb29f84);
    rr_renderer_begin_path(renderer);
    rr_renderer_move_to(renderer, 40.29, -81.00);
    rr_renderer_bezier_curve_to(renderer, 40.55, -82.73, 48.56, -79.08, 49.52,
                                -80.24);
    rr_renderer_bezier_curve_to(renderer, 50.48, -81.39, 44.46, -88.05, 46.06,
                                -87.92);
    rr_renderer_bezier_curve_to(renderer, 47.66, -87.79, 54.00, -85.04, 59.12,
                                -79.47);
    rr_renderer_bezier_curve_to(renderer, 64.25, -73.90, 78.65, -56.09, 76.80,
                                -54.49);
    rr_renderer_bezier_curve_to(renderer, 74.94, -52.89, 54.06, -65.44, 47.98,
                                -69.86);
    rr_renderer_bezier_curve_to(renderer, 41.90, -74.28, 40.04, -79.28, 40.29,
                                -81.00);
    rr_renderer_fill(renderer);
    rr_renderer_set_fill(renderer, 0xffb29f84);
    rr_renderer_begin_path(renderer);
    rr_renderer_move_to(renderer, -44.23, 5.96);
    rr_renderer_bezier_curve_to(renderer, -20.59, 5.96, -1.43, 24.76, -1.43,
                                47.95);
    rr_renderer_bezier_curve_to(renderer, -1.43, 59.08, -5.94, 69.76, -13.97,
                                77.63);
    rr_renderer_bezier_curve_to(renderer, -21.99, 85.50, -32.88, 89.93, -44.23,
                                89.93);
    rr_renderer_bezier_curve_to(renderer, -67.87, 89.93, -87.03, 71.13, -87.03,
                                47.95);
    rr_renderer_bezier_curve_to(renderer, -87.03, 24.76, -67.87, 5.96, -44.23,
                                5.96);
    rr_renderer_fill(renderer);
    rr_renderer_set_fill(renderer, 0xff9f8e76);
    rr_renderer_begin_path(renderer);
    rr_renderer_move_to(renderer, -44.23, 0.31);
    rr_renderer_bezier_curve_to(renderer, -17.41, 0.31, 4.33, 21.64, 4.33,
                                47.95);
    rr_renderer_bezier_curve_to(renderer, 4.33, 60.59, -0.78, 72.70, -9.89,
                                81.64);
    rr_renderer_bezier_curve_to(renderer, -19.00, 90.57, -31.35, 95.59, -44.23,
                                95.59);
    rr_renderer_bezier_curve_to(renderer, -71.06, 95.59, -92.80, 74.26, -92.80,
                                47.95);
    rr_renderer_bezier_curve_to(renderer, -92.80, 21.64, -71.06, 0.31, -44.23,
                                0.31);
    rr_renderer_move_to(renderer, -44.23, 13.53);
    rr_renderer_bezier_curve_to(renderer, -63.76, 13.53, -79.58, 28.94, -79.58,
                                47.95);
    rr_renderer_bezier_curve_to(renderer, -79.58, 66.96, -63.76, 82.37, -44.23,
                                82.37);
    rr_renderer_bezier_curve_to(renderer, -24.71, 82.37, -8.89, 66.96, -8.89,
                                47.95);
    rr_renderer_bezier_curve_to(renderer, -8.89, 28.94, -24.71, 13.53, -44.23,
                                13.53);
    rr_renderer_fill(renderer);
}

void rr_pachycephalosaurus_leg2_draw(struct rr_renderer *renderer)
{
    rr_renderer_set_fill(renderer, 0xff9f8e76);
    rr_renderer_begin_path(renderer);
    rr_renderer_move_to(renderer, 47.98, 74.86);
    rr_renderer_bezier_curve_to(renderer, 43.12, 80.94, 39.66, 89.84, 41.45,
                                91.76);
    rr_renderer_bezier_curve_to(renderer, 43.24, 93.69, 53.49, 89.65, 58.74,
                                86.39);
    rr_renderer_bezier_curve_to(renderer, 63.99, 83.12, 69.05, 77.36, 72.96,
                                72.17);
    rr_renderer_bezier_curve_to(renderer, 76.86, 66.98, 82.56, 58.08, 82.18,
                                55.26);
    rr_renderer_bezier_curve_to(renderer, 81.79, 52.45, 76.35, 52.00, 70.65,
                                55.26);
    rr_renderer_bezier_curve_to(renderer, 64.95, 58.53, 52.85, 68.78, 47.98,
                                74.86);
    rr_renderer_fill(renderer);
    rr_renderer_set_fill(renderer, 0xff9f8e76);
    rr_renderer_begin_path(renderer);
    rr_renderer_move_to(renderer, 81.76, 58.18);
    rr_renderer_bezier_curve_to(renderer, 79.14, 61.98, 75.36, 65.20, 69.64,
                                69.40);
    rr_renderer_bezier_curve_to(renderer, 63.92, 73.60, 54.60, 80.01, 47.46,
                                83.39);
    rr_renderer_bezier_curve_to(renderer, 40.31, 86.78, 29.20, 89.90, 26.78,
                                89.72);
    rr_renderer_bezier_curve_to(renderer, 24.36, 89.54, 31.66, 84.04, 32.94,
                                82.29);
    rr_renderer_bezier_curve_to(renderer, 34.21, 80.53, 34.71, 79.73, 34.44,
                                79.19);
    rr_renderer_bezier_curve_to(renderer, 34.17, 78.66, 33.94, 78.87, 31.32,
                                79.06);
    rr_renderer_bezier_curve_to(renderer, 28.69, 79.25, 19.11, 81.80, 18.70,
                                80.31);
    rr_renderer_bezier_curve_to(renderer, 18.30, 78.82, 24.31, 74.98, 28.91,
                                70.12);
    rr_renderer_bezier_curve_to(renderer, 33.51, 65.26, 41.39, 57.28, 46.30,
                                51.14);
    rr_renderer_bezier_curve_to(renderer, 51.22, 44.99, 54.93, 36.94, 58.41,
                                33.27);
    rr_renderer_bezier_curve_to(renderer, 61.89, 29.59, 63.90, 29.04, 67.18,
                                29.08);
    rr_renderer_bezier_curve_to(renderer, 70.46, 29.13, 75.05, 30.63, 78.08,
                                33.54);
    rr_renderer_bezier_curve_to(renderer, 81.11, 36.45, 84.74, 42.45, 85.35,
                                46.56);
    rr_renderer_bezier_curve_to(renderer, 85.97, 50.66, 84.38, 54.37, 81.76,
                                58.18);
    rr_renderer_fill(renderer);
    rr_renderer_set_fill(renderer, 0xffb29f84);
    rr_renderer_begin_path(renderer);
    rr_renderer_move_to(renderer, 76.62, 55.75);
    rr_renderer_bezier_curve_to(renderer, 74.41, 58.90, 70.60, 62.39, 66.01,
                                66.09);
    rr_renderer_bezier_curve_to(renderer, 61.41, 69.80, 53.54, 75.26, 49.03,
                                77.98);
    rr_renderer_bezier_curve_to(renderer, 44.52, 80.70, 40.51, 82.27, 38.95,
                                82.43);
    rr_renderer_bezier_curve_to(renderer, 37.39, 82.60, 39.83, 80.10, 39.67,
                                78.98);
    rr_renderer_bezier_curve_to(renderer, 39.51, 77.86, 38.95, 76.37, 37.98,
                                75.72);
    rr_renderer_bezier_curve_to(renderer, 37.02, 75.08, 34.99, 75.33, 33.88,
                                75.12);
    rr_renderer_bezier_curve_to(renderer, 32.77, 74.91, 30.80, 75.48, 31.32,
                                74.46);
    rr_renderer_bezier_curve_to(renderer, 31.84, 73.45, 34.07, 71.94, 37.01,
                                69.02);
    rr_renderer_bezier_curve_to(renderer, 39.96, 66.09, 45.30, 61.62, 48.99,
                                56.90);
    rr_renderer_bezier_curve_to(renderer, 52.68, 52.18, 56.36, 44.33, 59.16,
                                40.71);
    rr_renderer_bezier_curve_to(renderer, 61.96, 37.09, 63.25, 35.61, 65.77,
                                35.18);
    rr_renderer_bezier_curve_to(renderer, 68.30, 34.74, 72.04, 36.11, 74.29,
                                38.10);
    rr_renderer_bezier_curve_to(renderer, 76.55, 40.10, 78.92, 44.22, 79.31,
                                47.16);
    rr_renderer_bezier_curve_to(renderer, 79.70, 50.10, 78.84, 52.59, 76.62,
                                55.75);
    rr_renderer_fill(renderer);
    rr_renderer_set_fill(renderer, 0xffb29f84);
    rr_renderer_begin_path(renderer);
    rr_renderer_move_to(renderer, 40.30, 81.01);
    rr_renderer_bezier_curve_to(renderer, 40.55, 82.74, 48.56, 79.09, 49.52,
                                80.24);
    rr_renderer_bezier_curve_to(renderer, 50.48, 81.39, 44.46, 88.05, 46.06,
                                87.92);
    rr_renderer_bezier_curve_to(renderer, 47.66, 87.79, 54.00, 85.04, 59.12,
                                79.47);
    rr_renderer_bezier_curve_to(renderer, 64.25, 73.90, 78.66, 56.10, 76.80,
                                54.50);
    rr_renderer_bezier_curve_to(renderer, 74.94, 52.89, 54.07, 65.45, 47.98,
                                69.87);
    rr_renderer_bezier_curve_to(renderer, 41.90, 74.28, 40.04, 79.28, 40.30,
                                81.01);
    rr_renderer_fill(renderer);
    rr_renderer_set_fill(renderer, 0xffb29f84);
    rr_renderer_begin_path(renderer);
    rr_renderer_move_to(renderer, -44.23, -89.94);
    rr_renderer_bezier_curve_to(renderer, -20.59, -89.94, -1.43, -71.14, -1.43,
                                -47.96);
    rr_renderer_bezier_curve_to(renderer, -1.43, -36.82, -5.94, -26.15, -13.97,
                                -18.27);
    rr_renderer_bezier_curve_to(renderer, -22.00, -10.40, -32.88, -5.98, -44.23,
                                -5.98);
    rr_renderer_bezier_curve_to(renderer, -67.87, -5.98, -87.03, -24.77, -87.03,
                                -47.96);
    rr_renderer_bezier_curve_to(renderer, -87.03, -71.14, -67.87, -89.94,
                                -44.23, -89.94);
    rr_renderer_fill(renderer);
    rr_renderer_set_fill(renderer, 0xff9f8e76);
    rr_renderer_begin_path(renderer);
    rr_renderer_move_to(renderer, -44.23, -95.60);
    rr_renderer_bezier_curve_to(renderer, -17.41, -95.60, 4.33, -74.27, 4.33,
                                -47.95);
    rr_renderer_bezier_curve_to(renderer, 4.33, -35.32, -0.78, -23.20, -9.89,
                                -14.26);
    rr_renderer_bezier_curve_to(renderer, -19.00, -5.33, -31.35, -0.31, -44.23,
                                -0.31);
    rr_renderer_bezier_curve_to(renderer, -71.06, -0.31, -92.80, -21.64, -92.80,
                                -47.95);
    rr_renderer_bezier_curve_to(renderer, -92.80, -74.27, -71.06, -95.60,
                                -44.23, -95.60);
    rr_renderer_move_to(renderer, -44.23, -82.38);
    rr_renderer_bezier_curve_to(renderer, -63.76, -82.38, -79.58, -66.96,
                                -79.58, -47.95);
    rr_renderer_bezier_curve_to(renderer, -79.58, -28.94, -63.76, -13.53,
                                -44.23, -13.53);
    rr_renderer_bezier_curve_to(renderer, -24.71, -13.53, -8.89, -28.94, -8.89,
                                -47.95);
    rr_renderer_bezier_curve_to(renderer, -8.89, -66.96, -24.71, -82.38, -44.23,
                                -82.38);
    rr_renderer_fill(renderer);
}

void rr_pachycephalosaurus_tail_draw(struct rr_renderer *renderer)
{
    rr_renderer_set_fill(renderer, 0xff9f8e76);
    rr_renderer_begin_path(renderer);
    rr_renderer_move_to(renderer, 65.62, 51.73);
    rr_renderer_line_to(renderer, -129.19, 16.14);
    rr_renderer_line_to(renderer, -129.19, -16.13);
    rr_renderer_line_to(renderer, 65.62, -51.73);
    rr_renderer_fill(renderer);
    rr_renderer_set_fill(renderer, 0xff9f8e76);
    rr_renderer_begin_path(renderer);
    rr_renderer_move_to(renderer, 80.03, -53.25);
    rr_renderer_bezier_curve_to(renderer, 116.76, -53.25, 146.54, -29.41,
                                146.54, 0.00);
    rr_renderer_bezier_curve_to(renderer, 146.54, 14.12, 139.53, 27.67, 127.06,
                                37.65);
    rr_renderer_bezier_curve_to(renderer, 114.59, 47.64, 97.67, 53.25, 80.03,
                                53.25);
    rr_renderer_bezier_curve_to(renderer, 43.30, 53.25, 13.52, 29.41, 13.52,
                                0.00);
    rr_renderer_bezier_curve_to(renderer, 13.52, -29.41, 43.30, -53.25, 80.03,
                                -53.25);
    rr_renderer_fill(renderer);
    rr_renderer_set_fill(renderer, 0xff9f8e76);
    rr_renderer_begin_path(renderer);
    rr_renderer_move_to(renderer, 80.05, -36.87);
    rr_renderer_bezier_curve_to(renderer, 105.47, -36.87, 126.08, -20.37,
                                126.08, -0.01);
    rr_renderer_bezier_curve_to(renderer, 126.08, 9.76, 121.23, 19.14, 112.60,
                                26.05);
    rr_renderer_bezier_curve_to(renderer, 103.97, 32.96, 92.26, 36.84, 80.05,
                                36.84);
    rr_renderer_bezier_curve_to(renderer, 54.62, 36.84, 34.01, 20.34, 34.01,
                                -0.01);
    rr_renderer_bezier_curve_to(renderer, 34.01, -20.37, 54.62, -36.87, 80.05,
                                -36.87);
    rr_renderer_fill(renderer);
    rr_renderer_set_fill(renderer, 0xff9f8e76);
    rr_renderer_begin_path(renderer);
    rr_renderer_move_to(renderer, -126.23, -16.27);
    rr_renderer_bezier_curve_to(renderer, -115.01, -16.27, -105.92, -8.99,
                                -105.92, -0.01);
    rr_renderer_bezier_curve_to(renderer, -105.92, 4.31, -108.06, 8.44, -111.87,
                                11.49);
    rr_renderer_bezier_curve_to(renderer, -115.68, 14.54, -120.84, 16.25,
                                -126.23, 16.25);
    rr_renderer_bezier_curve_to(renderer, -137.45, 16.25, -146.54, 8.97,
                                -146.54, -0.01);
    rr_renderer_bezier_curve_to(renderer, -146.54, -8.99, -137.45, -16.27,
                                -126.23, -16.27);
    rr_renderer_fill(renderer);
    rr_renderer_set_fill(renderer, 0xff9f8e76);
    rr_renderer_begin_path(renderer);
    rr_renderer_move_to(renderer, 67.76, 35.50);
    rr_renderer_line_to(renderer, -128.88, -0.01);
    rr_renderer_line_to(renderer, 67.76, -35.52);
    rr_renderer_fill(renderer);
    rr_renderer_set_fill(renderer, 0xffb29f84);
    rr_renderer_begin_path(renderer);
    rr_renderer_move_to(renderer, 80.08, -36.94);
    rr_renderer_bezier_curve_to(renderer, 105.50, -36.94, 126.11, -20.44,
                                126.11, -0.09);
    rr_renderer_bezier_curve_to(renderer, 126.11, 9.68, 121.26, 19.05, 112.63,
                                25.96);
    rr_renderer_bezier_curve_to(renderer, 104.00, 32.87, 92.29, 36.75, 80.08,
                                36.75);
    rr_renderer_bezier_curve_to(renderer, 54.66, 36.75, 34.05, 20.26, 34.05,
                                -0.09);
    rr_renderer_bezier_curve_to(renderer, 34.05, -20.44, 54.66, -36.94, 80.08,
                                -36.94);
    rr_renderer_fill(renderer);
    rr_renderer_set_fill(renderer, 0xffb29f84);
    rr_renderer_begin_path(renderer);
    rr_renderer_move_to(renderer, 67.79, 35.42);
    rr_renderer_line_to(renderer, -128.83, -0.09);
    rr_renderer_line_to(renderer, 67.79, -35.59);
    rr_renderer_fill(renderer);
}