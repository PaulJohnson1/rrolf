#include <Client/Assets/RenderFunctions.h>

#include <math.h>
#include <stdlib.h>

#include <Client/Assets/Render.h>
#include <Client/Renderer/Renderer.h>
#include <Shared/StaticData.h>

//head, body, legs, tail, IN THAT ORDER

struct rr_renderer_spritesheet mob_sprites[rr_mob_id_max];
struct rr_renderer_spritesheet friendly_trex_spritesheet;
void render_sprite(struct rr_renderer *renderer, uint8_t id, uint32_t pos, uint8_t flags)
{
}

void rr_renderer_draw_mob(struct rr_renderer *renderer, uint8_t id, float orig_animation_tick, float turning_value, uint8_t flags)
{
    struct rr_renderer_context_state original_state;
    struct rr_renderer_context_state state;

    rr_renderer_context_state_init(renderer, &original_state);
    rr_renderer_rotate(renderer, -0 / 2);
    float animation_tick = sinf(orig_animation_tick);
    float animation_tick_2 = cosf(orig_animation_tick);
    switch (id)
    {
        case rr_mob_id_baby_ant:
            rr_renderer_set_fill(renderer, 0xff454545);
            rr_renderer_set_stroke(renderer, 0xff292929);
            rr_renderer_set_line_width(renderer, 7);
            rr_renderer_set_line_cap(renderer, 1);
            rr_renderer_begin_path(renderer);
            rr_renderer_move_to(renderer, 0, -7);
            rr_renderer_quadratic_curve_to(renderer, 11, -10 + animation_tick, 22, -5 + animation_tick);
            rr_renderer_stroke(renderer);
            rr_renderer_begin_path(renderer);
            rr_renderer_move_to(renderer, 0, 7);
            rr_renderer_quadratic_curve_to(renderer, 11, 10 - animation_tick, 22, 5 - animation_tick);
            rr_renderer_stroke(renderer);
            rr_renderer_set_fill(renderer, 0xff555555);
            rr_renderer_set_stroke(renderer, 0xff454545);
            rr_renderer_begin_path(renderer);
            rr_renderer_arc(renderer, 0, 0, 14);
            rr_renderer_fill(renderer);
            rr_renderer_stroke(renderer);
            break;
        case rr_mob_id_worker_ant:
            rr_renderer_set_fill(renderer, 0xff555555);
            rr_renderer_set_stroke(renderer, 0xff454545);
            rr_renderer_set_line_width(renderer, 7);
            rr_renderer_begin_path(renderer);
            rr_renderer_arc(renderer, -12, 0, 10);
            rr_renderer_fill(renderer);
            rr_renderer_stroke(renderer);
            rr_renderer_set_fill(renderer, 0xff454545);
            rr_renderer_set_stroke(renderer, 0xff292929);
            rr_renderer_set_line_cap(renderer, 1);
            rr_renderer_begin_path(renderer);
            rr_renderer_move_to(renderer, 4, -7);
            rr_renderer_quadratic_curve_to(renderer, 15, -10 + animation_tick, 26, -5 + animation_tick);
            rr_renderer_stroke(renderer);
            rr_renderer_begin_path(renderer);
            rr_renderer_move_to(renderer, 4, 7);
            rr_renderer_quadratic_curve_to(renderer, 15, 10 - animation_tick, 26, 5 - animation_tick);
            rr_renderer_stroke(renderer);
            rr_renderer_set_fill(renderer, 0xff555555);
            rr_renderer_set_stroke(renderer, 0xff454545);
            rr_renderer_begin_path(renderer);
            rr_renderer_arc(renderer, 4, 0, 14);
            rr_renderer_fill(renderer);
            rr_renderer_stroke(renderer);
            break;
        case rr_mob_id_soldier_ant:
            rr_renderer_set_fill(renderer, 0xff555555);
            rr_renderer_set_stroke(renderer, 0xff454545);
            rr_renderer_set_line_width(renderer, 7);
            rr_renderer_begin_path(renderer);
            rr_renderer_arc(renderer, -12, 0, 10);
            rr_renderer_fill(renderer);
            rr_renderer_stroke(renderer);
            rr_renderer_set_fill(renderer, 0x80eeeeee);
            rr_renderer_context_state_init(renderer, &state);
            rr_renderer_begin_path(renderer);
            rr_renderer_rotate(renderer, 0.1 * animation_tick);
            rr_renderer_translate(renderer, -11, -8);
            rr_renderer_rotate(renderer, 0.1 * M_PI);
            rr_renderer_ellipse(renderer, 0,0,15,7);
            rr_renderer_fill(renderer);
            rr_renderer_context_state_free(renderer, &state);
            rr_renderer_context_state_init(renderer, &state);
            rr_renderer_begin_path(renderer);
            rr_renderer_rotate(renderer, -0.1 * animation_tick);
            rr_renderer_translate(renderer, -11, 8);
            rr_renderer_rotate(renderer, -0.1 * M_PI);
            rr_renderer_ellipse(renderer, 0,0,15,7);
            rr_renderer_fill(renderer);
            rr_renderer_context_state_free(renderer, &state);
            rr_renderer_set_fill(renderer, 0xff454545);
            rr_renderer_set_stroke(renderer, 0xff292929);
            rr_renderer_set_line_cap(renderer, 1);
            rr_renderer_begin_path(renderer);
            rr_renderer_move_to(renderer, 4, -7);
            rr_renderer_quadratic_curve_to(renderer, 15, -10 + animation_tick, 26, -5 + animation_tick);
            rr_renderer_stroke(renderer);
            rr_renderer_begin_path(renderer);
            rr_renderer_move_to(renderer, 4, 7);
            rr_renderer_quadratic_curve_to(renderer, 15, 10 - animation_tick, 26, 5 - animation_tick);
            rr_renderer_stroke(renderer);
            rr_renderer_set_fill(renderer, 0xff555555);
            rr_renderer_set_stroke(renderer, 0xff454545);
            rr_renderer_begin_path(renderer);
            rr_renderer_arc(renderer, 4, 0, 14);
            rr_renderer_fill(renderer);
            rr_renderer_stroke(renderer);
            break;
        case rr_mob_id_bee:
            rr_renderer_set_fill(renderer, 0xff333333);
            rr_renderer_set_stroke(renderer, 0xff292929);
            rr_renderer_set_line_width(renderer, 5);
            rr_renderer_set_line_cap(renderer, 1);
            rr_renderer_set_line_join(renderer, 1);
            rr_renderer_begin_path(renderer);
            rr_renderer_move_to(renderer, -25,9);
            rr_renderer_line_to(renderer, -37,0);
            rr_renderer_line_to(renderer, -25,-9);
            rr_renderer_fill(renderer);
            rr_renderer_stroke(renderer);
            rr_renderer_set_fill(renderer, 0xffffe763);
            rr_renderer_begin_path(renderer);
            rr_renderer_ellipse(renderer, 0,0,30,20);
            rr_renderer_fill(renderer);
            rr_renderer_context_state_init(renderer, &state);
            rr_renderer_clip(renderer);
            rr_renderer_set_fill(renderer, 0xff333333);
            rr_renderer_fill_rect(renderer, -30,-20,10,40);
            rr_renderer_fill_rect(renderer, -10,-20,10,40);
            rr_renderer_fill_rect(renderer, 10,-20,10,40);
            rr_renderer_context_state_free(renderer, &state);
            rr_renderer_set_stroke(renderer, 0xffd3bd46);
            rr_renderer_set_line_width(renderer, 5);
            rr_renderer_begin_path(renderer);
            rr_renderer_ellipse(renderer, 0,0,30,20);
            rr_renderer_stroke(renderer);
            rr_renderer_set_stroke(renderer, 0xff333333);
            rr_renderer_set_line_width(renderer, 3);
            rr_renderer_begin_path(renderer);
            rr_renderer_move_to(renderer, 25,-5);
            rr_renderer_quadratic_curve_to(renderer, 35,-5,40,-15);
            rr_renderer_stroke(renderer);
            rr_renderer_set_fill(renderer, 0xff333333);
            rr_renderer_begin_path(renderer);
            rr_renderer_arc(renderer, 40,-15,5);
            rr_renderer_fill(renderer);
            rr_renderer_set_stroke(renderer, 0xff333333);
            rr_renderer_set_line_width(renderer, 3);
            rr_renderer_begin_path(renderer);
            rr_renderer_move_to(renderer, 25,5);
            rr_renderer_quadratic_curve_to(renderer, 35,5,40,15);
            rr_renderer_stroke(renderer);
            rr_renderer_set_fill(renderer, 0xff333333);
            rr_renderer_begin_path(renderer);
            rr_renderer_arc(renderer, 40,15,5);
            rr_renderer_fill(renderer);
            break;
        case rr_mob_id_hornet:
            rr_renderer_set_fill(renderer, 0xff333333);
            rr_renderer_set_stroke(renderer, 0xff292929);
            rr_renderer_set_line_width(renderer, 5);
            rr_renderer_set_line_cap(renderer, 1);
            rr_renderer_set_line_join(renderer, 1);
            rr_renderer_begin_path(renderer);
            rr_renderer_move_to(renderer, -25,-6);
            rr_renderer_line_to(renderer, -47,0);
            rr_renderer_line_to(renderer, -25,6);
            rr_renderer_fill(renderer);
            rr_renderer_stroke(renderer);
            rr_renderer_set_fill(renderer, 0xffffe763);
            rr_renderer_begin_path(renderer);
            rr_renderer_ellipse(renderer, 0,0,30,20);
            rr_renderer_fill(renderer);
            rr_renderer_context_state_init(renderer, &state);
            rr_renderer_clip(renderer);
            rr_renderer_set_fill(renderer, 0xff333333);
            rr_renderer_fill_rect(renderer, -30,-20,10,40);
            rr_renderer_fill_rect(renderer, -10,-20,10,40);
            rr_renderer_fill_rect(renderer, 10,-20,10,40);
            rr_renderer_context_state_free(renderer, &state);
            rr_renderer_set_stroke(renderer, 0xffd3bd46);
            rr_renderer_set_line_width(renderer, 5);
            rr_renderer_begin_path(renderer);
            rr_renderer_ellipse(renderer, 0,0,30,20);
            rr_renderer_stroke(renderer);
            rr_renderer_set_stroke(renderer, 0xff333333);
            rr_renderer_set_line_width(renderer, 3);
            rr_renderer_begin_path(renderer);
            rr_renderer_move_to(renderer, 25, 5);
            rr_renderer_quadratic_curve_to(renderer, 40, 10, 50, 15);
            rr_renderer_quadratic_curve_to(renderer, 40, 5, 25, 5);
            rr_renderer_move_to(renderer, 25, -5);
            rr_renderer_quadratic_curve_to(renderer, 40, -10, 50, -15);
            rr_renderer_quadratic_curve_to(renderer, 40, -5, 25, -5);
            rr_renderer_fill(renderer);
            rr_renderer_stroke(renderer);
            break;
        case rr_mob_id_spider:
            rr_renderer_set_stroke(renderer,0xff333333);
            rr_renderer_set_line_width(renderer, 5);
            rr_renderer_set_line_cap(renderer, 1);
            rr_renderer_begin_path(renderer);
            #define draw_leg(angle) \
            { \
                float cos = cosf(angle) * 35; \
                float sin = sinf(angle) * 35; \
                rr_renderer_move_to(renderer,0,0); \
                rr_renderer_quadratic_curve_to(renderer, sin * 0.8, cos * 0.5, sin, cos); \
            }
            draw_leg(-M_PI + 0.9 + animation_tick * 0.2)
            draw_leg(-M_PI + 0.3 + animation_tick_2 * 0.2)
            draw_leg(-M_PI - 0.3 + animation_tick * 0.2)
            draw_leg(-M_PI - 0.9 - animation_tick_2 * 0.2)
            draw_leg(-0.9 - animation_tick * 0.2)
            draw_leg(-0.3 + animation_tick_2 * 0.2)
            draw_leg(0.3 - animation_tick * 0.2)
            draw_leg(0.9 - animation_tick_2 * 0.2)
            rr_renderer_stroke(renderer);
            rr_renderer_begin_path(renderer);
            rr_renderer_arc(renderer,0,0,15);
            rr_renderer_set_fill(renderer,0xff4f412e);
            rr_renderer_fill(renderer);
            rr_renderer_set_stroke(renderer,0xff403525);
            rr_renderer_set_line_width(renderer, 5);
            rr_renderer_stroke(renderer);
            break;
        case rr_mob_id_centipede:
            rr_renderer_begin_path(renderer);
            rr_renderer_arc(renderer,0,-30,15);
            rr_renderer_set_fill(renderer,0xff333333);
            rr_renderer_fill(renderer);
            rr_renderer_begin_path(renderer);
            rr_renderer_arc(renderer,0,30,15);
            rr_renderer_set_fill(renderer,0xff333333);
            rr_renderer_fill(renderer);
            rr_renderer_begin_path(renderer);
            rr_renderer_arc(renderer,0,0,35);
            rr_renderer_set_fill(renderer,0xff8ac255);
            rr_renderer_fill(renderer);
            rr_renderer_set_stroke(renderer,0xff709d45);
            rr_renderer_set_line_width(renderer, 7);
            rr_renderer_stroke(renderer);
            if (!(flags & 4))
            {
                rr_renderer_begin_path(renderer);
                rr_renderer_move_to(renderer,25,-10);
                rr_renderer_quadratic_curve_to(renderer,45,-10,55,-30);
                rr_renderer_set_stroke(renderer,0xff333333);
                rr_renderer_set_line_width(renderer, 3);
                rr_renderer_stroke(renderer);
                rr_renderer_begin_path(renderer);
                rr_renderer_arc(renderer,55,-30,5);
                rr_renderer_set_fill(renderer,0xff333333);
                rr_renderer_fill(renderer);
                rr_renderer_begin_path(renderer);
                rr_renderer_move_to(renderer,25,10);
                rr_renderer_quadratic_curve_to(renderer,45,10,55,30);
                rr_renderer_set_stroke(renderer,0xff333333);
                rr_renderer_set_line_width(renderer, 3);
                rr_renderer_stroke(renderer);
                rr_renderer_begin_path(renderer);
                rr_renderer_arc(renderer,55,30,5);
                rr_renderer_set_fill(renderer,0xff333333);
                rr_renderer_fill(renderer);
            }
            break;
        case rr_mob_id_ladybug:
            rr_renderer_set_fill(renderer, 0xff111111);
            rr_renderer_begin_path(renderer);
            rr_renderer_arc(renderer, 15,0,18.5);
            rr_renderer_fill(renderer);
            rr_renderer_set_fill(renderer, 0xffeb4034);
            rr_renderer_begin_path(renderer);
            rr_renderer_move_to(renderer, 24.760068893432617,16.939273834228516);
            rr_renderer_quadratic_curve_to(renderer, 17.74359130859375,27.195226669311523,5.530136585235596,29.485883712768555);
            rr_renderer_quadratic_curve_to(renderer, -6.683317184448242,31.77654457092285,-16.939273834228516,24.760068893432617);
            rr_renderer_quadratic_curve_to(renderer, -27.195226669311523,17.74359130859375,-29.485883712768555,5.530136585235596);
            rr_renderer_quadratic_curve_to(renderer, -31.77654457092285,-6.683317184448242,-24.760068893432617,-16.939273834228516);
            rr_renderer_quadratic_curve_to(renderer, -17.74359130859375,-27.195226669311523,-5.530136585235596,-29.485883712768555);
            rr_renderer_quadratic_curve_to(renderer, 6.683317184448242,-31.77654457092285,16.939273834228516,-24.760068893432617);
            rr_renderer_quadratic_curve_to(renderer, 19.241104125976562,-23.185302734375,21.213199615478516,-21.213205337524414);
            rr_renderer_quadratic_curve_to(renderer, 23.1852970123291,-19.241111755371094,24.76006507873535,-16.939281463623047);
            rr_renderer_quadratic_curve_to(renderer, 10,0,24.760068893432617,16.939273834228516);
            rr_renderer_fill(renderer);
            {
                rr_renderer_context_state_init(renderer, &state);
                rr_renderer_clip(renderer);
                rr_renderer_set_fill(renderer, 0xff111111);
                rr_renderer_begin_path(renderer);
                rr_renderer_arc(renderer, -24.998876571655273,-20.74837875366211,7.209468364715576);
                rr_renderer_fill(renderer);
                rr_renderer_begin_path(renderer);
                rr_renderer_arc(renderer, 19.580562591552734,23.397785186767578,4.327828407287598);
                rr_renderer_fill(renderer);
                rr_renderer_begin_path(renderer);
                rr_renderer_arc(renderer, 0.7487926483154297,-5.099580764770508,4.840342998504639);
                rr_renderer_fill(renderer);
                rr_renderer_context_state_free(renderer, &state);
            }
            rr_renderer_set_fill(renderer, 0xffbe342a);
            rr_renderer_begin_path(renderer);
            rr_renderer_move_to(renderer, 27.64874267578125,18.915523529052734);
            rr_renderer_quadratic_curve_to(renderer, 19.813682556152344,30.36800765991211,6.175320625305176,32.925907135009766);
            rr_renderer_quadratic_curve_to(renderer, -7.463029861450195,35.48381042480469,-18.91551971435547,27.648746490478516);
            rr_renderer_quadratic_curve_to(renderer, -30.36800765991211,19.813682556152344,-32.925907135009766,6.175320625305176);
            rr_renderer_quadratic_curve_to(renderer, -35.48381042480469,-7.463029861450195,-27.648746490478516,-18.91551971435547);
            rr_renderer_quadratic_curve_to(renderer, -19.813682556152344,-30.36800765991211,-6.175320625305176,-32.925907135009766);
            rr_renderer_quadratic_curve_to(renderer, 7.463029861450195,-35.48381042480469,18.91551971435547,-27.648746490478516);
            rr_renderer_quadratic_curve_to(renderer, 24.10110092163086,-24.101102828979492,27.648740768432617,-18.915529251098633);
            rr_renderer_quadratic_curve_to(renderer, 28.323867797851562,-17.928699493408203,28.25410270690918,-16.73506736755371);
            rr_renderer_quadratic_curve_to(renderer, 28.184337615966797,-15.541434288024902,27.398849487304688,-14.639973640441895);
            rr_renderer_quadratic_curve_to(renderer, 14.642288208007812,0,27.398853302001953,14.639965057373047);
            rr_renderer_quadratic_curve_to(renderer, 28.184343338012695,15.541427612304688,28.254106521606445,16.735061645507812);
            rr_renderer_quadratic_curve_to(renderer, 28.323869705200195,17.928693771362305,27.64874267578125,18.9155216217041);
            rr_renderer_line_to(renderer, 27.64874267578125,18.915523529052734);
            rr_renderer_move_to(renderer, 21.871395111083984,14.963025093078613);
            rr_renderer_line_to(renderer, 24.760068893432617,16.939273834228516);
            rr_renderer_line_to(renderer, 22.12128448486328,19.238582611083984);
            rr_renderer_quadratic_curve_to(renderer, 5.3577117919921875,0,22.121280670166016,-19.238590240478516);
            rr_renderer_line_to(renderer, 24.76006507873535,-16.939281463623047);
            rr_renderer_line_to(renderer, 21.871389389038086,-14.963033676147461);
            rr_renderer_quadratic_curve_to(renderer, 19.065046310424805,-19.0650577545166,14.96302318572998,-21.871395111083984);
            rr_renderer_quadratic_curve_to(renderer, 5.903592586517334,-28.06928253173828,-4.884955406188965,-26.045866012573242);
            rr_renderer_quadratic_curve_to(renderer, -15.673511505126953,-24.022449493408203,-21.871395111083984,-14.96302318572998);
            rr_renderer_quadratic_curve_to(renderer, -28.06928253173828,-5.903592586517334,-26.045866012573242,4.884955406188965);
            rr_renderer_quadratic_curve_to(renderer, -24.022449493408203,15.673511505126953,-14.96302318572998,21.871395111083984);
            rr_renderer_quadratic_curve_to(renderer, -5.903592586517334,28.06928253173828,4.884955406188965,26.045866012573242);
            rr_renderer_quadratic_curve_to(renderer, 15.673511505126953,24.022449493408203,21.871395111083984,14.963025093078613);
            rr_renderer_fill(renderer);
            break;
        case rr_mob_id_evil_centipede:
            rr_renderer_begin_path(renderer);
            rr_renderer_arc(renderer,0,-30,15);
            rr_renderer_set_fill(renderer,0xff333333);
            rr_renderer_fill(renderer);
            rr_renderer_begin_path(renderer);
            rr_renderer_arc(renderer,0,30,15);
            rr_renderer_set_fill(renderer,0xff333333);
            rr_renderer_fill(renderer);
            rr_renderer_begin_path(renderer);
            rr_renderer_arc(renderer,0,0,35);
            rr_renderer_set_fill(renderer,0xff905db0);
            rr_renderer_fill(renderer);
            rr_renderer_set_stroke(renderer,0xff754b8f);
            rr_renderer_set_line_width(renderer, 7);
            rr_renderer_stroke(renderer);
            if (!(flags & 4))
            {
                rr_renderer_begin_path(renderer);
                rr_renderer_move_to(renderer,25,-10);
                rr_renderer_quadratic_curve_to(renderer,45,-10,55,-30);
                rr_renderer_set_stroke(renderer,0xff333333);
                rr_renderer_set_line_width(renderer, 3);
                rr_renderer_stroke(renderer);
                rr_renderer_begin_path(renderer);
                rr_renderer_arc(renderer,55,-30,5);
                rr_renderer_set_fill(renderer,0xff333333);
                rr_renderer_fill(renderer);
                rr_renderer_begin_path(renderer);
                rr_renderer_move_to(renderer,25,10);
                rr_renderer_quadratic_curve_to(renderer,45,10,55,30);
                rr_renderer_set_stroke(renderer,0xff333333);
                rr_renderer_set_line_width(renderer, 3);
                rr_renderer_stroke(renderer);
                rr_renderer_begin_path(renderer);
                rr_renderer_arc(renderer,55,30,5);
                rr_renderer_set_fill(renderer,0xff333333);
                rr_renderer_fill(renderer);
            }
            break;
    }
    rr_renderer_context_state_free(renderer, &original_state);
}

static void friendly_mask(struct rr_renderer *renderer)
{
    rr_renderer_add_color_filter(renderer, 0xffffff45, 0.3);
}

void rr_renderer_mob_cache_init()
{
}