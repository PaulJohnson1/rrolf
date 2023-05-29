#include <Server/System/Health.h>

#include <stdio.h>
#include <string.h>

#include <Server/Simulation.h>
#include <Shared/Bitset.h>

struct colliding_with_captures
{
    struct rr_simulation *simulation;
    struct rr_component_health *health;
};

static void system_default_idle_heal(EntityIdx entity, void *captures)
{
    struct rr_simulation *this = captures;
    if (!rr_simulation_has_health(this, entity))
        return;
    struct rr_component_health *health = rr_simulation_get_health(this, entity);
    // heal 1% of max hp per second (0.0004 is 0.01 / 25)
    rr_component_health_set_health(health, health->health + health->max_health * 0.0004);
}

static void colliding_with_function(uint64_t i, void *_captures)
{
    struct colliding_with_captures *captures = _captures;
    struct rr_simulation *this = captures->simulation;
    EntityIdx entity1 = captures->health->parent_id;
    EntityIdx entity2 = i;
    if (!rr_simulation_has_health(this, entity2))
        return;
    if (rr_simulation_get_relations(this, entity2)->team == rr_simulation_get_relations(this, entity1)->team)
        return;
    struct rr_component_health *health1 = captures->health;
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
    struct rr_component_health *health = rr_simulation_get_health(this, entity);

    struct colliding_with_captures captures;
    captures.health = health;
    captures.simulation = this;

    rr_bitset_for_each_bit(physical->collisions, physical->collisions + (RR_BITSET_ROUND(RR_MAX_ENTITY_COUNT)), &captures, colliding_with_function);
}

static void system_deletion_for_each_function(EntityIdx entity, void *_captures)
{
    struct rr_simulation *this = _captures;
    if (!rr_simulation_has_health(this, entity))
        return;
    if (rr_simulation_get_health(this, entity)->health == 0)
        rr_simulation_request_entity_deletion(this, entity);
}

void rr_system_health_tick(struct rr_simulation *this)
{
    rr_simulation_for_each_entity(this, this, system_default_idle_heal);
    rr_simulation_for_each_entity(this, this, system_for_each_function);
    rr_simulation_for_each_entity(this, this, system_deletion_for_each_function);
}
