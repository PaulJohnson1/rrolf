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

void rr_spider_head_draw(struct rr_renderer *renderer)
{
    rr_renderer_set_fill(renderer, 0xff1e242a);
    rr_renderer_begin_path(renderer);
    rr_renderer_move_to(renderer, 27.74, 48.23);
    rr_renderer_bezier_curve_to(renderer, 29.96, 52.69, 40.02, 50.02, 49.13,
                                46.93);
    rr_renderer_bezier_curve_to(renderer, 58.25, 43.84, 73.93, 36.97, 82.44,
                                29.70);
    rr_renderer_bezier_curve_to(renderer, 90.95, 22.44, 98.45, 7.68, 100.19,
                                3.35);
    rr_renderer_bezier_curve_to(renderer, 101.92, -0.98, 95.54, 3.41, 92.86,
                                3.72);
    rr_renderer_bezier_curve_to(renderer, 90.18, 4.02, 88.30, 5.25, 84.09,
                                5.18);
    rr_renderer_bezier_curve_to(renderer, 79.87, 5.11, 73.10, 2.73, 67.57,
                                3.28);
    rr_renderer_bezier_curve_to(renderer, 62.05, 3.83, 56.25, 5.66, 50.96,
                                8.48);
    rr_renderer_bezier_curve_to(renderer, 45.67, 11.30, 39.70, 13.58, 35.83,
                                20.20);
    rr_renderer_bezier_curve_to(renderer, 31.96, 26.83, 25.52, 43.78, 27.74,
                                48.23);
    rr_renderer_fill(renderer);
    rr_renderer_set_fill(renderer, 0xff1e242a);
    rr_renderer_begin_path(renderer);
    rr_renderer_move_to(renderer, 27.74, -48.22);
    rr_renderer_bezier_curve_to(renderer, 29.96, -52.67, 40.02, -50.00, 49.13,
                                -46.92);
    rr_renderer_bezier_curve_to(renderer, 58.25, -43.83, 73.93, -36.95, 82.44,
                                -29.69);
    rr_renderer_bezier_curve_to(renderer, 90.95, -22.42, 98.45, -7.67, 100.19,
                                -3.34);
    rr_renderer_bezier_curve_to(renderer, 101.92, 0.99, 95.54, -3.40, 92.86,
                                -3.70);
    rr_renderer_bezier_curve_to(renderer, 90.18, -4.00, 88.30, -5.23, 84.09,
                                -5.16);
    rr_renderer_bezier_curve_to(renderer, 79.88, -5.09, 73.10, -2.72, 67.57,
                                -3.27);
    rr_renderer_bezier_curve_to(renderer, 62.05, -3.82, 56.25, -5.65, 50.96,
                                -8.47);
    rr_renderer_bezier_curve_to(renderer, 45.67, -11.29, 39.70, -13.56, 35.83,
                                -20.19);
    rr_renderer_bezier_curve_to(renderer, 31.96, -26.81, 25.52, -43.76, 27.74,
                                -48.22);
    rr_renderer_fill(renderer);
    rr_renderer_set_fill(renderer, 0xff484848);
    rr_renderer_begin_path(renderer);
    rr_renderer_move_to(renderer, -11.39, -87.36);
    rr_renderer_bezier_curve_to(renderer, 37.79, -87.36, 77.67, -48.26, 77.67,
                                -0.02);
    rr_renderer_bezier_curve_to(renderer, 77.67, 23.15, 68.28, 45.36, 51.58,
                                61.74);
    rr_renderer_bezier_curve_to(renderer, 34.88, 78.12, 12.23, 87.33, -11.39,
                                87.33);
    rr_renderer_bezier_curve_to(renderer, -60.58, 87.33, -100.45, 48.22,
                                -100.45, -0.02);
    rr_renderer_bezier_curve_to(renderer, -100.45, -48.26, -60.58, -87.36,
                                -11.39, -87.36);
    rr_renderer_move_to(renderer, -11.39, -63.12);
    rr_renderer_bezier_curve_to(renderer, -47.19, -63.12, -76.21, -34.87,
                                -76.21, -0.02);
    rr_renderer_bezier_curve_to(renderer, -76.21, 34.83, -47.19, 63.09, -11.39,
                                63.09);
    rr_renderer_bezier_curve_to(renderer, 24.41, 63.09, 53.43, 34.83, 53.43,
                                -0.02);
    rr_renderer_bezier_curve_to(renderer, 53.43, -34.87, 24.41, -63.12, -11.39,
                                -63.12);
    rr_renderer_fill(renderer);
    rr_renderer_set_fill(renderer, 0xff2d353e);
    rr_renderer_begin_path(renderer);
    rr_renderer_move_to(renderer, -11.41, -87.36);
    rr_renderer_bezier_curve_to(renderer, 37.79, -87.36, 77.67, -48.25, 77.67,
                                -0.00);
    rr_renderer_bezier_curve_to(renderer, 77.67, 23.17, 68.28, 45.39, 51.58,
                                61.77);
    rr_renderer_bezier_curve_to(renderer, 34.87, 78.16, 12.22, 87.36, -11.41,
                                87.36);
    rr_renderer_bezier_curve_to(renderer, -60.60, 87.36, -100.48, 48.25,
                                -100.48, -0.00);
    rr_renderer_bezier_curve_to(renderer, -100.48, -48.25, -60.60, -87.36,
                                -11.41, -87.36);
    rr_renderer_move_to(renderer, -11.41, -41.29);
    rr_renderer_bezier_curve_to(renderer, -35.16, -41.29, -54.41, -22.80,
                                -54.41, -0.00);
    rr_renderer_bezier_curve_to(renderer, -54.41, 22.80, -35.16, 41.29, -11.41,
                                41.29);
    rr_renderer_bezier_curve_to(renderer, 12.34, 41.29, 31.59, 22.80, 31.59,
                                -0.00);
    rr_renderer_bezier_curve_to(renderer, 31.59, -22.80, 12.34, -41.29, -11.41,
                                -41.29);
    rr_renderer_fill(renderer);
    rr_renderer_set_fill(renderer, 0xff37424c);
    rr_renderer_begin_path(renderer);
    rr_renderer_move_to(renderer, -11.41, -59.98);
    rr_renderer_bezier_curve_to(renderer, 22.36, -59.98, 49.73, -33.13, 49.73,
                                0.00);
    rr_renderer_bezier_curve_to(renderer, 49.73, 15.91, 43.29, 31.17, 31.82,
                                42.42);
    rr_renderer_bezier_curve_to(renderer, 20.36, 53.66, 4.81, 59.98, -11.41,
                                59.98);
    rr_renderer_bezier_curve_to(renderer, -45.18, 59.98, -72.55, 33.13, -72.55,
                                0.00);
    rr_renderer_bezier_curve_to(renderer, -72.55, -33.13, -45.18, -59.98,
                                -11.41, -59.98);
    rr_renderer_fill(renderer);
}

