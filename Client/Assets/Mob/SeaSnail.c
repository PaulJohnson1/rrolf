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

void rr_sea_snail_body_draw(struct rr_renderer *renderer)
{
    rr_renderer_set_fill(renderer, 0xffab9761);
    rr_renderer_begin_path(renderer);
    rr_renderer_move_to(renderer, 85.98682, -73.008373);
    rr_renderer_line_to(renderer, 16.11596999999999, -68.5843236);
    rr_renderer_line_to(renderer, -51.70253000000001, -93.7141816);
    rr_renderer_line_to(renderer, -103.34758000000001, -37.627404600000006);
    rr_renderer_line_to(renderer, -88.390944, 47.46131539999999);
    rr_renderer_line_to(renderer, -13.146383999999998, 93.6394924);
    rr_renderer_line_to(renderer, 66.58630600000001, 65.94161639999999);
    rr_renderer_line_to(renderer, 103.894486, -2.7309336000000144);
    rr_renderer_fill(renderer);
    rr_renderer_set_fill(renderer, 0xff938150);
    rr_renderer_begin_path(renderer);
    rr_renderer_move_to(renderer, 4.834440000000001, 26.351259999999996);
    rr_renderer_bezier_curve_to(renderer, -14.491281999999998,
                                38.381288999999995, -39.522227, 35.728106,
                                -55.896563, 19.913988999999997);
    rr_renderer_line_to(renderer, -38.650446, 2.056918999999997);
    rr_renderer_bezier_curve_to(
        renderer, -30.463274000000002, 9.963977699999997, -17.947802000000003,
        11.290576999999997, -8.284945000000004, 5.275554599999997);
    rr_renderer_fill(renderer);
    rr_renderer_set_fill(renderer, 0xff938150);
    rr_renderer_begin_path(renderer);
    rr_renderer_move_to(renderer, -55.896609999999995, 19.914140000000003);
    rr_renderer_bezier_curve_to(renderer, -71.37488499999999, 4.965432000000003,
                                -73.507217, -19.089309999999998,
                                -60.899894499999995, -36.52766999999999);
    rr_renderer_line_to(renderer, -40.694492499999996, -21.919873999999993);
    rr_renderer_bezier_curve_to(renderer, -46.0329401, -14.535771999999993,
                                -45.13002409999999, -4.350033999999994,
                                -38.5759012, 1.9798530000000056);
    rr_renderer_fill(renderer);
    rr_renderer_set_fill(renderer, 0xff938150);
    rr_renderer_begin_path(renderer);
    rr_renderer_move_to(renderer, 32.85764, -18.824799999999996);
    rr_renderer_bezier_curve_to(
        renderer, 30.780308500000004, -0.21618799999999538, 20.395940000000003,
        16.453720000000004, 4.609150000000003, 26.522154);
    rr_renderer_line_to(renderer, -8.803492999999996, 5.4918119999999995);
    rr_renderer_bezier_curve_to(renderer, 0.6253170000000043,
                                -0.5216615000000004, 6.827488000000004,
                                -10.47793, 8.068196000000004, -21.592111);
    rr_renderer_fill(renderer);
    rr_renderer_set_fill(renderer, 0xff938150);
    rr_renderer_begin_path(renderer);
    rr_renderer_move_to(renderer, 19.13103000000001, -75.347652);
    rr_renderer_bezier_curve_to(renderer, 30.01321700000001, -58.300121,
                                34.76047000000001, -38.052848,
                                32.58986200000001, -17.944914999999995);
    rr_renderer_line_to(renderer, 7.813739000000012, -20.619444999999995);
    rr_renderer_bezier_curve_to(renderer, 9.376178000000012, -35.09353599999999,
                                5.959025600000013, -49.66793,
                                -1.8742034999999877, -61.939077999999995);
    rr_renderer_fill(renderer);
    rr_renderer_set_fill(renderer, 0xff938150);
    rr_renderer_begin_path(renderer);
    rr_renderer_move_to(renderer, -41.86452, -38.425476);
    rr_renderer_bezier_curve_to(renderer, -36.9577665, -33.6865997, -36.8216733,
                                -25.867271000000002, -41.5605573,
                                -20.960518000000004);
    rr_renderer_bezier_curve_to(renderer, -43.8362455, -18.604210000000005,
                                -46.9547683, -17.248428500000003, -50.2300823,
                                -17.191421600000005);
    rr_renderer_bezier_curve_to(renderer, -53.5053966, -17.134422393000005,
                                -56.6692073, -18.380859500000007,
                                -59.025515299999995, -20.656555300000004);
    rr_renderer_bezier_curve_to(renderer, -63.932264999999994,
                                -25.395431600000006, -64.0683583, -33.2147603,
                                -59.329477999999995, -38.121513300000004);
    rr_renderer_bezier_curve_to(renderer, -54.59060169999999,
                                -43.028266800000004, -46.771272999999994,
                                -43.164352300000004, -41.86452, -38.425476);
    rr_renderer_fill(renderer);
    rr_renderer_set_fill(renderer, 0xff938150);
    rr_renderer_begin_path(renderer);
    rr_renderer_move_to(renderer, -44.742965999999996, -102.86555);
    rr_renderer_bezier_curve_to(renderer, -19.686927999999995, -107.6136427,
                                5.718116000000002, -96.518317,
                                19.263934000000006, -74.911366);
    rr_renderer_line_to(renderer, -1.870045999999995, -61.662064);
    rr_renderer_bezier_curve_to(renderer, -9.960423999999994, -74.567032,
                                -25.133839999999996, -81.193829,
                                -40.098805999999996, -78.357983);
    rr_renderer_fill(renderer);
    rr_renderer_set_fill(renderer, 0xff938150);
    rr_renderer_begin_path(renderer);
    rr_renderer_move_to(renderer, -115.552542, -29.33019);
    rr_renderer_bezier_curve_to(renderer, -109.73121900000001,
                                -66.33397400000001, -81.349852, -95.72449,
                                -44.571951999999996, -102.83463);
    rr_renderer_line_to(renderer, -39.841795999999995, -78.367406);
    rr_renderer_bezier_curve_to(renderer, -66.315265, -73.2493907, -86.744739,
                                -52.093506000000005, -90.935042,
                                -25.457446000000004);
    rr_renderer_fill(renderer);
    rr_renderer_set_fill(renderer, 0xff938150);
    rr_renderer_begin_path(renderer);
    rr_renderer_move_to(renderer, 98.65916000000001, -74.46423300000001);
    rr_renderer_bezier_curve_to(
        renderer, 125.31858400000002, -30.737123000000004, 120.14040700000001,
        25.299577, 85.91947500000002, 63.400926999999996);
    rr_renderer_bezier_curve_to(renderer, 51.69855800000002, 101.50229099999999,
                                -3.462354999999974, 112.64673099999999,
                                -49.791024999999976, 90.819217);
    rr_renderer_bezier_curve_to(renderer, -96.11969199999999, 68.991702,
                                -122.64647499999998, 19.360536999999994,
                                -115.05398499999998, -31.286673000000008);
    rr_renderer_line_to(renderer, -90.35851799999998, -27.584585600000008);
    rr_renderer_bezier_curve_to(
        renderer, -96.31619599999998, 12.157258399999993, -75.50115299999997,
        51.10185439999999, -39.14798099999997, 68.22946439999998);
    rr_renderer_bezier_curve_to(
        renderer, -2.7948009999999712, 85.35707439999999, 40.48886900000002,
        76.61226139999998, 67.34134900000002, 46.714877399999985);
    rr_renderer_bezier_curve_to(renderer, 94.19382700000003, 16.817507399999986,
                                98.25702900000002, -27.153362600000015,
                                77.33791600000002, -61.46515260000002);
    rr_renderer_fill(renderer);
    rr_renderer_set_fill(renderer, 0xff938150);
    rr_renderer_begin_path(renderer);
    rr_renderer_move_to(renderer, 5.946520000000007, -71.526478);
    rr_renderer_bezier_curve_to(renderer, 28.303606000000006, -94.594814,
                                63.646150000000006, -99.12714199999999,
                                91.10063000000001, -82.44664);
    rr_renderer_line_to(renderer, 77.867354, -60.665955000000004);
    rr_renderer_bezier_curve_to(renderer, 60.579817000000006, -71.169331,
                                38.32531600000001, -68.315415,
                                24.247511000000003, -53.78974960000001);
    rr_renderer_fill(renderer);
    rr_renderer_set_fill(renderer, 0xff938150);
    rr_renderer_begin_path(renderer);
    rr_renderer_move_to(renderer, 95.73846, -79.481785);
    rr_renderer_bezier_curve_to(renderer, 100.6452135, -74.7429087, 100.7813067,
                                -66.92358, 96.04243034000001,
                                -62.016827000000006);
    rr_renderer_bezier_curve_to(renderer, 93.76673454000002, -59.66051900000001,
                                90.64821934000001, -58.30473750000001,
                                87.37290534000002, -58.247730600000004);
    rr_renderer_bezier_curve_to(renderer, 84.09757574000001, -58.19072758,
                                80.93377264000002, -59.43717230000001,
                                78.57746434000002, -61.712860500000005);
    rr_renderer_bezier_curve_to(renderer, 73.67071084000003, -66.4517368,
                                73.53461764000002, -74.27106850000001,
                                78.27349400000001, -79.1778185);
    rr_renderer_bezier_curve_to(renderer, 83.01238560000002, -84.084572,
                                90.83170600000001, -84.2206615,
                                95.73846000000002, -79.48178502);
    rr_renderer_fill(renderer);
}

