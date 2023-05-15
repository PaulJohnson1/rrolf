#include <Client/Renderer.h>

#ifdef EMSCRIPTEN
#include <emscripten.h>
#else
#endif
#include <math.h>

#define PI 3.14159265358979323846
#define PI_2 2.0 * 3.14159265358979323846


void rr_renderer_init(struct rr_renderer *renderer)
{
    memset(renderer, 0, sizeof(*renderer));
    renderer->transform_matrix[0] = 1;
    renderer->transform_matrix[4] = 1;
}

void rr_renderer_init_context_lock(struct rr_renderer *renderer)
{
    renderer->context_lock.filter.color = renderer->filter.color;
    for (uint64_t i = 0; i < 6; ++i)
        renderer->context_lock.transform_matrix[i] = renderer->transform_matrix[i];
}

void rr_renderer_free_context_lock(struct rr_renderer *renderer)
{
    renderer->filter.color = renderer->context_lock.filter.color;
    for (uint64_t i = 0; i < 6; ++i)
        renderer->transform_matrix[i] = renderer->context_lock.transform_matrix[i];
}

void rr_renderer_set_fill(struct rr_renderer *renderer, uint32_t c)
{
#ifdef EMSCRIPTEN
        EM_ASM({Module.ctxs[$0].fillStyle = `rgba(${$1 >> 16 & 255}, ${$1 >> 8 & 255}, ${$1 & 255}, ${($1 >> 24 & 255) / 255})` }, renderer->context_id, c);
#else
#endif
}

void rr_renderer_set_stroke(struct rr_renderer *renderer, uint32_t c)
{
#ifdef EMSCRIPTEN
        EM_ASM({Module.ctxs[$0].strokeStyle = `rgba(${$1 >> 16 & 255}, ${$1 >> 8 & 255}, ${$1 & 255}, ${($1 >> 24 & 255) / 255})` }, renderer->context_id, c);
#else
#endif
}

void rr_renderer_set_line_width(struct rr_renderer *renderer, float w)
{
#ifdef EMSCRIPTEN
        EM_ASM({Module.ctxs[$0].strokeStyle = $1 }, renderer->context_id, w);
#else
#endif 
}

void rr_renderer_set_line_cap(struct rr_renderer *renderer, uint8_t l)
{
#ifdef EMSCRIPTEN
        EM_ASM({
            if ($1 == 0)
                Module.ctxs[$0].lineCap = 'butt';
            else if ($1 == 1)
                Module.ctxs[$0].lineCap = 'round';
            else
                Module.ctxs[$0].lineCap = 'square';
        }, renderer->context_id, l);
#else
#endif
}

void rr_renderer_set_line_join(struct rr_renderer *renderer, uint8_t l)
{
#ifdef EMSCRIPTEN
        EM_ASM({
            if ($1 == 0)
                Module.ctxs[$0].lineJoin = 'bevel';
            else if ($1 == 1)
                Module.ctxs[$0].lineJoin = 'round';
            else
                Module.ctxs[$0].lineJoin = 'miter';
        }, renderer->context_id, l);
#else
#endif
}
void rr_renderer_set_text_align(struct rr_renderer *renderer, uint8_t l)
{
#ifdef EMSCRIPTEN
        EM_ASM({
            if ($1 == 0)
                Module.ctxs[$0].textAlign = 'left';
            else if ($1 == 1)
                Module.ctxs[$0].textAlign = 'center';
            else
                Module.ctxs[$0].textAlign = 'right';
        }, renderer->context_id, l);
#else
#endif
}
void rr_renderer_set_text_baseline(struct rr_renderer *renderer, uint8_t l)
{
#ifdef EMSCRIPTEN
        EM_ASM({
            if ($1 == 0)
                Module.ctxs[$0].textBaseline = 'top';
            else if ($1 == 1)
                Module.ctxs[$0].textBaseline = 'middle';
            else
                Module.ctxs[$0].textBaseline = 'bottom';
        }, renderer->context_id, l);
#else
#endif
}

void rr_renderer_update_transform(struct rr_renderer *renderer)
{
#ifdef EMSCRIPTEN
        EM_ASM({
            Module.ctxs[$0].setTransform($1, $2, $3, $4, $5, $6);
        }, renderer->context_id, renderer->transform_matrix[0], transform_matrix[1], transform_matrix[3], transform_matrix[4], transform_matrix[2], transform_matrix[5]);
#else
#endif
}

void rr_renderer_set_transform(struct rr_renderer *renderer, float a, float b, float c, float d, float e, float f)
{
    renderer->transform_matrix[0] = a;
    renderer->transform_matrix[1] = b;
    renderer->transform_matrix[2] = c;
    renderer->transform_matrix[3] = d;
    renderer->transform_matrix[4] = e;
    renderer->transform_matrix[5] = f;
    rr_renderer_update_transform(renderer);
}

void rr_renderer_translate(struct rr_renderer *renderer, float x, float y)
{
    renderer->transform_matrix[2] += x * renderer->transform_matrix[0] + y * renderer->transform_matrix[3];
    renderer->transform_matrix[5] += x * renderer->transform_matrix[1] + y * renderer->transform_matrix[4];
    rr_renderer_update_transform(renderer);
}
void rr_renderer_rotate(struct rr_renderer *renderer, float a)
{
    float cos_a = cos(a);
    float sin_a = sin(a);
    float original0 = renderer->transform_matrix[0];
    float original1 = renderer->transform_matrix[1];
    float original3 = renderer->transform_matrix[3];
    float original4 = renderer->transform_matrix[4];
    renderer->transform_matrix[0] = original0 * cos_a + original1 * -sin_a;
    renderer->transform_matrix[1] = original0 * sin_a + original1 * cos_a;
    renderer->transform_matrix[3] = original3 * cos_a + original4 * -sin_a;
    renderer->transform_matrix[4] = original3 * sin_a + original4 * cos_a;
    rr_renderer_update_transform(renderer);
}

