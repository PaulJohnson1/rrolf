#include <Client/Particle.h>

#include <string.h>
#include <stdio.h>

#include <Client/Renderer/Renderer.h>

#include <Shared/StaticData.h>

struct rr_simulation_animation *rr_particle_alloc(struct rr_particle_manager *this, uint8_t type)
{
    struct rr_simulation_animation *ret = &this->particles[this->size];
    memset(ret, 0, sizeof *ret);
    ret->type = type;
    ++this->size;
    return ret;
}

void rr_particle_delete(struct rr_particle_manager *this, struct rr_simulation_animation *particle)
{
    if (&this->particles[this->size - 1] != particle)
        memcpy(particle, &this->particles[this->size - 1], sizeof(struct rr_simulation_animation));
    --this->size;
}

void rr_renderer_render_particle(struct rr_renderer *renderer, struct rr_simulation_animation *this)
{
    rr_renderer_set_global_alpha(renderer, this->opacity);
    switch(this->type)
    {
        case rr_animation_type_default:
            rr_renderer_set_fill(renderer, this->color);
            rr_renderer_begin_path(renderer);
            rr_renderer_arc(renderer, this->x, this->y, this->size);
            rr_renderer_fill(renderer);
            break;
        case rr_animation_type_lightningbolt:
            rr_renderer_set_stroke(renderer, 0xffccccfc);
            rr_renderer_set_line_width(renderer, 4);
            rr_renderer_begin_path(renderer);
            rr_renderer_move_to(renderer, this->points[0].x, this->points[0].y);
            for (uint32_t i = 1; i < this->length; ++i)
                rr_renderer_line_to(renderer, this->points[i].x, this->points[i].y);
            rr_renderer_stroke(renderer);
            break;
        case rr_animation_type_damagenumber:
            rr_renderer_set_fill(renderer, 0xffff4444);
            rr_renderer_set_stroke(renderer, 0xff222222);
            rr_renderer_set_text_size(renderer, 36);
            rr_renderer_set_line_width(renderer, 36 * 0.12);
            rr_renderer_set_text_align(renderer, 1);
            rr_renderer_set_text_baseline(renderer, 1);
            rr_renderer_begin_path(renderer);
            char a[16];
            sprintf(a, "%d", this->damage);
            rr_renderer_stroke_text(renderer, a, this->x, this->y);
            rr_renderer_fill_text(renderer, a, this->x, this->y);
            break;
        default:
            break;
    }
    rr_renderer_set_global_alpha(renderer, 1);
}