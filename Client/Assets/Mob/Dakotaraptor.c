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

void rr_dakotaraptor_body_draw(struct rr_renderer *renderer)
{
    rr_renderer_set_fill(renderer, 0xff85929c);
    rr_renderer_begin_path(renderer);
    rr_renderer_move_to(renderer, -24.12, -53.82);
    rr_renderer_bezier_curve_to(renderer, 29.40, -53.82, 72.78, -29.72, 72.78,
                                -0.01);
    rr_renderer_bezier_curve_to(renderer, 72.78, 14.27, 62.58, 27.95, 44.40,
                                38.04);
    rr_renderer_bezier_curve_to(renderer, 26.23, 48.14, 1.58, 53.81, -24.12,
                                53.81);
    rr_renderer_bezier_curve_to(renderer, -77.64, 53.81, -121.02, 29.71,
                                -121.02, -0.01);
    rr_renderer_bezier_curve_to(renderer, -121.02, -29.72, -77.64, -53.82,
                                -24.12, -53.82);
    rr_renderer_fill(renderer);
    rr_renderer_set_fill(renderer, 0xff6e7a82);
    rr_renderer_begin_path(renderer);
    rr_renderer_move_to(renderer, -24.13, -61.07);
    rr_renderer_bezier_curve_to(renderer, 36.61, -61.07, 85.84, -33.73, 85.84,
                                -0.00);
    rr_renderer_bezier_curve_to(renderer, 85.84, 16.20, 74.26, 31.73, 53.63,
                                43.18);
    rr_renderer_bezier_curve_to(renderer, 33.01, 54.63, 5.04, 61.07, -24.13,
                                61.07);
    rr_renderer_bezier_curve_to(renderer, -84.86, 61.07, -134.10, 33.73,
                                -134.10, -0.00);
    rr_renderer_bezier_curve_to(renderer, -134.10, -33.73, -84.86, -61.07,
                                -24.13, -61.07);
    rr_renderer_move_to(renderer, -24.13, -47.21);
    rr_renderer_bezier_curve_to(renderer, -77.21, -47.21, -120.24, -26.07,
                                -120.24, -0.00);
    rr_renderer_bezier_curve_to(renderer, -120.24, 26.07, -77.21, 47.21, -24.13,
                                47.21);
    rr_renderer_bezier_curve_to(renderer, 28.95, 47.21, 71.98, 26.07, 71.98,
                                -0.00);
    rr_renderer_bezier_curve_to(renderer, 71.98, -26.07, 28.95, -47.21, -24.13,
                                -47.21);
    rr_renderer_fill(renderer);
    rr_renderer_set_fill(renderer, 0xff6e7a82);
    rr_renderer_begin_path(renderer);
    rr_renderer_move_to(renderer, 92.65, -41.43);
    rr_renderer_bezier_curve_to(renderer, 115.54, -41.43, 134.10, -22.87,
                                134.10, 0.02);
    rr_renderer_bezier_curve_to(renderer, 134.10, 11.01, 129.73, 21.55, 121.96,
                                29.33);
    rr_renderer_bezier_curve_to(renderer, 114.19, 37.10, 103.65, 41.47, 92.65,
                                41.47);
    rr_renderer_line_to(renderer, 48.81, 41.47);
    rr_renderer_bezier_curve_to(renderer, 25.92, 41.47, 7.36, 22.91, 7.36,
                                0.02);
    rr_renderer_bezier_curve_to(renderer, 7.36, -22.87, 25.92, -41.43, 48.81,
                                -41.43);
    rr_renderer_fill(renderer);
    rr_renderer_set_fill(renderer, 0xff85929c);
    rr_renderer_begin_path(renderer);
    rr_renderer_move_to(renderer, 90.02, -29.77);
    rr_renderer_bezier_curve_to(renderer, 106.47, -29.77, 119.81, -16.43,
                                119.81, 0.02);
    rr_renderer_bezier_curve_to(renderer, 119.81, 7.92, 116.67, 15.50, 111.09,
                                21.08);
    rr_renderer_bezier_curve_to(renderer, 105.50, 26.67, 97.92, 29.81, 90.02,
                                29.81);
    rr_renderer_line_to(renderer, 22.86, 29.81);
    rr_renderer_bezier_curve_to(renderer, 6.41, 29.81, -6.93, 16.47, -6.93,
                                0.02);
    rr_renderer_bezier_curve_to(renderer, -6.93, -16.43, 6.41, -29.77, 22.86,
                                -29.77);
    rr_renderer_fill(renderer);
}

