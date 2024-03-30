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

void rr_king_mackarel_body_draw(struct rr_renderer *renderer)
{
    rr_renderer_set_fill(renderer, 0xff2e445b);
    rr_renderer_begin_path(renderer);
    rr_renderer_move_to(renderer, -67.784657, -98.67781);
    rr_renderer_bezier_curve_to(renderer, -67.771971224, 47.277770000000004,
                                -37.41709899999999, 165.56499,
                                0.01899300000000892, 165.54027);
    rr_renderer_bezier_curve_to(renderer, 37.45509700000001, 165.515550762,
                                67.79967300000001, 47.18821999999999,
                                67.79967300000001, -98.76735);
    rr_renderer_line_to(renderer, 0.0075130000000172, -98.76735);
    rr_renderer_fill(renderer);
    rr_renderer_set_fill(renderer, 0xff395470);
    rr_renderer_begin_path(renderer);
    rr_renderer_move_to(renderer, -59.745068, -98.77282);
    rr_renderer_bezier_curve_to(renderer, -59.745068, -131.774205, -32.996128,
                                -158.52711499999998, 0.0003659999999996444,
                                -158.52711499999998);
    rr_renderer_bezier_curve_to(renderer, 15.845839999999999,
                                -158.52711499999998, 31.04232, -152.2315923,
                                42.246766, -141.025488);
    rr_renderer_bezier_curve_to(renderer, 53.451203, -129.81938399999999,
                                59.745789, -114.620646, 59.745789,
                                -98.77282199999999);
    rr_renderer_bezier_curve_to(renderer, 59.745789, -65.771442,
                                32.996857000000006, -39.01852699999999,
                                0.00036700000000422506, -39.01852699999999);
    rr_renderer_bezier_curve_to(renderer, -32.996126999999994,
                                -39.01852699999999, -59.745067, -65.771441,
                                -59.745067, -98.77282199999999);
    rr_renderer_fill(renderer);
    rr_renderer_set_fill(renderer, 0xff2e445b);
    rr_renderer_begin_path(renderer);
    rr_renderer_move_to(renderer, -67.79802000000001, -98.77823);
    rr_renderer_bezier_curve_to(renderer, -67.79802000000001, -136.22436,
                                -37.44643500000001, -166.58044999999998,
                                -0.005850000000009459, -166.58044999999998);
    rr_renderer_bezier_curve_to(
        renderer, 17.97374899999999, -166.58044999999998, 35.21694999999999,
        -159.43702199999998, 47.93045199999999, -146.72163999999998);
    rr_renderer_bezier_curve_to(
        renderer, 60.64395299999999, -134.00625499999998, 67.786317,
        -116.76049699999999, 67.786317, -98.77822999999998);
    rr_renderer_bezier_curve_to(renderer, 67.786317, -61.33209399999998,
                                37.434723999999996, -30.975999999999985,
                                -0.0058530000000018845, -30.975999999999985);
    rr_renderer_bezier_curve_to(renderer, -37.446435, -30.975999999999985,
                                -67.798023, -61.332093999999984, -67.798023,
                                -98.77822999999998);
    rr_renderer_move_to(renderer, -50.806595, -98.77822999999998);
    rr_renderer_bezier_curve_to(renderer, -50.806595, -70.71620299999998,
                                -28.062328, -47.96742999999998,
                                -0.00585500000000394, -47.96742999999998);
    rr_renderer_bezier_curve_to(
        renderer, 28.050617999999996, -47.96742999999998, 50.79488799999999,
        -70.71620199999998, 50.79488799999999, -98.77822999999998);
    rr_renderer_bezier_curve_to(
        renderer, 50.79488799999999, -126.84025299999998, 28.050617999999993,
        -149.58901999999998, -0.00585500000000394, -149.58901999999998);
    rr_renderer_bezier_curve_to(
        renderer, -28.062328000000004, -149.58901999999998, -50.806595,
        -126.84025199999998, -50.806595, -98.77822999999998);
    rr_renderer_fill(renderer);
    rr_renderer_set_fill(renderer, 0xff395470);
    rr_renderer_begin_path(renderer);
    rr_renderer_move_to(renderer, -50.717224, -98.69905);
    rr_renderer_bezier_curve_to(renderer, -50.7095946055, 37.151759999999996,
                                -27.998588, 147.2558, 0.011725999999995906,
                                147.23731);
    rr_renderer_bezier_curve_to(
        renderer, 28.022040999999994, 147.21881634800002, 50.726865999999994,
        37.084770000000006, 50.726865999999994, -98.76605999999998);
    rr_renderer_line_to(renderer, 0.004811999999994043, -98.76605999999998);
    rr_renderer_fill(renderer);
    rr_renderer_set_fill(renderer, 0xff1e3042);
    rr_renderer_begin_path(renderer);
    rr_renderer_move_to(renderer, -7.627780000000001, 42.9409);
    rr_renderer_bezier_curve_to(renderer, -11.850077700000002, 38.71861,
                                -11.850077700000002, 31.872906999999998,
                                -7.627780000000001, 27.650602);
    rr_renderer_quadratic_curve_to(renderer, -3.8052016000000015,
                                   23.828031199999998, 0.017368999999998636,
                                   20.005444999999998);
    rr_renderer_quadratic_curve_to(renderer, 3.8399473999999985, 23.828031,
                                   7.662517999999999, 27.650602);
    rr_renderer_bezier_curve_to(renderer, 11.884823299999999, 31.8729073,
                                11.884823299999999, 38.71861, 7.662517999999999,
                                42.9409);
    rr_renderer_bezier_curve_to(renderer, 3.4402202999999982, 47.1632053,
                                -3.405483000000002, 47.1632053,
                                -7.627780000000001, 42.9409);
    rr_renderer_fill(renderer);
    rr_renderer_set_fill(renderer, 0xff1e3042);
    rr_renderer_begin_path(renderer);
    rr_renderer_move_to(renderer, 7.662520000000001, 27.650599999999997);
    rr_renderer_bezier_curve_to(renderer, 11.884825300000001, 31.8729053,
                                11.884825300000001, 38.718607999999996,
                                7.662520000000001, 42.940898);
    rr_renderer_quadratic_curve_to(renderer, 3.839949200000001, 46.763484,
                                   0.01737100000000069, 50.586054999999995);
    rr_renderer_quadratic_curve_to(renderer, -3.805199799999999,
                                   46.76348419999999, -7.627777999999999,
                                   42.940898);
    rr_renderer_bezier_curve_to(renderer, -11.8500757, 38.718607999999996,
                                -11.8500757, 31.872904999999996,
                                -7.627777999999999, 27.650599999999997);
    rr_renderer_bezier_curve_to(
        renderer, -3.405480299999999, 23.428294699999995, 3.4402230000000014,
        23.428294699999995, 7.662520000000001, 27.650599999999997);
    rr_renderer_fill(renderer);
    rr_renderer_set_fill(renderer, 0xff1e3042);
    rr_renderer_begin_path(renderer);
    rr_renderer_move_to(renderer, -7.627780000000001, 84.08456000000001);
    rr_renderer_bezier_curve_to(
        renderer, -11.850077700000002, 79.86227000000001, -11.850077700000002,
        73.01656700000001, -7.627780000000001, 68.794262);
    rr_renderer_quadratic_curve_to(renderer, -3.8052016000000015,
                                   64.97169120000001, 0.017368999999998636,
                                   61.1491204);
    rr_renderer_quadratic_curve_to(renderer, 3.8399473999999985, 64.9716912,
                                   7.662517999999999, 68.794262);
    rr_renderer_bezier_curve_to(renderer, 11.884823299999999, 73.0165673,
                                11.884823299999999, 79.86227000000001,
                                7.662517999999999, 84.08456000000001);
    rr_renderer_bezier_curve_to(renderer, 3.4402202999999982, 88.30688060000001,
                                -3.405483000000002, 88.30688060000001,
                                -7.627780000000001, 84.08456000000001);
    rr_renderer_fill(renderer);
    rr_renderer_set_fill(renderer, 0xff1e3042);
    rr_renderer_begin_path(renderer);
    rr_renderer_move_to(renderer, 7.662520000000001, 68.79427000000001);
    rr_renderer_bezier_curve_to(renderer, 11.884825300000001, 73.01657530000001,
                                11.884825300000001, 79.86227800000002,
                                7.662520000000001, 84.08456800000002);
    rr_renderer_quadratic_curve_to(renderer, 3.839949200000001,
                                   87.90715400000002, 0.01737100000000069,
                                   91.72970960000002);
    rr_renderer_quadratic_curve_to(renderer, -3.805199799999999,
                                   87.90715410000001, -7.627777999999999,
                                   84.08456800000002);
    rr_renderer_bezier_curve_to(renderer, -11.8500757, 79.86227800000002,
                                -11.8500757, 73.01657500000002,
                                -7.627777999999999, 68.79427000000001);
    rr_renderer_bezier_curve_to(renderer, -3.405480299999999, 64.57198000000001,
                                3.4402230000000014, 64.57198000000001,
                                7.662520000000001, 68.79427000000001);
    rr_renderer_fill(renderer);
    rr_renderer_set_fill(renderer, 0xff1e3042);
    rr_renderer_begin_path(renderer);
    rr_renderer_move_to(renderer, -7.629074000000003, 125.22951999999998);
    rr_renderer_bezier_curve_to(
        renderer, -11.851371700000003, 121.00722999999998, -11.851371700000003,
        114.16152699999998, -7.629074000000003, 109.93923699999998);
    rr_renderer_quadratic_curve_to(renderer, -3.806495600000003,
                                   106.11666619999998, 0.016074999999997175,
                                   102.29406499999997);
    rr_renderer_quadratic_curve_to(renderer, 3.838653399999997,
                                   106.11666629999998, 7.661223999999997,
                                   109.93923699999998);
    rr_renderer_bezier_curve_to(
        renderer, 11.883529299999998, 114.16152699999998, 11.883529299999998,
        121.00722999999998, 7.661223999999997, 125.22951999999998);
    rr_renderer_bezier_curve_to(
        renderer, 3.4389262999999968, 129.45184059999997, -3.4067770000000035,
        129.45184059999997, -7.629074000000003, 125.22951999999998);
    rr_renderer_fill(renderer);
    rr_renderer_set_fill(renderer, 0xff1e3042);
    rr_renderer_begin_path(renderer);
    rr_renderer_move_to(renderer, 7.661224000000004, 109.93923999999998);
    rr_renderer_bezier_curve_to(
        renderer, 11.883529300000005, 114.16152999999998, 11.883529300000005,
        121.00723299999999, 7.661224000000004, 125.22952299999999);
    rr_renderer_quadratic_curve_to(renderer, 3.8386532000000044, 129.0520938,
                                   0.01607500000000428, 132.87469499999997);
    rr_renderer_quadratic_curve_to(renderer, -3.8064957999999955,
                                   129.05209369999997, -7.629073999999996,
                                   125.22952299999997);
    rr_renderer_bezier_curve_to(
        renderer, -11.851371699999996, 121.00723299999997, -11.851371699999996,
        114.16152999999997, -7.629073999999996, 109.93923999999997);
    rr_renderer_bezier_curve_to(
        renderer, -3.4067762999999953, 105.71691939999997, 3.438927000000005,
        105.71691939999997, 7.661224000000004, 109.93923999999997);
    rr_renderer_fill(renderer);
    rr_renderer_set_fill(renderer, 0xff1e3042);
    rr_renderer_begin_path(renderer);
    rr_renderer_move_to(renderer, 7.662239999999997, -13.488139999999987);
    rr_renderer_bezier_curve_to(
        renderer, 11.883980699999997, -9.266414499999987, 11.883980699999997,
        -2.421611999999987, 7.662239999999997, 1.8001290000000125);
    rr_renderer_quadratic_curve_to(renderer, 3.840172699999997,
                                   5.622196300000013, 0.01810549999999722,
                                   9.444263500000012);
    rr_renderer_quadratic_curve_to(renderer, -3.803961800000003,
                                   5.622196200000012, -7.626029000000003,
                                   1.8001290000000125);
    rr_renderer_bezier_curve_to(
        renderer, -11.847769700000002, -2.4216116999999873, -11.847769700000002,
        -9.266414999999988, -7.626029000000003, -13.488139999999987);
    rr_renderer_bezier_curve_to(
        renderer, -3.404288300000003, -17.709880699999985, 3.4405069999999967,
        -17.709880699999985, 7.662239999999997, -13.488139999999987);
    rr_renderer_fill(renderer);
    rr_renderer_set_fill(renderer, 0xff1e3042);
    rr_renderer_begin_path(renderer);
    rr_renderer_move_to(renderer, -10.677170000000004, -8.141459999999995);
    rr_renderer_line_to(renderer, 0.01839399999999536, -79.44520999999999);
    rr_renderer_line_to(renderer, 10.713957999999995, -8.141459999999995);
    rr_renderer_fill(renderer);
}

