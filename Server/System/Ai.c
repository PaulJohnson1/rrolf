#include <Server/System/MapBoundary.h>

#include <stdlib.h>
#include <math.h>

#include <Server/Simulation.h>
#include <Shared/Entity.h>
#include <Shared/Vector.h>
#include <Shared/Component/Physical.h>

static void system_for_each_function(EntityIdx entity, void *simulation)
{
    struct rr_simulation *this = simulation;
    if (!rr_simulation_has_ai(this, entity))
        return;
    struct rr_component_ai *ai = rr_simulation_get_ai(this, entity);

    // idle tick lol
    {
        struct rr_component_physical *physical = rr_simulation_get_physical(this, entity);
        if (ai->ai_state == rr_ai_state_idle_moving)
        {
            struct rr_vector accel;
            rr_vector_from_polar(&accel, 5.0f, physical->angle);
            rr_vector_add(&physical->acceleration, &accel);
        }

        if (ai->ticks_until_next_action == 0)
        {
            if (ai->ai_state == rr_ai_state_idle)
            {
                // move for 50 ticks
                ai->ai_state = rr_ai_state_idle_moving;
                ai->ticks_until_next_action = rand() % 25 + 25;

                rr_component_physical_set_angle(physical, (float)rand() / (float)RAND_MAX * M_PI * 2);
            }
            else if (ai->ai_state == rr_ai_state_idle_moving)
            {
                // stay still for 75 ticks
                ai->ai_state = rr_ai_state_idle;
                ai->ticks_until_next_action = rand() % 25 + 50;
            }
            else
            {
                assert(0);
            }
        }

        ai->ticks_until_next_action--;
    }
}

void rr_system_ai_tick(struct rr_simulation *simulation)
{
    rr_simulation_for_each_entity(simulation, simulation, system_for_each_function);
}
