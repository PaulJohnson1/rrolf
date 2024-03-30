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

void rr_ornithomimus_body_draw(struct rr_renderer *renderer)
{
    rr_renderer_set_fill(renderer, 0xffb8b8b8);
    rr_renderer_begin_path(renderer);
    rr_renderer_move_to(renderer, -43.69, -55.42);
    rr_renderer_bezier_curve_to(renderer, 11.42, -55.42, 56.10, -30.61, 56.10,
                                -0.01);
    rr_renderer_bezier_curve_to(renderer, 56.10, 14.69, 45.58, 28.78, 26.87,
                                39.18);
    rr_renderer_bezier_curve_to(renderer, 8.16, 49.57, -17.22, 55.40, -43.69,
                                55.40);
    rr_renderer_bezier_curve_to(renderer, -98.80, 55.40, -143.47, 30.60,
                                -143.47, -0.01);
    rr_renderer_bezier_curve_to(renderer, -143.47, -30.61, -98.80, -55.42,
                                -43.69, -55.42);
    rr_renderer_fill(renderer);
    rr_renderer_set_fill(renderer, 0xffa7a7a7);
    rr_renderer_begin_path(renderer);
    rr_renderer_move_to(renderer, -43.70, -62.88);
    rr_renderer_bezier_curve_to(renderer, 18.84, -62.88, 69.54, -34.73, 69.54,
                                -0.00);
    rr_renderer_bezier_curve_to(renderer, 69.54, 16.68, 57.61, 32.67, 36.38,
                                44.46);
    rr_renderer_bezier_curve_to(renderer, 15.14, 56.26, -13.66, 62.88, -43.70,
                                62.88);
    rr_renderer_bezier_curve_to(renderer, -106.24, 62.88, -156.94, 34.73,
                                -156.94, -0.00);
    rr_renderer_bezier_curve_to(renderer, -156.94, -34.73, -106.24, -62.88,
                                -43.70, -62.88);
    rr_renderer_move_to(renderer, -43.70, -48.61);
    rr_renderer_bezier_curve_to(renderer, -98.36, -48.61, -142.67, -26.85,
                                -142.67, -0.00);
    rr_renderer_bezier_curve_to(renderer, -142.67, 26.85, -98.36, 48.61, -43.70,
                                48.61);
    rr_renderer_bezier_curve_to(renderer, 10.96, 48.61, 55.27, 26.85, 55.27,
                                -0.00);
    rr_renderer_bezier_curve_to(renderer, 55.27, -26.85, 10.96, -48.61, -43.70,
                                -48.61);
    rr_renderer_fill(renderer);
    rr_renderer_set_fill(renderer, 0xffa7a7a7);
    rr_renderer_begin_path(renderer);
    rr_renderer_move_to(renderer, 118.34, -38.55);
    rr_renderer_bezier_curve_to(renderer, 139.66, -38.55, 156.94, -21.26,
                                156.94, 0.06);
    rr_renderer_bezier_curve_to(renderer, 156.94, 10.30, 152.87, 20.11, 145.63,
                                27.35);
    rr_renderer_bezier_curve_to(renderer, 138.39, 34.59, 128.58, 38.66, 118.34,
                                38.66);
    rr_renderer_line_to(renderer, 25.18, 38.66);
    rr_renderer_bezier_curve_to(renderer, 3.86, 38.66, -13.42, 21.38, -13.42,
                                0.06);
    rr_renderer_bezier_curve_to(renderer, -13.42, -21.26, 3.86, -38.55, 25.18,
                                -38.55);
    rr_renderer_fill(renderer);
    rr_renderer_set_fill(renderer, 0xffb8b8b8);
    rr_renderer_begin_path(renderer);
    rr_renderer_move_to(renderer, 116.28, -27.69);
    rr_renderer_bezier_curve_to(renderer, 131.60, -27.69, 144.02, -15.27,
                                144.02, 0.06);
    rr_renderer_bezier_curve_to(renderer, 144.02, 7.42, 141.10, 14.47, 135.89,
                                19.68);
    rr_renderer_bezier_curve_to(renderer, 130.69, 24.88, 123.63, 27.80, 116.28,
                                27.80);
    rr_renderer_line_to(renderer, 1.40, 27.80);
    rr_renderer_bezier_curve_to(renderer, -13.92, 27.80, -26.34, 15.38, -26.34,
                                0.06);
    rr_renderer_bezier_curve_to(renderer, -26.34, -15.27, -13.92, -27.69, 1.40,
                                -27.69);
    rr_renderer_fill(renderer);
}

