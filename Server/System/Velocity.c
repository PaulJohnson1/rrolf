#include <Server/System/Velocity.h>

#include <Server/Simulation.h>

#include <Shared/Entity.h>
#include <Shared/Vector.h>

static void system(EntityIdx id, void *simulation)
{
    struct rr_component_physical *physical =
        rr_simulation_get_physical(simulation, id);
    rr_vector_scale(&physical->velocity, physical->friction);
    if (physical->webbed)
        physical->acceleration_scale *= 0.2;
    if (physical->stun_ticks > 0)
    {
        physical->acceleration_scale = 0;
        --physical->stun_ticks;
    }
    struct rr_vector accel = {
        physical->acceleration.x * physical->acceleration_scale,
        physical->acceleration.y * physical->acceleration_scale};
    rr_vector_add(&physical->velocity, &accel);
    physical->acceleration_scale = 1;
    physical->webbed = 0;
    rr_component_physical_set_x(physical, physical->x + physical->velocity.x);
    rr_component_physical_set_y(physical, physical->y + physical->velocity.y);
    if (rr_simulation_has_flower(simulation, id))
    {
        if (physical->acceleration.x != 0.0f ||
            physical->acceleration.y != 0.0f)
        {
            rr_component_flower_set_eye_angle(
                rr_simulation_get_flower(simulation, id),
                rr_vector_theta(&physical->acceleration));
        }
    }
    rr_vector_set(&physical->acceleration, 0, 0);
}

void rr_system_velocity_tick(struct rr_simulation *simulation)
{
    rr_simulation_for_each_physical(simulation, simulation, system);
}
