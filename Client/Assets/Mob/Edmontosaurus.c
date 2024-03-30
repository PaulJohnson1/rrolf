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

void rr_edmontosaurus_body_draw(struct rr_renderer *renderer)
{
    rr_renderer_set_fill(renderer, 0xff55785a);
    rr_renderer_begin_path(renderer);
    rr_renderer_move_to(renderer, -24.27, -62.12);
    rr_renderer_bezier_curve_to(renderer, 32.78, -62.12, 79.03, -34.31, 79.03,
                                -0.00);
    rr_renderer_bezier_curve_to(renderer, 79.03, 16.47, 68.14, 32.27, 48.77,
                                43.92);
    rr_renderer_bezier_curve_to(renderer, 29.40, 55.56, 3.12, 62.11, -24.27,
                                62.11);
    rr_renderer_bezier_curve_to(renderer, -81.33, 62.11, -127.57, 34.30,
                                -127.57, -0.00);
    rr_renderer_bezier_curve_to(renderer, -127.57, -34.31, -81.33, -62.12,
                                -24.27, -62.12);
    rr_renderer_fill(renderer);
    rr_renderer_set_fill(renderer, 0xff46624a);
    rr_renderer_begin_path(renderer);
    rr_renderer_move_to(renderer, -24.28, -70.49);
    rr_renderer_bezier_curve_to(renderer, 40.46, -70.49, 92.95, -38.93, 92.95,
                                0.00);
    rr_renderer_bezier_curve_to(renderer, 92.95, 18.70, 80.60, 36.63, 58.61,
                                49.85);
    rr_renderer_bezier_curve_to(renderer, 36.63, 63.07, 6.81, 70.49, -24.28,
                                70.49);
    rr_renderer_bezier_curve_to(renderer, -89.03, 70.49, -141.52, 38.93,
                                -141.52, 0.00);
    rr_renderer_bezier_curve_to(renderer, -141.52, -38.93, -89.03, -70.49,
                                -24.28, -70.49);
    rr_renderer_move_to(renderer, -24.28, -54.49);
    rr_renderer_bezier_curve_to(renderer, -80.19, -54.49, -125.52, -30.09,
                                -125.52, 0.00);
    rr_renderer_bezier_curve_to(renderer, -125.52, 30.10, -80.19, 54.49, -24.28,
                                54.49);
    rr_renderer_bezier_curve_to(renderer, 31.62, 54.49, 76.95, 30.10, 76.95,
                                0.00);
    rr_renderer_bezier_curve_to(renderer, 76.95, -30.09, 31.62, -54.49, -24.28,
                                -54.49);
    rr_renderer_fill(renderer);
    rr_renderer_set_fill(renderer, 0xff46624a);
    rr_renderer_begin_path(renderer);
    rr_renderer_move_to(renderer, 102.96, -38.55);
    rr_renderer_bezier_curve_to(renderer, 124.25, -38.55, 141.52, -21.28,
                                141.52, 0.01);
    rr_renderer_bezier_curve_to(renderer, 141.52, 10.24, 137.45, 20.04, 130.22,
                                27.27);
    rr_renderer_bezier_curve_to(renderer, 122.99, 34.51, 113.18, 38.57, 102.96,
                                38.57);
    rr_renderer_line_to(renderer, 58.31, 38.57);
    rr_renderer_bezier_curve_to(renderer, 37.01, 38.57, 19.75, 21.31, 19.75,
                                0.01);
    rr_renderer_bezier_curve_to(renderer, 19.75, -21.28, 37.01, -38.55, 58.31,
                                -38.55);
    rr_renderer_fill(renderer);
    rr_renderer_set_fill(renderer, 0xff55785a);
    rr_renderer_begin_path(renderer);
    rr_renderer_move_to(renderer, 102.29, -27.70);
    rr_renderer_bezier_curve_to(renderer, 117.60, -27.70, 130.01, -15.30,
                                130.01, 0.01);
    rr_renderer_bezier_curve_to(renderer, 130.01, 7.36, 127.09, 14.41, 121.89,
                                19.60);
    rr_renderer_bezier_curve_to(renderer, 116.69, 24.80, 109.64, 27.72, 102.29,
                                27.72);
    rr_renderer_line_to(renderer, 35.95, 27.72);
    rr_renderer_bezier_curve_to(renderer, 20.64, 27.72, 8.24, 15.31, 8.24,
                                0.01);
    rr_renderer_bezier_curve_to(renderer, 8.24, -15.30, 20.64, -27.70, 35.95,
                                -27.70);
    rr_renderer_fill(renderer);
    rr_renderer_set_fill(renderer, 0xff3c4d3e);
    rr_renderer_begin_path(renderer);
    rr_renderer_move_to(renderer, 30.48, -6.67);
    rr_renderer_bezier_curve_to(renderer, 34.16, -6.67, 37.15, -3.68, 37.15,
                                0.00);
    rr_renderer_bezier_curve_to(renderer, 37.15, 1.77, 36.44, 3.47, 35.19,
                                4.72);
    rr_renderer_bezier_curve_to(renderer, 33.94, 5.97, 32.25, 6.67, 30.48,
                                6.67);
    rr_renderer_line_to(renderer, 15.02, 6.67);
    rr_renderer_bezier_curve_to(renderer, 11.33, 6.67, 8.35, 3.69, 8.35, 0.00);
    rr_renderer_bezier_curve_to(renderer, 8.35, -3.68, 11.33, -6.67, 15.02,
                                -6.67);
    rr_renderer_fill(renderer);
    rr_renderer_set_fill(renderer, 0xff3c4d3e);
    rr_renderer_begin_path(renderer);
    rr_renderer_move_to(renderer, 69.37, -6.70);
    rr_renderer_bezier_curve_to(renderer, 73.06, -6.70, 76.04, -3.72, 76.04,
                                -0.04);
    rr_renderer_bezier_curve_to(renderer, 76.04, 1.73, 75.34, 3.43, 74.09,
                                4.68);
    rr_renderer_bezier_curve_to(renderer, 72.84, 5.93, 71.14, 6.63, 69.37,
                                6.63);
    rr_renderer_line_to(renderer, 53.91, 6.63);
    rr_renderer_bezier_curve_to(renderer, 50.23, 6.63, 47.24, 3.65, 47.24,
                                -0.04);
    rr_renderer_bezier_curve_to(renderer, 47.24, -3.72, 50.23, -6.70, 53.91,
                                -6.70);
    rr_renderer_fill(renderer);
    rr_renderer_set_fill(renderer, 0xff3c4d3e);
    rr_renderer_begin_path(renderer);
    rr_renderer_move_to(renderer, -52.06, -7.37);
    rr_renderer_bezier_curve_to(renderer, -47.96, -7.37, -44.64, -4.05, -44.64,
                                0.05);
    rr_renderer_bezier_curve_to(renderer, -44.64, 2.01, -45.42, 3.90, -46.82,
                                5.29);
    rr_renderer_bezier_curve_to(renderer, -48.21, 6.68, -50.09, 7.46, -52.06,
                                7.46);
    rr_renderer_line_to(renderer, -69.26, 7.46);
    rr_renderer_bezier_curve_to(renderer, -73.35, 7.46, -76.67, 4.14, -76.67,
                                0.05);
    rr_renderer_bezier_curve_to(renderer, -76.67, -4.05, -73.35, -7.37, -69.26,
                                -7.37);
    rr_renderer_fill(renderer);
    rr_renderer_set_fill(renderer, 0xff3c4d3e);
    rr_renderer_begin_path(renderer);
    rr_renderer_move_to(renderer, -8.85, -7.36);
    rr_renderer_bezier_curve_to(renderer, -4.75, -7.36, -1.43, -4.04, -1.43,
                                0.06);
    rr_renderer_bezier_curve_to(renderer, -1.43, 2.02, -2.21, 3.91, -3.61,
                                5.30);
    rr_renderer_bezier_curve_to(renderer, -5.00, 6.69, -6.88, 7.47, -8.85,
                                7.47);
    rr_renderer_line_to(renderer, -26.05, 7.47);
    rr_renderer_bezier_curve_to(renderer, -30.14, 7.47, -33.46, 4.15, -33.46,
                                0.06);
    rr_renderer_bezier_curve_to(renderer, -33.46, -4.04, -30.14, -7.36, -26.05,
                                -7.36);
    rr_renderer_fill(renderer);
    rr_renderer_set_fill(renderer, 0xff3c4d3e);
    rr_renderer_begin_path(renderer);
    rr_renderer_move_to(renderer, -93.76, -7.37);
    rr_renderer_bezier_curve_to(renderer, -89.66, -7.37, -86.34, -4.05, -86.34,
                                0.05);
    rr_renderer_bezier_curve_to(renderer, -86.34, 2.02, -87.13, 3.91, -88.52,
                                5.30);
    rr_renderer_bezier_curve_to(renderer, -89.91, 6.69, -91.79, 7.47, -93.76,
                                7.47);
    rr_renderer_line_to(renderer, -110.96, 7.47);
    rr_renderer_bezier_curve_to(renderer, -115.05, 7.47, -118.38, 4.15, -118.38,
                                0.05);
    rr_renderer_bezier_curve_to(renderer, -118.38, -4.05, -115.05, -7.37,
                                -110.96, -7.37);
    rr_renderer_fill(renderer);
}