void rr_king_mackarel_fin1_draw(struct rr_renderer *renderer)
{
    rr_renderer_set_fill(renderer, 0xff1e3042);
    rr_renderer_begin_path(renderer);
    rr_renderer_move_to(renderer, 22.135154999999997, -36.84164);
    rr_renderer_line_to(renderer, -39.142115000000004, -30.367339599999998);
    rr_renderer_line_to(renderer, -41.075384500000006, -12.981273599999998);
    rr_renderer_line_to(renderer, 24.54310549999999, -20.581409599999997);
    rr_renderer_fill(renderer);
    rr_renderer_set_fill(renderer, 0xff1e3042);
    rr_renderer_begin_path(renderer);
    rr_renderer_move_to(renderer, -50.344381, -16.050888);
    rr_renderer_bezier_curve_to(renderer, -47.0493466, 14.768218999999998,
                                -25.083540999999997, 40.359329,
                                4.878275000000002, 48.285882);
    rr_renderer_line_to(renderer, 23.999132000000003, -24.000557999999998);
    rr_renderer_fill(renderer);
    rr_renderer_set_fill(renderer, 0xff1e3042);
    rr_renderer_begin_path(renderer);
    rr_renderer_move_to(renderer, 21.79562, 33.824690000000004);
    rr_renderer_bezier_curve_to(renderer, 21.18028644, 26.393843000000004,
                                14.658024, 20.868818000000005, 7.227741,
                                21.484198000000006);
    rr_renderer_bezier_curve_to(renderer, 3.6595876, 21.779714970000008,
                                0.35496899999999965, 23.480680800000005,
                                -1.959149, 26.212889000000008);
    rr_renderer_bezier_curve_to(renderer, -4.273266400000001, 28.94510500000001,
                                -5.4073150000000005, 32.48476250000001,
                                -5.1118208, 36.053183000000004);
    rr_renderer_bezier_curve_to(renderer, -4.49648724, 43.484030000000004,
                                2.0257752, 49.009055000000004, 9.4560652,
                                48.393675);
    rr_renderer_bezier_curve_to(renderer, 16.8863478, 47.77829567,
                                22.410952199999997, 41.255537000000004,
                                21.795619199999997, 33.824690000000004);
    rr_renderer_fill(renderer);
    rr_renderer_set_fill(renderer, 0xff1e3042);
    rr_renderer_begin_path(renderer);
    rr_renderer_move_to(renderer, 37.23068000000001, -22.11045);
    rr_renderer_line_to(renderer, 20.797407000000007, 41.12323);
    rr_renderer_line_to(renderer, 2.9191650000000067, 33.8100357);
    rr_renderer_line_to(renderer, 14.928244000000007, -18.378822300000003);
    rr_renderer_fill(renderer);
    rr_renderer_set_fill(renderer, 0xff1e3042);
    rr_renderer_begin_path(renderer);
    rr_renderer_move_to(renderer, -23.609104000000002, -18.27017);
    rr_renderer_bezier_curve_to(renderer, -24.224441400000003, -25.701017,
                                -30.746704, -31.226042, -38.17699,
                                -30.610661999999998);
    rr_renderer_bezier_curve_to(renderer, -41.7451358, -30.315145029999996,
                                -45.0497584, -28.614182999999997, -47.363874,
                                -25.881966999999996);
    rr_renderer_bezier_curve_to(renderer, -49.6779914, -23.149754999999995,
                                -50.81204, -19.610093499999998, -50.5165458,
                                -16.041676999999996);
    rr_renderer_bezier_curve_to(renderer, -49.90121224, -8.610829999999996,
                                -43.378947800000006, -3.0858019999999957,
                                -35.9486648, -3.701188999999996);
    rr_renderer_bezier_curve_to(
        renderer, -28.518378400000003, -4.3165683299999955, -22.993769800000003,
        -10.839322999999997, -23.609103800000003, -18.270169999999997);
    rr_renderer_fill(renderer);
    rr_renderer_set_fill(renderer, 0xff1e3042);
    rr_renderer_begin_path(renderer);
    rr_renderer_move_to(renderer, 37.478669999999994, -24.803116000000003);
    rr_renderer_bezier_curve_to(renderer, 36.86332879999999, -32.233963,
                                30.341066199999993, -37.758988,
                                22.910783999999992, -37.143604);
    rr_renderer_bezier_curve_to(
        renderer, 19.342638199999993, -36.848090850000006, 16.03801199999999,
        -35.147128800000004, 13.723893999999992, -32.414913000000006);
    rr_renderer_bezier_curve_to(
        renderer, 11.409784199999992, -29.682697000000005, 10.275727999999992,
        -26.143039500000008, 10.571222199999992, -22.574623000000006);
    rr_renderer_bezier_curve_to(
        renderer, 11.186563399999992, -15.143776000000006, 17.70882599999999,
        -9.618748000000005, 25.139108199999992, -10.234131000000007);
    rr_renderer_bezier_curve_to(
        renderer, 32.569390799999994, -10.849510330000006, 38.09400319999999,
        -17.372269000000006, 37.47866919999999, -24.803116000000006);
    rr_renderer_fill(renderer);
    rr_renderer_set_fill(renderer, 0xff283e56);
    rr_renderer_begin_path(renderer);
    rr_renderer_move_to(renderer, -37.39735, -17.44243);
    rr_renderer_bezier_curve_to(renderer, -34.7931134, 8.155355999999998,
                                -16.598000000000003, 29.459019999999995,
                                8.275839999999995, 36.033826999999995);
    rr_renderer_line_to(renderer, 24.061613999999995, -23.696016000000007);
    rr_renderer_fill(renderer);
}

