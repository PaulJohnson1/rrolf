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

void rr_triceratops_body_draw(struct rr_renderer *renderer)
{
    rr_renderer_set_fill(renderer, 0xffa49b8a);
    rr_renderer_begin_path(renderer);
    rr_renderer_move_to(renderer, 0.01, -77.37);
    rr_renderer_bezier_curve_to(renderer, 65.95, -77.37, 119.40, -42.74, 119.40,
                                -0.01);
    rr_renderer_bezier_curve_to(renderer, 119.40, 20.51, 106.82, 40.19, 84.43,
                                54.70);
    rr_renderer_bezier_curve_to(renderer, 62.04, 69.20, 31.67, 77.36, 0.01,
                                77.36);
    rr_renderer_bezier_curve_to(renderer, -65.92, 77.36, -119.38, 42.72,
                                -119.38, -0.01);
    rr_renderer_bezier_curve_to(renderer, -119.38, -42.74, -65.92, -77.37, 0.01,
                                -77.37);
    rr_renderer_fill(renderer);
    rr_renderer_set_fill(renderer, 0xff898276);
    rr_renderer_begin_path(renderer);
    rr_renderer_move_to(renderer, -0.00, -87.80);
    rr_renderer_bezier_curve_to(renderer, 74.83, -87.80, 135.49, -48.49, 135.49,
                                -0.00);
    rr_renderer_bezier_curve_to(renderer, 135.49, 23.28, 121.21, 45.62, 95.80,
                                62.08);
    rr_renderer_bezier_curve_to(renderer, 70.40, 78.55, 35.93, 87.80, -0.00,
                                87.80);
    rr_renderer_bezier_curve_to(renderer, -74.83, 87.80, -135.49, 48.49,
                                -135.49, -0.00);
    rr_renderer_bezier_curve_to(renderer, -135.49, -48.49, -74.83, -87.80,
                                -0.00, -87.80);
    rr_renderer_move_to(renderer, -0.00, -67.87);
    rr_renderer_bezier_curve_to(renderer, -63.82, -67.87, -115.56, -37.48,
                                -115.56, -0.00);
    rr_renderer_bezier_curve_to(renderer, -115.56, 37.48, -63.82, 67.87, -0.00,
                                67.87);
    rr_renderer_bezier_curve_to(renderer, 63.82, 67.87, 115.56, 37.48, 115.56,
                                -0.00);
    rr_renderer_bezier_curve_to(renderer, 115.56, -37.48, 63.82, -67.87, -0.00,
                                -67.87);
    rr_renderer_fill(renderer);
    rr_renderer_set_fill(renderer, 0xff898276);
    rr_renderer_begin_path(renderer);
    rr_renderer_move_to(renderer, 50.68, -8.94);
    rr_renderer_bezier_curve_to(renderer, 55.62, -8.94, 59.62, -4.94, 59.62,
                                0.00);
    rr_renderer_bezier_curve_to(renderer, 59.62, 2.37, 58.68, 4.65, 57.00,
                                6.32);
    rr_renderer_bezier_curve_to(renderer, 55.33, 8.00, 53.05, 8.94, 50.68,
                                8.94);
    rr_renderer_line_to(renderer, -90.80, 8.94);
    rr_renderer_bezier_curve_to(renderer, -95.74, 8.94, -99.75, 4.94, -99.75,
                                0.00);
    rr_renderer_bezier_curve_to(renderer, -99.75, -4.94, -95.74, -8.94, -90.80,
                                -8.94);
    rr_renderer_fill(renderer);
}

