// Copyright (C) 2024  Paul Johnson

// This program is free software: you can redistribute it and/or modify
// it under the terms of the GNU Affero General Public License as
// published by the Free Software Foundation, either version 3 of the
// License, or (at your option) any later version.

// This program is distributed in the hope that it will be useful,
// but WITHOUT ANY WARRANTY; without even the implied warranty of
// MERCHANTABILITY or FITNESS FOR A PARTICULAR PURPOSE.  See the
// GNU Affero General Public License for more details.

// You should have received a copy of the GNU Affero General Public License
// along with this program.  If not, see <https://www.gnu.org/licenses/>.

#include <Client/Renderer/Renderer.h>

#include <emscripten.h>
#include <math.h>
#include <stdlib.h>
#include <string.h>

#include <Shared/Utilities.h>

struct renderer_args
{
    uint8_t type;
    uint16_t context_id;
    uint16_t context_id_2;
    float args[6];
    char const *text_arg;
};

static struct renderer_args instruction_tape[INSTRUCTION_QUEUE_MAX_SIZE] = {0};
static uint32_t instruction_size = 0;
static uint32_t rollovers = 0;

static void update_if_transformed(struct rr_renderer *this)
{
    if (this->matrix_moddified)
    {
        this->matrix_moddified = 0;
        instruction_tape[instruction_size].type = 9;
        instruction_tape[instruction_size].context_id = this->context_id;
        instruction_tape[instruction_size].args[0] =
            this->state.transform_matrix[0];
        instruction_tape[instruction_size].args[1] =
            this->state.transform_matrix[1];
        instruction_tape[instruction_size].args[2] =
            this->state.transform_matrix[2];
        instruction_tape[instruction_size].args[3] =
            this->state.transform_matrix[3];
        instruction_tape[instruction_size].args[4] =
            this->state.transform_matrix[4];
        instruction_tape[instruction_size].args[5] =
            this->state.transform_matrix[5];
        if (++instruction_size == INSTRUCTION_QUEUE_MAX_SIZE)
            rr_renderer_execute_instructions();
    }
}

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
    instruction_tape[instruction_size].args[3] =
        (float)(c >> 24) * 1.0f / 255.0f;
    if (++instruction_size == INSTRUCTION_QUEUE_MAX_SIZE)
        rr_renderer_execute_instructions();
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
    instruction_tape[instruction_size].args[3] =
        (float)(c >> 24) * 1.0f / 255.0f;
    if (++instruction_size == INSTRUCTION_QUEUE_MAX_SIZE)
        rr_renderer_execute_instructions();
}

void rr_renderer_set_line_width(struct rr_renderer *this, float w)
{
    instruction_tape[instruction_size].type = 2;
    instruction_tape[instruction_size].context_id = this->context_id;
    instruction_tape[instruction_size].args[0] = w;
    if (++instruction_size == INSTRUCTION_QUEUE_MAX_SIZE)
        rr_renderer_execute_instructions();
}

void rr_renderer_set_text_size(struct rr_renderer *this, float s)
{
    instruction_tape[instruction_size].type = 3;
    instruction_tape[instruction_size].context_id = this->context_id;
    instruction_tape[instruction_size].args[0] = s;
    if (++instruction_size == INSTRUCTION_QUEUE_MAX_SIZE)
        rr_renderer_execute_instructions();
}

void rr_renderer_set_global_alpha(struct rr_renderer *this, float a)
{
    instruction_tape[instruction_size].type = 4;
    instruction_tape[instruction_size].context_id = this->context_id;
    instruction_tape[instruction_size].args[0] = a;
    this->state.global_alpha = a;
    if (++instruction_size == INSTRUCTION_QUEUE_MAX_SIZE)
        rr_renderer_execute_instructions();
}

