#pragma once

#include <stdint.h>

#include <Client/Simulation.h>

#include <Shared/Vector.h>

struct rr_renderer;

struct rr_particle_manager
{
    struct rr_simulation_animation particles[16384];
    uint32_t size;
};

struct rr_simulation_animation *rr_particle_alloc(struct rr_particle_manager *, uint8_t);
void rr_particle_delete(struct rr_particle_manager *, struct rr_simulation_animation *);
void rr_renderer_render_particle(struct rr_renderer *, struct rr_simulation_animation *);