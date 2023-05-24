#include <Shared/Component/Health.h>

#include <string.h>

#include <Shared/pb.h>
#include <Shared/Entity.h>
#include <Shared/SimulationCommon.h>

enum
{
    state_flags_health =     0b000001,
    state_flags_max_health = 0b000010,
    state_flags_all =        0b000011
};

void rr_component_health_init(struct rr_component_health *this)
{
    memset(this, 0, sizeof *this);
}

void rr_component_health_free(struct rr_component_health *this, struct rr_simulation *simulation)
{
}

#ifdef RR_SERVER
void rr_component_health_write(struct rr_component_health *this, struct proto_bug *encoder, int is_creation)
{
    uint64_t state = this->protocol_state | (state_flags_all * is_creation);
    proto_bug_write_varuint(encoder, state, "health component state");
    RR_ENCODE_PUBLIC_FIELD(health, float32);
    RR_ENCODE_PUBLIC_FIELD(max_health, float32);
}

void rr_component_health_set_health(struct rr_component_health *this, float v)
{
    if (v > this->max_health)
        v = this->max_health;
    else if (v < 0)
        v = 0;
    this->protocol_state |= (v != this->health) * state_flags_health;
    this->health = v;
}
void rr_component_health_set_max_health(struct rr_component_health *this, float v)
{
    this->protocol_state |= (v != this->max_health) * state_flags_max_health;
    this->max_health = v;
}
#endif

#ifdef RR_CLIENT
void rr_component_health_read(struct rr_component_health *this, struct proto_bug *encoder)
{
    uint64_t state = proto_bug_read_varuint(encoder, "health component state");
    RR_DECODE_PUBLIC_FIELD(health, float32);
    RR_DECODE_PUBLIC_FIELD(max_health, float32);
}
#endif