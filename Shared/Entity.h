#pragma once

#include <stdint.h>

typedef uint16_t EntityIdx;
#define RR_MAX_ENTITY_COUNT (1024)
#define RR_NULL_ENTITY (0)
#define RR_MAX_COLLISION_COUNT (128)

#define RR_FOR_EACH_COMPONENT \
    XX(mob, 12) \
    XX(centipede, 4) \
    XX(player_info, 5) \
    XX(projectile, 1) \
    XX(physical, 8) \
    XX(flower, 6) \
    XX(health, 7) \
    XX(relations, 11) \
    XX(petal, 2) \
    XX(arena, 10) \
    XX(drop, 3) \
    XX(ai, 9) 