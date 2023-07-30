#include <Client/Renderer/RenderFunctions.h>

#include <math.h>
#include <stdio.h>

#include <Client/Assets/Render.h>
#include <Client/Game.h>
#include <Client/Renderer/Renderer.h>
#include <Shared/StaticData.h>

void rr_renderer_render_petal(struct rr_renderer *renderer, uint8_t id)
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
        rr_renderer_set_fill(renderer, 0xff333333);
        rr_renderer_set_stroke(renderer, 0xff292929);
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
        rr_renderer_set_fill(renderer, 0xff333333);
        rr_renderer_set_stroke(renderer, 0xff333333);
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
        rr_renderer_move_to(renderer, 39.5,18);
        rr_renderer_quadratic_curve_to(renderer, 0,30,0,0);
        rr_renderer_stroke(renderer);
        rr_renderer_set_stroke(renderer, 0xff4343a4);
        rr_renderer_set_line_width(renderer, 16.8);
        rr_renderer_begin_path(renderer);
        rr_renderer_move_to(renderer, 40,18);
        rr_renderer_quadratic_curve_to(renderer, 0,30,0,0);
        rr_renderer_stroke(renderer);
        rr_renderer_set_stroke(renderer, 0xff853636);
        rr_renderer_set_line_width(renderer, 28);
        rr_renderer_begin_path(renderer);
        rr_renderer_move_to(renderer, 39.5,-18);
        rr_renderer_quadratic_curve_to(renderer, 0,-30,0,0);
        rr_renderer_stroke(renderer);
        rr_renderer_set_stroke(renderer, 0xffa44343);
        rr_renderer_set_line_width(renderer, 16.8);
        rr_renderer_begin_path(renderer);
        rr_renderer_move_to(renderer, 40,-18);
        rr_renderer_quadratic_curve_to(renderer, 0,-30,0,0);
        rr_renderer_stroke(renderer);
        rr_renderer_begin_path(renderer);
        rr_renderer_set_stroke(renderer, 0xff363685);
        rr_renderer_set_line_width(renderer, 28);
        rr_renderer_move_to(renderer, 39.5,18);
        rr_renderer_quadratic_curve_to(renderer, 0,30,0,0);
        rr_renderer_stroke(renderer);
        rr_renderer_set_stroke(renderer, 0xff4343a4);
        rr_renderer_set_line_width(renderer, 16.8);
        rr_renderer_begin_path(renderer);
        rr_renderer_move_to(renderer, 40,18);
        rr_renderer_quadratic_curve_to(renderer, 0,30,0,0);
        rr_renderer_stroke(renderer);
        rr_renderer_set_line_cap(renderer, 0);
        rr_renderer_set_stroke(renderer, 0xff853636);
        rr_renderer_set_line_width(renderer, 28);
        rr_renderer_begin_path(renderer);
        rr_renderer_move_to(renderer, 39.5,-18);
        rr_renderer_quadratic_curve_to(renderer, 0,-30,0,0);
        rr_renderer_stroke(renderer);
        rr_renderer_set_stroke(renderer, 0xffa44343);
        rr_renderer_set_line_width(renderer, 16.8);
        rr_renderer_begin_path(renderer);
        rr_renderer_move_to(renderer, 40,-18);
        rr_renderer_quadratic_curve_to(renderer, 0,-30,0,0);
        rr_renderer_stroke(renderer);
        break;
    case rr_petal_id_uranium:
        rr_renderer_set_fill(renderer, 0xff63bf2e);
        rr_renderer_set_stroke(renderer, 0xff509b25);
        rr_renderer_set_line_cap(renderer, 1);
        rr_renderer_set_line_join(renderer, 1);
        rr_renderer_set_line_width(renderer, 3);
        rr_renderer_begin_path(renderer);
        rr_renderer_move_to(renderer,-7,-5);
        rr_renderer_line_to(renderer,-1,-9);
        rr_renderer_line_to(renderer,7,-6);
        rr_renderer_line_to(renderer,9,3);
        rr_renderer_line_to(renderer,2,9);
        rr_renderer_line_to(renderer,-5,6);
        rr_renderer_line_to(renderer,-8,2);
        rr_renderer_line_to(renderer,-7,-5);
        rr_renderer_fill(renderer);
        rr_renderer_stroke(renderer);
        break;
    case rr_petal_id_speed:
        rr_renderer_set_fill(renderer, 0xff1945f5);
        rr_renderer_set_stroke(renderer, 0xff1437c4);
        rr_renderer_set_line_cap(renderer, 1);
        rr_renderer_set_line_join(renderer, 1);
        rr_renderer_set_line_width(renderer, 5);
        rr_renderer_begin_path(renderer);
        rr_renderer_move_to(renderer,-10,-10);
        rr_renderer_line_to(renderer,5,-10);
        rr_renderer_line_to(renderer,10,0);
        rr_renderer_line_to(renderer,5,10);
        rr_renderer_line_to(renderer,-10,10);
        rr_renderer_line_to(renderer,-5,0);
        rr_renderer_line_to(renderer,-10,-10);
        rr_renderer_stroke(renderer);
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
        rr_renderer_quadratic_curve_to(renderer, -12.94427190999916, -9.40456403667957, -2.4721359549995796, -7.608452130361228);
        rr_renderer_quadratic_curve_to(renderer, 4.944271909999157, -15.216904260722458, 6.472135954999579, -4.702282018339786);
        rr_renderer_quadratic_curve_to(renderer, 16, -1.959434878635765e-15, 6.4721359549995805, 4.702282018339784);
        rr_renderer_quadratic_curve_to(renderer, 4.944271909999161, 15.216904260722456, -2.472135954999578, 7.608452130361229);
        rr_renderer_quadratic_curve_to(renderer, -12.944271909999157, 9.404564036679574, -8, 1.959434878635765e-15);
        rr_renderer_fill(renderer);
        rr_renderer_stroke(renderer);
        break;
    case rr_petal_id_bone:
        rr_renderer_scale(renderer, 0.1);
        rr_renderer_set_fill(renderer, 0xffa19a84);
        rr_renderer_begin_path(renderer);
        rr_renderer_move_to(renderer, -52.30789, 37.23142999999999);
        rr_renderer_bezier_curve_to(renderer, -52.325330796, 60.77389499999999, -46.342066, 134.50020999999998, -40.291669999999996, 154.88824499999998);
        rr_renderer_bezier_curve_to(renderer, -34.241277999999994, 175.276276, -24.568678, 167.81780999999998, -16.005529999999997, 159.55963169999998);
        rr_renderer_bezier_curve_to(renderer, -7.442373999999997, 151.30145269999997, 0.7581950000000042, 120.55264169999998, 11.087259000000003, 105.33917169999998);
        rr_renderer_bezier_curve_to(renderer, 21.416322, 90.12573169999997, 40.778429, 85.40676769999999, 45.968859, 68.27886869999998);
        rr_renderer_bezier_curve_to(renderer, 51.159288700000005, 51.150984699999974, 56.589159, 11.679381699999972, 42.2298453, 2.57181869999998);
        rr_renderer_bezier_curve_to(renderer, 27.870531300000003, -6.5357553000000195, -24.430730700000005, 7.85685269999998, -40.1870147, 13.63346419999998);
        rr_renderer_bezier_curve_to(renderer, -55.9433017, 19.41006019999998, -52.2904467, 13.68896041599998, -52.307887199999996, 37.23142519999998);
        rr_renderer_fill(renderer);
        rr_renderer_set_fill(renderer, 0xffa19a84);
        rr_renderer_begin_path(renderer);
        rr_renderer_move_to(renderer, -52.679153, -69.82287);
        rr_renderer_bezier_curve_to(renderer, -52.679153, -98.59625399999999, -29.353713, -121.921694, -0.580328999999999, -121.921694);
        rr_renderer_bezier_curve_to(renderer, 13.237138000000002, -121.921694, 26.488679, -116.432726, 36.259095, -106.662302);
        rr_renderer_bezier_curve_to(renderer, 46.0295265, -96.89187799999999, 51.518494000000004, -83.64033699999999, 51.518494000000004, -69.82287199999999);
        rr_renderer_line_to(renderer, 51.518494000000004, 25.051018000000013);
        rr_renderer_bezier_curve_to(renderer, 51.518494000000004, 53.824410000000015, 28.193054000000004, 77.14984800000002, -0.5803299999999965, 77.14984800000002);
        rr_renderer_bezier_curve_to(renderer, -29.353713999999997, 77.14984800000002, -52.679154, 53.82440800000002, -52.679154, 25.05101800000002);
        rr_renderer_fill(renderer);
        rr_renderer_set_fill(renderer, 0xffa19a84);
        rr_renderer_begin_path(renderer);
        rr_renderer_move_to(renderer, -22.684880000000007, -92.49658);
        rr_renderer_bezier_curve_to(renderer, -22.684880000000007, -123.85515799999999, 2.736262999999994, -149.276308, 34.094835999999994, -149.276308);
        rr_renderer_bezier_curve_to(renderer, 49.15376499999999, -149.276308, 63.59590399999999, -143.294176, 74.24417399999999, -132.64591000000001);
        rr_renderer_bezier_curve_to(renderer, 84.89242799999998, -121.99764800000001, 90.87455999999999, -107.55550200000002, 90.87455999999999, -92.49658000000002);
        rr_renderer_bezier_curve_to(renderer, 90.87455999999999, -61.13800600000002, 65.45341699999999, -35.71685600000002, 34.09483599999999, -35.71685600000002);
        rr_renderer_bezier_curve_to(renderer, 2.7362619999999858, -35.71685600000002, -22.684880000000014, -61.13800600000002, -22.684880000000014, -92.49658000000002);
        rr_renderer_fill(renderer);
        rr_renderer_set_fill(renderer, 0xffa19a84);
        rr_renderer_begin_path(renderer);
        rr_renderer_move_to(renderer, -90.874807, -105.729);
        rr_renderer_bezier_curve_to(renderer, -90.874807, -140.114143, -63.000141, -167.988808, -28.614999000000005, -167.988808);
        rr_renderer_bezier_curve_to(renderer, -12.102678000000004, -167.988808, 3.733350999999999, -161.4293116, 15.409330999999995, -149.753332);
        rr_renderer_bezier_curve_to(renderer, 27.085302999999996, -138.077354, 33.64480499999999, -122.24132900000001, 33.64480499999999, -105.72900200000001);
        rr_renderer_bezier_curve_to(renderer, 33.64480499999999, -71.34385900000001, 5.770140999999992, -43.46919400000001, -28.61499900000001, -43.46919400000001);
        rr_renderer_bezier_curve_to(renderer, -63.00014200000001, -43.46919400000001, -90.874807, -71.34385800000001, -90.874807, -105.72900200000001);
        rr_renderer_fill(renderer);
        rr_renderer_set_fill(renderer, 0xffa19a84);
        rr_renderer_begin_path(renderer);
        rr_renderer_move_to(renderer, -68.815947, -58.239875999999995);
        rr_renderer_bezier_curve_to(renderer, -60.59798099999999, -62.0230791, -50.323882999999995, -57.20976279999999, -45.868106999999995, -47.48902149999999);
        rr_renderer_bezier_curve_to(renderer, -41.412330999999995, -37.76828049999999, -44.462188899999994, -26.821167499999994, -52.680153, -23.037964499999994);
        rr_renderer_bezier_curve_to(renderer, -51.6542932, -36.453034499999994, -57.9922143, -50.27986949999999, -68.815947, -58.239876499999994);
        rr_renderer_fill(renderer);
        rr_renderer_set_fill(renderer, 0xffa19a84);
        rr_renderer_begin_path(renderer);
        rr_renderer_move_to(renderer, 51.524100000000004, -11.064699999999988);
        rr_renderer_bezier_curve_to(renderer, 43.60037870000001, -14.448565399999987, 40.499411, -24.969728999999987, 44.5978915, -34.56434999999999);
        rr_renderer_bezier_curve_to(renderer, 48.6963565, -44.15898499999999, 58.4422675, -49.19380599999999, 66.3659885, -45.80993999999999);
        rr_renderer_bezier_curve_to(renderer, 56.0345675, -37.80653699999999, 50.1631535, -24.06138999999999, 51.5241005, -11.064699999999988);
        rr_renderer_fill(renderer);
        rr_renderer_set_fill(renderer, 0xffccc3a8);
        rr_renderer_begin_path(renderer);
        rr_renderer_move_to(renderer, -73.95985, -105.72996499999999);
        rr_renderer_bezier_curve_to(renderer, -73.95985, -130.77268999999998, -53.658714, -151.073829, -28.615990000000004, -151.073829);
        rr_renderer_bezier_curve_to(renderer, -16.590050000000005, -151.073829, -5.056664000000005, -146.2965425, 3.446959999999997, -137.79291849999998);
        rr_renderer_bezier_curve_to(renderer, 11.950583999999997, -129.28929649999998, 16.727873999999996, -117.75590649999998, 16.727873999999996, -105.72996849999998);
        rr_renderer_bezier_curve_to(renderer, 16.727873999999996, -80.68724349999998, -3.573266000000004, -60.38610449999998, -28.615990000000007, -60.38610449999998);
        rr_renderer_bezier_curve_to(renderer, -53.65871500000001, -60.38610449999998, -73.95985, -80.68724449999998, -73.95985, -105.72996849999998);
        rr_renderer_fill(renderer);
        rr_renderer_set_fill(renderer, 0xffccc3a8);
        rr_renderer_begin_path(renderer);
        rr_renderer_move_to(renderer, -7.198784000000003, -92.49596);
        rr_renderer_bezier_curve_to(renderer, -7.198784000000003, -114.64873499999999, 10.759581999999998, -132.607105, 32.912352999999996, -132.607105);
        rr_renderer_bezier_curve_to(renderer, 43.550490999999994, -132.607105, 53.752928999999995, -128.3811223, 61.275223, -120.858825);
        rr_renderer_bezier_curve_to(renderer, 68.797516, -113.3365243, 73.023499, -103.134097, 73.023499, -92.49596);
        rr_renderer_bezier_curve_to(renderer, 73.023499, -70.343189, 55.06514, -52.384814999999996, 32.912354, -52.384814999999996);
        rr_renderer_bezier_curve_to(renderer, 10.759583, -52.384814999999996, -7.198782999999999, -70.343189, -7.198782999999999, -92.49596);
        rr_renderer_fill(renderer);
        rr_renderer_set_fill(renderer, 0xffccc3a8);
        rr_renderer_begin_path(renderer);
        rr_renderer_move_to(renderer, -34.906063, -65.727585);
        rr_renderer_bezier_curve_to(renderer, -34.906063, -84.685654, -19.537514, -100.05419900000001, -0.5794430000000048, -100.05419900000001);
        rr_renderer_bezier_curve_to(renderer, 8.524537999999994, -100.05419900000001, 17.255646999999996, -96.43766000000001, 23.693139999999996, -90.00016800000002);
        rr_renderer_bezier_curve_to(renderer, 30.130632399999996, -83.56267560000002, 33.747178999999996, -74.83156600000001, 33.747178999999996, -65.72758500000002);
        rr_renderer_line_to(renderer, 33.747178999999996, 27.852404999999976);
        rr_renderer_bezier_curve_to(renderer, 33.747178999999996, 46.81047399999997, 18.378625999999997, 62.179018999999975, -0.5794430000000048, 62.179018999999975);
        rr_renderer_bezier_curve_to(renderer, -19.537512000000003, 62.179018999999975, -34.906063, 46.81047299999997, -34.906063, 27.852404999999976);
        rr_renderer_fill(renderer);
        rr_renderer_set_fill(renderer, 0xffccc3a8);
        rr_renderer_begin_path(renderer);
        rr_renderer_move_to(renderer, -58.027287, -70.988205);
        rr_renderer_bezier_curve_to(renderer, -46.215275000000005, -76.41079699999999, -31.451584, -69.4762116, -25.051659, -55.49936699999999);
        rr_renderer_bezier_curve_to(renderer, -18.6517414, -41.522521999999995, -23.039101000000002, -25.79615799999999, -34.851113, -20.373566999999994);
        rr_renderer_bezier_curve_to(renderer, -33.371605599999995, -39.649964999999995, -42.474896, -59.530716999999996, -58.027287, -70.98820699999999);
        rr_renderer_fill(renderer);
        rr_renderer_set_fill(renderer, 0xffccc3a8);
        rr_renderer_begin_path(renderer);
        rr_renderer_move_to(renderer, 33.68027000000001, -7.4407799999999895);
        rr_renderer_bezier_curve_to(renderer, 21.742160000000005, -12.54811029999999, 17.082179000000007, -28.41929599999999, 23.271930000000005, -42.89005999999999);
        rr_renderer_bezier_curve_to(renderer, 29.461673000000005, -57.360823999999994, 44.157214, -64.95138499999999, 56.095325, -59.84405499999999);
        rr_renderer_bezier_curve_to(renderer, 40.513446, -47.77596999999999, 31.646091000000002, -27.045317999999988, 33.680271000000005, -7.4407799999999895);
        rr_renderer_fill(renderer);
        rr_renderer_set_fill(renderer, 0xffccc3a8);
        rr_renderer_begin_path(renderer);
        rr_renderer_move_to(renderer, -34.85657, 32.84309999999999);
        rr_renderer_bezier_curve_to(renderer, -34.77570223, 55.19631, -32.894568199999995, 134.49256, -27.270719999999997, 144.71857);
        rr_renderer_bezier_curve_to(renderer, -21.646872, 154.94455299999998, -10.654469999999996, 107.64026, -1.1134859999999982, 94.19907);
        rr_renderer_bezier_curve_to(renderer, 8.427507000000002, 80.757862, 24.320688, 77.137241, 29.97519, 64.071308);
        rr_renderer_bezier_curve_to(renderer, 35.6297005, 51.005375, 34.390763, 25.977131, 32.8135384, 15.803470000000004);
        rr_renderer_bezier_curve_to(renderer, 31.2363289, 5.629794000000004, 30.60682, 3.8966550000000044, 20.511902399999997, 3.0293000000000045);
        rr_renderer_bezier_curve_to(renderer, 10.416992399999996, 2.1619294000000044, -18.527854600000005, 5.630328400000005, -27.7559356, 10.599292000000005);
        rr_renderer_bezier_curve_to(renderer, -36.984016600000004, 15.568255600000006, -34.9374426, 10.489886480000006, -34.856571100000004, 32.843097);
        rr_renderer_fill(renderer);
        rr_renderer_set_fill(renderer, 0xffa19a84);
        rr_renderer_begin_path(renderer);
        rr_renderer_move_to(renderer, 7.4694199999999995, -143.298567);
        rr_renderer_bezier_curve_to(renderer, 1.8085769999999997, -142.26893629999998, -5.008752000000001, -135.42306539999998, -8.745653, -128.123692);
        rr_renderer_bezier_curve_to(renderer, -12.482553300000001, -120.82431460000001, -14.328806, -108.014206, -14.951974700000001, -99.50232);
        rr_renderer_bezier_curve_to(renderer, -15.575143650000001, -90.990433, -15.906549300000002, -73.735161, -12.484666700000002, -77.05238399999999);
        rr_renderer_bezier_curve_to(renderer, -9.062791700000002, -80.36960659999998, -0.704713700000001, -109.86415399999998, 5.579305299999998, -119.405667);
        rr_renderer_bezier_curve_to(renderer, 11.863317299999999, -128.947182, 24.904409299999998, -130.31931749999998, 25.2194263, -134.301469);
        rr_renderer_bezier_curve_to(renderer, 25.53445163, -138.28361619999998, 13.130269299999998, -144.328197, 7.469418299999997, -143.298568);
        rr_renderer_fill(renderer);
        rr_renderer_set_fill(renderer, 0xffa19a84);
        rr_renderer_begin_path(renderer);
        rr_renderer_move_to(renderer, -1.8945099999999968, 81.83704);
        rr_renderer_bezier_curve_to(renderer, -1.1677491399999969, 64.905232, -2.9336563999999967, 2.2511300000000034, -1.272927969999997, 3.2892200000000003);
        rr_renderer_bezier_curve_to(renderer, 0.38780053000000314, 4.327305900000001, 8.796614030000004, 71.13375, 8.069845030000003, 88.06556);
        rr_renderer_bezier_curve_to(renderer, 7.343084170000004, 104.997353, -3.9727959699999964, 105.91810000000001, -5.633523969999997, 104.880013);
        rr_renderer_bezier_curve_to(renderer, -7.294252469999997, 103.8419271, -2.621278769999997, 98.7688375, -1.894510269999997, 81.837044);
        rr_renderer_fill(renderer);
        break;
    case rr_petal_id_web:
        rr_renderer_set_fill(renderer, 0xffffffff);
        rr_renderer_set_stroke(renderer, 0xffcfcfcf);
        rr_renderer_set_line_cap(renderer, 1);
        rr_renderer_set_line_join(renderer, 1);
        rr_renderer_set_line_width(renderer, 3);
        rr_renderer_begin_path(renderer);
        rr_renderer_move_to(renderer,11,0);
        rr_renderer_quadratic_curve_to(renderer,4.319756031036377,3.138486623764038,3.399186611175537,10.46162223815918);
        rr_renderer_quadratic_curve_to(renderer,-1.6500004529953003,5.0781779289245605,-8.899188041687012,6.46563720703125);
        rr_renderer_quadratic_curve_to(renderer,-5.339512348175049,-5.722046125811175e-7,-8.899186134338379,-6.465639114379883);
        rr_renderer_quadratic_curve_to(renderer,-1.6499993801116943,-5.078178405761719,3.399188280105591,-10.461621284484863);
        rr_renderer_quadratic_curve_to(renderer,4.319756507873535,-3.138485908508301,11,0.000001923301169881597);
        rr_renderer_fill(renderer);
        rr_renderer_stroke(renderer);
        break;
    case rr_petal_id_seed:
        rr_renderer_scale(renderer, 0.1);
        rr_renderer_set_fill(renderer, 0xffb07200);
        rr_renderer_begin_path(renderer);
        rr_renderer_move_to(renderer, 80.90206999999998, -82.33018000000001);
        rr_renderer_bezier_curve_to(renderer, 125.71978999999999, -37.51246000000001, 125.71978999999999, 35.15142999999999, 80.90206999999998, 79.96911999999998);
        rr_renderer_bezier_curve_to(renderer, 59.37985299999998, 101.49136699999997, 30.189453999999984, 113.58242999999997, -0.2475700000000245, 113.58242999999997);
        rr_renderer_bezier_curve_to(renderer, -30.684597000000025, 113.58242999999997, -59.874996000000024, 101.49136599999997, -81.39723000000002, 79.96911999999998);
        rr_renderer_bezier_curve_to(renderer, -126.21495000000002, 35.15143199999998, -126.21495000000002, -37.51246000000002, -81.39723000000002, -82.33018000000001);
        rr_renderer_bezier_curve_to(renderer, -36.57951000000002, -127.14790000000002, 36.08437999999998, -127.14790000000002, 80.90206999999997, -82.33018000000001);
        rr_renderer_fill(renderer);
        rr_renderer_set_fill(renderer, 0xffb07200);
        rr_renderer_begin_path(renderer);
        rr_renderer_move_to(renderer, 95.57850000000002, 39.56533999999999);
        rr_renderer_bezier_curve_to(renderer, 110.78849100000002, 54.775330999999994, 110.78849100000002, 79.43557999999999, 95.57850000000002, 94.64553999999998);
        rr_renderer_bezier_curve_to(renderer, 88.27442300000001, 101.94964769999999, 78.36796000000001, 106.05304099999998, 68.03840000000002, 106.05304099999998);
        rr_renderer_bezier_curve_to(renderer, 57.70887100000002, 106.05304099999998, 47.80240800000003, 101.94964739999998, 40.49830000000003, 94.64553999999998);
        rr_renderer_bezier_curve_to(renderer, 25.28833900000003, 79.43557899999999, 25.28833900000003, 54.77532999999998, 40.49830000000003, 39.565339999999985);
        rr_renderer_bezier_curve_to(renderer, 55.70829100000003, 24.355378999999985, 80.36854000000002, 24.355378999999985, 95.57850000000002, 39.565339999999985);
        rr_renderer_fill(renderer);
        rr_renderer_set_fill(renderer, 0xffc98200);
        rr_renderer_begin_path(renderer);
        rr_renderer_move_to(renderer, -0.24810999999999694, -82.33045999999999);
        rr_renderer_bezier_curve_to(renderer, 44.569610000000004, -82.33045999999999, 80.90155, -45.998519999999985, 80.90155, -1.1807999999999907);
        rr_renderer_quadratic_curve_to(renderer, 80.90155, 34.63580500000001, 71.385132, 70.45242400000001);
        rr_renderer_quadratic_curve_to(renderer, 35.568512, 79.96884200000001, -0.248108000000002, 79.96884200000001);
        rr_renderer_bezier_curve_to(renderer, -45.065828, 79.96884200000001, -81.397768, 43.636902000000006, -81.397768, -1.1807979999999958);
        rr_renderer_bezier_curve_to(renderer, -81.397768, -45.998518, -45.065827999999996, -82.330458, -0.248108000000002, -82.330458);
        rr_renderer_fill(renderer);
        rr_renderer_set_fill(renderer, 0xffb07200);
        rr_renderer_begin_path(renderer);
        rr_renderer_move_to(renderer, -74.22667999999999, -77.81169);
        rr_renderer_bezier_curve_to(renderer, -15.663126999999989, -81.5095202, 35.641390000000015, -38.93869, 42.810490000000016, 19.301910000000007);
        rr_renderer_line_to(renderer, 6.678913000000016, 23.749481000000007);
        rr_renderer_bezier_curve_to(renderer, 1.8635900000000154, -15.369552999999993, -32.59664699999998, -43.963528999999994, -71.93259699999999, -41.47976899999999);
        rr_renderer_fill(renderer);
        rr_renderer_set_fill(renderer, 0xffb07200);
        rr_renderer_begin_path(renderer);
        rr_renderer_move_to(renderer, 37.648829999999975, 9.861109999999996);
        rr_renderer_bezier_curve_to(renderer, 44.736689999999975, 16.948969999999996, 44.736689999999975, 28.440669999999997, 37.648829999999975, 35.528529999999996);
        rr_renderer_bezier_curve_to(renderer, 34.245112999999975, 38.932247, 29.628687999999975, 40.8444175, 24.815119999999975, 40.8444175);
        rr_renderer_bezier_curve_to(renderer, 20.001551999999975, 40.8444175, 15.385111999999975, 38.9322471, 11.981409999999975, 35.528529999999996);
        rr_renderer_bezier_curve_to(renderer, 4.893549999999975, 28.440669999999997, 4.893549999999975, 16.948969999999996, 11.981409999999975, 9.861109999999996);
        rr_renderer_bezier_curve_to(renderer, 19.069269999999975, 2.7732499999999964, 30.560969999999976, 2.7732499999999964, 37.648829999999975, 9.861109999999996);
        rr_renderer_fill(renderer);
        break;
    default:
        break;
    }
}

