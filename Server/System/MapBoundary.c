#include <Server/System/MapBoundary.h>

#include <Server/Simulation.h>

#include <Shared/Component/Physical.h>
#include <Shared/Entity.h>
#include <Shared/Vector.h>

static void rr_system_map_boundary_foreach_function(EntityIdx id,
                                                    void *simulation)
{
    struct rr_simulation *this = simulation;
    struct rr_component_physical *physical =
        rr_simulation_get_physical(this, id);
    struct rr_component_arena *arena = rr_simulation_get_arena(this, 1);
    struct rr_vector position;
    rr_vector_set(&position, physical->x, physical->y);
    if (rr_vector_get_magnitude(&position) > arena->radius - physical->radius)
    {
        if (rr_simulation_has_petal(this, id))
            if (rr_simulation_get_petal(this, id)->detached)
                rr_simulation_request_entity_deletion(this, id);

        rr_vector_set_magnitude(&position, arena->radius - physical->radius);
        rr_component_physical_set_x(physical, position.x);
        rr_component_physical_set_y(physical, position.y);
    }
}

void rr_system_map_boundary_tick(struct rr_simulation *simulation)
{
    rr_simulation_for_each_physical(simulation, simulation,
                                    rr_system_map_boundary_foreach_function);
}