void rr_edmontosaurus_head_draw(struct rr_renderer *renderer)
{
    rr_renderer_set_fill(renderer, 0xff46624a);
    rr_renderer_begin_path(renderer);
    rr_renderer_move_to(renderer, 37.57, -34.48);
    rr_renderer_bezier_curve_to(renderer, 56.62, -34.48, 72.05, -19.04, 72.05,
                                0.00);
    rr_renderer_bezier_curve_to(renderer, 72.05, 9.15, 68.42, 17.92, 61.95,
                                24.38);
    rr_renderer_bezier_curve_to(renderer, 55.49, 30.85, 46.72, 34.48, 37.57,
                                34.48);
    rr_renderer_line_to(renderer, 37.31, 34.48);
    rr_renderer_bezier_curve_to(renderer, 18.27, 34.48, 2.83, 19.05, 2.83,
                                0.00);
    rr_renderer_bezier_curve_to(renderer, 2.83, -19.04, 18.27, -34.48, 37.31,
                                -34.48);
    rr_renderer_fill(renderer);
    rr_renderer_set_fill(renderer, 0xff55785a);
    rr_renderer_begin_path(renderer);
    rr_renderer_move_to(renderer, -29.05, -36.62);
    rr_renderer_bezier_curve_to(renderer, -8.13, -36.62, 8.83, -20.22, 8.83,
                                -0.00);
    rr_renderer_bezier_curve_to(renderer, 8.83, 9.71, 4.84, 19.02, -2.26,
                                25.89);
    rr_renderer_bezier_curve_to(renderer, -9.37, 32.75, -19.00, 36.61, -29.05,
                                36.61);
    rr_renderer_bezier_curve_to(renderer, -49.97, 36.61, -66.94, 20.22, -66.94,
                                -0.00);
    rr_renderer_bezier_curve_to(renderer, -66.94, -20.22, -49.97, -36.62,
                                -29.05, -36.62);
    rr_renderer_fill(renderer);
    rr_renderer_set_fill(renderer, 0xff46624a);
    rr_renderer_begin_path(renderer);
    rr_renderer_move_to(renderer, -29.06, -41.55);
    rr_renderer_bezier_curve_to(renderer, -5.31, -41.55, 13.94, -22.95, 13.94,
                                0.00);
    rr_renderer_bezier_curve_to(renderer, 13.94, 11.02, 9.41, 21.59, 1.35,
                                29.38);
    rr_renderer_bezier_curve_to(renderer, -6.72, 37.18, -17.65, 41.55, -29.06,
                                41.55);
    rr_renderer_bezier_curve_to(renderer, -52.81, 41.55, -72.06, 22.95, -72.06,
                                0.00);
    rr_renderer_bezier_curve_to(renderer, -72.06, -22.95, -52.81, -41.55,
                                -29.06, -41.55);
    rr_renderer_move_to(renderer, -29.06, -30.02);
    rr_renderer_bezier_curve_to(renderer, -46.44, -30.02, -60.53, -16.58,
                                -60.53, 0.00);
    rr_renderer_bezier_curve_to(renderer, -60.53, 16.58, -46.44, 30.02, -29.06,
                                30.02);
    rr_renderer_bezier_curve_to(renderer, -11.68, 30.02, 2.41, 16.58, 2.41,
                                0.00);
    rr_renderer_bezier_curve_to(renderer, 2.41, -16.58, -11.68, -30.02, -29.06,
                                -30.02);
    rr_renderer_fill(renderer);
    rr_renderer_set_fill(renderer, 0xff55785a);
    rr_renderer_begin_path(renderer);
    rr_renderer_move_to(renderer, 37.53, -23.41);
    rr_renderer_bezier_curve_to(renderer, 50.46, -23.41, 60.94, -12.93, 60.94,
                                0.00);
    rr_renderer_bezier_curve_to(renderer, 60.94, 6.21, 58.48, 12.17, 54.09,
                                16.56);
    rr_renderer_bezier_curve_to(renderer, 49.69, 20.95, 43.74, 23.42, 37.53,
                                23.42);
    rr_renderer_line_to(renderer, 37.36, 23.42);
    rr_renderer_bezier_curve_to(renderer, 24.42, 23.42, 13.94, 12.93, 13.94,
                                0.00);
    rr_renderer_bezier_curve_to(renderer, 13.94, -12.93, 24.42, -23.41, 37.36,
                                -23.41);
    rr_renderer_fill(renderer);
    rr_renderer_set_fill(renderer, 0xff46624a);
    rr_renderer_begin_path(renderer);
    rr_renderer_move_to(renderer, -21.27, 29.16);
    rr_renderer_bezier_curve_to(renderer, -22.27, 19.87, -10.37, 10.97, 5.30,
                                9.29);
    rr_renderer_bezier_curve_to(renderer, 20.97, 7.61, 34.48, 13.78, 35.48,
                                23.07);
    rr_renderer_bezier_curve_to(renderer, 17.00, 19.86, -3.89, 22.10, -21.27,
                                29.16);
    rr_renderer_fill(renderer);
    rr_renderer_set_fill(renderer, 0xff46624a);
    rr_renderer_begin_path(renderer);
    rr_renderer_move_to(renderer, -13.08, -38.67);
    rr_renderer_bezier_curve_to(renderer, -14.08, -29.38, -5.12, -20.80, 6.94,
                                -19.50);
    rr_renderer_bezier_curve_to(renderer, 18.99, -18.21, 29.57, -24.69, 30.57,
                                -33.98);
    rr_renderer_bezier_curve_to(renderer, 16.23, -30.33, 0.16, -32.05, -13.08,
                                -38.67);
    rr_renderer_fill(renderer);
    rr_renderer_set_fill(renderer, 0xff55785a);
    rr_renderer_begin_path(renderer);
    rr_renderer_move_to(renderer, -21.27, -29.43);
    rr_renderer_bezier_curve_to(renderer, -22.27, -20.13, -10.37, -11.24, 5.30,
                                -9.56);
    rr_renderer_bezier_curve_to(renderer, 20.97, -7.88, 34.48, -14.05, 35.48,
                                -23.34);
    rr_renderer_bezier_curve_to(renderer, 17.00, -20.13, -3.89, -22.37, -21.27,
                                -29.43);
    rr_renderer_fill(renderer);
    rr_renderer_set_fill(renderer, 0xff55785a);
    rr_renderer_begin_path(renderer);
    rr_renderer_move_to(renderer, 23.10, -16.90);
    rr_renderer_line_to(renderer, 23.10, 16.90);
    rr_renderer_line_to(renderer, -10.69, 16.90);
    rr_renderer_line_to(renderer, -10.69, -16.90);
    rr_renderer_fill(renderer);
    rr_renderer_set_fill(renderer, 0xff3c4d3e);
    rr_renderer_begin_path(renderer);
    rr_renderer_move_to(renderer, -8.50, -6.94);
    rr_renderer_bezier_curve_to(renderer, -4.66, -6.94, -1.55, -3.83, -1.55,
                                0.00);
    rr_renderer_bezier_curve_to(renderer, -1.55, 1.85, -2.28, 3.61, -3.59,
                                4.92);
    rr_renderer_bezier_curve_to(renderer, -4.89, 6.22, -6.66, 6.95, -8.50,
                                6.95);
    rr_renderer_line_to(renderer, -41.61, 6.95);
    rr_renderer_bezier_curve_to(renderer, -45.44, 6.95, -48.56, 3.84, -48.56,
                                0.00);
    rr_renderer_bezier_curve_to(renderer, -48.56, -3.83, -45.44, -6.94, -41.61,
                                -6.94);
    rr_renderer_fill(renderer);
    rr_renderer_set_fill(renderer, 0xff46624a);
    rr_renderer_begin_path(renderer);
    rr_renderer_move_to(renderer, -13.08, 38.68);
    rr_renderer_bezier_curve_to(renderer, -14.08, 29.39, -5.12, 20.80, 6.94,
                                19.51);
    rr_renderer_bezier_curve_to(renderer, 18.99, 18.21, 29.57, 24.70, 30.57,
                                33.99);
    rr_renderer_bezier_curve_to(renderer, 16.23, 30.34, 0.16, 32.06, -13.08,
                                38.68);
    rr_renderer_fill(renderer);
    rr_renderer_set_fill(renderer, 0xff55785a);
    rr_renderer_begin_path(renderer);
    rr_renderer_move_to(renderer, -21.27, 29.43);
    rr_renderer_bezier_curve_to(renderer, -22.27, 20.14, -10.37, 11.25, 5.30,
                                9.57);
    rr_renderer_bezier_curve_to(renderer, 20.97, 7.89, 34.48, 14.06, 35.48,
                                23.35);
    rr_renderer_bezier_curve_to(renderer, 17.00, 20.14, -3.89, 22.38, -21.27,
                                29.43);
    rr_renderer_fill(renderer);
}

