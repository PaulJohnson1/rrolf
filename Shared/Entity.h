#pragma once

#include <stdint.h>

typedef uint16_t EntityIdx;
#define RR_MAX_ENTITY_COUNT (1024)
#define RR_NULL_ENTITY (0)
#define RR_MAX_COLLISION_COUNT (128)

#define RR_FOR_EACH_COMPONENT \
    XX(petal, 4) \
    XX(ai, 12) \
    XX(centipede, 1) \
    XX(drop, 2) \
    XX(arena, 10) \
    XX(relations, 9) \
    XX(health, 6) \
    XX(flower, 8) \
    XX(physical, 7) \
    XX(mob, 11) \
    XX(projectile, 5) \
    XX(player_info, 3) 