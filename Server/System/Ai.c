#include <Server/System/MapBoundary.h>

#include <stdlib.h>
#include <math.h>
#include <assert.h>

#include <Server/Simulation.h>
#include <Shared/Entity.h>
#include <Shared/Vector.h>
#include <Shared/Component/Physical.h>

static void system_for_each_function(EntityIdx entity, void *simulation)
{
    struct rr_simulation *this = simulation;
    if (!rr_simulation_has_ai(this, entity))
        return;
    if (rr_simulation_has_centipede(this, entity) && rr_simulation_get_centipede(this, entity)->parent_node != RR_NULL_ENTITY)
        return;
    struct rr_component_ai *ai = rr_simulation_get_ai(this, entity);
    struct rr_component_physical *physical = rr_simulation_get_physical(this, entity);

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
        

    case rr_ai_state_attacking:
    {
        ai->ticks_until_next_action = 10; // when the ai is done being pissed, wait a little until the next action
        if (!rr_simulation_has_entity(this, ai->target_entity)) // target died (what a noob)
        {
            ai->ai_state = rr_ai_state_spin2team;
            ai->target_entity = RR_NULL_ENTITY; // you really don't want the entity being reallocated and then the mob goes sicko mode
            break;
        }

        struct rr_component_physical *target_physical = rr_simulation_get_physical(this, ai->target_entity);
        struct rr_vector delta = {target_physical->x - physical->x, target_physical->y - physical->y};
        rr_vector_set_magnitude(&delta, 0.75f);
        rr_vector_add(&physical->acceleration, &delta);
        rr_component_physical_set_angle(physical, rr_vector_theta(&delta));
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
        }
    }
    ai->ticks_until_next_action--;
}

void rr_system_ai_tick(struct rr_simulation *simulation)
{
    rr_simulation_for_each_entity(simulation, simulation, system_for_each_function);
}