void rr_ornithomimus_head_draw(struct rr_renderer *renderer)
{
    rr_renderer_set_fill(renderer, 0xffa7a7a7);
    rr_renderer_begin_path(renderer);
    rr_renderer_move_to(renderer, -28.57, 41.44);
    rr_renderer_bezier_curve_to(renderer, -51.46, 41.44, -70.02, 22.89, -70.02,
                                -0.01);
    rr_renderer_bezier_curve_to(renderer, -70.02, -11.00, -65.65, -21.54,
                                -57.88, -29.31);
    rr_renderer_bezier_curve_to(renderer, -50.11, -37.09, -39.56, -41.45,
                                -28.57, -41.45);
    rr_renderer_bezier_curve_to(renderer, -5.68, -41.45, 12.87, -22.90, 12.87,
                                -0.01);
    rr_renderer_bezier_curve_to(renderer, 12.87, 22.89, -5.68, 41.44, -28.57,
                                41.44);
    rr_renderer_fill(renderer);
    rr_renderer_set_fill(renderer, 0xffa7a7a7);
    rr_renderer_begin_path(renderer);
    rr_renderer_move_to(renderer, -63.45, 14.06);
    rr_renderer_bezier_curve_to(renderer, -71.22, 14.06, -77.51, 7.76, -77.51,
                                -0.01);
    rr_renderer_bezier_curve_to(renderer, -77.51, -3.74, -76.03, -7.31, -73.39,
                                -9.95);
    rr_renderer_bezier_curve_to(renderer, -70.76, -12.59, -67.18, -14.07,
                                -63.45, -14.07);
    rr_renderer_bezier_curve_to(renderer, -55.68, -14.07, -49.38, -7.77, -49.38,
                                -0.01);
    rr_renderer_bezier_curve_to(renderer, -49.38, 7.76, -55.68, 14.06, -63.45,
                                14.06);
    rr_renderer_fill(renderer);
    rr_renderer_set_fill(renderer, 0xffa7a7a7);
    rr_renderer_begin_path(renderer);
    rr_renderer_move_to(renderer, -59.99, 27.05);
    rr_renderer_line_to(renderer, -74.40, 8.74);
    rr_renderer_line_to(renderer, -66.36, 11.93);
    rr_renderer_fill(renderer);
    rr_renderer_set_fill(renderer, 0xffa7a7a7);
    rr_renderer_begin_path(renderer);
    rr_renderer_move_to(renderer, -59.99, -27.19);
    rr_renderer_line_to(renderer, -74.40, -8.88);
    rr_renderer_line_to(renderer, -66.36, -12.06);
    rr_renderer_fill(renderer);
    rr_renderer_set_fill(renderer, 0xffb8b8b8);
    rr_renderer_begin_path(renderer);
    rr_renderer_move_to(renderer, -7.85, 20.72);
    rr_renderer_bezier_curve_to(renderer, -19.29, 32.16, -37.85, 32.16, -49.30,
                                20.72);
    rr_renderer_quadratic_curve_to(renderer, -58.44, 11.57, -65.16, -0.01);
    rr_renderer_quadratic_curve_to(renderer, -58.44, -11.59, -49.30, -20.73);
    rr_renderer_bezier_curve_to(renderer, -37.85, -32.18, -19.29, -32.18, -7.85,
                                -20.73);
    rr_renderer_bezier_curve_to(renderer, 3.60, -9.29, 3.60, 9.27, -7.85,
                                20.72);
    rr_renderer_fill(renderer);
    rr_renderer_set_fill(renderer, 0xff95754f);
    rr_renderer_begin_path(renderer);
    rr_renderer_move_to(renderer, -26.14, -30.24);
    rr_renderer_bezier_curve_to(renderer, 6.79, -30.24, 33.49, -16.72, 33.49,
                                -0.04);
    rr_renderer_bezier_curve_to(renderer, 33.49, 16.64, 6.79, 30.17, -26.14,
                                30.17);
    rr_renderer_bezier_curve_to(renderer, 2.20, 12.59, 2.20, -12.67, -26.14,
                                -30.24);
    rr_renderer_fill(renderer);
    rr_renderer_set_fill(renderer, 0xff7f6342);
    rr_renderer_begin_path(renderer);
    rr_renderer_move_to(renderer, 52.68, -24.79);
    rr_renderer_bezier_curve_to(renderer, 66.39, -24.79, 77.51, -13.67, 77.51,
                                0.05);
    rr_renderer_bezier_curve_to(renderer, 77.51, 6.63, 74.89, 12.95, 70.24,
                                17.61);
    rr_renderer_bezier_curve_to(renderer, 65.58, 22.26, 59.26, 24.88, 52.68,
                                24.88);
    rr_renderer_bezier_curve_to(renderer, 38.96, 24.88, 27.84, 13.76, 27.84,
                                0.05);
    rr_renderer_bezier_curve_to(renderer, 27.84, -13.67, 38.96, -24.79, 52.68,
                                -24.79);
    rr_renderer_fill(renderer);
    rr_renderer_set_fill(renderer, 0xff7f6342);
    rr_renderer_begin_path(renderer);
    rr_renderer_move_to(renderer, 4.06, -32.80);
    rr_renderer_line_to(renderer, 55.58, -24.71);
    rr_renderer_line_to(renderer, 55.58, 24.79);
    rr_renderer_line_to(renderer, 4.06, 32.87);
    rr_renderer_fill(renderer);
    rr_renderer_set_fill(renderer, 0xff7f6342);
    rr_renderer_begin_path(renderer);
    rr_renderer_move_to(renderer, -24.62, -41.49);
    rr_renderer_bezier_curve_to(renderer, -8.37, -41.49, 6.63, -33.55, 14.72,
                                -20.68);
    rr_renderer_bezier_curve_to(renderer, 22.80, -7.80, 22.74, 8.04, 14.55,
                                20.86);
    rr_renderer_bezier_curve_to(renderer, 6.36, 33.68, -8.70, 41.51, -24.95,
                                41.41);
    rr_renderer_line_to(renderer, -24.86, 29.99);
    rr_renderer_bezier_curve_to(renderer, -12.70, 30.06, -1.43, 24.38, 4.69,
                                15.10);
    rr_renderer_bezier_curve_to(renderer, 10.82, 5.81, 10.86, -5.67, 4.81,
                                -14.99);
    rr_renderer_bezier_curve_to(renderer, -1.24, -24.32, -12.46, -30.07, -24.62,
                                -30.07);
    rr_renderer_fill(renderer);
    rr_renderer_set_fill(renderer, 0xffa7a7a7);
    rr_renderer_begin_path(renderer);
    rr_renderer_move_to(renderer, -24.62, 41.41);
    rr_renderer_bezier_curve_to(renderer, -40.86, 41.41, -55.86, 33.47, -63.95,
                                20.60);
    rr_renderer_bezier_curve_to(renderer, -72.04, 7.72, -71.97, -8.12, -63.78,
                                -20.94);
    rr_renderer_bezier_curve_to(renderer, -55.59, -33.76, -40.53, -41.60,
                                -24.29, -41.49);
    rr_renderer_line_to(renderer, -24.38, -30.07);
    rr_renderer_bezier_curve_to(renderer, -36.53, -30.15, -47.80, -24.47,
                                -53.93, -15.18);
    rr_renderer_bezier_curve_to(renderer, -60.05, -5.89, -60.10, 5.59, -54.05,
                                14.91);
    rr_renderer_bezier_curve_to(renderer, -47.99, 24.24, -36.77, 29.99, -24.62,
                                29.99);
    rr_renderer_fill(renderer);
    rr_renderer_set_fill(renderer, 0xff7f6342);
    rr_renderer_begin_path(renderer);
    rr_renderer_move_to(renderer, -24.62, -41.49);
    rr_renderer_bezier_curve_to(renderer, -21.46, -41.49, -18.90, -38.93,
                                -18.90, -35.77);
    rr_renderer_bezier_curve_to(renderer, -18.90, -34.26, -19.50, -32.80,
                                -20.57, -31.73);
    rr_renderer_bezier_curve_to(renderer, -21.65, -30.66, -23.10, -30.06,
                                -24.62, -30.06);
    rr_renderer_bezier_curve_to(renderer, -27.77, -30.06, -30.33, -32.62,
                                -30.33, -35.77);
    rr_renderer_bezier_curve_to(renderer, -30.33, -38.93, -27.77, -41.49,
                                -24.62, -41.49);
    rr_renderer_fill(renderer);
    rr_renderer_set_fill(renderer, 0xff95754f);
    rr_renderer_begin_path(renderer);
    rr_renderer_move_to(renderer, -8.55, -26.40);
    rr_renderer_bezier_curve_to(renderer, -11.28, -22.56, -8.70, -18.17, -2.78,
                                -16.61);
    rr_renderer_bezier_curve_to(renderer, 3.13, -15.04, 10.14, -16.89, 12.87,
                                -20.73);
    rr_renderer_bezier_curve_to(renderer, 4.72, -20.76, -2.95, -22.79, -8.55,
                                -26.40);
    rr_renderer_fill(renderer);
    rr_renderer_set_fill(renderer, 0xff95754f);
    rr_renderer_begin_path(renderer);
    rr_renderer_move_to(renderer, -8.55, 26.46);
    rr_renderer_bezier_curve_to(renderer, -11.28, 22.61, -8.70, 18.23, -2.78,
                                16.66);
    rr_renderer_bezier_curve_to(renderer, 3.13, 15.10, 10.14, 16.94, 12.87,
                                20.79);
    rr_renderer_bezier_curve_to(renderer, 4.72, 20.82, -2.95, 22.85, -8.55,
                                26.46);
    rr_renderer_fill(renderer);
    rr_renderer_set_fill(renderer, 0xff7f6342);
    rr_renderer_begin_path(renderer);
    rr_renderer_move_to(renderer, 4.94, -32.57);
    rr_renderer_bezier_curve_to(renderer, 2.66, -33.28, 0.63, -34.72, -0.23,
                                -33.69);
    rr_renderer_bezier_curve_to(renderer, -1.09, -32.66, -0.98, -28.36, -0.23,
                                -26.38);
    rr_renderer_bezier_curve_to(renderer, 0.52, -24.40, 2.06, -23.03, 4.27,
                                -21.83);
    rr_renderer_bezier_curve_to(renderer, 6.48, -20.63, 10.16, -19.64, 13.04,
                                -19.18);
    rr_renderer_bezier_curve_to(renderer, 15.93, -18.72, 21.52, -17.37, 21.59,
                                -19.07);
    rr_renderer_bezier_curve_to(renderer, 21.67, -20.78, 16.27, -27.17, 13.49,
                                -29.42);
    rr_renderer_bezier_curve_to(renderer, 10.72, -31.67, 7.23, -31.86, 4.94,
                                -32.57);
    rr_renderer_fill(renderer);
    rr_renderer_set_fill(renderer, 0xff7f6342);
    rr_renderer_begin_path(renderer);
    rr_renderer_move_to(renderer, 4.94, 32.59);
    rr_renderer_bezier_curve_to(renderer, 2.66, 33.30, 0.63, 34.75, -0.23,
                                33.71);
    rr_renderer_bezier_curve_to(renderer, -1.09, 32.68, -0.98, 28.38, -0.23,
                                26.40);
    rr_renderer_bezier_curve_to(renderer, 0.52, 24.43, 2.05, 23.05, 4.27,
                                21.85);
    rr_renderer_bezier_curve_to(renderer, 6.48, 20.65, 10.15, 19.66, 13.04,
                                19.20);
    rr_renderer_bezier_curve_to(renderer, 15.93, 18.75, 21.52, 17.39, 21.59,
                                19.09);
    rr_renderer_bezier_curve_to(renderer, 21.66, 20.80, 16.27, 27.19, 13.49,
                                29.44);
    rr_renderer_bezier_curve_to(renderer, 10.72, 31.69, 7.23, 31.88, 4.94,
                                32.59);
    rr_renderer_fill(renderer);
    rr_renderer_set_fill(renderer, 0xff95754f);
    rr_renderer_begin_path(renderer);
    rr_renderer_move_to(renderer, 4.06, -21.69);
    rr_renderer_line_to(renderer, 55.58, -15.27);
    rr_renderer_line_to(renderer, 55.58, 15.26);
    rr_renderer_line_to(renderer, 4.06, 21.68);
    rr_renderer_fill(renderer);
    rr_renderer_set_fill(renderer, 0xff95754f);
    rr_renderer_begin_path(renderer);
    rr_renderer_move_to(renderer, 52.67, -15.50);
    rr_renderer_bezier_curve_to(renderer, 61.23, -15.50, 68.18, -8.56, 68.18,
                                0.01);
    rr_renderer_bezier_curve_to(renderer, 68.18, 4.12, 66.54, 8.07, 63.63,
                                10.98);
    rr_renderer_bezier_curve_to(renderer, 60.72, 13.88, 56.78, 15.52, 52.67,
                                15.52);
    rr_renderer_bezier_curve_to(renderer, 44.10, 15.52, 37.15, 8.57, 37.15,
                                0.01);
    rr_renderer_bezier_curve_to(renderer, 37.15, -8.56, 44.10, -15.50, 52.67,
                                -15.50);
    rr_renderer_fill(renderer);
    rr_renderer_set_fill(renderer, 0xffb8b8b8);
    rr_renderer_begin_path(renderer);
    rr_renderer_move_to(renderer, -51.25, 18.46);
    rr_renderer_line_to(renderer, -65.46, -0.01);
    rr_renderer_line_to(renderer, -51.25, -18.48);
    rr_renderer_fill(renderer);
    rr_renderer_set_fill(renderer, 0xff7f6342);
    rr_renderer_begin_path(renderer);
    rr_renderer_move_to(renderer, -24.62, 29.98);
    rr_renderer_bezier_curve_to(renderer, -21.46, 29.98, -18.90, 32.54, -18.90,
                                35.69);
    rr_renderer_bezier_curve_to(renderer, -18.90, 37.21, -19.50, 38.66, -20.57,
                                39.74);
    rr_renderer_bezier_curve_to(renderer, -21.65, 40.81, -23.10, 41.41, -24.62,
                                41.41);
    rr_renderer_bezier_curve_to(renderer, -27.77, 41.41, -30.33, 38.85, -30.33,
                                35.69);
    rr_renderer_bezier_curve_to(renderer, -30.33, 32.54, -27.77, 29.98, -24.62,
                                29.98);
    rr_renderer_fill(renderer);
}