void rr_dakotaraptor_head_draw(struct rr_renderer *renderer)
{
    rr_renderer_set_fill(renderer, 0xff6e6356);
    rr_renderer_begin_path(renderer);
    rr_renderer_move_to(renderer, 19.14, -37.63);
    rr_renderer_line_to(renderer, 78.16, -21.91);
    rr_renderer_line_to(renderer, 78.16, 21.89);
    rr_renderer_line_to(renderer, 19.14, 37.61);
    rr_renderer_fill(renderer);
    rr_renderer_set_fill(renderer, 0xff6e6356);
    rr_renderer_begin_path(renderer);
    rr_renderer_move_to(renderer, 74.40, -22.22);
    rr_renderer_bezier_curve_to(renderer, 86.67, -22.22, 96.62, -12.27, 96.62,
                                -0.00);
    rr_renderer_bezier_curve_to(renderer, 96.62, 5.89, 94.28, 11.54, 90.11,
                                15.71);
    rr_renderer_bezier_curve_to(renderer, 85.95, 19.88, 80.29, 22.22, 74.40,
                                22.22);
    rr_renderer_bezier_curve_to(renderer, 62.13, 22.22, 52.18, 12.27, 52.18,
                                -0.00);
    rr_renderer_bezier_curve_to(renderer, 52.18, -12.27, 62.13, -22.22, 74.40,
                                -22.22);
    rr_renderer_fill(renderer);
    rr_renderer_set_fill(renderer, 0xff85929c);
    rr_renderer_begin_path(renderer);
    rr_renderer_move_to(renderer, -13.72, -41.89);
    rr_renderer_bezier_curve_to(renderer, 11.56, -41.89, 32.06, -23.16, 32.06,
                                -0.06);
    rr_renderer_bezier_curve_to(renderer, 32.06, 11.03, 27.24, 21.67, 18.65,
                                29.52);
    rr_renderer_bezier_curve_to(renderer, 10.06, 37.36, -1.58, 41.77, -13.72,
                                41.77);
    rr_renderer_bezier_curve_to(renderer, -39.00, 41.77, -59.50, 23.04, -59.50,
                                -0.06);
    rr_renderer_bezier_curve_to(renderer, -59.50, -23.16, -39.00, -41.89,
                                -13.72, -41.89);
    rr_renderer_fill(renderer);
    rr_renderer_set_fill(renderer, 0xff6e7a82);
    rr_renderer_begin_path(renderer);
    rr_renderer_move_to(renderer, -13.72, -47.52);
    rr_renderer_bezier_curve_to(renderer, 14.97, -47.52, 38.23, -26.27, 38.23,
                                -0.04);
    rr_renderer_bezier_curve_to(renderer, 38.23, 12.55, 32.76, 24.62, 23.01,
                                33.53);
    rr_renderer_bezier_curve_to(renderer, 13.27, 42.43, 0.06, 47.44, -13.72,
                                47.44);
    rr_renderer_bezier_curve_to(renderer, -42.42, 47.44, -65.68, 26.18, -65.68,
                                -0.04);
    rr_renderer_bezier_curve_to(renderer, -65.68, -26.27, -42.42, -47.52,
                                -13.72, -47.52);
    rr_renderer_move_to(renderer, -13.72, -34.35);
    rr_renderer_bezier_curve_to(renderer, -35.14, -34.35, -52.50, -18.99,
                                -52.50, -0.04);
    rr_renderer_bezier_curve_to(renderer, -52.50, 18.90, -35.14, 34.26, -13.72,
                                34.26);
    rr_renderer_bezier_curve_to(renderer, 7.69, 34.26, 25.05, 18.90, 25.05,
                                -0.04);
    rr_renderer_bezier_curve_to(renderer, 25.05, -18.99, 7.69, -34.35, -13.72,
                                -34.35);
    rr_renderer_fill(renderer);
    rr_renderer_set_fill(renderer, 0xff85929c);
    rr_renderer_begin_path(renderer);
    rr_renderer_move_to(renderer, 4.70, -30.29);
    rr_renderer_bezier_curve_to(renderer, 1.57, -25.89, 4.52, -20.87, 11.29,
                                -19.08);
    rr_renderer_bezier_curve_to(renderer, 18.07, -17.29, 26.10, -19.40, 29.23,
                                -23.81);
    rr_renderer_bezier_curve_to(renderer, 19.90, -23.84, 11.11, -26.16, 4.70,
                                -30.29);
    rr_renderer_fill(renderer);
    rr_renderer_set_fill(renderer, 0xff85929c);
    rr_renderer_begin_path(renderer);
    rr_renderer_move_to(renderer, 4.70, 30.24);
    rr_renderer_bezier_curve_to(renderer, 1.57, 25.83, 4.52, 20.81, 11.29,
                                19.02);
    rr_renderer_bezier_curve_to(renderer, 18.07, 17.23, 26.10, 19.35, 29.23,
                                23.75);
    rr_renderer_bezier_curve_to(renderer, 19.90, 23.78, 11.11, 26.10, 4.70,
                                30.24);
    rr_renderer_fill(renderer);
    rr_renderer_set_fill(renderer, 0xff6e6356);
    rr_renderer_begin_path(renderer);
    rr_renderer_move_to(renderer, 20.15, -37.37);
    rr_renderer_bezier_curve_to(renderer, 17.53, -38.19, 15.21, -39.84, 14.22,
                                -38.66);
    rr_renderer_bezier_curve_to(renderer, 13.23, -37.48, 13.36, -32.55, 14.22,
                                -30.28);
    rr_renderer_bezier_curve_to(renderer, 15.08, -28.02, 16.84, -26.44, 19.37,
                                -25.07);
    rr_renderer_bezier_curve_to(renderer, 21.91, -23.69, 26.12, -22.56, 29.43,
                                -22.04);
    rr_renderer_bezier_curve_to(renderer, 32.73, -21.51, 39.13, -19.95, 39.22,
                                -21.91);
    rr_renderer_bezier_curve_to(renderer, 39.30, -23.86, 33.12, -31.19, 29.94,
                                -33.76);
    rr_renderer_bezier_curve_to(renderer, 26.76, -36.34, 22.77, -36.56, 20.15,
                                -37.37);
    rr_renderer_fill(renderer);
    rr_renderer_set_fill(renderer, 0xff6e6356);
    rr_renderer_begin_path(renderer);
    rr_renderer_move_to(renderer, 20.15, 37.27);
    rr_renderer_bezier_curve_to(renderer, 17.53, 38.09, 15.21, 39.74, 14.22,
                                38.56);
    rr_renderer_bezier_curve_to(renderer, 13.23, 37.38, 13.36, 32.45, 14.22,
                                30.19);
    rr_renderer_bezier_curve_to(renderer, 15.08, 27.92, 16.84, 26.34, 19.37,
                                24.97);
    rr_renderer_bezier_curve_to(renderer, 21.91, 23.59, 26.12, 22.47, 29.43,
                                21.94);
    rr_renderer_bezier_curve_to(renderer, 32.73, 21.41, 39.13, 19.86, 39.22,
                                21.81);
    rr_renderer_bezier_curve_to(renderer, 39.30, 23.77, 33.12, 31.09, 29.94,
                                33.67);
    rr_renderer_bezier_curve_to(renderer, 26.76, 36.24, 22.77, 36.46, 20.15,
                                37.27);
    rr_renderer_fill(renderer);
    rr_renderer_set_fill(renderer, 0xff827566);
    rr_renderer_begin_path(renderer);
    rr_renderer_move_to(renderer, 19.14, -24.91);
    rr_renderer_line_to(renderer, 78.16, -10.05);
    rr_renderer_line_to(renderer, 78.16, 9.94);
    rr_renderer_line_to(renderer, 19.14, 24.79);
    rr_renderer_fill(renderer);
    rr_renderer_set_fill(renderer, 0xff85929c);
    rr_renderer_begin_path(renderer);
    rr_renderer_move_to(renderer, 16.72, -24.85);
    rr_renderer_bezier_curve_to(renderer, 30.36, -24.85, 41.41, -13.73, 41.41,
                                -0.00);
    rr_renderer_bezier_curve_to(renderer, 41.41, 6.59, 38.81, 12.91, 34.18,
                                17.57);
    rr_renderer_bezier_curve_to(renderer, 29.55, 22.23, 23.27, 24.85, 16.72,
                                24.85);
    rr_renderer_bezier_curve_to(renderer, 3.08, 24.85, -7.97, 13.72, -7.97,
                                -0.00);
    rr_renderer_bezier_curve_to(renderer, -7.97, -13.73, 3.08, -24.85, 16.72,
                                -24.85);
    rr_renderer_fill(renderer);
    rr_renderer_set_fill(renderer, 0xff827566);
    rr_renderer_begin_path(renderer);
    rr_renderer_move_to(renderer, 74.40, -10.69);
    rr_renderer_bezier_curve_to(renderer, 80.31, -10.69, 85.09, -5.91, 85.09,
                                -0.00);
    rr_renderer_bezier_curve_to(renderer, 85.09, 2.83, 83.97, 5.55, 81.96,
                                7.56);
    rr_renderer_bezier_curve_to(renderer, 79.96, 9.57, 77.24, 10.69, 74.40,
                                10.69);
    rr_renderer_bezier_curve_to(renderer, 68.50, 10.69, 63.71, 5.90, 63.71,
                                -0.00);
    rr_renderer_bezier_curve_to(renderer, 63.71, -5.91, 68.50, -10.69, 74.40,
                                -10.69);
    rr_renderer_fill(renderer);
    rr_renderer_set_fill(renderer, 0xff46555e);
    rr_renderer_begin_path(renderer);
    rr_renderer_move_to(renderer, -89.38, 63.46);
    rr_renderer_bezier_curve_to(renderer, -93.38, 55.00, -75.20, 36.58, -48.77,
                                22.33);
    rr_renderer_bezier_curve_to(renderer, -22.35, 8.07, 2.32, 3.38, 6.31,
                                11.85);
    rr_renderer_bezier_curve_to(renderer, -5.33, 10.75, -25.69, 17.04, -46.08,
                                28.04);
    rr_renderer_bezier_curve_to(renderer, -66.47, 39.03, -83.29, 52.80, -89.38,
                                63.46);
    rr_renderer_fill(renderer);
    rr_renderer_set_fill(renderer, 0xff46555e);
    rr_renderer_begin_path(renderer);
    rr_renderer_move_to(renderer, -85.73, 63.31);
    rr_renderer_bezier_curve_to(renderer, -87.37, 64.20, -89.16, 63.95, -89.72,
                                62.76);
    rr_renderer_bezier_curve_to(renderer, -89.99, 62.19, -89.93, 61.48, -89.57,
                                60.77);
    rr_renderer_bezier_curve_to(renderer, -89.20, 60.07, -88.55, 59.44, -87.76,
                                59.01);
    rr_renderer_bezier_curve_to(renderer, -86.12, 58.13, -84.34, 58.37, -83.78,
                                59.56);
    rr_renderer_bezier_curve_to(renderer, -83.21, 60.75, -84.09, 62.43, -85.73,
                                63.31);
    rr_renderer_fill(renderer);
    rr_renderer_set_fill(renderer, 0xff46555e);
    rr_renderer_begin_path(renderer);
    rr_renderer_move_to(renderer, 4.03, 14.90);
    rr_renderer_bezier_curve_to(renderer, 2.39, 15.79, 0.60, 15.54, 0.04,
                                14.36);
    rr_renderer_bezier_curve_to(renderer, -0.23, 13.79, -0.18, 13.07, 0.19,
                                12.37);
    rr_renderer_bezier_curve_to(renderer, 0.56, 11.66, 1.21, 11.03, 1.99,
                                10.61);
    rr_renderer_bezier_curve_to(renderer, 3.63, 9.72, 5.42, 9.97, 5.98, 11.15);
    rr_renderer_bezier_curve_to(renderer, 6.54, 12.34, 5.67, 14.02, 4.03,
                                14.90);
    rr_renderer_fill(renderer);
    rr_renderer_set_fill(renderer, 0xff46555e);
    rr_renderer_begin_path(renderer);
    rr_renderer_move_to(renderer, -85.47, 63.09);
    rr_renderer_bezier_curve_to(renderer, -89.85, 53.81, -73.53, 35.56, -49.01,
                                22.34);
    rr_renderer_bezier_curve_to(renderer, -24.49, 9.11, -1.07, 5.92, 3.31,
                                15.21);
    rr_renderer_bezier_curve_to(renderer, -27.14, 28.12, -57.66, 44.58, -85.47,
                                63.09);
    rr_renderer_fill(renderer);
    rr_renderer_set_fill(renderer, 0xff46555e);
    rr_renderer_begin_path(renderer);
    rr_renderer_move_to(renderer, -87.20, 62.27);
    rr_renderer_bezier_curve_to(renderer, -91.15, 53.90, -74.04, 36.15, -48.96,
                                22.62);
    rr_renderer_bezier_curve_to(renderer, -23.88, 9.10, -0.35, 4.92, 3.61,
                                13.30);
    rr_renderer_bezier_curve_to(renderer, -9.74, 14.84, -27.61, 21.21, -45.16,
                                30.67);
    rr_renderer_bezier_curve_to(renderer, -62.70, 40.14, -78.11, 51.72, -87.20,
                                62.27);
    rr_renderer_fill(renderer);
    rr_renderer_set_fill(renderer, 0xff46555e);
    rr_renderer_begin_path(renderer);
    rr_renderer_move_to(renderer, -89.39, -63.46);
    rr_renderer_bezier_curve_to(renderer, -93.38, -55.00, -75.20, -36.58,
                                -48.77, -22.33);
    rr_renderer_bezier_curve_to(renderer, -22.35, -8.07, 2.32, -3.38, 6.31,
                                -11.85);
    rr_renderer_bezier_curve_to(renderer, -5.33, -10.75, -25.69, -17.04, -46.08,
                                -28.04);
    rr_renderer_bezier_curve_to(renderer, -66.47, -39.03, -83.29, -52.80,
                                -89.39, -63.46);
    rr_renderer_fill(renderer);
    rr_renderer_set_fill(renderer, 0xff46555e);
    rr_renderer_begin_path(renderer);
    rr_renderer_move_to(renderer, -85.73, -63.31);
    rr_renderer_bezier_curve_to(renderer, -87.37, -64.20, -89.16, -63.95,
                                -89.72, -62.76);
    rr_renderer_bezier_curve_to(renderer, -89.99, -62.19, -89.93, -61.48,
                                -89.57, -60.78);
    rr_renderer_bezier_curve_to(renderer, -89.20, -60.07, -88.55, -59.44,
                                -87.76, -59.01);
    rr_renderer_bezier_curve_to(renderer, -86.12, -58.13, -84.34, -58.37,
                                -83.78, -59.56);
    rr_renderer_bezier_curve_to(renderer, -83.21, -60.75, -84.09, -62.43,
                                -85.73, -63.31);
    rr_renderer_fill(renderer);
    rr_renderer_set_fill(renderer, 0xff46555e);
    rr_renderer_begin_path(renderer);
    rr_renderer_move_to(renderer, 4.03, -14.90);
    rr_renderer_bezier_curve_to(renderer, 2.39, -15.79, 0.60, -15.55, 0.04,
                                -14.36);
    rr_renderer_bezier_curve_to(renderer, -0.23, -13.79, -0.18, -13.07, 0.19,
                                -12.37);
    rr_renderer_bezier_curve_to(renderer, 0.56, -11.67, 1.21, -11.03, 1.99,
                                -10.61);
    rr_renderer_bezier_curve_to(renderer, 3.63, -9.72, 5.42, -9.97, 5.98,
                                -11.15);
    rr_renderer_bezier_curve_to(renderer, 6.54, -12.34, 5.67, -14.02, 4.03,
                                -14.90);
    rr_renderer_fill(renderer);
    rr_renderer_set_fill(renderer, 0xff46555e);
    rr_renderer_begin_path(renderer);
    rr_renderer_move_to(renderer, -85.47, -63.09);
    rr_renderer_bezier_curve_to(renderer, -89.85, -53.81, -73.53, -35.56,
                                -49.01, -22.34);
    rr_renderer_bezier_curve_to(renderer, -24.49, -9.11, -1.07, -5.92, 3.31,
                                -15.21);
    rr_renderer_bezier_curve_to(renderer, -27.14, -28.12, -57.66, -44.58,
                                -85.47, -63.09);
    rr_renderer_fill(renderer);
    rr_renderer_set_fill(renderer, 0xff46555e);
    rr_renderer_begin_path(renderer);
    rr_renderer_move_to(renderer, -87.20, -62.27);
    rr_renderer_bezier_curve_to(renderer, -91.16, -53.90, -74.04, -36.15,
                                -48.96, -22.62);
    rr_renderer_bezier_curve_to(renderer, -23.88, -9.10, -0.35, -4.92, 3.61,
                                -13.30);
    rr_renderer_bezier_curve_to(renderer, -9.74, -14.84, -27.61, -21.21, -45.16,
                                -30.67);
    rr_renderer_bezier_curve_to(renderer, -62.70, -40.14, -78.11, -51.72,
                                -87.20, -62.27);
    rr_renderer_fill(renderer);
}

