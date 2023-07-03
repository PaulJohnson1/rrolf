#include <Client/Renderer/Renderer.h>

#include <math.h>
#include <string.h>
#include <Shared/Utilities.h>

#ifdef EMSCRIPTEN
#include <emscripten.h>
#else
#endif

void rr_renderer_init(struct rr_renderer *this)
{
    memset(this, 0, sizeof(*this));
    this->state.transform_matrix[0] = 1;
    this->state.transform_matrix[4] = 1;
#ifdef EMSCRIPTEN
    this->context_id = EM_ASM_INT({ return Module.addCtx(); });
#endif
}

void rr_renderer_set_dimensions(struct rr_renderer *this, float w, float h)
{
    this->width = w;
    this->height = h;
#ifdef EMSCRIPTEN
    EM_ASM({ Module.ctxs[$0].canvas.width = $1; Module.ctxs[$0].canvas.height = $2; }, this->context_id, w, h);
#endif
}

void rr_renderer_init_context_state(struct rr_renderer *this, struct rr_renderer_context_state *state)
{
    memcpy(state, &this->state, sizeof *state);
    rr_renderer_save(this);
}

void rr_renderer_free_context_state(struct rr_renderer *this, struct rr_renderer_context_state *state)
{
    memcpy(&this->state, state, sizeof *state);
    rr_renderer_restore(this);
}

void rr_renderer_set_fill(struct rr_renderer *this, uint32_t c)
{
    float a = this->state.filter.amount;
    uint32_t fc = this->state.filter.color;
    uint8_t red = rr_fclamp((((c >> 16) & 255) * (1 - a) + ((fc >> 16) & 255) * a), 0, 255);
    uint8_t green = rr_fclamp((((c >> 8) & 255) * (1 - a) + ((fc >> 8) & 255) * a), 0, 255);
    uint8_t blue = rr_fclamp((((c >> 0) & 255) * (1 - a) + ((fc >> 0) & 255) * a), 0, 255);
    c = ((c >> 24) << 24) | (red << 16) | (green << 8) | blue;
#ifdef EMSCRIPTEN
    EM_ASM({Module.ctxs[$0].fillStyle = `rgba(${$1 >> 16 & 255}, ${$1 >> 8 & 255}, ${$1 & 255}, ${($1 >> 24 & 255) / 255})` }, this->context_id, c);
#else
#endif
}

void rr_renderer_set_stroke(struct rr_renderer *this, uint32_t c)
{
    float a = this->state.filter.amount;
    uint32_t fc = this->state.filter.color;
    uint8_t red = rr_fclamp((((c >> 16) & 255) * (1 - a) + ((fc >> 16) & 255) * a), 0, 255);
    uint8_t green = rr_fclamp((((c >> 8) & 255) * (1 - a) + ((fc >> 8) & 255) * a), 0, 255);
    uint8_t blue = rr_fclamp((((c >> 0) & 255) * (1 - a) + ((fc >> 0) & 255) * a), 0, 255);
    c = ((c >> 24) << 24) | (red << 16) | (green << 8) | blue;
#ifdef EMSCRIPTEN
    EM_ASM({Module.ctxs[$0].strokeStyle = `rgba(${$1 >> 16 & 255}, ${$1 >> 8 & 255}, ${$1 & 255}, ${($1 >> 24 & 255) / 255})` }, this->context_id, c);
#else
#endif
}

void rr_renderer_set_line_width(struct rr_renderer *this, float w)
{
#ifdef EMSCRIPTEN
    EM_ASM({Module.ctxs[$0].lineWidth = $1}, this->context_id, w);
#else
#endif
}

void rr_renderer_set_text_size(struct rr_renderer *this, float s)
{
#ifdef EMSCRIPTEN
    EM_ASM({ Module.ctxs[$0].font = $1 + "px Ubuntu"; }, this->context_id, s);
#endif
}

void rr_renderer_set_global_alpha(struct rr_renderer *this, float a)
{
#ifdef EMSCRIPTEN
    EM_ASM({Module.ctxs[$0].globalAlpha = $1}, this->context_id, a);
#else
#endif
}

