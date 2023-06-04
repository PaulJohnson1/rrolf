#pragma once

#include <stdint.h>

typedef uint16_t EntityIdx;
#define RR_MAX_ENTITY_COUNT (1024)
#define RR_NULL_ENTITY (0)
#define RR_MAX_COLLISION_COUNT (128)

#define RR_FOR_EACH_COMPONENT \
    XX(player_info, 3) \
    XX(petal, 5) \
    XX(arena, 10) \
    XX(projectile, 4) \
    XX(centipede, 1) \
    XX(ai, 6) \
    XX(relations, 8) \
    XX(mob, 9) \
    XX(health, 11) \
    XX(flower, 7) \
    XX(physical, 12) \
    XX(drop, 2) 