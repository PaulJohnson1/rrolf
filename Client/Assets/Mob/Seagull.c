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

void rr_seagull_wing1_draw(struct rr_renderer *renderer)
{
    rr_renderer_set_fill(renderer, 0xff9c9c9c);
    rr_renderer_begin_path(renderer);
    rr_renderer_move_to(renderer, 133.29397999999998, -45.0583);
    rr_renderer_bezier_curve_to(renderer, 122.03717499999998, -60.254955,
                                93.08889999999997, -37.5004463,
                                73.95190999999997, -41.681690200000006);
    rr_renderer_bezier_curve_to(
        renderer, 54.814916999999966, -45.862934200000005, 35.67840999999997,
        -65.72361420000001, 18.472066999999967, -70.14577820000001);
    rr_renderer_bezier_curve_to(renderer, 1.265736999999966, -74.5679355,
                                -12.803476000000032, -73.6823612,
                                -29.286127000000036, -68.21464870000001);
    rr_renderer_bezier_curve_to(
        renderer, -45.76876200000004, -62.74694370000001, -62.573740000000036,
        -51.97339870000001, -80.42377700000003, -37.33951870000001);
    rr_renderer_bezier_curve_to(
        renderer, -98.27382900000003, -22.705630700000015, -128.34575700000002,
        4.472471299999988, -136.38640100000003, 19.588666299999986);
    rr_renderer_bezier_curve_to(
        renderer, -144.42703500000005, 34.704846299999986, -146.35673000000003,
        50.54331629999999, -128.66761300000005, 53.35763329999999);
    rr_renderer_bezier_curve_to(
        renderer, -110.97849600000005, 56.17194909999999, -60.14649300000005,
        33.64263729999999, -30.25168900000004, 36.47457629999999);
    rr_renderer_bezier_curve_to(
        renderer, -0.35686800000004126, 39.30651599999999, 24.40875699999996,
        65.04246229999998, 50.70127099999996, 70.34924029999999);
    rr_renderer_bezier_curve_to(renderer, 76.99381299999996, 75.65601829999999,
                                112.37155899999996, 71.79043289999998,
                                127.50345599999996, 68.31527429999998);
    rr_renderer_bezier_curve_to(renderer, 142.63538349999996, 64.84010029999999,
                                140.52759499999996, 68.39382654599999,
                                141.49268299999994, 49.49824229999999);
    rr_renderer_bezier_curve_to(
        renderer, 142.45777089999993, 30.602642299999985, 144.55078849999995,
        -29.861643700000016, 133.29398299999994, -45.05829770000001);
    rr_renderer_fill(renderer);
    rr_renderer_set_fill(renderer, 0xffadadad);
    rr_renderer_begin_path(renderer);
    rr_renderer_move_to(renderer, 126.54462000000001, -32.86459000000001);
    rr_renderer_bezier_curve_to(renderer, 116.491916, -43.86015700000001,
                                88.68796, -23.929585000000007, 69.05829,
                                -28.052364700000005);
    rr_renderer_bezier_curve_to(renderer, 49.428651, -32.1751367, 28.30301,
                                -54.927784700000004, 8.766694999999999,
                                -57.60123870000001);
    rr_renderer_bezier_curve_to(
        renderer, -10.769605000000002, -60.27470070000001, -26.540145000000003,
        -57.36009643000001, -48.159545, -44.09311370000001);
    rr_renderer_bezier_curve_to(renderer, -69.778945, -30.82612270000001,
                                -109.70272, 8.251406299999992,
                                -120.94966500000001, 22.000676299999988);
    rr_renderer_bezier_curve_to(
        renderer, -132.19662100000002, 35.74994429999999, -131.63245,
        38.48277729999999, -115.64123900000001, 38.40253129999999);
    rr_renderer_bezier_curve_to(renderer, -99.65002800000002, 38.32228532999999,
                                -53.67309200000001, 18.951374299999994,
                                -25.002389000000008, 21.519215299999992);
    rr_renderer_bezier_curve_to(renderer, 3.668295999999991, 24.08704059999999,
                                32.42250699999999, 48.34222829999999,
                                56.38291099999999, 53.809515299999994);
    rr_renderer_bezier_curve_to(renderer, 80.34333, 59.27680029999999,
                                106.59482499999999, 56.97098379999999,
                                118.760078, 54.322912499999994);
    rr_renderer_bezier_curve_to(renderer, 130.925331, 51.674841199999996,
                                128.077064, 52.45230699999999,
                                129.37448799999999, 37.92105749999999);
    rr_renderer_bezier_curve_to(renderer, 130.67191229999997, 23.38980749999999,
                                136.59732739999998, -21.86901250000001,
                                126.54462349999999, -32.86458750000001);
    rr_renderer_fill(renderer);
}