void rr_renderer_set_line_cap(struct rr_renderer *this, uint8_t l)
{
#ifdef EMSCRIPTEN
    EM_ASM({
        if ($1 == 0)
            Module.ctxs[$0].lineCap = 'butt';
        else if ($1 == 1)
            Module.ctxs[$0].lineCap = 'round';
        else if ($1 == 2)
            Module.ctxs[$0].lineCap = 'square';
        else
            throw "line cap oopsie happened";
    },
           this->context_id, l);
#else
#endif
}

void rr_renderer_set_line_join(struct rr_renderer *this, uint8_t l)
{
#ifdef EMSCRIPTEN
    EM_ASM({
        if ($1 == 0)
            Module.ctxs[$0].lineJoin = 'bevel';
        else if ($1 == 1)
            Module.ctxs[$0].lineJoin = 'round';
        else if ($1 == 2)
            Module.ctxs[$0].lineJoin = 'miter';
        else
            throw "line cap oopsie happened";
    },
           this->context_id, l);
#else
#endif
}
void rr_renderer_set_text_align(struct rr_renderer *this, uint8_t l)
{
#ifdef EMSCRIPTEN
    EM_ASM({
        if ($1 == 0)
            Module.ctxs[$0].textAlign = 'left';
        else if ($1 == 1)
            Module.ctxs[$0].textAlign = 'center';
        else
            Module.ctxs[$0].textAlign = 'right';
    },
           this->context_id, l);
#else
#endif
}
void rr_renderer_set_text_baseline(struct rr_renderer *this, uint8_t l)
{
#ifdef EMSCRIPTEN
    EM_ASM({
        if ($1 == 0)
            Module.ctxs[$0].textBaseline = 'top';
        else if ($1 == 1)
            Module.ctxs[$0].textBaseline = 'middle';
        else
            Module.ctxs[$0].textBaseline = 'bottom';
    },
           this->context_id, l);
#else
#endif
}

void rr_renderer_update_transform(struct rr_renderer *this)
{
#ifdef EMSCRIPTEN
    EM_ASM({
        Module.ctxs[$0].setTransform($1, $2, $3, $4, $5, $6);
    },
           this->context_id, this->state.transform_matrix[0], this->state.transform_matrix[1], this->state.transform_matrix[3], this->state.transform_matrix[4], this->state.transform_matrix[2], this->state.transform_matrix[5]);
#else
#endif
}

void rr_renderer_set_transform(struct rr_renderer *this, float a, float b, float c, float d, float e, float f)
{
    this->state.transform_matrix[0] = a;
    this->state.transform_matrix[1] = b;
    this->state.transform_matrix[2] = c;
    this->state.transform_matrix[3] = d;
    this->state.transform_matrix[4] = e;
    this->state.transform_matrix[5] = f;
    rr_renderer_update_transform(this);
}

void rr_renderer_translate(struct rr_renderer *this, float x, float y)
{
    this->state.transform_matrix[2] += x * this->state.transform_matrix[0] + y * this->state.transform_matrix[3];
    this->state.transform_matrix[5] += x * this->state.transform_matrix[1] + y * this->state.transform_matrix[4];
    rr_renderer_update_transform(this);
}

void rr_renderer_rotate(struct rr_renderer *this, float a)
{
    float cos_a = cosf(a);
    float sin_a = sinf(a);
    float original0 = this->state.transform_matrix[0];
    float original1 = this->state.transform_matrix[1];
    float original3 = this->state.transform_matrix[3];
    float original4 = this->state.transform_matrix[4];
    this->state.transform_matrix[0] = original0 * cos_a + original1 * -sin_a;
    this->state.transform_matrix[1] = original0 * sin_a + original1 * cos_a;
    this->state.transform_matrix[3] = original3 * cos_a + original4 * -sin_a;
    this->state.transform_matrix[4] = original3 * sin_a + original4 * cos_a;
    rr_renderer_update_transform(this);
}

