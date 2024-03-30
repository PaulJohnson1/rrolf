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

void rr_pectinodon_body_draw(struct rr_renderer *renderer)
{
    rr_renderer_set_fill(renderer, 0xff635248);
    rr_renderer_begin_path(renderer);
    rr_renderer_move_to(renderer, -31.41, -73.71);
    rr_renderer_bezier_curve_to(renderer, 35.06, -73.71, 88.95, -40.71, 88.95,
                                -0.01);
    rr_renderer_bezier_curve_to(renderer, 88.95, 19.54, 76.27, 38.29, 53.70,
                                52.11);
    rr_renderer_bezier_curve_to(renderer, 31.12, 65.93, 0.51, 73.69, -31.41,
                                73.69);
    rr_renderer_bezier_curve_to(renderer, -97.87, 73.69, -151.76, 40.70,
                                -151.76, -0.01);
    rr_renderer_bezier_curve_to(renderer, -151.76, -40.71, -97.87, -73.71,
                                -31.41, -73.71);
    rr_renderer_fill(renderer);
    rr_renderer_set_fill(renderer, 0xff54453c);
    rr_renderer_begin_path(renderer);
    rr_renderer_move_to(renderer, -31.42, -83.64);
    rr_renderer_bezier_curve_to(renderer, 44.02, -83.64, 105.17, -46.19, 105.17,
                                0.00);
    rr_renderer_bezier_curve_to(renderer, 105.17, 22.18, 90.78, 43.46, 65.16,
                                59.14);
    rr_renderer_bezier_curve_to(renderer, 39.55, 74.83, 4.81, 83.64, -31.42,
                                83.64);
    rr_renderer_bezier_curve_to(renderer, -106.85, 83.64, -168.00, 46.19,
                                -168.00, 0.00);
    rr_renderer_bezier_curve_to(renderer, -168.00, -46.19, -106.85, -83.64,
                                -31.42, -83.64);
    rr_renderer_move_to(renderer, -31.42, -64.65);
    rr_renderer_bezier_curve_to(renderer, -96.37, -64.65, -149.02, -35.71,
                                -149.02, 0.00);
    rr_renderer_bezier_curve_to(renderer, -149.02, 35.71, -96.37, 64.66, -31.42,
                                64.66);
    rr_renderer_bezier_curve_to(renderer, 33.53, 64.66, 86.18, 35.71, 86.18,
                                0.00);
    rr_renderer_bezier_curve_to(renderer, 86.18, -35.71, 33.53, -64.65, -31.42,
                                -64.65);
    rr_renderer_fill(renderer);
    rr_renderer_set_fill(renderer, 0xff54453c);
    rr_renderer_begin_path(renderer);
    rr_renderer_move_to(renderer, 114.29, -53.85);
    rr_renderer_bezier_curve_to(renderer, 143.95, -53.85, 168.00, -29.80,
                                168.00, -0.14);
    rr_renderer_bezier_curve_to(renderer, 168.00, 14.11, 162.34, 27.77, 152.27,
                                37.84);
    rr_renderer_bezier_curve_to(renderer, 142.19, 47.92, 128.53, 53.58, 114.29,
                                53.58);
    rr_renderer_line_to(renderer, 47.62, 53.58);
    rr_renderer_bezier_curve_to(renderer, 17.96, 53.58, -6.09, 29.53, -6.09,
                                -0.14);
    rr_renderer_bezier_curve_to(renderer, -6.09, -29.80, 17.96, -53.85, 47.62,
                                -53.85);
    rr_renderer_fill(renderer);
    rr_renderer_set_fill(renderer, 0xff635248);
    rr_renderer_begin_path(renderer);
    rr_renderer_move_to(renderer, 110.87, -38.74);
    rr_renderer_bezier_curve_to(renderer, 132.19, -38.74, 149.47, -21.46,
                                149.47, -0.14);
    rr_renderer_bezier_curve_to(renderer, 149.47, 10.10, 145.40, 19.92, 138.16,
                                27.16);
    rr_renderer_bezier_curve_to(renderer, 130.92, 34.40, 121.10, 38.47, 110.87,
                                38.47);
    rr_renderer_line_to(renderer, 13.98, 38.47);
    rr_renderer_bezier_curve_to(renderer, -7.34, 38.47, -24.62, 21.18, -24.62,
                                -0.14);
    rr_renderer_bezier_curve_to(renderer, -24.62, -21.46, -7.34, -38.74, 13.98,
                                -38.74);
    rr_renderer_fill(renderer);
}

