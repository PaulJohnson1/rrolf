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
        case rr_petal_id_light:
            rr_renderer_set_stroke(renderer, 0xffcfcfcf);
            rr_renderer_set_fill(renderer, 0xffffffff);
            rr_renderer_set_line_width(renderer, 3.0f);
            rr_renderer_begin_path(renderer);
            rr_renderer_arc(renderer, 0.0f, 0.0f, 7.0f);
            rr_renderer_fill(renderer);
            rr_renderer_stroke(renderer);
            break;
        case rr_petal_id_leaf:
            rr_renderer_set_stroke(renderer, 0xff2e933c);
            rr_renderer_set_fill(renderer, 0xff39b54a);
            rr_renderer_set_line_width(renderer, 3);
            rr_renderer_set_line_join(renderer, 1);
            rr_renderer_set_line_cap(renderer, 1);
            rr_renderer_begin_path(renderer);
            rr_renderer_move_to(renderer, -20, 0);
            rr_renderer_line_to(renderer, -15, 0);
            rr_renderer_bezier_curve_to(renderer,-10,-12,5,-12,15,0);
            rr_renderer_bezier_curve_to(renderer,5,12,-10,12,-15,0);
            rr_renderer_fill(renderer);
            rr_renderer_stroke(renderer);
            rr_renderer_begin_path(renderer);
            rr_renderer_move_to(renderer, -9, 0);
            rr_renderer_quadratic_curve_to(renderer,0,-1.5,7.5,0);
            rr_renderer_stroke(renderer);
            break;
        case rr_petal_id_stinger:
            rr_renderer_set_fill(renderer, 0xff333333);
            rr_renderer_set_stroke(renderer, 0xff292929);
            rr_renderer_set_line_width(renderer, 3.0f);
            rr_renderer_set_line_join(renderer, 1.0f);
            rr_renderer_set_line_cap(renderer, 1.0f);
            rr_renderer_begin_path(renderer);
            rr_renderer_move_to(renderer,7.00,0.00);
            rr_renderer_line_to(renderer,-3.50,6.06);
            rr_renderer_line_to(renderer,-3.50,-6.06);
            rr_renderer_line_to(renderer,7.00,0.00);
            rr_renderer_fill(renderer);
            rr_renderer_stroke(renderer);
            break;
        case rr_petal_id_missile:
            rr_renderer_set_fill(renderer, 0xff222222);
            rr_renderer_set_stroke(renderer, 0xff222222);
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
        case rr_petal_id_faster:
            rr_renderer_set_stroke(renderer, 0xffcecfa3);
            rr_renderer_set_fill(renderer, 0xfffeffc9);
            rr_renderer_set_line_width(renderer, 3.0f);
            rr_renderer_begin_path(renderer);
            rr_renderer_arc(renderer, 0.0f, 0.0f, 7.0f);
            rr_renderer_fill(renderer);
            rr_renderer_stroke(renderer);
            break;
        case rr_petal_id_web:
            rr_renderer_set_fill(renderer, 0xffffffff);
            rr_renderer_set_stroke(renderer, 0xffcfcfcf);
            rr_renderer_set_line_cap(renderer, 1);
            rr_renderer_set_line_join(renderer, 1);
            rr_renderer_set_line_width(renderer, 3);
            rr_renderer_begin_path(renderer);
            rr_renderer_move_to(renderer,11.00,0.00);
            rr_renderer_quadratic_curve_to(renderer,4.32,3.14,3.40,10.46);
            rr_renderer_quadratic_curve_to(renderer,-1.65,5.08,-8.90,6.47);
            rr_renderer_quadratic_curve_to(renderer,-5.34,-0.00,-8.90,-6.47);
            rr_renderer_quadratic_curve_to(renderer,-1.65,-5.08,3.40,-10.46);
            rr_renderer_quadratic_curve_to(renderer,4.32,-3.14,11.00,0.00);
            rr_renderer_fill(renderer);
            rr_renderer_stroke(renderer);
            break;
        case rr_petal_id_antennae:
            rr_renderer_set_fill(renderer,0xff333333);
            rr_renderer_set_stroke(renderer,0xff333333);
            rr_renderer_set_line_width(renderer, 3);
            rr_renderer_set_line_cap(renderer, 1);
            rr_renderer_set_line_join(renderer, 1);
            rr_renderer_rotate(renderer, -M_PI / 2);
            rr_renderer_begin_path(renderer);
            rr_renderer_move_to(renderer,-10,-5);
            rr_renderer_quadratic_curve_to(renderer,5,-10,15,-15);
            rr_renderer_quadratic_curve_to(renderer,5,-5,-10,-5);
            rr_renderer_move_to(renderer,-10,5);
            rr_renderer_quadratic_curve_to(renderer,5,10,15,15);
            rr_renderer_quadratic_curve_to(renderer,5,5,-10,5);
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
        case rr_petal_id_rose:
            rr_renderer_set_stroke(renderer,0xffcf78a3);
            rr_renderer_set_fill(renderer,0xffff94c9);
            rr_renderer_set_line_width(renderer, 3);
            rr_renderer_begin_path(renderer);
            rr_renderer_arc(renderer,0,0,10);
            rr_renderer_fill(renderer);
            rr_renderer_stroke(renderer);
            break;
        case rr_petal_id_iris:
            rr_renderer_set_stroke(renderer,0xffa760b1);
            rr_renderer_set_fill(renderer,0xffce76db);
            rr_renderer_set_line_width(renderer, 3);
            rr_renderer_begin_path(renderer);
            rr_renderer_arc(renderer,0,0,6);
            rr_renderer_fill(renderer);
            rr_renderer_stroke(renderer);
            break;
        case rr_petal_id_grapes:
            rr_renderer_set_stroke(renderer, 0xffa760b1);
            rr_renderer_set_fill(renderer, 0xffce76db);
            rr_renderer_set_line_width(renderer, 3.0f);
            rr_renderer_begin_path(renderer);
            rr_renderer_arc(renderer, 0.0f, 0.0f, 7.0f);
            rr_renderer_fill(renderer);
            rr_renderer_stroke(renderer);
            break;
        case rr_petal_id_oranges:
            rr_renderer_begin_path(renderer);
            rr_renderer_arc(renderer,0,0,12);
            rr_renderer_set_fill(renderer,0xfff0bd48);
            rr_renderer_fill(renderer);
            rr_renderer_set_stroke(renderer,0xffc2993a);
            rr_renderer_set_line_width(renderer, 4);
            rr_renderer_stroke(renderer);
            rr_renderer_translate(renderer,8.29,1.8);
            rr_renderer_rotate(renderer, 3);
            rr_renderer_set_fill(renderer,0xff39b54a);
            rr_renderer_begin_path(renderer);
            rr_renderer_move_to(renderer,0,0);
            rr_renderer_bezier_curve_to(renderer,-3,-7.5,4.5,-9,7.5,-12);
            rr_renderer_bezier_curve_to(renderer,7.5,-7.5,6,1.5,0,0);
            rr_renderer_fill(renderer);
            rr_renderer_set_fill(renderer,0xff2e933c);
            rr_renderer_begin_path(renderer);
            rr_renderer_move_to(renderer,-1.3927149772644043,0.5570859909057617);
            rr_renderer_quadratic_curve_to(renderer,-3.168971061706543,-3.883553981781006,-1.0050835609436035,-7.1033172607421875);
            rr_renderer_quadratic_curve_to(renderer,0.1904260516166687,-8.882179260253906,3.766146659851074,-11.13597297668457);
            rr_renderer_quadratic_curve_to(renderer,5.790802001953125,-12.412123680114746,6.439339637756348,-13.060660362243652);
            rr_renderer_quadratic_curve_to(renderer,6.878679275512695,-13.5,7.499999523162842,-13.5);
            rr_renderer_quadratic_curve_to(renderer,8.121319770812988,-13.5,8.560660362243652,-13.060660362243652);
            rr_renderer_quadratic_curve_to(renderer,8.771637916564941,-12.84968090057373,8.885818481445312,-12.574024200439453);
            rr_renderer_quadratic_curve_to(renderer,8.999999046325684,-12.298367500305176,9,-12);
            rr_renderer_quadratic_curve_to(renderer,9,-6.942111968994141,7.378717422485352,-3.159121036529541);
            rr_renderer_quadratic_curve_to(renderer,4.8432464599609375,2.7569756507873535,-0.3638034462928772,1.4552137851715088);
            rr_renderer_quadratic_curve_to(renderer,-0.714259684085846,1.367599606513977,-0.9864063858985901,1.1300452947616577);
            rr_renderer_quadratic_curve_to(renderer,-1.2585530281066895,0.8924908638000488,-1.3927150964736938,0.5570860505104065);
            rr_renderer_line_to(renderer,-1.3927149772644043,0.5570859909057617);
            rr_renderer_move_to(renderer,1.3927149772644043,-0.5570859909057617);
            rr_renderer_line_to(renderer,0,0);
            rr_renderer_line_to(renderer,0.3638034462928772,-1.4552137851715088);
            rr_renderer_quadratic_curve_to(renderer,3.0922369956970215,-0.7731051445007324,4.621282577514648,-4.340878963470459);
            rr_renderer_quadratic_curve_to(renderer,6.000000953674316,-7.557886123657227,6,-12);
            rr_renderer_line_to(renderer,7.5,-12);
            rr_renderer_line_to(renderer,8.560660362243652,-10.939339637756348);
            rr_renderer_quadratic_curve_to(renderer,7.674622058868408,-10.053300857543945,5.365812301635742,-8.598047256469727);
            rr_renderer_quadratic_curve_to(renderer,2.3266048431396484,-6.68242073059082,1.484847068786621,-5.429924011230469);
            rr_renderer_quadratic_curve_to(renderer,0.20520126819610596,-3.5258703231811523,1.3927149772644043,-0.5570859909057617);
            rr_renderer_fill(renderer);
            break;
        case rr_petal_id_pollen:
            rr_renderer_set_stroke(renderer, 0xffcfbb50);
            rr_renderer_set_fill(renderer, 0xffffe763);
            rr_renderer_set_line_width(renderer, 3.0f);
            rr_renderer_begin_path(renderer);
            rr_renderer_arc(renderer, 0.0f, 0.0f, 7.0f);
            rr_renderer_fill(renderer);
            rr_renderer_stroke(renderer);
            break;
        case rr_petal_id_wing:
            rr_renderer_begin_path(renderer);
            rr_renderer_partial_arc(renderer,0,0,15,-1.5707963267948966,1.5707963267948966,0);
            rr_renderer_quadratic_curve_to(renderer,10,0,0,-15);
            rr_renderer_set_fill(renderer,0xffffffff);
            rr_renderer_fill(renderer);
            rr_renderer_set_stroke(renderer,0xffcfcfcf);
            rr_renderer_set_line_width(renderer, 3);
            rr_renderer_set_line_cap(renderer, 1);
            rr_renderer_set_line_join(renderer, 1);
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
    if (id == rr_petal_id_peas || id == rr_petal_id_grapes)
        rr_renderer_rotate(renderer, 1.0f - M_PI / 4.0f);
    else if (id == rr_petal_id_wing)
        rr_renderer_rotate(renderer, 1.0f);
    if (count <= 1)
    {
        if (id == rr_petal_id_leaf)
            rr_renderer_rotate(renderer, -1);
        else if (id == rr_petal_id_missile)
            rr_renderer_rotate(renderer, 1);
        rr_renderer_draw_petal(renderer, id, flags);
    }
    else
    {
        struct rr_renderer_context_state state;
        float r = RR_PETAL_DATA[id].clump_radius == 0.0f
                      ? 10.0f
                      : fminf(RR_PETAL_DATA[id].clump_radius, 10);
        for (uint32_t i = 0; i < count; ++i)
        {
            rr_renderer_context_state_init(renderer, &state);
            rr_renderer_translate(renderer, r, 0.0f);
            if (id == rr_petal_id_stinger && rarity == rr_rarity_id_ultra)
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