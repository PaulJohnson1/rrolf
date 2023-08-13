#include <Shared/Component/Physical.h>

#include <string.h>

#include <Shared/pb.h>

enum
{
    state_flags_angle = 0b00001,
    state_flags_radius = 0b00010,
    state_flags_y = 0b00100,
    state_flags_x = 0b01000,
    state_flags_all = 0b11111
};

#define FOR_EACH_PUBLIC_FIELD                                                  \
    X(angle, float32)                                                          \
    X(radius, float32)                                                         \
    X(x, float32)                                                              \
    X(y, float32)

void rr_component_physical_init(struct rr_component_physical *this,
                                struct rr_simulation *simulation)
{
    memset(this, 0, sizeof *this);
    RR_SERVER_ONLY(this->mass = 1;)
    RR_SERVER_ONLY(this->acceleration_scale = 1;)
    RR_SERVER_ONLY(this->knockback_scale = 1;)
}

void rr_component_physical_free(struct rr_component_physical *this,
                                struct rr_simulation *simulation)
{
}

#ifdef RR_SERVER
void rr_component_physical_write(struct rr_component_physical *this,
                                 struct proto_bug *encoder, int is_creation,
                                 struct rr_component_player_info *client)
{
    uint64_t state = this->protocol_state | (state_flags_all * is_creation);
    proto_bug_write_varuint(encoder, state, "physical component state");
#define X(NAME, TYPE) RR_ENCODE_PUBLIC_FIELD(NAME, TYPE);
    FOR_EACH_PUBLIC_FIELD
#undef X
}

RR_DEFINE_PUBLIC_FIELD(physical, float, x)
RR_DEFINE_PUBLIC_FIELD(physical, float, y)
RR_DEFINE_PUBLIC_FIELD(physical, float, angle)
RR_DEFINE_PUBLIC_FIELD(physical, float, radius)
#endif

#ifdef RR_CLIENT
void rr_component_physical_read(struct rr_component_physical *this,
                                struct proto_bug *encoder)
{
    uint64_t state =
        proto_bug_read_varuint(encoder, "physical component state");
#define X(NAME, TYPE) RR_DECODE_PUBLIC_FIELD(NAME, TYPE);
    FOR_EACH_PUBLIC_FIELD
#undef X
}
#endif