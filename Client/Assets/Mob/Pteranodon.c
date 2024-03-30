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

void rr_pteranodon_body_draw(struct rr_renderer *renderer)
{
    rr_renderer_set_fill(renderer, 0xffad9168);
    rr_renderer_begin_path(renderer);
    rr_renderer_move_to(renderer, -27.39, 62.62);
    rr_renderer_bezier_curve_to(renderer, -76.97, 62.62, -117.17, 34.62,
                                -117.17, 0.09);
    rr_renderer_bezier_curve_to(renderer, -117.17, -16.50, -107.71, -32.40,
                                -90.87, -44.13);
    rr_renderer_bezier_curve_to(renderer, -74.04, -55.86, -51.20, -62.44,
                                -27.39, -62.44);
    rr_renderer_bezier_curve_to(renderer, 22.20, -62.44, 62.39, -34.45, 62.39,
                                0.09);
    rr_renderer_bezier_curve_to(renderer, 62.39, 34.62, 22.20, 62.62, -27.39,
                                62.62);
    rr_renderer_fill(renderer);
    rr_renderer_set_fill(renderer, 0xffad9168);
    rr_renderer_begin_path(renderer);
    rr_renderer_move_to(renderer, -99.81, 22.60);
    rr_renderer_bezier_curve_to(renderer, -118.23, 22.60, -133.16, 12.51,
                                -133.16, 0.08);
    rr_renderer_bezier_curve_to(renderer, -133.16, -5.89, -129.65, -11.62,
                                -123.39, -15.85);
    rr_renderer_bezier_curve_to(renderer, -117.14, -20.07, -108.66, -22.44,
                                -99.81, -22.44);
    rr_renderer_bezier_curve_to(renderer, -81.39, -22.44, -66.46, -12.36,
                                -66.46, 0.08);
    rr_renderer_bezier_curve_to(renderer, -66.46, 12.51, -81.39, 22.60, -99.81,
                                22.60);
    rr_renderer_fill(renderer);
    rr_renderer_set_fill(renderer, 0xffc4a575);
    rr_renderer_begin_path(renderer);
    rr_renderer_move_to(renderer, 20.85, 31.35);
    rr_renderer_bezier_curve_to(renderer, -5.60, 48.62, -48.49, 48.62, -74.94,
                                31.35);
    rr_renderer_quadratic_curve_to(renderer, -96.28, 17.41, -112.41, 0.07);
    rr_renderer_quadratic_curve_to(renderer, -96.28, -17.27, -74.94, -31.21);
    rr_renderer_bezier_curve_to(renderer, -48.49, -48.48, -5.60, -48.48, 20.85,
                                -31.21);
    rr_renderer_bezier_curve_to(renderer, 47.31, -13.93, 47.31, 14.07, 20.85,
                                31.35);
    rr_renderer_fill(renderer);
    rr_renderer_set_fill(renderer, 0xffad9168);
    rr_renderer_begin_path(renderer);
    rr_renderer_move_to(renderer, -127.07, 13.20);
    rr_renderer_line_to(renderer, -95.48, 40.68);
    rr_renderer_line_to(renderer, -101.29, 14.09);
    rr_renderer_fill(renderer);
    rr_renderer_set_fill(renderer, 0xffad9168);
    rr_renderer_begin_path(renderer);
    rr_renderer_move_to(renderer, -127.07, -13.04);
    rr_renderer_line_to(renderer, -95.48, -40.52);
    rr_renderer_line_to(renderer, -101.29, -13.93);
    rr_renderer_fill(renderer);
    rr_renderer_set_fill(renderer, 0xff897d6d);
    rr_renderer_begin_path(renderer);
    rr_renderer_move_to(renderer, 52.45, 45.56);
    rr_renderer_bezier_curve_to(renderer, 57.63, 48.88, 75.49, 30.79, 88.51,
                                23.42);
    rr_renderer_bezier_curve_to(renderer, 101.52, 16.06, 125.12, 5.77, 130.53,
                                1.35);
    rr_renderer_bezier_curve_to(renderer, 135.94, -3.08, 133.14, -3.49, 120.95,
                                -3.14);
    rr_renderer_bezier_curve_to(renderer, 108.77, -2.79, 68.82, -4.65, 57.40,
                                3.46);
    rr_renderer_bezier_curve_to(renderer, 45.98, 11.58, 47.26, 42.23, 52.45,
                                45.56);
    rr_renderer_fill(renderer);
    rr_renderer_set_fill(renderer, 0xff9d8f7d);
    rr_renderer_begin_path(renderer);
    rr_renderer_move_to(renderer, 52.45, -49.56);
    rr_renderer_bezier_curve_to(renderer, 57.63, -52.89, 75.49, -34.79, 88.51,
                                -27.43);
    rr_renderer_bezier_curve_to(renderer, 101.52, -20.06, 125.12, -9.78, 130.53,
                                -5.35);
    rr_renderer_bezier_curve_to(renderer, 135.94, -0.92, 133.14, -0.51, 120.95,
                                -0.86);
    rr_renderer_bezier_curve_to(renderer, 108.77, -1.21, 68.82, 0.65, 57.40,
                                -7.46);
    rr_renderer_bezier_curve_to(renderer, 45.98, -15.58, 47.26, -46.23, 52.45,
                                -49.56);
    rr_renderer_fill(renderer);
    rr_renderer_set_fill(renderer, 0xffbca787);
    rr_renderer_begin_path(renderer);
    rr_renderer_move_to(renderer, -17.29, 77.19);
    rr_renderer_bezier_curve_to(renderer, -51.79, 77.19, -79.76, 42.64, -79.76,
                                0.02);
    rr_renderer_bezier_curve_to(renderer, -79.76, -42.60, -51.79, -77.14,
                                -17.29, -77.14);
    rr_renderer_bezier_curve_to(renderer, 17.21, -77.14, 45.18, -42.60, 45.18,
                                0.02);
    rr_renderer_bezier_curve_to(renderer, 45.18, 42.64, 17.21, 77.19, -17.29,
                                77.19);
    rr_renderer_fill(renderer);
    rr_renderer_set_fill(renderer, 0xffbca787);
    rr_renderer_begin_path(renderer);
    rr_renderer_move_to(renderer, -66.65, 27.80);
    rr_renderer_bezier_curve_to(renderer, -79.07, 27.80, -89.14, 15.36, -89.14,
                                0.01);
    rr_renderer_bezier_curve_to(renderer, -89.14, -15.34, -79.07, -27.79,
                                -66.65, -27.79);
    rr_renderer_bezier_curve_to(renderer, -54.23, -27.79, -44.16, -15.34,
                                -44.16, 0.01);
    rr_renderer_bezier_curve_to(renderer, -44.16, 15.36, -54.23, 27.80, -66.65,
                                27.80);
    rr_renderer_fill(renderer);
    rr_renderer_set_fill(renderer, 0xffd4c0a2);
    rr_renderer_begin_path(renderer);
    rr_renderer_move_to(renderer, 13.99, 39.91);
    rr_renderer_bezier_curve_to(renderer, -3.28, 61.95, -31.28, 61.95, -48.56,
                                39.91);
    rr_renderer_quadratic_curve_to(renderer, -62.01, 22.74, -71.10, 0.00);
    rr_renderer_quadratic_curve_to(renderer, -62.01, -22.74, -48.56, -39.90);
    rr_renderer_bezier_curve_to(renderer, -31.28, -61.94, -3.28, -61.94, 13.99,
                                -39.90);
    rr_renderer_bezier_curve_to(renderer, 31.27, -17.87, 31.27, 17.87, 13.99,
                                39.91);
    rr_renderer_fill(renderer);
    rr_renderer_set_fill(renderer, 0xffbca787);
    rr_renderer_begin_path(renderer);
    rr_renderer_move_to(renderer, -86.41, -13.39);
    rr_renderer_line_to(renderer, -68.37, -45.35);
    rr_renderer_line_to(renderer, -64.72, -19.78);
    rr_renderer_fill(renderer);
    rr_renderer_set_fill(renderer, 0xffbca787);
    rr_renderer_begin_path(renderer);
    rr_renderer_move_to(renderer, -86.41, 13.43);
    rr_renderer_line_to(renderer, -68.37, 45.39);
    rr_renderer_line_to(renderer, -64.72, 19.82);
    rr_renderer_fill(renderer);
    rr_renderer_set_fill(renderer, 0xffad9168);
    rr_renderer_begin_path(renderer);
    rr_renderer_move_to(renderer, 21.38, 62.60);
    rr_renderer_bezier_curve_to(renderer, -13.13, 62.60, -41.10, 34.60, -41.10,
                                0.07);
    rr_renderer_bezier_curve_to(renderer, -41.10, -16.51, -34.52, -32.42,
                                -22.80, -44.15);
    rr_renderer_bezier_curve_to(renderer, -11.09, -55.87, 4.80, -62.46, 21.38,
                                -62.46);
    rr_renderer_bezier_curve_to(renderer, 55.88, -62.46, 83.86, -34.47, 83.86,
                                0.07);
    rr_renderer_bezier_curve_to(renderer, 83.86, 34.60, 55.88, 62.60, 21.38,
                                62.60);
    rr_renderer_fill(renderer);
    rr_renderer_set_fill(renderer, 0xffad9168);
    rr_renderer_begin_path(renderer);
    rr_renderer_move_to(renderer, -27.99, 22.58);
    rr_renderer_bezier_curve_to(renderer, -40.41, 22.58, -50.48, 12.50, -50.48,
                                0.06);
    rr_renderer_bezier_curve_to(renderer, -50.48, -5.91, -48.11, -11.64, -43.90,
                                -15.86);
    rr_renderer_bezier_curve_to(renderer, -39.68, -20.08, -33.96, -22.46,
                                -27.99, -22.46);
    rr_renderer_bezier_curve_to(renderer, -15.57, -22.46, -5.50, -12.37, -5.50,
                                0.06);
    rr_renderer_bezier_curve_to(renderer, -5.50, 12.50, -15.57, 22.58, -27.99,
                                22.58);
    rr_renderer_fill(renderer);
    rr_renderer_set_fill(renderer, 0xffc4a575);
    rr_renderer_begin_path(renderer);
    rr_renderer_move_to(renderer, 52.64, 31.33);
    rr_renderer_bezier_curve_to(renderer, 35.37, 48.60, 7.37, 48.60, -9.90,
                                31.33);
    rr_renderer_quadratic_curve_to(renderer, -23.35, 17.87, -32.44, 0.06);
    rr_renderer_quadratic_curve_to(renderer, -23.35, -17.76, -9.90, -31.22);
    rr_renderer_bezier_curve_to(renderer, 7.37, -48.49, 35.37, -48.49, 52.64,
                                -31.22);
    rr_renderer_bezier_curve_to(renderer, 69.91, -13.95, 69.91, 14.06, 52.64,
                                31.33);
    rr_renderer_fill(renderer);
    rr_renderer_set_fill(renderer, 0xffad9168);
    rr_renderer_begin_path(renderer);
    rr_renderer_move_to(renderer, -44.54, 15.28);
    rr_renderer_line_to(renderer, -26.06, 40.50);
    rr_renderer_line_to(renderer, -26.06, 16.11);
    rr_renderer_fill(renderer);
    rr_renderer_set_fill(renderer, 0xffad9168);
    rr_renderer_begin_path(renderer);
    rr_renderer_move_to(renderer, -44.54, -15.14);
    rr_renderer_line_to(renderer, -26.06, -40.36);
    rr_renderer_line_to(renderer, -26.06, -15.97);
    rr_renderer_fill(renderer);
}

