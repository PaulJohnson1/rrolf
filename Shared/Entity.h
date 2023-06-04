#pragma once

#include <stdint.h>

typedef uint16_t EntityIdx;
#define RR_MAX_ENTITY_COUNT (1024)
#define RR_NULL_ENTITY (0)
#define RR_MAX_COLLISION_COUNT (128)

#define RR_FOR_EACH_COMPONENT \
    XX(flower, 7) \
    XX(drop, 10) \
    XX(mob, 8) \
    XX(player_info, 3) \
    XX(projectile, 6) \
    XX(physical, 5) \
    XX(arena, 4) \
    XX(centipede, 9) \
    XX(health, 2) \
    XX(ai, 12) \
    XX(petal, 1) \
    XX(relations, 11) 