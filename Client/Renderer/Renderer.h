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

#pragma once

#include <stdint.h>

#ifdef EMSCRIPTEN
#include <emscripten.h>
#else
// todo: skia
#endif

// reason this is here is because this header is also included in the native.cc
// file and in the wasm.c file for the target specific function implementations.
#ifdef __cplusplus
extern "C"
{
#endif
#define INSTRUCTION_QUEUE_MAX_SIZE 16384

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
        float global_alpha;
    };

    struct rr_renderer
    {
#ifndef EMSCRIPTEN
        // todo: skia
#else
    uint32_t context_id;
#endif
        struct rr_renderer_context_state state;
        float width;
        float height;
        float scale;

        uint8_t matrix_moddified;
    };

    struct rr_sprite_bounds
    {
        float x;
        float y;
        float w;
        float h;
        void (*render)(struct rr_renderer *);
    };

    struct rr_renderer_spritesheet
    {
        struct rr_renderer renderer;
        struct rr_sprite_bounds sprites[16];
    };

    void rr_renderer_init(struct rr_renderer *);
    void rr_renderer_set_dimensions(struct rr_renderer *, float, float);

    void rr_renderer_spritesheet_init(struct rr_renderer_spritesheet *,
                                      void (*)(struct rr_renderer *), ...);
    void render_sprite_from_cache(struct rr_renderer *,
                                  struct rr_renderer_spritesheet *, uint32_t);

    void rr_renderer_context_state_init(struct rr_renderer *,
                                        struct rr_renderer_context_state *);
    void rr_renderer_context_state_free(struct rr_renderer *,
                                        struct rr_renderer_context_state *);

    void rr_renderer_add_color_filter(struct rr_renderer *, uint32_t, float);
    void rr_renderer_reset_color_filter(struct rr_renderer *);

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
    void rr_renderer_draw_clipped_image(struct rr_renderer *,
                                        struct rr_renderer *, float, float,
                                        float, float, float, float);
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

    void rr_renderer_execute_instructions();
    uint32_t rr_renderer_get_op_size();
    void rr_renderer_reset_instruction_queue();
#ifdef __cplusplus
}
#endif
