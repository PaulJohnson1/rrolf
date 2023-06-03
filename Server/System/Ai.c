#include <Server/System/MapBoundary.h>

#include <stdlib.h>
#include <math.h>
#include <assert.h>

#include <Server/Simulation.h>
#include <Shared/Entity.h>
#include <Shared/Vector.h>
#include <Shared/Component/Physical.h>

struct aggressive_find_target_captures
{
    struct rr_simulation *simulation;
    struct rr_component_ai *ai;
    float closest_distance; // squared
};

static void aggressive_find_target(EntityIdx i, void *_captures)
{
    struct aggressive_find_target_captures *captures = _captures;

    struct rr_simulation *this = captures->simulation;
    struct rr_component_ai *ai = captures->ai;

    struct rr_component_physical *ai_physical = rr_simulation_get_physical(this, ai->parent_id);
    struct rr_component_physical *flower_physical = rr_simulation_get_physical(this, i);

    struct rr_vector delta = {ai_physical->x - flower_physical->x, ai_physical->x - flower_physical->x};

    float distance = delta.x * delta.x + delta.y * delta.y;

    if (distance < captures->closest_distance)
    {
        ai->ai_state = rr_ai_state_attacking;
        ai->target_entity = i;
        captures->closest_distance = distance;
    }
}

static void system_for_each_function(EntityIdx entity, void *simulation)
{
    struct rr_simulation *this = simulation;

    if (rr_simulation_has_centipede(this, entity) && rr_simulation_get_centipede(this, entity)->parent_node != RR_NULL_ENTITY)
        return;
    struct rr_component_ai *ai = rr_simulation_get_ai(this, entity);
    struct rr_component_physical *physical = rr_simulation_get_physical(this, entity);

    switch (ai->ai_type)
    {
    case rr_ai_type_aggressive:
    {
        if (ai->ai_state == rr_ai_state_attacking)
            break;
        // find nearest flower and violently eliminate it
        struct aggressive_find_target_captures captures;
        captures.ai = ai;
        captures.simulation = this;
        captures.closest_distance = 1500.0f * 1500.0f; // ai detection range

        rr_simulation_for_each_flower(this, &captures, aggressive_find_target);
    }
    default:
        break;
    }

    // tick the current state
    switch (ai->ai_state)
    {
    case rr_ai_state_idle_moving:
    {
        struct rr_vector accel;
        rr_vector_from_polar(&accel, 0.5f, physical->angle);
        rr_vector_add(&physical->acceleration, &accel);
        break;
    }
    case rr_ai_state_idle:
        break;
    case rr_ai_state_spin2team:
        rr_component_physical_set_angle(physical, physical->angle + 1);
        break;

    case rr_ai_state_attacking:
    {
        if (!rr_simulation_has_entity(this, ai->target_entity)) // target died (what a noob)
        {
            ai->ai_state = rr_ai_state_spin2team;
            ai->target_entity = RR_NULL_ENTITY; // you really don't want the entity being reallocated and then the mob goes sicko mode
            break;
        }
        struct rr_component_physical *target_physical = rr_simulation_get_physical(this, ai->target_entity);
        struct rr_vector delta = {target_physical->x - physical->x, target_physical->y - physical->y};
        rr_component_physical_set_angle(physical, rr_vector_theta(&delta));
        if (ai->ai_aggro_type == rr_ai_aggro_type_hornet)
            if (delta.x * delta.x + delta.y * delta.y <= 500 * 500)
            {
                break;
            }
        ai->ticks_until_next_action = rand() % 10 + 25; // when the ai is done being pissed, wait a little until the next action
        // if and only if aggro type is hornet and is too close then break
        rr_vector_set_magnitude(&delta, 0.75f);
        rr_vector_add(&physical->acceleration, &delta);
    }
    }

    if (ai->ticks_until_next_action == 0)
    {
        // find new state based on the type
        switch (ai->ai_state)
        {
        case rr_ai_state_idle_moving:
            ai->ai_state = rr_ai_state_idle;
            ai->ticks_until_next_action = rand() % 10 + 25;
            break;
        case rr_ai_state_idle:
            ai->ai_state = rr_ai_state_idle_moving;
            rr_component_physical_set_angle(physical, 2 * M_PI * rand() / RAND_MAX);
            ai->ticks_until_next_action = rand() % 10 + 75;
            break;
        case rr_ai_state_spin2team:
            ai->ai_state = rr_ai_state_idle;
            ai->ticks_until_next_action = 50;
            break;
        case rr_ai_state_attacking:
            if (ai->ai_aggro_type == rr_ai_aggro_type_hornet)
            {
                //spawn a missile
                EntityIdx petal_id = rr_simulation_alloc_entity(simulation);
                struct rr_component_physical *physical2 = rr_simulation_add_physical(simulation, petal_id);
                struct rr_component_petal *petal = rr_simulation_add_petal(simulation, petal_id);
                struct rr_component_relations *relations = rr_simulation_add_relations(simulation, petal_id);
                struct rr_component_health *health = rr_simulation_add_health(simulation, petal_id); 
                struct rr_component_projectile *projectile = rr_simulation_add_projectile(simulation, petal_id);

                rr_component_physical_set_x(physical2, physical->x);
                rr_component_physical_set_y(physical2, physical->y);
                rr_component_physical_set_angle(physical2, physical->angle);
                rr_component_physical_set_radius(physical2, 10);
                physical2->friction = 0.75f;
                physical2->mass = 0.05f;
                rr_vector_from_polar(&physical2->acceleration, 100, physical->angle);

                rr_component_relations_set_team(relations, rr_simulation_team_id_mobs);
                rr_component_relations_set_owner(relations, ai->parent_id);

                rr_component_petal_set_id(petal, rr_petal_id_missile);
                rr_component_petal_set_rarity(petal, rr_rarity_id_unusual); // need fix later
                petal->detached = 1;

                rr_component_health_set_max_health(health, 100);
                rr_component_health_set_health(health, 100);
                health->damage = 1.0f;
                rr_component_health_set_hidden(health, 1);

                projectile->ticks_until_death = 50;
                
                ai->ticks_until_next_action = 50;

                rr_vector_from_polar(&physical->acceleration, -2, physical->angle); //recoil
            }
            break;
        }
    }
    ai->ticks_until_next_action--;
}

void rr_system_ai_tick(struct rr_simulation *simulation)
{
    rr_simulation_for_each_ai(simulation, simulation, system_for_each_function);
}
