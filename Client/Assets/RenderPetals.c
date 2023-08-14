#include <Client/Assets/RenderFunctions.h>

#include <math.h>

#include <Client/Renderer/Renderer.h>
#include <Shared/StaticData.h>

struct rr_renderer petal_cache;

void rr_renderer_draw_petal(struct rr_renderer *renderer, uint8_t id, uint8_t flags)
{
    if (flags & 1)
        rr_renderer_draw_clipped_image(renderer, &petal_cache, 25 + 50 * id, 25, 50, 50, 0, 0);
    else
    {
        switch (id)
        {
        case rr_petal_id_no_petal:
            break;
        case rr_petal_id_basic:
            rr_renderer_set_stroke(renderer, 0xffcfcfcf);
            rr_renderer_set_fill(renderer, 0xffffffff);
            rr_renderer_set_line_width(renderer, 3.0f);
            rr_renderer_begin_path(renderer);
            rr_renderer_arc(renderer, 0.0f, 0.0f, 10.0f);
            rr_renderer_fill(renderer);
            rr_renderer_stroke(renderer);
            break;
        case rr_petal_id_pellet:
            rr_renderer_set_stroke(renderer, 0xffcfcfcf);
            rr_renderer_set_fill(renderer, 0xffffffff);
            rr_renderer_set_line_width(renderer, 3.0f);
            rr_renderer_begin_path(renderer);
            rr_renderer_arc(renderer, 0.0f, 0.0f, 7.0f);
            rr_renderer_fill(renderer);
            rr_renderer_stroke(renderer);
            break;
        case rr_petal_id_rock:
            rr_renderer_set_stroke(renderer, 0xff606060);
            rr_renderer_set_fill(renderer, 0xff777777);
            rr_renderer_set_line_width(renderer, 3.0f);
            rr_renderer_begin_path(renderer);
            rr_renderer_move_to(renderer, 12.138091087341309f, 0.0f);
            rr_renderer_line_to(renderer, 3.8414306640625f, 12.377452850341797f);
            rr_renderer_line_to(renderer, -11.311542510986328f, 7.916932582855225f);
            rr_renderer_line_to(renderer, -11.461170196533203f,
                                -7.836822032928467f);
            rr_renderer_line_to(renderer, 4.538298606872559f, -13.891617774963379f);
            rr_renderer_line_to(renderer, 12.138091087341309f, 0.0f);
            rr_renderer_fill(renderer);
            rr_renderer_stroke(renderer);
            break;
        case rr_petal_id_stinger:
            rr_renderer_set_fill(renderer, 0xffd4b30c);
            rr_renderer_set_stroke(renderer, 0xffd4b30c);
            rr_renderer_set_line_width(renderer, 3.0f);
            rr_renderer_set_line_join(renderer, 1.0f);
            rr_renderer_set_line_cap(renderer, 1.0f);
            rr_renderer_begin_path(renderer);
            rr_renderer_move_to(renderer, 7.0f, 0.0f);
            rr_renderer_line_to(renderer, -3.5f, 6.062177658081055f);
            rr_renderer_line_to(renderer, -3.5f, -6.062178134918213f);
            rr_renderer_line_to(renderer, 7.0f, 0.0f);
            rr_renderer_fill(renderer);
            rr_renderer_stroke(renderer);
            break;
        case rr_petal_id_light:
            rr_renderer_set_stroke(renderer, 0xffcecfa3);
            rr_renderer_set_fill(renderer, 0xfffeffc9);
            rr_renderer_set_line_width(renderer, 3.0f);
            rr_renderer_begin_path(renderer);
            rr_renderer_arc(renderer, 0.0f, 0.0f, 7.0f);
            rr_renderer_fill(renderer);
            rr_renderer_stroke(renderer);
            break;
        case rr_petal_id_missile:
            rr_renderer_set_fill(renderer, 0xffd4b30c);
            rr_renderer_set_stroke(renderer, 0xffd4b30c);
            rr_renderer_set_line_width(renderer, 5.0f);
            rr_renderer_set_line_join(renderer, 1.0f);
            rr_renderer_set_line_cap(renderer, 1.0f);
            rr_renderer_begin_path(renderer);
            rr_renderer_move_to(renderer, 11.0f, 0.0f);
            rr_renderer_line_to(renderer, -11.0f, -6.0f);
            rr_renderer_line_to(renderer, -11.0f, 6.0f);
            rr_renderer_line_to(renderer, 11.0f, 0.0f);
            rr_renderer_fill(renderer);
            rr_renderer_stroke(renderer);
            break;
        case rr_petal_id_peas:
            rr_renderer_set_stroke(renderer, 0xff709d45);
            rr_renderer_set_fill(renderer, 0xff8ac255);
            rr_renderer_set_line_width(renderer, 3.0f);
            rr_renderer_begin_path(renderer);
            rr_renderer_arc(renderer, 0.0f, 0.0f, 7.0f);
            rr_renderer_fill(renderer);
            rr_renderer_stroke(renderer);
            break;
        case rr_petal_id_leaf:
            rr_renderer_set_stroke(renderer, 0xff2e933c);
            rr_renderer_set_fill(renderer, 0xff39b54a);
            rr_renderer_set_line_width(renderer, 3.0f);
            rr_renderer_set_line_join(renderer, 1.0f);
            rr_renderer_set_line_cap(renderer, 1.0f);
            rr_renderer_begin_path(renderer);
            rr_renderer_move_to(renderer, -20.0f, 0.0f);
            rr_renderer_line_to(renderer, -15.0f, 0.0f);
            rr_renderer_bezier_curve_to(renderer, -10.0f, -12.0f, 5.0f, -12.0f,
                                        15.0f, 0.0f);
            rr_renderer_bezier_curve_to(renderer, 5.0f, 12.0f, -10.0f, 12.0f,
                                        -15.0f, 0.0f);
            rr_renderer_fill(renderer);
            rr_renderer_stroke(renderer);
            rr_renderer_begin_path(renderer);
            rr_renderer_move_to(renderer, -9.0f, 0.0f);
            rr_renderer_quadratic_curve_to(renderer, 0.0f, -1.5f, 7.5f, 0.0f);
            rr_renderer_stroke(renderer);
            break;
        case rr_petal_id_egg:
            rr_renderer_set_stroke(renderer, 0xffb08a48);
            rr_renderer_set_fill(renderer, 0xffddad5a);
            rr_renderer_set_line_width(renderer, 3);
            rr_renderer_begin_path(renderer);
            rr_renderer_arc(renderer, 0, 0, 12);
            rr_renderer_fill(renderer);
            rr_renderer_stroke(renderer);
            break;
        case rr_petal_id_magnet:
            rr_renderer_scale(renderer, 0.5);
            rr_renderer_translate(renderer, -20, 0);
            rr_renderer_set_line_cap(renderer, 1);
            rr_renderer_set_stroke(renderer, 0xff363685);
            rr_renderer_set_line_width(renderer, 28);
            rr_renderer_begin_path(renderer);
            rr_renderer_move_to(renderer, 39.5, 18);
            rr_renderer_quadratic_curve_to(renderer, 0, 30, 0, 0);
            rr_renderer_stroke(renderer);
            rr_renderer_set_stroke(renderer, 0xff4343a4);
            rr_renderer_set_line_width(renderer, 16.8);
            rr_renderer_begin_path(renderer);
            rr_renderer_move_to(renderer, 40, 18);
            rr_renderer_quadratic_curve_to(renderer, 0, 30, 0, 0);
            rr_renderer_stroke(renderer);
            rr_renderer_set_stroke(renderer, 0xff853636);
            rr_renderer_set_line_width(renderer, 28);
            rr_renderer_begin_path(renderer);
            rr_renderer_move_to(renderer, 39.5, -18);
            rr_renderer_quadratic_curve_to(renderer, 0, -30, 0, 0);
            rr_renderer_stroke(renderer);
            rr_renderer_set_stroke(renderer, 0xffa44343);
            rr_renderer_set_line_width(renderer, 16.8);
            rr_renderer_begin_path(renderer);
            rr_renderer_move_to(renderer, 40, -18);
            rr_renderer_quadratic_curve_to(renderer, 0, -30, 0, 0);
            rr_renderer_stroke(renderer);
            rr_renderer_begin_path(renderer);
            rr_renderer_set_stroke(renderer, 0xff363685);
            rr_renderer_set_line_width(renderer, 28);
            rr_renderer_move_to(renderer, 39.5, 18);
            rr_renderer_quadratic_curve_to(renderer, 0, 30, 0, 0);
            rr_renderer_stroke(renderer);
            rr_renderer_set_stroke(renderer, 0xff4343a4);
            rr_renderer_set_line_width(renderer, 16.8);
            rr_renderer_begin_path(renderer);
            rr_renderer_move_to(renderer, 40, 18);
            rr_renderer_quadratic_curve_to(renderer, 0, 30, 0, 0);
            rr_renderer_stroke(renderer);
            rr_renderer_set_line_cap(renderer, 0);
            rr_renderer_set_stroke(renderer, 0xff853636);
            rr_renderer_set_line_width(renderer, 28);
            rr_renderer_begin_path(renderer);
            rr_renderer_move_to(renderer, 39.5, -18);
            rr_renderer_quadratic_curve_to(renderer, 0, -30, 0, 0);
            rr_renderer_stroke(renderer);
            rr_renderer_set_stroke(renderer, 0xffa44343);
            rr_renderer_set_line_width(renderer, 16.8);
            rr_renderer_begin_path(renderer);
            rr_renderer_move_to(renderer, 40, -18);
            rr_renderer_quadratic_curve_to(renderer, 0, -30, 0, 0);
            rr_renderer_stroke(renderer);
            break;
        case rr_petal_id_uranium:
            rr_renderer_set_fill(renderer, 0xff63bf2e);
            rr_renderer_set_stroke(renderer, 0xff509b25);
            rr_renderer_set_line_cap(renderer, 1);
            rr_renderer_set_line_join(renderer, 1);
            rr_renderer_set_line_width(renderer, 3);
            rr_renderer_begin_path(renderer);
            rr_renderer_move_to(renderer, -7, -5);
            rr_renderer_line_to(renderer, -1, -9);
            rr_renderer_line_to(renderer, 7, -6);
            rr_renderer_line_to(renderer, 9, 3);
            rr_renderer_line_to(renderer, 2, 9);
            rr_renderer_line_to(renderer, -5, 6);
            rr_renderer_line_to(renderer, -8, 2);
            rr_renderer_line_to(renderer, -7, -5);
            rr_renderer_fill(renderer);
            rr_renderer_stroke(renderer);
            break;
        case rr_petal_id_feather:
            rr_renderer_scale(renderer, 0.1);
            rr_renderer_set_fill(renderer, 0xffcccccc);
            rr_renderer_begin_path(renderer);
            rr_renderer_move_to(renderer, -42.33436, 139.46956999999998);
            rr_renderer_bezier_curve_to(renderer, -56.511694, 129.02984199999997, -69.45178999999999, 114.43511599999998, -77.900804, 101.65209599999997);
            rr_renderer_bezier_curve_to(renderer, -86.34982199999999, 88.86904499999997, -91.17809799999999, 72.52903399999997, -93.028464, 62.77138899999997);
            rr_renderer_bezier_curve_to(renderer, -94.8788296, 53.01372899999997, -88.675245, 51.02285399999997, -89.002998, 43.106151999999966);
            rr_renderer_bezier_curve_to(renderer, -89.33075154000001, 35.18946499999997, -94.16932, 24.620387999999966, -94.994985, 15.271221999999966);
            rr_renderer_bezier_curve_to(renderer, -95.82065, 5.9220549999999665, -95.50337537, -5.642734000000033, -93.956988, -12.988864000000035);
            rr_renderer_bezier_curve_to(renderer, -92.4106003, -20.334979000000036, -87.609844, -22.660739000000035, -85.71665999999999, -28.805514000000034);
            rr_renderer_bezier_curve_to(renderer, -83.82347719999999, -34.95030460000004, -84.82527205999999, -41.95567600000003, -82.59788939999999, -49.85756200000003);
            rr_renderer_bezier_curve_to(renderer, -80.37050579999999, -57.75944800000003, -75.83459239999999, -69.95770500000003, -72.35235939999998, -76.21682200000004);
            rr_renderer_bezier_curve_to(renderer, -68.87012639999999, -82.47593900000004, -66.51202159999998, -80.84089100000004, -61.70449439999999, -87.41226400000004);
            rr_renderer_bezier_curve_to(renderer, -56.89696879999999, -93.98363700000003, -53.12253939999999, -103.21232000000003, -43.507198399999986, -115.64505600000004);
            rr_renderer_bezier_curve_to(renderer, -33.891857399999985, -128.07778800000003, -14.043853399999985, -155.19720300000003, -4.012443399999988, -162.00865400000004);
            rr_renderer_bezier_curve_to(renderer, 6.018959600000011, -168.82010350000004, 11.782058600000012, -160.87012140000004, 16.681243600000013, -156.51375500000003);
            rr_renderer_bezier_curve_to(renderer, 21.58042120000001, -152.15738900000002, 22.730964600000014, -141.97629600000002, 25.382644600000013, -135.87046000000004);
            rr_renderer_bezier_curve_to(renderer, 28.034332200000012, -129.76462100000003, 29.602027800000013, -125.05570900000004, 32.59133910000001, -119.87873000000003);
            rr_renderer_bezier_curve_to(renderer, 35.58064270000001, -114.70175100000003, 41.08975210000001, -108.94689500000004, 43.318497100000016, -104.80859300000003);
            rr_renderer_bezier_curve_to(renderer, 45.547256900000015, -100.67029100000003, 44.175796900000016, -97.56074830000003, 45.96385230000001, -95.04891500000004);
            rr_renderer_bezier_curve_to(renderer, 47.75190770000001, -92.53708180000004, 49.94271890000002, -94.21045980000004, 54.04682930000001, -89.73759000000004);
            rr_renderer_bezier_curve_to(renderer, 58.15092480000001, -85.26472000000004, 66.64167830000001, -76.69826000000003, 70.58847030000001, -68.21168000000004);
            rr_renderer_bezier_curve_to(renderer, 74.5352629, -59.72510000000004, 76.43934630000001, -44.852603000000045, 77.72759990000002, -38.81811800000004);
            rr_renderer_bezier_curve_to(renderer, 79.01583840000002, -32.78361800000004, 76.94688396000002, -34.44235500000004, 78.31794720000002, -32.00474820000004);
            rr_renderer_bezier_curve_to(renderer, 79.68901040000002, -29.567156600000036, 83.28463720000002, -29.957491700000038, 85.95393350000002, -24.192522900000036);
            rr_renderer_bezier_curve_to(renderer, 88.62324500000003, -18.427553900000035, 93.09286480000002, -6.365068900000036, 94.33378550000002, 2.585034099999966);
            rr_renderer_bezier_curve_to(renderer, 95.57470650000002, 11.535153099999967, 94.76052805000002, 23.085705099999966, 93.39948985000002, 29.508175099999967);
            rr_renderer_bezier_curve_to(renderer, 92.03845165000003, 35.930645099999964, 86.61077835000002, 37.67274109999997, 86.16755625000002, 41.119839099999965);
            rr_renderer_bezier_curve_to(renderer, 85.72433420000002, 44.566936899999966, 91.06254525000001, 44.52938509999996, 90.74015755000002, 50.19074709999997);
            rr_renderer_bezier_curve_to(renderer, 90.41776985000003, 55.85210879999997, 91.87470955000002, 61.185330099999966, 84.23326055000003, 75.08799409999997);
            rr_renderer_bezier_curve_to(renderer, 76.59181155000003, 88.99065809999998, 57.73645055000003, 118.73968209999998, 44.89143355000002, 133.60674709999998);
            rr_renderer_bezier_curve_to(renderer, 32.04643255000002, 148.47384309999998, 21.700835550000022, 163.31332009999997, 7.163207550000024, 164.29046309999998);
            rr_renderer_bezier_curve_to(renderer, -7.374428449999975, 165.26757489999997, -28.157022449999978, 149.90929809999997, -42.334358449999975, 139.4695711);
            rr_renderer_fill(renderer);
            rr_renderer_set_fill(renderer, 0xffe1e1e1);
            rr_renderer_begin_path(renderer);
            rr_renderer_move_to(renderer, -4.135895000000005, 148.08492999999999);
            rr_renderer_bezier_curve_to(renderer, -19.449661500000005, 143.290954, -47.242760000000004, 114.21337999999999, -58.707165, 99.65652399999999);
            rr_renderer_bezier_curve_to(renderer, -70.171572, 85.099639, -75.271952, 65.95800699999998, -72.922329, 60.74372799999999);
            rr_renderer_bezier_curve_to(renderer, -70.57270820000001, 55.52944899999999, -44.845729000000006, 71.38171299999999, -44.609436, 68.37081849999998);
            rr_renderer_bezier_curve_to(renderer, -44.37314602, 65.35990849999999, -66.010559, 55.26766949999998, -71.504581, 42.678328499999985);
            rr_renderer_bezier_curve_to(renderer, -76.99860340000001, 30.088973499999987, -83.542137, -2.639435500000012, -77.57357, -7.1652995000000175);
            rr_renderer_bezier_curve_to(renderer, -71.605005, -11.691163100000018, -36.990673, 18.215742499999983, -35.693184, 15.523116499999983);
            rr_renderer_bezier_curve_to(renderer, -34.395691, 12.830489499999983, -65.95689200000001, -9.609039500000016, -69.78862000000001, -23.321076500000014);
            rr_renderer_bezier_curve_to(renderer, -73.62035, -37.033112500000016, -65.8993015, -61.49939050000002, -58.683557500000006, -66.74907650000002);
            rr_renderer_bezier_curve_to(renderer, -51.467813500000005, -71.99876350000001, -28.775548500000006, -51.91499250000001, -26.494153500000003, -54.81920550000002);
            rr_renderer_bezier_curve_to(renderer, -24.212758500000003, -57.72342610000002, -49.355703500000004, -68.65470850000001, -44.995179500000006, -84.17436950000001);
            rr_renderer_bezier_curve_to(renderer, -40.634656500000006, -99.69402250000002, -10.725827500000008, -142.22229750000002, -0.33102150000000563, -147.93713350000002);
            rr_renderer_bezier_curve_to(renderer, 10.063792499999995, -153.6519715, 12.097483499999994, -128.17625750000002, 17.373675499999994, -118.46339050000002);
            rr_renderer_bezier_curve_to(renderer, 22.649867199999996, -108.75052650000002, 31.747828499999994, -99.73278850000001, 31.326121499999992, -89.65994250000001);
            rr_renderer_bezier_curve_to(renderer, 30.904414349999993, -79.58709750000001, 12.926089499999993, -59.57215150000002, 14.843440499999993, -58.026313500000015);
            rr_renderer_bezier_curve_to(renderer, 16.760791299999994, -56.480483700000015, 34.75024749999999, -84.74945850000002, 42.83023449999999, -80.38494850000001);
            rr_renderer_bezier_curve_to(renderer, 50.91020549999999, -76.0204465, 66.53508449999998, -45.499558500000006, 63.323352499999984, -31.839278500000006);
            rr_renderer_bezier_curve_to(renderer, 60.111606299999984, -18.179015500000006, 21.867198499999986, -0.7460625000000043, 23.559802499999982, 1.5766914999999955);
            rr_renderer_bezier_curve_to(renderer, 25.252406599999983, 3.8994454999999957, 64.31703549999997, -23.191283500000004, 73.47897649999999, -17.902754500000004);
            rr_renderer_bezier_curve_to(renderer, 82.64091849999998, -12.614226100000003, 83.96414449999999, 21.419495499999993, 78.5314665, 33.3078625);
            rr_renderer_bezier_curve_to(renderer, 73.0987885, 45.1962295, 41.02257049999999, 49.7542585, 40.88292249999999, 53.4274305);
            rr_renderer_bezier_curve_to(renderer, 40.743289319999995, 57.1006025, 78.9782285, 42.8480695, 77.69365249999998, 55.3469099);
            rr_renderer_bezier_curve_to(renderer, 76.40907609999998, 67.8457499, 46.81370849999999, 112.9641129, 33.17546249999999, 128.42043990000002);
            rr_renderer_bezier_curve_to(renderer, 19.537202499999985, 143.8767999, 11.177881499999987, 152.87893590000002, -4.135893500000016, 148.08492990000002);
            rr_renderer_fill(renderer);
            rr_renderer_set_fill(renderer, 0xffcccccc);
            rr_renderer_begin_path(renderer);
            rr_renderer_move_to(renderer, 5.317565999999999, 157.962);
            rr_renderer_bezier_curve_to(renderer, 0.5448839999999997, 151.69295699999998, -8.425392, 129.668543, -13.459778, 112.818018);
            rr_renderer_bezier_curve_to(renderer, -18.494156, 95.967524, -22.894905, 76.048304, -24.888733000000002, 56.858912);
            rr_renderer_bezier_curve_to(renderer, -26.8825608, 37.66951999999999, -28.1544114, 19.253778999999994, -25.4227525, -2.318318000000005);
            rr_renderer_bezier_curve_to(renderer, -22.6910935, -23.890416000000005, -11.356445500000001, -72.22319800000001, -8.498787500000002, -72.573688);
            rr_renderer_bezier_curve_to(renderer, -5.641121500000002, -72.92419000000001, -8.771500200000002, -22.612628, -8.276772120000002, -4.421298000000007);
            rr_renderer_bezier_curve_to(renderer, -7.7820440200000025, 13.770016999999992, -7.613419150000002, 19.089046999999994, -5.5304113200000025, 36.57426199999999);
            rr_renderer_bezier_curve_to(renderer, -3.4474035200000026, 54.05947599999999, -0.5173423200000027, 81.49918899999999, 4.221266679999998, 100.49001799999999);
            rr_renderer_bezier_curve_to(renderer, 8.959883679999997, 119.48083199999999, 21.075422679999996, 142.19552299999998, 22.90126668, 150.51922299999998);
            rr_renderer_bezier_curve_to(renderer, 24.72711048, 158.842953, 18.10693968, 149.1918304, 15.17632168, 150.43227842);
            rr_renderer_bezier_curve_to(renderer, 12.245710979999998, 151.67275691999998, 10.09024668, 164.23104542, 5.3175646799999985, 157.96200241999998);
            rr_renderer_fill(renderer);
            break;
        case rr_petal_id_azalea:
            rr_renderer_set_fill(renderer, 0xfff686bd);
            rr_renderer_set_stroke(renderer, 0xffc46b97);
            rr_renderer_set_line_cap(renderer, 1);
            rr_renderer_set_line_join(renderer, 1);
            rr_renderer_set_line_width(renderer, 3);
            rr_renderer_begin_path(renderer);
            rr_renderer_move_to(renderer, -8, 0);
            rr_renderer_quadratic_curve_to(renderer, -12.94427190999916,
                                        -9.40456403667957, -2.4721359549995796,
                                        -7.608452130361228);
            rr_renderer_quadratic_curve_to(renderer, 4.944271909999157,
                                        -15.216904260722458, 6.472135954999579,
                                        -4.702282018339786);
            rr_renderer_quadratic_curve_to(renderer, 16, -1.959434878635765e-15,
                                        6.4721359549995805, 4.702282018339784);
            rr_renderer_quadratic_curve_to(renderer, 4.944271909999161,
                                        15.216904260722456, -2.472135954999578,
                                        7.608452130361229);
            rr_renderer_quadratic_curve_to(renderer, -12.944271909999157,
                                        9.404564036679574, -8,
                                        1.959434878635765e-15);
            rr_renderer_fill(renderer);
            rr_renderer_stroke(renderer);
            break;
        case rr_petal_id_bone:
            rr_renderer_scale(renderer, 0.1);
            rr_renderer_set_fill(renderer, 0xffa19a84);
            rr_renderer_begin_path(renderer);
            rr_renderer_move_to(renderer, -52.30789, 37.23142999999999);
            rr_renderer_bezier_curve_to(renderer, -52.325330796, 60.77389499999999,
                                        -46.342066, 134.50020999999998,
                                        -40.291669999999996, 154.88824499999998);
            rr_renderer_bezier_curve_to(renderer, -34.241277999999994, 175.276276,
                                        -24.568678, 167.81780999999998,
                                        -16.005529999999997, 159.55963169999998);
            rr_renderer_bezier_curve_to(renderer, -7.442373999999997,
                                        151.30145269999997, 0.7581950000000042,
                                        120.55264169999998, 11.087259000000003,
                                        105.33917169999998);
            rr_renderer_bezier_curve_to(renderer, 21.416322, 90.12573169999997,
                                        40.778429, 85.40676769999999, 45.968859,
                                        68.27886869999998);
            rr_renderer_bezier_curve_to(
                renderer, 51.159288700000005, 51.150984699999974, 56.589159,
                11.679381699999972, 42.2298453, 2.57181869999998);
            rr_renderer_bezier_curve_to(renderer, 27.870531300000003,
                                        -6.5357553000000195, -24.430730700000005,
                                        7.85685269999998, -40.1870147,
                                        13.63346419999998);
            rr_renderer_bezier_curve_to(renderer, -55.9433017, 19.41006019999998,
                                        -52.2904467, 13.68896041599998,
                                        -52.307887199999996, 37.23142519999998);
            rr_renderer_fill(renderer);
            rr_renderer_set_fill(renderer, 0xffa19a84);
            rr_renderer_begin_path(renderer);
            rr_renderer_move_to(renderer, -52.679153, -69.82287);
            rr_renderer_bezier_curve_to(renderer, -52.679153, -98.59625399999999,
                                        -29.353713, -121.921694, -0.580328999999999,
                                        -121.921694);
            rr_renderer_bezier_curve_to(renderer, 13.237138000000002, -121.921694,
                                        26.488679, -116.432726, 36.259095,
                                        -106.662302);
            rr_renderer_bezier_curve_to(renderer, 46.0295265, -96.89187799999999,
                                        51.518494000000004, -83.64033699999999,
                                        51.518494000000004, -69.82287199999999);
            rr_renderer_line_to(renderer, 51.518494000000004, 25.051018000000013);
            rr_renderer_bezier_curve_to(renderer, 51.518494000000004,
                                        53.824410000000015, 28.193054000000004,
                                        77.14984800000002, -0.5803299999999965,
                                        77.14984800000002);
            rr_renderer_bezier_curve_to(
                renderer, -29.353713999999997, 77.14984800000002, -52.679154,
                53.82440800000002, -52.679154, 25.05101800000002);
            rr_renderer_fill(renderer);
            rr_renderer_set_fill(renderer, 0xffa19a84);
            rr_renderer_begin_path(renderer);
            rr_renderer_move_to(renderer, -22.684880000000007, -92.49658);
            rr_renderer_bezier_curve_to(
                renderer, -22.684880000000007, -123.85515799999999,
                2.736262999999994, -149.276308, 34.094835999999994, -149.276308);
            rr_renderer_bezier_curve_to(renderer, 49.15376499999999, -149.276308,
                                        63.59590399999999, -143.294176,
                                        74.24417399999999, -132.64591000000001);
            rr_renderer_bezier_curve_to(
                renderer, 84.89242799999998, -121.99764800000001, 90.87455999999999,
                -107.55550200000002, 90.87455999999999, -92.49658000000002);
            rr_renderer_bezier_curve_to(
                renderer, 90.87455999999999, -61.13800600000002, 65.45341699999999,
                -35.71685600000002, 34.09483599999999, -35.71685600000002);
            rr_renderer_bezier_curve_to(renderer, 2.7362619999999858,
                                        -35.71685600000002, -22.684880000000014,
                                        -61.13800600000002, -22.684880000000014,
                                        -92.49658000000002);
            rr_renderer_fill(renderer);
            rr_renderer_set_fill(renderer, 0xffa19a84);
            rr_renderer_begin_path(renderer);
            rr_renderer_move_to(renderer, -90.874807, -105.729);
            rr_renderer_bezier_curve_to(renderer, -90.874807, -140.114143,
                                        -63.000141, -167.988808,
                                        -28.614999000000005, -167.988808);
            rr_renderer_bezier_curve_to(renderer, -12.102678000000004, -167.988808,
                                        3.733350999999999, -161.4293116,
                                        15.409330999999995, -149.753332);
            rr_renderer_bezier_curve_to(renderer, 27.085302999999996, -138.077354,
                                        33.64480499999999, -122.24132900000001,
                                        33.64480499999999, -105.72900200000001);
            rr_renderer_bezier_curve_to(
                renderer, 33.64480499999999, -71.34385900000001, 5.770140999999992,
                -43.46919400000001, -28.61499900000001, -43.46919400000001);
            rr_renderer_bezier_curve_to(
                renderer, -63.00014200000001, -43.46919400000001, -90.874807,
                -71.34385800000001, -90.874807, -105.72900200000001);
            rr_renderer_fill(renderer);
            rr_renderer_set_fill(renderer, 0xffa19a84);
            rr_renderer_begin_path(renderer);
            rr_renderer_move_to(renderer, -68.815947, -58.239875999999995);
            rr_renderer_bezier_curve_to(renderer, -60.59798099999999, -62.0230791,
                                        -50.323882999999995, -57.20976279999999,
                                        -45.868106999999995, -47.48902149999999);
            rr_renderer_bezier_curve_to(renderer, -41.412330999999995,
                                        -37.76828049999999, -44.462188899999994,
                                        -26.821167499999994, -52.680153,
                                        -23.037964499999994);
            rr_renderer_bezier_curve_to(renderer, -51.6542932, -36.453034499999994,
                                        -57.9922143, -50.27986949999999, -68.815947,
                                        -58.239876499999994);
            rr_renderer_fill(renderer);
            rr_renderer_set_fill(renderer, 0xffa19a84);
            rr_renderer_begin_path(renderer);
            rr_renderer_move_to(renderer, 51.524100000000004, -11.064699999999988);
            rr_renderer_bezier_curve_to(
                renderer, 43.60037870000001, -14.448565399999987, 40.499411,
                -24.969728999999987, 44.5978915, -34.56434999999999);
            rr_renderer_bezier_curve_to(renderer, 48.6963565, -44.15898499999999,
                                        58.4422675, -49.19380599999999, 66.3659885,
                                        -45.80993999999999);
            rr_renderer_bezier_curve_to(renderer, 56.0345675, -37.80653699999999,
                                        50.1631535, -24.06138999999999, 51.5241005,
                                        -11.064699999999988);
            rr_renderer_fill(renderer);
            rr_renderer_set_fill(renderer, 0xffccc3a8);
            rr_renderer_begin_path(renderer);
            rr_renderer_move_to(renderer, -73.95985, -105.72996499999999);
            rr_renderer_bezier_curve_to(renderer, -73.95985, -130.77268999999998,
                                        -53.658714, -151.073829,
                                        -28.615990000000004, -151.073829);
            rr_renderer_bezier_curve_to(renderer, -16.590050000000005, -151.073829,
                                        -5.056664000000005, -146.2965425,
                                        3.446959999999997, -137.79291849999998);
            rr_renderer_bezier_curve_to(renderer, 11.950583999999997,
                                        -129.28929649999998, 16.727873999999996,
                                        -117.75590649999998, 16.727873999999996,
                                        -105.72996849999998);
            rr_renderer_bezier_curve_to(renderer, 16.727873999999996,
                                        -80.68724349999998, -3.573266000000004,
                                        -60.38610449999998, -28.615990000000007,
                                        -60.38610449999998);
            rr_renderer_bezier_curve_to(
                renderer, -53.65871500000001, -60.38610449999998, -73.95985,
                -80.68724449999998, -73.95985, -105.72996849999998);
            rr_renderer_fill(renderer);
            rr_renderer_set_fill(renderer, 0xffccc3a8);
            rr_renderer_begin_path(renderer);
            rr_renderer_move_to(renderer, -7.198784000000003, -92.49596);
            rr_renderer_bezier_curve_to(
                renderer, -7.198784000000003, -114.64873499999999,
                10.759581999999998, -132.607105, 32.912352999999996, -132.607105);
            rr_renderer_bezier_curve_to(renderer, 43.550490999999994, -132.607105,
                                        53.752928999999995, -128.3811223, 61.275223,
                                        -120.858825);
            rr_renderer_bezier_curve_to(renderer, 68.797516, -113.3365243,
                                        73.023499, -103.134097, 73.023499,
                                        -92.49596);
            rr_renderer_bezier_curve_to(renderer, 73.023499, -70.343189, 55.06514,
                                        -52.384814999999996, 32.912354,
                                        -52.384814999999996);
            rr_renderer_bezier_curve_to(renderer, 10.759583, -52.384814999999996,
                                        -7.198782999999999, -70.343189,
                                        -7.198782999999999, -92.49596);
            rr_renderer_fill(renderer);
            rr_renderer_set_fill(renderer, 0xffccc3a8);
            rr_renderer_begin_path(renderer);
            rr_renderer_move_to(renderer, -34.906063, -65.727585);
            rr_renderer_bezier_curve_to(renderer, -34.906063, -84.685654,
                                        -19.537514, -100.05419900000001,
                                        -0.5794430000000048, -100.05419900000001);
            rr_renderer_bezier_curve_to(renderer, 8.524537999999994,
                                        -100.05419900000001, 17.255646999999996,
                                        -96.43766000000001, 23.693139999999996,
                                        -90.00016800000002);
            rr_renderer_bezier_curve_to(renderer, 30.130632399999996,
                                        -83.56267560000002, 33.747178999999996,
                                        -74.83156600000001, 33.747178999999996,
                                        -65.72758500000002);
            rr_renderer_line_to(renderer, 33.747178999999996, 27.852404999999976);
            rr_renderer_bezier_curve_to(
                renderer, 33.747178999999996, 46.81047399999997, 18.378625999999997,
                62.179018999999975, -0.5794430000000048, 62.179018999999975);
            rr_renderer_bezier_curve_to(
                renderer, -19.537512000000003, 62.179018999999975, -34.906063,
                46.81047299999997, -34.906063, 27.852404999999976);
            rr_renderer_fill(renderer);
            rr_renderer_set_fill(renderer, 0xffccc3a8);
            rr_renderer_begin_path(renderer);
            rr_renderer_move_to(renderer, -58.027287, -70.988205);
            rr_renderer_bezier_curve_to(renderer, -46.215275000000005,
                                        -76.41079699999999, -31.451584, -69.4762116,
                                        -25.051659, -55.49936699999999);
            rr_renderer_bezier_curve_to(renderer, -18.6517414, -41.522521999999995,
                                        -23.039101000000002, -25.79615799999999,
                                        -34.851113, -20.373566999999994);
            rr_renderer_bezier_curve_to(
                renderer, -33.371605599999995, -39.649964999999995, -42.474896,
                -59.530716999999996, -58.027287, -70.98820699999999);
            rr_renderer_fill(renderer);
            rr_renderer_set_fill(renderer, 0xffccc3a8);
            rr_renderer_begin_path(renderer);
            rr_renderer_move_to(renderer, 33.68027000000001, -7.4407799999999895);
            rr_renderer_bezier_curve_to(renderer, 21.742160000000005,
                                        -12.54811029999999, 17.082179000000007,
                                        -28.41929599999999, 23.271930000000005,
                                        -42.89005999999999);
            rr_renderer_bezier_curve_to(
                renderer, 29.461673000000005, -57.360823999999994, 44.157214,
                -64.95138499999999, 56.095325, -59.84405499999999);
            rr_renderer_bezier_curve_to(renderer, 40.513446, -47.77596999999999,
                                        31.646091000000002, -27.045317999999988,
                                        33.680271000000005, -7.4407799999999895);
            rr_renderer_fill(renderer);
            rr_renderer_set_fill(renderer, 0xffccc3a8);
            rr_renderer_begin_path(renderer);
            rr_renderer_move_to(renderer, -34.85657, 32.84309999999999);
            rr_renderer_bezier_curve_to(renderer, -34.77570223, 55.19631,
                                        -32.894568199999995, 134.49256,
                                        -27.270719999999997, 144.71857);
            rr_renderer_bezier_curve_to(renderer, -21.646872, 154.94455299999998,
                                        -10.654469999999996, 107.64026,
                                        -1.1134859999999982, 94.19907);
            rr_renderer_bezier_curve_to(renderer, 8.427507000000002, 80.757862,
                                        24.320688, 77.137241, 29.97519, 64.071308);
            rr_renderer_bezier_curve_to(renderer, 35.6297005, 51.005375, 34.390763,
                                        25.977131, 32.8135384, 15.803470000000004);
            rr_renderer_bezier_curve_to(renderer, 31.2363289, 5.629794000000004,
                                        30.60682, 3.8966550000000044,
                                        20.511902399999997, 3.0293000000000045);
            rr_renderer_bezier_curve_to(renderer, 10.416992399999996,
                                        2.1619294000000044, -18.527854600000005,
                                        5.630328400000005, -27.7559356,
                                        10.599292000000005);
            rr_renderer_bezier_curve_to(
                renderer, -36.984016600000004, 15.568255600000006, -34.9374426,
                10.489886480000006, -34.856571100000004, 32.843097);
            rr_renderer_fill(renderer);
            rr_renderer_set_fill(renderer, 0xffa19a84);
            rr_renderer_begin_path(renderer);
            rr_renderer_move_to(renderer, 7.4694199999999995, -143.298567);
            rr_renderer_bezier_curve_to(
                renderer, 1.8085769999999997, -142.26893629999998,
                -5.008752000000001, -135.42306539999998, -8.745653, -128.123692);
            rr_renderer_bezier_curve_to(
                renderer, -12.482553300000001, -120.82431460000001, -14.328806,
                -108.014206, -14.951974700000001, -99.50232);
            rr_renderer_bezier_curve_to(renderer, -15.575143650000001, -90.990433,
                                        -15.906549300000002, -73.735161,
                                        -12.484666700000002, -77.05238399999999);
            rr_renderer_bezier_curve_to(renderer, -9.062791700000002,
                                        -80.36960659999998, -0.704713700000001,
                                        -109.86415399999998, 5.579305299999998,
                                        -119.405667);
            rr_renderer_bezier_curve_to(renderer, 11.863317299999999, -128.947182,
                                        24.904409299999998, -130.31931749999998,
                                        25.2194263, -134.301469);
            rr_renderer_bezier_curve_to(renderer, 25.53445163, -138.28361619999998,
                                        13.130269299999998, -144.328197,
                                        7.469418299999997, -143.298568);
            rr_renderer_fill(renderer);
            rr_renderer_set_fill(renderer, 0xffa19a84);
            rr_renderer_begin_path(renderer);
            rr_renderer_move_to(renderer, -1.8945099999999968, 81.83704);
            rr_renderer_bezier_curve_to(renderer, -1.1677491399999969, 64.905232,
                                        -2.9336563999999967, 2.2511300000000034,
                                        -1.272927969999997, 3.2892200000000003);
            rr_renderer_bezier_curve_to(renderer, 0.38780053000000314,
                                        4.327305900000001, 8.796614030000004,
                                        71.13375, 8.069845030000003, 88.06556);
            rr_renderer_bezier_curve_to(renderer, 7.343084170000004, 104.997353,
                                        -3.9727959699999964, 105.91810000000001,
                                        -5.633523969999997, 104.880013);
            rr_renderer_bezier_curve_to(renderer, -7.294252469999997, 103.8419271,
                                        -2.621278769999997, 98.7688375,
                                        -1.894510269999997, 81.837044);
            rr_renderer_fill(renderer);
            break;
        case rr_petal_id_web:
            rr_renderer_set_fill(renderer, 0xffffffff);
            rr_renderer_set_stroke(renderer, 0xffcfcfcf);
            rr_renderer_set_line_cap(renderer, 1);
            rr_renderer_set_line_join(renderer, 1);
            rr_renderer_set_line_width(renderer, 3);
            rr_renderer_begin_path(renderer);
            rr_renderer_move_to(renderer, 11, 0);
            rr_renderer_quadratic_curve_to(renderer, 4.319756031036377,
                                        3.138486623764038, 3.399186611175537,
                                        10.46162223815918);
            rr_renderer_quadratic_curve_to(renderer, -1.6500004529953003,
                                        5.0781779289245605, -8.899188041687012,
                                        6.46563720703125);
            rr_renderer_quadratic_curve_to(renderer, -5.339512348175049,
                                        -5.722046125811175e-7,
                                        -8.899186134338379, -6.465639114379883);
            rr_renderer_quadratic_curve_to(renderer, -1.6499993801116943,
                                        -5.078178405761719, 3.399188280105591,
                                        -10.461621284484863);
            rr_renderer_quadratic_curve_to(renderer, 4.319756507873535,
                                        -3.138485908508301, 11,
                                        0.000001923301169881597);
            rr_renderer_fill(renderer);
            rr_renderer_stroke(renderer);
            break;
        case rr_petal_id_seed:
            rr_renderer_scale(renderer, 0.1);
            rr_renderer_set_fill(renderer, 0xffb07200);
            rr_renderer_begin_path(renderer);
            rr_renderer_move_to(renderer, 80.90206999999998, -82.33018000000001);
            rr_renderer_bezier_curve_to(renderer, 125.71978999999999,
                                        -37.51246000000001, 125.71978999999999,
                                        35.15142999999999, 80.90206999999998,
                                        79.96911999999998);
            rr_renderer_bezier_curve_to(
                renderer, 59.37985299999998, 101.49136699999997, 30.189453999999984,
                113.58242999999997, -0.2475700000000245, 113.58242999999997);
            rr_renderer_bezier_curve_to(renderer, -30.684597000000025,
                                        113.58242999999997, -59.874996000000024,
                                        101.49136599999997, -81.39723000000002,
                                        79.96911999999998);
            rr_renderer_bezier_curve_to(renderer, -126.21495000000002,
                                        35.15143199999998, -126.21495000000002,
                                        -37.51246000000002, -81.39723000000002,
                                        -82.33018000000001);
            rr_renderer_bezier_curve_to(renderer, -36.57951000000002,
                                        -127.14790000000002, 36.08437999999998,
                                        -127.14790000000002, 80.90206999999997,
                                        -82.33018000000001);
            rr_renderer_fill(renderer);
            rr_renderer_set_fill(renderer, 0xffb07200);
            rr_renderer_begin_path(renderer);
            rr_renderer_move_to(renderer, 95.57850000000002, 39.56533999999999);
            rr_renderer_bezier_curve_to(renderer, 110.78849100000002,
                                        54.775330999999994, 110.78849100000002,
                                        79.43557999999999, 95.57850000000002,
                                        94.64553999999998);
            rr_renderer_bezier_curve_to(
                renderer, 88.27442300000001, 101.94964769999999, 78.36796000000001,
                106.05304099999998, 68.03840000000002, 106.05304099999998);
            rr_renderer_bezier_curve_to(
                renderer, 57.70887100000002, 106.05304099999998, 47.80240800000003,
                101.94964739999998, 40.49830000000003, 94.64553999999998);
            rr_renderer_bezier_curve_to(
                renderer, 25.28833900000003, 79.43557899999999, 25.28833900000003,
                54.77532999999998, 40.49830000000003, 39.565339999999985);
            rr_renderer_bezier_curve_to(
                renderer, 55.70829100000003, 24.355378999999985, 80.36854000000002,
                24.355378999999985, 95.57850000000002, 39.565339999999985);
            rr_renderer_fill(renderer);
            rr_renderer_set_fill(renderer, 0xffc98200);
            rr_renderer_begin_path(renderer);
            rr_renderer_move_to(renderer, -0.24810999999999694, -82.33045999999999);
            rr_renderer_bezier_curve_to(
                renderer, 44.569610000000004, -82.33045999999999, 80.90155,
                -45.998519999999985, 80.90155, -1.1807999999999907);
            rr_renderer_quadratic_curve_to(renderer, 80.90155, 34.63580500000001,
                                        71.385132, 70.45242400000001);
            rr_renderer_quadratic_curve_to(renderer, 35.568512, 79.96884200000001,
                                        -0.248108000000002, 79.96884200000001);
            rr_renderer_bezier_curve_to(renderer, -45.065828, 79.96884200000001,
                                        -81.397768, 43.636902000000006, -81.397768,
                                        -1.1807979999999958);
            rr_renderer_bezier_curve_to(renderer, -81.397768, -45.998518,
                                        -45.065827999999996, -82.330458,
                                        -0.248108000000002, -82.330458);
            rr_renderer_fill(renderer);
            rr_renderer_set_fill(renderer, 0xffb07200);
            rr_renderer_begin_path(renderer);
            rr_renderer_move_to(renderer, -74.22667999999999, -77.81169);
            rr_renderer_bezier_curve_to(renderer, -15.663126999999989, -81.5095202,
                                        35.641390000000015, -38.93869,
                                        42.810490000000016, 19.301910000000007);
            rr_renderer_line_to(renderer, 6.678913000000016, 23.749481000000007);
            rr_renderer_bezier_curve_to(renderer, 1.8635900000000154,
                                        -15.369552999999993, -32.59664699999998,
                                        -43.963528999999994, -71.93259699999999,
                                        -41.47976899999999);
            rr_renderer_fill(renderer);
            rr_renderer_set_fill(renderer, 0xffb07200);
            rr_renderer_begin_path(renderer);
            rr_renderer_move_to(renderer, 37.648829999999975, 9.861109999999996);
            rr_renderer_bezier_curve_to(renderer, 44.736689999999975,
                                        16.948969999999996, 44.736689999999975,
                                        28.440669999999997, 37.648829999999975,
                                        35.528529999999996);
            rr_renderer_bezier_curve_to(renderer, 34.245112999999975, 38.932247,
                                        29.628687999999975, 40.8444175,
                                        24.815119999999975, 40.8444175);
            rr_renderer_bezier_curve_to(renderer, 20.001551999999975, 40.8444175,
                                        15.385111999999975, 38.9322471,
                                        11.981409999999975, 35.528529999999996);
            rr_renderer_bezier_curve_to(
                renderer, 4.893549999999975, 28.440669999999997, 4.893549999999975,
                16.948969999999996, 11.981409999999975, 9.861109999999996);
            rr_renderer_bezier_curve_to(renderer, 19.069269999999975,
                                        2.7732499999999964, 30.560969999999976,
                                        2.7732499999999964, 37.648829999999975,
                                        9.861109999999996);
            rr_renderer_fill(renderer);
            break;
        case rr_petal_id_gravel:
            rr_renderer_set_stroke(renderer, 0xff606060);
            rr_renderer_set_fill(renderer, 0xff777777);
            rr_renderer_set_line_width(renderer, 3.0f);
            rr_renderer_begin_path(renderer);
            rr_renderer_arc(renderer, 0.0f, 0.0f, 7.0f);
            rr_renderer_fill(renderer);
            rr_renderer_stroke(renderer);
            break;
        case rr_petal_id_club:
            rr_renderer_scale(renderer, 0.2);
            rr_renderer_set_fill(renderer, 0xff7d6c64);
            rr_renderer_begin_path(renderer);
            rr_renderer_move_to(renderer, 72.00243, 2.3752000000000066);
            rr_renderer_bezier_curve_to(renderer, 72.00243, 31.365251000000008, 48.943821, 54.86633500000001, 20.499590000000005, 54.86633500000001);
            rr_renderer_bezier_curve_to(renderer, 6.840189000000004, 54.86633500000001, -6.2597639999999934, 49.336031000000006, -15.918416999999998, 39.49203700000001);
            rr_renderer_bezier_curve_to(renderer, -25.57707, 29.64804300000001, -31.003248, 16.29671700000001, -31.003248, 2.3752000000000137);
            rr_renderer_bezier_curve_to(renderer, -31.003248, -26.614850999999987, -7.944647, -50.115934999999986, 20.499592, -50.115934999999986);
            rr_renderer_bezier_curve_to(renderer, 48.943822, -50.115934999999986, 72.002432, -26.614853999999987, 72.002432, 2.3752000000000137);
            rr_renderer_fill(renderer);
            rr_renderer_set_fill(renderer, 0xff7d6c64);
            rr_renderer_begin_path(renderer);
            rr_renderer_move_to(renderer, 33.82495, 36.99807);
            rr_renderer_bezier_curve_to(renderer, 33.82495, 56.04033, 18.681052, 71.477127, 0.00011299999999891952, 71.477127);
            rr_renderer_bezier_curve_to(renderer, -8.970792000000001, 71.477127, -17.574270000000002, 67.84452809999999, -23.917657000000002, 61.37844799999999);
            rr_renderer_bezier_curve_to(renderer, -30.2610446, 54.91236829999999, -33.82472, 46.14248599999999, -33.82472, 36.99806899999999);
            rr_renderer_bezier_curve_to(renderer, -33.82472, 17.955808999999988, -18.680826, 2.5190119999999894, 0.00011299999999891952, 2.5190119999999894);
            rr_renderer_bezier_curve_to(renderer, 18.681051999999998, 2.5190119999999894, 33.82495, 17.95580999999999, 33.82495, 36.99806899999999);
            rr_renderer_fill(renderer);
            rr_renderer_set_fill(renderer, 0xff7d6c64);
            rr_renderer_begin_path(renderer);
            rr_renderer_move_to(renderer, 31.003929999999997, 2.3752000000000066);
            rr_renderer_bezier_curve_to(renderer, 31.003929999999997, 31.365251000000008, 7.945320999999996, 54.86633500000001, -20.498910000000002, 54.86633500000001);
            rr_renderer_bezier_curve_to(renderer, -34.158311000000005, 54.86633500000001, -47.258258, 49.336031000000006, -56.916913, 39.49203700000001);
            rr_renderer_bezier_curve_to(renderer, -66.575568, 29.64804300000001, -72.001743, 16.29671700000001, -72.001743, 2.3752000000000137);
            rr_renderer_bezier_curve_to(renderer, -72.001743, -26.614850999999987, -48.94314, -50.115934999999986, -20.498909000000005, -50.115934999999986);
            rr_renderer_bezier_curve_to(renderer, 7.945320999999996, -50.115934999999986, 31.003930999999994, -26.614853999999987, 31.003930999999994, 2.3752000000000137);
            rr_renderer_fill(renderer);
            rr_renderer_set_fill(renderer, 0xff917d73);
            rr_renderer_begin_path(renderer);
            rr_renderer_move_to(renderer, 58.375460000000004, 3.8080599999999976);
            rr_renderer_bezier_curve_to(renderer, 58.375460000000004, 25.125854999999998, 41.418040000000005, 42.40735, 20.500002000000002, 42.40735);
            rr_renderer_bezier_curve_to(renderer, 10.454805000000002, 42.40735, 0.8210320000000024, 38.340646, -6.2819959999999995, 31.101877);
            rr_renderer_bezier_curve_to(renderer, -13.3850233, 23.8631075, -17.375464, 14.045229000000003, -17.375464, 3.808061000000002);
            rr_renderer_bezier_curve_to(renderer, -17.375464, -17.509738, -0.41803600000000074, -34.791229, 20.500000999999997, -34.791229);
            rr_renderer_bezier_curve_to(renderer, 41.418037999999996, -34.791229, 58.375459, -17.509739, 58.375459, 3.808061000000002);
            rr_renderer_fill(renderer);
            rr_renderer_set_fill(renderer, 0xff917d73);
            rr_renderer_begin_path(renderer);
            rr_renderer_move_to(renderer, 17.377350000000007, 3.8080599999999976);
            rr_renderer_bezier_curve_to(renderer, 17.377350000000007, 25.125854999999998, 0.4199300000000079, 42.40735, -20.49810999999999, 42.40735);
            rr_renderer_bezier_curve_to(renderer, -30.54330999999999, 42.40735, -40.17707999999999, 38.340646, -47.28010799999999, 31.101877);
            rr_renderer_bezier_curve_to(renderer, -54.38313529999999, 23.8631075, -58.37357499999999, 14.045229000000003, -58.37357499999999, 3.808061000000002);
            rr_renderer_bezier_curve_to(renderer, -58.37357499999999, -17.509738, -41.416150999999985, -34.791229, -20.49810999999999, -34.791229);
            rr_renderer_bezier_curve_to(renderer, 0.41993100000000894, -34.791229, 17.377350000000007, -17.509739, 17.377350000000007, 3.808061000000002);
            rr_renderer_fill(renderer);
            rr_renderer_set_fill(renderer, 0xff917d73);
            rr_renderer_begin_path(renderer);
            rr_renderer_move_to(renderer, 20.880035000000007, 36.998245);
            rr_renderer_bezier_curve_to(renderer, 20.880035000000007, 48.752632, 11.531951500000007, 58.281448, 0.0005110000000065895, 58.281448);
            rr_renderer_bezier_curve_to(renderer, -5.5370866999999935, 58.281448, -10.847873999999994, 56.039108, -14.763545999999993, 52.047736799999996);
            rr_renderer_bezier_curve_to(renderer, -18.679214499999993, 48.05636559999999, -20.879016999999994, 42.64289779999999, -20.879016999999994, 36.998244799999995);
            rr_renderer_bezier_curve_to(renderer, -20.879016999999994, 25.243857799999994, -11.530933499999994, 15.715049799999996, 0.0005110000000065895, 15.715049799999996);
            rr_renderer_bezier_curve_to(renderer, 11.531952000000006, 15.715049799999996, 20.880035000000007, 25.243858799999998, 20.880035000000007, 36.998244799999995);
            rr_renderer_fill(renderer);
            rr_renderer_set_fill(renderer, 0xff6a5045);
            rr_renderer_begin_path(renderer);
            rr_renderer_move_to(renderer, -22.819927, -44.688831);
            rr_renderer_line_to(renderer, -13.858169, 4.247239);
            rr_renderer_line_to(renderer, 1.648987, 4.764901050000001);
            rr_renderer_line_to(renderer, -5.5878065, -38.657588950000005);
            rr_renderer_fill(renderer);
            rr_renderer_set_fill(renderer, 0xff6a5045);
            rr_renderer_begin_path(renderer);
            rr_renderer_move_to(renderer, 22.844179999999994, -44.688831);
            rr_renderer_line_to(renderer, 13.882418999999995, 4.247239);
            rr_renderer_line_to(renderer, -1.624737000000005, 4.764901050000001);
            rr_renderer_line_to(renderer, 5.612056499999995, -38.657588950000005);
            rr_renderer_fill(renderer);
            rr_renderer_set_fill(renderer, 0xff6a5045);
            rr_renderer_begin_path(renderer);
            rr_renderer_move_to(renderer, -14.096783000000002, 1.735510000000005);
            rr_renderer_bezier_curve_to(renderer, -14.096783000000002, -6.079721299999995, -7.779732000000002, -12.415227999999995, 0.012740999999998337, -12.415227999999995);
            rr_renderer_bezier_curve_to(renderer, 3.754821699999998, -12.415227999999995, 7.343635499999999, -10.924348999999996, 9.989684999999998, -8.270570999999997);
            rr_renderer_bezier_curve_to(renderer, 12.635734499999998, -5.616792999999997, 14.122268599999998, -2.017496399999997, 14.122268599999998, 1.7355100000000032);
            rr_renderer_bezier_curve_to(renderer, 14.122268599999998, 9.550749000000003, 7.805213899999998, 15.886252000000002, 0.012740599999998992, 15.886252000000002);
            rr_renderer_bezier_curve_to(renderer, -7.779732400000001, 15.886252000000002, -14.096783400000001, 9.550749400000003, -14.096783400000001, 1.7355100000000032);
            rr_renderer_fill(renderer);
            rr_renderer_set_fill(renderer, 0xff6a5045);
            rr_renderer_begin_path(renderer);
            rr_renderer_move_to(renderer, -23.09894, -48.305275);
            rr_renderer_bezier_curve_to(renderer, -23.09894, -61.103043, -12.750951999999998, -71.47768500000001, 0.013933000000001527, -71.47768500000001);
            rr_renderer_bezier_curve_to(renderer, 6.143854000000002, -71.47768500000001, 12.022699000000001, -69.036313, 16.357210000000002, -64.6906433);
            rr_renderer_bezier_curve_to(renderer, 20.691713, -60.34497400000001, 23.126810000000003, -54.45098130000001, 23.126810000000003, -48.3052773);
            rr_renderer_bezier_curve_to(renderer, 23.126810000000003, -35.5075093, 12.778826000000002, -25.1328673, 0.013933000000001527, -25.1328673);
            rr_renderer_bezier_curve_to(renderer, -12.750951999999998, -25.1328673, -23.09894, -35.5075083, -23.09894, -48.3052773);
            rr_renderer_fill(renderer);
            rr_renderer_set_fill(renderer, 0xff856456);
            rr_renderer_begin_path(renderer);
            rr_renderer_move_to(renderer, 9.730130000000003, -47.690360999999996);
            rr_renderer_line_to(renderer, 0.012372000000002714, 2.0066690000000023);
            rr_renderer_line_to(renderer, -9.705385999999997, -47.690360999999996);
            rr_renderer_fill(renderer);
            rr_renderer_set_fill(renderer, 0xff856456);
            rr_renderer_begin_path(renderer);
            rr_renderer_move_to(renderer, -9.706184, -48.30256);
            rr_renderer_bezier_curve_to(renderer, -9.706184, -53.682176, -5.3553997, -58.043215000000004, 0.011573999999999529, -58.043215000000004);
            rr_renderer_bezier_curve_to(renderer, 2.5888826999999996, -58.043215000000004, 5.060631, -57.01696990000001, 6.8830645, -55.19024400000001);
            rr_renderer_bezier_curve_to(renderer, 8.705498, -53.36351520000001, 9.7293322, -50.88594200000001, 9.7293322, -48.30256000000001);
            rr_renderer_bezier_curve_to(renderer, 9.7293322, -42.92294400000001, 5.3785402, -38.561904000000006, 0.01157420000000009, -38.561904000000006);
            rr_renderer_bezier_curve_to(renderer, -5.3553998, -38.561904000000006, -9.7061838, -42.92294400000001, -9.7061838, -48.30256000000001);
            rr_renderer_fill(renderer);
            break;
        case rr_petal_id_crest:
            rr_renderer_scale(renderer, 0.25);
            rr_renderer_set_fill(renderer, 0xff46555e);
            rr_renderer_begin_path(renderer);
            rr_renderer_move_to(renderer, -71.1893077, -49.993254);
            rr_renderer_bezier_curve_to(renderer, -61.6957827, -54.4760097, -41.040849699999995, -34.082108, -25.0552207, -4.442197999999998);
            rr_renderer_bezier_curve_to(renderer, -9.0695947, 25.19771, -3.806708699999998, 52.859592, -13.3002307, 57.342348);
            rr_renderer_bezier_curve_to(renderer, -12.0682551, 44.2819995, -19.1231717, 21.450243, -31.4572967, -1.419195000000002);
            rr_renderer_bezier_curve_to(renderer, -43.7914222, -24.288637, -59.2292657, -43.162055, -71.1893067, -49.993255000000005);
            rr_renderer_fill(renderer);
            rr_renderer_set_fill(renderer, 0xff46555e);
            rr_renderer_begin_path(renderer);
            rr_renderer_move_to(renderer, -71.01766384, -45.89501);
            rr_renderer_bezier_curve_to(renderer, -72.01029694, -47.7356682, -71.73571144, -49.7382908, -70.40435993999999, -50.3679905);
            rr_renderer_bezier_curve_to(renderer, -69.76502228, -50.67038346, -68.96251034, -50.60925484, -68.17336714, -50.19805527);
            rr_renderer_bezier_curve_to(renderer, -67.38422428999999, -49.78685761, -66.67309274, -49.05926897, -66.19641344, -48.175352069999995);
            rr_renderer_bezier_curve_to(renderer, -65.2037801, -46.334691969999994, -65.47836584, -44.33207126999999, -66.8097171, -43.70237157);
            rr_renderer_bezier_curve_to(renderer, -68.1410689, -43.07267186999999, -70.0250305, -44.054349869999996, -71.0176641, -45.89500997);
            rr_renderer_fill(renderer);
            rr_renderer_set_fill(renderer, 0xff46555e);
            rr_renderer_begin_path(renderer);
            rr_renderer_move_to(renderer, -16.729504, 54.779210000000006);
            rr_renderer_bezier_curve_to(renderer, -17.7221378, 52.938549900000005, -17.4475521, 50.935933000000006, -16.11619986, 50.3062333);
            rr_renderer_bezier_curve_to(renderer, -15.476864229999999, 50.00383462, -14.674351059999998, 50.06496133, -13.885208459999998, 50.476162800000004);
            rr_renderer_bezier_curve_to(renderer, -13.096065859999998, 50.88736428000001, -12.384933759999997, 51.614949100000004, -11.908253059999998, 52.498867800000006);
            rr_renderer_bezier_curve_to(renderer, -10.915623059999998, 54.33952790000001, -11.190208759999997, 56.34214480000001, -12.521557199999998, 56.9718445);
            rr_renderer_bezier_curve_to(renderer, -13.852909399999998, 57.601544200000006, -15.736870199999998, 56.619870000000006, -16.729504199999997, 54.779209900000005);
            rr_renderer_fill(renderer);
            rr_renderer_set_fill(renderer, 0xff46555e);
            rr_renderer_begin_path(renderer);
            rr_renderer_move_to(renderer, -70.7721734, -45.605413);
            rr_renderer_bezier_curve_to(renderer, -60.3565834, -50.519712, -39.892334399999996, -32.210536499999996, -25.0639934, -4.7107230000000015);
            rr_renderer_bezier_curve_to(renderer, -10.235651400000002, 22.789087, -6.658414400000002, 49.065911, -17.074003400000002, 53.98021);
            rr_renderer_bezier_curve_to(renderer, -31.550531400000004, 19.820656, -50.0092754, -14.411900000000003, -70.7721734, -45.605414999999994);
            rr_renderer_fill(renderer);
            rr_renderer_set_fill(renderer, 0xff46555e);
            rr_renderer_begin_path(renderer);
            rr_renderer_move_to(renderer, -69.8517892, -47.54002);
            rr_renderer_bezier_curve_to(renderer, -60.461762199999995, -51.978740699999996, -40.5543112, -32.77713, -25.3872542, -4.652023);
            rr_renderer_bezier_curve_to(renderer, -10.220197200000001, 23.473084, -5.5369882, 49.871277, -14.927015200000001, 54.309997);
            rr_renderer_bezier_curve_to(renderer, -16.6607798, 39.33846200000001, -23.802114200000002, 19.296020000000006, -34.4152282, -0.3844530000000006);
            rr_renderer_bezier_curve_to(renderer, -45.0283382, -20.064923, -58.0138482, -37.344793, -69.8517882, -47.54002);
            rr_renderer_fill(renderer);
            rr_renderer_set_fill(renderer, 0xff46555e);
            rr_renderer_begin_path(renderer);
            rr_renderer_move_to(renderer, 71.19191000000001, -49.993612);
            rr_renderer_bezier_curve_to(renderer, 61.69838000000001, -54.4763677, 41.04345000000001, -34.082466, 25.057823000000006, -4.442555999999996);
            rr_renderer_bezier_curve_to(renderer, 9.072189000000007, 25.197352000000002, 3.809303000000007, 52.859234, 13.302826000000007, 57.341984000000004);
            rr_renderer_bezier_curve_to(renderer, 12.070854300000008, 44.281643, 19.125770600000006, 21.449887000000004, 31.459892000000007, -1.419551999999996);
            rr_renderer_bezier_curve_to(renderer, 43.79402100000001, -24.288993999999995, 59.23187200000001, -43.162411999999996, 71.19191000000001, -49.993612);
            rr_renderer_fill(renderer);
            rr_renderer_set_fill(renderer, 0xff46555e);
            rr_renderer_begin_path(renderer);
            rr_renderer_move_to(renderer, 71.02026000000001, -45.895369);
            rr_renderer_bezier_curve_to(renderer, 72.01289000000001, -47.7360291, 71.73830810000001, -49.738649800000005, 70.40694823000001, -50.3683495);
            rr_renderer_bezier_curve_to(renderer, 69.76762023, -50.67074246, 68.96509943000001, -50.60961575, 68.17596073000001, -50.19841618);
            rr_renderer_bezier_curve_to(renderer, 67.38682193000001, -49.78721661, 66.67568603000001, -49.05962798, 66.19900153000002, -48.17571298);
            rr_renderer_bezier_curve_to(renderer, 65.20637153000001, -46.33505288, 65.48095343000001, -44.33243028, 66.81231330000001, -43.70273058);
            rr_renderer_bezier_curve_to(renderer, 68.14365790000001, -43.07303088, 70.02763010000001, -44.05470888, 71.02026030000002, -45.89536898);
            rr_renderer_fill(renderer);
            rr_renderer_set_fill(renderer, 0xff46555e);
            rr_renderer_begin_path(renderer);
            rr_renderer_move_to(renderer, 16.732100000000003, 54.778853999999995);
            rr_renderer_bezier_curve_to(renderer, 17.724737630000003, 52.938193899999995, 17.450148100000003, 50.9355694, 16.118795860000002, 50.30587729999999);
            rr_renderer_bezier_curve_to(renderer, 15.479460230000003, 50.00347861999999, 14.676947060000002, 50.06460532999999, 13.887800660000002, 50.475806799999994);
            rr_renderer_bezier_curve_to(renderer, 13.098661860000002, 50.887008279999996, 12.387525960000001, 51.61459309999999, 11.910849060000002, 52.498511799999996);
            rr_renderer_bezier_curve_to(renderer, 10.918219060000002, 54.3391719, 11.192800960000001, 56.34179639999999, 12.524153200000002, 56.971496099999996);
            rr_renderer_bezier_curve_to(renderer, 13.855505400000002, 57.6011958, 15.739470000000003, 56.6195216, 16.7321002, 54.778853899999994);
            rr_renderer_fill(renderer);
            rr_renderer_set_fill(renderer, 0xff46555e);
            rr_renderer_begin_path(renderer);
            rr_renderer_move_to(renderer, 70.77476999999999, -45.605774);
            rr_renderer_bezier_curve_to(renderer, 60.35918199999999, -50.520070999999994, 39.894932999999995, -32.210896, 25.066593999999988, -4.711084);
            rr_renderer_bezier_curve_to(renderer, 10.238254999999988, 22.788726, 6.661014999999988, 49.06555, 17.076611399999987, 53.979849);
            rr_renderer_bezier_curve_to(renderer, 31.553135399999988, 19.820295, 50.01188339999999, -14.412261, 70.77477139999999, -45.60577599999999);
            rr_renderer_fill(renderer);
            rr_renderer_set_fill(renderer, 0xff46555e);
            rr_renderer_begin_path(renderer);
            rr_renderer_move_to(renderer, 69.85439, -47.540379);
            rr_renderer_bezier_curve_to(renderer, 60.46436, -51.9790997, 40.556912, -32.777489, 25.38985999999999, -4.652382000000003);
            rr_renderer_bezier_curve_to(renderer, 10.222798999999991, 23.472724999999997, 5.53958699999999, 49.870917999999996, 14.929616999999991, 54.309638);
            rr_renderer_bezier_curve_to(renderer, 16.66338159999999, 39.338103000000004, 23.804715999999992, 19.295661000000003, 34.41782999999999, -0.3848120000000037);
            rr_renderer_bezier_curve_to(renderer, 45.03093599999999, -20.065285000000003, 58.016454999999986, -37.345152000000006, 69.85439, -47.540379);
            rr_renderer_fill(renderer);
            break;
        case rr_petal_id_droplet:
            rr_renderer_scale(renderer, 0.2);
            rr_renderer_set_fill(renderer, 0xff308eb0);
            rr_renderer_begin_path(renderer);
            rr_renderer_move_to(renderer, -63.561600999999996, 6.623819999999995);
            rr_renderer_bezier_curve_to(renderer, -63.561600999999996, -29.241590000000002, -34.461594999999996, -58.31625000000001, 1.435089000000005, -58.31625000000001);
            rr_renderer_bezier_curve_to(renderer, 18.673279000000004, -58.31625000000001, 35.20544400000001, -51.47437000000001, 47.394684000000005, -39.29574200000001);
            rr_renderer_bezier_curve_to(renderer, 59.583923500000004, -27.11711900000001, 66.43177800000001, -10.599358000000013, 66.43177800000001, 6.623820999999985);
            rr_renderer_bezier_curve_to(renderer, 66.43177800000001, 42.48923099999998, 37.33176400000001, 71.56389099999998, 1.4350880000000075, 71.56389099999998);
            rr_renderer_bezier_curve_to(renderer, -34.461594999999996, 71.56389099999998, -63.56160199999999, 42.489229999999985, -63.56160199999999, 6.623820999999978);
            rr_renderer_fill(renderer);
            rr_renderer_set_fill(renderer, 0xff308eb0);
            rr_renderer_begin_path(renderer);
            rr_renderer_move_to(renderer, -21.966763, -48.361326);
            rr_renderer_bezier_curve_to(renderer, -21.966763, -61.275374, -11.489407, -71.74428, 1.435065999999999, -71.74428);
            rr_renderer_bezier_curve_to(renderer, 7.641616599999999, -71.74428, 13.593962999999999, -69.28072590000001, 17.982658, -64.89557140000001);
            rr_renderer_bezier_curve_to(renderer, 22.371353, -60.510417200000006, 24.836891, -54.56287040000001, 24.836891, -48.36132640000001);
            rr_renderer_bezier_curve_to(renderer, 24.836891, -35.44727740000001, 14.359535000000001, -24.97837040000001, 1.4350660000000026, -24.97837040000001);
            rr_renderer_bezier_curve_to(renderer, -11.489406999999998, -24.97837040000001, -21.966762999999997, -35.44727640000001, -21.966762999999997, -48.36132640000001);
            rr_renderer_fill(renderer);
            rr_renderer_set_fill(renderer, 0xff308eb0);
            rr_renderer_begin_path(renderer);
            rr_renderer_move_to(renderer, -39.788616, -43.445704);
            rr_renderer_line_to(renderer, -12.945712999999998, -66.932457);
            rr_renderer_line_to(renderer, -14.861266999999998, -50.154857);
            rr_renderer_fill(renderer);
            rr_renderer_set_fill(renderer, 0xff308eb0);
            rr_renderer_begin_path(renderer);
            rr_renderer_move_to(renderer, 42.658789999999996, -43.445704);
            rr_renderer_line_to(renderer, 15.815886999999996, -66.932457);
            rr_renderer_line_to(renderer, 17.731437199999995, -50.154857);
            rr_renderer_fill(renderer);
            rr_renderer_set_fill(renderer, 0xff43a6c9);
            rr_renderer_begin_path(renderer);
            rr_renderer_move_to(renderer, -31.062187, 39.121219999999994);
            rr_renderer_bezier_curve_to(renderer, -49.010528, 21.172878999999995, -49.010528, -7.927127000000006, -31.062187, -25.875470000000007);
            rr_renderer_quadratic_curve_to(renderer, -16.503582, -40.43407700000001, 1.4361570000000015, -51.611558);
            rr_renderer_quadratic_curve_to(renderer, 19.375892, -40.434077, 33.934501000000004, -25.875470000000004);
            rr_renderer_bezier_curve_to(renderer, 51.882835, -7.927132000000004, 51.882835, 21.172873999999997, 33.934501000000004, 39.121219999999994);
            rr_renderer_bezier_curve_to(renderer, 15.986160000000005, 57.06956099999999, -13.113848999999995, 57.06956099999999, -31.062188999999996, 39.121219999999994);
            rr_renderer_fill(renderer);
            rr_renderer_set_fill(renderer, 0xff97d7ed);
            rr_renderer_begin_path(renderer);
            rr_renderer_move_to(renderer, -48.685750999999996, 27.064670000000007);
            rr_renderer_bezier_curve_to(renderer, -57.947573999999996, 4.998096000000007, -51.209878999999994, -20.538406999999992, -32.267165999999996, -35.16333999999999);
            rr_renderer_line_to(renderer, -22.352759999999996, -22.32185599999999);
            rr_renderer_bezier_curve_to(renderer, -35.47513549999999, -12.19058499999999, -40.142604999999996, 5.49957400000001, -33.726569999999995, 20.78597400000001);
            rr_renderer_fill(renderer);
            rr_renderer_set_fill(renderer, 0xff97d7ed);
            rr_renderer_begin_path(renderer);
            rr_renderer_move_to(renderer, -34.850395, -31.574703);
            rr_renderer_bezier_curve_to(renderer, -33.1808966, -35.659335999999996, -28.516250399999997, -37.617191, -24.431618, -35.9476927);
            rr_renderer_bezier_curve_to(renderer, -22.4701083, -35.14597303, -20.9074214, -33.597881099999995, -20.0873263, -31.643977899999996);
            rr_renderer_bezier_curve_to(renderer, -19.26723124, -29.690078499999995, -19.25690867, -27.490424899999997, -20.058628332, -25.528915199999997);
            rr_renderer_bezier_curve_to(renderer, -21.728126732, -21.444282199999996, -26.392772932, -19.486427199999998, -30.477409332, -21.155925499999995);
            rr_renderer_bezier_curve_to(renderer, -34.562042332000004, -22.825423899999993, -36.519893632, -27.490070099999997, -34.850395332, -31.574702499999994);
            rr_renderer_fill(renderer);
            rr_renderer_set_fill(renderer, 0xff97d7ed);
            rr_renderer_begin_path(renderer);
            rr_renderer_move_to(renderer, -48.632149999999996, 20.853179999999995);
            rr_renderer_bezier_curve_to(renderer, -46.962651599999994, 16.768546999999995, -42.298005399999994, 14.810691999999996, -38.213370999999995, 16.480193999999994);
            rr_renderer_bezier_curve_to(renderer, -36.251861299999995, 17.281913669999994, -34.6891744, 18.830009399999994, -33.869079299999996, 20.783904999999994);
            rr_renderer_bezier_curve_to(renderer, -33.048984239999996, 22.737808199999993, -33.038661669999996, 24.937461999999993, -33.84038514699999, 26.898971499999995);
            rr_renderer_bezier_curve_to(renderer, -35.509883546999994, 30.983604499999995, -40.17452784699999, 32.94145949999999, -44.25916214699999, 31.271957499999996);
            rr_renderer_bezier_curve_to(renderer, -48.343795146999994, 29.602462899999995, -50.301648146999995, 24.937812899999997, -48.632149846999994, 20.853180499999993);
            rr_renderer_fill(renderer);
            break;
        case rr_petal_id_beak:
            rr_renderer_scale(renderer, 0.1);
            rr_renderer_set_fill(renderer, 0xff292d31);
            rr_renderer_begin_path(renderer);
            rr_renderer_move_to(renderer, -63.370785, -16.611649999999997);
            rr_renderer_bezier_curve_to(renderer, -53.279056999999995, -50.393808, -43.088165, -80.59633, -33.689053, -102.36258);
            rr_renderer_bezier_curve_to(renderer, -24.28994, -124.128834, -14.989983000000002, -141.61450299999998, -6.976098, -147.20916);
            rr_renderer_bezier_curve_to(renderer, 1.0377875000000003, -152.803818, 6.578452, -148.00093666, 14.394271, -135.93052699999998);
            rr_renderer_bezier_curve_to(renderer, 22.210082, -123.86011499999998, 31.806007, -95.76142899999999, 39.918807, -74.78669699999998);
            rr_renderer_bezier_curve_to(renderer, 48.0316, -53.81196599999998, 53.968902, -35.11315699999997, 63.071044, -10.082152999999977);
            rr_renderer_bezier_curve_to(renderer, 72.173171, 14.948853000000025, 90.772079, 54.72155700000002, 94.531615, 75.39930700000002);
            rr_renderer_bezier_curve_to(renderer, 98.291167, 96.07705700000002, 94.63154481000001, 105.97070300000001, 85.62831, 113.98434400000002);
            rr_renderer_bezier_curve_to(renderer, 76.62509, 121.99798500000003, 53.769819999999996, 122.78875700000002, 40.51225, 123.48110900000002);
            rr_renderer_bezier_curve_to(renderer, 27.254682000000003, 124.17346130000001, 14.888051, 117.49938900000002, 6.082900000000002, 118.13851870000002);
            rr_renderer_bezier_curve_to(renderer, -2.7222604999999973, 118.77764834000001, -3.8102579999999975, 122.96258470000002, -12.318687999999998, 127.31585670000003);
            rr_renderer_bezier_curve_to(renderer, -20.827118499999997, 131.66909770000004, -32.501641, 141.13735970000002, -44.967687999999995, 144.25802670000002);
            rr_renderer_bezier_curve_to(renderer, -57.433733, 147.37869320000001, -78.903006, 153.36117570000002, -87.114966, 146.03988710000002);
            rr_renderer_bezier_curve_to(renderer, -95.326922, 138.71862860000002, -98.19679199999999, 127.43896510000002, -94.2394296, 100.33038410000002);
            rr_renderer_bezier_curve_to(renderer, -90.28206689999999, 73.22180210000002, -73.4625196, 17.17051410000002, -63.370789599999995, -16.611645899999985);
            rr_renderer_fill(renderer);
            rr_renderer_set_fill(renderer, 0xff444a51);
            rr_renderer_begin_path(renderer);
            rr_renderer_move_to(renderer, 77.90186, 96.01440000000002);
            rr_renderer_bezier_curve_to(renderer, 85.8242843, 79.36872400000001, 52.184253999999996, 17.157710000000023, 40.005406, -19.07211999999997);
            rr_renderer_bezier_curve_to(renderer, 27.82655, -55.301939999999966, 11.814435, -108.43806399999997, 4.8287559999999985, -121.36453999999998);
            rr_renderer_bezier_curve_to(renderer, -2.156931300000002, -134.29101599999998, 0.15094529999999828, -130.32536699999997, -1.9087090000000018, -96.63096199999998);
            rr_renderer_bezier_curve_to(renderer, -3.968363200000002, -62.93654999999998, -20.830935, 48.694338000000016, -7.529169500000002, 80.80189800000002);
            rr_renderer_bezier_curve_to(renderer, 5.772588499999998, 112.90947200000002, 69.97943649999999, 112.66005200000002, 77.9018605, 96.01439200000002);
            rr_renderer_fill(renderer);
            rr_renderer_set_fill(renderer, 0xff3b4147);
            rr_renderer_begin_path(renderer);
            rr_renderer_move_to(renderer, -76.425026, 127.36446999999998);
            rr_renderer_bezier_curve_to(renderer, -84.264123, 111.31155299999998, -52.726296000000005, 22.38176999999999, -40.950508, -19.07253000000003);
            rr_renderer_bezier_curve_to(renderer, -29.174720999999998, -60.52684500000003, -13.016044, -108.17194000000003, -5.770317999999996, -121.36141000000003);
            rr_renderer_bezier_curve_to(renderer, 1.475409500000004, -134.55088200000003, 0.5481253000000041, -131.31040000000004, 2.523856000000004, -98.20936000000003);
            rr_renderer_bezier_curve_to(renderer, 4.499586900000004, -65.10832400000004, 19.242216000000006, 39.64917999999997, 6.084074800000003, 77.24481999999998);
            rr_renderer_bezier_curve_to(renderer, -7.074075199999996, 114.84044699999998, -68.5859312, 143.41734999999997, -76.4250252, 127.36446399999997);
            rr_renderer_fill(renderer);
            break;
        case rr_petal_id_lightning:
            rr_renderer_set_stroke(renderer, 0xff00cfcf);
            rr_renderer_set_fill(renderer, 0xff00ffff);
            rr_renderer_set_line_width(renderer, 3.0f);
            rr_renderer_begin_path(renderer);
            rr_renderer_arc(renderer, 0.0f, 0.0f, 10.0f);
            rr_renderer_fill(renderer);
            rr_renderer_stroke(renderer);
            break;
        default:
            break;
        }
    }
}

