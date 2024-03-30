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

void rr_prop_moss_draw(struct rr_renderer *renderer)
{
    rr_renderer_set_fill(renderer, 0xff11470f);
    rr_renderer_begin_path(renderer);
    rr_renderer_move_to(renderer, -226.56431, 41.28035999999997);
    rr_renderer_bezier_curve_to(renderer, -226.56431, -57.00895000000003,
                                -145.29871, -136.68814000000003,
                                -45.05250000000001, -136.68814000000003);
    rr_renderer_bezier_curve_to(
        renderer, 3.087422999999994, -136.68814000000003, 49.255669999999995,
        -117.93794200000004, 83.29574, -84.56237700000003);
    rr_renderer_bezier_curve_to(renderer, 117.33581, -51.18679700000003,
                                136.459314, -5.919827000000026, 136.459314,
                                41.28036299999998);
    rr_renderer_bezier_curve_to(renderer, 136.459314, 139.569639,
                                55.19372000000001, 219.24884299999997,
                                -45.05249599999999, 219.24884299999997);
    rr_renderer_bezier_curve_to(renderer, -145.298712, 219.24884299999997,
                                -226.564306, 139.56964299999999, -226.564306,
                                41.280362999999966);
    rr_renderer_fill(renderer);
    rr_renderer_set_fill(renderer, 0xff11470f);
    rr_renderer_begin_path(renderer);
    rr_renderer_move_to(renderer, -104.37496999999999, -79.80054000000001);
    rr_renderer_bezier_curve_to(
        renderer, -104.37496999999999, -156.81598000000002, -40.70071499999999,
        -219.24934000000002, 37.84549000000001, -219.24934000000002);
    rr_renderer_bezier_curve_to(renderer, 75.56469800000002,
                                -219.24934000000002, 111.73904500000002,
                                -204.55744500000003, 138.41055, -178.405727);
    rr_renderer_bezier_curve_to(renderer, 165.08205900000002, -152.253994,
                                180.065976, -116.784647, 180.065976,
                                -79.80053300000002);
    rr_renderer_bezier_curve_to(renderer, 180.065976, -2.7850630000000223,
                                116.39169000000001, 59.648286999999996,
                                37.845485999999994, 59.648286999999996);
    rr_renderer_bezier_curve_to(
        renderer, -40.700714000000005, 59.648286999999996, -104.37497400000001,
        -2.785063000000001, -104.37497400000001, -79.80053300000002);
    rr_renderer_fill(renderer);
    rr_renderer_set_fill(renderer, 0xff11470f);
    rr_renderer_begin_path(renderer);
    rr_renderer_move_to(renderer, 135.7581, 59.426800000000014);
    rr_renderer_bezier_curve_to(renderer, 111.47495800000002, 51.02509700000002,
                                97.43009700000002, 28.491284000000014,
                                104.38801300000002, 9.096080000000015);
    rr_renderer_bezier_curve_to(
        renderer, 111.34592930000001, -10.299122999999984, 136.671826,
        -19.211109999999984, 160.95493800000003, -10.809437999999986);
    rr_renderer_bezier_curve_to(renderer, 145.35914300000002, 9.701396000000013,
                                136.69773600000002, 33.84510200000001, 135.7581,
                                59.42680200000001);
    rr_renderer_fill(renderer);
    rr_renderer_set_fill(renderer, 0xff11470f);
    rr_renderer_begin_path(renderer);
    rr_renderer_move_to(renderer, 36.168000000000006, 22.95116999999999);
    rr_renderer_bezier_curve_to(
        renderer, 36.168000000000006, -28.58090400000001, 78.789094,
        -70.35593000000001, 131.36487, -70.35593000000001);
    rr_renderer_bezier_curve_to(renderer, 156.612642, -70.35593000000001,
                                180.826296, -60.52539400000001,
                                198.67919999999998, -43.02692000000002);
    rr_renderer_bezier_curve_to(
        renderer, 216.53204399999998, -25.528446000000017, 226.56170699999998,
        -1.7954140000000152, 226.56170699999998, 22.951169999999976);
    rr_renderer_bezier_curve_to(renderer, 226.56170699999998, 74.48324399999998,
                                183.94061299999998, 116.25826999999998,
                                131.364867, 116.25826999999998);
    rr_renderer_bezier_curve_to(renderer, 78.78909200000001, 116.25826999999998,
                                36.167997, 74.48324599999998, 36.167997,
                                22.951169999999976);
    rr_renderer_fill(renderer);
    rr_renderer_set_fill(renderer, 0xff11470f);
    rr_renderer_begin_path(renderer);
    rr_renderer_move_to(renderer, 109.71370000000002, 166.16021999999998);
    rr_renderer_bezier_curve_to(renderer, 109.71370000000002, 143.99924,
                                128.03126600000002, 126.03424299999998,
                                150.62709, 126.03424299999998);
    rr_renderer_bezier_curve_to(renderer, 161.478012, 126.03424299999998,
                                171.884475, 130.26178199999998,
                                179.55723500000002, 137.78686749999997);
    rr_renderer_bezier_curve_to(renderer, 187.22996450000002,
                                145.31195289999997, 191.540511, 155.5181295,
                                191.540511, 166.16021949999998);
    rr_renderer_bezier_curve_to(renderer, 191.540511, 188.3211695, 173.222945,
                                206.2861965, 150.627091, 206.2861965);
    rr_renderer_bezier_curve_to(renderer, 128.03126600000002, 206.2861965,
                                109.71370100000001, 188.3211695,
                                109.71370100000001, 166.16021949999998);
    rr_renderer_fill(renderer);
    rr_renderer_set_fill(renderer, 0xff155814);
    rr_renderer_begin_path(renderer);
    rr_renderer_move_to(renderer, -196.2336, 41.28075999999999);
    rr_renderer_bezier_curve_to(renderer, -196.2336, -40.579130000000006,
                                -128.54752, -106.93971000000002,
                                -45.05250000000001, -106.93971000000002);
    rr_renderer_bezier_curve_to(
        renderer, -4.956797000000009, -106.93971000000002, 33.496725,
        -91.32366700000001, 61.84868399999999, -63.52694400000002);
    rr_renderer_bezier_curve_to(renderer, 90.20064399999998, -35.73019100000002,
                                106.128591, 1.9702459999999817, 106.128591,
                                41.28076599999998);
    rr_renderer_bezier_curve_to(renderer, 106.128591, 123.14065599999998,
                                38.442525, 189.50122599999997,
                                -45.05249900000001, 189.50122599999997);
    rr_renderer_bezier_curve_to(renderer, -128.547525, 189.50122599999997,
                                -196.233599, 123.14066099999998, -196.233599,
                                41.28076599999997);
    rr_renderer_fill(renderer);
    rr_renderer_set_fill(renderer, 0xff155814);
    rr_renderer_begin_path(renderer);
    rr_renderer_move_to(renderer, -74.57999999999998, -79.80054000000001);
    rr_renderer_bezier_curve_to(renderer, -74.57999999999998, -140.673617,
                                -24.24552699999998, -190.02100000000002,
                                37.84520000000002, -190.02100000000002);
    rr_renderer_bezier_curve_to(
        renderer, 67.66221700000003, -190.02100000000002, 96.25801000000001,
        -178.40852700000002, 117.34181000000002, -157.73818);
    rr_renderer_bezier_curve_to(renderer, 138.42564200000004,
                                -137.06783000000001, 150.27040000000002,
                                -109.032812, 150.27040000000002, -79.80054);
    rr_renderer_bezier_curve_to(renderer, 150.27040000000002,
                                -18.927431999999996, 99.93592700000002,
                                30.41995, 37.84520000000002, 30.41995);
    rr_renderer_bezier_curve_to(renderer, -24.24552999999998, 30.41995,
                                -74.57999999999998, -18.92743,
                                -74.57999999999998, -79.80054);
    rr_renderer_fill(renderer);
    rr_renderer_set_fill(renderer, 0xff155814);
    rr_renderer_begin_path(renderer);
    rr_renderer_move_to(renderer, 64.86090000000002, 22.95013);
    rr_renderer_bezier_curve_to(
        renderer, 64.86090000000002, -13.057102999999998, 94.63571000000002,
        -42.24670999999999, 131.36484000000002, -42.24670999999999);
    rr_renderer_bezier_curve_to(
        renderer, 149.00278000000003, -42.24670999999999, 165.91830700000003,
        -35.377782999999994, 178.39020000000002, -23.151006999999993);
    rr_renderer_bezier_curve_to(
        renderer, 190.86212400000002, -10.924230999999994, 197.86877700000002,
        5.658868000000009, 197.86877700000002, 22.950128000000007);
    rr_renderer_bezier_curve_to(
        renderer, 197.86877700000002, 58.957361000000006, 168.093936,
        88.14699800000001, 131.36483700000002, 88.14699800000001);
    rr_renderer_bezier_curve_to(renderer, 94.63571100000001, 88.14699800000001,
                                64.86089700000002, 58.95736200000001,
                                64.86089700000002, 22.950128000000007);
    rr_renderer_fill(renderer);
    rr_renderer_set_fill(renderer, 0xff155814);
    rr_renderer_begin_path(renderer);
    rr_renderer_move_to(renderer, 132.20211999999998, 166.15982000000002);
    rr_renderer_bezier_curve_to(
        renderer, 132.20211999999998, 156.17520100000002, 140.45135699999997,
        148.08108500000003, 150.627321, 148.08108500000003);
    rr_renderer_bezier_curve_to(renderer, 155.5139787, 148.08108500000003,
                                160.200502, 149.98577860000003, 163.655916,
                                153.37622050000002);
    rr_renderer_bezier_curve_to(renderer, 167.11129929999998,
                                156.76663190000002, 169.0525224, 161.3650205,
                                169.0525224, 166.15982050000002);
    rr_renderer_bezier_curve_to(renderer, 169.0525224, 176.14440950000002,
                                160.8032854, 184.23852550000004,
                                150.62732139999997, 184.23852550000004);
    rr_renderer_bezier_curve_to(
        renderer, 140.45135739999998, 184.23852550000004, 132.20212039999996,
        176.14440950000005, 132.20212039999996, 166.15982050000002);
    rr_renderer_fill(renderer);
    rr_renderer_set_fill(renderer, 0xff196316);
    rr_renderer_begin_path(renderer);
    rr_renderer_move_to(renderer, 27.318240000000003, -72.81896999999998);
    rr_renderer_bezier_curve_to(
        renderer, 27.318240000000003, -100.83328299999998, 50.472506,
        -123.54336599999998, 79.034762, -123.54336599999998);
    rr_renderer_bezier_curve_to(renderer, 92.750857, -123.54336599999998,
                                105.905154, -118.19920399999998, 115.603884,
                                -108.68653899999998);
    rr_renderer_bezier_curve_to(
        renderer, 125.30261399999999, -99.17385899999998, 130.75131399999998,
        -86.27191199999999, 130.75131399999998, -72.81896899999998);
    rr_renderer_bezier_curve_to(
        renderer, 130.75131399999998, -44.80465599999998, 107.59701699999998,
        -22.09454299999998, 79.03476099999997, -22.09454299999998);
    rr_renderer_bezier_curve_to(renderer, 50.47250499999997, -22.09454299999998,
                                27.318238999999977, -44.80465699999998,
                                27.318238999999977, -72.81896899999998);
    rr_renderer_fill(renderer);
    rr_renderer_set_fill(renderer, 0xff196316);
    rr_renderer_begin_path(renderer);
    rr_renderer_move_to(renderer, 89.87009999999998, 22.81103999999999);
    rr_renderer_bezier_curve_to(
        renderer, 89.87009999999998, -1.1676900000000074, 109.68238599999998,
        -20.606288000000006, 134.122053, -20.606288000000006);
    rr_renderer_bezier_curve_to(renderer, 145.858412, -20.606288000000006,
                                157.11408799999998, -16.031977700000006,
                                165.412916, -7.889644000000006);
    rr_renderer_bezier_curve_to(renderer, 173.711775, 0.2526899999999941,
                                178.374037, 11.296055999999995, 178.374037,
                                22.81103999999999);
    rr_renderer_bezier_curve_to(renderer, 178.374037, 46.78976999999999,
                                158.561751, 66.22836799999999, 134.122053,
                                66.22836799999999);
    rr_renderer_bezier_curve_to(renderer, 109.682386, 66.22836799999999,
                                89.8701, 46.78976899999999, 89.8701,
                                22.81103999999999);
    rr_renderer_fill(renderer);
    rr_renderer_set_fill(renderer, 0xff196316);
    rr_renderer_begin_path(renderer);
    rr_renderer_move_to(renderer, -9.368769999999984, 22.810969999999998);
    rr_renderer_bezier_curve_to(renderer, -9.368769999999984,
                                1.3457899999999974, 8.370640000000016,
                                -16.05518, 30.253300000000017, -16.05518);
    rr_renderer_bezier_curve_to(renderer, 40.76169200000002, -16.05518,
                                50.83972600000001, -11.960362,
                                58.27029800000002, -4.671544000000001);
    rr_renderer_bezier_curve_to(renderer, 65.70087050000002, 2.6172743999999994,
                                69.87533950000002, 12.503015999999999,
                                69.87533950000002, 22.810969);
    rr_renderer_bezier_curve_to(renderer, 69.87533950000002, 44.276149000000004,
                                52.135929500000024, 61.677089,
                                30.253299500000026, 61.677089);
    rr_renderer_bezier_curve_to(renderer, 8.370639500000024, 61.677089,
                                -9.368770499999975, 44.276149000000004,
                                -9.368770499999975, 22.810969);
    rr_renderer_fill(renderer);
    rr_renderer_set_fill(renderer, 0xff196316);
    rr_renderer_begin_path(renderer);
    rr_renderer_move_to(renderer, -169.00063, 27.841340000000002);
    rr_renderer_bezier_curve_to(renderer, -174.6626326, 11.812043000000003,
                                -166.00446, -5.863889999999998,
                                -149.66205300000001, -11.638976);
    rr_renderer_bezier_curve_to(renderer, -141.8141526, -14.412260999999999,
                                -133.207555, -14.0141286, -125.73563100000001,
                                -10.532134);
    rr_renderer_bezier_curve_to(renderer, -118.2637224, -7.05017,
                                -112.53851800000001, -0.7695909999999984,
                                -109.81952400000002, 6.927949000000002);
    rr_renderer_bezier_curve_to(renderer, -104.15752140000002, 22.957276,
                                -112.81570930000001, 40.63320900000001,
                                -129.158117, 46.408265);
    rr_renderer_bezier_curve_to(renderer, -145.500524, 52.1833504, -163.338627,
                                43.8706368, -169.000631, 27.84134);
    rr_renderer_fill(renderer);
    rr_renderer_set_fill(renderer, 0xff196316);
    rr_renderer_begin_path(renderer);
    rr_renderer_move_to(renderer, -113.86385000000001, 69.91829999999999);
    rr_renderer_bezier_curve_to(
        renderer, -118.70830200000002, 56.193781999999985, -111.29808460000001,
        41.05608699999999, -97.31267200000002, 36.10726499999999);
    rr_renderer_bezier_curve_to(renderer, -90.59663800000003, 33.73076959999999,
                                -83.23152600000002, 34.06975899999999,
                                -76.83755900000003, 37.04964779999999);
    rr_renderer_bezier_curve_to(renderer, -70.44360760000002, 40.02956719999999,
                                -65.54456000000003, 45.40630679999999,
                                -63.218174000000026, 51.99703579999999);
    rr_renderer_bezier_curve_to(renderer, -58.37372200000003, 65.72152279999999,
                                -65.78393940000002, 80.8592188,
                                -79.76935200000003, 85.80804079999999);
    rr_renderer_bezier_curve_to(renderer, -93.75478000000003, 90.7568628,
                                -109.01939800000002, 83.64278809999999,
                                -113.86385000000003, 69.91830079999998);
    rr_renderer_fill(renderer);
    rr_renderer_set_fill(renderer, 0xff196316);
    rr_renderer_begin_path(renderer);
    rr_renderer_move_to(renderer, -170.64384, 89.9991);
    rr_renderer_bezier_curve_to(renderer, -174.9838516, 77.709702,
                                -168.34919280000003, 64.158371, -155.824947,
                                59.731399999999994);
    rr_renderer_bezier_curve_to(renderer, -149.8105885, 57.605484499999996,
                                -143.214641, 57.91105699999999,
                                -137.48814000000002, 60.58085679999999);
    rr_renderer_bezier_curve_to(
        renderer, -131.76162330000002, 63.25065659999999, -127.37365300000002,
        68.06602529999999, -125.28951600000002, 73.96760579999999);
    rr_renderer_bezier_curve_to(
        renderer, -120.94950440000002, 86.25703479999999, -127.58416320000002,
        99.80836579999999, -140.10840900000002, 104.23533579999999);
    rr_renderer_bezier_curve_to(
        renderer, -152.63265500000003, 108.66230719999999, -166.30384400000003,
        102.28852789999999, -170.643839, 89.99909879999998);
    rr_renderer_fill(renderer);
    rr_renderer_set_fill(renderer, 0xff196316);
    rr_renderer_begin_path(renderer);
    rr_renderer_move_to(renderer, -45.67487, 155.0233);
    rr_renderer_bezier_curve_to(renderer, -50.519322, 141.298813,
                                -43.109104599999995, 126.16108700000001,
                                -29.123692, 121.212265);
    rr_renderer_bezier_curve_to(renderer, -22.407657999999998, 118.8357696,
                                -15.042545999999998, 119.17475900000001,
                                -8.648594, 122.1546478);
    rr_renderer_bezier_curve_to(renderer, -2.2546425999999995, 125.1345672,
                                2.644405000000001, 130.5113068, 4.970791,
                                137.1020358);
    rr_renderer_bezier_curve_to(renderer, 9.815243, 150.82652280000002,
                                2.4050256, 165.9642488, -11.580387,
                                170.9130708);
    rr_renderer_bezier_curve_to(renderer, -25.5658, 175.86189280000002,
                                -40.830417, 168.7477876, -45.674869,
                                155.02330030000002);
    rr_renderer_fill(renderer);
    rr_renderer_set_fill(renderer, 0xff196316);
    rr_renderer_begin_path(renderer);
    rr_renderer_move_to(renderer, -59.41766000000001, -63.858600000000024);
    rr_renderer_bezier_curve_to(
        renderer, -64.26211200000002, -77.58308700000002, -56.85189460000001,
        -92.72079800000003, -42.86648200000001, -97.66962000000002);
    rr_renderer_bezier_curve_to(
        renderer, -36.15044800000001, -100.04613060000003, -28.78530500000001,
        -99.70714140000003, -22.39135400000001, -96.72723720000002);
    rr_renderer_bezier_curve_to(
        renderer, -15.997402600000012, -93.74731780000002, -11.09835500000001,
        -88.37059320000002, -8.771969000000011, -81.77986520000002);
    rr_renderer_bezier_curve_to(
        renderer, -3.9275170000000106, -68.05537820000002, -11.337734400000011,
        -52.91765220000002, -25.323147000000013, -47.96883020000002);
    rr_renderer_bezier_curve_to(
        renderer, -39.30859000000001, -43.02000820000002, -54.57320800000001,
        -50.13411340000002, -59.41766000000001, -63.85860070000002);
    rr_renderer_fill(renderer);
}