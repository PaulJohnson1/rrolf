#include <Shared/Component/Flower.h>

#include <string.h>

#include <Shared/Encoder.h>
#include <Shared/Entity.h>
#include <Shared/SimulationCommon.h>

enum
{
    state_flags_face_flags = 0b000001,
    state_flags_eye_angle =  0b000010,
    state_flags_all =        0b000011
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