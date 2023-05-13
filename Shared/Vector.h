#pragma once

struct rr_vector
{
    float x;
    float y;
};

void rr_vector_set(struct rr_vector *self, float x, float y);
void rr_vector_add(struct rr_vector *self, struct rr_vector *right);
int rr_vector_equals(struct rr_vector *self, struct rr_vector *other);
