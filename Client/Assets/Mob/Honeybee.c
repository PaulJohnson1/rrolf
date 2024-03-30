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

void rr_honeybee_head_draw(struct rr_renderer *renderer)
{
    rr_renderer_set_fill(renderer, 0xff332a10);
    rr_renderer_begin_path(renderer);
    rr_renderer_move_to(renderer, 12.04, 37.93);
    rr_renderer_bezier_curve_to(renderer, 16.00, 37.93, 18.95, 36.43, 25.02,
                                33.34);
    rr_renderer_bezier_curve_to(renderer, 31.10, 30.24, 42.44, 24.53, 48.50,
                                19.35);
    rr_renderer_bezier_curve_to(renderer, 54.56, 14.18, 62.23, 5.43, 61.37,
                                2.31);
    rr_renderer_bezier_curve_to(renderer, 60.50, -0.81, 49.27, 1.64, 43.31,
                                0.64);
    rr_renderer_bezier_curve_to(renderer, 37.35, -0.36, 29.80, -5.63, 25.60,
                                -3.70);
    rr_renderer_bezier_curve_to(renderer, 21.40, -1.76, 22.17, 7.94, 18.11,
                                12.26);
    rr_renderer_bezier_curve_to(renderer, 14.05, 16.58, 4.05, 18.74, 1.24,
                                22.25);
    rr_renderer_bezier_curve_to(renderer, -1.57, 25.76, -0.55, 30.72, 1.25,
                                33.34);
    rr_renderer_bezier_curve_to(renderer, 3.05, 35.95, 8.08, 37.93, 12.04,
                                37.93);
    rr_renderer_fill(renderer);
    rr_renderer_set_fill(renderer, 0xff332a10);
    rr_renderer_begin_path(renderer);
    rr_renderer_move_to(renderer, 12.04, -37.93);
    rr_renderer_bezier_curve_to(renderer, 16.00, -37.93, 18.95, -36.43, 25.02,
                                -33.33);
    rr_renderer_bezier_curve_to(renderer, 31.10, -30.24, 42.44, -24.52, 48.50,
                                -19.35);
    rr_renderer_bezier_curve_to(renderer, 54.56, -14.18, 62.23, -5.43, 61.37,
                                -2.31);
    rr_renderer_bezier_curve_to(renderer, 60.50, 0.81, 49.27, -1.64, 43.31,
                                -0.64);
    rr_renderer_bezier_curve_to(renderer, 37.35, 0.36, 29.80, 5.63, 25.60,
                                3.70);
    rr_renderer_bezier_curve_to(renderer, 21.40, 1.76, 22.17, -7.93, 18.11,
                                -12.26);
    rr_renderer_bezier_curve_to(renderer, 14.05, -16.58, 4.05, -18.73, 1.24,
                                -22.25);
    rr_renderer_bezier_curve_to(renderer, -1.57, -25.76, -0.55, -30.72, 1.25,
                                -33.33);
    rr_renderer_bezier_curve_to(renderer, 3.05, -35.95, 8.08, -37.93, 12.04,
                                -37.93);
    rr_renderer_fill(renderer);
    rr_renderer_set_fill(renderer, 0xff8b7437);
    rr_renderer_begin_path(renderer);
    rr_renderer_move_to(renderer, -12.69, -55.43);
    rr_renderer_bezier_curve_to(renderer, 18.53, -55.43, 43.84, -30.61, 43.84,
                                0.01);
    rr_renderer_bezier_curve_to(renderer, 43.84, 14.72, 37.88, 28.82, 27.28,
                                39.22);
    rr_renderer_bezier_curve_to(renderer, 16.68, 49.61, 2.30, 55.46, -12.69,
                                55.46);
    rr_renderer_bezier_curve_to(renderer, -43.92, 55.46, -69.23, 30.63, -69.23,
                                0.01);
    rr_renderer_bezier_curve_to(renderer, -69.23, -30.61, -43.92, -55.43,
                                -12.69, -55.43);
    rr_renderer_move_to(renderer, -12.69, -26.19);
    rr_renderer_bezier_curve_to(renderer, -27.77, -26.19, -39.99, -14.46,
                                -39.99, 0.01);
    rr_renderer_bezier_curve_to(renderer, -39.99, 14.48, -27.77, 26.22, -12.69,
                                26.22);
    rr_renderer_bezier_curve_to(renderer, 2.38, 26.22, 14.60, 14.48, 14.60,
                                0.01);
    rr_renderer_bezier_curve_to(renderer, 14.60, -14.46, 2.38, -26.19, -12.69,
                                -26.19);
    rr_renderer_fill(renderer);
    rr_renderer_set_fill(renderer, 0xffa48941);
    rr_renderer_begin_path(renderer);
    rr_renderer_move_to(renderer, -12.70, -38.74);
    rr_renderer_bezier_curve_to(renderer, 9.13, -38.74, 26.82, -21.39, 26.82,
                                0.02);
    rr_renderer_bezier_curve_to(renderer, 26.82, 10.30, 22.66, 20.16, 15.25,
                                27.43);
    rr_renderer_bezier_curve_to(renderer, 7.84, 34.69, -2.21, 38.78, -12.70,
                                38.78);
    rr_renderer_bezier_curve_to(renderer, -34.52, 38.78, -52.21, 21.42, -52.21,
                                0.02);
    rr_renderer_bezier_curve_to(renderer, -52.21, -21.39, -34.52, -38.74,
                                -12.70, -38.74);
    rr_renderer_fill(renderer);
    rr_renderer_set_fill(renderer, 0xff332a10);
    rr_renderer_begin_path(renderer);
    rr_renderer_move_to(renderer, 48.83, 81.23);
    rr_renderer_line_to(renderer, 7.77, 62.02);
    rr_renderer_line_to(renderer, 13.33, 46.72);
    rr_renderer_line_to(renderer, 57.14, 58.34);
    rr_renderer_fill(renderer);
    rr_renderer_set_fill(renderer, 0xff332a10);
    rr_renderer_begin_path(renderer);
    rr_renderer_move_to(renderer, 13.84, 47.00);
    rr_renderer_bezier_curve_to(renderer, 18.02, 48.52, 20.17, 53.14, 18.66,
                                57.32);
    rr_renderer_bezier_curve_to(renderer, 17.93, 59.32, 16.43, 60.96, 14.49,
                                61.86);
    rr_renderer_bezier_curve_to(renderer, 12.56, 62.76, 10.35, 62.86, 8.34,
                                62.13);
    rr_renderer_bezier_curve_to(renderer, 4.16, 60.61, 2.00, 55.99, 3.52,
                                51.82);
    rr_renderer_bezier_curve_to(renderer, 5.04, 47.64, 9.66, 45.48, 13.84,
                                47.00);
    rr_renderer_fill(renderer);
    rr_renderer_set_fill(renderer, 0xff332a10);
    rr_renderer_begin_path(renderer);
    rr_renderer_move_to(renderer, 57.78, 58.43);
    rr_renderer_bezier_curve_to(renderer, 64.10, 60.73, 67.36, 67.71, 65.07,
                                74.03);
    rr_renderer_bezier_curve_to(renderer, 63.96, 77.07, 61.70, 79.54, 58.77,
                                80.90);
    rr_renderer_bezier_curve_to(renderer, 55.85, 82.27, 52.50, 82.42, 49.46,
                                81.31);
    rr_renderer_bezier_curve_to(renderer, 43.14, 79.02, 39.88, 72.03, 42.17,
                                65.72);
    rr_renderer_bezier_curve_to(renderer, 44.47, 59.40, 51.46, 56.14, 57.78,
                                58.43);
    rr_renderer_fill(renderer);
    rr_renderer_set_fill(renderer, 0xff332a10);
    rr_renderer_begin_path(renderer);
    rr_renderer_move_to(renderer, 17.18, 49.62);
    rr_renderer_bezier_curve_to(renderer, 18.67, 53.81, 16.48, 58.41, 12.30,
                                59.90);
    rr_renderer_bezier_curve_to(renderer, 10.29, 60.61, 8.08, 60.50, 6.15,
                                59.58);
    rr_renderer_bezier_curve_to(renderer, 4.22, 58.67, 2.74, 57.02, 2.03,
                                55.01);
    rr_renderer_line_to(renderer, -9.44, 22.71);
    rr_renderer_bezier_curve_to(renderer, -10.93, 18.53, -8.74, 13.93, -4.56,
                                12.44);
    rr_renderer_bezier_curve_to(renderer, -0.37, 10.95, 4.22, 13.13, 5.71,
                                17.32);
    rr_renderer_fill(renderer);
    rr_renderer_set_fill(renderer, 0xff332a10);
    rr_renderer_begin_path(renderer);
    rr_renderer_move_to(renderer, 48.83, -81.23);
    rr_renderer_line_to(renderer, 7.78, -62.02);
    rr_renderer_line_to(renderer, 13.34, -46.72);
    rr_renderer_line_to(renderer, 57.14, -58.35);
    rr_renderer_fill(renderer);
    rr_renderer_set_fill(renderer, 0xff332a10);
    rr_renderer_begin_path(renderer);
    rr_renderer_move_to(renderer, 13.84, -47.00);
    rr_renderer_bezier_curve_to(renderer, 18.02, -48.52, 20.17, -53.14, 18.66,
                                -57.32);
    rr_renderer_bezier_curve_to(renderer, 17.93, -59.32, 16.43, -60.96, 14.50,
                                -61.86);
    rr_renderer_bezier_curve_to(renderer, 12.56, -62.76, 10.35, -62.86, 8.34,
                                -62.13);
    rr_renderer_bezier_curve_to(renderer, 4.16, -60.61, 2.00, -56.00, 3.52,
                                -51.82);
    rr_renderer_bezier_curve_to(renderer, 5.04, -47.64, 9.66, -45.48, 13.84,
                                -47.00);
    rr_renderer_fill(renderer);
    rr_renderer_set_fill(renderer, 0xff332a10);
    rr_renderer_begin_path(renderer);
    rr_renderer_move_to(renderer, 57.78, -58.43);
    rr_renderer_bezier_curve_to(renderer, 64.10, -60.73, 67.36, -67.71, 65.07,
                                -74.03);
    rr_renderer_bezier_curve_to(renderer, 63.96, -77.07, 61.70, -79.54, 58.78,
                                -80.90);
    rr_renderer_bezier_curve_to(renderer, 55.85, -82.27, 52.50, -82.42, 49.47,
                                -81.31);
    rr_renderer_bezier_curve_to(renderer, 43.14, -79.02, 39.88, -72.03, 42.18,
                                -65.72);
    rr_renderer_bezier_curve_to(renderer, 44.47, -59.40, 51.46, -56.14, 57.78,
                                -58.43);
    rr_renderer_fill(renderer);
    rr_renderer_set_fill(renderer, 0xff332a10);
    rr_renderer_begin_path(renderer);
    rr_renderer_move_to(renderer, 17.18, -49.62);
    rr_renderer_bezier_curve_to(renderer, 18.67, -53.81, 16.48, -58.41, 12.30,
                                -59.90);
    rr_renderer_bezier_curve_to(renderer, 10.29, -60.61, 8.08, -60.50, 6.15,
                                -59.58);
    rr_renderer_bezier_curve_to(renderer, 4.23, -58.67, 2.74, -57.02, 2.03,
                                -55.01);
    rr_renderer_line_to(renderer, -9.44, -22.71);
    rr_renderer_bezier_curve_to(renderer, -10.93, -18.53, -8.74, -13.93, -4.56,
                                -12.44);
    rr_renderer_bezier_curve_to(renderer, -0.37, -10.95, 4.23, -13.14, 5.71,
                                -17.32);
    rr_renderer_fill(renderer);
}

