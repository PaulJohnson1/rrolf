#include <Shared/Vector.h>

void rr_vector_set(struct rr_vector *this, float x, float y)
{
    this->x = x;
    this->y = y;
}

void rr_vector_add(struct rr_vector *this, struct rr_vector *right)
{
    this->x += right->x;
    this->y += right->y;
}

void rr_vector_scale(struct rr_vector *this, float v)
{
    this->x *= v;
    this->y *= v;
}

int rr_vector_equals(struct rr_vector *this, struct rr_vector *other)
{
    return this->x == other->x && this->y == other->y;
}
