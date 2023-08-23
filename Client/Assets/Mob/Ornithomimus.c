#include <Client/Assets/Render.h>

#include <Client/Renderer/Renderer.h>

void rr_ornithomimus_body_draw(struct rr_renderer *renderer)
{
    rr_renderer_set_fill(renderer, 0xffb8b8b8);
    rr_renderer_begin_path(renderer);
    rr_renderer_move_to(renderer, -55.415188, 43.688320000000004);
    rr_renderer_bezier_curve_to(renderer, -55.415188, -11.420962999999993,
                                -30.607392, -56.09585, -0.005425000000002456,
                                -56.09585);
    rr_renderer_bezier_curve_to(renderer, 14.690154999999997, -56.09585,
                                28.783851, -45.582910999999996,
                                39.175200999999994, -26.869753);
    rr_renderer_bezier_curve_to(renderer, 49.566542999999996, -8.156588,
                                55.40434199999999, 17.223907, 55.40434199999999,
                                43.688322);
    rr_renderer_bezier_curve_to(renderer, 55.40434199999999, 98.797605,
                                30.596541999999992, 143.47250200000002,
                                -0.005425000000009561, 143.47250200000002);
    rr_renderer_bezier_curve_to(
        renderer, -30.607392000000008, 143.47250200000002, -55.41518800000001,
        98.79760600000003, -55.41518800000001, 43.688322000000014);
    rr_renderer_fill(renderer);
    rr_renderer_set_fill(renderer, 0xffa7a7a7);
    rr_renderer_begin_path(renderer);
    rr_renderer_move_to(renderer, -62.88302, 43.69783000000001);
    rr_renderer_bezier_curve_to(renderer, -62.88302, -18.844024999999988,
                                -34.729398, -69.54422999999998,
                                -0.00014600000000086766, -69.54422999999998);
    rr_renderer_bezier_curve_to(renderer, 16.677428, -69.54422999999998,
                                32.671934, -57.61340599999998, 44.464751,
                                -36.37640599999998);
    rr_renderer_bezier_curve_to(renderer, 56.257582, -15.139390999999982,
                                62.88272, 13.66416700000002, 62.88272,
                                43.69782800000002);
    rr_renderer_bezier_curve_to(renderer, 62.88272, 106.23968300000001,
                                34.72911, 156.93987800000002,
                                -0.00014600000000086766, 156.93987800000002);
    rr_renderer_bezier_curve_to(renderer, -34.729396, 156.93987800000002,
                                -62.88302, 106.23968300000001, -62.88302,
                                43.697828000000015);
    rr_renderer_move_to(renderer, -48.609865, 43.697828000000015);
    rr_renderer_bezier_curve_to(renderer, -48.609865, 98.35683800000001,
                                -26.846552, 142.666718, -0.000144999999996287,
                                142.666718);
    rr_renderer_bezier_curve_to(renderer, 26.846260000000004, 142.666718,
                                48.60957500000001, 98.356843, 48.60957500000001,
                                43.697828);
    rr_renderer_bezier_curve_to(renderer, 48.60957500000001, -10.961182,
                                26.846262000000007, -55.271072000000004,
                                -0.000144999999996287, -55.271072000000004);
    rr_renderer_bezier_curve_to(renderer, -26.846549999999997,
                                -55.271072000000004, -48.609865, -10.961182,
                                -48.609865, 43.697828);
    rr_renderer_fill(renderer);
    rr_renderer_set_fill(renderer, 0xffa7a7a7);
    rr_renderer_begin_path(renderer);
    rr_renderer_move_to(renderer, -38.547134, -118.336502);
    rr_renderer_bezier_curve_to(renderer, -38.547134, -139.657095, -21.263382,
                                -156.940852, 0.057212999999997294, -156.940852);
    rr_renderer_bezier_curve_to(renderer, 10.295722999999997, -156.940852,
                                20.114890999999997, -152.87361900000002,
                                27.354613999999998, -145.6339);
    rr_renderer_bezier_curve_to(renderer, 34.594329599999995, -138.3941806,
                                38.661559999999994, -128.575013,
                                38.661559999999994, -118.33650200000001);
    rr_renderer_line_to(renderer, 38.661559999999994, -25.184967000000015);
    rr_renderer_bezier_curve_to(
        renderer, 38.661559999999994, -3.8643650000000136, 21.377807999999995,
        13.419387999999984, 0.057212999999997294, 13.419387999999984);
    rr_renderer_bezier_curve_to(
        renderer, -21.263382000000004, 13.419387999999984, -38.547134,
        -3.864364000000016, -38.547134, -25.184967000000015);
    rr_renderer_fill(renderer);
    rr_renderer_set_fill(renderer, 0xffb8b8b8);
    rr_renderer_begin_path(renderer);
    rr_renderer_move_to(renderer, -27.687065000000004, -116.27569);
    rr_renderer_bezier_curve_to(renderer, -27.687065000000004, -131.598513,
                                -15.265457000000003, -144.020119,
                                0.057364999999997224, -144.020119);
    rr_renderer_bezier_curve_to(renderer, 7.4156489999999975, -144.020119,
                                14.472548999999997, -141.097052, 19.675644,
                                -135.89396499999998);
    rr_renderer_bezier_curve_to(renderer, 24.878731, -130.6908743,
                                27.801795999999996, -123.63397049999998,
                                27.801795999999996, -116.27568999999998);
    rr_renderer_line_to(renderer, 27.801795999999996, -1.4043139999999852);
    rr_renderer_bezier_curve_to(
        renderer, 27.801795999999996, 13.918516000000015, 15.380187999999995,
        26.340116000000016, 0.0573659999999947, 26.340116000000016);
    rr_renderer_bezier_curve_to(
        renderer, -15.265457000000005, 26.340116000000016, -27.687064000000007,
        13.918516000000016, -27.687064000000007, -1.4043139999999852);
    rr_renderer_fill(renderer);
}


