#pragma once

#include <stdint.h>

typedef uint16_t EntityIdx;
#define RR_MAX_ENTITY_COUNT (1024)
#define RR_NULL_ENTITY (0)
#define RR_MAX_COLLISION_COUNT (128)

#define RR_FOR_EACH_COMPONENT \
    XX(petal, 1) \
    XX(ai, 2) \
    XX(drop, 3) \
    XX(arena, 4) \
    XX(relations, 5) \
    XX(health, 6) \
    XX(flower, 7) \
    XX(physical, 8) \
    XX(mob, 9) \
    XX(projectile, 10) \
    XX(player_info, 11) \
    XX(centipede, 12)