void rr_edmontosaurus_leg1_draw(struct rr_renderer *renderer)
{
    rr_renderer_set_fill(renderer, 0xff3c4d3e);
    rr_renderer_begin_path(renderer);
    rr_renderer_move_to(renderer, 57.47, 76.09);
    rr_renderer_bezier_curve_to(renderer, 68.30, 79.05, 79.49, 72.67, 82.46,
                                61.84);
    rr_renderer_bezier_curve_to(renderer, 83.88, 56.63, 83.18, 51.08, 80.51,
                                46.39);
    rr_renderer_bezier_curve_to(renderer, 77.83, 41.70, 73.41, 38.27, 68.21,
                                36.84);
    rr_renderer_line_to(renderer, 51.20, 32.19);
    rr_renderer_bezier_curve_to(renderer, 40.36, 29.22, 29.17, 35.60, 26.21,
                                46.44);
    rr_renderer_bezier_curve_to(renderer, 23.24, 57.27, 29.62, 68.46, 40.46,
                                71.43);
    rr_renderer_fill(renderer);
    rr_renderer_set_fill(renderer, 0xff3c4d3e);
    rr_renderer_begin_path(renderer);
    rr_renderer_move_to(renderer, 59.11, 68.24);
    rr_renderer_bezier_curve_to(renderer, 65.68, 70.04, 72.47, 66.17, 74.27,
                                59.60);
    rr_renderer_bezier_curve_to(renderer, 75.14, 56.44, 74.71, 53.07, 73.09,
                                50.22);
    rr_renderer_bezier_curve_to(renderer, 71.47, 47.38, 68.79, 45.29, 65.63,
                                44.43);
    rr_renderer_line_to(renderer, 42.79, 38.17);
    rr_renderer_bezier_curve_to(renderer, 36.22, 36.37, 29.43, 40.23, 27.63,
                                46.81);
    rr_renderer_bezier_curve_to(renderer, 25.83, 53.39, 29.70, 60.18, 36.27,
                                61.98);
    rr_renderer_fill(renderer);
    rr_renderer_set_fill(renderer, 0xff55785a);
    rr_renderer_begin_path(renderer);
    rr_renderer_move_to(renderer, 37.01, 75.51);
    rr_renderer_bezier_curve_to(renderer, 50.69, 79.25, 64.77, 71.40, 68.45,
                                57.96);
    rr_renderer_bezier_curve_to(renderer, 70.22, 51.51, 69.30, 44.61, 65.90,
                                38.77);
    rr_renderer_bezier_curve_to(renderer, 62.50, 32.93, 56.90, 28.64, 50.33,
                                26.84);
    rr_renderer_bezier_curve_to(renderer, 36.64, 23.10, 22.56, 30.95, 18.88,
                                44.39);
    rr_renderer_bezier_curve_to(renderer, 15.20, 57.82, 23.32, 71.76, 37.01,
                                75.51);
    rr_renderer_fill(renderer);
    rr_renderer_set_fill(renderer, 0xff46624a);
    rr_renderer_begin_path(renderer);
    rr_renderer_move_to(renderer, 36.09, 78.79);
    rr_renderer_bezier_curve_to(renderer, 51.64, 83.04, 67.62, 74.13, 71.80,
                                58.88);
    rr_renderer_bezier_curve_to(renderer, 73.80, 51.56, 72.76, 43.73, 68.90,
                                37.10);
    rr_renderer_bezier_curve_to(renderer, 65.04, 30.48, 58.68, 25.62, 51.21,
                                23.57);
    rr_renderer_bezier_curve_to(renderer, 35.67, 19.32, 19.69, 28.23, 15.51,
                                43.48);
    rr_renderer_bezier_curve_to(renderer, 11.34, 58.72, 20.55, 74.53, 36.09,
                                78.79);
    rr_renderer_move_to(renderer, 38.19, 71.12);
    rr_renderer_bezier_curve_to(renderer, 26.88, 68.03, 20.16, 56.59, 23.17,
                                45.57);
    rr_renderer_bezier_curve_to(renderer, 26.19, 34.56, 37.80, 28.14, 49.11,
                                31.23);
    rr_renderer_bezier_curve_to(renderer, 60.43, 34.33, 67.15, 45.77, 64.13,
                                56.78);
    rr_renderer_bezier_curve_to(renderer, 61.12, 67.80, 49.50, 74.22, 38.19,
                                71.12);
    rr_renderer_fill(renderer);
    rr_renderer_set_fill(renderer, 0xff55785a);
    rr_renderer_begin_path(renderer);
    rr_renderer_move_to(renderer, -48.51, -81.91);
    rr_renderer_bezier_curve_to(renderer, -29.38, -81.91, -13.87, -66.69,
                                -13.87, -47.92);
    rr_renderer_bezier_curve_to(renderer, -13.87, -38.91, -17.52, -30.26,
                                -24.02, -23.89);
    rr_renderer_bezier_curve_to(renderer, -30.51, -17.52, -39.32, -13.94,
                                -48.51, -13.94);
    rr_renderer_bezier_curve_to(renderer, -67.64, -13.94, -83.15, -29.15,
                                -83.15, -47.92);
    rr_renderer_bezier_curve_to(renderer, -83.15, -66.69, -67.64, -81.91,
                                -48.51, -81.91);
    rr_renderer_fill(renderer);
    rr_renderer_set_fill(renderer, 0xff46624a);
    rr_renderer_begin_path(renderer);
    rr_renderer_move_to(renderer, -48.51, -86.49);
    rr_renderer_bezier_curve_to(renderer, -26.80, -86.49, -9.20, -69.22, -9.20,
                                -47.92);
    rr_renderer_bezier_curve_to(renderer, -9.20, -37.69, -13.34, -27.88, -20.72,
                                -20.65);
    rr_renderer_bezier_curve_to(renderer, -28.09, -13.41, -38.09, -9.35, -48.51,
                                -9.35);
    rr_renderer_bezier_curve_to(renderer, -70.23, -9.35, -87.83, -26.62, -87.83,
                                -47.92);
    rr_renderer_bezier_curve_to(renderer, -87.83, -69.22, -70.23, -86.49,
                                -48.51, -86.49);
    rr_renderer_move_to(renderer, -48.51, -75.78);
    rr_renderer_bezier_curve_to(renderer, -64.32, -75.78, -77.13, -63.31,
                                -77.13, -47.92);
    rr_renderer_bezier_curve_to(renderer, -77.13, -32.53, -64.32, -20.05,
                                -48.51, -20.05);
    rr_renderer_bezier_curve_to(renderer, -32.71, -20.05, -19.90, -32.53,
                                -19.90, -47.92);
    rr_renderer_bezier_curve_to(renderer, -19.90, -63.31, -32.71, -75.78,
                                -48.51, -75.78);
    rr_renderer_fill(renderer);
}