void rr_pectinodon_head_draw(struct rr_renderer *renderer)
{
    rr_renderer_set_fill(renderer, 0xff54453c);
    rr_renderer_begin_path(renderer);
    rr_renderer_move_to(renderer, 11.36, 44.87);
    rr_renderer_bezier_curve_to(renderer, 4.00, 35.26, -10.16, 34.22, -20.28,
                                42.54);
    rr_renderer_bezier_curve_to(renderer, -30.40, 50.86, -32.64, 65.39, -25.29,
                                75.00);
    rr_renderer_bezier_curve_to(renderer, -15.48, 62.21, -2.89, 51.86, 11.36,
                                44.87);
    rr_renderer_fill(renderer);
    rr_renderer_set_fill(renderer, 0xff54453c);
    rr_renderer_begin_path(renderer);
    rr_renderer_move_to(renderer, -35.63, 79.56);
    rr_renderer_bezier_curve_to(renderer, -27.65, 79.56, -21.18, 72.85, -21.18,
                                64.57);
    rr_renderer_bezier_curve_to(renderer, -21.18, 60.60, -22.71, 56.78, -25.41,
                                53.97);
    rr_renderer_bezier_curve_to(renderer, -28.12, 51.16, -31.80, 49.58, -35.63,
                                49.58);
    rr_renderer_bezier_curve_to(renderer, -43.60, 49.58, -50.07, 56.29, -50.07,
                                64.57);
    rr_renderer_bezier_curve_to(renderer, -50.07, 72.85, -43.60, 79.56, -35.63,
                                79.56);
    rr_renderer_fill(renderer);
    rr_renderer_set_fill(renderer, 0xff54453c);
    rr_renderer_begin_path(renderer);
    rr_renderer_move_to(renderer, -33.25, 79.08);
    rr_renderer_bezier_curve_to(renderer, -22.22, 74.62, -21.24, 49.71, -31.07,
                                23.46);
    rr_renderer_bezier_curve_to(renderer, -40.90, -2.80, -57.81, -20.47, -68.85,
                                -16.01);
    rr_renderer_bezier_curve_to(renderer, -79.88, -11.55, -80.85, 13.36, -71.02,
                                39.61);
    rr_renderer_bezier_curve_to(renderer, -61.20, 65.87, -44.28, 83.54, -33.25,
                                79.08);
    rr_renderer_fill(renderer);
    rr_renderer_set_fill(renderer, 0xff54453c);
    rr_renderer_begin_path(renderer);
    rr_renderer_move_to(renderer, 11.37, -44.87);
    rr_renderer_bezier_curve_to(renderer, 4.01, -35.26, -10.15, -34.22, -20.27,
                                -42.54);
    rr_renderer_bezier_curve_to(renderer, -30.39, -50.86, -32.63, -65.39,
                                -25.28, -75.00);
    rr_renderer_bezier_curve_to(renderer, -15.47, -62.21, -2.88, -51.86, 11.37,
                                -44.87);
    rr_renderer_fill(renderer);
    rr_renderer_set_fill(renderer, 0xff54453c);
    rr_renderer_begin_path(renderer);
    rr_renderer_move_to(renderer, -35.62, -79.56);
    rr_renderer_bezier_curve_to(renderer, -27.64, -79.56, -21.18, -72.85,
                                -21.18, -64.57);
    rr_renderer_bezier_curve_to(renderer, -21.18, -60.60, -22.70, -56.78,
                                -25.40, -53.97);
    rr_renderer_bezier_curve_to(renderer, -28.11, -51.16, -31.79, -49.58,
                                -35.62, -49.58);
    rr_renderer_bezier_curve_to(renderer, -43.59, -49.58, -50.06, -56.29,
                                -50.06, -64.57);
    rr_renderer_bezier_curve_to(renderer, -50.06, -72.85, -43.59, -79.56,
                                -35.62, -79.56);
    rr_renderer_fill(renderer);
    rr_renderer_set_fill(renderer, 0xff54453c);
    rr_renderer_begin_path(renderer);
    rr_renderer_move_to(renderer, -33.24, -79.08);
    rr_renderer_bezier_curve_to(renderer, -22.21, -74.62, -21.24, -49.71,
                                -31.06, -23.46);
    rr_renderer_bezier_curve_to(renderer, -40.89, 2.80, -57.80, 20.47, -68.84,
                                16.01);
    rr_renderer_bezier_curve_to(renderer, -79.87, 11.55, -80.84, -13.36, -71.02,
                                -39.61);
    rr_renderer_bezier_curve_to(renderer, -61.19, -65.87, -44.28, -83.54,
                                -33.24, -79.08);
    rr_renderer_fill(renderer);
    rr_renderer_set_fill(renderer, 0xff6e6356);
    rr_renderer_begin_path(renderer);
    rr_renderer_move_to(renderer, 60.39, -28.42);
    rr_renderer_bezier_curve_to(renderer, 76.09, -28.42, 88.82, -15.70, 88.82,
                                0.00);
    rr_renderer_bezier_curve_to(renderer, 88.82, 7.54, 85.83, 14.77, 80.50,
                                20.10);
    rr_renderer_bezier_curve_to(renderer, 75.16, 25.43, 67.93, 28.43, 60.39,
                                28.43);
    rr_renderer_bezier_curve_to(renderer, 44.70, 28.43, 31.97, 15.70, 31.97,
                                0.00);
    rr_renderer_bezier_curve_to(renderer, 31.97, -15.70, 44.70, -28.42, 60.39,
                                -28.42);
    rr_renderer_fill(renderer);
    rr_renderer_set_fill(renderer, 0xff635248);
    rr_renderer_begin_path(renderer);
    rr_renderer_move_to(renderer, -21.91, -49.55);
    rr_renderer_bezier_curve_to(renderer, 6.30, -49.55, 29.16, -27.37, 29.16,
                                -0.01);
    rr_renderer_bezier_curve_to(renderer, 29.16, 13.12, 23.78, 25.73, 14.20,
                                35.02);
    rr_renderer_bezier_curve_to(renderer, 4.62, 44.31, -8.37, 49.53, -21.91,
                                49.53);
    rr_renderer_bezier_curve_to(renderer, -50.12, 49.53, -72.98, 27.35, -72.98,
                                -0.01);
    rr_renderer_bezier_curve_to(renderer, -72.98, -27.37, -50.12, -49.55,
                                -21.91, -49.55);
    rr_renderer_fill(renderer);
    rr_renderer_set_fill(renderer, 0xff54453c);
    rr_renderer_begin_path(renderer);
    rr_renderer_move_to(renderer, -21.94, -54.27);
    rr_renderer_bezier_curve_to(renderer, 8.95, -54.27, 33.98, -29.98, 33.98,
                                -0.02);
    rr_renderer_bezier_curve_to(renderer, 33.98, 14.36, 28.09, 28.16, 17.60,
                                38.33);
    rr_renderer_bezier_curve_to(renderer, 7.12, 48.51, -7.11, 54.22, -21.94,
                                54.22);
    rr_renderer_bezier_curve_to(renderer, -52.82, 54.22, -77.86, 29.94, -77.86,
                                -0.02);
    rr_renderer_bezier_curve_to(renderer, -77.86, -29.98, -52.82, -54.27,
                                -21.94, -54.27);
    rr_renderer_move_to(renderer, -21.94, -39.22);
    rr_renderer_bezier_curve_to(renderer, -44.51, -39.22, -62.81, -21.67,
                                -62.81, -0.02);
    rr_renderer_bezier_curve_to(renderer, -62.81, 21.62, -44.51, 39.17, -21.94,
                                39.17);
    rr_renderer_bezier_curve_to(renderer, 0.63, 39.17, 18.93, 21.62, 18.93,
                                -0.02);
    rr_renderer_bezier_curve_to(renderer, 18.93, -21.67, 0.63, -39.22, -21.94,
                                -39.22);
    rr_renderer_fill(renderer);
    rr_renderer_set_fill(renderer, 0xff635248);
    rr_renderer_begin_path(renderer);
    rr_renderer_move_to(renderer, -35.44, 65.30);
    rr_renderer_bezier_curve_to(renderer, -51.39, 65.28, -64.32, 36.04, -64.32,
                                -0.02);
    rr_renderer_bezier_curve_to(renderer, -64.32, -36.07, -51.39, -65.28,
                                -35.44, -65.26);
    rr_renderer_bezier_curve_to(renderer, -42.72, -23.31, -42.72, 23.33, -35.44,
                                65.30);
    rr_renderer_fill(renderer);
    rr_renderer_set_fill(renderer, 0xff6e6356);
    rr_renderer_begin_path(renderer);
    rr_renderer_move_to(renderer, 10.40, -45.02);
    rr_renderer_line_to(renderer, 65.46, -27.99);
    rr_renderer_line_to(renderer, 65.46, 28.00);
    rr_renderer_line_to(renderer, 10.40, 45.03);
    rr_renderer_fill(renderer);
    rr_renderer_set_fill(renderer, 0xff827566);
    rr_renderer_begin_path(renderer);
    rr_renderer_move_to(renderer, -0.39, -34.78);
    rr_renderer_line_to(renderer, 65.46, -15.10);
    rr_renderer_line_to(renderer, 65.46, 15.10);
    rr_renderer_line_to(renderer, -0.39, 34.78);
    rr_renderer_fill(renderer);
    rr_renderer_set_fill(renderer, 0xff635248);
    rr_renderer_begin_path(renderer);
    rr_renderer_move_to(renderer, 3.07, -33.07);
    rr_renderer_bezier_curve_to(renderer, -7.10, -20.77, -23.95, -17.87, -34.56,
                                -26.59);
    rr_renderer_bezier_curve_to(renderer, -45.18, -35.31, -45.54, -52.36,
                                -35.37, -64.66);
    rr_renderer_bezier_curve_to(renderer, -25.83, -50.58, -12.61, -39.72, 3.07,
                                -33.07);
    rr_renderer_fill(renderer);
    rr_renderer_set_fill(renderer, 0xff635248);
    rr_renderer_begin_path(renderer);
    rr_renderer_move_to(renderer, 3.07, 33.07);
    rr_renderer_bezier_curve_to(renderer, -7.10, 20.77, -23.95, 17.87, -34.56,
                                26.59);
    rr_renderer_bezier_curve_to(renderer, -45.18, 35.31, -45.54, 52.36, -35.37,
                                64.66);
    rr_renderer_bezier_curve_to(renderer, -25.83, 50.58, -12.61, 39.73, 3.07,
                                33.07);
    rr_renderer_fill(renderer);
    rr_renderer_set_fill(renderer, 0xff635248);
    rr_renderer_begin_path(renderer);
    rr_renderer_move_to(renderer, 23.61, -13.81);
    rr_renderer_bezier_curve_to(renderer, 31.24, -13.81, 37.42, -7.62, 37.42,
                                0.00);
    rr_renderer_bezier_curve_to(renderer, 37.42, 3.66, 35.97, 7.18, 33.38,
                                9.77);
    rr_renderer_bezier_curve_to(renderer, 30.79, 12.35, 27.28, 13.81, 23.61,
                                13.81);
    rr_renderer_line_to(renderer, -16.62, 13.81);
    rr_renderer_bezier_curve_to(renderer, -24.25, 13.81, -30.43, 7.63, -30.43,
                                0.00);
    rr_renderer_bezier_curve_to(renderer, -30.43, -7.62, -24.25, -13.81, -16.62,
                                -13.81);
    rr_renderer_fill(renderer);
    rr_renderer_set_fill(renderer, 0xff54453c);
    rr_renderer_begin_path(renderer);
    rr_renderer_move_to(renderer, 8.99, 31.14);
    rr_renderer_bezier_curve_to(renderer, 12.92, 31.14, 16.10, 34.32, 16.10,
                                38.25);
    rr_renderer_bezier_curve_to(renderer, 16.10, 40.14, 15.35, 41.95, 14.02,
                                43.28);
    rr_renderer_bezier_curve_to(renderer, 12.68, 44.62, 10.87, 45.37, 8.99,
                                45.37);
    rr_renderer_bezier_curve_to(renderer, 5.06, 45.37, 1.87, 42.18, 1.87,
                                38.25);
    rr_renderer_bezier_curve_to(renderer, 1.87, 34.32, 5.06, 31.14, 8.99,
                                31.14);
    rr_renderer_fill(renderer);
    rr_renderer_set_fill(renderer, 0xff54453c);
    rr_renderer_begin_path(renderer);
    rr_renderer_move_to(renderer, 8.99, -30.58);
    rr_renderer_bezier_curve_to(renderer, 12.92, -30.58, 16.10, -33.89, 16.10,
                                -37.97);
    rr_renderer_bezier_curve_to(renderer, 16.10, -39.93, 15.35, -41.81, 14.02,
                                -43.20);
    rr_renderer_bezier_curve_to(renderer, 12.68, -44.59, 10.87, -45.37, 8.99,
                                -45.37);
    rr_renderer_bezier_curve_to(renderer, 5.06, -45.37, 1.87, -42.06, 1.87,
                                -37.97);
    rr_renderer_bezier_curve_to(renderer, 1.87, -33.89, 5.06, -30.58, 8.99,
                                -30.58);
    rr_renderer_fill(renderer);
    rr_renderer_set_fill(renderer, 0xff635248);
    rr_renderer_begin_path(renderer);
    rr_renderer_move_to(renderer, 11.23, 31.58);
    rr_renderer_bezier_curve_to(renderer, -1.09, 23.99, -8.63, 13.88, -5.62,
                                8.99);
    rr_renderer_bezier_curve_to(renderer, -2.60, 4.10, 9.84, 6.28, 22.16,
                                13.87);
    rr_renderer_bezier_curve_to(renderer, 9.75, 13.61, 5.43, 20.62, 11.23,
                                31.58);
    rr_renderer_fill(renderer);
    rr_renderer_set_fill(renderer, 0xff635248);
    rr_renderer_begin_path(renderer);
    rr_renderer_move_to(renderer, 11.27, 31.28);
    rr_renderer_line_to(renderer, -7.13, 37.89);
    rr_renderer_line_to(renderer, -1.38, 21.36);
    rr_renderer_fill(renderer);
    rr_renderer_set_fill(renderer, 0xff635248);
    rr_renderer_begin_path(renderer);
    rr_renderer_move_to(renderer, 11.23, -31.61);
    rr_renderer_bezier_curve_to(renderer, -1.09, -24.02, -8.63, -13.91, -5.62,
                                -9.02);
    rr_renderer_bezier_curve_to(renderer, -2.60, -4.13, 9.84, -6.31, 22.16,
                                -13.90);
    rr_renderer_bezier_curve_to(renderer, 9.75, -13.64, 5.43, -20.65, 11.23,
                                -31.61);
    rr_renderer_fill(renderer);
    rr_renderer_set_fill(renderer, 0xff635248);
    rr_renderer_begin_path(renderer);
    rr_renderer_move_to(renderer, 11.27, -31.31);
    rr_renderer_line_to(renderer, -7.13, -37.92);
    rr_renderer_line_to(renderer, -1.38, -21.39);
    rr_renderer_fill(renderer);
    rr_renderer_set_fill(renderer, 0xff827566);
    rr_renderer_begin_path(renderer);
    rr_renderer_move_to(renderer, 60.39, -15.86);
    rr_renderer_bezier_curve_to(renderer, 69.16, -15.86, 76.26, -8.76, 76.26,
                                0.00);
    rr_renderer_bezier_curve_to(renderer, 76.26, 4.21, 74.59, 8.24, 71.61,
                                11.22);
    rr_renderer_bezier_curve_to(renderer, 68.64, 14.19, 64.60, 15.86, 60.39,
                                15.86);
    rr_renderer_bezier_curve_to(renderer, 51.63, 15.86, 44.53, 8.76, 44.53,
                                0.00);
    rr_renderer_bezier_curve_to(renderer, 44.53, -8.76, 51.63, -15.86, 60.39,
                                -15.86);
    rr_renderer_fill(renderer);
    rr_renderer_set_fill(renderer, 0xff54453c);
    rr_renderer_begin_path(renderer);
    rr_renderer_move_to(renderer, -31.43, -42.16);
    rr_renderer_bezier_curve_to(renderer, -19.96, -49.77, -5.60, -51.60, 7.41,
                                -47.09);
    rr_renderer_line_to(renderer, 2.97, -34.29);
    rr_renderer_bezier_curve_to(renderer, -6.04, -37.41, -15.99, -36.15, -23.93,
                                -30.87);
    rr_renderer_fill(renderer);
    rr_renderer_set_fill(renderer, 0xff54453c);
    rr_renderer_begin_path(renderer);
    rr_renderer_move_to(renderer, -26.45, -43.03);
    rr_renderer_bezier_curve_to(renderer, -22.83, -42.31, -20.47, -38.79,
                                -21.19, -35.18);
    rr_renderer_bezier_curve_to(renderer, -21.54, -33.44, -22.56, -31.91,
                                -24.03, -30.92);
    rr_renderer_bezier_curve_to(renderer, -25.50, -29.94, -27.31, -29.58,
                                -29.05, -29.92);
    rr_renderer_bezier_curve_to(renderer, -32.67, -30.64, -35.02, -34.16,
                                -34.30, -37.78);
    rr_renderer_bezier_curve_to(renderer, -33.58, -41.39, -30.06, -43.75,
                                -26.45, -43.03);
    rr_renderer_fill(renderer);
    rr_renderer_set_fill(renderer, 0xff54453c);
    rr_renderer_begin_path(renderer);
    rr_renderer_move_to(renderer, -31.43, 42.16);
    rr_renderer_bezier_curve_to(renderer, -19.96, 49.78, -5.60, 51.60, 7.41,
                                47.10);
    rr_renderer_line_to(renderer, 2.97, 34.30);
    rr_renderer_bezier_curve_to(renderer, -6.04, 37.42, -15.99, 36.15, -23.93,
                                30.88);
    rr_renderer_fill(renderer);
    rr_renderer_set_fill(renderer, 0xff54453c);
    rr_renderer_begin_path(renderer);
    rr_renderer_move_to(renderer, -26.45, 43.03);
    rr_renderer_bezier_curve_to(renderer, -22.83, 42.32, -20.48, 38.80, -21.19,
                                35.18);
    rr_renderer_bezier_curve_to(renderer, -21.54, 33.44, -22.56, 31.91, -24.03,
                                30.93);
    rr_renderer_bezier_curve_to(renderer, -25.51, 29.94, -27.31, 29.58, -29.05,
                                29.93);
    rr_renderer_bezier_curve_to(renderer, -32.67, 30.65, -35.02, 34.16, -34.30,
                                37.78);
    rr_renderer_bezier_curve_to(renderer, -33.58, 41.40, -30.07, 43.75, -26.45,
                                43.03);
    rr_renderer_fill(renderer);
}