void rr_ornithomimus_head_draw(struct rr_renderer *renderer)
{
    rr_renderer_set_fill(renderer, 0xffa7a7a7);
rr_renderer_begin_path(renderer);
rr_renderer_move_to(renderer, 41.44248, 28.573229999999995);
rr_renderer_bezier_curve_to(renderer, 41.44248, 51.462298999999994, 22.885588000000002, 70.01755, -0.005487999999999715, 70.01755);
rr_renderer_bezier_curve_to(renderer, -10.998175, 70.01755, -21.540629, 65.65111, -29.313628, 57.878787);
rr_renderer_bezier_curve_to(renderer, -37.0866306, 50.106478700000004, -41.453458, 39.564959, -41.453458, 28.573230000000002);
rr_renderer_bezier_curve_to(renderer, -41.453458, 5.684169000000001, -22.896570999999998, -12.871082999999999, -0.005489999999994666, -12.871082999999999);
rr_renderer_bezier_curve_to(renderer, 22.885585000000006, -12.871082999999999, 41.44247800000001, 5.684169000000001, 41.44247800000001, 28.573230000000002);
rr_renderer_fill(renderer);
rr_renderer_set_fill(renderer, 0xffa7a7a7);
rr_renderer_begin_path(renderer);
rr_renderer_move_to(renderer, 14.060879999999997, 63.44788);
rr_renderer_bezier_curve_to(renderer, 14.060879999999997, 71.2158396, 7.763150499999997, 77.51302, -0.005488000000003268, 77.51302);
rr_renderer_bezier_curve_to(renderer, -3.7361246000000032, 77.51302, -7.313959700000003, 76.0311627, -9.951914000000004, 73.39343699999999);
rr_renderer_bezier_curve_to(renderer, -12.589872500000004, 70.7557112, -14.071859500000004, 67.17818129999999, -14.071859500000004, 63.44787999999999);
rr_renderer_bezier_curve_to(renderer, -14.071859500000004, 55.67992039999999, -7.774133800000004, 49.38275549999999, -0.00548750000000453, 49.38275549999999);
rr_renderer_bezier_curve_to(renderer, 7.7631510999999955, 49.38275549999999, 14.060880499999996, 55.67992049999999, 14.060880499999996, 63.447879999999984);
rr_renderer_fill(renderer);
rr_renderer_set_fill(renderer, 0xffa7a7a7);
rr_renderer_begin_path(renderer);
rr_renderer_move_to(renderer, 27.048270000000002, 59.989689999999996);
rr_renderer_line_to(renderer, 8.741637, 74.404241);
rr_renderer_line_to(renderer, 11.9254367, 66.356725);
rr_renderer_fill(renderer);
rr_renderer_set_fill(renderer, 0xffa7a7a7);
rr_renderer_begin_path(renderer);
rr_renderer_move_to(renderer, -27.185833000000002, 59.989689999999996);
rr_renderer_line_to(renderer, -8.879196000000004, 74.404241);
rr_renderer_line_to(renderer, -12.062995700000004, 66.356725);
rr_renderer_fill(renderer);
rr_renderer_set_fill(renderer, 0xffb8b8b8);
rr_renderer_begin_path(renderer);
rr_renderer_move_to(renderer, 20.717309999999998, 7.849739999999997);
rr_renderer_bezier_curve_to(renderer, 32.163469, 19.294891999999997, 32.163469, 37.851151, 20.717309999999998, 49.29631);
rr_renderer_quadratic_curve_to(renderer, 11.569970999999997, 58.44284, -0.007803000000002669, 65.159149);
rr_renderer_quadratic_curve_to(renderer, -11.585577000000002, 58.4428404, -20.732913000000003, 49.29631);
rr_renderer_bezier_curve_to(renderer, -32.179076, 37.85115, -32.179076, 19.29489, -20.732913000000003, 7.849739999999997);
rr_renderer_bezier_curve_to(renderer, -9.286754000000004, -3.595412000000003, 9.271141999999998, -3.595412000000003, 20.717308999999993, 7.849739999999997);
rr_renderer_fill(renderer);
rr_renderer_set_fill(renderer, 0xff95754f);
rr_renderer_begin_path(renderer);
rr_renderer_move_to(renderer, -30.244095, 26.13649000000001);
rr_renderer_bezier_curve_to(renderer, -30.244095, -6.791861999999988, -16.720978000000002, -33.485564999999994, -0.03936800000000318, -33.485564999999994);
rr_renderer_bezier_curve_to(renderer, 16.642234, -33.485564999999994, 30.165351999999995, -6.791861999999995, 30.165351999999995, 26.13649000000001);
rr_renderer_bezier_curve_to(renderer, 12.586913999999997, -2.1975019999999894, -12.665653000000002, -2.1975019999999894, -30.244095000000005, 26.13649000000001);
rr_renderer_fill(renderer);
rr_renderer_set_fill(renderer, 0xff7f6342);
rr_renderer_begin_path(renderer);
rr_renderer_move_to(renderer, -24.78779, -52.676056);
rr_renderer_bezier_curve_to(renderer, -24.78779, -66.391853, -13.668943, -77.5107, 0.04684999999999917, -77.5107);
rr_renderer_bezier_curve_to(renderer, 6.633412999999999, -77.5107, 12.950201, -74.894203, 17.607602999999997, -70.236801);
rr_renderer_bezier_curve_to(renderer, 22.2649974, -65.579403, 24.881498299999997, -59.262615, 24.881498299999997, -52.676056);
rr_renderer_bezier_curve_to(renderer, 24.881498299999997, -38.960259, 13.762647299999998, -27.841408, 0.04685029999999557, -27.841408);
rr_renderer_bezier_curve_to(renderer, -13.668943700000005, -27.841408, -24.787789700000005, -38.960259, -24.787789700000005, -52.676056);
rr_renderer_fill(renderer);
rr_renderer_set_fill(renderer, 0xff7f6342);
rr_renderer_begin_path(renderer);
rr_renderer_move_to(renderer, -32.797394, -4.055250000000001);
rr_renderer_line_to(renderer, -24.711173999999996, -55.582807);
rr_renderer_line_to(renderer, 24.785683000000002, -55.582807);
rr_renderer_line_to(renderer, 32.871903, -4.055250000000001);
rr_renderer_fill(renderer);
rr_renderer_set_fill(renderer, 0xff7f6342);
rr_renderer_begin_path(renderer);
rr_renderer_move_to(renderer, -41.489502, 24.61679000000001);
rr_renderer_bezier_curve_to(renderer, -41.489502, 8.373992000000008, -33.5513916, -6.62873999999999, -20.678059, -14.71603499999999);
rr_renderer_bezier_curve_to(renderer, -7.8047260000000005, -22.803330999999993, 8.038160999999999, -22.740326999999994, 20.857431000000002, -14.550850979999991);
rr_renderer_bezier_curve_to(renderer, 33.676698, -6.36137497999999, 41.51494, 8.70408502000001, 41.407045, 24.946471020000004);
rr_renderer_line_to(renderer, 29.988245, 24.855650710000003);
rr_renderer_bezier_curve_to(renderer, 30.06393622, 12.703627710000003, 24.383699399999998, 1.433485710000003, 15.096017999999999, -4.691995289999998);
rr_renderer_bezier_curve_to(renderer, 5.808335999999999, -10.817468289999997, -5.668858999999999, -10.863114989999998, -14.994459, -4.811662339999998);
rr_renderer_bezier_curve_to(renderer, -24.3200625, 1.2397902600000021, -30.070349, 12.464475660000002, -30.070349, 24.616789660000002);
rr_renderer_fill(renderer);
rr_renderer_set_fill(renderer, 0xffa7a7a7);
rr_renderer_begin_path(renderer);
rr_renderer_move_to(renderer, 41.408134000000004, 24.61679000000001);
rr_renderer_bezier_curve_to(renderer, 41.408134000000004, 40.85960300000001, 33.470023600000005, 55.862334000000004, 20.596694000000003, 63.949630000000006);
rr_renderer_bezier_curve_to(renderer, 7.723357000000004, 72.03692600000001, -8.119525999999997, 71.973922, -20.938797999999995, 63.78445361000001);
rr_renderer_bezier_curve_to(renderer, -33.758064999999995, 55.59496961000001, -41.596306999999996, 40.529509610000005, -41.48840799999999, 24.28712361000001);
rr_renderer_line_to(renderer, -30.069607999999995, 24.37794392000001);
rr_renderer_bezier_curve_to(renderer, -30.145299219999995, 36.52996692000001, -24.465062399999994, 47.800108920000014, -15.177380999999995, 53.92558192000001);
rr_renderer_bezier_curve_to(renderer, -5.8897029999999955, 60.05105492000001, 5.587493000000004, 60.096709220000015, 14.913092000000004, 54.045256600000016);
rr_renderer_bezier_curve_to(renderer, 24.238699000000004, 47.99380400000002, 29.988982000000004, 36.76911860000001, 29.988982000000004, 24.616789600000015);
rr_renderer_fill(renderer);
rr_renderer_set_fill(renderer, 0xff7f6342);
rr_renderer_begin_path(renderer);
rr_renderer_move_to(renderer, -41.489548, 24.616780000000006);
rr_renderer_bezier_curve_to(renderer, -41.489548, 21.459629700000004, -38.9301684, 18.900242500000004, -35.7730143, 18.900242500000004);
rr_renderer_bezier_curve_to(renderer, -34.2568934, 18.900242500000004, -32.8028719, 19.502522160000005, -31.7308123, 20.574574200000004);
rr_renderer_bezier_curve_to(renderer, -30.6587527, 21.646641500000005, -30.0564768, 23.100666700000005, -30.0564768, 24.616780200000004);
rr_renderer_bezier_curve_to(renderer, -30.0564768, 27.773930500000006, -32.6158564, 30.333317700000006, -35.7730143, 30.333317700000006);
rr_renderer_bezier_curve_to(renderer, -38.9301683, 30.333317700000006, -41.489548, 27.773930500000006, -41.489548, 24.616780200000004);
rr_renderer_fill(renderer);
rr_renderer_set_fill(renderer, 0xff95754f);
rr_renderer_begin_path(renderer);
rr_renderer_move_to(renderer, -26.400509999999997, 8.547820000000002);
rr_renderer_bezier_curve_to(renderer, -22.556260299999998, 11.278807500000001, -18.170765999999997, 8.698271660000001, -16.605236999999995, 2.784041300000002);
rr_renderer_bezier_curve_to(renderer, -15.039704299999995, -3.130188999999998, -16.886971469999995, -10.138512699999998, -20.731220999999994, -12.869500699999998);
rr_renderer_bezier_curve_to(renderer, -20.760288992999996, -4.724175699999998, -22.790707399999995, 2.9462803000000015, -26.400509599999992, 8.547819300000002);
rr_renderer_fill(renderer);
rr_renderer_set_fill(renderer, 0xff95754f);
rr_renderer_begin_path(renderer);
rr_renderer_move_to(renderer, 26.456509999999994, 8.547820000000002);
rr_renderer_bezier_curve_to(renderer, 22.612256499999994, 11.278807500000001, 18.226765999999994, 8.698271660000001, 16.661236999999993, 2.7840490000000013);
rr_renderer_bezier_curve_to(renderer, 15.095700499999992, -3.1301812999999985, 16.942967649999993, -10.138512999999998, 20.78722099999999, -12.869492999999999);
rr_renderer_bezier_curve_to(renderer, 20.816288992999993, -4.724175999999998, 22.846707399999993, 2.946288000000001, 26.45650959999999, 8.547820000000002);
rr_renderer_fill(renderer);
rr_renderer_set_fill(renderer, 0xff7f6342);
rr_renderer_begin_path(renderer);
rr_renderer_move_to(renderer, -32.567924, -4.9439239999999955);
rr_renderer_bezier_curve_to(renderer, -33.28006694, -2.6566696999999957, -34.7238269, -0.6309739999999957, -33.6928439, 0.23161300000000473);
rr_renderer_bezier_curve_to(renderer, -32.6618571, 1.0942000000000047, -28.3595996, 0.9815596000000048, -26.3820186, 0.23161300000000473);
rr_renderer_bezier_curve_to(renderer, -24.404437599999998, -0.5183335999999953, -23.027118199999997, -2.055641299999995, -21.8273616, -4.268058999999996);
rr_renderer_bezier_curve_to(renderer, -20.6276012, -6.480476599999996, -19.642818, -10.155746699999995, -19.1834598, -13.042884999999995);
rr_renderer_bezier_curve_to(renderer, -18.72409777, -15.930015699999995, -17.3651081, -21.516044999999995, -19.071197074, -21.590888999999997);
rr_renderer_bezier_curve_to(renderer, -20.777282274, -21.66572573, -27.170532074, -16.266425999999996, -29.419986074, -13.491935999999997);
rr_renderer_bezier_curve_to(renderer, -31.669440574, -10.717437999999998, -31.855780874, -7.2311859999999974, -32.567923874, -4.943923999999997);
rr_renderer_fill(renderer);
rr_renderer_set_fill(renderer, 0xff7f6342);
rr_renderer_begin_path(renderer);
rr_renderer_move_to(renderer, 32.589200000000005, -4.943160000000006);
rr_renderer_bezier_curve_to(renderer, 33.301342940000005, -2.655898000000006, 34.745099, -0.6302020000000059, 33.714116100000005, 0.23238469999999367);
rr_renderer_bezier_curve_to(renderer, 32.683133100000006, 1.0949716999999937, 28.380871800000005, 0.9823312999999937, 26.403294600000006, 0.23238469999999367);
rr_renderer_bezier_curve_to(renderer, 24.425709800000007, -0.5175619000000063, 23.048390400000006, -2.054869600000006, 21.848630000000007, -4.267287300000007);
rr_renderer_bezier_curve_to(renderer, 20.64886960000001, -6.479704900000007, 19.664090200000008, -10.154975000000007, 19.204732000000007, -13.042113300000006);
rr_renderer_bezier_curve_to(renderer, 18.745366160000007, -15.929251700000005, 17.386380300000006, -21.515273300000004, 19.092465460000007, -21.590117300000006);
rr_renderer_bezier_curve_to(renderer, 20.798558260000007, -21.664954030000008, 27.191800460000007, -16.26565430000001, 29.441258460000007, -13.491164300000007);
rr_renderer_bezier_curve_to(renderer, 31.690716760000008, -10.716666300000007, 31.877057060000006, -7.230414300000007, 32.58920006000001, -4.943160300000006);
rr_renderer_fill(renderer);
rr_renderer_set_fill(renderer, 0xff95754f);
rr_renderer_begin_path(renderer);
rr_renderer_move_to(renderer, -21.690216, -4.055250000000001);
rr_renderer_line_to(renderer, -15.265808, -55.582807);
rr_renderer_line_to(renderer, 15.255455000000001, -55.582807);
rr_renderer_line_to(renderer, 21.679863, -4.055250000000001);
rr_renderer_fill(renderer);
rr_renderer_set_fill(renderer, 0xff95754f);
rr_renderer_begin_path(renderer);
rr_renderer_move_to(renderer, -15.504350000000002, -52.665049999999994);
rr_renderer_bezier_curve_to(renderer, -15.504350000000002, -61.23198649999999, -8.559476000000002, -68.17685999999999, 0.007459999999998246, -68.17685999999999);
rr_renderer_bezier_curve_to(renderer, 4.121450999999999, -68.17685999999999, 8.066938999999998, -66.54258649999998, 10.975965999999998, -63.633555599999994);
rr_renderer_bezier_curve_to(renderer, 13.884992999999998, -60.72452859999999, 15.519270399999998, -56.7790366, 15.519270399999998, -52.665049599999996);
rr_renderer_bezier_curve_to(renderer, 15.519270399999998, -44.0981166, 8.574392799999998, -37.15323959999999, 0.007460399999997591, -37.15323959999999);
rr_renderer_bezier_curve_to(renderer, -8.559476100000003, -37.15323959999999, -15.504349600000003, -44.09811719999999, -15.504349600000003, -52.66504959999999);
rr_renderer_fill(renderer);
rr_renderer_set_fill(renderer, 0xffb8b8b8);
rr_renderer_begin_path(renderer);
rr_renderer_move_to(renderer, 18.464569999999995, 51.25460000000001);
rr_renderer_line_to(renderer, -0.007873000000003572, 65.45932700000002);
rr_renderer_line_to(renderer, -18.480316000000002, 51.25460000000002);
rr_renderer_fill(renderer);
rr_renderer_set_fill(renderer, 0xff7f6342);
rr_renderer_begin_path(renderer);
rr_renderer_move_to(renderer, 29.977645999999993, 24.616780000000006);
rr_renderer_bezier_curve_to(renderer, 29.977645999999993, 21.459629700000004, 32.53702559999999, 18.900242500000004, 35.69417599999999, 18.900242500000004);
rr_renderer_bezier_curve_to(renderer, 37.21029689999999, 18.900242500000004, 38.664322199999994, 19.502522160000005, 39.73638199999999, 20.574574200000004);
rr_renderer_bezier_curve_to(renderer, 40.808441599999995, 21.646641500000005, 41.410713699999995, 23.100666700000005, 41.410713699999995, 24.616780200000004);
rr_renderer_bezier_curve_to(renderer, 41.410713699999995, 27.773930500000006, 38.851334099999995, 30.333317700000006, 35.694176199999994, 30.333317700000006);
rr_renderer_bezier_curve_to(renderer, 32.537025899999996, 30.333317700000006, 29.977646199999995, 27.773930500000006, 29.977646199999995, 24.616780200000004);
rr_renderer_fill(renderer);
}