void rr_dakotaraptor_tail_draw(struct rr_renderer *renderer)
{
    rr_renderer_set_fill(renderer, 0xff46555e);
    rr_renderer_begin_path(renderer);
    rr_renderer_move_to(renderer, -107.80, -26.79);
    rr_renderer_bezier_curve_to(renderer, -123.11, -26.79, -135.52, -14.38,
                                -135.52, 0.93);
    rr_renderer_bezier_curve_to(renderer, -135.52, 8.28, -132.60, 15.33,
                                -127.40, 20.53);
    rr_renderer_bezier_curve_to(renderer, -122.21, 25.73, -115.16, 28.65,
                                -107.80, 28.65);
    rr_renderer_bezier_curve_to(renderer, -92.50, 28.65, -80.09, 16.24, -80.09,
                                0.93);
    rr_renderer_bezier_curve_to(renderer, -80.09, -14.38, -92.50, -26.79,
                                -107.80, -26.79);
    rr_renderer_fill(renderer);
    rr_renderer_set_fill(renderer, 0xff46555e);
    rr_renderer_begin_path(renderer);
    rr_renderer_move_to(renderer, -136.85, -8.47);
    rr_renderer_bezier_curve_to(renderer, -142.05, -8.47, -146.25, -4.26,
                                -146.25, 0.93);
    rr_renderer_bezier_curve_to(renderer, -146.25, 3.42, -145.26, 5.81, -143.50,
                                7.58);
    rr_renderer_bezier_curve_to(renderer, -141.74, 9.34, -139.35, 10.33,
                                -136.85, 10.33);
    rr_renderer_bezier_curve_to(renderer, -131.66, 10.33, -127.45, 6.12,
                                -127.45, 0.93);
    rr_renderer_bezier_curve_to(renderer, -127.45, -4.26, -131.66, -8.47,
                                -136.85, -8.47);
    rr_renderer_fill(renderer);
    rr_renderer_set_fill(renderer, 0xff46555e);
    rr_renderer_begin_path(renderer);
    rr_renderer_move_to(renderer, -125.73, 21.62);
    rr_renderer_line_to(renderer, -142.55, 8.39);
    rr_renderer_line_to(renderer, -133.08, 6.92);
    rr_renderer_fill(renderer);
    rr_renderer_set_fill(renderer, 0xff46555e);
    rr_renderer_begin_path(renderer);
    rr_renderer_move_to(renderer, -125.73, -19.86);
    rr_renderer_line_to(renderer, -142.55, -6.64);
    rr_renderer_line_to(renderer, -133.08, -5.17);
    rr_renderer_fill(renderer);
    rr_renderer_set_fill(renderer, 0xff46555e);
    rr_renderer_begin_path(renderer);
    rr_renderer_move_to(renderer, -93.14, 8.66);
    rr_renderer_bezier_curve_to(renderer, -107.01, 2.19, -113.01, -14.30,
                                -106.54, -28.18);
    rr_renderer_bezier_curve_to(renderer, -103.44, -34.84, -97.81, -39.99,
                                -90.90, -42.50);
    rr_renderer_bezier_curve_to(renderer, -83.99, -45.02, -76.37, -44.68,
                                -69.71, -41.58);
    rr_renderer_bezier_curve_to(renderer, -55.84, -35.11, -49.84, -18.61,
                                -56.31, -4.74);
    rr_renderer_bezier_curve_to(renderer, -62.78, 9.13, -79.27, 15.13, -93.14,
                                8.66);
    rr_renderer_fill(renderer);
    rr_renderer_set_fill(renderer, 0xff46555e);
    rr_renderer_begin_path(renderer);
    rr_renderer_move_to(renderer, -111.72, -20.21);
    rr_renderer_bezier_curve_to(renderer, -116.43, -22.41, -118.46, -28.01,
                                -116.26, -32.71);
    rr_renderer_bezier_curve_to(renderer, -115.20, -34.97, -113.29, -36.72,
                                -110.95, -37.57);
    rr_renderer_bezier_curve_to(renderer, -108.60, -38.42, -106.01, -38.30,
                                -103.75, -37.25);
    rr_renderer_bezier_curve_to(renderer, -99.05, -35.05, -97.02, -29.45,
                                -99.22, -24.74);
    rr_renderer_bezier_curve_to(renderer, -101.42, -20.04, -107.02, -18.01,
                                -111.72, -20.21);
    rr_renderer_fill(renderer);
    rr_renderer_set_fill(renderer, 0xff46555e);
    rr_renderer_begin_path(renderer);
    rr_renderer_move_to(renderer, -88.91, -42.78);
    rr_renderer_line_to(renderer, -109.75, -37.91);
    rr_renderer_line_to(renderer, -101.79, -32.57);
    rr_renderer_fill(renderer);
    rr_renderer_set_fill(renderer, 0xff46555e);
    rr_renderer_begin_path(renderer);
    rr_renderer_move_to(renderer, -106.46, -5.18);
    rr_renderer_line_to(renderer, -116.11, -24.28);
    rr_renderer_line_to(renderer, -106.90, -21.61);
    rr_renderer_fill(renderer);
    rr_renderer_set_fill(renderer, 0xff46555e);
    rr_renderer_begin_path(renderer);
    rr_renderer_move_to(renderer, -64.69, -6.99);
    rr_renderer_bezier_curve_to(renderer, -76.70, -16.48, -78.73, -33.92,
                                -69.24, -45.93);
    rr_renderer_bezier_curve_to(renderer, -64.68, -51.70, -58.01, -55.42,
                                -50.71, -56.27);
    rr_renderer_bezier_curve_to(renderer, -43.40, -57.13, -36.06, -55.04,
                                -30.29, -50.48);
    rr_renderer_bezier_curve_to(renderer, -18.28, -40.99, -16.24, -23.55,
                                -25.74, -11.54);
    rr_renderer_bezier_curve_to(renderer, -35.24, 0.47, -52.67, 2.51, -64.69,
                                -6.99);
    rr_renderer_fill(renderer);
    rr_renderer_set_fill(renderer, 0xff46555e);
    rr_renderer_begin_path(renderer);
    rr_renderer_move_to(renderer, -76.11, -39.36);
    rr_renderer_bezier_curve_to(renderer, -80.19, -42.59, -80.88, -48.51,
                                -77.65, -52.59);
    rr_renderer_bezier_curve_to(renderer, -76.10, -54.55, -73.84, -55.81,
                                -71.36, -56.10);
    rr_renderer_bezier_curve_to(renderer, -68.88, -56.39, -66.38, -55.69,
                                -64.42, -54.14);
    rr_renderer_bezier_curve_to(renderer, -60.34, -50.91, -59.65, -44.99,
                                -62.88, -40.91);
    rr_renderer_bezier_curve_to(renderer, -66.11, -36.83, -72.03, -36.14,
                                -76.11, -39.36);
    rr_renderer_fill(renderer);
    rr_renderer_set_fill(renderer, 0xff46555e);
    rr_renderer_begin_path(renderer);
    rr_renderer_move_to(renderer, -48.73, -56.08);
    rr_renderer_line_to(renderer, -70.12, -56.14);
    rr_renderer_line_to(renderer, -63.61, -49.11);
    rr_renderer_fill(renderer);
    rr_renderer_set_fill(renderer, 0xff46555e);
    rr_renderer_begin_path(renderer);
    rr_renderer_move_to(renderer, -74.46, -23.55);
    rr_renderer_line_to(renderer, -79.45, -44.35);
    rr_renderer_line_to(renderer, -71.11, -39.63);
    rr_renderer_fill(renderer);
    rr_renderer_set_fill(renderer, 0xff46555e);
    rr_renderer_begin_path(renderer);
    rr_renderer_move_to(renderer, -31.67, -18.43);
    rr_renderer_bezier_curve_to(renderer, -44.00, -27.52, -46.62, -44.88,
                                -37.53, -57.20);
    rr_renderer_bezier_curve_to(renderer, -33.17, -63.12, -26.63, -67.06,
                                -19.36, -68.16);
    rr_renderer_bezier_curve_to(renderer, -12.09, -69.26, -4.68, -67.42, 1.24,
                                -63.06);
    rr_renderer_bezier_curve_to(renderer, 13.56, -53.97, 16.19, -36.61, 7.10,
                                -24.29);
    rr_renderer_bezier_curve_to(renderer, -1.99, -11.96, -19.35, -9.34, -31.67,
                                -18.43);
    rr_renderer_fill(renderer);
    rr_renderer_set_fill(renderer, 0xff46555e);
    rr_renderer_begin_path(renderer);
    rr_renderer_move_to(renderer, -44.18, -50.41);
    rr_renderer_bezier_curve_to(renderer, -48.37, -53.49, -49.25, -59.39,
                                -46.17, -63.57);
    rr_renderer_bezier_curve_to(renderer, -44.68, -65.58, -42.46, -66.92,
                                -40.00, -67.29);
    rr_renderer_bezier_curve_to(renderer, -37.53, -67.66, -35.01, -67.04,
                                -33.00, -65.56);
    rr_renderer_bezier_curve_to(renderer, -28.82, -62.47, -27.93, -56.57,
                                -31.02, -52.39);
    rr_renderer_bezier_curve_to(renderer, -34.10, -48.21, -40.00, -47.32,
                                -44.18, -50.41);
    rr_renderer_fill(renderer);
    rr_renderer_set_fill(renderer, 0xff46555e);
    rr_renderer_begin_path(renderer);
    rr_renderer_move_to(renderer, -17.38, -68.03);
    rr_renderer_line_to(renderer, -38.76, -67.37);
    rr_renderer_line_to(renderer, -32.01, -60.57);
    rr_renderer_fill(renderer);
    rr_renderer_set_fill(renderer, 0xff46555e);
    rr_renderer_begin_path(renderer);
    rr_renderer_move_to(renderer, -42.00, -34.65);
    rr_renderer_line_to(renderer, -47.68, -55.27);
    rr_renderer_line_to(renderer, -39.19, -50.83);
    rr_renderer_fill(renderer);
    rr_renderer_set_fill(renderer, 0xff46555e);
    rr_renderer_begin_path(renderer);
    rr_renderer_move_to(renderer, 31.73, -26.26);
    rr_renderer_bezier_curve_to(renderer, 23.73, -35.35, 24.62, -49.20, 33.71,
                                -57.19);
    rr_renderer_bezier_curve_to(renderer, 38.08, -61.03, 43.79, -62.98, 49.59,
                                -62.60);
    rr_renderer_bezier_curve_to(renderer, 55.39, -62.23, 60.80, -59.57, 64.64,
                                -55.21);
    rr_renderer_bezier_curve_to(renderer, 72.63, -46.12, 71.74, -32.27, 62.66,
                                -24.28);
    rr_renderer_bezier_curve_to(renderer, 53.57, -16.28, 39.72, -17.17, 31.73,
                                -26.26);
    rr_renderer_fill(renderer);
    rr_renderer_set_fill(renderer, 0xff46555e);
    rr_renderer_begin_path(renderer);
    rr_renderer_move_to(renderer, 27.44, -53.06);
    rr_renderer_bezier_curve_to(renderer, 24.72, -56.15, 25.02, -60.85, 28.11,
                                -63.57);
    rr_renderer_bezier_curve_to(renderer, 29.59, -64.87, 31.53, -65.53, 33.50,
                                -65.40);
    rr_renderer_bezier_curve_to(renderer, 35.47, -65.28, 37.31, -64.37, 38.62,
                                -62.89);
    rr_renderer_bezier_curve_to(renderer, 41.33, -59.80, 41.03, -55.10, 37.94,
                                -52.39);
    rr_renderer_bezier_curve_to(renderer, 34.85, -49.67, 30.15, -49.98, 27.44,
                                -53.06);
    rr_renderer_fill(renderer);
    rr_renderer_set_fill(renderer, 0xff46555e);
    rr_renderer_begin_path(renderer);
    rr_renderer_move_to(renderer, 51.11, -62.18);
    rr_renderer_line_to(renderer, 34.47, -65.26);
    rr_renderer_line_to(renderer, 38.54, -58.87);
    rr_renderer_fill(renderer);
    rr_renderer_set_fill(renderer, 0xff46555e);
    rr_renderer_begin_path(renderer);
    rr_renderer_move_to(renderer, 26.47, -40.52);
    rr_renderer_line_to(renderer, 25.55, -57.41);
    rr_renderer_line_to(renderer, 31.36, -52.55);
    rr_renderer_fill(renderer);
    rr_renderer_set_fill(renderer, 0xff46555e);
    rr_renderer_begin_path(renderer);
    rr_renderer_move_to(renderer, 56.80, -28.07);
    rr_renderer_bezier_curve_to(renderer, 51.97, -36.25, 54.69, -46.79, 62.86,
                                -51.62);
    rr_renderer_bezier_curve_to(renderer, 66.79, -53.93, 71.47, -54.60, 75.89,
                                -53.46);
    rr_renderer_bezier_curve_to(renderer, 80.30, -52.32, 84.09, -49.48, 86.41,
                                -45.55);
    rr_renderer_bezier_curve_to(renderer, 91.23, -37.38, 88.52, -26.84, 80.34,
                                -22.01);
    rr_renderer_bezier_curve_to(renderer, 72.17, -17.18, 61.63, -19.90, 56.80,
                                -28.07);
    rr_renderer_fill(renderer);
    rr_renderer_set_fill(renderer, 0xff46555e);
    rr_renderer_begin_path(renderer);
    rr_renderer_move_to(renderer, 57.42, -49.36);
    rr_renderer_bezier_curve_to(renderer, 55.78, -52.13, 56.71, -55.71, 59.48,
                                -57.34);
    rr_renderer_bezier_curve_to(renderer, 60.82, -58.13, 62.41, -58.35, 63.90,
                                -57.96);
    rr_renderer_bezier_curve_to(renderer, 65.40, -57.58, 66.68, -56.61, 67.47,
                                -55.28);
    rr_renderer_bezier_curve_to(renderer, 69.10, -52.50, 68.18, -48.93, 65.40,
                                -47.29);
    rr_renderer_bezier_curve_to(renderer, 62.63, -45.66, 59.06, -46.58, 57.42,
                                -49.36);
    rr_renderer_fill(renderer);
    rr_renderer_set_fill(renderer, 0xff46555e);
    rr_renderer_begin_path(renderer);
    rr_renderer_move_to(renderer, 77.00, -52.90);
    rr_renderer_line_to(renderer, 64.64, -57.71);
    rr_renderer_line_to(renderer, 66.84, -52.19);
    rr_renderer_fill(renderer);
    rr_renderer_set_fill(renderer, 0xff46555e);
    rr_renderer_begin_path(renderer);
    rr_renderer_move_to(renderer, 54.84, -39.83);
    rr_renderer_line_to(renderer, 56.61, -52.98);
    rr_renderer_line_to(renderer, 60.38, -48.38);
    rr_renderer_fill(renderer);
    rr_renderer_set_fill(renderer, 0xff46555e);
    rr_renderer_begin_path(renderer);
    rr_renderer_move_to(renderer, -93.14, -8.66);
    rr_renderer_bezier_curve_to(renderer, -107.01, -2.19, -113.01, 14.30,
                                -106.54, 28.18);
    rr_renderer_bezier_curve_to(renderer, -103.43, 34.84, -97.80, 39.99, -90.90,
                                42.51);
    rr_renderer_bezier_curve_to(renderer, -83.99, 45.02, -76.37, 44.68, -69.70,
                                41.58);
    rr_renderer_bezier_curve_to(renderer, -55.83, 35.11, -49.83, 18.61, -56.30,
                                4.74);
    rr_renderer_bezier_curve_to(renderer, -62.77, -9.13, -79.26, -15.13, -93.14,
                                -8.66);
    rr_renderer_fill(renderer);
    rr_renderer_set_fill(renderer, 0xff46555e);
    rr_renderer_begin_path(renderer);
    rr_renderer_move_to(renderer, -111.72, 20.21);
    rr_renderer_bezier_curve_to(renderer, -116.42, 22.41, -118.45, 28.01,
                                -116.25, 32.71);
    rr_renderer_bezier_curve_to(renderer, -115.20, 34.97, -113.29, 36.72,
                                -110.94, 37.57);
    rr_renderer_bezier_curve_to(renderer, -108.60, 38.42, -106.01, 38.30,
                                -103.75, 37.25);
    rr_renderer_bezier_curve_to(renderer, -99.04, 35.05, -97.01, 29.45, -99.21,
                                24.74);
    rr_renderer_bezier_curve_to(renderer, -101.41, 20.04, -107.01, 18.01,
                                -111.72, 20.21);
    rr_renderer_fill(renderer);
    rr_renderer_set_fill(renderer, 0xff46555e);
    rr_renderer_begin_path(renderer);
    rr_renderer_move_to(renderer, -88.91, 42.78);
    rr_renderer_line_to(renderer, -109.74, 37.91);
    rr_renderer_line_to(renderer, -101.78, 32.57);
    rr_renderer_fill(renderer);
    rr_renderer_set_fill(renderer, 0xff46555e);
    rr_renderer_begin_path(renderer);
    rr_renderer_move_to(renderer, -106.46, 5.18);
    rr_renderer_line_to(renderer, -116.10, 24.28);
    rr_renderer_line_to(renderer, -106.90, 21.61);
    rr_renderer_fill(renderer);
    rr_renderer_set_fill(renderer, 0xff46555e);
    rr_renderer_begin_path(renderer);
    rr_renderer_move_to(renderer, -64.68, 6.99);
    rr_renderer_bezier_curve_to(renderer, -76.69, 16.48, -78.73, 33.92, -69.23,
                                45.93);
    rr_renderer_bezier_curve_to(renderer, -64.67, 51.70, -58.00, 55.42, -50.70,
                                56.27);
    rr_renderer_bezier_curve_to(renderer, -43.40, 57.13, -36.05, 55.04, -30.29,
                                50.48);
    rr_renderer_bezier_curve_to(renderer, -18.27, 40.99, -16.24, 23.55, -25.73,
                                11.54);
    rr_renderer_bezier_curve_to(renderer, -35.23, -0.47, -52.67, -2.51, -64.68,
                                6.99);
    rr_renderer_fill(renderer);
    rr_renderer_set_fill(renderer, 0xff46555e);
    rr_renderer_begin_path(renderer);
    rr_renderer_move_to(renderer, -76.10, 39.36);
    rr_renderer_bezier_curve_to(renderer, -80.18, 42.59, -80.87, 48.51, -77.65,
                                52.59);
    rr_renderer_bezier_curve_to(renderer, -76.10, 54.55, -73.83, 55.81, -71.35,
                                56.10);
    rr_renderer_bezier_curve_to(renderer, -68.87, 56.39, -66.38, 55.69, -64.42,
                                54.14);
    rr_renderer_bezier_curve_to(renderer, -60.34, 50.91, -59.65, 44.99, -62.88,
                                40.91);
    rr_renderer_bezier_curve_to(renderer, -66.10, 36.83, -72.02, 36.14, -76.10,
                                39.36);
    rr_renderer_fill(renderer);
    rr_renderer_set_fill(renderer, 0xff46555e);
    rr_renderer_begin_path(renderer);
    rr_renderer_move_to(renderer, -48.73, 56.08);
    rr_renderer_line_to(renderer, -70.12, 56.14);
    rr_renderer_line_to(renderer, -63.60, 49.11);
    rr_renderer_fill(renderer);
    rr_renderer_set_fill(renderer, 0xff46555e);
    rr_renderer_begin_path(renderer);
    rr_renderer_move_to(renderer, -74.45, 23.55);
    rr_renderer_line_to(renderer, -79.44, 44.35);
    rr_renderer_line_to(renderer, -71.10, 39.63);
    rr_renderer_fill(renderer);
    rr_renderer_set_fill(renderer, 0xff46555e);
    rr_renderer_begin_path(renderer);
    rr_renderer_move_to(renderer, -31.67, 18.43);
    rr_renderer_bezier_curve_to(renderer, -43.99, 27.52, -46.62, 44.88, -37.53,
                                57.20);
    rr_renderer_bezier_curve_to(renderer, -33.16, 63.12, -26.63, 67.06, -19.35,
                                68.16);
    rr_renderer_bezier_curve_to(renderer, -12.08, 69.26, -4.67, 67.42, 1.24,
                                63.06);
    rr_renderer_bezier_curve_to(renderer, 13.57, 53.97, 16.19, 36.61, 7.10,
                                24.29);
    rr_renderer_bezier_curve_to(renderer, -1.99, 11.96, -19.34, 9.34, -31.67,
                                18.43);
    rr_renderer_fill(renderer);
    rr_renderer_set_fill(renderer, 0xff46555e);
    rr_renderer_begin_path(renderer);
    rr_renderer_move_to(renderer, -6.65, -24.56);
    rr_renderer_bezier_curve_to(renderer, -16.39, -36.37, -14.72, -53.84, -2.91,
                                -63.59);
    rr_renderer_bezier_curve_to(renderer, 2.77, -68.26, 10.06, -70.50, 17.38,
                                -69.79);
    rr_renderer_bezier_curve_to(renderer, 24.70, -69.09, 31.44, -65.51, 36.12,
                                -59.84);
    rr_renderer_bezier_curve_to(renderer, 45.86, -48.03, 44.18, -30.55, 32.37,
                                -20.81);
    rr_renderer_bezier_curve_to(renderer, 20.56, -11.07, 3.09, -12.75, -6.65,
                                -24.56);
    rr_renderer_fill(renderer);
    rr_renderer_set_fill(renderer, 0xff46555e);
    rr_renderer_begin_path(renderer);
    rr_renderer_move_to(renderer, -11.01, -58.62);
    rr_renderer_bezier_curve_to(renderer, -14.31, -62.63, -13.74, -68.56, -9.73,
                                -71.86);
    rr_renderer_bezier_curve_to(renderer, -7.80, -73.45, -5.33, -74.21, -2.84,
                                -73.97);
    rr_renderer_bezier_curve_to(renderer, -0.36, -73.73, 1.93, -72.51, 3.51,
                                -70.59);
    rr_renderer_bezier_curve_to(renderer, 6.82, -66.58, 6.25, -60.65, 2.24,
                                -57.34);
    rr_renderer_bezier_curve_to(renderer, -1.77, -54.04, -7.70, -54.61, -11.01,
                                -58.62);
    rr_renderer_fill(renderer);
    rr_renderer_set_fill(renderer, 0xff46555e);
    rr_renderer_begin_path(renderer);
    rr_renderer_move_to(renderer, 19.29, -69.18);
    rr_renderer_line_to(renderer, -1.62, -73.74);
    rr_renderer_line_to(renderer, 3.27, -65.50);
    rr_renderer_fill(renderer);
    rr_renderer_set_fill(renderer, 0xff46555e);
    rr_renderer_begin_path(renderer);
    rr_renderer_move_to(renderer, -12.72, -42.79);
    rr_renderer_line_to(renderer, -13.22, -64.18);
    rr_renderer_line_to(renderer, -6.06, -57.81);
    rr_renderer_fill(renderer);
    rr_renderer_set_fill(renderer, 0xff46555e);
    rr_renderer_begin_path(renderer);
    rr_renderer_move_to(renderer, -6.65, 24.56);
    rr_renderer_bezier_curve_to(renderer, -16.39, 36.37, -14.71, 53.84, -2.90,
                                63.59);
    rr_renderer_bezier_curve_to(renderer, 2.77, 68.26, 10.07, 70.50, 17.39,
                                69.79);
    rr_renderer_bezier_curve_to(renderer, 24.71, 69.09, 31.45, 65.51, 36.12,
                                59.84);
    rr_renderer_bezier_curve_to(renderer, 45.86, 48.03, 44.19, 30.56, 32.38,
                                20.81);
    rr_renderer_bezier_curve_to(renderer, 20.56, 11.07, 3.09, 12.75, -6.65,
                                24.56);
    rr_renderer_fill(renderer);
    rr_renderer_set_fill(renderer, 0xff46555e);
    rr_renderer_begin_path(renderer);
    rr_renderer_move_to(renderer, -11.00, 58.62);
    rr_renderer_bezier_curve_to(renderer, -14.31, 62.63, -13.73, 68.56, -9.73,
                                71.86);
    rr_renderer_bezier_curve_to(renderer, -7.80, 73.45, -5.32, 74.21, -2.84,
                                73.97);
    rr_renderer_bezier_curve_to(renderer, -0.36, 73.73, 1.93, 72.51, 3.52,
                                70.59);
    rr_renderer_bezier_curve_to(renderer, 6.82, 66.58, 6.25, 60.65, 2.24,
                                57.34);
    rr_renderer_bezier_curve_to(renderer, -1.77, 54.04, -7.70, 54.61, -11.00,
                                58.62);
    rr_renderer_fill(renderer);
    rr_renderer_set_fill(renderer, 0xff46555e);
    rr_renderer_begin_path(renderer);
    rr_renderer_move_to(renderer, 19.29, 69.18);
    rr_renderer_line_to(renderer, -1.61, 73.74);
    rr_renderer_line_to(renderer, 3.28, 65.50);
    rr_renderer_fill(renderer);
    rr_renderer_set_fill(renderer, 0xff46555e);
    rr_renderer_begin_path(renderer);
    rr_renderer_move_to(renderer, -12.72, 42.79);
    rr_renderer_line_to(renderer, -13.21, 64.18);
    rr_renderer_line_to(renderer, -6.05, 57.81);
    rr_renderer_fill(renderer);
    rr_renderer_set_fill(renderer, 0xff46555e);
    rr_renderer_begin_path(renderer);
    rr_renderer_move_to(renderer, -44.18, 50.41);
    rr_renderer_bezier_curve_to(renderer, -48.36, 53.49, -49.25, 59.39, -46.16,
                                63.57);
    rr_renderer_bezier_curve_to(renderer, -44.68, 65.58, -42.46, 66.92, -39.99,
                                67.29);
    rr_renderer_bezier_curve_to(renderer, -37.52, 67.66, -35.01, 67.04, -33.00,
                                65.56);
    rr_renderer_bezier_curve_to(renderer, -28.81, 62.47, -27.92, 56.57, -31.01,
                                52.39);
    rr_renderer_bezier_curve_to(renderer, -34.10, 48.21, -39.99, 47.32, -44.18,
                                50.41);
    rr_renderer_fill(renderer);
    rr_renderer_set_fill(renderer, 0xff46555e);
    rr_renderer_begin_path(renderer);
    rr_renderer_move_to(renderer, -17.37, 68.03);
    rr_renderer_line_to(renderer, -38.75, 67.37);
    rr_renderer_line_to(renderer, -32.01, 60.57);
    rr_renderer_fill(renderer);
    rr_renderer_set_fill(renderer, 0xff46555e);
    rr_renderer_begin_path(renderer);
    rr_renderer_move_to(renderer, -41.99, 34.65);
    rr_renderer_line_to(renderer, -47.68, 55.27);
    rr_renderer_line_to(renderer, -39.19, 50.83);
    rr_renderer_fill(renderer);
    rr_renderer_set_fill(renderer, 0xff46555e);
    rr_renderer_begin_path(renderer);
    rr_renderer_move_to(renderer, 31.73, 26.26);
    rr_renderer_bezier_curve_to(renderer, 23.74, 35.35, 24.63, 49.20, 33.72,
                                57.19);
    rr_renderer_bezier_curve_to(renderer, 38.08, 61.03, 43.79, 62.98, 49.59,
                                62.60);
    rr_renderer_bezier_curve_to(renderer, 55.39, 62.23, 60.81, 59.57, 64.65,
                                55.21);
    rr_renderer_bezier_curve_to(renderer, 72.64, 46.12, 71.75, 32.27, 62.66,
                                24.28);
    rr_renderer_bezier_curve_to(renderer, 53.57, 16.28, 39.72, 17.17, 31.73,
                                26.26);
    rr_renderer_fill(renderer);
    rr_renderer_set_fill(renderer, 0xff46555e);
    rr_renderer_begin_path(renderer);
    rr_renderer_move_to(renderer, 27.44, 53.06);
    rr_renderer_bezier_curve_to(renderer, 24.73, 56.15, 25.03, 60.85, 28.12,
                                63.57);
    rr_renderer_bezier_curve_to(renderer, 29.60, 64.87, 31.54, 65.53, 33.51,
                                65.41);
    rr_renderer_bezier_curve_to(renderer, 35.48, 65.28, 37.32, 64.37, 38.62,
                                62.89);
    rr_renderer_bezier_curve_to(renderer, 41.34, 59.80, 41.03, 55.10, 37.94,
                                52.39);
    rr_renderer_bezier_curve_to(renderer, 34.86, 49.67, 30.15, 49.98, 27.44,
                                53.06);
    rr_renderer_fill(renderer);
    rr_renderer_set_fill(renderer, 0xff46555e);
    rr_renderer_begin_path(renderer);
    rr_renderer_move_to(renderer, 51.11, 62.18);
    rr_renderer_line_to(renderer, 34.48, 65.26);
    rr_renderer_line_to(renderer, 38.55, 58.87);
    rr_renderer_fill(renderer);
    rr_renderer_set_fill(renderer, 0xff46555e);
    rr_renderer_begin_path(renderer);
    rr_renderer_move_to(renderer, 26.48, 40.52);
    rr_renderer_line_to(renderer, 25.55, 57.41);
    rr_renderer_line_to(renderer, 31.37, 52.55);
    rr_renderer_fill(renderer);
    rr_renderer_set_fill(renderer, 0xff46555e);
    rr_renderer_begin_path(renderer);
    rr_renderer_move_to(renderer, 56.80, 28.07);
    rr_renderer_bezier_curve_to(renderer, 51.98, 36.25, 54.69, 46.79, 62.87,
                                51.62);
    rr_renderer_bezier_curve_to(renderer, 66.79, 53.93, 71.48, 54.60, 75.89,
                                53.46);
    rr_renderer_bezier_curve_to(renderer, 80.31, 52.32, 84.09, 49.48, 86.41,
                                45.55);
    rr_renderer_bezier_curve_to(renderer, 91.24, 37.38, 88.52, 26.84, 80.35,
                                22.01);
    rr_renderer_bezier_curve_to(renderer, 72.17, 17.18, 61.63, 19.90, 56.80,
                                28.07);
    rr_renderer_fill(renderer);
    rr_renderer_set_fill(renderer, 0xff46555e);
    rr_renderer_begin_path(renderer);
    rr_renderer_move_to(renderer, 57.43, 49.36);
    rr_renderer_bezier_curve_to(renderer, 55.79, 52.13, 56.71, 55.71, 59.49,
                                57.34);
    rr_renderer_bezier_curve_to(renderer, 60.82, 58.13, 62.41, 58.35, 63.91,
                                57.96);
    rr_renderer_bezier_curve_to(renderer, 65.41, 57.58, 66.69, 56.61, 67.47,
                                55.28);
    rr_renderer_bezier_curve_to(renderer, 69.11, 52.50, 68.18, 48.93, 65.41,
                                47.29);
    rr_renderer_bezier_curve_to(renderer, 62.64, 45.66, 59.06, 46.58, 57.43,
                                49.36);
    rr_renderer_fill(renderer);
    rr_renderer_set_fill(renderer, 0xff46555e);
    rr_renderer_begin_path(renderer);
    rr_renderer_move_to(renderer, 77.01, 52.90);
    rr_renderer_line_to(renderer, 64.64, 57.71);
    rr_renderer_line_to(renderer, 66.84, 52.19);
    rr_renderer_fill(renderer);
    rr_renderer_set_fill(renderer, 0xff46555e);
    rr_renderer_begin_path(renderer);
    rr_renderer_move_to(renderer, 54.85, 39.83);
    rr_renderer_line_to(renderer, 56.61, 52.98);
    rr_renderer_line_to(renderer, 60.38, 48.38);
    rr_renderer_fill(renderer);
    rr_renderer_set_fill(renderer, 0xff596a74);
    rr_renderer_begin_path(renderer);
    rr_renderer_move_to(renderer, -93.95, -12.98);
    rr_renderer_bezier_curve_to(renderer, -101.60, -20.63, -114.01, -20.63,
                                -121.66, -12.98);
    rr_renderer_quadratic_curve_to(renderer, -129.37, -5.26, -138.65, 0.88);
    rr_renderer_quadratic_curve_to(renderer, -129.37, 7.03, -121.66, 14.74);
    rr_renderer_bezier_curve_to(renderer, -114.01, 22.39, -101.60, 22.39,
                                -93.95, 14.74);
    rr_renderer_bezier_curve_to(renderer, -86.29, 7.09, -86.29, -5.32, -93.95,
                                -12.98);
    rr_renderer_fill(renderer);
    rr_renderer_set_fill(renderer, 0xff596a74);
    rr_renderer_begin_path(renderer);
    rr_renderer_move_to(renderer, -74.75, 2.02);
    rr_renderer_bezier_curve_to(renderer, -84.92, 5.71, -96.16, 0.47, -99.86,
                                -9.70);
    rr_renderer_quadratic_curve_to(renderer, -103.58, -19.94, -109.38, -29.43);
    rr_renderer_quadratic_curve_to(renderer, -98.38, -31.08, -88.14, -34.80);
    rr_renderer_bezier_curve_to(renderer, -77.97, -38.50, -66.73, -33.25,
                                -63.04, -23.09);
    rr_renderer_bezier_curve_to(renderer, -59.34, -12.92, -64.59, -1.68, -74.75,
                                2.02);
    rr_renderer_fill(renderer);
    rr_renderer_set_fill(renderer, 0xff596a74);
    rr_renderer_begin_path(renderer);
    rr_renderer_move_to(renderer, -45.25, -9.22);
    rr_renderer_bezier_curve_to(renderer, -56.00, -7.97, -65.73, -15.67, -66.99,
                                -26.42);
    rr_renderer_quadratic_curve_to(renderer, -68.25, -37.25, -71.71, -47.82);
    rr_renderer_quadratic_curve_to(renderer, -60.62, -46.89, -49.79, -48.15);
    rr_renderer_bezier_curve_to(renderer, -39.04, -49.40, -29.31, -41.70,
                                -28.06, -30.95);
    rr_renderer_bezier_curve_to(renderer, -26.80, -20.20, -34.50, -10.47,
                                -45.25, -9.22);
    rr_renderer_fill(renderer);
    rr_renderer_set_fill(renderer, 0xff596a74);
    rr_renderer_begin_path(renderer);
    rr_renderer_move_to(renderer, -12.34, -21.32);
    rr_renderer_bezier_curve_to(renderer, -23.04, -19.71, -33.02, -27.07,
                                -34.64, -37.76);
    rr_renderer_quadratic_curve_to(renderer, -36.27, -48.54, -40.09, -58.99);
    rr_renderer_quadratic_curve_to(renderer, -28.98, -58.43, -18.20, -60.06);
    rr_renderer_bezier_curve_to(renderer, -7.50, -61.68, 2.48, -54.32, 4.10,
                                -43.62);
    rr_renderer_bezier_curve_to(renderer, 5.72, -32.92, -1.64, -22.94, -12.34,
                                -21.32);
    rr_renderer_fill(renderer);
    rr_renderer_set_fill(renderer, 0xff596a74);
    rr_renderer_begin_path(renderer);
    rr_renderer_move_to(renderer, 47.17, -25.24);
    rr_renderer_bezier_curve_to(renderer, 38.62, -25.79, 32.15, -33.16, 32.69,
                                -41.70);
    rr_renderer_quadratic_curve_to(renderer, 33.25, -50.30, 32.05, -59.02);
    rr_renderer_quadratic_curve_to(renderer, 40.54, -56.72, 49.15, -56.17);
    rr_renderer_bezier_curve_to(renderer, 57.69, -55.62, 64.17, -48.26, 63.62,
                                -39.71);
    rr_renderer_bezier_curve_to(renderer, 63.07, -31.17, 55.71, -24.69, 47.17,
                                -25.24);
    rr_renderer_fill(renderer);
    rr_renderer_set_fill(renderer, 0xff596a74);
    rr_renderer_begin_path(renderer);
    rr_renderer_move_to(renderer, 68.53, -25.01);
    rr_renderer_bezier_curve_to(renderer, 62.03, -26.69, 58.13, -33.32, 59.81,
                                -39.82);
    rr_renderer_quadratic_curve_to(renderer, 61.50, -46.36, 61.86, -53.25);
    rr_renderer_quadratic_curve_to(renderer, 68.06, -50.23, 74.61, -48.54);
    rr_renderer_bezier_curve_to(renderer, 81.11, -46.86, 85.01, -40.23, 83.33,
                                -33.74);
    rr_renderer_bezier_curve_to(renderer, 81.66, -27.24, 75.03, -23.33, 68.53,
                                -25.01);
    rr_renderer_fill(renderer);
    rr_renderer_set_fill(renderer, 0xff596a74);
    rr_renderer_begin_path(renderer);
    rr_renderer_move_to(renderer, -74.75, -2.02);
    rr_renderer_bezier_curve_to(renderer, -84.92, -5.71, -96.15, -0.47, -99.85,
                                9.70);
    rr_renderer_quadratic_curve_to(renderer, -103.58, 19.94, -109.38, 29.43);
    rr_renderer_quadratic_curve_to(renderer, -98.38, 31.08, -88.13, 34.80);
    rr_renderer_bezier_curve_to(renderer, -77.97, 38.50, -66.73, 33.25, -63.03,
                                23.09);
    rr_renderer_bezier_curve_to(renderer, -59.34, 12.92, -64.58, 1.68, -74.75,
                                -2.02);
    rr_renderer_fill(renderer);
    rr_renderer_set_fill(renderer, 0xff596a74);
    rr_renderer_begin_path(renderer);
    rr_renderer_move_to(renderer, -45.25, 9.22);
    rr_renderer_bezier_curve_to(renderer, -56.00, 7.97, -65.73, 15.67, -66.98,
                                26.42);
    rr_renderer_quadratic_curve_to(renderer, -68.24, 37.25, -71.70, 47.82);
    rr_renderer_quadratic_curve_to(renderer, -60.62, 46.89, -49.78, 48.15);
    rr_renderer_bezier_curve_to(renderer, -39.03, 49.40, -29.30, 41.70, -28.05,
                                30.95);
    rr_renderer_bezier_curve_to(renderer, -26.80, 20.20, -34.50, 10.47, -45.25,
                                9.22);
    rr_renderer_fill(renderer);
    rr_renderer_set_fill(renderer, 0xff596a74);
    rr_renderer_begin_path(renderer);
    rr_renderer_move_to(renderer, -12.33, 21.32);
    rr_renderer_bezier_curve_to(renderer, -23.03, 19.71, -33.01, 27.07, -34.63,
                                37.76);
    rr_renderer_quadratic_curve_to(renderer, -36.26, 48.54, -40.08, 58.99);
    rr_renderer_quadratic_curve_to(renderer, -28.97, 58.43, -18.19, 60.06);
    rr_renderer_bezier_curve_to(renderer, -7.49, 61.68, 2.49, 54.32, 4.11,
                                43.62);
    rr_renderer_bezier_curve_to(renderer, 5.73, 32.92, -1.64, 22.94, -12.33,
                                21.32);
    rr_renderer_fill(renderer);
    rr_renderer_set_fill(renderer, 0xff596a74);
    rr_renderer_begin_path(renderer);
    rr_renderer_move_to(renderer, 12.80, -22.66);
    rr_renderer_bezier_curve_to(renderer, 2.03, -23.69, -5.86, -33.26, -4.82,
                                -44.03);
    rr_renderer_quadratic_curve_to(renderer, -3.78, -54.88, -4.94, -65.94);
    rr_renderer_quadratic_curve_to(renderer, 5.70, -62.69, 16.55, -61.65);
    rr_renderer_bezier_curve_to(renderer, 27.31, -60.61, 35.20, -51.05, 34.17,
                                -40.28);
    rr_renderer_bezier_curve_to(renderer, 33.13, -29.51, 23.57, -21.62, 12.80,
                                -22.66);
    rr_renderer_fill(renderer);
    rr_renderer_set_fill(renderer, 0xff596a74);
    rr_renderer_begin_path(renderer);
    rr_renderer_move_to(renderer, 12.80, 22.66);
    rr_renderer_bezier_curve_to(renderer, 2.04, 23.69, -5.85, 33.26, -4.82,
                                44.03);
    rr_renderer_quadratic_curve_to(renderer, -3.78, 54.88, -4.94, 65.94);
    rr_renderer_quadratic_curve_to(renderer, 5.70, 62.69, 16.55, 61.65);
    rr_renderer_bezier_curve_to(renderer, 27.32, 60.61, 35.21, 51.05, 34.17,
                                40.28);
    rr_renderer_bezier_curve_to(renderer, 33.14, 29.51, 23.57, 21.62, 12.80,
                                22.66);
    rr_renderer_fill(renderer);
    rr_renderer_set_fill(renderer, 0xff596a74);
    rr_renderer_begin_path(renderer);
    rr_renderer_move_to(renderer, 47.17, 25.24);
    rr_renderer_bezier_curve_to(renderer, 38.63, 25.79, 32.15, 33.16, 32.70,
                                41.70);
    rr_renderer_quadratic_curve_to(renderer, 33.25, 50.31, 32.06, 59.02);
    rr_renderer_quadratic_curve_to(renderer, 40.55, 56.72, 49.16, 56.17);
    rr_renderer_bezier_curve_to(renderer, 57.70, 55.62, 64.18, 48.26, 63.63,
                                39.72);
    rr_renderer_bezier_curve_to(renderer, 63.08, 31.17, 55.71, 24.69, 47.17,
                                25.24);
    rr_renderer_fill(renderer);
    rr_renderer_set_fill(renderer, 0xff596a74);
    rr_renderer_begin_path(renderer);
    rr_renderer_move_to(renderer, 68.54, 25.01);
    rr_renderer_bezier_curve_to(renderer, 62.04, 26.69, 58.13, 33.32, 59.81,
                                39.82);
    rr_renderer_quadratic_curve_to(renderer, 61.50, 46.36, 61.87, 53.25);
    rr_renderer_quadratic_curve_to(renderer, 68.07, 50.23, 74.62, 48.54);
    rr_renderer_bezier_curve_to(renderer, 81.11, 46.86, 85.02, 40.23, 83.34,
                                33.74);
    rr_renderer_bezier_curve_to(renderer, 81.66, 27.24, 75.03, 23.33, 68.54,
                                25.01);
    rr_renderer_fill(renderer);
    rr_renderer_set_fill(renderer, 0xff6e7a82);
    rr_renderer_begin_path(renderer);
    rr_renderer_move_to(renderer, 78.72, 47.65);
    rr_renderer_line_to(renderer, -83.84, 15.49);
    rr_renderer_line_to(renderer, -83.84, -13.67);
    rr_renderer_line_to(renderer, 78.72, -45.83);
    rr_renderer_fill(renderer);
    rr_renderer_set_fill(renderer, 0xff6e7a82);
    rr_renderer_begin_path(renderer);
    rr_renderer_move_to(renderer, 90.76, -47.20);
    rr_renderer_bezier_curve_to(renderer, 121.41, -47.20, 146.25, -25.66,
                                146.25, 0.91);
    rr_renderer_bezier_curve_to(renderer, 146.25, 13.67, 140.41, 25.91, 130.00,
                                34.93);
    rr_renderer_bezier_curve_to(renderer, 119.59, 43.95, 105.48, 49.02, 90.76,
                                49.02);
    rr_renderer_bezier_curve_to(renderer, 60.11, 49.02, 35.26, 27.48, 35.26,
                                0.91);
    rr_renderer_bezier_curve_to(renderer, 35.26, -25.66, 60.11, -47.20, 90.76,
                                -47.20);
    rr_renderer_fill(renderer);
    rr_renderer_set_fill(renderer, 0xff6e7a82);
    rr_renderer_begin_path(renderer);
    rr_renderer_move_to(renderer, 90.77, -32.40);
    rr_renderer_bezier_curve_to(renderer, 111.98, -32.40, 129.18, -17.49,
                                129.18, 0.89);
    rr_renderer_bezier_curve_to(renderer, 129.18, 9.72, 125.13, 18.19, 117.93,
                                24.43);
    rr_renderer_bezier_curve_to(renderer, 110.73, 30.68, 100.96, 34.18, 90.77,
                                34.18);
    rr_renderer_bezier_curve_to(renderer, 69.56, 34.18, 52.36, 19.28, 52.36,
                                0.89);
    rr_renderer_bezier_curve_to(renderer, 52.36, -17.49, 69.56, -32.40, 90.77,
                                -32.40);
    rr_renderer_fill(renderer);
    rr_renderer_set_fill(renderer, 0xff6e7a82);
    rr_renderer_begin_path(renderer);
    rr_renderer_move_to(renderer, -81.36, -13.79);
    rr_renderer_bezier_curve_to(renderer, -72.00, -13.79, -64.41, -7.21, -64.41,
                                0.91);
    rr_renderer_bezier_curve_to(renderer, -64.41, 4.80, -66.20, 8.54, -69.38,
                                11.29);
    rr_renderer_bezier_curve_to(renderer, -72.56, 14.05, -76.87, 15.60, -81.36,
                                15.60);
    rr_renderer_bezier_curve_to(renderer, -90.72, 15.60, -98.30, 9.02, -98.30,
                                0.91);
    rr_renderer_bezier_curve_to(renderer, -98.30, -7.21, -90.72, -13.79, -81.36,
                                -13.79);
    rr_renderer_fill(renderer);
    rr_renderer_set_fill(renderer, 0xff6e7a82);
    rr_renderer_begin_path(renderer);
    rr_renderer_move_to(renderer, 80.52, 32.99);
    rr_renderer_line_to(renderer, -83.58, 0.91);
    rr_renderer_line_to(renderer, 80.52, -31.17);
    rr_renderer_fill(renderer);
    rr_renderer_set_fill(renderer, 0xff85929c);
    rr_renderer_begin_path(renderer);
    rr_renderer_move_to(renderer, 90.77, -32.40);
    rr_renderer_bezier_curve_to(renderer, 111.98, -32.40, 129.18, -17.49,
                                129.18, 0.90);
    rr_renderer_bezier_curve_to(renderer, 129.18, 9.73, 125.13, 18.20, 117.93,
                                24.44);
    rr_renderer_bezier_curve_to(renderer, 110.72, 30.69, 100.95, 34.20, 90.77,
                                34.20);
    rr_renderer_bezier_curve_to(renderer, 69.55, 34.20, 52.35, 19.29, 52.35,
                                0.90);
    rr_renderer_bezier_curve_to(renderer, 52.35, -17.49, 69.55, -32.40, 90.77,
                                -32.40);
    rr_renderer_fill(renderer);
    rr_renderer_set_fill(renderer, 0xff85929c);
    rr_renderer_begin_path(renderer);
    rr_renderer_move_to(renderer, 80.51, 32.99);
    rr_renderer_line_to(renderer, -83.58, 0.90);
    rr_renderer_line_to(renderer, 80.51, -31.18);
    rr_renderer_fill(renderer);
}

