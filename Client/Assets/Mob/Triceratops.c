#include <Client/Assets/Render.h>

#include <Client/Renderer/Renderer.h>

void rr_triceratops_body_draw(struct rr_renderer *renderer)
{
    rr_renderer_set_fill(renderer, 0xffa49b8a);
    rr_renderer_begin_path(renderer);
    rr_renderer_move_to(renderer, -77.37249800000001, -0.011020000000002028);
    rr_renderer_bezier_curve_to(renderer, -77.37249800000001,
                                -65.94679000000001, -42.735468000000004,
                                -119.3983, -0.008522000000013463, -119.3983);
    rr_renderer_bezier_curve_to(renderer, 20.509681999999987, -119.3983,
                                40.18751499999998, -106.82003,
                                54.696074999999986, -84.430576);
    rr_renderer_bezier_curve_to(renderer, 69.20463499999998, -62.041111,
                                77.35545299999998, -31.674486,
                                77.35545299999998, -0.011020000000002028);
    rr_renderer_bezier_curve_to(renderer, 77.35545299999998, 65.924756,
                                42.718428999999986, 119.37628,
                                -0.008523000000010938, 119.37628);
    rr_renderer_bezier_curve_to(renderer, -42.735467000000014, 119.37628,
                                -77.372499, 65.924757, -77.372499,
                                -0.011020000000002028);
    rr_renderer_fill(renderer);
    rr_renderer_set_fill(renderer, 0xff898276);
    rr_renderer_begin_path(renderer);
    rr_renderer_move_to(renderer, -87.799199, 0.0003700000000037562);
    rr_renderer_bezier_curve_to(renderer, -87.799199, -74.82816, -48.490674,
                                -135.48866999999998, -0.0011489999999980682,
                                -135.48866999999998);
    rr_renderer_bezier_curve_to(
        renderer, 23.284343000000003, -135.48866999999998, 45.616121,
        -121.21397399999998, 62.081441000000005, -95.80485499999998);
    rr_renderer_bezier_curve_to(renderer, 78.546773, -70.39572899999997,
                                87.796895, -35.93356299999998, 87.796895,
                                0.00036500000003059085);
    rr_renderer_bezier_curve_to(renderer, 87.796895, 74.82888500000003,
                                48.488378000000004, 135.48937500000005,
                                -0.0011449999999939564, 135.48937500000005);
    rr_renderer_bezier_curve_to(
        renderer, -48.49066499999999, 135.48937500000005, -87.799195,
        74.82888300000005, -87.799195, 0.0003650000000448017);
    rr_renderer_move_to(renderer, -67.87079299999999, 0.0003650000000448017);
    rr_renderer_bezier_curve_to(
        renderer, -67.87079299999999, 63.822737000000046, -37.48451899999999,
        115.56100500000005, -0.0011489999999980682, 115.56100500000005);
    rr_renderer_bezier_curve_to(renderer, 37.482227, 115.56100500000005,
                                67.868501, 63.82273900000005, 67.868501,
                                0.0003650000000448017);
    rr_renderer_bezier_curve_to(renderer, 67.868501, -63.82201499999996,
                                37.482225, -115.56027499999996,
                                -0.0011489999999980682, -115.56027499999996);
    rr_renderer_bezier_curve_to(renderer, -37.484519, -115.56027499999996,
                                -67.87079299999999, -63.822014999999965,
                                -67.87079299999999, 0.0003650000000448017);
    rr_renderer_fill(renderer);
    rr_renderer_set_fill(renderer, 0xff898276);
    rr_renderer_begin_path(renderer);
    rr_renderer_move_to(renderer, -8.944885, -50.678929999999994);
    rr_renderer_bezier_curve_to(renderer, -8.944885, -55.61905449999999,
                                -4.940124299999999, -59.62381499999999, 0,
                                -59.62381499999999);
    rr_renderer_bezier_curve_to(renderer, 2.3723297, -59.62381499999999,
                                4.647499, -58.68140929999999, 6.3249893,
                                -57.003918999999996);
    rr_renderer_bezier_curve_to(renderer, 8.0024795, -55.326428799999995,
                                8.9448853, -53.0512594, 8.9448853, -50.6789297);
    rr_renderer_line_to(renderer, 8.9448853, 90.80139030000001);
    rr_renderer_bezier_curve_to(renderer, 8.9448853, 95.7415148,
                                4.940124599999999, 99.74627530000001,
                                2.9999999995311555e-7, 99.74627530000001);
    rr_renderer_bezier_curve_to(renderer, -4.9401242, 99.74627530000001,
                                -8.9448847, 95.7415146, -8.9448847,
                                90.80139030000001);
    rr_renderer_fill(renderer);
}