void rr_pteranodon_wing1_draw(struct rr_renderer *renderer)
{
    rr_renderer_set_fill(renderer, 0xff786750);
    rr_renderer_begin_path(renderer);
    rr_renderer_move_to(renderer, -60.51, -168.98);
    rr_renderer_bezier_curve_to(renderer, -29.76, -176.26, -2.29, -171.45, 0.84,
                                -158.22);
    rr_renderer_bezier_curve_to(renderer, 2.34, -151.87, -2.08, -144.39, -11.46,
                                -137.43);
    rr_renderer_bezier_curve_to(renderer, -20.84, -130.46, -34.40, -124.58,
                                -49.17, -121.08);
    rr_renderer_bezier_curve_to(renderer, -79.92, -113.80, -107.39, -118.61,
                                -110.52, -131.84);
    rr_renderer_bezier_curve_to(renderer, -113.65, -145.06, -91.26, -161.69,
                                -60.51, -168.98);
    rr_renderer_fill(renderer);
    rr_renderer_set_fill(renderer, 0xff786750);
    rr_renderer_begin_path(renderer);
    rr_renderer_move_to(renderer, -109.90, -129.34);
    rr_renderer_bezier_curve_to(renderer, -86.85, -145.98, -16.58, -87.97,
                                47.06, 0.22);
    rr_renderer_bezier_curve_to(renderer, 110.69, 88.42, 143.59, 173.40, 120.54,
                                190.04);
    rr_renderer_bezier_curve_to(renderer, 61.33, 80.05, -24.19, -38.48, -109.90,
                                -129.34);
    rr_renderer_fill(renderer);
    rr_renderer_set_fill(renderer, 0xff786750);
    rr_renderer_begin_path(renderer);
    rr_renderer_move_to(renderer, -21.32, -168.75);
    rr_renderer_bezier_curve_to(renderer, 5.09, -179.27, 58.44, -107.48, 97.84,
                                -8.42);
    rr_renderer_bezier_curve_to(renderer, 137.25, 90.64, 147.78, 179.47, 121.38,
                                189.99);
    rr_renderer_bezier_curve_to(renderer, 119.58, 141.65, 102.01, 71.67, 73.94,
                                1.10);
    rr_renderer_bezier_curve_to(renderer, 45.86, -69.47, 10.57, -132.40, -21.32,
                                -168.75);
    rr_renderer_fill(renderer);
    rr_renderer_set_fill(renderer, 0xff786750);
    rr_renderer_begin_path(renderer);
    rr_renderer_move_to(renderer, -15.69, -166.71);
    rr_renderer_line_to(renderer, -104.38, -130.89);
    rr_renderer_line_to(renderer, 119.69, 147.22);
    rr_renderer_line_to(renderer, 72.29, -33.67);
    rr_renderer_fill(renderer);
    rr_renderer_set_fill(renderer, 0xff8c785b);
    rr_renderer_begin_path(renderer);
    rr_renderer_move_to(renderer, -24.56, -156.66);
    rr_renderer_bezier_curve_to(renderer, -8.22, -164.10, 36.08, -101.94, 74.39,
                                -17.80);
    rr_renderer_bezier_curve_to(renderer, 112.70, 66.33, 130.51, 140.57, 114.17,
                                148.02);
    rr_renderer_bezier_curve_to(renderer, 107.11, 107.81, 86.89, 48.88, 59.60,
                                -11.06);
    rr_renderer_bezier_curve_to(renderer, 32.31, -71.00, 1.13, -124.94, -24.56,
                                -156.66);
    rr_renderer_fill(renderer);
    rr_renderer_set_fill(renderer, 0xff8c785b);
    rr_renderer_begin_path(renderer);
    rr_renderer_move_to(renderer, -97.05, -133.52);
    rr_renderer_bezier_curve_to(renderer, -82.73, -144.35, -23.68, -90.29,
                                34.82, -12.78);
    rr_renderer_bezier_curve_to(renderer, 93.33, 64.74, 129.15, 136.35, 114.82,
                                147.18);
    rr_renderer_bezier_curve_to(renderer, 97.98, 107.88, 63.54, 52.25, 21.85,
                                -2.97);
    rr_renderer_bezier_curve_to(renderer, -19.83, -58.19, -63.88, -106.56,
                                -97.05, -133.52);
    rr_renderer_fill(renderer);
    rr_renderer_set_fill(renderer, 0xff8c785b);
    rr_renderer_begin_path(renderer);
    rr_renderer_move_to(renderer, -16.27, -151.72);
    rr_renderer_line_to(renderer, -84.01, -129.11);
    rr_renderer_line_to(renderer, 23.65, -19.84);
    rr_renderer_line_to(renderer, 110.08, 125.59);
    rr_renderer_line_to(renderer, 89.12, 32.28);
    rr_renderer_line_to(renderer, 39.63, -73.40);
    rr_renderer_fill(renderer);
    rr_renderer_set_fill(renderer, 0xff8c785b);
    rr_renderer_begin_path(renderer);
    rr_renderer_move_to(renderer, -60.40, -153.59);
    rr_renderer_bezier_curve_to(renderer, -39.05, -159.07, -20.65, -159.25,
                                -19.30, -153.98);
    rr_renderer_bezier_curve_to(renderer, -18.65, -151.45, -22.10, -147.98,
                                -28.89, -144.33);
    rr_renderer_bezier_curve_to(renderer, -35.67, -140.69, -45.25, -137.16,
                                -55.49, -134.53);
    rr_renderer_bezier_curve_to(renderer, -76.84, -129.05, -95.24, -128.87,
                                -96.59, -134.14);
    rr_renderer_bezier_curve_to(renderer, -97.24, -136.67, -93.79, -140.14,
                                -87.00, -143.78);
    rr_renderer_bezier_curve_to(renderer, -80.22, -147.43, -70.64, -150.96,
                                -60.40, -153.59);
    rr_renderer_fill(renderer);
    rr_renderer_set_fill(renderer, 0xff897d6d);
    rr_renderer_begin_path(renderer);
    rr_renderer_move_to(renderer, -65.12, -145.78);
    rr_renderer_bezier_curve_to(renderer, -68.84, -142.00, -73.76, -139.13,
                                -81.06, -135.53);
    rr_renderer_bezier_curve_to(renderer, -88.37, -131.93, -100.18, -126.57,
                                -108.93, -124.17);
    rr_renderer_bezier_curve_to(renderer, -117.68, -121.78, -130.86, -120.47,
                                -133.56, -121.17);
    rr_renderer_bezier_curve_to(renderer, -136.25, -121.86, -126.90, -126.61,
                                -125.11, -128.33);
    rr_renderer_bezier_curve_to(renderer, -123.31, -130.06, -122.59, -130.86,
                                -122.79, -131.53);
    rr_renderer_bezier_curve_to(renderer, -122.99, -132.19, -123.30, -131.98,
                                -126.30, -132.30);
    rr_renderer_bezier_curve_to(renderer, -129.30, -132.62, -140.63, -131.66,
                                -140.79, -133.42);
    rr_renderer_bezier_curve_to(renderer, -140.94, -135.19, -133.39, -138.31,
                                -127.22, -142.88);
    rr_renderer_bezier_curve_to(renderer, -121.05, -147.45, -110.55, -154.89,
                                -103.76, -160.85);
    rr_renderer_bezier_curve_to(renderer, -96.98, -166.80, -90.51, -174.10,
                                -86.51, -178.60);
    rr_renderer_bezier_curve_to(renderer, -82.51, -183.11, -83.44, -188.59,
                                -79.74, -187.88);
    rr_renderer_bezier_curve_to(renderer, -76.05, -187.17, -67.84, -179.30,
                                -64.34, -174.35);
    rr_renderer_bezier_curve_to(renderer, -60.84, -169.40, -58.60, -162.95,
                                -58.73, -158.19);
    rr_renderer_bezier_curve_to(renderer, -58.86, -153.42, -61.40, -149.55,
                                -65.12, -145.78);
    rr_renderer_fill(renderer);
    rr_renderer_set_fill(renderer, 0xff9d8f7d);
    rr_renderer_begin_path(renderer);
    rr_renderer_move_to(renderer, -70.44, -149.56);
    rr_renderer_bezier_curve_to(renderer, -73.58, -146.44, -78.57, -143.26,
                                -84.51, -140.00);
    rr_renderer_bezier_curve_to(renderer, -90.44, -136.73, -100.42, -132.14,
                                -106.07, -129.97);
    rr_renderer_bezier_curve_to(renderer, -111.71, -127.80, -116.55, -126.84,
                                -118.35, -126.96);
    rr_renderer_bezier_curve_to(renderer, -120.15, -127.09, -116.89, -129.43,
                                -116.85, -130.72);
    rr_renderer_bezier_curve_to(renderer, -116.80, -132.02, -117.13, -133.81,
                                -118.10, -134.73);
    rr_renderer_bezier_curve_to(renderer, -119.06, -135.65, -121.40, -135.78,
                                -122.61, -136.24);
    rr_renderer_bezier_curve_to(renderer, -123.83, -136.70, -126.16, -136.45,
                                -125.37, -137.49);
    rr_renderer_bezier_curve_to(renderer, -124.58, -138.54, -121.76, -139.79,
                                -117.85, -142.51);
    rr_renderer_bezier_curve_to(renderer, -113.94, -145.22, -107.14, -149.45,
                                -101.89, -153.79);
    rr_renderer_bezier_curve_to(renderer, -96.63, -158.13, -90.43, -164.54,
                                -86.32, -168.55);
    rr_renderer_bezier_curve_to(renderer, -82.21, -172.56, -80.03, -177.62,
                                -77.23, -177.85);
    rr_renderer_bezier_curve_to(renderer, -74.44, -178.09, -71.46, -173.14,
                                -69.54, -169.95);
    rr_renderer_bezier_curve_to(renderer, -67.61, -166.77, -65.53, -162.12,
                                -65.68, -158.72);
    rr_renderer_bezier_curve_to(renderer, -65.83, -155.32, -67.30, -152.68,
                                -70.44, -149.56);
    rr_renderer_fill(renderer);
}