void rr_ornithomimus_tail_draw(struct rr_renderer *renderer)
{
    rr_renderer_set_fill(renderer, 0xff585858);
    rr_renderer_begin_path(renderer);
    rr_renderer_move_to(renderer, -110.99, -27.58);
    rr_renderer_bezier_curve_to(renderer, -126.76, -27.58, -139.54, -14.80,
                                -139.54, 0.97);
    rr_renderer_bezier_curve_to(renderer, -139.54, 8.54, -136.54, 15.80,
                                -131.18, 21.16);
    rr_renderer_bezier_curve_to(renderer, -125.83, 26.51, -118.57, 29.52,
                                -110.99, 29.52);
    rr_renderer_bezier_curve_to(renderer, -95.23, 29.52, -82.44, 16.74, -82.44,
                                0.97);
    rr_renderer_bezier_curve_to(renderer, -82.44, -14.80, -95.23, -27.58,
                                -110.99, -27.58);
    rr_renderer_fill(renderer);
    rr_renderer_set_fill(renderer, 0xff585858);
    rr_renderer_begin_path(renderer);
    rr_renderer_move_to(renderer, -140.91, -8.73);
    rr_renderer_bezier_curve_to(renderer, -146.26, -8.73, -150.60, -4.39,
                                -150.60, 0.96);
    rr_renderer_bezier_curve_to(renderer, -150.60, 3.53, -149.57, 5.99, -147.76,
                                7.81);
    rr_renderer_bezier_curve_to(renderer, -145.94, 9.63, -143.48, 10.65,
                                -140.91, 10.65);
    rr_renderer_bezier_curve_to(renderer, -135.56, 10.65, -131.22, 6.31,
                                -131.22, 0.96);
    rr_renderer_bezier_curve_to(renderer, -131.22, -4.39, -135.56, -8.73,
                                -140.91, -8.73);
    rr_renderer_fill(renderer);
    rr_renderer_set_fill(renderer, 0xff585858);
    rr_renderer_begin_path(renderer);
    rr_renderer_move_to(renderer, -129.47, 22.26);
    rr_renderer_line_to(renderer, -146.78, 8.64);
    rr_renderer_line_to(renderer, -137.03, 7.13);
    rr_renderer_fill(renderer);
    rr_renderer_set_fill(renderer, 0xff585858);
    rr_renderer_begin_path(renderer);
    rr_renderer_move_to(renderer, -129.47, -20.45);
    rr_renderer_line_to(renderer, -146.78, -6.84);
    rr_renderer_line_to(renderer, -137.03, -5.32);
    rr_renderer_fill(renderer);
    rr_renderer_set_fill(renderer, 0xff585858);
    rr_renderer_begin_path(renderer);
    rr_renderer_move_to(renderer, -95.90, 8.93);
    rr_renderer_bezier_curve_to(renderer, -110.19, 2.26, -116.36, -14.73,
                                -109.69, -29.02);
    rr_renderer_bezier_curve_to(renderer, -106.49, -35.88, -100.70, -41.19,
                                -93.58, -43.78);
    rr_renderer_bezier_curve_to(renderer, -86.46, -46.37, -78.61, -46.02,
                                -71.75, -42.82);
    rr_renderer_bezier_curve_to(renderer, -57.46, -36.15, -51.28, -19.16,
                                -57.95, -4.87);
    rr_renderer_bezier_curve_to(renderer, -64.62, 9.42, -81.61, 15.60, -95.90,
                                8.93);
    rr_renderer_fill(renderer);
    rr_renderer_set_fill(renderer, 0xff585858);
    rr_renderer_begin_path(renderer);
    rr_renderer_move_to(renderer, -115.03, -20.82);
    rr_renderer_bezier_curve_to(renderer, -119.88, -23.08, -121.98, -28.84,
                                -119.72, -33.69);
    rr_renderer_bezier_curve_to(renderer, -118.63, -36.02, -116.67, -37.82,
                                -114.25, -38.70);
    rr_renderer_bezier_curve_to(renderer, -111.84, -39.58, -109.18, -39.47,
                                -106.85, -38.38);
    rr_renderer_bezier_curve_to(renderer, -102.00, -36.12, -99.90, -30.36,
                                -102.16, -25.51);
    rr_renderer_bezier_curve_to(renderer, -104.42, -20.66, -110.18, -18.56,
                                -115.03, -20.82);
    rr_renderer_fill(renderer);
    rr_renderer_set_fill(renderer, 0xff585858);
    rr_renderer_begin_path(renderer);
    rr_renderer_move_to(renderer, -91.56, -44.06);
    rr_renderer_line_to(renderer, -113.00, -39.04);
    rr_renderer_line_to(renderer, -104.81, -33.54);
    rr_renderer_fill(renderer);
    rr_renderer_set_fill(renderer, 0xff585858);
    rr_renderer_begin_path(renderer);
    rr_renderer_move_to(renderer, -109.61, -5.34);
    rr_renderer_line_to(renderer, -119.55, -25.01);
    rr_renderer_line_to(renderer, -110.07, -22.26);
    rr_renderer_fill(renderer);
    rr_renderer_set_fill(renderer, 0xff585858);
    rr_renderer_begin_path(renderer);
    rr_renderer_move_to(renderer, -66.60, -7.20);
    rr_renderer_bezier_curve_to(renderer, -78.97, -16.98, -81.07, -34.93,
                                -71.29, -47.30);
    rr_renderer_bezier_curve_to(renderer, -66.60, -53.24, -59.73, -57.07,
                                -52.21, -57.95);
    rr_renderer_bezier_curve_to(renderer, -44.69, -58.83, -37.13, -56.69,
                                -31.19, -51.99);
    rr_renderer_bezier_curve_to(renderer, -18.82, -42.21, -16.72, -24.26,
                                -26.50, -11.89);
    rr_renderer_bezier_curve_to(renderer, -36.28, 0.48, -54.23, 2.58, -66.60,
                                -7.20);
    rr_renderer_fill(renderer);
    rr_renderer_set_fill(renderer, 0xff585858);
    rr_renderer_begin_path(renderer);
    rr_renderer_move_to(renderer, -78.37, -40.54);
    rr_renderer_bezier_curve_to(renderer, -82.57, -43.86, -83.28, -49.96,
                                -79.96, -54.16);
    rr_renderer_bezier_curve_to(renderer, -78.37, -56.17, -76.04, -57.48,
                                -73.48, -57.77);
    rr_renderer_bezier_curve_to(renderer, -70.93, -58.07, -68.36, -57.34,
                                -66.35, -55.75);
    rr_renderer_bezier_curve_to(renderer, -62.15, -52.43, -61.43, -46.34,
                                -64.75, -42.14);
    rr_renderer_bezier_curve_to(renderer, -68.07, -37.94, -74.17, -37.22,
                                -78.37, -40.54);
    rr_renderer_fill(renderer);
    rr_renderer_set_fill(renderer, 0xff585858);
    rr_renderer_begin_path(renderer);
    rr_renderer_move_to(renderer, -50.18, -57.75);
    rr_renderer_line_to(renderer, -72.20, -57.81);
    rr_renderer_line_to(renderer, -65.50, -50.57);
    rr_renderer_fill(renderer);
    rr_renderer_set_fill(renderer, 0xff585858);
    rr_renderer_begin_path(renderer);
    rr_renderer_move_to(renderer, -76.67, -24.25);
    rr_renderer_line_to(renderer, -81.80, -45.67);
    rr_renderer_line_to(renderer, -73.22, -40.81);
    rr_renderer_fill(renderer);
    rr_renderer_set_fill(renderer, 0xff585858);
    rr_renderer_begin_path(renderer);
    rr_renderer_move_to(renderer, -32.62, -18.98);
    rr_renderer_bezier_curve_to(renderer, -45.30, -28.34, -48.00, -46.21,
                                -38.64, -58.90);
    rr_renderer_bezier_curve_to(renderer, -34.15, -65.00, -27.42, -69.05,
                                -19.93, -70.18);
    rr_renderer_bezier_curve_to(renderer, -12.45, -71.31, -4.82, -69.43, 1.27,
                                -64.93);
    rr_renderer_bezier_curve_to(renderer, 13.96, -55.57, 16.66, -37.70, 7.30,
                                -25.01);
    rr_renderer_bezier_curve_to(renderer, -2.06, -12.32, -19.93, -9.62, -32.62,
                                -18.98);
    rr_renderer_fill(renderer);
    rr_renderer_set_fill(renderer, 0xff585858);
    rr_renderer_begin_path(renderer);
    rr_renderer_move_to(renderer, -45.49, -51.91);
    rr_renderer_bezier_curve_to(renderer, -49.80, -55.09, -50.71, -61.16,
                                -47.53, -65.47);
    rr_renderer_bezier_curve_to(renderer, -46.01, -67.54, -43.72, -68.92,
                                -41.18, -69.30);
    rr_renderer_bezier_curve_to(renderer, -38.64, -69.68, -36.04, -69.04,
                                -33.98, -67.51);
    rr_renderer_bezier_curve_to(renderer, -29.67, -64.33, -28.75, -58.26,
                                -31.93, -53.95);
    rr_renderer_bezier_curve_to(renderer, -35.11, -49.64, -41.18, -48.73,
                                -45.49, -51.91);
    rr_renderer_fill(renderer);
    rr_renderer_set_fill(renderer, 0xff585858);
    rr_renderer_begin_path(renderer);
    rr_renderer_move_to(renderer, -17.89, -70.06);
    rr_renderer_line_to(renderer, -39.91, -69.38);
    rr_renderer_line_to(renderer, -32.96, -62.37);
    rr_renderer_fill(renderer);
    rr_renderer_set_fill(renderer, 0xff585858);
    rr_renderer_begin_path(renderer);
    rr_renderer_move_to(renderer, -43.25, -35.68);
    rr_renderer_line_to(renderer, -49.10, -56.92);
    rr_renderer_line_to(renderer, -40.35, -52.35);
    rr_renderer_fill(renderer);
    rr_renderer_set_fill(renderer, 0xff585858);
    rr_renderer_begin_path(renderer);
    rr_renderer_move_to(renderer, 32.67, -27.04);
    rr_renderer_bezier_curve_to(renderer, 24.44, -36.40, 25.36, -50.66, 34.71,
                                -58.89);
    rr_renderer_bezier_curve_to(renderer, 39.21, -62.84, 45.09, -64.85, 51.06,
                                -64.46);
    rr_renderer_bezier_curve_to(renderer, 57.03, -64.08, 62.61, -61.34, 66.56,
                                -56.84);
    rr_renderer_bezier_curve_to(renderer, 74.79, -47.49, 73.87, -33.23, 64.51,
                                -25.00);
    rr_renderer_bezier_curve_to(renderer, 55.15, -16.77, 40.90, -17.68, 32.67,
                                -27.04);
    rr_renderer_fill(renderer);
    rr_renderer_set_fill(renderer, 0xff585858);
    rr_renderer_begin_path(renderer);
    rr_renderer_move_to(renderer, 28.24, -54.64);
    rr_renderer_bezier_curve_to(renderer, 25.45, -57.82, 25.77, -62.66, 28.95,
                                -65.45);
    rr_renderer_bezier_curve_to(renderer, 30.48, -66.79, 32.47, -67.47, 34.50,
                                -67.34);
    rr_renderer_bezier_curve_to(renderer, 36.53, -67.21, 38.42, -66.27, 39.76,
                                -64.75);
    rr_renderer_bezier_curve_to(renderer, 42.55, -61.57, 42.23, -56.73, 39.05,
                                -53.94);
    rr_renderer_bezier_curve_to(renderer, 35.87, -51.15, 31.03, -51.46, 28.24,
                                -54.64);
    rr_renderer_fill(renderer);
    rr_renderer_set_fill(renderer, 0xff585858);
    rr_renderer_begin_path(renderer);
    rr_renderer_move_to(renderer, 52.63, -64.03);
    rr_renderer_line_to(renderer, 35.50, -67.20);
    rr_renderer_line_to(renderer, 39.69, -60.62);
    rr_renderer_fill(renderer);
    rr_renderer_set_fill(renderer, 0xff585858);
    rr_renderer_begin_path(renderer);
    rr_renderer_move_to(renderer, 27.26, -41.73);
    rr_renderer_line_to(renderer, 26.31, -59.12);
    rr_renderer_line_to(renderer, 32.30, -54.12);
    rr_renderer_fill(renderer);
    rr_renderer_set_fill(renderer, 0xff585858);
    rr_renderer_begin_path(renderer);
    rr_renderer_move_to(renderer, 58.49, -28.91);
    rr_renderer_bezier_curve_to(renderer, 53.52, -37.33, 56.31, -48.18, 64.73,
                                -53.15);
    rr_renderer_bezier_curve_to(renderer, 68.77, -55.54, 73.60, -56.22, 78.15,
                                -55.05);
    rr_renderer_bezier_curve_to(renderer, 82.69, -53.88, 86.59, -50.95, 88.97,
                                -46.90);
    rr_renderer_bezier_curve_to(renderer, 93.94, -38.49, 91.15, -27.63, 82.73,
                                -22.66);
    rr_renderer_bezier_curve_to(renderer, 74.31, -17.69, 63.46, -20.49, 58.49,
                                -28.91);
    rr_renderer_fill(renderer);
    rr_renderer_set_fill(renderer, 0xff585858);
    rr_renderer_begin_path(renderer);
    rr_renderer_move_to(renderer, 59.12, -50.82);
    rr_renderer_bezier_curve_to(renderer, 57.44, -53.68, 58.40, -57.36, 61.26,
                                -59.04);
    rr_renderer_bezier_curve_to(renderer, 62.63, -59.85, 64.27, -60.08, 65.81,
                                -59.68);
    rr_renderer_bezier_curve_to(renderer, 67.35, -59.28, 68.67, -58.28, 69.48,
                                -56.91);
    rr_renderer_bezier_curve_to(renderer, 71.16, -54.05, 70.20, -50.37, 67.34,
                                -48.69);
    rr_renderer_bezier_curve_to(renderer, 64.48, -47.01, 60.80, -47.96, 59.12,
                                -50.82);
    rr_renderer_fill(renderer);
    rr_renderer_set_fill(renderer, 0xff585858);
    rr_renderer_begin_path(renderer);
    rr_renderer_move_to(renderer, 79.29, -54.48);
    rr_renderer_line_to(renderer, 66.56, -59.43);
    rr_renderer_line_to(renderer, 68.83, -53.75);
    rr_renderer_fill(renderer);
    rr_renderer_set_fill(renderer, 0xff585858);
    rr_renderer_begin_path(renderer);
    rr_renderer_move_to(renderer, 56.48, -41.01);
    rr_renderer_line_to(renderer, 58.29, -54.55);
    rr_renderer_line_to(renderer, 62.17, -49.82);
    rr_renderer_fill(renderer);
    rr_renderer_set_fill(renderer, 0xff585858);
    rr_renderer_begin_path(renderer);
    rr_renderer_move_to(renderer, -95.89, -8.93);
    rr_renderer_bezier_curve_to(renderer, -110.18, -2.26, -116.36, 14.73,
                                -109.69, 29.02);
    rr_renderer_bezier_curve_to(renderer, -106.49, 35.88, -100.69, 41.19,
                                -93.57, 43.78);
    rr_renderer_bezier_curve_to(renderer, -86.46, 46.37, -78.60, 46.02, -71.74,
                                42.82);
    rr_renderer_bezier_curve_to(renderer, -57.46, 36.15, -51.28, 19.16, -57.95,
                                4.87);
    rr_renderer_bezier_curve_to(renderer, -64.62, -9.42, -81.61, -15.60, -95.89,
                                -8.93);
    rr_renderer_fill(renderer);
    rr_renderer_set_fill(renderer, 0xff585858);
    rr_renderer_begin_path(renderer);
    rr_renderer_move_to(renderer, -115.02, 20.82);
    rr_renderer_bezier_curve_to(renderer, -119.87, 23.08, -121.97, 28.84,
                                -119.71, 33.69);
    rr_renderer_bezier_curve_to(renderer, -118.63, 36.02, -116.66, 37.83,
                                -114.25, 38.70);
    rr_renderer_bezier_curve_to(renderer, -111.83, 39.58, -109.17, 39.47,
                                -106.84, 38.38);
    rr_renderer_bezier_curve_to(renderer, -101.99, 36.12, -99.89, 30.36,
                                -102.15, 25.51);
    rr_renderer_bezier_curve_to(renderer, -104.41, 20.66, -110.18, 18.56,
                                -115.02, 20.82);
    rr_renderer_fill(renderer);
    rr_renderer_set_fill(renderer, 0xff585858);
    rr_renderer_begin_path(renderer);
    rr_renderer_move_to(renderer, -91.55, 44.06);
    rr_renderer_line_to(renderer, -113.00, 39.04);
    rr_renderer_line_to(renderer, -104.80, 33.54);
    rr_renderer_fill(renderer);
    rr_renderer_set_fill(renderer, 0xff585858);
    rr_renderer_begin_path(renderer);
    rr_renderer_move_to(renderer, -109.61, 5.35);
    rr_renderer_line_to(renderer, -119.55, 25.01);
    rr_renderer_line_to(renderer, -110.07, 22.26);
    rr_renderer_fill(renderer);
    rr_renderer_set_fill(renderer, 0xff585858);
    rr_renderer_begin_path(renderer);
    rr_renderer_move_to(renderer, -66.60, 7.20);
    rr_renderer_bezier_curve_to(renderer, -78.97, 16.98, -81.06, 34.93, -71.29,
                                47.30);
    rr_renderer_bezier_curve_to(renderer, -66.59, 53.24, -59.73, 57.07, -52.21,
                                57.95);
    rr_renderer_bezier_curve_to(renderer, -44.69, 58.83, -37.13, 56.69, -31.19,
                                51.99);
    rr_renderer_bezier_curve_to(renderer, -18.82, 42.21, -16.72, 24.26, -26.50,
                                11.89);
    rr_renderer_bezier_curve_to(renderer, -36.28, -0.48, -54.23, -2.58, -66.60,
                                7.20);
    rr_renderer_fill(renderer);
    rr_renderer_set_fill(renderer, 0xff585858);
    rr_renderer_begin_path(renderer);
    rr_renderer_move_to(renderer, -78.36, 40.54);
    rr_renderer_bezier_curve_to(renderer, -82.56, 43.86, -83.28, 49.96, -79.96,
                                54.16);
    rr_renderer_bezier_curve_to(renderer, -78.36, 56.18, -76.03, 57.48, -73.48,
                                57.78);
    rr_renderer_bezier_curve_to(renderer, -70.93, 58.07, -68.36, 57.35, -66.34,
                                55.75);
    rr_renderer_bezier_curve_to(renderer, -62.14, 52.43, -61.43, 46.34, -64.75,
                                42.14);
    rr_renderer_bezier_curve_to(renderer, -68.07, 37.94, -74.16, 37.22, -78.36,
                                40.54);
    rr_renderer_fill(renderer);
    rr_renderer_set_fill(renderer, 0xff585858);
    rr_renderer_begin_path(renderer);
    rr_renderer_move_to(renderer, -50.17, 57.75);
    rr_renderer_line_to(renderer, -72.20, 57.81);
    rr_renderer_line_to(renderer, -65.49, 50.58);
    rr_renderer_fill(renderer);
    rr_renderer_set_fill(renderer, 0xff585858);
    rr_renderer_begin_path(renderer);
    rr_renderer_move_to(renderer, -76.67, 24.25);
    rr_renderer_line_to(renderer, -81.80, 45.67);
    rr_renderer_line_to(renderer, -73.21, 40.81);
    rr_renderer_fill(renderer);
    rr_renderer_set_fill(renderer, 0xff585858);
    rr_renderer_begin_path(renderer);
    rr_renderer_move_to(renderer, -32.61, 18.98);
    rr_renderer_bezier_curve_to(renderer, -45.30, 28.34, -48.00, 46.21, -38.64,
                                58.90);
    rr_renderer_bezier_curve_to(renderer, -34.14, 65.00, -27.41, 69.05, -19.93,
                                70.19);
    rr_renderer_bezier_curve_to(renderer, -12.44, 71.32, -4.81, 69.43, 1.28,
                                64.93);
    rr_renderer_bezier_curve_to(renderer, 13.97, 55.57, 16.67, 37.70, 7.31,
                                25.01);
    rr_renderer_bezier_curve_to(renderer, -2.05, 12.32, -19.92, 9.62, -32.61,
                                18.98);
    rr_renderer_fill(renderer);
    rr_renderer_set_fill(renderer, 0xff585858);
    rr_renderer_begin_path(renderer);
    rr_renderer_move_to(renderer, -6.85, -25.30);
    rr_renderer_bezier_curve_to(renderer, -16.88, -37.46, -15.15, -55.45, -3.00,
                                -65.48);
    rr_renderer_bezier_curve_to(renderer, 2.84, -70.29, 10.36, -72.59, 17.89,
                                -71.87);
    rr_renderer_bezier_curve_to(renderer, 25.42, -71.15, 32.36, -67.46, 37.18,
                                -61.62);
    rr_renderer_bezier_curve_to(renderer, 47.21, -49.46, 45.48, -31.47, 33.32,
                                -21.44);
    rr_renderer_bezier_curve_to(renderer, 21.16, -11.41, 3.18, -13.14, -6.85,
                                -25.30);
    rr_renderer_fill(renderer);
    rr_renderer_set_fill(renderer, 0xff585858);
    rr_renderer_begin_path(renderer);
    rr_renderer_move_to(renderer, -11.34, -60.36);
    rr_renderer_bezier_curve_to(renderer, -14.74, -64.49, -14.14, -70.59,
                                -10.02, -73.99);
    rr_renderer_bezier_curve_to(renderer, -8.03, -75.63, -5.48, -76.41, -2.93,
                                -76.16);
    rr_renderer_bezier_curve_to(renderer, -0.37, -75.91, 1.98, -74.66, 3.62,
                                -72.67);
    rr_renderer_bezier_curve_to(renderer, 7.02, -68.54, 6.42, -62.44, 2.30,
                                -59.04);
    rr_renderer_bezier_curve_to(renderer, -1.83, -55.64, -7.94, -56.23, -11.34,
                                -60.36);
    rr_renderer_fill(renderer);
    rr_renderer_set_fill(renderer, 0xff585858);
    rr_renderer_begin_path(renderer);
    rr_renderer_move_to(renderer, 19.86, -71.25);
    rr_renderer_line_to(renderer, -1.66, -75.94);
    rr_renderer_line_to(renderer, 3.37, -67.45);
    rr_renderer_fill(renderer);
    rr_renderer_set_fill(renderer, 0xff585858);
    rr_renderer_begin_path(renderer);
    rr_renderer_move_to(renderer, -13.09, -44.07);
    rr_renderer_line_to(renderer, -13.61, -66.09);
    rr_renderer_line_to(renderer, -6.23, -59.53);
    rr_renderer_fill(renderer);
    rr_renderer_set_fill(renderer, 0xff585858);
    rr_renderer_begin_path(renderer);
    rr_renderer_move_to(renderer, -6.85, 25.30);
    rr_renderer_bezier_curve_to(renderer, -16.87, 37.46, -15.15, 55.45, -2.99,
                                65.48);
    rr_renderer_bezier_curve_to(renderer, 2.85, 70.29, 10.36, 72.59, 17.89,
                                71.87);
    rr_renderer_bezier_curve_to(renderer, 25.43, 71.15, 32.37, 67.46, 37.18,
                                61.62);
    rr_renderer_bezier_curve_to(renderer, 47.21, 49.46, 45.48, 31.47, 33.33,
                                21.44);
    rr_renderer_bezier_curve_to(renderer, 21.17, 11.41, 3.18, 13.14, -6.85,
                                25.30);
    rr_renderer_fill(renderer);
    rr_renderer_set_fill(renderer, 0xff585858);
    rr_renderer_begin_path(renderer);
    rr_renderer_move_to(renderer, -11.33, 60.36);
    rr_renderer_bezier_curve_to(renderer, -14.73, 64.49, -14.14, 70.60, -10.01,
                                74.00);
    rr_renderer_bezier_curve_to(renderer, -8.03, 75.63, -5.48, 76.41, -2.92,
                                76.16);
    rr_renderer_bezier_curve_to(renderer, -0.36, 75.91, 1.99, 74.66, 3.62,
                                72.67);
    rr_renderer_bezier_curve_to(renderer, 7.02, 68.54, 6.43, 62.44, 2.30,
                                59.04);
    rr_renderer_bezier_curve_to(renderer, -1.83, 55.64, -7.93, 56.23, -11.33,
                                60.36);
    rr_renderer_fill(renderer);
    rr_renderer_set_fill(renderer, 0xff585858);
    rr_renderer_begin_path(renderer);
    rr_renderer_move_to(renderer, 19.87, 71.25);
    rr_renderer_line_to(renderer, -1.66, 75.94);
    rr_renderer_line_to(renderer, 3.38, 67.46);
    rr_renderer_fill(renderer);
    rr_renderer_set_fill(renderer, 0xff585858);
    rr_renderer_begin_path(renderer);
    rr_renderer_move_to(renderer, -13.09, 44.07);
    rr_renderer_line_to(renderer, -13.60, 66.09);
    rr_renderer_line_to(renderer, -6.23, 59.53);
    rr_renderer_fill(renderer);
    rr_renderer_set_fill(renderer, 0xff585858);
    rr_renderer_begin_path(renderer);
    rr_renderer_move_to(renderer, -45.48, 51.91);
    rr_renderer_bezier_curve_to(renderer, -49.79, 55.09, -50.71, 61.16, -47.53,
                                65.47);
    rr_renderer_bezier_curve_to(renderer, -46.00, 67.54, -43.72, 68.92, -41.17,
                                69.30);
    rr_renderer_bezier_curve_to(renderer, -38.63, 69.68, -36.04, 69.04, -33.97,
                                67.51);
    rr_renderer_bezier_curve_to(renderer, -29.66, 64.33, -28.74, 58.26, -31.92,
                                53.95);
    rr_renderer_bezier_curve_to(renderer, -35.10, 49.64, -41.17, 48.73, -45.48,
                                51.91);
    rr_renderer_fill(renderer);
    rr_renderer_set_fill(renderer, 0xff585858);
    rr_renderer_begin_path(renderer);
    rr_renderer_move_to(renderer, -17.89, 70.06);
    rr_renderer_line_to(renderer, -39.90, 69.38);
    rr_renderer_line_to(renderer, -32.96, 62.37);
    rr_renderer_fill(renderer);
    rr_renderer_set_fill(renderer, 0xff585858);
    rr_renderer_begin_path(renderer);
    rr_renderer_move_to(renderer, -43.24, 35.68);
    rr_renderer_line_to(renderer, -49.09, 56.92);
    rr_renderer_line_to(renderer, -40.35, 52.35);
    rr_renderer_fill(renderer);
    rr_renderer_set_fill(renderer, 0xff585858);
    rr_renderer_begin_path(renderer);
    rr_renderer_move_to(renderer, 32.67, 27.04);
    rr_renderer_bezier_curve_to(renderer, 24.45, 36.40, 25.36, 50.66, 34.72,
                                58.89);
    rr_renderer_bezier_curve_to(renderer, 39.21, 62.84, 45.09, 64.85, 51.07,
                                64.46);
    rr_renderer_bezier_curve_to(renderer, 57.04, 64.08, 62.61, 61.34, 66.56,
                                56.85);
    rr_renderer_bezier_curve_to(renderer, 74.79, 47.49, 73.88, 33.23, 64.52,
                                25.00);
    rr_renderer_bezier_curve_to(renderer, 55.16, 16.77, 40.90, 17.68, 32.67,
                                27.04);
    rr_renderer_fill(renderer);
    rr_renderer_set_fill(renderer, 0xff585858);
    rr_renderer_begin_path(renderer);
    rr_renderer_move_to(renderer, 28.25, 54.64);
    rr_renderer_bezier_curve_to(renderer, 25.46, 57.82, 25.78, 62.66, 28.96,
                                65.45);
    rr_renderer_bezier_curve_to(renderer, 30.48, 66.79, 32.48, 67.47, 34.51,
                                67.34);
    rr_renderer_bezier_curve_to(renderer, 36.53, 67.21, 38.42, 66.27, 39.76,
                                64.75);
    rr_renderer_bezier_curve_to(renderer, 42.55, 61.57, 42.24, 56.73, 39.06,
                                53.94);
    rr_renderer_bezier_curve_to(renderer, 35.88, 51.15, 31.04, 51.47, 28.25,
                                54.64);
    rr_renderer_fill(renderer);
    rr_renderer_set_fill(renderer, 0xff585858);
    rr_renderer_begin_path(renderer);
    rr_renderer_move_to(renderer, 52.63, 64.03);
    rr_renderer_line_to(renderer, 35.51, 67.21);
    rr_renderer_line_to(renderer, 39.70, 60.62);
    rr_renderer_fill(renderer);
    rr_renderer_set_fill(renderer, 0xff585858);
    rr_renderer_begin_path(renderer);
    rr_renderer_move_to(renderer, 27.26, 41.73);
    rr_renderer_line_to(renderer, 26.31, 59.12);
    rr_renderer_line_to(renderer, 32.30, 54.12);
    rr_renderer_fill(renderer);
    rr_renderer_set_fill(renderer, 0xff585858);
    rr_renderer_begin_path(renderer);
    rr_renderer_move_to(renderer, 58.49, 28.91);
    rr_renderer_bezier_curve_to(renderer, 53.52, 37.33, 56.32, 48.18, 64.74,
                                53.15);
    rr_renderer_bezier_curve_to(renderer, 68.78, 55.54, 73.61, 56.22, 78.15,
                                55.05);
    rr_renderer_bezier_curve_to(renderer, 82.70, 53.88, 86.59, 50.95, 88.98,
                                46.91);
    rr_renderer_bezier_curve_to(renderer, 93.95, 38.49, 91.15, 27.63, 82.73,
                                22.66);
    rr_renderer_bezier_curve_to(renderer, 74.31, 17.69, 63.46, 20.49, 58.49,
                                28.91);
    rr_renderer_fill(renderer);
    rr_renderer_set_fill(renderer, 0xff585858);
    rr_renderer_begin_path(renderer);
    rr_renderer_move_to(renderer, 59.13, 50.82);
    rr_renderer_bezier_curve_to(renderer, 57.45, 53.68, 58.40, 57.36, 61.26,
                                59.04);
    rr_renderer_bezier_curve_to(renderer, 62.64, 59.85, 64.27, 60.08, 65.81,
                                59.68);
    rr_renderer_bezier_curve_to(renderer, 67.36, 59.28, 68.67, 58.28, 69.48,
                                56.91);
    rr_renderer_bezier_curve_to(renderer, 71.16, 54.05, 70.20, 50.37, 67.35,
                                48.69);
    rr_renderer_bezier_curve_to(renderer, 64.49, 47.01, 60.81, 47.96, 59.13,
                                50.82);
    rr_renderer_fill(renderer);
    rr_renderer_set_fill(renderer, 0xff585858);
    rr_renderer_begin_path(renderer);
    rr_renderer_move_to(renderer, 79.30, 54.48);
    rr_renderer_line_to(renderer, 66.57, 59.43);
    rr_renderer_line_to(renderer, 68.83, 53.75);
    rr_renderer_fill(renderer);
    rr_renderer_set_fill(renderer, 0xff585858);
    rr_renderer_begin_path(renderer);
    rr_renderer_move_to(renderer, 56.48, 41.01);
    rr_renderer_line_to(renderer, 58.30, 54.56);
    rr_renderer_line_to(renderer, 62.18, 49.82);
    rr_renderer_fill(renderer);
    rr_renderer_set_fill(renderer, 0xff6e6e6e);
    rr_renderer_begin_path(renderer);
    rr_renderer_move_to(renderer, -96.74, -13.37);
    rr_renderer_bezier_curve_to(renderer, -104.62, -21.25, -117.39, -21.25,
                                -125.27, -13.37);
    rr_renderer_quadratic_curve_to(renderer, -133.21, -5.43, -142.76, 0.90);
    rr_renderer_quadratic_curve_to(renderer, -133.21, 7.23, -125.27, 15.17);
    rr_renderer_bezier_curve_to(renderer, -117.39, 23.05, -104.62, 23.05,
                                -96.74, 15.17);
    rr_renderer_bezier_curve_to(renderer, -88.86, 7.29, -88.86, -5.49, -96.74,
                                -13.37);
    rr_renderer_fill(renderer);
    rr_renderer_set_fill(renderer, 0xff6e6e6e);
    rr_renderer_begin_path(renderer);
    rr_renderer_move_to(renderer, -76.97, 2.07);
    rr_renderer_bezier_curve_to(renderer, -87.44, 5.88, -99.02, 0.48, -102.82,
                                -9.99);
    rr_renderer_quadratic_curve_to(renderer, -106.66, -20.54, -112.64, -30.31);
    rr_renderer_quadratic_curve_to(renderer, -101.32, -32.00, -90.77, -35.84);
    rr_renderer_bezier_curve_to(renderer, -80.30, -39.65, -68.72, -34.25,
                                -64.92, -23.78);
    rr_renderer_bezier_curve_to(renderer, -61.11, -13.31, -66.50, -1.74, -76.97,
                                2.07);
    rr_renderer_fill(renderer);
    rr_renderer_set_fill(renderer, 0xff6e6e6e);
    rr_renderer_begin_path(renderer);
    rr_renderer_move_to(renderer, -46.60, -9.49);
    rr_renderer_bezier_curve_to(renderer, -57.67, -8.20, -67.68, -16.13, -68.97,
                                -27.20);
    rr_renderer_quadratic_curve_to(renderer, -70.27, -38.36, -73.84, -49.25);
    rr_renderer_quadratic_curve_to(renderer, -62.42, -48.28, -51.27, -49.58);
    rr_renderer_bezier_curve_to(renderer, -40.20, -50.87, -30.18, -42.94,
                                -28.89, -31.87);
    rr_renderer_bezier_curve_to(renderer, -27.60, -20.80, -35.53, -10.78,
                                -46.60, -9.49);
    rr_renderer_fill(renderer);
    rr_renderer_set_fill(renderer, 0xff6e6e6e);
    rr_renderer_begin_path(renderer);
    rr_renderer_move_to(renderer, -12.70, -21.97);
    rr_renderer_bezier_curve_to(renderer, -23.72, -20.30, -34.00, -27.87,
                                -35.67, -38.89);
    rr_renderer_quadratic_curve_to(renderer, -37.35, -50.00, -41.29, -60.76);
    rr_renderer_quadratic_curve_to(renderer, -29.85, -60.19, -18.74, -61.87);
    rr_renderer_bezier_curve_to(renderer, -7.73, -63.54, 2.56, -55.96, 4.23,
                                -44.94);
    rr_renderer_bezier_curve_to(renderer, 5.90, -33.92, -1.68, -23.63, -12.70,
                                -21.97);
    rr_renderer_fill(renderer);
    rr_renderer_set_fill(renderer, 0xff6e6e6e);
    rr_renderer_begin_path(renderer);
    rr_renderer_move_to(renderer, 48.58, -26.00);
    rr_renderer_bezier_curve_to(renderer, 39.78, -26.56, 33.10, -34.15, 33.66,
                                -42.95);
    rr_renderer_quadratic_curve_to(renderer, 34.22, -51.81, 32.99, -60.80);
    rr_renderer_quadratic_curve_to(renderer, 41.74, -58.43, 50.60, -57.87);
    rr_renderer_bezier_curve_to(renderer, 59.40, -57.31, 66.08, -49.72, 65.52,
                                -40.92);
    rr_renderer_bezier_curve_to(renderer, 64.96, -32.12, 57.38, -25.44, 48.58,
                                -26.00);
    rr_renderer_fill(renderer);
    rr_renderer_set_fill(renderer, 0xff6e6e6e);
    rr_renderer_begin_path(renderer);
    rr_renderer_move_to(renderer, 70.57, -25.76);
    rr_renderer_bezier_curve_to(renderer, 63.88, -27.49, 59.86, -34.31, 61.59,
                                -41.00);
    rr_renderer_quadratic_curve_to(renderer, 63.33, -47.74, 63.70, -54.84);
    rr_renderer_quadratic_curve_to(renderer, 70.09, -51.72, 76.83, -49.98);
    rr_renderer_bezier_curve_to(renderer, 83.52, -48.25, 87.54, -41.43, 85.81,
                                -34.74);
    rr_renderer_bezier_curve_to(renderer, 84.08, -28.05, 77.26, -24.03, 70.57,
                                -25.76);
    rr_renderer_fill(renderer);
    rr_renderer_set_fill(renderer, 0xff6e6e6e);
    rr_renderer_begin_path(renderer);
    rr_renderer_move_to(renderer, -76.97, -2.07);
    rr_renderer_bezier_curve_to(renderer, -87.44, -5.88, -99.01, -0.48, -102.82,
                                9.99);
    rr_renderer_quadratic_curve_to(renderer, -106.66, 20.54, -112.64, 30.31);
    rr_renderer_quadratic_curve_to(renderer, -101.31, 32.00, -90.76, 35.84);
    rr_renderer_bezier_curve_to(renderer, -80.29, 39.65, -68.72, 34.25, -64.91,
                                23.78);
    rr_renderer_bezier_curve_to(renderer, -61.10, 13.31, -66.50, 1.74, -76.97,
                                -2.07);
    rr_renderer_fill(renderer);
    rr_renderer_set_fill(renderer, 0xff6e6e6e);
    rr_renderer_begin_path(renderer);
    rr_renderer_move_to(renderer, -46.59, 9.50);
    rr_renderer_bezier_curve_to(renderer, -57.66, 8.21, -67.68, 16.13, -68.97,
                                27.20);
    rr_renderer_quadratic_curve_to(renderer, -70.27, 38.36, -73.83, 49.25);
    rr_renderer_quadratic_curve_to(renderer, -62.42, 48.28, -51.26, 49.58);
    rr_renderer_bezier_curve_to(renderer, -40.19, 50.87, -30.18, 42.94, -28.89,
                                31.87);
    rr_renderer_bezier_curve_to(renderer, -27.60, 20.80, -35.52, 10.79, -46.59,
                                9.50);
    rr_renderer_fill(renderer);
    rr_renderer_set_fill(renderer, 0xff6e6e6e);
    rr_renderer_begin_path(renderer);
    rr_renderer_move_to(renderer, -12.69, 21.97);
    rr_renderer_bezier_curve_to(renderer, -23.71, 20.30, -34.00, 27.88, -35.67,
                                38.89);
    rr_renderer_quadratic_curve_to(renderer, -37.35, 50.00, -41.28, 60.76);
    rr_renderer_quadratic_curve_to(renderer, -29.84, 60.19, -18.74, 61.87);
    rr_renderer_bezier_curve_to(renderer, -7.72, 63.54, 2.57, 55.96, 4.24,
                                44.94);
    rr_renderer_bezier_curve_to(renderer, 5.91, 33.92, -1.67, 23.64, -12.69,
                                21.97);
    rr_renderer_fill(renderer);
    rr_renderer_set_fill(renderer, 0xff6e6e6e);
    rr_renderer_begin_path(renderer);
    rr_renderer_move_to(renderer, 13.18, -23.32);
    rr_renderer_bezier_curve_to(renderer, 2.09, -24.39, -6.03, -34.25, -4.96,
                                -45.34);
    rr_renderer_quadratic_curve_to(renderer, -3.88, -56.51, -5.07, -67.91);
    rr_renderer_quadratic_curve_to(renderer, 5.88, -64.56, 17.06, -63.48);
    rr_renderer_bezier_curve_to(renderer, 28.15, -62.41, 36.27, -52.56, 35.20,
                                -41.47);
    rr_renderer_bezier_curve_to(renderer, 34.13, -30.38, 24.27, -22.25, 13.18,
                                -23.32);
    rr_renderer_fill(renderer);
    rr_renderer_set_fill(renderer, 0xff6e6e6e);
    rr_renderer_begin_path(renderer);
    rr_renderer_move_to(renderer, 13.19, 23.33);
    rr_renderer_bezier_curve_to(renderer, 2.10, 24.40, -6.02, 34.25, -4.95,
                                45.34);
    rr_renderer_quadratic_curve_to(renderer, -3.87, 56.52, -5.06, 67.91);
    rr_renderer_quadratic_curve_to(renderer, 5.89, 64.56, 17.06, 63.48);
    rr_renderer_bezier_curve_to(renderer, 28.15, 62.41, 36.27, 52.56, 35.20,
                                41.47);
    rr_renderer_bezier_curve_to(renderer, 34.13, 30.38, 24.28, 22.26, 13.19,
                                23.33);
    rr_renderer_fill(renderer);
    rr_renderer_set_fill(renderer, 0xff6e6e6e);
    rr_renderer_begin_path(renderer);
    rr_renderer_move_to(renderer, 48.58, 26.00);
    rr_renderer_bezier_curve_to(renderer, 39.78, 26.56, 33.10, 34.15, 33.66,
                                42.95);
    rr_renderer_quadratic_curve_to(renderer, 34.23, 51.82, 32.99, 60.80);
    rr_renderer_quadratic_curve_to(renderer, 41.74, 58.43, 50.61, 57.87);
    rr_renderer_bezier_curve_to(renderer, 59.41, 57.31, 66.09, 49.72, 65.53,
                                40.92);
    rr_renderer_bezier_curve_to(renderer, 64.97, 32.12, 57.38, 25.44, 48.58,
                                26.00);
    rr_renderer_fill(renderer);
    rr_renderer_set_fill(renderer, 0xff6e6e6e);
    rr_renderer_begin_path(renderer);
    rr_renderer_move_to(renderer, 70.57, 25.76);
    rr_renderer_bezier_curve_to(renderer, 63.88, 27.49, 59.86, 34.31, 61.59,
                                41.00);
    rr_renderer_quadratic_curve_to(renderer, 63.34, 47.74, 63.71, 54.84);
    rr_renderer_quadratic_curve_to(renderer, 70.10, 51.72, 76.84, 49.98);
    rr_renderer_bezier_curve_to(renderer, 83.53, 48.25, 87.55, 41.43, 85.82,
                                34.74);
    rr_renderer_bezier_curve_to(renderer, 84.09, 28.05, 77.26, 24.03, 70.57,
                                25.76);
    rr_renderer_fill(renderer);
    rr_renderer_set_fill(renderer, 0xffa7a7a7);
    rr_renderer_begin_path(renderer);
    rr_renderer_move_to(renderer, 81.05, 48.07);
    rr_renderer_line_to(renderer, -86.33, 14.95);
    rr_renderer_line_to(renderer, -86.33, -15.07);
    rr_renderer_line_to(renderer, 81.05, -48.19);
    rr_renderer_fill(renderer);
    rr_renderer_set_fill(renderer, 0xffa7a7a7);
    rr_renderer_begin_path(renderer);
    rr_renderer_move_to(renderer, 93.45, -49.59);
    rr_renderer_bezier_curve_to(renderer, 125.01, -49.59, 150.59, -27.41,
                                150.59, -0.05);
    rr_renderer_bezier_curve_to(renderer, 150.59, 13.09, 144.57, 25.69, 133.86,
                                34.98);
    rr_renderer_bezier_curve_to(renderer, 123.14, 44.27, 108.61, 49.49, 93.45,
                                49.49);
    rr_renderer_bezier_curve_to(renderer, 61.89, 49.49, 36.31, 27.31, 36.31,
                                -0.05);
    rr_renderer_bezier_curve_to(renderer, 36.31, -27.41, 61.89, -49.59, 93.45,
                                -49.59);
    rr_renderer_fill(renderer);
    rr_renderer_set_fill(renderer, 0xffa7a7a7);
    rr_renderer_begin_path(renderer);
    rr_renderer_move_to(renderer, 93.46, -34.35);
    rr_renderer_bezier_curve_to(renderer, 115.31, -34.35, 133.01, -19.01,
                                133.01, -0.07);
    rr_renderer_bezier_curve_to(renderer, 133.01, 9.02, 128.85, 17.74, 121.43,
                                24.17);
    rr_renderer_bezier_curve_to(renderer, 114.01, 30.60, 103.95, 34.21, 93.46,
                                34.21);
    rr_renderer_bezier_curve_to(renderer, 71.62, 34.21, 53.91, 18.86, 53.91,
                                -0.07);
    rr_renderer_bezier_curve_to(renderer, 53.91, -19.01, 71.62, -34.35, 93.46,
                                -34.35);
    rr_renderer_fill(renderer);
    rr_renderer_set_fill(renderer, 0xffa7a7a7);
    rr_renderer_begin_path(renderer);
    rr_renderer_move_to(renderer, -83.78, -15.19);
    rr_renderer_bezier_curve_to(renderer, -74.14, -15.19, -66.33, -8.42, -66.33,
                                -0.06);
    rr_renderer_bezier_curve_to(renderer, -66.33, 3.95, -68.17, 7.80, -71.44,
                                10.64);
    rr_renderer_bezier_curve_to(renderer, -74.71, 13.47, -79.15, 15.07, -83.78,
                                15.07);
    rr_renderer_bezier_curve_to(renderer, -93.41, 15.07, -101.23, 8.29, -101.23,
                                -0.06);
    rr_renderer_bezier_curve_to(renderer, -101.23, -8.42, -93.41, -15.19,
                                -83.78, -15.19);
    rr_renderer_fill(renderer);
    rr_renderer_set_fill(renderer, 0xffa7a7a7);
    rr_renderer_begin_path(renderer);
    rr_renderer_move_to(renderer, 82.91, 32.97);
    rr_renderer_line_to(renderer, -86.06, -0.06);
    rr_renderer_line_to(renderer, 82.91, -33.09);
    rr_renderer_fill(renderer);
    rr_renderer_set_fill(renderer, 0xffb8b8b8);
    rr_renderer_begin_path(renderer);
    rr_renderer_move_to(renderer, 93.45, -34.34);
    rr_renderer_bezier_curve_to(renderer, 115.29, -34.34, 133.00, -18.99,
                                133.00, -0.06);
    rr_renderer_bezier_curve_to(renderer, 133.00, 9.03, 128.84, 17.75, 121.42,
                                24.18);
    rr_renderer_bezier_curve_to(renderer, 114.00, 30.61, 103.94, 34.22, 93.45,
                                34.22);
    rr_renderer_bezier_curve_to(renderer, 71.60, 34.22, 53.89, 18.88, 53.89,
                                -0.06);
    rr_renderer_bezier_curve_to(renderer, 53.89, -18.99, 71.60, -34.34, 93.45,
                                -34.34);
    rr_renderer_fill(renderer);
    rr_renderer_set_fill(renderer, 0xffb8b8b8);
    rr_renderer_begin_path(renderer);
    rr_renderer_move_to(renderer, 82.89, 32.98);
    rr_renderer_line_to(renderer, -86.08, -0.05);
    rr_renderer_line_to(renderer, 82.89, -33.09);
    rr_renderer_fill(renderer);
}

