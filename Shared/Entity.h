#pragma once

#include <stdint.h>

typedef uint16_t EntityIdx;
#define RR_ARENA_RADIUS (2250)
#define RR_MAX_ENTITY_COUNT (8192)
#define RR_NULL_ENTITY (0)
#define RR_MAX_COLLISION_COUNT (1024)
#define RR_SQUAD_MEMBER_COUNT (8)

#define RR_FOR_EACH_COMPONENT                                                  \
    XX(projectile, 7) \
    XX(petal, 5) \
    XX(physical, 8) \
    XX(flower, 10) \
    XX(health, 13) \
    XX(web, 1) \
    XX(relations, 9) \
    XX(centipede, 2) \
    XX(mob, 11) \
    XX(drop, 3) \
    XX(player_info, 4) \
    XX(ai, 12) \
    XX(arena, 6) 