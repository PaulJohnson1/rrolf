#include <Client/Renderer/ComponentRender.h>

#include <math.h>

#include <Client/Game.h>
#include <Client/Renderer/Renderer.h>
#include <Client/Simulation.h>

#include <Client/Assets/RenderFunctions.h>

void rr_component_petal_render(EntityIdx entity, struct rr_game *game, struct rr_simulation *simulation)
{
    struct rr_renderer *renderer = game->renderer;
    struct rr_component_physical *physical =
        rr_simulation_get_physical(simulation, entity);
    struct rr_component_petal *petal =
        rr_simulation_get_petal(simulation, entity);
    struct rr_component_health *health = rr_simulation_get_health(simulation, entity);
    rr_renderer_add_color_filter(renderer, 0xffff0000, 0.5 * health->damage_animation);
    rr_renderer_set_global_alpha(renderer, 1 - physical->deletion_animation);
    rr_renderer_scale(renderer, 1 + physical->deletion_animation * 0.5);
    rr_renderer_rotate(renderer, physical->lerp_angle);
    if (rr_simulation_get_relations(simulation, entity)->team ==
        rr_simulation_team_id_mobs)
    {
        rr_renderer_scale(renderer,
                          RR_MOB_RARITY_SCALING[petal->rarity].radius);
    }
    /*
    if (rr_frand() < 0.5) {
        struct rr_particle *particle = rr_particle_alloc(&game->particle_manager, 0);
        particle->position.x = physical->lerp_x + rr_frand() * 20 - 10;
        particle->position.y = physical->lerp_y + rr_frand() * 20 - 10;
        float angle = rr_frand() * 2 * M_PI;
        rr_vector_from_polar(&particle->velocity, rr_frand() * 5 + 3, angle);
        particle->size = 5;
        particle->opacity = 0.4;
        particle->color = RR_RARITY_COLORS[petal->rarity];
    }
    */
    uint8_t use_cache = health->damage_animation < 0.1;
    if (petal->id != rr_petal_id_peas || petal->detached == 1)
        rr_renderer_draw_petal(renderer, petal->id, use_cache);
    else
        rr_renderer_draw_static_petal(renderer, petal->id, petal->rarity, use_cache);
    if (petal->id == rr_petal_id_stick)
    {
        struct rr_particle *particle = rr_particle_alloc(&game->particle_manager, 0);
        float angle = rr_vector_theta(&physical->lerp_velocity) + M_PI - 0.5 + rr_frand();
        float dist = 10;
        if (rr_simulation_get_relations(simulation, entity)->team ==
        rr_simulation_team_id_mobs)
            dist *= RR_MOB_RARITY_SCALING[petal->rarity].radius;
        rr_vector_from_polar(&particle->velocity, (rr_frand() * 5 + 5), angle);
        rr_vector_set(&particle->position[0], physical->lerp_x + sinf(physical->angle) * dist, physical->lerp_y - cosf(physical->angle) * dist);
        particle->size = (3 + rr_frand() * 2);
        particle->opacity = 0.8;
        particle->color = rr_frand() > 0.25 ? 0xffab3423 : 0xff999999;
    }
    /*
    if (petal->id == rr_petal_id_stick)
    {
        rr_renderer_translate(renderer, 0, -10);
        rr_renderer_rotate(renderer, -physical->angle);
        rr_renderer_scale(renderer, 0.1 + 0.02 * sinf(physical->animation / 2.5));
        rr_renderer_set_global_alpha(renderer, 0.5);
        rr_renderer_set_fill(renderer, 0xffad0000);
        rr_renderer_begin_path(renderer);
        rr_renderer_move_to(renderer, 96.00233, 46.94934000000001);
        rr_renderer_bezier_curve_to(renderer, 96.003489668, 81.23176500000001, 77.7149, 112.91058000000001, 48.025844, 130.05246);
        rr_renderer_bezier_curve_to(renderer, 18.33678, 147.194336, -18.242176000000008, 147.19494699999998, -47.931816000000005, 130.0540774316);
        rr_renderer_bezier_curve_to(renderer, -77.621458, 112.9132074316, -95.911114, 81.23500043160001, -95.911114, 46.952577431600005);
        rr_renderer_fill(renderer);
        rr_renderer_set_fill(renderer, 0xffad0000);
        rr_renderer_begin_path(renderer);
        rr_renderer_move_to(renderer, -92.3304982, 65.61174);
        rr_renderer_bezier_curve_to(renderer, -108.1980902, 31.295226999999997, -68.57757419999999, -93.51784, -50.9996422, -123.38989000000001);
        rr_renderer_bezier_curve_to(renderer, -33.4217122, -153.26194, -2.7305001999999945, -147.937068, 13.137087800000003, -113.620557);
        rr_renderer_bezier_curve_to(renderer, 29.004679800000005, -79.304047, 61.7838318, 52.63712299999999, 44.2059048, 82.50917299999999);
        rr_renderer_bezier_curve_to(renderer, 26.6279778, 112.381228, -76.4629052, 99.92825599999999, -92.33049519999999, 65.61174299999999);
        rr_renderer_fill(renderer);
        rr_renderer_set_fill(renderer, 0xffad0000);
        rr_renderer_begin_path(renderer);
        rr_renderer_move_to(renderer, 92.94798, 61.33455000000001);
        rr_renderer_bezier_curve_to(renderer, 103.483289, 38.81541500000001, 83.447888, -45.08143, 70.146146, -65.50925);
        rr_renderer_bezier_curve_to(renderer, 56.844403, -85.93707599999999, 23.672826, -83.75153, 13.137509999999999, -61.232386999999996);
        rr_renderer_bezier_curve_to(renderer, 2.602193999999999, -38.713252, -6.367495000000002, 49.177753, 6.934247699999999, 69.60558300000002);
        rr_renderer_bezier_curve_to(renderer, 20.2359907, 90.03339300000002, 82.4126717, 83.85369100000003, 92.9479777, 61.33455600000002);
        rr_renderer_fill(renderer);
        rr_renderer_set_fill(renderer, 0xffe75a00);
        rr_renderer_begin_path(renderer);
        rr_renderer_move_to(renderer, 68.44966, 46.94933);
        rr_renderer_bezier_curve_to(renderer, 68.45048397459999, 71.38853900000001, 55.412946999999996, 93.971715, 34.24824399999999, 106.191777);
        rr_renderer_bezier_curve_to(renderer, 13.083540999999993, 118.41187000000001, -12.992822000000004, 118.412297, -34.157936000000014, 106.192936668);
        rr_renderer_bezier_curve_to(renderer, -55.323051000000014, 93.973576668, -68.36135900000002, 71.390842668, -68.36135900000002, 46.951634668000004);
        rr_renderer_fill(renderer);
        rr_renderer_set_fill(renderer, 0xffe75a00);
        rr_renderer_begin_path(renderer);
        rr_renderer_move_to(renderer, -65.405598, 64.24815000000001);
        rr_renderer_bezier_curve_to(renderer, -77.207682, 38.01150100000001, -50.522076, -64.64726999999999, -39.849446, -91.28171);
        rr_renderer_bezier_curve_to(renderer, -29.1768195, -117.91615900000001, -13.171914000000001, -121.795218, -1.3698279999999983, -95.5585655);
        rr_renderer_bezier_curve_to(renderer, 10.432250000000002, -69.3219165, 41.635696, 39.5037545, 30.963065, 66.13821449999999);
        rr_renderer_bezier_curve_to(renderer, 20.290435000000002, 92.7726745, -53.603509, 90.48480249999999, -65.405605, 64.2481541);
        rr_renderer_fill(renderer);
        rr_renderer_set_fill(renderer, 0xffe75a00);
        rr_renderer_begin_path(renderer);
        rr_renderer_move_to(renderer, 67.32639, 56.24682999999999);
        rr_renderer_bezier_curve_to(renderer, 75.366536, 40.13049699999999, 59.4861495, -23.421825000000013, 52.78749500000001, -39.35556000000001);
        rr_renderer_bezier_curve_to(renderer, 46.08882560000001, -55.28929100000001, 35.17456500000001, -55.47190000000001, 27.134411000000007, -39.35556000000001);
        rr_renderer_bezier_curve_to(renderer, 19.094265000000007, -23.239212000000013, -2.1520419999999945, 41.40874999999998, 4.546620000000008, 57.342483999999985);
        rr_renderer_bezier_curve_to(renderer, 11.245282000000007, 73.27621499999998, 59.28624400000001, 72.36317499999998, 67.32639, 56.246826699999986);
        rr_renderer_fill(renderer);
        rr_renderer_set_fill(renderer, 0xfff9b300);
        rr_renderer_begin_path(renderer);
        rr_renderer_move_to(renderer, 44.54043999999999, 46.95093);
        rr_renderer_bezier_curve_to(renderer, 44.54097405759999, 62.862826, 36.05247899999999, 77.56628599999999, 22.27255699999999, 85.52253999999999);
        rr_renderer_bezier_curve_to(renderer, 8.492634499999989, 93.478793, -8.485172000000013, 93.47906769999999, -22.26536900000001, 85.52328768065999);
        rr_renderer_bezier_curve_to(renderer, -36.04555850000001, 77.56749238065998, -44.53454500000001, 62.864337680659986, -44.53454500000001, 46.95244068065999);
        rr_renderer_fill(renderer);
        rr_renderer_set_fill(renderer, 0xfff9b300);
        rr_renderer_begin_path(renderer);
        rr_renderer_move_to(renderer, -43.245544, 56.088300000000004);
        rr_renderer_bezier_curve_to(renderer, -49.826385, 35.739148, -34.946491, -43.882975, -28.995437000000003, -64.54065);
        rr_renderer_bezier_curve_to(renderer, -23.044379600000003, -85.198334, -14.120040000000003, -88.20693299999999, -7.5391990000000035, -67.8577887);
        rr_renderer_bezier_curve_to(renderer, -0.9583580000000032, -47.5086367, 16.440674999999995, 36.896541299999996, 10.489616999999996, 57.5542313);
        rr_renderer_bezier_curve_to(renderer, 4.538566999999995, 78.2119153, -36.664703, 76.4374553, -43.245543000000005, 56.088304199999996);
        rr_renderer_fill(renderer);
        rr_renderer_set_fill(renderer, 0xfff9b300);
        rr_renderer_begin_path(renderer);
        rr_renderer_move_to(renderer, 44.354870000000005, 49.78880000000001);
        rr_renderer_bezier_curve_to(renderer, 46.82445920000001, 39.294537000000005, 41.834789400000005, 2.1772740000000113, 39.75492500000001, -7.345034999999989);
        rr_renderer_bezier_curve_to(renderer, 37.67506050000001, -16.86734299999999, 34.345242000000006, -17.83929799999999, 31.875652500000008, -7.345034999999989);
        rr_renderer_bezier_curve_to(renderer, 29.40605560000001, 3.1492280000000115, 22.85749450000001, 46.098202000000015, 24.93736650000001, 55.620511000000015);
        rr_renderer_bezier_curve_to(renderer, 27.01723860000001, 65.14280400000001, 41.88528050000001, 60.28304760000002, 44.35486950000001, 49.788800000000016);
        rr_renderer_fill(renderer);
        rr_renderer_set_fill(renderer, 0xfff9b300);
        rr_renderer_begin_path(renderer);
        rr_renderer_move_to(renderer, 31.522329999999997, -5.334949999999992);
        rr_renderer_bezier_curve_to(renderer, 31.522329999999997, 32.457744000000005, 25.783308699999996, 63.094780000000014, 18.703863999999996, 63.094780000000014);
        rr_renderer_bezier_curve_to(renderer, 11.624426699999995, 63.094780000000014, 5.885404999999995, 32.457740000000015, 5.885404999999995, -5.334949999999992);
        rr_renderer_bezier_curve_to(renderer, 8.911436499999995, 16.20380700000001, 13.660482999999996, 28.87991000000001, 18.703863999999996, 28.87991000000001);
        rr_renderer_bezier_curve_to(renderer, 23.747244699999996, 28.87991000000001, 28.496298999999993, 16.20380800000001, 31.522329999999997, -5.334949999999992);
        rr_renderer_fill(renderer);
    }
    */
}