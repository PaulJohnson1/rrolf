#include <Shared/Component/Mob.h>

#include <string.h>

#include <Shared/pb.h>
#include <Shared/Entity.h>
#include <Shared/SimulationCommon.h>

enum
{
    state_flags_id = 0b000001,
    state_flags_rarity = 0b000010,
    state_flags_all = 0b000011
};

void rr_component_mob_init(struct rr_component_mob *this)
{
    memset(this, 0, sizeof *this);
}

void rr_component_mob_free(struct rr_component_mob *this, struct rr_simulation *simulation)
{
}

#ifdef RR_SERVER
void rr_component_mob_write(struct rr_component_mob *this, struct proto_bug *encoder, int is_creation)
{
    uint64_t state = this->protocol_state | (state_flags_all * is_creation);
    proto_bug_write_varuint(encoder, state, "mob component state");
    RR_ENCODE_PUBLIC_FIELD(id, uint8);
    RR_ENCODE_PUBLIC_FIELD(rarity, uint8);
}

RR_DEFINE_PUBLIC_FIELD(mob, uint8_t, id)
RR_DEFINE_PUBLIC_FIELD(mob, uint8_t, rarity)
#endif

#ifdef RR_CLIENT
void rr_component_mob_read(struct rr_component_mob *this, struct proto_bug *encoder)
{
    uint64_t state = proto_bug_read_varuint(encoder, "mob component state");
    RR_DECODE_PUBLIC_FIELD(id, uint8);
    RR_DECODE_PUBLIC_FIELD(rarity, uint8);
}
#endif