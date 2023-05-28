#include <Server/System/Centipede.h>

#include <Server/Simulation.h>

#include <stdio.h>

#include <Shared/Entity.h>
#include <Shared/Vector.h>

void rr_system_centipede_foreach_function(EntityIdx id, void *simulation)
{
    if (!rr_simulation_has_centipede(simulation, id))
        return;
    struct rr_component_centipede *centipede = rr_simulation_get_centipede(simulation, id);
    struct rr_component_physical *physical = rr_simulation_get_physical(simulation, id);
    struct rr_vector parent_vector = {physical->x, physical->y};
    //printf("parent=%d, child=%d, self=%d\n", centipede->parent_node, centipede->child_node, centipede->parent_id);
    if (centipede->parent_node != RR_NULL_ENTITY)
        return;
    //printf("parent is %d\n", id);
    while (centipede->child_node != RR_NULL_ENTITY)
    {
        float radius = physical->radius;
        //printf("looking at %d\n", centipede->child_node);
        centipede = rr_simulation_get_centipede(simulation, centipede->child_node);
        physical = rr_simulation_get_physical(simulation, centipede->parent_id);
        //printf("physical stats are %f %f %f\n", physical->x, physical->y, physical->radius);
        struct rr_vector delta = {physical->x - parent_vector.x, physical->y - parent_vector.y};
        if (delta.x == 0.0f && delta.y == 0.0f)
            delta.x = 1.0f;
        printf("delta is (%f, %f)\n", delta.x, delta.y);

        rr_vector_set_magnitude(&delta, radius + physical->radius + 0.01f);
        rr_component_physical_set_x(physical, parent_vector.x + delta.x);
        rr_component_physical_set_y(physical, parent_vector.y + delta.y);
        rr_component_physical_set_angle(physical, rr_vector_theta(&delta));
        //printf("parent vector is (%f, %f)\n", parent_vector.x, parent_vector.y);
        //printf("physical is (%f, %f)\n", physical->x, physical->y);
        rr_vector_set(&parent_vector, physical->x, physical->y);
    }
}

void rr_system_centipede_tick(struct rr_simulation *simulation)
{
    rr_simulation_for_each_entity(simulation, simulation, rr_system_centipede_foreach_function);
}
