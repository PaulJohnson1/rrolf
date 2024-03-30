// Copyright (C) 2024  Paul Johnson

// This program is free software: you can redistribute it and/or modify
// it under the terms of the GNU Affero General Public License as
// published by the Free Software Foundation, either version 3 of the
// License, or (at your option) any later version.

// This program is distributed in the hope that it will be useful,
// but WITHOUT ANY WARRANTY; without even the implied warranty of
// MERCHANTABILITY or FITNESS FOR A PARTICULAR PURPOSE.  See the
// GNU Affero General Public License for more details.

// You should have received a copy of the GNU Affero General Public License
// along with this program.  If not, see <https://www.gnu.org/licenses/>.

#include <Server/System/System.h>

#include <Server/Simulation.h>
#include <Shared/Entity.h>
#include <Shared/Vector.h>

void rr_system_camera_tick(struct rr_simulation *this)
{
    for (EntityIdx i = 0; i < this->player_info_count; ++i)
    {
        struct rr_component_player_info *player_info =
            rr_simulation_get_player_info(this, this->player_info_vector[i]);
        if (player_info->flower_id != RR_NULL_ENTITY)
        {
            struct rr_component_physical *physical =
                rr_simulation_get_physical(this, player_info->flower_id);
            rr_component_player_info_set_camera_x(player_info, physical->x);
            rr_component_player_info_set_camera_y(player_info, physical->y);
            rr_component_player_info_set_arena(player_info, physical->arena);
            continue;
        }
        // tempfix
        continue;
        uint8_t has_seed = 0;
        for (EntityIdx j = 0; j < this->petal_count; ++j)
        {
            struct rr_component_petal *petal =
                rr_simulation_get_petal(this, this->petal_vector[j]);
            if (petal->id != rr_petal_id_seed || petal->detached == 0)
                continue;
            struct rr_component_physical *physical =
                rr_simulation_get_physical(this, this->petal_vector[j]);
            rr_component_player_info_set_camera_x(player_info, physical->x);
            rr_component_player_info_set_camera_y(player_info, physical->y);
            has_seed = 1;
            break;
        }
        if (this->flower_count > 0 && !has_seed)
        {
            struct rr_component_physical *physical =
                rr_simulation_get_physical(this, this->flower_vector[0]);
            rr_component_player_info_set_camera_x(player_info, physical->x);
            rr_component_player_info_set_camera_y(player_info, physical->y);
        }
    }
}