void rr_pectinodon_tail_draw(struct rr_renderer *renderer)
{
    rr_renderer_set_fill(renderer, 0xff372d27);
    rr_renderer_begin_path(renderer);
    rr_renderer_move_to(renderer, -128.08, -23.34);
    rr_renderer_bezier_curve_to(renderer, -143.97, -23.34, -156.85, -12.53,
                                -156.85, 0.81);
    rr_renderer_bezier_curve_to(renderer, -156.85, 7.22, -153.82, 13.36,
                                -148.43, 17.89);
    rr_renderer_bezier_curve_to(renderer, -143.03, 22.42, -135.71, 24.96,
                                -128.08, 24.96);
    rr_renderer_bezier_curve_to(renderer, -112.19, 24.96, -99.31, 14.15, -99.31,
                                0.81);
    rr_renderer_bezier_curve_to(renderer, -99.31, -12.53, -112.19, -23.34,
                                -128.08, -23.34);
    rr_renderer_fill(renderer);
    rr_renderer_set_fill(renderer, 0xff372d27);
    rr_renderer_begin_path(renderer);
    rr_renderer_move_to(renderer, -158.24, -7.38);
    rr_renderer_bezier_curve_to(renderer, -163.63, -7.38, -167.99, -3.72,
                                -167.99, 0.81);
    rr_renderer_bezier_curve_to(renderer, -167.99, 2.98, -166.97, 5.06, -165.14,
                                6.60);
    rr_renderer_bezier_curve_to(renderer, -163.31, 8.14, -160.82, 9.00, -158.24,
                                9.00);
    rr_renderer_bezier_curve_to(renderer, -152.85, 9.00, -148.48, 5.33, -148.48,
                                0.81);
    rr_renderer_bezier_curve_to(renderer, -148.48, -3.72, -152.85, -7.38,
                                -158.24, -7.38);
    rr_renderer_fill(renderer);
    rr_renderer_set_fill(renderer, 0xff372d27);
    rr_renderer_begin_path(renderer);
    rr_renderer_move_to(renderer, -146.69, 18.84);
    rr_renderer_line_to(renderer, -164.14, 7.31);
    rr_renderer_line_to(renderer, -154.32, 6.03);
    rr_renderer_fill(renderer);
    rr_renderer_set_fill(renderer, 0xff372d27);
    rr_renderer_begin_path(renderer);
    rr_renderer_move_to(renderer, -146.69, -17.31);
    rr_renderer_line_to(renderer, -164.14, -5.78);
    rr_renderer_line_to(renderer, -154.32, -4.50);
    rr_renderer_fill(renderer);
    rr_renderer_set_fill(renderer, 0xff372d27);
    rr_renderer_begin_path(renderer);
    rr_renderer_move_to(renderer, -112.86, 7.55);
    rr_renderer_bezier_curve_to(renderer, -127.26, 1.91, -133.49, -12.46,
                                -126.78, -24.55);
    rr_renderer_bezier_curve_to(renderer, -123.55, -30.35, -117.71, -34.84,
                                -110.54, -37.03);
    rr_renderer_bezier_curve_to(renderer, -103.37, -39.22, -95.46, -38.93,
                                -88.54, -36.23);
    rr_renderer_bezier_curve_to(renderer, -74.14, -30.59, -67.91, -16.22,
                                -74.63, -4.13);
    rr_renderer_bezier_curve_to(renderer, -81.35, 7.96, -98.46, 13.18, -112.86,
                                7.55);
    rr_renderer_fill(renderer);
    rr_renderer_set_fill(renderer, 0xff372d27);
    rr_renderer_begin_path(renderer);
    rr_renderer_move_to(renderer, -132.15, -17.61);
    rr_renderer_bezier_curve_to(renderer, -137.03, -19.52, -139.14, -24.40,
                                -136.86, -28.50);
    rr_renderer_bezier_curve_to(renderer, -135.76, -30.47, -133.78, -31.99,
                                -131.34, -32.73);
    rr_renderer_bezier_curve_to(renderer, -128.91, -33.47, -126.22, -33.37,
                                -123.88, -32.45);
    rr_renderer_bezier_curve_to(renderer, -119.00, -30.53, -116.89, -25.66,
                                -119.17, -21.56);
    rr_renderer_bezier_curve_to(renderer, -121.46, -17.46, -127.27, -15.69,
                                -132.15, -17.61);
    rr_renderer_fill(renderer);
    rr_renderer_set_fill(renderer, 0xff372d27);
    rr_renderer_begin_path(renderer);
    rr_renderer_move_to(renderer, -108.47, -37.27);
    rr_renderer_line_to(renderer, -130.10, -33.03);
    rr_renderer_line_to(renderer, -121.84, -28.38);
    rr_renderer_fill(renderer);
    rr_renderer_set_fill(renderer, 0xff372d27);
    rr_renderer_begin_path(renderer);
    rr_renderer_move_to(renderer, -126.69, -4.52);
    rr_renderer_line_to(renderer, -136.70, -21.16);
    rr_renderer_line_to(renderer, -127.15, -18.83);
    rr_renderer_fill(renderer);
    rr_renderer_set_fill(renderer, 0xff372d27);
    rr_renderer_begin_path(renderer);
    rr_renderer_move_to(renderer, -83.33, -6.09);
    rr_renderer_bezier_curve_to(renderer, -95.79, -14.36, -97.91, -29.55,
                                -88.05, -40.02);
    rr_renderer_bezier_curve_to(renderer, -83.32, -45.05, -76.40, -48.29,
                                -68.82, -49.03);
    rr_renderer_bezier_curve_to(renderer, -61.23, -49.77, -53.61, -47.96,
                                -47.62, -43.99);
    rr_renderer_bezier_curve_to(renderer, -35.16, -35.71, -33.04, -20.52,
                                -42.90, -10.05);
    rr_renderer_bezier_curve_to(renderer, -52.76, 0.41, -70.86, 2.19, -83.33,
                                -6.09);
    rr_renderer_fill(renderer);
    rr_renderer_set_fill(renderer, 0xff372d27);
    rr_renderer_begin_path(renderer);
    rr_renderer_move_to(renderer, -95.18, -34.30);
    rr_renderer_bezier_curve_to(renderer, -99.42, -37.11, -100.13, -42.27,
                                -96.79, -45.82);
    rr_renderer_bezier_curve_to(renderer, -95.18, -47.53, -92.83, -48.63,
                                -90.25, -48.88);
    rr_renderer_bezier_curve_to(renderer, -87.68, -49.14, -85.09, -48.52,
                                -83.05, -47.17);
    rr_renderer_bezier_curve_to(renderer, -78.82, -44.36, -78.10, -39.20,
                                -81.45, -35.64);
    rr_renderer_bezier_curve_to(renderer, -84.80, -32.09, -90.95, -31.49,
                                -95.18, -34.30);
    rr_renderer_fill(renderer);
    rr_renderer_set_fill(renderer, 0xff372d27);
    rr_renderer_begin_path(renderer);
    rr_renderer_move_to(renderer, -66.77, -48.87);
    rr_renderer_line_to(renderer, -88.97, -48.91);
    rr_renderer_line_to(renderer, -82.21, -42.79);
    rr_renderer_fill(renderer);
    rr_renderer_set_fill(renderer, 0xff372d27);
    rr_renderer_begin_path(renderer);
    rr_renderer_move_to(renderer, -93.47, -20.52);
    rr_renderer_line_to(renderer, -98.65, -38.64);
    rr_renderer_line_to(renderer, -89.99, -34.53);
    rr_renderer_fill(renderer);
    rr_renderer_set_fill(renderer, 0xff372d27);
    rr_renderer_begin_path(renderer);
    rr_renderer_move_to(renderer, -49.06, -16.06);
    rr_renderer_bezier_curve_to(renderer, -61.85, -23.98, -64.57, -39.10,
                                -55.14, -49.84);
    rr_renderer_bezier_curve_to(renderer, -50.61, -55.00, -43.83, -58.43,
                                -36.28, -59.39);
    rr_renderer_bezier_curve_to(renderer, -28.73, -60.35, -21.04, -58.75,
                                -14.90, -54.94);
    rr_renderer_bezier_curve_to(renderer, -2.10, -47.02, 0.62, -31.90, -8.81,
                                -21.16);
    rr_renderer_bezier_curve_to(renderer, -18.25, -10.42, -36.27, -8.14, -49.06,
                                -16.06);
    rr_renderer_fill(renderer);
    rr_renderer_set_fill(renderer, 0xff372d27);
    rr_renderer_begin_path(renderer);
    rr_renderer_move_to(renderer, -62.04, -43.92);
    rr_renderer_bezier_curve_to(renderer, -66.39, -46.61, -67.31, -51.74,
                                -64.10, -55.39);
    rr_renderer_bezier_curve_to(renderer, -62.56, -57.14, -60.26, -58.31,
                                -57.70, -58.63);
    rr_renderer_bezier_curve_to(renderer, -55.13, -58.95, -52.52, -58.41,
                                -50.44, -57.12);
    rr_renderer_bezier_curve_to(renderer, -46.10, -54.43, -45.17, -49.29,
                                -48.38, -45.65);
    rr_renderer_bezier_curve_to(renderer, -51.58, -42.00, -57.70, -41.23,
                                -62.04, -43.92);
    rr_renderer_fill(renderer);
    rr_renderer_set_fill(renderer, 0xff372d27);
    rr_renderer_begin_path(renderer);
    rr_renderer_move_to(renderer, -34.22, -59.28);
    rr_renderer_line_to(renderer, -56.42, -58.70);
    rr_renderer_line_to(renderer, -49.41, -52.77);
    rr_renderer_fill(renderer);
    rr_renderer_set_fill(renderer, 0xff372d27);
    rr_renderer_begin_path(renderer);
    rr_renderer_move_to(renderer, -59.78, -30.19);
    rr_renderer_line_to(renderer, -65.68, -48.16);
    rr_renderer_line_to(renderer, -56.86, -44.29);
    rr_renderer_fill(renderer);
    rr_renderer_set_fill(renderer, 0xff372d27);
    rr_renderer_begin_path(renderer);
    rr_renderer_move_to(renderer, 16.75, -22.88);
    rr_renderer_bezier_curve_to(renderer, 8.45, -30.80, 9.38, -42.87, 18.81,
                                -49.83);
    rr_renderer_bezier_curve_to(renderer, 23.34, -53.17, 29.27, -54.87, 35.29,
                                -54.55);
    rr_renderer_bezier_curve_to(renderer, 41.31, -54.22, 46.93, -51.90, 50.91,
                                -48.10);
    rr_renderer_bezier_curve_to(renderer, 59.21, -40.18, 58.29, -28.12, 48.85,
                                -21.15);
    rr_renderer_bezier_curve_to(renderer, 39.42, -14.19, 25.05, -14.96, 16.75,
                                -22.88);
    rr_renderer_fill(renderer);
    rr_renderer_set_fill(renderer, 0xff372d27);
    rr_renderer_begin_path(renderer);
    rr_renderer_move_to(renderer, 12.30, -46.23);
    rr_renderer_bezier_curve_to(renderer, 9.48, -48.92, 9.79, -53.02, 13.00,
                                -55.39);
    rr_renderer_bezier_curve_to(renderer, 14.54, -56.52, 16.55, -57.10, 18.60,
                                -56.99);
    rr_renderer_bezier_curve_to(renderer, 20.64, -56.88, 22.55, -56.09, 23.90,
                                -54.80);
    rr_renderer_bezier_curve_to(renderer, 26.72, -52.11, 26.40, -48.01, 23.20,
                                -45.64);
    rr_renderer_bezier_curve_to(renderer, 19.99, -43.28, 15.11, -43.54, 12.30,
                                -46.23);
    rr_renderer_fill(renderer);
    rr_renderer_set_fill(renderer, 0xff372d27);
    rr_renderer_begin_path(renderer);
    rr_renderer_move_to(renderer, 36.87, -54.17);
    rr_renderer_line_to(renderer, 19.60, -56.86);
    rr_renderer_line_to(renderer, 23.83, -51.29);
    rr_renderer_fill(renderer);
    rr_renderer_set_fill(renderer, 0xff372d27);
    rr_renderer_begin_path(renderer);
    rr_renderer_move_to(renderer, 11.29, -35.30);
    rr_renderer_line_to(renderer, 10.34, -50.02);
    rr_renderer_line_to(renderer, 16.37, -45.79);
    rr_renderer_fill(renderer);
    rr_renderer_set_fill(renderer, 0xff372d27);
    rr_renderer_begin_path(renderer);
    rr_renderer_move_to(renderer, 42.77, -24.46);
    rr_renderer_bezier_curve_to(renderer, 37.76, -31.58, 40.58, -40.77, 49.07,
                                -44.97);
    rr_renderer_bezier_curve_to(renderer, 57.55, -49.18, 68.50, -46.81, 73.51,
                                -39.69);
    rr_renderer_bezier_curve_to(renderer, 78.52, -32.57, 75.70, -23.38, 67.21,
                                -19.18);
    rr_renderer_bezier_curve_to(renderer, 58.73, -14.97, 47.79, -17.34, 42.77,
                                -24.46);
    rr_renderer_fill(renderer);
    rr_renderer_set_fill(renderer, 0xff372d27);
    rr_renderer_begin_path(renderer);
    rr_renderer_move_to(renderer, 43.42, -43.00);
    rr_renderer_bezier_curve_to(renderer, 41.72, -45.42, 42.68, -48.54, 45.56,
                                -49.96);
    rr_renderer_bezier_curve_to(renderer, 48.44, -51.39, 52.15, -50.58, 53.85,
                                -48.16);
    rr_renderer_bezier_curve_to(renderer, 55.55, -45.75, 54.59, -42.63, 51.71,
                                -41.21);
    rr_renderer_bezier_curve_to(renderer, 48.83, -39.78, 45.12, -40.59, 43.42,
                                -43.00);
    rr_renderer_fill(renderer);
    rr_renderer_set_fill(renderer, 0xff372d27);
    rr_renderer_begin_path(renderer);
    rr_renderer_move_to(renderer, 63.75, -46.09);
    rr_renderer_line_to(renderer, 50.91, -50.29);
    rr_renderer_line_to(renderer, 53.19, -45.48);
    rr_renderer_fill(renderer);
    rr_renderer_set_fill(renderer, 0xff372d27);
    rr_renderer_begin_path(renderer);
    rr_renderer_move_to(renderer, 40.74, -34.70);
    rr_renderer_line_to(renderer, 42.58, -46.16);
    rr_renderer_line_to(renderer, 46.49, -42.15);
    rr_renderer_fill(renderer);
    rr_renderer_set_fill(renderer, 0xff372d27);
    rr_renderer_begin_path(renderer);
    rr_renderer_move_to(renderer, -112.86, -7.54);
    rr_renderer_bezier_curve_to(renderer, -127.26, -1.91, -133.49, 12.46,
                                -126.77, 24.55);
    rr_renderer_bezier_curve_to(renderer, -123.54, 30.35, -117.70, 34.85,
                                -110.53, 37.04);
    rr_renderer_bezier_curve_to(renderer, -103.36, 39.23, -95.45, 38.93, -88.54,
                                36.23);
    rr_renderer_bezier_curve_to(renderer, -74.14, 30.59, -67.91, 16.22, -74.62,
                                4.13);
    rr_renderer_bezier_curve_to(renderer, -81.34, -7.95, -98.46, -13.18,
                                -112.86, -7.54);
    rr_renderer_fill(renderer);
    rr_renderer_set_fill(renderer, 0xff372d27);
    rr_renderer_begin_path(renderer);
    rr_renderer_move_to(renderer, -132.15, 17.61);
    rr_renderer_bezier_curve_to(renderer, -137.03, 19.52, -139.14, 24.40,
                                -136.85, 28.50);
    rr_renderer_bezier_curve_to(renderer, -135.76, 30.47, -133.77, 31.99,
                                -131.34, 32.73);
    rr_renderer_bezier_curve_to(renderer, -128.90, 33.48, -126.22, 33.37,
                                -123.87, 32.45);
    rr_renderer_bezier_curve_to(renderer, -118.99, 30.54, -116.88, 25.66,
                                -119.17, 21.56);
    rr_renderer_bezier_curve_to(renderer, -121.45, 17.46, -127.26, 15.69,
                                -132.15, 17.61);
    rr_renderer_fill(renderer);
    rr_renderer_set_fill(renderer, 0xff372d27);
    rr_renderer_begin_path(renderer);
    rr_renderer_move_to(renderer, -108.47, 37.27);
    rr_renderer_line_to(renderer, -130.09, 33.03);
    rr_renderer_line_to(renderer, -121.83, 28.38);
    rr_renderer_fill(renderer);
    rr_renderer_set_fill(renderer, 0xff372d27);
    rr_renderer_begin_path(renderer);
    rr_renderer_move_to(renderer, -126.68, 4.52);
    rr_renderer_line_to(renderer, -136.69, 21.16);
    rr_renderer_line_to(renderer, -127.14, 18.83);
    rr_renderer_fill(renderer);
    rr_renderer_set_fill(renderer, 0xff372d27);
    rr_renderer_begin_path(renderer);
    rr_renderer_move_to(renderer, -83.32, 6.09);
    rr_renderer_bezier_curve_to(renderer, -95.79, 14.36, -97.90, 29.56, -88.04,
                                40.02);
    rr_renderer_bezier_curve_to(renderer, -83.31, 45.05, -76.39, 48.29, -68.81,
                                49.03);
    rr_renderer_bezier_curve_to(renderer, -61.23, 49.78, -53.61, 47.96, -47.62,
                                43.99);
    rr_renderer_bezier_curve_to(renderer, -35.15, 35.71, -33.04, 20.52, -42.90,
                                10.05);
    rr_renderer_bezier_curve_to(renderer, -52.75, -0.41, -70.85, -2.19, -83.32,
                                6.09);
    rr_renderer_fill(renderer);
    rr_renderer_set_fill(renderer, 0xff372d27);
    rr_renderer_begin_path(renderer);
    rr_renderer_move_to(renderer, -95.18, 34.30);
    rr_renderer_bezier_curve_to(renderer, -99.41, 37.11, -100.13, 42.27, -96.78,
                                45.82);
    rr_renderer_bezier_curve_to(renderer, -95.17, 47.53, -92.82, 48.63, -90.25,
                                48.88);
    rr_renderer_bezier_curve_to(renderer, -87.67, 49.14, -85.08, 48.52, -83.05,
                                47.17);
    rr_renderer_bezier_curve_to(renderer, -78.81, 44.36, -78.10, 39.20, -81.45,
                                35.64);
    rr_renderer_bezier_curve_to(renderer, -84.80, 32.09, -90.94, 31.49, -95.18,
                                34.30);
    rr_renderer_fill(renderer);
    rr_renderer_set_fill(renderer, 0xff372d27);
    rr_renderer_begin_path(renderer);
    rr_renderer_move_to(renderer, -66.76, 48.87);
    rr_renderer_line_to(renderer, -88.96, 48.91);
    rr_renderer_line_to(renderer, -82.20, 42.79);
    rr_renderer_fill(renderer);
    rr_renderer_set_fill(renderer, 0xff372d27);
    rr_renderer_begin_path(renderer);
    rr_renderer_move_to(renderer, -93.46, 20.52);
    rr_renderer_line_to(renderer, -98.64, 38.64);
    rr_renderer_line_to(renderer, -89.99, 34.53);
    rr_renderer_fill(renderer);
    rr_renderer_set_fill(renderer, 0xff372d27);
    rr_renderer_begin_path(renderer);
    rr_renderer_move_to(renderer, -49.05, 16.06);
    rr_renderer_bezier_curve_to(renderer, -61.85, 23.98, -64.57, 39.10, -55.14,
                                49.84);
    rr_renderer_bezier_curve_to(renderer, -50.60, 55.00, -43.82, 58.43, -36.27,
                                59.39);
    rr_renderer_bezier_curve_to(renderer, -28.72, 60.35, -21.03, 58.75, -14.89,
                                54.95);
    rr_renderer_bezier_curve_to(renderer, -2.10, 47.03, 0.62, 31.90, -8.81,
                                21.16);
    rr_renderer_bezier_curve_to(renderer, -18.24, 10.43, -36.26, 8.14, -49.05,
                                16.06);
    rr_renderer_fill(renderer);
    rr_renderer_set_fill(renderer, 0xff372d27);
    rr_renderer_begin_path(renderer);
    rr_renderer_move_to(renderer, -23.09, -21.40);
    rr_renderer_bezier_curve_to(renderer, -33.20, -31.69, -31.46, -46.91,
                                -19.20, -55.40);
    rr_renderer_bezier_curve_to(renderer, -13.31, -59.48, -5.74, -61.42, 1.86,
                                -60.81);
    rr_renderer_bezier_curve_to(renderer, 9.46, -60.20, 16.45, -57.08, 21.31,
                                -52.14);
    rr_renderer_bezier_curve_to(renderer, 31.42, -41.84, 29.68, -26.62, 17.42,
                                -18.13);
    rr_renderer_bezier_curve_to(renderer, 5.16, -9.65, -12.98, -11.11, -23.09,
                                -21.40);
    rr_renderer_fill(renderer);
    rr_renderer_set_fill(renderer, 0xff372d27);
    rr_renderer_begin_path(renderer);
    rr_renderer_move_to(renderer, -27.61, -51.07);
    rr_renderer_bezier_curve_to(renderer, -31.04, -54.57, -30.44, -59.73,
                                -26.28, -62.61);
    rr_renderer_bezier_curve_to(renderer, -24.28, -63.99, -21.71, -64.65,
                                -19.13, -64.45);
    rr_renderer_bezier_curve_to(renderer, -16.56, -64.24, -14.18, -63.18,
                                -12.54, -61.50);
    rr_renderer_bezier_curve_to(renderer, -9.10, -58.01, -9.70, -52.84, -13.86,
                                -49.96);
    rr_renderer_bezier_curve_to(renderer, -18.02, -47.08, -24.18, -47.58,
                                -27.61, -51.07);
    rr_renderer_fill(renderer);
    rr_renderer_set_fill(renderer, 0xff372d27);
    rr_renderer_begin_path(renderer);
    rr_renderer_move_to(renderer, 3.84, -60.28);
    rr_renderer_line_to(renderer, -17.86, -64.25);
    rr_renderer_line_to(renderer, -12.79, -57.07);
    rr_renderer_fill(renderer);
    rr_renderer_set_fill(renderer, 0xff372d27);
    rr_renderer_begin_path(renderer);
    rr_renderer_move_to(renderer, -29.39, -37.28);
    rr_renderer_line_to(renderer, -29.90, -55.92);
    rr_renderer_line_to(renderer, -22.47, -50.37);
    rr_renderer_fill(renderer);
    rr_renderer_set_fill(renderer, 0xff372d27);
    rr_renderer_begin_path(renderer);
    rr_renderer_move_to(renderer, -23.08, 21.40);
    rr_renderer_bezier_curve_to(renderer, -33.19, 31.69, -31.45, 46.92, -19.19,
                                55.40);
    rr_renderer_bezier_curve_to(renderer, -13.31, 59.48, -5.73, 61.42, 1.87,
                                60.81);
    rr_renderer_bezier_curve_to(renderer, 9.46, 60.20, 16.46, 57.08, 21.31,
                                52.14);
    rr_renderer_bezier_curve_to(renderer, 31.43, 41.85, 29.68, 26.62, 17.42,
                                18.14);
    rr_renderer_bezier_curve_to(renderer, 5.16, 9.65, -12.97, 11.11, -23.08,
                                21.40);
    rr_renderer_fill(renderer);
    rr_renderer_set_fill(renderer, 0xff372d27);
    rr_renderer_begin_path(renderer);
    rr_renderer_move_to(renderer, -27.60, 51.07);
    rr_renderer_bezier_curve_to(renderer, -31.03, 54.57, -30.44, 59.73, -26.28,
                                62.61);
    rr_renderer_bezier_curve_to(renderer, -24.28, 64.00, -21.71, 64.66, -19.13,
                                64.45);
    rr_renderer_bezier_curve_to(renderer, -16.55, 64.24, -14.18, 63.18, -12.53,
                                61.50);
    rr_renderer_bezier_curve_to(renderer, -9.10, 58.01, -9.69, 52.84, -13.85,
                                49.96);
    rr_renderer_bezier_curve_to(renderer, -18.02, 47.08, -24.17, 47.58, -27.60,
                                51.07);
    rr_renderer_fill(renderer);
    rr_renderer_set_fill(renderer, 0xff372d27);
    rr_renderer_begin_path(renderer);
    rr_renderer_move_to(renderer, 3.84, 60.28);
    rr_renderer_line_to(renderer, -17.86, 64.25);
    rr_renderer_line_to(renderer, -12.78, 57.07);
    rr_renderer_fill(renderer);
    rr_renderer_set_fill(renderer, 0xff372d27);
    rr_renderer_begin_path(renderer);
    rr_renderer_move_to(renderer, -29.38, 37.29);
    rr_renderer_line_to(renderer, -29.90, 55.92);
    rr_renderer_line_to(renderer, -22.47, 50.37);
    rr_renderer_fill(renderer);
    rr_renderer_set_fill(renderer, 0xff372d27);
    rr_renderer_begin_path(renderer);
    rr_renderer_move_to(renderer, -62.04, 43.92);
    rr_renderer_bezier_curve_to(renderer, -66.38, 46.61, -67.30, 51.75, -64.10,
                                55.39);
    rr_renderer_bezier_curve_to(renderer, -62.56, 57.14, -60.25, 58.31, -57.69,
                                58.63);
    rr_renderer_bezier_curve_to(renderer, -55.13, 58.95, -52.52, 58.41, -50.43,
                                57.12);
    rr_renderer_bezier_curve_to(renderer, -46.09, 54.43, -45.17, 49.29, -48.37,
                                45.65);
    rr_renderer_bezier_curve_to(renderer, -51.58, 42.00, -57.70, 41.23, -62.04,
                                43.92);
    rr_renderer_fill(renderer);
    rr_renderer_set_fill(renderer, 0xff372d27);
    rr_renderer_begin_path(renderer);
    rr_renderer_move_to(renderer, -34.22, 59.28);
    rr_renderer_line_to(renderer, -56.41, 58.70);
    rr_renderer_line_to(renderer, -49.41, 52.77);
    rr_renderer_fill(renderer);
    rr_renderer_set_fill(renderer, 0xff372d27);
    rr_renderer_begin_path(renderer);
    rr_renderer_move_to(renderer, -59.77, 30.19);
    rr_renderer_line_to(renderer, -65.67, 48.16);
    rr_renderer_line_to(renderer, -56.86, 44.29);
    rr_renderer_fill(renderer);
    rr_renderer_set_fill(renderer, 0xff372d27);
    rr_renderer_begin_path(renderer);
    rr_renderer_move_to(renderer, 16.76, 22.88);
    rr_renderer_bezier_curve_to(renderer, 8.46, 30.80, 9.38, 42.87, 18.81,
                                49.83);
    rr_renderer_bezier_curve_to(renderer, 23.35, 53.18, 29.27, 54.87, 35.29,
                                54.55);
    rr_renderer_bezier_curve_to(renderer, 41.31, 54.22, 46.94, 51.90, 50.92,
                                48.10);
    rr_renderer_bezier_curve_to(renderer, 59.22, 40.18, 58.29, 28.12, 48.86,
                                21.15);
    rr_renderer_bezier_curve_to(renderer, 39.43, 14.19, 25.05, 14.96, 16.76,
                                22.88);
    rr_renderer_fill(renderer);
    rr_renderer_set_fill(renderer, 0xff372d27);
    rr_renderer_begin_path(renderer);
    rr_renderer_move_to(renderer, 12.30, 46.24);
    rr_renderer_bezier_curve_to(renderer, 9.48, 48.93, 9.80, 53.02, 13.00,
                                55.39);
    rr_renderer_bezier_curve_to(renderer, 14.54, 56.52, 16.56, 57.10, 18.60,
                                56.99);
    rr_renderer_bezier_curve_to(renderer, 20.65, 56.88, 22.55, 56.09, 23.91,
                                54.80);
    rr_renderer_bezier_curve_to(renderer, 26.72, 52.11, 26.41, 48.01, 23.20,
                                45.65);
    rr_renderer_bezier_curve_to(renderer, 20.00, 43.28, 15.12, 43.55, 12.30,
                                46.24);
    rr_renderer_fill(renderer);
    rr_renderer_set_fill(renderer, 0xff372d27);
    rr_renderer_begin_path(renderer);
    rr_renderer_move_to(renderer, 36.87, 54.18);
    rr_renderer_line_to(renderer, 19.61, 56.86);
    rr_renderer_line_to(renderer, 23.83, 51.29);
    rr_renderer_fill(renderer);
    rr_renderer_set_fill(renderer, 0xff372d27);
    rr_renderer_begin_path(renderer);
    rr_renderer_move_to(renderer, 11.30, 35.31);
    rr_renderer_line_to(renderer, 10.34, 50.02);
    rr_renderer_line_to(renderer, 16.38, 45.79);
    rr_renderer_fill(renderer);
    rr_renderer_set_fill(renderer, 0xff372d27);
    rr_renderer_begin_path(renderer);
    rr_renderer_move_to(renderer, 42.78, 24.46);
    rr_renderer_bezier_curve_to(renderer, 37.77, 31.58, 40.59, 40.77, 49.07,
                                44.97);
    rr_renderer_bezier_curve_to(renderer, 57.56, 49.18, 68.50, 46.81, 73.51,
                                39.69);
    rr_renderer_bezier_curve_to(renderer, 78.52, 32.57, 75.70, 23.38, 67.22,
                                19.18);
    rr_renderer_bezier_curve_to(renderer, 58.73, 14.97, 47.79, 17.34, 42.78,
                                24.46);
    rr_renderer_fill(renderer);
    rr_renderer_set_fill(renderer, 0xff372d27);
    rr_renderer_begin_path(renderer);
    rr_renderer_move_to(renderer, 43.43, 43.01);
    rr_renderer_bezier_curve_to(renderer, 41.73, 45.42, 42.69, 48.54, 45.57,
                                49.96);
    rr_renderer_bezier_curve_to(renderer, 48.45, 51.39, 52.16, 50.58, 53.85,
                                48.16);
    rr_renderer_bezier_curve_to(renderer, 55.55, 45.75, 54.59, 42.63, 51.71,
                                41.21);
    rr_renderer_bezier_curve_to(renderer, 48.83, 39.78, 45.12, 40.59, 43.43,
                                43.01);
    rr_renderer_fill(renderer);
    rr_renderer_set_fill(renderer, 0xff372d27);
    rr_renderer_begin_path(renderer);
    rr_renderer_move_to(renderer, 63.75, 46.09);
    rr_renderer_line_to(renderer, 50.92, 50.29);
    rr_renderer_line_to(renderer, 53.20, 45.48);
    rr_renderer_fill(renderer);
    rr_renderer_set_fill(renderer, 0xff372d27);
    rr_renderer_begin_path(renderer);
    rr_renderer_move_to(renderer, 40.75, 34.70);
    rr_renderer_line_to(renderer, 42.58, 46.16);
    rr_renderer_line_to(renderer, 46.49, 42.16);
    rr_renderer_fill(renderer);
    rr_renderer_set_fill(renderer, 0xff41362f);
    rr_renderer_begin_path(renderer);
    rr_renderer_move_to(renderer, -113.70, -11.31);
    rr_renderer_bezier_curve_to(renderer, -121.64, -17.97, -134.52, -17.97,
                                -142.47, -11.31);
    rr_renderer_quadratic_curve_to(renderer, -150.47, -4.59, -160.10, 0.77);
    rr_renderer_quadratic_curve_to(renderer, -150.47, 6.12, -142.47, 12.84);
    rr_renderer_bezier_curve_to(renderer, -134.52, 19.51, -121.64, 19.51,
                                -113.70, 12.84);
    rr_renderer_bezier_curve_to(renderer, -105.75, 6.18, -105.75, -4.64,
                                -113.70, -11.31);
    rr_renderer_fill(renderer);
    rr_renderer_set_fill(renderer, 0xff41362f);
    rr_renderer_begin_path(renderer);
    rr_renderer_move_to(renderer, -93.78, 1.76);
    rr_renderer_bezier_curve_to(renderer, -104.33, 4.98, -116.00, 0.41, -119.83,
                                -8.45);
    rr_renderer_quadratic_curve_to(renderer, -123.70, -17.38, -129.72, -25.64);
    rr_renderer_quadratic_curve_to(renderer, -118.31, -27.08, -107.67, -30.32);
    rr_renderer_bezier_curve_to(renderer, -97.12, -33.54, -85.45, -28.97,
                                -81.61, -20.11);
    rr_renderer_bezier_curve_to(renderer, -77.78, -11.25, -83.22, -1.46, -93.78,
                                1.76);
    rr_renderer_fill(renderer);
    rr_renderer_set_fill(renderer, 0xff41362f);
    rr_renderer_begin_path(renderer);
    rr_renderer_move_to(renderer, -63.16, -8.03);
    rr_renderer_bezier_curve_to(renderer, -74.31, -6.94, -84.41, -13.65, -85.71,
                                -23.02);
    rr_renderer_quadratic_curve_to(renderer, -87.02, -32.45, -90.62, -41.67);
    rr_renderer_quadratic_curve_to(renderer, -79.11, -40.85, -67.86, -41.95);
    rr_renderer_bezier_curve_to(renderer, -56.71, -43.04, -46.61, -36.33,
                                -45.31, -26.97);
    rr_renderer_bezier_curve_to(renderer, -44.01, -17.60, -52.00, -9.12, -63.16,
                                -8.03);
    rr_renderer_fill(renderer);
    rr_renderer_set_fill(renderer, 0xff41362f);
    rr_renderer_begin_path(renderer);
    rr_renderer_move_to(renderer, -28.99, -18.58);
    rr_renderer_bezier_curve_to(renderer, -40.09, -17.17, -50.46, -23.58,
                                -52.14, -32.90);
    rr_renderer_quadratic_curve_to(renderer, -53.83, -42.30, -57.79, -51.40);
    rr_renderer_quadratic_curve_to(renderer, -46.26, -50.91, -35.07, -52.33);
    rr_renderer_bezier_curve_to(renderer, -23.97, -53.74, -13.60, -47.33,
                                -11.92, -38.01);
    rr_renderer_bezier_curve_to(renderer, -10.25, -28.69, -17.89, -19.99,
                                -28.99, -18.58);
    rr_renderer_fill(renderer);
    rr_renderer_set_fill(renderer, 0xff41362f);
    rr_renderer_begin_path(renderer);
    rr_renderer_move_to(renderer, 32.78, -21.99);
    rr_renderer_bezier_curve_to(renderer, 23.91, -22.47, 17.18, -28.89, 17.75,
                                -36.33);
    rr_renderer_quadratic_curve_to(renderer, 18.33, -43.83, 17.09, -51.43);
    rr_renderer_quadratic_curve_to(renderer, 25.90, -49.42, 34.84, -48.94);
    rr_renderer_bezier_curve_to(renderer, 43.70, -48.46, 50.43, -42.04, 49.86,
                                -34.60);
    rr_renderer_bezier_curve_to(renderer, 49.29, -27.16, 41.64, -21.52, 32.78,
                                -21.99);
    rr_renderer_fill(renderer);
    rr_renderer_set_fill(renderer, 0xff41362f);
    rr_renderer_begin_path(renderer);
    rr_renderer_move_to(renderer, 54.95, -21.79);
    rr_renderer_bezier_curve_to(renderer, 48.21, -23.26, 44.15, -29.03, 45.90,
                                -34.69);
    rr_renderer_quadratic_curve_to(renderer, 47.65, -40.40, 48.03, -46.40);
    rr_renderer_quadratic_curve_to(renderer, 54.47, -43.77, 61.26, -42.29);
    rr_renderer_bezier_curve_to(renderer, 68.01, -40.83, 72.06, -35.06, 70.32,
                                -29.39);
    rr_renderer_bezier_curve_to(renderer, 68.58, -23.73, 61.70, -20.33, 54.95,
                                -21.79);
    rr_renderer_fill(renderer);
    rr_renderer_set_fill(renderer, 0xff41362f);
    rr_renderer_begin_path(renderer);
    rr_renderer_move_to(renderer, -93.77, -1.76);
    rr_renderer_bezier_curve_to(renderer, -104.32, -4.98, -115.99, -0.41,
                                -119.83, 8.45);
    rr_renderer_quadratic_curve_to(renderer, -123.69, 17.38, -129.72, 25.65);
    rr_renderer_quadratic_curve_to(renderer, -118.30, 27.08, -107.67, 30.32);
    rr_renderer_bezier_curve_to(renderer, -97.11, 33.54, -85.45, 28.97, -81.61,
                                20.12);
    rr_renderer_bezier_curve_to(renderer, -77.77, 11.26, -83.22, 1.46, -93.77,
                                -1.76);
    rr_renderer_fill(renderer);
    rr_renderer_set_fill(renderer, 0xff41362f);
    rr_renderer_begin_path(renderer);
    rr_renderer_move_to(renderer, -63.15, 8.03);
    rr_renderer_bezier_curve_to(renderer, -74.31, 6.94, -84.41, 13.65, -85.71,
                                23.02);
    rr_renderer_quadratic_curve_to(renderer, -87.02, 32.46, -90.61, 41.67);
    rr_renderer_quadratic_curve_to(renderer, -79.10, 40.85, -67.86, 41.95);
    rr_renderer_bezier_curve_to(renderer, -56.70, 43.04, -46.60, 36.34, -45.30,
                                26.97);
    rr_renderer_bezier_curve_to(renderer, -44.00, 17.60, -51.99, 9.13, -63.15,
                                8.03);
    rr_renderer_fill(renderer);
    rr_renderer_set_fill(renderer, 0xff41362f);
    rr_renderer_begin_path(renderer);
    rr_renderer_move_to(renderer, -28.98, 18.58);
    rr_renderer_bezier_curve_to(renderer, -40.09, 17.17, -50.45, 23.58, -52.13,
                                32.90);
    rr_renderer_quadratic_curve_to(renderer, -53.82, 42.30, -57.79, 51.40);
    rr_renderer_quadratic_curve_to(renderer, -46.25, 50.91, -35.07, 52.33);
    rr_renderer_bezier_curve_to(renderer, -23.96, 53.74, -13.60, 47.33, -11.92,
                                38.01);
    rr_renderer_bezier_curve_to(renderer, -10.24, 28.69, -17.88, 19.99, -28.98,
                                18.58);
    rr_renderer_fill(renderer);
    rr_renderer_set_fill(renderer, 0xff41362f);
    rr_renderer_begin_path(renderer);
    rr_renderer_move_to(renderer, -2.90, -19.74);
    rr_renderer_bezier_curve_to(renderer, -14.07, -20.64, -22.26, -28.98,
                                -21.19, -38.36);
    rr_renderer_quadratic_curve_to(renderer, -20.11, -47.81, -21.31, -57.45);
    rr_renderer_quadratic_curve_to(renderer, -10.27, -54.62, 0.99, -53.71);
    rr_renderer_bezier_curve_to(renderer, 12.17, -52.81, 20.36, -44.48, 19.28,
                                -35.09);
    rr_renderer_bezier_curve_to(renderer, 18.21, -25.71, 8.28, -18.84, -2.90,
                                -19.74);
    rr_renderer_fill(renderer);
    rr_renderer_set_fill(renderer, 0xff41362f);
    rr_renderer_begin_path(renderer);
    rr_renderer_move_to(renderer, -2.89, 19.74);
    rr_renderer_bezier_curve_to(renderer, -14.07, 20.64, -22.26, 28.98, -21.18,
                                38.36);
    rr_renderer_quadratic_curve_to(renderer, -20.10, 47.82, -21.31, 57.45);
    rr_renderer_quadratic_curve_to(renderer, -10.26, 54.62, 1.00, 53.72);
    rr_renderer_bezier_curve_to(renderer, 12.17, 52.81, 20.36, 44.48, 19.29,
                                35.10);
    rr_renderer_bezier_curve_to(renderer, 18.22, 25.71, 8.28, 18.84, -2.89,
                                19.74);
    rr_renderer_fill(renderer);
    rr_renderer_set_fill(renderer, 0xff41362f);
    rr_renderer_begin_path(renderer);
    rr_renderer_move_to(renderer, 32.78, 21.99);
    rr_renderer_bezier_curve_to(renderer, 23.92, 22.47, 17.19, 28.89, 17.76,
                                36.33);
    rr_renderer_quadratic_curve_to(renderer, 18.33, 43.83, 17.09, 51.43);
    rr_renderer_quadratic_curve_to(renderer, 25.91, 49.42, 34.84, 48.94);
    rr_renderer_bezier_curve_to(renderer, 43.71, 48.47, 50.43, 42.05, 49.86,
                                34.60);
    rr_renderer_bezier_curve_to(renderer, 49.29, 27.16, 41.65, 21.52, 32.78,
                                21.99);
    rr_renderer_fill(renderer);
    rr_renderer_set_fill(renderer, 0xff41362f);
    rr_renderer_begin_path(renderer);
    rr_renderer_move_to(renderer, 54.96, 21.79);
    rr_renderer_bezier_curve_to(renderer, 48.21, 23.26, 44.16, 29.03, 45.90,
                                34.69);
    rr_renderer_quadratic_curve_to(renderer, 47.66, 40.40, 48.03, 46.40);
    rr_renderer_quadratic_curve_to(renderer, 54.47, 43.77, 61.27, 42.29);
    rr_renderer_bezier_curve_to(renderer, 68.01, 40.83, 72.07, 35.06, 70.32,
                                29.40);
    rr_renderer_bezier_curve_to(renderer, 68.58, 23.74, 61.70, 20.33, 54.96,
                                21.79);
    rr_renderer_fill(renderer);
    rr_renderer_set_fill(renderer, 0xff54453c);
    rr_renderer_begin_path(renderer);
    rr_renderer_move_to(renderer, 93.13, 51.83);
    rr_renderer_line_to(renderer, -87.04, 16.17);
    rr_renderer_line_to(renderer, -87.04, -16.15);
    rr_renderer_line_to(renderer, 93.13, -51.80);
    rr_renderer_fill(renderer);
    rr_renderer_set_fill(renderer, 0xff54453c);
    rr_renderer_begin_path(renderer);
    rr_renderer_move_to(renderer, 106.48, -53.31);
    rr_renderer_bezier_curve_to(renderer, 140.45, -53.31, 167.99, -29.43,
                                167.99, 0.02);
    rr_renderer_bezier_curve_to(renderer, 167.99, 14.16, 161.51, 27.73, 149.98,
                                37.73);
    rr_renderer_bezier_curve_to(renderer, 138.44, 47.73, 122.79, 53.35, 106.48,
                                53.35);
    rr_renderer_bezier_curve_to(renderer, 72.51, 53.35, 44.97, 29.47, 44.97,
                                0.02);
    rr_renderer_bezier_curve_to(renderer, 44.97, -29.43, 72.51, -53.31, 106.48,
                                -53.31);
    rr_renderer_fill(renderer);
    rr_renderer_set_fill(renderer, 0xff54453c);
    rr_renderer_begin_path(renderer);
    rr_renderer_move_to(renderer, 106.50, -36.91);
    rr_renderer_bezier_curve_to(renderer, 130.01, -36.91, 149.07, -20.38,
                                149.07, -0.00);
    rr_renderer_bezier_curve_to(renderer, 149.07, 9.79, 144.58, 19.17, 136.60,
                                26.09);
    rr_renderer_bezier_curve_to(renderer, 128.61, 33.01, 117.79, 36.90, 106.50,
                                36.90);
    rr_renderer_bezier_curve_to(renderer, 82.98, 36.90, 63.92, 20.38, 63.92,
                                -0.00);
    rr_renderer_bezier_curve_to(renderer, 63.92, -20.38, 82.98, -36.91, 106.50,
                                -36.91);
    rr_renderer_fill(renderer);
    rr_renderer_set_fill(renderer, 0xff54453c);
    rr_renderer_begin_path(renderer);
    rr_renderer_move_to(renderer, -84.29, -16.28);
    rr_renderer_bezier_curve_to(renderer, -73.92, -16.28, -65.51, -8.98, -65.51,
                                0.01);
    rr_renderer_bezier_curve_to(renderer, -65.51, 4.33, -67.49, 8.47, -71.01,
                                11.53);
    rr_renderer_bezier_curve_to(renderer, -74.54, 14.58, -79.31, 16.30, -84.29,
                                16.30);
    rr_renderer_bezier_curve_to(renderer, -94.67, 16.30, -103.08, 9.01, -103.08,
                                0.01);
    rr_renderer_bezier_curve_to(renderer, -103.08, -8.98, -94.67, -16.28,
                                -84.29, -16.28);
    rr_renderer_fill(renderer);
    rr_renderer_set_fill(renderer, 0xff54453c);
    rr_renderer_begin_path(renderer);
    rr_renderer_move_to(renderer, 95.13, 35.57);
    rr_renderer_line_to(renderer, -86.75, 0.01);
    rr_renderer_line_to(renderer, 95.13, -35.54);
    rr_renderer_fill(renderer);
    rr_renderer_set_fill(renderer, 0xff635248);
    rr_renderer_begin_path(renderer);
    rr_renderer_move_to(renderer, 104.19, -36.96);
    rr_renderer_bezier_curve_to(renderer, 127.70, -36.96, 146.77, -20.44,
                                146.77, -0.05);
    rr_renderer_bezier_curve_to(renderer, 146.77, 9.74, 142.28, 19.12, 134.30,
                                26.04);
    rr_renderer_bezier_curve_to(renderer, 126.31, 32.96, 115.48, 36.85, 104.19,
                                36.85);
    rr_renderer_bezier_curve_to(renderer, 80.67, 36.85, 61.61, 20.33, 61.61,
                                -0.05);
    rr_renderer_bezier_curve_to(renderer, 61.61, -20.44, 80.67, -36.96, 104.19,
                                -36.96);
    rr_renderer_fill(renderer);
    rr_renderer_set_fill(renderer, 0xff635248);
    rr_renderer_begin_path(renderer);
    rr_renderer_move_to(renderer, 92.82, 35.51);
    rr_renderer_line_to(renderer, -89.06, -0.05);
    rr_renderer_line_to(renderer, 92.82, -35.61);
    rr_renderer_fill(renderer);
}

