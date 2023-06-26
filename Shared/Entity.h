#pragma once

#include <stdint.h>

typedef uint16_t EntityIdx;
#define RR_MAX_ENTITY_COUNT (1024)
#define RR_NULL_ENTITY (0)
#define RR_MAX_COLLISION_COUNT (128)

#define RR_FOR_EACH_COMPONENT \
    XX(flower, 4) \
    XX(player_info, 12) \
    XX(centipede, 2) \
    XX(mob, 9) \
    XX(drop, 5) \
    XX(health, 7) \
    XX(projectile, 3) \
    XX(physical, 10) \
    XX(ai, 1) \
    XX(petal, 6) \
    XX(relations, 11) \
    XX(arena, 8) 