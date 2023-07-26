#include <Client/Renderer/Renderer.h>

#include <math.h>
#include <string.h>
#include <stdlib.h>
#include <emscripten.h>

#include <Shared/Utilities.h>

struct renderer_args
{
    uint8_t type;
    uint32_t context_id;
    float args[6];
    char const *text_arg;
};

static struct renderer_args instruction_tape[20000];
static uint32_t instruction_size;

void rr_renderer_init(struct rr_renderer *this)
{
    memset(this, 0, sizeof(*this));
    this->state.transform_matrix[0] = 1;
    this->state.transform_matrix[4] = 1;
    this->context_id = EM_ASM_INT({ return Module.addCtx(); });
}

void rr_renderer_set_dimensions(struct rr_renderer *this, float w, float h)
{
    this->width = w;
    this->height = h;
    EM_ASM(
        {
            Module.ctxs[$0].canvas.width = $1;
            Module.ctxs[$0].canvas.height = $2;
        },
        this->context_id, w, h);
}

void rr_renderer_set_fill(struct rr_renderer *this, uint32_t c)
{
    float a = this->state.filter.amount;
    uint32_t fc = this->state.filter.color;
    uint8_t red = rr_fclamp(
        (((c >> 16) & 255) * (1 - a) + ((fc >> 16) & 255) * a), 0, 255);
    uint8_t green =
        rr_fclamp((((c >> 8) & 255) * (1 - a) + ((fc >> 8) & 255) * a), 0, 255);
    uint8_t blue =
        rr_fclamp((((c >> 0) & 255) * (1 - a) + ((fc >> 0) & 255) * a), 0, 255);
    instruction_tape[instruction_size].type = 0;
    instruction_tape[instruction_size].context_id = this->context_id;
    instruction_tape[instruction_size].args[0] = red;
    instruction_tape[instruction_size].args[1] = green;
    instruction_tape[instruction_size].args[2] = blue;
    instruction_tape[instruction_size].args[3] = (float)(c >> 24) * 1.0f/255.0f;
    ++instruction_size;
    return;
    c = ((c >> 24) << 24) | (red << 16) | (green << 8) | blue;
    EM_ASM({Module.ctxs[$0].fillStyle = `rgba(${$1 >> 16 & 255},
                                              ${$1 >> 8 & 255}, ${$1 & 255},
                                              ${($1 >> 24 & 255) / 255})` },
           this->context_id, c);
}

void rr_renderer_set_stroke(struct rr_renderer *this, uint32_t c)
{
    float a = this->state.filter.amount;
    uint32_t fc = this->state.filter.color;
    uint8_t red = rr_fclamp(
        (((c >> 16) & 255) * (1 - a) + ((fc >> 16) & 255) * a), 0, 255);
    uint8_t green =
        rr_fclamp((((c >> 8) & 255) * (1 - a) + ((fc >> 8) & 255) * a), 0, 255);
    uint8_t blue =
        rr_fclamp((((c >> 0) & 255) * (1 - a) + ((fc >> 0) & 255) * a), 0, 255);
    instruction_tape[instruction_size].type = 1;
    instruction_tape[instruction_size].context_id = this->context_id;
    instruction_tape[instruction_size].args[0] = red;
    instruction_tape[instruction_size].args[1] = green;
    instruction_tape[instruction_size].args[2] = blue;
    instruction_tape[instruction_size].args[3] = (float)(c >> 24) * 1.0f/255.0f;
    ++instruction_size;
    return;
    c = ((c >> 24) << 24) | (red << 16) | (green << 8) | blue;
    EM_ASM({Module.ctxs[$0].strokeStyle = `rgba(${$1 >> 16 & 255},
                                                ${$1 >> 8 & 255}, ${$1 & 255},
                                                ${($1 >> 24 & 255) / 255})` },
           this->context_id, c);
}

void rr_renderer_set_line_width(struct rr_renderer *this, float w)
{
    instruction_tape[instruction_size].type = 2;
    instruction_tape[instruction_size].context_id = this->context_id;
    instruction_tape[instruction_size].args[0] = w;
    ++instruction_size;
    return;
    EM_ASM({Module.ctxs[$0].lineWidth = $1}, this->context_id, w);
}

