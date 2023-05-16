#include <Shared/SimulationCommon.h>

#include <assert.h>
#include <string.h>
#include <stdio.h>

#include <Shared/Bitset.h>
#include <Shared/Utilities.h>

void rr_simulation_init(struct rr_simulation *this)
{
    memset(this, 0, sizeof *this);
}

void rr_simulation_free_entity(struct rr_simulation *this, EntityIdx entity)
{
    printf("deleted entity with id %d\n", entity);
#define XX(COMPONENT, ID)                            \
    if (rr_simulation_has_##COMPONENT(this, entity)) \
        rr_component_##COMPONENT##_free(rr_simulation_get_##COMPONENT(this, entity));
    RR_FOR_EACH_COMPONENT;
#undef XX

    // unset them
#define XX(COMPONENT, ID) \
    rr_bitset_unset(this->COMPONENT##_tracker, entity);
    RR_FOR_EACH_COMPONENT;
#undef XX

    // unset entity
    rr_bitset_unset(this->entity_tracker, entity);
}

int rr_simulation_has_entity(struct rr_simulation *this, EntityIdx entity)
{
    return rr_bitset_get(this->entity_tracker, entity);
}

struct rr_simulation_for_each_entity_function_captures
{
    void (*user_cb)(EntityIdx, void *);
    void *user_captures;
};

// used to convert the uint64_t index that rr_bitset_for_each_bit into an EntityIdx for the user
void rr_simulation_for_each_entity_function(uint64_t _id, void *_captures)
{
    EntityIdx id = _id;
    struct rr_simulation_for_each_entity_function_captures *captures = _captures;

    captures->user_cb(id, captures->user_captures);
}

void rr_simulation_for_each_entity(struct rr_simulation *this, void *user_captures, void (*cb)(EntityIdx, void *))
{
    struct rr_simulation_for_each_entity_function_captures captures;
    captures.user_cb = cb;
    captures.user_captures = user_captures;

    rr_bitset_for_each_bit(&this->entity_tracker[0], &this->entity_tracker[0] + (RR_MAX_ENTITY_COUNT >> 3), &captures, rr_simulation_for_each_entity_function);
}

#define XX(COMPONENT, ID)                                                                                        \
    int rr_simulation_has_##COMPONENT(struct rr_simulation *this, EntityIdx entity)                              \
    {                                                                                                            \
        assert(rr_simulation_has_entity(this, entity));                                                          \
        return rr_bitset_get(this->COMPONENT##_tracker, entity);                                                 \
    }                                                                                                            \
    struct rr_component_##COMPONENT *rr_simulation_add_##COMPONENT(struct rr_simulation *this, EntityIdx entity) \
    {                                                                                                            \
        assert(rr_simulation_has_entity(this, entity));                                                          \
        rr_bitset_set(this->COMPONENT##_tracker, entity);                                                        \
        rr_component_##COMPONENT##_init(this->COMPONENT##_components + entity);                                  \
        this->COMPONENT##_components[entity].parent_id = entity;                                                 \
        return rr_simulation_get_##COMPONENT(this, entity);                                                      \
    }                                                                                                            \
    struct rr_component_##COMPONENT *rr_simulation_get_##COMPONENT(struct rr_simulation *this, EntityIdx entity) \
    {                                                                                                            \
        assert(rr_simulation_has_entity(this, entity));                                                          \
        assert(rr_simulation_has_##COMPONENT(this, entity));                                                     \
        return &this->COMPONENT##_components[entity];                                                            \
    }
RR_FOR_EACH_COMPONENT;
#undef XX