void rr_renderer_render_static_petal(struct rr_renderer *renderer, uint8_t id,
                                     uint8_t rarity)
{
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
        rr_renderer_render_petal(renderer, id);
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
            rr_renderer_render_petal(renderer, id);
            rr_renderer_context_state_free(renderer, &state);
            rr_renderer_rotate(renderer, M_PI * 2.0f / count);
        }
    }
}

// clang-format off
void rr_renderer_render_mob(struct rr_renderer *renderer, struct rr_game *game,
                            uint8_t id, float animation_tick, float turning_value, uint8_t use_image_cache)
{
    if (game->cache.ourpetsnake_mode)
    {
        rr_renderer_set_fill(renderer, 0xff888888);
        rr_renderer_set_stroke(renderer, 0xff6c6c6c);
        rr_renderer_set_line_width(renderer, 5);
        rr_renderer_begin_path(renderer);
        rr_renderer_arc(renderer, 0, 0, RR_MOB_DATA[id].radius);
        rr_renderer_fill(renderer);
        rr_renderer_stroke(renderer);
        return;
    }
    struct rr_renderer_context_state original_state;
    struct rr_renderer_context_state state;

    rr_renderer_context_state_init(renderer, &original_state);
    switch (id)
    {
    case rr_mob_id_triceratops:
        rr_renderer_rotate(renderer, M_PI / 2);
        rr_renderer_scale(renderer, 0.2f);

        rr_renderer_context_state_init(renderer, &state);
            rr_renderer_translate(renderer, 0.0f, animation_tick * 10.0f);
            if (use_image_cache)
                rr_renderer_draw_image(renderer, &game->mob_triceratops_legs[0]);
            else
                rr_triceratops_leg1_draw(renderer);
        rr_renderer_context_state_free(renderer, &state);

        rr_renderer_context_state_init(renderer, &state);
            rr_renderer_translate(renderer, 0.0f, animation_tick * -10.0f);
            if (use_image_cache)
                rr_renderer_draw_image(renderer, &game->mob_triceratops_legs[1]);
            else
                rr_triceratops_leg2_draw(renderer);
        rr_renderer_context_state_free(renderer, &state);

        rr_renderer_context_state_init(renderer, &state);
            rr_renderer_translate(renderer,  0, 75);
            rr_renderer_rotate(renderer, turning_value);
            rr_renderer_translate(renderer,  0, -75 + 155);
            if (use_image_cache)
                rr_renderer_draw_image(renderer, &game->mob_triceratops_tail);
            else
                rr_triceratops_tail_draw(renderer);
        rr_renderer_context_state_free(renderer, &state);

        if (use_image_cache)
            rr_renderer_draw_image(renderer, &game->mob_triceratops_body);
        else
            rr_triceratops_body_draw(renderer);

        rr_renderer_context_state_init(renderer, &state);
            rr_renderer_translate(renderer,  0, -75);
            rr_renderer_rotate(renderer, -0);
            rr_renderer_translate(renderer,  0, 75 - 145);
            if (use_image_cache)
                rr_renderer_draw_image(renderer, &game->mob_triceratops_head);
            else
                rr_triceratops_head_draw(renderer);
        rr_renderer_context_state_free(renderer, &state);
        break;
    case rr_mob_id_trex:
        rr_renderer_rotate(renderer, M_PI / 2);
        rr_renderer_scale(renderer, 0.2f);

        rr_renderer_context_state_init(renderer, &state);
            rr_renderer_translate(renderer, 0.0f, animation_tick * 10.0f);
            if (use_image_cache)
                rr_renderer_draw_image(renderer, &game->mob_trex_legs[0]);
            else
                rr_t_rex_leg1_draw(renderer);
        rr_renderer_context_state_free(renderer, &state);

        rr_renderer_context_state_init(renderer, &state);
            rr_renderer_translate(renderer, 0.0f, animation_tick * -10.0f);
            if (use_image_cache)
                rr_renderer_draw_image(renderer, &game->mob_trex_legs[1]);
            else
                rr_t_rex_leg2_draw(renderer);
        rr_renderer_context_state_free(renderer, &state);

    rr_renderer_context_state_init(renderer, &state);
        rr_renderer_translate(renderer,  0, 75);
        rr_renderer_rotate(renderer, turning_value);
        rr_renderer_translate(renderer,  0, -75 + 150);
        if (use_image_cache)
            rr_renderer_draw_image(renderer, &game->mob_trex_tail);
        else
            rr_t_rex_tail_draw(renderer);
    rr_renderer_context_state_free(renderer, &state);
    
    if (use_image_cache)
        rr_renderer_draw_image(renderer, &game->mob_trex_body);
    else
        rr_t_rex_body_draw(renderer);
    
    rr_renderer_translate(renderer, 0, -125);
    if (use_image_cache)
        rr_renderer_draw_image(renderer, &game->mob_trex_head);
    else
        rr_t_rex_head_draw(renderer);
    break;
    case rr_mob_id_fern:
        rr_renderer_scale(renderer, 0.15f);
        if (use_image_cache)
            rr_renderer_draw_image(renderer, &game->mob_fern);
        else
            rr_fern_draw(renderer);
        break;
    case rr_mob_id_stump:
        rr_renderer_rotate(renderer, M_PI / 2);
        rr_renderer_scale(renderer, 0.12f);
        if (use_image_cache)
            rr_renderer_draw_image(renderer, &game->mob_stump);
        else
            rr_stump_draw(renderer);
        break;
    case rr_mob_id_pteranodon:
        rr_renderer_rotate(renderer, M_PI / 2);
        rr_renderer_scale(renderer, 0.2f);

        rr_renderer_context_state_init(renderer, &state);
            rr_renderer_rotate(renderer, animation_tick * 0.1f);
            rr_renderer_translate(renderer, 175, 0);
            if (use_image_cache)
                rr_renderer_draw_image(renderer, &game->mob_pteranodon_wings[0]);
            else
                rr_pteranodon_wing1_draw(renderer);
        rr_renderer_context_state_free(renderer, &state);

        rr_renderer_context_state_init(renderer, &state);
            rr_renderer_rotate(renderer, animation_tick * -0.1f);
            rr_renderer_translate(renderer, -175, 0);
            if (use_image_cache)
                rr_renderer_draw_image(renderer, &game->mob_pteranodon_wings[1]);
            else
                rr_pteranodon_wing2_draw(renderer);
        rr_renderer_context_state_free(renderer, &state);
        if (use_image_cache)
            rr_renderer_draw_image(renderer, &game->mob_pteranodon_body);
        else
            rr_pteranodon_body_draw(renderer);
        break;
    case rr_mob_id_dakotaraptor:
        rr_renderer_rotate(renderer, M_PI / 2);
        rr_renderer_scale(renderer, 0.2f);

        rr_renderer_context_state_init(renderer, &state);
            rr_renderer_translate(renderer, -65, 0);
            rr_renderer_rotate(renderer, animation_tick * 0.1f);
            if (use_image_cache)
                rr_renderer_draw_image(renderer, &game->mob_dakotaraptor_wings[0]);
            else
                rr_dakotaraptor_wing1_draw(renderer);
        rr_renderer_context_state_free(renderer, &state);
        
        rr_renderer_context_state_init(renderer, &state);
            rr_renderer_translate(renderer, 65, 0);
            rr_renderer_rotate(renderer, animation_tick * -0.1f);
            if (use_image_cache)
                rr_renderer_draw_image(renderer, &game->mob_dakotaraptor_wings[1]);
            else
                rr_dakotaraptor_wing2_draw(renderer);
        rr_renderer_context_state_free(renderer, &state);

        rr_renderer_context_state_init(renderer, &state);
            rr_renderer_translate(renderer, 0, 155);
            rr_renderer_rotate(renderer, turning_value);
            rr_renderer_translate(renderer,  0, 0);
            if (use_image_cache)
                rr_renderer_draw_image(renderer, &game->mob_dakotaraptor_tail);
            else
                rr_dakotaraptor_tail_draw(renderer);
        rr_renderer_context_state_free(renderer, &state);

        if (use_image_cache)
            rr_renderer_draw_image(renderer, &game->mob_dakotaraptor_body);
        else
            rr_dakotaraptor_body_draw(renderer);

        rr_renderer_context_state_init(renderer, &state);
            rr_renderer_translate(renderer, 0, -125);
            rr_renderer_rotate(renderer, -0);
            if (use_image_cache)
                rr_renderer_draw_image(renderer, &game->mob_dakotaraptor_head);
            else
                rr_dakotaraptor_head_draw(renderer);
        rr_renderer_context_state_free(renderer, &state);
        break;
    case rr_mob_id_pachycephalosaurus:
        rr_renderer_rotate(renderer, M_PI / 2);
        rr_renderer_scale(renderer, 0.2f);

        rr_renderer_context_state_init(renderer, &state);
            rr_renderer_translate(renderer, 0.0f, animation_tick * 10.0f);
            if (use_image_cache)
                rr_renderer_draw_image(renderer, &game->mob_pachycephalosaurus_legs[0]);
            else
                rr_pachycephalosaurus_leg1_draw(renderer);
        rr_renderer_context_state_free(renderer, &state);

        rr_renderer_context_state_init(renderer, &state);
            rr_renderer_translate(renderer, 0.0f, animation_tick * -10.0f);
            if (use_image_cache)
                rr_renderer_draw_image(renderer, &game->mob_pachycephalosaurus_legs[1]);
            else
                rr_pachycephalosaurus_leg2_draw(renderer);
        rr_renderer_context_state_free(renderer, &state);

        rr_renderer_context_state_init(renderer, &state);
            rr_renderer_translate(renderer, 0, 155);
            rr_renderer_rotate(renderer, turning_value);
            rr_renderer_translate(renderer,  0, -0);
            if (use_image_cache)
                rr_renderer_draw_image(renderer, &game->mob_pachycephalosaurus_tail);
            else
                rr_pachycephalosaurus_tail_draw(renderer);
        rr_renderer_context_state_free(renderer, &state);

        if (use_image_cache)
            rr_renderer_draw_image(renderer, &game->mob_pachycephalosaurus_body);
        else
            rr_pachycephalosaurus_body_draw(renderer);
        
        rr_renderer_context_state_init(renderer, &state);
            rr_renderer_translate(renderer, 0, -135);
            rr_renderer_rotate(renderer, -0);
            if (use_image_cache)
                rr_renderer_draw_image(renderer, &game->mob_pachycephalosaurus_head);
            else
                rr_pachycephalosaurus_head_draw(renderer);
        rr_renderer_context_state_free(renderer, &state);
        break;
    case rr_mob_id_ornithomimus:
        rr_renderer_rotate(renderer, M_PI / 2);
        rr_renderer_scale(renderer, 0.2f);

        rr_renderer_context_state_init(renderer, &state);
            rr_renderer_translate(renderer, 70, 0);
            rr_renderer_rotate(renderer, animation_tick * 0.1f);
            if (use_image_cache)
                rr_renderer_draw_image(renderer, &game->mob_ornithomimus_wings[0]);
            else
                rr_ornithomimus_wing1_draw(renderer);
        rr_renderer_context_state_free(renderer, &state);
        
        rr_renderer_context_state_init(renderer, &state);
            rr_renderer_translate(renderer, -70, 0);
            rr_renderer_rotate(renderer, animation_tick * -0.1f);
            if (use_image_cache)
                rr_renderer_draw_image(renderer, &game->mob_ornithomimus_wings[1]);
            else
                rr_ornithomimus_wing2_draw(renderer);
        rr_renderer_context_state_free(renderer, &state);

        rr_renderer_context_state_init(renderer, &state);
            rr_renderer_translate(renderer, 0, 155);
            rr_renderer_rotate(renderer, turning_value);
            rr_renderer_translate(renderer,  0, -0);
            if (use_image_cache)
                rr_renderer_draw_image(renderer, &game->mob_ornithomimus_tail);
            else
                rr_ornithomimus_tail_draw(renderer);
        rr_renderer_context_state_free(renderer, &state);

        if (use_image_cache)
            rr_renderer_draw_image(renderer, &game->mob_ornithomimus_body);
        else
            rr_ornithomimus_body_draw(renderer);
        
        rr_renderer_context_state_init(renderer, &state);
            rr_renderer_translate(renderer, 0, -145);
            rr_renderer_rotate(renderer, -0);
            rr_renderer_draw_image(renderer, &game->mob_ornithomimus_head); //fix
        rr_renderer_context_state_free(renderer, &state);
        break;
    case 255:
        rr_renderer_set_stroke(renderer, 0xffcfcfcf);
        rr_renderer_set_fill(renderer, 0xffffffff);
        rr_renderer_set_line_width(renderer, 7.0f);
        rr_renderer_begin_path(renderer);
        rr_renderer_arc(renderer, 0.0f, 0.0f, 7.0f);
        rr_renderer_fill(renderer);
        rr_renderer_stroke(renderer);
        break;
    default:
        break;
    }

    rr_renderer_context_state_free(renderer, &original_state);
}

