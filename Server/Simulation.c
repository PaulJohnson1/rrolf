#include <Server/Simulation.h>

#include <Server/System/Velocity.h>

#include <assert.h>
#include <string.h>
#include <stdio.h>

#include <Shared/Bitset.h>
#include <Shared/Utilities.h>

void rr_simulation_init(struct rr_simulation *self)
{
    memset(self, 0, sizeof *self);
}

// will change later probably
EntityIdx rr_simulation_alloc_entity(struct rr_simulation *self)
{
    for (EntityIdx i = 1; i < MAX_ENTITY_COUNT; i++)
    {
        if (!rr_simulation_has_entity(self, i))
        {
            rr_bitset_set(self->entity_tracker, i);
            printf("created with id %d\n", i);
            return i;
        }
    }

    RR_UNREACHABLE("ran out of entity ids");
}

void rr_simulation_free_entity(struct rr_simulation *self, EntityIdx entity)
{
    printf("deleted entity with id %d\n", entity);
#define XX(COMPONENT, ID)                            \
    if (rr_simulation_has_##COMPONENT(self, entity)) \
        rr_component_##COMPONENT##_free(rr_simulation_get_##COMPONENT(self, entity));
    FOR_EACH_COMPONENT;
#undef XX

    // unset them
#define XX(COMPONENT, ID) \
    rr_bitset_unset(self->COMPONENT##_tracker, entity);
    FOR_EACH_COMPONENT;
#undef XX

    // unset entity
    // rr_bitset_unset(self->entity_tracker, entity);
    self->entity_tracker[entity] &= ~(1 << (entity & 7));
    // self->entity_tracker[entity] = 0;
}

int rr_simulation_has_entity(struct rr_simulation *self, EntityIdx entity)
{
    // return rr_bitset_get(self->entity_tracker, entity);
    return self->entity_tracker[entity >> 3] & (1 << (entity & 7));
    // return self->entity_tracker[entity];
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

    rr_encoder_write_varuint(encoder, component_flags);
#define XX(COMPONENT, ID)            \
    if (component_flags & (1 << ID)) \
        rr_component_##COMPONENT##_write(rr_simulation_get_##COMPONENT(simulation, id), encoder, is_creation);
    FOR_EACH_COMPONENT;
#undef XX
}

struct rr_simulation_find_entities_in_view_foreach_function_captures
{
    int32_t view_width;
    int32_t view_height;
    int32_t view_x;
    int32_t view_y;
    uint8_t *entities_in_view;
    struct rr_simulation *simulation;
};

void rr_simulation_find_entities_in_view_foreach_function(EntityIdx entity, void *data)
{
    struct rr_simulation_find_entities_in_view_foreach_function_captures *captures = data;
    struct rr_simulation *simulation = captures->simulation;

    if (!rr_simulation_has_physical(simulation, entity))
        return;
    struct rr_component_physical *physical = rr_simulation_get_physical(simulation, entity);

    if (physical->x + physical->radius < captures->view_x - captures->view_width ||
        physical->x - physical->radius > captures->view_x + captures->view_width ||
        physical->y + physical->radius < captures->view_y - captures->view_height ||
        physical->y - physical->radius > captures->view_y + captures->view_height)
        return;
    
    captures->entities_in_view[entity >> 3] |= 1 << (entity & 7);
}

void rr_simulation_find_entities_in_view(struct rr_simulation *self, struct rr_component_player_info *player_info, uint8_t *entities_in_view)
{
    struct rr_simulation_find_entities_in_view_foreach_function_captures captures;
    memset(&captures, 0, sizeof captures);
    captures.view_width = (int32_t)(1280.0f / player_info->camera_fov);
    captures.view_height = (int32_t)(720.0f / player_info->camera_fov);
    captures.view_x = (int32_t)player_info->camera_x;
    captures.view_y = (int32_t)player_info->camera_y;
    captures.entities_in_view = entities_in_view;
    captures.simulation = self;

    rr_simulation_for_each_entity(self, &captures, rr_simulation_find_entities_in_view_foreach_function);
}

void rr_simulation_write_binary(struct rr_simulation *self, struct rr_encoder *encoder, struct rr_component_player_info *player_info)
{
    // don't use spatial hashing to query (large areas are slow)
    uint8_t entities_in_view[MAX_ENTITY_COUNT >> 3];
    memset(entities_in_view, 0, (MAX_ENTITY_COUNT >> 3) * (sizeof *entities_in_view));

    rr_simulation_find_entities_in_view(self, player_info, entities_in_view);

    struct rr_simulation_encoder_temp a = (struct rr_simulation_encoder_temp){
        .simulation = self,
        .encoder = encoder};
    rr_simulation_for_each_entity(self, &a, rr_protocol_foreach_function);
    rr_encoder_write_uint8(encoder, 0); // null terminate entity update ids
}

// will change later definitely
void rr_simulation_for_each_entity(struct rr_simulation *self, void *d, void (*cb)(EntityIdx, void *))
{
    for (EntityIdx i = 1; i < MAX_ENTITY_COUNT; i++)
        if (rr_simulation_has_entity(self, i))
            cb(i, d);
}

void rr_simulation_tick(struct rr_simulation *self)
{
    rr_system_velocity_tick(self);
}

#define XX(COMPONENT, ID)                                                                                        \
    int rr_simulation_has_##COMPONENT(struct rr_simulation *self, EntityIdx entity)                              \
    {                                                                                                            \
        assert(rr_simulation_has_entity(self, entity));                                                          \
        return rr_bitset_get(self->COMPONENT##_tracker, entity);                                                 \
    }                                                                                                            \
    struct rr_component_##COMPONENT *rr_simulation_add_##COMPONENT(struct rr_simulation *self, EntityIdx entity) \
    {                                                                                                            \
        assert(rr_simulation_has_entity(self, entity));                                                          \
        rr_bitset_set(self->COMPONENT##_tracker, entity);                                                        \
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