void rr_pectinodon_wing1_draw(struct rr_renderer *renderer)
{
    rr_renderer_set_fill(renderer, 0xff372d27);
    rr_renderer_begin_path(renderer);
    rr_renderer_move_to(renderer, -75.37, -38.98);
    rr_renderer_line_to(renderer, -93.38, -30.72);
    rr_renderer_line_to(renderer, -92.64, -19.38);
    rr_renderer_line_to(renderer, -87.37, -12.89);
    rr_renderer_line_to(renderer, -76.56, -8.39);
    rr_renderer_line_to(renderer, -69.83, -11.90);
    rr_renderer_line_to(renderer, -66.37, -4.40);
    rr_renderer_line_to(renderer, -50.79, 0.04);
    rr_renderer_line_to(renderer, -44.89, -4.86);
    rr_renderer_line_to(renderer, -41.49, 1.74);
    rr_renderer_line_to(renderer, -16.78, 8.61);
    rr_renderer_line_to(renderer, -25.16, 44.86);
    rr_renderer_line_to(renderer, 34.89, -6.61);
    rr_renderer_fill(renderer);
    rr_renderer_set_fill(renderer, 0xff41362f);
    rr_renderer_begin_path(renderer);
    rr_renderer_move_to(renderer, -10.59, 21.86);
    rr_renderer_line_to(renderer, -6.52, 3.70);
    rr_renderer_line_to(renderer, -37.89, -4.70);
    rr_renderer_line_to(renderer, -44.31, -13.62);
    rr_renderer_line_to(renderer, -52.87, -6.96);
    rr_renderer_line_to(renderer, -61.65, -8.92);
    rr_renderer_line_to(renderer, -66.57, -19.86);
    rr_renderer_line_to(renderer, -77.86, -14.26);
    rr_renderer_line_to(renderer, -83.46, -16.93);
    rr_renderer_line_to(renderer, -87.41, -22.18);
    rr_renderer_line_to(renderer, -87.34, -26.93);
    rr_renderer_line_to(renderer, -71.02, -34.98);
    rr_renderer_line_to(renderer, 13.95, -13.34);
    rr_renderer_line_to(renderer, 18.94, -0.79);
    rr_renderer_line_to(renderer, 6.43, 19.50);
    rr_renderer_fill(renderer);
    rr_renderer_set_fill(renderer, 0xff54453c);
    rr_renderer_begin_path(renderer);
    rr_renderer_move_to(renderer, -79.90, -37.44);
    rr_renderer_bezier_curve_to(renderer, -87.77, -32.13, -5.11, -22.71, 8.14,
                                -11.91);
    rr_renderer_bezier_curve_to(renderer, 21.39, -1.12, -6.53, 24.06, -0.40,
                                27.32);
    rr_renderer_bezier_curve_to(renderer, 5.73, 30.58, 35.64, 19.51, 44.94,
                                7.65);
    rr_renderer_bezier_curve_to(renderer, 54.23, -4.20, 76.17, -36.28, 55.37,
                                -43.79);
    rr_renderer_bezier_curve_to(renderer, 34.56, -51.31, -72.03, -42.75, -79.90,
                                -37.44);
    rr_renderer_fill(renderer);
    rr_renderer_set_fill(renderer, 0xff54453c);
    rr_renderer_begin_path(renderer);
    rr_renderer_move_to(renderer, 26.13, 46.51);
    rr_renderer_bezier_curve_to(renderer, 32.91, 52.22, 42.30, 50.80, 47.10,
                                43.34);
    rr_renderer_line_to(renderer, 87.27, -19.11);
    rr_renderer_bezier_curve_to(renderer, 89.58, -22.69, 90.49, -27.22, 89.82,
                                -31.69);
    rr_renderer_bezier_curve_to(renderer, 89.14, -36.16, 86.93, -40.22, 83.68,
                                -42.96);
    rr_renderer_bezier_curve_to(renderer, 76.89, -48.68, 67.50, -47.26, 62.70,
                                -39.80);
    rr_renderer_line_to(renderer, 22.53, 22.65);
    rr_renderer_bezier_curve_to(renderer, 17.73, 30.11, 19.34, 40.79, 26.13,
                                46.51);
    rr_renderer_fill(renderer);
    rr_renderer_set_fill(renderer, 0xff54453c);
    rr_renderer_begin_path(renderer);
    rr_renderer_move_to(renderer, 55.27, -22.46);
    rr_renderer_bezier_curve_to(renderer, 30.95, -21.12, -74.88, -34.75, -71.72,
                                -38.81);
    rr_renderer_bezier_curve_to(renderer, -68.56, -42.87, 53.07, -49.53, 74.23,
                                -46.81);
    rr_renderer_bezier_curve_to(renderer, 95.40, -44.08, 79.60, -23.79, 55.27,
                                -22.46);
    rr_renderer_fill(renderer);
    rr_renderer_set_fill(renderer, 0xff635248);
    rr_renderer_begin_path(renderer);
    rr_renderer_move_to(renderer, 21.48, 45.21);
    rr_renderer_bezier_curve_to(renderer, 26.44, 49.38, 33.29, 48.35, 36.80,
                                42.91);
    rr_renderer_line_to(renderer, 75.79, -17.66);
    rr_renderer_bezier_curve_to(renderer, 77.48, -20.28, 78.15, -23.58, 77.65,
                                -26.85);
    rr_renderer_bezier_curve_to(renderer, 77.16, -30.11, 75.55, -33.08, 73.17,
                                -35.08);
    rr_renderer_bezier_curve_to(renderer, 68.22, -39.25, 61.36, -38.22, 57.86,
                                -32.77);
    rr_renderer_line_to(renderer, 18.86, 27.79);
    rr_renderer_bezier_curve_to(renderer, 15.36, 33.24, 16.53, 41.04, 21.48,
                                45.21);
    rr_renderer_fill(renderer);
    rr_renderer_set_fill(renderer, 0xff635248);
    rr_renderer_begin_path(renderer);
    rr_renderer_move_to(renderer, 67.85, -37.89);
    rr_renderer_bezier_curve_to(renderer, 53.15, -42.44, -27.73, -39.69, -35.80,
                                -35.64);
    rr_renderer_bezier_curve_to(renderer, -43.86, -31.59, 12.06, -24.84, 19.47,
                                -13.58);
    rr_renderer_bezier_curve_to(renderer, 26.87, -2.31, 3.14, 31.09, 8.62,
                                31.97);
    rr_renderer_bezier_curve_to(renderer, 14.11, 32.85, 42.50, 3.34, 52.37,
                                -8.30);
    rr_renderer_bezier_curve_to(renderer, 62.24, -19.94, 82.54, -33.33, 67.85,
                                -37.89);
    rr_renderer_fill(renderer);
}

