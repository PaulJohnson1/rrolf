#include <Server/MobAi/Ai.h>

#include <math.h>

#include <Server/EntityDetection.h>
#include <Server/Simulation.h>

void tick_ai_passive_default(EntityIdx entity,
                                struct rr_simulation *simulation)
{
    struct rr_component_ai *ai = rr_simulation_get_ai(simulation, entity);
    struct rr_component_physical *physical =
        rr_simulation_get_physical(simulation, entity);

    switch (ai->ai_state)
    {
    case rr_ai_state_idle:
        tick_idle(entity, simulation);
        break;

    case rr_ai_state_idle_moving:
        tick_idle_move_default(entity, simulation);
        break;
    default:
        break;
    }
}