void rr_spider_abdomen_draw(struct rr_renderer *renderer)
{
    rr_renderer_set_fill(renderer, 0xff37424c);
    rr_renderer_begin_path(renderer);
    rr_renderer_move_to(renderer, 0.00, -83.43);
    rr_renderer_bezier_curve_to(renderer, 46.98, -83.43, 85.06, -46.08, 85.06,
                                0.00);
    rr_renderer_bezier_curve_to(renderer, 85.06, 22.13, 76.09, 43.35, 60.14,
                                59.00);
    rr_renderer_bezier_curve_to(renderer, 44.19, 74.64, 22.56, 83.43, 0.00,
                                83.43);
    rr_renderer_bezier_curve_to(renderer, -46.97, 83.43, -85.05, 46.08, -85.05,
                                0.00);
    rr_renderer_bezier_curve_to(renderer, -85.05, -46.08, -46.97, -83.43, 0.00,
                                -83.43);
    rr_renderer_fill(renderer);
    rr_renderer_set_fill(renderer, 0xff2d353e);
    rr_renderer_begin_path(renderer);
    rr_renderer_move_to(renderer, -0.00, -111.88);
    rr_renderer_bezier_curve_to(renderer, 62.99, -111.88, 114.06, -61.79,
                                114.06, -0.00);
    rr_renderer_bezier_curve_to(renderer, 114.06, 29.67, 102.05, 58.13, 80.65,
                                79.11);
    rr_renderer_bezier_curve_to(renderer, 59.26, 100.09, 30.25, 111.87, -0.00,
                                111.87);
    rr_renderer_bezier_curve_to(renderer, -63.00, 111.87, -114.06, 61.79,
                                -114.06, -0.00);
    rr_renderer_bezier_curve_to(renderer, -114.06, -61.79, -63.00, -111.88,
                                -0.00, -111.88);
    rr_renderer_move_to(renderer, -0.00, -80.38);
    rr_renderer_bezier_curve_to(renderer, -45.60, -80.38, -82.56, -44.39,
                                -82.56, -0.00);
    rr_renderer_bezier_curve_to(renderer, -82.56, 44.39, -45.60, 80.37, -0.00,
                                80.37);
    rr_renderer_bezier_curve_to(renderer, 45.60, 80.37, 82.56, 44.39, 82.56,
                                -0.00);
    rr_renderer_bezier_curve_to(renderer, 82.56, -44.39, 45.60, -80.38, -0.00,
                                -80.38);
    rr_renderer_fill(renderer);
}