void rr_renderer_scale2(struct rr_renderer *renderer, float x, float y)
{        
    renderer->transform_matrix[0] *= x;
    renderer->transform_matrix[1] *= y;
    renderer->transform_matrix[3] *= x;
    renderer->transform_matrix[4] *= y;
    rr_renderer_update_transform(renderer);
}
void rr_renderer_scale(struct rr_renderer *renderer, float s)
{
    rr_renderer_scale2(renderer, s, s);
}

void rr_renderer_save(struct rr_renderer *renderer)
{
#ifdef EMSCRIPTEN
    EM_ASM({
        Module.ctxs[$0].save();
    }, renderer->context_id);
#else
#endif
}

void rr_renderer_restore(struct rr_renderer *renderer)
{
#ifdef EMSCRIPTEN
    EM_ASM({
        Module.ctxs[$0].restore();
    }, renderer->context_id);
#else
#endif
}

void rr_renderer_begin_path(struct rr_renderer *renderer)
{
#ifdef EMSCRIPTEN
    EM_ASM({
        Module.ctxs[$0].beginPath();
    }, renderer->context_id);
#else
#endif
}
void rr_renderer_move_to(struct rr_renderer *renderer, float x, float y)
{
#ifdef EMSCRIPTEN
    EM_ASM({
        Module.ctxs[$0].moveTo($1, $2);
    }, renderer->context_id, x, y);
#else
#endif
}

void rr_renderer_line_to(struct rr_renderer *renderer, float x, float y)
{
#ifdef EMSCRIPTEN
    EM_ASM({
        Module.ctxs[$0].lineTo($1, $2);
    }, renderer->context_id, x, y);
#else
#endif
}

void rr_renderer_quadratic_curve_to(struct rr_renderer *renderer, float x1, float y1, float x, float y)
{
#ifdef EMSCRIPTEN
    EM_ASM({
        Module.ctxs[$0].quadraticCurveTo($1, $2, $3, $4);
    }, renderer->context_id, x1, y1, x, y);
#else
#endif
}

void rr_renderer_bezier_curve_to(struct rr_renderer *renderer, float x1, float y1, float x2, float y2, float x, float y)
{
#ifdef EMSCRIPTEN
    EM_ASM({
        Module.ctxs[$0].bezierCurveTo($1, $2, $3, $4, $5, $6);
    }, renderer->context_id, x1, y1, x2, y2, x, y);
#else
#endif
}
void rr_renderer_arc(struct rr_renderer *renderer, float x, float y, float r)
{
    rr_renderer_partial_arc(renderer, x, y, r, 0, 2 * PI);
}

void rr_renderer_partial_arc(struct rr_renderer *renderer, float x, float y, float r, float sa, float ea)
{
#ifdef EMSCRIPTEN
    EM_ASM({ Module.ctxs[$0].arc($1, $2, $3, $4, $5); }, renderer->context_id, x, y, r, sa, ea);
#else
#endif
}

void rr_renderer_ellipse(struct rr_renderer *renderer, float x, float y, float rx, float ry)
{
#ifdef EMSCRIPTEN
    EM_ASM({ Module.ctxs[$0].ellipse($1, $2, $3, $4, 0, 0, 6.283185307179586); }, renderer->context_id, x, y, rx, ry);
#else
#endif
}

void rr_renderer_rect(struct rr_renderer *renderer, float x, float y, float w, float h)
{
#ifdef EMSCRIPTEN
    EM_ASM({ Module.ctxs[$0].rect($1, $2, $3, $4); }, renderer->context_id, x, y, w, h);
#else
#endif
}

void rr_renderer_round_rect(struct rr_renderer *renderer, float x, float y, float w, float h, float r)
{
    rr_renderer_begin_path(renderer);
    rr_renderer_move_to(renderer, x + r, y);
    rr_renderer_line_to(renderer, x + w - r, y);
    rr_renderer_quadratic_curve_to(renderer, x + w, y, x + w, y + r);
    rr_renderer_line_to(renderer, x + w, y + h - r);
    rr_renderer_quadratic_curve_to(renderer, x + w, y + h, x + w - r, y + h);
    rr_renderer_line_to(renderer, x + r, y + h);
    rr_renderer_quadratic_curve_to(renderer, x, y + h, x, y + h - r);
    rr_renderer_line_to(renderer, x, y + r);
    rr_renderer_quadratic_curve_to(renderer, x, y, x + r, y);
}

void rr_renderer_fill(struct rr_renderer *renderer)
{
#ifdef EMSCRIPTEN
    EM_ASM({ Module.ctxs[$0].fill(); }, renderer->context_id);
#else
#endif
}
void rr_renderer_stroke(struct rr_renderer *renderer)
{
#ifdef EMSCRIPTEN
    EM_ASM({ Module.ctxs[$0].stroke(); }, renderer->context_id);
#else
#endif
}
void rr_renderer_clip(struct rr_renderer *renderer)
{
#ifdef EMSCRIPTEN
    EM_ASM({ Module.ctxs[$0].clip(); }, renderer->context_id);
#else
#endif
}

void rr_renderer_fill_text(struct rr_renderer *renderer, char const *c) {}
void rr_renderer_stroke_text(struct rr_renderer *renderer, char const *c) {}
