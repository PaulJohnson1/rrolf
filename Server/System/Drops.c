#include <Server/System/Drops.h>

#include <Server/Simulation.h>

static void drop_despawn_tick(EntityIdx entity, void *_captures)
{
    struct rr_simulation *this = _captures;
    struct rr_component_drop *drop = rr_simulation_get_drop(this, entity);
    struct rr_component_physical *physical = rr_simulation_get_physical(this, entity);
    if (drop->ticks_until_despawn == 0)
    {
        rr_simulation_request_entity_deletion(this, entity);
        return;
    }
    --drop->ticks_until_despawn;
}

void rr_system_drops_tick(struct rr_simulation *this)
{
    rr_simulation_for_each_drop(this, this, drop_despawn_tick);
}