void rr_renderer_draw_static_petal(struct rr_renderer *renderer, uint8_t id, uint8_t rarity, uint8_t flags)
{
    struct rr_renderer_context_state state;
    rr_renderer_context_state_init(renderer, &state);
    uint32_t count = RR_PETAL_DATA[id].count[rarity];
    if (id == rr_petal_id_peas)
        rr_renderer_rotate(renderer, 1.0f - M_PI / 4.0f);
    if (count <= 1)
    {
        if (id == rr_petal_id_missile)
            rr_renderer_rotate(renderer, 1.0f);
        else if (id == rr_petal_id_leaf)
            rr_renderer_rotate(renderer, -1.0f);
        else if (id == rr_petal_id_magnet)
            rr_renderer_rotate(renderer, -1.0f);
        else if (id == rr_petal_id_bone)
            rr_renderer_rotate(renderer, -1.0f);
        else if (id == rr_petal_id_club)
            rr_renderer_rotate(renderer, -1.0f);
        else if (id == rr_petal_id_feather)
            rr_renderer_rotate(renderer, 0.5f);
        rr_renderer_draw_petal(renderer, id, flags);
    }
    else
    {
        struct rr_renderer_context_state state;
        float r = RR_PETAL_DATA[id].clump_radius == 0.0f
                      ? 10.0f
                      : RR_PETAL_DATA[id].clump_radius;
        for (uint32_t i = 0; i < count; ++i)
        {
            rr_renderer_context_state_init(renderer, &state);
            rr_renderer_translate(renderer, r, 0.0f);
            if (id == rr_petal_id_missile)
                rr_renderer_rotate(renderer, 1.0f);
            else if (id == rr_petal_id_leaf)
                rr_renderer_rotate(renderer, -1.0f);
            else if (id == rr_petal_id_stinger && rarity == rr_rarity_id_ultra)
                rr_renderer_rotate(renderer, M_PI);
            rr_renderer_draw_petal(renderer, id, flags);
            rr_renderer_context_state_free(renderer, &state);
            rr_renderer_rotate(renderer, M_PI * 2.0f / count);
        }
    }
    rr_renderer_context_state_free(renderer, &state);
}

void rr_renderer_draw_petal_with_name(struct rr_renderer *renderer, uint8_t id, uint8_t rarity)
{
    rr_renderer_translate(renderer, 0, -5);
    rr_renderer_draw_static_petal(renderer, id, rarity, 1);
    rr_renderer_translate(renderer, 0, 25);
    rr_renderer_draw_petal_name(renderer, id, 12, 0, 0);
}

void rr_renderer_petal_cache_init()
{
    rr_renderer_init(&petal_cache);
    rr_renderer_set_dimensions(&petal_cache, 50 * rr_petal_id_max, 50);
    rr_renderer_translate(&petal_cache, 25, 25);
    struct rr_renderer_context_state state;
    for (uint32_t i = 0; i < rr_petal_id_max; ++i)
    {
        rr_renderer_context_state_init(&petal_cache, &state);
        rr_renderer_draw_petal(&petal_cache, i, 0);
        rr_renderer_context_state_free(&petal_cache, &state);
        rr_renderer_translate(&petal_cache, 50, 0);
    }
}