#include <Server/Simulation.h>

#include <Server/System/Velocity.h>

#include <assert.h>
#include <string.h>
#include <stdio.h>

#include <Shared/Utilities.h>

void rr_simulation_init(struct rr_simulation *self)
{
    *self = (struct rr_simulation){0};
}

// will change later probably
EntityIdx rr_simulation_alloc_entity(struct rr_simulation *self)
{
    for (EntityIdx i = 1; i < MAX_ENTITY_COUNT; i++)
    {
        if (!rr_simulation_has_entity(self, i))
        {
            self->entity_tracker[i >> 3] |= 1 << (i & 7);
            return i;
        }
    }

    RR_UNREACHABLE();
}

void rr_simulation_free_entity(struct rr_simulation *self, EntityIdx entity)
{
#define XX(COMPONENT, ID) \
    rr_component_##COMPONENT##_free(rr_simulation_get_##COMPONENT(self, entity));
    FOR_EACH_COMPONENT;
#undef XX
    self->entity_tracker[entity >> 3] &= ~(1 << (entity & 7));
}

int rr_simulation_has_entity(struct rr_simulation *self, EntityIdx entity)
{
    if (self->entity_tracker[entity >> 3] & (1 << (entity & 7)))
        return 1;
    else
        return 0;
}

// TODO: use a less goofy name
struct rr_simulation_encoder_temp
{
    struct rr_simulation *simulation;
    struct rr_encoder *encoder;
};

void rr_protocol_foreach_function(EntityIdx id, void *_simulation_encoder)
{
    struct rr_simulation_encoder_temp *simulation_encoder = _simulation_encoder;
    struct rr_simulation *simulation = simulation_encoder->simulation;
    struct rr_encoder *encoder = simulation_encoder->encoder;
    rr_encoder_write_varuint(simulation_encoder->encoder, id);
    int is_creation = 1; // TODO: fix
    uint32_t component_flags = 0;
    if (is_creation)
    {
#define XX(COMPONENT, ID) \
    component_flags |= rr_simulation_has_##COMPONENT(simulation, id) << ID;
        FOR_EACH_COMPONENT;
#undef XX
    }
    else
    {
#define XX(COMPONENT, ID)                                                                   \
    component_flags |= (rr_simulation_has_##COMPONENT(simulation, id) &&                    \
                        rr_simulation_get_##COMPONENT(simulation, id)->protocol_state != 0) \
                       << ID;
        FOR_EACH_COMPONENT;
#undef XX
    }

    printf("%d component flags\n", component_flags);
    rr_encoder_write_varuint(encoder, component_flags);
#define XX(COMPONENT, ID)            \
    if (component_flags & (1 << ID)) \
        rr_component_##COMPONENT##_write(rr_simulation_get_##COMPONENT(simulation, id), encoder, is_creation);
    FOR_EACH_COMPONENT;
#undef XX
}

void rr_simulation_write_binary(struct rr_simulation *self, struct rr_encoder *encoder)
{
    rr_encoder_write_uint8(encoder, 0); // null terminate deletion array
    // only one capture allowed, must have two fields though
    struct rr_simulation_encoder_temp a = (struct rr_simulation_encoder_temp){
        .simulation = self,
        .encoder = encoder};
    rr_simulation_for_each_entity(self, &a, rr_protocol_foreach_function);
    rr_encoder_write_uint8(encoder, 0); // null terminate entity update ids
}

// will change later definitely
void rr_simulation_for_each_entity(struct rr_simulation *self, void *d, void (*cb)(EntityIdx, void *))
{
    for (EntityIdx i = 1; i < MAX_ENTITY_COUNT; i++) // i beg you turn this into a macro xd
    {
        if (rr_simulation_has_entity(self, i))
            cb(i, d);
    }
}

void rr_simulation_tick(struct rr_simulation *self)
{
    rr_system_velocity_tick(self);
}

#define XX(COMPONENT, ID)                                                                                        \
    int rr_simulation_has_##COMPONENT(struct rr_simulation *self, EntityIdx entity)                              \
    {                                                                                                            \
        assert(rr_simulation_has_entity(self, entity));                                                          \
        if (self->COMPONENT##_tracker[entity >> 3] & (1 << (entity & 7)))                                        \
            return 1;                                                                                            \
        else                                                                                                     \
            return 0;                                                                                            \
    }                                                                                                            \
    struct rr_component_##COMPONENT *rr_simulation_add_##COMPONENT(struct rr_simulation *self, EntityIdx entity) \
    {                                                                                                            \
        assert(rr_simulation_has_entity(self, entity));                                                          \
        self->COMPONENT##_tracker[entity >> 3] |= 1 << (entity & 7);                                             \
        rr_component_##COMPONENT##_init(self->COMPONENT##_components + entity);                                  \
        return rr_simulation_get_##COMPONENT(self, entity);                                                      \
    }                                                                                                            \
    struct rr_component_##COMPONENT *rr_simulation_get_##COMPONENT(struct rr_simulation *self, EntityIdx entity) \
    {                                                                                                            \
        assert(rr_simulation_has_entity(self, entity));                                                          \
        assert(rr_simulation_has_##COMPONENT(self, entity));                                                     \
        return &self->COMPONENT##_components[entity];                                                            \
    }
FOR_EACH_COMPONENT;
#undef XX
