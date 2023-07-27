#include <Server/System/Respawn.h>

#include <math.h>
#include <stdlib.h>

#include <Server/Simulation.h>

static void respawn_system_tick(EntityIdx entity, void *_captures)
{
    struct rr_simulation *this = _captures;
    struct rr_component_player_info *player_info =
        rr_simulation_get_player_info(this, entity);
    if (player_info->flower_id != RR_NULL_ENTITY)
        return;
    rr_simulation_alloc_player(entity, this);
}
void rr_system_respawn_tick(struct rr_simulation *this)
{
    rr_simulation_for_each_player_info(this, this, respawn_system_tick);
}