void rr_renderer_set_text_size(struct rr_renderer *this, float s)
{
    instruction_tape[instruction_size].type = 3;
    instruction_tape[instruction_size].context_id = this->context_id;
    instruction_tape[instruction_size].args[0] = s;
    ++instruction_size;
    return;
    EM_ASM({ Module.ctxs[$0].font = $1 + "px Ubuntu"; }, this->context_id, s);
}

void rr_renderer_set_global_alpha(struct rr_renderer *this, float a)
{
    instruction_tape[instruction_size].type = 4;
    instruction_tape[instruction_size].context_id = this->context_id;
    instruction_tape[instruction_size].args[0] = a;
    ++instruction_size;
    return;
    EM_ASM({Module.ctxs[$0].globalAlpha = $1}, this->context_id, a);
}

void rr_renderer_set_line_cap(struct rr_renderer *this, uint8_t l)
{
    instruction_tape[instruction_size].type = 5;
    instruction_tape[instruction_size].context_id = this->context_id;
    instruction_tape[instruction_size].args[0] = l;
    ++instruction_size;
    return;
    EM_ASM(
        {
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
}

void rr_renderer_set_line_join(struct rr_renderer *this, uint8_t l)
{
    instruction_tape[instruction_size].type = 6;
    instruction_tape[instruction_size].context_id = this->context_id;
    instruction_tape[instruction_size].args[0] = l;
    ++instruction_size;
    return;
    EM_ASM(
        {
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
}

void rr_renderer_set_text_align(struct rr_renderer *this, uint8_t l)
{
    instruction_tape[instruction_size].type = 7;
    instruction_tape[instruction_size].context_id = this->context_id;
    instruction_tape[instruction_size].args[0] = l;
    ++instruction_size;
    return;
    EM_ASM(
        {
            if ($1 == 0)
                Module.ctxs[$0].textAlign = 'left';
            else if ($1 == 1)
                Module.ctxs[$0].textAlign = 'center';
            else
                Module.ctxs[$0].textAlign = 'right';
        },
        this->context_id, l);
}

void rr_renderer_set_text_baseline(struct rr_renderer *this, uint8_t l)
{
    instruction_tape[instruction_size].type = 8;
    instruction_tape[instruction_size].context_id = this->context_id;
    instruction_tape[instruction_size].args[0] = l;
    ++instruction_size;
    return;
    EM_ASM(
        {
            if ($1 == 0)
                Module.ctxs[$0].textBaseline = 'top';
            else if ($1 == 1)
                Module.ctxs[$0].textBaseline = 'middle';
            else
                Module.ctxs[$0].textBaseline = 'bottom';
        },
        this->context_id, l);
}

void rr_renderer_update_transform(struct rr_renderer *this)
{
    instruction_tape[instruction_size].type = 9;
    instruction_tape[instruction_size].context_id = this->context_id;
    instruction_tape[instruction_size].args[0] = this->state.transform_matrix[0];
    instruction_tape[instruction_size].args[1] = this->state.transform_matrix[1];
    instruction_tape[instruction_size].args[2] = this->state.transform_matrix[2];
    instruction_tape[instruction_size].args[3] = this->state.transform_matrix[3];
    instruction_tape[instruction_size].args[4] = this->state.transform_matrix[4];
    instruction_tape[instruction_size].args[5] = this->state.transform_matrix[5];
    ++instruction_size;
    return;
    EM_ASM({ Module.ctxs[$0].setTransform($1, $2, $3, $4, $5, $6); },
           this->context_id, this->state.transform_matrix[0],
           this->state.transform_matrix[1], this->state.transform_matrix[3],
           this->state.transform_matrix[4], this->state.transform_matrix[2],
           this->state.transform_matrix[5]);
}

void rr_renderer_save(struct rr_renderer *this)
{
    instruction_tape[instruction_size].type = 10;
    instruction_tape[instruction_size].context_id = this->context_id;
    ++instruction_size;
    return;
    EM_ASM({ Module.ctxs[$0].save(); }, this->context_id);
}

void rr_renderer_restore(struct rr_renderer *this)
{
    instruction_tape[instruction_size].type = 11;
    instruction_tape[instruction_size].context_id = this->context_id;
    ++instruction_size;
    return;
    EM_ASM({ Module.ctxs[$0].restore(); }, this->context_id);
}

void rr_renderer_begin_path(struct rr_renderer *this)
{
    instruction_tape[instruction_size].type = 12;
    instruction_tape[instruction_size].context_id = this->context_id;
    ++instruction_size;
    return;
    EM_ASM({ Module.ctxs[$0].beginPath(); }, this->context_id);
}

void rr_renderer_move_to(struct rr_renderer *this, float x, float y)
{
    instruction_tape[instruction_size].type = 13;
    instruction_tape[instruction_size].context_id = this->context_id;
    instruction_tape[instruction_size].args[0] = x;
    instruction_tape[instruction_size].args[1] = y;
    ++instruction_size;
    return;
    EM_ASM({ Module.ctxs[$0].moveTo($1, $2); }, this->context_id, x, y);
}

void rr_renderer_line_to(struct rr_renderer *this, float x, float y)
{
    instruction_tape[instruction_size].type = 14;
    instruction_tape[instruction_size].context_id = this->context_id;
    instruction_tape[instruction_size].args[0] = x;
    instruction_tape[instruction_size].args[1] = y;
    ++instruction_size;
    return;
    EM_ASM({ Module.ctxs[$0].lineTo($1, $2); }, this->context_id, x, y);
}

void rr_renderer_quadratic_curve_to(struct rr_renderer *this, float x1,
                                    float y1, float x, float y)
{
    instruction_tape[instruction_size].type = 15;
    instruction_tape[instruction_size].context_id = this->context_id;
    instruction_tape[instruction_size].args[0] = x1;
    instruction_tape[instruction_size].args[1] = y1;
    instruction_tape[instruction_size].args[2] = x;
    instruction_tape[instruction_size].args[3] = y;
    ++instruction_size;
    return;
    EM_ASM({ Module.ctxs[$0].quadraticCurveTo($1, $2, $3, $4); },
           this->context_id, x1, y1, x, y);
}

void rr_renderer_bezier_curve_to(struct rr_renderer *this, float x1, float y1,
                                 float x2, float y2, float x, float y)
{
    instruction_tape[instruction_size].type = 16;
    instruction_tape[instruction_size].context_id = this->context_id;
    instruction_tape[instruction_size].args[0] = x1;
    instruction_tape[instruction_size].args[1] = y1;
    instruction_tape[instruction_size].args[2] = x2;
    instruction_tape[instruction_size].args[3] = y2;
    instruction_tape[instruction_size].args[4] = x;
    instruction_tape[instruction_size].args[5] = y;
    ++instruction_size;
    return;
    EM_ASM({ Module.ctxs[$0].bezierCurveTo($1, $2, $3, $4, $5, $6); },
           this->context_id, x1, y1, x2, y2, x, y);
}
void rr_renderer_partial_arc(struct rr_renderer *this, float x, float y,
                             float r, float sa, float ea, uint8_t ccw)
{
    instruction_tape[instruction_size].type = 17;
    instruction_tape[instruction_size].context_id = this->context_id;
    instruction_tape[instruction_size].args[0] = x;
    instruction_tape[instruction_size].args[1] = y;
    instruction_tape[instruction_size].args[2] = r;
    instruction_tape[instruction_size].args[3] = sa;
    instruction_tape[instruction_size].args[4] = ea;
    instruction_tape[instruction_size].args[5] = ccw;
    ++instruction_size;
    return;
    EM_ASM({ Module.ctxs[$0].arc($1, $2, $3, $4, $5, !!$6); }, this->context_id,
           x, y, r, sa, ea, ccw);
}

void rr_renderer_ellipse(struct rr_renderer *this, float x, float y, float rx,
                         float ry)
{
    instruction_tape[instruction_size].type = 18;
    instruction_tape[instruction_size].context_id = this->context_id;
    instruction_tape[instruction_size].args[0] = x;
    instruction_tape[instruction_size].args[1] = y;
    instruction_tape[instruction_size].args[2] = rx;
    instruction_tape[instruction_size].args[3] = ry;
    ++instruction_size;
    return;
    EM_ASM(
        { Module.ctxs[$0].ellipse($1, $2, $3, $4, 0, 0, 6.283185307179586); },
        this->context_id, x, y, rx, ry);
}

void rr_renderer_rect(struct rr_renderer *this, float x, float y, float w,
                      float h)
{
    instruction_tape[instruction_size].type = 19;
    instruction_tape[instruction_size].context_id = this->context_id;
    instruction_tape[instruction_size].args[0] = x;
    instruction_tape[instruction_size].args[1] = y;
    instruction_tape[instruction_size].args[2] = w;
    instruction_tape[instruction_size].args[3] = h;
    ++instruction_size;
    return;
    EM_ASM({ Module.ctxs[$0].rect($1, $2, $3, $4); }, this->context_id, x, y, w,
           h);
}

void rr_renderer_draw_translated_image(struct rr_renderer *this, struct rr_renderer *image, float x, float y)
{
    instruction_tape[instruction_size].type = 20;
    instruction_tape[instruction_size].context_id = this->context_id;
    instruction_tape[instruction_size].args[0] = image->context_id;
    instruction_tape[instruction_size].args[1] = -image->width / 2 + x;
    instruction_tape[instruction_size].args[2] = -image->height / 2 + y;
    ++instruction_size;
    return;
    EM_ASM(
    {
        Module.ctxs[$0].drawImage(Module.ctxs[$1].canvas, $2, $3);
    },
    this->context_id, image->context_id, -image->width / 2 + x, -image->height / 2 + y);
}

void rr_renderer_draw_image(struct rr_renderer *this, struct rr_renderer *image)
{
    rr_renderer_draw_translated_image(this, image, 0, 0);
}

void rr_renderer_draw_svg(struct rr_renderer *this, char *svg, float x, float y)
{
    EM_ASM(
        {
            let string = "";
            while (Module.HEAPU8[$1])
                string += String.fromCharCode(Module.HEAPU8[$1++]);
            const DOMURL = window.URL || window.webkitURL || window;
            const img = new Image();
            const svgBlob = new Blob([string],
                                     {
                                         type:
                                             'image/svg+xml;charset=utf-8'
                                     });
            const url = DOMURL.createObjectURL(svgBlob);
            img.src = url;
            img.onload = function() { Module.ctxs[$0].drawImage(img, 0, 0); };
        },
        this->context_id, svg, x, y);
}

void rr_renderer_fill_rect(struct rr_renderer *this, float x, float y, float w,
                           float h)
{
    instruction_tape[instruction_size].type = 21;
    instruction_tape[instruction_size].context_id = this->context_id;
    instruction_tape[instruction_size].args[0] = x;
    instruction_tape[instruction_size].args[1] = y;
    instruction_tape[instruction_size].args[2] = w;
    instruction_tape[instruction_size].args[3] = h;
    ++instruction_size;
    return;
    EM_ASM({ Module.ctxs[$0].fillRect($1, $2, $3, $4); }, this->context_id, x,
           y, w, h);
}

void rr_renderer_stroke_rect(struct rr_renderer *this, float x, float y,
                             float w, float h)
{
    instruction_tape[instruction_size].type = 22;
    instruction_tape[instruction_size].context_id = this->context_id;
    instruction_tape[instruction_size].args[0] = x;
    instruction_tape[instruction_size].args[1] = y;
    instruction_tape[instruction_size].args[2] = w;
    instruction_tape[instruction_size].args[3] = h;
    ++instruction_size;
    return;
    EM_ASM({ Module.ctxs[$0].strokeRect($1, $2, $3, $4); }, this->context_id, x,
           y, w, h);
}

void rr_renderer_fill(struct rr_renderer *this)
{
    instruction_tape[instruction_size].type = 23;
    instruction_tape[instruction_size].context_id = this->context_id;
    ++instruction_size;
    return;
    EM_ASM({ Module.ctxs[$0].fill(); }, this->context_id);
}

void rr_renderer_stroke(struct rr_renderer *this)
{
    instruction_tape[instruction_size].type = 24;
    instruction_tape[instruction_size].context_id = this->context_id;
    ++instruction_size;
    return;
    EM_ASM({ Module.ctxs[$0].stroke(); }, this->context_id);
}

void rr_renderer_clip(struct rr_renderer *this)
{
    instruction_tape[instruction_size].type = 25;
    instruction_tape[instruction_size].context_id = this->context_id;
    ++instruction_size;
    return;
    EM_ASM({ Module.ctxs[$0].clip(); }, this->context_id);
}

void rr_renderer_clip2(struct rr_renderer *this)
{
    instruction_tape[instruction_size].type = 26;
    instruction_tape[instruction_size].context_id = this->context_id;
    ++instruction_size;
    return;
    EM_ASM({ Module.ctxs[$0].clip("evenodd"); }, this->context_id);
}

void rr_renderer_fill_text(struct rr_renderer *this, char const *c, float x,
                           float y)
{
    instruction_tape[instruction_size].type = 27;
    instruction_tape[instruction_size].context_id = this->context_id;
    instruction_tape[instruction_size].args[0] = x;
    instruction_tape[instruction_size].args[1] = y;
    uint32_t len = strlen(c) + 1;
    char *text = malloc(len * (sizeof *text));
    memcpy(text, c, len * sizeof *text);
    instruction_tape[instruction_size].text_arg = text;
    ++instruction_size;
    return;
    EM_ASM(
        {
            let string = Module.ReadCstr($3);
            Module.ctxs[$0].fillText(string, $1, $2)
        },
        this->context_id, x, y, c);
}
void rr_renderer_stroke_text(struct rr_renderer *this, char const *c, float x,
                             float y)
{
    instruction_tape[instruction_size].type = 28;
    instruction_tape[instruction_size].context_id = this->context_id;
    instruction_tape[instruction_size].args[0] = x;
    instruction_tape[instruction_size].args[1] = y;
    uint32_t len = strlen(c) + 1;
    char *text = malloc(len * (sizeof *text));
    memcpy(text, c, len * sizeof *text);
    instruction_tape[instruction_size].text_arg = text;
    ++instruction_size;
    return;
    EM_ASM(
        {
            let string = Module.ReadCstr($3);
            Module.ctxs[$0].strokeText(string, $1, $2)
        },
        this->context_id, x, y, c);
}

float rr_renderer_get_text_size(char const *c)
{
    return EM_ASM_DOUBLE(
        {
            let string = "";
            while (Module.HEAPU8[$0])
                string += String.fromCharCode(Module.HEAPU8[$0++]);
            Module.ctxs[0].font = '1px Ubuntu';
            return Module.ctxs[0].measureText(string).width;
        },
        c);
    return 0.0f;
}

void rr_renderer_execute_order_66()
{
    EM_ASM({
        for (let n = 0; n < $1; ++n)
        {
            const instr = n * $2 + $0;
            const ctx_id = Module.HEAPU32[instr + 4 >> 2];
            const argptr = instr + 8;
            const args = Module.HEAPF32.subarray(argptr >> 2, argptr + 24 >> 2);
            const char_arg = Module.HEAPU32[argptr + 24 >> 2];
            let str;
            switch (Module.HEAPU8[instr])
            {
                case 0:
                    Module.ctxs[ctx_id].fillStyle = "rgba(" + args[0] + ',' + args[1] + ',' + args[2] + ',' + args[3] + ')';
                    break;
                case 1:
                    Module.ctxs[ctx_id].strokeStyle = "rgba(" + args[0] + ',' + args[1] + ',' + args[2] + ',' + args[3] + ')';
                    break;
                case 2:
                    Module.ctxs[ctx_id].lineWidth = args[0];
                    break;
                case 3:
                    Module.ctxs[ctx_id].font = args[0] + "px Ubuntu";
                    break;
                case 4:
                    Module.ctxs[ctx_id].globalAlpha = args[0];
                    break;
                case 5:
                    if (args[0] == 0)
                        Module.ctxs[ctx_id].lineCap = 'butt';
                    else if (args[0] == 1)
                        Module.ctxs[ctx_id].lineCap = 'round';
                    else if (args[0] == 2)
                        Module.ctxs[ctx_id].lineCap = 'square';
                    break;
                case 6:
                    if (args[0] == 0)
                        Module.ctxs[ctx_id].lineJoin = 'bevel';
                    else if (args[0] == 1)
                        Module.ctxs[ctx_id].lineJoin = 'round';
                    else if (args[0] == 2)
                        Module.ctxs[ctx_id].lineJoin = 'miter';
                    break;
                case 7:
                    if (args[0] == 0)
                        Module.ctxs[ctx_id].textAlign = 'left';
                    else if (args[0] == 1)
                        Module.ctxs[ctx_id].textAlign = 'center';
                    else if (args[0] == 2)
                        Module.ctxs[ctx_id].textAlign = 'right';
                    break;
                case 8:
                    if (args[0] == 0)
                        Module.ctxs[ctx_id].textBaseline = 'top';
                    else if (args[0] == 1)
                        Module.ctxs[ctx_id].textBaseline = 'middle';
                    else if (args[0] == 2)
                        Module.ctxs[ctx_id].textBaseline = 'bottom';
                    break;
                case 9:
                    Module.ctxs[ctx_id].setTransform(args[0], args[1], args[3], args[4], args[2], args[5]);
                    break;
                case 10:
                    Module.ctxs[ctx_id].save();
                    break;
                case 11:
                    Module.ctxs[ctx_id].restore();
                    break;
                case 12:
                    Module.ctxs[ctx_id].beginPath();
                    break;
                case 13:
                    Module.ctxs[ctx_id].moveTo(args[0], args[1]);
                    break;
                case 14:
                    Module.ctxs[ctx_id].lineTo(args[0], args[1]);
                    break;
                case 15:
                    Module.ctxs[ctx_id].quadraticCurveTo(args[0], args[1], args[2], args[3]);
                    break;
                case 16:
                    Module.ctxs[ctx_id].bezierCurveTo(args[0], args[1], args[2], args[3], args[4], args[5]);
                    break;
                case 17:
                    Module.ctxs[ctx_id].arc(args[0], args[1], args[2], args[3], args[4], args[5]);
                    break;
                case 18:
                    Module.ctxs[ctx_id].ellipse(args[0], args[1], args[2], args[3], 0, 6.283185307179586);
                    break;
                case 19:
                    Module.ctxs[ctx_id].rect(args[0], args[1], args[2], args[3]);
                    break;
                case 20:
                    Module.ctxs[ctx_id].drawImage(Module.ctxs[args[0]].canvas, args[1], args[2]);
                    break;
                case 21:
                    Module.ctxs[ctx_id].fillRect(args[0], args[1], args[2], args[3]);
                    break;
                case 22:
                    Module.ctxs[ctx_id].strokeRect(args[0], args[1], args[2], args[3]);
                    break;
                case 23:
                    Module.ctxs[ctx_id].fill();
                    break;
                case 24:
                    Module.ctxs[ctx_id].stroke();
                    break;
                case 25:
                    Module.ctxs[ctx_id].clip();
                    break;
                case 26:
                    Module.ctxs[ctx_id].clip("evenodd");
                    break;
                case 27:
                    str = Module.ReadCstr(char_arg);
                    Module.ctxs[ctx_id].fillText(str, args[0], args[1]);
                    Module._free(char_arg);
                    break;
                case 28:
                    str = Module.ReadCstr(char_arg);
                    Module.ctxs[ctx_id].strokeText(str, args[0], args[1]);
                    Module._free(char_arg);
                    break;
                default:
                    break;
            }
        }
    }, &instruction_tape[0], instruction_size, sizeof (struct renderer_args));
    instruction_size = 0;
}

uint32_t rr_renderer_get_op_size()
{
    return instruction_size;
}