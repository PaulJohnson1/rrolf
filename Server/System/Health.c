#include <Server/System/Health.h>

#include <stdio.h>
#include <string.h>

#include <Server/Simulation.h>
#include <Shared/Bitset.h>

struct colliding_with_captures
{
    struct rr_simulation *simulation;
    struct rr_component_physical *physical;
};

// that's for the casting which is not impm
static void colliding_with_function(uint64_t i, void *_captures)
{
    struct colliding_with_captures *captures = _captures;
    struct rr_simulation *this = captures->simulation;
    EntityIdx entity1 = captures->physical->parent_id;
    EntityIdx entity2 = i;
    if (!rr_simulation_has_health(this, entity2))
        return;
    if (rr_simulation_get_relations(this, entity2)->team == rr_simulation_get_relations(this, entity1)->team)
        return;
    struct rr_component_health *health1 = rr_simulation_get_health(this, entity1);
    struct rr_component_health *health2 = rr_simulation_get_health(this, entity2);
    rr_component_health_set_health(health1, health1->health - health2->damage);
    rr_component_health_set_health(health2, health2->health - health1->damage);
}

static void system_for_each_function(EntityIdx entity, void *_captures)
{
    struct rr_simulation *this = _captures;

    if (!rr_simulation_has_physical(this, entity))
        return;
    if (!rr_simulation_has_health(this, entity))
        return;
    struct rr_component_physical *physical = rr_simulation_get_physical(this, entity);

    struct colliding_with_captures captures;
    captures.physical = physical;
    captures.simulation = this;

    rr_bitset_for_each_bit(physical->collisions, physical->collisions + (RR_MAX_ENTITY_COUNT >> 3), &captures, colliding_with_function);
}

void rr_system_health_tick(struct rr_simulation *this)
{
    rr_simulation_for_each_entity(this, this, system_for_each_function);
}
