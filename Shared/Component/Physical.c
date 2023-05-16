#include <Shared/Component/Physical.h>

#include <string.h>

#include <Shared/Encoder.h>

#ifdef RR_CLIENT
#include <Client/Renderer/Renderer.h>
#endif

enum
{
    state_flags_x =             0b000001,
    state_flags_y =             0b000010,
    state_flags_angle =         0b000100,
    state_flags_radius =        0b001000,
    state_flags_deletion_tick = 0b010000,
    state_flags_all =           0b011111
};

void rr_component_physical_init(struct rr_component_physical *this)
{
    memset(this, 0, sizeof *this);
}

void rr_component_physical_free(struct rr_component_physical *this)
{
}

#ifdef RR_SERVER
void rr_component_physical_write(struct rr_component_physical *this, struct rr_encoder *encoder, int is_creation)
{
    uint64_t state = this->protocol_state | (state_flags_all * is_creation);
    rr_encoder_write_varuint(encoder, state);
    RR_ENCODE_PUBLIC_FIELD(x, float);
    RR_ENCODE_PUBLIC_FIELD(y, float);
    RR_ENCODE_PUBLIC_FIELD(angle, float);
    RR_ENCODE_PUBLIC_FIELD(radius, float);
    RR_ENCODE_PUBLIC_FIELD(deletion_tick, uint8);
}

RR_DEFINE_PUBLIC_FIELD(physical, float, x)
RR_DEFINE_PUBLIC_FIELD(physical, float, y)
RR_DEFINE_PUBLIC_FIELD(physical, float, angle)
RR_DEFINE_PUBLIC_FIELD(physical, float, radius)
RR_DEFINE_PUBLIC_FIELD(physical, uint32_t, deletion_tick)
#endif

#ifdef RR_CLIENT
void rr_component_physical_read(struct rr_component_physical *this, struct rr_encoder *encoder)
{
    uint64_t state = rr_encoder_read_varuint(encoder);
    RR_DECODE_PUBLIC_FIELD(x, float);
    RR_DECODE_PUBLIC_FIELD(y, float);
    RR_DECODE_PUBLIC_FIELD(angle, float);
    RR_DECODE_PUBLIC_FIELD(radius, float);
    RR_DECODE_PUBLIC_FIELD(deletion_tick, uint8);
}

void rr_component_physical_render(struct rr_component_physical *this, struct rr_renderer *renderer)
{
    rr_renderer_translate(renderer, this->x, this->y);
    rr_renderer_begin_path(renderer);
    rr_renderer_arc(renderer, 0, 0, this->radius);
    rr_renderer_fill(renderer);
}
#endif