void rr_king_mackarel_fin2_draw(struct rr_renderer *renderer)
{
    rr_renderer_set_fill(renderer, 0xff1e3042);
    rr_renderer_begin_path(renderer);
    rr_renderer_move_to(renderer, -22.135193, -36.840675);
    rr_renderer_line_to(renderer, 39.142082, -30.366374599999997);
    rr_renderer_line_to(renderer, 41.0753477, -12.980308599999997);
    rr_renderer_line_to(renderer, -24.543142299999992, -20.580444599999996);
    rr_renderer_fill(renderer);
    rr_renderer_set_fill(renderer, 0xff1e3042);
    rr_renderer_begin_path(renderer);
    rr_renderer_move_to(renderer, 50.344345000000004, -16.049923);
    rr_renderer_bezier_curve_to(
        renderer, 47.049308700000005, 14.769186999999999, 25.083504000000005,
        40.360297, -4.8783109999999965, 48.286857000000005);
    rr_renderer_line_to(renderer, -23.999167999999997, -23.999582999999994);
    rr_renderer_fill(renderer);
    rr_renderer_set_fill(renderer, 0xff1e3042);
    rr_renderer_begin_path(renderer);
    rr_renderer_move_to(renderer, -21.795659999999998, 33.82566);
    rr_renderer_bezier_curve_to(renderer, -21.180326439999998, 26.394813,
                                -14.658063999999998, 20.869788,
                                -7.227776999999998, 21.485168);
    rr_renderer_bezier_curve_to(
        renderer, -3.659631199999998, 21.780684970000003, -0.3550049999999976,
        23.4816432, 1.9591050000000028, 26.213859000000003);
    rr_renderer_bezier_curve_to(renderer, 4.273222400000003, 28.946075000000004,
                                5.407271000000003, 32.485732500000005,
                                5.111776800000003, 36.054153);
    rr_renderer_bezier_curve_to(renderer, 4.496443240000003, 43.485,
                                -2.0258191999999973, 49.010025,
                                -9.456102199999997, 48.394645);
    rr_renderer_bezier_curve_to(renderer, -16.886388599999997,
                                47.779258039999995, -22.410997199999997,
                                41.256507, -21.795660199999997, 33.82566);
    rr_renderer_fill(renderer);
    rr_renderer_set_fill(renderer, 0xff1e3042);
    rr_renderer_begin_path(renderer);
    rr_renderer_move_to(renderer, -37.23072, -22.109479999999998);
    rr_renderer_line_to(renderer, -20.797442999999998, 41.1242);
    rr_renderer_line_to(renderer, -2.919196999999997, 33.8110057);
    rr_renderer_line_to(renderer, -14.928275999999997, -18.377854299999996);
    rr_renderer_fill(renderer);
    rr_renderer_set_fill(renderer, 0xff1e3042);
    rr_renderer_begin_path(renderer);
    rr_renderer_move_to(renderer, 23.609070000000003, -18.269202999999997);
    rr_renderer_bezier_curve_to(
        renderer, 24.224403560000002, -25.700049999999997, 30.746666000000005,
        -31.225074999999997, 38.176956000000004, -30.609690999999998);
    rr_renderer_bezier_curve_to(renderer, 41.7451018, -30.314177849999997,
                                45.0497206, -28.6132158, 47.363838,
                                -25.880999999999997);
    rr_renderer_bezier_curve_to(renderer, 49.6779554, -23.148783999999996,
                                50.812004, -19.609126499999995, 50.5165098,
                                -16.040709999999997);
    rr_renderer_bezier_curve_to(renderer, 49.90117624, -8.609862999999997,
                                43.3789138, -3.0848379999999977,
                                35.948630800000004, -3.700217999999998);
    rr_renderer_bezier_curve_to(
        renderer, 28.518340800000004, -4.3155973299999975, 22.993735800000003,
        -10.838355999999997, 23.609069800000004, -18.269202999999997);
    rr_renderer_fill(renderer);
    rr_renderer_set_fill(renderer, 0xff1e3042);
    rr_renderer_begin_path(renderer);
    rr_renderer_move_to(renderer, -37.4787, -24.802149999999997);
    rr_renderer_bezier_curve_to(renderer, -36.86336644, -32.2329934, -30.341104,
                                -37.758022, -22.910817, -37.142638);
    rr_renderer_bezier_curve_to(renderer, -19.342667400000003, -36.84712103,
                                -16.038048600000003, -35.146159,
                                -13.723931000000002, -32.413947);
    rr_renderer_bezier_curve_to(renderer, -11.409813600000001, -29.681731,
                                -10.275765000000002, -26.142073500000002,
                                -10.571259200000002, -22.573653);
    rr_renderer_bezier_curve_to(renderer, -11.186592760000002, -15.1428096,
                                -17.708859200000003, -9.617781,
                                -25.139142200000002, -10.233165);
    rr_renderer_bezier_curve_to(renderer, -32.5694286, -10.84854433,
                                -38.0940372, -17.371302999999997,
                                -37.478700200000006, -24.802149999999997);
    rr_renderer_fill(renderer);
    rr_renderer_set_fill(renderer, 0xff283e56);
    rr_renderer_begin_path(renderer);
    rr_renderer_move_to(renderer, 37.397316000000004, -17.441463);
    rr_renderer_bezier_curve_to(renderer, 34.7930756, 8.156319,
                                16.597961000000005, 29.459992,
                                -8.275873999999995, 36.034797000000005);
    rr_renderer_line_to(renderer, -24.061647999999995, -23.695049999999995);
    rr_renderer_fill(renderer);
}

