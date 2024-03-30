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

void rr_ga_tile_1_draw(struct rr_renderer *renderer)
{
    rr_renderer_set_fill(renderer, 0xff2c773f);
    rr_renderer_begin_path(renderer);
    rr_renderer_move_to(renderer, -128.00, -128.00);
    rr_renderer_line_to(renderer, 128.00, -128.00);
    rr_renderer_line_to(renderer, 128.00, 128.00);
    rr_renderer_line_to(renderer, -128.00, 128.00);
    rr_renderer_fill(renderer);
    rr_renderer_clip(renderer);
    rr_renderer_set_fill(renderer, 0xff318647);
    rr_renderer_begin_path(renderer);
    rr_renderer_move_to(renderer, 89.44, -146.93);
    rr_renderer_bezier_curve_to(renderer, 72.24, -138.47, 60.74, -127.29, 49.87,
                                -109.08);
    rr_renderer_bezier_curve_to(renderer, 39.01, -90.87, 43.57, -56.18, 24.25,
                                -37.69);
    rr_renderer_bezier_curve_to(renderer, 4.92, -19.19, -42.70, -16.90, -66.07,
                                1.88);
    rr_renderer_bezier_curve_to(renderer, -89.44, 20.66, -98.76, 57.79, -115.96,
                                75.00);
    rr_renderer_bezier_curve_to(renderer, -133.16, 92.20, -163.84, 90.77,
                                -169.29, 105.10);
    rr_renderer_bezier_curve_to(renderer, -174.74, 119.44, -166.28, 154.56,
                                -148.65, 161.01);
    rr_renderer_bezier_curve_to(renderer, -131.01, 167.46, -85.28, 159.29,
                                -63.49, 143.81);
    rr_renderer_bezier_curve_to(renderer, -41.70, 128.33, -43.13, 88.47, -17.90,
                                68.11);
    rr_renderer_bezier_curve_to(renderer, 7.33, 47.76, 65.13, 45.32, 87.90,
                                21.67);
    rr_renderer_bezier_curve_to(renderer, 110.66, -1.99, 105.67, -53.74, 118.69,
                                -73.81);
    rr_renderer_bezier_curve_to(renderer, 131.70, -93.89, 160.26, -84.42,
                                166.00, -98.76);
    rr_renderer_bezier_curve_to(renderer, 171.73, -113.10, 165.85, -151.80,
                                153.09, -159.83);
    rr_renderer_bezier_curve_to(renderer, 140.33, -167.86, 106.64, -155.39,
                                89.44, -146.93);
    rr_renderer_fill(renderer);
    rr_renderer_set_fill(renderer, 0xff318647);
    rr_renderer_begin_path(renderer);
    rr_renderer_move_to(renderer, 89.44, -403.75);
    rr_renderer_bezier_curve_to(renderer, 72.24, -395.29, 60.74, -384.11, 49.87,
                                -365.91);
    rr_renderer_bezier_curve_to(renderer, 39.01, -347.70, 43.57, -313.01, 24.25,
                                -294.51);
    rr_renderer_bezier_curve_to(renderer, 4.92, -276.02, -42.70, -273.72,
                                -66.07, -254.94);
    rr_renderer_bezier_curve_to(renderer, -89.44, -236.16, -98.76, -199.03,
                                -115.96, -181.83);
    rr_renderer_bezier_curve_to(renderer, -133.16, -164.63, -165.28, -167.86,
                                -169.29, -151.72);
    rr_renderer_bezier_curve_to(renderer, -173.30, -135.59, -157.68, -91.46,
                                -140.04, -85.01);
    rr_renderer_bezier_curve_to(renderer, -122.41, -78.56, -83.85, -95.73,
                                -63.49, -113.02);
    rr_renderer_bezier_curve_to(renderer, -43.13, -130.30, -43.13, -168.35,
                                -17.90, -188.71);
    rr_renderer_bezier_curve_to(renderer, 7.33, -209.07, 65.13, -211.51, 87.90,
                                -235.16);
    rr_renderer_bezier_curve_to(renderer, 110.66, -258.82, 105.67, -310.57,
                                118.69, -330.64);
    rr_renderer_bezier_curve_to(renderer, 131.70, -350.71, 160.26, -341.25,
                                166.00, -355.59);
    rr_renderer_bezier_curve_to(renderer, 171.73, -369.92, 165.85, -408.63,
                                153.09, -416.66);
    rr_renderer_bezier_curve_to(renderer, 140.33, -424.69, 106.64, -412.21,
                                89.44, -403.75);
    rr_renderer_fill(renderer);
    rr_renderer_set_fill(renderer, 0xff318647);
    rr_renderer_begin_path(renderer);
    rr_renderer_move_to(renderer, 101.50, 94.39);
    rr_renderer_bezier_curve_to(renderer, 84.29, 102.84, 72.80, 114.03, 61.93,
                                132.23);
    rr_renderer_bezier_curve_to(renderer, 51.06, 150.44, 55.63, 185.13, 36.30,
                                203.63);
    rr_renderer_bezier_curve_to(renderer, 16.98, 222.12, -30.64, 224.41, -54.01,
                                243.20);
    rr_renderer_bezier_curve_to(renderer, -77.38, 261.98, -86.70, 299.11,
                                -103.90, 316.31);
    rr_renderer_bezier_curve_to(renderer, -121.11, 333.51, -153.22, 330.28,
                                -157.23, 346.41);
    rr_renderer_bezier_curve_to(renderer, -161.25, 362.55, -145.62, 406.68,
                                -127.99, 413.13);
    rr_renderer_bezier_curve_to(renderer, -110.35, 419.58, -71.79, 402.41,
                                -51.43, 385.12);
    rr_renderer_bezier_curve_to(renderer, -31.07, 367.84, -31.07, 329.79, -5.84,
                                309.43);
    rr_renderer_bezier_curve_to(renderer, 19.39, 289.07, 77.19, 286.63, 99.96,
                                262.98);
    rr_renderer_bezier_curve_to(renderer, 122.72, 239.32, 117.73, 187.57,
                                130.74, 167.50);
    rr_renderer_bezier_curve_to(renderer, 143.76, 147.43, 172.32, 156.89,
                                178.05, 142.55);
    rr_renderer_bezier_curve_to(renderer, 183.79, 128.22, 177.91, 89.51, 165.15,
                                81.48);
    rr_renderer_bezier_curve_to(renderer, 152.39, 73.45, 118.70, 85.93, 101.50,
                                94.39);
    rr_renderer_fill(renderer);
    rr_renderer_set_fill(renderer, 0xff2f8043);
    rr_renderer_begin_path(renderer);
    rr_renderer_move_to(renderer, 35.15, 90.69);
    rr_renderer_bezier_curve_to(renderer, 29.75, 77.74, 35.85, 62.87, 48.79,
                                57.48);
    rr_renderer_bezier_curve_to(renderer, 55.00, 54.89, 61.98, 54.87, 68.21,
                                57.44);
    rr_renderer_bezier_curve_to(renderer, 74.44, 60.01, 79.39, 64.94, 81.98,
                                71.16);
    rr_renderer_bezier_curve_to(renderer, 87.39, 84.11, 81.28, 98.98, 68.35,
                                104.37);
    rr_renderer_bezier_curve_to(renderer, 55.41, 109.77, 40.55, 103.64, 35.15,
                                90.69);
    rr_renderer_fill(renderer);
    rr_renderer_set_fill(renderer, 0xff2f8043);
    rr_renderer_begin_path(renderer);
    rr_renderer_move_to(renderer, -98.67, 77.59);
    rr_renderer_bezier_curve_to(renderer, -104.88, 62.71, -97.87, 45.63, -83.00,
                                39.44);
    rr_renderer_bezier_curve_to(renderer, -75.87, 36.46, -67.84, 36.45, -60.68,
                                39.40);
    rr_renderer_bezier_curve_to(renderer, -53.52, 42.35, -47.83, 48.02, -44.85,
                                55.17);
    rr_renderer_bezier_curve_to(renderer, -38.64, 70.05, -45.65, 87.13, -60.52,
                                93.33);
    rr_renderer_bezier_curve_to(renderer, -75.38, 99.52, -92.46, 92.47, -98.67,
                                77.59);
    rr_renderer_fill(renderer);
    rr_renderer_set_fill(renderer, 0xff2f8043);
    rr_renderer_begin_path(renderer);
    rr_renderer_move_to(renderer, 17.30, -80.17);
    rr_renderer_bezier_curve_to(renderer, 11.09, -95.05, 18.11, -112.14, 32.97,
                                -118.33);
    rr_renderer_bezier_curve_to(renderer, 40.11, -121.30, 48.14, -121.32, 55.30,
                                -118.37);
    rr_renderer_bezier_curve_to(renderer, 62.45, -115.42, 68.15, -109.74, 71.13,
                                -102.60);
    rr_renderer_bezier_curve_to(renderer, 77.34, -87.72, 70.33, -70.63, 55.46,
                                -64.44);
    rr_renderer_bezier_curve_to(renderer, 40.60, -58.25, 23.51, -65.29, 17.30,
                                -80.17);
    rr_renderer_fill(renderer);
    rr_renderer_set_fill(renderer, 0xff2f8043);
    rr_renderer_begin_path(renderer);
    rr_renderer_move_to(renderer, -104.88, -5.28);
    rr_renderer_bezier_curve_to(renderer, -111.09, -20.16, -104.07, -37.25,
                                -89.21, -43.44);
    rr_renderer_bezier_curve_to(renderer, -82.07, -46.41, -74.04, -46.43,
                                -66.89, -43.47);
    rr_renderer_bezier_curve_to(renderer, -59.73, -40.52, -54.03, -34.85,
                                -51.05, -27.71);
    rr_renderer_bezier_curve_to(renderer, -44.84, -12.82, -51.86, 4.26, -66.72,
                                10.45);
    rr_renderer_bezier_curve_to(renderer, -81.59, 16.64, -98.67, 9.60, -104.88,
                                -5.28);
    rr_renderer_fill(renderer);
    rr_renderer_set_fill(renderer, 0xff2f8043);
    rr_renderer_begin_path(renderer);
    rr_renderer_move_to(renderer, -60.25, 98.38);
    rr_renderer_bezier_curve_to(renderer, -65.58, 85.61, -59.56, 70.94, -46.80,
                                65.63);
    rr_renderer_bezier_curve_to(renderer, -40.67, 63.07, -33.78, 63.06, -27.64,
                                65.60);
    rr_renderer_bezier_curve_to(renderer, -21.50, 68.13, -16.61, 73.00, -14.05,
                                79.14);
    rr_renderer_bezier_curve_to(renderer, -8.71, 91.91, -14.74, 106.58, -27.49,
                                111.89);
    rr_renderer_bezier_curve_to(renderer, -40.25, 117.21, -54.92, 111.16,
                                -60.25, 98.38);
    rr_renderer_fill(renderer);
    rr_renderer_set_fill(renderer, 0xff2f8043);
    rr_renderer_begin_path(renderer);
    rr_renderer_move_to(renderer, 46.17, -4.70);
    rr_renderer_bezier_curve_to(renderer, 42.06, -14.56, 46.71, -25.87, 56.55,
                                -29.96);
    rr_renderer_bezier_curve_to(renderer, 61.28, -31.93, 66.60, -31.94, 71.34,
                                -29.98);
    rr_renderer_bezier_curve_to(renderer, 76.08, -28.03, 79.85, -24.27, 81.83,
                                -19.54);
    rr_renderer_bezier_curve_to(renderer, 85.94, -9.68, 81.30, 1.62, 71.45,
                                5.72);
    rr_renderer_bezier_curve_to(renderer, 61.60, 9.82, 50.29, 5.15, 46.17,
                                -4.70);
    rr_renderer_fill(renderer);
    rr_renderer_set_fill(renderer, 0xff2f8043);
    rr_renderer_begin_path(renderer);
    rr_renderer_move_to(renderer, -47.49, 29.87);
    rr_renderer_bezier_curve_to(renderer, -51.61, 20.02, -46.96, 8.71, -37.12,
                                4.61);
    rr_renderer_bezier_curve_to(renderer, -32.39, 2.64, -27.07, 2.64, -22.33,
                                4.59);
    rr_renderer_bezier_curve_to(renderer, -17.59, 6.55, -13.82, 10.30, -11.84,
                                15.03);
    rr_renderer_bezier_curve_to(renderer, -7.73, 24.89, -12.37, 36.20, -22.22,
                                40.29);
    rr_renderer_bezier_curve_to(renderer, -32.06, 44.39, -43.38, 39.72, -47.49,
                                29.87);
    rr_renderer_fill(renderer);
    rr_renderer_set_fill(renderer, 0xff2f8043);
    rr_renderer_begin_path(renderer);
    rr_renderer_move_to(renderer, -39.77, -66.27);
    rr_renderer_bezier_curve_to(renderer, -43.89, -76.12, -39.24, -87.43,
                                -29.39, -91.53);
    rr_renderer_bezier_curve_to(renderer, -24.67, -93.49, -19.35, -93.50,
                                -14.61, -91.54);
    rr_renderer_bezier_curve_to(renderer, -9.87, -89.59, -6.09, -85.83, -4.12,
                                -81.10);
    rr_renderer_bezier_curve_to(renderer, -0.01, -71.25, -4.65, -59.94, -14.50,
                                -55.84);
    rr_renderer_bezier_curve_to(renderer, -24.34, -51.74, -35.66, -56.41,
                                -39.77, -66.27);
    rr_renderer_fill(renderer);
    rr_renderer_set_fill(renderer, 0xff2f8043);
    rr_renderer_begin_path(renderer);
    rr_renderer_move_to(renderer, -83.62, -41.45);
    rr_renderer_bezier_curve_to(renderer, -86.36, -48.00, -83.27, -55.53,
                                -76.72, -58.27);
    rr_renderer_bezier_curve_to(renderer, -73.58, -59.58, -70.04, -59.58,
                                -66.88, -58.28);
    rr_renderer_bezier_curve_to(renderer, -63.73, -56.98, -61.22, -54.49,
                                -59.90, -51.34);
    rr_renderer_bezier_curve_to(renderer, -57.16, -44.78, -60.25, -37.25,
                                -66.80, -34.52);
    rr_renderer_bezier_curve_to(renderer, -73.35, -31.79, -80.88, -34.89,
                                -83.62, -41.45);
    rr_renderer_fill(renderer);
    rr_renderer_set_fill(renderer, 0xff2f8043);
    rr_renderer_begin_path(renderer);
    rr_renderer_move_to(renderer, 68.77, 99.36);
    rr_renderer_bezier_curve_to(renderer, 66.03, 92.80, 69.11, 85.27, 75.66,
                                82.54);
    rr_renderer_bezier_curve_to(renderer, 78.81, 81.23, 82.35, 81.22, 85.50,
                                82.52);
    rr_renderer_bezier_curve_to(renderer, 88.65, 83.82, 91.17, 86.32, 92.48,
                                89.47);
    rr_renderer_bezier_curve_to(renderer, 95.22, 96.03, 92.13, 103.56, 85.58,
                                106.29);
    rr_renderer_bezier_curve_to(renderer, 79.03, 109.02, 71.50, 105.92, 68.77,
                                99.36);
    rr_renderer_fill(renderer);
    rr_renderer_set_fill(renderer, 0xff2f8043);
    rr_renderer_begin_path(renderer);
    rr_renderer_move_to(renderer, -53.38, -89.43);
    rr_renderer_bezier_curve_to(renderer, -56.12, -95.99, -53.03, -103.52,
                                -46.48, -106.25);
    rr_renderer_bezier_curve_to(renderer, -43.34, -107.56, -39.80, -107.57,
                                -36.64, -106.27);
    rr_renderer_bezier_curve_to(renderer, -33.49, -104.97, -30.98, -102.47,
                                -29.66, -99.32);
    rr_renderer_bezier_curve_to(renderer, -26.92, -92.76, -30.01, -85.23,
                                -36.56, -82.50);
    rr_renderer_bezier_curve_to(renderer, -43.11, -79.77, -50.64, -82.87,
                                -53.38, -89.43);
    rr_renderer_fill(renderer);
    rr_renderer_set_fill(renderer, 0xff2f8043);
    rr_renderer_begin_path(renderer);
    rr_renderer_move_to(renderer, -22.62, 9.79);
    rr_renderer_bezier_curve_to(renderer, -25.36, 3.23, -22.27, -4.30, -15.72,
                                -7.03);
    rr_renderer_bezier_curve_to(renderer, -12.58, -8.34, -9.04, -8.35, -5.88,
                                -7.05);
    rr_renderer_bezier_curve_to(renderer, -2.73, -5.75, -0.22, -3.25, 1.10,
                                -0.10);
    rr_renderer_bezier_curve_to(renderer, 3.84, 6.46, 0.75, 13.99, -5.80,
                                16.72);
    rr_renderer_bezier_curve_to(renderer, -12.35, 19.45, -19.88, 16.35, -22.62,
                                9.79);
    rr_renderer_fill(renderer);
    rr_renderer_set_fill(renderer, 0xff2f8043);
    rr_renderer_begin_path(renderer);
    rr_renderer_move_to(renderer, 74.81, -55.79);
    rr_renderer_bezier_curve_to(renderer, 72.07, -62.35, 75.16, -69.88, 81.71,
                                -72.61);
    rr_renderer_bezier_curve_to(renderer, 84.86, -73.92, 88.39, -73.93, 91.55,
                                -72.63);
    rr_renderer_bezier_curve_to(renderer, 94.70, -71.33, 97.21, -68.83, 98.53,
                                -65.68);
    rr_renderer_bezier_curve_to(renderer, 101.27, -59.13, 98.18, -51.60, 91.63,
                                -48.86);
    rr_renderer_bezier_curve_to(renderer, 85.08, -46.13, 77.55, -49.24, 74.81,
                                -55.79);
    rr_renderer_fill(renderer);
}

