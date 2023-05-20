#include <Shared/Component/Flower.h>

#include <string.h>

#include <Shared/Encoder.h>
#include <Shared/Entity.h>
#include <Shared/SimulationCommon.h>

#ifdef RR_CLIENT
#include <Client/Renderer/Renderer.h>
#endif

enum
{
    state_flags_face_flags =    0b000001,
    state_flags_eye_angle =     0b000010,
    state_flags_all =           0b000011
};

void rr_component_flower_init(struct rr_component_flower *this)
{
    memset(this, 0, sizeof *this);
}

void rr_component_flower_free(struct rr_component_flower *this)
{
}

#ifdef RR_SERVER
void rr_component_flower_write(struct rr_component_flower *this, struct rr_encoder *encoder, int is_creation)
{
    uint64_t state = this->protocol_state | (state_flags_all * is_creation);
    rr_encoder_write_varuint(encoder, state);
    RR_ENCODE_PUBLIC_FIELD(face_flags, uint8);
    RR_ENCODE_PUBLIC_FIELD(eye_angle, float);
}

RR_DEFINE_PUBLIC_FIELD(flower, uint8_t, face_flags)
RR_DEFINE_PUBLIC_FIELD(flower, float, eye_angle)
#endif

#ifdef RR_CLIENT
void rr_component_flower_read(struct rr_component_flower *this, struct rr_encoder *encoder)
{
    uint64_t state = rr_encoder_read_varuint(encoder);
    RR_DECODE_PUBLIC_FIELD(face_flags, uint8);
    RR_DECODE_PUBLIC_FIELD(eye_angle, float);
}
#endif

#ifdef RR_CLIENT
void rr_component_flower_render(EntityIdx entity, struct rr_simulation *simulation, struct rr_renderer *renderer)
{
    struct rr_component_physical *physical = rr_simulation_get_physical(simulation, entity);
    rr_renderer_translate(renderer, physical->x, physical->y);
    rr_renderer_begin_path(renderer);
    rr_renderer_arc(renderer, 0, 0, physical->radius + 1.5);
    rr_renderer_set_fill(renderer, 0xffcfbb50);
    rr_renderer_fill(renderer);
    rr_renderer_begin_path(renderer);
    rr_renderer_arc(renderer, 0, 0, physical->radius - 1.5);
    rr_renderer_set_fill(renderer, 0xffffe763);
    rr_renderer_fill(renderer);
    rr_renderer_scale(renderer, physical->radius / 25);
    struct rr_renderer_context_state state;
    rr_renderer_init_context_state(renderer, &state);
    rr_renderer_set_fill(renderer, 0xff222222);
    rr_renderer_scale2(renderer, 1, 2);
    rr_renderer_begin_path(renderer);
    rr_renderer_arc(renderer, -7, -2.5, 3.25);
    rr_renderer_fill(renderer);
    rr_renderer_begin_path(renderer);
    rr_renderer_arc(renderer, -7, -2.5, 3);
    rr_renderer_clip(renderer);
    rr_renderer_scale2(renderer, 1, 0.5);
    rr_renderer_set_fill(renderer, 0xffffffff);
    rr_renderer_begin_path(renderer);
    rr_renderer_arc(renderer, -7, -5, 3);
    rr_renderer_fill(renderer);
    rr_renderer_free_context_state(renderer, &state);

    rr_renderer_init_context_state(renderer, &state);
    rr_renderer_set_fill(renderer, 0xff222222);
    rr_renderer_scale2(renderer, 1, 2);
    rr_renderer_begin_path(renderer);
    rr_renderer_arc(renderer, 7, -2.5, 3.25);
    rr_renderer_fill(renderer);
    rr_renderer_begin_path(renderer);
    rr_renderer_arc(renderer, 7, -2.5, 3);
    rr_renderer_clip(renderer);
    rr_renderer_scale2(renderer, 1, 0.5);
    rr_renderer_set_fill(renderer, 0xffffffff);
    rr_renderer_begin_path(renderer);
    rr_renderer_arc(renderer, 7, -5, 3);
    rr_renderer_fill(renderer);
    rr_renderer_free_context_state(renderer, &state);
    rr_renderer_set_stroke(renderer, 0xff222222);
    rr_renderer_set_line_width(renderer, 1.5);
    rr_renderer_set_line_cap(renderer, 1);
    rr_renderer_begin_path(renderer);
    rr_renderer_move_to(renderer, -6, 10);
    rr_renderer_quadratic_curve_to(renderer, 0, 15, 6, 10);
    rr_renderer_stroke(renderer);
}
#endif