void rr_seagull_wing2_draw(struct rr_renderer *renderer)
{
    rr_renderer_set_fill(renderer, 0xff9c9c9c);
    rr_renderer_begin_path(renderer);
    rr_renderer_move_to(renderer, -133.29397, -45.05837);
    rr_renderer_bezier_curve_to(renderer, -122.037172, -60.255024999999996,
                                -93.088877, -37.5005087, -73.95188999999999,
                                -41.6817602);
    rr_renderer_bezier_curve_to(renderer, -54.81491199999999, -45.8630042,
                                -35.67838999999999, -65.72368420000001,
                                -18.472061999999994, -70.1458482);
    rr_renderer_bezier_curve_to(renderer, -1.265716999999995, -74.5680055,
                                12.803496000000006, -73.6824312,
                                29.28613200000001, -68.2147187);
    rr_renderer_bezier_curve_to(
        renderer, 45.76876700000001, -62.747013700000004, 62.57376200000001,
        -51.973468700000005, 80.42379700000001, -37.33958170000001);
    rr_renderer_bezier_curve_to(renderer, 98.27383400000001, -22.70570070000001,
                                128.345764, 4.472398299999988, 136.386413,
                                19.588595299999987);
    rr_renderer_bezier_curve_to(renderer, 144.427062, 34.70477529999999,
                                146.35675, 50.54324529999999, 128.6676325,
                                53.35756229999999);
    rr_renderer_bezier_curve_to(renderer, 110.9785155, 56.171878099999994,
                                60.1465125, 33.64256629999999,
                                30.25169249999999, 36.47450529999999);
    rr_renderer_bezier_curve_to(renderer, 0.356886499999991, 39.30644499999999,
                                -24.408737500000008, 65.04239129999999,
                                -50.701267500000014, 70.3491693);
    rr_renderer_bezier_curve_to(renderer, -76.99379350000001, 75.6559473,
                                -112.37155550000001, 71.7903619,
                                -127.50345750000001, 68.3152033);
    rr_renderer_bezier_curve_to(renderer, -142.6353625, 64.8400293,
                                -140.52759650000002, 68.393755546, -141.4926845,
                                49.498171299999996);
    rr_renderer_bezier_curve_to(renderer, -142.45776476, 30.602571299999994,
                                -144.5507747, -29.861714700000007, -133.2939695,
                                -45.0583687);
    rr_renderer_fill(renderer);
    rr_renderer_set_fill(renderer, 0xffadadad);
    rr_renderer_begin_path(renderer);
    rr_renderer_move_to(renderer, -126.54461, -32.86466);
    rr_renderer_bezier_curve_to(renderer, -116.49191400000001, -43.860235,
                                -88.68795, -23.929662, -69.05829, -28.0524347);
    rr_renderer_bezier_curve_to(renderer, -49.428636, -32.1752147,
                                -28.302995000000003, -54.927861699999994,
                                -8.766694999999999, -57.6013167);
    rr_renderer_bezier_curve_to(renderer, 10.769621, -60.2747787,
                                26.540159000000003, -57.36017443, 48.159545,
                                -44.0931917);
    rr_renderer_bezier_curve_to(renderer, 69.77896, -30.826200699999998,
                                109.70272700000001, 8.251328300000004,
                                120.94967500000001, 22.0005983);
    rr_renderer_bezier_curve_to(renderer, 132.19662300000002, 35.7498813,
                                131.63244500000002, 38.4826993,
                                115.64123400000001, 38.402453300000005);
    rr_renderer_bezier_curve_to(renderer, 99.650023, 38.322207330000005,
                                53.67309400000001, 18.951296300000006,
                                25.002410000000012, 21.519137300000004);
    rr_renderer_bezier_curve_to(
        renderer, -3.6682899999999883, 24.086962600000003, -32.422499999999985,
        48.3421503, -56.382904999999994, 53.809437300000006);
    rr_renderer_bezier_curve_to(renderer, -80.343324, 59.2767223,
                                -106.59479499999999, 56.970905800000004,
                                -118.760055, 54.322834500000006);
    rr_renderer_bezier_curve_to(renderer, -130.92531499999998,
                                51.67476320000001, -128.077033, 52.452229,
                                -129.374465, 37.9209795);
    rr_renderer_bezier_curve_to(renderer, -130.67188929999998, 23.3897295,
                                -136.59730439999998, -21.8690905,
                                -126.54460809999999, -32.8646605);
    rr_renderer_fill(renderer);
}

