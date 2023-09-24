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
                      : RR_PETAL_DATA[id].clump_radius;
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