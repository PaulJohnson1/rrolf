#include <Shared/Component/Relations.h>

#include <string.h>

#include <Shared/Encoder.h>
#include <Shared/Entity.h>
#include <Shared/SimulationCommon.h>

enum
{
    state_flags_owner = 0b000001,
    state_flags_team =  0b000010,
    state_flags_all =   0b000011
};

void rr_component_relations_init(struct rr_component_relations *this)
{
    memset(this, 0, sizeof *this);
}

void rr_component_relations_free(struct rr_component_relations *this)
{
}

#ifdef RR_SERVER
void rr_component_relations_write(struct rr_component_relations *this, struct rr_encoder *encoder, int is_creation)
{
    uint64_t state = this->protocol_state | (state_flags_all * is_creation);
    rr_encoder_write_varuint(encoder, state);
    RR_ENCODE_PUBLIC_FIELD(owner, uint8);
    RR_ENCODE_PUBLIC_FIELD(team, varuint);
}

RR_DEFINE_PUBLIC_FIELD(relations, EntityIdx, owner)
RR_DEFINE_PUBLIC_FIELD(relations, uint32_t, team)
#endif

#ifdef RR_CLIENT
void rr_component_relations_read(struct rr_component_relations *this, struct rr_encoder *encoder)
{
    uint64_t state = rr_encoder_read_varuint(encoder);
    RR_DECODE_PUBLIC_FIELD(owner, uint8);
    RR_DECODE_PUBLIC_FIELD(team, varuint);
}
#endif