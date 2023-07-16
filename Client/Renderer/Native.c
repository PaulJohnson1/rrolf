#include <Client/Renderer/Renderer.h>

#include <math.h>
#include <string.h>

void rr_renderer_init(struct rr_renderer *this)
{
    memset(this, 0, sizeof(*this));
    this->state.transform_matrix[0] = 1;
    this->state.transform_matrix[4] = 1;
    this->surface = cairo_image_surface_create(
        CAIRO_FORMAT_ARGB32, 500, 500); // default size, should be resized later
    this->context = cairo_create(this->surface);
}

void rr_renderer_set_dimensions(struct rr_renderer *this, float w, float h)
{
    this->width = w;
    this->height = h;
    cairo_surface_destroy(this->surface);
    this->surface = cairo_image_surface_create(CAIRO_FORMAT_ARGB32, w, h);
    cairo_destroy(this->context);
    this->context = cairo_create(this->surface);
}

void rr_renderer_set_fill(struct rr_renderer *this, uint32_t c)
{
    // Convert the uint32_t color into RGBA
    double r = ((c >> 16) & 0xFF) / 255.0;
    double g = ((c >> 8) & 0xFF) / 255.0;
    double b = (c & 0xFF) / 255.0;
    double a = ((c >> 24) & 0xFF) / 255.0;

    cairo_set_source_rgba(this->context, r, g, b, a);
}

void rr_renderer_set_stroke(struct rr_renderer *this, uint32_t c)
{
    // Convert the uint32_t color into RGBA
    double r = ((c >> 16) & 0xFF) / 255.0;
    double g = ((c >> 8) & 0xFF) / 255.0;
    double b = (c & 0xFF) / 255.0;
    double a = ((c >> 24) & 0xFF) / 255.0;

    cairo_set_source_rgba(this->context, r, g, b, a);
}

void rr_renderer_set_line_width(struct rr_renderer *this, float w)
{
    cairo_set_line_width(this->context, w);
}

void rr_renderer_set_global_alpha(struct rr_renderer *this, float a)
{
    // Not applicable in cairo
}

void rr_renderer_set_line_cap(struct rr_renderer *this, uint8_t l)
{
    cairo_line_cap_t cap;
    switch (l)
    {
    case 0:
        cap = CAIRO_LINE_CAP_BUTT;
        break;
    case 1:
        cap = CAIRO_LINE_CAP_ROUND;
        break;
    case 2:
        cap = CAIRO_LINE_CAP_SQUARE;
        break;
    }
    cairo_set_line_cap(this->context, cap);
}

void rr_renderer_set_line_join(struct rr_renderer *this, uint8_t l)
{
    cairo_line_join_t join;
    switch (l)
    {
    case 0:
        join = CAIRO_LINE_JOIN_BEVEL;
        break;
    case 1:
        join = CAIRO_LINE_JOIN_ROUND;
        break;
    case 2:
        join = CAIRO_LINE_JOIN_MITER;
        break;
    }
    cairo_set_line_join(this->context, join);
}

void rr_renderer_update_transform(struct rr_renderer *this)
{
    cairo_matrix_t matrix;
    cairo_matrix_init(
        &matrix, this->state.transform_matrix[0],
        this->state.transform_matrix[1], this->state.transform_matrix[3],
        this->state.transform_matrix[4], this->state.transform_matrix[2],
        this->state.transform_matrix[5]);
    cairo_set_matrix(this->context, &matrix);
}

void rr_renderer_save(struct rr_renderer *this) { cairo_save(this->context); }

void rr_renderer_restore(struct rr_renderer *this)
{
    cairo_restore(this->context);
}

void rr_renderer_begin_path(struct rr_renderer *this)
{
    cairo_new_path(this->context);
}

void rr_renderer_move_to(struct rr_renderer *this, float x, float y)
{
    cairo_move_to(this->context, x, y);
}

void rr_renderer_line_to(struct rr_renderer *this, float x, float y)
{
    cairo_line_to(this->context, x, y);
}

void rr_renderer_quadratic_curve_to(struct rr_renderer *this, float x1,
                                    float y1, float x, float y)
{
    double x0, y0;
    cairo_get_current_point(this->context, &x0, &y0);
    cairo_curve_to(this->context, x0 + 2. / 3 * (x1 - x0),
                   y0 + 2. / 3 * (y1 - y0), x1, y1, x, y);
}

void rr_renderer_bezier_curve_to(struct rr_renderer *this, float x1, float y1,
                                 float x2, float y2, float x, float y)
{
    cairo_curve_to(this->context, x1, y1, x2, y2, x, y);
}

void rr_renderer_partial_arc(struct rr_renderer *this, float x, float y,
                             float r, float sa, float ea, uint8_t ccw)
{
    if (ccw)
        cairo_arc_negative(this->context, x, y, r, sa, ea);
    else
        cairo_arc(this->context, x, y, r, sa, ea);
}

void rr_renderer_ellipse(struct rr_renderer *this, float x, float y, float rx,
                         float ry)
{
    cairo_save(this->context);
    cairo_translate(this->context, x, y);
    cairo_scale(this->context, rx, ry);
    cairo_arc(this->context, 0., 0., 1., 0., 2 * M_PI);
    cairo_restore(this->context);
}

void rr_renderer_rect(struct rr_renderer *this, float x, float y, float w,
                      float h)
{
    cairo_rectangle(this->context, x, y, w, h);
}

void rr_renderer_fill_rect(struct rr_renderer *this, float x, float y, float w,
                           float h)
{
    cairo_rectangle(this->context, x, y, w, h);
    cairo_fill(this->context);
}

void rr_renderer_stroke_rect(struct rr_renderer *this, float x, float y,
                             float w, float h)
{
    cairo_rectangle(this->context, x, y, w, h);
    cairo_stroke(this->context);
}

void rr_renderer_fill(struct rr_renderer *this) { cairo_fill(this->context); }

void rr_renderer_stroke(struct rr_renderer *this)
{
    cairo_stroke(this->context);
}

void rr_renderer_clip(struct rr_renderer *this) { cairo_clip(this->context); }

void rr_renderer_clip2(struct rr_renderer *this)
{
    cairo_fill_rule_t fill_rule = CAIRO_FILL_RULE_EVEN_ODD;
    cairo_set_fill_rule(this->context, fill_rule);
    cairo_clip(this->context);
}

void rr_renderer_draw_image(struct rr_renderer *this, struct rr_renderer *b) {}
void rr_renderer_fill_text(struct rr_renderer *this, char const *a, float b,
                           float c)
{
}
void rr_renderer_stroke_text(struct rr_renderer *this, char const *a, float b,
                             float c)
{
}
void rr_renderer_set_text_align(struct rr_renderer *this, uint8_t a) {}
void rr_renderer_set_text_baseline(struct rr_renderer *this, uint8_t a) {}
void rr_renderer_set_text_size(struct rr_renderer *this, float a) {}
void rr_renderer_draw_svg(struct rr_renderer *this, char *svg, float x, float y)
{
}
float rr_renderer_get_text_size(char const *a) { return 0; }
