#include <Server/System/MapBoundary.h>

#include <Server/Simulation.h>

#include <Shared/Entity.h>
#include <Shared/Vector.h>
#include <Shared/Component/Physical.h>

static void rr_system_map_boundary_foreach_function(EntityIdx id, void *simulation)
{
    if (!rr_simulation_has_physical(simulation, id))
        return;
    struct rr_component_physical *physical = rr_simulation_get_physical(simulation, id);
    struct rr_vector position;
    rr_vector_set(&position, physical->x, physical->y);
    if (rr_vector_get_magnitude(&position) > 1650.0f - physical->radius)
    {
        rr_vector_set_magnitude(&position, 1650.0f - physical->radius);
        rr_component_physical_set_x(physical, position.x);
        rr_component_physical_set_y(physical, position.y);
    }
}

void rr_system_map_boundary_tick(struct rr_simulation *simulation)
{
    rr_simulation_for_each_entity(simulation, simulation, rr_system_map_boundary_foreach_function);
}
