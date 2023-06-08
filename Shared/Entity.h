#pragma once

#include <stdint.h>

typedef uint16_t EntityIdx;
#define RR_MAX_ENTITY_COUNT (1024)
#define RR_NULL_ENTITY (0)
#define RR_MAX_COLLISION_COUNT (128)

#define RR_FOR_EACH_COMPONENT \
    XX(arena, 9) \
    XX(ai, 11) \
    XX(relations, 5) \
    XX(petal, 12) \
    XX(centipede, 3) \
    XX(physical, 7) \
    XX(projectile, 6) \
    XX(mob, 10) \
    XX(flower, 8) \
    XX(drop, 2) \
    XX(player_info, 1) \
    XX(health, 4) 