void rr_king_mackarel_head_draw(struct rr_renderer *renderer)
{
    rr_renderer_set_fill(renderer, 0xff395470);
    rr_renderer_begin_path(renderer);
    rr_renderer_move_to(renderer, -48.650076, 26.00743);
    rr_renderer_bezier_curve_to(renderer, -48.650076, -0.9996580000000002,
                                -26.868022999999997, -22.893234999999997,
                                0.0015040000000041687, -22.893234999999997);
    rr_renderer_bezier_curve_to(
        renderer, 12.904702000000004, -22.893234999999997, 25.279420000000005,
        -17.741211699999997, 34.403359, -8.570556999999997);
    rr_renderer_bezier_curve_to(renderer, 43.5272985, 0.6000970000000034,
                                48.653077, 13.038177000000001, 48.653077,
                                26.007431);
    rr_renderer_bezier_curve_to(renderer, 48.653077, 53.014526000000004,
                                26.871026000000004, 74.908111,
                                0.0015040000000041687, 74.908111);
    rr_renderer_bezier_curve_to(renderer, -26.868021999999996, 74.908111,
                                -48.650076, 53.014526000000004, -48.650076,
                                26.007431000000004);
    rr_renderer_fill(renderer);
    rr_renderer_set_fill(renderer, 0xff2e445b);
    rr_renderer_begin_path(renderer);
    rr_renderer_move_to(renderer, 36.11053, 75.54409999999999);
    rr_renderer_bezier_curve_to(renderer, 37.9057876, 71.48250029999998,
                                36.23884879, 66.80684099999999, 32.3873397,
                                65.10070999999999);
    rr_renderer_bezier_curve_to(renderer, 30.5377761, 64.28140459999999,
                                28.4214889, 64.27046399999999,
                                26.504046699999996, 65.07029923299999);
    rr_renderer_bezier_curve_to(renderer, 24.586604399999995, 65.87013443299999,
                                23.025065699999995, 67.41522423299999,
                                22.1629594, 69.36566363299998);
    rr_renderer_bezier_curve_to(renderer, 20.367709499999997, 73.42726333299998,
                                22.034640609999997, 78.10293763299998,
                                25.8861574, 79.80905363299999);
    rr_renderer_bezier_curve_to(renderer, 29.7376664, 81.51518463299999,
                                34.3152804, 79.605699753, 36.1105304,
                                75.54410003299999);
    rr_renderer_fill(renderer);
    rr_renderer_set_fill(renderer, 0xff2e445b);
    rr_renderer_begin_path(renderer);
    rr_renderer_move_to(renderer, 33.345214999999996, 78.95006000000001);
    rr_renderer_bezier_curve_to(renderer, 47.150138999999996, 69.00113100000002,
                                56.319626, 53.869555000000005,
                                58.74955799999999, 37.02756000000001);
    rr_renderer_bezier_curve_to(renderer, 61.1794896, 20.185565000000008,
                                56.66124009999999, 3.0791420000000116,
                                46.23161399999999, -10.366306999999992);
    rr_renderer_line_to(renderer, 33.94242899999999, -0.8335919999999923);
    rr_renderer_bezier_curve_to(renderer, 41.78550759999999, 9.277393000000007,
                                45.18322799999999, 22.141406000000007,
                                43.355918999999986, 34.80659800000001);
    rr_renderer_bezier_curve_to(renderer, 41.52861029999998, 47.47177400000001,
                                34.633155999999985, 58.850711000000004,
                                24.251853999999987, 66.332324);
    rr_renderer_fill(renderer);
    rr_renderer_set_fill(renderer, 0xff2e445b);
    rr_renderer_begin_path(renderer);
    rr_renderer_move_to(renderer, -36.10896, 75.5446);
    rr_renderer_bezier_curve_to(renderer, -37.904209900000005, 71.4830003,
                                -36.237278790000005, 66.807326, -32.385762,
                                65.10121000000001);
    rr_renderer_bezier_curve_to(renderer, -30.5361984, 64.2818893,
                                -28.419918799999998, 64.27094877, -26.5024765,
                                65.07078397500001);
    rr_renderer_bezier_curve_to(renderer, -24.5850304, 65.87061917500002,
                                -23.0234955, 67.41572417500001, -22.1613855,
                                69.36616357500002);
    rr_renderer_bezier_curve_to(renderer, -20.3661317, 73.42776327500002,
                                -22.0330629, 78.10343757500002,
                                -25.884579600000002, 79.80955357500002);
    rr_renderer_bezier_curve_to(
        renderer, -29.736096300000003, 81.51568457500002, -34.3137066,
        79.60619969500003, -36.108960100000004, 75.54459997500003);
    rr_renderer_fill(renderer);
    rr_renderer_set_fill(renderer, 0xff2e445b);
    rr_renderer_begin_path(renderer);
    rr_renderer_move_to(renderer, -33.343643, 78.95056);
    rr_renderer_bezier_curve_to(renderer, -47.148567, 69.001631, -56.31805,
                                53.870054999999994, -58.747982,
                                37.028059999999996);
    rr_renderer_bezier_curve_to(
        renderer, -61.177913600000004, 20.186064999999996, -56.6596699,
        3.0796419999999998, -46.230044, -10.365807000000004);
    rr_renderer_line_to(renderer, -33.940856, -0.8331000000000035);
    rr_renderer_bezier_curve_to(renderer, -41.783932699999994,
                                9.277876999999997, -45.181653, 22.141906,
                                -43.354344, 34.807082);
    rr_renderer_bezier_curve_to(renderer, -41.527035299999994, 47.472274,
                                -34.631583, 58.85121, -24.250280999999998,
                                66.332808);
    rr_renderer_fill(renderer);
    rr_renderer_set_fill(renderer, 0xff2e445b);
    rr_renderer_begin_path(renderer);
    rr_renderer_move_to(renderer, -55.24308, 5.957579999999993);
    rr_renderer_line_to(renderer, -22.881092000000002, -69.39398000000001);
    rr_renderer_line_to(renderer, 22.900168, -69.39398000000001);
    rr_renderer_line_to(renderer, 55.262158, 5.957579999999993);
    rr_renderer_fill(renderer);
    rr_renderer_set_fill(renderer, 0xff2e445b);
    rr_renderer_begin_path(renderer);
    rr_renderer_move_to(renderer, -24.393135, -60.991547);
    rr_renderer_bezier_curve_to(renderer, -24.393135, -74.4650005, -13.470741,
                                -85.387391, 0.0027089999999994063, -85.387391);
    rr_renderer_bezier_curve_to(renderer, 6.472893299999999, -85.387391,
                                12.678071, -82.81712429999999, 17.253182,
                                -78.242013);
    rr_renderer_bezier_curve_to(renderer, 21.8282858, -73.6669054, 24.39856,
                                -67.461728, 24.39856, -60.991548);
    rr_renderer_bezier_curve_to(renderer, 24.39856, -47.518091, 13.476166,
                                -36.595704, 0.0027089999999994063, -36.595704);
    rr_renderer_bezier_curve_to(renderer, -13.470741, -36.595704, -24.393135,
                                -47.51809, -24.393135, -60.991547999999995);
    rr_renderer_fill(renderer);
    rr_renderer_set_fill(renderer, 0xff395470);
    rr_renderer_begin_path(renderer);
    rr_renderer_move_to(renderer, -41.491245, 12.690519999999992);
    rr_renderer_line_to(renderer, -6.0987849999999995, -66.33521);
    rr_renderer_line_to(renderer, 5.971871, -66.33521);
    rr_renderer_line_to(renderer, 41.364335, 12.690519999999992);
    rr_renderer_fill(renderer);
    rr_renderer_set_fill(renderer, 0xff395470);
    rr_renderer_begin_path(renderer);
    rr_renderer_move_to(renderer, -7.955344999999994, -60.990536);
    rr_renderer_bezier_curve_to(renderer, -7.955344999999994, -65.34985,
                                -4.421424699999994, -68.8837664,
                                -0.06211069999999452, -68.8837664);
    rr_renderer_bezier_curve_to(renderer, 2.0313036000000055, -68.8837664,
                                4.038978800000005, -68.0521624,
                                5.519241300000005, -66.5718958);
    rr_renderer_bezier_curve_to(renderer, 6.9995117000000056, -65.0916254,
                                7.831115700000005, -63.08395019999999,
                                7.831115700000005, -60.99053579999999);
    rr_renderer_bezier_curve_to(renderer, 7.831115700000005, -56.63122579999999,
                                4.297195400000005, -53.09730539999999,
                                -0.062110899999995084, -53.09730539999999);
    rr_renderer_bezier_curve_to(
        renderer, -4.421424899999995, -53.09730539999999, -7.955345199999995,
        -56.63122569999999, -7.955345199999995, -60.99053579999999);
    rr_renderer_fill(renderer);
}

