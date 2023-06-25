#pragma once

#include <stdint.h>

typedef uint16_t EntityIdx;
#define RR_MAX_ENTITY_COUNT (1024)
#define RR_NULL_ENTITY (0)
#define RR_MAX_COLLISION_COUNT (128)

#define RR_FOR_EACH_COMPONENT \
    XX(centipede, 8) \
    XX(drop, 10) \
    XX(projectile, 9) \
    XX(player_info, 12) \
    XX(ai, 5) \
    XX(physical, 7) \
    XX(health, 6) \
    XX(petal, 11) \
    XX(flower, 4) \
    XX(relations, 3) \
    XX(arena, 1) \
    XX(mob, 2) 