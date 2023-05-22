#include <Server/System/CollisionDetection.h>

#include <stdio.h>
#include <string.h>

#include <Server/Simulation.h>
#include <Shared/Bitset.h>

struct second_for_each_function_captures
{
    struct rr_simulation *simulation;
    struct rr_component_physical *physical;
};

static void system_for_each_2nd_function(EntityIdx entity2, void *_captures)
{
    struct second_for_each_function_captures *captures = _captures;
    EntityIdx entity1 = captures->physical->parent_id;
    struct rr_simulation *this = captures->simulation;
    struct rr_component_physical *physical1 = captures->physical;

    if (entity1 == entity2)
        return;

    if (!rr_simulation_has_physical(this, entity2))
        return;

    struct rr_component_physical *physical2 = rr_simulation_get_physical(this, entity2);
    struct rr_vector delta = {physical1->x - physical2->x, physical1->y - physical2->y};
    float collision_radius = physical1->radius + physical2->radius;
    if ((delta.x * delta.x + delta.y * delta.y) < collision_radius * collision_radius)
    {
        if (!rr_bitset_get_bit(physical1->collisions, entity1)
         && !rr_bitset_get_bit(physical2->collisions, entity1)
         && !rr_bitset_get_bit(physical1->collisions, entity2)
         && !rr_bitset_get_bit(physical2->collisions, entity2))
            rr_bitset_set(physical1->collisions, entity2);
    }
}

static void system_for_each_function(EntityIdx entity1, void *incoming_captures)
{
    struct rr_simulation *this = incoming_captures;
    
    if (!rr_simulation_has_physical(this, entity1))
        return;

    struct rr_component_physical *physical1 = rr_simulation_get_physical(this, entity1);
    struct second_for_each_function_captures captures;
    captures.simulation = this;
    captures.physical = physical1;

    rr_simulation_for_each_entity(this, &captures, system_for_each_2nd_function);
}

void system_reset_colliding_with(EntityIdx entity, void *captures)
{
    struct rr_simulation *this = captures;
    if (!rr_simulation_has_physical(this, entity))
        return;
    
    struct rr_component_physical *physical = rr_simulation_get_physical(this, entity);
    memset(&physical->collisions[0], 0, RR_MAX_ENTITY_COUNT >> 3);
}

void rr_system_collision_detection_tick(struct rr_simulation *this)
{
    rr_simulation_for_each_entity(this, this, system_reset_colliding_with);
    rr_simulation_for_each_entity(this, this, system_for_each_function);
}