void rr_renderer_scale2(struct rr_renderer *this, float x, float y)
{
    this->state.transform_matrix[0] *= x;
    this->state.transform_matrix[1] *= y;
    this->state.transform_matrix[3] *= x;
    this->state.transform_matrix[4] *= y;
    rr_renderer_update_transform(this);
}
void rr_renderer_scale(struct rr_renderer *this, float s)
{
    rr_renderer_scale2(this, s, s);
}

void rr_renderer_save(struct rr_renderer *this)
{
#ifdef EMSCRIPTEN
    EM_ASM({
        Module.ctxs[$0].save();
    },
           this->context_id);
#else
#endif
}

void rr_renderer_restore(struct rr_renderer *this)
{
#ifdef EMSCRIPTEN
    EM_ASM({
        Module.ctxs[$0].restore();
    },
           this->context_id);
#else
#endif
}

void rr_renderer_begin_path(struct rr_renderer *this)
{
#ifdef EMSCRIPTEN
    EM_ASM({
        Module.ctxs[$0].beginPath();
    },
           this->context_id);
#else
#endif
}
void rr_renderer_move_to(struct rr_renderer *this, float x, float y)
{
#ifdef EMSCRIPTEN
    EM_ASM({
        Module.ctxs[$0].moveTo($1, $2);
    },
           this->context_id, x, y);
#else
#endif
}

void rr_renderer_line_to(struct rr_renderer *this, float x, float y)
{
#ifdef EMSCRIPTEN
    EM_ASM({
        Module.ctxs[$0].lineTo($1, $2);
    },
           this->context_id, x, y);
#else
#endif
}

void rr_renderer_quadratic_curve_to(struct rr_renderer *this, float x1, float y1, float x, float y)
{
#ifdef EMSCRIPTEN
    EM_ASM({
        Module.ctxs[$0].quadraticCurveTo($1, $2, $3, $4);
    },
           this->context_id, x1, y1, x, y);
#else
#endif
}

void rr_renderer_bezier_curve_to(struct rr_renderer *this, float x1, float y1, float x2, float y2, float x, float y)
{
#ifdef EMSCRIPTEN
    EM_ASM({
        Module.ctxs[$0].bezierCurveTo($1, $2, $3, $4, $5, $6);
    },
           this->context_id, x1, y1, x2, y2, x, y);
#else
#endif
}
void rr_renderer_arc(struct rr_renderer *this, float x, float y, float r)
{
    rr_renderer_partial_arc(this, x, y, r, 0, 2 * M_PI, 0);
}

void rr_renderer_reverse_arc(struct rr_renderer *this, float x, float y, float r)
{
    rr_renderer_partial_arc(this, x, y, r, 2 * M_PI, 0, 1);
}

void rr_renderer_partial_arc(struct rr_renderer *this, float x, float y, float r, float sa, float ea, uint8_t ccw)
{
#ifdef EMSCRIPTEN
    EM_ASM({ Module.ctxs[$0].arc($1, $2, $3, $4, $5, !!$6); }, this->context_id, x, y, r, sa, ea, ccw);
#else
#endif
}

void rr_renderer_ellipse(struct rr_renderer *this, float x, float y, float rx, float ry)
{
#ifdef EMSCRIPTEN
    EM_ASM({ Module.ctxs[$0].ellipse($1, $2, $3, $4, 0, 0, 6.283185307179586); }, this->context_id, x, y, rx, ry);
#else
#endif
}

void rr_renderer_rect(struct rr_renderer *this, float x, float y, float w, float h)
{
#ifdef EMSCRIPTEN
    EM_ASM({ Module.ctxs[$0].rect($1, $2, $3, $4); }, this->context_id, x, y, w, h);
#else
#endif
}

void rr_renderer_round_rect(struct rr_renderer *this, float x, float y, float w, float h, float r)
{
    rr_renderer_begin_path(this);
    rr_renderer_move_to(this, x + r, y);
    rr_renderer_line_to(this, x + w - r, y);
    rr_renderer_quadratic_curve_to(this, x + w, y, x + w, y + r);
    rr_renderer_line_to(this, x + w, y + h - r);
    rr_renderer_quadratic_curve_to(this, x + w, y + h, x + w - r, y + h);
    rr_renderer_line_to(this, x + r, y + h);
    rr_renderer_quadratic_curve_to(this, x, y + h, x, y + h - r);
    rr_renderer_line_to(this, x, y + r);
    rr_renderer_quadratic_curve_to(this, x, y, x + r, y);
}

