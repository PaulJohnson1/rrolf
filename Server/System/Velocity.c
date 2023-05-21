#include <Server/System/Velocity.h>

#include <Server/Simulation.h>

#include <Shared/Entity.h>
#include <Shared/Vector.h>

void rr_system_velocity_foreach_function(EntityIdx id, void *simulation)
{
    if (!rr_simulation_has_physical(simulation, id))
        return;
    struct rr_component_physical *physical = rr_simulation_get_physical(simulation, id);
    rr_vector_scale(&physical->velocity, physical->friction);
    rr_vector_add(&physical->velocity, &physical->acceleration);
    rr_component_physical_set_x(physical, physical->x + physical->velocity.x);
    rr_component_physical_set_y(physical, physical->y + physical->velocity.y);
    if (!rr_simulation_has_flower(simulation, id))
        return;
    //flower eye angle
    rr_simulation_get_flower(simulation, id)->eye_angle = rr_vector_theta(&physical->acceleration);
}

void rr_system_velocity_tick(struct rr_simulation *simulation)
{
    rr_simulation_for_each_entity(simulation, simulation, rr_system_velocity_foreach_function);
}
