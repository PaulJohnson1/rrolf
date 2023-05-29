#include <Client/Renderer/RenderFunctions.h>

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
    default:
        break;
    }
}

void rr_renderer_render_mob(struct rr_renderer *renderer, uint8_t id)
{
    switch (id)
    {
    case rr_mob_id_baby_ant:
        rr_renderer_set_stroke(renderer, 0xff292929);
        rr_renderer_set_fill(renderer, 0xff454545);
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
    case 2123123:
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