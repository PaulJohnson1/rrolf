#include <Shared/Component/Arena.h>

#include <string.h>

#include <Shared/Encoder.h>
#include <Shared/Entity.h>
#include <Shared/SimulationCommon.h>

enum
{
    state_flags_radius    =     0b000001,
    state_flags_all =           0b000001
};

void rr_component_arena_init(struct rr_component_arena *this)
{
    memset(this, 0, sizeof *this);
}

void rr_component_arena_free(struct rr_component_arena *this)
{
}

#ifdef RR_SERVER
void rr_component_arena_write(struct rr_component_arena *this, struct rr_encoder *encoder, int is_creation)
{
    uint64_t state = this->protocol_state | (state_flags_all * is_creation);
    rr_encoder_write_varuint(encoder, state);
    RR_ENCODE_PUBLIC_FIELD(radius, float);
}

RR_DEFINE_PUBLIC_FIELD(arena, float, radius)
#endif

#ifdef RR_CLIENT
void rr_component_arena_read(struct rr_component_arena *this, struct rr_encoder *encoder)
{
    uint64_t state = rr_encoder_read_varuint(encoder);
    RR_DECODE_PUBLIC_FIELD(radius, float);
}
#endif