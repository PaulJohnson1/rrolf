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
#include <Shared/Bitset.h>

static void system_for_each_function(EntityIdx entity, void *_captures)
{
    struct rr_simulation *this = _captures;

    struct rr_component_physical *physical =
        rr_simulation_get_physical(this, entity);

    struct rr_component_web *web = rr_simulation_get_web(this, entity);
    if (web->ticks_until_death == 0)
    {
        rr_simulation_request_entity_deletion(this, entity);
        return;
    }
    --web->ticks_until_death;
}

void rr_system_web_tick(struct rr_simulation *this)
{
    rr_simulation_for_each_web(this, this, system_for_each_function);
}