void rr_pteranodon_wing2_draw(struct rr_renderer *renderer)
{
    rr_renderer_set_fill(renderer, 0xff786750);
    rr_renderer_begin_path(renderer);
    rr_renderer_move_to(renderer, -60.51, 168.98);
    rr_renderer_bezier_curve_to(renderer, -29.76, 176.27, -2.29, 171.45, 0.84,
                                158.22);
    rr_renderer_bezier_curve_to(renderer, 2.34, 151.87, -2.08, 144.39, -11.46,
                                137.43);
    rr_renderer_bezier_curve_to(renderer, -20.84, 130.46, -34.40, 124.58,
                                -49.17, 121.08);
    rr_renderer_bezier_curve_to(renderer, -79.92, 113.80, -107.39, 118.61,
                                -110.52, 131.84);
    rr_renderer_bezier_curve_to(renderer, -113.65, 145.06, -91.27, 161.69,
                                -60.51, 168.98);
    rr_renderer_fill(renderer);
    rr_renderer_set_fill(renderer, 0xff786750);
    rr_renderer_begin_path(renderer);
    rr_renderer_move_to(renderer, -109.90, 129.34);
    rr_renderer_bezier_curve_to(renderer, -86.85, 145.98, -16.58, 87.97, 47.05,
                                -0.22);
    rr_renderer_bezier_curve_to(renderer, 110.69, -88.42, 143.59, -173.40,
                                120.54, -190.03);
    rr_renderer_bezier_curve_to(renderer, 61.33, -80.05, -24.19, 38.48, -109.90,
                                129.34);
    rr_renderer_fill(renderer);
    rr_renderer_set_fill(renderer, 0xff786750);
    rr_renderer_begin_path(renderer);
    rr_renderer_move_to(renderer, -21.32, 168.75);
    rr_renderer_bezier_curve_to(renderer, 5.09, 179.27, 58.44, 107.48, 97.84,
                                8.42);
    rr_renderer_bezier_curve_to(renderer, 137.24, -90.64, 147.78, -179.47,
                                121.38, -189.99);
    rr_renderer_bezier_curve_to(renderer, 119.58, -141.65, 102.01, -71.67,
                                73.93, -1.10);
    rr_renderer_bezier_curve_to(renderer, 45.86, 69.47, 10.57, 132.40, -21.32,
                                168.75);
    rr_renderer_fill(renderer);
    rr_renderer_set_fill(renderer, 0xff786750);
    rr_renderer_begin_path(renderer);
    rr_renderer_move_to(renderer, -15.69, 166.71);
    rr_renderer_line_to(renderer, -104.38, 130.89);
    rr_renderer_line_to(renderer, 119.69, -147.22);
    rr_renderer_line_to(renderer, 72.29, 33.67);
    rr_renderer_fill(renderer);
    rr_renderer_set_fill(renderer, 0xff8c785b);
    rr_renderer_begin_path(renderer);
    rr_renderer_move_to(renderer, -24.56, 156.66);
    rr_renderer_bezier_curve_to(renderer, -8.22, 164.10, 36.08, 101.94, 74.39,
                                17.80);
    rr_renderer_bezier_curve_to(renderer, 112.70, -66.33, 130.51, -140.57,
                                114.17, -148.02);
    rr_renderer_bezier_curve_to(renderer, 107.11, -107.81, 86.89, -48.87, 59.60,
                                11.06);
    rr_renderer_bezier_curve_to(renderer, 32.31, 71.00, 1.13, 124.94, -24.56,
                                156.66);
    rr_renderer_fill(renderer);
    rr_renderer_set_fill(renderer, 0xff8c785b);
    rr_renderer_begin_path(renderer);
    rr_renderer_move_to(renderer, -97.05, 133.52);
    rr_renderer_bezier_curve_to(renderer, -82.73, 144.35, -23.68, 90.29, 34.82,
                                12.78);
    rr_renderer_bezier_curve_to(renderer, 93.33, -64.74, 129.15, -136.35,
                                114.82, -147.18);
    rr_renderer_bezier_curve_to(renderer, 97.98, -107.87, 63.53, -52.25, 21.85,
                                2.97);
    rr_renderer_bezier_curve_to(renderer, -19.83, 58.19, -63.88, 106.56, -97.05,
                                133.52);
    rr_renderer_fill(renderer);
    rr_renderer_set_fill(renderer, 0xff8c785b);
    rr_renderer_begin_path(renderer);
    rr_renderer_move_to(renderer, -16.28, 151.72);
    rr_renderer_line_to(renderer, -84.02, 129.11);
    rr_renderer_line_to(renderer, 23.65, 19.84);
    rr_renderer_line_to(renderer, 110.08, -125.59);
    rr_renderer_line_to(renderer, 89.12, -32.28);
    rr_renderer_line_to(renderer, 39.63, 73.40);
    rr_renderer_fill(renderer);
    rr_renderer_set_fill(renderer, 0xff8c785b);
    rr_renderer_begin_path(renderer);
    rr_renderer_move_to(renderer, -60.40, 153.59);
    rr_renderer_bezier_curve_to(renderer, -39.05, 159.07, -20.66, 159.25,
                                -19.30, 153.98);
    rr_renderer_bezier_curve_to(renderer, -18.65, 151.45, -22.10, 147.98,
                                -28.89, 144.34);
    rr_renderer_bezier_curve_to(renderer, -35.68, 140.69, -45.25, 137.16,
                                -55.50, 134.53);
    rr_renderer_bezier_curve_to(renderer, -76.84, 129.05, -95.24, 128.87,
                                -96.59, 134.14);
    rr_renderer_bezier_curve_to(renderer, -97.24, 136.67, -93.79, 140.14,
                                -87.00, 143.78);
    rr_renderer_bezier_curve_to(renderer, -80.22, 147.43, -70.65, 150.96,
                                -60.40, 153.59);
    rr_renderer_fill(renderer);
    rr_renderer_set_fill(renderer, 0xff897d6d);
    rr_renderer_begin_path(renderer);
    rr_renderer_move_to(renderer, -65.12, 145.78);
    rr_renderer_bezier_curve_to(renderer, -68.84, 142.00, -73.76, 139.13,
                                -81.07, 135.53);
    rr_renderer_bezier_curve_to(renderer, -88.37, 131.93, -100.18, 126.57,
                                -108.93, 124.17);
    rr_renderer_bezier_curve_to(renderer, -117.68, 121.78, -130.86, 120.48,
                                -133.56, 121.17);
    rr_renderer_bezier_curve_to(renderer, -136.26, 121.86, -126.91, 126.61,
                                -125.11, 128.33);
    rr_renderer_bezier_curve_to(renderer, -123.32, 130.06, -122.59, 130.87,
                                -122.79, 131.53);
    rr_renderer_bezier_curve_to(renderer, -122.99, 132.19, -123.30, 131.98,
                                -126.30, 132.30);
    rr_renderer_bezier_curve_to(renderer, -129.30, 132.62, -140.64, 131.66,
                                -140.79, 133.42);
    rr_renderer_bezier_curve_to(renderer, -140.94, 135.19, -133.39, 138.31,
                                -127.22, 142.88);
    rr_renderer_bezier_curve_to(renderer, -121.05, 147.45, -110.55, 154.89,
                                -103.76, 160.85);
    rr_renderer_bezier_curve_to(renderer, -96.98, 166.80, -90.51, 174.10,
                                -86.51, 178.60);
    rr_renderer_bezier_curve_to(renderer, -82.51, 183.11, -83.44, 188.59,
                                -79.74, 187.88);
    rr_renderer_bezier_curve_to(renderer, -76.05, 187.17, -67.84, 179.30,
                                -64.34, 174.35);
    rr_renderer_bezier_curve_to(renderer, -60.84, 169.40, -58.60, 162.95,
                                -58.74, 158.19);
    rr_renderer_bezier_curve_to(renderer, -58.87, 153.43, -61.40, 149.55,
                                -65.12, 145.78);
    rr_renderer_fill(renderer);
    rr_renderer_set_fill(renderer, 0xff9d8f7d);
    rr_renderer_begin_path(renderer);
    rr_renderer_move_to(renderer, -70.44, 149.56);
    rr_renderer_bezier_curve_to(renderer, -73.58, 146.44, -78.57, 143.26,
                                -84.51, 140.00);
    rr_renderer_bezier_curve_to(renderer, -90.45, 136.73, -100.43, 132.14,
                                -106.07, 129.97);
    rr_renderer_bezier_curve_to(renderer, -111.71, 127.80, -116.55, 126.84,
                                -118.35, 126.96);
    rr_renderer_bezier_curve_to(renderer, -120.15, 127.09, -116.89, 129.43,
                                -116.85, 130.72);
    rr_renderer_bezier_curve_to(renderer, -116.81, 132.02, -117.14, 133.81,
                                -118.10, 134.73);
    rr_renderer_bezier_curve_to(renderer, -119.06, 135.65, -121.40, 135.78,
                                -122.61, 136.24);
    rr_renderer_bezier_curve_to(renderer, -123.83, 136.70, -126.17, 136.45,
                                -125.37, 137.49);
    rr_renderer_bezier_curve_to(renderer, -124.58, 138.54, -121.76, 139.79,
                                -117.85, 142.51);
    rr_renderer_bezier_curve_to(renderer, -113.94, 145.22, -107.14, 149.45,
                                -101.89, 153.79);
    rr_renderer_bezier_curve_to(renderer, -96.63, 158.13, -90.43, 164.54,
                                -86.32, 168.55);
    rr_renderer_bezier_curve_to(renderer, -82.21, 172.56, -80.03, 177.62,
                                -77.24, 177.86);
    rr_renderer_bezier_curve_to(renderer, -74.44, 178.09, -71.47, 173.14,
                                -69.54, 169.96);
    rr_renderer_bezier_curve_to(renderer, -67.61, 166.77, -65.53, 162.12,
                                -65.68, 158.72);
    rr_renderer_bezier_curve_to(renderer, -65.83, 155.32, -67.30, 152.68,
                                -70.44, 149.56);
    rr_renderer_fill(renderer);
}