void rr_honeybee_thorax_draw(struct rr_renderer *renderer)
{
    rr_renderer_set_fill(renderer, 0xff5b4c1d);
    rr_renderer_begin_path(renderer);
    rr_renderer_move_to(renderer, -0.00, -62.81);
    rr_renderer_bezier_curve_to(renderer, 28.30, -62.81, 51.24, -34.69, 51.24,
                                -0.00);
    rr_renderer_bezier_curve_to(renderer, 51.24, 34.69, 28.30, 62.81, -0.00,
                                62.81);
    rr_renderer_bezier_curve_to(renderer, -28.30, 62.81, -51.24, 34.69, -51.24,
                                -0.00);
    rr_renderer_bezier_curve_to(renderer, -51.24, -34.69, -28.30, -62.81, -0.00,
                                -62.81);
    rr_renderer_fill(renderer);
    rr_renderer_set_fill(renderer, 0xff4a3e18);
    rr_renderer_begin_path(renderer);
    rr_renderer_move_to(renderer, -0.00, -71.27);
    rr_renderer_bezier_curve_to(renderer, 32.11, -71.27, 58.15, -39.36, 58.15,
                                -0.00);
    rr_renderer_bezier_curve_to(renderer, 58.15, 39.36, 32.11, 71.27, -0.00,
                                71.27);
    rr_renderer_bezier_curve_to(renderer, -32.11, 71.27, -58.15, 39.36, -58.15,
                                -0.00);
    rr_renderer_bezier_curve_to(renderer, -58.15, -39.36, -32.11, -71.27, -0.00,
                                -71.27);
    rr_renderer_move_to(renderer, -0.00, -53.89);
    rr_renderer_bezier_curve_to(renderer, -22.52, -53.89, -40.77, -29.76,
                                -40.77, -0.00);
    rr_renderer_bezier_curve_to(renderer, -40.77, 29.76, -22.52, 53.89, -0.00,
                                53.89);
    rr_renderer_bezier_curve_to(renderer, 22.52, 53.89, 40.77, 29.76, 40.77,
                                -0.00);
    rr_renderer_bezier_curve_to(renderer, 40.77, -29.76, 22.52, -53.89, -0.00,
                                -53.89);
    rr_renderer_fill(renderer);
}

