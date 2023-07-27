#include <Server/System/Camera.h>

#include <Server/Simulation.h>

#include <Shared/Entity.h>
#include <Shared/Vector.h>

void rr_system_camera_tick(struct rr_simulation *this)
{
    for (EntityIdx i = 0; i < this->player_info_count; ++i)
    {
        struct rr_component_player_info *player_info = rr_simulation_get_player_info(this, this->player_info_vector[i]);
        if (player_info->flower_id != RR_NULL_ENTITY)
        {
            struct rr_component_physical *physical = rr_simulation_get_physical(this, player_info->flower_id);
            rr_component_player_info_set_camera_x(player_info, physical->x);
            rr_component_player_info_set_camera_y(player_info, physical->y);
        }
        else if (this->flower_count > 0)
        {
            struct rr_component_physical *physical = rr_simulation_get_physical(this, this->flower_vector[0]);
            rr_component_player_info_set_camera_x(player_info, physical->x);
            rr_component_player_info_set_camera_y(player_info, physical->y);
        }
    }
}