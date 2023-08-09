#include <Client/Particle.h>

#include <string.h>

#include <Client/Renderer/Renderer.h>


struct rr_particle *rr_particle_alloc(struct rr_particle_manager *this, uint8_t type)
{
    struct rr_particle *ret = &this->particles[this->size];
    memset(ret, 0, sizeof *ret);
    ret->type = type;
    ret->pos = this->size++;
    return ret;
}

void rr_particle_delete(struct rr_particle_manager *this, struct rr_particle *particle)
{
    if (this->size != particle->pos + 1)
    {
        uint16_t pos = particle->pos;
        memcpy(particle, &this->particles[this->size - 1], sizeof(struct rr_particle));
        particle->pos = pos;
    }
    --this->size;
}

void rr_renderer_render_particle(struct rr_renderer *renderer, struct rr_particle *this)
{
    rr_renderer_set_global_alpha(renderer, this->opacity);
    rr_renderer_set_fill(renderer, this->color);
    rr_renderer_begin_path(renderer);
    rr_renderer_arc(renderer, this->position.x, this->position.y, this->size);
    rr_renderer_fill(renderer);
    rr_renderer_set_global_alpha(renderer, 1);
}