#include <Shared/Component/Physical.h>

#include <string.h>

#include <Shared/Encoder.h>

// if bots become a problem, just reorder these and they disappear
enum : uint64_t
{
    state_flags_x =             0b000001,
    state_flags_y =             0b000010,
    state_flags_angle =         0b000100,
    state_flags_radius =        0b001000,
    state_flags_deletion_tick = 0b010000,
    state_flags_all =           0b011111
};

void rr_component_physical_init(struct rr_component_physical *self)
{
    memset(self, 0, sizeof *self);
}

void rr_component_physical_free(struct rr_component_physical *self)
{
}

void rr_component_physical_write(struct rr_component_physical *self, struct rr_encoder *encoder, int is_creation)
{
    uint64_t state = self->protocol_state | (state_flags_all * is_creation);
    rr_encoder_write_varuint(encoder, state);
    if (state & state_flags_x)
        rr_encoder_write_float(encoder, self->x);
    if (state & state_flags_y)
        rr_encoder_write_float(encoder, self->y);
    if (state & state_flags_angle)
        rr_encoder_write_float(encoder, self->angle);
    if (state & state_flags_radius)
        rr_encoder_write_float(encoder, self->radius);
    if (state & state_flags_deletion_tick)
        rr_encoder_write_uint8(encoder, self->deletion_tick);
}

void rr_component_physical_read(struct rr_component_physical *self, struct rr_encoder *encoder)
{
    uint64_t state = rr_encoder_read_varuint(encoder);

    if (state & state_flags_x)
        self->x = rr_encoder_read_float(encoder);
    if (state & state_flags_y)
        self->y = rr_encoder_read_float(encoder);
    if (state & state_flags_angle)
        self->angle = rr_encoder_read_float(encoder);
    if (state & state_flags_radius)
        self->radius = rr_encoder_read_float(encoder);
    if (state & state_flags_deletion_tick)
        self->deletion_tick = rr_encoder_read_uint8(encoder);
}

void rr_component_physical_set_x(struct rr_component_physical *self, float x)
{
    self->protocol_state |= (self->x != x) * state_flags_x;
    self->x = x;
}

void rr_component_physical_set_y(struct rr_component_physical *self, float y)
{
    self->protocol_state |= (self->y != y) * state_flags_y;
    self->y = y;
}

void rr_component_physical_set_angle(struct rr_component_physical *self, float angle)
{
    self->protocol_state |= (self->angle != angle) * state_flags_angle;
    self->angle = angle;
}

void rr_component_physical_set_radius(struct rr_component_physical *self, float radius)
{
    self->protocol_state |= (self->radius != radius) * state_flags_radius;
    self->radius = radius;
}