void rr_triceratops_head_draw(struct rr_renderer *renderer)
{
    rr_renderer_set_fill(renderer, 0xff898276);
    rr_renderer_begin_path(renderer);
    rr_renderer_move_to(renderer, -57.74, 85.07);
    rr_renderer_bezier_curve_to(renderer, -24.22, 78.12, -0.11, 55.30, -3.89,
                                34.12);
    rr_renderer_bezier_curve_to(renderer, -5.71, 23.94, -13.84, 15.51, -26.51,
                                10.68);
    rr_renderer_bezier_curve_to(renderer, -39.17, 5.84, -55.33, 5.01, -71.43,
                                8.34);
    rr_renderer_bezier_curve_to(renderer, -104.95, 15.30, -129.06, 38.11,
                                -125.28, 59.30);
    rr_renderer_bezier_curve_to(renderer, -121.50, 80.49, -91.27, 92.02, -57.74,
                                85.07);
    rr_renderer_fill(renderer);
    rr_renderer_set_fill(renderer, 0xff898276);
    rr_renderer_begin_path(renderer);
    rr_renderer_move_to(renderer, -91.22, 82.18);
    rr_renderer_bezier_curve_to(renderer, -69.85, 80.48, -53.76, 60.35, -55.29,
                                37.21);
    rr_renderer_bezier_curve_to(renderer, -56.82, 14.08, -75.39, -3.31, -96.77,
                                -1.61);
    rr_renderer_bezier_curve_to(renderer, -118.15, 0.08, -134.24, 20.21,
                                -132.71, 43.35);
    rr_renderer_bezier_curve_to(renderer, -131.17, 66.49, -112.60, 83.87,
                                -91.22, 82.18);
    rr_renderer_fill(renderer);
    rr_renderer_set_fill(renderer, 0xff898276);
    rr_renderer_begin_path(renderer);
    rr_renderer_move_to(renderer, -57.75, -85.06);
    rr_renderer_bezier_curve_to(renderer, -24.23, -78.11, -0.11, -55.29, -3.89,
                                -34.10);
    rr_renderer_bezier_curve_to(renderer, -5.71, -23.93, -13.84, -15.50, -26.51,
                                -10.66);
    rr_renderer_bezier_curve_to(renderer, -39.17, -5.83, -55.33, -4.99, -71.43,
                                -8.33);
    rr_renderer_bezier_curve_to(renderer, -104.95, -15.28, -129.06, -38.10,
                                -125.28, -59.29);
    rr_renderer_bezier_curve_to(renderer, -121.50, -80.48, -91.27, -92.02,
                                -57.75, -85.06);
    rr_renderer_fill(renderer);
    rr_renderer_set_fill(renderer, 0xff898276);
    rr_renderer_begin_path(renderer);
    rr_renderer_move_to(renderer, -91.22, -82.17);
    rr_renderer_bezier_curve_to(renderer, -69.85, -80.47, -53.76, -60.34,
                                -55.29, -37.20);
    rr_renderer_bezier_curve_to(renderer, -56.82, -14.06, -75.39, 3.32, -96.77,
                                1.63);
    rr_renderer_bezier_curve_to(renderer, -118.15, -0.07, -134.24, -20.20,
                                -132.71, -43.34);
    rr_renderer_bezier_curve_to(renderer, -131.18, -66.48, -112.60, -83.86,
                                -91.22, -82.17);
    rr_renderer_fill(renderer);
    rr_renderer_set_fill(renderer, 0xff898276);
    rr_renderer_begin_path(renderer);
    rr_renderer_move_to(renderer, -121.75, -11.04);
    rr_renderer_bezier_curve_to(renderer, -107.57, -11.04, -96.08, -6.17,
                                -96.08, -0.15);
    rr_renderer_bezier_curve_to(renderer, -96.08, 5.86, -107.57, 10.74, -121.75,
                                10.74);
    rr_renderer_bezier_curve_to(renderer, -114.72, 3.78, -114.72, -4.09,
                                -121.75, -11.04);
    rr_renderer_fill(renderer);
    rr_renderer_set_fill(renderer, 0xff898276);
    rr_renderer_begin_path(renderer);
    rr_renderer_move_to(renderer, 73.09, -31.30);
    rr_renderer_bezier_curve_to(renderer, 68.98, -20.15, 52.47, -15.97, 36.22,
                                -21.96);
    rr_renderer_bezier_curve_to(renderer, 19.97, -27.95, 10.12, -41.84, 14.23,
                                -52.98);
    rr_renderer_bezier_curve_to(renderer, 30.77, -40.26, 52.24, -32.35, 73.09,
                                -31.30);
    rr_renderer_fill(renderer);
    rr_renderer_set_fill(renderer, 0xff898276);
    rr_renderer_begin_path(renderer);
    rr_renderer_move_to(renderer, 73.09, 31.30);
    rr_renderer_bezier_curve_to(renderer, 68.98, 20.16, 52.47, 15.98, 36.22,
                                21.97);
    rr_renderer_bezier_curve_to(renderer, 19.97, 27.96, 10.12, 41.84, 14.23,
                                52.99);
    rr_renderer_bezier_curve_to(renderer, 30.77, 40.26, 52.24, 32.35, 73.09,
                                31.30);
    rr_renderer_fill(renderer);
    rr_renderer_set_fill(renderer, 0xff898276);
    rr_renderer_begin_path(renderer);
    rr_renderer_move_to(renderer, -26.26, -66.11);
    rr_renderer_bezier_curve_to(renderer, 10.98, -66.11, 41.17, -36.48, 41.17,
                                0.06);
    rr_renderer_bezier_curve_to(renderer, 41.17, 17.61, 34.06, 34.44, 21.42,
                                46.85);
    rr_renderer_bezier_curve_to(renderer, 8.77, 59.26, -8.38, 66.23, -26.26,
                                66.23);
    rr_renderer_bezier_curve_to(renderer, -63.49, 66.23, -93.68, 36.61, -93.68,
                                0.06);
    rr_renderer_bezier_curve_to(renderer, -93.68, -36.48, -63.49, -66.11,
                                -26.26, -66.11);
    rr_renderer_fill(renderer);
    rr_renderer_set_fill(renderer, 0xff898276);
    rr_renderer_begin_path(renderer);
    rr_renderer_move_to(renderer, 68.00, -31.70);
    rr_renderer_bezier_curve_to(renderer, 85.84, -31.70, 100.30, -17.51, 100.30,
                                0.00);
    rr_renderer_bezier_curve_to(renderer, 100.30, 8.41, 96.90, 16.47, 90.84,
                                22.42);
    rr_renderer_bezier_curve_to(renderer, 84.78, 28.36, 76.57, 31.70, 68.00,
                                31.70);
    rr_renderer_bezier_curve_to(renderer, 50.16, 31.70, 35.70, 17.51, 35.70,
                                0.00);
    rr_renderer_bezier_curve_to(renderer, 35.70, -17.51, 50.16, -31.70, 68.00,
                                -31.70);
    rr_renderer_fill(renderer);
    rr_renderer_set_fill(renderer, 0xffa49b8a);
    rr_renderer_begin_path(renderer);
    rr_renderer_move_to(renderer, 68.00, -18.06);
    rr_renderer_bezier_curve_to(renderer, 78.16, -18.06, 86.40, -9.97, 86.40,
                                0.00);
    rr_renderer_bezier_curve_to(renderer, 86.40, 4.79, 84.46, 9.39, 81.01,
                                12.78);
    rr_renderer_bezier_curve_to(renderer, 77.56, 16.16, 72.88, 18.07, 68.00,
                                18.07);
    rr_renderer_bezier_curve_to(renderer, 57.84, 18.07, 49.60, 9.98, 49.60,
                                0.00);
    rr_renderer_bezier_curve_to(renderer, 49.60, -9.97, 57.84, -18.06, 68.00,
                                -18.06);
    rr_renderer_fill(renderer);
    rr_renderer_set_fill(renderer, 0xffa49b8a);
    rr_renderer_begin_path(renderer);
    rr_renderer_move_to(renderer, -26.26, -52.98);
    rr_renderer_bezier_curve_to(renderer, 3.57, -52.98, 27.75, -29.26, 27.75,
                                0.00);
    rr_renderer_bezier_curve_to(renderer, 27.75, 14.06, 22.06, 27.53, 11.93,
                                37.47);
    rr_renderer_bezier_curve_to(renderer, 1.80, 47.41, -11.93, 52.99, -26.26,
                                52.99);
    rr_renderer_bezier_curve_to(renderer, -56.08, 52.99, -80.26, 29.27, -80.26,
                                0.00);
    rr_renderer_bezier_curve_to(renderer, -80.26, -29.26, -56.08, -52.98,
                                -26.26, -52.98);
    rr_renderer_fill(renderer);
    rr_renderer_set_fill(renderer, 0xffa49b8a);
    rr_renderer_begin_path(renderer);
    rr_renderer_move_to(renderer, 68.25, -18.20);
    rr_renderer_bezier_curve_to(renderer, 64.69, -8.56, 48.63, -5.59, 32.38,
                                -11.58);
    rr_renderer_bezier_curve_to(renderer, 16.12, -17.57, 5.83, -30.24, 9.39,
                                -39.88);
    rr_renderer_bezier_curve_to(renderer, 25.65, -27.30, 47.71, -19.17, 68.25,
                                -18.20);
    rr_renderer_fill(renderer);
    rr_renderer_set_fill(renderer, 0xffa49b8a);
    rr_renderer_begin_path(renderer);
    rr_renderer_move_to(renderer, 68.25, -18.20);
    rr_renderer_bezier_curve_to(renderer, 64.69, -8.56, 48.63, -5.59, 32.38,
                                -11.58);
    rr_renderer_bezier_curve_to(renderer, 16.12, -17.57, 5.83, -30.24, 9.39,
                                -39.88);
    rr_renderer_bezier_curve_to(renderer, 25.65, -27.30, 47.71, -19.17, 68.25,
                                -18.20);
    rr_renderer_fill(renderer);
    rr_renderer_set_fill(renderer, 0xffa49b8a);
    rr_renderer_begin_path(renderer);
    rr_renderer_move_to(renderer, 68.25, 18.18);
    rr_renderer_bezier_curve_to(renderer, 64.69, 8.53, 48.63, 5.57, 32.38,
                                11.56);
    rr_renderer_bezier_curve_to(renderer, 16.12, 17.54, 5.83, 30.22, 9.39,
                                39.86);
    rr_renderer_bezier_curve_to(renderer, 25.65, 27.28, 47.71, 19.15, 68.25,
                                18.18);
    rr_renderer_fill(renderer);
    rr_renderer_set_fill(renderer, 0xffa49b8a);
    rr_renderer_begin_path(renderer);
    rr_renderer_move_to(renderer, 68.25, 18.18);
    rr_renderer_bezier_curve_to(renderer, 64.69, 8.53, 48.63, 5.57, 32.38,
                                11.56);
    rr_renderer_bezier_curve_to(renderer, 16.12, 17.54, 5.83, 30.22, 9.39,
                                39.86);
    rr_renderer_bezier_curve_to(renderer, 25.65, 27.28, 47.71, 19.15, 68.25,
                                18.18);
    rr_renderer_fill(renderer);
    rr_renderer_set_fill(renderer, 0xffa49b8a);
    rr_renderer_begin_path(renderer);
    rr_renderer_move_to(renderer, 24.00, -17.11);
    rr_renderer_line_to(renderer, 59.41, -6.41);
    rr_renderer_line_to(renderer, 59.41, 6.42);
    rr_renderer_line_to(renderer, 24.00, 17.12);
    rr_renderer_fill(renderer);
    rr_renderer_set_fill(renderer, 0xffa49b8a);
    rr_renderer_begin_path(renderer);
    rr_renderer_move_to(renderer, -59.72, -69.37);
    rr_renderer_bezier_curve_to(renderer, -33.87, -62.83, -15.40, -46.39,
                                -18.46, -32.67);
    rr_renderer_bezier_curve_to(renderer, -19.93, -26.08, -26.27, -21.01,
                                -36.09, -18.57);
    rr_renderer_bezier_curve_to(renderer, -45.91, -16.13, -58.40, -16.53,
                                -70.81, -19.67);
    rr_renderer_bezier_curve_to(renderer, -96.67, -26.22, -115.14, -42.65,
                                -112.07, -56.37);
    rr_renderer_bezier_curve_to(renderer, -109.01, -70.10, -85.57, -75.92,
                                -59.72, -69.37);
    rr_renderer_fill(renderer);
    rr_renderer_set_fill(renderer, 0xffa49b8a);
    rr_renderer_begin_path(renderer);
    rr_renderer_move_to(renderer, -92.12, -68.78);
    rr_renderer_bezier_curve_to(renderer, -77.84, -67.65, -67.10, -53.98,
                                -68.14, -38.25);
    rr_renderer_bezier_curve_to(renderer, -69.19, -22.52, -81.61, -10.68,
                                -95.89, -11.82);
    rr_renderer_bezier_curve_to(renderer, -110.17, -12.95, -120.90, -26.62,
                                -119.86, -42.35);
    rr_renderer_bezier_curve_to(renderer, -118.82, -58.08, -106.40, -69.92,
                                -92.12, -68.78);
    rr_renderer_fill(renderer);
    rr_renderer_set_fill(renderer, 0xffa49b8a);
    rr_renderer_begin_path(renderer);
    rr_renderer_move_to(renderer, -111.16, -18.82);
    rr_renderer_bezier_curve_to(renderer, -81.96, -18.82, -58.28, -10.46,
                                -58.28, -0.15);
    rr_renderer_bezier_curve_to(renderer, -58.28, 10.16, -81.96, 18.51, -111.16,
                                18.51);
    rr_renderer_bezier_curve_to(renderer, -100.17, 6.37, -100.17, -6.68,
                                -111.16, -18.82);
    rr_renderer_fill(renderer);
    rr_renderer_set_fill(renderer, 0xffa49b8a);
    rr_renderer_begin_path(renderer);
    rr_renderer_move_to(renderer, -59.72, 69.50);
    rr_renderer_bezier_curve_to(renderer, -33.87, 62.95, -15.39, 46.52, -18.46,
                                32.80);
    rr_renderer_bezier_curve_to(renderer, -19.93, 26.21, -26.27, 21.13, -36.09,
                                18.70);
    rr_renderer_bezier_curve_to(renderer, -45.91, 16.26, -58.40, 16.66, -70.81,
                                19.80);
    rr_renderer_bezier_curve_to(renderer, -96.66, 26.34, -115.14, 42.78,
                                -112.07, 56.50);
    rr_renderer_bezier_curve_to(renderer, -109.01, 70.23, -85.57, 76.05, -59.72,
                                69.50);
    rr_renderer_fill(renderer);
    rr_renderer_set_fill(renderer, 0xffa49b8a);
    rr_renderer_begin_path(renderer);
    rr_renderer_move_to(renderer, -92.12, 68.91);
    rr_renderer_bezier_curve_to(renderer, -77.84, 67.78, -67.10, 54.11, -68.14,
                                38.38);
    rr_renderer_bezier_curve_to(renderer, -69.19, 22.64, -81.61, 10.81, -95.89,
                                11.94);
    rr_renderer_bezier_curve_to(renderer, -110.17, 13.08, -120.90, 26.75,
                                -119.86, 42.48);
    rr_renderer_bezier_curve_to(renderer, -118.82, 58.21, -106.40, 70.05,
                                -92.12, 68.91);
    rr_renderer_fill(renderer);
    rr_renderer_set_fill(renderer, 0xffa49b8a);
    rr_renderer_begin_path(renderer);
    rr_renderer_move_to(renderer, -85.77, -30.81);
    rr_renderer_line_to(renderer, -48.89, -19.28);
    rr_renderer_line_to(renderer, -48.89, 18.97);
    rr_renderer_line_to(renderer, -85.77, 30.50);
    rr_renderer_fill(renderer);
    rr_renderer_set_fill(renderer, 0xffbfbab0);
    rr_renderer_begin_path(renderer);
    rr_renderer_move_to(renderer, 57.15, -7.41);
    rr_renderer_bezier_curve_to(renderer, 62.82, -11.50, 72.02, -11.50, 77.69,
                                -7.41);
    rr_renderer_quadratic_curve_to(renderer, 82.83, -3.70, 87.97, 0.00);
    rr_renderer_quadratic_curve_to(renderer, 82.83, 3.71, 77.69, 7.41);
    rr_renderer_bezier_curve_to(renderer, 72.02, 11.50, 62.82, 11.50, 57.15,
                                7.41);
    rr_renderer_bezier_curve_to(renderer, 51.47, 3.32, 51.47, -3.31, 57.15,
                                -7.41);
    rr_renderer_fill(renderer);
    rr_renderer_set_fill(renderer, 0xff898276);
    rr_renderer_begin_path(renderer);
    rr_renderer_move_to(renderer, -101.03, 42.22);
    rr_renderer_bezier_curve_to(renderer, -94.59, 22.02, -75.84, 8.29, -54.63,
                                8.25);
    rr_renderer_line_to(renderer, -54.61, 22.80);
    rr_renderer_bezier_curve_to(renderer, -69.49, 22.82, -82.65, 32.46, -87.17,
                                46.64);
    rr_renderer_fill(renderer);
    rr_renderer_set_fill(renderer, 0xff898276);
    rr_renderer_begin_path(renderer);
    rr_renderer_move_to(renderer, -54.54, 8.17);
    rr_renderer_bezier_curve_to(renderer, -50.55, 8.17, -47.31, 11.41, -47.31,
                                15.41);
    rr_renderer_bezier_curve_to(renderer, -47.31, 17.32, -48.07, 19.16, -49.43,
                                20.52);
    rr_renderer_bezier_curve_to(renderer, -50.78, 21.88, -52.62, 22.64, -54.54,
                                22.64);
    rr_renderer_bezier_curve_to(renderer, -58.54, 22.64, -61.77, 19.40, -61.77,
                                15.41);
    rr_renderer_bezier_curve_to(renderer, -61.77, 11.41, -58.54, 8.17, -54.54,
                                8.17);
    rr_renderer_fill(renderer);
    rr_renderer_set_fill(renderer, 0xff898276);
    rr_renderer_begin_path(renderer);
    rr_renderer_move_to(renderer, -94.26, 37.93);
    rr_renderer_bezier_curve_to(renderer, -90.27, 37.93, -87.03, 41.17, -87.03,
                                45.17);
    rr_renderer_bezier_curve_to(renderer, -87.03, 47.09, -87.79, 48.93, -89.15,
                                50.28);
    rr_renderer_bezier_curve_to(renderer, -90.50, 51.64, -92.34, 52.40, -94.26,
                                52.40);
    rr_renderer_bezier_curve_to(renderer, -98.26, 52.40, -101.50, 49.16,
                                -101.50, 45.17);
    rr_renderer_bezier_curve_to(renderer, -101.50, 41.17, -98.26, 37.93, -94.26,
                                37.93);
    rr_renderer_fill(renderer);
    rr_renderer_set_fill(renderer, 0xff898276);
    rr_renderer_begin_path(renderer);
    rr_renderer_move_to(renderer, -101.03, -42.21);
    rr_renderer_bezier_curve_to(renderer, -94.59, -22.01, -75.84, -8.28, -54.63,
                                -8.24);
    rr_renderer_line_to(renderer, -54.61, -22.79);
    rr_renderer_bezier_curve_to(renderer, -69.49, -22.82, -82.65, -32.46,
                                -87.17, -46.63);
    rr_renderer_fill(renderer);
    rr_renderer_set_fill(renderer, 0xff898276);
    rr_renderer_begin_path(renderer);
    rr_renderer_move_to(renderer, -54.54, -8.17);
    rr_renderer_bezier_curve_to(renderer, -50.55, -8.17, -47.31, -11.41, -47.31,
                                -15.40);
    rr_renderer_bezier_curve_to(renderer, -47.31, -17.32, -48.07, -19.16,
                                -49.43, -20.52);
    rr_renderer_bezier_curve_to(renderer, -50.78, -21.87, -52.62, -22.64,
                                -54.54, -22.64);
    rr_renderer_bezier_curve_to(renderer, -58.54, -22.64, -61.77, -19.40,
                                -61.77, -15.40);
    rr_renderer_bezier_curve_to(renderer, -61.77, -11.41, -58.54, -8.17, -54.54,
                                -8.17);
    rr_renderer_fill(renderer);
    rr_renderer_set_fill(renderer, 0xff898276);
    rr_renderer_begin_path(renderer);
    rr_renderer_move_to(renderer, -94.26, -37.93);
    rr_renderer_bezier_curve_to(renderer, -90.27, -37.93, -87.03, -41.17,
                                -87.03, -45.16);
    rr_renderer_bezier_curve_to(renderer, -87.03, -47.08, -87.79, -48.92,
                                -89.15, -50.28);
    rr_renderer_bezier_curve_to(renderer, -90.50, -51.64, -92.34, -52.40,
                                -94.26, -52.40);
    rr_renderer_bezier_curve_to(renderer, -98.26, -52.40, -101.50, -49.16,
                                -101.50, -45.16);
    rr_renderer_bezier_curve_to(renderer, -101.50, -41.17, -98.26, -37.93,
                                -94.26, -37.93);
    rr_renderer_fill(renderer);
    rr_renderer_set_fill(renderer, 0xffbfbab0);
    rr_renderer_begin_path(renderer);
    rr_renderer_move_to(renderer, 4.38, 21.44);
    rr_renderer_bezier_curve_to(renderer, 12.26, 21.40, 21.06, 35.28, 33.67,
                                36.86);
    rr_renderer_bezier_curve_to(renderer, 46.28, 38.44, 63.09, 28.79, 80.06,
                                30.91);
    rr_renderer_bezier_curve_to(renderer, 97.03, 33.04, 135.64, 46.43, 135.48,
                                49.61);
    rr_renderer_bezier_curve_to(renderer, 135.32, 52.80, 97.30, 48.37, 79.12,
                                50.05);
    rr_renderer_bezier_curve_to(renderer, 60.94, 51.73, 41.87, 61.87, 26.42,
                                59.71);
    rr_renderer_bezier_curve_to(renderer, 10.96, 57.55, -9.92, 43.47, -13.59,
                                37.10);
    rr_renderer_bezier_curve_to(renderer, -17.27, 30.72, -3.50, 21.48, 4.38,
                                21.44);
    rr_renderer_fill(renderer);
    rr_renderer_set_fill(renderer, 0xffbfbab0);
    rr_renderer_begin_path(renderer);
    rr_renderer_move_to(renderer, 4.38, -21.31);
    rr_renderer_bezier_curve_to(renderer, 12.26, -21.27, 21.06, -35.15, 33.67,
                                -36.73);
    rr_renderer_bezier_curve_to(renderer, 46.28, -38.31, 63.09, -28.66, 80.06,
                                -30.79);
    rr_renderer_bezier_curve_to(renderer, 97.03, -32.91, 135.64, -46.30, 135.48,
                                -49.49);
    rr_renderer_bezier_curve_to(renderer, 135.32, -52.68, 97.30, -48.24, 79.12,
                                -49.92);
    rr_renderer_bezier_curve_to(renderer, 60.94, -51.60, 41.87, -61.74, 26.42,
                                -59.58);
    rr_renderer_bezier_curve_to(renderer, 10.96, -57.42, -9.92, -43.35, -13.59,
                                -36.97);
    rr_renderer_bezier_curve_to(renderer, -17.27, -30.59, -3.50, -21.35, 4.38,
                                -21.31);
    rr_renderer_fill(renderer);
}

