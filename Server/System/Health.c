#include <Server/System/Health.h>

#include <stdio.h>
#include <math.h>
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
        if (health->damage_paused > 0)
            health->damage_paused -= 1;
    }
    else
        rr_simulation_request_entity_deletion(this, entity);
}

static void petal_effect(struct rr_simulation *simulation, EntityIdx target, EntityIdx petal_id)
{
    if (!rr_simulation_has_petal(simulation, petal_id))
        return;
    struct rr_component_petal *petal = rr_simulation_get_petal(simulation, petal_id);
    if (petal->id == rr_petal_id_beak)
    {
        struct rr_component_physical *physical = rr_simulation_get_physical(simulation, target);
        physical->stun_ticks = 25 + 25 * petal->rarity / 2;
    }
    else if (petal->id == rr_petal_id_lightning)
    {
        struct rr_component_physical *physical = rr_simulation_get_physical(simulation, target);
        struct rr_component_physical *petal_physical = rr_simulation_get_physical(simulation, petal_id);
        struct rr_simulation_animation *animation = &simulation->animations[simulation->animation_length++];
        animation->type = 1;
        EntityIdx chain[16] = {target};
        animation->points[0].x = petal_physical->x;
        animation->points[0].y = petal_physical->y;
        animation->points[1].x = physical->x;
        animation->points[1].y = physical->y;
        uint32_t chain_size = 2;
        uint32_t chain_amount = petal->rarity + 2;   
        float damage = rr_simulation_get_health(simulation, petal_id)->damage * 0.5; 
    
        for (; chain_size < chain_amount + 2; ++chain_size)
        {
            float old_x = physical->x, old_y = physical->y;
            target = RR_NULL_ENTITY;
            float min_dist = 100;
            for (uint16_t i = 0; i < simulation->mob_count; ++i)
            {
                EntityIdx mob_id = simulation->mob_vector[i];
                uint8_t hit_before = 0;
                for (uint32_t j = 0; j < chain_size; ++j)
                    hit_before |= chain[j] == mob_id;
                if (hit_before)
                    continue;
                if (rr_simulation_get_relations(simulation, mob_id)->team == rr_simulation_team_id_players)
                    continue;
                physical = rr_simulation_get_physical(simulation, mob_id);
                float x = physical->x, y = physical->y;
                float dist = sqrtf((x - old_x) * (x - old_x) + (y - old_y) * (y - old_y)) - physical->radius;
                if (dist > min_dist)
                    continue;
                target = mob_id;
                min_dist = dist;
            }
            if (target == RR_NULL_ENTITY)
                break;
            struct rr_component_health *health = rr_simulation_get_health(simulation, target);
            rr_component_health_do_damage(health, damage);
            health->damage_paused = 5;
            chain[chain_size] = target;
            physical = rr_simulation_get_physical(simulation, target);
            animation->points[chain_size].x = physical->x;
            animation->points[chain_size].y = physical->y;
        }
        animation->length = chain_size;
        rr_simulation_request_entity_deletion(simulation, petal_id);
    }
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
        petal_effect(this, entity1, entity2);
    }
    if (health2->damage_paused == 0 || bypass)
    {
        rr_component_health_do_damage(health2, health1->damage);
        health2->damage_paused = 5;

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
        petal_effect(this, entity2, entity1);
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