void rr_triceratops_head_draw(struct rr_renderer *renderer)
{
    rr_renderer_set_fill(renderer, 0xff898276);
    rr_renderer_begin_path(renderer);
    rr_renderer_move_to(renderer, 85.07123999999999, 57.74476999999999);
    rr_renderer_bezier_curve_to(renderer, 78.11768779999998, 24.224414999999986,
                                55.30488299999999, 0.11377299999998769,
                                34.11744399999999, 3.8921549999999883);
    rr_renderer_bezier_curve_to(renderer, 23.94287599999999, 5.706592899999988,
                                15.511524999999992, 13.841251999999988,
                                10.67820399999999, 26.50658099999999);
    rr_renderer_bezier_curve_to(renderer, 5.84488339999999, 39.17190999999999,
                                5.0055049999999905, 55.33044899999999,
                                8.34472319999999, 71.427495);
    rr_renderer_bezier_curve_to(renderer, 15.29829069999999, 104.94784999999999,
                                38.11108019999999, 129.058475,
                                59.29853319999999, 125.28009499999999);
    rr_renderer_bezier_curve_to(renderer, 80.48597219999999, 121.50171369999998,
                                92.02480619999999, 91.26511099999999,
                                85.07123819999998, 57.744770999999986);
    rr_renderer_fill(renderer);
    rr_renderer_set_fill(renderer, 0xff898276);
    rr_renderer_begin_path(renderer);
    rr_renderer_move_to(renderer, 82.17663999999999, 91.2235);
    rr_renderer_bezier_curve_to(renderer, 80.4816479, 69.845036,
                                60.35075799999999, 53.756093, 37.21304699999999,
                                55.287877);
    rr_renderer_bezier_curve_to(renderer, 14.07534399999999, 56.8196458,
                                -3.307407000000012, 75.392079,
                                -1.6124150000000128, 96.770557);
    rr_renderer_bezier_curve_to(renderer, 0.0825846999999873, 118.149036,
                                20.213466999999987, 134.237964,
                                43.35116999999999, 132.706197);
    rr_renderer_bezier_curve_to(renderer, 66.48888, 131.1744282,
                                83.87163199999999, 112.601979,
                                82.17663999999999, 91.2235);
    rr_renderer_fill(renderer);
    rr_renderer_set_fill(renderer, 0xff898276);
    rr_renderer_begin_path(renderer);
    rr_renderer_move_to(renderer, -85.063058, 57.7457);
    rr_renderer_bezier_curve_to(renderer, -78.108797, 24.225344999999997,
                                -55.293721, 0.11470299999999867, -34.104158,
                                3.8930849999999992);
    rr_renderer_bezier_curve_to(renderer, -23.928575, 5.707522899999999,
                                -15.496384999999997, 13.842182,
                                -10.662575999999998, 26.507511);
    rr_renderer_bezier_curve_to(renderer, -5.828774699999998, 39.17284,
                                -4.989312499999998, 55.331379,
                                -8.328866299999998, 71.428425);
    rr_renderer_bezier_curve_to(renderer, -15.283128299999998,
                                104.94876500000001, -38.098203299999994,
                                129.059422, -59.2877663, 125.28104);
    rr_renderer_bezier_curve_to(renderer, -80.4773283, 121.5026587, -92.0173193,
                                91.266056, -85.0630573, 57.7457);
    rr_renderer_fill(renderer);
    rr_renderer_set_fill(renderer, 0xff898276);
    rr_renderer_begin_path(renderer);
    rr_renderer_move_to(renderer, -82.168158, 91.22446000000002);
    rr_renderer_bezier_curve_to(renderer, -80.4729933, 69.84596600000002,
                                -60.340096, 53.75703800000002,
                                -37.200072000000006, 55.28880600000002);
    rr_renderer_bezier_curve_to(
        renderer, -14.060050000000007, 56.820590000000024, 3.324440999999993,
        75.39302400000003, 1.6292809999999918, 96.77148600000002);
    rr_renderer_bezier_curve_to(
        renderer, -0.06588650000000817, 118.14999600000002, -20.19878300000001,
        134.23892400000003, -43.33880500000001, 132.70715600000003);
    rr_renderer_bezier_curve_to(renderer, -66.478829, 131.17535670000004,
                                -83.86332200000001, 112.60293800000002,
                                -82.168158, 91.22445900000002);
    rr_renderer_fill(renderer);
    rr_renderer_set_fill(renderer, 0xff898276);
    rr_renderer_begin_path(renderer);
    rr_renderer_move_to(renderer, -11.04446, 121.74630000000002);
    rr_renderer_bezier_curve_to(renderer, -11.04446, 107.57228900000001,
                                -6.168521600000001, 96.08196300000002,
                                -0.15375100000000153, 96.08196300000002);
    rr_renderer_bezier_curve_to(renderer, 5.8610194999999985, 96.08196300000002,
                                10.736957999999998, 107.57228900000001,
                                10.736957999999998, 121.74630000000002);
    rr_renderer_bezier_curve_to(renderer, 3.782406299999998, 114.72216060000002,
                                -4.089916000000002, 114.72216060000002,
                                -11.04446, 121.74630000000002);
    rr_renderer_fill(renderer);
    rr_renderer_set_fill(renderer, 0xff898276);
    rr_renderer_begin_path(renderer);
    rr_renderer_move_to(renderer, -31.295615999999995, -73.08517);
    rr_renderer_bezier_curve_to(
        renderer, -20.152755999999997, -68.97886960000001, -15.973868999999995,
        -52.473850000000006, -21.961806999999993, -36.220172000000005);
    rr_renderer_bezier_curve_to(
        renderer, -27.949744999999993, -19.966495000000005, -41.837002,
        -10.119098000000005, -52.97985799999999, -14.225391000000005);
    rr_renderer_bezier_curve_to(renderer, -40.255759999999995,
                                -30.771137000000007, -32.34726699999999,
                                -52.237971, -31.295615999999992, -73.085171);
    rr_renderer_fill(renderer);
    rr_renderer_set_fill(renderer, 0xff898276);
    rr_renderer_begin_path(renderer);
    rr_renderer_move_to(renderer, 31.302139999999994, -73.08515);
    rr_renderer_bezier_curve_to(renderer, 20.159279999999995, -68.9788573,
                                15.980392999999994, -52.473837,
                                21.968330999999992, -36.220152);
    rr_renderer_bezier_curve_to(renderer, 27.956268999999992, -19.966475,
                                41.843520999999996, -10.119077999999998,
                                52.98638999999999, -14.225370999999999);
    rr_renderer_bezier_curve_to(renderer, 40.262283999999994, -30.771117,
                                32.353790999999994, -52.237961,
                                31.302139999999994, -73.085151);
    rr_renderer_fill(renderer);
    rr_renderer_set_fill(renderer, 0xff898276);
    rr_renderer_begin_path(renderer);
    rr_renderer_move_to(renderer, -66.10990100000001, 26.25659999999999);
    rr_renderer_bezier_curve_to(renderer, -66.10990100000001,
                                -10.979362000000009, -36.48428700000001,
                                -41.16508, 0.06075899999999024, -41.16508);
    rr_renderer_bezier_curve_to(renderer, 17.61031199999999, -41.16508,
                                34.44108399999999, -34.0617475,
                                46.85049299999999, -21.417720000000003);
    rr_renderer_bezier_curve_to(
        renderer, 59.259885999999995, -8.773708000000003, 66.23142899999999,
        8.375263999999998, 66.23142899999999, 26.256595999999995);
    rr_renderer_bezier_curve_to(renderer, 66.23142899999999, 63.492557999999995,
                                36.605802999999995, 93.67827599999998,
                                0.06075899999999024, 93.67827599999998);
    rr_renderer_bezier_curve_to(renderer, -36.48428900000001, 93.67827599999998,
                                -66.10990100000001, 63.49256099999998,
                                -66.10990100000001, 26.256595999999988);
    rr_renderer_fill(renderer);
    rr_renderer_set_fill(renderer, 0xff898276);
    rr_renderer_begin_path(renderer);
    rr_renderer_move_to(renderer, -31.69878, -67.99976);
    rr_renderer_bezier_curve_to(renderer, -31.69878, -85.84107599999999,
                                -17.505657, -100.304318, 0.0024529999999991503,
                                -100.304318);
    rr_renderer_bezier_curve_to(renderer, 8.410136999999999, -100.304318,
                                16.473468999999998, -96.90081459999999,
                                22.418606, -90.842534);
    rr_renderer_bezier_curve_to(renderer, 28.363743, -84.784253, 31.703678,
                                -76.567464, 31.703678, -67.999761);
    rr_renderer_bezier_curve_to(renderer, 31.703678, -50.15844500000001,
                                17.510555, -35.69520300000001,
                                0.0024529999999991503, -35.69520300000001);
    rr_renderer_bezier_curve_to(renderer, -17.505657, -35.69520300000001,
                                -31.69878, -50.15844500000001, -31.69878,
                                -67.999761);
    rr_renderer_fill(renderer);
    rr_renderer_set_fill(renderer, 0xffa49b8a);
    rr_renderer_begin_path(renderer);
    rr_renderer_move_to(renderer, -18.061930000000004, -67.99976);
    rr_renderer_bezier_curve_to(renderer, -18.061930000000004,
                                -78.16260199999999, -9.974268000000004,
                                -86.401203, 0.002362999999995452, -86.401203);
    rr_renderer_bezier_curve_to(renderer, 4.7933099999999955, -86.401203,
                                9.388036499999995, -84.4624899,
                                12.775746999999996, -81.011547);
    rr_renderer_bezier_curve_to(renderer, 16.163457599999994, -77.560604,
                                18.066655999999995, -72.88013099999999,
                                18.066655999999995, -67.99976);
    rr_renderer_bezier_curve_to(
        renderer, 18.066655999999995, -57.83692599999999, 9.978993999999995,
        -49.598316999999994, 0.002362999999995452, -49.598316999999994);
    rr_renderer_bezier_curve_to(
        renderer, -9.974268000000004, -49.598316999999994, -18.061930000000004,
        -57.83692599999999, -18.061930000000004, -67.99976);
    rr_renderer_fill(renderer);
    rr_renderer_set_fill(renderer, 0xffa49b8a);
    rr_renderer_begin_path(renderer);
    rr_renderer_move_to(renderer, -52.983818, 26.256619999999998);
    rr_renderer_bezier_curve_to(renderer, -52.983818, -3.570376000000003,
                                -29.261077999999998, -27.749926000000002,
                                0.002402000000003568, -27.749926000000002);
    rr_renderer_bezier_curve_to(
        renderer, 14.055220000000004, -27.749926000000002, 27.532469000000003,
        -22.059969300000002, 37.469312, -11.931780000000002);
    rr_renderer_bezier_curve_to(renderer, 47.406156, -1.8035910000000008,
                                52.988614, 11.933195, 52.988614,
                                26.256619999999998);
    rr_renderer_bezier_curve_to(renderer, 52.988614, 56.083616,
                                29.265880999999997, 80.263166,
                                0.002400000000001512, 80.263166);
    rr_renderer_bezier_curve_to(renderer, -29.261080999999997, 80.263166,
                                -52.98382, 56.083616, -52.98382,
                                26.256619999999998);
    rr_renderer_fill(renderer);
    rr_renderer_set_fill(renderer, 0xffa49b8a);
    rr_renderer_begin_path(renderer);
    rr_renderer_move_to(renderer, -18.198710000000005, -68.24967);
    rr_renderer_bezier_curve_to(
        renderer, -8.555285000000005, -64.69219009999999, -5.591929000000006,
        -48.63207, -11.579867000000005, -32.37838599999999);
    rr_renderer_bezier_curve_to(
        renderer, -17.567805000000007, -16.124708999999992, -30.239527000000002,
        -5.832410999999993, -39.882952, -9.389890999999992);
    rr_renderer_bezier_curve_to(renderer, -27.300471, -25.649686999999993,
                                -19.174074000000005, -47.70799099999999,
                                -18.198710000000002, -68.24967099999999);
    rr_renderer_fill(renderer);
    rr_renderer_set_fill(renderer, 0xffa49b8a);
    rr_renderer_begin_path(renderer);
    rr_renderer_move_to(renderer, -18.198710000000005, -68.24967);
    rr_renderer_bezier_curve_to(
        renderer, -8.555285000000005, -64.69219009999999, -5.591929000000006,
        -48.63207, -11.579867000000005, -32.37838599999999);
    rr_renderer_bezier_curve_to(
        renderer, -17.567805000000007, -16.124708999999992, -30.239527000000002,
        -5.832410999999993, -39.882952, -9.389890999999992);
    rr_renderer_bezier_curve_to(renderer, -27.300471, -25.649686999999993,
                                -19.174074000000005, -47.70799099999999,
                                -18.198710000000002, -68.24967099999999);
    rr_renderer_fill(renderer);
    rr_renderer_set_fill(renderer, 0xffa49b8a);
    rr_renderer_begin_path(renderer);
    rr_renderer_move_to(renderer, 18.175299999999993, -68.24967);
    rr_renderer_bezier_curve_to(renderer, 8.531874999999992, -64.69219009999999,
                                5.568518999999993, -48.63207,
                                11.556464599999993, -32.37838599999999);
    rr_renderer_bezier_curve_to(
        renderer, 17.54440259999999, -16.124708999999992, 30.216124599999993,
        -5.832410999999993, 39.85954259999999, -9.389890999999992);
    rr_renderer_bezier_curve_to(
        renderer, 27.27706159999999, -25.649686999999993, 19.15067259999999,
        -47.70799099999999, 18.17530059999999, -68.24967099999999);
    rr_renderer_fill(renderer);
    rr_renderer_set_fill(renderer, 0xffa49b8a);
    rr_renderer_begin_path(renderer);
    rr_renderer_move_to(renderer, 18.175299999999993, -68.24967);
    rr_renderer_bezier_curve_to(renderer, 8.531874999999992, -64.69219009999999,
                                5.568518999999993, -48.63207,
                                11.556464599999993, -32.37838599999999);
    rr_renderer_bezier_curve_to(
        renderer, 17.54440259999999, -16.124708999999992, 30.216124599999993,
        -5.832410999999993, 39.85954259999999, -9.389890999999992);
    rr_renderer_bezier_curve_to(
        renderer, 27.27706159999999, -25.649686999999993, 19.15067259999999,
        -47.70799099999999, 18.17530059999999, -68.24967099999999);
    rr_renderer_fill(renderer);
    rr_renderer_set_fill(renderer, 0xffa49b8a);
    rr_renderer_begin_path(renderer);
    rr_renderer_move_to(renderer, -17.111850000000004, -24.004289999999997);
    rr_renderer_line_to(renderer, -6.4109070000000035, -59.40533);
    rr_renderer_line_to(renderer, 6.417080999999996, -59.40533);
    rr_renderer_line_to(renderer, 17.118024, -24.004289999999997);
    rr_renderer_fill(renderer);
    rr_renderer_set_fill(renderer, 0xffa49b8a);
    rr_renderer_begin_path(renderer);
    rr_renderer_move_to(renderer, -69.372675, 59.71969999999999);
    rr_renderer_bezier_curve_to(renderer, -62.826889, 33.86842699999999,
                                -46.394402, 15.395343999999987,
                                -32.669695000000004, 18.458879999999986);
    rr_renderer_bezier_curve_to(
        renderer, -26.078859400000006, 19.930056099999987, -21.006678000000004,
        26.272493999999988, -18.568964000000005, 36.09094499999999);
    rr_renderer_bezier_curve_to(
        renderer, -16.131258000000006, 45.90939599999999, -16.527711900000003,
        58.39958499999999, -19.671106300000005, 70.81379999999999);
    rr_renderer_bezier_curve_to(
        renderer, -26.216897900000006, 96.66507299999998, -42.6493813,
        115.13815599999998, -56.374090300000006, 112.07458799999998);
    rr_renderer_bezier_curve_to(
        renderer, -70.09879930000001, 109.01105039999997, -75.91846430000001,
        85.57095599999998, -69.3726773, 59.71969799999998);
    rr_renderer_fill(renderer);
    rr_renderer_set_fill(renderer, 0xffa49b8a);
    rr_renderer_begin_path(renderer);
    rr_renderer_move_to(renderer, -68.784039, 92.11737);
    rr_renderer_bezier_curve_to(renderer, -67.65052460000001, 77.83612,
                                -53.978863000000004, 67.10325599999999,
                                -38.24752900000001, 68.144866);
    rr_renderer_bezier_curve_to(renderer, -22.516190500000008, 69.1864767,
                                -10.682321000000009, 81.60810799999999,
                                -11.815835000000007, 95.88937299999999);
    rr_renderer_bezier_curve_to(
        renderer, -12.949349400000006, 110.17062299999999, -26.621011000000006,
        120.90347299999999, -42.35234500000001, 119.86187699999999);
    rr_renderer_bezier_curve_to(renderer, -58.08368000000001, 118.820251,
                                -69.917552, 106.39862, -68.784039, 92.11737);
    rr_renderer_fill(renderer);
    rr_renderer_set_fill(renderer, 0xffa49b8a);
    rr_renderer_begin_path(renderer);
    rr_renderer_move_to(renderer, -18.818150000000003, 111.16379999999998);
    rr_renderer_bezier_curve_to(
        renderer, -18.818150000000003, 81.95794399999998, -10.461178000000002,
        58.28191999999998, -0.15232500000000115, 58.28191999999998);
    rr_renderer_bezier_curve_to(renderer, 10.1565205, 58.28191999999998,
                                18.5135, 81.95794499999998, 18.5135,
                                111.16379999999998);
    rr_renderer_bezier_curve_to(renderer, 6.372181000000001, 100.16929299999998,
                                -6.676829999999999, 100.16929299999998,
                                -18.818150000000003, 111.16379999999998);
    rr_renderer_fill(renderer);
    rr_renderer_set_fill(renderer, 0xffa49b8a);
    rr_renderer_begin_path(renderer);
    rr_renderer_move_to(renderer, 69.50052, 59.71922000000001);
    rr_renderer_bezier_curve_to(renderer, 62.95474359999999, 33.86794700000001,
                                46.522248999999995, 15.394864000000005,
                                32.79754799999999, 18.458417000000004);
    rr_renderer_bezier_curve_to(
        renderer, 26.206704999999992, 19.929577900000005, 21.134522999999994,
        26.272015600000003, 18.696816999999992, 36.090467000000004);
    rr_renderer_bezier_curve_to(renderer, 16.259103399999994, 45.908918,
                                16.655557199999993, 58.399107,
                                19.798959299999993, 70.813322);
    rr_renderer_bezier_curve_to(renderer, 26.344743299999994, 96.664579,
                                42.77722329999999, 115.137662,
                                56.50193929999999, 112.07412500000001);
    rr_renderer_bezier_curve_to(renderer, 70.22664029999999, 109.0105874,
                                76.04631229999998, 85.57047800000001,
                                69.50052029999999, 59.71922100000001);
    rr_renderer_fill(renderer);
    rr_renderer_set_fill(renderer, 0xffa49b8a);
    rr_renderer_begin_path(renderer);
    rr_renderer_move_to(renderer, 68.91188, 92.11689999999999);
    rr_renderer_bezier_curve_to(renderer, 67.7783656, 77.83563499999998,
                                54.10670399999999, 67.10276999999999, 38.375381,
                                68.14438099999998);
    rr_renderer_bezier_curve_to(renderer, 22.644042499999998, 69.18599169999999,
                                10.810164999999998, 81.60762299999998,
                                11.943678999999996, 95.88887299999999);
    rr_renderer_bezier_curve_to(
        renderer, 13.077193399999995, 110.17012299999999, 26.748854999999995,
        120.90300299999998, 42.480193, 119.86137699999999);
    rr_renderer_bezier_curve_to(renderer, 58.2115315, 118.81978149999999,
                                70.045393, 106.39815099999998, 68.911879,
                                92.11690099999998);
    rr_renderer_fill(renderer);
    rr_renderer_set_fill(renderer, 0xffa49b8a);
    rr_renderer_begin_path(renderer);
    rr_renderer_move_to(renderer, -30.808914, 85.77369999999999);
    rr_renderer_line_to(renderer, -19.277023, 48.88581999999999);
    rr_renderer_line_to(renderer, 18.972586999999997, 48.88581999999999);
    rr_renderer_line_to(renderer, 30.504478, 85.77369999999999);
    rr_renderer_fill(renderer);
    rr_renderer_set_fill(renderer, 0xffbfbab0);
    rr_renderer_begin_path(renderer);
    rr_renderer_move_to(renderer, -7.405460000000005, -57.14565);
    rr_renderer_bezier_curve_to(renderer, -11.497058500000005, -62.8199817,
                                -11.497058500000005, -72.01988700000001,
                                -7.405460000000005, -77.694219);
    rr_renderer_quadratic_curve_to(renderer, -3.701221000000005, -82.831365,
                                   0.00302539999999496, -87.968511);
    rr_renderer_quadratic_curve_to(renderer, 3.707271899999995, -82.831365,
                                   7.411510799999995, -77.694219);
    rr_renderer_bezier_curve_to(renderer, 11.503109299999995,
                                -72.01988730000001, 11.503109299999995,
                                -62.819982, 7.411510799999995, -57.14565);
    rr_renderer_bezier_curve_to(
        renderer, 3.3199197999999948, -51.47131830000001, -3.3138692000000045,
        -51.47131830000001, -7.405460200000006, -57.14565);
    rr_renderer_fill(renderer);
    rr_renderer_set_fill(renderer, 0xff898276);
    rr_renderer_begin_path(renderer);
    rr_renderer_move_to(renderer, 42.215959999999995, 101.02963);
    rr_renderer_bezier_curve_to(renderer, 22.015420999999996, 94.5872777,
                                8.286989999999996, 75.837262, 8.246119999999998,
                                54.63435);
    rr_renderer_line_to(renderer, 22.795199999999998, 54.606304345999995);
    rr_renderer_bezier_curve_to(renderer, 22.823886523, 69.487362346, 32.459049,
                                82.64686234599999, 46.636585, 87.168361346);
    rr_renderer_fill(renderer);
    rr_renderer_set_fill(renderer, 0xff898276);
    rr_renderer_begin_path(renderer);
    rr_renderer_move_to(renderer, 8.172389999999993, 54.54082);
    rr_renderer_bezier_curve_to(renderer, 8.172389999999993, 50.5458401,
                                11.410961199999992, 47.307283999999996,
                                15.405940999999993, 47.307283999999996);
    rr_renderer_bezier_curve_to(renderer, 17.32439039999999, 47.307283999999996,
                                19.164272299999993, 48.069384199999995,
                                20.520824399999995, 49.4259363);
    rr_renderer_bezier_curve_to(renderer, 21.877376499999997, 50.7824884,
                                22.639484399999994, 52.6223627,
                                22.639484399999994, 54.5408197);
    rr_renderer_bezier_curve_to(renderer, 22.639484399999994, 58.5357996,
                                19.400913199999994, 61.7743707,
                                15.405940999999993, 61.7743707);
    rr_renderer_bezier_curve_to(renderer, 11.410961099999993, 61.7743707,
                                8.172389999999993, 58.535799499999996,
                                8.172389999999993, 54.5408197);
    rr_renderer_fill(renderer);
    rr_renderer_set_fill(renderer, 0xff898276);
    rr_renderer_begin_path(renderer);
    rr_renderer_move_to(renderer, 37.93496999999999, 94.26334000000003);
    rr_renderer_bezier_curve_to(renderer, 37.93496999999999, 90.26834500000002,
                                41.173525999999995, 87.02978900000002,
                                45.168505999999994, 87.02978900000002);
    rr_renderer_bezier_curve_to(renderer, 47.086963, 87.02978900000002,
                                48.926837299999995, 87.79188920000003,
                                50.28340469999999, 89.14844130000002);
    rr_renderer_bezier_curve_to(renderer, 51.63995679999999, 90.50497820000001,
                                52.40205699999999, 92.34488300000001,
                                52.40205699999999, 94.26334000000001);
    rr_renderer_bezier_curve_to(renderer, 52.40205699999999, 98.25830460000002,
                                49.16348579999999, 101.49686050000001,
                                45.168505999999994, 101.49686050000001);
    rr_renderer_bezier_curve_to(renderer, 41.1735261, 101.49686050000001,
                                37.93496999999999, 98.25830450000001,
                                37.93496999999999, 94.26334000000001);
    rr_renderer_fill(renderer);
    rr_renderer_set_fill(renderer, 0xff898276);
    rr_renderer_begin_path(renderer);
    rr_renderer_move_to(renderer, -42.212246, 101.02960000000002);
    rr_renderer_bezier_curve_to(renderer, -22.011719, 94.58724770000002,
                                -8.283286000000004, 75.83724800000002,
                                -8.242409000000002, 54.63433600000002);
    rr_renderer_line_to(renderer, -22.791497, 54.606290346000016);
    rr_renderer_bezier_curve_to(renderer, -22.820183523, 69.48734834600002,
                                -32.455346, 82.64684834600001, -46.632886,
                                87.16834734600002);
    rr_renderer_fill(renderer);
    rr_renderer_set_fill(renderer, 0xff898276);
    rr_renderer_begin_path(renderer);
    rr_renderer_move_to(renderer, -8.168689999999998, 54.54079999999999);
    rr_renderer_bezier_curve_to(renderer, -8.168689999999998, 50.54582009999999,
                                -11.407261199999997, 47.30724899999999,
                                -15.402233399999998, 47.30724899999999);
    rr_renderer_bezier_curve_to(
        renderer, -17.320690399999997, 47.30724899999999, -19.1605724,
        48.06936449999999, -20.5171244, 49.425916599999994);
    rr_renderer_bezier_curve_to(
        renderer, -21.873676500000002, 50.782468699999995, -22.6357767,
        52.622342999999994, -22.6357767, 54.54079999999999);
    rr_renderer_bezier_curve_to(renderer, -22.6357767, 58.53577989999999,
                                -19.3972132, 61.77435099999999, -15.4022333,
                                61.77435099999999);
    rr_renderer_bezier_curve_to(
        renderer, -11.407261100000001, 61.77435099999999, -8.1686899,
        58.535779799999986, -8.1686899, 54.54079999999999);
    rr_renderer_fill(renderer);
    rr_renderer_set_fill(renderer, 0xff898276);
    rr_renderer_begin_path(renderer);
    rr_renderer_move_to(renderer, -37.93126, 94.26330000000002);
    rr_renderer_bezier_curve_to(renderer, -37.93126, 90.26833540000001,
                                -41.1698274, 87.02976400000001,
                                -45.164803400000004, 87.02976400000001);
    rr_renderer_bezier_curve_to(
        renderer, -47.083256600000006, 87.02976400000001, -48.923138400000006,
        87.79186420000002, -50.27969040000001, 89.14840100000002);
    rr_renderer_bezier_curve_to(renderer, -51.63624250000001, 90.50496840000002,
                                -52.39834660000001, 92.34484270000002,
                                -52.39834660000001, 94.26329970000002);
    rr_renderer_bezier_curve_to(renderer, -52.39834660000001, 98.25826430000002,
                                -49.15977920000001, 101.49685070000002,
                                -45.16480320000001, 101.49685070000002);
    rr_renderer_bezier_curve_to(
        renderer, -41.16982720000001, 101.49685070000002, -37.93125980000001,
        98.25826430000002, -37.93125980000001, 94.26329970000002);
    rr_renderer_fill(renderer);
    rr_renderer_set_fill(renderer, 0xffbfbab0);
    rr_renderer_begin_path(renderer);
    rr_renderer_move_to(renderer, 21.439999999999998, -4.381130000000013);
    rr_renderer_bezier_curve_to(
        renderer, 21.400563659999996, -12.258373000000013, 35.279767,
        -21.057369000000012, 36.858823, -33.67052800000001);
    rr_renderer_bezier_curve_to(renderer, 38.4378635, -46.28369500000001,
                                28.78835, -63.09179300000001, 30.9142887,
                                -80.06009300000001);
    rr_renderer_bezier_curve_to(renderer, 33.0402195, -97.02839300000001,
                                46.4252907, -135.63731, 49.6144387,
                                -135.48031600000002);
    rr_renderer_bezier_curve_to(renderer, 52.803586700000004, -135.32332213,
                                48.3668648, -97.29555100000002, 50.04919212,
                                -79.11813600000002);
    rr_renderer_bezier_curve_to(
        renderer, 51.731504120000004, -60.94072200000002, 61.86727712,
        -41.86768600000002, 59.708311120000005, -26.415826000000024);
    rr_renderer_bezier_curve_to(
        renderer, 57.549360320000005, -10.963983000000024, 43.47347812000001,
        9.920507999999977, 37.095426120000006, 13.592963999999974);
    rr_renderer_bezier_curve_to(renderer, 30.71736672000001, 17.265418799999974,
                                21.479429120000006, 3.496115999999974,
                                21.440000120000008, -4.381126000000027);
    rr_renderer_fill(renderer);
    rr_renderer_set_fill(renderer, 0xffbfbab0);
    rr_renderer_begin_path(renderer);
    rr_renderer_move_to(renderer, -21.312820000000002, -4.38094000000001);
    rr_renderer_bezier_curve_to(renderer, -21.27338366, -12.25819830000001,
                                -35.152591, -21.05719400000001, -36.731639,
                                -33.670353000000006);
    rr_renderer_bezier_curve_to(renderer, -38.310687200000004, -46.283512,
                                -28.661170000000002, -63.09161,
                                -30.787108500000002, -80.05991);
    rr_renderer_bezier_curve_to(renderer, -32.9130393, -97.02821, -46.2981025,
                                -135.637127, -49.487254500000006, -135.480133);
    rr_renderer_bezier_curve_to(renderer, -52.67640250000001, -135.32313913,
                                -48.239688300000005, -97.295368,
                                -49.92200410000001, -79.117953);
    rr_renderer_bezier_curve_to(renderer, -51.60431610000001, -60.940539,
                                -61.74009610000001, -41.867503,
                                -59.58113410000001, -26.415653);
    rr_renderer_bezier_curve_to(
        renderer, -57.42217190000001, -10.963809999999999, -43.34629410000001,
        9.920697000000004, -36.96823810000001, 13.593136999999999);
    rr_renderer_bezier_curve_to(renderer, -30.590186300000006, 17.2655918,
                                -21.352248100000008, 3.4963049999999996,
                                -21.31282010000001, -4.380938);
    rr_renderer_fill(renderer);
}


