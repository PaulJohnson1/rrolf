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

void rr_ant_head_draw(struct rr_renderer *renderer)
{
    rr_renderer_set_fill(renderer, 0xff1e242a);
    rr_renderer_begin_path(renderer);
    rr_renderer_move_to(renderer, 18.68, 39.87);
    rr_renderer_bezier_curve_to(renderer, 22.79, 39.87, 25.90, 38.04, 32.16,
                                35.10);
    rr_renderer_bezier_curve_to(renderer, 38.42, 32.16, 49.94, 27.61, 56.23,
                                22.24);
    rr_renderer_bezier_curve_to(renderer, 62.53, 16.87, 70.76, 6.39, 69.92,
                                2.87);
    rr_renderer_bezier_curve_to(renderer, 69.07, -0.64, 57.35, 2.18, 51.16,
                                1.14);
    rr_renderer_bezier_curve_to(renderer, 44.97, 0.10, 37.12, -5.38, 32.76,
                                -3.37);
    rr_renderer_bezier_curve_to(renderer, 28.40, -1.35, 29.20, 8.72, 24.98,
                                13.21);
    rr_renderer_bezier_curve_to(renderer, 20.76, 17.70, 10.37, 19.94, 7.46,
                                23.59);
    rr_renderer_bezier_curve_to(renderer, 4.54, 27.23, 5.60, 32.39, 7.47,
                                35.10);
    rr_renderer_bezier_curve_to(renderer, 9.34, 37.82, 14.56, 39.87, 18.68,
                                39.87);
    rr_renderer_fill(renderer);
    rr_renderer_set_fill(renderer, 0xff1e242a);
    rr_renderer_begin_path(renderer);
    rr_renderer_move_to(renderer, 18.68, -40.02);
    rr_renderer_bezier_curve_to(renderer, 22.79, -40.02, 25.90, -38.18, 32.16,
                                -35.24);
    rr_renderer_bezier_curve_to(renderer, 38.42, -32.31, 49.94, -27.75, 56.23,
                                -22.38);
    rr_renderer_bezier_curve_to(renderer, 62.53, -17.01, 70.76, -6.53, 69.92,
                                -3.02);
    rr_renderer_bezier_curve_to(renderer, 69.07, 0.50, 57.35, -2.32, 51.16,
                                -1.28);
    rr_renderer_bezier_curve_to(renderer, 44.96, -0.24, 37.12, 5.23, 32.76,
                                3.22);
    rr_renderer_bezier_curve_to(renderer, 28.40, 1.21, 29.20, -8.86, 24.98,
                                -13.35);
    rr_renderer_bezier_curve_to(renderer, 20.76, -17.84, 10.37, -20.08, 7.46,
                                -23.73);
    rr_renderer_bezier_curve_to(renderer, 4.54, -27.38, 5.60, -32.53, 7.47,
                                -35.24);
    rr_renderer_bezier_curve_to(renderer, 9.34, -37.96, 14.56, -40.02, 18.68,
                                -40.02);
    rr_renderer_fill(renderer);
    rr_renderer_set_fill(renderer, 0xff484848);
    rr_renderer_begin_path(renderer);
    rr_renderer_move_to(renderer, -9.23, -59.64);
    rr_renderer_bezier_curve_to(renderer, 24.31, -59.64, 51.50, -32.98, 51.50,
                                -0.08);
    rr_renderer_bezier_curve_to(renderer, 51.50, 15.71, 45.10, 30.86, 33.71,
                                42.03);
    rr_renderer_bezier_curve_to(renderer, 22.32, 53.20, 6.88, 59.48, -9.23,
                                59.48);
    rr_renderer_bezier_curve_to(renderer, -42.77, 59.48, -69.96, 32.81, -69.96,
                                -0.08);
    rr_renderer_bezier_curve_to(renderer, -69.96, -32.98, -42.77, -59.64, -9.23,
                                -59.64);
    rr_renderer_move_to(renderer, -9.23, -43.11);
    rr_renderer_bezier_curve_to(renderer, -33.64, -43.11, -53.43, -23.85,
                                -53.43, -0.08);
    rr_renderer_bezier_curve_to(renderer, -53.43, 23.68, -33.64, 42.95, -9.23,
                                42.95);
    rr_renderer_bezier_curve_to(renderer, 15.18, 42.95, 34.97, 23.68, 34.97,
                                -0.08);
    rr_renderer_bezier_curve_to(renderer, 34.97, -23.85, 15.18, -43.11, -9.23,
                                -43.11);
    rr_renderer_fill(renderer);
    rr_renderer_set_fill(renderer, 0xff2d353e);
    rr_renderer_begin_path(renderer);
    rr_renderer_move_to(renderer, -9.24, -59.64);
    rr_renderer_bezier_curve_to(renderer, 24.30, -59.64, 51.50, -32.97, 51.50,
                                -0.07);
    rr_renderer_bezier_curve_to(renderer, 51.50, 15.73, 45.10, 30.88, 33.71,
                                42.05);
    rr_renderer_bezier_curve_to(renderer, 22.32, 53.22, 6.87, 59.50, -9.24,
                                59.50);
    rr_renderer_bezier_curve_to(renderer, -42.79, 59.50, -69.98, 32.83, -69.98,
                                -0.07);
    rr_renderer_bezier_curve_to(renderer, -69.98, -32.97, -42.79, -59.64, -9.24,
                                -59.64);
    rr_renderer_move_to(renderer, -9.24, -28.23);
    rr_renderer_bezier_curve_to(renderer, -25.44, -28.23, -38.56, -15.62,
                                -38.56, -0.07);
    rr_renderer_bezier_curve_to(renderer, -38.56, 15.48, -25.44, 28.09, -9.24,
                                28.09);
    rr_renderer_bezier_curve_to(renderer, 6.95, 28.09, 20.08, 15.48, 20.08,
                                -0.07);
    rr_renderer_bezier_curve_to(renderer, 20.08, -15.62, 6.95, -28.23, -9.24,
                                -28.23);
    rr_renderer_fill(renderer);
    rr_renderer_set_fill(renderer, 0xff37424c);
    rr_renderer_begin_path(renderer);
    rr_renderer_move_to(renderer, -9.27, -42.41);
    rr_renderer_bezier_curve_to(renderer, 14.64, -42.41, 34.02, -23.40, 34.02,
                                0.05);
    rr_renderer_bezier_curve_to(renderer, 34.02, 11.31, 29.46, 22.11, 21.34,
                                30.07);
    rr_renderer_bezier_curve_to(renderer, 13.22, 38.03, 2.21, 42.51, -9.27,
                                42.51);
    rr_renderer_bezier_curve_to(renderer, -33.17, 42.51, -52.55, 23.50, -52.55,
                                0.05);
    rr_renderer_bezier_curve_to(renderer, -52.55, -23.40, -33.17, -42.41, -9.27,
                                -42.41);
    rr_renderer_fill(renderer);
    rr_renderer_set_fill(renderer, 0xff1e242a);
    rr_renderer_begin_path(renderer);
    rr_renderer_move_to(renderer, -11.57, 61.43);
    rr_renderer_bezier_curve_to(renderer, -13.19, 65.93, -18.14, 68.27, -22.64,
                                66.66);
    rr_renderer_bezier_curve_to(renderer, -24.81, 65.89, -26.57, 64.29, -27.55,
                                62.21);
    rr_renderer_bezier_curve_to(renderer, -28.53, 60.14, -28.65, 57.76, -27.87,
                                55.59);
    rr_renderer_line_to(renderer, -15.45, 20.95);
    rr_renderer_bezier_curve_to(renderer, -13.83, 16.45, -8.88, 14.11, -4.38,
                                15.73);
    rr_renderer_bezier_curve_to(renderer, 0.12, 17.34, 2.46, 22.29, 0.85,
                                26.79);
    rr_renderer_fill(renderer);
    rr_renderer_set_fill(renderer, 0xff1e242a);
    rr_renderer_begin_path(renderer);
    rr_renderer_move_to(renderer, 20.35, 87.99);
    rr_renderer_line_to(renderer, -23.74, 67.36);
    rr_renderer_line_to(renderer, -17.77, 50.92);
    rr_renderer_line_to(renderer, 29.29, 63.41);
    rr_renderer_fill(renderer);
    rr_renderer_set_fill(renderer, 0xff1e242a);
    rr_renderer_begin_path(renderer);
    rr_renderer_move_to(renderer, -17.23, 51.22);
    rr_renderer_bezier_curve_to(renderer, -12.74, 52.85, -10.42, 57.81, -12.05,
                                62.30);
    rr_renderer_bezier_curve_to(renderer, -12.84, 64.46, -14.44, 66.21, -16.52,
                                67.18);
    rr_renderer_bezier_curve_to(renderer, -18.60, 68.15, -20.98, 68.26, -23.13,
                                67.47);
    rr_renderer_bezier_curve_to(renderer, -27.62, 65.84, -29.94, 60.88, -28.31,
                                56.39);
    rr_renderer_bezier_curve_to(renderer, -26.68, 51.91, -21.72, 49.59, -17.23,
                                51.22);
    rr_renderer_fill(renderer);
    rr_renderer_set_fill(renderer, 0xff1e242a);
    rr_renderer_begin_path(renderer);
    rr_renderer_move_to(renderer, 29.97, 63.51);
    rr_renderer_bezier_curve_to(renderer, 36.76, 65.97, 40.27, 73.47, 37.80,
                                80.26);
    rr_renderer_bezier_curve_to(renderer, 36.61, 83.52, 34.18, 86.18, 31.04,
                                87.64);
    rr_renderer_bezier_curve_to(renderer, 27.90, 89.11, 24.30, 89.27, 21.04,
                                88.08);
    rr_renderer_bezier_curve_to(renderer, 14.25, 85.62, 10.74, 78.11, 13.21,
                                71.33);
    rr_renderer_bezier_curve_to(renderer, 15.68, 64.54, 23.18, 61.04, 29.97,
                                63.51);
    rr_renderer_fill(renderer);
    rr_renderer_set_fill(renderer, 0xff1e242a);
    rr_renderer_begin_path(renderer);
    rr_renderer_move_to(renderer, -11.57, -61.43);
    rr_renderer_bezier_curve_to(renderer, -13.19, -65.93, -18.14, -68.27,
                                -22.64, -66.66);
    rr_renderer_bezier_curve_to(renderer, -24.81, -65.88, -26.57, -64.28,
                                -27.55, -62.21);
    rr_renderer_bezier_curve_to(renderer, -28.53, -60.13, -28.65, -57.75,
                                -27.87, -55.59);
    rr_renderer_line_to(renderer, -15.45, -20.94);
    rr_renderer_bezier_curve_to(renderer, -13.83, -16.44, -8.88, -14.10, -4.38,
                                -15.71);
    rr_renderer_bezier_curve_to(renderer, 0.12, -17.33, 2.46, -22.28, 0.85,
                                -26.78);
    rr_renderer_fill(renderer);
    rr_renderer_set_fill(renderer, 0xff1e242a);
    rr_renderer_begin_path(renderer);
    rr_renderer_move_to(renderer, 20.35, -87.99);
    rr_renderer_line_to(renderer, -23.74, -67.35);
    rr_renderer_line_to(renderer, -17.77, -50.91);
    rr_renderer_line_to(renderer, 29.29, -63.41);
    rr_renderer_fill(renderer);
    rr_renderer_set_fill(renderer, 0xff1e242a);
    rr_renderer_begin_path(renderer);
    rr_renderer_move_to(renderer, -17.23, -51.21);
    rr_renderer_bezier_curve_to(renderer, -12.74, -52.85, -10.42, -57.81,
                                -12.05, -62.30);
    rr_renderer_bezier_curve_to(renderer, -12.84, -64.45, -14.44, -66.21,
                                -16.52, -67.18);
    rr_renderer_bezier_curve_to(renderer, -18.60, -68.15, -20.98, -68.25,
                                -23.13, -67.47);
    rr_renderer_bezier_curve_to(renderer, -27.62, -65.84, -29.94, -60.88,
                                -28.31, -56.39);
    rr_renderer_bezier_curve_to(renderer, -26.68, -51.90, -21.72, -49.58,
                                -17.23, -51.21);
    rr_renderer_fill(renderer);
    rr_renderer_set_fill(renderer, 0xff1e242a);
    rr_renderer_begin_path(renderer);
    rr_renderer_move_to(renderer, 29.97, -63.50);
    rr_renderer_bezier_curve_to(renderer, 36.76, -65.97, 40.27, -73.47, 37.80,
                                -80.26);
    rr_renderer_bezier_curve_to(renderer, 36.61, -83.52, 34.18, -86.17, 31.04,
                                -87.64);
    rr_renderer_bezier_curve_to(renderer, 27.90, -89.11, 24.30, -89.27, 21.04,
                                -88.08);
    rr_renderer_bezier_curve_to(renderer, 14.25, -85.61, 10.74, -78.11, 13.21,
                                -71.32);
    rr_renderer_bezier_curve_to(renderer, 15.68, -64.54, 23.18, -61.03, 29.97,
                                -63.50);
    rr_renderer_fill(renderer);
}