void rr_pectinodon_wing2_draw(struct rr_renderer *renderer)
{
    rr_renderer_set_fill(renderer, 0xff372d27);
    rr_renderer_begin_path(renderer);
    rr_renderer_move_to(renderer, -75.37, 31.40);
    rr_renderer_line_to(renderer, -93.38, 23.14);
    rr_renderer_line_to(renderer, -92.64, 11.81);
    rr_renderer_line_to(renderer, -87.37, 5.31);
    rr_renderer_line_to(renderer, -76.56, 0.81);
    rr_renderer_line_to(renderer, -69.83, 4.32);
    rr_renderer_line_to(renderer, -66.37, -3.17);
    rr_renderer_line_to(renderer, -50.79, -7.61);
    rr_renderer_line_to(renderer, -44.89, -2.71);
    rr_renderer_line_to(renderer, -41.50, -9.31);
    rr_renderer_line_to(renderer, -16.78, -16.19);
    rr_renderer_line_to(renderer, -25.16, -52.44);
    rr_renderer_line_to(renderer, 34.89, -0.96);
    rr_renderer_fill(renderer);
    rr_renderer_set_fill(renderer, 0xff41362f);
    rr_renderer_begin_path(renderer);
    rr_renderer_move_to(renderer, -10.59, -29.44);
    rr_renderer_line_to(renderer, -6.52, -11.28);
    rr_renderer_line_to(renderer, -37.89, -2.88);
    rr_renderer_line_to(renderer, -44.31, 6.05);
    rr_renderer_line_to(renderer, -52.87, -0.61);
    rr_renderer_line_to(renderer, -61.65, 1.35);
    rr_renderer_line_to(renderer, -66.57, 12.28);
    rr_renderer_line_to(renderer, -77.86, 6.69);
    rr_renderer_line_to(renderer, -83.46, 9.35);
    rr_renderer_line_to(renderer, -87.41, 14.61);
    rr_renderer_line_to(renderer, -87.34, 19.36);
    rr_renderer_line_to(renderer, -71.02, 27.41);
    rr_renderer_line_to(renderer, 13.95, 5.77);
    rr_renderer_line_to(renderer, 18.94, -6.78);
    rr_renderer_line_to(renderer, 6.43, -27.08);
    rr_renderer_fill(renderer);
    rr_renderer_set_fill(renderer, 0xff54453c);
    rr_renderer_begin_path(renderer);
    rr_renderer_move_to(renderer, -79.90, 29.87);
    rr_renderer_bezier_curve_to(renderer, -87.77, 24.55, -5.11, 15.13, 8.14,
                                4.34);
    rr_renderer_bezier_curve_to(renderer, 21.39, -6.45, -6.53, -31.63, -0.40,
                                -34.89);
    rr_renderer_bezier_curve_to(renderer, 5.73, -38.16, 35.64, -27.08, 44.94,
                                -15.23);
    rr_renderer_bezier_curve_to(renderer, 54.23, -3.38, 76.17, 28.71, 55.37,
                                36.22);
    rr_renderer_bezier_curve_to(renderer, 34.56, 43.74, -72.03, 35.18, -79.90,
                                29.87);
    rr_renderer_fill(renderer);
    rr_renderer_set_fill(renderer, 0xff54453c);
    rr_renderer_begin_path(renderer);
    rr_renderer_move_to(renderer, 26.13, -54.08);
    rr_renderer_bezier_curve_to(renderer, 32.91, -59.79, 42.30, -58.38, 47.10,
                                -50.92);
    rr_renderer_line_to(renderer, 87.27, 11.54);
    rr_renderer_bezier_curve_to(renderer, 89.58, 15.12, 90.49, 19.64, 89.82,
                                24.12);
    rr_renderer_bezier_curve_to(renderer, 89.14, 28.59, 86.93, 32.64, 83.68,
                                35.39);
    rr_renderer_bezier_curve_to(renderer, 76.89, 41.10, 67.50, 39.69, 62.70,
                                32.22);
    rr_renderer_line_to(renderer, 22.53, -30.23);
    rr_renderer_bezier_curve_to(renderer, 17.73, -37.69, 19.34, -48.37, 26.13,
                                -54.08);
    rr_renderer_fill(renderer);
    rr_renderer_set_fill(renderer, 0xff54453c);
    rr_renderer_begin_path(renderer);
    rr_renderer_move_to(renderer, 55.27, 14.88);
    rr_renderer_bezier_curve_to(renderer, 30.95, 13.55, -74.88, 27.17, -71.72,
                                31.23);
    rr_renderer_bezier_curve_to(renderer, -68.56, 35.29, 53.07, 41.96, 74.23,
                                39.24);
    rr_renderer_bezier_curve_to(renderer, 95.40, 36.51, 79.60, 16.22, 55.27,
                                14.88);
    rr_renderer_fill(renderer);
    rr_renderer_set_fill(renderer, 0xff635248);
    rr_renderer_begin_path(renderer);
    rr_renderer_move_to(renderer, 21.48, -52.78);
    rr_renderer_bezier_curve_to(renderer, 26.44, -56.96, 33.29, -55.92, 36.80,
                                -50.48);
    rr_renderer_line_to(renderer, 75.79, 10.09);
    rr_renderer_bezier_curve_to(renderer, 77.48, 12.70, 78.15, 16.01, 77.65,
                                19.27);
    rr_renderer_bezier_curve_to(renderer, 77.16, 22.54, 75.55, 25.50, 73.17,
                                27.51);
    rr_renderer_bezier_curve_to(renderer, 68.22, 31.68, 61.36, 30.65, 57.86,
                                25.20);
    rr_renderer_line_to(renderer, 18.86, -35.37);
    rr_renderer_bezier_curve_to(renderer, 15.36, -40.81, 16.53, -48.61, 21.48,
                                -52.78);
    rr_renderer_fill(renderer);
    rr_renderer_set_fill(renderer, 0xff635248);
    rr_renderer_begin_path(renderer);
    rr_renderer_move_to(renderer, 67.85, 30.31);
    rr_renderer_bezier_curve_to(renderer, 53.15, 34.87, -27.73, 32.12, -35.80,
                                28.07);
    rr_renderer_bezier_curve_to(renderer, -43.86, 24.02, 12.06, 17.27, 19.47,
                                6.00);
    rr_renderer_bezier_curve_to(renderer, 26.87, -5.27, 3.14, -38.67, 8.62,
                                -39.55);
    rr_renderer_bezier_curve_to(renderer, 14.11, -40.43, 42.50, -10.92, 52.37,
                                0.73);
    rr_renderer_bezier_curve_to(renderer, 62.24, 12.37, 82.54, 25.75, 67.85,
                                30.31);
    rr_renderer_fill(renderer);
}