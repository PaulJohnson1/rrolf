#pragma once

#include <stdint.h>

typedef uint16_t EntityIdx;
#define RR_MAX_ENTITY_COUNT (1024)
#define RR_NULL_ENTITY (0)
#define RR_MAX_COLLISION_COUNT (128)

#define RR_FOR_EACH_COMPONENT \
    XX(arena, 7) \
    XX(relations, 11) \
    XX(ai, 4) \
    XX(petal, 12) \
    XX(mob, 6) \
    XX(health, 10) \
    XX(drop, 3) \
    XX(player_info, 9) \
    XX(flower, 1) \
    XX(physical, 5) \
    XX(centipede, 8) \
    XX(projectile, 2) 