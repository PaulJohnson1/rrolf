#include <Shared/Vector.h>

#include <math.h>

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

void rr_vector_normalize(struct rr_vector *this)
{
    rr_vector_scale(this, 1 / sqrtf(this->x*this->x+this->y*this->y));
}

void rr_vector_set_magnitude(struct rr_vector *this, float mag)
{
    rr_vector_scale(this, mag / sqrtf(this->x*this->x+this->y*this->y));
}

float rr_vector_get_magnitude(struct rr_vector *this)
{
    return sqrtf(this->x*this->x+this->y*this->y);
}

float rr_vector_theta(struct rr_vector *this)
{
    return atan2f(this->y, this->x);
}