void rr_dakotaraptor_wing1_draw(struct rr_renderer *renderer)
{
    rr_renderer_set_fill(renderer, 0xff46555e);
    rr_renderer_begin_path(renderer);
    rr_renderer_move_to(renderer, -68.65, -55.96);
    rr_renderer_line_to(renderer, -87.01, -51.98);
    rr_renderer_line_to(renderer, -88.64, -41.34);
    rr_renderer_line_to(renderer, -85.08, -34.26);
    rr_renderer_line_to(renderer, -75.99, -27.88);
    rr_renderer_line_to(renderer, -69.05, -29.76);
    rr_renderer_line_to(renderer, -67.37, -22.12);
    rr_renderer_line_to(renderer, -53.86, -14.83);
    rr_renderer_line_to(renderer, -47.40, -18.16);
    rr_renderer_line_to(renderer, -45.60, -11.36);
    rr_renderer_line_to(renderer, -24.13, 0.05);
    rr_renderer_line_to(renderer, -39.28, 31.89);
    rr_renderer_line_to(renderer, 26.80, -3.50);
    rr_renderer_fill(renderer);
    rr_renderer_set_fill(renderer, 0xff596a74);
    rr_renderer_begin_path(renderer);
    rr_renderer_move_to(renderer, -21.11, 13.58);
    rr_renderer_line_to(renderer, -13.63, -2.40);
    rr_renderer_line_to(renderer, -40.95, -16.58);
    rr_renderer_line_to(renderer, -45.08, -26.15);
    rr_renderer_line_to(renderer, -54.36, -21.73);
    rr_renderer_line_to(renderer, -62.08, -25.34);
    rr_renderer_line_to(renderer, -64.41, -36.46);
    rr_renderer_line_to(renderer, -76.00, -33.59);
    rr_renderer_line_to(renderer, -80.64, -37.20);
    rr_renderer_line_to(renderer, -83.22, -42.87);
    rr_renderer_line_to(renderer, -82.19, -47.25);
    rr_renderer_line_to(renderer, -65.44, -51.37);
    rr_renderer_line_to(renderer, 8.79, -14.00);
    rr_renderer_line_to(renderer, 10.85, -1.37);
    rr_renderer_line_to(renderer, -4.87, 14.86);
    rr_renderer_fill(renderer);
    rr_renderer_set_fill(renderer, 0xff6e7a82);
    rr_renderer_begin_path(renderer);
    rr_renderer_move_to(renderer, -73.16, -55.46);
    rr_renderer_bezier_curve_to(renderer, -81.53, -52.15, -6.94, -26.56, 3.12,
                                -13.87);
    rr_renderer_bezier_curve_to(renderer, 13.18, -1.18, -17.80, 16.44, -12.79,
                                20.71);
    rr_renderer_bezier_curve_to(renderer, -7.77, 24.98, 22.17, 20.83, 33.19,
                                11.75);
    rr_renderer_bezier_curve_to(renderer, 44.21, 2.68, 71.07, -22.54, 53.34,
                                -33.74);
    rr_renderer_bezier_curve_to(renderer, 35.62, -44.94, -64.79, -58.77, -73.16,
                                -55.46);
    rr_renderer_fill(renderer);
    rr_renderer_set_fill(renderer, 0xff6e7a82);
    rr_renderer_begin_path(renderer);
    rr_renderer_move_to(renderer, 7.85, 43.88);
    rr_renderer_bezier_curve_to(renderer, 12.97, 50.55, 21.95, 51.16, 27.91,
                                45.23);
    rr_renderer_line_to(renderer, 77.84, -4.37);
    rr_renderer_bezier_curve_to(renderer, 80.71, -7.22, 82.48, -11.22, 82.77,
                                -15.49);
    rr_renderer_bezier_curve_to(renderer, 83.05, -19.77, 81.84, -23.97, 79.38,
                                -27.18);
    rr_renderer_bezier_curve_to(renderer, 74.27, -33.85, 65.29, -34.45, 59.32,
                                -28.53);
    rr_renderer_line_to(renderer, 9.39, 21.07);
    rr_renderer_bezier_curve_to(renderer, 3.43, 27.00, 2.74, 37.21, 7.85,
                                43.88);
    rr_renderer_fill(renderer);
    rr_renderer_set_fill(renderer, 0xff6e7a82);
    rr_renderer_begin_path(renderer);
    rr_renderer_move_to(renderer, 48.90, -14.01);
    rr_renderer_bezier_curve_to(renderer, 26.11, -17.74, -69.06, -51.94, -65.31,
                                -55.06);
    rr_renderer_bezier_curve_to(renderer, -61.56, -58.17, 52.38, -39.52, 71.42,
                                -32.68);
    rr_renderer_bezier_curve_to(renderer, 90.45, -25.84, 71.69, -10.28, 48.90,
                                -14.01);
    rr_renderer_fill(renderer);
    rr_renderer_set_fill(renderer, 0xff85929c);
    rr_renderer_begin_path(renderer);
    rr_renderer_move_to(renderer, 3.82, 41.73);
    rr_renderer_bezier_curve_to(renderer, 7.55, 46.60, 14.11, 47.05, 18.46,
                                42.72);
    rr_renderer_line_to(renderer, 66.92, -5.40);
    rr_renderer_bezier_curve_to(renderer, 69.01, -7.48, 70.30, -10.40, 70.51,
                                -13.52);
    rr_renderer_bezier_curve_to(renderer, 70.72, -16.64, 69.83, -19.71, 68.04,
                                -22.05);
    rr_renderer_bezier_curve_to(renderer, 64.31, -26.92, 57.76, -27.36, 53.40,
                                -23.04);
    rr_renderer_line_to(renderer, 4.95, 25.09);
    rr_renderer_bezier_curve_to(renderer, 0.59, 29.41, 0.09, 36.86, 3.82,
                                41.73);
    rr_renderer_fill(renderer);
    rr_renderer_set_fill(renderer, 0xff85929c);
    rr_renderer_begin_path(renderer);
    rr_renderer_move_to(renderer, 63.69, -25.73);
    rr_renderer_bezier_curve_to(renderer, 51.02, -32.94, -24.41, -46.90, -32.70,
                                -44.80);
    rr_renderer_bezier_curve_to(renderer, -40.99, -42.69, 9.39, -25.04, 13.94,
                                -13.10);
    rr_renderer_bezier_curve_to(renderer, 18.50, -1.15, -10.28, 24.92, -5.38,
                                26.85);
    rr_renderer_bezier_curve_to(renderer, -0.49, 28.79, 31.82, 7.27, 43.33,
                                -1.50);
    rr_renderer_bezier_curve_to(renderer, 54.84, -10.26, 76.36, -18.51, 63.69,
                                -25.73);
    rr_renderer_fill(renderer);
}

