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

#include <Client/System/DeletionAnimation.h>

#include <math.h>

#include <Shared/Entity.h>
#include <Shared/SimulationCommon.h>
#include <Shared/Utilities.h>
#include <Shared/Vector.h>

struct function_captures
{
    float delta;
    struct rr_simulation *simulation;
};

void system_deletion_animation_for_each_function(EntityIdx entity,
                                                 void *_captures)
{
    struct function_captures *captures = _captures;
    struct rr_simulation *this = captures->simulation;
    float delta = captures->delta;
    if (rr_simulation_has_physical(this, entity))
    {
        struct rr_component_physical *physical =
            rr_simulation_get_physical(this, entity);
        physical->deletion_animation =
            rr_lerp(physical->deletion_animation, 1, 15 * delta);
        if (physical->deletion_animation > 0.9)
            rr_simulation_request_entity_deletion(this, entity);
    }
}

void rr_system_deletion_animation_tick(struct rr_simulation *simulation,
                                       float delta)
{
    struct function_captures captures;
    captures.simulation = simulation;
    captures.delta = delta;
    rr_simulation_for_each_entity(simulation, &captures,
                                  system_deletion_animation_for_each_function);
}