void rr_triceratops_leg1_draw(struct rr_renderer *renderer)
{
    rr_renderer_set_fill(renderer, 0xffa49b8a);
    rr_renderer_begin_path(renderer);
    rr_renderer_move_to(renderer, -100.41649, -66.806183);
    rr_renderer_bezier_curve_to(renderer, -100.41649, -87.52919,
                                -83.93959799999999, -104.328507,
                                -63.61432799999999, -104.328507);
    rr_renderer_bezier_curve_to(renderer, -53.85378399999999, -104.328507,
                                -44.49301299999999, -100.3752733,
                                -37.591263999999995, -93.33847300000001);
    rr_renderer_bezier_curve_to(renderer, -30.689522999999994, -86.3016707,
                                -26.812157999999997, -76.757722,
                                -26.812157999999997, -66.806183);
    rr_renderer_bezier_curve_to(
        renderer, -26.812157999999997, -46.08317600000001, -43.289047999999994,
        -29.283859000000007, -63.61432799999999, -29.283859000000007);
    rr_renderer_bezier_curve_to(renderer, -83.93959999999998,
                                -29.283859000000007, -100.41649,
                                -46.08317500000001, -100.41649, -66.806183);
    rr_renderer_fill(renderer);
    rr_renderer_set_fill(renderer, 0xff898276);
    rr_renderer_begin_path(renderer);
    rr_renderer_move_to(renderer, -105.37648899999999, -66.80261);
    rr_renderer_bezier_curve_to(renderer, -105.37648899999999, -90.320528,
                                -86.67736199999999, -109.385564,
                                -63.61082199999999, -109.385564);
    rr_renderer_bezier_curve_to(renderer, -52.53387599999999, -109.385564,
                                -41.91061499999999, -104.8991577,
                                -34.07803499999999, -96.91330500000001);
    rr_renderer_bezier_curve_to(renderer, -26.245454399999993, -88.927452,
                                -21.84515499999999, -78.096309,
                                -21.84515499999999, -66.802608);
    rr_renderer_bezier_curve_to(
        renderer, -21.84515499999999, -43.284690000000005, -40.544281999999995,
        -24.21965800000001, -63.61082199999999, -24.21965800000001);
    rr_renderer_bezier_curve_to(
        renderer, -86.67736199999999, -24.21965800000001, -105.37648899999999,
        -43.28469100000001, -105.37648899999999, -66.802608);
    rr_renderer_move_to(renderer, -93.78651649999999, -66.802608);
    rr_renderer_bezier_curve_to(
        renderer, -93.78651649999999, -49.68566100000001, -80.27639799999999,
        -35.80963100000001, -63.610821499999986, -35.80963100000001);
    rr_renderer_bezier_curve_to(
        renderer, -46.94524449999999, -35.80963100000001, -33.435127499999986,
        -49.68566100000001, -33.435127499999986, -66.802608);
    rr_renderer_bezier_curve_to(renderer, -33.435127499999986, -83.919559,
                                -46.94524449999999, -97.795589,
                                -63.610821499999986, -97.795589);
    rr_renderer_bezier_curve_to(renderer, -80.27639849999998, -97.795589,
                                -93.78651649999999, -83.919559,
                                -93.78651649999999, -66.802608);
    rr_renderer_fill(renderer);
    rr_renderer_set_fill(renderer, 0xffa49b8a);
    rr_renderer_begin_path(renderer);
    rr_renderer_move_to(renderer, 26.802930000000003, 66.79865000000001);
    rr_renderer_bezier_curve_to(
        renderer, 26.802930000000003, 46.075643000000014, 43.279813000000004,
        29.27632600000001, 63.605085, 29.27632600000001);
    rr_renderer_bezier_curve_to(renderer, 73.365629, 29.27632600000001,
                                82.726408, 33.22955780000001, 89.628156,
                                40.266362000000015);
    rr_renderer_bezier_curve_to(renderer, 96.5298894, 47.30316600000002,
                                100.40725450000001, 56.84711200000001,
                                100.40725450000001, 66.79865000000001);
    rr_renderer_bezier_curve_to(renderer, 100.40725450000001, 87.521657,
                                83.9303715, 104.320974, 63.60508450000001,
                                104.320974);
    rr_renderer_bezier_curve_to(renderer, 43.27981250000001, 104.320974,
                                26.802929500000012, 87.521658,
                                26.802929500000012, 66.79865000000001);
    rr_renderer_fill(renderer);
    rr_renderer_set_fill(renderer, 0xff898276);
    rr_renderer_begin_path(renderer);
    rr_renderer_move_to(renderer, 21.842929999999996, 66.80222);
    rr_renderer_bezier_curve_to(renderer, 21.842929999999996, 43.284306,
                                40.542057, 24.21927300000001,
                                63.608599999999996, 24.21927300000001);
    rr_renderer_bezier_curve_to(renderer, 74.68554999999999, 24.21927300000001,
                                85.30881, 28.705677400000006, 93.141391,
                                36.69153250000001);
    rr_renderer_bezier_curve_to(renderer, 100.9739716, 44.677372500000004,
                                105.374271, 55.50851850000001, 105.374271,
                                66.8022195);
    rr_renderer_bezier_curve_to(renderer, 105.374271, 90.32013350000001,
                                86.67514399999999, 109.38518150000002,
                                63.60860099999999, 109.38518150000002);
    rr_renderer_bezier_curve_to(renderer, 40.54205699999999, 109.38518150000002,
                                21.842930999999993, 90.32013350000001,
                                21.842930999999993, 66.8022195);
    rr_renderer_move_to(renderer, 33.432911999999995, 66.8022195);
    rr_renderer_bezier_curve_to(renderer, 33.432911999999995, 83.91917850000002,
                                46.943028999999996, 97.7952005,
                                63.60860199999999, 97.7952005);
    rr_renderer_bezier_curve_to(renderer, 80.27417499999999, 97.7952005,
                                93.78430699999998, 83.9191785,
                                93.78430699999998, 66.8022195);
    rr_renderer_bezier_curve_to(renderer, 93.78430699999998, 49.68527650000001,
                                80.27417499999999, 35.809238500000006,
                                63.60860199999998, 35.809238500000006);
    rr_renderer_bezier_curve_to(renderer, 46.94302899999998, 35.809238500000006,
                                33.43291199999999, 49.68527650000001,
                                33.43291199999999, 66.8022195);
    rr_renderer_fill(renderer);
}