void rr_triceratops_leg1_draw(struct rr_renderer *renderer)
{
    rr_renderer_set_fill(renderer, 0xffa49b8a);
    rr_renderer_begin_path(renderer);
    rr_renderer_move_to(renderer, 66.81, -100.42);
    rr_renderer_bezier_curve_to(renderer, 87.53, -100.42, 104.33, -83.94,
                                104.33, -63.61);
    rr_renderer_bezier_curve_to(renderer, 104.33, -53.85, 100.38, -44.49, 93.34,
                                -37.59);
    rr_renderer_bezier_curve_to(renderer, 86.30, -30.69, 76.76, -26.81, 66.81,
                                -26.81);
    rr_renderer_bezier_curve_to(renderer, 46.08, -26.81, 29.28, -43.29, 29.28,
                                -63.61);
    rr_renderer_bezier_curve_to(renderer, 29.28, -83.94, 46.08, -100.42, 66.81,
                                -100.42);
    rr_renderer_fill(renderer);
    rr_renderer_set_fill(renderer, 0xff898276);
    rr_renderer_begin_path(renderer);
    rr_renderer_move_to(renderer, 66.80, -105.38);
    rr_renderer_bezier_curve_to(renderer, 90.32, -105.38, 109.39, -86.68,
                                109.39, -63.61);
    rr_renderer_bezier_curve_to(renderer, 109.39, -52.53, 104.90, -41.91, 96.91,
                                -34.08);
    rr_renderer_bezier_curve_to(renderer, 88.93, -26.25, 78.10, -21.85, 66.80,
                                -21.85);
    rr_renderer_bezier_curve_to(renderer, 43.28, -21.85, 24.22, -40.54, 24.22,
                                -63.61);
    rr_renderer_bezier_curve_to(renderer, 24.22, -86.68, 43.28, -105.38, 66.80,
                                -105.38);
    rr_renderer_move_to(renderer, 66.80, -93.79);
    rr_renderer_bezier_curve_to(renderer, 49.69, -93.79, 35.81, -80.28, 35.81,
                                -63.61);
    rr_renderer_bezier_curve_to(renderer, 35.81, -46.95, 49.69, -33.44, 66.80,
                                -33.44);
    rr_renderer_bezier_curve_to(renderer, 83.92, -33.44, 97.80, -46.95, 97.80,
                                -63.61);
    rr_renderer_bezier_curve_to(renderer, 97.80, -80.28, 83.92, -93.79, 66.80,
                                -93.79);
    rr_renderer_fill(renderer);
    rr_renderer_set_fill(renderer, 0xffa49b8a);
    rr_renderer_begin_path(renderer);
    rr_renderer_move_to(renderer, -66.80, 26.80);
    rr_renderer_bezier_curve_to(renderer, -46.08, 26.80, -29.28, 43.28, -29.28,
                                63.61);
    rr_renderer_bezier_curve_to(renderer, -29.28, 73.37, -33.23, 82.73, -40.27,
                                89.63);
    rr_renderer_bezier_curve_to(renderer, -47.30, 96.53, -56.85, 100.41, -66.80,
                                100.41);
    rr_renderer_bezier_curve_to(renderer, -87.52, 100.41, -104.32, 83.93,
                                -104.32, 63.61);
    rr_renderer_bezier_curve_to(renderer, -104.32, 43.28, -87.52, 26.80, -66.80,
                                26.80);
    rr_renderer_fill(renderer);
    rr_renderer_set_fill(renderer, 0xff898276);
    rr_renderer_begin_path(renderer);
    rr_renderer_move_to(renderer, -66.80, 21.84);
    rr_renderer_bezier_curve_to(renderer, -43.28, 21.84, -24.22, 40.54, -24.22,
                                63.61);
    rr_renderer_bezier_curve_to(renderer, -24.22, 74.69, -28.71, 85.31, -36.69,
                                93.14);
    rr_renderer_bezier_curve_to(renderer, -44.68, 100.97, -55.51, 105.37,
                                -66.80, 105.37);
    rr_renderer_bezier_curve_to(renderer, -90.32, 105.37, -109.39, 86.68,
                                -109.39, 63.61);
    rr_renderer_bezier_curve_to(renderer, -109.39, 40.54, -90.32, 21.84, -66.80,
                                21.84);
    rr_renderer_move_to(renderer, -66.80, 33.43);
    rr_renderer_bezier_curve_to(renderer, -83.92, 33.43, -97.80, 46.94, -97.80,
                                63.61);
    rr_renderer_bezier_curve_to(renderer, -97.80, 80.27, -83.92, 93.78, -66.80,
                                93.78);
    rr_renderer_bezier_curve_to(renderer, -49.69, 93.78, -35.81, 80.27, -35.81,
                                63.61);
    rr_renderer_bezier_curve_to(renderer, -35.81, 46.94, -49.69, 33.43, -66.80,
                                33.43);
    rr_renderer_fill(renderer);
}

