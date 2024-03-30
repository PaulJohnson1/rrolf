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

void rr_ankylosaurus_body_draw(struct rr_renderer *renderer)
{
    rr_renderer_set_fill(renderer, 0xff6a5045);
    rr_renderer_begin_path(renderer);
    rr_renderer_move_to(renderer, -18.30, -87.97);
    rr_renderer_bezier_curve_to(renderer, 49.30, -87.97, 104.09, -48.57, 104.09,
                                0.02);
    rr_renderer_bezier_curve_to(renderer, 104.09, 23.35, 91.20, 45.73, 68.25,
                                62.23);
    rr_renderer_bezier_curve_to(renderer, 45.29, 78.73, 14.16, 88.00, -18.30,
                                88.00);
    rr_renderer_bezier_curve_to(renderer, -85.89, 88.00, -140.69, 48.61,
                                -140.69, 0.02);
    rr_renderer_bezier_curve_to(renderer, -140.69, -48.57, -85.89, -87.97,
                                -18.30, -87.97);
    rr_renderer_fill(renderer);
    rr_renderer_set_fill(renderer, 0xff856456);
    rr_renderer_begin_path(renderer);
    rr_renderer_move_to(renderer, -120.56, 13.77);
    rr_renderer_bezier_curve_to(renderer, -109.80, 13.77, -101.08, 22.32,
                                -101.08, 32.87);
    rr_renderer_bezier_curve_to(renderer, -101.08, 37.94, -103.13, 42.80,
                                -106.79, 46.38);
    rr_renderer_bezier_curve_to(renderer, -110.44, 49.96, -115.39, 51.97,
                                -120.56, 51.97);
    rr_renderer_bezier_curve_to(renderer, -131.32, 51.97, -140.04, 43.42,
                                -140.04, 32.87);
    rr_renderer_bezier_curve_to(renderer, -140.04, 22.32, -131.32, 13.77,
                                -120.56, 13.77);
    rr_renderer_fill(renderer);
    rr_renderer_set_fill(renderer, 0xff6a5045);
    rr_renderer_begin_path(renderer);
    rr_renderer_move_to(renderer, -120.56, 11.20);
    rr_renderer_bezier_curve_to(renderer, -108.35, 11.20, -98.46, 20.90, -98.46,
                                32.87);
    rr_renderer_bezier_curve_to(renderer, -98.46, 38.62, -100.78, 44.14,
                                -104.93, 48.20);
    rr_renderer_bezier_curve_to(renderer, -109.07, 52.27, -114.70, 54.55,
                                -120.56, 54.55);
    rr_renderer_bezier_curve_to(renderer, -132.77, 54.55, -142.66, 44.85,
                                -142.66, 32.87);
    rr_renderer_bezier_curve_to(renderer, -142.66, 20.90, -132.77, 11.20,
                                -120.56, 11.20);
    rr_renderer_move_to(renderer, -120.56, 20.89);
    rr_renderer_bezier_curve_to(renderer, -127.42, 20.89, -132.97, 26.26,
                                -132.97, 32.87);
    rr_renderer_bezier_curve_to(renderer, -132.97, 39.49, -127.42, 44.86,
                                -120.56, 44.86);
    rr_renderer_bezier_curve_to(renderer, -113.70, 44.86, -108.15, 39.49,
                                -108.15, 32.87);
    rr_renderer_bezier_curve_to(renderer, -108.15, 26.26, -113.70, 20.89,
                                -120.56, 20.89);
    rr_renderer_fill(renderer);
    rr_renderer_set_fill(renderer, 0xff856456);
    rr_renderer_begin_path(renderer);
    rr_renderer_move_to(renderer, -120.56, -13.78);
    rr_renderer_bezier_curve_to(renderer, -109.80, -13.78, -101.08, -22.33,
                                -101.08, -32.88);
    rr_renderer_bezier_curve_to(renderer, -101.08, -37.94, -103.13, -42.80,
                                -106.78, -46.38);
    rr_renderer_bezier_curve_to(renderer, -110.44, -49.96, -115.39, -51.97,
                                -120.56, -51.97);
    rr_renderer_bezier_curve_to(renderer, -131.31, -51.97, -140.03, -43.42,
                                -140.03, -32.88);
    rr_renderer_bezier_curve_to(renderer, -140.03, -22.33, -131.31, -13.78,
                                -120.56, -13.78);
    rr_renderer_fill(renderer);
    rr_renderer_set_fill(renderer, 0xff6a5045);
    rr_renderer_begin_path(renderer);
    rr_renderer_move_to(renderer, -120.56, -11.20);
    rr_renderer_bezier_curve_to(renderer, -108.35, -11.20, -98.45, -20.91,
                                -98.45, -32.88);
    rr_renderer_bezier_curve_to(renderer, -98.45, -38.63, -100.78, -44.14,
                                -104.93, -48.20);
    rr_renderer_bezier_curve_to(renderer, -109.07, -52.27, -114.70, -54.55,
                                -120.56, -54.55);
    rr_renderer_bezier_curve_to(renderer, -132.77, -54.55, -142.66, -44.85,
                                -142.66, -32.88);
    rr_renderer_bezier_curve_to(renderer, -142.66, -20.91, -132.77, -11.20,
                                -120.56, -11.20);
    rr_renderer_move_to(renderer, -120.56, -20.89);
    rr_renderer_bezier_curve_to(renderer, -127.41, -20.89, -132.97, -26.26,
                                -132.97, -32.88);
    rr_renderer_bezier_curve_to(renderer, -132.97, -39.50, -127.41, -44.86,
                                -120.56, -44.86);
    rr_renderer_bezier_curve_to(renderer, -113.70, -44.86, -108.15, -39.50,
                                -108.15, -32.88);
    rr_renderer_bezier_curve_to(renderer, -108.15, -26.26, -113.70, -20.89,
                                -120.56, -20.89);
    rr_renderer_fill(renderer);
    rr_renderer_set_fill(renderer, 0xff856456);
    rr_renderer_begin_path(renderer);
    rr_renderer_move_to(renderer, -1.63, 50.37);
    rr_renderer_bezier_curve_to(renderer, 10.41, 50.37, 20.17, 59.95, 20.17,
                                71.77);
    rr_renderer_bezier_curve_to(renderer, 20.17, 77.44, 17.87, 82.88, 13.79,
                                86.89);
    rr_renderer_bezier_curve_to(renderer, 9.70, 90.91, 4.15, 93.16, -1.63,
                                93.16);
    rr_renderer_bezier_curve_to(renderer, -13.67, 93.16, -23.44, 83.58, -23.44,
                                71.77);
    rr_renderer_bezier_curve_to(renderer, -23.44, 59.95, -13.67, 50.37, -1.63,
                                50.37);
    rr_renderer_fill(renderer);
    rr_renderer_set_fill(renderer, 0xff6a5045);
    rr_renderer_begin_path(renderer);
    rr_renderer_move_to(renderer, -1.63, 47.49);
    rr_renderer_bezier_curve_to(renderer, 12.03, 47.49, 23.11, 58.36, 23.11,
                                71.77);
    rr_renderer_bezier_curve_to(renderer, 23.11, 78.21, 20.50, 84.38, 15.86,
                                88.94);
    rr_renderer_bezier_curve_to(renderer, 11.22, 93.49, 4.93, 96.05, -1.63,
                                96.05);
    rr_renderer_bezier_curve_to(renderer, -15.30, 96.05, -26.38, 85.18, -26.38,
                                71.77);
    rr_renderer_bezier_curve_to(renderer, -26.38, 58.36, -15.30, 47.49, -1.63,
                                47.49);
    rr_renderer_move_to(renderer, -1.63, 58.35);
    rr_renderer_bezier_curve_to(renderer, -9.30, 58.35, -15.52, 64.36, -15.52,
                                71.77);
    rr_renderer_bezier_curve_to(renderer, -15.52, 79.18, -9.30, 85.19, -1.63,
                                85.19);
    rr_renderer_bezier_curve_to(renderer, 6.04, 85.19, 12.25, 79.18, 12.25,
                                71.77);
    rr_renderer_bezier_curve_to(renderer, 12.25, 64.36, 6.04, 58.35, -1.63,
                                58.35);
    rr_renderer_fill(renderer);
    rr_renderer_set_fill(renderer, 0xff856456);
    rr_renderer_begin_path(renderer);
    rr_renderer_move_to(renderer, -46.46, 50.38);
    rr_renderer_bezier_curve_to(renderer, -34.42, 50.38, -24.66, 59.95, -24.66,
                                71.77);
    rr_renderer_bezier_curve_to(renderer, -24.66, 77.44, -26.95, 82.88, -31.04,
                                86.90);
    rr_renderer_bezier_curve_to(renderer, -35.13, 90.91, -40.68, 93.16, -46.46,
                                93.16);
    rr_renderer_bezier_curve_to(renderer, -58.50, 93.16, -68.26, 83.58, -68.26,
                                71.77);
    rr_renderer_bezier_curve_to(renderer, -68.26, 59.95, -58.50, 50.38, -46.46,
                                50.38);
    rr_renderer_fill(renderer);
    rr_renderer_set_fill(renderer, 0xff6a5045);
    rr_renderer_begin_path(renderer);
    rr_renderer_move_to(renderer, -46.46, 47.49);
    rr_renderer_bezier_curve_to(renderer, -32.80, 47.49, -21.72, 58.36, -21.72,
                                71.77);
    rr_renderer_bezier_curve_to(renderer, -21.72, 78.21, -24.32, 84.39, -28.96,
                                88.94);
    rr_renderer_bezier_curve_to(renderer, -33.61, 93.49, -39.90, 96.05, -46.46,
                                96.05);
    rr_renderer_bezier_curve_to(renderer, -60.13, 96.05, -71.21, 85.18, -71.21,
                                71.77);
    rr_renderer_bezier_curve_to(renderer, -71.21, 58.36, -60.13, 47.49, -46.46,
                                47.49);
    rr_renderer_move_to(renderer, -46.46, 58.35);
    rr_renderer_bezier_curve_to(renderer, -54.13, 58.35, -60.35, 64.36, -60.35,
                                71.77);
    rr_renderer_bezier_curve_to(renderer, -60.35, 79.18, -54.13, 85.19, -46.46,
                                85.19);
    rr_renderer_bezier_curve_to(renderer, -38.79, 85.19, -32.57, 79.18, -32.57,
                                71.77);
    rr_renderer_bezier_curve_to(renderer, -32.57, 64.36, -38.79, 58.35, -46.46,
                                58.35);
    rr_renderer_fill(renderer);
    rr_renderer_set_fill(renderer, 0xff856456);
    rr_renderer_begin_path(renderer);
    rr_renderer_move_to(renderer, -88.31, 37.49);
    rr_renderer_bezier_curve_to(renderer, -77.56, 37.49, -68.85, 46.04, -68.85,
                                56.59);
    rr_renderer_bezier_curve_to(renderer, -68.85, 61.66, -70.90, 66.51, -74.55,
                                70.10);
    rr_renderer_bezier_curve_to(renderer, -78.20, 73.68, -83.15, 75.69, -88.31,
                                75.69);
    rr_renderer_bezier_curve_to(renderer, -99.07, 75.69, -107.78, 67.14,
                                -107.78, 56.59);
    rr_renderer_bezier_curve_to(renderer, -107.78, 46.04, -99.07, 37.49, -88.31,
                                37.49);
    rr_renderer_fill(renderer);
    rr_renderer_set_fill(renderer, 0xff6a5045);
    rr_renderer_begin_path(renderer);
    rr_renderer_move_to(renderer, -88.32, 34.92);
    rr_renderer_bezier_curve_to(renderer, -76.12, 34.92, -66.22, 44.62, -66.22,
                                56.59);
    rr_renderer_bezier_curve_to(renderer, -66.22, 62.34, -68.55, 67.85, -72.69,
                                71.92);
    rr_renderer_bezier_curve_to(renderer, -76.84, 75.98, -82.46, 78.27, -88.32,
                                78.27);
    rr_renderer_bezier_curve_to(renderer, -100.52, 78.27, -110.41, 68.56,
                                -110.41, 56.59);
    rr_renderer_bezier_curve_to(renderer, -110.41, 44.62, -100.52, 34.92,
                                -88.32, 34.92);
    rr_renderer_move_to(renderer, -88.32, 44.61);
    rr_renderer_bezier_curve_to(renderer, -95.17, 44.61, -100.72, 49.97,
                                -100.72, 56.59);
    rr_renderer_bezier_curve_to(renderer, -100.72, 63.21, -95.17, 68.58, -88.32,
                                68.58);
    rr_renderer_bezier_curve_to(renderer, -81.47, 68.58, -75.92, 63.21, -75.92,
                                56.59);
    rr_renderer_bezier_curve_to(renderer, -75.92, 49.97, -81.47, 44.61, -88.32,
                                44.61);
    rr_renderer_fill(renderer);
    rr_renderer_set_fill(renderer, 0xff856456);
    rr_renderer_begin_path(renderer);
    rr_renderer_move_to(renderer, 38.50, 43.19);
    rr_renderer_bezier_curve_to(renderer, 49.25, 43.19, 57.97, 51.74, 57.97,
                                62.29);
    rr_renderer_bezier_curve_to(renderer, 57.97, 67.35, 55.92, 72.21, 52.26,
                                75.79);
    rr_renderer_bezier_curve_to(renderer, 48.61, 79.38, 43.66, 81.39, 38.50,
                                81.39);
    rr_renderer_bezier_curve_to(renderer, 27.75, 81.39, 19.03, 72.84, 19.03,
                                62.29);
    rr_renderer_bezier_curve_to(renderer, 19.03, 51.74, 27.75, 43.19, 38.50,
                                43.19);
    rr_renderer_fill(renderer);
    rr_renderer_set_fill(renderer, 0xff6a5045);
    rr_renderer_begin_path(renderer);
    rr_renderer_move_to(renderer, 38.50, 40.62);
    rr_renderer_bezier_curve_to(renderer, 50.70, 40.62, 60.59, 50.32, 60.59,
                                62.29);
    rr_renderer_bezier_curve_to(renderer, 60.59, 68.04, 58.26, 73.55, 54.12,
                                77.62);
    rr_renderer_bezier_curve_to(renderer, 49.98, 81.68, 44.36, 83.97, 38.50,
                                83.97);
    rr_renderer_bezier_curve_to(renderer, 26.30, 83.97, 16.40, 74.26, 16.40,
                                62.29);
    rr_renderer_bezier_curve_to(renderer, 16.40, 50.32, 26.30, 40.62, 38.50,
                                40.62);
    rr_renderer_move_to(renderer, 38.50, 50.31);
    rr_renderer_bezier_curve_to(renderer, 31.65, 50.31, 26.10, 55.67, 26.10,
                                62.29);
    rr_renderer_bezier_curve_to(renderer, 26.10, 68.91, 31.65, 74.27, 38.50,
                                74.27);
    rr_renderer_bezier_curve_to(renderer, 45.35, 74.27, 50.90, 68.91, 50.90,
                                62.29);
    rr_renderer_bezier_curve_to(renderer, 50.90, 55.67, 45.35, 50.31, 38.50,
                                50.31);
    rr_renderer_fill(renderer);
    rr_renderer_set_fill(renderer, 0xff856456);
    rr_renderer_begin_path(renderer);
    rr_renderer_move_to(renderer, -1.63, -50.38);
    rr_renderer_bezier_curve_to(renderer, 10.41, -50.38, 20.17, -59.95, 20.17,
                                -71.77);
    rr_renderer_bezier_curve_to(renderer, 20.17, -77.44, 17.88, -82.88, 13.79,
                                -86.90);
    rr_renderer_bezier_curve_to(renderer, 9.70, -90.91, 4.15, -93.16, -1.63,
                                -93.16);
    rr_renderer_bezier_curve_to(renderer, -13.67, -93.16, -23.43, -83.58,
                                -23.43, -71.77);
    rr_renderer_bezier_curve_to(renderer, -23.43, -59.95, -13.67, -50.38, -1.63,
                                -50.38);
    rr_renderer_fill(renderer);
    rr_renderer_set_fill(renderer, 0xff6a5045);
    rr_renderer_begin_path(renderer);
    rr_renderer_move_to(renderer, -1.63, -47.49);
    rr_renderer_bezier_curve_to(renderer, 12.03, -47.49, 23.11, -58.36, 23.11,
                                -71.77);
    rr_renderer_bezier_curve_to(renderer, 23.11, -78.21, 20.50, -84.39, 15.86,
                                -88.94);
    rr_renderer_bezier_curve_to(renderer, 11.22, -93.49, 4.93, -96.05, -1.63,
                                -96.05);
    rr_renderer_bezier_curve_to(renderer, -15.30, -96.05, -26.38, -85.18,
                                -26.38, -71.77);
    rr_renderer_bezier_curve_to(renderer, -26.38, -58.36, -15.30, -47.49, -1.63,
                                -47.49);
    rr_renderer_move_to(renderer, -1.63, -58.35);
    rr_renderer_bezier_curve_to(renderer, -9.30, -58.35, -15.52, -64.36, -15.52,
                                -71.77);
    rr_renderer_bezier_curve_to(renderer, -15.52, -79.18, -9.30, -85.19, -1.63,
                                -85.19);
    rr_renderer_bezier_curve_to(renderer, 6.04, -85.19, 12.26, -79.18, 12.26,
                                -71.77);
    rr_renderer_bezier_curve_to(renderer, 12.26, -64.36, 6.04, -58.35, -1.63,
                                -58.35);
    rr_renderer_fill(renderer);
    rr_renderer_set_fill(renderer, 0xff856456);
    rr_renderer_begin_path(renderer);
    rr_renderer_move_to(renderer, -46.46, -50.38);
    rr_renderer_bezier_curve_to(renderer, -34.42, -50.38, -24.65, -59.96,
                                -24.65, -71.77);
    rr_renderer_bezier_curve_to(renderer, -24.65, -77.45, -26.95, -82.89,
                                -31.04, -86.90);
    rr_renderer_bezier_curve_to(renderer, -35.13, -90.91, -40.68, -93.16,
                                -46.46, -93.16);
    rr_renderer_bezier_curve_to(renderer, -58.50, -93.16, -68.26, -83.59,
                                -68.26, -71.77);
    rr_renderer_bezier_curve_to(renderer, -68.26, -59.96, -58.50, -50.38,
                                -46.46, -50.38);
    rr_renderer_fill(renderer);
    rr_renderer_set_fill(renderer, 0xff6a5045);
    rr_renderer_begin_path(renderer);
    rr_renderer_move_to(renderer, -46.46, -47.50);
    rr_renderer_bezier_curve_to(renderer, -32.79, -47.50, -21.72, -58.37,
                                -21.72, -71.77);
    rr_renderer_bezier_curve_to(renderer, -21.72, -78.21, -24.32, -84.39,
                                -28.96, -88.94);
    rr_renderer_bezier_curve_to(renderer, -33.60, -93.49, -39.90, -96.05,
                                -46.46, -96.05);
    rr_renderer_bezier_curve_to(renderer, -60.13, -96.05, -71.20, -85.18,
                                -71.20, -71.77);
    rr_renderer_bezier_curve_to(renderer, -71.20, -58.37, -60.13, -47.50,
                                -46.46, -47.50);
    rr_renderer_move_to(renderer, -46.46, -58.35);
    rr_renderer_bezier_curve_to(renderer, -54.13, -58.35, -60.35, -64.36,
                                -60.35, -71.77);
    rr_renderer_bezier_curve_to(renderer, -60.35, -79.19, -54.13, -85.20,
                                -46.46, -85.20);
    rr_renderer_bezier_curve_to(renderer, -38.79, -85.20, -32.57, -79.19,
                                -32.57, -71.77);
    rr_renderer_bezier_curve_to(renderer, -32.57, -64.36, -38.79, -58.35,
                                -46.46, -58.35);
    rr_renderer_fill(renderer);
    rr_renderer_set_fill(renderer, 0xff856456);
    rr_renderer_begin_path(renderer);
    rr_renderer_move_to(renderer, -88.31, -37.49);
    rr_renderer_bezier_curve_to(renderer, -77.56, -37.49, -68.85, -46.05,
                                -68.85, -56.59);
    rr_renderer_bezier_curve_to(renderer, -68.85, -61.66, -70.90, -66.52,
                                -74.55, -70.10);
    rr_renderer_bezier_curve_to(renderer, -78.20, -73.68, -83.15, -75.69,
                                -88.31, -75.69);
    rr_renderer_bezier_curve_to(renderer, -99.06, -75.69, -107.78, -67.14,
                                -107.78, -56.59);
    rr_renderer_bezier_curve_to(renderer, -107.78, -46.05, -99.06, -37.49,
                                -88.31, -37.49);
    rr_renderer_fill(renderer);
    rr_renderer_set_fill(renderer, 0xff6a5045);
    rr_renderer_begin_path(renderer);
    rr_renderer_move_to(renderer, -88.32, -34.92);
    rr_renderer_bezier_curve_to(renderer, -76.11, -34.92, -66.22, -44.62,
                                -66.22, -56.60);
    rr_renderer_bezier_curve_to(renderer, -66.22, -62.34, -68.55, -67.86,
                                -72.69, -71.92);
    rr_renderer_bezier_curve_to(renderer, -76.84, -75.99, -82.46, -78.27,
                                -88.32, -78.27);
    rr_renderer_bezier_curve_to(renderer, -100.52, -78.27, -110.41, -68.57,
                                -110.41, -56.60);
    rr_renderer_bezier_curve_to(renderer, -110.41, -44.62, -100.52, -34.92,
                                -88.32, -34.92);
    rr_renderer_move_to(renderer, -88.32, -44.61);
    rr_renderer_bezier_curve_to(renderer, -95.16, -44.61, -100.72, -49.98,
                                -100.72, -56.60);
    rr_renderer_bezier_curve_to(renderer, -100.72, -63.21, -95.16, -68.58,
                                -88.32, -68.58);
    rr_renderer_bezier_curve_to(renderer, -81.47, -68.58, -75.91, -63.21,
                                -75.91, -56.60);
    rr_renderer_bezier_curve_to(renderer, -75.91, -49.98, -81.47, -44.61,
                                -88.32, -44.61);
    rr_renderer_fill(renderer);
    rr_renderer_set_fill(renderer, 0xff856456);
    rr_renderer_begin_path(renderer);
    rr_renderer_move_to(renderer, 38.50, -43.19);
    rr_renderer_bezier_curve_to(renderer, 49.25, -43.19, 57.97, -51.74, 57.97,
                                -62.29);
    rr_renderer_bezier_curve_to(renderer, 57.97, -67.36, 55.92, -72.21, 52.27,
                                -75.80);
    rr_renderer_bezier_curve_to(renderer, 48.61, -79.38, 43.66, -81.39, 38.50,
                                -81.39);
    rr_renderer_bezier_curve_to(renderer, 27.75, -81.39, 19.03, -72.84, 19.03,
                                -62.29);
    rr_renderer_bezier_curve_to(renderer, 19.03, -51.74, 27.75, -43.19, 38.50,
                                -43.19);
    rr_renderer_fill(renderer);
    rr_renderer_set_fill(renderer, 0xff6a5045);
    rr_renderer_begin_path(renderer);
    rr_renderer_move_to(renderer, 38.50, -40.62);
    rr_renderer_bezier_curve_to(renderer, 50.70, -40.62, 60.59, -50.32, 60.59,
                                -62.29);
    rr_renderer_bezier_curve_to(renderer, 60.59, -68.04, 58.26, -73.55, 54.12,
                                -77.62);
    rr_renderer_bezier_curve_to(renderer, 49.98, -81.68, 44.36, -83.97, 38.50,
                                -83.97);
    rr_renderer_bezier_curve_to(renderer, 26.30, -83.97, 16.41, -74.26, 16.41,
                                -62.29);
    rr_renderer_bezier_curve_to(renderer, 16.41, -50.32, 26.30, -40.62, 38.50,
                                -40.62);
    rr_renderer_move_to(renderer, 38.50, -50.31);
    rr_renderer_bezier_curve_to(renderer, 31.65, -50.31, 26.10, -55.68, 26.10,
                                -62.29);
    rr_renderer_bezier_curve_to(renderer, 26.10, -68.91, 31.65, -74.28, 38.50,
                                -74.28);
    rr_renderer_bezier_curve_to(renderer, 45.35, -74.28, 50.90, -68.91, 50.90,
                                -62.29);
    rr_renderer_bezier_curve_to(renderer, 50.90, -55.68, 45.35, -50.31, 38.50,
                                -50.31);
    rr_renderer_fill(renderer);
    rr_renderer_set_fill(renderer, 0xff856456);
    rr_renderer_begin_path(renderer);
    rr_renderer_move_to(renderer, -18.31, -75.00);
    rr_renderer_bezier_curve_to(renderer, 41.04, -75.00, 89.16, -41.42, 89.16,
                                0.01);
    rr_renderer_bezier_curve_to(renderer, 89.16, 19.90, 77.83, 38.98, 57.68,
                                53.05);
    rr_renderer_bezier_curve_to(renderer, 37.53, 67.12, 10.19, 75.02, -18.31,
                                75.02);
    rr_renderer_bezier_curve_to(renderer, -77.66, 75.02, -125.78, 41.44,
                                -125.78, 0.01);
    rr_renderer_bezier_curve_to(renderer, -125.78, -41.42, -77.66, -75.00,
                                -18.31, -75.00);
    rr_renderer_fill(renderer);
    rr_renderer_set_fill(renderer, 0xff6a5045);
    rr_renderer_begin_path(renderer);
    rr_renderer_move_to(renderer, 28.69, -46.87);
    rr_renderer_bezier_curve_to(renderer, -10.18, -59.19, -52.34, -55.76,
                                -88.71, -37.29);
    rr_renderer_line_to(renderer, -82.14, -24.35);
    rr_renderer_bezier_curve_to(renderer, -49.17, -41.09, -10.94, -44.21, 24.30,
                                -33.03);
    rr_renderer_fill(renderer);
    rr_renderer_set_fill(renderer, 0xff6a5045);
    rr_renderer_begin_path(renderer);
    rr_renderer_move_to(renderer, 26.47, -47.09);
    rr_renderer_bezier_curve_to(renderer, 30.40, -47.09, 33.59, -43.90, 33.59,
                                -39.97);
    rr_renderer_bezier_curve_to(renderer, 33.59, -38.08, 32.84, -36.27, 31.50,
                                -34.94);
    rr_renderer_bezier_curve_to(renderer, 30.17, -33.60, 28.36, -32.85, 26.47,
                                -32.85);
    rr_renderer_bezier_curve_to(renderer, 22.54, -32.85, 19.35, -36.04, 19.35,
                                -39.97);
    rr_renderer_bezier_curve_to(renderer, 19.35, -43.90, 22.54, -47.09, 26.47,
                                -47.09);
    rr_renderer_fill(renderer);
    rr_renderer_set_fill(renderer, 0xff6a5045);
    rr_renderer_begin_path(renderer);
    rr_renderer_move_to(renderer, -85.72, -37.85);
    rr_renderer_bezier_curve_to(renderer, -81.78, -37.85, -78.60, -34.67,
                                -78.60, -30.73);
    rr_renderer_bezier_curve_to(renderer, -78.60, -28.85, -79.35, -27.03,
                                -80.68, -25.70);
    rr_renderer_bezier_curve_to(renderer, -82.02, -24.36, -83.83, -23.61,
                                -85.72, -23.61);
    rr_renderer_bezier_curve_to(renderer, -89.65, -23.61, -92.84, -26.80,
                                -92.84, -30.73);
    rr_renderer_bezier_curve_to(renderer, -92.84, -34.67, -89.65, -37.85,
                                -85.72, -37.85);
    rr_renderer_fill(renderer);
    rr_renderer_set_fill(renderer, 0xff6a5045);
    rr_renderer_begin_path(renderer);
    rr_renderer_move_to(renderer, 28.69, 46.87);
    rr_renderer_bezier_curve_to(renderer, -10.18, 59.19, -52.34, 55.76, -88.71,
                                37.29);
    rr_renderer_line_to(renderer, -82.14, 24.35);
    rr_renderer_bezier_curve_to(renderer, -49.17, 41.09, -10.94, 44.21, 24.30,
                                33.03);
    rr_renderer_fill(renderer);
    rr_renderer_set_fill(renderer, 0xff6a5045);
    rr_renderer_begin_path(renderer);
    rr_renderer_move_to(renderer, 26.47, 47.09);
    rr_renderer_bezier_curve_to(renderer, 30.40, 47.09, 33.59, 43.90, 33.59,
                                39.97);
    rr_renderer_bezier_curve_to(renderer, 33.59, 38.08, 32.84, 36.27, 31.50,
                                34.94);
    rr_renderer_bezier_curve_to(renderer, 30.17, 33.60, 28.36, 32.85, 26.47,
                                32.85);
    rr_renderer_bezier_curve_to(renderer, 22.54, 32.85, 19.35, 36.04, 19.35,
                                39.97);
    rr_renderer_bezier_curve_to(renderer, 19.35, 43.90, 22.54, 47.09, 26.47,
                                47.09);
    rr_renderer_fill(renderer);
    rr_renderer_set_fill(renderer, 0xff6a5045);
    rr_renderer_begin_path(renderer);
    rr_renderer_move_to(renderer, -85.72, 37.85);
    rr_renderer_bezier_curve_to(renderer, -81.78, 37.85, -78.60, 34.66, -78.60,
                                30.73);
    rr_renderer_bezier_curve_to(renderer, -78.60, 28.84, -79.35, 27.03, -80.68,
                                25.70);
    rr_renderer_bezier_curve_to(renderer, -82.02, 24.36, -83.83, 23.61, -85.72,
                                23.61);
    rr_renderer_bezier_curve_to(renderer, -89.65, 23.61, -92.83, 26.80, -92.83,
                                30.73);
    rr_renderer_bezier_curve_to(renderer, -92.83, 34.66, -89.65, 37.85, -85.72,
                                37.85);
    rr_renderer_fill(renderer);
    rr_renderer_set_fill(renderer, 0xff6a5045);
    rr_renderer_begin_path(renderer);
    rr_renderer_move_to(renderer, 102.40, -47.78);
    rr_renderer_bezier_curve_to(renderer, 128.79, -47.78, 150.18, -26.39,
                                150.18, 0.00);
    rr_renderer_bezier_curve_to(renderer, 150.18, 12.67, 145.14, 24.83, 136.18,
                                33.79);
    rr_renderer_bezier_curve_to(renderer, 127.22, 42.75, 115.07, 47.78, 102.40,
                                47.78);
    rr_renderer_line_to(renderer, 86.99, 47.78);
    rr_renderer_bezier_curve_to(renderer, 60.60, 47.78, 39.21, 26.39, 39.21,
                                0.00);
    rr_renderer_bezier_curve_to(renderer, 39.21, -26.39, 60.60, -47.78, 86.99,
                                -47.78);
    rr_renderer_fill(renderer);
    rr_renderer_set_fill(renderer, 0xff856456);
    rr_renderer_begin_path(renderer);
    rr_renderer_move_to(renderer, 101.58, -34.34);
    rr_renderer_bezier_curve_to(renderer, 120.54, -34.34, 135.92, -18.97,
                                135.92, -0.00);
    rr_renderer_bezier_curve_to(renderer, 135.92, 9.11, 132.30, 17.84, 125.86,
                                24.28);
    rr_renderer_bezier_curve_to(renderer, 119.42, 30.72, 110.69, 34.34, 101.58,
                                34.34);
    rr_renderer_line_to(renderer, 59.29, 34.34);
    rr_renderer_bezier_curve_to(renderer, 40.32, 34.34, 24.95, 18.96, 24.95,
                                -0.00);
    rr_renderer_bezier_curve_to(renderer, 24.95, -18.97, 40.32, -34.34, 59.29,
                                -34.34);
    rr_renderer_fill(renderer);
    rr_renderer_set_fill(renderer, 0xff6a5045);
    rr_renderer_begin_path(renderer);
    rr_renderer_move_to(renderer, 50.77, -7.75);
    rr_renderer_bezier_curve_to(renderer, 55.05, -7.75, 58.52, -4.28, 58.52,
                                0.00);
    rr_renderer_bezier_curve_to(renderer, 58.52, 2.06, 57.70, 4.03, 56.25,
                                5.48);
    rr_renderer_bezier_curve_to(renderer, 54.80, 6.93, 52.83, 7.75, 50.77,
                                7.75);
    rr_renderer_line_to(renderer, -99.68, 7.75);
    rr_renderer_bezier_curve_to(renderer, -103.96, 7.75, -107.43, 4.28, -107.43,
                                0.00);
    rr_renderer_bezier_curve_to(renderer, -107.43, -4.28, -103.96, -7.75,
                                -99.68, -7.75);
    rr_renderer_fill(renderer);
}

