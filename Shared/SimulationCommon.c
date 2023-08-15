#include <Shared/SimulationCommon.h>

#include <assert.h>
#include <stdio.h>
#include <stdlib.h>
#include <string.h>

#include <Shared/Bitset.h>
#include <Shared/Utilities.h>

int rr_simulation_has_entity(struct rr_simulation *this, EntityIdx entity)
{
    return rr_bitset_get(this->entity_tracker, entity);
}

void rr_simulation_request_entity_deletion(struct rr_simulation *this,
                                           EntityIdx entity)
{
#ifndef NDEBUG
    printf("request deletion of entity %u\n", entity);
#endif
    assert(rr_simulation_has_entity(this, entity));
    rr_bitset_set(this->pending_deletions, entity);
}

void __rr_simulation_pending_deletion_free_components(uint64_t i,
                                                      void *captures)
{
    struct rr_simulation *this = captures;
    assert(rr_simulation_has_entity(this, i));
#define XX(COMPONENT, ID)                                                      \
    if (rr_simulation_has_##COMPONENT(this, i))                                \
        rr_component_##COMPONENT##_free(                                       \
            rr_simulation_get_##COMPONENT(this, i), this);
    RR_FOR_EACH_COMPONENT;
#undef XX
}

void __rr_simulation_pending_deletion_unset_entity(uint64_t i, void *captures)
{
    struct rr_simulation *this = captures;
    assert(rr_simulation_has_entity(this, i));

    RR_SERVER_ONLY(rr_bitset_set(this->recently_deleted, i);)
#ifndef NDEBUG
    RR_SERVER_ONLY(printf("deleted with id %d\n", i);)
#endif

#define XX(COMPONENT, ID)                                                      \
    if (rr_simulation_has_##COMPONENT(this, i))                                \
        rr_bitset_unset(this->COMPONENT##_tracker, i);
    RR_FOR_EACH_COMPONENT;
#undef XX

    rr_bitset_unset(this->entity_tracker, i);
}

struct rr_simulation_for_each_entity_function_captures
{
    void (*user_cb)(EntityIdx, void *);
    void *user_captures;
    struct rr_simulation *simulation;
};

// used to convert the uint64_t index that rr_bitset_for_each_bit into an
// EntityIdx for the user
void rr_simulation_for_each_entity_function(uint64_t _id, void *_captures)
{
    EntityIdx id = _id;
    struct rr_simulation_for_each_entity_function_captures *captures =
        _captures;

    captures->user_cb(id, captures->user_captures);
}

void rr_simulation_create_component_vectors(struct rr_simulation *this)
{
#define XX(COMPONENT, ID)                                                      \
    this->COMPONENT##_count = 0;                                               \
    for (EntityIdx entity = 1; entity < RR_MAX_ENTITY_COUNT; ++entity)         \
    {                                                                          \
        if (rr_bitset_get(&this->COMPONENT##_tracker[0], entity) == 0)         \
            continue;                                                          \
        this->COMPONENT##_vector[this->COMPONENT##_count++] = entity;          \
    }
    RR_FOR_EACH_COMPONENT;
#undef XX
}

void rr_simulation_for_each_entity(struct rr_simulation *this,
                                   void *user_captures,
                                   void (*cb)(EntityIdx, void *))
{
    struct rr_simulation_for_each_entity_function_captures captures;
    captures.user_cb = cb;
    captures.user_captures = user_captures;

    rr_bitset_for_each_bit(&this->entity_tracker[0],
                           &this->entity_tracker[0] +
                               (RR_BITSET_ROUND(RR_MAX_ENTITY_COUNT)),
                           &captures, rr_simulation_for_each_entity_function);
}

#define XX(COMPONENT, ID)                                                      \
    static void COMPONENT##for_each(uint64_t bit, void *_captures)             \
    {                                                                          \
        EntityIdx id = bit;                                                    \
        struct rr_simulation_for_each_entity_function_captures *captures =     \
            _captures;                                                         \
        assert(rr_simulation_has_##COMPONENT(captures->simulation, id));       \
        captures->user_cb(id, captures->user_captures);                        \
    }                                                                          \
    void rr_simulation_for_each_##COMPONENT(struct rr_simulation *this,        \
                                            void *user_captures,               \
                                            void (*cb)(EntityIdx, void *))     \
    {                                                                          \
        struct rr_simulation_for_each_entity_function_captures captures;       \
        captures.user_cb = cb;                                                 \
        captures.user_captures = user_captures;                                \
        captures.simulation = this;                                            \
        for (uint16_t pos = 0; pos < this->COMPONENT##_count; ++pos)           \
            cb(this->COMPONENT##_vector[pos], user_captures);                  \
        return;                                                                \
    }                                                                          \
                                                                               \
    uint8_t rr_simulation_has_##COMPONENT(struct rr_simulation *this,          \
                                          EntityIdx entity)                    \
    {                                                                          \
        assert(rr_simulation_has_entity(this, entity));                        \
        return rr_bitset_get(this->COMPONENT##_tracker, entity);               \
    }                                                                          \
    struct rr_component_##COMPONENT *rr_simulation_add_##COMPONENT(            \
        struct rr_simulation *this, EntityIdx entity)                          \
    {                                                                          \
        assert(rr_simulation_has_entity(this, entity));                        \
        rr_bitset_set(this->COMPONENT##_tracker, entity);                      \
        rr_component_##COMPONENT##_init(this->COMPONENT##_components + entity, \
                                        this);                                 \
        this->COMPONENT##_components[entity].parent_id = entity;               \
        this->COMPONENT##_vector[this->COMPONENT##_count++] = entity;          \
        return rr_simulation_get_##COMPONENT(this, entity);                    \
    }                                                                          \
    struct rr_component_##COMPONENT *rr_simulation_get_##COMPONENT(            \
        struct rr_simulation *this, EntityIdx entity)                          \
    {                                                                          \
        assert(rr_simulation_has_entity(this, entity));                        \
        assert(rr_simulation_has_##COMPONENT(this, entity));                   \
        return &this->COMPONENT##_components[entity];                          \
    }
RR_FOR_EACH_COMPONENT;
#undef XX
