#pragma once

#include <stdint.h>

typedef uint16_t EntityIdx;
#define RR_MAX_ENTITY_COUNT (1024)
#define RR_NULL_ENTITY (0)
#define RR_MAX_COLLISION_COUNT (128)

#define RR_FOR_EACH_COMPONENT \
    XX(relations, 12) \
    XX(physical, 2) \
    XX(projectile, 7) \
    XX(health, 9) \
    XX(drop, 5) \
    XX(petal, 10) \
    XX(arena, 1) \
    XX(flower, 8) \
    XX(centipede, 11) \
    XX(ai, 6) \
    XX(mob, 3) \
    XX(player_info, 4) 