void rr_ankylosaurus_head_draw(struct rr_renderer *renderer)
{
    rr_renderer_set_fill(renderer, 0xff6a5045);
    rr_renderer_begin_path(renderer);
    rr_renderer_move_to(renderer, 36.77, -29.06);
    rr_renderer_bezier_curve_to(renderer, 38.57, -37.80, 23.88, -44.18, 14.83,
                                -49.14);
    rr_renderer_bezier_curve_to(renderer, 5.78, -54.10, -8.41, -57.07, -17.53,
                                -58.81);
    rr_renderer_bezier_curve_to(renderer, -26.64, -60.54, -35.13, -61.60,
                                -39.84, -59.55);
    rr_renderer_bezier_curve_to(renderer, -44.55, -57.51, -45.73, -52.43,
                                -45.79, -46.54);
    rr_renderer_bezier_curve_to(renderer, -45.86, -40.65, -41.39, -31.66,
                                -40.21, -24.23);
    rr_renderer_bezier_curve_to(renderer, -39.04, -16.79, -39.84, -6.75, -38.73,
                                -1.92);
    rr_renderer_bezier_curve_to(renderer, -37.61, 2.92, -40.65, 3.91, -33.52,
                                4.78);
    rr_renderer_bezier_curve_to(renderer, -26.39, 5.64, -7.67, 8.93, 4.04,
                                3.29);
    rr_renderer_bezier_curve_to(renderer, 15.76, -2.35, 34.98, -20.32, 36.77,
                                -29.06);
    rr_renderer_fill(renderer);
    rr_renderer_set_fill(renderer, 0xff6a5045);
    rr_renderer_begin_path(renderer);
    rr_renderer_move_to(renderer, 36.77, 29.06);
    rr_renderer_bezier_curve_to(renderer, 38.57, 37.80, 23.88, 44.18, 14.83,
                                49.14);
    rr_renderer_bezier_curve_to(renderer, 5.78, 54.10, -8.41, 57.07, -17.53,
                                58.81);
    rr_renderer_bezier_curve_to(renderer, -26.64, 60.54, -35.13, 61.60, -39.84,
                                59.55);
    rr_renderer_bezier_curve_to(renderer, -44.55, 57.51, -45.73, 52.43, -45.79,
                                46.54);
    rr_renderer_bezier_curve_to(renderer, -45.86, 40.65, -41.39, 31.66, -40.21,
                                24.23);
    rr_renderer_bezier_curve_to(renderer, -39.04, 16.79, -39.84, 6.75, -38.73,
                                1.92);
    rr_renderer_bezier_curve_to(renderer, -37.61, -2.92, -40.65, -3.91, -33.52,
                                -4.77);
    rr_renderer_bezier_curve_to(renderer, -26.39, -5.64, -7.67, -8.93, 4.04,
                                -3.29);
    rr_renderer_bezier_curve_to(renderer, 15.76, 2.35, 34.98, 20.32, 36.77,
                                29.06);
    rr_renderer_fill(renderer);
    rr_renderer_set_fill(renderer, 0xff6a5045);
    rr_renderer_begin_path(renderer);
    rr_renderer_move_to(renderer, 17.66, -43.21);
    rr_renderer_bezier_curve_to(renderer, 41.53, -43.21, 60.89, -23.87, 60.89,
                                0.00);
    rr_renderer_bezier_curve_to(renderer, 60.89, 11.46, 56.33, 22.45, 48.23,
                                30.56);
    rr_renderer_bezier_curve_to(renderer, 40.12, 38.66, 29.13, 43.21, 17.66,
                                43.21);
    rr_renderer_bezier_curve_to(renderer, -6.21, 43.21, -25.56, 23.87, -25.56,
                                0.00);
    rr_renderer_bezier_curve_to(renderer, -25.56, -23.87, -6.21, -43.21, 17.66,
                                -43.21);
    rr_renderer_fill(renderer);
    rr_renderer_set_fill(renderer, 0xff6a5045);
    rr_renderer_begin_path(renderer);
    rr_renderer_move_to(renderer, -18.88, -22.35);
    rr_renderer_line_to(renderer, -18.88, 22.36);
    rr_renderer_line_to(renderer, -39.33, 22.36);
    rr_renderer_line_to(renderer, -39.33, -22.35);
    rr_renderer_fill(renderer);
    rr_renderer_set_fill(renderer, 0xff856456);
    rr_renderer_begin_path(renderer);
    rr_renderer_move_to(renderer, 17.37, -30.10);
    rr_renderer_bezier_curve_to(renderer, 34.00, -30.10, 47.48, -16.62, 47.48,
                                0.00);
    rr_renderer_bezier_curve_to(renderer, 47.48, 7.99, 44.31, 15.64, 38.66,
                                21.29);
    rr_renderer_bezier_curve_to(renderer, 33.02, 26.93, 25.36, 30.10, 17.37,
                                30.10);
    rr_renderer_bezier_curve_to(renderer, 0.74, 30.10, -12.74, 16.63, -12.74,
                                0.00);
    rr_renderer_bezier_curve_to(renderer, -12.74, -16.62, 0.74, -30.10, 17.37,
                                -30.10);
    rr_renderer_fill(renderer);
    rr_renderer_set_fill(renderer, 0xff856456);
    rr_renderer_begin_path(renderer);
    rr_renderer_move_to(renderer, 22.83, 27.13);
    rr_renderer_bezier_curve_to(renderer, 17.06, 37.47, -19.82, 47.58, -28.13,
                                46.65);
    rr_renderer_bezier_curve_to(renderer, -36.43, 45.72, -28.16, 31.75, -27.01,
                                21.55);
    rr_renderer_bezier_curve_to(renderer, -25.86, 11.36, -26.83, -8.36, -21.25,
                                -14.52);
    rr_renderer_bezier_curve_to(renderer, -15.66, -20.67, -0.85, -22.31, 6.50,
                                -15.36);
    rr_renderer_bezier_curve_to(renderer, 13.84, -8.42, 28.60, 16.79, 22.83,
                                27.13);
    rr_renderer_fill(renderer);
    rr_renderer_set_fill(renderer, 0xff856456);
    rr_renderer_begin_path(renderer);
    rr_renderer_move_to(renderer, 22.83, -27.13);
    rr_renderer_bezier_curve_to(renderer, 17.06, -37.46, -19.82, -47.58, -28.13,
                                -46.65);
    rr_renderer_bezier_curve_to(renderer, -36.43, -45.72, -28.16, -31.74,
                                -27.01, -21.55);
    rr_renderer_bezier_curve_to(renderer, -25.86, -11.35, -26.83, 8.37, -21.25,
                                14.52);
    rr_renderer_bezier_curve_to(renderer, -15.66, 20.67, -0.85, 22.31, 6.50,
                                15.37);
    rr_renderer_bezier_curve_to(renderer, 13.84, 8.43, 28.60, -16.79, 22.83,
                                -27.13);
    rr_renderer_fill(renderer);
    rr_renderer_set_fill(renderer, 0xff856456);
    rr_renderer_begin_path(renderer);
    rr_renderer_move_to(renderer, -5.84, -33.59);
    rr_renderer_line_to(renderer, -5.84, 33.59);
    rr_renderer_line_to(renderer, -26.29, 33.59);
    rr_renderer_line_to(renderer, -26.29, -33.59);
    rr_renderer_fill(renderer);
    rr_renderer_set_fill(renderer, 0xff6a5045);
    rr_renderer_begin_path(renderer);
    rr_renderer_move_to(renderer, -11.20, 31.88);
    rr_renderer_bezier_curve_to(renderer, 0.81, 31.61, 12.12, 26.15, 19.80,
                                16.91);
    rr_renderer_line_to(renderer, 10.28, 9.00);
    rr_renderer_bezier_curve_to(renderer, 4.89, 15.48, -3.05, 19.31, -11.48,
                                19.50);
    rr_renderer_fill(renderer);
    rr_renderer_set_fill(renderer, 0xff6a5045);
    rr_renderer_begin_path(renderer);
    rr_renderer_move_to(renderer, 19.90, 16.89);
    rr_renderer_bezier_curve_to(renderer, 22.08, 14.27, 21.71, 10.39, 19.10,
                                8.22);
    rr_renderer_bezier_curve_to(renderer, 17.84, 7.18, 16.22, 6.68, 14.60,
                                6.83);
    rr_renderer_bezier_curve_to(renderer, 12.97, 6.98, 11.47, 7.77, 10.43,
                                9.03);
    rr_renderer_bezier_curve_to(renderer, 8.26, 11.64, 8.62, 15.52, 11.23,
                                17.70);
    rr_renderer_bezier_curve_to(renderer, 13.85, 19.87, 17.73, 19.51, 19.90,
                                16.89);
    rr_renderer_fill(renderer);
    rr_renderer_set_fill(renderer, 0xff6a5045);
    rr_renderer_begin_path(renderer);
    rr_renderer_move_to(renderer, -6.59, 29.58);
    rr_renderer_bezier_curve_to(renderer, -4.42, 26.96, -4.78, 23.08, -7.40,
                                20.91);
    rr_renderer_bezier_curve_to(renderer, -8.65, 19.87, -10.27, 19.37, -11.90,
                                19.52);
    rr_renderer_bezier_curve_to(renderer, -13.52, 19.67, -15.02, 20.46, -16.07,
                                21.72);
    rr_renderer_bezier_curve_to(renderer, -18.24, 24.33, -17.88, 28.21, -15.26,
                                30.38);
    rr_renderer_bezier_curve_to(renderer, -12.64, 32.55, -8.76, 32.19, -6.59,
                                29.58);
    rr_renderer_fill(renderer);
    rr_renderer_set_fill(renderer, 0xff6a5045);
    rr_renderer_begin_path(renderer);
    rr_renderer_move_to(renderer, -11.20, -31.89);
    rr_renderer_bezier_curve_to(renderer, 0.81, -31.62, 12.12, -26.16, 19.80,
                                -16.92);
    rr_renderer_line_to(renderer, 10.28, -9.00);
    rr_renderer_bezier_curve_to(renderer, 4.89, -15.49, -3.05, -19.32, -11.48,
                                -19.51);
    rr_renderer_fill(renderer);
    rr_renderer_set_fill(renderer, 0xff6a5045);
    rr_renderer_begin_path(renderer);
    rr_renderer_move_to(renderer, 19.91, -16.90);
    rr_renderer_bezier_curve_to(renderer, 22.08, -14.28, 21.72, -10.40, 19.10,
                                -8.23);
    rr_renderer_bezier_curve_to(renderer, 17.84, -7.19, 16.22, -6.69, 14.60,
                                -6.84);
    rr_renderer_bezier_curve_to(renderer, 12.97, -6.99, 11.47, -7.78, 10.43,
                                -9.04);
    rr_renderer_bezier_curve_to(renderer, 8.26, -11.65, 8.62, -15.53, 11.24,
                                -17.71);
    rr_renderer_bezier_curve_to(renderer, 13.85, -19.88, 17.73, -19.52, 19.91,
                                -16.90);
    rr_renderer_fill(renderer);
    rr_renderer_set_fill(renderer, 0xff6a5045);
    rr_renderer_begin_path(renderer);
    rr_renderer_move_to(renderer, -6.59, -29.59);
    rr_renderer_bezier_curve_to(renderer, -4.42, -26.97, -4.78, -23.09, -7.39,
                                -20.92);
    rr_renderer_bezier_curve_to(renderer, -8.65, -19.88, -10.27, -19.38, -11.90,
                                -19.53);
    rr_renderer_bezier_curve_to(renderer, -13.52, -19.68, -15.02, -20.47,
                                -16.06, -21.73);
    rr_renderer_bezier_curve_to(renderer, -18.24, -24.34, -17.87, -28.22,
                                -15.26, -30.40);
    rr_renderer_bezier_curve_to(renderer, -12.64, -32.57, -8.76, -32.21, -6.59,
                                -29.59);
    rr_renderer_fill(renderer);
}

