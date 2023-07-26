#pragma once

#include <stdint.h>

#ifdef EMSCRIPTEN
#include <emscripten.h>
#else
#include <cairo/cairo.h>
#endif

#ifdef __cplusplus
extern "C"
{
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
#ifndef EMSCRIPTEN
    cairo_t *context;
    cairo_surface_t *surface;
#else
    uint32_t context_id;
#endif
    float width;
    float height;
    float scale;

    struct rr_renderer_context_state state;
};

void rr_renderer_init(struct rr_renderer *);
void rr_renderer_set_dimensions(struct rr_renderer *, float, float);

void rr_renderer_context_state_init(struct rr_renderer *,
                                    struct rr_renderer_context_state *);
void rr_renderer_context_state_free(struct rr_renderer *,
                                    struct rr_renderer_context_state *);

void rr_renderer_set_fill(struct rr_renderer *, uint32_t);
void rr_renderer_set_stroke(struct rr_renderer *, uint32_t);

void rr_renderer_set_line_width(struct rr_renderer *, float);
void rr_renderer_set_text_size(struct rr_renderer *, float);
void rr_renderer_set_global_alpha(struct rr_renderer *, float);

void rr_renderer_set_line_cap(struct rr_renderer *, uint8_t);
void rr_renderer_set_line_join(struct rr_renderer *, uint8_t);
void rr_renderer_set_text_align(struct rr_renderer *, uint8_t);
void rr_renderer_set_text_baseline(struct rr_renderer *, uint8_t);

void rr_renderer_update_transform(struct rr_renderer *);
void rr_renderer_set_transform(struct rr_renderer *, float, float, float,
                                float, float, float);
void rr_renderer_translate(struct rr_renderer *, float, float);
void rr_renderer_rotate(struct rr_renderer *, float);
void rr_renderer_scale(struct rr_renderer *, float);
void rr_renderer_scale2(struct rr_renderer *, float, float);

void rr_renderer_save(struct rr_renderer *);
void rr_renderer_restore(struct rr_renderer *);

void rr_renderer_begin_path(struct rr_renderer *);
void rr_renderer_move_to(struct rr_renderer *, float, float);
void rr_renderer_line_to(struct rr_renderer *, float, float);
void rr_renderer_quadratic_curve_to(struct rr_renderer *, float, float,
                                    float, float);
void rr_renderer_bezier_curve_to(struct rr_renderer *, float, float, float,
                                    float, float, float);
void rr_renderer_arc(struct rr_renderer *, float, float, float);
void rr_renderer_reverse_arc(struct rr_renderer *, float, float, float);
void rr_renderer_partial_arc(struct rr_renderer *, float, float, float,
                                float, float, uint8_t);
void rr_renderer_ellipse(struct rr_renderer *, float, float, float, float);
void rr_renderer_rect(struct rr_renderer *, float, float, float, float);
void rr_renderer_round_rect(struct rr_renderer *, float, float, float,
                            float, float);

void rr_renderer_draw_translated_image(struct rr_renderer *,
                                        struct rr_renderer *, float, float);
void rr_renderer_draw_image(struct rr_renderer *, struct rr_renderer *);
void rr_renderer_draw_svg(struct rr_renderer *, char *svg, float x,
                            float y);

void rr_renderer_fill_rect(struct rr_renderer *, float, float, float,
                            float);
void rr_renderer_stroke_rect(struct rr_renderer *, float, float, float,
                                float);
void rr_renderer_fill(struct rr_renderer *);
void rr_renderer_stroke(struct rr_renderer *);
void rr_renderer_clip(struct rr_renderer *);
void rr_renderer_clip2(struct rr_renderer *);

void rr_renderer_fill_text(struct rr_renderer *, char const *, float,
                            float);
void rr_renderer_stroke_text(struct rr_renderer *, char const *, float,
                                float);

float rr_renderer_get_text_size(char const *);

void rr_renderer_execute_order_66();
uint32_t rr_renderer_get_op_size();
#ifdef __cplusplus
}
#endif