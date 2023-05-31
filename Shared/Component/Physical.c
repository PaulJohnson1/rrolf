#include <Shared/Component/Physical.h>

#include <string.h>

#include <Shared/pb.h>

enum
{
    state_flags_x =             0b000001,
    state_flags_y =             0b000010,
    state_flags_angle =         0b000100,
    state_flags_radius =        0b001000,
    state_flags_deletion_tick = 0b010000,
    state_flags_all =           0b011111
};

void rr_component_physical_init(struct rr_component_physical *this)
{
    memset(this, 0, sizeof *this);
    RR_SERVER_ONLY(this->mass = 1;)
}

void rr_component_physical_free(struct rr_component_physical *this, struct rr_simulation *simulation)
{
}

#ifdef RR_SERVER
void rr_component_physical_write(struct rr_component_physical *this, struct proto_bug *encoder, int is_creation)
{
    uint64_t state = this->protocol_state | (state_flags_all * is_creation);
    proto_bug_write_varuint(encoder, state, "physical component state");
    RR_ENCODE_PUBLIC_FIELD(x, float32);
    RR_ENCODE_PUBLIC_FIELD(y, float32);
    RR_ENCODE_PUBLIC_FIELD(angle, float32);
    RR_ENCODE_PUBLIC_FIELD(radius, float32);
    RR_ENCODE_PUBLIC_FIELD(deletion_tick, uint8);
}

RR_DEFINE_PUBLIC_FIELD(physical, float, x)
RR_DEFINE_PUBLIC_FIELD(physical, float, y)
RR_DEFINE_PUBLIC_FIELD(physical, float, angle)
RR_DEFINE_PUBLIC_FIELD(physical, float, radius)
RR_DEFINE_PUBLIC_FIELD(physical, uint32_t, deletion_tick)
#endif

#ifdef RR_CLIENT
void rr_component_physical_read(struct rr_component_physical *this, struct proto_bug *encoder)
{
    uint64_t state = proto_bug_read_varuint(encoder, "physical component state");
    if (state & state_flags_x)
    {
        float new_x = proto_bug_read_float32(encoder, "field " "x");
        if (this->x == 0)
            this->x = new_x;
        this->velocity.x = this->x - new_x;
        this->x = new_x;
    }
    if (state & state_flags_y)
    {
        float new_y = proto_bug_read_float32(encoder, "field " "y");
        if (this->y == 0)
            this->y = new_y;
        this->velocity.y = this->y - new_y;
        this->y = new_y;
    }
    // RR_DECODE_PUBLIC_FIELD(x, float32);
    // RR_DECODE_PUBLIC_FIELD(y, float32);
    RR_DECODE_PUBLIC_FIELD(angle, float32);
    RR_DECODE_PUBLIC_FIELD(radius, float32);
    RR_DECODE_PUBLIC_FIELD(deletion_tick, uint8);
}
#endif