void rr_renderer_set_line_cap(struct rr_renderer *this, uint8_t l)
{
    instruction_tape[instruction_size].type = 5;
    instruction_tape[instruction_size].context_id = this->context_id;
    instruction_tape[instruction_size].args[0] = l;
    if (++instruction_size == INSTRUCTION_QUEUE_MAX_SIZE)
        rr_renderer_execute_instructions();
}

void rr_renderer_set_line_join(struct rr_renderer *this, uint8_t l)
{
    instruction_tape[instruction_size].type = 6;
    instruction_tape[instruction_size].context_id = this->context_id;
    instruction_tape[instruction_size].args[0] = l;
    if (++instruction_size == INSTRUCTION_QUEUE_MAX_SIZE)
        rr_renderer_execute_instructions();
}

void rr_renderer_set_text_align(struct rr_renderer *this, uint8_t l)
{
    instruction_tape[instruction_size].type = 7;
    instruction_tape[instruction_size].context_id = this->context_id;
    instruction_tape[instruction_size].args[0] = l;
    if (++instruction_size == INSTRUCTION_QUEUE_MAX_SIZE)
        rr_renderer_execute_instructions();
}

void rr_renderer_set_text_baseline(struct rr_renderer *this, uint8_t l)
{
    instruction_tape[instruction_size].type = 8;
    instruction_tape[instruction_size].context_id = this->context_id;
    instruction_tape[instruction_size].args[0] = l;
    if (++instruction_size == INSTRUCTION_QUEUE_MAX_SIZE)
        rr_renderer_execute_instructions();
}

void rr_renderer_update_transform(struct rr_renderer *this)
{
    this->matrix_moddified = 1;
}

void rr_renderer_save(struct rr_renderer *this)
{
    instruction_tape[instruction_size].type = 10;
    instruction_tape[instruction_size].context_id = this->context_id;
    if (++instruction_size == INSTRUCTION_QUEUE_MAX_SIZE)
        rr_renderer_execute_instructions();
}

void rr_renderer_restore(struct rr_renderer *this)
{
    this->matrix_moddified = 1;
    instruction_tape[instruction_size].type = 11;
    instruction_tape[instruction_size].context_id = this->context_id;
    if (++instruction_size == INSTRUCTION_QUEUE_MAX_SIZE)
        rr_renderer_execute_instructions();
}

void rr_renderer_begin_path(struct rr_renderer *this)
{
    update_if_transformed(this);
    instruction_tape[instruction_size].type = 12;
    instruction_tape[instruction_size].context_id = this->context_id;
    if (++instruction_size == INSTRUCTION_QUEUE_MAX_SIZE)
        rr_renderer_execute_instructions();
}

void rr_renderer_move_to(struct rr_renderer *this, float x, float y)
{
    update_if_transformed(this);
    instruction_tape[instruction_size].type = 13;
    instruction_tape[instruction_size].context_id = this->context_id;
    instruction_tape[instruction_size].args[0] = x;
    instruction_tape[instruction_size].args[1] = y;
    if (++instruction_size == INSTRUCTION_QUEUE_MAX_SIZE)
        rr_renderer_execute_instructions();
}

void rr_renderer_line_to(struct rr_renderer *this, float x, float y)
{
    update_if_transformed(this);
    instruction_tape[instruction_size].type = 14;
    instruction_tape[instruction_size].context_id = this->context_id;
    instruction_tape[instruction_size].args[0] = x;
    instruction_tape[instruction_size].args[1] = y;
    if (++instruction_size == INSTRUCTION_QUEUE_MAX_SIZE)
        rr_renderer_execute_instructions();
}

void rr_renderer_quadratic_curve_to(struct rr_renderer *this, float x1,
                                    float y1, float x, float y)
{
    update_if_transformed(this);
    instruction_tape[instruction_size].type = 15;
    instruction_tape[instruction_size].context_id = this->context_id;
    instruction_tape[instruction_size].args[0] = x1;
    instruction_tape[instruction_size].args[1] = y1;
    instruction_tape[instruction_size].args[2] = x;
    instruction_tape[instruction_size].args[3] = y;
    if (++instruction_size == INSTRUCTION_QUEUE_MAX_SIZE)
        rr_renderer_execute_instructions();
}