void rr_ornithomimus_wing1_draw(struct rr_renderer *renderer)
{
    rr_renderer_set_fill(renderer, 0xff585858);
    rr_renderer_begin_path(renderer);
    rr_renderer_move_to(renderer, -59.56, -48.54);
    rr_renderer_line_to(renderer, -75.48, -45.10);
    rr_renderer_line_to(renderer, -76.90, -35.86);
    rr_renderer_line_to(renderer, -73.81, -29.72);
    rr_renderer_line_to(renderer, -65.93, -24.19);
    rr_renderer_line_to(renderer, -59.90, -25.82);
    rr_renderer_line_to(renderer, -58.45, -19.19);
    rr_renderer_line_to(renderer, -46.73, -12.86);
    rr_renderer_line_to(renderer, -41.12, -15.76);
    rr_renderer_line_to(renderer, -39.56, -9.85);
    rr_renderer_line_to(renderer, -20.93, 0.04);
    rr_renderer_line_to(renderer, -34.08, 27.66);
    rr_renderer_line_to(renderer, 23.25, -3.04);
    rr_renderer_fill(renderer);
    rr_renderer_set_fill(renderer, 0xff6e6e6e);
    rr_renderer_begin_path(renderer);
    rr_renderer_move_to(renderer, -18.31, 11.78);
    rr_renderer_line_to(renderer, -11.83, -2.09);
    rr_renderer_line_to(renderer, -35.53, -14.38);
    rr_renderer_line_to(renderer, -39.11, -22.69);
    rr_renderer_line_to(renderer, -47.15, -18.85);
    rr_renderer_line_to(renderer, -53.86, -21.98);
    rr_renderer_line_to(renderer, -55.88, -31.63);
    rr_renderer_line_to(renderer, -65.93, -29.14);
    rr_renderer_line_to(renderer, -69.96, -32.27);
    rr_renderer_line_to(renderer, -72.19, -37.19);
    rr_renderer_line_to(renderer, -71.30, -40.99);
    rr_renderer_line_to(renderer, -56.77, -44.57);
    rr_renderer_line_to(renderer, 7.62, -12.15);
    rr_renderer_line_to(renderer, 9.41, -1.19);
    rr_renderer_line_to(renderer, -4.23, 12.89);
    rr_renderer_fill(renderer);
    rr_renderer_set_fill(renderer, 0xffa7a7a7);
    rr_renderer_begin_path(renderer);
    rr_renderer_move_to(renderer, -63.47, -48.11);
    rr_renderer_bezier_curve_to(renderer, -70.73, -45.24, -6.02, -23.04, 2.71,
                                -12.03);
    rr_renderer_bezier_curve_to(renderer, 11.43, -1.02, -15.44, 14.26, -11.09,
                                17.96);
    rr_renderer_bezier_curve_to(renderer, -6.75, 21.67, 19.23, 18.07, 28.79,
                                10.20);
    rr_renderer_bezier_curve_to(renderer, 38.35, 2.32, 61.65, -19.55, 46.27,
                                -29.27);
    rr_renderer_bezier_curve_to(renderer, 30.90, -38.99, -56.20, -50.98, -63.47,
                                -48.11);
    rr_renderer_fill(renderer);
    rr_renderer_set_fill(renderer, 0xffa7a7a7);
    rr_renderer_begin_path(renderer);
    rr_renderer_move_to(renderer, 6.81, 38.06);
    rr_renderer_bezier_curve_to(renderer, 11.25, 43.85, 19.04, 44.38, 24.21,
                                39.24);
    rr_renderer_line_to(renderer, 67.53, -3.79);
    rr_renderer_bezier_curve_to(renderer, 70.01, -6.26, 71.55, -9.73, 71.80,
                                -13.44);
    rr_renderer_bezier_curve_to(renderer, 72.05, -17.15, 70.99, -20.80, 68.86,
                                -23.58);
    rr_renderer_bezier_curve_to(renderer, 64.42, -29.36, 56.63, -29.89, 51.46,
                                -24.75);
    rr_renderer_line_to(renderer, 8.15, 18.28);
    rr_renderer_bezier_curve_to(renderer, 2.97, 23.42, 2.37, 32.28, 6.81,
                                38.06);
    rr_renderer_fill(renderer);
    rr_renderer_set_fill(renderer, 0xffa7a7a7);
    rr_renderer_begin_path(renderer);
    rr_renderer_move_to(renderer, 42.42, -12.15);
    rr_renderer_bezier_curve_to(renderer, 22.65, -15.39, -59.91, -45.06, -56.66,
                                -47.76);
    rr_renderer_bezier_curve_to(renderer, -53.40, -50.46, 45.44, -34.29, 61.95,
                                -28.35);
    rr_renderer_bezier_curve_to(renderer, 78.47, -22.42, 62.19, -8.92, 42.42,
                                -12.15);
    rr_renderer_fill(renderer);
    rr_renderer_set_fill(renderer, 0xffb8b8b8);
    rr_renderer_begin_path(renderer);
    rr_renderer_move_to(renderer, 3.31, 36.20);
    rr_renderer_bezier_curve_to(renderer, 6.55, 40.43, 12.24, 40.81, 16.01,
                                37.06);
    rr_renderer_line_to(renderer, 58.05, -4.68);
    rr_renderer_bezier_curve_to(renderer, 59.86, -6.49, 60.98, -9.02, 61.17,
                                -11.73);
    rr_renderer_bezier_curve_to(renderer, 61.35, -14.44, 60.58, -17.10, 59.03,
                                -19.13);
    rr_renderer_bezier_curve_to(renderer, 55.79, -23.35, 50.10, -23.74, 46.33,
                                -19.98);
    rr_renderer_line_to(renderer, 4.29, 21.76);
    rr_renderer_bezier_curve_to(renderer, 0.51, 25.51, 0.08, 31.98, 3.31,
                                36.20);
    rr_renderer_fill(renderer);
    rr_renderer_set_fill(renderer, 0xffb8b8b8);
    rr_renderer_begin_path(renderer);
    rr_renderer_move_to(renderer, 55.25, -22.32);
    rr_renderer_bezier_curve_to(renderer, 44.25, -28.58, -21.18, -40.69, -28.37,
                                -38.86);
    rr_renderer_bezier_curve_to(renderer, -35.56, -37.03, 8.15, -21.72, 12.10,
                                -11.36);
    rr_renderer_bezier_curve_to(renderer, 16.05, -1.00, -8.92, 21.62, -4.67,
                                23.29);
    rr_renderer_bezier_curve_to(renderer, -0.42, 24.97, 27.60, 6.30, 37.59,
                                -1.30);
    rr_renderer_bezier_curve_to(renderer, 47.57, -8.90, 66.24, -16.06, 55.25,
                                -22.32);
    rr_renderer_fill(renderer);
}