void rr_renderer_draw_image(struct rr_renderer *this, struct rr_renderer *image)
{
#ifdef EMSCRIPTEN
    EM_ASM({ Module.ctxs[$0].drawImage(Module.ctxs[$1].canvas, -Module.ctxs[$1].canvas.width / 2, -Module.ctxs[$1].canvas.height / 2); }, this->context_id, image->context_id);
#else
#endif
}

void rr_renderer_draw_svg(struct rr_renderer *this, char *svg, float x, float y)
{
#ifdef EMSCRIPTEN
    EM_ASM({
        let string = "";
        while (Module.HEAPU8[$1])
            string += String.fromCharCode(Module.HEAPU8[$1++]);
        const DOMURL = window.URL || window.webkitURL || window;
        const img = new Image();
        const svgBlob = new Blob([string],
                                 { type: 'image/svg+xml;charset=utf-8' });
        const url = DOMURL.createObjectURL(svgBlob);
        img.src = url;
        img.onload = function()
        {
            Module.ctxs[$0].drawImage(img, 0, 0);
        };
    },
           this->context_id, svg, x, y);
#else
#endif
}

void rr_renderer_fill_rect(struct rr_renderer *this, float x, float y, float w, float h)
{
#ifdef EMSCRIPTEN
    EM_ASM({ Module.ctxs[$0].fillRect($1, $2, $3, $4); }, this->context_id, x, y, w, h);
#else
#endif
}

void rr_renderer_stroke_rect(struct rr_renderer *this, float x, float y, float w, float h)
{
#ifdef EMSCRIPTEN
    EM_ASM({ Module.ctxs[$0].strokeRect($1, $2, $3, $4); }, this->context_id, x, y, w, h);
#else
#endif
}

void rr_renderer_fill(struct rr_renderer *this)
{
#ifdef EMSCRIPTEN
    EM_ASM({ Module.ctxs[$0].fill(); }, this->context_id);
#else
#endif
}
void rr_renderer_stroke(struct rr_renderer *this)
{
#ifdef EMSCRIPTEN
    EM_ASM({ Module.ctxs[$0].stroke(); }, this->context_id);
#else
#endif
}
void rr_renderer_clip(struct rr_renderer *this)
{
#ifdef EMSCRIPTEN
    EM_ASM({ Module.ctxs[$0].clip(); }, this->context_id);
#else
#endif
}

void rr_renderer_clip2(struct rr_renderer *this)
{
#ifdef EMSCRIPTEN
    EM_ASM({ Module.ctxs[$0].clip("evenodd"); }, this->context_id);
#else
#endif
}

void rr_renderer_fill_text(struct rr_renderer *this, char const *c, float x, float y)
{
#ifdef EMSCRIPTEN
    EM_ASM({
        let string = Module.ReadCstr($3);
        Module.ctxs[$0].fillText(string, $1, $2)
    },
           this->context_id, x, y, c);
#endif
}
void rr_renderer_stroke_text(struct rr_renderer *this, char const *c, float x, float y)
{
#ifdef EMSCRIPTEN
    EM_ASM({
        let string = Module.ReadCstr($3);
        Module.ctxs[$0].strokeText(string, $1, $2)
    },
           this->context_id, x, y, c);
#endif
}

float rr_renderer_get_text_size(char const *c)
{
#ifdef EMSCRIPTEN
    return EM_ASM_DOUBLE({
        let string = "";
        while (Module.HEAPU8[$0])
            string += String.fromCharCode(Module.HEAPU8[$0++]);
        Module.ctxs[0].font = '1px Ubuntu';
        return Module.ctxs[0].measureText(string).width;
    },
                         c);
#endif
    return 0.0f;
}
