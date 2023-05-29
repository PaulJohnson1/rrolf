#include <Client/Renderer/RenderFunctions.h>

#include <math.h>
#include <stdio.h>

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
        rr_renderer_set_line_width(renderer, 3);
        rr_renderer_begin_path(renderer);
        rr_renderer_arc(renderer, 0, 0, 10);
        rr_renderer_fill(renderer);
        rr_renderer_stroke(renderer);
        break;
    case rr_petal_id_light:
        rr_renderer_set_stroke(renderer, 0xffcfcfcf);
        rr_renderer_set_fill(renderer, 0xffffffff);
        rr_renderer_set_line_width(renderer, 3);
        rr_renderer_begin_path(renderer);
        rr_renderer_arc(renderer, 0, 0, 7);
        rr_renderer_fill(renderer);
        rr_renderer_stroke(renderer);
        break;
    case rr_petal_id_stinger:
        rr_renderer_set_fill(renderer, 0xff333333);
        rr_renderer_set_stroke(renderer, 0xff292929);
        rr_renderer_set_line_width(renderer, 3);
        rr_renderer_set_line_join(renderer, 1);
        rr_renderer_begin_path(renderer);
        rr_renderer_move_to(renderer,7,0);
        rr_renderer_line_to(renderer,-3.5,6.062177658081055);
        rr_renderer_line_to(renderer,-3.5,-6.062178134918213);
        rr_renderer_line_to(renderer,7,0);
        rr_renderer_fill(renderer);
        rr_renderer_stroke(renderer);
        break;
    case rr_petal_id_faster:
        rr_renderer_set_stroke(renderer, 0xffcecfa3);
        rr_renderer_set_fill(renderer, 0xfffeffc9);
        rr_renderer_set_line_width(renderer, 3);
        rr_renderer_begin_path(renderer);
        rr_renderer_arc(renderer, 0, 0, 7);
        rr_renderer_fill(renderer);
        rr_renderer_stroke(renderer);
        break;
    case rr_petal_id_missile:
        rr_renderer_set_fill(renderer, 0xff333333);
        rr_renderer_set_stroke(renderer, 0xff333333);
        rr_renderer_set_line_width(renderer, 5);
        rr_renderer_set_line_join(renderer, 1);
        rr_renderer_set_line_cap(renderer, 1);
        rr_renderer_begin_path(renderer);
        rr_renderer_move_to(renderer, 11, 0);
        rr_renderer_line_to(renderer, -11, -6);
        rr_renderer_line_to(renderer, -11, 6);
        rr_renderer_line_to(renderer, 11, 0);
        rr_renderer_fill(renderer);
        rr_renderer_stroke(renderer);
        break;
    case rr_petal_id_peas:
        rr_renderer_set_stroke(renderer, 0xff709d45);
        rr_renderer_set_fill(renderer, 0xff8ac255);
        rr_renderer_set_line_width(renderer, 3);
        rr_renderer_begin_path(renderer);
        rr_renderer_arc(renderer, 0,0,7);
        rr_renderer_fill(renderer);
        rr_renderer_stroke(renderer);
        break;
    default:
        break;
    }
}

void rr_renderer_render_static_petal(struct rr_renderer *renderer, uint8_t id, uint8_t rarity)
{
    uint32_t count = RR_PETAL_DATA[id].count[rarity];
    if (count == 1)
    {
        if (id == rr_petal_id_missile)
            rr_renderer_rotate(renderer, 1);
        rr_renderer_render_petal(renderer, id);
    }
    else
    {
        if (id == rr_petal_id_peas)
            rr_renderer_rotate(renderer, 1 - M_PI / 4);
        struct rr_renderer_context_state state;
        float r = RR_PETAL_DATA[id].clump_radius == 0 ? 10 : RR_PETAL_DATA[id].clump_radius;
        for (uint32_t i = 0; i < count; ++i)
        {
            rr_renderer_init_context_state(renderer, &state);
            rr_renderer_translate(renderer, r, 0);
            if (id == rr_petal_id_missile)
                rr_renderer_rotate(renderer, 1);
            rr_renderer_render_petal(renderer, id);
            rr_renderer_free_context_state(renderer, &state);
            rr_renderer_rotate(renderer, M_PI * 2.0f / count);
        }
    }
}