void rr_dakotaraptor_wing2_draw(struct rr_renderer *renderer)
{
    rr_renderer_set_fill(renderer, 0xff46555e);
    rr_renderer_begin_path(renderer);
    rr_renderer_move_to(renderer, -68.66, 55.96);
    rr_renderer_line_to(renderer, -87.01, 51.98);
    rr_renderer_line_to(renderer, -88.64, 41.34);
    rr_renderer_line_to(renderer, -85.08, 34.26);
    rr_renderer_line_to(renderer, -75.99, 27.88);
    rr_renderer_line_to(renderer, -69.05, 29.76);
    rr_renderer_line_to(renderer, -67.37, 22.12);
    rr_renderer_line_to(renderer, -53.86, 14.83);
    rr_renderer_line_to(renderer, -47.40, 18.16);
    rr_renderer_line_to(renderer, -45.61, 11.36);
    rr_renderer_line_to(renderer, -24.13, -0.05);
    rr_renderer_line_to(renderer, -39.29, -31.89);
    rr_renderer_line_to(renderer, 26.80, 3.50);
    rr_renderer_fill(renderer);
    rr_renderer_set_fill(renderer, 0xff596a74);
    rr_renderer_begin_path(renderer);
    rr_renderer_move_to(renderer, -21.11, -13.58);
    rr_renderer_line_to(renderer, -13.63, 2.40);
    rr_renderer_line_to(renderer, -40.95, 16.58);
    rr_renderer_line_to(renderer, -45.08, 26.15);
    rr_renderer_line_to(renderer, -54.36, 21.73);
    rr_renderer_line_to(renderer, -62.09, 25.34);
    rr_renderer_line_to(renderer, -64.41, 36.46);
    rr_renderer_line_to(renderer, -76.00, 33.59);
    rr_renderer_line_to(renderer, -80.64, 37.20);
    rr_renderer_line_to(renderer, -83.22, 42.87);
    rr_renderer_line_to(renderer, -82.19, 47.25);
    rr_renderer_line_to(renderer, -65.44, 51.37);
    rr_renderer_line_to(renderer, 8.79, 14.00);
    rr_renderer_line_to(renderer, 10.85, 1.37);
    rr_renderer_line_to(renderer, -4.87, -14.86);
    rr_renderer_fill(renderer);
    rr_renderer_set_fill(renderer, 0xff6e7a82);
    rr_renderer_begin_path(renderer);
    rr_renderer_move_to(renderer, -73.16, 55.46);
    rr_renderer_bezier_curve_to(renderer, -81.53, 52.14, -6.94, 26.56, 3.12,
                                13.87);
    rr_renderer_bezier_curve_to(renderer, 13.18, 1.17, -17.80, -16.44, -12.79,
                                -20.71);
    rr_renderer_bezier_curve_to(renderer, -7.77, -24.98, 22.17, -20.83, 33.19,
                                -11.75);
    rr_renderer_bezier_curve_to(renderer, 44.21, -2.68, 71.07, 22.54, 53.34,
                                33.74);
    rr_renderer_bezier_curve_to(renderer, 35.62, 44.94, -64.79, 58.77, -73.16,
                                55.46);
    rr_renderer_fill(renderer);
    rr_renderer_set_fill(renderer, 0xff6e7a82);
    rr_renderer_begin_path(renderer);
    rr_renderer_move_to(renderer, 7.85, -43.88);
    rr_renderer_bezier_curve_to(renderer, 12.97, -50.55, 21.95, -51.16, 27.91,
                                -45.23);
    rr_renderer_line_to(renderer, 77.84, 4.37);
    rr_renderer_bezier_curve_to(renderer, 80.71, 7.22, 82.48, 11.22, 82.77,
                                15.49);
    rr_renderer_bezier_curve_to(renderer, 83.05, 19.77, 81.84, 23.97, 79.38,
                                27.18);
    rr_renderer_bezier_curve_to(renderer, 74.27, 33.85, 65.29, 34.45, 59.32,
                                28.53);
    rr_renderer_line_to(renderer, 9.39, -21.07);
    rr_renderer_bezier_curve_to(renderer, 3.43, -27.00, 2.74, -37.21, 7.85,
                                -43.88);
    rr_renderer_fill(renderer);
    rr_renderer_set_fill(renderer, 0xff6e7a82);
    rr_renderer_begin_path(renderer);
    rr_renderer_move_to(renderer, 48.90, 14.01);
    rr_renderer_bezier_curve_to(renderer, 26.11, 17.74, -69.06, 51.94, -65.31,
                                55.05);
    rr_renderer_bezier_curve_to(renderer, -61.56, 58.17, 52.38, 39.52, 71.42,
                                32.68);
    rr_renderer_bezier_curve_to(renderer, 90.45, 25.84, 71.69, 10.28, 48.90,
                                14.01);
    rr_renderer_fill(renderer);
    rr_renderer_set_fill(renderer, 0xff85929c);
    rr_renderer_begin_path(renderer);
    rr_renderer_move_to(renderer, 3.82, -41.73);
    rr_renderer_bezier_curve_to(renderer, 7.55, -46.60, 14.11, -47.05, 18.46,
                                -42.72);
    rr_renderer_line_to(renderer, 66.92, 5.40);
    rr_renderer_bezier_curve_to(renderer, 69.01, 7.47, 70.30, 10.40, 70.51,
                                13.52);
    rr_renderer_bezier_curve_to(renderer, 70.72, 16.64, 69.83, 19.71, 68.04,
                                22.05);
    rr_renderer_bezier_curve_to(renderer, 64.31, 26.92, 57.76, 27.36, 53.40,
                                23.04);
    rr_renderer_line_to(renderer, 4.95, -25.09);
    rr_renderer_bezier_curve_to(renderer, 0.59, -29.41, 0.09, -36.86, 3.82,
                                -41.73);
    rr_renderer_fill(renderer);
    rr_renderer_set_fill(renderer, 0xff85929c);
    rr_renderer_begin_path(renderer);
    rr_renderer_move_to(renderer, 63.69, 25.72);
    rr_renderer_bezier_curve_to(renderer, 51.02, 32.94, -24.41, 46.90, -32.70,
                                44.80);
    rr_renderer_bezier_curve_to(renderer, -40.99, 42.69, 9.39, 25.04, 13.94,
                                13.09);
    rr_renderer_bezier_curve_to(renderer, 18.50, 1.15, -10.28, -24.92, -5.38,
                                -26.85);
    rr_renderer_bezier_curve_to(renderer, -0.49, -28.79, 31.82, -7.27, 43.33,
                                1.50);
    rr_renderer_bezier_curve_to(renderer, 54.84, 10.26, 76.36, 18.51, 63.69,
                                25.72);
    rr_renderer_fill(renderer);
}