void rr_ornithomimus_tail_draw(struct rr_renderer *renderer)
{
    rr_renderer_set_fill(renderer, 0xff585858);
    rr_renderer_begin_path(renderer);
    rr_renderer_move_to(renderer, -27.583015000000003, 110.9932);
    rr_renderer_bezier_curve_to(renderer, -27.583015000000003, 126.7609,
                                -14.799675000000002, 139.543127,
                                0.9693759999999969, 139.543127);
    rr_renderer_bezier_curve_to(renderer, 8.541938999999996, 139.543127,
                                15.804351999999996, 136.5351924,
                                21.158965999999996, 131.181036);
    rr_renderer_bezier_curve_to(
        renderer, 26.513580299999994, 125.82691000000001, 29.521766999999997,
        118.56513000000001, 29.521766999999997, 110.9932);
    rr_renderer_bezier_curve_to(renderer, 29.521766999999997, 95.22553,
                                16.738426999999994, 82.443304,
                                0.9693759999999969, 82.443304);
    rr_renderer_bezier_curve_to(renderer, -14.799675000000002, 82.443304,
                                -27.583015000000003, 95.225531,
                                -27.583015000000003, 110.9932);
    rr_renderer_fill(renderer);
    rr_renderer_set_fill(renderer, 0xff585858);
    rr_renderer_begin_path(renderer);
    rr_renderer_move_to(renderer, -8.726100000000002, 140.90949999999998);
    rr_renderer_bezier_curve_to(
        renderer, -8.726100000000002, 146.25871259999997, -4.389331000000002,
        150.59510799999998, 0.960346999999997, 150.59510799999998);
    rr_renderer_bezier_curve_to(renderer, 3.529354899999997, 150.59510799999998,
                                5.9931379999999965, 149.57466119999998,
                                7.809704599999997, 147.758255);
    rr_renderer_bezier_curve_to(renderer, 9.626263399999997, 145.9418488,
                                10.646794099999997, 143.47828669999998,
                                10.646794099999997, 140.90949999999998);
    rr_renderer_bezier_curve_to(renderer, 10.646794099999997, 135.5602874,
                                6.310025099999997, 131.22389199999998,
                                0.9603470999999981, 131.22389199999998);
    rr_renderer_bezier_curve_to(
        renderer, -4.389330900000002, 131.22389199999998, -8.726099900000001,
        135.56028729999997, -8.726099900000001, 140.90949999999998);
    rr_renderer_fill(renderer);
    rr_renderer_set_fill(renderer, 0xff585858);
    rr_renderer_begin_path(renderer);
    rr_renderer_move_to(renderer, 22.2568, 129.4663);
    rr_renderer_line_to(renderer, 8.642816999999999, 146.77589999999998);
    rr_renderer_line_to(renderer, 7.129740199999999, 137.02916499999998);
    rr_renderer_fill(renderer);
    rr_renderer_set_fill(renderer, 0xff585858);
    rr_renderer_begin_path(renderer);
    rr_renderer_move_to(renderer, -20.450905000000006, 129.4663);
    rr_renderer_line_to(renderer, -6.836922000000007, 146.77589999999998);
    rr_renderer_line_to(renderer, -5.323845200000006, 137.02916499999998);
    rr_renderer_fill(renderer);
    rr_renderer_set_fill(renderer, 0xff585858);
    rr_renderer_begin_path(renderer);
    rr_renderer_move_to(renderer, 8.928479999999993, 95.89963);
    rr_renderer_bezier_curve_to(renderer, 2.2588859999999933, 110.187502,
                                -14.731531000000007, 116.363833,
                                -29.02067000000001, 109.694827);
    rr_renderer_bezier_curve_to(renderer, -35.88255500000001, 106.4922513,
                                -41.19106900000001, 100.695193,
                                -43.77839500000001, 93.578982);
    rr_renderer_bezier_curve_to(renderer, -46.36572490000001, 86.4627405,
                                -46.01992260000001, 78.610247,
                                -42.81706840000001, 71.748965);
    rr_renderer_bezier_curve_to(renderer, -36.14747080000001, 57.461062,
                                -19.15705340000001, 51.284746999999996,
                                -4.867914400000011, 57.953768);
    rr_renderer_bezier_curve_to(renderer, 9.42122459999999, 64.6227743,
                                15.59808159999999, 81.611712, 8.928479599999989,
                                95.899628);
    rr_renderer_fill(renderer);
    rr_renderer_set_fill(renderer, 0xff585858);
    rr_renderer_begin_path(renderer);
    rr_renderer_move_to(renderer, -20.819466000000006, 115.03030000000001);
    rr_renderer_bezier_curve_to(
        renderer, -23.079330800000005, 119.87960400000001, -28.842781000000006,
        121.97890840000001, -33.692486, 119.71923430000001);
    rr_renderer_bezier_curve_to(
        renderer, -36.021396800000005, 118.63409030000001, -37.8238184,
        116.66833100000001, -38.7032396, 114.25439050000001);
    rr_renderer_bezier_curve_to(
        renderer, -39.582657000000005, 111.84041950000001, -39.467037360000006,
        109.17602150000002, -38.3818132, 106.84731650000002);
    rr_renderer_bezier_curve_to(renderer, -36.1219484, 101.99804280000002,
                                -30.358505200000003, 99.89873850000002,
                                -25.508797200000004, 102.15841250000003);
    rr_renderer_bezier_curve_to(
        renderer, -20.659088600000004, 104.41808650000003, -18.559601200000003,
        110.18102650000003, -20.819466200000004, 115.03029950000003);
    rr_renderer_fill(renderer);
    rr_renderer_set_fill(renderer, 0xff585858);
    rr_renderer_begin_path(renderer);
    rr_renderer_move_to(renderer, -44.058075, 91.55540000000002);
    rr_renderer_line_to(renderer, -39.036423, 113.00419200000002);
    rr_renderer_line_to(renderer, -33.542748, 104.80790300000001);
    rr_renderer_fill(renderer);
    rr_renderer_set_fill(renderer, 0xff585858);
    rr_renderer_begin_path(renderer);
    rr_renderer_move_to(renderer, -5.344930000000005, 109.61471999999998);
    rr_renderer_line_to(renderer, -25.007306000000003, 119.55060299999998);
    rr_renderer_line_to(renderer, -22.257046600000002, 110.07474199999999);
    rr_renderer_fill(renderer);
    rr_renderer_set_fill(renderer, 0xff585858);
    rr_renderer_begin_path(renderer);
    rr_renderer_move_to(renderer, -7.196470000000005, 66.6028);
    rr_renderer_bezier_curve_to(renderer, -16.975881000000005, 78.970979,
                                -34.930925, 81.0702835, -47.300184, 71.291719);
    rr_renderer_bezier_curve_to(renderer, -53.24011, 66.5958877, -57.071176,
                                59.732973, -57.9505975, 52.212709000000004);
    rr_renderer_bezier_curve_to(renderer, -58.8300149, 44.692460600000004,
                                -56.6857507, 37.13090700000001, -51.9895112,
                                31.191499000000004);
    rr_renderer_bezier_curve_to(renderer, -42.2101002, 18.823320000000002,
                                -24.255056200000002, 16.724015500000004,
                                -11.885801200000003, 26.502580000000002);
    rr_renderer_bezier_curve_to(renderer, 0.4834537999999977, 36.281144,
                                2.5829407999999976, 54.23462000000001,
                                -7.196470200000003, 66.6028);
    rr_renderer_fill(renderer);
    rr_renderer_set_fill(renderer, 0xff585858);
    rr_renderer_begin_path(renderer);
    rr_renderer_move_to(renderer, -40.54199, 78.36797000000001);
    rr_renderer_bezier_curve_to(renderer, -43.8617913, 82.56734130000001,
                                -49.957589999999996, 83.28062870000001,
                                -54.157334999999996, 79.96110960000001);
    rr_renderer_bezier_curve_to(renderer, -56.17412349999999, 78.36702390000002,
                                -57.4750077, 76.03712890000001,
                                -57.773809199999995, 73.48398260000002);
    rr_renderer_bezier_curve_to(
        renderer, -58.072606799999996, 70.93083620000002, -57.344846499999996,
        68.36356020000002, -55.750619699999994, 66.34694360000002);
    rr_renderer_bezier_curve_to(
        renderer, -52.43081839999999, 62.147572300000014, -46.335023699999994,
        61.434284900000016, -42.1352747, 64.75380400000002);
    rr_renderer_bezier_curve_to(renderer, -37.9355297, 68.07330780000002,
                                -37.2221887, 74.16858400000001, -40.5419901,
                                78.36797000000001);
    rr_renderer_fill(renderer);
    rr_renderer_set_fill(renderer, 0xff585858);
    rr_renderer_begin_path(renderer);
    rr_renderer_move_to(renderer, -57.748238, 50.17819);
    rr_renderer_line_to(renderer, -57.809509667, 72.202223);
    rr_renderer_line_to(renderer, -50.574848667, 65.4952986);
    rr_renderer_fill(renderer);
    rr_renderer_set_fill(renderer, 0xff585858);
    rr_renderer_begin_path(renderer);
    rr_renderer_move_to(renderer, -24.246260000000007, 76.67169000000001);
    rr_renderer_line_to(renderer, -45.665915000000005, 81.80392270000002);
    rr_renderer_line_to(renderer, -40.80505230000001, 73.21963270000002);
    rr_renderer_fill(renderer);
    rr_renderer_set_fill(renderer, 0xff585858);
    rr_renderer_begin_path(renderer);
    rr_renderer_move_to(renderer, -18.978790000000004, 32.61564999999999);
    rr_renderer_bezier_curve_to(
        renderer, -28.338226000000006, 45.30379099999999, -46.212208000000004,
        48.002887999999984, -58.901443, 38.64425999999999);
    rr_renderer_bezier_curve_to(renderer, -64.995031, 34.150103999999985,
                                -69.053583, 27.419543999999988, -70.184265,
                                19.93324599999999);
    rr_renderer_bezier_curve_to(renderer, -71.31494699999999, 12.44694839999999,
                                -69.42514023999999, 4.81813399999999,
                                -64.93057999999999, -1.2749140000000097);
    rr_renderer_bezier_curve_to(
        renderer, -55.57114399999999, -13.96305500000001, -37.69716199999999,
        -16.66215200000001, -25.007926999999995, -7.303524000000009);
    rr_renderer_bezier_curve_to(
        renderer, -12.318687499999996, 2.055102999999991, -9.619353999999996,
        19.92752499999999, -18.978790299999996, 32.61564999999999);
    rr_renderer_fill(renderer);
    rr_renderer_set_fill(renderer, 0xff585858);
    rr_renderer_begin_path(renderer);
    rr_renderer_move_to(renderer, -51.906487, 45.48917);
    rr_renderer_bezier_curve_to(renderer, -55.0862966, 49.798542, -61.157776,
                                50.714451000000004, -65.467516, 47.5349158);
    rr_renderer_bezier_curve_to(renderer, -67.53712660000001,
                                46.008045100000004, -68.915373, 43.7216528,
                                -69.299059, 41.1786841);
    rr_renderer_bezier_curve_to(renderer, -69.68274316, 38.6357153,
                                -69.04043588, 36.0444981, -67.5134393,
                                33.9750708);
    rr_renderer_bezier_curve_to(renderer, -64.3336297, 29.665698799999998,
                                -58.2621503, 28.7497898, -53.9524113,
                                31.929325);
    rr_renderer_bezier_curve_to(renderer, -49.6426693, 35.10886, -48.7266803,
                                41.179812999999996, -51.9064862, 45.48917);
    rr_renderer_fill(renderer);
    rr_renderer_set_fill(renderer, 0xff585858);
    rr_renderer_begin_path(renderer);
    rr_renderer_move_to(renderer, -70.056574, 17.894839999999988);
    rr_renderer_line_to(renderer, -69.3762895, 39.90831399999999);
    rr_renderer_line_to(renderer, -62.371586, 32.96170449999999);
    rr_renderer_fill(renderer);
    rr_renderer_set_fill(renderer, 0xff585858);
    rr_renderer_begin_path(renderer);
    rr_renderer_move_to(renderer, -35.682636, 43.246430000000004);
    rr_renderer_line_to(renderer, -56.917213000000004, 49.096772);
    rr_renderer_line_to(renderer, -52.3481594, 40.353776);
    rr_renderer_fill(renderer);
    rr_renderer_set_fill(renderer, 0xff585858);
    rr_renderer_begin_path(renderer);
    rr_renderer_move_to(renderer, -27.043189999999996, -32.668560000000014);
    rr_renderer_bezier_curve_to(renderer, -36.402626, -24.439770000000014,
                                -50.661282, -25.355678500000014,
                                -58.890784999999994, -34.71430580000001);
    rr_renderer_bezier_curve_to(renderer, -62.8427313, -39.208476800000014,
                                -64.8473604, -45.088336800000015,
                                -64.46367599999999, -51.06039780000001);
    rr_renderer_bezier_curve_to(renderer, -64.07998993, -57.03246680000001,
                                -61.339419899999996, -62.60752480000001,
                                -56.84485959999999, -66.55912380000001);
    rr_renderer_bezier_curve_to(
        renderer, -47.48542359999999, -74.78791380000001, -33.22677159999999,
        -73.87200530000001, -24.99726859999999, -64.513378);
    rr_renderer_bezier_curve_to(renderer, -16.767761599999993, -55.154758,
                                -17.683753899999992, -40.897343000000006,
                                -27.04318989999999, -32.66856);
    rr_renderer_fill(renderer);
    rr_renderer_set_fill(renderer, 0xff585858);
    rr_renderer_begin_path(renderer);
    rr_renderer_move_to(renderer, -54.64363, -28.24387999999999);
    rr_renderer_bezier_curve_to(renderer, -57.8234396, -25.45429869999999,
                                -62.662787, -25.77039979999999, -65.4526205,
                                -28.94993469999999);
    rr_renderer_bezier_curve_to(renderer, -66.792346, -30.47680539999999,
                                -67.4706011, -32.47328069999999,
                                -67.33817769999999, -34.50019719999999);
    rr_renderer_bezier_curve_to(
        renderer, -67.20575619999998, -36.527098399999986, -66.27350329999999,
        -38.41837959999999, -64.74650469999999, -39.75797919999999);
    rr_renderer_bezier_curve_to(
        renderer, -61.56669889999999, -42.54757579999999, -56.72734769999999,
        -42.23146709999999, -53.93751419999999, -39.051939799999985);
    rr_renderer_bezier_curve_to(
        renderer, -51.14768119999999, -35.872404799999984, -51.46382039999999,
        -31.033476799999985, -54.643629899999986, -28.243879799999988);
    rr_renderer_fill(renderer);
    rr_renderer_set_fill(renderer, 0xff585858);
    rr_renderer_begin_path(renderer);
    rr_renderer_move_to(renderer, -64.027004, -52.626720000000006);
    rr_renderer_line_to(renderer, -67.2041566, -35.500476000000006);
    rr_renderer_line_to(renderer, -60.622497300000006, -39.69070730000001);
    rr_renderer_fill(renderer);
    rr_renderer_set_fill(renderer, 0xff585858);
    rr_renderer_begin_path(renderer);
    rr_renderer_move_to(renderer, -41.726067, -27.258440000000007);
    rr_renderer_line_to(renderer, -59.120057, -26.308580400000007);
    rr_renderer_line_to(renderer, -54.1184777, -32.296678400000005);
    rr_renderer_fill(renderer);
    rr_renderer_set_fill(renderer, 0xff585858);
    rr_renderer_begin_path(renderer);
    rr_renderer_move_to(renderer, -28.907880000000006, -58.485985);
    rr_renderer_bezier_curve_to(renderer, -37.32737100000001, -53.516716,
                                -48.181459000000004, -56.3130877,
                                -53.15115900000001, -64.73185);
    rr_renderer_bezier_curve_to(renderer, -55.53769460000001,
                                -68.77468139999999, -56.22033470000001,
                                -73.599892, -55.04890600000001, -78.145989);
    rr_renderer_bezier_curve_to(renderer, -53.87747730000001, -82.6920934,
                                -50.94794240000001, -86.586693,
                                -46.904756000000006, -88.973015);
    rr_renderer_bezier_curve_to(renderer, -38.485265000000005, -93.942284,
                                -27.631177000000005, -91.14592,
                                -22.661474000000005, -82.7271578);
    rr_renderer_bezier_curve_to(renderer, -17.691778000000006, -74.3083958,
                                -20.488386000000006, -63.4552538,
                                -28.907880600000006, -58.4859848);
    rr_renderer_fill(renderer);
    rr_renderer_set_fill(renderer, 0xff585858);
    rr_renderer_begin_path(renderer);
    rr_renderer_move_to(renderer, -50.82196, -59.12065);
    rr_renderer_bezier_curve_to(renderer, -53.681788999999995,
                                -57.440901499999995, -57.361964699999994,
                                -58.3973376, -59.041861999999995, -61.2569186);
    rr_renderer_bezier_curve_to(renderer, -59.84857889999999, -62.6301333,
                                -60.0766978, -64.26754629999999, -59.67603635,
                                -65.80894359999999);
    rr_renderer_bezier_curve_to(renderer, -59.275374879999994,
                                -67.35034069999999, -58.278750849999994,
                                -68.669463, -56.90541405, -69.47610359999999);
    rr_renderer_bezier_curve_to(renderer, -54.04558505, -71.15585979999999,
                                -50.36540935, -70.19942359999999, -48.68551205,
                                -67.33984259999998);
    rr_renderer_bezier_curve_to(renderer, -47.00561095, -64.48026159999998,
                                -47.96213485, -60.800406299999985, -50.82196005,
                                -59.120650099999985);
    rr_renderer_fill(renderer);
    rr_renderer_set_fill(renderer, 0xff585858);
    rr_renderer_begin_path(renderer);
    rr_renderer_move_to(renderer, -54.47665, -79.2931);
    rr_renderer_line_to(renderer, -59.433208, -66.561487);
    rr_renderer_line_to(renderer, -53.7479015, -68.8265245);
    rr_renderer_fill(renderer);
    rr_renderer_set_fill(renderer, 0xff585858);
    rr_renderer_begin_path(renderer);
    rr_renderer_move_to(renderer, -41.012238, -56.476659999999995);
    rr_renderer_line_to(renderer, -54.554543, -58.291860799999995);
    rr_renderer_line_to(renderer, -49.823471500000004, -62.173658599999996);
    rr_renderer_fill(renderer);
    rr_renderer_set_fill(renderer, 0xff585858);
    rr_renderer_begin_path(renderer);
    rr_renderer_move_to(renderer, -8.92729, 95.89409999999998);
    rr_renderer_bezier_curve_to(
        renderer, -2.257688599999999, 110.18200299999998, 14.732728999999999,
        116.35830299999998, 29.021867999999998, 109.68929699999998);
    rr_renderer_bezier_curve_to(
        renderer, 35.883760699999996, 106.48672129999999, 41.192263,
        100.68966299999998, 43.779589, 93.57345199999997);
    rr_renderer_bezier_curve_to(renderer, 46.366915, 86.45722599999998,
                                46.0211204, 78.60473249999997, 42.81827003,
                                71.74344999999997);
    rr_renderer_bezier_curve_to(renderer, 36.14866863, 57.45554699999997,
                                19.158251030000002, 51.279231999999965,
                                4.869112030000004, 57.94823799999997);
    rr_renderer_bezier_curve_to(renderer, -9.420026969999997, 64.61725959999997,
                                -15.596883969999997, 81.60619699999997,
                                -8.927289969999997, 95.89409799999997);
    rr_renderer_fill(renderer);
    rr_renderer_set_fill(renderer, 0xff585858);
    rr_renderer_begin_path(renderer);
    rr_renderer_move_to(renderer, 20.820660000000004, 115.02480000000003);
    rr_renderer_bezier_curve_to(
        renderer, 23.080524800000003, 119.87407370000003, 28.843968000000004,
        121.97337800000003, 33.693676, 119.71370400000002);
    rr_renderer_bezier_curve_to(
        renderer, 36.022594500000004, 118.62859050000002, 37.8250084,
        116.66280070000002, 38.704433400000006, 114.24886020000002);
    rr_renderer_bezier_curve_to(renderer, 39.58385845000001, 111.83491980000002,
                                39.46822735000001, 109.17052160000003,
                                38.383007000000006, 106.84181670000002);
    rr_renderer_bezier_curve_to(renderer, 36.12314980000001, 101.99251270000002,
                                30.359692000000006, 99.89320830000003,
                                25.509991000000007, 102.15288240000002);
    rr_renderer_bezier_curve_to(
        renderer, 20.660282400000007, 104.41255640000003, 18.560795000000006,
        110.17549640000003, 20.820660000000007, 115.02480040000003);
    rr_renderer_fill(renderer);
    rr_renderer_set_fill(renderer, 0xff585858);
    rr_renderer_begin_path(renderer);
    rr_renderer_move_to(renderer, 44.05927, 91.54987);
    rr_renderer_line_to(renderer, 39.037617999999995, 112.998692);
    rr_renderer_line_to(renderer, 33.54395039999999, 104.802372);
    rr_renderer_fill(renderer);
    rr_renderer_set_fill(renderer, 0xff585858);
    rr_renderer_begin_path(renderer);
    rr_renderer_move_to(renderer, 5.346130000000002, 109.60919999999999);
    rr_renderer_line_to(renderer, 25.008506, 119.54511299999999);
    rr_renderer_line_to(renderer, 22.2582466, 110.06925199999999);
    rr_renderer_fill(renderer);
    rr_renderer_set_fill(renderer, 0xff585858);
    rr_renderer_begin_path(renderer);
    rr_renderer_move_to(renderer, 7.197670000000002, 66.59728999999999);
    rr_renderer_bezier_curve_to(renderer, 16.977081000000002, 78.96546899999998,
                                34.932129, 81.06475799999998,
                                47.301376000000005, 71.28620899999999);
    rr_renderer_bezier_curve_to(renderer, 53.241302000000005, 66.59037769999999,
                                57.072372, 59.727446999999984,
                                57.951797000000006, 52.20719899999999);
    rr_renderer_bezier_curve_to(renderer, 58.831206800000004, 44.68695059999999,
                                56.686950200000005, 37.12539699999999,
                                51.99070700000001, 31.18598899999999);
    rr_renderer_bezier_curve_to(renderer, 42.21130300000001, 18.817809999999987,
                                24.256256000000008, 16.71850549999999,
                                11.887001000000005, 26.497069999999987);
    rr_renderer_bezier_curve_to(
        renderer, -0.48225399999999574, 36.275618999999985, -2.5817409999999956,
        54.22910999999999, 7.197670000000005, 66.59728999999999);
    rr_renderer_fill(renderer);
    rr_renderer_set_fill(renderer, 0xff585858);
    rr_renderer_begin_path(renderer);
    rr_renderer_move_to(renderer, 40.54318000000001, 78.36243999999999);
    rr_renderer_bezier_curve_to(renderer, 43.862989000000006, 82.56182659999999,
                                49.95878400000001, 83.27509869999999,
                                54.15852100000001, 79.9555949);
    rr_renderer_bezier_curve_to(renderer, 56.17532100000001, 78.3615092,
                                57.476209000000004, 76.03161419999999,
                                57.775006600000005, 73.4784679);
    rr_renderer_bezier_curve_to(renderer, 58.073804200000005, 70.9253063,
                                57.346036260000005, 68.3580455,
                                55.75181320000001, 66.3414289);
    rr_renderer_bezier_curve_to(renderer, 52.43201950000001, 62.142057599999994,
                                46.336209200000006, 61.428770199999995,
                                42.13647220000001, 64.7482893);
    rr_renderer_bezier_curve_to(renderer, 37.936719200000006, 68.0677931,
                                37.22338620000001, 74.16306929999999,
                                40.54318000000001, 78.3624403);
    rr_renderer_fill(renderer);
    rr_renderer_set_fill(renderer, 0xff585858);
    rr_renderer_begin_path(renderer);
    rr_renderer_move_to(renderer, 57.74943999999999, 50.172680000000014);
    rr_renderer_line_to(renderer, 57.81070403799999, 72.19669700000001);
    rr_renderer_line_to(renderer, 50.57605433799999, 65.48978800000002);
    rr_renderer_fill(renderer);
    rr_renderer_set_fill(renderer, 0xff585858);
    rr_renderer_begin_path(renderer);
    rr_renderer_move_to(renderer, 24.247460000000004, 76.66618);
    rr_renderer_line_to(renderer, 45.667115, 81.7984127);
    rr_renderer_line_to(renderer, 40.8062446, 73.2141227);
    rr_renderer_fill(renderer);
    rr_renderer_set_fill(renderer, 0xff585858);
    rr_renderer_begin_path(renderer);
    rr_renderer_move_to(renderer, 18.97999, 32.61014);
    rr_renderer_bezier_curve_to(renderer, 28.339426000000003, 45.298281,
                                46.213411, 47.997378, 58.90265, 38.63875);
    rr_renderer_bezier_curve_to(renderer, 64.996232, 34.144579, 69.05478,
                                27.414034, 70.185456, 19.92772);
    rr_renderer_bezier_curve_to(renderer, 71.3161475, 12.4414224, 69.42633124,
                                4.812623, 64.9317786, -1.2804249999999975);
    rr_renderer_bezier_curve_to(renderer, 55.5723426, -13.968565999999997,
                                37.698364600000005, -16.667662999999997,
                                25.009125600000004, -7.309034999999997);
    rr_renderer_bezier_curve_to(
        renderer, 12.319886100000005, 2.0495770000000038, 9.620552600000005,
        19.922014, 18.979988900000006, 32.610139000000004);
    rr_renderer_fill(renderer);
    rr_renderer_set_fill(renderer, 0xff585858);
    rr_renderer_begin_path(renderer);
    rr_renderer_move_to(renderer, -25.299620000000004, 6.851820000000004);
    rr_renderer_bezier_curve_to(
        renderer, -37.458887000000004, 16.880339000000003, -55.44635600000001,
        15.153883000000004, -65.475752, 2.9956799000000034);
    rr_renderer_bezier_curve_to(renderer, -70.292036, -2.8428973999999965,
                                -72.591492, -10.355440099999996, -71.8682634,
                                -17.889269099999996);
    rr_renderer_bezier_curve_to(
        renderer, -71.14503495000001, -25.423097799999997, -67.45836270000001,
        -32.361086099999994, -61.619276400000004, -37.1769591);
    rr_renderer_bezier_curve_to(renderer, -49.460009400000004, -47.2054851,
                                -31.472540400000003, -45.479030099999996,
                                -21.4431444, -33.320819);
    rr_renderer_bezier_curve_to(renderer, -11.413748400000001, -21.162616,
                                -13.140356400000002, -3.1767150000000015,
                                -25.2996202, 6.851818999999999);
    rr_renderer_fill(renderer);
    rr_renderer_set_fill(renderer, 0xff585858);
    rr_renderer_begin_path(renderer);
    rr_renderer_move_to(renderer, -60.36096, 11.336989999999986);
    rr_renderer_bezier_curve_to(renderer, -64.490711, 14.736495599999985,
                                -70.59461399999999, 14.144790299999986,
                                -73.99441, 10.015410999999986);
    rr_renderer_bezier_curve_to(renderer, -75.6270489, 8.032393999999986,
                                -76.4050068, 5.482100999999986, -76.1571393,
                                2.9255671999999864);
    rr_renderer_bezier_curve_to(
        renderer, -75.90927171999999, 0.3690181999999864, -74.6558843,
        -1.9843602000000136, -72.6727071, -3.6168522000000136);
    rr_renderer_bezier_curve_to(renderer, -68.5429561, -7.016357800000014,
                                -62.4390511, -6.424667800000014,
                                -59.039256099999996, -2.295273200000014);
    rr_renderer_bezier_curve_to(
        renderer, -55.639464399999994, 1.8341212999999863, -56.231207899999994,
        7.937499799999986, -60.360960999999996, 11.336989799999987);
    rr_renderer_fill(renderer);
    rr_renderer_set_fill(renderer, 0xff585858);
    rr_renderer_begin_path(renderer);
    rr_renderer_move_to(renderer, -71.24536499999999, -19.86070000000001);
    rr_renderer_line_to(renderer, -75.9404086, 1.6628139999999902);
    rr_renderer_line_to(renderer, -67.45439859999999, -3.37327300000001);
    rr_renderer_fill(renderer);
    rr_renderer_set_fill(renderer, 0xff585858);
    rr_renderer_begin_path(renderer);
    rr_renderer_move_to(renderer, -44.06712, 13.094400000000007);
    rr_renderer_line_to(renderer, -66.09266, 13.605859350000006);
    rr_renderer_line_to(renderer, -59.53278829999999, 6.234445350000007);
    rr_renderer_fill(renderer);
    rr_renderer_set_fill(renderer, 0xff585858);
    rr_renderer_begin_path(renderer);
    rr_renderer_move_to(renderer, 25.30082, 6.846300000000014);
    rr_renderer_bezier_curve_to(renderer, 37.460084, 16.874834000000014,
                                55.447556000000006, 15.148378000000013,
                                65.476945, 2.9901751000000134);
    rr_renderer_bezier_curve_to(renderer, 70.293229, -2.8484173999999864,
                                72.592698, -10.360944899999986, 71.869462,
                                -17.894788899999988);
    rr_renderer_bezier_curve_to(renderer, 71.1462259, -25.42861759999999,
                                67.459565, -32.36660589999999, 61.620469,
                                -37.18246289999999);
    rr_renderer_bezier_curve_to(renderer, 49.461213, -47.21098889999999,
                                31.47374, -45.48454089999999, 21.444344,
                                -33.32632279999999);
    rr_renderer_bezier_curve_to(renderer, 11.414948, -21.168119799999992,
                                13.141549000000001, -3.182218799999994,
                                25.3008198, 6.846300200000009);
    rr_renderer_fill(renderer);
    rr_renderer_set_fill(renderer, 0xff585858);
    rr_renderer_begin_path(renderer);
    rr_renderer_move_to(renderer, 60.362150000000014, 11.331479999999999);
    rr_renderer_bezier_curve_to(renderer, 64.49191070000002, 14.730985599999999,
                                70.59580800000002, 14.1392803,
                                73.99560300000002, 10.0098858);
    rr_renderer_bezier_curve_to(renderer, 75.62824770000002, 8.0268841,
                                76.40620180000002, 5.476591099999999,
                                76.15833800000001, 2.9200419999999996);
    rr_renderer_bezier_curve_to(renderer, 75.91045897000001, 0.3635081999999996,
                                74.65707150000001, -1.9898700000000007,
                                72.67390200000001, -3.6223774000000004);
    rr_renderer_bezier_curve_to(renderer, 68.5441413, -7.021867800000001,
                                62.440244000000014, -6.4301777,
                                59.04044900000001, -2.3007832000000006);
    rr_renderer_bezier_curve_to(renderer, 55.640653500000006,
                                1.8286112999999995, 56.23240460000001,
                                7.9319748, 60.36215000000001, 11.3314798);
    rr_renderer_fill(renderer);
    rr_renderer_set_fill(renderer, 0xff585858);
    rr_renderer_begin_path(renderer);
    rr_renderer_move_to(renderer, 71.24656999999999, -19.866209999999995);
    rr_renderer_line_to(renderer, 75.94160799999999, 1.6573040000000034);
    rr_renderer_line_to(renderer, 67.45559999999999, -3.378798299999996);
    rr_renderer_fill(renderer);
    rr_renderer_set_fill(renderer, 0xff585858);
    rr_renderer_begin_path(renderer);
    rr_renderer_move_to(renderer, 44.06831, 13.088879999999989);
    rr_renderer_line_to(renderer, 66.093853, 13.600339349999988);
    rr_renderer_line_to(renderer, 59.53397749999999, 6.228940349999988);
    rr_renderer_fill(renderer);
    rr_renderer_set_fill(renderer, 0xff585858);
    rr_renderer_begin_path(renderer);
    rr_renderer_move_to(renderer, 51.90768, 45.483659999999986);
    rr_renderer_bezier_curve_to(renderer, 55.0874896, 49.79303199999998,
                                61.158962, 50.70894099999999, 65.468715,
                                47.529405799999985);
    rr_renderer_bezier_curve_to(renderer, 67.53832560000001, 46.00253509999999,
                                68.9165605, 43.716127599999986, 69.3002427,
                                41.17317409999998);
    rr_renderer_bezier_curve_to(renderer, 69.6839402, 38.630205299999986,
                                69.04162148, 36.03898809999998, 67.5146287,
                                33.96956079999998);
    rr_renderer_bezier_curve_to(renderer, 64.3348191, 29.660188799999982,
                                58.2633467, 28.744279799999983,
                                53.953608700000004, 31.923814999999983);
    rr_renderer_bezier_curve_to(
        renderer, 49.643855300000006, 35.103349999999985, 48.727870200000005,
        41.17428799999998, 51.9076797, 45.483659999999986);
    rr_renderer_fill(renderer);
    rr_renderer_set_fill(renderer, 0xff585858);
    rr_renderer_begin_path(renderer);
    rr_renderer_move_to(renderer, 70.05777, 17.88933);
    rr_renderer_line_to(renderer, 69.3774874, 39.902788);
    rr_renderer_line_to(renderer, 62.3727877, 32.9561785);
    rr_renderer_fill(renderer);
    rr_renderer_set_fill(renderer, 0xff585858);
    rr_renderer_begin_path(renderer);
    rr_renderer_move_to(renderer, 35.683840000000004, 43.24091999999999);
    rr_renderer_line_to(renderer, 56.918413, 49.091261999999986);
    rr_renderer_line_to(renderer, 52.3493517, 40.34825099999999);
    rr_renderer_fill(renderer);
    rr_renderer_set_fill(renderer, 0xff585858);
    rr_renderer_begin_path(renderer);
    rr_renderer_move_to(renderer, 27.044390000000007, -32.67407);
    rr_renderer_bezier_curve_to(renderer, 36.40382600000001, -24.44528,
                                50.66247800000001, -25.3611885,
                                58.891985000000005, -34.7198158);
    rr_renderer_bezier_curve_to(renderer, 62.843935, -39.2139868,
                                64.84855850000001, -45.0938548, 64.464876,
                                -51.0659158);
    rr_renderer_bezier_curve_to(renderer, 64.08119375, -57.037976799999996,
                                61.3406237, -62.6130348, 56.846056000000004,
                                -66.5646418);
    rr_renderer_bezier_curve_to(renderer, 47.48662, -74.79343180000001,
                                33.227968000000004, -73.8775158,
                                24.998468000000006, -64.518896);
    rr_renderer_bezier_curve_to(renderer, 16.768961000000004, -55.160269,
                                17.684953300000007, -40.902861,
                                27.044389300000006, -32.67407);
    rr_renderer_fill(renderer);
    rr_renderer_set_fill(renderer, 0xff585858);
    rr_renderer_begin_path(renderer);
    rr_renderer_move_to(renderer, 54.64482000000001, -28.249390000000005);
    rr_renderer_bezier_curve_to(
        renderer, 57.82462960000001, -25.459808700000004, 62.66398500000001,
        -25.775925000000004, 65.4538105, -28.955444700000005);
    rr_renderer_bezier_curve_to(renderer, 66.79354740000001,
                                -30.482315400000005, 67.4718005,
                                -32.478805900000005, 67.3393696, -34.5057072);
    rr_renderer_bezier_curve_to(renderer, 67.20695383, -36.5326084, 66.2747029,
                                -38.4238896, 64.7476948, -39.7635044);
    rr_renderer_bezier_curve_to(renderer, 61.56790050000001, -42.5530934,
                                56.72854480000001, -42.236977,
                                53.938704300000005, -39.0574497);
    rr_renderer_bezier_curve_to(renderer, 51.14887890000001, -35.8779147,
                                51.465025700000005, -31.0389867, 54.64482,
                                -28.249389700000002);
    rr_renderer_fill(renderer);
    rr_renderer_set_fill(renderer, 0xff585858);
    rr_renderer_begin_path(renderer);
    rr_renderer_move_to(renderer, 64.0282, -52.632225000000005);
    rr_renderer_line_to(renderer, 67.2053545, -35.50599700000001);
    rr_renderer_line_to(renderer, 60.6236895, -39.69622830000001);
    rr_renderer_fill(renderer);
    rr_renderer_set_fill(renderer, 0xff585858);
    rr_renderer_begin_path(renderer);
    rr_renderer_move_to(renderer, 41.72726, -27.263949999999994);
    rr_renderer_line_to(renderer, 59.121242, -26.314090399999994);
    rr_renderer_line_to(renderer, 54.1196703, -32.30218839999999);
    rr_renderer_fill(renderer);
    rr_renderer_set_fill(renderer, 0xff585858);
    rr_renderer_begin_path(renderer);
    rr_renderer_move_to(renderer, 28.909080000000003, -58.4915);
    rr_renderer_bezier_curve_to(renderer, 37.32856700000001,
                                -53.522231000000005, 48.18266200000001,
                                -56.318595, 53.152359000000004, -64.7373572);
    rr_renderer_bezier_curve_to(renderer, 55.538894600000006, -68.7801886,
                                56.221527, -73.60539920000001, 55.0501099,
                                -78.15150320000001);
    rr_renderer_bezier_curve_to(renderer, 53.8786774, -82.69760760000001,
                                50.9491425, -86.59220020000001, 46.9059599,
                                -88.97852920000001);
    rr_renderer_bezier_curve_to(renderer, 38.4864649, -93.94779820000001,
                                27.632377899999998, -91.15143420000001,
                                22.662673899999998, -82.73267200000001);
    rr_renderer_bezier_curve_to(renderer, 17.6929779, -74.31391,
                                20.489585899999998, -63.46076800000001,
                                28.909080499999998, -58.491499000000005);
    rr_renderer_fill(renderer);
    rr_renderer_set_fill(renderer, 0xff585858);
    rr_renderer_begin_path(renderer);
    rr_renderer_move_to(renderer, 50.823170000000005, -59.12617);
    rr_renderer_bezier_curve_to(renderer, 53.6829875, -57.4464138,
                                57.363163300000004, -58.402857600000004,
                                59.043064, -61.262431);
    rr_renderer_bezier_curve_to(renderer, 59.8497809, -62.6356534,
                                60.077899800000004, -64.2730664, 59.67723453,
                                -65.8144635);
    rr_renderer_bezier_curve_to(renderer, 59.27656925, -67.3558606, 58.27995673,
                                -68.6749753, 56.90661993, -69.4816235);
    rr_renderer_bezier_curve_to(renderer, 54.04678713, -71.161372, 50.36661143,
                                -70.2049359, 48.68670993, -67.3453549);
    rr_renderer_bezier_curve_to(renderer, 47.00680883, -64.4857739, 47.96333653,
                                -60.805918600000005, 50.82316933,
                                -59.12616990000001);
    rr_renderer_fill(renderer);
    rr_renderer_set_fill(renderer, 0xff585858);
    rr_renderer_begin_path(renderer);
    rr_renderer_move_to(renderer, 54.477839999999986, -79.29861);
    rr_renderer_line_to(renderer, 59.43439799999999, -66.566997);
    rr_renderer_line_to(renderer, 53.749095299999986, -68.8320422);
    rr_renderer_fill(renderer);
    rr_renderer_set_fill(renderer, 0xff585858);
    rr_renderer_begin_path(renderer);
    rr_renderer_move_to(renderer, 41.01343, -56.48218);
    rr_renderer_line_to(renderer, 54.555743, -58.2973732);
    rr_renderer_line_to(renderer, 49.824664, -62.179171000000004);
    rr_renderer_fill(renderer);
    rr_renderer_set_fill(renderer, 0xff6e6e6e);
    rr_renderer_begin_path(renderer);
    rr_renderer_move_to(renderer, -13.36582, 96.73649999999998);
    rr_renderer_bezier_curve_to(renderer, -21.245352, 104.61531469999998,
                                -21.245352, 117.38945399999997, -13.36582,
                                125.26829999999998);
    rr_renderer_quadratic_curve_to(renderer, -5.426297999999999,
                                   133.20711229999998, 0.9013230000000014,
                                   142.75770999999997);
    rr_renderer_quadratic_curve_to(renderer, 7.228944500000002,
                                   133.20711199999997, 15.168466000000002,
                                   125.26829999999998);
    rr_renderer_bezier_curve_to(
        renderer, 23.047990000000002, 117.38945499999998, 23.047990000000002,
        104.61531499999998, 15.168466000000002, 96.73649999999998);
    rr_renderer_bezier_curve_to(renderer, 7.288934000000002, 88.85765499999998,
                                -5.486295999999999, 88.85765499999998,
                                -13.36582, 96.73649999999998);
    rr_renderer_fill(renderer);
    rr_renderer_set_fill(renderer, 0xff6e6e6e);
    rr_renderer_begin_path(renderer);
    rr_renderer_move_to(renderer, 2.0716800000000006, 76.97227000000001);
    rr_renderer_bezier_curve_to(renderer, 5.8814487, 87.44073,
                                0.48277470000000067, 99.01525400000001,
                                -9.986593, 102.824672);
    rr_renderer_quadratic_curve_to(renderer, -20.535680999999997, 106.6631425,
                                   -30.305403, 112.64309200000001);
    rr_renderer_quadratic_curve_to(renderer, -32.0024817, 101.315638,
                                   -35.841260999999996, 90.767452);
    rr_renderer_bezier_curve_to(renderer, -39.6510335, 80.299007, -34.2523633,
                                68.724483, -23.782994999999996,
                                64.91505000000001);
    rr_renderer_bezier_curve_to(
        renderer, -13.313618999999996, 61.10560180000001, -1.7380879999999976,
        66.5038104, 2.071680000000004, 76.97227000000001);
    rr_renderer_fill(renderer);
    rr_renderer_set_fill(renderer, 0xff6e6e6e);
    rr_renderer_begin_path(renderer);
    rr_renderer_move_to(renderer, -9.494659999999996, 46.59720999999999);
    rr_renderer_bezier_curve_to(renderer, -8.204735399999997, 57.66556899999999,
                                -16.132515499999997, 67.683865,
                                -27.201850999999998, 68.97367499999999);
    rr_renderer_quadratic_curve_to(renderer, -38.355464999999995,
                                   70.27329659999998, -49.245209,
                                   73.83716999999999);
    rr_renderer_quadratic_curve_to(renderer, -48.28051784, 62.42066599999998,
                                   -49.580261500000006, 51.268016999999986);
    rr_renderer_bezier_curve_to(renderer, -50.8701823, 40.199657999999985,
                                -42.942402200000004, 30.181361999999986,
                                -31.873070500000004, 28.891551999999987);
    rr_renderer_bezier_curve_to(
        renderer, -20.803734500000004, 27.601741799999985, -10.784577500000005,
        35.52883529999998, -9.494660500000005, 46.59720999999999);
    rr_renderer_fill(renderer);
    rr_renderer_set_fill(renderer, 0xff6e6e6e);
    rr_renderer_begin_path(renderer);
    rr_renderer_move_to(renderer, -21.965100000000007, 12.697309999999987);
    rr_renderer_bezier_curve_to(
        renderer, -20.295201000000006, 23.715681999999987, -27.874417000000008,
        34.00144799999998, -38.893758000000005, 35.67120199999999);
    rr_renderer_quadratic_curve_to(renderer, -49.996999, 37.35366659999999,
                                   -60.758630000000004, 41.29014429999999);
    rr_renderer_quadratic_curve_to(renderer, -60.18703576, 29.846296299999988,
                                   -61.86965300000001, 18.74401729999999);
    rr_renderer_bezier_curve_to(renderer, -63.53955200000001, 7.725645299999989,
                                -55.960336000000005, -2.5601207000000095,
                                -44.940999000000005, -4.2298747000000105);
    rr_renderer_bezier_curve_to(
        renderer, -33.921662000000005, -5.899628700000011, -23.634999000000004,
        1.6789232999999895, -21.965100000000007, 12.697310299999991);
    rr_renderer_fill(renderer);
    rr_renderer_set_fill(renderer, 0xff6e6e6e);
    rr_renderer_begin_path(renderer);
    rr_renderer_move_to(renderer, -26.001589999999993, -48.57652);
    rr_renderer_bezier_curve_to(renderer, -26.561557039999993,
                                -39.777814000000006, -34.14887499999999,
                                -33.09895, -42.948347999999996, -33.658872);
    rr_renderer_quadratic_curve_to(renderer, -51.814817999999995,
                                   -34.223050470000004, -60.79584, -32.9873022);
    rr_renderer_quadratic_curve_to(renderer, -58.431517299999996, -41.7384542,
                                   -57.867289299999996, -50.604162200000005);
    rr_renderer_bezier_curve_to(renderer, -57.30732226, -59.402860200000006,
                                -49.720000299999995, -66.08172420000001,
                                -40.92053129999999, -65.52180320000001);
    rr_renderer_bezier_curve_to(renderer, -32.121058299999994, -64.96188956,
                                -25.44162229999999, -57.375219200000004,
                                -26.00158979999999, -48.57652120000001);
    rr_renderer_fill(renderer);
    rr_renderer_set_fill(renderer, 0xff6e6e6e);
    rr_renderer_begin_path(renderer);
    rr_renderer_move_to(renderer, -25.755260000000007, -70.56706);
    rr_renderer_bezier_curve_to(renderer, -27.485148900000006, -63.8780418,
                                -34.31050100000001, -59.857763,
                                -41.000099000000006, -61.587507);
    rr_renderer_quadratic_curve_to(renderer, -47.74063100000001, -63.3304269,
                                   -54.835048500000006, -63.704976800000004);
    rr_renderer_quadratic_curve_to(renderer, -51.723499100000005,
                                   -70.09107780000001, -49.980430500000004,
                                   -76.8310218);
    rr_renderer_bezier_curve_to(renderer, -48.250534, -83.52004, -41.4251895,
                                -87.5403188, -34.735591500000005, -85.8105748);
    rr_renderer_bezier_curve_to(renderer, -28.045993500000005, -84.0808308,
                                -24.025363500000005, -77.2560778,
                                -25.755260500000006, -70.5670598);
    rr_renderer_fill(renderer);
    rr_renderer_set_fill(renderer, 0xff6e6e6e);
    rr_renderer_begin_path(renderer);
    rr_renderer_move_to(renderer, -2.0704800000000034, 76.96674999999999);
    rr_renderer_bezier_curve_to(renderer, -5.880248700000003, 87.43520999999998,
                                -0.48158230000000346, 99.009734,
                                9.987792999999996, 102.81918199999998);
    rr_renderer_quadratic_curve_to(renderer, 20.536872999999996,
                                   106.65762199999999, 30.306602999999996,
                                   112.63757199999998);
    rr_renderer_quadratic_curve_to(renderer, 32.00367789999999,
                                   101.31011799999997, 35.842468999999994,
                                   90.76196199999998);
    rr_renderer_bezier_curve_to(renderer, 39.65223769999999, 80.29350199999999,
                                34.253555999999996, 68.71897799999998,
                                23.784187999999993, 64.90952999999999);
    rr_renderer_bezier_curve_to(renderer, 13.314819999999994, 61.10009699999999,
                                1.7392889999999923, 66.49829039999999,
                                -2.070480000000007, 76.96674999999999);
    rr_renderer_fill(renderer);
    rr_renderer_set_fill(renderer, 0xff6e6e6e);
    rr_renderer_begin_path(renderer);
    rr_renderer_move_to(renderer, 9.495859999999993, 46.59169);
    rr_renderer_bezier_curve_to(renderer, 8.205935399999994, 57.660065,
                                16.133715499999994, 67.67836,
                                27.203043999999995, 68.96817);
    rr_renderer_quadratic_curve_to(renderer, 38.35666199999999, 70.2677916,
                                   49.246401999999996, 73.831665);
    rr_renderer_quadratic_curve_to(renderer, 48.281710839999995, 62.415161,
                                   49.5814545, 51.262512);
    rr_renderer_bezier_curve_to(renderer, 50.871386799999996, 40.194137,
                                42.9436065, 30.175857, 31.874270499999998,
                                28.886047);
    rr_renderer_bezier_curve_to(renderer, 20.804934499999998, 27.5962368,
                                10.785777499999998, 35.5233303, 9.4958605,
                                46.59169);
    rr_renderer_fill(renderer);
    rr_renderer_set_fill(renderer, 0xff6e6e6e);
    rr_renderer_begin_path(renderer);
    rr_renderer_move_to(renderer, 21.966300000000004, 12.691789999999997);
    rr_renderer_bezier_curve_to(renderer, 20.296401000000003,
                                23.710176999999998, 27.875617000000005,
                                33.995943, 38.894958, 35.665696999999994);
    rr_renderer_quadratic_curve_to(renderer, 49.998199, 37.3481616,
                                   60.759826000000004, 41.284639299999995);
    rr_renderer_quadratic_curve_to(renderer, 60.18823176, 29.840791299999996,
                                   61.87084900000001, 18.738512299999996);
    rr_renderer_bezier_curve_to(renderer, 63.540755600000004, 7.720140299999997,
                                55.961532000000005, -2.565625700000002,
                                44.942199, -4.235379700000003);
    rr_renderer_bezier_curve_to(renderer, 33.922866, -5.905133700000003,
                                23.636199, 1.6734182999999971,
                                21.966300000000004, 12.691790299999997);
    rr_renderer_fill(renderer);
    rr_renderer_set_fill(renderer, 0xff6e6e6e);
    rr_renderer_begin_path(renderer);
    rr_renderer_move_to(renderer, -23.324349999999995, -13.183150000000012);
    rr_renderer_bezier_curve_to(
        renderer, -24.394288699999997, -2.0947860000000116, -34.251321,
        6.026840999999987, -45.340654, 4.957001999999989);
    rr_renderer_quadratic_curve_to(renderer, -56.514421, 3.8790142999999886,
                                   -67.90706800000001, 5.069352463999989);
    rr_renderer_quadratic_curve_to(renderer, -64.56045900000001,
                                   -5.884596536000011, -63.48237400000001,
                                   -17.057387536000014);
    rr_renderer_bezier_curve_to(
        renderer, -62.41243920000001, -28.145751536000013, -52.555406000000005,
        -36.26737853600001, -41.466074000000006, -35.197539536000015);
    rr_renderer_bezier_curve_to(
        renderer, -30.376741000000006, -34.127700036000014, -22.254412000000006,
        -24.271514536000016, -23.324350000000006, -13.183150536000014);
    rr_renderer_fill(renderer);
    rr_renderer_set_fill(renderer, 0xff6e6e6e);
    rr_renderer_begin_path(renderer);
    rr_renderer_move_to(renderer, 23.325550000000007, -13.188659999999999);
    rr_renderer_bezier_curve_to(
        renderer, 24.395481000000007, -2.1002959999999984, 34.25252100000001,
        6.021331, 45.341846000000004, 4.951477000000001);
    rr_renderer_quadratic_curve_to(renderer, 56.51562800000001,
                                   3.8734893000000006, 67.908268, 5.06384272);
    rr_renderer_quadratic_curve_to(renderer, 64.56164930000001,
                                   -5.8901062799999995, 63.48357000000001,
                                   -17.06289728);
    rr_renderer_bezier_curve_to(renderer, 62.41363900000001, -28.15127628,
                                52.556599000000006, -36.272888280000004,
                                41.467274, -35.20304928);
    rr_renderer_bezier_curve_to(renderer, 30.377941000000003, -34.13320978,
                                22.255612000000003, -24.277024280000003,
                                23.325550000000003, -13.18866028);
    rr_renderer_fill(renderer);
    rr_renderer_set_fill(renderer, 0xff6e6e6e);
    rr_renderer_begin_path(renderer);
    rr_renderer_move_to(renderer, 26.002785000000003, -48.58203);
    rr_renderer_bezier_curve_to(renderer, 26.562752040000003,
                                -39.78332400000001, 34.15007,
                                -33.104476000000005, 42.949539, -33.664382);
    rr_renderer_quadratic_curve_to(renderer, 51.816009, -34.2285757, 60.797043,
                                   -32.9928122);
    rr_renderer_quadratic_curve_to(renderer, 58.432709, -41.7439722, 57.8684847,
                                   -50.609672200000006);
    rr_renderer_bezier_curve_to(renderer, 57.30851766000001, -59.4083782,
                                49.721191700000006, -66.08723420000001,
                                40.921722700000004, -65.5273202);
    rr_renderer_bezier_curve_to(renderer, 32.1222537, -64.96739894000001,
                                25.442817700000006, -57.3807362,
                                26.002784700000003, -48.582030200000005);
    rr_renderer_fill(renderer);
    rr_renderer_set_fill(renderer, 0xff6e6e6e);
    rr_renderer_begin_path(renderer);
    rr_renderer_move_to(renderer, 25.75645, -70.57258);
    rr_renderer_bezier_curve_to(renderer, 27.4863465, -63.8835618, 34.311694,
                                -59.863275, 41.0013, -61.593027000000006);
    rr_renderer_quadratic_curve_to(renderer, 47.7418243, -63.33593930000001,
                                   54.836246, -63.71049680000001);
    rr_renderer_quadratic_curve_to(renderer, 51.724689000000005, -70.0965898,
                                   49.9816317, -76.8365418);
    rr_renderer_bezier_curve_to(renderer, 48.2517275, -83.52555240000001,
                                41.4263797, -87.54583880000001,
                                34.736788700000005, -85.8160948);
    rr_renderer_bezier_curve_to(renderer, 28.047190700000005, -84.0863432,
                                24.026552700000003, -77.26159080000001,
                                25.756449700000005, -70.5725798);
    rr_renderer_fill(renderer);
    rr_renderer_set_fill(renderer, 0xffa7a7a7);
    rr_renderer_begin_path(renderer);
    rr_renderer_move_to(renderer, 48.070359999999994, -81.05086);
    rr_renderer_line_to(renderer, 14.953249999999997, 86.32809);
    rr_renderer_line_to(renderer, -15.069210000000002, 86.32809);
    rr_renderer_line_to(renderer, -48.186317, -81.05086);
    rr_renderer_fill(renderer);
    rr_renderer_set_fill(renderer, 0xffa7a7a7);
    rr_renderer_begin_path(renderer);
    rr_renderer_move_to(renderer, -49.591743, -93.45048);
    rr_renderer_bezier_curve_to(renderer, -49.591743, -125.010401, -27.41233,
                                -150.594775, -0.05263300000000015, -150.594775);
    rr_renderer_bezier_curve_to(renderer, 13.085955, -150.594775, 25.686427,
                                -144.574233, 34.976807, -133.8576);
    rr_renderer_bezier_curve_to(renderer, 44.267197, -123.14096299999999,
                                49.486481, -108.60609, 49.486481, -93.45048);
    rr_renderer_bezier_curve_to(renderer, 49.486481, -61.890558999999996,
                                27.307060999999997, -36.306185,
                                -0.05263500000000221, -36.306185);
    rr_renderer_bezier_curve_to(renderer, -27.41233, -36.306185, -49.591745,
                                -61.890558, -49.591745, -93.45048);
    rr_renderer_fill(renderer);
    rr_renderer_set_fill(renderer, 0xffa7a7a7);
    rr_renderer_begin_path(renderer);
    rr_renderer_move_to(renderer, -34.353218, -93.46389);
    rr_renderer_bezier_curve_to(renderer, -34.353218, -115.30687, -19.005501,
                                -133.014103, -0.07312799999999697, -133.014103);
    rr_renderer_bezier_curve_to(renderer, 9.018516000000004, -133.014103,
                                17.737792000000002, -128.8472176,
                                24.166557000000005, -121.430115);
    rr_renderer_bezier_curve_to(renderer, 30.595321300000005, -114.013012,
                                34.206970000000005, -103.95326299999999,
                                34.206970000000005, -93.46388999999999);
    rr_renderer_bezier_curve_to(
        renderer, 34.206970000000005, -71.62091799999999, 18.859245000000005,
        -53.91367999999999, -0.07312799999999697, -53.91367999999999);
    rr_renderer_bezier_curve_to(
        renderer, -19.005500999999995, -53.91367999999999, -34.353218,
        -71.62091699999999, -34.353218, -93.46388999999999);
    rr_renderer_fill(renderer);
    rr_renderer_set_fill(renderer, 0xffa7a7a7);
    rr_renderer_begin_path(renderer);
    rr_renderer_move_to(renderer, -15.190290000000005, 83.77832000000001);
    rr_renderer_bezier_curve_to(
        renderer, -15.190290000000005, 74.14198300000001, -8.416677000000004,
        66.33017000000001, -0.060995000000003685, 66.33017000000001);
    rr_renderer_bezier_curve_to(renderer, 3.951539999999996, 66.33017000000001,
                                7.799737999999996, 68.16845740000001,
                                10.637025999999997, 71.44061300000001);
    rr_renderer_bezier_curve_to(renderer, 13.474321499999997, 74.71278400000001,
                                15.068292999999997, 79.15078760000002,
                                15.068292999999997, 83.7783205);
    rr_renderer_bezier_curve_to(renderer, 15.068292999999997, 93.4146735,
                                8.294679999999996, 101.2264705,
                                -0.060995000000003685, 101.2264705);
    rr_renderer_bezier_curve_to(renderer, -8.416677000000004, 101.2264705,
                                -15.190290000000005, 93.41467250000001,
                                -15.190290000000005, 83.7783205);
    rr_renderer_fill(renderer);
    rr_renderer_set_fill(renderer, 0xffa7a7a7);
    rr_renderer_begin_path(renderer);
    rr_renderer_move_to(renderer, 32.97394, -82.90695);
    rr_renderer_line_to(renderer, -0.05752999999999986, 86.06115);
    rr_renderer_line_to(renderer, -33.08901, -82.90695);
    rr_renderer_fill(renderer);
    rr_renderer_set_fill(renderer, 0xffb8b8b8);
    rr_renderer_begin_path(renderer);
    rr_renderer_move_to(renderer, -34.342262, -93.44778);
    rr_renderer_bezier_curve_to(renderer, -34.342262, -115.29423499999999,
                                -18.992957999999998, -133.004287,
                                -0.0586319999999958, -133.004287);
    rr_renderer_bezier_curve_to(renderer, 9.033951000000004, -133.004287,
                                17.754128000000005, -128.836738,
                                24.183556000000003, -121.4184525);
    rr_renderer_bezier_curve_to(renderer, 30.612984000000004, -114.0001709,
                                34.224991, -103.9388225, 34.224991,
                                -93.4477795);
    rr_renderer_bezier_curve_to(renderer, 34.224991, -71.60132949999999,
                                18.875694000000003, -53.8912765,
                                -0.0586319999999958, -53.8912765);
    rr_renderer_bezier_curve_to(renderer, -18.992957999999994, -53.8912765,
                                -34.342262, -71.6013285, -34.342262,
                                -93.4477795);
    rr_renderer_fill(renderer);
    rr_renderer_set_fill(renderer, 0xffb8b8b8);
    rr_renderer_begin_path(renderer);
    rr_renderer_move_to(renderer, 32.98098999999999, -82.88664);
    rr_renderer_line_to(renderer, -0.05448000000000519, 86.07772);
    rr_renderer_line_to(renderer, -33.08995, -82.88664);
    rr_renderer_fill(renderer);
}


