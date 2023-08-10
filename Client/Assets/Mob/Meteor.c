#include <Client/Assets/Render.h>

#include <Client/Renderer/Renderer.h>

void rr_meteor_draw(struct rr_renderer *renderer)
{
    rr_renderer_set_fill(renderer, 0xffaaaaaa);
    rr_renderer_set_stroke(renderer, 0xff888888);
    rr_renderer_set_line_width(renderer, 5);
    rr_renderer_begin_path(renderer);
    rr_renderer_arc(renderer, 0, 0, 32);
    rr_renderer_fill(renderer);
    rr_renderer_stroke(renderer);
}