#include <Shared/Vector.h>

void rr_vector_set(struct rr_vector *self, float x, float y)
{
    self->x = x;
    self->y = y;
}

void rr_vector_add(struct rr_vector *self, struct rr_vector *right)
{
    self->x += right->x;
    self->y += right->y;
}

void rr_vector_scale(struct rr_vector *self, float v)
{
    self->x *= v;
    self->y *= v;
}

int rr_vector_equals(struct rr_vector *self, struct rr_vector *other)
{
    return self->x == other->x && self->y == other->y;
}