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
        case rr_petal_id_fossil:
            rr_renderer_scale(renderer, 0.2);
            rr_renderer_set_fill(renderer, 0xff95896a);
            rr_renderer_begin_path(renderer);
            rr_renderer_move_to(renderer, -51.079252, -54.7705);
            rr_renderer_line_to(renderer, 13.74432800000001, -69.950457);
            rr_renderer_line_to(renderer, 72.003118, -25.230933);
            rr_renderer_line_to(renderer, 66.2596793, 33.848199);
            rr_renderer_line_to(renderer, 19.487775300000003, 69.951554);
            rr_renderer_line_to(renderer, -42.2597527, 56.496842);
            rr_renderer_line_to(renderer, -72.0026437, 6.358994000000003);
            rr_renderer_fill(renderer);
            rr_renderer_set_fill(renderer, 0xffa49776);
            rr_renderer_begin_path(renderer);
            rr_renderer_move_to(renderer, -32.087955, 42.40651);
            rr_renderer_line_to(renderer, -55.971649, 5.870329999999996);
            rr_renderer_line_to(renderer, -40.746397, -41.542750000000005);
            rr_renderer_line_to(renderer, 11.016039, -54.156981);
            rr_renderer_line_to(renderer, 57.558443, -18.488463000000003);
            rr_renderer_line_to(renderer, 51.468743999999994, 28.052937);
            rr_renderer_line_to(renderer, 14.930558999999995, 54.15308);
            rr_renderer_fill(renderer);
            rr_renderer_set_fill(renderer, 0xff9a8d6d);
            rr_renderer_begin_path(renderer);
            rr_renderer_move_to(renderer, -38.273388, -7.077699999999993);
            rr_renderer_line_to(renderer, -19.242541999999997, 10.284086000000006);
            rr_renderer_line_to(renderer, -8.558303999999996, 34.657049);
            rr_renderer_line_to(renderer, 19.487289000000004, 33.98933965);
            rr_renderer_line_to(renderer, 38.184494, 8.280949649999997);
            rr_renderer_line_to(renderer, 31.172882, -23.437697350000004);
            rr_renderer_line_to(renderer, 3.4613569999999996, -37.460494350000005);
            rr_renderer_line_to(renderer, -24.250591, -29.781169350000006);
            rr_renderer_fill(renderer);
            rr_renderer_set_fill(renderer, 0xff84785c);
            rr_renderer_begin_path(renderer);
            rr_renderer_move_to(renderer, 8.767579999999995, -10.992503999999997);
            rr_renderer_bezier_curve_to(renderer, 16.891473999999995, -8.952628999999996, 22.587502999999995, -1.6495279999999966, 22.587502999999995, 6.726547000000004);
            rr_renderer_line_to(renderer, 13.452958999999995, 6.726547000000004);
            rr_renderer_bezier_curve_to(renderer, 13.452958999999995, 2.5385053000000033, 10.604936499999994, -1.113044999999996, 6.542993499999994, -2.1329809999999956);
            rr_renderer_fill(renderer);
            rr_renderer_set_fill(renderer, 0xff84785c);
            rr_renderer_begin_path(renderer);
            rr_renderer_move_to(renderer, 22.587554999999995, 6.726519999999994);
            rr_renderer_bezier_curve_to(renderer, 22.587554999999995, 14.644229399999993, 16.766074999999994, 21.357310999999996, 8.928084999999994, 22.478030999999994);
            rr_renderer_line_to(renderer, 7.629531499999994, 13.396342999999995);
            rr_renderer_bezier_curve_to(renderer, 10.948455499999994, 12.921787029999994, 13.413505199999994, 10.079196699999994, 13.413505199999994, 6.7265202999999945);
            rr_renderer_fill(renderer);
            rr_renderer_set_fill(renderer, 0xff84785c);
            rr_renderer_begin_path(renderer);
            rr_renderer_move_to(renderer, -10.352215000000001, -6.861750000000001);
            rr_renderer_bezier_curve_to(renderer, -4.896103000000001, -11.068564, 2.1702879999999993, -12.581202000000001, 8.870398999999999, -10.976561);
            rr_renderer_line_to(renderer, 6.732779999999999, -2.051012);
            rr_renderer_bezier_curve_to(renderer, 2.731070999999999, -3.0094013, -1.4894030000000003, -2.1059589, -4.7481160000000004, 0.40659899999999993);
            rr_renderer_fill(renderer);
            rr_renderer_set_fill(renderer, 0xff84785c);
            rr_renderer_begin_path(renderer);
            rr_renderer_move_to(renderer, -21.80334, 11.219260000000006);
            rr_renderer_bezier_curve_to(renderer, -20.073027699999997, 3.9815050000000056, -15.927668599999999, -2.450424999999994, -10.050890999999998, -7.015793999999996);
            rr_renderer_line_to(renderer, -4.425642999999998, 0.22531780000000357);
            rr_renderer_bezier_curve_to(renderer, -8.655863999999998, 3.5115651000000034, -11.639776999999999, 8.141386800000003, -12.885286999999998, 13.351271800000003);
            rr_renderer_fill(renderer);
            rr_renderer_set_fill(renderer, 0xff84785c);
            rr_renderer_begin_path(renderer);
            rr_renderer_move_to(renderer, 3.5600900000000024, 17.925064000000006);
            rr_renderer_bezier_curve_to(renderer, 3.5600900000000024, 15.415077100000007, 5.5948420000000025, 13.380333000000007, 8.104821000000001, 13.380333000000007);
            rr_renderer_bezier_curve_to(renderer, 9.310158500000002, 13.380333000000007, 10.4661339, 13.859153800000007, 11.318436400000001, 14.711448700000007);
            rr_renderer_bezier_curve_to(renderer, 12.17073895, 15.563751250000006, 12.649552100000001, 16.719726700000006, 12.649552100000001, 17.925064100000007);
            rr_renderer_bezier_curve_to(renderer, 12.649552100000001, 20.43505100000001, 10.614807800000001, 22.469795100000006, 8.104821100000002, 22.469795100000006);
            rr_renderer_bezier_curve_to(renderer, 5.594841900000002, 22.469795100000006, 3.5600901000000027, 20.435050800000006, 3.5600901000000027, 17.925064100000007);
            rr_renderer_fill(renderer);
            rr_renderer_set_fill(renderer, 0xff84785c);
            rr_renderer_begin_path(renderer);
            rr_renderer_move_to(renderer, -12.759407000000003, 35.158649999999994);
            rr_renderer_bezier_curve_to(renderer, -20.420742000000004, 29.740780399999995, -23.978031, 20.180744999999995, -21.721840000000004, 11.072559999999996);
            rr_renderer_line_to(renderer, -12.813034000000004, 13.279362399999997);
            rr_renderer_bezier_curve_to(renderer, -14.160564400000004, 18.719319099999996, -12.035938200000004, 24.429142399999996, -7.460128700000004, 27.665020399999996);
            rr_renderer_fill(renderer);
            rr_renderer_set_fill(renderer, 0xff84785c);
            rr_renderer_begin_path(renderer);
            rr_renderer_move_to(renderer, 24.802986000000004, 35.103095999999994);
            rr_renderer_bezier_curve_to(renderer, 13.521232000000005, 43.0210495, -1.512176999999994, 43.02200299999999, -12.794936999999997, 35.105491629899994);
            rr_renderer_line_to(renderer, -7.528319999999997, 27.599411029899994);
            rr_renderer_bezier_curve_to(renderer, 0.5932390000000023, 33.29787442989999, 11.414590000000004, 33.29718802989999, 19.535416, 27.59768678669999);
            rr_renderer_fill(renderer);
            rr_renderer_set_fill(renderer, 0xff84785c);
            rr_renderer_begin_path(renderer);
            rr_renderer_move_to(renderer, -41.897999, -10.055163999999998);
            rr_renderer_bezier_curve_to(renderer, -37.139309, -28.288321999999997, -20.984538999999998, -41.241562, -2.152968999999999, -41.923576);
            rr_renderer_bezier_curve_to(renderer, 16.678604, -42.6055924, 33.728066, -30.854895999999997, 39.793244, -13.013739999999999);
            rr_renderer_bezier_curve_to(renderer, 45.8584143, 4.827416000000003, 39.50320494, 24.53463, 24.157731000000002, 35.471245);
            rr_renderer_line_to(renderer, 18.825059000000003, 27.988823000000004);
            rr_renderer_bezier_curve_to(renderer, 30.866349000000003, 19.407082000000003, 35.853159000000005, 3.9432230000000033, 31.093934000000004, -10.056373999999998);
            rr_renderer_bezier_curve_to(renderer, 26.334710000000005, -24.055972999999998, 12.956338000000006, -33.276509, -1.8204179999999965, -32.741344);
            rr_renderer_bezier_curve_to(renderer, -16.597177999999996, -32.2061801, -29.273500999999996, -22.042033999999997, -33.007548, -7.734839999999998);
            rr_renderer_fill(renderer);
            rr_renderer_set_fill(renderer, 0xff84785c);
            rr_renderer_begin_path(renderer);
            rr_renderer_move_to(renderer, -17.421856, 13.732039999999998);
            rr_renderer_bezier_curve_to(renderer, -29.242095999999997, 13.711402487999997, -39.475696, 5.5158609999999975, -42.078629, -6.0142440000000015);
            rr_renderer_line_to(renderer, -32.931354999999996, -8.079250300000002);
            rr_renderer_bezier_curve_to(renderer, -31.292343599999995, -0.818969700000002, -24.848449999999996, 4.341598699999999, -17.405479999999997, 4.3545916999999985);
            rr_renderer_fill(renderer);
            rr_renderer_set_fill(renderer, 0xff84785c);
            rr_renderer_begin_path(renderer);
            rr_renderer_move_to(renderer, -42.479417999999995, -7.999595999999997);
            rr_renderer_bezier_curve_to(renderer, -42.479417999999995, -10.509578999999997, -40.444671799999995, -12.544323299999997, -37.93468899999999, -12.544323299999997);
            rr_renderer_bezier_curve_to(renderer, -36.72935149999999, -12.544323299999997, -35.57337999999999, -12.065506299999997, -34.72107739999999, -11.213203799999997);
            rr_renderer_bezier_curve_to(renderer, -33.868774849999994, -10.360901249999998, -33.38995789999999, -9.204929799999997, -33.38995789999999, -7.999595999999997);
            rr_renderer_bezier_curve_to(renderer, -33.38995789999999, -5.489609099999997, -35.42470219999999, -3.454864999999997, -37.93468889999999, -3.454864999999997);
            rr_renderer_bezier_curve_to(renderer, -40.44467189999999, -3.454864999999997, -42.47941789999999, -5.489609299999997, -42.47941789999999, -7.999595999999997);
            rr_renderer_fill(renderer);
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
        case rr_petal_id_shell:
            rr_renderer_scale(renderer, 0.15f);
            rr_renderer_set_fill(renderer, 0xffd2c6a7);
            rr_renderer_begin_path(renderer);
            rr_renderer_move_to(renderer, -64.4642935, -11.540416999999998);
            rr_renderer_line_to(renderer, -32.453990499999996, 17.657959);
            rr_renderer_line_to(renderer, -14.482860499999997, 58.647476);
            rr_renderer_line_to(renderer, 32.690445499999996, 57.5245359);
            rr_renderer_line_to(renderer, 64.1395575, 14.2891689);
            rr_renderer_line_to(renderer, 52.345871499999994, -39.0540311);
            rr_renderer_line_to(renderer, 5.7344744999999975, -62.637027100000005);
            rr_renderer_line_to(renderer, -40.8776395, -49.7222371);
            rr_renderer_fill(renderer);
            rr_renderer_set_fill(renderer, 0xffaa9e80);
            rr_renderer_begin_path(renderer);
            rr_renderer_move_to(renderer, 14.666939999999997, -18.123779999999996);
            rr_renderer_bezier_curve_to(renderer, 28.332031999999998, -14.693600399999996, 37.91344599999999, -2.4112709999999957, 37.91344599999999, 11.675712000000004);
            rr_renderer_line_to(renderer, 22.551316999999994, 11.675712000000004);
            rr_renderer_bezier_curve_to(renderer, 22.551316999999994, 4.632011000000004, 17.759583999999993, -1.5092779999999966, 10.925713999999994, -3.2241749999999954);
            rr_renderer_fill(renderer);
            rr_renderer_set_fill(renderer, 0xffaa9e80);
            rr_renderer_begin_path(renderer);
            rr_renderer_move_to(renderer, 37.91353599999999, 11.675659999999993);
            rr_renderer_bezier_curve_to(renderer, 37.91353599999999, 24.991577999999993, 28.121360999999993, 36.28149499999999, 14.937423999999993, 38.16601599999999);
            rr_renderer_line_to(renderer, 12.753570899999993, 22.89278449999999);
            rr_renderer_bezier_curve_to(renderer, 18.337509499999992, 22.09494819999999, 22.484962899999992, 17.31427799999999, 22.484962899999992, 11.675659499999991);
            rr_renderer_fill(renderer);
            rr_renderer_set_fill(renderer, 0xffaa9e80);
            rr_renderer_begin_path(renderer);
            rr_renderer_move_to(renderer, -17.491107999999997, -11.177169999999997);
            rr_renderer_bezier_curve_to(renderer, -8.313674999999996, -18.251747299999998, 3.572136000000004, -20.795345499999996, 14.841759000000003, -18.0965006);
            rr_renderer_line_to(renderer, 11.245941400000003, -3.086029599999998);
            rr_renderer_bezier_curve_to(renderer, 4.514808900000003, -4.698204599999998, -2.5843425999999976, -3.179268429999998, -8.065818599999997, 1.0459131000000017);
            rr_renderer_fill(renderer);
            rr_renderer_set_fill(renderer, 0xffaa9e80);
            rr_renderer_begin_path(renderer);
            rr_renderer_move_to(renderer, -36.75228, 19.22864);
            rr_renderer_bezier_curve_to(renderer, -33.8411815, 7.056383999999998, -26.867835, -3.760389, -16.982295, -11.437769000000003);
            rr_renderer_line_to(renderer, -7.521613, 0.7402129999999971);
            rr_renderer_bezier_curve_to(renderer, -14.6380604, 6.266473399999997, -19.658175, 14.052598999999997, -21.754023, 22.814484999999998);
            rr_renderer_fill(renderer);
            rr_renderer_set_fill(renderer, 0xffaa9e80);
            rr_renderer_begin_path(renderer);
            rr_renderer_move_to(renderer, 5.908919999999995, 30.508939999999996);
            rr_renderer_bezier_curve_to(renderer, 5.908919999999995, 26.287740999999997, 9.331405399999994, 22.865781999999996, 13.553260499999995, 22.865781999999996);
            rr_renderer_bezier_curve_to(renderer, 15.580657699999994, 22.865781999999996, 17.525031699999996, 23.671041699999996, 18.958617899999993, 25.104414199999997);
            rr_renderer_bezier_curve_to(renderer, 20.392211699999994, 26.537779099999998, 21.19759339999999, 28.481847999999996, 21.19759339999999, 30.508939999999996);
            rr_renderer_bezier_curve_to(renderer, 21.19759339999999, 34.7301314, 17.775107999999992, 38.1520903, 13.553260399999992, 38.1520903);
            rr_renderer_bezier_curve_to(renderer, 9.331405399999992, 38.1520903, 5.908919899999992, 34.7301313, 5.908919899999992, 30.508939999999996);
            rr_renderer_fill(renderer);
            rr_renderer_set_fill(renderer, 0xffaa9e80);
            rr_renderer_begin_path(renderer);
            rr_renderer_move_to(renderer, -21.540672, 59.49185);
            rr_renderer_bezier_curve_to(renderer, -34.427086, 50.380468, -40.41064, 34.303090999999995, -36.616043000000005, 18.985425999999997);
            rr_renderer_line_to(renderer, -21.632152000000005, 22.696187999999996);
            rr_renderer_bezier_curve_to(renderer, -23.898250000000004, 31.844838999999993, -20.324126600000007, 41.447286999999996, -12.627242500000005, 46.88931099999999);
            rr_renderer_fill(renderer);
            rr_renderer_set_fill(renderer, 0xffaa9e80);
            rr_renderer_begin_path(renderer);
            rr_renderer_move_to(renderer, 41.639219999999995, 59.398799999999994);
            rr_renderer_bezier_curve_to(renderer, 22.663801999999993, 72.71392449999999, -2.6212700000000027, 72.71586199999999, -21.598720000000007, 59.40363703599999);
            rr_renderer_line_to(renderer, -12.741336000000008, 46.78076603599999);
            rr_renderer_bezier_curve_to(renderer, 0.9191829999999932, 56.36262203599999, 19.120033999999993, 56.36088203599999, 32.77927399999999, 46.776386763499985);
            rr_renderer_fill(renderer);
            rr_renderer_set_fill(renderer, 0xffaa9e80);
            rr_renderer_begin_path(renderer);
            rr_renderer_move_to(renderer, -70.5519133, -16.549754999999998);
            rr_renderer_bezier_curve_to(renderer, -62.546451299999994, -47.213578999999996, -35.3725033, -68.996895, -3.6970132999999947, -70.142319);
            rr_renderer_bezier_curve_to(renderer, 27.978477700000006, -71.2877429, 56.6552737, -51.524054, 66.8553017, -21.518566);
            rr_renderer_bezier_curve_to(renderer, 77.0553137, 8.486924000000002, 66.36335834, 41.629418, 40.550316699999996, 60.02049400000001);
            rr_renderer_line_to(renderer, 31.582039699999996, 47.436845000000005);
            rr_renderer_bezier_curve_to(renderer, 51.838219699999996, 33.006105000000005, 60.22885169999999, 6.999932000000008, 52.22513669999999, -16.544977999999993);
            rr_renderer_bezier_curve_to(renderer, 44.221421199999995, -40.08988699999999, 21.718514699999993, -55.59844799999999, -3.1377483000000055, -54.699991999999995);
            rr_renderer_bezier_curve_to(renderer, -27.994006300000006, -53.801537329999995, -49.318038300000005, -36.708805999999996, -55.600298300000006, -12.647516999999993);
            rr_renderer_fill(renderer);
            rr_renderer_set_fill(renderer, 0xffaa9e80);
            rr_renderer_begin_path(renderer);
            rr_renderer_move_to(renderer, -29.381805, 23.457279999999997);
            rr_renderer_bezier_curve_to(renderer, -49.26428, 23.423207123999997, -66.47819899999999, 9.640056999999997, -70.856449, -9.75139);
            rr_renderer_line_to(renderer, -55.472629, -13.2237106);
            rr_renderer_bezier_curve_to(renderer, -52.7157282, -1.0130936000000013, -41.875524, 7.665792400000001, -29.354768999999997, 7.6867734);
            rr_renderer_fill(renderer);
            rr_renderer_set_fill(renderer, 0xffaa9e80);
            rr_renderer_begin_path(renderer);
            rr_renderer_move_to(renderer, -71.5305585, -13.090139999999998);
            rr_renderer_bezier_curve_to(renderer, -71.5305585, -17.311338999999997, -68.1080717, -20.733293999999997, -63.8862208, -20.733293999999997);
            rr_renderer_bezier_curve_to(renderer, -61.858816, -20.733293999999997, -59.9144486, -19.928034299999997, -58.480857799999995, -18.494665599999998);
            rr_renderer_bezier_curve_to(renderer, -57.04726599999999, -17.0612969, -56.24188229999999, -15.117231799999997, -56.24188229999999, -13.090139799999998);
            rr_renderer_bezier_curve_to(renderer, -56.24188229999999, -8.868944799999998, -59.66436959999999, -5.446989499999997, -63.88622089999999, -5.446989499999997);
            rr_renderer_bezier_curve_to(renderer, -68.10807189999998, -5.446989499999997, -71.53055859999999, -8.868944499999998, -71.53055859999999, -13.090139799999998);
            rr_renderer_fill(renderer);
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
            rr_renderer_scale(renderer, 0.2);
            rr_renderer_rotate(renderer, M_PI * 3/4);
            rr_renderer_set_fill(renderer, 0xff2e6513);
            rr_renderer_begin_path(renderer);
            rr_renderer_move_to(renderer, -42.501121999999995, 42.727806);
            rr_renderer_bezier_curve_to(renderer, -66.057271, 19.171661, -66.057271, -19.020404, -42.501121999999995, -42.576554);
            rr_renderer_bezier_curve_to(renderer, -31.189060999999995, -53.888615, -15.846611999999997, -60.243664, 0.15106200000000314, -60.243664);
            rr_renderer_bezier_curve_to(renderer, 16.148727, -60.243664, 31.491180000000004, -53.888615, 42.803238, -42.576554);
            rr_renderer_bezier_curve_to(renderer, 66.35939, -19.020405, 66.35939, 19.171661, 42.803238, 42.727806);
            rr_renderer_bezier_curve_to(renderer, 19.247093, 66.283951, -18.944972, 66.283951, -42.501122, 42.727806);
            rr_renderer_fill(renderer);
            rr_renderer_set_fill(renderer, 0xff2e6513);
            rr_renderer_begin_path(renderer);
            rr_renderer_move_to(renderer, -59.019598, -30.141710000000003);
            rr_renderer_bezier_curve_to(renderer, -67.0129223, -38.1350343, -67.0129223, -51.094772000000006, -59.019598, -59.088098);
            rr_renderer_bezier_curve_to(renderer, -55.1810684, -62.9266276, -49.974905, -65.0830907, -44.546404, -65.0830907);
            rr_renderer_bezier_curve_to(renderer, -39.117905, -65.0830907, -33.911739000000004, -62.9266276, -30.073212000000005, -59.088098);
            rr_renderer_bezier_curve_to(renderer, -22.079887700000004, -51.094773, -22.079887700000004, -38.135034000000005, -30.073212000000005, -30.141710000000003);
            rr_renderer_bezier_curve_to(renderer, -38.0665363, -22.148385700000002, -51.026274, -22.148385700000002, -59.019598, -30.141710000000003);
            rr_renderer_fill(renderer);
            rr_renderer_set_fill(renderer, 0xff2e6513);
            rr_renderer_begin_path(renderer);
            rr_renderer_move_to(renderer, 4.384704999999997, -59.335198);
            rr_renderer_line_to(renderer, -41.833085000000004, -64.8605724);
            rr_renderer_line_to(renderer, -29.526568000000005, -48.031442399999996);
            rr_renderer_fill(renderer);
            rr_renderer_set_fill(renderer, 0xff3d811c);
            rr_renderer_begin_path(renderer);
            rr_renderer_move_to(renderer, 0.057395999999997116, 42.798770000000005);
            rr_renderer_bezier_curve_to(renderer, -23.490276, 42.798770000000005, -42.579437000000006, 23.709613000000004, -42.579437000000006, 0.16194400000000542);
            rr_renderer_quadratic_curve_to(renderer, -42.579437000000006, -23.565029999999993, -47.396547000000005, -47.29200099999999);
            rr_renderer_quadratic_curve_to(renderer, -23.669577000000004, -42.47489099999999, 0.057392999999997585, -42.47489099999999);
            rr_renderer_bezier_curve_to(renderer, 23.605061, -42.47489099999999, 42.694226, -23.385731999999994, 42.694226, 0.16194200000001047);
            rr_renderer_bezier_curve_to(renderer, 42.694226, 23.709610000000012, 23.605061, 42.79876800000001, 0.057392999999997585, 42.79876800000001);
            rr_renderer_fill(renderer);
            rr_renderer_set_fill(renderer, 0xff2e6513);
            rr_renderer_begin_path(renderer);
            rr_renderer_move_to(renderer, -17.003666000000003, -3.6040650000000056);
            rr_renderer_bezier_curve_to(renderer, -20.724842100000004, -7.325241100000006, -20.724842100000004, -13.358456000000006, -17.003666000000003, -17.079632000000004);
            rr_renderer_bezier_curve_to(renderer, -15.216694000000002, -18.866604000000002, -12.793041300000002, -19.870518000000004, -10.265880700000004, -19.870518000000004);
            rr_renderer_bezier_curve_to(renderer, -7.738723900000004, -19.870518000000004, -5.315063700000004, -18.866604100000004, -3.5280917000000036, -17.079632000000004);
            rr_renderer_line_to(renderer, 59.091873299999996, 45.540338);
            rr_renderer_bezier_curve_to(renderer, 62.8130494, 49.2615141, 62.8130494, 55.294733, 59.091873299999996, 59.015901);
            rr_renderer_bezier_curve_to(renderer, 55.370697199999995, 62.7370771, 49.337478299999994, 62.7370771, 45.616302299999994, 59.015901);
            rr_renderer_fill(renderer);
            rr_renderer_set_fill(renderer, 0xff2e6513);
            rr_renderer_begin_path(renderer);
            rr_renderer_move_to(renderer, -59.43815, 4.487656000000001);
            rr_renderer_line_to(renderer, -64.9635244, -41.730134);
            rr_renderer_line_to(renderer, -48.134392399999996, -29.423617);
            rr_renderer_fill(renderer);
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
            rr_renderer_set_fill(renderer, 0xff6e6054);
            rr_renderer_begin_path(renderer);
            rr_renderer_move_to(renderer, -63.370872, -16.611559999999997);
            rr_renderer_bezier_curve_to(renderer, -53.27914, -50.393718, -43.088252, -80.596233, -33.689136, -102.36249);
            rr_renderer_bezier_curve_to(renderer, -24.290022999999998, -124.12874, -14.990065999999999, -141.61441, -6.976180999999997, -147.209067);
            rr_renderer_bezier_curve_to(renderer, 1.0377045000000038, -152.80372400000002, 6.578369000000004, -148.00084175, 14.394180000000002, -135.93043);
            rr_renderer_bezier_curve_to(renderer, 22.209999000000003, -123.860022, 31.805923000000003, -95.76133200000001, 39.918716, -74.78659999999999);
            rr_renderer_bezier_curve_to(renderer, 48.031509, -53.811876, 53.96882600000001, -35.11305399999999, 63.070953, -10.082059999999998);
            rr_renderer_bezier_curve_to(renderer, 72.173095, 14.948946000000003, 90.77198800000001, 54.72165, 94.53154, 75.3994);
            rr_renderer_bezier_curve_to(renderer, 98.2910767, 96.07715, 94.63145455, 105.970826, 85.62822, 113.984437);
            rr_renderer_bezier_curve_to(renderer, 76.625, 121.99807799999999, 53.769745, 122.78885, 40.512177, 123.481202);
            rr_renderer_bezier_curve_to(renderer, 27.254601, 124.1735848, 14.887970000000003, 117.499482, 6.082816999999999, 118.1386117);
            rr_renderer_bezier_curve_to(renderer, -2.722343500000001, 118.77774133999999, -3.810341000000001, 122.9627084, -12.318771000000002, 127.3159497);
            rr_renderer_bezier_curve_to(renderer, -20.8272015, 131.6691907, -32.501724, 141.1374527, -44.967771, 144.2581197);
            rr_renderer_bezier_curve_to(renderer, -57.43382, 147.3787862, -78.903089, 153.3612687, -87.115049, 146.0399801);
            rr_renderer_bezier_curve_to(renderer, -95.327005, 138.7187216, -98.196875, 127.4390891, -94.2395126, 100.33047710000001);
            rr_renderer_bezier_curve_to(renderer, -90.2821499, 73.22189510000001, -73.4625996, 17.170607100000012, -63.370873599999996, -16.611552899999992);
            rr_renderer_fill(renderer);
            rr_renderer_set_fill(renderer, 0xff7d6e62);
            rr_renderer_begin_path(renderer);
            rr_renderer_move_to(renderer, 77.90176, 96.0145);
            rr_renderer_bezier_curve_to(renderer, 85.8241996, 79.36882399999999, 52.18415399999999, 17.157809999999998, 40.005306, -19.072019999999995);
            rr_renderer_bezier_curve_to(renderer, 27.826457999999995, -55.301832999999995, 11.814341999999996, -108.43795999999999, 4.828662999999999, -121.36443);
            rr_renderer_bezier_curve_to(renderer, -2.1570243000000016, -134.290902, 0.1508522999999986, -130.325257, -1.9088020000000014, -96.630848);
            rr_renderer_bezier_curve_to(renderer, -3.9684562000000017, -62.936443, -20.831028, 48.694472000000005, -7.5292625000000015, 80.802012);
            rr_renderer_bezier_curve_to(renderer, 5.772495499999998, 112.909572, 69.9793375, 112.66015100000001, 77.9017575, 96.014491);
            rr_renderer_fill(renderer);
            rr_renderer_set_fill(renderer, 0xff938479);
            rr_renderer_begin_path(renderer);
            rr_renderer_move_to(renderer, -76.42511, 127.36455999999998);
            rr_renderer_bezier_curve_to(renderer, -84.264208, 111.31167299999998, -52.726380000000006, 22.38187999999998, -40.950596000000004, -19.07244000000003);
            rr_renderer_bezier_curve_to(renderer, -29.174812000000003, -60.526748000000026, -13.016129000000003, -108.17184000000003, -5.770401000000007, -121.36131000000003);
            rr_renderer_bezier_curve_to(renderer, 1.4753264999999933, -134.55078200000003, 0.5480422999999934, -131.31029600000002, 2.523772999999993, -98.20925600000004);
            rr_renderer_bezier_curve_to(renderer, 4.4995038999999935, -65.10822000000005, 19.242132999999995, 39.64929399999997, 6.083991799999993, 77.24490399999996);
            rr_renderer_bezier_curve_to(renderer, -7.0741582000000065, 114.84053099999997, -68.58601420000001, 143.41743399999996, -76.42510820000001, 127.36454799999996);
            rr_renderer_fill(renderer);
            break;
        case rr_petal_id_lightning:
            rr_renderer_scale(renderer, 0.18f);
            rr_renderer_set_fill(renderer, 0xffcbdce8);
            rr_renderer_begin_path(renderer);
            rr_renderer_move_to(renderer, -71.9941265094, 13.193855);
            rr_renderer_line_to(renderer, -41.797648509400005, 3.6378629999999994);
            rr_renderer_line_to(renderer, -43.326140509400005, 20.456138);
            rr_renderer_fill(renderer);
            rr_renderer_set_fill(renderer, 0xffcbdce8);
            rr_renderer_begin_path(renderer);
            rr_renderer_move_to(renderer, 71.61339000000001, -17.582625999999998);
            rr_renderer_line_to(renderer, 55.94245300000001, -16.8183819);
            rr_renderer_line_to(renderer, 62.057390000000005, -1.9107208999999994);
            rr_renderer_fill(renderer);
            rr_renderer_set_fill(renderer, 0xffcbdce8);
            rr_renderer_begin_path(renderer);
            rr_renderer_move_to(renderer, -6.386949999999999, 66.1978);
            rr_renderer_line_to(renderer, 16.475103, 53.141289);
            rr_renderer_line_to(renderer, 39.070066, 47.3831255);
            rr_renderer_line_to(renderer, 58.991147999999995, 24.9490055);
            rr_renderer_line_to(renderer, 2.1591479999999947, 40.3323745);
            rr_renderer_fill(renderer);
            rr_renderer_set_fill(renderer, 0xffcbdce8);
            rr_renderer_begin_path(renderer);
            rr_renderer_move_to(renderer, 46.55997000000001, -66.5079975);
            rr_renderer_line_to(renderer, 24.39002500000001, -49.6897175);
            rr_renderer_line_to(renderer, 39.67981200000001, -37.0757665);
            rr_renderer_fill(renderer);
            rr_renderer_set_fill(renderer, 0xffcbdce8);
            rr_renderer_begin_path(renderer);
            rr_renderer_move_to(renderer, 5.661609999999996, -44.721148);
            rr_renderer_line_to(renderer, 11.394428599999996, -56.56988);
            rr_renderer_line_to(renderer, -34.4729814, -62.303672299999995);
            rr_renderer_line_to(renderer, -57.4062014, -42.80955829999999);
            rr_renderer_line_to(renderer, -51.6733838, -2.2928382999999926);
            rr_renderer_line_to(renderer, -34.1532478, -29.997718299999992);
            rr_renderer_line_to(renderer, -18.802047800000004, -44.72114729999999);
            rr_renderer_fill(renderer);
            rr_renderer_set_fill(renderer, 0xff95a4ad);
            rr_renderer_begin_path(renderer);
            rr_renderer_move_to(renderer, -54.028504999999996, -16.2374);
            rr_renderer_line_to(renderer, -20.392922999999996, -49.10971);
            rr_renderer_line_to(renderer, 23.181754000000005, -59.047827999999996);
            rr_renderer_line_to(renderer, 66.755446, -32.673553);
            rr_renderer_line_to(renderer, 50.702391000000006, 19.691895000000002);
            rr_renderer_line_to(renderer, -4.338891999999994, 60.590729);
            rr_renderer_line_to(renderer, -49.82418199999999, 51.798989000000006);
            rr_renderer_line_to(renderer, -50.20630403999999, 16.633935000000008);
            rr_renderer_fill(renderer);
            rr_renderer_set_fill(renderer, 0xffabbbc5);
            rr_renderer_begin_path(renderer);
            rr_renderer_move_to(renderer, -36.828102, -12.033073000000002);
            rr_renderer_line_to(renderer, -11.730820000000001, -35.288951);
            rr_renderer_line_to(renderer, 19.363449, -42.3816195);
            rr_renderer_line_to(renderer, 45.350723, -25.7933955);
            rr_renderer_line_to(renderer, 35.795707, 11.665367499999999);
            rr_renderer_line_to(renderer, -8.543213000000002, 43.3903355);
            rr_renderer_line_to(renderer, -33.388023000000004, 39.1860125);
            rr_renderer_line_to(renderer, -33.005900960000005, 13.958099499999996);
            rr_renderer_fill(renderer);
            rr_renderer_set_fill(renderer, 0xffe5f5ff);
            rr_renderer_begin_path(renderer);
            rr_renderer_move_to(renderer, -14.979840000000003, 25.79611);
            rr_renderer_line_to(renderer, -6.5711910000000024, -12.426897000000004);
            rr_renderer_line_to(renderer, 28.593862999999995, -34.213747000000005);
            rr_renderer_line_to(renderer, 46.558507999999996, -66.321814);
            rr_renderer_line_to(renderer, 45.41213809999999, -22.365014000000002);
            rr_renderer_line_to(renderer, 7.18913109999999, 0.18705599999999833);
            rr_renderer_fill(renderer);
            rr_renderer_set_fill(renderer, 0xffe5f5ff);
            rr_renderer_begin_path(renderer);
            rr_renderer_move_to(renderer, 41.97304, 22.169846000000007);
            rr_renderer_line_to(renderer, 11.777536999999999, 20.64038130000001);
            rr_renderer_line_to(renderer, -12.365415000000002, 45.30094930000001);
            rr_renderer_line_to(renderer, -35.299608000000006, 54.85694130000002);
            rr_renderer_line_to(renderer, -20.010797000000004, 60.20861830000002);
            rr_renderer_line_to(renderer, -6.1880850000000045, 66.50779730000002);
            rr_renderer_line_to(renderer, 20.186182999999996, 33.63645130000002);
            rr_renderer_fill(renderer);
            rr_renderer_set_fill(renderer, 0xffe5f5ff);
            rr_renderer_begin_path(renderer);
            rr_renderer_move_to(renderer, -53.966604000000004, -15.671039999999998);
            rr_renderer_line_to(renderer, -36.001957000000004, -15.288917959999997);
            rr_renderer_line_to(renderer, -25.681717000000006, 5.351562040000003);
            rr_renderer_line_to(renderer, -21.095268300000008, -22.551200959999996);
            rr_renderer_line_to(renderer, -57.40668530000001, -43.19168096);
            rr_renderer_fill(renderer);
            rr_renderer_set_fill(renderer, 0xffe5f5ff);
            rr_renderer_begin_path(renderer);
            rr_renderer_move_to(renderer, 71.99600000000001, -17.582625999999998);
            rr_renderer_line_to(renderer, 52.58863600000001, -3.1448209999999968);
            rr_renderer_line_to(renderer, 30.924612000000007, 5.264809000000003);
            rr_renderer_line_to(renderer, 54.14247700000001, 9.371651000000004);
            rr_renderer_line_to(renderer, 65.99120900000001, -0.5664669999999958);
            rr_renderer_fill(renderer);
            rr_renderer_set_fill(renderer, 0xffe5f5ff);
            rr_renderer_begin_path(renderer);
            rr_renderer_move_to(renderer, -71.61102888, 13.193855);
            rr_renderer_line_to(renderer, -49.89436388000001, 30.013106999999998);
            rr_renderer_line_to(renderer, -23.83202788000001, 18.284278999999998);
            rr_renderer_line_to(renderer, -48.157264880000014, 16.9809648);
            rr_renderer_fill(renderer);
            break;
        case rr_petal_id_stick:
            rr_renderer_scale(renderer, 0.1);
            rr_renderer_set_fill(renderer, 0xff2f190b);
            rr_renderer_begin_path(renderer);
            rr_renderer_move_to(renderer, -58.631, -32.99924999999999);
            rr_renderer_bezier_curve_to(renderer, -77.817943, -21.22031899999999, -83.809772, 3.8741800000000097, -72.014125, 23.05084500000001);
            rr_renderer_line_to(renderer, -14.385780000000004, 116.73968500000001);
            rr_renderer_bezier_curve_to(renderer, -8.721305500000003, 125.94863900000001, 0.37136899999999606, 132.53341700000001, 10.891959999999997, 135.04541);
            rr_renderer_bezier_curve_to(renderer, 21.412551999999998, 137.557434, 32.499266999999996, 135.79089340000002, 41.713165, 130.1344603);
            rr_renderer_bezier_curve_to(renderer, 60.900099999999995, 118.3555293, 66.891937, 93.2610473, 55.096283, 74.08435030000001);
            rr_renderer_line_to(renderer, -2.532057000000002, -19.604479699999985);
            rr_renderer_bezier_curve_to(renderer, -14.327704000000002, -38.78114569999998, -39.444057, -44.778200699999985, -58.630997, -32.99925469999998);
            rr_renderer_fill(renderer);
            rr_renderer_set_fill(renderer, 0xff2f190b);
            rr_renderer_begin_path(renderer);
            rr_renderer_move_to(renderer, 56.71646000000001, -141.013626);
            rr_renderer_bezier_curve_to(renderer, 36.47241000000001, -146.608389, 15.535796000000012, -134.73007199999998, 9.95320800000001, -114.48266199999999);
            rr_renderer_line_to(renderer, -24.440451999999986, 10.259312000000008);
            rr_renderer_bezier_curve_to(renderer, -27.121306799999985, 19.98245700000001, -25.830489499999985, 30.37465300000001, -20.851973999999988, 39.14973900000001);
            rr_renderer_bezier_curve_to(renderer, -15.873458399999988, 47.92484000000001, -7.615057999999987, 54.36400300000001, 2.1064760000000113, 57.05069400000001);
            rr_renderer_bezier_curve_to(renderer, 22.350526000000013, 62.64546630000001, 43.28715600000001, 50.767140000000005, 48.86973600000002, 30.519734000000007);
            rr_renderer_line_to(renderer, 83.26339600000001, -94.22223599999998);
            rr_renderer_bezier_curve_to(renderer, 88.84597660000001, -114.46964199999998, 76.96050900000002, -135.41886599999998, 56.71646000000001, -141.013626);
            rr_renderer_fill(renderer);
            rr_renderer_set_fill(renderer, 0xff2f190b);
            rr_renderer_begin_path(renderer);
            rr_renderer_move_to(renderer, -16.603480000000005, -163.065623);
            rr_renderer_bezier_curve_to(renderer, -40.80465600000001, -159.33266279999998, -57.395278000000005, -136.687899, -53.659667000000006, -112.48712799999998);
            rr_renderer_line_to(renderer, -16.846049000000008, 126.006032);
            rr_renderer_bezier_curve_to(renderer, -15.052141800000008, 137.627645, -8.714961000000008, 148.061147, 0.771382999999993, 155.011312);
            rr_renderer_bezier_curve_to(renderer, 10.257733999999994, 161.9614463, 22.116177999999994, 164.85890700000002, 33.73798899999999, 163.066274);
            rr_renderer_bezier_curve_to(renderer, 57.93917599999999, 159.3333333, 74.529799, 136.688558, 70.79418899999999, 112.48778399999999);
            rr_renderer_line_to(renderer, 33.980558999999985, -126.005376);
            rr_renderer_bezier_curve_to(renderer, 30.244947999999987, -150.206146, 7.597708999999984, -166.798586, -16.603479000000014, -163.065626);
            rr_renderer_fill(renderer);
            rr_renderer_set_fill(renderer, 0xff4a2810);
            rr_renderer_begin_path(renderer);
            rr_renderer_move_to(renderer, 51.41475, -121.752613);
            rr_renderer_bezier_curve_to(renderer, 41.517243, -124.4845046, 31.28051, -118.6752357, 28.550355, -108.777252);
            rr_renderer_line_to(renderer, -5.569326999999998, 14.921368000000001);
            rr_renderer_bezier_curve_to(renderer, -6.880392699999998, 19.674557, -6.2496553699999975, 24.754208, -3.8158784999999975, 29.0428585);
            rr_renderer_bezier_curve_to(renderer, -1.3820939999999977, 33.3315245, 2.655366500000002, 36.477886500000004, 7.408318500000003, 37.7897915);
            rr_renderer_bezier_curve_to(renderer, 17.3058255, 40.5216793, 27.542565500000002, 34.7124142, 30.272713500000002, 24.8144195);
            rr_renderer_line_to(renderer, 64.39239549999999, -98.8842005);
            rr_renderer_bezier_curve_to(renderer, 67.12254379999999, -108.7821845, 61.312256299999994, -119.02072050000001, 51.41474949999999, -121.7526125);
            rr_renderer_fill(renderer);
            rr_renderer_set_fill(renderer, 0xff5b3316);
            rr_renderer_begin_path(renderer);
            rr_renderer_move_to(renderer, -13.790999999999997, -144.907005);
            rr_renderer_bezier_curve_to(renderer, -28.300482999999996, -142.6709706, -38.247882, -129.096386, -36.009142999999995, -114.587322);
            rr_renderer_line_to(renderer, 0.6015170000000083, 122.682928);
            rr_renderer_bezier_curve_to(renderer, 1.6765979000000082, 129.650427, 5.475555700000008, 135.905981, 11.162659000000009, 140.07349200000002);
            rr_renderer_bezier_curve_to(renderer, 16.84976230000001, 144.24097250000003, 23.959160000000008, 145.9790096, 30.92685700000001, 144.90521800000002);
            rr_renderer_bezier_curve_to(renderer, 45.43634000000001, 142.66919500000003, 55.38374300000001, 129.09461000000002, 53.14500400000001, 114.58551600000001);
            rr_renderer_line_to(renderer, 16.534340000000007, -122.68471399999999);
            rr_renderer_bezier_curve_to(renderer, 14.295601000000008, -137.19377799999998, 0.718483000000008, -147.143034, -13.790999999999993, -144.90699999999998);
            rr_renderer_fill(renderer);
            rr_renderer_set_fill(renderer, 0xff5b3316);
            rr_renderer_begin_path(renderer);
            rr_renderer_move_to(renderer, -49.23036, -17.70284000000001);
            rr_renderer_bezier_curve_to(renderer, -59.445932, -11.425099500000009, -62.633959, 1.9427599999999927, -56.351011199999995, 12.15513099999999);
            rr_renderer_line_to(renderer, 2.4387648000000084, 107.712671);
            rr_renderer_bezier_curve_to(renderer, 5.4559386000000085, 112.6168153, 10.298322800000008, 116.122522, 15.90063280000001, 117.458612);
            rr_renderer_bezier_curve_to(renderer, 21.502950800000008, 118.7946716, 27.40628580000001, 117.85161737, 32.31197880000001, 114.83693840000001);
            rr_renderer_bezier_curve_to(renderer, 42.52755480000001, 108.55922840000001, 45.715573800000016, 95.1913384, 39.43263000000001, 84.97896740000002);
            rr_renderer_line_to(renderer, -19.35714999999999, -10.57855859999998);
            rr_renderer_bezier_curve_to(renderer, -25.64009369999999, -20.79093059999998, -39.01478499999999, -23.98058159999998, -49.23035999999999, -17.702841599999978);
            rr_renderer_fill(renderer);
            break;
        case rr_petal_id_kelp:
            rr_renderer_scale(renderer, 0.2);
            rr_renderer_set_fill(renderer, 0xff6c9d44);
            rr_renderer_begin_path(renderer);
            rr_renderer_move_to(renderer, -43.727036, -12.215054000000002);
            rr_renderer_bezier_curve_to(renderer, -30.418445999999996, -25.535534000000002, -5.157815999999997, -17.956818000000002, 10.698577, -27.523148000000003);
            rr_renderer_bezier_curve_to(renderer, 26.554977, -37.089478, 41.632637, -65.552538, 51.411347, -69.613038);
            rr_renderer_bezier_curve_to(renderer, 61.190049, -73.673542, 69.54686, -67.9749317, 69.37082, -51.88617000000001);
            rr_renderer_bezier_curve_to(renderer, 69.19479460999999, -35.797408000000004, 63.972229999999996, 11.63877999999999, 50.355126, 26.919524999999993);
            rr_renderer_bezier_curve_to(renderer, 36.738022, 42.200278999999995, 5.064546, 32.48608399999999, -12.331821000000005, 39.798331999999995);
            rr_renderer_bezier_curve_to(renderer, -29.728183000000005, 47.11058, -44.55286100000001, 68.69279499999999, -54.023044000000006, 70.79302999999999);
            rr_renderer_bezier_curve_to(renderer, -63.493232000000006, 72.89326499999999, -70.868947, 66.23442099999998, -69.152946, 52.39973499999999);
            rr_renderer_bezier_curve_to(renderer, -67.4369443, 38.56505599999999, -57.035621, 1.1054309999999958, -43.727033, -12.215055000000007);
            rr_renderer_fill(renderer);
            rr_renderer_set_fill(renderer, 0xff7fb851);
            rr_renderer_begin_path(renderer);
            rr_renderer_move_to(renderer, -58.158388, 57.5796);
            rr_renderer_bezier_curve_to(renderer, -61.202148300000005, 52.790347, -47.394148, 9.71011, -34.349243, -2.444569999999999);
            rr_renderer_bezier_curve_to(renderer, -21.304340000000003, -14.599248, 4.988386999999996, -6.602414499999999, 20.111036999999996, -15.348462499999998);
            rr_renderer_bezier_curve_to(renderer, 35.233679499999994, -24.0945105, 52.921856999999996, -59.9925095, 56.386641, -54.9208425);
            rr_renderer_bezier_curve_to(renderer, 59.8514237, -49.8491795, 52.978605699999996, 1.5462215000000015, 40.89971799999999, 15.081522499999998);
            rr_renderer_bezier_curve_to(renderer, 28.820829999999994, 28.6168235, 0.4229949999999931, 19.207941499999997, -16.086686000000007, 26.290957);
            rr_renderer_bezier_curve_to(renderer, -32.59636800000001, 33.3739724, -55.11462900000001, 62.368860999999995, -58.15838600000001, 57.5796);
            rr_renderer_fill(renderer);
            rr_renderer_set_fill(renderer, 0xff6c9d44);
            rr_renderer_begin_path(renderer);
            rr_renderer_move_to(renderer, -60.191725, 46.69233);
            rr_renderer_bezier_curve_to(renderer, -55.528681, 37.063058, -39.873795, 13.016404000000001, -26.355711, 4.7503129999999985);
            rr_renderer_bezier_curve_to(renderer, -12.8376255, -3.515785000000001, 8.841608999999998, 2.5758209999999986, 20.916789, -2.9042204000000016);
            rr_renderer_bezier_curve_to(renderer, 32.991961, -8.3842657, 44.349315000000004, -29.6677854, 46.095347000000004, -28.129962400000004);
            rr_renderer_bezier_curve_to(renderer, 47.841379700000005, -26.592135900000002, 42.6592203, -1.317725400000004, 31.392985000000003, 6.322731599999997);
            rr_renderer_bezier_curve_to(renderer, 20.12675, 13.963196599999996, -7.214238999999999, 8.345612199999998, -21.502064999999995, 17.712814599999998);
            rr_renderer_bezier_curve_to(renderer, -35.789891999999995, 27.080009599999997, -47.88569799999999, 57.6960146, -54.333974999999995, 62.5259406);
            rr_renderer_bezier_curve_to(renderer, -60.7822506, 67.3558661, -64.854767, 56.3215949, -60.191722999999996, 46.6923296);
            rr_renderer_fill(renderer);
            break;
        case rr_petal_id_fish_egg:
            rr_renderer_scale(renderer, 0.12);
            rr_renderer_set_fill(renderer, 0xbfe55f1a);
            rr_renderer_begin_path(renderer);
            rr_renderer_move_to(renderer, -49.986475, -0.01755500000000154);
            rr_renderer_bezier_curve_to(renderer, -49.986475, -27.623764, -27.607224, -50.003017, -0.0010149999999953252, -50.003017);
            rr_renderer_bezier_curve_to(renderer, 13.255958000000005, -50.003017, 25.969955000000006, -44.7367073, 35.344047, -35.362612999999996);
            rr_renderer_bezier_curve_to(renderer, 44.718139, -25.988521, 49.98445100000001, -13.274523999999996, 49.98445100000001, -0.017552999999999486);
            rr_renderer_bezier_curve_to(renderer, 49.98445100000001, 27.588656, 27.605194000000008, 49.967907000000004, -0.0010149999999953252, 49.967907000000004);
            rr_renderer_bezier_curve_to(renderer, -27.607223999999995, 49.967907000000004, -49.986475, 27.588657000000005, -49.986475, -0.017552999999999486);
            rr_renderer_fill(renderer);
            rr_renderer_set_fill(renderer, 0xbfbf4a0d);
            rr_renderer_begin_path(renderer);
            rr_renderer_move_to(renderer, -69.4587798, -0.01755500000000154);
            rr_renderer_bezier_curve_to(renderer, -69.4587798, -38.378021000000004, -38.361476800000005, -69.475315, -0.001019800000008786, -69.475315);
            rr_renderer_bezier_curve_to(renderer, 18.42032919999999, -69.475315, 36.08718319999999, -62.157464, 49.11304019999999, -49.131606999999995);
            rr_renderer_bezier_curve_to(renderer, 62.13889619999999, -36.105748999999996, 69.4567522, -18.438893999999994, 69.4567522, -0.017546999999993318);
            rr_renderer_bezier_curve_to(renderer, 69.4567522, 38.34291900000001, 38.3594472, 69.440223, -0.0010177999999996246, 69.440223);
            rr_renderer_bezier_curve_to(renderer, -38.3614798, 69.440223, -69.4587778, 38.342918000000004, -69.4587778, -0.017546999999993318);
            rr_renderer_move_to(renderer, -49.81889779999999, -0.017546999999993318);
            rr_renderer_bezier_curve_to(renderer, -49.81889779999999, 27.496110000000005, -27.514671799999988, 49.80033900000001, -0.0010117999999863514, 49.80033900000001);
            rr_renderer_bezier_curve_to(renderer, 27.512652200000012, 49.80033900000001, 49.816874200000015, 27.496109000000008, 49.816874200000015, -0.017546999999993318);
            rr_renderer_bezier_curve_to(renderer, 49.816874200000015, -27.531206999999995, 27.512652200000016, -49.835432999999995, -0.0010117999999863514, -49.835432999999995);
            rr_renderer_bezier_curve_to(renderer, -27.514671799999988, -49.835432999999995, -49.81889779999999, -27.531204999999996, -49.81889779999999, -0.017546999999993318);
            rr_renderer_fill(renderer);
            rr_renderer_set_fill(renderer, 0xfff7a87f);
            rr_renderer_begin_path(renderer);
            rr_renderer_move_to(renderer, -57.759892, 0.0002599999999972624);
            rr_renderer_bezier_curve_to(renderer, -57.759892, -26.179225000000002, -40.152283, -49.085100000000004, -14.853222000000002, -55.817356000000004);
            rr_renderer_line_to(renderer, -10.289352500000003, -38.666836);
            rr_renderer_bezier_curve_to(renderer, -27.815022500000005, -34.003132, -40.0125185, -18.135319000000003, -40.0125185, 0.0002589999999997872);
            rr_renderer_fill(renderer);
            rr_renderer_set_fill(renderer, 0xfff7a87f);
            rr_renderer_begin_path(renderer);
            rr_renderer_move_to(renderer, -18.978218, -53.291197);
            rr_renderer_bezier_curve_to(renderer, -15.564906999999998, -56.704510899999995, -10.030829999999998, -56.704510899999995, -6.617515499999998, -53.291197);
            rr_renderer_bezier_curve_to(renderer, -4.9783858999999975, -51.6520655, -4.057533199999998, -49.4289286, -4.057533199999998, -47.1108457);
            rr_renderer_bezier_curve_to(renderer, -4.057533199999998, -44.7927647, -4.978385859999998, -42.569626, -6.617515499999998, -40.930496399999996);
            rr_renderer_bezier_curve_to(renderer, -10.030830299999998, -37.517181599999994, -15.564906999999998, -37.517181599999994, -18.978218, -40.930496399999996);
            rr_renderer_bezier_curve_to(renderer, -22.3915328, -44.3438094, -22.3915328, -49.8778844, -18.978218, -53.291197399999994);
            rr_renderer_fill(renderer);
            rr_renderer_set_fill(renderer, 0xfff7a87f);
            rr_renderer_begin_path(renderer);
            rr_renderer_move_to(renderer, -55.076077999999995, -6.242500000000007);
            rr_renderer_bezier_curve_to(renderer, -51.66276319999999, -9.655814800000007, -46.12868999999999, -9.655814800000007, -42.71537549999999, -6.242500000000007);
            rr_renderer_bezier_curve_to(renderer, -41.076245899999996, -4.603370400000006, -40.15539129999999, -2.3802335000000068, -40.15539129999999, -0.06214870000000694);
            rr_renderer_bezier_curve_to(renderer, -40.15539129999999, 2.2559282999999932, -41.076245869999994, 4.479065299999993, -42.71537549999999, 6.118202599999993);
            rr_renderer_bezier_curve_to(renderer, -46.128690299999995, 9.531509799999993, -51.6627635, 9.531509799999993, -55.076077999999995, 6.118202599999993);
            rr_renderer_bezier_curve_to(renderer, -58.489391, 2.7048877999999927, -58.489391, -2.829185400000007, -55.076077999999995, -6.242499900000007);
            rr_renderer_fill(renderer);
            break;
        case rr_petal_id_scales:
            rr_renderer_set_fill(renderer, 0xff2e445b);
            rr_renderer_scale(renderer, 0.2);
            rr_renderer_begin_path(renderer);
            rr_renderer_move_to(renderer, -37.79403, -28.584328);
            rr_renderer_bezier_curve_to(renderer, -37.79403, -49.430785, -20.877599, -66.33017799999999, -0.01012500000000216, -66.33017799999999);
            rr_renderer_bezier_curve_to(renderer, 10.010794999999998, -66.33017799999999, 19.621275999999998, -62.35339419999999, 26.707137, -55.27467399999999);
            rr_renderer_bezier_curve_to(renderer, 33.792990599999996, -48.19595599999999, 37.773787, -38.59515199999999, 37.773787, -28.58432999999999);
            rr_renderer_bezier_curve_to(renderer, 37.773787, -7.737871999999992, 20.857352, 9.161520000000007, -0.010125999999999635, 9.161520000000007);
            rr_renderer_bezier_curve_to(renderer, -20.8776, 9.161520000000007, -37.794031, -7.737870999999995, -37.794031, -28.58432999999999);
            rr_renderer_fill(renderer);
            rr_renderer_set_fill(renderer, 0xff2e445b);
            rr_renderer_begin_path(renderer);
            rr_renderer_move_to(renderer, -13.615459999999999, -58.409654);
            rr_renderer_bezier_curve_to(renderer, -13.615459999999999, -65.91374760000001, -7.523666999999999, -71.997018, -0.009063999999998629, -71.997018);
            rr_renderer_bezier_curve_to(renderer, 3.5995786000000014, -71.997018, 7.060417000000001, -70.56549629999999, 9.612106, -68.017371);
            rr_renderer_bezier_curve_to(renderer, 12.163802800000001, -65.4692462, 13.5973279, -62.013247, 13.5973279, -58.4096535);
            rr_renderer_bezier_curve_to(renderer, 13.5973279, -50.905559499999995, 7.5055387, -44.822290499999994, -0.009064099999999797, -44.822290499999994);
            rr_renderer_bezier_curve_to(renderer, -7.5236668, -44.822290499999994, -13.6154601, -50.905559499999995, -13.6154601, -58.40965349999999);
            rr_renderer_fill(renderer);
            rr_renderer_set_fill(renderer, 0xff395470);
            rr_renderer_begin_path(renderer);
            rr_renderer_move_to(renderer, -18.896698, -9.685139999999997);
            rr_renderer_bezier_curve_to(renderer, -29.333061, -20.121506999999998, -29.333061, -37.042199999999994, -18.896698, -47.478567);
            rr_renderer_quadratic_curve_to(renderer, -10.767521, -55.607742, 0.000014999999997655777, -61.09856);
            rr_renderer_quadratic_curve_to(renderer, 10.767546999999997, -55.607742, 18.896727999999996, -47.478567);
            rr_renderer_bezier_curve_to(renderer, 29.333090999999996, -37.042201999999996, 29.333090999999996, -20.121509, 18.896727999999996, -9.685139999999997);
            rr_renderer_bezier_curve_to(renderer, 8.460356999999997, 0.7512270000000036, -8.460332000000005, 0.7512270000000036, -18.896699000000005, -9.685139999999997);
            rr_renderer_fill(renderer);
            rr_renderer_set_fill(renderer, 0xff2e445b);
            rr_renderer_begin_path(renderer);
            rr_renderer_move_to(renderer, -9.203823, -68.404038);
            rr_renderer_line_to(renderer, -24.440384, -57.241047);
            rr_renderer_line_to(renderer, -9.703655000000001, -57.241047);
            rr_renderer_fill(renderer);
            rr_renderer_set_fill(renderer, 0xff2e445b);
            rr_renderer_begin_path(renderer);
            rr_renderer_move_to(renderer, 9.179400000000001, -68.404038);
            rr_renderer_line_to(renderer, 24.415957, -57.241047);
            rr_renderer_line_to(renderer, 9.679224499999998, -57.241047);
            rr_renderer_fill(renderer);
            rr_renderer_set_fill(renderer, 0xff2e445b);
            rr_renderer_begin_path(renderer);
            rr_renderer_move_to(renderer, -6.403496000000004, 2.806365999999997);
            rr_renderer_bezier_curve_to(renderer, -6.403496000000004, -18.040092, 10.512938999999996, -34.939484, 31.380416999999994, -34.939484);
            rr_renderer_bezier_curve_to(renderer, 41.40132899999999, -34.939484, 51.01181799999999, -30.9627002, 58.097671999999996, -23.88398);
            rr_renderer_bezier_curve_to(renderer, 65.183533, -16.80526, 69.164322, -7.204453000000001, 69.164322, 2.8063660000000006);
            rr_renderer_bezier_curve_to(renderer, 69.164322, 23.652824, 52.247887, 40.552216, 31.380417, 40.552216);
            rr_renderer_bezier_curve_to(renderer, 10.51294, 40.552216, -6.403495999999997, 23.652825, -6.403495999999997, 2.806366000000004);
            rr_renderer_fill(renderer);
            rr_renderer_set_fill(renderer, 0xff2e445b);
            rr_renderer_begin_path(renderer);
            rr_renderer_move_to(renderer, 17.775080000000003, -27.018963);
            rr_renderer_bezier_curve_to(renderer, 17.775080000000003, -34.523056, 23.866869200000004, -40.606325, 31.381472000000002, -40.606325);
            rr_renderer_bezier_curve_to(renderer, 34.990114600000005, -40.606325, 38.450953, -39.1748045, 41.00265, -36.626678299999995);
            rr_renderer_bezier_curve_to(renderer, 43.5543391, -34.078552099999996, 44.987864200000004, -30.622554599999994, 44.987864200000004, -27.018962299999995);
            rr_renderer_bezier_curve_to(renderer, 44.987864200000004, -19.514869299999994, 38.896075, -13.431598299999994, 31.381472200000005, -13.431598299999994);
            rr_renderer_bezier_curve_to(renderer, 23.866869500000004, -13.431598299999994, 17.775080200000005, -19.514869299999994, 17.775080200000005, -27.018962299999995);
            rr_renderer_fill(renderer);
            rr_renderer_set_fill(renderer, 0xff395470);
            rr_renderer_begin_path(renderer);
            rr_renderer_move_to(renderer, 12.493835000000004, 21.705550000000002);
            rr_renderer_bezier_curve_to(renderer, 2.057472000000004, 11.269187000000002, 2.057472000000004, -5.651505999999998, 12.493835000000004, -16.087872999999995);
            rr_renderer_quadratic_curve_to(renderer, 20.623016000000007, -24.217049999999993, 31.390548000000003, -29.707867999999994);
            rr_renderer_quadratic_curve_to(renderer, 42.158088000000006, -24.217049999999993, 50.287261, -16.087872999999995);
            rr_renderer_bezier_curve_to(renderer, 60.723632, -5.651505999999994, 60.723632, 11.269187000000006, 50.287261, 21.705550000000002);
            rr_renderer_bezier_curve_to(renderer, 39.850898, 32.141921, 22.930205, 32.141921, 12.493834, 21.705550000000002);
            rr_renderer_fill(renderer);
            rr_renderer_set_fill(renderer, 0xff2e445b);
            rr_renderer_begin_path(renderer);
            rr_renderer_move_to(renderer, 22.186713999999995, -37.013348);
            rr_renderer_line_to(renderer, 6.950148999999994, -25.850357000000002);
            rr_renderer_line_to(renderer, 21.686881499999995, -25.850357000000002);
            rr_renderer_fill(renderer);
            rr_renderer_set_fill(renderer, 0xff2e445b);
            rr_renderer_begin_path(renderer);
            rr_renderer_move_to(renderer, 40.56993, -37.013348);
            rr_renderer_line_to(renderer, 55.806487, -25.850357000000002);
            rr_renderer_line_to(renderer, 41.069762, -25.850357000000002);
            rr_renderer_fill(renderer);
            rr_renderer_set_fill(renderer, 0xff2e445b);
            rr_renderer_begin_path(renderer);
            rr_renderer_move_to(renderer, -69.184565, 2.806365999999997);
            rr_renderer_bezier_curve_to(renderer, -69.184565, -18.040092, -52.268134, -34.939484, -31.400655000000008, -34.939484);
            rr_renderer_bezier_curve_to(renderer, -21.379739000000008, -34.939484, -11.769254000000007, -30.9627002, -4.683393000000006, -23.88398);
            rr_renderer_bezier_curve_to(renderer, 2.402460599999994, -16.80526, 6.383256999999993, -7.204453000000001, 6.383256999999993, 2.8063660000000006);
            rr_renderer_bezier_curve_to(renderer, 6.383256999999993, 23.652824, -10.533178000000007, 40.552216, -31.400656000000005, 40.552216);
            rr_renderer_bezier_curve_to(renderer, -52.26813200000001, 40.552216, -69.184566, 23.652825, -69.184566, 2.806366000000004);
            rr_renderer_fill(renderer);
            rr_renderer_set_fill(renderer, 0xff2e445b);
            rr_renderer_begin_path(renderer);
            rr_renderer_move_to(renderer, -45.005993000000004, -27.018963);
            rr_renderer_bezier_curve_to(renderer, -45.005993000000004, -34.523056, -38.9142038, -40.606325, -31.399601000000004, -40.606325);
            rr_renderer_bezier_curve_to(renderer, -27.790958400000005, -40.606325, -24.330120000000004, -39.1748045, -21.778427000000004, -36.626678299999995);
            rr_renderer_bezier_curve_to(renderer, -19.226734000000004, -34.078552099999996, -17.793205100000005, -30.622554599999994, -17.793205100000005, -27.018962299999995);
            rr_renderer_bezier_curve_to(renderer, -17.793205100000005, -19.514869299999994, -23.884994300000006, -13.431598299999994, -31.399601100000005, -13.431598299999994);
            rr_renderer_bezier_curve_to(renderer, -38.9142038, -13.431598299999994, -45.005993100000005, -19.514869299999994, -45.005993100000005, -27.018962299999995);
            rr_renderer_fill(renderer);
            rr_renderer_set_fill(renderer, 0xff395470);
            rr_renderer_begin_path(renderer);
            rr_renderer_move_to(renderer, -50.287231, 21.705550000000002);
            rr_renderer_bezier_curve_to(renderer, -60.723597, 11.269187000000002, -60.723597, -5.651505999999998, -50.287231, -16.087872999999995);
            rr_renderer_quadratic_curve_to(renderer, -42.158056, -24.217049999999993, -31.390521, -29.707867999999994);
            rr_renderer_quadratic_curve_to(renderer, -20.622985, -24.217049999999993, -12.493808000000001, -16.087872999999995);
            rr_renderer_bezier_curve_to(renderer, -2.0574410000000007, -5.651505999999994, -2.0574410000000007, 11.269187000000006, -12.493808000000001, 21.705550000000002);
            rr_renderer_bezier_curve_to(renderer, -22.930175000000002, 32.141921, -39.850868000000006, 32.141921, -50.287231, 21.705550000000002);
            rr_renderer_fill(renderer);
            rr_renderer_set_fill(renderer, 0xff2e445b);
            rr_renderer_begin_path(renderer);
            rr_renderer_move_to(renderer, -40.594358, -37.013348);
            rr_renderer_line_to(renderer, -55.830919, -25.850357000000002);
            rr_renderer_line_to(renderer, -41.094188, -25.850357000000002);
            rr_renderer_fill(renderer);
            rr_renderer_set_fill(renderer, 0xff2e445b);
            rr_renderer_begin_path(renderer);
            rr_renderer_move_to(renderer, -22.21114, -37.013348);
            rr_renderer_line_to(renderer, -6.974579, -25.850357000000002);
            rr_renderer_line_to(renderer, -21.711308000000002, -25.850357000000002);
            rr_renderer_fill(renderer);
            rr_renderer_set_fill(renderer, 0xff2e445b);
            rr_renderer_begin_path(renderer);
            rr_renderer_move_to(renderer, -37.789383, 34.20237);
            rr_renderer_bezier_curve_to(renderer, -37.789383, 13.355912000000004, -20.872952, -3.5434799999999953, -0.005470000000002528, -3.5434799999999953);
            rr_renderer_bezier_curve_to(renderer, 10.015441999999997, -3.5434799999999953, 19.625922999999997, 0.4333038000000049, 26.711785, 7.512024000000006);
            rr_renderer_bezier_curve_to(renderer, 33.7976386, 14.590744000000004, 37.778435, 24.191551000000004, 37.778435, 34.20237000000001);
            rr_renderer_bezier_curve_to(renderer, 37.778435, 55.04882800000001, 20.862000000000002, 71.94821200000001, -0.005469999999995423, 71.94821200000001);
            rr_renderer_bezier_curve_to(renderer, -20.872950999999997, 71.94821200000001, -37.789382999999994, 55.048828000000015, -37.789382999999994, 34.20237000000001);
            rr_renderer_fill(renderer);
            rr_renderer_set_fill(renderer, 0xff2e445b);
            rr_renderer_begin_path(renderer);
            rr_renderer_move_to(renderer, -13.61081, 4.377044999999995);
            rr_renderer_bezier_curve_to(renderer, -13.61081, -3.1270520000000044, -7.519020800000001, -9.210323000000004, -0.004418000000001143, -9.210323000000004);
            rr_renderer_bezier_curve_to(renderer, 3.604224599999999, -9.210323000000004, 7.0650629999999985, -7.778800600000004, 9.616751999999998, -5.230674400000004);
            rr_renderer_bezier_curve_to(renderer, 12.168448799999998, -2.6825482000000043, 13.601973899999997, 0.7734530999999958, 13.601973899999997, 4.377044599999995);
            rr_renderer_bezier_curve_to(renderer, 13.601973899999997, 11.881133999999996, 7.510184699999997, 17.964408599999995, -0.004418100000002312, 17.964408599999995);
            rr_renderer_bezier_curve_to(renderer, -7.5190208000000025, 17.964408599999995, -13.610810100000002, 11.881133599999995, -13.610810100000002, 4.377044599999994);
            rr_renderer_fill(renderer);
            rr_renderer_set_fill(renderer, 0xff395470);
            rr_renderer_begin_path(renderer);
            rr_renderer_move_to(renderer, -18.892048000000003, 53.101555000000005);
            rr_renderer_bezier_curve_to(renderer, -29.328415000000003, 42.665192000000005, -29.328415000000003, 25.744499000000005, -18.892048000000003, 15.308135000000007);
            rr_renderer_quadratic_curve_to(renderer, -10.762875000000003, 7.178954000000006, 0.004661999999996169, 1.6881400000000077);
            rr_renderer_quadratic_curve_to(renderer, 10.772193999999995, 7.178954000000008, 18.901374999999994, 15.308135000000007);
            rr_renderer_bezier_curve_to(renderer, 29.337737999999995, 25.744498000000007, 29.337737999999995, 42.66519100000001, 18.901374999999994, 53.101555000000005);
            rr_renderer_bezier_curve_to(renderer, 8.465011999999994, 63.537918000000005, -8.455685000000006, 63.537918000000005, -18.892048000000003, 53.101555000000005);
            rr_renderer_fill(renderer);
            rr_renderer_set_fill(renderer, 0xff2e445b);
            rr_renderer_begin_path(renderer);
            rr_renderer_move_to(renderer, -9.199176999999999, -5.617339999999999);
            rr_renderer_line_to(renderer, -24.435738, 5.545647000000001);
            rr_renderer_line_to(renderer, -9.699009, 5.545647000000001);
            rr_renderer_fill(renderer);
            rr_renderer_set_fill(renderer, 0xff2e445b);
            rr_renderer_begin_path(renderer);
            rr_renderer_move_to(renderer, 9.184044, -5.617339999999999);
            rr_renderer_line_to(renderer, 24.420600999999998, 5.545647000000001);
            rr_renderer_line_to(renderer, 9.683875999999998, 5.545647000000001);
            rr_renderer_fill(renderer);
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
        if (id == rr_petal_id_shell)
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
        else if (id == rr_petal_id_beak)
            rr_renderer_rotate(renderer, 1.0f);
        else if (id == rr_petal_id_lightning)
            rr_renderer_rotate(renderer, 1.0f);
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
            if (id == rr_petal_id_shell)
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