void rr_sea_snail_head_draw(struct rr_renderer *renderer)
{
    rr_renderer_set_fill(renderer, 0xffab9f7d);
    rr_renderer_begin_path(renderer);
    rr_renderer_move_to(renderer, -23.813156000000006, -6.061226000000005);
    rr_renderer_line_to(renderer, 24.008573999999996, -6.061226000000005);
    rr_renderer_line_to(renderer, 24.008573999999996, 78.816589);
    rr_renderer_line_to(renderer, -23.813156000000006, 78.816589);
    rr_renderer_fill(renderer);
    rr_renderer_set_fill(renderer, 0xffab9f7d);
    rr_renderer_begin_path(renderer);
    rr_renderer_move_to(renderer, -38.555756, -84.303005);
    rr_renderer_bezier_curve_to(renderer, -26.537476, -81.5476835,
                                -19.028366000000002, -69.571316, -21.783684,
                                -57.553039);
    rr_renderer_bezier_curve_to(renderer, -23.1068423, -51.781653999999996,
                                -26.6684725, -46.772277, -31.685059000000003,
                                -43.626906999999996);
    rr_renderer_bezier_curve_to(renderer, -36.701653, -40.481528999999995,
                                -42.762276, -39.457816699999995, -48.533654,
                                -40.780975);
    rr_renderer_bezier_curve_to(renderer, -60.551934, -43.5362927, -68.061044,
                                -55.512664, -65.305722, -67.530941);
    rr_renderer_bezier_curve_to(renderer, -62.5504005, -79.549217, -50.574029,
                                -87.05832699999999, -38.555756, -84.303005);
    rr_renderer_fill(renderer);
    rr_renderer_set_fill(renderer, 0xffab9f7d);
    rr_renderer_begin_path(renderer);
    rr_renderer_move_to(renderer, -38.873059999999995, -84.15933);
    rr_renderer_bezier_curve_to(renderer, -15.175046999999996, -79.5628983,
                                1.942454000000005, -58.81765899999999,
                                1.9554160000000067, -34.678003);
    rr_renderer_line_to(renderer, -42.41484599999999, -34.654168770999995);
    rr_renderer_bezier_curve_to(renderer, -42.41640239649999, -37.555268971,
                                -44.47358469999999, -40.048432770999995,
                                -47.32160699999999, -40.600831770999996);
    rr_renderer_fill(renderer);
    rr_renderer_set_fill(renderer, 0xffab9f7d);
    rr_renderer_begin_path(renderer);
    rr_renderer_move_to(renderer, -42.36308, -38.218630000000005);
    rr_renderer_bezier_curve_to(renderer, -42.36308, -50.381922,
                                -32.502781999999996, -60.24222400000001,
                                -20.339481999999997, -60.24222400000001);
    rr_renderer_bezier_curve_to(
        renderer, -14.498463299999997, -60.24222400000001, -8.896679999999996,
        -57.92188860000001, -4.766452999999997, -53.791658700000006);
    rr_renderer_bezier_curve_to(
        renderer, -0.6362269999999963, -49.66144020000001, 1.6841085000000033,
        -44.059648700000004, 1.6841085000000033, -38.21862970000001);
    rr_renderer_line_to(renderer, 1.6841085000000033, 1.8899132999999892);
    rr_renderer_bezier_curve_to(renderer, 1.6841085000000033, 14.05320529999999,
                                -8.176189499999996, 23.91351129999999,
                                -20.339481499999994, 23.91351129999999);
    rr_renderer_bezier_curve_to(renderer, -32.5027815, 23.91351129999999,
                                -42.3630795, 14.05320529999999, -42.3630795,
                                1.8899132999999892);
    rr_renderer_fill(renderer);
    rr_renderer_set_fill(renderer, 0xffab9f7d);
    rr_renderer_begin_path(renderer);
    rr_renderer_move_to(renderer, -72.585915, 29.34022999999999);
    rr_renderer_bezier_curve_to(renderer, -81.388585, 18.07576499999999,
                                -79.391663, 1.8097119999999904,
                                -68.12566029999999, -6.991000000000007);
    rr_renderer_bezier_curve_to(
        renderer, -62.71553459999999, -11.217249700000007, -55.84774829999999,
        -13.121539000000006, -49.0331353, -12.284930000000006);
    rr_renderer_bezier_curve_to(renderer, -42.218522, -11.448328740000006,
                                -36.015305299999994, -7.9393640000000065,
                                -31.7881093, -2.529971000000007);
    rr_renderer_line_to(renderer, -0.8768242999999991, 37.026129);
    rr_renderer_bezier_curve_to(renderer, 7.925841700000001, 48.29061,
                                5.928916100000001, 64.55666199999999,
                                -5.337082799999999, 73.357367);
    rr_renderer_bezier_curve_to(renderer, -16.603088800000002, 82.158087,
                                -32.8719568, 80.16081849999999, -41.6746298,
                                68.896338);
    rr_renderer_fill(renderer);
    rr_renderer_set_fill(renderer, 0xffab9f7d);
    rr_renderer_begin_path(renderer);
    rr_renderer_move_to(renderer, 38.55628999999999, -84.30373800000001);
    rr_renderer_bezier_curve_to(renderer, 26.53800999999999, -81.54841650000002,
                                19.02889999999999, -69.572049,
                                21.78422599999999, -57.55377200000001);
    rr_renderer_bezier_curve_to(
        renderer, 23.107376599999988, -51.78238700000001, 26.66900699999999,
        -46.77301000000001, 31.68559299999999, -43.62764000000001);
    rr_renderer_bezier_curve_to(
        renderer, 36.70219459999999, -40.482262000000006, 42.76281799999999,
        -39.458549700000006, 48.53419499999999, -40.78170800000001);
    rr_renderer_bezier_curve_to(renderer, 60.55247499999999, -43.53702570000001,
                                68.061585, -55.51339700000001,
                                65.30625899999998, -67.53167400000001);
    rr_renderer_bezier_curve_to(renderer, 62.55093369999998, -79.54995000000001,
                                50.57456999999998, -87.05906000000002,
                                38.55628899999998, -84.30373800000001);
    rr_renderer_fill(renderer);
    rr_renderer_set_fill(renderer, 0xffab9f7d);
    rr_renderer_begin_path(renderer);
    rr_renderer_move_to(renderer, 38.87360000000001, -84.16006);
    rr_renderer_bezier_curve_to(renderer, 15.17558700000001, -79.5636245,
                                -1.9419059999999888, -58.818388999999996,
                                -1.9548759999999916, -34.678733);
    rr_renderer_line_to(renderer, 42.41537900000001, -34.654898771);
    rr_renderer_bezier_curve_to(renderer, 42.416950655300006, -37.555998971,
                                44.47412530000001, -40.049162771,
                                47.322148000000006, -40.601561771);
    rr_renderer_fill(renderer);
    rr_renderer_set_fill(renderer, 0xffab9f7d);
    rr_renderer_begin_path(renderer);
    rr_renderer_move_to(renderer, 42.36362, -38.219359999999995);
    rr_renderer_bezier_curve_to(renderer, 42.36362, -50.38265199999999,
                                32.503328999999994, -60.242954, 20.34003,
                                -60.242954);
    rr_renderer_bezier_curve_to(renderer, 14.4990113, -60.242954,
                                8.897219999999999, -57.9226148,
                                4.766993999999999, -53.7923887);
    rr_renderer_bezier_curve_to(renderer, 0.6367679999999982, -49.6621702,
                                -1.6835675000000014, -44.060378699999994,
                                -1.6835675000000014, -38.2193597);
    rr_renderer_line_to(renderer, -1.6835675000000014, 1.8891832999999991);
    rr_renderer_bezier_curve_to(renderer, -1.6835675000000014, 14.0524753,
                                8.176730499999998, 23.9127813,
                                20.340030499999997, 23.9127813);
    rr_renderer_bezier_curve_to(renderer, 32.5033305, 23.9127813,
                                42.363620499999996, 14.0524753,
                                42.363620499999996, 1.8891832999999991);
    rr_renderer_fill(renderer);
    rr_renderer_set_fill(renderer, 0xffab9f7d);
    rr_renderer_begin_path(renderer);
    rr_renderer_move_to(renderer, 72.58645999999999, 29.33950999999999);
    rr_renderer_bezier_curve_to(renderer, 81.38913299999999, 18.07502899999999,
                                79.3922004, 1.8089769999999916,
                                68.12619399999998, -6.991735000000013);
    rr_renderer_bezier_curve_to(
        renderer, 62.71606829999998, -11.217984700000013, 55.84828599999999,
        -13.122274000000012, 49.03367999999998, -12.285665000000012);
    rr_renderer_bezier_curve_to(
        renderer, 42.21905899999998, -11.449063740000012, 36.015841999999985,
        -7.9400990000000125, 31.788653999999983, -2.530706000000013);
    rr_renderer_line_to(renderer, 0.8773689999999839, 37.02539399999999);
    rr_renderer_bezier_curve_to(
        renderer, -7.925304000000017, 48.289874999999995, -5.9283790000000165,
        64.555927, 5.337619999999984, 73.35663199999999);
    rr_renderer_bezier_curve_to(renderer, 16.603625999999984, 82.15735199999999,
                                32.87250199999998, 80.16008349999998,
                                41.67517499999999, 68.895603);
    rr_renderer_fill(renderer);
    rr_renderer_set_fill(renderer, 0xffc1b490);
    rr_renderer_begin_path(renderer);
    rr_renderer_move_to(renderer, -42.282875000000004, -72.268757);
    rr_renderer_bezier_curve_to(renderer, -23.526489000000005, -68.6307947,
                                -9.981795000000005, -52.206565999999995,
                                -9.981795000000005, -33.100638999999994);
    rr_renderer_line_to(renderer, -29.930831000000005, -33.100638999999994);
    rr_renderer_bezier_curve_to(
        renderer, -29.930831000000005, -42.65360199999999, -36.7031775,
        -50.865714999999994, -46.081367, -52.684698999999995);
    rr_renderer_fill(renderer);
    rr_renderer_set_fill(renderer, 0xffc1b490);
    rr_renderer_begin_path(renderer);
    rr_renderer_move_to(renderer, -41.00533, -72.00901400000001);
    rr_renderer_bezier_curve_to(renderer, -35.6387986, -70.77976600000001,
                                -32.284863, -65.43283450000001, -33.514104,
                                -60.06629900000001);
    rr_renderer_bezier_curve_to(
        renderer, -34.104413140000005, -57.489200200000006, -35.6942874,
        -55.252151000000005, -37.933980000000005, -53.84727430000001);
    rr_renderer_bezier_curve_to(
        renderer, -40.173672700000004, -52.44239760000001, -42.8797197,
        -51.98477130000001, -45.45682240000001, -52.57508040000001);
    rr_renderer_bezier_curve_to(
        renderer, -50.82335380000001, -53.80432080000001, -54.17728940000001,
        -59.15125610000001, -52.948041, -64.51779140000001);
    rr_renderer_bezier_curve_to(renderer, -51.718793000000005, -69.8843228,
                                -46.3718615, -73.2382584, -41.00533,
                                -72.0090138);
    rr_renderer_fill(renderer);
    rr_renderer_set_fill(renderer, 0xffc1b490);
    rr_renderer_begin_path(renderer);
    rr_renderer_move_to(renderer, -29.92626, -34.71585);
    rr_renderer_bezier_curve_to(renderer, -29.92626, -40.222869,
                                -25.461942699999998, -44.687186000000004,
                                -19.954924, -44.687186000000004);
    rr_renderer_bezier_curve_to(renderer, -17.310354599999997,
                                -44.687186000000004, -14.774107299999997,
                                -43.6366413, -12.904119999999999, -41.7666461);
    rr_renderer_bezier_curve_to(renderer, -11.034132499999998, -39.8966586,
                                -9.9835801, -37.360411400000004, -9.9835801,
                                -34.715849600000006);
    rr_renderer_line_to(renderer, -9.9835801, 29.48735039999999);
    rr_renderer_bezier_curve_to(renderer, -9.9835801, 34.99436939999999,
                                -14.4479051, 39.45869439999999, -19.9549241,
                                39.45869439999999);
    rr_renderer_bezier_curve_to(renderer, -25.4619431, 39.45869439999999,
                                -29.9262601, 34.99436939999999, -29.9262601,
                                29.48735039999999);
    rr_renderer_fill(renderer);
    rr_renderer_set_fill(renderer, 0xffc1b490);
    rr_renderer_begin_path(renderer);
    rr_renderer_move_to(renderer, 42.475510000000014, -72.26881399999999);
    rr_renderer_bezier_curve_to(renderer, 23.719132000000013, -68.6308517,
                                10.174424000000016, -52.20661899999999,
                                10.174424000000016, -33.10069399999999);
    rr_renderer_line_to(renderer, 30.123460000000016, -33.10069399999999);
    rr_renderer_bezier_curve_to(
        renderer, 30.123460000000016, -42.65365699999999, 36.895814000000016,
        -50.865776999999994, 46.274003000000015, -52.68475399999999);
    rr_renderer_fill(renderer);
    rr_renderer_set_fill(renderer, 0xffc1b490);
    rr_renderer_begin_path(renderer);
    rr_renderer_move_to(renderer, 41.19797, -72.009068);
    rr_renderer_bezier_curve_to(renderer, 35.8314386, -70.7798238, 32.477496,
                                -65.4328885, 33.706744, -60.066356999999996);
    rr_renderer_bezier_curve_to(renderer, 34.2970455, -57.489258199999995,
                                35.8869198, -55.252205, 38.12662,
                                -53.847328499999996);
    rr_renderer_bezier_curve_to(
        renderer, 40.366305000000004, -52.44245179999999, 43.0723597,
        -51.984833099999996, 45.649462400000004, -52.5751346);
    rr_renderer_bezier_curve_to(renderer, 51.015993800000004, -53.8043826,
                                54.3699214, -59.1513141, 53.140673400000004,
                                -64.5178496);
    rr_renderer_bezier_curve_to(renderer, 51.911440600000006, -69.884381,
                                46.564501400000005, -73.2383166, 41.1979704,
                                -72.0090682);
    rr_renderer_fill(renderer);
    rr_renderer_set_fill(renderer, 0xffc1b490);
    rr_renderer_begin_path(renderer);
    rr_renderer_move_to(renderer, 30.11894000000001, -34.71592);
    rr_renderer_bezier_curve_to(renderer, 30.11894000000001, -40.222939,
                                25.65461500000001, -44.687264,
                                20.147596000000007, -44.687264);
    rr_renderer_bezier_curve_to(renderer, 17.50303420000001, -44.687264,
                                14.966779300000006, -43.6367116,
                                13.096799500000007, -41.7667241);
    rr_renderer_bezier_curve_to(renderer, 11.226804400000006, -39.8967366,
                                10.176267300000006, -37.3604894,
                                10.176267300000006, -34.7159201);
    rr_renderer_line_to(renderer, 10.176267300000006, 29.4872899);
    rr_renderer_bezier_curve_to(renderer, 10.176267300000006, 34.9943089,
                                14.640577000000008, 39.458618900000005,
                                20.147596300000007, 39.458618900000005);
    rr_renderer_bezier_curve_to(
        renderer, 25.654615300000007, 39.458618900000005, 30.118940300000006,
        34.994309200000004, 30.118940300000006, 29.487289900000004);
    rr_renderer_fill(renderer);
    rr_renderer_set_fill(renderer, 0xffc1b490);
    rr_renderer_begin_path(renderer);
    rr_renderer_move_to(renderer, 10.010649999999998, 4.497640000000004);
    rr_renderer_bezier_curve_to(
        renderer, 10.010649999999998, 10.751493000000004, 5.550742499999998,
        15.821241000000004, 0.04916299999999829, 15.821241000000004);
    rr_renderer_bezier_curve_to(
        renderer, -5.452416300000002, 15.821241000000004, -9.912331000000002,
        10.751493000000004, -9.912331000000002, 4.497640000000004);
    rr_renderer_bezier_curve_to(renderer, -8.315864900000001, 9.169126000000004,
                                -4.359604300000002, 12.246717000000004,
                                0.04916299999999829, 12.246717000000004);
    rr_renderer_bezier_curve_to(renderer, 4.457922999999998, 12.246717000000004,
                                8.414183999999999, 9.169126000000004,
                                10.010649999999998, 4.497640000000004);
    rr_renderer_fill(renderer);
    rr_renderer_set_fill(renderer, 0xffc1b490);
    rr_renderer_begin_path(renderer);
    rr_renderer_move_to(renderer, -20.977189999999993, 12.555419999999998);
    rr_renderer_line_to(renderer, 21.067854000000004, 12.555419999999998);
    rr_renderer_line_to(renderer, 21.067854000000004, 66.974365);
    rr_renderer_line_to(renderer, -20.977189999999993, 66.974365);
    rr_renderer_fill(renderer);
    rr_renderer_set_fill(renderer, 0xffc1b490);
    rr_renderer_begin_path(renderer);
    rr_renderer_move_to(renderer, -12.292730000000006, -0.2751599999999996);
    rr_renderer_line_to(renderer, -7.714048000000006, 9.925112);
    rr_renderer_line_to(renderer, -0.01297530000000613, 14.08832);
    rr_renderer_line_to(renderer, 7.272631099999994, 10.132845099999999);
    rr_renderer_line_to(renderer, 12.476641099999995, 0.7656420999999991);
    rr_renderer_line_to(renderer, 13.725176299999994, 15.544588099999999);
    rr_renderer_line_to(renderer, -13.541264700000006, 14.711519249999998);
    rr_renderer_fill(renderer);
    rr_renderer_set_fill(renderer, 0xffc1b490);
    rr_renderer_begin_path(renderer);
    rr_renderer_move_to(renderer, -62.849728, 21.851139999999987);
    rr_renderer_bezier_curve_to(
        renderer, -67.45150029999999, 15.881062499999986, -66.3468975,
        7.304859999999987, -60.382530599999996, 2.695675999999988);
    rr_renderer_bezier_curve_to(renderer, -57.5183415, 0.482266599999988,
                                -53.893600899999996, -0.5016050000000116,
                                -50.305717599999994, -0.039484800000011866);
    rr_renderer_bezier_curve_to(
        renderer, -46.717834599999996, 0.42262762999998815, -43.460701099999994,
        2.292866899999988, -41.250846599999996, 5.159810199999988);
    rr_renderer_line_to(renderer, -10.608939599999996, 44.91297019999999);
    rr_renderer_bezier_curve_to(renderer, -6.007163599999996, 50.88306319999999,
                                -7.111770099999996, 59.45926519999999,
                                -13.076133199999996, 64.06845719999998);
    rr_renderer_bezier_curve_to(
        renderer, -19.040503899999997, 68.67763379999998, -27.606048199999996,
        67.57440819999998, -32.207816199999996, 61.60431539999998);
    rr_renderer_fill(renderer);
    rr_renderer_set_fill(renderer, 0xffc1b490);
    rr_renderer_begin_path(renderer);
    rr_renderer_move_to(renderer, -29.876350000000002, 6.426850000000002);
    rr_renderer_bezier_curve_to(renderer, -26.992652500000002, 13.1554724,
                                -26.3922573, 19.357407000000002,
                                -28.535331300000003, 20.279236);
    rr_renderer_bezier_curve_to(renderer, -30.6784053, 21.2010805, -34.7534099,
                                16.493744, -37.637107300000004,
                                9.765122000000002);
    rr_renderer_bezier_curve_to(renderer, -35.1558756, 12.841553300000001,
                                -32.883262300000005, 14.238236,
                                -31.398116300000005, 13.599411600000002);
    rr_renderer_bezier_curve_to(
        renderer, -29.912970700000006, 12.960571900000001, -29.358657100000006,
        10.347901000000002, -29.876349600000005, 6.426850000000002);
    rr_renderer_fill(renderer);
    rr_renderer_set_fill(renderer, 0xffc1b490);
    rr_renderer_begin_path(renderer);
    rr_renderer_move_to(renderer, 62.94165000000001, 21.85123999999999);
    rr_renderer_bezier_curve_to(renderer, 67.54342600000001, 15.88114699999999,
                                66.43882710000001, 7.304959999999991,
                                60.47445640000001, 2.6957679999999904);
    rr_renderer_bezier_curve_to(renderer, 57.61027490000001, 0.4823585999999902,
                                53.985534400000006, -0.5015053000000096,
                                50.39764340000001, -0.039392800000009665);
    rr_renderer_bezier_curve_to(
        renderer, 46.809752800000005, 0.42271962999999035, 43.55262690000001,
        2.29296649999999, 41.34277240000001, 5.159902199999991);
    rr_renderer_line_to(renderer, 10.700865400000009, 44.91306819999999);
    rr_renderer_bezier_curve_to(renderer, 6.099089400000008, 50.88316119999999,
                                7.2036959000000085, 59.45936319999999,
                                13.168059000000008, 64.06854019999999);
    rr_renderer_bezier_curve_to(renderer, 19.13242970000001, 68.67773219999998,
                                27.697966000000008, 67.57450639999999,
                                32.29974200000001, 61.60441359999999);
    rr_renderer_fill(renderer);
    rr_renderer_set_fill(renderer, 0xffc1b490);
    rr_renderer_begin_path(renderer);
    rr_renderer_move_to(renderer, 29.968279999999993, 6.426956000000004);
    rr_renderer_bezier_curve_to(
        renderer, 27.084582499999993, 13.155578400000003, 26.484194999999993,
        19.357498000000007, 28.627261299999994, 20.279342000000003);
    rr_renderer_bezier_curve_to(
        renderer, 30.770342999999993, 21.201171200000005, 34.84533989999999,
        16.493850000000002, 37.729037299999995, 9.765228000000004);
    rr_renderer_bezier_curve_to(renderer, 35.24780559999999, 12.841659300000003,
                                32.975192299999996, 14.238342000000003,
                                31.490054299999994, 13.599502300000005);
    rr_renderer_bezier_curve_to(
        renderer, 30.004901099999994, 12.960677840000004, 29.450579799999993,
        10.348006900000005, 29.968279999999993, 6.426955900000005);
    rr_renderer_fill(renderer);
}
