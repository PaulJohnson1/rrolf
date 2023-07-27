#include <Shared/Component/Arena.h>

#include <stdlib.h>
#include <string.h>

#include <Shared/Entity.h>
#include <Shared/SimulationCommon.h>
#include <Shared/StaticData.h>
#include <Shared/pb.h>

#define FOR_EACH_PUBLIC_FIELD                                                  \
    X(radius, float32)                                                         \
    X(wave_tick, varuint)                                                      \
    X(wave, varuint)

enum
{
    state_flags_wave = 0b000001,
    state_flags_wave_tick = 0b000010,
    state_flags_radius = 0b000100,
    state_flags_all = 0b000111
};

void rr_component_arena_init(struct rr_component_arena *this,
                             struct rr_simulation *simulation)
{
    memset(this, 0, sizeof *this);
    this->mob_counters =
        calloc(rr_rarity_id_max * rr_mob_id_max, sizeof(uint32_t));
}

void rr_component_arena_free(struct rr_component_arena *this,
                             struct rr_simulation *simulation)
{
    free(this->mob_counters);
}

#ifdef RR_SERVER
void rr_component_arena_write(struct rr_component_arena *this,
                              struct proto_bug *encoder, int is_creation, struct rr_component_player_info *client)
{
    uint64_t state = this->protocol_state | (state_flags_all * is_creation);
    proto_bug_write_varuint(encoder, state, "arena component state");

    // 1 arena component, shouldn't matter if the networking is like 1 KB for
    // this

    for (uint64_t i = 0; i < rr_mob_id_max * rr_rarity_id_max; ++i)
        proto_bug_write_varuint(
            encoder, this->mob_counters[i],
            "mob count");

#define X(NAME, TYPE) RR_ENCODE_PUBLIC_FIELD(NAME, TYPE);
    FOR_EACH_PUBLIC_FIELD
#undef X
}

RR_DEFINE_PUBLIC_FIELD(arena, float, radius)
RR_DEFINE_PUBLIC_FIELD(arena, uint16_t, wave_tick)
RR_DEFINE_PUBLIC_FIELD(arena, uint16_t, wave)
#endif

#ifdef RR_CLIENT
void rr_component_arena_read(struct rr_component_arena *this,
                             struct proto_bug *encoder)
{
    uint64_t state = proto_bug_read_varuint(encoder, "arena component state");

    for (uint64_t i = 0; i < rr_mob_id_max * rr_rarity_id_max; ++i)
            this->mob_counters[i] =
                proto_bug_read_varuint(encoder, "mob count");

#define X(NAME, TYPE) RR_DECODE_PUBLIC_FIELD(NAME, TYPE);
    FOR_EACH_PUBLIC_FIELD
#undef X
}
#endif