void rr_ornithomimus_wing1_draw(struct rr_renderer *renderer)
{
rr_renderer_set_fill(renderer, 0xff585858);
    rr_renderer_begin_path(renderer);
    rr_renderer_move_to(renderer, -48.543220000000005, 59.559200000000004);
    rr_renderer_line_to(renderer, -45.09598870000001, 75.47930500000001);
    rr_renderer_line_to(renderer, -35.86314720000001, 76.89554950000002);
    rr_renderer_line_to(renderer, -29.717788200000008, 73.80807090000002);
    rr_renderer_line_to(renderer, -24.189467900000007, 65.92542620000002);
    rr_renderer_line_to(renderer, -25.81745100000001, 59.89846390000002);
    rr_renderer_line_to(renderer, -19.18711040000001, 58.44808550000002);
    rr_renderer_line_to(renderer, -12.864150400000009, 46.72658850000002);
    rr_renderer_line_to(renderer, -15.755816800000009, 41.118571500000016);
    rr_renderer_line_to(renderer, -9.85408720000001, 39.56344150000002);
    rr_renderer_line_to(renderer, 0.04133679999999096, 20.93154450000002);
    rr_renderer_line_to(renderer, 27.664719799999993, 34.080668500000016);
    rr_renderer_line_to(renderer, -3.037040200000007, -23.251751499999983);
    rr_renderer_fill(renderer);
    rr_renderer_set_fill(renderer, 0xff6e6e6e);
    rr_renderer_begin_path(renderer);
    rr_renderer_move_to(renderer, 11.776489999999995, 18.310840000000013);
    rr_renderer_line_to(renderer, -2.085296000000005, 11.828494400000013);
    rr_renderer_line_to(renderer, -14.382846000000004, 35.526507400000014);
    rr_renderer_line_to(renderer, -22.686710000000005, 39.105792100000016);
    rr_renderer_line_to(renderer, -18.852405200000007, 47.15465110000002);
    rr_renderer_line_to(renderer, -21.98314630000001, 53.860126100000016);
    rr_renderer_line_to(renderer, -31.63038630000001, 55.87518650000002);
    rr_renderer_line_to(renderer, -29.13717650000001, 65.93454350000002);
    rr_renderer_line_to(renderer, -32.26791760000001, 69.95782850000002);
    rr_renderer_line_to(renderer, -37.18830490000001, 72.19374460000002);
    rr_renderer_line_to(renderer, -40.988456700000015, 71.30119700000002);
    rr_renderer_line_to(renderer, -44.56547170000002, 56.76773400000002);
    rr_renderer_line_to(renderer, -12.146926700000016, -7.623081999999982);
    rr_renderer_line_to(renderer, -1.1904677000000152, -9.412731999999982);
    rr_renderer_line_to(renderer, 12.894447299999985, 4.225917000000017);
    rr_renderer_fill(renderer);
    rr_renderer_set_fill(renderer, 0xffa7a7a7);
    rr_renderer_begin_path(renderer);
    rr_renderer_move_to(renderer, -48.109314, 63.46630999999999);
    rr_renderer_bezier_curve_to(renderer, -45.2362423, 70.72773899999999,
                                -23.043647999999997, 6.023842999999992,
                                -12.031787999999999, -2.705040000000011);
    rr_renderer_bezier_curve_to(
        renderer, -1.0199279999999984, -11.433929000000012, 14.257332000000002,
        15.440352999999988, 17.961852, 11.092986999999988);
    rr_renderer_bezier_curve_to(renderer, 21.6663732, 6.745620699999988,
                                18.06735127, -19.22814900000001, 10.1953344,
                                -28.78923800000001);
    rr_renderer_bezier_curve_to(renderer, 2.3233251, -38.35033400000001,
                                -19.5527776, -61.64950200000001,
                                -29.270222599999997, -46.27357500000001);
    rr_renderer_bezier_curve_to(
        renderer, -38.987664599999995, -30.897652000000008, -50.9823866,
        56.20487999999999, -48.1093146, 63.46630499999999);
    rr_renderer_fill(renderer);
    rr_renderer_set_fill(renderer, 0xffa7a7a7);
    rr_renderer_begin_path(renderer);
    rr_renderer_move_to(renderer, 38.064896000000005, -6.811070000000001);
    rr_renderer_bezier_curve_to(renderer, 43.85190600000001, -11.247525,
                                44.3771976, -19.037694000000002,
                                39.23816720000001, -24.210888);
    rr_renderer_line_to(renderer, -3.792075799999992, -67.527238);
    rr_renderer_bezier_curve_to(renderer, -6.2599254999999925, -70.0114947,
                                -9.730655399999993, -71.547681,
                                -13.440753799999992, -71.7978526);
    rr_renderer_bezier_curve_to(renderer, -17.150848299999993, -72.04802426,
                                -20.796397799999994, -70.9916888,
                                -23.575416799999992, -68.86122999999999);
    rr_renderer_bezier_curve_to(renderer, -29.362426799999994, -64.4247714,
                                -29.88771839999999, -56.634609999999995,
                                -24.74868799999999, -51.46140799999999);
    rr_renderer_line_to(renderer, 18.281555000000008, -8.145062999999993);
    rr_renderer_bezier_curve_to(renderer, 23.42058550000001, -2.971860499999993,
                                32.27788500000001, -2.3746159999999934,
                                38.06489500000001, -6.811070999999993);
    rr_renderer_fill(renderer);
    rr_renderer_set_fill(renderer, 0xffa7a7a7);
    rr_renderer_begin_path(renderer);
    rr_renderer_move_to(renderer, -12.154220000000002, -42.419106);
    rr_renderer_bezier_curve_to(renderer, -15.388938300000003,
                                -22.650275999999998, -45.06078,
                                59.914013999999995, -47.76043, 56.65805);
    rr_renderer_bezier_curve_to(renderer, -50.460076, 53.4020686,
                                -34.286474999999996, -45.44207999999999,
                                -28.35211, -61.95492999999999);
    rr_renderer_bezier_curve_to(renderer, -22.417742, -78.46779, -8.9195,
                                -62.187931709999994, -12.154222999999998,
                                -42.419101999999995);
    rr_renderer_fill(renderer);
    rr_renderer_set_fill(renderer, 0xffb8b8b8);
    rr_renderer_begin_path(renderer);
    rr_renderer_move_to(renderer, 36.203109999999995, -3.314009999999996);
    rr_renderer_bezier_curve_to(renderer, 40.428307, -6.550811099999996,
                                40.813041999999996, -12.236235999999996,
                                37.06243919999999, -16.012762999999996);
    rr_renderer_line_to(renderer, -4.684173800000011, -58.048002999999994);
    rr_renderer_bezier_curve_to(
        renderer, -6.485275500000011, -59.86155589999999, -9.01863120000001,
        -60.983363, -11.72692880000001, -61.16663629999999);
    rr_renderer_bezier_curve_to(
        renderer, -14.43522650000001, -61.349905799999995, -17.09661880000001,
        -60.57963449999999, -19.12562950000001, -59.02526739999999);
    rr_renderer_bezier_curve_to(
        renderer, -23.35082650000001, -55.78846629999999, -23.735565300000008,
        -50.10303339999999, -19.984966350000008, -46.32650639999999);
    rr_renderer_line_to(renderer, 21.76165764999999, -4.291266399999991);
    rr_renderer_bezier_curve_to(
        renderer, 25.51225264999999, -0.5147389999999907, 31.97791264999999,
        -0.07720839999999107, 36.20310964999999, -3.3140095999999906);
    rr_renderer_fill(renderer);
    rr_renderer_set_fill(renderer, 0xffb8b8b8);
    rr_renderer_begin_path(renderer);
    rr_renderer_move_to(renderer, -22.316612, -55.247574);
    rr_renderer_bezier_curve_to(renderer, -28.5769575, -44.254685, -40.686664,
                                21.179716, -38.860588, 28.371685999999997);
    rr_renderer_bezier_curve_to(renderer, -37.0345115, 35.563657, -21.719307,
                                -8.145664000000004, -11.360157000000001,
                                -12.095706);
    rr_renderer_bezier_curve_to(renderer, -1.0010070000000013, -16.0457564,
                                21.617371, 8.919721, 23.294303,
                                4.6714069999999985);
    rr_renderer_bezier_curve_to(
        renderer, 24.971243899999997, 0.4230854999999982, 6.303297999999998,
        -27.599139000000005, -1.2985240000000005, -37.585634999999996);
    rr_renderer_bezier_curve_to(renderer, -8.900342, -47.572131,
                                -16.056268000000003, -66.24045799999999,
                                -22.316614, -55.24757699999999);
    rr_renderer_fill(renderer);
}