void rr_spider_leg_draw(struct rr_renderer *renderer)
{
    rr_renderer_set_fill(renderer, 0xff1e242a);
    rr_renderer_begin_path(renderer);
    rr_renderer_move_to(renderer, 72.41, -7.47);
    rr_renderer_bezier_curve_to(renderer, 27.37, -27.36, -23.86, -27.85, -69.27,
                                -8.81);
    rr_renderer_line_to(renderer, -59.09, 15.47);
    rr_renderer_bezier_curve_to(renderer, -20.36, -0.77, 23.35, -0.36, 61.78,
                                16.61);
    rr_renderer_fill(renderer);
    rr_renderer_set_fill(renderer, 0xff1e242a);
    rr_renderer_begin_path(renderer);
    rr_renderer_move_to(renderer, 56.21, 13.69);
    rr_renderer_bezier_curve_to(renderer, 61.88, 18.43, 70.33, 17.68, 75.07,
                                12.01);
    rr_renderer_bezier_curve_to(renderer, 77.35, 9.28, 78.45, 5.77, 78.14,
                                2.23);
    rr_renderer_bezier_curve_to(renderer, 77.82, -1.31, 76.11, -4.57, 73.39,
                                -6.85);
    rr_renderer_bezier_curve_to(renderer, 67.72, -11.60, 59.27, -10.84, 54.53,
                                -5.17);
    rr_renderer_bezier_curve_to(renderer, 49.79, 0.50, 50.54, 8.95, 56.21,
                                13.69);
    rr_renderer_fill(renderer);
    rr_renderer_set_fill(renderer, 0xff1e242a);
    rr_renderer_begin_path(renderer);
    rr_renderer_move_to(renderer, -72.00, 13.11);
    rr_renderer_bezier_curve_to(renderer, -66.33, 17.86, -57.89, 17.11, -53.14,
                                11.43);
    rr_renderer_bezier_curve_to(renderer, -50.86, 8.71, -49.76, 5.19, -50.08,
                                1.65);
    rr_renderer_bezier_curve_to(renderer, -50.39, -1.88, -52.10, -5.15, -54.82,
                                -7.43);
    rr_renderer_bezier_curve_to(renderer, -60.50, -12.17, -68.94, -11.42,
                                -73.68, -5.75);
    rr_renderer_bezier_curve_to(renderer, -78.43, -0.07, -77.67, 8.37, -72.00,
                                13.11);
    rr_renderer_fill(renderer);
}
