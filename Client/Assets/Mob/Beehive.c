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

void rr_beehive_draw(struct rr_renderer *renderer)
{
    rr_renderer_set_fill(renderer, 0xff917319);
    rr_renderer_begin_path(renderer);
    rr_renderer_move_to(renderer, -129.47, 96.70);
    rr_renderer_line_to(renderer, 19.09, -160.42);
    rr_renderer_line_to(renderer, 129.47, -96.65);
    rr_renderer_line_to(renderer, -19.09, 160.47);
    rr_renderer_fill(renderer);
    rr_renderer_set_fill(renderer, 0xff917319);
    rr_renderer_begin_path(renderer);
    rr_renderer_move_to(renderer, -122.17, 122.14);
    rr_renderer_bezier_curve_to(renderer, -113.80, 107.64, -89.69, 105.91,
                                -68.31, 118.26);
    rr_renderer_bezier_curve_to(renderer, -46.94, 130.61, -36.40, 152.36,
                                -44.77, 166.86);
    rr_renderer_bezier_curve_to(renderer, -58.36, 140.34, -92.42, 120.66,
                                -122.17, 122.14);
    rr_renderer_fill(renderer);
    rr_renderer_set_fill(renderer, 0xff917319);
    rr_renderer_begin_path(renderer);
    rr_renderer_move_to(renderer, 122.17, -122.09);
    rr_renderer_bezier_curve_to(renderer, 113.80, -107.60, 89.68, -105.86,
                                68.31, -118.21);
    rr_renderer_bezier_curve_to(renderer, 46.94, -130.56, 36.40, -152.32, 44.77,
                                -166.81);
    rr_renderer_bezier_curve_to(renderer, 58.36, -140.29, 92.41, -120.61,
                                122.17, -122.09);
    rr_renderer_fill(renderer);
    rr_renderer_set_fill(renderer, 0xff917319);
    rr_renderer_begin_path(renderer);
    rr_renderer_move_to(renderer, -18.96, -160.44);
    rr_renderer_line_to(renderer, 129.39, 96.80);
    rr_renderer_line_to(renderer, 18.95, 160.49);
    rr_renderer_line_to(renderer, -129.40, -96.75);
    rr_renderer_fill(renderer);
    rr_renderer_set_fill(renderer, 0xff917319);
    rr_renderer_begin_path(renderer);
    rr_renderer_move_to(renderer, -44.64, -166.85);
    rr_renderer_bezier_curve_to(renderer, -36.28, -152.35, -46.84, -130.60,
                                -68.22, -118.27);
    rr_renderer_bezier_curve_to(renderer, -89.60, -105.93, -113.72, -107.69,
                                -122.08, -122.19);
    rr_renderer_bezier_curve_to(renderer, -92.32, -120.69, -58.25, -140.34,
                                -44.64, -166.85);
    rr_renderer_fill(renderer);
    rr_renderer_set_fill(renderer, 0xff917319);
    rr_renderer_begin_path(renderer);
    rr_renderer_move_to(renderer, 44.63, 166.89);
    rr_renderer_bezier_curve_to(renderer, 36.27, 152.39, 46.83, 130.64, 68.21,
                                118.31);
    rr_renderer_bezier_curve_to(renderer, 89.60, 105.98, 113.71, 107.73, 122.07,
                                122.23);
    rr_renderer_bezier_curve_to(renderer, 92.31, 120.73, 58.24, 140.38, 44.63,
                                166.89);
    rr_renderer_fill(renderer);
    rr_renderer_set_fill(renderer, 0xff917319);
    rr_renderer_begin_path(renderer);
    rr_renderer_move_to(renderer, -148.48, -63.74);
    rr_renderer_line_to(renderer, 148.46, -63.74);
    rr_renderer_line_to(renderer, 148.46, 63.74);
    rr_renderer_line_to(renderer, -148.48, 63.74);
    rr_renderer_fill(renderer);
    rr_renderer_set_fill(renderer, 0xff917319);
    rr_renderer_begin_path(renderer);
    rr_renderer_move_to(renderer, -166.85, -44.69);
    rr_renderer_bezier_curve_to(renderer, -150.12, -44.69, -136.55, -24.68,
                                -136.55, -0.00);
    rr_renderer_bezier_curve_to(renderer, -136.55, 24.68, -150.12, 44.69,
                                -166.85, 44.69);
    rr_renderer_bezier_curve_to(renderer, -150.69, 19.67, -150.69, -19.67,
                                -166.85, -44.69);
    rr_renderer_fill(renderer);
    rr_renderer_set_fill(renderer, 0xff917319);
    rr_renderer_begin_path(renderer);
    rr_renderer_move_to(renderer, 166.84, 44.69);
    rr_renderer_bezier_curve_to(renderer, 150.10, 44.69, 136.53, 24.68, 136.53,
                                -0.00);
    rr_renderer_bezier_curve_to(renderer, 136.53, -24.68, 150.10, -44.69,
                                166.84, -44.69);
    rr_renderer_bezier_curve_to(renderer, 150.67, -19.67, 150.67, 19.67, 166.84,
                                44.69);
    rr_renderer_fill(renderer);
    rr_renderer_set_fill(renderer, 0xffedbe2b);
    rr_renderer_begin_path(renderer);
    rr_renderer_move_to(renderer, -41.60, -131.79);
    rr_renderer_bezier_curve_to(renderer, -41.60, -154.76, -22.97, -173.39,
                                -0.00, -173.39);
    rr_renderer_bezier_curve_to(renderer, 11.03, -173.39, 21.61, -169.00, 29.41,
                                -161.20);
    rr_renderer_bezier_curve_to(renderer, 37.21, -153.40, 41.59, -142.82, 41.59,
                                -131.79);
    rr_renderer_bezier_curve_to(renderer, 41.59, -108.82, 22.97, -90.19, -0.00,
                                -90.19);
    rr_renderer_bezier_curve_to(renderer, -22.97, -90.19, -41.60, -108.82,
                                -41.60, -131.79);
    rr_renderer_fill(renderer);
    rr_renderer_set_fill(renderer, 0xffd0a51f);
    rr_renderer_begin_path(renderer);
    rr_renderer_move_to(renderer, -37.37, -174.63);
    rr_renderer_bezier_curve_to(renderer, -37.37, -181.72, -31.62, -187.46,
                                -24.54, -187.46);
    rr_renderer_bezier_curve_to(renderer, -21.13, -187.46, -17.87, -186.11,
                                -15.46, -183.70);
    rr_renderer_bezier_curve_to(renderer, -13.06, -181.30, -11.71, -178.03,
                                -11.71, -174.63);
    rr_renderer_bezier_curve_to(renderer, -11.71, -167.54, -17.45, -161.80,
                                -24.54, -161.80);
    rr_renderer_bezier_curve_to(renderer, -31.62, -161.80, -37.37, -167.54,
                                -37.37, -174.63);
    rr_renderer_fill(renderer);
    rr_renderer_set_fill(renderer, 0xffd0a51f);
    rr_renderer_begin_path(renderer);
    rr_renderer_move_to(renderer, 11.71, -174.63);
    rr_renderer_bezier_curve_to(renderer, 11.71, -181.72, 17.46, -187.46, 24.54,
                                -187.46);
    rr_renderer_bezier_curve_to(renderer, 27.94, -187.46, 31.21, -186.11, 33.61,
                                -183.70);
    rr_renderer_bezier_curve_to(renderer, 36.02, -181.30, 37.37, -178.03, 37.37,
                                -174.63);
    rr_renderer_bezier_curve_to(renderer, 37.37, -167.54, 31.63, -161.80, 24.54,
                                -161.80);
    rr_renderer_bezier_curve_to(renderer, 17.46, -161.80, 11.71, -167.54, 11.71,
                                -174.63);
    rr_renderer_fill(renderer);
    rr_renderer_set_fill(renderer, 0xffd0a51f);
    rr_renderer_begin_path(renderer);
    rr_renderer_move_to(renderer, -24.83, -187.46);
    rr_renderer_line_to(renderer, 24.83, -187.46);
    rr_renderer_line_to(renderer, 24.83, -161.80);
    rr_renderer_line_to(renderer, -24.83, -161.80);
    rr_renderer_fill(renderer);
    rr_renderer_set_fill(renderer, 0xffd0a51f);
    rr_renderer_begin_path(renderer);
    rr_renderer_move_to(renderer, 37.37, -88.95);
    rr_renderer_bezier_curve_to(renderer, 37.37, -81.86, 31.63, -76.12, 24.54,
                                -76.12);
    rr_renderer_bezier_curve_to(renderer, 21.14, -76.12, 17.87, -77.47, 15.47,
                                -79.88);
    rr_renderer_bezier_curve_to(renderer, 13.06, -82.28, 11.71, -85.55, 11.71,
                                -88.95);
    rr_renderer_bezier_curve_to(renderer, 11.71, -96.04, 17.46, -101.78, 24.54,
                                -101.78);
    rr_renderer_bezier_curve_to(renderer, 31.63, -101.78, 37.37, -96.04, 37.37,
                                -88.95);
    rr_renderer_fill(renderer);
    rr_renderer_set_fill(renderer, 0xffd0a51f);
    rr_renderer_begin_path(renderer);
    rr_renderer_move_to(renderer, -11.71, -88.95);
    rr_renderer_bezier_curve_to(renderer, -11.71, -81.86, -17.45, -76.12,
                                -24.54, -76.12);
    rr_renderer_bezier_curve_to(renderer, -27.94, -76.12, -31.20, -77.47,
                                -33.61, -79.88);
    rr_renderer_bezier_curve_to(renderer, -36.02, -82.28, -37.37, -85.55,
                                -37.37, -88.95);
    rr_renderer_bezier_curve_to(renderer, -37.37, -96.04, -31.62, -101.78,
                                -24.54, -101.78);
    rr_renderer_bezier_curve_to(renderer, -17.45, -101.78, -11.71, -96.04,
                                -11.71, -88.95);
    rr_renderer_fill(renderer);
    rr_renderer_set_fill(renderer, 0xffd0a51f);
    rr_renderer_begin_path(renderer);
    rr_renderer_move_to(renderer, 24.83, -76.12);
    rr_renderer_line_to(renderer, -24.83, -76.12);
    rr_renderer_line_to(renderer, -24.83, -101.73);
    rr_renderer_line_to(renderer, 24.83, -101.73);
    rr_renderer_fill(renderer);
    rr_renderer_set_fill(renderer, 0xffd0a51f);
    rr_renderer_begin_path(renderer);
    rr_renderer_move_to(renderer, 18.42, -185.57);
    rr_renderer_bezier_curve_to(renderer, 24.56, -189.11, 32.41, -187.01, 35.95,
                                -180.87);
    rr_renderer_bezier_curve_to(renderer, 37.65, -177.92, 38.11, -174.42, 37.23,
                                -171.13);
    rr_renderer_bezier_curve_to(renderer, 36.35, -167.85, 34.20, -165.05, 31.25,
                                -163.34);
    rr_renderer_bezier_curve_to(renderer, 25.11, -159.80, 17.27, -161.91, 13.72,
                                -168.04);
    rr_renderer_bezier_curve_to(renderer, 10.18, -174.18, 12.28, -182.03, 18.42,
                                -185.57);
    rr_renderer_fill(renderer);
    rr_renderer_set_fill(renderer, 0xffd0a51f);
    rr_renderer_begin_path(renderer);
    rr_renderer_move_to(renderer, 42.96, -143.06);
    rr_renderer_bezier_curve_to(renderer, 49.09, -146.61, 56.94, -144.50, 60.48,
                                -138.36);
    rr_renderer_bezier_curve_to(renderer, 62.18, -135.42, 62.65, -131.91, 61.76,
                                -128.63);
    rr_renderer_bezier_curve_to(renderer, 60.88, -125.34, 58.73, -122.54, 55.78,
                                -120.84);
    rr_renderer_bezier_curve_to(renderer, 49.65, -117.29, 41.80, -119.40, 38.26,
                                -125.54);
    rr_renderer_bezier_curve_to(renderer, 34.71, -131.67, 36.82, -139.52, 42.96,
                                -143.06);
    rr_renderer_fill(renderer);
    rr_renderer_set_fill(renderer, 0xffd0a51f);
    rr_renderer_begin_path(renderer);
    rr_renderer_move_to(renderer, 35.80, -181.12);
    rr_renderer_line_to(renderer, 60.63, -138.11);
    rr_renderer_line_to(renderer, 38.36, -125.26);
    rr_renderer_line_to(renderer, 13.53, -168.27);
    rr_renderer_fill(renderer);
    rr_renderer_set_fill(renderer, 0xffd0a51f);
    rr_renderer_begin_path(renderer);
    rr_renderer_move_to(renderer, -18.42, -78.01);
    rr_renderer_bezier_curve_to(renderer, -24.56, -74.46, -32.41, -76.57,
                                -35.95, -82.71);
    rr_renderer_bezier_curve_to(renderer, -37.65, -85.65, -38.11, -89.16,
                                -37.23, -92.44);
    rr_renderer_bezier_curve_to(renderer, -36.35, -95.73, -34.20, -98.53,
                                -31.25, -100.23);
    rr_renderer_bezier_curve_to(renderer, -25.11, -103.78, -17.26, -101.67,
                                -13.72, -95.53);
    rr_renderer_bezier_curve_to(renderer, -10.18, -89.40, -12.28, -81.55,
                                -18.42, -78.01);
    rr_renderer_fill(renderer);
    rr_renderer_set_fill(renderer, 0xffd0a51f);
    rr_renderer_begin_path(renderer);
    rr_renderer_move_to(renderer, -42.96, -120.51);
    rr_renderer_bezier_curve_to(renderer, -49.09, -116.97, -56.94, -119.07,
                                -60.48, -125.21);
    rr_renderer_bezier_curve_to(renderer, -62.18, -128.16, -62.64, -131.66,
                                -61.76, -134.95);
    rr_renderer_bezier_curve_to(renderer, -60.88, -138.24, -58.73, -141.04,
                                -55.78, -142.74);
    rr_renderer_bezier_curve_to(renderer, -49.65, -146.28, -41.80, -144.18,
                                -38.26, -138.04);
    rr_renderer_bezier_curve_to(renderer, -34.71, -131.90, -36.82, -124.06,
                                -42.96, -120.51);
    rr_renderer_fill(renderer);
    rr_renderer_set_fill(renderer, 0xffd0a51f);
    rr_renderer_begin_path(renderer);
    rr_renderer_move_to(renderer, -35.80, -82.45);
    rr_renderer_line_to(renderer, -60.63, -125.46);
    rr_renderer_line_to(renderer, -38.42, -138.28);
    rr_renderer_line_to(renderer, -13.60, -95.27);
    rr_renderer_fill(renderer);
    rr_renderer_set_fill(renderer, 0xffd0a51f);
    rr_renderer_begin_path(renderer);
    rr_renderer_move_to(renderer, -55.78, -120.84);
    rr_renderer_bezier_curve_to(renderer, -61.92, -124.39, -64.02, -132.23,
                                -60.48, -138.37);
    rr_renderer_bezier_curve_to(renderer, -58.78, -141.32, -55.98, -143.47,
                                -52.69, -144.35);
    rr_renderer_bezier_curve_to(renderer, -49.40, -145.23, -45.90, -144.77,
                                -42.95, -143.07);
    rr_renderer_bezier_curve_to(renderer, -36.82, -139.53, -34.71, -131.68,
                                -38.25, -125.54);
    rr_renderer_bezier_curve_to(renderer, -41.80, -119.40, -49.64, -117.30,
                                -55.78, -120.84);
    rr_renderer_fill(renderer);
    rr_renderer_set_fill(renderer, 0xffd0a51f);
    rr_renderer_begin_path(renderer);
    rr_renderer_move_to(renderer, -31.25, -163.35);
    rr_renderer_bezier_curve_to(renderer, -37.39, -166.89, -39.49, -174.74,
                                -35.95, -180.88);
    rr_renderer_bezier_curve_to(renderer, -34.25, -183.83, -31.44, -185.98,
                                -28.16, -186.86);
    rr_renderer_bezier_curve_to(renderer, -24.87, -187.74, -21.37, -187.28,
                                -18.42, -185.58);
    rr_renderer_bezier_curve_to(renderer, -12.28, -182.03, -10.18, -174.19,
                                -13.72, -168.05);
    rr_renderer_bezier_curve_to(renderer, -17.26, -161.91, -25.11, -159.81,
                                -31.25, -163.35);
    rr_renderer_fill(renderer);
    rr_renderer_set_fill(renderer, 0xffd0a51f);
    rr_renderer_begin_path(renderer);
    rr_renderer_move_to(renderer, -60.63, -138.12);
    rr_renderer_line_to(renderer, -35.80, -181.13);
    rr_renderer_line_to(renderer, -13.61, -168.32);
    rr_renderer_line_to(renderer, -38.44, -125.31);
    rr_renderer_fill(renderer);
    rr_renderer_set_fill(renderer, 0xffd0a51f);
    rr_renderer_begin_path(renderer);
    rr_renderer_move_to(renderer, 55.79, -142.75);
    rr_renderer_bezier_curve_to(renderer, 61.92, -139.20, 64.03, -131.36, 60.49,
                                -125.22);
    rr_renderer_bezier_curve_to(renderer, 58.78, -122.27, 55.98, -120.12, 52.69,
                                -119.24);
    rr_renderer_bezier_curve_to(renderer, 49.41, -118.36, 45.90, -118.82, 42.96,
                                -120.52);
    rr_renderer_bezier_curve_to(renderer, 36.82, -124.06, 34.72, -131.91, 38.26,
                                -138.05);
    rr_renderer_bezier_curve_to(renderer, 41.80, -144.19, 49.65, -146.29, 55.79,
                                -142.75);
    rr_renderer_fill(renderer);
    rr_renderer_set_fill(renderer, 0xffd0a51f);
    rr_renderer_begin_path(renderer);
    rr_renderer_move_to(renderer, 31.25, -100.24);
    rr_renderer_bezier_curve_to(renderer, 37.39, -96.70, 39.49, -88.85, 35.95,
                                -82.71);
    rr_renderer_bezier_curve_to(renderer, 34.25, -79.76, 31.45, -77.61, 28.16,
                                -76.73);
    rr_renderer_bezier_curve_to(renderer, 24.87, -75.85, 21.37, -76.31, 18.42,
                                -78.01);
    rr_renderer_bezier_curve_to(renderer, 12.29, -81.56, 10.18, -89.40, 13.72,
                                -95.54);
    rr_renderer_bezier_curve_to(renderer, 17.27, -101.68, 25.11, -103.78, 31.25,
                                -100.24);
    rr_renderer_fill(renderer);
    rr_renderer_set_fill(renderer, 0xffd0a51f);
    rr_renderer_begin_path(renderer);
    rr_renderer_move_to(renderer, 60.63, -125.47);
    rr_renderer_line_to(renderer, 35.81, -82.46);
    rr_renderer_line_to(renderer, 13.72, -95.21);
    rr_renderer_line_to(renderer, 38.54, -138.22);
    rr_renderer_fill(renderer);
    rr_renderer_set_fill(renderer, 0xffd0a51f);
    rr_renderer_begin_path(renderer);
    rr_renderer_move_to(renderer, -28.66, -121.34);
    rr_renderer_bezier_curve_to(renderer, -34.43, -121.34, -39.11, -126.02,
                                -39.11, -131.79);
    rr_renderer_bezier_curve_to(renderer, -39.11, -137.57, -34.43, -142.25,
                                -28.66, -142.25);
    rr_renderer_bezier_curve_to(renderer, -33.19, -136.01, -33.19, -127.57,
                                -28.66, -121.34);
    rr_renderer_fill(renderer);
    rr_renderer_set_fill(renderer, 0xffd0a51f);
    rr_renderer_begin_path(renderer);
    rr_renderer_move_to(renderer, 28.66, -142.25);
    rr_renderer_bezier_curve_to(renderer, 34.43, -142.25, 39.11, -137.57, 39.11,
                                -131.79);
    rr_renderer_bezier_curve_to(renderer, 39.11, -126.02, 34.43, -121.34, 28.66,
                                -121.34);
    rr_renderer_bezier_curve_to(renderer, 33.20, -127.57, 33.20, -136.01, 28.66,
                                -142.25);
    rr_renderer_fill(renderer);
    rr_renderer_set_fill(renderer, 0xffd0a51f);
    rr_renderer_begin_path(renderer);
    rr_renderer_move_to(renderer, -5.27, -101.74);
    rr_renderer_bezier_curve_to(renderer, -8.15, -96.75, -14.54, -95.03, -19.55,
                                -97.92);
    rr_renderer_bezier_curve_to(renderer, -24.55, -100.81, -26.27, -107.19,
                                -23.39, -112.19);
    rr_renderer_bezier_curve_to(renderer, -20.25, -105.15, -12.93, -100.93,
                                -5.27, -101.74);
    rr_renderer_fill(renderer);
    rr_renderer_set_fill(renderer, 0xffd0a51f);
    rr_renderer_begin_path(renderer);
    rr_renderer_move_to(renderer, 5.27, -161.84);
    rr_renderer_bezier_curve_to(renderer, 8.15, -166.84, 14.55, -168.55, 19.55,
                                -165.66);
    rr_renderer_bezier_curve_to(renderer, 24.55, -162.78, 26.27, -156.39, 23.39,
                                -151.39);
    rr_renderer_bezier_curve_to(renderer, 20.25, -158.43, 12.94, -162.65, 5.27,
                                -161.84);
    rr_renderer_fill(renderer);
    rr_renderer_set_fill(renderer, 0xffd0a51f);
    rr_renderer_begin_path(renderer);
    rr_renderer_move_to(renderer, -23.37, -151.40);
    rr_renderer_bezier_curve_to(renderer, -26.25, -156.40, -24.53, -162.80,
                                -19.53, -165.68);
    rr_renderer_bezier_curve_to(renderer, -14.53, -168.56, -8.14, -166.84,
                                -5.25, -161.84);
    rr_renderer_bezier_curve_to(renderer, -12.92, -162.66, -20.23, -158.44,
                                -23.37, -151.40);
    rr_renderer_fill(renderer);
    rr_renderer_set_fill(renderer, 0xffd0a51f);
    rr_renderer_begin_path(renderer);
    rr_renderer_move_to(renderer, 23.37, -112.18);
    rr_renderer_bezier_curve_to(renderer, 26.25, -107.18, 24.53, -100.79, 19.53,
                                -97.90);
    rr_renderer_bezier_curve_to(renderer, 14.53, -95.02, 8.14, -96.74, 5.26,
                                -101.74);
    rr_renderer_bezier_curve_to(renderer, 12.92, -100.92, 20.24, -105.14, 23.37,
                                -112.18);
    rr_renderer_fill(renderer);
    rr_renderer_set_fill(renderer, 0xffedbe2b);
    rr_renderer_begin_path(renderer);
    rr_renderer_move_to(renderer, 73.16, -65.89);
    rr_renderer_bezier_curve_to(renderer, 73.16, -88.87, 91.78, -107.49, 114.76,
                                -107.49);
    rr_renderer_bezier_curve_to(renderer, 125.79, -107.49, 136.37, -103.11,
                                144.17, -95.31);
    rr_renderer_bezier_curve_to(renderer, 151.97, -87.51, 156.35, -76.93,
                                156.35, -65.89);
    rr_renderer_bezier_curve_to(renderer, 156.35, -42.92, 137.73, -24.30,
                                114.76, -24.30);
    rr_renderer_bezier_curve_to(renderer, 91.78, -24.30, 73.16, -42.92, 73.16,
                                -65.89);
    rr_renderer_fill(renderer);
    rr_renderer_set_fill(renderer, 0xffd0a51f);
    rr_renderer_begin_path(renderer);
    rr_renderer_move_to(renderer, 77.39, -108.73);
    rr_renderer_bezier_curve_to(renderer, 77.39, -115.82, 83.13, -121.56, 90.22,
                                -121.56);
    rr_renderer_bezier_curve_to(renderer, 93.62, -121.56, 96.88, -120.21, 99.29,
                                -117.81);
    rr_renderer_bezier_curve_to(renderer, 101.70, -115.40, 103.05, -112.14,
                                103.05, -108.73);
    rr_renderer_bezier_curve_to(renderer, 103.05, -101.65, 97.30, -95.90, 90.22,
                                -95.90);
    rr_renderer_bezier_curve_to(renderer, 83.13, -95.90, 77.39, -101.65, 77.39,
                                -108.73);
    rr_renderer_fill(renderer);
    rr_renderer_set_fill(renderer, 0xffd0a51f);
    rr_renderer_begin_path(renderer);
    rr_renderer_move_to(renderer, 126.47, -108.73);
    rr_renderer_bezier_curve_to(renderer, 126.47, -115.82, 132.21, -121.56,
                                139.30, -121.56);
    rr_renderer_bezier_curve_to(renderer, 142.70, -121.56, 145.96, -120.21,
                                148.37, -117.81);
    rr_renderer_bezier_curve_to(renderer, 150.78, -115.40, 152.13, -112.14,
                                152.13, -108.73);
    rr_renderer_bezier_curve_to(renderer, 152.13, -101.65, 146.38, -95.90,
                                139.30, -95.90);
    rr_renderer_bezier_curve_to(renderer, 132.21, -95.90, 126.47, -101.65,
                                126.47, -108.73);
    rr_renderer_fill(renderer);
    rr_renderer_set_fill(renderer, 0xffd0a51f);
    rr_renderer_begin_path(renderer);
    rr_renderer_move_to(renderer, 89.93, -121.56);
    rr_renderer_line_to(renderer, 139.59, -121.56);
    rr_renderer_line_to(renderer, 139.59, -95.90);
    rr_renderer_line_to(renderer, 89.93, -95.90);
    rr_renderer_fill(renderer);
    rr_renderer_set_fill(renderer, 0xffd0a51f);
    rr_renderer_begin_path(renderer);
    rr_renderer_move_to(renderer, 152.13, -23.05);
    rr_renderer_bezier_curve_to(renderer, 152.13, -15.97, 146.38, -10.22,
                                139.30, -10.22);
    rr_renderer_bezier_curve_to(renderer, 135.89, -10.22, 132.63, -11.58,
                                130.22, -13.98);
    rr_renderer_bezier_curve_to(renderer, 127.82, -16.39, 126.47, -19.65,
                                126.47, -23.05);
    rr_renderer_bezier_curve_to(renderer, 126.47, -30.14, 132.21, -35.89,
                                139.30, -35.89);
    rr_renderer_bezier_curve_to(renderer, 146.38, -35.89, 152.13, -30.14,
                                152.13, -23.05);
    rr_renderer_fill(renderer);
    rr_renderer_set_fill(renderer, 0xffd0a51f);
    rr_renderer_begin_path(renderer);
    rr_renderer_move_to(renderer, 103.05, -23.05);
    rr_renderer_bezier_curve_to(renderer, 103.05, -15.97, 97.30, -10.22, 90.22,
                                -10.22);
    rr_renderer_bezier_curve_to(renderer, 86.82, -10.22, 83.55, -11.58, 81.14,
                                -13.98);
    rr_renderer_bezier_curve_to(renderer, 78.74, -16.39, 77.39, -19.65, 77.39,
                                -23.05);
    rr_renderer_bezier_curve_to(renderer, 77.39, -30.14, 83.13, -35.89, 90.22,
                                -35.89);
    rr_renderer_bezier_curve_to(renderer, 97.30, -35.89, 103.05, -30.14, 103.05,
                                -23.05);
    rr_renderer_fill(renderer);
    rr_renderer_set_fill(renderer, 0xffd0a51f);
    rr_renderer_begin_path(renderer);
    rr_renderer_move_to(renderer, 139.59, -10.22);
    rr_renderer_line_to(renderer, 89.93, -10.22);
    rr_renderer_line_to(renderer, 89.93, -35.84);
    rr_renderer_line_to(renderer, 139.59, -35.84);
    rr_renderer_fill(renderer);
    rr_renderer_set_fill(renderer, 0xffd0a51f);
    rr_renderer_begin_path(renderer);
    rr_renderer_move_to(renderer, 133.18, -119.67);
    rr_renderer_bezier_curve_to(renderer, 139.31, -123.22, 147.16, -121.11,
                                150.70, -114.98);
    rr_renderer_bezier_curve_to(renderer, 152.41, -112.03, 152.87, -108.53,
                                151.98, -105.24);
    rr_renderer_bezier_curve_to(renderer, 151.10, -101.95, 148.95, -99.15,
                                146.01, -97.45);
    rr_renderer_bezier_curve_to(renderer, 139.87, -93.91, 132.02, -96.01,
                                128.48, -102.15);
    rr_renderer_bezier_curve_to(renderer, 124.94, -108.28, 127.04, -116.13,
                                133.18, -119.67);
    rr_renderer_fill(renderer);
    rr_renderer_set_fill(renderer, 0xffd0a51f);
    rr_renderer_begin_path(renderer);
    rr_renderer_move_to(renderer, 157.71, -77.17);
    rr_renderer_bezier_curve_to(renderer, 163.85, -80.71, 171.70, -78.61,
                                175.24, -72.47);
    rr_renderer_bezier_curve_to(renderer, 176.94, -69.52, 177.40, -66.02,
                                176.52, -62.73);
    rr_renderer_bezier_curve_to(renderer, 175.64, -59.44, 173.49, -56.64,
                                170.54, -54.94);
    rr_renderer_bezier_curve_to(renderer, 164.40, -51.40, 156.55, -53.50,
                                153.01, -59.64);
    rr_renderer_bezier_curve_to(renderer, 149.47, -65.78, 151.57, -73.62,
                                157.71, -77.17);
    rr_renderer_fill(renderer);
    rr_renderer_set_fill(renderer, 0xffd0a51f);
    rr_renderer_begin_path(renderer);
    rr_renderer_move_to(renderer, 150.56, -115.23);
    rr_renderer_line_to(renderer, 175.38, -72.22);
    rr_renderer_line_to(renderer, 153.11, -59.36);
    rr_renderer_line_to(renderer, 128.29, -102.37);
    rr_renderer_fill(renderer);
    rr_renderer_set_fill(renderer, 0xffd0a51f);
    rr_renderer_begin_path(renderer);
    rr_renderer_move_to(renderer, 96.33, -12.11);
    rr_renderer_bezier_curve_to(renderer, 90.20, -8.57, 82.35, -10.67, 78.81,
                                -16.81);
    rr_renderer_bezier_curve_to(renderer, 77.11, -19.76, 76.64, -23.26, 77.53,
                                -26.55);
    rr_renderer_bezier_curve_to(renderer, 78.41, -29.83, 80.56, -32.64, 83.51,
                                -34.34);
    rr_renderer_bezier_curve_to(renderer, 89.64, -37.88, 97.49, -35.78, 101.03,
                                -29.64);
    rr_renderer_bezier_curve_to(renderer, 104.58, -23.50, 102.47, -15.65, 96.33,
                                -12.11);
    rr_renderer_fill(renderer);
    rr_renderer_set_fill(renderer, 0xffd0a51f);
    rr_renderer_begin_path(renderer);
    rr_renderer_move_to(renderer, 71.80, -54.62);
    rr_renderer_bezier_curve_to(renderer, 65.66, -51.07, 57.81, -53.18, 54.27,
                                -59.32);
    rr_renderer_bezier_curve_to(renderer, 52.57, -62.26, 52.11, -65.77, 52.99,
                                -69.05);
    rr_renderer_bezier_curve_to(renderer, 53.87, -72.34, 56.02, -75.14, 58.97,
                                -76.84);
    rr_renderer_bezier_curve_to(renderer, 65.11, -80.39, 72.96, -78.28, 76.50,
                                -72.14);
    rr_renderer_bezier_curve_to(renderer, 80.04, -66.01, 77.94, -58.16, 71.80,
                                -54.62);
    rr_renderer_fill(renderer);
    rr_renderer_set_fill(renderer, 0xffd0a51f);
    rr_renderer_begin_path(renderer);
    rr_renderer_move_to(renderer, 78.95, -16.56);
    rr_renderer_line_to(renderer, 54.13, -59.57);
    rr_renderer_line_to(renderer, 76.33, -72.39);
    rr_renderer_line_to(renderer, 101.16, -29.38);
    rr_renderer_fill(renderer);
    rr_renderer_set_fill(renderer, 0xffd0a51f);
    rr_renderer_begin_path(renderer);
    rr_renderer_move_to(renderer, 58.97, -54.95);
    rr_renderer_bezier_curve_to(renderer, 52.84, -58.49, 50.73, -66.34, 54.27,
                                -72.47);
    rr_renderer_bezier_curve_to(renderer, 55.98, -75.42, 58.78, -77.57, 62.06,
                                -78.45);
    rr_renderer_bezier_curve_to(renderer, 65.35, -79.34, 68.85, -78.87, 71.80,
                                -77.17);
    rr_renderer_bezier_curve_to(renderer, 77.94, -73.63, 80.04, -65.78, 76.50,
                                -59.65);
    rr_renderer_bezier_curve_to(renderer, 72.96, -53.51, 65.11, -51.40, 58.97,
                                -54.95);
    rr_renderer_fill(renderer);
    rr_renderer_set_fill(renderer, 0xffd0a51f);
    rr_renderer_begin_path(renderer);
    rr_renderer_move_to(renderer, 83.51, -97.45);
    rr_renderer_bezier_curve_to(renderer, 77.37, -101.00, 75.27, -108.84, 78.81,
                                -114.98);
    rr_renderer_bezier_curve_to(renderer, 80.51, -117.93, 83.31, -120.08, 86.60,
                                -120.96);
    rr_renderer_bezier_curve_to(renderer, 89.89, -121.84, 93.39, -121.38, 96.34,
                                -119.68);
    rr_renderer_bezier_curve_to(renderer, 102.47, -116.14, 104.58, -108.29,
                                101.03, -102.15);
    rr_renderer_bezier_curve_to(renderer, 97.49, -96.02, 89.65, -93.91, 83.51,
                                -97.45);
    rr_renderer_fill(renderer);
    rr_renderer_set_fill(renderer, 0xffd0a51f);
    rr_renderer_begin_path(renderer);
    rr_renderer_move_to(renderer, 54.13, -72.22);
    rr_renderer_line_to(renderer, 78.95, -115.23);
    rr_renderer_line_to(renderer, 101.14, -102.43);
    rr_renderer_line_to(renderer, 76.32, -59.42);
    rr_renderer_fill(renderer);
    rr_renderer_set_fill(renderer, 0xffd0a51f);
    rr_renderer_begin_path(renderer);
    rr_renderer_move_to(renderer, 170.54, -76.85);
    rr_renderer_bezier_curve_to(renderer, 176.68, -73.31, 178.78, -65.46,
                                175.24, -59.32);
    rr_renderer_bezier_curve_to(renderer, 173.54, -56.38, 170.74, -54.22,
                                167.45, -53.34);
    rr_renderer_bezier_curve_to(renderer, 164.16, -52.46, 160.66, -52.92,
                                157.71, -54.62);
    rr_renderer_bezier_curve_to(renderer, 151.58, -58.17, 149.47, -66.01,
                                153.01, -72.15);
    rr_renderer_bezier_curve_to(renderer, 156.56, -78.29, 164.40, -80.39,
                                170.54, -76.85);
    rr_renderer_fill(renderer);
    rr_renderer_set_fill(renderer, 0xffd0a51f);
    rr_renderer_begin_path(renderer);
    rr_renderer_move_to(renderer, 146.01, -34.34);
    rr_renderer_bezier_curve_to(renderer, 152.14, -30.80, 154.25, -22.95,
                                150.71, -16.82);
    rr_renderer_bezier_curve_to(renderer, 149.00, -13.87, 146.20, -11.72,
                                142.92, -10.84);
    rr_renderer_bezier_curve_to(renderer, 139.63, -9.95, 136.13, -10.42, 133.18,
                                -12.12);
    rr_renderer_bezier_curve_to(renderer, 127.04, -15.66, 124.94, -23.51,
                                128.48, -29.64);
    rr_renderer_bezier_curve_to(renderer, 132.02, -35.78, 139.87, -37.89,
                                146.01, -34.34);
    rr_renderer_fill(renderer);
    rr_renderer_set_fill(renderer, 0xffd0a51f);
    rr_renderer_begin_path(renderer);
    rr_renderer_move_to(renderer, 175.39, -59.57);
    rr_renderer_line_to(renderer, 150.56, -16.56);
    rr_renderer_line_to(renderer, 128.47, -29.31);
    rr_renderer_line_to(renderer, 153.30, -72.32);
    rr_renderer_fill(renderer);
    rr_renderer_set_fill(renderer, 0xffd0a51f);
    rr_renderer_begin_path(renderer);
    rr_renderer_move_to(renderer, 86.10, -55.44);
    rr_renderer_bezier_curve_to(renderer, 80.32, -55.44, 75.65, -60.12, 75.65,
                                -65.90);
    rr_renderer_bezier_curve_to(renderer, 75.65, -71.67, 80.32, -76.35, 86.10,
                                -76.35);
    rr_renderer_bezier_curve_to(renderer, 81.56, -70.12, 81.56, -61.67, 86.10,
                                -55.44);
    rr_renderer_fill(renderer);
    rr_renderer_set_fill(renderer, 0xffd0a51f);
    rr_renderer_begin_path(renderer);
    rr_renderer_move_to(renderer, 143.42, -76.35);
    rr_renderer_bezier_curve_to(renderer, 149.19, -76.35, 153.87, -71.67,
                                153.87, -65.90);
    rr_renderer_bezier_curve_to(renderer, 153.87, -60.12, 149.19, -55.44,
                                143.42, -55.44);
    rr_renderer_bezier_curve_to(renderer, 147.95, -61.67, 147.95, -70.12,
                                143.42, -76.35);
    rr_renderer_fill(renderer);
    rr_renderer_set_fill(renderer, 0xffd0a51f);
    rr_renderer_begin_path(renderer);
    rr_renderer_move_to(renderer, 109.49, -35.85);
    rr_renderer_bezier_curve_to(renderer, 106.60, -30.85, 100.21, -29.14, 95.21,
                                -32.02);
    rr_renderer_bezier_curve_to(renderer, 90.21, -34.91, 88.49, -41.30, 91.37,
                                -46.30);
    rr_renderer_bezier_curve_to(renderer, 94.50, -39.26, 101.82, -35.03, 109.49,
                                -35.85);
    rr_renderer_fill(renderer);
    rr_renderer_set_fill(renderer, 0xffd0a51f);
    rr_renderer_begin_path(renderer);
    rr_renderer_move_to(renderer, 120.03, -95.94);
    rr_renderer_bezier_curve_to(renderer, 122.91, -100.94, 129.30, -102.65,
                                134.30, -99.77);
    rr_renderer_bezier_curve_to(renderer, 139.31, -96.88, 141.03, -90.49,
                                138.14, -85.50);
    rr_renderer_bezier_curve_to(renderer, 135.01, -92.53, 127.69, -96.76,
                                120.03, -95.94);
    rr_renderer_fill(renderer);
    rr_renderer_set_fill(renderer, 0xffd0a51f);
    rr_renderer_begin_path(renderer);
    rr_renderer_move_to(renderer, 91.39, -85.50);
    rr_renderer_bezier_curve_to(renderer, 88.50, -90.51, 90.22, -96.90, 95.22,
                                -99.78);
    rr_renderer_bezier_curve_to(renderer, 100.23, -102.66, 106.62, -100.95,
                                109.50, -95.94);
    rr_renderer_bezier_curve_to(renderer, 101.84, -96.76, 94.52, -92.55, 91.39,
                                -85.50);
    rr_renderer_fill(renderer);
    rr_renderer_set_fill(renderer, 0xffd0a51f);
    rr_renderer_begin_path(renderer);
    rr_renderer_move_to(renderer, 138.13, -46.29);
    rr_renderer_bezier_curve_to(renderer, 141.01, -41.28, 139.29, -34.89,
                                134.29, -32.01);
    rr_renderer_bezier_curve_to(renderer, 129.28, -29.13, 122.89, -30.84,
                                120.01, -35.85);
    rr_renderer_bezier_curve_to(renderer, 127.67, -35.03, 134.99, -39.24,
                                138.13, -46.29);
    rr_renderer_fill(renderer);
    rr_renderer_set_fill(renderer, 0xffedbe2b);
    rr_renderer_begin_path(renderer);
    rr_renderer_move_to(renderer, -41.60, 131.79);
    rr_renderer_bezier_curve_to(renderer, -41.60, 108.82, -22.97, 90.20, -0.00,
                                90.20);
    rr_renderer_bezier_curve_to(renderer, 11.03, 90.20, 21.61, 94.58, 29.41,
                                102.38);
    rr_renderer_bezier_curve_to(renderer, 37.21, 110.18, 41.59, 120.76, 41.59,
                                131.79);
    rr_renderer_bezier_curve_to(renderer, 41.59, 154.77, 22.97, 173.39, -0.00,
                                173.39);
    rr_renderer_bezier_curve_to(renderer, -22.97, 173.39, -41.60, 154.77,
                                -41.60, 131.79);
    rr_renderer_fill(renderer);
    rr_renderer_set_fill(renderer, 0xffd0a51f);
    rr_renderer_begin_path(renderer);
    rr_renderer_move_to(renderer, -37.37, 88.96);
    rr_renderer_bezier_curve_to(renderer, -37.37, 81.87, -31.62, 76.12, -24.54,
                                76.12);
    rr_renderer_bezier_curve_to(renderer, -21.13, 76.12, -17.87, 77.48, -15.46,
                                79.88);
    rr_renderer_bezier_curve_to(renderer, -13.06, 82.29, -11.71, 85.55, -11.71,
                                88.96);
    rr_renderer_bezier_curve_to(renderer, -11.71, 96.04, -17.45, 101.79, -24.54,
                                101.79);
    rr_renderer_bezier_curve_to(renderer, -31.62, 101.79, -37.37, 96.04, -37.37,
                                88.96);
    rr_renderer_fill(renderer);
    rr_renderer_set_fill(renderer, 0xffd0a51f);
    rr_renderer_begin_path(renderer);
    rr_renderer_move_to(renderer, 11.71, 88.96);
    rr_renderer_bezier_curve_to(renderer, 11.71, 81.87, 17.45, 76.12, 24.54,
                                76.12);
    rr_renderer_bezier_curve_to(renderer, 27.94, 76.12, 31.21, 77.48, 33.61,
                                79.88);
    rr_renderer_bezier_curve_to(renderer, 36.02, 82.29, 37.37, 85.55, 37.37,
                                88.96);
    rr_renderer_bezier_curve_to(renderer, 37.37, 96.04, 31.63, 101.79, 24.54,
                                101.79);
    rr_renderer_bezier_curve_to(renderer, 17.45, 101.79, 11.71, 96.04, 11.71,
                                88.96);
    rr_renderer_fill(renderer);
    rr_renderer_set_fill(renderer, 0xffd0a51f);
    rr_renderer_begin_path(renderer);
    rr_renderer_move_to(renderer, -24.83, 76.12);
    rr_renderer_line_to(renderer, 24.83, 76.12);
    rr_renderer_line_to(renderer, 24.83, 101.79);
    rr_renderer_line_to(renderer, -24.83, 101.79);
    rr_renderer_fill(renderer);
    rr_renderer_set_fill(renderer, 0xffd0a51f);
    rr_renderer_begin_path(renderer);
    rr_renderer_move_to(renderer, 37.37, 174.63);
    rr_renderer_bezier_curve_to(renderer, 37.37, 181.72, 31.63, 187.47, 24.54,
                                187.47);
    rr_renderer_bezier_curve_to(renderer, 21.14, 187.47, 17.87, 186.11, 15.47,
                                183.71);
    rr_renderer_bezier_curve_to(renderer, 13.06, 181.30, 11.71, 178.04, 11.71,
                                174.63);
    rr_renderer_bezier_curve_to(renderer, 11.71, 167.55, 17.45, 161.80, 24.54,
                                161.80);
    rr_renderer_bezier_curve_to(renderer, 31.63, 161.80, 37.37, 167.55, 37.37,
                                174.63);
    rr_renderer_fill(renderer);
    rr_renderer_set_fill(renderer, 0xffd0a51f);
    rr_renderer_begin_path(renderer);
    rr_renderer_move_to(renderer, -11.71, 174.63);
    rr_renderer_bezier_curve_to(renderer, -11.71, 181.72, -17.45, 187.47,
                                -24.54, 187.47);
    rr_renderer_bezier_curve_to(renderer, -27.94, 187.47, -31.20, 186.11,
                                -33.61, 183.71);
    rr_renderer_bezier_curve_to(renderer, -36.02, 181.30, -37.37, 178.04,
                                -37.37, 174.63);
    rr_renderer_bezier_curve_to(renderer, -37.37, 167.55, -31.62, 161.80,
                                -24.54, 161.80);
    rr_renderer_bezier_curve_to(renderer, -17.45, 161.80, -11.71, 167.55,
                                -11.71, 174.63);
    rr_renderer_fill(renderer);
    rr_renderer_set_fill(renderer, 0xffd0a51f);
    rr_renderer_begin_path(renderer);
    rr_renderer_move_to(renderer, 24.83, 187.46);
    rr_renderer_line_to(renderer, -24.83, 187.46);
    rr_renderer_line_to(renderer, -24.83, 161.85);
    rr_renderer_line_to(renderer, 24.83, 161.85);
    rr_renderer_fill(renderer);
    rr_renderer_set_fill(renderer, 0xffd0a51f);
    rr_renderer_begin_path(renderer);
    rr_renderer_move_to(renderer, 18.42, 78.01);
    rr_renderer_bezier_curve_to(renderer, 24.56, 74.47, 32.41, 76.58, 35.95,
                                82.71);
    rr_renderer_bezier_curve_to(renderer, 37.65, 85.66, 38.11, 89.16, 37.23,
                                92.45);
    rr_renderer_bezier_curve_to(renderer, 36.35, 95.74, 34.20, 98.54, 31.25,
                                100.24);
    rr_renderer_bezier_curve_to(renderer, 25.11, 103.78, 17.26, 101.68, 13.72,
                                95.54);
    rr_renderer_bezier_curve_to(renderer, 10.18, 89.40, 12.28, 81.56, 18.42,
                                78.01);
    rr_renderer_fill(renderer);
    rr_renderer_set_fill(renderer, 0xffd0a51f);
    rr_renderer_begin_path(renderer);
    rr_renderer_move_to(renderer, 42.96, 120.52);
    rr_renderer_bezier_curve_to(renderer, 49.09, 116.98, 56.94, 119.08, 60.48,
                                125.22);
    rr_renderer_bezier_curve_to(renderer, 62.18, 128.17, 62.64, 131.67, 61.76,
                                134.96);
    rr_renderer_bezier_curve_to(renderer, 60.88, 138.24, 58.73, 141.05, 55.78,
                                142.75);
    rr_renderer_bezier_curve_to(renderer, 49.65, 146.29, 41.80, 144.19, 38.26,
                                138.05);
    rr_renderer_bezier_curve_to(renderer, 34.71, 131.91, 36.82, 124.06, 42.96,
                                120.52);
    rr_renderer_fill(renderer);
    rr_renderer_set_fill(renderer, 0xffd0a51f);
    rr_renderer_begin_path(renderer);
    rr_renderer_move_to(renderer, 35.80, 82.46);
    rr_renderer_line_to(renderer, 60.63, 125.47);
    rr_renderer_line_to(renderer, 38.36, 138.33);
    rr_renderer_line_to(renderer, 13.53, 95.32);
    rr_renderer_fill(renderer);
    rr_renderer_set_fill(renderer, 0xffd0a51f);
    rr_renderer_begin_path(renderer);
    rr_renderer_move_to(renderer, -18.42, 185.58);
    rr_renderer_bezier_curve_to(renderer, -24.56, 189.12, -32.41, 187.02,
                                -35.95, 180.88);
    rr_renderer_bezier_curve_to(renderer, -37.65, 177.93, -38.11, 174.43,
                                -37.23, 171.14);
    rr_renderer_bezier_curve_to(renderer, -36.35, 167.86, -34.20, 165.05,
                                -31.25, 163.35);
    rr_renderer_bezier_curve_to(renderer, -25.11, 159.81, -17.27, 161.91,
                                -13.72, 168.05);
    rr_renderer_bezier_curve_to(renderer, -10.18, 174.19, -12.28, 182.04,
                                -18.42, 185.58);
    rr_renderer_fill(renderer);
    rr_renderer_set_fill(renderer, 0xffd0a51f);
    rr_renderer_begin_path(renderer);
    rr_renderer_move_to(renderer, -42.96, 143.07);
    rr_renderer_bezier_curve_to(renderer, -49.09, 146.61, -56.94, 144.51,
                                -60.48, 138.37);
    rr_renderer_bezier_curve_to(renderer, -62.18, 135.42, -62.65, 131.92,
                                -61.76, 128.64);
    rr_renderer_bezier_curve_to(renderer, -60.88, 125.35, -58.73, 122.55,
                                -55.78, 120.84);
    rr_renderer_bezier_curve_to(renderer, -49.65, 117.30, -41.80, 119.41,
                                -38.26, 125.54);
    rr_renderer_bezier_curve_to(renderer, -34.71, 131.68, -36.82, 139.53,
                                -42.96, 143.07);
    rr_renderer_fill(renderer);
    rr_renderer_set_fill(renderer, 0xffd0a51f);
    rr_renderer_begin_path(renderer);
    rr_renderer_move_to(renderer, -35.80, 181.13);
    rr_renderer_line_to(renderer, -60.63, 138.12);
    rr_renderer_line_to(renderer, -38.42, 125.30);
    rr_renderer_line_to(renderer, -13.60, 168.31);
    rr_renderer_fill(renderer);
    rr_renderer_set_fill(renderer, 0xffd0a51f);
    rr_renderer_begin_path(renderer);
    rr_renderer_move_to(renderer, -55.78, 142.74);
    rr_renderer_bezier_curve_to(renderer, -61.92, 139.20, -64.02, 131.35,
                                -60.48, 125.21);
    rr_renderer_bezier_curve_to(renderer, -58.78, 122.27, -55.98, 120.12,
                                -52.69, 119.23);
    rr_renderer_bezier_curve_to(renderer, -49.40, 118.35, -45.90, 118.81,
                                -42.95, 120.51);
    rr_renderer_bezier_curve_to(renderer, -36.82, 124.06, -34.71, 131.90,
                                -38.26, 138.04);
    rr_renderer_bezier_curve_to(renderer, -41.80, 144.18, -49.65, 146.28,
                                -55.78, 142.74);
    rr_renderer_fill(renderer);
    rr_renderer_set_fill(renderer, 0xffd0a51f);
    rr_renderer_begin_path(renderer);
    rr_renderer_move_to(renderer, -31.25, 100.23);
    rr_renderer_bezier_curve_to(renderer, -37.39, 96.69, -39.49, 88.84, -35.95,
                                82.71);
    rr_renderer_bezier_curve_to(renderer, -34.25, 79.76, -31.44, 77.61, -28.16,
                                76.73);
    rr_renderer_bezier_curve_to(renderer, -24.87, 75.85, -21.37, 76.31, -18.42,
                                78.01);
    rr_renderer_bezier_curve_to(renderer, -12.28, 81.55, -10.18, 89.40, -13.72,
                                95.54);
    rr_renderer_bezier_curve_to(renderer, -17.26, 101.67, -25.11, 103.78,
                                -31.25, 100.23);
    rr_renderer_fill(renderer);
    rr_renderer_set_fill(renderer, 0xffd0a51f);
    rr_renderer_begin_path(renderer);
    rr_renderer_move_to(renderer, -60.63, 125.46);
    rr_renderer_line_to(renderer, -35.80, 82.45);
    rr_renderer_line_to(renderer, -13.61, 95.26);
    rr_renderer_line_to(renderer, -38.44, 138.27);
    rr_renderer_fill(renderer);
    rr_renderer_set_fill(renderer, 0xffd0a51f);
    rr_renderer_begin_path(renderer);
    rr_renderer_move_to(renderer, 55.79, 120.84);
    rr_renderer_bezier_curve_to(renderer, 61.92, 124.38, 64.03, 132.23, 60.48,
                                138.37);
    rr_renderer_bezier_curve_to(renderer, 58.78, 141.31, 55.98, 143.46, 52.69,
                                144.35);
    rr_renderer_bezier_curve_to(renderer, 49.41, 145.23, 45.90, 144.77, 42.96,
                                143.06);
    rr_renderer_bezier_curve_to(renderer, 36.82, 139.52, 34.72, 131.67, 38.26,
                                125.54);
    rr_renderer_bezier_curve_to(renderer, 41.80, 119.40, 49.65, 117.30, 55.79,
                                120.84);
    rr_renderer_fill(renderer);
    rr_renderer_set_fill(renderer, 0xffd0a51f);
    rr_renderer_begin_path(renderer);
    rr_renderer_move_to(renderer, 31.25, 163.35);
    rr_renderer_bezier_curve_to(renderer, 37.39, 166.89, 39.49, 174.74, 35.95,
                                180.87);
    rr_renderer_bezier_curve_to(renderer, 34.25, 183.82, 31.45, 185.97, 28.16,
                                186.85);
    rr_renderer_bezier_curve_to(renderer, 24.87, 187.73, 21.37, 187.27, 18.42,
                                185.57);
    rr_renderer_bezier_curve_to(renderer, 12.28, 182.03, 10.18, 174.18, 13.72,
                                168.04);
    rr_renderer_bezier_curve_to(renderer, 17.27, 161.91, 25.11, 159.80, 31.25,
                                163.35);
    rr_renderer_fill(renderer);
    rr_renderer_set_fill(renderer, 0xffd0a51f);
    rr_renderer_begin_path(renderer);
    rr_renderer_move_to(renderer, 60.63, 138.11);
    rr_renderer_line_to(renderer, 35.80, 181.12);
    rr_renderer_line_to(renderer, 13.72, 168.38);
    rr_renderer_line_to(renderer, 38.54, 125.37);
    rr_renderer_fill(renderer);
    rr_renderer_set_fill(renderer, 0xffd0a51f);
    rr_renderer_begin_path(renderer);
    rr_renderer_move_to(renderer, -28.66, 142.25);
    rr_renderer_bezier_curve_to(renderer, -34.43, 142.25, -39.11, 137.57,
                                -39.11, 131.79);
    rr_renderer_bezier_curve_to(renderer, -39.11, 126.02, -34.43, 121.34,
                                -28.66, 121.34);
    rr_renderer_bezier_curve_to(renderer, -33.19, 127.57, -33.19, 136.02,
                                -28.66, 142.25);
    rr_renderer_fill(renderer);
    rr_renderer_set_fill(renderer, 0xffd0a51f);
    rr_renderer_begin_path(renderer);
    rr_renderer_move_to(renderer, 28.66, 121.34);
    rr_renderer_bezier_curve_to(renderer, 34.43, 121.34, 39.11, 126.02, 39.11,
                                131.79);
    rr_renderer_bezier_curve_to(renderer, 39.11, 137.57, 34.43, 142.25, 28.66,
                                142.25);
    rr_renderer_bezier_curve_to(renderer, 33.19, 136.02, 33.19, 127.57, 28.66,
                                121.34);
    rr_renderer_fill(renderer);
    rr_renderer_set_fill(renderer, 0xffd0a51f);
    rr_renderer_begin_path(renderer);
    rr_renderer_move_to(renderer, -5.27, 161.84);
    rr_renderer_bezier_curve_to(renderer, -8.15, 166.84, -14.55, 168.55, -19.55,
                                165.66);
    rr_renderer_bezier_curve_to(renderer, -24.55, 162.78, -26.27, 156.39,
                                -23.39, 151.39);
    rr_renderer_bezier_curve_to(renderer, -20.25, 158.43, -12.93, 162.65, -5.27,
                                161.84);
    rr_renderer_fill(renderer);
    rr_renderer_set_fill(renderer, 0xffd0a51f);
    rr_renderer_begin_path(renderer);
    rr_renderer_move_to(renderer, 5.27, 101.74);
    rr_renderer_bezier_curve_to(renderer, 8.15, 96.75, 14.55, 95.04, 19.55,
                                97.92);
    rr_renderer_bezier_curve_to(renderer, 24.55, 100.81, 26.27, 107.20, 23.39,
                                112.19);
    rr_renderer_bezier_curve_to(renderer, 20.25, 105.15, 12.94, 100.93, 5.27,
                                101.74);
    rr_renderer_fill(renderer);
    rr_renderer_set_fill(renderer, 0xffd0a51f);
    rr_renderer_begin_path(renderer);
    rr_renderer_move_to(renderer, -23.37, 112.18);
    rr_renderer_bezier_curve_to(renderer, -26.25, 107.18, -24.53, 100.79,
                                -19.53, 97.91);
    rr_renderer_bezier_curve_to(renderer, -14.53, 95.02, -8.14, 96.74, -5.25,
                                101.75);
    rr_renderer_bezier_curve_to(renderer, -12.92, 100.93, -20.24, 105.14,
                                -23.37, 112.18);
    rr_renderer_fill(renderer);
    rr_renderer_set_fill(renderer, 0xffd0a51f);
    rr_renderer_begin_path(renderer);
    rr_renderer_move_to(renderer, 23.37, 151.40);
    rr_renderer_bezier_curve_to(renderer, 26.25, 156.41, 24.53, 162.80, 19.53,
                                165.68);
    rr_renderer_bezier_curve_to(renderer, 14.53, 168.56, 8.14, 166.84, 5.25,
                                161.84);
    rr_renderer_bezier_curve_to(renderer, 12.92, 162.66, 20.24, 158.44, 23.37,
                                151.40);
    rr_renderer_fill(renderer);
    rr_renderer_set_fill(renderer, 0xffedbe2b);
    rr_renderer_begin_path(renderer);
    rr_renderer_move_to(renderer, 73.16, 65.90);
    rr_renderer_bezier_curve_to(renderer, 73.16, 42.92, 91.78, 24.30, 114.75,
                                24.30);
    rr_renderer_bezier_curve_to(renderer, 125.79, 24.30, 136.37, 28.68, 144.17,
                                36.48);
    rr_renderer_bezier_curve_to(renderer, 151.97, 44.29, 156.35, 54.87, 156.35,
                                65.90);
    rr_renderer_bezier_curve_to(renderer, 156.35, 88.87, 137.73, 107.49, 114.75,
                                107.49);
    rr_renderer_bezier_curve_to(renderer, 91.78, 107.49, 73.16, 88.87, 73.16,
                                65.90);
    rr_renderer_fill(renderer);
    rr_renderer_set_fill(renderer, 0xffd0a51f);
    rr_renderer_begin_path(renderer);
    rr_renderer_move_to(renderer, 77.39, 23.26);
    rr_renderer_bezier_curve_to(renderer, 77.39, 16.17, 83.13, 10.43, 90.22,
                                10.43);
    rr_renderer_bezier_curve_to(renderer, 93.62, 10.43, 96.89, 11.78, 99.29,
                                14.19);
    rr_renderer_bezier_curve_to(renderer, 101.70, 16.59, 103.05, 19.86, 103.05,
                                23.26);
    rr_renderer_bezier_curve_to(renderer, 103.05, 30.34, 97.31, 36.09, 90.22,
                                36.09);
    rr_renderer_bezier_curve_to(renderer, 83.13, 36.09, 77.39, 30.34, 77.39,
                                23.26);
    rr_renderer_fill(renderer);
    rr_renderer_set_fill(renderer, 0xffd0a51f);
    rr_renderer_begin_path(renderer);
    rr_renderer_move_to(renderer, 126.47, 23.26);
    rr_renderer_bezier_curve_to(renderer, 126.47, 16.17, 132.21, 10.43, 139.30,
                                10.43);
    rr_renderer_bezier_curve_to(renderer, 142.70, 10.43, 145.96, 11.78, 148.37,
                                14.19);
    rr_renderer_bezier_curve_to(renderer, 150.78, 16.59, 152.13, 19.86, 152.13,
                                23.26);
    rr_renderer_bezier_curve_to(renderer, 152.13, 30.34, 146.38, 36.09, 139.30,
                                36.09);
    rr_renderer_bezier_curve_to(renderer, 132.21, 36.09, 126.47, 30.34, 126.47,
                                23.26);
    rr_renderer_fill(renderer);
    rr_renderer_set_fill(renderer, 0xffd0a51f);
    rr_renderer_begin_path(renderer);
    rr_renderer_move_to(renderer, 89.93, 10.43);
    rr_renderer_line_to(renderer, 139.59, 10.43);
    rr_renderer_line_to(renderer, 139.59, 36.09);
    rr_renderer_line_to(renderer, 89.93, 36.09);
    rr_renderer_fill(renderer);
    rr_renderer_set_fill(renderer, 0xffd0a51f);
    rr_renderer_begin_path(renderer);
    rr_renderer_move_to(renderer, 152.13, 108.94);
    rr_renderer_bezier_curve_to(renderer, 152.13, 116.02, 146.38, 121.77,
                                139.30, 121.77);
    rr_renderer_bezier_curve_to(renderer, 135.89, 121.77, 132.63, 120.42,
                                130.22, 118.01);
    rr_renderer_bezier_curve_to(renderer, 127.82, 115.60, 126.47, 112.34,
                                126.47, 108.94);
    rr_renderer_bezier_curve_to(renderer, 126.47, 101.85, 132.21, 96.10, 139.30,
                                96.10);
    rr_renderer_bezier_curve_to(renderer, 146.38, 96.10, 152.13, 101.85, 152.13,
                                108.94);
    rr_renderer_fill(renderer);
    rr_renderer_set_fill(renderer, 0xffd0a51f);
    rr_renderer_begin_path(renderer);
    rr_renderer_move_to(renderer, 103.05, 108.94);
    rr_renderer_bezier_curve_to(renderer, 103.05, 116.02, 97.31, 121.77, 90.22,
                                121.77);
    rr_renderer_bezier_curve_to(renderer, 86.82, 121.77, 83.55, 120.42, 81.15,
                                118.01);
    rr_renderer_bezier_curve_to(renderer, 78.74, 115.60, 77.39, 112.34, 77.39,
                                108.94);
    rr_renderer_bezier_curve_to(renderer, 77.39, 101.85, 83.13, 96.10, 90.22,
                                96.10);
    rr_renderer_bezier_curve_to(renderer, 97.31, 96.10, 103.05, 101.85, 103.05,
                                108.94);
    rr_renderer_fill(renderer);
    rr_renderer_set_fill(renderer, 0xffd0a51f);
    rr_renderer_begin_path(renderer);
    rr_renderer_move_to(renderer, 139.59, 121.77);
    rr_renderer_line_to(renderer, 89.93, 121.77);
    rr_renderer_line_to(renderer, 89.93, 96.16);
    rr_renderer_line_to(renderer, 139.59, 96.16);
    rr_renderer_fill(renderer);
    rr_renderer_set_fill(renderer, 0xffd0a51f);
    rr_renderer_begin_path(renderer);
    rr_renderer_move_to(renderer, 133.18, 12.32);
    rr_renderer_bezier_curve_to(renderer, 139.32, 8.77, 147.16, 10.88, 150.70,
                                17.02);
    rr_renderer_bezier_curve_to(renderer, 152.41, 19.96, 152.87, 23.47, 151.99,
                                26.75);
    rr_renderer_bezier_curve_to(renderer, 151.10, 30.04, 148.95, 32.84, 146.01,
                                34.54);
    rr_renderer_bezier_curve_to(renderer, 139.87, 38.09, 132.02, 35.98, 128.48,
                                29.84);
    rr_renderer_bezier_curve_to(renderer, 124.94, 23.71, 127.04, 15.86, 133.18,
                                12.32);
    rr_renderer_fill(renderer);
    rr_renderer_set_fill(renderer, 0xffd0a51f);
    rr_renderer_begin_path(renderer);
    rr_renderer_move_to(renderer, 157.71, 54.82);
    rr_renderer_bezier_curve_to(renderer, 163.85, 51.28, 171.70, 53.38, 175.24,
                                59.52);
    rr_renderer_bezier_curve_to(renderer, 176.94, 62.47, 177.40, 65.97, 176.52,
                                69.26);
    rr_renderer_bezier_curve_to(renderer, 175.64, 72.55, 173.49, 75.35, 170.54,
                                77.05);
    rr_renderer_bezier_curve_to(renderer, 164.40, 80.59, 156.56, 78.49, 153.01,
                                72.35);
    rr_renderer_bezier_curve_to(renderer, 149.47, 66.21, 151.57, 58.37, 157.71,
                                54.82);
    rr_renderer_fill(renderer);
    rr_renderer_set_fill(renderer, 0xffd0a51f);
    rr_renderer_begin_path(renderer);
    rr_renderer_move_to(renderer, 150.56, 16.76);
    rr_renderer_line_to(renderer, 175.38, 59.77);
    rr_renderer_line_to(renderer, 153.11, 72.63);
    rr_renderer_line_to(renderer, 128.29, 29.62);
    rr_renderer_fill(renderer);
    rr_renderer_set_fill(renderer, 0xffd0a51f);
    rr_renderer_begin_path(renderer);
    rr_renderer_move_to(renderer, 96.34, 119.88);
    rr_renderer_bezier_curve_to(renderer, 90.20, 123.42, 82.35, 121.32, 78.81,
                                115.18);
    rr_renderer_bezier_curve_to(renderer, 77.11, 112.23, 76.65, 108.73, 77.53,
                                105.44);
    rr_renderer_bezier_curve_to(renderer, 78.41, 102.16, 80.56, 99.36, 83.51,
                                97.65);
    rr_renderer_bezier_curve_to(renderer, 89.64, 94.11, 97.49, 96.22, 101.03,
                                102.35);
    rr_renderer_bezier_curve_to(renderer, 104.58, 108.49, 102.47, 116.34, 96.34,
                                119.88);
    rr_renderer_fill(renderer);
    rr_renderer_set_fill(renderer, 0xffd0a51f);
    rr_renderer_begin_path(renderer);
    rr_renderer_move_to(renderer, 71.80, 77.37);
    rr_renderer_bezier_curve_to(renderer, 65.66, 80.92, 57.82, 78.81, 54.27,
                                72.67);
    rr_renderer_bezier_curve_to(renderer, 52.57, 69.73, 52.11, 66.22, 52.99,
                                62.94);
    rr_renderer_bezier_curve_to(renderer, 53.87, 59.65, 56.02, 56.85, 58.97,
                                55.15);
    rr_renderer_bezier_curve_to(renderer, 65.11, 51.60, 72.96, 53.71, 76.50,
                                59.85);
    rr_renderer_bezier_curve_to(renderer, 80.04, 65.98, 77.94, 73.83, 71.80,
                                77.37);
    rr_renderer_fill(renderer);
    rr_renderer_set_fill(renderer, 0xffd0a51f);
    rr_renderer_begin_path(renderer);
    rr_renderer_move_to(renderer, 78.95, 115.43);
    rr_renderer_line_to(renderer, 54.13, 72.42);
    rr_renderer_line_to(renderer, 76.34, 59.61);
    rr_renderer_line_to(renderer, 101.16, 102.62);
    rr_renderer_fill(renderer);
    rr_renderer_set_fill(renderer, 0xffd0a51f);
    rr_renderer_begin_path(renderer);
    rr_renderer_move_to(renderer, 58.97, 77.04);
    rr_renderer_bezier_curve_to(renderer, 52.84, 73.50, 50.73, 65.65, 54.27,
                                59.52);
    rr_renderer_bezier_curve_to(renderer, 55.98, 56.57, 58.78, 54.42, 62.07,
                                53.54);
    rr_renderer_bezier_curve_to(renderer, 65.35, 52.66, 68.86, 53.12, 71.80,
                                54.82);
    rr_renderer_bezier_curve_to(renderer, 77.94, 58.36, 80.04, 66.21, 76.50,
                                72.34);
    rr_renderer_bezier_curve_to(renderer, 72.96, 78.48, 65.11, 80.59, 58.97,
                                77.04);
    rr_renderer_fill(renderer);
    rr_renderer_set_fill(renderer, 0xffd0a51f);
    rr_renderer_begin_path(renderer);
    rr_renderer_move_to(renderer, 83.51, 34.54);
    rr_renderer_bezier_curve_to(renderer, 77.37, 30.99, 75.27, 23.15, 78.81,
                                17.01);
    rr_renderer_bezier_curve_to(renderer, 80.51, 14.06, 83.31, 11.91, 86.60,
                                11.03);
    rr_renderer_bezier_curve_to(renderer, 89.89, 10.15, 93.39, 10.61, 96.34,
                                12.31);
    rr_renderer_bezier_curve_to(renderer, 102.47, 15.85, 104.58, 23.70, 101.04,
                                29.84);
    rr_renderer_bezier_curve_to(renderer, 97.49, 35.98, 89.65, 38.08, 83.51,
                                34.54);
    rr_renderer_fill(renderer);
    rr_renderer_set_fill(renderer, 0xffd0a51f);
    rr_renderer_begin_path(renderer);
    rr_renderer_move_to(renderer, 54.13, 59.77);
    rr_renderer_line_to(renderer, 78.95, 16.76);
    rr_renderer_line_to(renderer, 101.14, 29.56);
    rr_renderer_line_to(renderer, 76.32, 72.57);
    rr_renderer_fill(renderer);
    rr_renderer_set_fill(renderer, 0xffd0a51f);
    rr_renderer_begin_path(renderer);
    rr_renderer_move_to(renderer, 170.54, 55.14);
    rr_renderer_bezier_curve_to(renderer, 176.68, 58.68, 178.78, 66.53, 175.24,
                                72.67);
    rr_renderer_bezier_curve_to(renderer, 173.54, 75.62, 170.74, 77.77, 167.45,
                                78.65);
    rr_renderer_bezier_curve_to(renderer, 164.16, 79.53, 160.66, 79.07, 157.71,
                                77.37);
    rr_renderer_bezier_curve_to(renderer, 151.58, 73.82, 149.47, 65.98, 153.01,
                                59.84);
    rr_renderer_bezier_curve_to(renderer, 156.56, 53.70, 164.40, 51.60, 170.54,
                                55.14);
    rr_renderer_fill(renderer);
    rr_renderer_set_fill(renderer, 0xffd0a51f);
    rr_renderer_begin_path(renderer);
    rr_renderer_move_to(renderer, 146.01, 97.65);
    rr_renderer_bezier_curve_to(renderer, 152.15, 101.19, 154.25, 109.04,
                                150.71, 115.18);
    rr_renderer_bezier_curve_to(renderer, 149.01, 118.12, 146.20, 120.27,
                                142.92, 121.15);
    rr_renderer_bezier_curve_to(renderer, 139.63, 122.04, 136.13, 121.58,
                                133.18, 119.87);
    rr_renderer_bezier_curve_to(renderer, 127.04, 116.33, 124.94, 108.48,
                                128.48, 102.35);
    rr_renderer_bezier_curve_to(renderer, 132.02, 96.21, 139.87, 94.11, 146.01,
                                97.65);
    rr_renderer_fill(renderer);
    rr_renderer_set_fill(renderer, 0xffd0a51f);
    rr_renderer_begin_path(renderer);
    rr_renderer_move_to(renderer, 175.39, 72.42);
    rr_renderer_line_to(renderer, 150.56, 115.43);
    rr_renderer_line_to(renderer, 128.47, 102.68);
    rr_renderer_line_to(renderer, 153.30, 59.67);
    rr_renderer_fill(renderer);
    rr_renderer_set_fill(renderer, 0xffd0a51f);
    rr_renderer_begin_path(renderer);
    rr_renderer_move_to(renderer, 86.10, 76.55);
    rr_renderer_bezier_curve_to(renderer, 80.33, 76.55, 75.65, 71.87, 75.65,
                                66.10);
    rr_renderer_bezier_curve_to(renderer, 75.65, 60.32, 80.33, 55.64, 86.10,
                                55.64);
    rr_renderer_bezier_curve_to(renderer, 81.56, 61.87, 81.56, 70.32, 86.10,
                                76.55);
    rr_renderer_fill(renderer);
    rr_renderer_set_fill(renderer, 0xffd0a51f);
    rr_renderer_begin_path(renderer);
    rr_renderer_move_to(renderer, 143.42, 55.64);
    rr_renderer_bezier_curve_to(renderer, 149.19, 55.64, 153.87, 60.32, 153.87,
                                66.10);
    rr_renderer_bezier_curve_to(renderer, 153.87, 71.87, 149.19, 76.55, 143.42,
                                76.55);
    rr_renderer_bezier_curve_to(renderer, 147.95, 70.32, 147.95, 61.87, 143.42,
                                55.64);
    rr_renderer_fill(renderer);
    rr_renderer_set_fill(renderer, 0xffd0a51f);
    rr_renderer_begin_path(renderer);
    rr_renderer_move_to(renderer, 109.49, 96.15);
    rr_renderer_bezier_curve_to(renderer, 106.60, 101.14, 100.21, 102.85, 95.21,
                                99.97);
    rr_renderer_bezier_curve_to(renderer, 90.21, 97.08, 88.49, 90.69, 91.37,
                                85.70);
    rr_renderer_bezier_curve_to(renderer, 94.50, 92.74, 101.82, 96.96, 109.49,
                                96.15);
    rr_renderer_fill(renderer);
    rr_renderer_set_fill(renderer, 0xffd0a51f);
    rr_renderer_begin_path(renderer);
    rr_renderer_move_to(renderer, 120.03, 36.05);
    rr_renderer_bezier_curve_to(renderer, 122.91, 31.05, 129.30, 29.34, 134.31,
                                32.22);
    rr_renderer_bezier_curve_to(renderer, 139.31, 35.11, 141.03, 41.50, 138.14,
                                46.50);
    rr_renderer_bezier_curve_to(renderer, 135.01, 39.46, 127.69, 35.24, 120.03,
                                36.05);
    rr_renderer_fill(renderer);
    rr_renderer_set_fill(renderer, 0xffd0a51f);
    rr_renderer_begin_path(renderer);
    rr_renderer_move_to(renderer, 91.39, 46.49);
    rr_renderer_bezier_curve_to(renderer, 88.50, 41.48, 90.22, 35.09, 95.23,
                                32.21);
    rr_renderer_bezier_curve_to(renderer, 100.23, 29.33, 106.62, 31.05, 109.50,
                                36.05);
    rr_renderer_bezier_curve_to(renderer, 101.84, 35.23, 94.52, 39.45, 91.39,
                                46.49);
    rr_renderer_fill(renderer);
    rr_renderer_set_fill(renderer, 0xffd0a51f);
    rr_renderer_begin_path(renderer);
    rr_renderer_move_to(renderer, 138.13, 85.71);
    rr_renderer_bezier_curve_to(renderer, 141.01, 90.71, 139.29, 97.10, 134.29,
                                99.98);
    rr_renderer_bezier_curve_to(renderer, 129.29, 102.86, 122.89, 101.15,
                                120.01, 96.14);
    rr_renderer_bezier_curve_to(renderer, 127.67, 96.96, 134.99, 92.75, 138.13,
                                85.71);
    rr_renderer_fill(renderer);
    rr_renderer_set_fill(renderer, 0xffedbe2b);
    rr_renderer_begin_path(renderer);
    rr_renderer_move_to(renderer, -156.35, 65.90);
    rr_renderer_bezier_curve_to(renderer, -156.35, 42.92, -137.73, 24.30,
                                -114.75, 24.30);
    rr_renderer_bezier_curve_to(renderer, -103.72, 24.30, -93.14, 28.68, -85.34,
                                36.48);
    rr_renderer_bezier_curve_to(renderer, -77.54, 44.29, -73.16, 54.87, -73.16,
                                65.90);
    rr_renderer_bezier_curve_to(renderer, -73.16, 88.87, -91.78, 107.49,
                                -114.75, 107.49);
    rr_renderer_bezier_curve_to(renderer, -137.73, 107.49, -156.35, 88.87,
                                -156.35, 65.90);
    rr_renderer_fill(renderer);
    rr_renderer_set_fill(renderer, 0xffd0a51f);
    rr_renderer_begin_path(renderer);
    rr_renderer_move_to(renderer, -152.13, 23.26);
    rr_renderer_bezier_curve_to(renderer, -152.13, 16.17, -146.38, 10.43,
                                -139.29, 10.43);
    rr_renderer_bezier_curve_to(renderer, -135.89, 10.43, -132.63, 11.78,
                                -130.22, 14.19);
    rr_renderer_bezier_curve_to(renderer, -127.81, 16.59, -126.46, 19.86,
                                -126.46, 23.26);
    rr_renderer_bezier_curve_to(renderer, -126.46, 30.34, -132.21, 36.09,
                                -139.29, 36.09);
    rr_renderer_bezier_curve_to(renderer, -146.38, 36.09, -152.13, 30.34,
                                -152.13, 23.26);
    rr_renderer_fill(renderer);
    rr_renderer_set_fill(renderer, 0xffd0a51f);
    rr_renderer_begin_path(renderer);
    rr_renderer_move_to(renderer, -103.05, 23.26);
    rr_renderer_bezier_curve_to(renderer, -103.05, 16.17, -97.30, 10.43, -90.22,
                                10.43);
    rr_renderer_bezier_curve_to(renderer, -86.81, 10.43, -83.55, 11.78, -81.14,
                                14.19);
    rr_renderer_bezier_curve_to(renderer, -78.74, 16.59, -77.38, 19.86, -77.38,
                                23.26);
    rr_renderer_bezier_curve_to(renderer, -77.38, 30.34, -83.13, 36.09, -90.22,
                                36.09);
    rr_renderer_bezier_curve_to(renderer, -97.30, 36.09, -103.05, 30.34,
                                -103.05, 23.26);
    rr_renderer_fill(renderer);
    rr_renderer_set_fill(renderer, 0xffd0a51f);
    rr_renderer_begin_path(renderer);
    rr_renderer_move_to(renderer, -139.58, 10.43);
    rr_renderer_line_to(renderer, -89.92, 10.43);
    rr_renderer_line_to(renderer, -89.92, 36.09);
    rr_renderer_line_to(renderer, -139.58, 36.09);
    rr_renderer_fill(renderer);
    rr_renderer_set_fill(renderer, 0xffd0a51f);
    rr_renderer_begin_path(renderer);
    rr_renderer_move_to(renderer, -77.38, 108.94);
    rr_renderer_bezier_curve_to(renderer, -77.38, 116.02, -83.13, 121.77,
                                -90.22, 121.77);
    rr_renderer_bezier_curve_to(renderer, -93.62, 121.77, -96.88, 120.42,
                                -99.29, 118.01);
    rr_renderer_bezier_curve_to(renderer, -101.69, 115.60, -103.05, 112.34,
                                -103.05, 108.94);
    rr_renderer_bezier_curve_to(renderer, -103.05, 101.85, -97.30, 96.10,
                                -90.22, 96.10);
    rr_renderer_bezier_curve_to(renderer, -83.13, 96.10, -77.38, 101.85, -77.38,
                                108.94);
    rr_renderer_fill(renderer);
    rr_renderer_set_fill(renderer, 0xffd0a51f);
    rr_renderer_begin_path(renderer);
    rr_renderer_move_to(renderer, -126.46, 108.94);
    rr_renderer_bezier_curve_to(renderer, -126.46, 116.02, -132.21, 121.77,
                                -139.29, 121.77);
    rr_renderer_bezier_curve_to(renderer, -142.70, 121.77, -145.96, 120.42,
                                -148.37, 118.01);
    rr_renderer_bezier_curve_to(renderer, -150.77, 115.60, -152.13, 112.34,
                                -152.13, 108.94);
    rr_renderer_bezier_curve_to(renderer, -152.13, 101.85, -146.38, 96.10,
                                -139.29, 96.10);
    rr_renderer_bezier_curve_to(renderer, -132.21, 96.10, -126.46, 101.85,
                                -126.46, 108.94);
    rr_renderer_fill(renderer);
    rr_renderer_set_fill(renderer, 0xffd0a51f);
    rr_renderer_begin_path(renderer);
    rr_renderer_move_to(renderer, -89.92, 121.77);
    rr_renderer_line_to(renderer, -139.58, 121.77);
    rr_renderer_line_to(renderer, -139.58, 96.16);
    rr_renderer_line_to(renderer, -89.92, 96.16);
    rr_renderer_fill(renderer);
    rr_renderer_set_fill(renderer, 0xffd0a51f);
    rr_renderer_begin_path(renderer);
    rr_renderer_move_to(renderer, -96.34, 12.32);
    rr_renderer_bezier_curve_to(renderer, -90.20, 8.77, -82.35, 10.88, -78.81,
                                17.02);
    rr_renderer_bezier_curve_to(renderer, -77.11, 19.96, -76.65, 23.47, -77.53,
                                26.75);
    rr_renderer_bezier_curve_to(renderer, -78.41, 30.04, -80.56, 32.84, -83.51,
                                34.54);
    rr_renderer_bezier_curve_to(renderer, -89.64, 38.09, -97.49, 35.98, -101.03,
                                29.84);
    rr_renderer_bezier_curve_to(renderer, -104.58, 23.71, -102.47, 15.86,
                                -96.34, 12.32);
    rr_renderer_fill(renderer);
    rr_renderer_set_fill(renderer, 0xffd0a51f);
    rr_renderer_begin_path(renderer);
    rr_renderer_move_to(renderer, -71.80, 54.82);
    rr_renderer_bezier_curve_to(renderer, -65.66, 51.28, -57.82, 53.38, -54.27,
                                59.52);
    rr_renderer_bezier_curve_to(renderer, -52.57, 62.47, -52.11, 65.97, -52.99,
                                69.26);
    rr_renderer_bezier_curve_to(renderer, -53.87, 72.55, -56.03, 75.35, -58.97,
                                77.05);
    rr_renderer_bezier_curve_to(renderer, -65.11, 80.59, -72.96, 78.49, -76.50,
                                72.35);
    rr_renderer_bezier_curve_to(renderer, -80.04, 66.21, -77.94, 58.37, -71.80,
                                54.82);
    rr_renderer_fill(renderer);
    rr_renderer_set_fill(renderer, 0xffd0a51f);
    rr_renderer_begin_path(renderer);
    rr_renderer_move_to(renderer, -78.95, 16.76);
    rr_renderer_line_to(renderer, -54.13, 59.77);
    rr_renderer_line_to(renderer, -76.40, 72.63);
    rr_renderer_line_to(renderer, -101.22, 29.62);
    rr_renderer_fill(renderer);
    rr_renderer_set_fill(renderer, 0xffd0a51f);
    rr_renderer_begin_path(renderer);
    rr_renderer_move_to(renderer, -133.18, 119.88);
    rr_renderer_bezier_curve_to(renderer, -139.32, 123.42, -147.16, 121.32,
                                -150.71, 115.18);
    rr_renderer_bezier_curve_to(renderer, -152.41, 112.23, -152.87, 108.73,
                                -151.99, 105.44);
    rr_renderer_bezier_curve_to(renderer, -151.11, 102.16, -148.95, 99.36,
                                -146.01, 97.65);
    rr_renderer_bezier_curve_to(renderer, -139.87, 94.11, -132.02, 96.22,
                                -128.48, 102.35);
    rr_renderer_bezier_curve_to(renderer, -124.94, 108.49, -127.04, 116.34,
                                -133.18, 119.88);
    rr_renderer_fill(renderer);
    rr_renderer_set_fill(renderer, 0xffd0a51f);
    rr_renderer_begin_path(renderer);
    rr_renderer_move_to(renderer, -157.71, 77.37);
    rr_renderer_bezier_curve_to(renderer, -163.85, 80.92, -171.70, 78.81,
                                -175.24, 72.67);
    rr_renderer_bezier_curve_to(renderer, -176.94, 69.73, -177.40, 66.22,
                                -176.52, 62.94);
    rr_renderer_bezier_curve_to(renderer, -175.64, 59.65, -173.49, 56.85,
                                -170.54, 55.15);
    rr_renderer_bezier_curve_to(renderer, -164.40, 51.60, -156.56, 53.71,
                                -153.01, 59.85);
    rr_renderer_bezier_curve_to(renderer, -149.47, 65.98, -151.57, 73.83,
                                -157.71, 77.37);
    rr_renderer_fill(renderer);
    rr_renderer_set_fill(renderer, 0xffd0a51f);
    rr_renderer_begin_path(renderer);
    rr_renderer_move_to(renderer, -150.56, 115.43);
    rr_renderer_line_to(renderer, -175.39, 72.42);
    rr_renderer_line_to(renderer, -153.18, 59.61);
    rr_renderer_line_to(renderer, -128.35, 102.62);
    rr_renderer_fill(renderer);
    rr_renderer_set_fill(renderer, 0xffd0a51f);
    rr_renderer_begin_path(renderer);
    rr_renderer_move_to(renderer, -170.54, 77.04);
    rr_renderer_bezier_curve_to(renderer, -176.68, 73.50, -178.78, 65.65,
                                -175.24, 59.52);
    rr_renderer_bezier_curve_to(renderer, -173.54, 56.57, -170.73, 54.42,
                                -167.45, 53.54);
    rr_renderer_bezier_curve_to(renderer, -164.16, 52.66, -160.66, 53.12,
                                -157.71, 54.82);
    rr_renderer_bezier_curve_to(renderer, -151.57, 58.36, -149.47, 66.21,
                                -153.01, 72.34);
    rr_renderer_bezier_curve_to(renderer, -156.55, 78.48, -164.40, 80.59,
                                -170.54, 77.04);
    rr_renderer_fill(renderer);
    rr_renderer_set_fill(renderer, 0xffd0a51f);
    rr_renderer_begin_path(renderer);
    rr_renderer_move_to(renderer, -146.00, 34.54);
    rr_renderer_bezier_curve_to(renderer, -152.14, 30.99, -154.25, 23.15,
                                -150.70, 17.01);
    rr_renderer_bezier_curve_to(renderer, -149.00, 14.06, -146.20, 11.91,
                                -142.91, 11.03);
    rr_renderer_bezier_curve_to(renderer, -139.63, 10.15, -136.12, 10.61,
                                -133.18, 12.31);
    rr_renderer_bezier_curve_to(renderer, -127.04, 15.85, -124.93, 23.70,
                                -128.48, 29.84);
    rr_renderer_bezier_curve_to(renderer, -132.02, 35.98, -139.87, 38.08,
                                -146.00, 34.54);
    rr_renderer_fill(renderer);
    rr_renderer_set_fill(renderer, 0xffd0a51f);
    rr_renderer_begin_path(renderer);
    rr_renderer_move_to(renderer, -175.38, 59.77);
    rr_renderer_line_to(renderer, -150.56, 16.76);
    rr_renderer_line_to(renderer, -128.37, 29.56);
    rr_renderer_line_to(renderer, -153.19, 72.57);
    rr_renderer_fill(renderer);
    rr_renderer_set_fill(renderer, 0xffd0a51f);
    rr_renderer_begin_path(renderer);
    rr_renderer_move_to(renderer, -58.97, 55.14);
    rr_renderer_bezier_curve_to(renderer, -52.83, 58.68, -50.73, 66.53, -54.27,
                                72.67);
    rr_renderer_bezier_curve_to(renderer, -55.97, 75.62, -58.78, 77.77, -62.06,
                                78.65);
    rr_renderer_bezier_curve_to(renderer, -65.35, 79.53, -68.85, 79.07, -71.80,
                                77.37);
    rr_renderer_bezier_curve_to(renderer, -77.94, 73.82, -80.04, 65.98, -76.50,
                                59.84);
    rr_renderer_bezier_curve_to(renderer, -72.96, 53.70, -65.11, 51.60, -58.97,
                                55.14);
    rr_renderer_fill(renderer);
    rr_renderer_set_fill(renderer, 0xffd0a51f);
    rr_renderer_begin_path(renderer);
    rr_renderer_move_to(renderer, -83.51, 97.65);
    rr_renderer_bezier_curve_to(renderer, -77.37, 101.19, -75.26, 109.04,
                                -78.81, 115.18);
    rr_renderer_bezier_curve_to(renderer, -80.51, 118.12, -83.31, 120.27,
                                -86.60, 121.15);
    rr_renderer_bezier_curve_to(renderer, -89.88, 122.04, -93.39, 121.58,
                                -96.33, 119.87);
    rr_renderer_bezier_curve_to(renderer, -102.47, 116.33, -104.58, 108.48,
                                -101.03, 102.35);
    rr_renderer_bezier_curve_to(renderer, -97.49, 96.21, -89.64, 94.11, -83.51,
                                97.65);
    rr_renderer_fill(renderer);
    rr_renderer_set_fill(renderer, 0xffd0a51f);
    rr_renderer_begin_path(renderer);
    rr_renderer_move_to(renderer, -54.13, 72.42);
    rr_renderer_line_to(renderer, -78.95, 115.43);
    rr_renderer_line_to(renderer, -101.04, 102.68);
    rr_renderer_line_to(renderer, -76.21, 59.67);
    rr_renderer_fill(renderer);
    rr_renderer_set_fill(renderer, 0xffd0a51f);
    rr_renderer_begin_path(renderer);
    rr_renderer_move_to(renderer, -143.42, 76.55);
    rr_renderer_bezier_curve_to(renderer, -149.19, 76.55, -153.87, 71.87,
                                -153.87, 66.10);
    rr_renderer_bezier_curve_to(renderer, -153.87, 60.32, -149.19, 55.64,
                                -143.42, 55.64);
    rr_renderer_bezier_curve_to(renderer, -147.95, 61.87, -147.95, 70.32,
                                -143.42, 76.55);
    rr_renderer_fill(renderer);
    rr_renderer_set_fill(renderer, 0xffd0a51f);
    rr_renderer_begin_path(renderer);
    rr_renderer_move_to(renderer, -86.10, 55.64);
    rr_renderer_bezier_curve_to(renderer, -80.32, 55.64, -75.65, 60.32, -75.65,
                                66.10);
    rr_renderer_bezier_curve_to(renderer, -75.65, 71.87, -80.32, 76.55, -86.10,
                                76.55);
    rr_renderer_bezier_curve_to(renderer, -81.56, 70.32, -81.56, 61.87, -86.10,
                                55.64);
    rr_renderer_fill(renderer);
    rr_renderer_set_fill(renderer, 0xffd0a51f);
    rr_renderer_begin_path(renderer);
    rr_renderer_move_to(renderer, -120.03, 96.15);
    rr_renderer_bezier_curve_to(renderer, -122.91, 101.14, -129.30, 102.85,
                                -134.30, 99.97);
    rr_renderer_bezier_curve_to(renderer, -139.31, 97.08, -141.03, 90.69,
                                -138.14, 85.70);
    rr_renderer_bezier_curve_to(renderer, -135.01, 92.74, -127.69, 96.96,
                                -120.03, 96.15);
    rr_renderer_fill(renderer);
    rr_renderer_set_fill(renderer, 0xffd0a51f);
    rr_renderer_begin_path(renderer);
    rr_renderer_move_to(renderer, -109.49, 36.05);
    rr_renderer_bezier_curve_to(renderer, -106.60, 31.05, -100.21, 29.34,
                                -95.21, 32.22);
    rr_renderer_bezier_curve_to(renderer, -90.21, 35.11, -88.49, 41.50, -91.37,
                                46.50);
    rr_renderer_bezier_curve_to(renderer, -94.50, 39.46, -101.82, 35.24,
                                -109.49, 36.05);
    rr_renderer_fill(renderer);
    rr_renderer_set_fill(renderer, 0xffd0a51f);
    rr_renderer_begin_path(renderer);
    rr_renderer_move_to(renderer, -138.13, 46.49);
    rr_renderer_bezier_curve_to(renderer, -141.01, 41.48, -139.29, 35.09,
                                -134.29, 32.21);
    rr_renderer_bezier_curve_to(renderer, -129.28, 29.33, -122.89, 31.05,
                                -120.01, 36.05);
    rr_renderer_bezier_curve_to(renderer, -127.67, 35.23, -134.99, 39.45,
                                -138.13, 46.49);
    rr_renderer_fill(renderer);
    rr_renderer_set_fill(renderer, 0xffd0a51f);
    rr_renderer_begin_path(renderer);
    rr_renderer_move_to(renderer, -91.39, 85.71);
    rr_renderer_bezier_curve_to(renderer, -88.50, 90.71, -90.22, 97.10, -95.22,
                                99.98);
    rr_renderer_bezier_curve_to(renderer, -100.23, 102.86, -106.62, 101.15,
                                -109.50, 96.14);
    rr_renderer_bezier_curve_to(renderer, -101.84, 96.96, -94.52, 92.75, -91.39,
                                85.71);
    rr_renderer_fill(renderer);
    rr_renderer_set_fill(renderer, 0xffedbe2b);
    rr_renderer_begin_path(renderer);
    rr_renderer_move_to(renderer, -156.35, -65.89);
    rr_renderer_bezier_curve_to(renderer, -156.35, -88.87, -137.73, -107.49,
                                -114.75, -107.49);
    rr_renderer_bezier_curve_to(renderer, -103.72, -107.49, -93.14, -103.11,
                                -85.34, -95.31);
    rr_renderer_bezier_curve_to(renderer, -77.54, -87.51, -73.16, -76.93,
                                -73.16, -65.89);
    rr_renderer_bezier_curve_to(renderer, -73.16, -42.92, -91.78, -24.30,
                                -114.75, -24.30);
    rr_renderer_bezier_curve_to(renderer, -137.73, -24.30, -156.35, -42.92,
                                -156.35, -65.89);
    rr_renderer_fill(renderer);
    rr_renderer_set_fill(renderer, 0xffd0a51f);
    rr_renderer_begin_path(renderer);
    rr_renderer_move_to(renderer, -152.13, -108.73);
    rr_renderer_bezier_curve_to(renderer, -152.13, -115.82, -146.38, -121.56,
                                -139.29, -121.56);
    rr_renderer_bezier_curve_to(renderer, -135.89, -121.56, -132.63, -120.21,
                                -130.22, -117.81);
    rr_renderer_bezier_curve_to(renderer, -127.81, -115.40, -126.46, -112.14,
                                -126.46, -108.73);
    rr_renderer_bezier_curve_to(renderer, -126.46, -101.65, -132.21, -95.90,
                                -139.29, -95.90);
    rr_renderer_bezier_curve_to(renderer, -146.38, -95.90, -152.13, -101.65,
                                -152.13, -108.73);
    rr_renderer_fill(renderer);
    rr_renderer_set_fill(renderer, 0xffd0a51f);
    rr_renderer_begin_path(renderer);
    rr_renderer_move_to(renderer, -103.05, -108.73);
    rr_renderer_bezier_curve_to(renderer, -103.05, -115.82, -97.30, -121.56,
                                -90.22, -121.56);
    rr_renderer_bezier_curve_to(renderer, -86.81, -121.56, -83.55, -120.21,
                                -81.14, -117.81);
    rr_renderer_bezier_curve_to(renderer, -78.74, -115.40, -77.38, -112.14,
                                -77.38, -108.73);
    rr_renderer_bezier_curve_to(renderer, -77.38, -101.65, -83.13, -95.90,
                                -90.22, -95.90);
    rr_renderer_bezier_curve_to(renderer, -97.30, -95.90, -103.05, -101.65,
                                -103.05, -108.73);
    rr_renderer_fill(renderer);
    rr_renderer_set_fill(renderer, 0xffd0a51f);
    rr_renderer_begin_path(renderer);
    rr_renderer_move_to(renderer, -139.58, -121.56);
    rr_renderer_line_to(renderer, -89.92, -121.56);
    rr_renderer_line_to(renderer, -89.92, -95.90);
    rr_renderer_line_to(renderer, -139.58, -95.90);
    rr_renderer_fill(renderer);
    rr_renderer_set_fill(renderer, 0xffd0a51f);
    rr_renderer_begin_path(renderer);
    rr_renderer_move_to(renderer, -77.38, -23.05);
    rr_renderer_bezier_curve_to(renderer, -77.38, -15.97, -83.13, -10.22,
                                -90.22, -10.22);
    rr_renderer_bezier_curve_to(renderer, -93.62, -10.22, -96.88, -11.57,
                                -99.29, -13.98);
    rr_renderer_bezier_curve_to(renderer, -101.69, -16.39, -103.05, -19.65,
                                -103.05, -23.05);
    rr_renderer_bezier_curve_to(renderer, -103.05, -30.14, -97.30, -35.89,
                                -90.22, -35.89);
    rr_renderer_bezier_curve_to(renderer, -83.13, -35.89, -77.38, -30.14,
                                -77.38, -23.05);
    rr_renderer_fill(renderer);
    rr_renderer_set_fill(renderer, 0xffd0a51f);
    rr_renderer_begin_path(renderer);
    rr_renderer_move_to(renderer, -126.46, -23.05);
    rr_renderer_bezier_curve_to(renderer, -126.46, -15.97, -132.21, -10.22,
                                -139.29, -10.22);
    rr_renderer_bezier_curve_to(renderer, -142.70, -10.22, -145.96, -11.57,
                                -148.37, -13.98);
    rr_renderer_bezier_curve_to(renderer, -150.77, -16.39, -152.13, -19.65,
                                -152.13, -23.05);
    rr_renderer_bezier_curve_to(renderer, -152.13, -30.14, -146.38, -35.89,
                                -139.29, -35.89);
    rr_renderer_bezier_curve_to(renderer, -132.21, -35.89, -126.46, -30.14,
                                -126.46, -23.05);
    rr_renderer_fill(renderer);
    rr_renderer_set_fill(renderer, 0xffd0a51f);
    rr_renderer_begin_path(renderer);
    rr_renderer_move_to(renderer, -89.92, -10.22);
    rr_renderer_line_to(renderer, -139.58, -10.22);
    rr_renderer_line_to(renderer, -139.58, -35.83);
    rr_renderer_line_to(renderer, -89.92, -35.83);
    rr_renderer_fill(renderer);
    rr_renderer_set_fill(renderer, 0xffd0a51f);
    rr_renderer_begin_path(renderer);
    rr_renderer_move_to(renderer, -96.34, -119.67);
    rr_renderer_bezier_curve_to(renderer, -90.20, -123.22, -82.35, -121.11,
                                -78.81, -114.97);
    rr_renderer_bezier_curve_to(renderer, -77.11, -112.03, -76.65, -108.52,
                                -77.53, -105.24);
    rr_renderer_bezier_curve_to(renderer, -78.41, -101.95, -80.56, -99.15,
                                -83.51, -97.45);
    rr_renderer_bezier_curve_to(renderer, -89.64, -93.90, -97.49, -96.01,
                                -101.03, -102.15);
    rr_renderer_bezier_curve_to(renderer, -104.58, -108.28, -102.47, -116.13,
                                -96.34, -119.67);
    rr_renderer_fill(renderer);
    rr_renderer_set_fill(renderer, 0xffd0a51f);
    rr_renderer_begin_path(renderer);
    rr_renderer_move_to(renderer, -71.80, -77.17);
    rr_renderer_bezier_curve_to(renderer, -65.66, -80.71, -57.82, -78.61,
                                -54.27, -72.47);
    rr_renderer_bezier_curve_to(renderer, -52.57, -69.52, -52.11, -66.02,
                                -52.99, -62.73);
    rr_renderer_bezier_curve_to(renderer, -53.87, -59.44, -56.03, -56.64,
                                -58.97, -54.94);
    rr_renderer_bezier_curve_to(renderer, -65.11, -51.40, -72.96, -53.50,
                                -76.50, -59.64);
    rr_renderer_bezier_curve_to(renderer, -80.04, -65.78, -77.94, -73.62,
                                -71.80, -77.17);
    rr_renderer_fill(renderer);
    rr_renderer_set_fill(renderer, 0xffd0a51f);
    rr_renderer_begin_path(renderer);
    rr_renderer_move_to(renderer, -78.95, -115.23);
    rr_renderer_line_to(renderer, -54.13, -72.22);
    rr_renderer_line_to(renderer, -76.40, -59.36);
    rr_renderer_line_to(renderer, -101.22, -102.37);
    rr_renderer_fill(renderer);
    rr_renderer_set_fill(renderer, 0xffd0a51f);
    rr_renderer_begin_path(renderer);
    rr_renderer_move_to(renderer, -133.18, -12.11);
    rr_renderer_bezier_curve_to(renderer, -139.32, -8.57, -147.16, -10.67,
                                -150.71, -16.81);
    rr_renderer_bezier_curve_to(renderer, -152.41, -19.76, -152.87, -23.26,
                                -151.99, -26.55);
    rr_renderer_bezier_curve_to(renderer, -151.11, -29.83, -148.95, -32.63,
                                -146.01, -34.34);
    rr_renderer_bezier_curve_to(renderer, -139.87, -37.88, -132.02, -35.77,
                                -128.48, -29.64);
    rr_renderer_bezier_curve_to(renderer, -124.94, -23.50, -127.04, -15.65,
                                -133.18, -12.11);
    rr_renderer_fill(renderer);
    rr_renderer_set_fill(renderer, 0xffd0a51f);
    rr_renderer_begin_path(renderer);
    rr_renderer_move_to(renderer, -157.71, -54.62);
    rr_renderer_bezier_curve_to(renderer, -163.85, -51.07, -171.70, -53.18,
                                -175.24, -59.32);
    rr_renderer_bezier_curve_to(renderer, -176.94, -62.26, -177.40, -65.77,
                                -176.52, -69.05);
    rr_renderer_bezier_curve_to(renderer, -175.64, -72.34, -173.49, -75.14,
                                -170.54, -76.84);
    rr_renderer_bezier_curve_to(renderer, -164.40, -80.39, -156.56, -78.28,
                                -153.01, -72.14);
    rr_renderer_bezier_curve_to(renderer, -149.47, -66.01, -151.57, -58.16,
                                -157.71, -54.62);
    rr_renderer_fill(renderer);
    rr_renderer_set_fill(renderer, 0xffd0a51f);
    rr_renderer_begin_path(renderer);
    rr_renderer_move_to(renderer, -150.56, -16.56);
    rr_renderer_line_to(renderer, -175.39, -59.57);
    rr_renderer_line_to(renderer, -153.18, -72.39);
    rr_renderer_line_to(renderer, -128.35, -29.37);
    rr_renderer_fill(renderer);
    rr_renderer_set_fill(renderer, 0xffd0a51f);
    rr_renderer_begin_path(renderer);
    rr_renderer_move_to(renderer, -170.54, -54.95);
    rr_renderer_bezier_curve_to(renderer, -176.68, -58.49, -178.78, -66.34,
                                -175.24, -72.47);
    rr_renderer_bezier_curve_to(renderer, -173.54, -75.42, -170.73, -77.57,
                                -167.45, -78.45);
    rr_renderer_bezier_curve_to(renderer, -164.16, -79.33, -160.66, -78.87,
                                -157.71, -77.17);
    rr_renderer_bezier_curve_to(renderer, -151.57, -73.63, -149.47, -65.78,
                                -153.01, -59.65);
    rr_renderer_bezier_curve_to(renderer, -156.55, -53.51, -164.40, -51.40,
                                -170.54, -54.95);
    rr_renderer_fill(renderer);
    rr_renderer_set_fill(renderer, 0xffd0a51f);
    rr_renderer_begin_path(renderer);
    rr_renderer_move_to(renderer, -146.00, -97.45);
    rr_renderer_bezier_curve_to(renderer, -152.14, -101.00, -154.25, -108.84,
                                -150.70, -114.98);
    rr_renderer_bezier_curve_to(renderer, -149.00, -117.93, -146.20, -120.08,
                                -142.91, -120.96);
    rr_renderer_bezier_curve_to(renderer, -139.63, -121.84, -136.12, -121.38,
                                -133.18, -119.68);
    rr_renderer_bezier_curve_to(renderer, -127.04, -116.14, -124.93, -108.29,
                                -128.48, -102.15);
    rr_renderer_bezier_curve_to(renderer, -132.02, -96.02, -139.87, -93.91,
                                -146.00, -97.45);
    rr_renderer_fill(renderer);
    rr_renderer_set_fill(renderer, 0xffd0a51f);
    rr_renderer_begin_path(renderer);
    rr_renderer_move_to(renderer, -175.38, -72.22);
    rr_renderer_line_to(renderer, -150.56, -115.23);
    rr_renderer_line_to(renderer, -128.37, -102.43);
    rr_renderer_line_to(renderer, -153.19, -59.42);
    rr_renderer_fill(renderer);
    rr_renderer_set_fill(renderer, 0xffd0a51f);
    rr_renderer_begin_path(renderer);
    rr_renderer_move_to(renderer, -58.97, -76.85);
    rr_renderer_bezier_curve_to(renderer, -52.83, -73.31, -50.73, -65.46,
                                -54.27, -59.32);
    rr_renderer_bezier_curve_to(renderer, -55.97, -56.37, -58.78, -54.22,
                                -62.06, -53.34);
    rr_renderer_bezier_curve_to(renderer, -65.35, -52.46, -68.85, -52.92,
                                -71.80, -54.62);
    rr_renderer_bezier_curve_to(renderer, -77.94, -58.17, -80.04, -66.01,
                                -76.50, -72.15);
    rr_renderer_bezier_curve_to(renderer, -72.96, -78.29, -65.11, -80.39,
                                -58.97, -76.85);
    rr_renderer_fill(renderer);
    rr_renderer_set_fill(renderer, 0xffd0a51f);
    rr_renderer_begin_path(renderer);
    rr_renderer_move_to(renderer, -83.51, -34.34);
    rr_renderer_bezier_curve_to(renderer, -77.37, -30.80, -75.26, -22.95,
                                -78.81, -16.81);
    rr_renderer_bezier_curve_to(renderer, -80.51, -13.87, -83.31, -11.72,
                                -86.60, -10.84);
    rr_renderer_bezier_curve_to(renderer, -89.88, -9.95, -93.39, -10.41, -96.33,
                                -12.12);
    rr_renderer_bezier_curve_to(renderer, -102.47, -15.66, -104.58, -23.51,
                                -101.03, -29.64);
    rr_renderer_bezier_curve_to(renderer, -97.49, -35.78, -89.64, -37.88,
                                -83.51, -34.34);
    rr_renderer_fill(renderer);
    rr_renderer_set_fill(renderer, 0xffd0a51f);
    rr_renderer_begin_path(renderer);
    rr_renderer_move_to(renderer, -54.13, -59.57);
    rr_renderer_line_to(renderer, -78.95, -16.56);
    rr_renderer_line_to(renderer, -101.04, -29.31);
    rr_renderer_line_to(renderer, -76.21, -72.32);
    rr_renderer_fill(renderer);
    rr_renderer_set_fill(renderer, 0xffd0a51f);
    rr_renderer_begin_path(renderer);
    rr_renderer_move_to(renderer, -143.42, -55.44);
    rr_renderer_bezier_curve_to(renderer, -149.19, -55.44, -153.87, -60.12,
                                -153.87, -65.89);
    rr_renderer_bezier_curve_to(renderer, -153.87, -71.67, -149.19, -76.35,
                                -143.42, -76.35);
    rr_renderer_bezier_curve_to(renderer, -147.95, -70.12, -147.95, -61.67,
                                -143.42, -55.44);
    rr_renderer_fill(renderer);
    rr_renderer_set_fill(renderer, 0xffd0a51f);
    rr_renderer_begin_path(renderer);
    rr_renderer_move_to(renderer, -86.10, -76.35);
    rr_renderer_bezier_curve_to(renderer, -80.32, -76.35, -75.65, -71.67,
                                -75.65, -65.89);
    rr_renderer_bezier_curve_to(renderer, -75.65, -60.12, -80.32, -55.44,
                                -86.10, -55.44);
    rr_renderer_bezier_curve_to(renderer, -81.56, -61.67, -81.56, -70.12,
                                -86.10, -76.35);
    rr_renderer_fill(renderer);
    rr_renderer_set_fill(renderer, 0xffd0a51f);
    rr_renderer_begin_path(renderer);
    rr_renderer_move_to(renderer, -120.03, -35.84);
    rr_renderer_bezier_curve_to(renderer, -122.91, -30.85, -129.30, -29.14,
                                -134.30, -32.02);
    rr_renderer_bezier_curve_to(renderer, -139.31, -34.91, -141.03, -41.30,
                                -138.14, -46.29);
    rr_renderer_bezier_curve_to(renderer, -135.01, -39.25, -127.69, -35.03,
                                -120.03, -35.84);
    rr_renderer_fill(renderer);
    rr_renderer_set_fill(renderer, 0xffd0a51f);
    rr_renderer_begin_path(renderer);
    rr_renderer_move_to(renderer, -109.49, -95.94);
    rr_renderer_bezier_curve_to(renderer, -106.60, -100.94, -100.21, -102.65,
                                -95.21, -99.77);
    rr_renderer_bezier_curve_to(renderer, -90.21, -96.88, -88.49, -90.49,
                                -91.37, -85.49);
    rr_renderer_bezier_curve_to(renderer, -94.50, -92.53, -101.82, -96.75,
                                -109.49, -95.94);
    rr_renderer_fill(renderer);
    rr_renderer_set_fill(renderer, 0xffd0a51f);
    rr_renderer_begin_path(renderer);
    rr_renderer_move_to(renderer, -138.13, -85.50);
    rr_renderer_bezier_curve_to(renderer, -141.01, -90.51, -139.29, -96.90,
                                -134.29, -99.78);
    rr_renderer_bezier_curve_to(renderer, -129.28, -102.66, -122.89, -100.94,
                                -120.01, -95.94);
    rr_renderer_bezier_curve_to(renderer, -127.67, -96.76, -134.99, -92.54,
                                -138.13, -85.50);
    rr_renderer_fill(renderer);
    rr_renderer_set_fill(renderer, 0xffd0a51f);
    rr_renderer_begin_path(renderer);
    rr_renderer_move_to(renderer, -91.39, -46.29);
    rr_renderer_bezier_curve_to(renderer, -88.50, -41.28, -90.22, -34.89,
                                -95.22, -32.01);
    rr_renderer_bezier_curve_to(renderer, -100.23, -29.13, -106.62, -30.84,
                                -109.50, -35.85);
    rr_renderer_bezier_curve_to(renderer, -101.84, -35.03, -94.52, -39.24,
                                -91.39, -46.29);
    rr_renderer_fill(renderer);
    rr_renderer_set_fill(renderer, 0xff4f3e0d);
    rr_renderer_begin_path(renderer);
    rr_renderer_move_to(renderer, -41.60, 0.00);
    rr_renderer_bezier_curve_to(renderer, -41.60, -22.97, -22.98, -41.59, -0.00,
                                -41.59);
    rr_renderer_bezier_curve_to(renderer, 11.03, -41.59, 21.61, -37.21, 29.41,
                                -29.41);
    rr_renderer_bezier_curve_to(renderer, 37.21, -21.61, 41.59, -11.03, 41.59,
                                0.00);
    rr_renderer_bezier_curve_to(renderer, 41.59, 22.98, 22.97, 41.60, -0.00,
                                41.60);
    rr_renderer_bezier_curve_to(renderer, -22.98, 41.60, -41.60, 22.98, -41.60,
                                0.00);
    rr_renderer_fill(renderer);
    rr_renderer_set_fill(renderer, 0xff4f3e0d);
    rr_renderer_begin_path(renderer);
    rr_renderer_move_to(renderer, -37.37, -42.83);
    rr_renderer_bezier_curve_to(renderer, -37.37, -49.92, -31.63, -55.67,
                                -24.54, -55.67);
    rr_renderer_bezier_curve_to(renderer, -21.14, -55.67, -17.88, -54.31,
                                -15.47, -51.91);
    rr_renderer_bezier_curve_to(renderer, -13.06, -49.50, -11.71, -46.24,
                                -11.71, -42.83);
    rr_renderer_bezier_curve_to(renderer, -11.71, -35.75, -17.46, -30.00,
                                -24.54, -30.00);
    rr_renderer_bezier_curve_to(renderer, -31.63, -30.00, -37.37, -35.75,
                                -37.37, -42.83);
    rr_renderer_fill(renderer);
    rr_renderer_set_fill(renderer, 0xff4f3e0d);
    rr_renderer_begin_path(renderer);
    rr_renderer_move_to(renderer, 11.71, -42.83);
    rr_renderer_bezier_curve_to(renderer, 11.71, -49.92, 17.45, -55.67, 24.54,
                                -55.67);
    rr_renderer_bezier_curve_to(renderer, 27.94, -55.67, 31.20, -54.31, 33.61,
                                -51.91);
    rr_renderer_bezier_curve_to(renderer, 36.02, -49.50, 37.37, -46.24, 37.37,
                                -42.83);
    rr_renderer_bezier_curve_to(renderer, 37.37, -35.75, 31.62, -30.00, 24.54,
                                -30.00);
    rr_renderer_bezier_curve_to(renderer, 17.45, -30.00, 11.71, -35.75, 11.71,
                                -42.83);
    rr_renderer_fill(renderer);
    rr_renderer_set_fill(renderer, 0xff4f3e0d);
    rr_renderer_begin_path(renderer);
    rr_renderer_move_to(renderer, -24.83, -55.67);
    rr_renderer_line_to(renderer, 24.83, -55.67);
    rr_renderer_line_to(renderer, 24.83, -30.00);
    rr_renderer_line_to(renderer, -24.83, -30.00);
    rr_renderer_fill(renderer);
    rr_renderer_set_fill(renderer, 0xff4f3e0d);
    rr_renderer_begin_path(renderer);
    rr_renderer_move_to(renderer, 37.37, 42.84);
    rr_renderer_bezier_curve_to(renderer, 37.37, 49.93, 31.62, 55.68, 24.54,
                                55.68);
    rr_renderer_bezier_curve_to(renderer, 21.13, 55.68, 17.87, 54.32, 15.46,
                                51.92);
    rr_renderer_bezier_curve_to(renderer, 13.06, 49.51, 11.71, 46.25, 11.71,
                                42.84);
    rr_renderer_bezier_curve_to(renderer, 11.71, 35.76, 17.45, 30.01, 24.54,
                                30.01);
    rr_renderer_bezier_curve_to(renderer, 31.62, 30.01, 37.37, 35.76, 37.37,
                                42.84);
    rr_renderer_fill(renderer);
    rr_renderer_set_fill(renderer, 0xff4f3e0d);
    rr_renderer_begin_path(renderer);
    rr_renderer_move_to(renderer, -11.71, 42.84);
    rr_renderer_bezier_curve_to(renderer, -11.71, 49.93, -17.46, 55.68, -24.54,
                                55.68);
    rr_renderer_bezier_curve_to(renderer, -27.95, 55.68, -31.21, 54.32, -33.62,
                                51.92);
    rr_renderer_bezier_curve_to(renderer, -36.02, 49.51, -37.37, 46.25, -37.37,
                                42.84);
    rr_renderer_bezier_curve_to(renderer, -37.37, 35.76, -31.63, 30.01, -24.54,
                                30.01);
    rr_renderer_bezier_curve_to(renderer, -17.46, 30.01, -11.71, 35.76, -11.71,
                                42.84);
    rr_renderer_fill(renderer);
    rr_renderer_set_fill(renderer, 0xff4f3e0d);
    rr_renderer_begin_path(renderer);
    rr_renderer_move_to(renderer, 24.83, 55.68);
    rr_renderer_line_to(renderer, -24.83, 55.68);
    rr_renderer_line_to(renderer, -24.83, 30.06);
    rr_renderer_line_to(renderer, 24.83, 30.06);
    rr_renderer_fill(renderer);
    rr_renderer_set_fill(renderer, 0xff4f3e0d);
    rr_renderer_begin_path(renderer);
    rr_renderer_move_to(renderer, 18.42, -53.78);
    rr_renderer_bezier_curve_to(renderer, 24.55, -57.32, 32.40, -55.21, 35.94,
                                -49.08);
    rr_renderer_bezier_curve_to(renderer, 37.64, -46.13, 38.11, -42.63, 37.22,
                                -39.34);
    rr_renderer_bezier_curve_to(renderer, 36.34, -36.05, 34.19, -33.25, 31.24,
                                -31.55);
    rr_renderer_bezier_curve_to(renderer, 25.11, -28.01, 17.26, -30.11, 13.72,
                                -36.25);
    rr_renderer_bezier_curve_to(renderer, 10.17, -42.39, 12.28, -50.23, 18.42,
                                -53.78);
    rr_renderer_fill(renderer);
    rr_renderer_set_fill(renderer, 0xff4f3e0d);
    rr_renderer_begin_path(renderer);
    rr_renderer_move_to(renderer, 42.95, -11.27);
    rr_renderer_bezier_curve_to(renderer, 49.09, -14.81, 56.94, -12.71, 60.48,
                                -6.57);
    rr_renderer_bezier_curve_to(renderer, 62.18, -3.62, 62.64, -0.12, 61.76,
                                3.17);
    rr_renderer_bezier_curve_to(renderer, 60.88, 6.45, 58.73, 9.26, 55.78,
                                10.96);
    rr_renderer_bezier_curve_to(renderer, 49.64, 14.50, 41.79, 12.40, 38.25,
                                6.26);
    rr_renderer_bezier_curve_to(renderer, 34.71, 0.12, 36.81, -7.73, 42.95,
                                -11.27);
    rr_renderer_fill(renderer);
    rr_renderer_set_fill(renderer, 0xff4f3e0d);
    rr_renderer_begin_path(renderer);
    rr_renderer_move_to(renderer, 35.80, -49.33);
    rr_renderer_line_to(renderer, 60.62, -6.32);
    rr_renderer_line_to(renderer, 38.35, 6.54);
    rr_renderer_line_to(renderer, 13.53, -36.47);
    rr_renderer_fill(renderer);
    rr_renderer_set_fill(renderer, 0xff4f3e0d);
    rr_renderer_begin_path(renderer);
    rr_renderer_move_to(renderer, -18.43, 53.79);
    rr_renderer_bezier_curve_to(renderer, -24.56, 57.33, -32.41, 55.23, -35.95,
                                49.09);
    rr_renderer_bezier_curve_to(renderer, -37.65, 46.14, -38.12, 42.64, -37.23,
                                39.35);
    rr_renderer_bezier_curve_to(renderer, -36.35, 36.07, -34.20, 33.26, -31.25,
                                31.56);
    rr_renderer_bezier_curve_to(renderer, -25.12, 28.02, -17.27, 30.12, -13.73,
                                36.26);
    rr_renderer_bezier_curve_to(renderer, -10.18, 42.40, -12.29, 50.25, -18.43,
                                53.79);
    rr_renderer_fill(renderer);
    rr_renderer_set_fill(renderer, 0xff4f3e0d);
    rr_renderer_begin_path(renderer);
    rr_renderer_move_to(renderer, -42.96, 11.28);
    rr_renderer_bezier_curve_to(renderer, -49.10, 14.82, -56.95, 12.72, -60.49,
                                6.58);
    rr_renderer_bezier_curve_to(renderer, -62.19, 3.64, -62.65, 0.13, -61.77,
                                -3.15);
    rr_renderer_bezier_curve_to(renderer, -60.89, -6.44, -58.74, -9.24, -55.79,
                                -10.94);
    rr_renderer_bezier_curve_to(renderer, -49.65, -14.49, -41.80, -12.38,
                                -38.26, -6.25);
    rr_renderer_bezier_curve_to(renderer, -34.72, -0.11, -36.82, 7.74, -42.96,
                                11.28);
    rr_renderer_fill(renderer);
    rr_renderer_set_fill(renderer, 0xff4f3e0d);
    rr_renderer_begin_path(renderer);
    rr_renderer_move_to(renderer, -35.81, 49.34);
    rr_renderer_line_to(renderer, -60.63, 6.33);
    rr_renderer_line_to(renderer, -38.43, -6.49);
    rr_renderer_line_to(renderer, -13.60, 36.52);
    rr_renderer_fill(renderer);
    rr_renderer_set_fill(renderer, 0xff4f3e0d);
    rr_renderer_begin_path(renderer);
    rr_renderer_move_to(renderer, -55.79, 10.95);
    rr_renderer_bezier_curve_to(renderer, -61.93, 7.41, -64.03, -0.44, -60.49,
                                -6.58);
    rr_renderer_bezier_curve_to(renderer, -58.79, -9.52, -55.98, -11.67, -52.70,
                                -12.56);
    rr_renderer_bezier_curve_to(renderer, -49.41, -13.44, -45.91, -12.98,
                                -42.96, -11.27);
    rr_renderer_bezier_curve_to(renderer, -36.82, -7.73, -34.72, 0.12, -38.26,
                                6.25);
    rr_renderer_bezier_curve_to(renderer, -41.80, 12.39, -49.65, 14.49, -55.79,
                                10.95);
    rr_renderer_fill(renderer);
    rr_renderer_set_fill(renderer, 0xff4f3e0d);
    rr_renderer_begin_path(renderer);
    rr_renderer_move_to(renderer, -31.25, -31.56);
    rr_renderer_bezier_curve_to(renderer, -37.39, -35.10, -39.49, -42.95,
                                -35.95, -49.08);
    rr_renderer_bezier_curve_to(renderer, -34.25, -52.03, -31.45, -54.18,
                                -28.16, -55.06);
    rr_renderer_bezier_curve_to(renderer, -24.87, -55.94, -21.37, -55.48,
                                -18.42, -53.78);
    rr_renderer_bezier_curve_to(renderer, -12.29, -50.24, -10.18, -42.39,
                                -13.73, -36.25);
    rr_renderer_bezier_curve_to(renderer, -17.27, -30.12, -25.12, -28.01,
                                -31.25, -31.56);
    rr_renderer_fill(renderer);
    rr_renderer_set_fill(renderer, 0xff4f3e0d);
    rr_renderer_begin_path(renderer);
    rr_renderer_move_to(renderer, -60.63, -6.32);
    rr_renderer_line_to(renderer, -35.81, -49.34);
    rr_renderer_line_to(renderer, -13.62, -36.53);
    rr_renderer_line_to(renderer, -38.44, 6.48);
    rr_renderer_fill(renderer);
    rr_renderer_set_fill(renderer, 0xff4f3e0d);
    rr_renderer_begin_path(renderer);
    rr_renderer_move_to(renderer, 55.78, -10.95);
    rr_renderer_bezier_curve_to(renderer, 61.92, -7.41, 64.02, 0.44, 60.48,
                                6.58);
    rr_renderer_bezier_curve_to(renderer, 58.78, 9.52, 55.98, 11.67, 52.69,
                                12.56);
    rr_renderer_bezier_curve_to(renderer, 49.40, 13.44, 45.90, 12.98, 42.95,
                                11.28);
    rr_renderer_bezier_curve_to(renderer, 36.81, 7.73, 34.71, -0.11, 38.25,
                                -6.25);
    rr_renderer_bezier_curve_to(renderer, 41.80, -12.39, 49.64, -14.49, 55.78,
                                -10.95);
    rr_renderer_fill(renderer);
    rr_renderer_set_fill(renderer, 0xff4f3e0d);
    rr_renderer_begin_path(renderer);
    rr_renderer_move_to(renderer, 31.25, 31.56);
    rr_renderer_bezier_curve_to(renderer, 37.38, 35.10, 39.49, 42.95, 35.95,
                                49.08);
    rr_renderer_bezier_curve_to(renderer, 34.24, 52.03, 31.44, 54.18, 28.15,
                                55.06);
    rr_renderer_bezier_curve_to(renderer, 24.87, 55.94, 21.37, 55.48, 18.42,
                                53.78);
    rr_renderer_bezier_curve_to(renderer, 12.28, 50.24, 10.18, 42.39, 13.72,
                                36.25);
    rr_renderer_bezier_curve_to(renderer, 17.26, 30.12, 25.11, 28.01, 31.25,
                                31.56);
    rr_renderer_fill(renderer);
    rr_renderer_set_fill(renderer, 0xff4f3e0d);
    rr_renderer_begin_path(renderer);
    rr_renderer_move_to(renderer, 60.63, 6.32);
    rr_renderer_line_to(renderer, 35.80, 49.34);
    rr_renderer_line_to(renderer, 13.71, 36.59);
    rr_renderer_line_to(renderer, 38.54, -6.42);
    rr_renderer_fill(renderer);
    rr_renderer_set_fill(renderer, 0xff4f3e0d);
    rr_renderer_begin_path(renderer);
    rr_renderer_move_to(renderer, -28.66, 10.46);
    rr_renderer_bezier_curve_to(renderer, -34.44, 10.46, -39.11, 5.78, -39.11,
                                0.00);
    rr_renderer_bezier_curve_to(renderer, -39.11, -5.77, -34.44, -10.45, -28.66,
                                -10.45);
    rr_renderer_bezier_curve_to(renderer, -33.20, -4.22, -33.20, 4.23, -28.66,
                                10.46);
    rr_renderer_fill(renderer);
    rr_renderer_set_fill(renderer, 0xff4f3e0d);
    rr_renderer_begin_path(renderer);
    rr_renderer_move_to(renderer, 28.66, -10.45);
    rr_renderer_bezier_curve_to(renderer, 34.43, -10.45, 39.11, -5.77, 39.11,
                                0.00);
    rr_renderer_bezier_curve_to(renderer, 39.11, 5.78, 34.43, 10.46, 28.66,
                                10.46);
    rr_renderer_bezier_curve_to(renderer, 33.19, 4.23, 33.19, -4.22, 28.66,
                                -10.45);
    rr_renderer_fill(renderer);
    rr_renderer_set_fill(renderer, 0xff4f3e0d);
    rr_renderer_begin_path(renderer);
    rr_renderer_move_to(renderer, -5.28, 30.05);
    rr_renderer_bezier_curve_to(renderer, -8.16, 35.05, -14.55, 36.76, -19.55,
                                33.88);
    rr_renderer_bezier_curve_to(renderer, -24.56, 30.99, -26.27, 24.60, -23.39,
                                19.60);
    rr_renderer_bezier_curve_to(renderer, -20.26, 26.64, -12.94, 30.86, -5.28,
                                30.05);
    rr_renderer_fill(renderer);
    rr_renderer_set_fill(renderer, 0xff4f3e0d);
    rr_renderer_begin_path(renderer);
    rr_renderer_move_to(renderer, 5.27, -30.05);
    rr_renderer_bezier_curve_to(renderer, 8.15, -35.04, 14.54, -36.75, 19.54,
                                -33.87);
    rr_renderer_bezier_curve_to(renderer, 24.55, -30.98, 26.27, -24.59, 23.38,
                                -19.60);
    rr_renderer_bezier_curve_to(renderer, 20.25, -26.64, 12.93, -30.86, 5.27,
                                -30.05);
    rr_renderer_fill(renderer);
    rr_renderer_set_fill(renderer, 0xff4f3e0d);
    rr_renderer_begin_path(renderer);
    rr_renderer_move_to(renderer, -23.37, -19.61);
    rr_renderer_bezier_curve_to(renderer, -26.26, -24.61, -24.54, -31.00,
                                -19.54, -33.88);
    rr_renderer_bezier_curve_to(renderer, -14.53, -36.77, -8.14, -35.05, -5.26,
                                -30.04);
    rr_renderer_bezier_curve_to(renderer, -12.92, -30.86, -20.24, -26.65,
                                -23.37, -19.61);
    rr_renderer_fill(renderer);
    rr_renderer_set_fill(renderer, 0xff4f3e0d);
    rr_renderer_begin_path(renderer);
    rr_renderer_move_to(renderer, 23.37, 19.61);
    rr_renderer_bezier_curve_to(renderer, 26.25, 24.62, 24.53, 31.01, 19.53,
                                33.89);
    rr_renderer_bezier_curve_to(renderer, 14.52, 36.77, 8.13, 35.05, 5.25,
                                30.05);
    rr_renderer_bezier_curve_to(renderer, 12.91, 30.87, 20.23, 26.65, 23.37,
                                19.61);
    rr_renderer_fill(renderer);
}