void rr_ankylosaurus_tail_draw(struct rr_renderer *renderer)
{
    rr_renderer_set_fill(renderer, 0xff7d6c64);
    rr_renderer_begin_path(renderer);
    rr_renderer_move_to(renderer, -81.27, 58.06);
    rr_renderer_bezier_curve_to(renderer, -104.65, 58.06, -123.60, 39.47,
                                -123.60, 16.53);
    rr_renderer_bezier_curve_to(renderer, -123.60, 5.52, -119.14, -5.05,
                                -111.20, -12.84);
    rr_renderer_bezier_curve_to(renderer, -103.26, -20.63, -92.50, -25.00,
                                -81.27, -25.00);
    rr_renderer_bezier_curve_to(renderer, -57.89, -25.00, -38.94, -6.41, -38.94,
                                16.53);
    rr_renderer_bezier_curve_to(renderer, -38.94, 39.47, -57.89, 58.06, -81.27,
                                58.06);
    rr_renderer_fill(renderer);
    rr_renderer_set_fill(renderer, 0xff7d6c64);
    rr_renderer_begin_path(renderer);
    rr_renderer_move_to(renderer, -109.19, 30.54);
    rr_renderer_bezier_curve_to(renderer, -126.38, 30.54, -140.32, 16.87,
                                -140.32, 0.00);
    rr_renderer_bezier_curve_to(renderer, -140.32, -8.10, -137.04, -15.87,
                                -131.20, -21.60);
    rr_renderer_bezier_curve_to(renderer, -125.36, -27.33, -117.45, -30.54,
                                -109.19, -30.54);
    rr_renderer_bezier_curve_to(renderer, -92.00, -30.54, -78.06, -16.87,
                                -78.06, 0.00);
    rr_renderer_bezier_curve_to(renderer, -78.06, 16.87, -92.00, 30.54, -109.19,
                                30.54);
    rr_renderer_fill(renderer);
    rr_renderer_set_fill(renderer, 0xff7d6c64);
    rr_renderer_begin_path(renderer);
    rr_renderer_move_to(renderer, -81.27, 25.00);
    rr_renderer_bezier_curve_to(renderer, -104.65, 25.00, -123.60, 6.41,
                                -123.60, -16.53);
    rr_renderer_bezier_curve_to(renderer, -123.60, -27.55, -119.14, -38.11,
                                -111.20, -45.90);
    rr_renderer_bezier_curve_to(renderer, -103.26, -53.69, -92.50, -58.06,
                                -81.27, -58.06);
    rr_renderer_bezier_curve_to(renderer, -57.89, -58.06, -38.94, -39.47,
                                -38.94, -16.53);
    rr_renderer_bezier_curve_to(renderer, -38.94, 6.41, -57.89, 25.00, -81.27,
                                25.00);
    rr_renderer_fill(renderer);
    rr_renderer_set_fill(renderer, 0xff917d73);
    rr_renderer_begin_path(renderer);
    rr_renderer_move_to(renderer, -82.43, 47.08);
    rr_renderer_bezier_curve_to(renderer, -99.62, 47.08, -113.55, 33.40,
                                -113.55, 16.53);
    rr_renderer_bezier_curve_to(renderer, -113.55, 8.43, -110.27, 0.66, -104.44,
                                -5.07);
    rr_renderer_bezier_curve_to(renderer, -98.60, -10.79, -90.68, -14.01,
                                -82.43, -14.01);
    rr_renderer_bezier_curve_to(renderer, -65.24, -14.01, -51.30, -0.34, -51.30,
                                16.53);
    rr_renderer_bezier_curve_to(renderer, -51.30, 33.40, -65.24, 47.08, -82.43,
                                47.08);
    rr_renderer_fill(renderer);
    rr_renderer_set_fill(renderer, 0xff917d73);
    rr_renderer_begin_path(renderer);
    rr_renderer_move_to(renderer, -82.43, 14.01);
    rr_renderer_bezier_curve_to(renderer, -99.62, 14.01, -113.55, 0.34, -113.55,
                                -16.53);
    rr_renderer_bezier_curve_to(renderer, -113.55, -24.63, -110.27, -32.40,
                                -104.44, -38.13);
    rr_renderer_bezier_curve_to(renderer, -98.60, -43.86, -90.68, -47.07,
                                -82.43, -47.07);
    rr_renderer_bezier_curve_to(renderer, -65.24, -47.07, -51.30, -33.40,
                                -51.30, -16.53);
    rr_renderer_bezier_curve_to(renderer, -51.30, 0.34, -65.24, 14.01, -82.43,
                                14.01);
    rr_renderer_fill(renderer);
    rr_renderer_set_fill(renderer, 0xff917d73);
    rr_renderer_begin_path(renderer);
    rr_renderer_move_to(renderer, -109.19, 16.84);
    rr_renderer_bezier_curve_to(renderer, -118.67, 16.84, -126.36, 9.30,
                                -126.36, 0.00);
    rr_renderer_bezier_curve_to(renderer, -126.36, -4.46, -124.55, -8.75,
                                -121.33, -11.91);
    rr_renderer_bezier_curve_to(renderer, -118.11, -15.06, -113.74, -16.84,
                                -109.19, -16.84);
    rr_renderer_bezier_curve_to(renderer, -99.71, -16.84, -92.03, -9.30, -92.03,
                                0.00);
    rr_renderer_bezier_curve_to(renderer, -92.03, 9.30, -99.71, 16.84, -109.19,
                                16.84);
    rr_renderer_fill(renderer);
    rr_renderer_set_fill(renderer, 0xff6a5045);
    rr_renderer_begin_path(renderer);
    rr_renderer_move_to(renderer, 80.60, 45.42);
    rr_renderer_line_to(renderer, -77.49, 14.15);
    rr_renderer_line_to(renderer, -77.49, -14.20);
    rr_renderer_line_to(renderer, 80.60, -45.47);
    rr_renderer_fill(renderer);
    rr_renderer_set_fill(renderer, 0xff6a5045);
    rr_renderer_begin_path(renderer);
    rr_renderer_move_to(renderer, 89.32, -46.81);
    rr_renderer_bezier_curve_to(renderer, 117.48, -46.81, 140.32, -25.86,
                                140.32, -0.03);
    rr_renderer_bezier_curve_to(renderer, 140.32, 12.38, 134.94, 24.28, 125.38,
                                33.05);
    rr_renderer_bezier_curve_to(renderer, 115.82, 41.82, 102.84, 46.75, 89.32,
                                46.75);
    rr_renderer_bezier_curve_to(renderer, 61.15, 46.75, 38.32, 25.81, 38.32,
                                -0.03);
    rr_renderer_bezier_curve_to(renderer, 38.32, -25.86, 61.15, -46.81, 89.32,
                                -46.81);
    rr_renderer_fill(renderer);
    rr_renderer_set_fill(renderer, 0xff6a5045);
    rr_renderer_begin_path(renderer);
    rr_renderer_move_to(renderer, 92.30, -32.42);
    rr_renderer_bezier_curve_to(renderer, 112.94, -32.42, 129.66, -17.92,
                                129.66, -0.04);
    rr_renderer_bezier_curve_to(renderer, 129.66, 8.55, 125.72, 16.78, 118.72,
                                22.85);
    rr_renderer_bezier_curve_to(renderer, 111.71, 28.93, 102.21, 32.34, 92.30,
                                32.34);
    rr_renderer_bezier_curve_to(renderer, 71.67, 32.34, 54.95, 17.84, 54.95,
                                -0.04);
    rr_renderer_bezier_curve_to(renderer, 54.95, -17.92, 71.67, -32.42, 92.30,
                                -32.42);
    rr_renderer_fill(renderer);
    rr_renderer_set_fill(renderer, 0xff6a5045);
    rr_renderer_begin_path(renderer);
    rr_renderer_move_to(renderer, -75.08, -14.32);
    rr_renderer_bezier_curve_to(renderer, -65.98, -14.32, -58.60, -7.93, -58.60,
                                -0.04);
    rr_renderer_bezier_curve_to(renderer, -58.60, 3.75, -60.34, 7.39, -63.43,
                                10.07);
    rr_renderer_bezier_curve_to(renderer, -66.52, 12.75, -70.71, 14.25, -75.08,
                                14.25);
    rr_renderer_bezier_curve_to(renderer, -84.19, 14.25, -91.56, 7.85, -91.56,
                                -0.04);
    rr_renderer_bezier_curve_to(renderer, -91.56, -7.93, -84.19, -14.32, -75.08,
                                -14.32);
    rr_renderer_fill(renderer);
    rr_renderer_set_fill(renderer, 0xff6a5045);
    rr_renderer_begin_path(renderer);
    rr_renderer_move_to(renderer, 82.33, 31.16);
    rr_renderer_line_to(renderer, -77.23, -0.04);
    rr_renderer_line_to(renderer, 82.33, -31.24);
    rr_renderer_fill(renderer);
    rr_renderer_set_fill(renderer, 0xff856456);
    rr_renderer_begin_path(renderer);
    rr_renderer_move_to(renderer, 51.69, 8.35);
    rr_renderer_bezier_curve_to(renderer, 60.31, 8.35, 67.29, 15.20, 67.29,
                                23.65);
    rr_renderer_bezier_curve_to(renderer, 67.29, 27.71, 65.65, 31.60, 62.72,
                                34.47);
    rr_renderer_bezier_curve_to(renderer, 59.80, 37.34, 55.83, 38.96, 51.69,
                                38.96);
    rr_renderer_bezier_curve_to(renderer, 43.08, 38.96, 36.09, 32.10, 36.09,
                                23.65);
    rr_renderer_bezier_curve_to(renderer, 36.09, 15.20, 43.08, 8.35, 51.69,
                                8.35);
    rr_renderer_fill(renderer);
    rr_renderer_set_fill(renderer, 0xff6a5045);
    rr_renderer_begin_path(renderer);
    rr_renderer_move_to(renderer, 51.69, 6.29);
    rr_renderer_bezier_curve_to(renderer, 61.47, 6.29, 69.39, 14.06, 69.39,
                                23.65);
    rr_renderer_bezier_curve_to(renderer, 69.39, 28.26, 67.53, 32.68, 64.21,
                                35.93);
    rr_renderer_bezier_curve_to(renderer, 60.89, 39.19, 56.39, 41.02, 51.69,
                                41.02);
    rr_renderer_bezier_curve_to(renderer, 41.91, 41.02, 33.99, 33.25, 33.99,
                                23.65);
    rr_renderer_bezier_curve_to(renderer, 33.99, 14.06, 41.91, 6.29, 51.69,
                                6.29);
    rr_renderer_move_to(renderer, 51.69, 14.05);
    rr_renderer_bezier_curve_to(renderer, 46.20, 14.05, 41.75, 18.35, 41.75,
                                23.65);
    rr_renderer_bezier_curve_to(renderer, 41.75, 28.96, 46.20, 33.26, 51.69,
                                33.26);
    rr_renderer_bezier_curve_to(renderer, 57.18, 33.26, 61.63, 28.96, 61.63,
                                23.65);
    rr_renderer_bezier_curve_to(renderer, 61.63, 18.35, 57.18, 14.05, 51.69,
                                14.05);
    rr_renderer_fill(renderer);
    rr_renderer_set_fill(renderer, 0xff856456);
    rr_renderer_begin_path(renderer);
    rr_renderer_move_to(renderer, 20.47, 3.16);
    rr_renderer_bezier_curve_to(renderer, 29.09, 3.16, 36.07, 10.01, 36.07,
                                18.46);
    rr_renderer_bezier_curve_to(renderer, 36.07, 22.52, 34.43, 26.41, 31.50,
                                29.28);
    rr_renderer_bezier_curve_to(renderer, 28.58, 32.15, 24.61, 33.77, 20.47,
                                33.77);
    rr_renderer_bezier_curve_to(renderer, 11.86, 33.77, 4.87, 26.91, 4.87,
                                18.46);
    rr_renderer_bezier_curve_to(renderer, 4.87, 10.01, 11.86, 3.16, 20.47,
                                3.16);
    rr_renderer_fill(renderer);
    rr_renderer_set_fill(renderer, 0xff6a5045);
    rr_renderer_begin_path(renderer);
    rr_renderer_move_to(renderer, 20.47, 1.10);
    rr_renderer_bezier_curve_to(renderer, 30.25, 1.10, 38.18, 8.87, 38.18,
                                18.46);
    rr_renderer_bezier_curve_to(renderer, 38.18, 23.07, 36.31, 27.49, 32.99,
                                30.74);
    rr_renderer_bezier_curve_to(renderer, 29.67, 34.00, 25.17, 35.83, 20.47,
                                35.83);
    rr_renderer_bezier_curve_to(renderer, 10.69, 35.83, 2.77, 28.06, 2.77,
                                18.46);
    rr_renderer_bezier_curve_to(renderer, 2.77, 8.87, 10.69, 1.10, 20.47, 1.10);
    rr_renderer_move_to(renderer, 20.47, 8.86);
    rr_renderer_bezier_curve_to(renderer, 14.98, 8.86, 10.53, 13.16, 10.53,
                                18.46);
    rr_renderer_bezier_curve_to(renderer, 10.53, 23.77, 14.98, 28.07, 20.47,
                                28.07);
    rr_renderer_bezier_curve_to(renderer, 25.96, 28.07, 30.41, 23.77, 30.41,
                                18.46);
    rr_renderer_bezier_curve_to(renderer, 30.41, 13.16, 25.96, 8.86, 20.47,
                                8.86);
    rr_renderer_fill(renderer);
    rr_renderer_set_fill(renderer, 0xff856456);
    rr_renderer_begin_path(renderer);
    rr_renderer_move_to(renderer, -17.80, 0.50);
    rr_renderer_bezier_curve_to(renderer, -11.16, 0.50, -5.77, 5.78, -5.77,
                                12.29);
    rr_renderer_bezier_curve_to(renderer, -5.77, 15.41, -7.04, 18.41, -9.29,
                                20.62);
    rr_renderer_bezier_curve_to(renderer, -11.55, 22.83, -14.61, 24.08, -17.80,
                                24.08);
    rr_renderer_bezier_curve_to(renderer, -24.44, 24.08, -29.83, 18.80, -29.83,
                                12.29);
    rr_renderer_bezier_curve_to(renderer, -29.83, 5.78, -24.44, 0.50, -17.80,
                                0.50);
    rr_renderer_fill(renderer);
    rr_renderer_set_fill(renderer, 0xff6a5045);
    rr_renderer_begin_path(renderer);
    rr_renderer_move_to(renderer, -17.80, -1.09);
    rr_renderer_bezier_curve_to(renderer, -10.26, -1.09, -4.15, 4.90, -4.15,
                                12.29);
    rr_renderer_bezier_curve_to(renderer, -4.15, 15.84, -5.59, 19.24, -8.15,
                                21.75);
    rr_renderer_bezier_curve_to(renderer, -10.71, 24.26, -14.18, 25.67, -17.80,
                                25.67);
    rr_renderer_bezier_curve_to(renderer, -25.34, 25.67, -31.45, 19.68, -31.45,
                                12.29);
    rr_renderer_bezier_curve_to(renderer, -31.45, 4.90, -25.34, -1.09, -17.80,
                                -1.09);
    rr_renderer_move_to(renderer, -17.80, 4.89);
    rr_renderer_bezier_curve_to(renderer, -22.04, 4.89, -25.47, 8.20, -25.47,
                                12.29);
    rr_renderer_bezier_curve_to(renderer, -25.47, 16.37, -22.04, 19.68, -17.80,
                                19.68);
    rr_renderer_bezier_curve_to(renderer, -13.56, 19.68, -10.13, 16.37, -10.13,
                                12.29);
    rr_renderer_bezier_curve_to(renderer, -10.13, 8.20, -13.56, 4.89, -17.80,
                                4.89);
    rr_renderer_fill(renderer);
    rr_renderer_set_fill(renderer, 0xff856456);
    rr_renderer_begin_path(renderer);
    rr_renderer_move_to(renderer, 51.69, -8.46);
    rr_renderer_bezier_curve_to(renderer, 60.31, -8.46, 67.29, -15.32, 67.29,
                                -23.77);
    rr_renderer_bezier_curve_to(renderer, 67.29, -27.83, 65.65, -31.72, 62.72,
                                -34.59);
    rr_renderer_bezier_curve_to(renderer, 59.80, -37.46, 55.83, -39.07, 51.69,
                                -39.07);
    rr_renderer_bezier_curve_to(renderer, 43.08, -39.07, 36.09, -32.22, 36.09,
                                -23.77);
    rr_renderer_bezier_curve_to(renderer, 36.09, -15.32, 43.08, -8.46, 51.69,
                                -8.46);
    rr_renderer_fill(renderer);
    rr_renderer_set_fill(renderer, 0xff6a5045);
    rr_renderer_begin_path(renderer);
    rr_renderer_move_to(renderer, 51.69, -6.40);
    rr_renderer_bezier_curve_to(renderer, 61.47, -6.40, 69.40, -14.18, 69.40,
                                -23.77);
    rr_renderer_bezier_curve_to(renderer, 69.40, -28.38, 67.53, -32.79, 64.21,
                                -36.05);
    rr_renderer_bezier_curve_to(renderer, 60.89, -39.31, 56.39, -41.14, 51.69,
                                -41.14);
    rr_renderer_bezier_curve_to(renderer, 41.91, -41.14, 33.99, -33.36, 33.99,
                                -23.77);
    rr_renderer_bezier_curve_to(renderer, 33.99, -14.18, 41.91, -6.40, 51.69,
                                -6.40);
    rr_renderer_move_to(renderer, 51.69, -14.17);
    rr_renderer_bezier_curve_to(renderer, 46.20, -14.17, 41.75, -18.47, 41.75,
                                -23.77);
    rr_renderer_bezier_curve_to(renderer, 41.75, -29.07, 46.20, -33.37, 51.69,
                                -33.37);
    rr_renderer_bezier_curve_to(renderer, 57.18, -33.37, 61.63, -29.07, 61.63,
                                -23.77);
    rr_renderer_bezier_curve_to(renderer, 61.63, -18.47, 57.18, -14.17, 51.69,
                                -14.17);
    rr_renderer_fill(renderer);
    rr_renderer_set_fill(renderer, 0xff856456);
    rr_renderer_begin_path(renderer);
    rr_renderer_move_to(renderer, 20.48, -3.27);
    rr_renderer_bezier_curve_to(renderer, 29.09, -3.27, 36.08, -10.13, 36.08,
                                -18.58);
    rr_renderer_bezier_curve_to(renderer, 36.08, -22.64, 34.43, -26.53, 31.51,
                                -29.40);
    rr_renderer_bezier_curve_to(renderer, 28.58, -32.27, 24.61, -33.88, 20.48,
                                -33.88);
    rr_renderer_bezier_curve_to(renderer, 11.86, -33.88, 4.88, -27.03, 4.88,
                                -18.58);
    rr_renderer_bezier_curve_to(renderer, 4.88, -10.13, 11.86, -3.27, 20.48,
                                -3.27);
    rr_renderer_fill(renderer);
    rr_renderer_set_fill(renderer, 0xff6a5045);
    rr_renderer_begin_path(renderer);
    rr_renderer_move_to(renderer, 20.47, -1.21);
    rr_renderer_bezier_curve_to(renderer, 30.25, -1.21, 38.18, -8.99, 38.18,
                                -18.58);
    rr_renderer_bezier_curve_to(renderer, 38.18, -23.19, 36.31, -27.60, 32.99,
                                -30.86);
    rr_renderer_bezier_curve_to(renderer, 29.67, -34.12, 25.17, -35.95, 20.47,
                                -35.95);
    rr_renderer_bezier_curve_to(renderer, 10.70, -35.95, 2.77, -28.17, 2.77,
                                -18.58);
    rr_renderer_bezier_curve_to(renderer, 2.77, -8.99, 10.70, -1.21, 20.47,
                                -1.21);
    rr_renderer_move_to(renderer, 20.47, -8.98);
    rr_renderer_bezier_curve_to(renderer, 14.98, -8.98, 10.54, -13.28, 10.54,
                                -18.58);
    rr_renderer_bezier_curve_to(renderer, 10.54, -23.88, 14.98, -28.18, 20.47,
                                -28.18);
    rr_renderer_bezier_curve_to(renderer, 25.96, -28.18, 30.41, -23.88, 30.41,
                                -18.58);
    rr_renderer_bezier_curve_to(renderer, 30.41, -13.28, 25.96, -8.98, 20.47,
                                -8.98);
    rr_renderer_fill(renderer);
    rr_renderer_set_fill(renderer, 0xff856456);
    rr_renderer_begin_path(renderer);
    rr_renderer_move_to(renderer, -17.80, -0.62);
    rr_renderer_bezier_curve_to(renderer, -11.15, -0.62, -5.77, -5.89, -5.77,
                                -12.40);
    rr_renderer_bezier_curve_to(renderer, -5.77, -15.53, -7.04, -18.53, -9.29,
                                -20.74);
    rr_renderer_bezier_curve_to(renderer, -11.55, -22.95, -14.61, -24.19,
                                -17.80, -24.19);
    rr_renderer_bezier_curve_to(renderer, -24.44, -24.19, -29.83, -18.91,
                                -29.83, -12.40);
    rr_renderer_bezier_curve_to(renderer, -29.83, -5.89, -24.44, -0.62, -17.80,
                                -0.62);
    rr_renderer_fill(renderer);
    rr_renderer_set_fill(renderer, 0xff6a5045);
    rr_renderer_begin_path(renderer);
    rr_renderer_move_to(renderer, -17.80, 0.97);
    rr_renderer_bezier_curve_to(renderer, -10.26, 0.97, -4.15, -5.02, -4.15,
                                -12.40);
    rr_renderer_bezier_curve_to(renderer, -4.15, -15.95, -5.58, -19.36, -8.15,
                                -21.86);
    rr_renderer_bezier_curve_to(renderer, -10.71, -24.37, -14.18, -25.78,
                                -17.80, -25.78);
    rr_renderer_bezier_curve_to(renderer, -25.34, -25.78, -31.45, -19.79,
                                -31.45, -12.40);
    rr_renderer_bezier_curve_to(renderer, -31.45, -5.02, -25.34, 0.97, -17.80,
                                0.97);
    rr_renderer_move_to(renderer, -17.80, -5.01);
    rr_renderer_bezier_curve_to(renderer, -22.04, -5.01, -25.47, -8.32, -25.47,
                                -12.40);
    rr_renderer_bezier_curve_to(renderer, -25.47, -16.49, -22.04, -19.80,
                                -17.80, -19.80);
    rr_renderer_bezier_curve_to(renderer, -13.56, -19.80, -10.13, -16.49,
                                -10.13, -12.40);
    rr_renderer_bezier_curve_to(renderer, -10.13, -8.32, -13.56, -5.01, -17.80,
                                -5.01);
    rr_renderer_fill(renderer);
    rr_renderer_set_fill(renderer, 0xff856456);
    rr_renderer_begin_path(renderer);
    rr_renderer_move_to(renderer, 88.75, -32.43);
    rr_renderer_bezier_curve_to(renderer, 107.42, -32.43, 122.56, -17.93,
                                122.56, -0.05);
    rr_renderer_bezier_curve_to(renderer, 122.56, 8.54, 119.00, 16.77, 112.66,
                                22.84);
    rr_renderer_bezier_curve_to(renderer, 106.32, 28.92, 97.72, 32.33, 88.75,
                                32.33);
    rr_renderer_bezier_curve_to(renderer, 70.08, 32.33, 54.94, 17.83, 54.94,
                                -0.05);
    rr_renderer_bezier_curve_to(renderer, 54.94, -17.93, 70.08, -32.43, 88.75,
                                -32.43);
    rr_renderer_fill(renderer);
    rr_renderer_set_fill(renderer, 0xff856456);
    rr_renderer_begin_path(renderer);
    rr_renderer_move_to(renderer, 82.34, 31.15);
    rr_renderer_line_to(renderer, -77.23, -0.05);
    rr_renderer_line_to(renderer, 82.34, -31.25);
    rr_renderer_fill(renderer);
}