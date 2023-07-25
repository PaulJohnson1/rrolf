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
    struct rr_component_physical *physical =
        rr_simulation_get_physical(this, entity);

    // heal 0.5% of max hp per second (0.0002 is 0.01 / 25)
    if (health->health > 0)
    {
        rr_component_health_set_health(health, health->health +
                                                   health->max_health * 0.0002);
        if (physical->server_animation_tick > 0)
            rr_component_physical_set_server_animation_tick(
                physical, physical->server_animation_tick - 1);
        if (health->damage_paused > 0)
            health->damage_paused -= 1;
    }
    else
        rr_simulation_request_entity_deletion(this, entity);
}

static void colliding_with_function(uint64_t i, void *_captures)
{
    struct colliding_with_captures *captures = _captures;
    struct rr_simulation *this = captures->simulation;
    EntityIdx entity1 = captures->health->parent_id;
    EntityIdx entity2 = i;
    if (!rr_simulation_has_health(this, entity2))
        return;
    struct rr_component_relations *relations1 =
        rr_simulation_get_relations(this, entity1);
    struct rr_component_relations *relations2 =
        rr_simulation_get_relations(this, entity2);
    if (relations1->team == relations2->team)
        return;
    struct rr_component_health *health1 = captures->health;
    struct rr_component_health *health2 =
        rr_simulation_get_health(this, entity2);
    struct rr_component_physical *physical1 =
        rr_simulation_get_physical(this, entity1);
    struct rr_component_physical *physical2 =
        rr_simulation_get_physical(this, entity2);
    if (health2->health == 0)
        return;
    uint8_t bypass = rr_simulation_has_petal(this, entity1) ||
                     rr_simulation_has_petal(this, entity2);
    if (health1->damage_paused == 0 || bypass)
    {
        rr_component_health_do_damage(health1, health2->damage);
        health1->damage_paused = 5;
        rr_component_physical_set_server_animation_tick(physical1, 5);

        if (rr_simulation_has_ai(this, entity1))
        {
            struct rr_component_ai *ai = rr_simulation_get_ai(this, entity1);
            if (ai->target_entity == RR_NULL_ENTITY)
            {
                if (rr_simulation_has_petal(this, entity2))
                {
                    struct rr_component_relations *relations =
                        rr_simulation_get_relations(this, entity2);
                    ai->target_entity = relations->owner;
                }
                else // allows for mob targeting
                    ai->target_entity = entity2;
            }
        }
    }
    if (health2->damage_paused == 0 || bypass)
    {
        rr_component_health_do_damage(health2, health1->damage);
        health2->damage_paused = 5;
        rr_component_physical_set_server_animation_tick(physical2, 5);

        if (rr_simulation_has_ai(this, entity2))
        {
            struct rr_component_ai *ai = rr_simulation_get_ai(this, entity2);
            if (ai->target_entity ==
                RR_NULL_ENTITY) // probably replaced by a is null check
            {
                if (rr_simulation_has_petal(this, entity1))
                {
                    struct rr_component_relations *relations =
                        rr_simulation_get_relations(this, entity1);
                    ai->target_entity = relations->owner;
                }
                else
                    ai->target_entity = entity1;
 
            }
        }
    }
}

static void system_for_each_function(EntityIdx entity, void *_captures)
{
    struct rr_simulation *this = _captures;
    // all health has physical

    struct rr_component_physical *physical =
        rr_simulation_get_physical(this, entity);
    struct rr_component_health *health = rr_simulation_get_health(this, entity);

    if (health->health == 0)
        return;

    struct colliding_with_captures captures;
    captures.health = health;
    captures.simulation = this;

    for (uint32_t i = 0; i < physical->colliding_with_size; ++i)
        colliding_with_function(physical->colliding_with[i], &captures);
}

void rr_system_health_tick(struct rr_simulation *this)
{
    rr_simulation_for_each_health(this, this, system_default_idle_heal);
    rr_simulation_for_each_health(this, this, system_for_each_function);
}