void rr_renderer_render_background(struct rr_renderer *renderer, uint8_t rarity)
{
    if (rarity == 255)
    {
        rr_renderer_set_fill(renderer, 0xffcccccc);
        renderer->state.filter.amount = 0.2f;
        rr_renderer_set_stroke(renderer, 0xffcccccc);
        rr_renderer_set_line_width(renderer, 6.0f);
        rr_renderer_begin_path(renderer);
        rr_renderer_round_rect(renderer, -30.0f, -30.0f, 60.0f, 60.0f, 6.0f);
        rr_renderer_fill(renderer);
        rr_renderer_stroke(renderer);
        renderer->state.filter.amount = 0.0f;
        return;
    }
    else if (rarity == 254)
    {
        rr_renderer_set_fill(renderer, 0x40ffffff);
        rr_renderer_begin_path(renderer);
        rr_renderer_round_rect(renderer, -32.0f, -32.0f, 64.0f, 64.0f, 6.0f);
        rr_renderer_fill(renderer);
        return;
    }
    renderer->state.filter.amount = 0.2f;
    rr_renderer_set_fill(renderer, RR_RARITY_COLORS[rarity]);
    rr_renderer_set_line_width(renderer, 6.0f);
    rr_renderer_begin_path(renderer);
    rr_renderer_round_rect(renderer, -33.0f, -33.0f, 66.0f, 66.0f, 6.0f);
    rr_renderer_fill(renderer);
    renderer->state.filter.amount = 0.0f;
    rr_renderer_set_fill(renderer, RR_RARITY_COLORS[rarity]);
    rr_renderer_begin_path(renderer);
    rr_renderer_round_rect(renderer, -27.0f, -27.0f, 54.0f, 54.0f, 3.0f);
    rr_renderer_fill(renderer);
    rr_renderer_clip(renderer);
}

void rr_renderer_render_petal_with_background(struct rr_renderer *renderer, struct rr_game *game, uint8_t id, uint8_t rarity)
{
    rr_renderer_translate(renderer, 0, -5);
    rr_renderer_draw_image(
        renderer, &game->static_petals[id][rarity]);
    rr_renderer_translate(renderer, 0, 20);
    float text_length = rr_renderer_get_text_size(RR_PETAL_NAMES[id]);
    rr_renderer_set_fill(renderer, 0xffffffff);
    rr_renderer_set_stroke(renderer, 0xff222222);
    rr_renderer_set_text_align(renderer, 1);
    rr_renderer_set_text_baseline(renderer, 1);
    float text_size = text_length > 50 / 14 ? 50 / text_length : 14;
    rr_renderer_set_text_size(renderer, text_size);
    rr_renderer_set_line_width(renderer, text_size * 0.12);
    rr_renderer_begin_path(renderer);
    rr_renderer_stroke_text(renderer, RR_PETAL_NAMES[id], 0, 0);
    rr_renderer_fill_text(renderer, RR_PETAL_NAMES[id], 0, 0);
}
// clang-format on
