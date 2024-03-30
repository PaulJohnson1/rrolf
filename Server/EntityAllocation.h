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

#pragma once

#include <Shared/SimulationCommon.h>

EntityIdx rr_simulation_alloc_entity(struct rr_simulation *);
EntityIdx rr_simulation_alloc_petal(struct rr_simulation *, EntityIdx, float, float,
                                    uint8_t, uint8_t, EntityIdx);
EntityIdx rr_simulation_alloc_mob(struct rr_simulation *, EntityIdx, float, float,
                                  enum rr_mob_id, enum rr_rarity_id,
                                  enum rr_simulation_team_id);
EntityIdx rr_simulation_alloc_player(struct rr_simulation *, EntityIdx, EntityIdx);