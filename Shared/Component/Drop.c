#include <Shared/Component/Drop.h>

#include <assert.h>
#include <stdio.h>
#include <string.h>

#include <Shared/Entity.h>
#include <Shared/SimulationCommon.h>
#include <Shared/pb.h>

#define FOR_EACH_PUBLIC_FIELD                                                  \
    X(rarity, uint8)                                                           \
    X(id, uint8)

enum
{
    state_flags_id = 0b000001,
    state_flags_rarity = 0b000010,
    state_flags_hidden = 0b000100,
    state_flags_all = 0b000111
};

void rr_component_drop_init(struct rr_component_drop *this,
                            struct rr_simulation *simulation)
{
    memset(this, 0, sizeof *this);
}

void rr_component_drop_free(struct rr_component_drop *this,
                            struct rr_simulation *simulation)
{
}

#ifdef RR_SERVER
void rr_component_drop_write(struct rr_component_drop *this,
                             struct proto_bug *encoder, int is_creation, struct rr_component_player_info *client)
{
    uint64_t state = this->protocol_state | (state_flags_all * is_creation);
    if (rr_bitset_get(&this->picked_up_this_tick[0], client->client_id))
        state |= state_flags_hidden;
    proto_bug_write_varuint(encoder, state, "drop component state");
#define X(NAME, TYPE) RR_ENCODE_PUBLIC_FIELD(NAME, TYPE);
    FOR_EACH_PUBLIC_FIELD
    if (state & state_flags_hidden)
        proto_bug_write_uint8(
            encoder, rr_bitset_get(&this->picked_up_by[0], client->client_id) + (is_creation != 0) * rr_bitset_get(&this->picked_up_by[0], client->client_id),
            "drop hidden");
#undef X
}

RR_DEFINE_PUBLIC_FIELD(drop, uint8_t, id)
RR_DEFINE_PUBLIC_FIELD(drop, uint8_t, rarity)
#endif

#ifdef RR_CLIENT
void rr_component_drop_read(struct rr_component_drop *this,
                            struct proto_bug *encoder)
{
    uint64_t state = proto_bug_read_varuint(encoder, "drop component state");
#define X(NAME, TYPE) RR_DECODE_PUBLIC_FIELD(NAME, TYPE);
    FOR_EACH_PUBLIC_FIELD
#undef X
    if (state & state_flags_hidden)
        this->hidden = proto_bug_read_uint8(encoder, "drop hidden");
}
#endif