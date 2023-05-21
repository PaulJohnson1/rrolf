#include <Client/Renderer/RenderFunctions.h>

#include <Client/Renderer/Renderer.h>

void rr_renderer_render_petal(struct rr_renderer *renderer, uint8_t id)
{
    switch (id)
    {
    case 0:
        break;
    case 1:
        rr_renderer_set_stroke(renderer, 0xffcfcfcf);
        rr_renderer_set_fill(renderer, 0xffffffff);
        rr_renderer_set_line_width(renderer, 3);
        rr_renderer_begin_path(renderer);
        rr_renderer_arc(renderer, 0, 0, 10);
        rr_renderer_fill(renderer);
        rr_renderer_stroke(renderer);
        break;
    case 2:
        rr_renderer_set_stroke(renderer, 0xffcfcfcf);
        rr_renderer_set_fill(renderer, 0xffffffff);
        rr_renderer_set_line_width(renderer, 3);
        rr_renderer_begin_path(renderer);
        rr_renderer_arc(renderer, 0, 0, 7);
        rr_renderer_fill(renderer);
        rr_renderer_stroke(renderer);
        break;
    default:
        break;
    }
}