void rr_king_mackarel_tail_draw(struct rr_renderer *renderer)
{
    rr_renderer_set_fill(renderer, 0xff1e3042);
    rr_renderer_begin_path(renderer);
    rr_renderer_move_to(renderer, -56.410416, 40.58250000000001);
    rr_renderer_line_to(renderer, -2.4039999999999964, 17.75129300000001);
    rr_renderer_line_to(renderer, 57.735427, 41.73716300000001);
    rr_renderer_line_to(renderer, 53.131194, 6.334393000000013);
    rr_renderer_line_to(renderer, -5.461548999999998, -8.712565999999986);
    rr_renderer_line_to(renderer, -57.432159, 16.713391000000016);
    rr_renderer_fill(renderer);
    rr_renderer_set_fill(renderer, 0xff1e3042);
    rr_renderer_begin_path(renderer);
    rr_renderer_move_to(renderer, 76.72813, 28.700439999999986);
    rr_renderer_bezier_curve_to(renderer, 76.72813, 36.41062999999998,
                                70.47256049999999, 42.65922599999999,
                                62.75591599999999, 42.657074499999986);
    rr_renderer_bezier_curve_to(renderer, 59.05024279999999, 42.656052161099986,
                                55.49634869999999, 41.18421989999999,
                                52.87604799999999, 38.565384499999986);
    rr_renderer_bezier_curve_to(renderer, 50.25574769999999, 35.94653379999998,
                                48.78368649999999, 32.39520319999998,
                                48.78368649999999, 28.692642499999984);
    rr_renderer_bezier_curve_to(renderer, 48.78368649999999, 20.982452499999983,
                                55.03925599999999, 14.733856499999984,
                                62.755915499999986, 14.736007999999984);
    rr_renderer_bezier_curve_to(renderer, 70.47255979999998, 14.738159489299983,
                                76.72812949999998, 20.990249999999982,
                                76.72812949999998, 28.700439999999986);
    rr_renderer_fill(renderer);
    rr_renderer_set_fill(renderer, 0xff1e3042);
    rr_renderer_begin_path(renderer);
    rr_renderer_move_to(renderer, -48.781654, 28.665449999999993);
    rr_renderer_bezier_curve_to(renderer, -48.781654, 36.37563999999999,
                                -55.037231000000006, 42.624235999999996,
                                -62.753875, 42.62208449999999);
    rr_renderer_bezier_curve_to(renderer, -66.4595406, 42.62106216109999,
                                -70.013431, 41.149229899999995, -72.633731,
                                38.53037919999999);
    rr_renderer_bezier_curve_to(renderer, -75.2540313, 35.91154379999999,
                                -76.7261, 32.36021319999999, -76.7261,
                                28.65765319999999);
    rr_renderer_bezier_curve_to(renderer, -76.7261, 20.94746319999999,
                                -70.470523, 14.698852199999992, -62.753875,
                                14.701003199999992);
    rr_renderer_bezier_curve_to(renderer, -55.0372307, 14.703154689299991,
                                -48.781654, 20.955245199999993, -48.781654,
                                28.66545019999999);
    rr_renderer_fill(renderer);
    rr_renderer_set_fill(renderer, 0xff1e3042);
    rr_renderer_begin_path(renderer);
    rr_renderer_move_to(renderer, -55.10611, 40.315140000000014);
    rr_renderer_bezier_curve_to(renderer, -55.10611, 11.988953000000013,
                                -30.43383, -10.967063999999986,
                                0.0009700000000023579, -10.958579999999984);
    rr_renderer_bezier_curve_to(
        renderer, 30.435762000000004, -10.950096112999983, 55.108050000000006,
        12.019684000000016, 55.108050000000006, 40.34585600000002);
    rr_renderer_bezier_curve_to(
        renderer, 50.054293300000005, 15.730408000000018, 26.925845000000006,
        -2.0780639999999835, 0.0009700000000023579, -2.0855709999999803);
    rr_renderer_bezier_curve_to(renderer, -26.923903, -2.0930783239999804,
                                -50.05235, 15.70249900000002, -55.10611,
                                40.315139000000016);
    rr_renderer_fill(renderer);
    rr_renderer_set_fill(renderer, 0xff1e3042);
    rr_renderer_begin_path(renderer);
    rr_renderer_move_to(renderer, -76.653893, 30.89152999999999);
    rr_renderer_bezier_curve_to(renderer, -76.653893, -9.730280000000015,
                                -42.318222999999996, -42.651195000000016,
                                0.036977000000007365, -42.63938400000001);
    rr_renderer_bezier_curve_to(renderer, 42.39217700000001, -42.62757369700001,
                                76.72785700000001, -9.687524000000003,
                                76.72785700000001, 30.934286);
    rr_renderer_bezier_curve_to(renderer, 33.701397000000014, -8.114359,
                                -33.627442999999985, -8.133133999999998,
                                -76.653883, 30.891530873);
    rr_renderer_fill(renderer);
    rr_renderer_set_fill(renderer, 0xff283e56);
    rr_renderer_begin_path(renderer);
    rr_renderer_move_to(renderer, -63.09736, 29.067579999999992);
    rr_renderer_bezier_curve_to(renderer, -63.09736, -3.6283200000000093,
                                -34.847253, -30.125710000000005,
                                0.0010300000000000864, -30.116000000000007);
    rr_renderer_bezier_curve_to(
        renderer, 34.849304000000004, -30.106280151000007, 63.09941,
        -3.5931420000000074, 63.09941, 29.10276499999999);
    rr_renderer_bezier_curve_to(renderer, 50.106260999999996, 7.92132999999999,
                                26.045499999999997, -5.138278000000007,
                                0.0010300000000000864, -5.145541000000009);
    rr_renderer_bezier_curve_to(renderer, -26.04345, -5.152796554000009,
                                -50.10421, 7.8933919999999915, -63.09736,
                                29.067578999999995);
    rr_renderer_fill(renderer);
    rr_renderer_set_fill(renderer, 0xff283e56);
    rr_renderer_begin_path(renderer);
    rr_renderer_move_to(renderer, -63.036823, 27.97720000000001);
    rr_renderer_line_to(renderer, -1.8863289999999964, 1.4796100000000116);
    rr_renderer_line_to(renderer, 62.320771, 28.996944000000013);
    rr_renderer_line_to(renderer, 56.716111, 12.688930000000013);
    rr_renderer_line_to(renderer, 3.718330999999999, -18.904750999999987);
    rr_renderer_line_to(renderer, -45.711669, -4.1250499999999874);
    rr_renderer_fill(renderer);
}