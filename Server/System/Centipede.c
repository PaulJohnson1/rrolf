#include <Server/System/Centipede.h>

#include <Server/Simulation.h>

#include <stdio.h>

#include <Shared/Entity.h>
#include <Shared/Vector.h>

void rr_system_centipede_foreach_function(EntityIdx id, void *simulation)
{
    struct rr_component_centipede *centipede =
        rr_simulation_get_centipede(simulation, id);
    struct rr_component_physical *physical =
        rr_simulation_get_physical(simulation, id);
    struct rr_vector parent_vector = {physical->x, physical->y};
    if (centipede->parent_node != RR_NULL_ENTITY)
        return;
    while (centipede->child_node != RR_NULL_ENTITY)
    {
        float radius = physical->radius;
        centipede =
            rr_simulation_get_centipede(simulation, centipede->child_node);
        physical = rr_simulation_get_physical(simulation, centipede->parent_id);
        struct rr_vector delta = {physical->x - parent_vector.x,
                                  physical->y - parent_vector.y};
        if (delta.x == 0.0f && delta.y == 0.0f)
            delta.x = 1.0f;

        rr_vector_set_magnitude(&delta, radius + physical->radius + 0.01f);
        rr_component_physical_set_x(physical, parent_vector.x + delta.x);
        rr_component_physical_set_y(physical, parent_vector.y + delta.y);
        rr_component_physical_set_angle(physical, rr_vector_theta(&delta));
        rr_vector_set(&parent_vector, physical->x, physical->y);
    }
}

void rr_system_centipede_tick(struct rr_simulation *simulation)
{
    rr_simulation_for_each_centipede(simulation, simulation,
                                     rr_system_centipede_foreach_function);
}
