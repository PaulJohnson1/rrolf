#include <Client/Simulation.h>

#include <assert.h>
#include <string.h>
#include <stdio.h>

#include <Shared/Bitset.h>

void rr_simulation_entity_create_with_id(struct rr_simulation *this, EntityIdx entity)
{
    rr_bitset_set(this->entity_tracker, entity);
}

void rr_simulation_read_binary(struct rr_simulation *this, struct rr_encoder *encoder)
{
    EntityIdx id = 0;
    while (1)
    {
        id = rr_encoder_read_varuint(encoder);
        if (id == RR_NULL_ENTITY)
            break;
        printf("deleting entity id %d\n", id);
        assert(id < RR_MAX_ENTITY_COUNT);
        assert(rr_bitset_get_bit(this->entity_tracker, id));
        rr_simulation_free_entity(this, id);
    }

    while (1)
    {
        id = rr_encoder_read_varuint(encoder);
        if (id == RR_NULL_ENTITY)
            break;
        uint8_t is_creation = !rr_bitset_get_bit(this->entity_tracker, id);
        uint32_t component_flags = rr_encoder_read_varuint(encoder);

        if (is_creation)
        {
            printf("create entity with id %d, components %d\n", id, component_flags);
            rr_bitset_set(this->entity_tracker, id);
#define XX(COMPONENT, ID)            \
    if (component_flags & (1 << ID)) \
        rr_simulation_add_##COMPONENT(this, id);
    RR_FOR_EACH_COMPONENT
#undef XX
        }

#define XX(COMPONENT, ID)\
    if (component_flags & (1 << ID))\
        rr_component_##COMPONENT##_read(rr_simulation_get_##COMPONENT(this, id), encoder);
    RR_FOR_EACH_COMPONENT
#undef XX
    }
}