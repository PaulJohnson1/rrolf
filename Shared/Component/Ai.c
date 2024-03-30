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

#include <Shared/Component/Ai.h>

#include <string.h>

#include <Shared/Entity.h>
#include <Shared/SimulationCommon.h>
#include <Shared/Utilities.h>
#include <Shared/pb.h>

void rr_component_ai_init(struct rr_component_ai *this,
                          struct rr_simulation *simulation)
{
    memset(this, 0, sizeof *this);
    RR_SERVER_ONLY(this->ai_state = rr_ai_state_idle;)
    RR_SERVER_ONLY(this->has_prediction = rr_frand() < 0.25;)
}

void rr_component_ai_free(struct rr_component_ai *this,
                          struct rr_simulation *simulation)
{
}

#ifdef RR_SERVER
void rr_component_ai_write(struct rr_component_ai *this,
                           struct proto_bug *encoder, int is_creation,
                           struct rr_component_player_info *client)
{
}

#endif

#ifdef RR_CLIENT
void rr_component_ai_read(struct rr_component_ai *this,
                          struct proto_bug *encoder)
{
}
#endif