void rr_renderer_render_mob(struct rr_renderer *renderer, uint8_t id)
{
    switch (id)
    {
    case rr_mob_id_baby_ant:
        rr_renderer_set_stroke(renderer, 0xff292929);
        rr_renderer_set_line_width(renderer, 7);
        rr_renderer_set_line_cap(renderer, 1);
        rr_renderer_begin_path(renderer);
        rr_renderer_move_to(renderer, 0, -7);
        rr_renderer_quadratic_curve_to(renderer, 11, -10, 22, -5);
        rr_renderer_stroke(renderer);
        rr_renderer_begin_path(renderer);
        rr_renderer_move_to(renderer, 0, 7);
        rr_renderer_quadratic_curve_to(renderer, 11, 10, 22, 5);
        rr_renderer_stroke(renderer);
        rr_renderer_set_stroke(renderer, 0xff454545);
        rr_renderer_set_fill(renderer, 0xff555555);
        rr_renderer_begin_path(renderer);
        rr_renderer_arc(renderer, 0, 0, 14);
        rr_renderer_fill(renderer);
        rr_renderer_stroke(renderer);
        break;
    case rr_mob_id_worker_ant:
        rr_renderer_set_stroke(renderer, 0xff454545);
        rr_renderer_set_fill(renderer, 0xff555555);
        rr_renderer_set_line_width(renderer, 7);
        rr_renderer_begin_path(renderer);
        rr_renderer_arc(renderer, -16, 0, 10);
        rr_renderer_fill(renderer);
        rr_renderer_stroke(renderer);
        rr_renderer_set_stroke(renderer, 0xff292929);
        rr_renderer_set_line_cap(renderer, 1);
        rr_renderer_begin_path(renderer);
        rr_renderer_move_to(renderer, 0, -7);
        rr_renderer_quadratic_curve_to(renderer, 11, -10, 22, -5);
        rr_renderer_stroke(renderer);
        rr_renderer_begin_path(renderer);
        rr_renderer_move_to(renderer, 0, 7);
        rr_renderer_quadratic_curve_to(renderer, 11, 10, 22, 5);
        rr_renderer_stroke(renderer);
        rr_renderer_set_stroke(renderer, 0xff454545);
        rr_renderer_set_fill(renderer, 0xff555555);
        rr_renderer_begin_path(renderer);
        rr_renderer_arc(renderer, 0, 0, 14);
        rr_renderer_fill(renderer);
        rr_renderer_stroke(renderer);
        break;
    case rr_mob_id_centipede_head:
        rr_renderer_set_fill(renderer, 0xff333333);
        rr_renderer_begin_path(renderer);
        rr_renderer_arc(renderer, 0,-30,15);
        rr_renderer_fill(renderer);
        rr_renderer_begin_path(renderer);
        rr_renderer_arc(renderer, 0,30,15);
        rr_renderer_fill(renderer);
        rr_renderer_begin_path(renderer);
        rr_renderer_arc(renderer, 55,30,5);
        rr_renderer_fill(renderer);
        rr_renderer_begin_path(renderer);
        rr_renderer_arc(renderer, 55,-30,5);
        rr_renderer_fill(renderer);
        rr_renderer_set_fill(renderer, 0xff8ac255);
        rr_renderer_set_stroke(renderer, 0xff709d45);
        rr_renderer_set_line_width(renderer, 7);
        rr_renderer_begin_path(renderer);
        rr_renderer_arc(renderer, 0,0,35);
        rr_renderer_fill(renderer);
        rr_renderer_stroke(renderer);
        rr_renderer_set_stroke(renderer, 0xff333333);
        rr_renderer_set_line_cap(renderer, 1);
        rr_renderer_set_line_width(renderer, 3);
        rr_renderer_begin_path(renderer);
        rr_renderer_move_to(renderer, 25,-10);
        rr_renderer_quadratic_curve_to(renderer, 45,-10,55,-30);
        rr_renderer_stroke(renderer);
        rr_renderer_begin_path(renderer);
        rr_renderer_move_to(renderer, 25, 10);
        rr_renderer_quadratic_curve_to(renderer, 45,10,55,30);
        rr_renderer_stroke(renderer);
        break;
    case rr_mob_id_centipede_body:
        rr_renderer_set_fill(renderer, 0xff333333);
        rr_renderer_begin_path(renderer);
        rr_renderer_arc(renderer, 0,-30,15);
        rr_renderer_fill(renderer);
        rr_renderer_begin_path(renderer);
        rr_renderer_arc(renderer, 0,30,15);
        rr_renderer_fill(renderer);
        rr_renderer_set_fill(renderer, 0xff8ac255);
        rr_renderer_set_stroke(renderer, 0xff709d45);
        rr_renderer_set_line_width(renderer, 7);
        rr_renderer_begin_path(renderer);
        rr_renderer_arc(renderer, 0,0,35);
        rr_renderer_fill(renderer);
        rr_renderer_stroke(renderer);
        break;
    case 255:
        rr_renderer_set_stroke(renderer, 0xffcfcfcf);
        rr_renderer_set_fill(renderer, 0xffffffff);
        rr_renderer_set_line_width(renderer, 7);
        rr_renderer_begin_path(renderer);
        rr_renderer_arc(renderer, 0, 0, 7);
        rr_renderer_fill(renderer);
        rr_renderer_stroke(renderer);
        break;
    default:
        break;
    }
}