void rr_triceratops_leg2_draw(struct rr_renderer *renderer)
{
    rr_renderer_set_fill(renderer, 0xffa49b8a);
    rr_renderer_begin_path(renderer);
    rr_renderer_move_to(renderer, 26.792429999999996, -66.806183);
    rr_renderer_bezier_curve_to(renderer, 26.792429999999996, -87.52919,
                                43.269313, -104.328507, 63.594584999999995,
                                -104.328507);
    rr_renderer_bezier_curve_to(renderer, 73.35512899999999, -104.328507,
                                82.715908, -100.3752733, 89.617656,
                                -93.33847300000001);
    rr_renderer_bezier_curve_to(renderer, 96.5193894, -86.3016707, 100.3967545,
                                -76.757722, 100.3967545, -66.806183);
    rr_renderer_bezier_curve_to(renderer, 100.3967545, -46.08317600000001,
                                83.9198715, -29.283859000000007, 63.5945845,
                                -29.283859000000007);
    rr_renderer_bezier_curve_to(
        renderer, 43.269312500000005, -29.283859000000007, 26.792429500000004,
        -46.08317500000001, 26.792429500000004, -66.806183);
    rr_renderer_fill(renderer);
    rr_renderer_set_fill(renderer, 0xff898276);
    rr_renderer_begin_path(renderer);
    rr_renderer_move_to(renderer, 21.832429999999988, -66.80261);
    rr_renderer_bezier_curve_to(renderer, 21.832429999999988, -90.320528,
                                40.53155699999999, -109.385564,
                                63.59809999999999, -109.385564);
    rr_renderer_bezier_curve_to(renderer, 74.67504999999998, -109.385564,
                                85.29830999999999, -104.8991577,
                                93.13089099999999, -96.91330500000001);
    rr_renderer_bezier_curve_to(renderer, 100.96347159999999, -88.927452,
                                105.36377099999999, -78.096309,
                                105.36377099999999, -66.802608);
    rr_renderer_bezier_curve_to(
        renderer, 105.36377099999999, -43.284690000000005, 86.66464399999998,
        -24.21965800000001, 63.598100999999986, -24.21965800000001);
    rr_renderer_bezier_curve_to(
        renderer, 40.531556999999985, -24.21965800000001, 21.832430999999985,
        -43.28469100000001, 21.832430999999985, -66.802608);
    rr_renderer_move_to(renderer, 33.42241199999999, -66.802608);
    rr_renderer_bezier_curve_to(renderer, 33.42241199999999, -49.68566100000001,
                                46.93252899999999, -35.80963100000001,
                                63.59810199999998, -35.80963100000001);
    rr_renderer_bezier_curve_to(renderer, 80.26367499999998, -35.80963100000001,
                                93.77380699999998, -49.68566100000001,
                                93.77380699999998, -66.802608);
    rr_renderer_bezier_curve_to(renderer, 93.77380699999998, -83.919559,
                                80.26367499999998, -97.795589,
                                63.598101999999976, -97.795589);
    rr_renderer_bezier_curve_to(renderer, 46.932528999999974, -97.795589,
                                33.42241199999998, -83.919559,
                                33.42241199999998, -66.802608);
    rr_renderer_fill(renderer);
    rr_renderer_set_fill(renderer, 0xffa49b8a);
    rr_renderer_begin_path(renderer);
    rr_renderer_move_to(renderer, -100.403368, 66.79865000000001);
    rr_renderer_bezier_curve_to(renderer, -100.403368, 46.075643000000014,
                                -83.92647600000001, 29.27632600000001,
                                -63.601198000000004, 29.27632600000001);
    rr_renderer_bezier_curve_to(
        renderer, -53.840658000000005, 29.27632600000001, -44.479887000000005,
        33.22955780000001, -37.578138, 40.266362000000015);
    rr_renderer_bezier_curve_to(renderer, -30.676397, 47.30316600000002,
                                -26.799032000000004, 56.84711200000001,
                                -26.799032000000004, 66.79865000000001);
    rr_renderer_bezier_curve_to(renderer, -26.799032000000004, 87.521657,
                                -43.27592200000001, 104.320974,
                                -63.601198000000004, 104.320974);
    rr_renderer_bezier_curve_to(renderer, -83.926473, 104.320974, -100.403368,
                                87.521658, -100.403368, 66.79865000000001);
    rr_renderer_fill(renderer);
    rr_renderer_set_fill(renderer, 0xff898276);
    rr_renderer_begin_path(renderer);
    rr_renderer_move_to(renderer, -105.363365, 66.80222);
    rr_renderer_bezier_curve_to(renderer, -105.363365, 43.284306, -86.664238,
                                24.21927300000001, -63.597695,
                                24.21927300000001);
    rr_renderer_bezier_curve_to(renderer, -52.520753, 24.21927300000001,
                                -41.897492, 28.705677400000006, -34.064911,
                                36.69153250000001);
    rr_renderer_bezier_curve_to(renderer, -26.232323, 44.677372500000004,
                                -21.832024000000004, 55.50851850000001,
                                -21.832024000000004, 66.8022195);
    rr_renderer_bezier_curve_to(
        renderer, -21.832024000000004, 90.32013350000001, -40.53115100000001,
        109.38518150000002, -63.597694000000004, 109.38518150000002);
    rr_renderer_bezier_curve_to(renderer, -86.66423800000001,
                                109.38518150000002, -105.363364,
                                90.32013350000001, -105.363364, 66.8022195);
    rr_renderer_move_to(renderer, -93.773391, 66.8022195);
    rr_renderer_bezier_curve_to(renderer, -93.773391, 83.91917850000002,
                                -80.263271, 97.7952005, -63.597694000000004,
                                97.7952005);
    rr_renderer_bezier_curve_to(renderer, -46.93212100000001, 97.7952005,
                                -33.421997000000005, 83.9191785,
                                -33.421997000000005, 66.8022195);
    rr_renderer_bezier_curve_to(
        renderer, -33.421997000000005, 49.68527650000001, -46.932121,
        35.809238500000006, -63.597694000000004, 35.809238500000006);
    rr_renderer_bezier_curve_to(renderer, -80.263271, 35.809238500000006,
                                -93.773391, 49.68527650000001, -93.773391,
                                66.8022195);
    rr_renderer_fill(renderer);
}