void rr_ornithomimus_wing2_draw(struct rr_renderer *renderer)
{
    rr_renderer_set_fill(renderer, 0xff585858);
    rr_renderer_begin_path(renderer);
    rr_renderer_move_to(renderer, -59.56, 48.54);
    rr_renderer_line_to(renderer, -75.48, 45.10);
    rr_renderer_line_to(renderer, -76.89, 35.86);
    rr_renderer_line_to(renderer, -73.81, 29.72);
    rr_renderer_line_to(renderer, -65.92, 24.19);
    rr_renderer_line_to(renderer, -59.90, 25.82);
    rr_renderer_line_to(renderer, -58.45, 19.19);
    rr_renderer_line_to(renderer, -46.72, 12.86);
    rr_renderer_line_to(renderer, -41.12, 15.75);
    rr_renderer_line_to(renderer, -39.56, 9.85);
    rr_renderer_line_to(renderer, -20.93, -0.04);
    rr_renderer_line_to(renderer, -34.08, -27.67);
    rr_renderer_line_to(renderer, 23.25, 3.04);
    rr_renderer_fill(renderer);
    rr_renderer_set_fill(renderer, 0xff6e6e6e);
    rr_renderer_begin_path(renderer);
    rr_renderer_move_to(renderer, -18.31, -11.78);
    rr_renderer_line_to(renderer, -11.83, 2.08);
    rr_renderer_line_to(renderer, -35.52, 14.38);
    rr_renderer_line_to(renderer, -39.10, 22.69);
    rr_renderer_line_to(renderer, -47.15, 18.85);
    rr_renderer_line_to(renderer, -53.86, 21.98);
    rr_renderer_line_to(renderer, -55.87, 31.63);
    rr_renderer_line_to(renderer, -65.93, 29.14);
    rr_renderer_line_to(renderer, -69.96, 32.27);
    rr_renderer_line_to(renderer, -72.19, 37.19);
    rr_renderer_line_to(renderer, -71.30, 40.99);
    rr_renderer_line_to(renderer, -56.77, 44.56);
    rr_renderer_line_to(renderer, 7.62, 12.15);
    rr_renderer_line_to(renderer, 9.41, 1.19);
    rr_renderer_line_to(renderer, -4.22, -12.90);
    rr_renderer_fill(renderer);
    rr_renderer_set_fill(renderer, 0xffa7a7a7);
    rr_renderer_begin_path(renderer);
    rr_renderer_move_to(renderer, -63.46, 48.11);
    rr_renderer_bezier_curve_to(renderer, -70.73, 45.24, -6.02, 23.04, 2.71,
                                12.03);
    rr_renderer_bezier_curve_to(renderer, 11.44, 1.02, -15.44, -14.26, -11.09,
                                -17.96);
    rr_renderer_bezier_curve_to(renderer, -6.74, -21.67, 19.23, -18.07, 28.79,
                                -10.20);
    rr_renderer_bezier_curve_to(renderer, 38.35, -2.32, 61.65, 19.55, 46.28,
                                29.27);
    rr_renderer_bezier_curve_to(renderer, 30.90, 38.99, -56.20, 50.98, -63.46,
                                48.11);
    rr_renderer_fill(renderer);
    rr_renderer_set_fill(renderer, 0xffa7a7a7);
    rr_renderer_begin_path(renderer);
    rr_renderer_move_to(renderer, 6.81, -38.07);
    rr_renderer_bezier_curve_to(renderer, 11.25, -43.85, 19.04, -44.38, 24.21,
                                -39.24);
    rr_renderer_line_to(renderer, 67.53, 3.79);
    rr_renderer_bezier_curve_to(renderer, 70.01, 6.26, 71.55, 9.73, 71.80,
                                13.44);
    rr_renderer_bezier_curve_to(renderer, 72.05, 17.15, 70.99, 20.80, 68.86,
                                23.57);
    rr_renderer_bezier_curve_to(renderer, 64.43, 29.36, 56.64, 29.89, 51.46,
                                24.75);
    rr_renderer_line_to(renderer, 8.15, -18.28);
    rr_renderer_bezier_curve_to(renderer, 2.97, -23.42, 2.38, -32.28, 6.81,
                                -38.07);
    rr_renderer_fill(renderer);
    rr_renderer_set_fill(renderer, 0xffa7a7a7);
    rr_renderer_begin_path(renderer);
    rr_renderer_move_to(renderer, 42.42, 12.15);
    rr_renderer_bezier_curve_to(renderer, 22.65, 15.39, -59.91, 45.06, -56.66,
                                47.76);
    rr_renderer_bezier_curve_to(renderer, -53.40, 50.46, 45.44, 34.29, 61.96,
                                28.35);
    rr_renderer_bezier_curve_to(renderer, 78.47, 22.42, 62.19, 8.92, 42.42,
                                12.15);
    rr_renderer_fill(renderer);
    rr_renderer_set_fill(renderer, 0xffb8b8b8);
    rr_renderer_begin_path(renderer);
    rr_renderer_move_to(renderer, 3.32, -36.20);
    rr_renderer_bezier_curve_to(renderer, 6.55, -40.43, 12.24, -40.81, 16.01,
                                -37.06);
    rr_renderer_line_to(renderer, 58.05, 4.68);
    rr_renderer_bezier_curve_to(renderer, 59.86, 6.48, 60.99, 9.02, 61.17,
                                11.73);
    rr_renderer_bezier_curve_to(renderer, 61.35, 14.43, 60.58, 17.10, 59.03,
                                19.12);
    rr_renderer_bezier_curve_to(renderer, 55.79, 23.35, 50.10, 23.73, 46.33,
                                19.98);
    rr_renderer_line_to(renderer, 4.29, -21.76);
    rr_renderer_bezier_curve_to(renderer, 0.52, -25.51, 0.08, -31.98, 3.32,
                                -36.20);
    rr_renderer_fill(renderer);
    rr_renderer_set_fill(renderer, 0xffb8b8b8);
    rr_renderer_begin_path(renderer);
    rr_renderer_move_to(renderer, 55.25, 22.32);
    rr_renderer_bezier_curve_to(renderer, 44.26, 28.58, -21.18, 40.69, -28.37,
                                38.86);
    rr_renderer_bezier_curve_to(renderer, -35.56, 37.03, 8.15, 21.72, 12.10,
                                11.36);
    rr_renderer_bezier_curve_to(renderer, 16.05, 1.00, -8.92, -21.62, -4.67,
                                -23.30);
    rr_renderer_bezier_curve_to(renderer, -0.42, -24.97, 27.60, -6.30, 37.59,
                                1.30);
    rr_renderer_bezier_curve_to(renderer, 47.57, 8.90, 66.24, 16.06, 55.25,
                                22.32);
    rr_renderer_fill(renderer);
}