void rr_seagull_body_draw(struct rr_renderer *renderer)
{
    rr_renderer_set_fill(renderer, 0xffd7af43);
    rr_renderer_begin_path(renderer);
    rr_renderer_move_to(renderer, 46.789469999999994, -88.562386);
    rr_renderer_bezier_curve_to(renderer, 49.909846599999995, -93.775368,
                                28.067202999999996, -102.499047,
                                21.746348999999995, -113.733464);
    rr_renderer_bezier_curve_to(renderer, 15.425502399999996, -124.967885,
                                12.983233999999994, -147.84384599999998,
                                8.864375999999995, -155.968899);
    rr_renderer_bezier_curve_to(renderer, 4.745517699999994, -164.093956,
                                -0.9554250000000053, -163.6188204,
                                -2.9667930000000045, -162.4838016);
    rr_renderer_bezier_curve_to(
        renderer, -4.978168400000005, -161.34878279999998, -4.202342900000005,
        -162.49682545299999, -3.2038688000000044, -149.15878759999998);
    rr_renderer_bezier_curve_to(
        renderer, -2.2053870500000046, -135.82074659999998, -5.308147400000005,
        -92.55496759999998, 3.0240745999999956, -82.45556359999998);
    rr_renderer_bezier_curve_to(
        renderer, 11.356296599999995, -72.35616759999998, 43.6690946,
        -83.34940059999998, 46.7894706, -88.56238259999998);
    rr_renderer_fill(renderer);
    rr_renderer_set_fill(renderer, 0xff9c9c9c);
    rr_renderer_begin_path(renderer);
    rr_renderer_move_to(renderer, 17.544210000000007, 66.49574000000001);
    rr_renderer_bezier_curve_to(renderer, 17.544210000000007, 56.80717200000001,
                                9.690076400000006, 48.95303000000001,
                                0.0015080000000082805, 48.95303000000001);
    rr_renderer_bezier_curve_to(renderer, -4.651102999999992, 48.95303000000001,
                                -9.11315399999999, 50.801281300000014,
                                -12.403047999999991, 54.09116800000001);
    rr_renderer_bezier_curve_to(
        renderer, -15.692941999999992, 57.38106970000001, -17.54118599999999,
        61.84312100000001, -17.54118599999999, 66.49574000000001);
    rr_renderer_bezier_curve_to(renderer, -17.54118599999999, 76.18430800000002,
                                -9.687052399999988, 84.03843400000001,
                                0.0015080000000118332, 84.03843400000001);
    rr_renderer_bezier_curve_to(renderer, 9.690076000000012, 84.03843400000001,
                                17.54421000000001, 76.18430800000002,
                                17.54421000000001, 66.49574000000001);
    rr_renderer_fill(renderer);
    rr_renderer_set_fill(renderer, 0xff9c9c9c);
    rr_renderer_begin_path(renderer);
    rr_renderer_move_to(renderer, -67.117502, 109.24624999999997);
    rr_renderer_line_to(renderer, -9.885041999999999, 52.01378199999998);
    rr_renderer_line_to(renderer, -4.628289999999999, 82.38208299999998);
    rr_renderer_line_to(renderer, -43.756464, 112.16690299999998);
    rr_renderer_fill(renderer);
    rr_renderer_set_fill(renderer, 0xff9c9c9c);
    rr_renderer_begin_path(renderer);
    rr_renderer_move_to(renderer, -67.276249, 134.40756);
    rr_renderer_bezier_curve_to(renderer, -49.057259, 153.41525,
                                -23.650849000000008, 163.82949599999998,
                                2.664775999999989, 163.07681);
    rr_renderer_line_to(renderer, 0.0006753999999893345, 69.89621);
    rr_renderer_fill(renderer);
    rr_renderer_set_fill(renderer, 0xff9c9c9c);
    rr_renderer_begin_path(renderer);
    rr_renderer_move_to(renderer, -37.51185, 121.84357);
    rr_renderer_bezier_curve_to(renderer, -37.51185, 112.156741, -45.3645912,
                                104.303989, -55.051439, 104.303989);
    rr_renderer_bezier_curve_to(renderer, -59.703226, 104.303989, -64.164489,
                                106.1519199, -67.453802, 109.4412265);
    rr_renderer_bezier_curve_to(renderer, -70.7431125, 112.7305331, -72.591028,
                                117.1917758, -72.591028, 121.8435705);
    rr_renderer_bezier_curve_to(renderer, -72.591028, 131.5304295, -64.7382868,
                                139.3831515, -55.051438999999995, 139.3831515);
    rr_renderer_bezier_curve_to(renderer, -45.364591, 139.3831515,
                                -37.511849999999995, 131.5304295,
                                -37.511849999999995, 121.8435705);
    rr_renderer_fill(renderer);
    rr_renderer_set_fill(renderer, 0xffadadad);
    rr_renderer_begin_path(renderer);
    rr_renderer_move_to(renderer, -57.940853, 122.05527000000001);
    rr_renderer_bezier_curve_to(
        renderer, -42.250018999999995, 138.42566200000002, -20.369032999999995,
        147.39493000000002, 2.295014000000002, 146.746676);
    rr_renderer_line_to(renderer, 0.0005728000000018163, 66.495636);
    rr_renderer_fill(renderer);
    rr_renderer_set_fill(renderer, 0xff9c9c9c);
    rr_renderer_begin_path(renderer);
    rr_renderer_move_to(renderer, 67.119, 109.24576000000002);
    rr_renderer_line_to(renderer, 9.886532000000003, 52.01329200000002);
    rr_renderer_line_to(renderer, 4.629772400000003, 82.38159300000002);
    rr_renderer_line_to(renderer, 43.7579464, 112.16641300000002);
    rr_renderer_fill(renderer);
    rr_renderer_set_fill(renderer, 0xff9c9c9c);
    rr_renderer_begin_path(renderer);
    rr_renderer_move_to(renderer, 67.27774, 134.40706999999998);
    rr_renderer_bezier_curve_to(renderer, 49.058746, 153.41475999999997,
                                23.652342999999995, 163.82900599999996,
                                -2.663285000000002, 163.07631999999998);
    rr_renderer_line_to(renderer, 0.0008232999999981949, 69.89571999999998);
    rr_renderer_fill(renderer);
    rr_renderer_set_fill(renderer, 0xff9c9c9c);
    rr_renderer_begin_path(renderer);
    rr_renderer_move_to(renderer, 37.51334, 121.84307999999999);
    rr_renderer_bezier_curve_to(renderer, 37.51334, 112.15625099999998,
                                45.366092699999996, 104.30349899999999,
                                55.052937, 104.30349899999999);
    rr_renderer_bezier_curve_to(renderer, 59.704716, 104.30349899999999,
                                64.165989, 106.15142989999998, 67.455296,
                                109.44073649999999);
    rr_renderer_bezier_curve_to(renderer, 70.74460260000001, 112.73004309999999,
                                72.59251830000001, 117.19128579999999,
                                72.59251830000001, 121.84308049999999);
    rr_renderer_bezier_curve_to(renderer, 72.59251830000001, 131.52993949999998,
                                64.73978090000001, 139.38266149999998,
                                55.05293730000001, 139.38266149999998);
    rr_renderer_bezier_curve_to(renderer, 45.36609330000001, 139.38266149999998,
                                37.51334030000001, 131.52993949999998,
                                37.51334030000001, 121.84308049999999);
    rr_renderer_fill(renderer);
    rr_renderer_set_fill(renderer, 0xffadadad);
    rr_renderer_begin_path(renderer);
    rr_renderer_move_to(renderer, 57.942350000000005, 122.05478);
    rr_renderer_bezier_curve_to(renderer, 42.251508, 138.425172,
                                20.370520000000006, 147.39444,
                                -2.293519999999994, 146.746186);
    rr_renderer_line_to(renderer, 0.0009136000000062872, 66.49514599999999);
    rr_renderer_fill(renderer);
    rr_renderer_set_fill(renderer, 0xff9c9c9c);
    rr_renderer_begin_path(renderer);
    rr_renderer_move_to(renderer, -42.763844, 61.90674000000001);
    rr_renderer_bezier_curve_to(renderer, -33.316529, 64.93594530000001,
                                -28.113616999999998, 75.042482, -31.142815,
                                84.48033300000002);
    rr_renderer_bezier_curve_to(renderer, -34.1720165, 93.91818400000001,
                                -44.286232, 99.11340500000001, -53.733548,
                                96.08423000000002);
    rr_renderer_bezier_curve_to(renderer, -44.065759, 87.57458600000002,
                                -39.853111999999996, 74.44957100000002,
                                -42.763844, 61.90674000000002);
    rr_renderer_fill(renderer);
    rr_renderer_set_fill(renderer, 0xffadadad);
    rr_renderer_begin_path(renderer);
    rr_renderer_move_to(renderer, -30.55753, 59.925749999999994);
    rr_renderer_bezier_curve_to(renderer, -16.396023, 64.46954269999999,
                                -8.599331, 79.63319299999999,
                                -13.143132000000001, 93.79470799999999);
    rr_renderer_bezier_curve_to(
        renderer, -17.686932400000003, 107.95620699999998, -32.850575000000006,
        115.75289799999999, -47.012082, 111.20910599999999);
    rr_renderer_bezier_curve_to(renderer, -32.516701999999995,
                                98.43936099999999, -26.197736, 78.745269,
                                -30.55753, 59.925749999999994);
    rr_renderer_fill(renderer);
    rr_renderer_set_fill(renderer, 0xff9c9c9c);
    rr_renderer_begin_path(renderer);
    rr_renderer_move_to(renderer, 42.76253, 61.905399999999986);
    rr_renderer_bezier_curve_to(renderer, 33.315219, 64.93460529999999,
                                28.112306999999998, 75.04114199999998,
                                31.141505, 84.47899299999999);
    rr_renderer_bezier_curve_to(renderer, 34.1707027, 93.91684399999998,
                                44.284915, 99.11206499999999, 53.732226,
                                96.08288999999999);
    rr_renderer_bezier_curve_to(renderer, 44.06444, 87.573246, 39.851794,
                                74.44823099999999, 42.76253, 61.90539999999999);
    rr_renderer_fill(renderer);
    rr_renderer_set_fill(renderer, 0xffadadad);
    rr_renderer_begin_path(renderer);
    rr_renderer_move_to(renderer, 30.556219999999996, 59.924409999999995);
    rr_renderer_bezier_curve_to(renderer, 16.394712999999996, 64.46820269999999,
                                8.598020999999996, 79.63185299999999,
                                13.141813999999997, 93.79336799999999);
    rr_renderer_bezier_curve_to(renderer, 17.6856144, 107.95486699999998,
                                32.849256999999994, 115.75155799999999,
                                47.010771999999996, 111.20776599999999);
    rr_renderer_bezier_curve_to(renderer, 32.51537999999999, 98.43802099999999,
                                26.196417999999994, 78.743929,
                                30.556219999999996, 59.924409999999995);
    rr_renderer_fill(renderer);
    rr_renderer_set_fill(renderer, 0xffc6c6c6);
    rr_renderer_begin_path(renderer);
    rr_renderer_move_to(renderer, 63.91568000000001, 9.583390000000009);
    rr_renderer_bezier_curve_to(renderer, 63.91568000000001, 60.289902000000005,
                                35.28662100000001, 101.39566,
                                -0.029099999999992576, 101.39566);
    rr_renderer_bezier_curve_to(renderer, -16.98830599999999, 101.39566,
                                -33.252903999999994, 91.72259500000001,
                                -45.244879999999995, 74.50445500000001);
    rr_renderer_bezier_curve_to(renderer, -57.23685, 57.28631500000001,
                                -63.97386899999999, 33.93351500000001,
                                -63.97386899999999, 9.583385000000007);
    rr_renderer_bezier_curve_to(
        renderer, -63.97386899999999, -41.12313499999999, -35.34481799999999,
        -82.22888499999999, -0.029101999999994632, -82.22888499999999);
    rr_renderer_bezier_curve_to(
        renderer, 35.286618000000004, -82.22888499999999, 63.91567800000001,
        -41.12313499999999, 63.91567800000001, 9.583385000000007);
    rr_renderer_fill(renderer);
    rr_renderer_set_fill(renderer, 0xffc6c6c6);
    rr_renderer_begin_path(renderer);
    rr_renderer_move_to(renderer, 22.989875999999995, 83.64496);
    rr_renderer_bezier_curve_to(renderer, 22.989875999999995, 102.479585,
                                12.679748999999996, 117.74805,
                                -0.038429000000004265, 117.74805);
    rr_renderer_bezier_curve_to(renderer, -6.1459120000000045, 117.74805,
                                -12.003257500000004, 114.15506300000001,
                                -16.321899000000005, 107.759494);
    rr_renderer_bezier_curve_to(renderer, -20.640540700000006,
                                101.36392500000001, -23.066734000000004,
                                92.68967, -23.066734000000004, 83.644962);
    rr_renderer_bezier_curve_to(
        renderer, -23.066734000000004, 64.81036700000001, -12.756607000000004,
        49.541889000000005, -0.038429000000004265, 49.541889000000005);
    rr_renderer_bezier_curve_to(renderer, 12.679748999999996,
                                49.541889000000005, 22.989875999999995,
                                64.810367, 22.989875999999995, 83.644962);
    rr_renderer_fill(renderer);
    rr_renderer_set_fill(renderer, 0xffdedede);
    rr_renderer_begin_path(renderer);
    rr_renderer_move_to(renderer, 31.93907, -39.75092000000001);
    rr_renderer_bezier_curve_to(renderer, 49.603575, -12.69902500000001,
                                49.603575, 31.160759999999996, 31.93907,
                                58.212659999999985);
    rr_renderer_quadratic_curve_to(renderer, 17.688414, 80.03649699999998,
                                   -0.04534999999999911, 96.52621299999998);
    rr_renderer_quadratic_curve_to(renderer, -17.779114999999997,
                                   80.03649699999998, -32.02977,
                                   58.212659999999985);
    rr_renderer_bezier_curve_to(
        renderer, -49.694278999999995, 31.160764999999987, -49.694278999999995,
        -12.699020000000019, -32.02977, -39.75092000000001);
    rr_renderer_bezier_curve_to(renderer, -14.365265, -66.802823,
                                14.274566999999998, -66.802823, 31.93907,
                                -39.75092000000001);
    rr_renderer_fill(renderer);
    rr_renderer_set_fill(renderer, 0xffc6c6c6);
    rr_renderer_begin_path(renderer);
    rr_renderer_move_to(renderer, 13.376975999999999, 111.52157999999997);
    rr_renderer_line_to(renderer, 41.481246, 79.21023999999997);
    rr_renderer_line_to(renderer, 14.294051, 85.15105099999997);
    rr_renderer_fill(renderer);
    rr_renderer_set_fill(renderer, 0xffc6c6c6);
    rr_renderer_begin_path(renderer);
    rr_renderer_move_to(renderer, -13.447699999999998, 111.52157999999997);
    rr_renderer_line_to(renderer, -41.551967, 79.21023999999997);
    rr_renderer_line_to(renderer, -14.364767999999998, 85.15105099999997);
    rr_renderer_fill(renderer);
    rr_renderer_set_fill(renderer, 0xffebc04e);
    rr_renderer_begin_path(renderer);
    rr_renderer_move_to(renderer, -46.784843, -88.563446);
    rr_renderer_bezier_curve_to(renderer, -49.9052196, -93.776428,
                                -28.062568000000002, -102.500107, -21.741714,
                                -113.734524);
    rr_renderer_bezier_curve_to(
        renderer, -15.420867400000002, -124.96894499999999, -12.978599,
        -147.84490599999998, -8.859741000000001, -155.969959);
    rr_renderer_bezier_curve_to(renderer, -4.740882700000001, -164.095015,
                                0.9600529999999985, -163.61988,
                                2.9714279999999977, -162.484861);
    rr_renderer_bezier_curve_to(renderer, 4.982803399999998,
                                -161.34984219999998, 4.206977899999998,
                                -162.497884853, 3.208496179999998, -149.159845);
    rr_renderer_bezier_curve_to(
        renderer, 2.2100220799999977, -135.82180599999998, 5.312782379999998,
        -92.556028, -3.019447220000002, -82.45662499999999);
    rr_renderer_bezier_curve_to(renderer, -11.351669220000002, -72.357222,
                                -43.66446322, -83.350462, -46.784843220000006,
                                -88.56344399999999);
    rr_renderer_fill(renderer);
    rr_renderer_set_fill(renderer, 0xffdedede);
    rr_renderer_begin_path(renderer);
    rr_renderer_move_to(renderer, -56.26146, -47.27589999999999);
    rr_renderer_bezier_curve_to(renderer, -56.26146, -79.006727, -31.026925,
                                -104.72963999999999, 0.1014550000000014,
                                -104.72963999999999);
    rr_renderer_bezier_curve_to(
        renderer, 15.049827000000002, -104.72963999999999, 29.385955000000003,
        -98.67649749999998, 39.956055, -87.90183199999998);
    rr_renderer_bezier_curve_to(renderer, 50.526154, -77.12716599999999,
                                56.464371, -62.51357999999998, 56.464371,
                                -47.27590199999999);
    rr_renderer_bezier_curve_to(renderer, 56.464371, -15.545074999999986,
                                31.229828, 10.177841000000015,
                                0.10145599999999888, 10.177841000000015);
    rr_renderer_bezier_curve_to(renderer, -31.026924, 10.177841000000015,
                                -56.261459, -15.545074999999986, -56.261459,
                                -47.27590199999999);
    rr_renderer_fill(renderer);
    rr_renderer_set_fill(renderer, 0xffc6c6c6);
    rr_renderer_begin_path(renderer);
    rr_renderer_move_to(renderer, -63.857754, -47.270430000000005);
    rr_renderer_bezier_curve_to(renderer, -63.857754, -83.28078300000001,
                                -35.219837, -112.47294500000001,
                                0.10681900000000155, -112.47294500000001);
    rr_renderer_bezier_curve_to(renderer, 17.071281000000003,
                                -112.47294500000001, 33.340927, -105.6034115,
                                45.336609, -93.37556700000002);
    rr_renderer_bezier_curve_to(
        renderer, 57.332291000000005, -81.14772300000001, 64.07139600000001,
        -64.56320400000001, 64.07139600000001, -47.27042700000002);
    rr_renderer_bezier_curve_to(renderer, 64.07139600000001, -11.26006700000002,
                                35.43348700000001, 17.932087999999986,
                                0.10681900000000866, 17.932087999999986);
    rr_renderer_bezier_curve_to(
        renderer, -35.21983699999999, 17.932087999999986, -63.85775399999999,
        -11.260066000000013, -63.85775399999999, -47.27042700000002);
    rr_renderer_move_to(renderer, -44.276917, -47.27042700000002);
    rr_renderer_bezier_curve_to(renderer, -44.276917, -22.07426000000002,
                                -24.40564, -1.6487370000000183,
                                0.10681900000000155, -1.6487370000000183);
    rr_renderer_bezier_curve_to(renderer, 24.619285, -1.6487370000000183,
                                44.490555, -22.07425900000002, 44.490555,
                                -47.27042700000002);
    rr_renderer_bezier_curve_to(renderer, 44.490555, -72.46658700000002,
                                24.619285, -92.89210700000001,
                                0.10681900000000155, -92.89210700000001);
    rr_renderer_bezier_curve_to(renderer, -24.40564, -92.89210700000001,
                                -44.276917, -72.46658500000001, -44.276917,
                                -47.27042700000001);
    rr_renderer_fill(renderer);
}
