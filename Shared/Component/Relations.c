#include <Shared/Component/Relations.h>

#include <string.h>

#include <Shared/Entity.h>
#include <Shared/SimulationCommon.h>
#include <Shared/pb.h>

#define FOR_EACH_PUBLIC_FIELD                                                  \
    X(owner, varuint)                                                          \
    X(team, varuint)

enum
{
    state_flags_team = 0b000001,
    state_flags_owner = 0b000010,
    state_flags_all = 0b000011
};

void rr_component_relations_init(struct rr_component_relations *this,
                                 struct rr_simulation *simulation)
{
    memset(this, 0, sizeof *this);
}

void rr_component_relations_free(struct rr_component_relations *this,
                                 struct rr_simulation *simulation)
{
}

#ifdef RR_SERVER
void rr_component_relations_write(struct rr_component_relations *this,
                                  struct proto_bug *encoder, int is_creation, struct rr_component_player_info *client)
{
    uint64_t state = this->protocol_state | (state_flags_all * is_creation);
    proto_bug_write_varuint(encoder, state, "relations component state");
#define X(NAME, TYPE) RR_ENCODE_PUBLIC_FIELD(NAME, TYPE);
    FOR_EACH_PUBLIC_FIELD
#undef X
}

RR_DEFINE_PUBLIC_FIELD(relations, EntityIdx, owner)
RR_DEFINE_PUBLIC_FIELD(relations, uint32_t, team)
#endif

#ifdef RR_CLIENT
void rr_component_relations_read(struct rr_component_relations *this,
                                 struct proto_bug *encoder)
{
    uint64_t state =
        proto_bug_read_varuint(encoder, "relations component state");
#define X(NAME, TYPE) RR_DECODE_PUBLIC_FIELD(NAME, TYPE);
    FOR_EACH_PUBLIC_FIELD
#undef X
}
#endif