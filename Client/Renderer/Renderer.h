#pragma once

#include <stdint.h>

#ifdef EMSCRIPTEN
#include <emscripten.h>
#else
#endif

struct rr_renderer_paint
{
    uint8_t alpha;
    uint8_t red;
    uint8_t green;
    uint8_t blue;
};

struct rr_renderer_filter
{
    uint32_t color;
    float amount;
};

struct rr_renderer_context_state
{
    float transform_matrix[6];
    struct rr_renderer_filter filter;
};

struct rr_renderer
{
    //uint8_t text_align;
    //uint8_t text_baseline;
    //uint8_t line_cap;
    //uint8_t line_join;
    uint32_t context_id;
    //struct rr_renderer_paint fill_style;
    //struct rr_renderer_paint stroke_style;
    
    //float line_width;

    float width;
    float height;
    float scale;

    struct rr_renderer_context_state state;
};

void rr_renderer_init(struct rr_renderer *);

void rr_renderer_init_context_state(struct rr_renderer *, struct rr_renderer_context_state *);
void rr_renderer_free_context_state(struct rr_renderer *, struct rr_renderer_context_state *);

void rr_renderer_set_fill(struct rr_renderer *, uint32_t);
void rr_renderer_set_stroke(struct rr_renderer *, uint32_t);

void rr_renderer_set_line_width(struct rr_renderer *, float);
void rr_renderer_set_text_size(struct rr_renderer *, float);

void rr_renderer_set_line_cap(struct rr_renderer *, uint8_t);
void rr_renderer_set_line_join(struct rr_renderer *, uint8_t);
void rr_renderer_set_text_align(struct rr_renderer *, uint8_t);
void rr_renderer_set_text_baseline(struct rr_renderer *, uint8_t);

void rr_renderer_update_transform(struct rr_renderer *);
void rr_renderer_set_transform(struct rr_renderer *, float, float, float, float, float, float);
void rr_renderer_translate(struct rr_renderer *, float, float);
void rr_renderer_rotate(struct rr_renderer *, float);
void rr_renderer_scale(struct rr_renderer *, float);
void rr_renderer_scale2(struct rr_renderer *, float, float);

void rr_renderer_save(struct rr_renderer *);
void rr_renderer_restore(struct rr_renderer *);

void rr_renderer_begin_path(struct rr_renderer *);
void rr_renderer_move_to(struct rr_renderer *, float, float);
void rr_renderer_line_to(struct rr_renderer *, float, float);
void rr_renderer_quadratic_curve_to(struct rr_renderer *, float, float, float, float);
void rr_renderer_bezier_curve_to(struct rr_renderer *, float, float, float, float, float, float);
void rr_renderer_arc(struct rr_renderer *, float, float, float);
void rr_renderer_partial_arc(struct rr_renderer *, float, float, float, float, float);
void rr_renderer_ellipse(struct rr_renderer *, float, float, float, float);
void rr_renderer_rect(struct rr_renderer *, float, float, float, float);
void rr_renderer_round_rect(struct rr_renderer *, float, float, float, float, float);

void rr_renderer_fill_rect(struct rr_renderer *, float, float, float, float);
void rr_renderer_stroke_rect(struct rr_renderer *, float, float, float, float);
void rr_renderer_fill(struct rr_renderer *);
void rr_renderer_stroke(struct rr_renderer *);
void rr_renderer_clip(struct rr_renderer *);

void rr_renderer_fill_text(struct rr_renderer *, char const *, float, float);
void rr_renderer_stroke_text(struct rr_renderer *,  char const *, float, float);
