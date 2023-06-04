#pragma once

#include <stdint.h>

typedef uint16_t EntityIdx;
#define RR_MAX_ENTITY_COUNT (1024)
#define RR_NULL_ENTITY (0)
#define RR_MAX_COLLISION_COUNT (128)

#define RR_FOR_EACH_COMPONENT \
    XX(player_info, 6) \
    XX(health, 3) \
    XX(projectile, 5) \
    XX(centipede, 9) \
    XX(arena, 11) \
    XX(petal, 1) \
    XX(flower, 12) \
    XX(physical, 4) \
    XX(drop, 2) \
    XX(relations, 8) \
    XX(mob, 7) \
    XX(ai, 10) 