void rr_triceratops_tail_draw(struct rr_renderer *renderer)
{
    rr_renderer_set_fill(renderer, 0xff898276);
    rr_renderer_begin_path(renderer);
    rr_renderer_move_to(renderer, 52.173869999999994, -61.130399999999995);
    rr_renderer_line_to(renderer, 16.27457799999999, 120.34763);
    rr_renderer_line_to(renderer, -16.270077000000008, 120.34763);
    rr_renderer_line_to(renderer, -52.16937300000001, -61.130399999999995);
    rr_renderer_fill(renderer);
    rr_renderer_set_fill(renderer, 0xff898276);
    rr_renderer_begin_path(renderer);
    rr_renderer_move_to(renderer, -53.70089, -74.5517);
    rr_renderer_bezier_curve_to(renderer, -53.70089, -108.770027, -29.65799,
                                -136.50946, 0.00043399999999849115, -136.50946);
    rr_renderer_bezier_curve_to(renderer, 14.242904, -136.50946,
                                27.902044999999998, -129.98178439999998,
                                37.973006, -118.36245299999999);
    rr_renderer_bezier_curve_to(
        renderer, 48.043943999999996, -106.74311799999998, 53.701750499999996,
        -90.98392099999998, 53.701750499999996, -74.55169999999998);
    rr_renderer_bezier_curve_to(
        renderer, 53.701750499999996, -40.333376999999984, 29.658850499999996,
        -12.593949999999985, 0.0004334999999926481, -12.593949999999985);
    rr_renderer_bezier_curve_to(
        renderer, -29.657990500000007, -12.593949999999985, -53.70089050000001,
        -40.33337599999999, -53.70089050000001, -74.55169999999998);
    rr_renderer_fill(renderer);
    rr_renderer_set_fill(renderer, 0xff898276);
    rr_renderer_begin_path(renderer);
    rr_renderer_move_to(renderer, -37.18092, -74.56619);
    rr_renderer_bezier_curve_to(renderer, -37.18092, -98.25003600000001,
                                -20.539887, -117.449582, -0.012129999999999086,
                                -117.449582);
    rr_renderer_bezier_curve_to(renderer, 9.845643, -117.449582, 19.299668,
                                -112.93152300000001, 26.270173, -104.889329);
    rr_renderer_bezier_curve_to(renderer, 33.2406625, -96.84713500000001,
                                37.156663, -85.939572, 37.156663,
                                -74.56618900000001);
    rr_renderer_bezier_curve_to(renderer, 37.156663, -50.88235100000001,
                                20.515626, -31.682797000000008,
                                -0.012129999999999086, -31.682797000000008);
    rr_renderer_bezier_curve_to(renderer, -20.539886, -31.682797000000008,
                                -37.18092, -50.88235100000001, -37.18092,
                                -74.56618900000001);
    rr_renderer_fill(renderer);
    rr_renderer_set_fill(renderer, 0xff898276);
    rr_renderer_begin_path(renderer);
    rr_renderer_move_to(renderer, -16.406530000000004, 117.58875);
    rr_renderer_bezier_curve_to(
        renderer, -16.406530000000004, 107.13864600000001, -9.063924400000005,
        98.66712000000001, -0.006368000000001928, 98.66712000000001);
    rr_renderer_bezier_curve_to(renderer, 4.343218499999998, 98.66712000000001,
                                8.514665999999998, 100.66065030000001,
                                11.590288999999999, 104.20914270000002);
    rr_renderer_bezier_curve_to(
        renderer, 14.665919199999998, 107.75763510000002, 16.3937863,
        112.57044070000002, 16.3937863, 117.58875070000002);
    rr_renderer_bezier_curve_to(renderer, 16.3937863, 128.0388847, 9.0511883,
                                136.51041170000002, -0.0063677000000019746,
                                136.51041170000002);
    rr_renderer_bezier_curve_to(
        renderer, -9.063923700000002, 136.51041170000002, -16.406529700000004,
        128.0388847, -16.406529700000004, 117.58875070000002);
    rr_renderer_fill(renderer);
    rr_renderer_set_fill(renderer, 0xff898276);
    rr_renderer_begin_path(renderer);
    rr_renderer_move_to(renderer, 35.80797000000001, -63.11681);
    rr_renderer_line_to(renderer, -0.007627999999989754, 120.05824);
    rr_renderer_line_to(renderer, -35.82321799999999, -63.11681);
    rr_renderer_fill(renderer);
    rr_renderer_set_fill(renderer, 0xffa49b8a);
    rr_renderer_begin_path(renderer);
    rr_renderer_move_to(renderer, -37.18092, -74.56619);
    rr_renderer_bezier_curve_to(renderer, -37.18092, -98.25003600000001,
                                -20.539887, -117.449582, -0.012129999999999086,
                                -117.449582);
    rr_renderer_bezier_curve_to(renderer, 9.845643, -117.449582, 19.299668,
                                -112.93152300000001, 26.270173, -104.889329);
    rr_renderer_bezier_curve_to(renderer, 33.2406625, -96.84713500000001,
                                37.156663, -85.939572, 37.156663,
                                -74.56618900000001);
    rr_renderer_bezier_curve_to(renderer, 37.156663, -50.88235100000001,
                                20.515626, -31.682797000000008,
                                -0.012129999999999086, -31.682797000000008);
    rr_renderer_bezier_curve_to(renderer, -20.539886, -31.682797000000008,
                                -37.18092, -50.88235100000001, -37.18092,
                                -74.56618900000001);
    rr_renderer_fill(renderer);
    rr_renderer_set_fill(renderer, 0xffa49b8a);
    rr_renderer_begin_path(renderer);
    rr_renderer_move_to(renderer, 35.80797000000001, -63.11681);
    rr_renderer_line_to(renderer, -0.007627999999989754, 120.05824);
    rr_renderer_line_to(renderer, -35.82321799999999, -63.11681);
    rr_renderer_fill(renderer);
    rr_renderer_set_fill(renderer, 0xff898276);
    rr_renderer_begin_path(renderer);
    rr_renderer_move_to(renderer, -8.944885, -28.527539999999988);
    rr_renderer_bezier_curve_to(renderer, -8.944885, -33.467664499999984,
                                -4.940124299999999, -37.47242499999999, 0,
                                -37.47242499999999);
    rr_renderer_bezier_curve_to(renderer, 2.3723297, -37.47242499999999,
                                4.647499, -36.53002689999999, 6.3249893,
                                -34.85253669999999);
    rr_renderer_bezier_curve_to(renderer, 8.0024795, -33.175046499999986,
                                8.9448853, -30.899869499999987, 8.9448853,
                                -28.527539699999988);
    rr_renderer_line_to(renderer, 8.9448853, 120.54331030000002);
    rr_renderer_bezier_curve_to(renderer, 8.9448853, 125.48343480000001,
                                4.940124599999999, 129.48819530000003,
                                2.9999999995311555e-7, 129.48819530000003);
    rr_renderer_bezier_curve_to(renderer, -4.9401242, 129.48819530000003,
                                -8.9448847, 125.48343460000002, -8.9448847,
                                120.54331030000003);
    rr_renderer_fill(renderer);
}