void rr_ornithomimus_wing2_draw(struct rr_renderer *renderer)
{
    rr_renderer_set_fill(renderer, 0xff585858);
    rr_renderer_begin_path(renderer);
    rr_renderer_move_to(renderer, 48.5423, 59.55748);
    rr_renderer_line_to(renderer, 45.0950725, 75.477585);
    rr_renderer_line_to(renderer, 35.862231, 76.89381420000001);
    rr_renderer_line_to(renderer, 29.716868, 73.80633560000001);
    rr_renderer_line_to(renderer, 24.1885477, 65.92369090000001);
    rr_renderer_line_to(renderer, 25.816530800000002, 59.89672860000001);
    rr_renderer_line_to(renderer, 19.186190200000002, 58.44635020000001);
    rr_renderer_line_to(renderer, 12.863230200000002, 46.72485320000001);
    rr_renderer_line_to(renderer, 15.754900400000002, 41.11683620000001);
    rr_renderer_line_to(renderer, 9.853167000000003, 39.56172150000001);
    rr_renderer_line_to(renderer, -0.042256999999997547, 20.929824500000013);
    rr_renderer_line_to(renderer, -27.665639999999996, 34.07893350000001);
    rr_renderer_line_to(renderer, 3.036120000000004, -23.25347949999999);
    rr_renderer_fill(renderer);
    rr_renderer_set_fill(renderer, 0xff6e6e6e);
    rr_renderer_begin_path(renderer);
    rr_renderer_move_to(renderer, -11.777411999999998, 18.3091);
    rr_renderer_line_to(renderer, 2.084374000000002, 11.8267697);
    rr_renderer_line_to(renderer, 14.381920000000003, 35.5247677);
    rr_renderer_line_to(renderer, 22.685791000000002, 39.1040677);
    rr_renderer_line_to(renderer, 18.851486200000004, 47.1529107);
    rr_renderer_line_to(renderer, 21.982223500000003, 53.8583857);
    rr_renderer_line_to(renderer, 31.629463500000004, 55.8734461);
    rr_renderer_line_to(renderer, 29.136253700000005, 65.9328031);
    rr_renderer_line_to(renderer, 32.2669987, 69.9560881);
    rr_renderer_line_to(renderer, 37.187386000000004, 72.1920195);
    rr_renderer_line_to(renderer, 40.987534000000004, 71.2994719);
    rr_renderer_line_to(renderer, 44.564545, 56.7659939);
    rr_renderer_line_to(renderer, 12.146005000000002, -7.624816100000004);
    rr_renderer_line_to(renderer, 1.1895460000000018, -9.414466100000004);
    rr_renderer_line_to(renderer, -12.895372999999998, 4.224182899999995);
    rr_renderer_fill(renderer);
    rr_renderer_set_fill(renderer, 0xffa7a7a7);
    rr_renderer_begin_path(renderer);
    rr_renderer_move_to(renderer, 48.10839, 63.46457000000001);
    rr_renderer_bezier_curve_to(renderer, 45.2353202, 70.725999, 23.042724,
                                6.022110000000012, 12.030867999999998,
                                -2.706779999999995);
    rr_renderer_bezier_curve_to(
        renderer, 1.019003999999999, -11.435661999999995, -14.258256000000003,
        15.438629000000006, -17.962777000000003, 11.091262000000006);
    rr_renderer_bezier_curve_to(renderer, -21.6672982, 6.743888000000005,
                                -18.068272450000002, -19.229881999999996,
                                -10.196263000000002, -28.790977999999996);
    rr_renderer_bezier_curve_to(
        renderer, -2.324250000000002, -38.352073999999995, 19.551857,
        -61.65123799999999, 29.269293999999995, -46.27531499999999);
    rr_renderer_bezier_curve_to(renderer, 38.98673899999999, -30.89939199999999,
                                50.98146, 56.20315500000001, 48.10839,
                                63.46456500000001);
    rr_renderer_fill(renderer);
    rr_renderer_set_fill(renderer, 0xffa7a7a7);
    rr_renderer_begin_path(renderer);
    rr_renderer_move_to(renderer, -38.06582, -6.812804999999997);
    rr_renderer_bezier_curve_to(renderer, -43.852830000000004,
                                -11.249259999999996, -44.3781216, -19.039429,
                                -39.239091200000004, -24.212622999999997);
    rr_renderer_line_to(renderer, 3.7911517999999944, -67.528973);
    rr_renderer_bezier_curve_to(renderer, 6.259001499999995, -70.01323359999999,
                                9.729735199999993, -71.54942,
                                13.439825799999994, -71.7995914);
    rr_renderer_bezier_curve_to(renderer, 17.149924099999993, -72.04976306,
                                20.795469799999992, -70.9934276,
                                23.574491799999993, -68.862965);
    rr_renderer_bezier_curve_to(
        renderer, 29.361501799999992, -64.42651000000001, 29.886793399999995,
        -56.636345000000006, 24.747762999999992, -51.46315);
    rr_renderer_line_to(renderer, -18.282480000000007, -8.146797);
    rr_renderer_bezier_curve_to(
        renderer, -23.421506600000008, -2.9736019999999996, -32.278814000000004,
        -2.3763499999999995, -38.06582, -6.812804999999999);
    rr_renderer_fill(renderer);
    rr_renderer_set_fill(renderer, 0xffa7a7a7);
    rr_renderer_begin_path(renderer);
    rr_renderer_move_to(renderer, 12.153300000000002, -42.42084);
    rr_renderer_bezier_curve_to(
        renderer, 15.388018300000002, -22.652009999999997, 45.059855,
        59.91227500000001, 47.75951, 56.656310000000005);
    rr_renderer_bezier_curve_to(renderer, 50.459156, 53.4003438, 34.285557,
                                -45.44381, 28.351184999999997, -61.956666);
    rr_renderer_bezier_curve_to(renderer, 22.416820699999995, -78.469522,
                                8.918582999999998, -62.18966771,
                                12.153300999999999, -42.420835);
    rr_renderer_fill(renderer);
    rr_renderer_set_fill(renderer, 0xffb8b8b8);
    rr_renderer_begin_path(renderer);
    rr_renderer_move_to(renderer, -36.204033, -3.3157400000000052);
    rr_renderer_bezier_curve_to(renderer, -40.429228, -6.552541100000005,
                                -40.813965, -12.237974000000005,
                                -37.063366040000005, -16.014501000000003);
    rr_renderer_line_to(renderer, 4.683249959999998, -58.049737);
    rr_renderer_bezier_curve_to(renderer, 6.484351659999998, -59.8632899,
                                9.017707359999998, -60.985097,
                                11.726004959999997, -61.1683665);
    rr_renderer_bezier_curve_to(renderer, 14.434302659999997,
                                -61.351639819999995, 17.095694959999996,
                                -60.581368499999996, 19.12470946, -59.0270015);
    rr_renderer_bezier_curve_to(renderer, 23.34990646, -55.7901965, 23.73464146,
                                -50.1047715, 19.98403866, -46.3282445);
    rr_renderer_line_to(renderer, -21.762577340000004, -4.293004499999995);
    rr_renderer_bezier_curve_to(
        renderer, -25.513176340000005, -0.516477099999995, -31.978836340000004,
        -0.07893889999999537, -36.20403334, -3.315740099999995);
    rr_renderer_fill(renderer);
    rr_renderer_set_fill(renderer, 0xffb8b8b8);
    rr_renderer_begin_path(renderer);
    rr_renderer_move_to(renderer, 22.315690000000004, -55.249306000000004);
    rr_renderer_bezier_curve_to(
        renderer, 28.576035500000003, -44.256417000000006, 40.68574600000001,
        21.177977999999996, 38.859666000000004, 28.36994899999999);
    rr_renderer_bezier_curve_to(renderer, 37.03359330000001, 35.56193499999999,
                                21.718385000000005, -8.147391000000006,
                                11.359231000000005, -12.097443000000005);
    rr_renderer_bezier_curve_to(
        renderer, 1.0000850000000039, -16.047485700000006, -21.618288999999994,
        8.917998999999995, -23.295225999999996, 4.669669999999993);
    rr_renderer_bezier_curve_to(
        renderer, -24.972166899999998, 0.4213484999999926, -6.304220999999995,
        -27.60087600000001, 1.2976010000000038, -37.587372);
    rr_renderer_bezier_curve_to(
        renderer, 8.899423000000004, -47.573868000000004, 16.055345000000003,
        -66.242192, 22.315691000000005, -55.249306000000004);
    rr_renderer_fill(renderer);
}