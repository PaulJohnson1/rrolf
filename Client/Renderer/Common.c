#include <Client/Renderer/Renderer.h>

#include <Shared/Utilities.h>
#include <math.h>
#include <string.h>

void rr_renderer_context_state_init(struct rr_renderer *this,
                                    struct rr_renderer_context_state *state)
{
    memcpy(state, &this->state, sizeof *state);
    rr_renderer_save(this);
}

void rr_renderer_context_state_free(struct rr_renderer *this,
                                    struct rr_renderer_context_state *state)
{
    memcpy(&this->state, state, sizeof *state);
    rr_renderer_restore(this);
}

void rr_renderer_set_transform(struct rr_renderer *this, float a, float b,
                               float c, float d, float e, float f)
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
    this->state.transform_matrix[2] += x * this->state.transform_matrix[0] +
                                       y * this->state.transform_matrix[3];
    this->state.transform_matrix[5] += x * this->state.transform_matrix[1] +
                                       y * this->state.transform_matrix[4];
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

void rr_renderer_arc(struct rr_renderer *this, float x, float y, float r)
{
    rr_renderer_partial_arc(this, x, y, r, 0, 2 * M_PI, 0);
}

void rr_renderer_reverse_arc(struct rr_renderer *this, float x, float y,
                             float r)
{
    rr_renderer_partial_arc(this, x, y, r, 2 * M_PI, 0, 1);
}

void rr_renderer_round_rect(struct rr_renderer *this, float x, float y, float w,
                            float h, float r)
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

void rr_renderer_add_color_filter(struct rr_renderer *this, uint32_t color,
                                  float amount)
{
    if (this->state.filter.amount == 0 || (this->state.filter.color << 8) == 0)
    {
        this->state.filter.color = color;
        this->state.filter.amount = amount;
        return;
    }
    float alpha = this->state.filter.amount;
    uint32_t c1 = this->state.filter.color;
    float new_amount = 1 - (1 - alpha) * (1 - amount);
    uint8_t old_red = (c1 >> 16) & 255;
    uint8_t c_red = (color >> 16) & 255;
    uint8_t new_red = rr_fclamp(
        (old_red * alpha * (1 - amount) + c_red * amount) / (new_amount), 0,
        255);
    uint8_t old_green = (c1 >> 8) & 255;
    uint8_t c_green = (color >> 8) & 255;
    uint8_t new_green = rr_fclamp(
        (old_green * alpha * (1 - amount) + c_green * amount) / (new_amount), 0,
        255);
    uint8_t old_blue = (c1)&255;
    uint8_t c_blue = (color)&255;
    uint8_t new_blue = rr_fclamp(
        (old_blue * alpha * (1 - amount) + c_blue * amount) / (new_amount), 0,
        255);
    this->state.filter.color =
        (255 << 24) | (new_red << 16) | (new_green << 8) | new_blue;
    this->state.filter.amount = new_amount;
}

void rr_renderer_reset_color_filter(struct rr_renderer *this)
{
    this->state.filter.color = 0x00000000;
    this->state.filter.amount = 0;
}