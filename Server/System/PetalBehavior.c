#include <Server/System/PetalBehavior.h>

#include <math.h>

#include <Server/Simulation.h>

#include <Shared/Component/PlayerInfo.h>
#include <Shared/StaticData.h>
#include <Shared/Entity.h>
#include <Shared/Vector.h>

void rr_system_petal_reload_foreach_function(EntityIdx id, void *simulation)
{
    if (!rr_simulation_has_player_info(simulation, id))
        return;
    struct rr_component_player_info *player_info = rr_simulation_get_player_info(simulation, id);
    if (player_info->flower_id == 0)
        return;
    uint32_t rotationPos = 0;
    for (uint64_t outer = 0; outer < player_info->slot_count; ++outer)
    {
        struct rr_component_player_info_petal_slot *slot = &player_info->slots[outer];
        struct rr_petal_data *data = slot->data;
        for (uint64_t inner = 0; inner < 10; ++inner)
        {
            ++rotationPos;
            struct rr_component_player_info_petal *p_petal = &slot->petals[inner];
            if (!p_petal->is_alive)
            {
                if(--p_petal->cooldown_ticks <= 0)
                {
                    p_petal->is_alive = 1;
                    p_petal->simulation_id = rr_simulation_alloc_entity(simulation);
                    struct rr_component_physical *physical = rr_simulation_add_physical(simulation, p_petal->simulation_id);
                    rr_component_physical_set_radius(physical, 10);
                    rr_component_physical_set_x(physical, player_info->camera_x);
                    rr_component_physical_set_y(physical, player_info->camera_y);
                    struct rr_component_petal *petal = rr_simulation_add_petal(simulation, p_petal->simulation_id);
                    petal->id = 1;
                    petal->rarity = 2; //need fix, use setters
                    petal->rotation_pos = rotationPos;
                    petal->owner = id;
                }
            }
        }
    }
    player_info->rotation_count = rotationPos;
    player_info->global_rotation += 0.1;
}

void rr_system_petal_behavior_petal_movement_foreach_function(EntityIdx id, void *simulation)
{
    if (!rr_simulation_has_petal(simulation, id))
        return;
    struct rr_component_petal *petal = rr_simulation_get_petal(simulation, id);
    struct rr_component_physical *physical = rr_simulation_get_physical(simulation, id);
    if (!rr_simulation_has_entity(simulation, petal->owner))
    {
        rr_simulation_free_entity(simulation, id);
        return;
    }
    if (!rr_simulation_has_player_info(simulation, petal->owner))
    {
        rr_simulation_free_entity(simulation, id);
        return;
    }
    struct rr_component_player_info *player_info = rr_simulation_get_player_info(simulation, petal->owner);
    if (player_info->flower_id == 0)
    {
        rr_simulation_free_entity(simulation, id);
        return;
    }
    struct rr_component_physical *flower_physical = rr_simulation_get_physical(simulation, player_info->flower_id);
    struct rr_vector position_vector;
    struct rr_vector flower_vector;
    rr_vector_set(&position_vector, physical->x, physical->y);
    rr_vector_set(&flower_vector, flower_physical->x, flower_physical->y);
    float holdingRadius = 50;
    float currAngle = player_info->global_rotation + petal->rotation_pos * 2 * M_PI / player_info->rotation_count;
    struct rr_vector chase_vector;
    rr_vector_from_polar(&chase_vector, holdingRadius, currAngle);
    rr_vector_add(&chase_vector, &flower_vector);
    rr_vector_sub(&chase_vector, &position_vector);
    physical->acceleration.x = chase_vector.x;
    physical->acceleration.y = chase_vector.y;
}

void rr_system_petal_behavior_tick(struct rr_simulation *simulation)
{
    rr_simulation_for_each_entity(simulation, simulation, rr_system_petal_reload_foreach_function);
    rr_simulation_for_each_entity(simulation, simulation, rr_system_petal_behavior_petal_movement_foreach_function);
}
