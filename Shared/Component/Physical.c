#include <Shared/Component/Physical.h>

#include <Shared/BinaryEncoder.h>

// if bots become a problem, just reorder these and they disappear
enum : uint64_t
{
    state_flags_x               = 0b000001,
    state_flags_y               = 0b000010,
    state_flags_angle           = 0b000100,
    state_flags_radius          = 0b001000,
    state_flags_deletion_tick   = 0b010000,
    state_flags_all             = 0b011111
};

void rr_component_physical_write(struct rr_component_physical *s, struct rr_binary_encoder *writer, int is_creation)
{
    uint64_t state = s->protocol_state | (state_flags_all * is_creation);
    rr_binary_encoder_write_varuint(writer, state);
    if (state & state_flags_x)
        rr_binary_encoder_write_float(writer, s->x);
    if (state & state_flags_y)
        rr_binary_encoder_write_float(writer, s->y);
    if (state & state_flags_angle)
        rr_binary_encoder_write_float(writer, s->angle);
    if (state & state_flags_radius)
        rr_binary_encoder_write_float(writer, s->radius);
    if (state & state_flags_deletion_tick)
        rr_binary_encoder_write_uint8(writer, s->deletion_tick);
}

void rr_component_physical_set_x(struct rr_component_physical *comp, float x)
{
    comp->protocol_state |= (comp->x != x) * state_flags_x;
    comp->x = x;
}

void rr_component_physical_set_y(struct rr_component_physical *comp, float y)
{
    comp->protocol_state |= (comp->y != y) * state_flags_y; 
    comp->y = y;
}

void rr_component_physical_set_angle(struct rr_component_physical *comp, float angle)
{
    comp->protocol_state |= (comp->angle != angle) * state_flags_angle; 
    comp->angle = angle;
}

void rr_component_physical_set_radius(struct rr_component_physical *comp, float radius)
{
    comp->protocol_state |= (comp->radius != radius) * state_flags_radius; 
    comp->radius = radius;
}