void rr_renderer_bezier_curve_to(struct rr_renderer *this, float x1, float y1,
                                 float x2, float y2, float x, float y)
{
    update_if_transformed(this);
    instruction_tape[instruction_size].type = 16;
    instruction_tape[instruction_size].context_id = this->context_id;
    instruction_tape[instruction_size].args[0] = x1;
    instruction_tape[instruction_size].args[1] = y1;
    instruction_tape[instruction_size].args[2] = x2;
    instruction_tape[instruction_size].args[3] = y2;
    instruction_tape[instruction_size].args[4] = x;
    instruction_tape[instruction_size].args[5] = y;
    if (++instruction_size == INSTRUCTION_QUEUE_MAX_SIZE)
        rr_renderer_execute_instructions();
}
void rr_renderer_partial_arc(struct rr_renderer *this, float x, float y,
                             float r, float sa, float ea, uint8_t ccw)
{
    update_if_transformed(this);
    instruction_tape[instruction_size].type = 17;
    instruction_tape[instruction_size].context_id = this->context_id;
    instruction_tape[instruction_size].args[0] = x;
    instruction_tape[instruction_size].args[1] = y;
    instruction_tape[instruction_size].args[2] = r;
    instruction_tape[instruction_size].args[3] = sa;
    instruction_tape[instruction_size].args[4] = ea;
    instruction_tape[instruction_size].args[5] = ccw;
    if (++instruction_size == INSTRUCTION_QUEUE_MAX_SIZE)
        rr_renderer_execute_instructions();
}

void rr_renderer_ellipse(struct rr_renderer *this, float x, float y, float rx,
                         float ry)
{
    update_if_transformed(this);
    instruction_tape[instruction_size].type = 18;
    instruction_tape[instruction_size].context_id = this->context_id;
    instruction_tape[instruction_size].args[0] = x;
    instruction_tape[instruction_size].args[1] = y;
    instruction_tape[instruction_size].args[2] = rx;
    instruction_tape[instruction_size].args[3] = ry;
    if (++instruction_size == INSTRUCTION_QUEUE_MAX_SIZE)
        rr_renderer_execute_instructions();
}

void rr_renderer_rect(struct rr_renderer *this, float x, float y, float w,
                      float h)
{
    update_if_transformed(this);
    instruction_tape[instruction_size].type = 19;
    instruction_tape[instruction_size].context_id = this->context_id;
    instruction_tape[instruction_size].args[0] = x;
    instruction_tape[instruction_size].args[1] = y;
    instruction_tape[instruction_size].args[2] = w;
    instruction_tape[instruction_size].args[3] = h;
    if (++instruction_size == INSTRUCTION_QUEUE_MAX_SIZE)
        rr_renderer_execute_instructions();
}

void rr_renderer_draw_clipped_image(struct rr_renderer *this,
                                    struct rr_renderer *image, float sx,
                                    float sy, float sw, float sh, float dx,
                                    float dy)
{
    update_if_transformed(this);
    instruction_tape[instruction_size].type = 20;
    instruction_tape[instruction_size].context_id = this->context_id;
    instruction_tape[instruction_size].context_id_2 = image->context_id;
    instruction_tape[instruction_size].args[0] = sx - sw / 2;
    instruction_tape[instruction_size].args[1] = sy - sh / 2;
    instruction_tape[instruction_size].args[2] = sw;
    instruction_tape[instruction_size].args[3] = sh;
    instruction_tape[instruction_size].args[4] = dx - sw / 2;
    instruction_tape[instruction_size].args[5] = dy - sh / 2;
    if (++instruction_size == INSTRUCTION_QUEUE_MAX_SIZE)
        rr_renderer_execute_instructions();
}

