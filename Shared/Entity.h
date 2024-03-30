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

typedef uint16_t EntityIdx;
typedef uint32_t EntityHash;

#define RR_MAX_ENTITY_COUNT (16384)
#define RR_NULL_ENTITY (0)
#define RR_SQUAD_MEMBER_COUNT (4)

#define RR_MAX_CLIENT_COUNT (64)
#define RR_SQUAD_COUNT (RR_MAX_CLIENT_COUNT)
#define RR_MAX_COLLISION_COUNT (256)

struct rr_id_rarity_pair
{
    uint8_t id;
    uint8_t rarity;
};

#define RR_FOR_EACH_COMPONENT                                                  \
    XX(ai, 7)                                                                  \
    XX(flower, 5)                                                              \
    XX(centipede, 2)                                                           \
    XX(web, 4)                                                                 \
    XX(mob, 11)                                                                \
    XX(health, 10)                                                             \
    XX(arena, 12)                                                              \
    XX(relations, 6)                                                           \
    XX(physical, 3)                                                            \
    XX(drop, 9)                                                                \
    XX(player_info, 1)                                                         \
    XX(petal, 8)