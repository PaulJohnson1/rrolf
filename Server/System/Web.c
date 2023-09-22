#include <Server/System/System.h>

#include <Server/Simulation.h>
#include <Shared/Bitset.h>

static void system_for_each_function(EntityIdx entity, void *_captures)
{
    struct rr_simulation *this = _captures;

    struct rr_component_physical *physical =
        rr_simulation_get_physical(this, entity);

    struct rr_component_web *web = rr_simulation_get_web(this, entity);
    if (web->ticks_until_death == 0)
    {
        rr_simulation_request_entity_deletion(this, entity);
        return;
    }
    --web->ticks_until_death;
}

void rr_system_web_tick(struct rr_simulation *this)
{
    rr_simulation_for_each_web(this, this, system_for_each_function);
}