void rr_renderer_draw_translated_image(struct rr_renderer *this,
                                       struct rr_renderer *image, float x,
                                       float y)
{
    rr_renderer_draw_clipped_image(this, image, image->width / 2,
                                   image->height / 2, image->width,
                                   image->height, x, y);
}

void rr_renderer_draw_image(struct rr_renderer *this, struct rr_renderer *image)
{
    rr_renderer_draw_translated_image(this, image, 0, 0);
}

// note: should only be called at the game instantiation.
void rr_renderer_draw_svg(struct rr_renderer *this, char *svg, float x, float y)
{
    update_if_transformed(this);
    EM_ASM(
        {
            let string = UTF8ToString($1);
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
    update_if_transformed(this);
    instruction_tape[instruction_size].type = 21;
    instruction_tape[instruction_size].context_id = this->context_id;
    instruction_tape[instruction_size].args[0] = x;
    instruction_tape[instruction_size].args[1] = y;
    instruction_tape[instruction_size].args[2] = w;
    instruction_tape[instruction_size].args[3] = h;
    if (++instruction_size == INSTRUCTION_QUEUE_MAX_SIZE)
        rr_renderer_execute_instructions();
}

void rr_renderer_stroke_rect(struct rr_renderer *this, float x, float y,
                             float w, float h)
{
    update_if_transformed(this);
    instruction_tape[instruction_size].type = 22;
    instruction_tape[instruction_size].context_id = this->context_id;
    instruction_tape[instruction_size].args[0] = x;
    instruction_tape[instruction_size].args[1] = y;
    instruction_tape[instruction_size].args[2] = w;
    instruction_tape[instruction_size].args[3] = h;
    if (++instruction_size == INSTRUCTION_QUEUE_MAX_SIZE)
        rr_renderer_execute_instructions();
}

void rr_renderer_fill(struct rr_renderer *this)
{
    update_if_transformed(this);
    instruction_tape[instruction_size].type = 23;
    instruction_tape[instruction_size].context_id = this->context_id;
    if (++instruction_size == INSTRUCTION_QUEUE_MAX_SIZE)
        rr_renderer_execute_instructions();
}

void rr_renderer_stroke(struct rr_renderer *this)
{
    update_if_transformed(this);
    instruction_tape[instruction_size].type = 24;
    instruction_tape[instruction_size].context_id = this->context_id;
    if (++instruction_size == INSTRUCTION_QUEUE_MAX_SIZE)
        rr_renderer_execute_instructions();
}

void rr_renderer_clip(struct rr_renderer *this)
{
    update_if_transformed(this);
    instruction_tape[instruction_size].type = 25;
    instruction_tape[instruction_size].context_id = this->context_id;
    if (++instruction_size == INSTRUCTION_QUEUE_MAX_SIZE)
        rr_renderer_execute_instructions();
}

void rr_renderer_clip2(struct rr_renderer *this)
{
    update_if_transformed(this);
    instruction_tape[instruction_size].type = 26;
    instruction_tape[instruction_size].context_id = this->context_id;
    if (++instruction_size == INSTRUCTION_QUEUE_MAX_SIZE)
        rr_renderer_execute_instructions();
}

void rr_renderer_fill_text(struct rr_renderer *this, char const *c, float x,
                           float y)
{
    update_if_transformed(this);
    instruction_tape[instruction_size].type = 27;
    instruction_tape[instruction_size].context_id = this->context_id;
    instruction_tape[instruction_size].args[0] = x;
    instruction_tape[instruction_size].args[1] = y;
    uint32_t len = strlen(c) + 1;
    char *text = malloc(len * (sizeof *text));
    memcpy(text, c, len * sizeof *text);
    instruction_tape[instruction_size].text_arg = text;
    if (++instruction_size == INSTRUCTION_QUEUE_MAX_SIZE)
        rr_renderer_execute_instructions();
}
void rr_renderer_stroke_text(struct rr_renderer *this, char const *c, float x,
                             float y)
{
    update_if_transformed(this);
    instruction_tape[instruction_size].type = 28;
    instruction_tape[instruction_size].context_id = this->context_id;
    instruction_tape[instruction_size].args[0] = x;
    instruction_tape[instruction_size].args[1] = y;
    uint32_t len = strlen(c) + 1;
    char *text = malloc(len * (sizeof *text));
    memcpy(text, c, len * sizeof *text);
    instruction_tape[instruction_size].text_arg = text;
    if (++instruction_size == INSTRUCTION_QUEUE_MAX_SIZE)
        rr_renderer_execute_instructions();
}

float rr_renderer_get_text_size(char const *c)
{
    // clang-format off
    return EM_ASM_DOUBLE(
        {
            let string = UTF8ToString($0);
            Module.ctxs[0].font = '1px Ubuntu';
            return Module.ctxs[0].measureText(string).width;
        },
        c);
    // clang-format on
}

void rr_renderer_execute_instructions()
{
    ++rollovers;
    EM_ASM(
        {
            let instr = $0;
            for (let n = 0; n < $1; ++n)
            {
                const ctx_id = HEAPU16[instr + 2 >> 1];
                const ctx_id_2 = HEAPU16[instr + 4 >> 1];
                const args = HEAPF32.subarray(instr + 8 >> 2, instr + 32 >> 2);
                const char_arg = HEAPU32[instr + 32 >> 2];
                let str;
                switch (HEAPU8[instr])
                {
                case 0:
                    Module.ctxs[ctx_id].fillStyle = "rgba(" + args[0] + ',' +
                                                    args[1] + ',' + args[2] +
                                                    ',' + args[3] + ')';
                    break;
                case 1:
                    Module.ctxs[ctx_id].strokeStyle = "rgba(" + args[0] + ',' +
                                                      args[1] + ',' + args[2] +
                                                      ',' + args[3] + ')';
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
                    Module.ctxs[ctx_id].setTransform(args[0], args[1], args[3],
                                                     args[4], args[2], args[5]);
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
                    Module.ctxs[ctx_id].quadraticCurveTo(args[0], args[1],
                                                         args[2], args[3]);
                    break;
                case 16:
                    Module.ctxs[ctx_id].bezierCurveTo(
                        args[0], args[1], args[2], args[3], args[4], args[5]);
                    break;
                case 17:
                    Module.ctxs[ctx_id].arc(args[0], args[1], args[2], args[3],
                                            args[4], args[5]);
                    break;
                case 18:
                    Module.ctxs[ctx_id].ellipse(args[0], args[1], args[2],
                                                args[3], 0, 6.283185307179586,
                                                0);
                    break;
                case 19:
                    Module.ctxs[ctx_id].rect(args[0], args[1], args[2],
                                             args[3]);
                    break;
                case 20:
                    Module.ctxs[ctx_id].drawImage(
                        Module.ctxs[ctx_id_2].canvas, args[0], args[1], args[2],
                        args[3], args[4], args[5], args[2], args[3]);
                    break;
                case 21:
                    Module.ctxs[ctx_id].fillRect(args[0], args[1], args[2],
                                                 args[3]);
                    break;
                case 22:
                    Module.ctxs[ctx_id].strokeRect(args[0], args[1], args[2],
                                                   args[3]);
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
                    str = UTF8ToString(char_arg);
                    Module.ctxs[ctx_id].fillText(str, args[0], args[1]);
                    _free(char_arg);
                    break;
                case 28:
                    str = UTF8ToString(char_arg);
                    Module.ctxs[ctx_id].strokeText(str, args[0], args[1]);
                    _free(char_arg);
                    break;
                default:
                    break;
                }
                instr += $2;
            }
        },
        &instruction_tape[0], instruction_size, sizeof(struct renderer_args));
    instruction_size = 0;
}

uint32_t rr_renderer_get_op_size()
{
    return instruction_size + rollovers * INSTRUCTION_QUEUE_MAX_SIZE;
}

void rr_renderer_reset_instruction_queue() { instruction_size = rollovers = 0; }