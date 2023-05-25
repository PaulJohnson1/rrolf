#include <Shared/Component/Flower.h>

#include <string.h>
#include <stdio.h>

#include <Shared/pb.h>
#include <Shared/Entity.h>
#include <Shared/SimulationCommon.h>

enum
{
    state_flags_face_flags = 0b000001,
    state_flags_eye_angle = 0b000010,
    state_flags_all = 0b000011
};

void rr_component_flower_init(struct rr_component_flower *this)
{
    memset(this, 0, sizeof *this);
}

void rr_component_flower_free(struct rr_component_flower *this, struct rr_simulation *simulation)
{
#ifdef RR_SERVER
    printf("flower deletion: %d, %d\n", rr_simulation_get_relations(simulation, this->parent_id)->owner, this->parent_id);
    rr_component_player_info_set_flower_id(
        rr_simulation_get_player_info(
            simulation,
            rr_simulation_get_relations(simulation, this->parent_id)->owner),
        RR_NULL_ENTITY);
#endif
}

#ifdef RR_SERVER
void rr_component_flower_write(struct rr_component_flower *this, struct proto_bug *encoder, int is_creation)
{
    uint64_t state = this->protocol_state | (state_flags_all * is_creation);
    proto_bug_write_varuint(encoder, state, "flower component state");
    RR_ENCODE_PUBLIC_FIELD(face_flags, uint8);
    RR_ENCODE_PUBLIC_FIELD(eye_angle, float32);
}

RR_DEFINE_PUBLIC_FIELD(flower, uint8_t, face_flags)
RR_DEFINE_PUBLIC_FIELD(flower, float, eye_angle)
#endif

#ifdef RR_CLIENT
void rr_component_flower_read(struct rr_component_flower *this, struct proto_bug *encoder)
{
    uint64_t state = proto_bug_read_varuint(encoder, "flower component state");
    RR_DECODE_PUBLIC_FIELD(face_flags, uint8);
    RR_DECODE_PUBLIC_FIELD(eye_angle, float32);
}
#endif