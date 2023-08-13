#pragma once

#include <stdint.h>

#include <Shared/Vector.h>

struct rr_particle
{
    struct rr_vector position[32];
    struct rr_vector velocity;
    struct rr_vector acceleration;
    float size;
    float opacity;
    uint32_t color;
    uint16_t pos;
    uint8_t type;
    uint8_t length;
};

struct rr_particle_manager
{
    struct rr_particle particles[1024];
    uint32_t size;
};

struct rr_renderer;

struct rr_particle *rr_particle_alloc(struct rr_particle_manager *, uint8_t);
void rr_particle_delete(struct rr_particle_manager *, struct rr_particle *);
void rr_renderer_render_particle(struct rr_renderer *, struct rr_particle *);