void rr_edmontosaurus_leg2_draw(struct rr_renderer *renderer)
{
    rr_renderer_set_fill(renderer, 0xff3c4d3e);
    rr_renderer_begin_path(renderer);
    rr_renderer_move_to(renderer, 57.47, -76.15);
    rr_renderer_bezier_curve_to(renderer, 68.30, -79.11, 79.49, -72.73, 82.46,
                                -61.90);
    rr_renderer_bezier_curve_to(renderer, 83.88, -56.69, 83.18, -51.14, 80.51,
                                -46.45);
    rr_renderer_bezier_curve_to(renderer, 77.84, -41.76, 73.41, -38.33, 68.21,
                                -36.90);
    rr_renderer_line_to(renderer, 51.20, -32.25);
    rr_renderer_bezier_curve_to(renderer, 40.36, -29.28, 29.17, -35.66, 26.21,
                                -46.50);
    rr_renderer_bezier_curve_to(renderer, 23.24, -57.33, 29.62, -68.52, 40.46,
                                -71.49);
    rr_renderer_fill(renderer);
    rr_renderer_set_fill(renderer, 0xff3c4d3e);
    rr_renderer_begin_path(renderer);
    rr_renderer_move_to(renderer, 59.11, -68.30);
    rr_renderer_bezier_curve_to(renderer, 65.68, -70.10, 72.47, -66.23, 74.27,
                                -59.66);
    rr_renderer_bezier_curve_to(renderer, 75.14, -56.50, 74.71, -53.13, 73.09,
                                -50.28);
    rr_renderer_bezier_curve_to(renderer, 71.47, -47.44, 68.79, -45.35, 65.63,
                                -44.49);
    rr_renderer_line_to(renderer, 42.79, -38.23);
    rr_renderer_bezier_curve_to(renderer, 36.22, -36.42, 29.43, -40.29, 27.63,
                                -46.87);
    rr_renderer_bezier_curve_to(renderer, 25.83, -53.44, 29.70, -60.24, 36.27,
                                -62.04);
    rr_renderer_fill(renderer);
    rr_renderer_set_fill(renderer, 0xff55785a);
    rr_renderer_begin_path(renderer);
    rr_renderer_move_to(renderer, 37.01, -75.56);
    rr_renderer_bezier_curve_to(renderer, 50.70, -79.31, 64.78, -71.46, 68.46,
                                -58.02);
    rr_renderer_bezier_curve_to(renderer, 70.22, -51.57, 69.31, -44.66, 65.91,
                                -38.83);
    rr_renderer_bezier_curve_to(renderer, 62.51, -32.99, 56.90, -28.70, 50.33,
                                -26.90);
    rr_renderer_bezier_curve_to(renderer, 36.64, -23.15, 22.56, -31.01, 18.88,
                                -44.45);
    rr_renderer_bezier_curve_to(renderer, 15.20, -57.88, 23.32, -71.82, 37.01,
                                -75.56);
    rr_renderer_fill(renderer);
    rr_renderer_set_fill(renderer, 0xff46624a);
    rr_renderer_begin_path(renderer);
    rr_renderer_move_to(renderer, 36.10, -78.84);
    rr_renderer_bezier_curve_to(renderer, 51.64, -83.10, 67.62, -74.19, 71.80,
                                -58.94);
    rr_renderer_bezier_curve_to(renderer, 73.80, -51.62, 72.76, -43.78, 68.90,
                                -37.16);
    rr_renderer_bezier_curve_to(renderer, 65.04, -30.54, 58.68, -25.67, 51.21,
                                -23.63);
    rr_renderer_bezier_curve_to(renderer, 35.67, -19.38, 19.69, -28.29, 15.51,
                                -43.54);
    rr_renderer_bezier_curve_to(renderer, 11.34, -58.78, 20.55, -74.59, 36.10,
                                -78.84);
    rr_renderer_move_to(renderer, 38.19, -71.18);
    rr_renderer_bezier_curve_to(renderer, 26.88, -68.09, 20.16, -56.65, 23.17,
                                -45.63);
    rr_renderer_bezier_curve_to(renderer, 26.19, -34.62, 37.81, -28.20, 49.12,
                                -31.29);
    rr_renderer_bezier_curve_to(renderer, 60.43, -34.39, 67.15, -45.83, 64.14,
                                -56.84);
    rr_renderer_bezier_curve_to(renderer, 61.12, -67.86, 49.51, -74.28, 38.19,
                                -71.18);
    rr_renderer_fill(renderer);
    rr_renderer_set_fill(renderer, 0xff55785a);
    rr_renderer_begin_path(renderer);
    rr_renderer_move_to(renderer, -48.51, 13.99);
    rr_renderer_bezier_curve_to(renderer, -29.38, 13.99, -13.87, 29.21, -13.87,
                                47.97);
    rr_renderer_bezier_curve_to(renderer, -13.87, 56.99, -17.52, 65.63, -24.02,
                                72.01);
    rr_renderer_bezier_curve_to(renderer, -30.51, 78.38, -39.32, 81.96, -48.51,
                                81.96);
    rr_renderer_bezier_curve_to(renderer, -67.64, 81.96, -83.15, 66.74, -83.15,
                                47.97);
    rr_renderer_bezier_curve_to(renderer, -83.15, 29.21, -67.64, 13.99, -48.51,
                                13.99);
    rr_renderer_fill(renderer);
    rr_renderer_set_fill(renderer, 0xff46624a);
    rr_renderer_begin_path(renderer);
    rr_renderer_move_to(renderer, -48.51, 9.41);
    rr_renderer_bezier_curve_to(renderer, -26.80, 9.41, -9.20, 26.68, -9.20,
                                47.98);
    rr_renderer_bezier_curve_to(renderer, -9.20, 58.21, -13.34, 68.02, -20.72,
                                75.25);
    rr_renderer_bezier_curve_to(renderer, -28.09, 82.48, -38.09, 86.55, -48.51,
                                86.55);
    rr_renderer_bezier_curve_to(renderer, -70.23, 86.55, -87.83, 69.28, -87.83,
                                47.98);
    rr_renderer_bezier_curve_to(renderer, -87.83, 26.68, -70.23, 9.41, -48.51,
                                9.41);
    rr_renderer_move_to(renderer, -48.51, 20.11);
    rr_renderer_bezier_curve_to(renderer, -64.32, 20.11, -77.13, 32.59, -77.13,
                                47.98);
    rr_renderer_bezier_curve_to(renderer, -77.13, 63.37, -64.32, 75.84, -48.51,
                                75.84);
    rr_renderer_bezier_curve_to(renderer, -32.71, 75.84, -19.90, 63.37, -19.90,
                                47.98);
    rr_renderer_bezier_curve_to(renderer, -19.90, 32.59, -32.71, 20.11, -48.51,
                                20.11);
    rr_renderer_fill(renderer);
}