void rr_triceratops_leg2_draw(struct rr_renderer *renderer)
{
    rr_renderer_set_fill(renderer, 0xffa49b8a);
    rr_renderer_begin_path(renderer);
    rr_renderer_move_to(renderer, 66.81, 26.79);
    rr_renderer_bezier_curve_to(renderer, 87.53, 26.79, 104.33, 43.27, 104.33,
                                63.59);
    rr_renderer_bezier_curve_to(renderer, 104.33, 73.36, 100.38, 82.72, 93.34,
                                89.62);
    rr_renderer_bezier_curve_to(renderer, 86.30, 96.52, 76.76, 100.40, 66.81,
                                100.40);
    rr_renderer_bezier_curve_to(renderer, 46.08, 100.40, 29.28, 83.92, 29.28,
                                63.59);
    rr_renderer_bezier_curve_to(renderer, 29.28, 43.27, 46.08, 26.79, 66.81,
                                26.79);
    rr_renderer_fill(renderer);
    rr_renderer_set_fill(renderer, 0xff898276);
    rr_renderer_begin_path(renderer);
    rr_renderer_move_to(renderer, 66.80, 21.83);
    rr_renderer_bezier_curve_to(renderer, 90.32, 21.83, 109.39, 40.53, 109.39,
                                63.60);
    rr_renderer_bezier_curve_to(renderer, 109.39, 74.68, 104.90, 85.30, 96.91,
                                93.13);
    rr_renderer_bezier_curve_to(renderer, 88.93, 100.96, 78.10, 105.36, 66.80,
                                105.36);
    rr_renderer_bezier_curve_to(renderer, 43.28, 105.36, 24.22, 86.66, 24.22,
                                63.60);
    rr_renderer_bezier_curve_to(renderer, 24.22, 40.53, 43.28, 21.83, 66.80,
                                21.83);
    rr_renderer_move_to(renderer, 66.80, 33.42);
    rr_renderer_bezier_curve_to(renderer, 49.69, 33.42, 35.81, 46.93, 35.81,
                                63.60);
    rr_renderer_bezier_curve_to(renderer, 35.81, 80.26, 49.69, 93.77, 66.80,
                                93.77);
    rr_renderer_bezier_curve_to(renderer, 83.92, 93.77, 97.80, 80.26, 97.80,
                                63.60);
    rr_renderer_bezier_curve_to(renderer, 97.80, 46.93, 83.92, 33.42, 66.80,
                                33.42);
    rr_renderer_fill(renderer);
    rr_renderer_set_fill(renderer, 0xffa49b8a);
    rr_renderer_begin_path(renderer);
    rr_renderer_move_to(renderer, -66.80, -100.40);
    rr_renderer_bezier_curve_to(renderer, -46.08, -100.40, -29.28, -83.93,
                                -29.28, -63.60);
    rr_renderer_bezier_curve_to(renderer, -29.28, -53.84, -33.23, -44.48,
                                -40.27, -37.58);
    rr_renderer_bezier_curve_to(renderer, -47.30, -30.68, -56.85, -26.80,
                                -66.80, -26.80);
    rr_renderer_bezier_curve_to(renderer, -87.52, -26.80, -104.32, -43.28,
                                -104.32, -63.60);
    rr_renderer_bezier_curve_to(renderer, -104.32, -83.93, -87.52, -100.40,
                                -66.80, -100.40);
    rr_renderer_fill(renderer);
    rr_renderer_set_fill(renderer, 0xff898276);
    rr_renderer_begin_path(renderer);
    rr_renderer_move_to(renderer, -66.80, -105.36);
    rr_renderer_bezier_curve_to(renderer, -43.28, -105.36, -24.22, -86.66,
                                -24.22, -63.60);
    rr_renderer_bezier_curve_to(renderer, -24.22, -52.52, -28.71, -41.90,
                                -36.69, -34.06);
    rr_renderer_bezier_curve_to(renderer, -44.68, -26.23, -55.51, -21.83,
                                -66.80, -21.83);
    rr_renderer_bezier_curve_to(renderer, -90.32, -21.83, -109.39, -40.53,
                                -109.39, -63.60);
    rr_renderer_bezier_curve_to(renderer, -109.39, -86.66, -90.32, -105.36,
                                -66.80, -105.36);
    rr_renderer_move_to(renderer, -66.80, -93.77);
    rr_renderer_bezier_curve_to(renderer, -83.92, -93.77, -97.80, -80.26,
                                -97.80, -63.60);
    rr_renderer_bezier_curve_to(renderer, -97.80, -46.93, -83.92, -33.42,
                                -66.80, -33.42);
    rr_renderer_bezier_curve_to(renderer, -49.69, -33.42, -35.81, -46.93,
                                -35.81, -63.60);
    rr_renderer_bezier_curve_to(renderer, -35.81, -80.26, -49.69, -93.77,
                                -66.80, -93.77);
    rr_renderer_fill(renderer);
}