void rr_honeybee_abdomen_draw(struct rr_renderer *renderer)
{
    rr_renderer_set_fill(renderer, 0xff332a10);
    rr_renderer_begin_path(renderer);
    rr_renderer_move_to(renderer, -38.69, 24.56);
    rr_renderer_line_to(renderer, -88.54, -7.39);
    rr_renderer_line_to(renderer, -38.69, -39.34);
    rr_renderer_fill(renderer);
    rr_renderer_set_fill(renderer, 0xff332a10);
    rr_renderer_begin_path(renderer);
    rr_renderer_move_to(renderer, -38.69, 39.35);
    rr_renderer_line_to(renderer, -88.54, 7.40);
    rr_renderer_line_to(renderer, -38.69, -24.56);
    rr_renderer_fill(renderer);
    rr_renderer_set_fill(renderer, 0xff332a10);
    rr_renderer_begin_path(renderer);
    rr_renderer_move_to(renderer, -82.55, -9.44);
    rr_renderer_bezier_curve_to(renderer, -77.34, -9.44, -73.12, -5.21, -73.12,
                                0.00);
    rr_renderer_bezier_curve_to(renderer, -73.12, 2.51, -74.11, 4.91, -75.88,
                                6.68);
    rr_renderer_bezier_curve_to(renderer, -77.65, 8.45, -80.05, 9.44, -82.55,
                                9.44);
    rr_renderer_bezier_curve_to(renderer, -87.77, 9.44, -91.99, 5.22, -91.99,
                                0.00);
    rr_renderer_bezier_curve_to(renderer, -91.99, -5.21, -87.77, -9.44, -82.55,
                                -9.44);
    rr_renderer_fill(renderer);
    rr_renderer_set_fill(renderer, 0xffa48941);
    rr_renderer_begin_path(renderer);
    rr_renderer_move_to(renderer, 11.55, -43.86);
    rr_renderer_bezier_curve_to(renderer, 45.44, -43.86, 72.92, -24.23, 72.92,
                                -0.01);
    rr_renderer_bezier_curve_to(renderer, 72.92, 11.62, 66.45, 22.78, 54.94,
                                31.00);
    rr_renderer_bezier_curve_to(renderer, 43.43, 39.23, 27.82, 43.85, 11.55,
                                43.85);
    rr_renderer_bezier_curve_to(renderer, -22.35, 43.85, -49.83, 24.21, -49.83,
                                -0.01);
    rr_renderer_bezier_curve_to(renderer, -49.83, -24.23, -22.35, -43.86, 11.55,
                                -43.86);
    rr_renderer_fill(renderer);
    rr_renderer_set_fill(renderer, 0xff332a10);
    rr_renderer_begin_path(renderer);
    rr_renderer_move_to(renderer, 13.20, 51.60);
    rr_renderer_bezier_curve_to(renderer, -8.73, 51.60, -26.50, 28.53, -26.50,
                                0.06);
    rr_renderer_bezier_curve_to(renderer, -26.50, -28.41, -8.73, -51.48, 13.20,
                                -51.48);
    rr_renderer_bezier_curve_to(renderer, 0.76, -39.27, -6.56, -20.19, -6.56,
                                0.06);
    rr_renderer_bezier_curve_to(renderer, -6.56, 20.31, 0.76, 39.39, 13.20,
                                51.60);
    rr_renderer_fill(renderer);
    rr_renderer_set_fill(renderer, 0xff332a10);
    rr_renderer_begin_path(renderer);
    rr_renderer_move_to(renderer, 0.98, 51.47);
    rr_renderer_bezier_curve_to(renderer, -19.50, 51.47, -36.11, 28.40, -36.11,
                                -0.07);
    rr_renderer_bezier_curve_to(renderer, -36.11, -28.54, -19.50, -51.61, 0.98,
                                -51.61);
    rr_renderer_bezier_curve_to(renderer, -11.83, -40.54, -19.62, -21.05,
                                -19.62, -0.07);
    rr_renderer_bezier_curve_to(renderer, -19.62, 20.91, -11.83, 40.39, 0.98,
                                51.47);
    rr_renderer_fill(renderer);
    rr_renderer_set_fill(renderer, 0xff332a10);
    rr_renderer_begin_path(renderer);
    rr_renderer_move_to(renderer, -1.68, -45.75);
    rr_renderer_line_to(renderer, -24.62, -3.52);
    rr_renderer_line_to(renderer, -4.83, 47.33);
    rr_renderer_line_to(renderer, -20.12, 46.04);
    rr_renderer_line_to(renderer, -32.55, -0.69);
    rr_renderer_line_to(renderer, -17.87, -48.77);
    rr_renderer_fill(renderer);
    rr_renderer_set_fill(renderer, 0xff8b7437);
    rr_renderer_begin_path(renderer);
    rr_renderer_move_to(renderer, 12.04, -59.73);
    rr_renderer_bezier_curve_to(renderer, 56.19, -59.73, 91.99, -32.99, 91.99,
                                -0.00);
    rr_renderer_bezier_curve_to(renderer, 91.99, 15.84, 83.57, 31.03, 68.57,
                                42.23);
    rr_renderer_bezier_curve_to(renderer, 53.58, 53.43, 33.24, 59.73, 12.04,
                                59.73);
    rr_renderer_bezier_curve_to(renderer, -32.12, 59.73, -67.92, 32.99, -67.92,
                                -0.00);
    rr_renderer_bezier_curve_to(renderer, -67.92, -32.99, -32.12, -59.73, 12.04,
                                -59.73);
    rr_renderer_move_to(renderer, 12.04, -40.35);
    rr_renderer_bezier_curve_to(renderer, -21.42, -40.35, -48.54, -22.28,
                                -48.54, -0.00);
    rr_renderer_bezier_curve_to(renderer, -48.54, 22.28, -21.42, 40.35, 12.04,
                                40.35);
    rr_renderer_bezier_curve_to(renderer, 45.49, 40.35, 72.61, 22.28, 72.61,
                                -0.00);
    rr_renderer_bezier_curve_to(renderer, 72.61, -22.28, 45.49, -40.35, 12.04,
                                -40.35);
    rr_renderer_fill(renderer);
}

