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
    struct rr_component_relations *relations1 = rr_simulation_get_relations(this, entity1);
    struct rr_component_relations *relations2 = rr_simulation_get_relations(this, entity2);
    if (relations1->team == relations2->team)
        return;
    struct rr_component_health *health1 = captures->health;
    struct rr_component_health *health2 = rr_simulation_get_health(this, entity2);
    rr_component_health_set_health(health1, health1->health - health2->damage);
    rr_component_health_set_health(health2, health2->health - health1->damage);
    health1->last_damaged_by = relations1->owner || entity2;
    health2->last_damaged_by = relations1->owner || entity1;

    if (rr_simulation_has_ai(this, entity1))
    {
        struct rr_component_ai *ai = rr_simulation_get_ai(this, entity1);
        if (rr_simulation_has_entity(this, ai->target_entity))
            return;
        if (rr_simulation_has_petal(this, entity2))
        {
            struct rr_component_relations *relations = rr_simulation_get_relations(this, entity2);
            ai->target_entity = relations->owner;
            printf("%u ai found new target %u", entity1, ai->target_entity);
        }
        else // allows for mob targeting
        {
            ai->target_entity = entity2;
            printf("%u ai found new target %u", entity1, ai->target_entity);
        }

    }
    if (rr_simulation_has_ai(this, entity2))
    {
        struct rr_component_ai *ai = rr_simulation_get_ai(this, entity2);
        if (rr_simulation_has_entity(this, ai->target_entity))
            return;
        if (rr_simulation_has_petal(this, entity1))
        {
            struct rr_component_relations *relations = rr_simulation_get_relations(this, entity1);
            ai->target_entity = relations->owner;
            printf("%u ai found new target %u", entity2, ai->target_entity);
        }
        else
        {
            ai->target_entity = entity1;
            printf("%u ai found new target %u", entity2, ai->target_entity);
        }
    }
}

static void system_for_each_function(EntityIdx entity, void *_captures)
{
    struct rr_simulation *this = _captures;
    // all health has physical

    struct rr_component_physical *physical = rr_simulation_get_physical(this, entity);
    struct rr_component_health *health = rr_simulation_get_health(this, entity);

    struct colliding_with_captures captures;
    captures.health = health;
    captures.simulation = this;

    for (uint32_t i = 0; i < physical->colliding_with_size; ++i)
        colliding_with_function(physical->colliding_with[i], &captures);
    // rr_bitset_for_each_bit(physical->collisions, physical->collisions + (RR_BITSET_ROUND(RR_MAX_ENTITY_COUNT)), &captures, colliding_with_function);
}

static void system_deletion_for_each_function(EntityIdx entity, void *_captures)
{
    struct rr_simulation *this = _captures;
    if (rr_simulation_get_health(this, entity)->health <= 0.001f)
        rr_simulation_request_entity_deletion(this, entity);
}

void rr_system_health_tick(struct rr_simulation *this)
{
    rr_simulation_for_each_health(this, this, system_default_idle_heal);
    rr_simulation_for_each_health(this, this, system_for_each_function);
    rr_simulation_for_each_health(this, this, system_deletion_for_each_function);
}