void rr_triceratops_tail_draw(struct rr_renderer *renderer)
{
    rr_renderer_set_fill(renderer, 0xff898276);
    rr_renderer_begin_path(renderer);
    rr_renderer_move_to(renderer, 61.13, 52.17);
    rr_renderer_line_to(renderer, -120.35, 16.27);
    rr_renderer_line_to(renderer, -120.35, -16.27);
    rr_renderer_line_to(renderer, 61.13, -52.17);
    rr_renderer_fill(renderer);
    rr_renderer_set_fill(renderer, 0xff898276);
    rr_renderer_begin_path(renderer);
    rr_renderer_move_to(renderer, 74.55, -53.70);
    rr_renderer_bezier_curve_to(renderer, 108.77, -53.70, 136.51, -29.66,
                                136.51, 0.00);
    rr_renderer_bezier_curve_to(renderer, 136.51, 14.24, 129.98, 27.90, 118.36,
                                37.97);
    rr_renderer_bezier_curve_to(renderer, 106.74, 48.04, 90.98, 53.70, 74.55,
                                53.70);
    rr_renderer_bezier_curve_to(renderer, 40.33, 53.70, 12.59, 29.66, 12.59,
                                0.00);
    rr_renderer_bezier_curve_to(renderer, 12.59, -29.66, 40.33, -53.70, 74.55,
                                -53.70);
    rr_renderer_fill(renderer);
    rr_renderer_set_fill(renderer, 0xff898276);
    rr_renderer_begin_path(renderer);
    rr_renderer_move_to(renderer, 74.57, -37.18);
    rr_renderer_bezier_curve_to(renderer, 98.25, -37.18, 117.45, -20.54, 117.45,
                                -0.01);
    rr_renderer_bezier_curve_to(renderer, 117.45, 9.85, 112.93, 19.30, 104.89,
                                26.27);
    rr_renderer_bezier_curve_to(renderer, 96.85, 33.24, 85.94, 37.16, 74.57,
                                37.16);
    rr_renderer_bezier_curve_to(renderer, 50.88, 37.16, 31.68, 20.52, 31.68,
                                -0.01);
    rr_renderer_bezier_curve_to(renderer, 31.68, -20.54, 50.88, -37.18, 74.57,
                                -37.18);
    rr_renderer_fill(renderer);
    rr_renderer_set_fill(renderer, 0xff898276);
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
    rr_renderer_set_fill(renderer, 0xff898276);
    rr_renderer_begin_path(renderer);
    rr_renderer_move_to(renderer, 63.12, 35.81);
    rr_renderer_line_to(renderer, -120.06, -0.01);
    rr_renderer_line_to(renderer, 63.12, -35.82);
    rr_renderer_fill(renderer);
    rr_renderer_set_fill(renderer, 0xffa49b8a);
    rr_renderer_begin_path(renderer);
    rr_renderer_move_to(renderer, 74.57, -37.18);
    rr_renderer_bezier_curve_to(renderer, 98.25, -37.18, 117.45, -20.54, 117.45,
                                -0.01);
    rr_renderer_bezier_curve_to(renderer, 117.45, 9.85, 112.93, 19.30, 104.89,
                                26.27);
    rr_renderer_bezier_curve_to(renderer, 96.85, 33.24, 85.94, 37.16, 74.57,
                                37.16);
    rr_renderer_bezier_curve_to(renderer, 50.88, 37.16, 31.68, 20.52, 31.68,
                                -0.01);
    rr_renderer_bezier_curve_to(renderer, 31.68, -20.54, 50.88, -37.18, 74.57,
                                -37.18);
    rr_renderer_fill(renderer);
    rr_renderer_set_fill(renderer, 0xffa49b8a);
    rr_renderer_begin_path(renderer);
    rr_renderer_move_to(renderer, 63.12, 35.81);
    rr_renderer_line_to(renderer, -120.06, -0.01);
    rr_renderer_line_to(renderer, 63.12, -35.82);
    rr_renderer_fill(renderer);
    rr_renderer_set_fill(renderer, 0xff898276);
    rr_renderer_begin_path(renderer);
    rr_renderer_move_to(renderer, 28.53, -8.94);
    rr_renderer_bezier_curve_to(renderer, 33.47, -8.94, 37.47, -4.94, 37.47,
                                0.00);
    rr_renderer_bezier_curve_to(renderer, 37.47, 2.37, 36.53, 4.65, 34.85,
                                6.32);
    rr_renderer_bezier_curve_to(renderer, 33.18, 8.00, 30.90, 8.94, 28.53,
                                8.94);
    rr_renderer_line_to(renderer, -120.54, 8.94);
    rr_renderer_bezier_curve_to(renderer, -125.48, 8.94, -129.49, 4.94, -129.49,
                                0.00);
    rr_renderer_bezier_curve_to(renderer, -129.49, -4.94, -125.48, -8.94,
                                -120.54, -8.94);
    rr_renderer_fill(renderer);
}