void rr_honeybee_leg_draw(struct rr_renderer *renderer)
{
    rr_renderer_set_fill(renderer, 0xff332a10);
    rr_renderer_begin_path(renderer);
    rr_renderer_move_to(renderer, -66.33, -9.61);
    rr_renderer_bezier_curve_to(renderer, -71.64, -9.61, -75.94, -5.30, -75.95,
                                0.00);
    rr_renderer_bezier_curve_to(renderer, -75.96, 2.55, -74.95, 4.99, -73.15,
                                6.79);
    rr_renderer_bezier_curve_to(renderer, -71.35, 8.60, -68.91, 9.61, -66.36,
                                9.61);
    rr_renderer_line_to(renderer, 66.33, 9.61);
    rr_renderer_bezier_curve_to(renderer, 71.64, 9.61, 75.94, 5.31, 75.95,
                                0.00);
    rr_renderer_bezier_curve_to(renderer, 75.96, -5.30, 71.67, -9.61, 66.36,
                                -9.61);
    rr_renderer_fill(renderer);
}

void rr_honeybee_wing_draw(struct rr_renderer *renderer)
{
    rr_renderer_set_fill(renderer, 0x7f8b7437);
    rr_renderer_begin_path(renderer);
    rr_renderer_move_to(renderer, -96.00, 0.00);
    rr_renderer_bezier_curve_to(renderer, -96.00, -22.31, -53.02, -40.39, 0.00,
                                -40.39);
    rr_renderer_bezier_curve_to(renderer, 53.02, -40.39, 96.00, -22.31, 96.00,
                                0.00);
    rr_renderer_bezier_curve_to(renderer, 96.00, 22.31, 53.02, 40.39, 0.00,
                                40.39);
    rr_renderer_bezier_curve_to(renderer, -53.02, 40.39, -96.00, 22.31, -96.00,
                                0.00);
    rr_renderer_move_to(renderer, -83.62, 0.00);
    rr_renderer_bezier_curve_to(renderer, -83.62, 15.47, -46.18, 28.02, 0.00,
                                28.02);
    rr_renderer_bezier_curve_to(renderer, 46.18, 28.02, 83.62, 15.47, 83.62,
                                0.00);
    rr_renderer_bezier_curve_to(renderer, 83.62, -15.47, 46.18, -28.02, 0.00,
                                -28.02);
    rr_renderer_bezier_curve_to(renderer, -46.18, -28.02, -83.62, -15.47,
                                -83.62, 0.00);
    rr_renderer_fill(renderer);
    rr_renderer_set_fill(renderer, 0x7fa48941);
    rr_renderer_begin_path(renderer);
    rr_renderer_move_to(renderer, 83.64, 0.04);
    rr_renderer_bezier_curve_to(renderer, 83.64, -15.39, 46.19, -27.92, -0.00,
                                -27.96);
    rr_renderer_bezier_curve_to(renderer, -46.19, -27.99, -83.64, -15.51,
                                -83.64, -0.08);
    rr_renderer_bezier_curve_to(renderer, -83.64, 15.35, -46.19, 27.88, -0.00,
                                27.91);
    rr_renderer_bezier_curve_to(renderer, 46.19, 27.94, 83.64, 15.46, 83.64,
                                0.04);
    rr_renderer_fill(renderer);
}