void rr_edmontosaurus_tail_draw(struct rr_renderer *renderer)
{
    rr_renderer_set_fill(renderer, 0xff46624a);
    rr_renderer_begin_path(renderer);
    rr_renderer_move_to(renderer, 68.34, 58.33);
    rr_renderer_line_to(renderer, -134.54, 18.19);
    rr_renderer_line_to(renderer, -134.54, -18.19);
    rr_renderer_line_to(renderer, 68.34, -58.32);
    rr_renderer_fill(renderer);
    rr_renderer_set_fill(renderer, 0xff46624a);
    rr_renderer_begin_path(renderer);
    rr_renderer_move_to(renderer, 83.35, -60.04);
    rr_renderer_bezier_curve_to(renderer, 121.60, -60.04, 152.61, -33.16,
                                152.61, 0.00);
    rr_renderer_bezier_curve_to(renderer, 152.61, 15.92, 145.31, 31.19, 132.32,
                                42.45);
    rr_renderer_bezier_curve_to(renderer, 119.33, 53.71, 101.72, 60.04, 83.35,
                                60.04);
    rr_renderer_bezier_curve_to(renderer, 45.09, 60.04, 14.08, 33.16, 14.08,
                                0.00);
    rr_renderer_bezier_curve_to(renderer, 14.08, -33.16, 45.09, -60.04, 83.35,
                                -60.04);
    rr_renderer_fill(renderer);
    rr_renderer_set_fill(renderer, 0xff46624a);
    rr_renderer_begin_path(renderer);
    rr_renderer_move_to(renderer, 83.36, -41.57);
    rr_renderer_bezier_curve_to(renderer, 109.84, -41.57, 131.30, -22.96,
                                131.30, -0.01);
    rr_renderer_bezier_curve_to(renderer, 131.30, 11.01, 126.25, 21.58, 117.26,
                                29.37);
    rr_renderer_bezier_curve_to(renderer, 108.27, 37.16, 96.08, 41.54, 83.36,
                                41.54);
    rr_renderer_bezier_curve_to(renderer, 56.88, 41.54, 35.42, 22.94, 35.42,
                                -0.01);
    rr_renderer_bezier_curve_to(renderer, 35.42, -22.96, 56.88, -41.57, 83.36,
                                -41.57);
    rr_renderer_fill(renderer);
    rr_renderer_set_fill(renderer, 0xff46624a);
    rr_renderer_begin_path(renderer);
    rr_renderer_move_to(renderer, -131.46, -18.34);
    rr_renderer_bezier_curve_to(renderer, -119.77, -18.34, -110.30, -10.13,
                                -110.30, -0.01);
    rr_renderer_bezier_curve_to(renderer, -110.30, 4.86, -112.53, 9.52, -116.50,
                                12.96);
    rr_renderer_bezier_curve_to(renderer, -120.47, 16.40, -125.85, 18.33,
                                -131.46, 18.33);
    rr_renderer_bezier_curve_to(renderer, -143.14, 18.33, -152.61, 10.12,
                                -152.61, -0.01);
    rr_renderer_bezier_curve_to(renderer, -152.61, -10.13, -143.14, -18.34,
                                -131.46, -18.34);
    rr_renderer_fill(renderer);
    rr_renderer_set_fill(renderer, 0xff46624a);
    rr_renderer_begin_path(renderer);
    rr_renderer_move_to(renderer, 70.56, 40.03);
    rr_renderer_line_to(renderer, -134.22, -0.01);
    rr_renderer_line_to(renderer, 70.56, -40.05);
    rr_renderer_fill(renderer);
    rr_renderer_set_fill(renderer, 0xff55785a);
    rr_renderer_begin_path(renderer);
    rr_renderer_move_to(renderer, 83.40, -41.57);
    rr_renderer_bezier_curve_to(renderer, 109.87, -41.57, 131.33, -22.96,
                                131.33, -0.01);
    rr_renderer_bezier_curve_to(renderer, 131.33, 11.01, 126.28, 21.58, 117.29,
                                29.37);
    rr_renderer_bezier_curve_to(renderer, 108.30, 37.16, 96.11, 41.54, 83.40,
                                41.54);
    rr_renderer_bezier_curve_to(renderer, 56.92, 41.54, 35.46, 22.94, 35.46,
                                -0.01);
    rr_renderer_bezier_curve_to(renderer, 35.46, -22.96, 56.92, -41.57, 83.40,
                                -41.57);
    rr_renderer_fill(renderer);
    rr_renderer_set_fill(renderer, 0xff55785a);
    rr_renderer_begin_path(renderer);
    rr_renderer_move_to(renderer, 70.60, 40.03);
    rr_renderer_line_to(renderer, -134.17, -0.01);
    rr_renderer_line_to(renderer, 70.60, -40.05);
    rr_renderer_fill(renderer);
    rr_renderer_set_fill(renderer, 0xff3c4d3e);
    rr_renderer_begin_path(renderer);
    rr_renderer_move_to(renderer, 63.16, -7.39);
    rr_renderer_bezier_curve_to(renderer, 67.26, -7.39, 70.58, -4.07, 70.58,
                                0.02);
    rr_renderer_bezier_curve_to(renderer, 70.58, 1.99, 69.80, 3.88, 68.41,
                                5.27);
    rr_renderer_bezier_curve_to(renderer, 67.02, 6.66, 65.13, 7.44, 63.16,
                                7.44);
    rr_renderer_line_to(renderer, 45.97, 7.44);
    rr_renderer_bezier_curve_to(renderer, 41.87, 7.44, 38.55, 4.12, 38.55,
                                0.02);
    rr_renderer_bezier_curve_to(renderer, 38.55, -4.07, 41.87, -7.39, 45.97,
                                -7.39);
    rr_renderer_fill(renderer);
    rr_renderer_set_fill(renderer, 0xff3c4d3e);
    rr_renderer_begin_path(renderer);
    rr_renderer_move_to(renderer, 19.95, -7.37);
    rr_renderer_bezier_curve_to(renderer, 24.05, -7.37, 27.37, -4.05, 27.37,
                                0.04);
    rr_renderer_bezier_curve_to(renderer, 27.37, 2.01, 26.59, 3.90, 25.20,
                                5.29);
    rr_renderer_bezier_curve_to(renderer, 23.81, 6.68, 21.92, 7.46, 19.95,
                                7.46);
    rr_renderer_line_to(renderer, 2.76, 7.46);
    rr_renderer_bezier_curve_to(renderer, -1.34, 7.46, -4.66, 4.14, -4.66,
                                0.04);
    rr_renderer_bezier_curve_to(renderer, -4.66, -4.05, -1.34, -7.37, 2.76,
                                -7.37);
    rr_renderer_fill(renderer);
    rr_renderer_set_fill(renderer, 0xff3c4d3e);
    rr_renderer_begin_path(renderer);
    rr_renderer_move_to(renderer, -23.26, -7.37);
    rr_renderer_bezier_curve_to(renderer, -19.16, -7.37, -15.84, -4.05, -15.84,
                                0.04);
    rr_renderer_bezier_curve_to(renderer, -15.84, 2.01, -16.62, 3.90, -18.01,
                                5.29);
    rr_renderer_bezier_curve_to(renderer, -19.40, 6.68, -21.29, 7.46, -23.26,
                                7.46);
    rr_renderer_line_to(renderer, -40.45, 7.46);
    rr_renderer_bezier_curve_to(renderer, -44.55, 7.46, -47.87, 4.14, -47.87,
                                0.04);
    rr_renderer_bezier_curve_to(renderer, -47.87, -4.05, -44.55, -7.37, -40.45,
                                -7.37);
    rr_renderer_fill(renderer);
    rr_renderer_set_fill(renderer, 0xff3c4d3e);
    rr_renderer_begin_path(renderer);
    rr_renderer_move_to(renderer, -66.47, -7.43);
    rr_renderer_bezier_curve_to(renderer, -62.37, -7.43, -59.05, -4.11, -59.05,
                                -0.01);
    rr_renderer_bezier_curve_to(renderer, -59.05, 1.96, -59.83, 3.84, -61.22,
                                5.24);
    rr_renderer_bezier_curve_to(renderer, -62.61, 6.63, -64.50, 7.41, -66.47,
                                7.41);
    rr_renderer_line_to(renderer, -83.66, 7.41);
    rr_renderer_bezier_curve_to(renderer, -87.76, 7.41, -91.08, 4.09, -91.08,
                                -0.01);
    rr_renderer_bezier_curve_to(renderer, -91.08, -4.11, -87.76, -7.43, -83.66,
                                -7.43);
    rr_renderer_fill(renderer);
    rr_renderer_set_fill(renderer, 0xff3c4d3e);
    rr_renderer_begin_path(renderer);
    rr_renderer_move_to(renderer, -109.68, -7.37);
    rr_renderer_bezier_curve_to(renderer, -105.58, -7.37, -102.26, -4.05,
                                -102.26, 0.04);
    rr_renderer_bezier_curve_to(renderer, -102.26, 2.01, -103.04, 3.90, -104.43,
                                5.29);
    rr_renderer_bezier_curve_to(renderer, -105.82, 6.68, -107.71, 7.46, -109.68,
                                7.46);
    rr_renderer_line_to(renderer, -126.87, 7.46);
    rr_renderer_bezier_curve_to(renderer, -130.97, 7.46, -134.29, 4.14, -134.29,
                                0.04);
    rr_renderer_bezier_curve_to(renderer, -134.29, -4.05, -130.97, -7.37,
                                -126.87, -7.37);
    rr_renderer_fill(renderer);
}