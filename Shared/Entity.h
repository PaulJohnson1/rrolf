#pragma once

#include <stdint.h>

typedef uint16_t EntityIdx;
#define RR_MAX_ENTITY_COUNT (1536)
#define RR_NULL_ENTITY (0)
#define RR_MAX_COLLISION_COUNT (128)

#define RR_FOR_EACH_COMPONENT                                                  \
    XX(projectile, 4)                                                          \
    XX(health, 2)                                                              \
    XX(flower, 1)                                                              \
    XX(relations, 5)                                                           \
    XX(player_info, 3)                                                         \
    XX(petal, 8)                                                               \
    XX(drop, 11)                                                               \
    XX(mob, 6)                                                                 \
    XX(ai, 12)                                                                 \
    XX(physical, 10)                                                           \
    XX(centipede, 7)                                                           \
    XX(arena, 9)                                                               \
    XX(web, 13)