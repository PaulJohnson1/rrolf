#include <Client/Particle.h>

#include <string.h>
#include <stdio.h>

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
    switch(this->type)
    {
        case 0:
            rr_renderer_set_fill(renderer, this->color);
            rr_renderer_begin_path(renderer);
            rr_renderer_arc(renderer, this->position[0].x, this->position[0].y, this->size);
            rr_renderer_fill(renderer);
            break;
        case 1:
            rr_renderer_set_stroke(renderer, 0xffccccfc);
            rr_renderer_set_line_width(renderer, 4);
            rr_renderer_begin_path(renderer);
            rr_renderer_move_to(renderer, this->position[0].x, this->position[0].y);
            for (uint32_t i = 1; i < this->length; ++i)
                rr_renderer_line_to(renderer, this->position[i].x, this->position[i].y);
            rr_renderer_stroke(renderer);
            break;
        default:
            break;
    }
    rr_renderer_set_global_alpha(renderer, 1);
}