void rr_ga_tile_2_draw(struct rr_renderer *renderer)
{
    rr_renderer_set_fill(renderer, 0xff2c773f);
    rr_renderer_begin_path(renderer);
    rr_renderer_move_to(renderer, -128.00, -128.00);
    rr_renderer_line_to(renderer, 128.00, -128.00);
    rr_renderer_line_to(renderer, 128.00, 128.00);
    rr_renderer_line_to(renderer, -128.00, 128.00);
    rr_renderer_fill(renderer);
    rr_renderer_clip(renderer);
    rr_renderer_set_fill(renderer, 0xff318647);
    rr_renderer_begin_path(renderer);
    rr_renderer_move_to(renderer, 89.44, -146.93);
    rr_renderer_bezier_curve_to(renderer, 72.24, -138.47, 60.74, -127.29, 49.87,
                                -109.08);
    rr_renderer_bezier_curve_to(renderer, 39.01, -90.87, 43.57, -56.18, 24.25,
                                -37.69);
    rr_renderer_bezier_curve_to(renderer, 4.92, -19.19, -42.70, -16.90, -66.07,
                                1.88);
    rr_renderer_bezier_curve_to(renderer, -89.44, 20.66, -98.76, 57.79, -115.96,
                                75.00);
    rr_renderer_bezier_curve_to(renderer, -133.16, 92.20, -163.84, 90.77,
                                -169.29, 105.10);
    rr_renderer_bezier_curve_to(renderer, -174.74, 119.44, -166.28, 154.56,
                                -148.65, 161.01);
    rr_renderer_bezier_curve_to(renderer, -131.01, 167.46, -85.28, 159.29,
                                -63.49, 143.81);
    rr_renderer_bezier_curve_to(renderer, -41.70, 128.33, -43.13, 88.47, -17.90,
                                68.11);
    rr_renderer_bezier_curve_to(renderer, 7.33, 47.76, 65.13, 45.32, 87.90,
                                21.67);
    rr_renderer_bezier_curve_to(renderer, 110.66, -1.99, 105.67, -53.74, 118.69,
                                -73.81);
    rr_renderer_bezier_curve_to(renderer, 131.70, -93.89, 160.26, -84.42,
                                166.00, -98.76);
    rr_renderer_bezier_curve_to(renderer, 171.73, -113.10, 165.85, -151.80,
                                153.09, -159.83);
    rr_renderer_bezier_curve_to(renderer, 140.33, -167.86, 106.64, -155.39,
                                89.44, -146.93);
    rr_renderer_fill(renderer);
    rr_renderer_set_fill(renderer, 0xff318647);
    rr_renderer_begin_path(renderer);
    rr_renderer_move_to(renderer, 89.44, -403.75);
    rr_renderer_bezier_curve_to(renderer, 72.24, -395.29, 60.74, -384.11, 49.87,
                                -365.91);
    rr_renderer_bezier_curve_to(renderer, 39.01, -347.70, 43.57, -313.01, 24.25,
                                -294.51);
    rr_renderer_bezier_curve_to(renderer, 4.92, -276.02, -42.70, -273.72,
                                -66.07, -254.94);
    rr_renderer_bezier_curve_to(renderer, -89.44, -236.16, -98.76, -199.03,
                                -115.96, -181.83);
    rr_renderer_bezier_curve_to(renderer, -133.16, -164.63, -165.28, -167.86,
                                -169.29, -151.72);
    rr_renderer_bezier_curve_to(renderer, -173.30, -135.59, -157.68, -91.46,
                                -140.04, -85.01);
    rr_renderer_bezier_curve_to(renderer, -122.41, -78.56, -83.85, -95.73,
                                -63.49, -113.02);
    rr_renderer_bezier_curve_to(renderer, -43.13, -130.30, -43.13, -168.35,
                                -17.90, -188.71);
    rr_renderer_bezier_curve_to(renderer, 7.33, -209.07, 65.13, -211.51, 87.90,
                                -235.16);
    rr_renderer_bezier_curve_to(renderer, 110.66, -258.82, 105.67, -310.57,
                                118.69, -330.64);
    rr_renderer_bezier_curve_to(renderer, 131.70, -350.71, 160.26, -341.25,
                                166.00, -355.59);
    rr_renderer_bezier_curve_to(renderer, 171.73, -369.92, 165.85, -408.63,
                                153.09, -416.66);
    rr_renderer_bezier_curve_to(renderer, 140.33, -424.69, 106.64, -412.21,
                                89.44, -403.75);
    rr_renderer_fill(renderer);
    rr_renderer_set_fill(renderer, 0xff318647);
    rr_renderer_begin_path(renderer);
    rr_renderer_move_to(renderer, 101.50, 94.39);
    rr_renderer_bezier_curve_to(renderer, 84.29, 102.84, 72.80, 114.03, 61.93,
                                132.23);
    rr_renderer_bezier_curve_to(renderer, 51.06, 150.44, 55.63, 185.13, 36.30,
                                203.63);
    rr_renderer_bezier_curve_to(renderer, 16.98, 222.12, -30.64, 224.41, -54.01,
                                243.20);
    rr_renderer_bezier_curve_to(renderer, -77.38, 261.98, -86.70, 299.11,
                                -103.90, 316.31);
    rr_renderer_bezier_curve_to(renderer, -121.11, 333.51, -153.22, 330.28,
                                -157.23, 346.41);
    rr_renderer_bezier_curve_to(renderer, -161.25, 362.55, -145.62, 406.68,
                                -127.99, 413.13);
    rr_renderer_bezier_curve_to(renderer, -110.35, 419.58, -71.79, 402.41,
                                -51.43, 385.12);
    rr_renderer_bezier_curve_to(renderer, -31.07, 367.84, -31.07, 329.79, -5.84,
                                309.43);
    rr_renderer_bezier_curve_to(renderer, 19.39, 289.07, 77.19, 286.63, 99.96,
                                262.98);
    rr_renderer_bezier_curve_to(renderer, 122.72, 239.32, 117.73, 187.57,
                                130.74, 167.50);
    rr_renderer_bezier_curve_to(renderer, 143.76, 147.43, 172.32, 156.89,
                                178.05, 142.55);
    rr_renderer_bezier_curve_to(renderer, 183.79, 128.22, 177.91, 89.51, 165.15,
                                81.48);
    rr_renderer_bezier_curve_to(renderer, 152.39, 73.45, 118.70, 85.93, 101.50,
                                94.39);
    rr_renderer_fill(renderer);
    rr_renderer_set_fill(renderer, 0xff2f8043);
    rr_renderer_begin_path(renderer);
    rr_renderer_move_to(renderer, -85.07, -91.77);
    rr_renderer_bezier_curve_to(renderer, -90.47, -104.72, -84.36, -119.59,
                                -71.43, -124.98);
    rr_renderer_bezier_curve_to(renderer, -65.22, -127.57, -58.23, -127.58,
                                -52.01, -125.02);
    rr_renderer_bezier_curve_to(renderer, -45.78, -122.45, -40.83, -117.51,
                                -38.23, -111.30);
    rr_renderer_bezier_curve_to(renderer, -32.83, -98.34, -38.94, -83.48,
                                -51.87, -78.08);
    rr_renderer_bezier_curve_to(renderer, -64.80, -72.69, -79.67, -78.82,
                                -85.07, -91.77);
    rr_renderer_fill(renderer);
    rr_renderer_set_fill(renderer, 0xff2f8043);
    rr_renderer_begin_path(renderer);
    rr_renderer_move_to(renderer, 20.35, 94.41);
    rr_renderer_bezier_curve_to(renderer, 14.14, 79.53, 21.16, 62.45, 36.02,
                                56.26);
    rr_renderer_bezier_curve_to(renderer, 43.16, 53.28, 51.19, 53.27, 58.34,
                                56.22);
    rr_renderer_bezier_curve_to(renderer, 65.50, 59.17, 71.19, 64.84, 74.18,
                                71.99);
    rr_renderer_bezier_curve_to(renderer, 80.39, 86.87, 73.37, 103.95, 58.51,
                                110.15);
    rr_renderer_bezier_curve_to(renderer, 43.64, 116.34, 26.56, 109.30, 20.35,
                                94.41);
    rr_renderer_fill(renderer);
    rr_renderer_set_fill(renderer, 0xff2f8043);
    rr_renderer_begin_path(renderer);
    rr_renderer_move_to(renderer, 5.23, -47.97);
    rr_renderer_bezier_curve_to(renderer, -0.98, -62.85, 6.03, -79.93, 20.90,
                                -86.12);
    rr_renderer_bezier_curve_to(renderer, 28.03, -89.10, 36.07, -89.11, 43.22,
                                -86.16);
    rr_renderer_bezier_curve_to(renderer, 50.38, -83.21, 56.07, -77.54, 59.05,
                                -70.39);
    rr_renderer_bezier_curve_to(renderer, 65.26, -55.51, 58.25, -38.43, 43.39,
                                -32.23);
    rr_renderer_bezier_curve_to(renderer, 28.52, -26.04, 11.44, -33.09, 5.23,
                                -47.97);
    rr_renderer_fill(renderer);
    rr_renderer_set_fill(renderer, 0xff2f8043);
    rr_renderer_begin_path(renderer);
    rr_renderer_move_to(renderer, -66.36, 22.34);
    rr_renderer_bezier_curve_to(renderer, -72.57, 7.46, -65.55, -9.62, -50.69,
                                -15.81);
    rr_renderer_bezier_curve_to(renderer, -43.55, -18.79, -35.52, -18.80,
                                -28.36, -15.85);
    rr_renderer_bezier_curve_to(renderer, -21.21, -12.90, -15.51, -7.23, -12.53,
                                -0.08);
    rr_renderer_bezier_curve_to(renderer, -6.32, 14.80, -13.34, 31.88, -28.20,
                                38.08);
    rr_renderer_bezier_curve_to(renderer, -43.06, 44.27, -60.15, 37.23, -66.36,
                                22.34);
    rr_renderer_fill(renderer);
    rr_renderer_set_fill(renderer, 0xff2f8043);
    rr_renderer_begin_path(renderer);
    rr_renderer_move_to(renderer, -73.61, 100.49);
    rr_renderer_bezier_curve_to(renderer, -78.94, 87.72, -72.92, 73.05, -60.16,
                                67.74);
    rr_renderer_bezier_curve_to(renderer, -54.03, 65.18, -47.14, 65.17, -41.00,
                                67.71);
    rr_renderer_bezier_curve_to(renderer, -34.85, 70.24, -29.96, 75.11, -27.40,
                                81.25);
    rr_renderer_bezier_curve_to(renderer, -22.07, 94.02, -28.09, 108.69, -40.85,
                                114.00);
    rr_renderer_bezier_curve_to(renderer, -53.61, 119.32, -68.28, 113.27,
                                -73.61, 100.49);
    rr_renderer_fill(renderer);
    rr_renderer_set_fill(renderer, 0xff2f8043);
    rr_renderer_begin_path(renderer);
    rr_renderer_move_to(renderer, 65.31, 73.96);
    rr_renderer_bezier_curve_to(renderer, 61.20, 64.11, 65.85, 52.80, 75.69,
                                48.70);
    rr_renderer_bezier_curve_to(renderer, 80.42, 46.74, 85.74, 46.73, 90.48,
                                48.68);
    rr_renderer_bezier_curve_to(renderer, 95.22, 50.64, 98.99, 54.40, 100.97,
                                59.13);
    rr_renderer_bezier_curve_to(renderer, 105.08, 68.98, 100.43, 80.29, 90.59,
                                84.39);
    rr_renderer_bezier_curve_to(renderer, 80.74, 88.48, 69.43, 83.82, 65.31,
                                73.96);
    rr_renderer_fill(renderer);
    rr_renderer_set_fill(renderer, 0xff2f8043);
    rr_renderer_begin_path(renderer);
    rr_renderer_move_to(renderer, -16.21, -44.88);
    rr_renderer_bezier_curve_to(renderer, -20.32, -54.73, -15.68, -66.04, -5.83,
                                -70.14);
    rr_renderer_bezier_curve_to(renderer, -1.10, -72.11, 4.22, -72.11, 8.96,
                                -70.16);
    rr_renderer_bezier_curve_to(renderer, 13.70, -68.20, 17.47, -64.45, 19.44,
                                -59.71);
    rr_renderer_bezier_curve_to(renderer, 23.56, -49.86, 18.91, -38.55, 9.07,
                                -34.45);
    rr_renderer_bezier_curve_to(renderer, -0.78, -30.36, -12.10, -35.03, -16.21,
                                -44.88);
    rr_renderer_fill(renderer);
    rr_renderer_set_fill(renderer, 0xff2f8043);
    rr_renderer_begin_path(renderer);
    rr_renderer_move_to(renderer, -104.60, -26.02);
    rr_renderer_bezier_curve_to(renderer, -108.72, -35.88, -104.07, -47.19,
                                -94.23, -51.28);
    rr_renderer_bezier_curve_to(renderer, -89.50, -53.25, -84.18, -53.26,
                                -79.44, -51.30);
    rr_renderer_bezier_curve_to(renderer, -74.70, -49.35, -70.93, -45.59,
                                -68.95, -40.86);
    rr_renderer_bezier_curve_to(renderer, -64.84, -31.00, -69.48, -19.70,
                                -79.33, -15.60);
    rr_renderer_bezier_curve_to(renderer, -89.17, -11.50, -100.49, -16.17,
                                -104.60, -26.02);
    rr_renderer_fill(renderer);
    rr_renderer_set_fill(renderer, 0xff2f8043);
    rr_renderer_begin_path(renderer);
    rr_renderer_move_to(renderer, -107.09, -7.81);
    rr_renderer_bezier_curve_to(renderer, -109.83, -14.37, -106.74, -21.90,
                                -100.19, -24.63);
    rr_renderer_bezier_curve_to(renderer, -97.05, -25.94, -93.51, -25.95,
                                -90.36, -24.65);
    rr_renderer_bezier_curve_to(renderer, -87.20, -23.35, -84.69, -20.85,
                                -83.37, -17.70);
    rr_renderer_bezier_curve_to(renderer, -80.64, -11.14, -83.72, -3.61, -90.27,
                                -0.88);
    rr_renderer_bezier_curve_to(renderer, -96.82, 1.85, -104.35, -1.25, -107.09,
                                -7.81);
    rr_renderer_fill(renderer);
    rr_renderer_set_fill(renderer, 0xff2f8043);
    rr_renderer_begin_path(renderer);
    rr_renderer_move_to(renderer, -62.36, -68.51);
    rr_renderer_bezier_curve_to(renderer, -65.10, -75.07, -62.01, -82.60,
                                -55.46, -85.33);
    rr_renderer_bezier_curve_to(renderer, -52.31, -86.64, -48.77, -86.65,
                                -45.62, -85.35);
    rr_renderer_bezier_curve_to(renderer, -42.47, -84.05, -39.95, -81.55,
                                -38.64, -78.40);
    rr_renderer_bezier_curve_to(renderer, -35.90, -71.85, -38.99, -64.31,
                                -45.54, -61.58);
    rr_renderer_bezier_curve_to(renderer, -52.09, -58.85, -59.62, -61.96,
                                -62.36, -68.51);
    rr_renderer_fill(renderer);
    rr_renderer_set_fill(renderer, 0xff2f8043);
    rr_renderer_begin_path(renderer);
    rr_renderer_move_to(renderer, -10.24, -106.25);
    rr_renderer_bezier_curve_to(renderer, -12.98, -112.81, -9.89, -120.34,
                                -3.34, -123.07);
    rr_renderer_bezier_curve_to(renderer, -0.20, -124.38, 3.34, -124.39, 6.50,
                                -123.09);
    rr_renderer_bezier_curve_to(renderer, 9.65, -121.79, 12.16, -119.29, 13.48,
                                -116.14);
    rr_renderer_bezier_curve_to(renderer, 16.22, -109.58, 13.13, -102.05, 6.58,
                                -99.32);
    rr_renderer_bezier_curve_to(renderer, 0.03, -96.59, -7.50, -99.69, -10.24,
                                -106.25);
    rr_renderer_fill(renderer);
    rr_renderer_set_fill(renderer, 0xff2f8043);
    rr_renderer_begin_path(renderer);
    rr_renderer_move_to(renderer, 8.21, 100.65);
    rr_renderer_bezier_curve_to(renderer, 5.47, 94.09, 8.56, 86.56, 15.11,
                                83.83);
    rr_renderer_bezier_curve_to(renderer, 18.25, 82.52, 21.79, 82.51, 24.94,
                                83.81);
    rr_renderer_bezier_curve_to(renderer, 28.10, 85.11, 30.61, 87.61, 31.92,
                                90.76);
    rr_renderer_bezier_curve_to(renderer, 34.66, 97.32, 31.58, 104.85, 25.03,
                                107.58);
    rr_renderer_bezier_curve_to(renderer, 18.48, 110.31, 10.95, 107.21, 8.21,
                                100.65);
    rr_renderer_fill(renderer);
    rr_renderer_set_fill(renderer, 0xff2f8043);
    rr_renderer_begin_path(renderer);
    rr_renderer_move_to(renderer, 90.38, -7.81);
    rr_renderer_bezier_curve_to(renderer, 87.64, -14.37, 90.73, -21.90, 97.28,
                                -24.63);
    rr_renderer_bezier_curve_to(renderer, 100.42, -25.94, 103.96, -25.95,
                                107.12, -24.65);
    rr_renderer_bezier_curve_to(renderer, 110.27, -23.35, 112.78, -20.85,
                                114.10, -17.70);
    rr_renderer_bezier_curve_to(renderer, 116.84, -11.14, 113.75, -3.61, 107.20,
                                -0.88);
    rr_renderer_bezier_curve_to(renderer, 100.65, 1.85, 93.12, -1.25, 90.38,
                                -7.81);
    rr_renderer_fill(renderer);
}
void rr_ga_tile_3_draw(struct rr_renderer *renderer)
{
    rr_renderer_set_fill(renderer, 0xff2c773f);
    rr_renderer_begin_path(renderer);
    rr_renderer_move_to(renderer, -128.00, -128.00);
    rr_renderer_line_to(renderer, 128.00, -128.00);
    rr_renderer_line_to(renderer, 128.00, 128.00);
    rr_renderer_line_to(renderer, -128.00, 128.00);
    rr_renderer_fill(renderer);
    rr_renderer_clip(renderer);
    rr_renderer_set_fill(renderer, 0xff318647);
    rr_renderer_begin_path(renderer);
    rr_renderer_move_to(renderer, 89.44, -146.93);
    rr_renderer_bezier_curve_to(renderer, 72.24, -138.47, 60.74, -127.29, 49.87,
                                -109.08);
    rr_renderer_bezier_curve_to(renderer, 39.01, -90.87, 43.57, -56.18, 24.25,
                                -37.69);
    rr_renderer_bezier_curve_to(renderer, 4.92, -19.19, -42.70, -16.90, -66.07,
                                1.88);
    rr_renderer_bezier_curve_to(renderer, -89.44, 20.66, -98.76, 57.79, -115.96,
                                75.00);
    rr_renderer_bezier_curve_to(renderer, -133.16, 92.20, -163.84, 90.77,
                                -169.29, 105.10);
    rr_renderer_bezier_curve_to(renderer, -174.74, 119.44, -166.28, 154.56,
                                -148.65, 161.01);
    rr_renderer_bezier_curve_to(renderer, -131.01, 167.46, -85.28, 159.29,
                                -63.49, 143.81);
    rr_renderer_bezier_curve_to(renderer, -41.70, 128.33, -43.13, 88.47, -17.90,
                                68.11);
    rr_renderer_bezier_curve_to(renderer, 7.33, 47.76, 65.13, 45.32, 87.90,
                                21.67);
    rr_renderer_bezier_curve_to(renderer, 110.66, -1.99, 105.67, -53.74, 118.69,
                                -73.81);
    rr_renderer_bezier_curve_to(renderer, 131.70, -93.89, 160.26, -84.42,
                                166.00, -98.76);
    rr_renderer_bezier_curve_to(renderer, 171.73, -113.10, 165.85, -151.80,
                                153.09, -159.83);
    rr_renderer_bezier_curve_to(renderer, 140.33, -167.86, 106.64, -155.39,
                                89.44, -146.93);
    rr_renderer_fill(renderer);
    rr_renderer_set_fill(renderer, 0xff318647);
    rr_renderer_begin_path(renderer);
    rr_renderer_move_to(renderer, 89.44, -403.75);
    rr_renderer_bezier_curve_to(renderer, 72.24, -395.29, 60.74, -384.11, 49.87,
                                -365.91);
    rr_renderer_bezier_curve_to(renderer, 39.01, -347.70, 43.57, -313.01, 24.25,
                                -294.51);
    rr_renderer_bezier_curve_to(renderer, 4.92, -276.02, -42.70, -273.72,
                                -66.07, -254.94);
    rr_renderer_bezier_curve_to(renderer, -89.44, -236.16, -98.76, -199.03,
                                -115.96, -181.83);
    rr_renderer_bezier_curve_to(renderer, -133.16, -164.63, -165.28, -167.86,
                                -169.29, -151.72);
    rr_renderer_bezier_curve_to(renderer, -173.30, -135.59, -157.68, -91.46,
                                -140.04, -85.01);
    rr_renderer_bezier_curve_to(renderer, -122.41, -78.56, -83.85, -95.73,
                                -63.49, -113.02);
    rr_renderer_bezier_curve_to(renderer, -43.13, -130.30, -43.13, -168.35,
                                -17.90, -188.71);
    rr_renderer_bezier_curve_to(renderer, 7.33, -209.07, 65.13, -211.51, 87.90,
                                -235.16);
    rr_renderer_bezier_curve_to(renderer, 110.66, -258.82, 105.67, -310.57,
                                118.69, -330.64);
    rr_renderer_bezier_curve_to(renderer, 131.70, -350.71, 160.26, -341.25,
                                166.00, -355.59);
    rr_renderer_bezier_curve_to(renderer, 171.73, -369.92, 165.85, -408.63,
                                153.09, -416.66);
    rr_renderer_bezier_curve_to(renderer, 140.33, -424.69, 106.64, -412.21,
                                89.44, -403.75);
    rr_renderer_fill(renderer);
    rr_renderer_set_fill(renderer, 0xff318647);
    rr_renderer_begin_path(renderer);
    rr_renderer_move_to(renderer, 101.50, 94.39);
    rr_renderer_bezier_curve_to(renderer, 84.29, 102.84, 72.80, 114.03, 61.93,
                                132.23);
    rr_renderer_bezier_curve_to(renderer, 51.06, 150.44, 55.63, 185.13, 36.30,
                                203.63);
    rr_renderer_bezier_curve_to(renderer, 16.98, 222.12, -30.64, 224.41, -54.01,
                                243.20);
    rr_renderer_bezier_curve_to(renderer, -77.38, 261.98, -86.70, 299.11,
                                -103.90, 316.31);
    rr_renderer_bezier_curve_to(renderer, -121.11, 333.51, -153.22, 330.28,
                                -157.23, 346.41);
    rr_renderer_bezier_curve_to(renderer, -161.25, 362.55, -145.62, 406.68,
                                -127.99, 413.13);
    rr_renderer_bezier_curve_to(renderer, -110.35, 419.58, -71.79, 402.41,
                                -51.43, 385.12);
    rr_renderer_bezier_curve_to(renderer, -31.07, 367.84, -31.07, 329.79, -5.84,
                                309.43);
    rr_renderer_bezier_curve_to(renderer, 19.39, 289.07, 77.19, 286.63, 99.96,
                                262.98);
    rr_renderer_bezier_curve_to(renderer, 122.72, 239.32, 117.73, 187.57,
                                130.74, 167.50);
    rr_renderer_bezier_curve_to(renderer, 143.76, 147.43, 172.32, 156.89,
                                178.05, 142.55);
    rr_renderer_bezier_curve_to(renderer, 183.79, 128.22, 177.91, 89.51, 165.15,
                                81.48);
    rr_renderer_bezier_curve_to(renderer, 152.39, 73.45, 118.70, 85.93, 101.50,
                                94.39);
    rr_renderer_fill(renderer);
    rr_renderer_set_fill(renderer, 0xff2f8043);
    rr_renderer_begin_path(renderer);
    rr_renderer_move_to(renderer, 35.15, 90.69);
    rr_renderer_bezier_curve_to(renderer, 29.75, 77.74, 35.85, 62.87, 48.79,
                                57.48);
    rr_renderer_bezier_curve_to(renderer, 55.00, 54.89, 61.98, 54.87, 68.21,
                                57.44);
    rr_renderer_bezier_curve_to(renderer, 74.44, 60.01, 79.39, 64.94, 81.98,
                                71.16);
    rr_renderer_bezier_curve_to(renderer, 87.39, 84.11, 81.28, 98.98, 68.35,
                                104.37);
    rr_renderer_bezier_curve_to(renderer, 55.41, 109.77, 40.55, 103.64, 35.15,
                                90.69);
    rr_renderer_fill(renderer);
    rr_renderer_set_fill(renderer, 0xff2f8043);
    rr_renderer_begin_path(renderer);
    rr_renderer_move_to(renderer, -98.67, 77.59);
    rr_renderer_bezier_curve_to(renderer, -104.88, 62.71, -97.87, 45.63, -83.00,
                                39.44);
    rr_renderer_bezier_curve_to(renderer, -75.87, 36.46, -67.84, 36.45, -60.68,
                                39.40);
    rr_renderer_bezier_curve_to(renderer, -53.52, 42.35, -47.83, 48.02, -44.85,
                                55.17);
    rr_renderer_bezier_curve_to(renderer, -38.64, 70.05, -45.65, 87.13, -60.52,
                                93.33);
    rr_renderer_bezier_curve_to(renderer, -75.38, 99.52, -92.46, 92.47, -98.67,
                                77.59);
    rr_renderer_fill(renderer);
    rr_renderer_set_fill(renderer, 0xff2f8043);
    rr_renderer_begin_path(renderer);
    rr_renderer_move_to(renderer, 17.30, -80.17);
    rr_renderer_bezier_curve_to(renderer, 11.09, -95.05, 18.11, -112.14, 32.97,
                                -118.33);
    rr_renderer_bezier_curve_to(renderer, 40.11, -121.30, 48.14, -121.32, 55.30,
                                -118.37);
    rr_renderer_bezier_curve_to(renderer, 62.45, -115.42, 68.15, -109.74, 71.13,
                                -102.60);
    rr_renderer_bezier_curve_to(renderer, 77.34, -87.72, 70.33, -70.63, 55.46,
                                -64.44);
    rr_renderer_bezier_curve_to(renderer, 40.60, -58.25, 23.51, -65.29, 17.30,
                                -80.17);
    rr_renderer_fill(renderer);
    rr_renderer_set_fill(renderer, 0xff2f8043);
    rr_renderer_begin_path(renderer);
    rr_renderer_move_to(renderer, -104.88, -5.28);
    rr_renderer_bezier_curve_to(renderer, -111.09, -20.16, -104.07, -37.25,
                                -89.21, -43.44);
    rr_renderer_bezier_curve_to(renderer, -82.07, -46.41, -74.04, -46.43,
                                -66.89, -43.47);
    rr_renderer_bezier_curve_to(renderer, -59.73, -40.52, -54.03, -34.85,
                                -51.05, -27.71);
    rr_renderer_bezier_curve_to(renderer, -44.84, -12.82, -51.86, 4.26, -66.72,
                                10.45);
    rr_renderer_bezier_curve_to(renderer, -81.59, 16.64, -98.67, 9.60, -104.88,
                                -5.28);
    rr_renderer_fill(renderer);
    rr_renderer_set_fill(renderer, 0xff2f8043);
    rr_renderer_begin_path(renderer);
    rr_renderer_move_to(renderer, -60.25, 98.38);
    rr_renderer_bezier_curve_to(renderer, -65.58, 85.61, -59.56, 70.94, -46.80,
                                65.63);
    rr_renderer_bezier_curve_to(renderer, -40.67, 63.07, -33.78, 63.06, -27.64,
                                65.60);
    rr_renderer_bezier_curve_to(renderer, -21.50, 68.13, -16.61, 73.00, -14.05,
                                79.14);
    rr_renderer_bezier_curve_to(renderer, -8.71, 91.91, -14.74, 106.58, -27.49,
                                111.89);
    rr_renderer_bezier_curve_to(renderer, -40.25, 117.21, -54.92, 111.16,
                                -60.25, 98.38);
    rr_renderer_fill(renderer);
    rr_renderer_set_fill(renderer, 0xff2f8043);
    rr_renderer_begin_path(renderer);
    rr_renderer_move_to(renderer, 46.17, -4.70);
    rr_renderer_bezier_curve_to(renderer, 42.06, -14.56, 46.71, -25.87, 56.55,
                                -29.96);
    rr_renderer_bezier_curve_to(renderer, 61.28, -31.93, 66.60, -31.94, 71.34,
                                -29.98);
    rr_renderer_bezier_curve_to(renderer, 76.08, -28.03, 79.85, -24.27, 81.83,
                                -19.54);
    rr_renderer_bezier_curve_to(renderer, 85.94, -9.68, 81.30, 1.62, 71.45,
                                5.72);
    rr_renderer_bezier_curve_to(renderer, 61.60, 9.82, 50.29, 5.15, 46.17,
                                -4.70);
    rr_renderer_fill(renderer);
    rr_renderer_set_fill(renderer, 0xff2f8043);
    rr_renderer_begin_path(renderer);
    rr_renderer_move_to(renderer, -47.49, 29.87);
    rr_renderer_bezier_curve_to(renderer, -51.61, 20.02, -46.96, 8.71, -37.12,
                                4.61);
    rr_renderer_bezier_curve_to(renderer, -32.39, 2.64, -27.07, 2.64, -22.33,
                                4.59);
    rr_renderer_bezier_curve_to(renderer, -17.59, 6.55, -13.82, 10.30, -11.84,
                                15.03);
    rr_renderer_bezier_curve_to(renderer, -7.73, 24.89, -12.37, 36.20, -22.22,
                                40.29);
    rr_renderer_bezier_curve_to(renderer, -32.06, 44.39, -43.38, 39.72, -47.49,
                                29.87);
    rr_renderer_fill(renderer);
    rr_renderer_set_fill(renderer, 0xff2f8043);
    rr_renderer_begin_path(renderer);
    rr_renderer_move_to(renderer, -39.77, -66.27);
    rr_renderer_bezier_curve_to(renderer, -43.89, -76.12, -39.24, -87.43,
                                -29.39, -91.53);
    rr_renderer_bezier_curve_to(renderer, -24.67, -93.49, -19.35, -93.50,
                                -14.61, -91.54);
    rr_renderer_bezier_curve_to(renderer, -9.87, -89.59, -6.09, -85.83, -4.12,
                                -81.10);
    rr_renderer_bezier_curve_to(renderer, -0.01, -71.25, -4.65, -59.94, -14.50,
                                -55.84);
    rr_renderer_bezier_curve_to(renderer, -24.34, -51.74, -35.66, -56.41,
                                -39.77, -66.27);
    rr_renderer_fill(renderer);
    rr_renderer_set_fill(renderer, 0xff2f8043);
    rr_renderer_begin_path(renderer);
    rr_renderer_move_to(renderer, -83.62, -41.45);
    rr_renderer_bezier_curve_to(renderer, -86.36, -48.00, -83.27, -55.53,
                                -76.72, -58.27);
    rr_renderer_bezier_curve_to(renderer, -73.58, -59.58, -70.04, -59.58,
                                -66.88, -58.28);
    rr_renderer_bezier_curve_to(renderer, -63.73, -56.98, -61.22, -54.49,
                                -59.90, -51.34);
    rr_renderer_bezier_curve_to(renderer, -57.16, -44.78, -60.25, -37.25,
                                -66.80, -34.52);
    rr_renderer_bezier_curve_to(renderer, -73.35, -31.79, -80.88, -34.89,
                                -83.62, -41.45);
    rr_renderer_fill(renderer);
    rr_renderer_set_fill(renderer, 0xff2f8043);
    rr_renderer_begin_path(renderer);
    rr_renderer_move_to(renderer, 68.77, 99.36);
    rr_renderer_bezier_curve_to(renderer, 66.03, 92.80, 69.11, 85.27, 75.66,
                                82.54);
    rr_renderer_bezier_curve_to(renderer, 78.81, 81.23, 82.35, 81.22, 85.50,
                                82.52);
    rr_renderer_bezier_curve_to(renderer, 88.65, 83.82, 91.17, 86.32, 92.48,
                                89.47);
    rr_renderer_bezier_curve_to(renderer, 95.22, 96.03, 92.13, 103.56, 85.58,
                                106.29);
    rr_renderer_bezier_curve_to(renderer, 79.03, 109.02, 71.50, 105.92, 68.77,
                                99.36);
    rr_renderer_fill(renderer);
    rr_renderer_set_fill(renderer, 0xff2f8043);
    rr_renderer_begin_path(renderer);
    rr_renderer_move_to(renderer, -53.38, -89.43);
    rr_renderer_bezier_curve_to(renderer, -56.12, -95.99, -53.03, -103.52,
                                -46.48, -106.25);
    rr_renderer_bezier_curve_to(renderer, -43.34, -107.56, -39.80, -107.57,
                                -36.64, -106.27);
    rr_renderer_bezier_curve_to(renderer, -33.49, -104.97, -30.98, -102.47,
                                -29.66, -99.32);
    rr_renderer_bezier_curve_to(renderer, -26.92, -92.76, -30.01, -85.23,
                                -36.56, -82.50);
    rr_renderer_bezier_curve_to(renderer, -43.11, -79.77, -50.64, -82.87,
                                -53.38, -89.43);
    rr_renderer_fill(renderer);
    rr_renderer_set_fill(renderer, 0xff2f8043);
    rr_renderer_begin_path(renderer);
    rr_renderer_move_to(renderer, -22.62, 9.79);
    rr_renderer_bezier_curve_to(renderer, -25.36, 3.23, -22.27, -4.30, -15.72,
                                -7.03);
    rr_renderer_bezier_curve_to(renderer, -12.58, -8.34, -9.04, -8.35, -5.88,
                                -7.05);
    rr_renderer_bezier_curve_to(renderer, -2.73, -5.75, -0.22, -3.25, 1.10,
                                -0.10);
    rr_renderer_bezier_curve_to(renderer, 3.84, 6.46, 0.75, 13.99, -5.80,
                                16.72);
    rr_renderer_bezier_curve_to(renderer, -12.35, 19.45, -19.88, 16.35, -22.62,
                                9.79);
    rr_renderer_fill(renderer);
    rr_renderer_set_fill(renderer, 0xff2f8043);
    rr_renderer_begin_path(renderer);
    rr_renderer_move_to(renderer, 74.81, -55.79);
    rr_renderer_bezier_curve_to(renderer, 72.07, -62.35, 75.16, -69.88, 81.71,
                                -72.61);
    rr_renderer_bezier_curve_to(renderer, 84.86, -73.92, 88.39, -73.93, 91.55,
                                -72.63);
    rr_renderer_bezier_curve_to(renderer, 94.70, -71.33, 97.21, -68.83, 98.53,
                                -65.68);
    rr_renderer_bezier_curve_to(renderer, 101.27, -59.13, 98.18, -51.60, 91.63,
                                -48.86);
    rr_renderer_bezier_curve_to(renderer, 85.08, -46.13, 77.55, -49.24, 74.81,
                                -55.79);
    rr_renderer_fill(renderer);
}