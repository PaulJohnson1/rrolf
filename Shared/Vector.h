#pragma once

struct rr_vector
{
    float x;
    float y;
};

void rr_vector_set(struct rr_vector *, float, float);
void rr_vector_add(struct rr_vector *, struct rr_vector *);
void rr_vector_scale(struct rr_vector *, float);
int rr_vector_equals(struct rr_vector *, struct rr_vector *);
