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

#include <stdint.h>

#include <Shared/Entity.h>

struct rr_simulation;

EntityIdx rr_simulation_find_nearest_enemy(
    struct rr_simulation *, EntityIdx, float, void *,
    uint8_t (*)(struct rr_simulation *, EntityIdx, EntityIdx, void *));
EntityIdx rr_simulation_find_nearest_enemy_custom_pos(
    struct rr_simulation *, EntityIdx, float, float, float, void *,
    uint8_t (*)(struct rr_simulation *, EntityIdx, EntityIdx, void *));

EntityIdx rr_simulation_find_nearest_friend(
    struct rr_simulation *, EntityIdx, float, void *,
    uint8_t (*)(struct rr_simulation *, EntityIdx, EntityIdx, void *));
EntityIdx rr_simulation_find_nearest_friend_custom_pos(
    struct rr_simulation *, EntityIdx, float, float, float, void *,
    uint8_t (*)(struct rr_simulation *, EntityIdx, EntityIdx, void *));

uint8_t no_filter(struct rr_simulation *, EntityIdx, EntityIdx, void *);