void rr_ant_thorax_draw(struct rr_renderer *renderer)
{
    rr_renderer_set_fill(renderer, 0xff2d353e);
    rr_renderer_begin_path(renderer);
    rr_renderer_move_to(renderer, 0.00, -44.89);
    rr_renderer_bezier_curve_to(renderer, 29.47, -44.89, 53.36, -24.79, 53.36,
                                0.00);
    rr_renderer_bezier_curve_to(renderer, 53.36, 11.90, 47.74, 23.32, 37.73,
                                31.74);
    rr_renderer_bezier_curve_to(renderer, 27.72, 40.16, 14.15, 44.89, 0.00,
                                44.89);
    rr_renderer_bezier_curve_to(renderer, -29.47, 44.89, -53.36, 24.79, -53.36,
                                0.00);
    rr_renderer_bezier_curve_to(renderer, -53.36, -24.79, -29.47, -44.89, 0.00,
                                -44.89);
    rr_renderer_move_to(renderer, 0.00, -21.21);
    rr_renderer_bezier_curve_to(renderer, -16.40, -21.21, -29.69, -11.72,
                                -29.69, 0.00);
    rr_renderer_bezier_curve_to(renderer, -29.69, 11.72, -16.40, 21.22, 0.00,
                                21.22);
    rr_renderer_bezier_curve_to(renderer, 16.40, 21.22, 29.69, 11.72, 29.69,
                                0.00);
    rr_renderer_bezier_curve_to(renderer, 29.69, -11.72, 16.40, -21.21, 0.00,
                                -21.21);
    rr_renderer_fill(renderer);
    rr_renderer_set_fill(renderer, 0xff37424c);
    rr_renderer_begin_path(renderer);
    rr_renderer_move_to(renderer, -0.00, -28.04);
    rr_renderer_bezier_curve_to(renderer, 20.00, -28.04, 36.21, -15.49, 36.21,
                                0.00);
    rr_renderer_bezier_curve_to(renderer, 36.21, 7.44, 32.40, 14.57, 25.61,
                                19.83);
    rr_renderer_bezier_curve_to(renderer, 18.82, 25.09, 9.60, 28.04, -0.00,
                                28.04);
    rr_renderer_bezier_curve_to(renderer, -20.00, 28.04, -36.21, 15.49, -36.21,
                                0.00);
    rr_renderer_bezier_curve_to(renderer, -36.21, -15.49, -20.00, -28.04, -0.00,
                                -28.04);
    rr_renderer_fill(renderer);
}

void rr_ant_abdomen_draw(struct rr_renderer *renderer)
{
    rr_renderer_set_fill(renderer, 0xff2d353e);
    rr_renderer_begin_path(renderer);
    rr_renderer_move_to(renderer, 0.00, -57.92);
    rr_renderer_bezier_curve_to(renderer, 41.77, -57.92, 75.62, -31.99, 75.62,
                                -0.00);
    rr_renderer_bezier_curve_to(renderer, 75.62, 15.36, 67.66, 30.09, 53.47,
                                40.95);
    rr_renderer_bezier_curve_to(renderer, 39.29, 51.81, 20.06, 57.92, 0.00,
                                57.92);
    rr_renderer_bezier_curve_to(renderer, -41.77, 57.92, -75.62, 31.99, -75.62,
                                -0.00);
    rr_renderer_bezier_curve_to(renderer, -75.62, -31.99, -41.77, -57.92, 0.00,
                                -57.92);
    rr_renderer_move_to(renderer, 0.00, -27.37);
    rr_renderer_bezier_curve_to(renderer, -24.90, -27.37, -45.08, -15.12,
                                -45.08, -0.00);
    rr_renderer_bezier_curve_to(renderer, -45.08, 15.12, -24.90, 27.37, 0.00,
                                27.37);
    rr_renderer_bezier_curve_to(renderer, 24.90, 27.37, 45.08, 15.12, 45.08,
                                -0.00);
    rr_renderer_bezier_curve_to(renderer, 45.08, -15.12, 24.90, -27.37, 0.00,
                                -27.37);
    rr_renderer_fill(renderer);
    rr_renderer_set_fill(renderer, 0xff37424c);
    rr_renderer_begin_path(renderer);
    rr_renderer_move_to(renderer, 0.00, -41.17);
    rr_renderer_bezier_curve_to(renderer, 31.22, -41.17, 56.53, -22.74, 56.53,
                                -0.00);
    rr_renderer_bezier_curve_to(renderer, 56.53, 10.92, 50.57, 21.39, 39.97,
                                29.11);
    rr_renderer_bezier_curve_to(renderer, 29.37, 36.83, 14.99, 41.17, 0.00,
                                41.17);
    rr_renderer_bezier_curve_to(renderer, -31.22, 41.17, -56.53, 22.74, -56.53,
                                -0.00);
    rr_renderer_bezier_curve_to(renderer, -56.53, -22.74, -31.22, -41.17, 0.00,
                                -41.17);
    rr_renderer_fill(renderer);
    rr_renderer_set_fill(renderer, 0xff2d353e);
    rr_renderer_begin_path(renderer);
    rr_renderer_move_to(renderer, 20.27, 47.61);
    rr_renderer_bezier_curve_to(renderer, -3.42, 47.61, -22.62, 26.30, -22.62,
                                -0.00);
    rr_renderer_bezier_curve_to(renderer, -22.62, -26.30, -3.42, -47.62, 20.27,
                                -47.62);
    rr_renderer_bezier_curve_to(renderer, 5.45, -37.38, -3.56, -19.38, -3.56,
                                -0.00);
    rr_renderer_bezier_curve_to(renderer, -3.56, 19.38, 5.45, 37.38, 20.27,
                                47.61);
    rr_renderer_fill(renderer);
    rr_renderer_set_fill(renderer, 0xff2d353e);
    rr_renderer_begin_path(renderer);
    rr_renderer_move_to(renderer, -2.43, 47.49);
    rr_renderer_bezier_curve_to(renderer, -19.31, 47.49, -32.98, 26.18, -32.98,
                                -0.12);
    rr_renderer_bezier_curve_to(renderer, -32.98, -26.42, -19.31, -47.74, -2.43,
                                -47.74);
    rr_renderer_bezier_curve_to(renderer, -12.99, -37.50, -19.41, -19.50,
                                -19.41, -0.12);
    rr_renderer_bezier_curve_to(renderer, -19.41, 19.26, -12.99, 37.26, -2.43,
                                47.49);
    rr_renderer_fill(renderer);
    rr_renderer_set_fill(renderer, 0xff2d353e);
    rr_renderer_begin_path(renderer);
    rr_renderer_move_to(renderer, 7.92, -42.32);
    rr_renderer_line_to(renderer, -15.32, -3.30);
    rr_renderer_line_to(renderer, 4.73, 43.67);
    rr_renderer_line_to(renderer, -10.77, 42.48);
    rr_renderer_line_to(renderer, -30.36, -1.71);
    rr_renderer_line_to(renderer, -8.49, -45.10);
    rr_renderer_fill(renderer);
}

void rr_ant_leg_draw(struct rr_renderer *renderer)
{
    rr_renderer_set_fill(renderer, 0xff1e242a);
    rr_renderer_begin_path(renderer);
    rr_renderer_move_to(renderer, 38.53, 9.24);
    rr_renderer_bezier_curve_to(renderer, 43.64, 9.24, 47.78, 5.10, 47.78,
                                -0.00);
    rr_renderer_bezier_curve_to(renderer, 47.78, -2.45, 46.80, -4.80, 45.07,
                                -6.54);
    rr_renderer_bezier_curve_to(renderer, 43.34, -8.27, 40.99, -9.25, 38.53,
                                -9.25);
    rr_renderer_line_to(renderer, -38.54, -9.25);
    rr_renderer_bezier_curve_to(renderer, -43.64, -9.25, -47.78, -5.11, -47.78,
                                -0.00);
    rr_renderer_bezier_curve_to(renderer, -47.78, 5.10, -43.64, 9.24, -38.54,
                                9.24);
    rr_renderer_fill(renderer);
}