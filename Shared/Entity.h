#pragma once

#include <stdint.h>

typedef uint16_t EntityIdx;
#define RR_MAX_ENTITY_COUNT (3000)
#define RR_NULL_ENTITY (0)
#define RR_MAX_COLLISION_COUNT (512)

#define RR_SQUAD_MEMBER_COUNT 8

#define RR_FOR_EACH_COMPONENT                                                  \
    XX(centipede, 6) \
    XX(drop, 10) \
    XX(projectile, 4) \
    XX(physical, 11) \
    XX(relations, 3) \
    XX(flower, 2) \
    XX(ai, 8) \
    XX(mob, 7) \
    XX(web, 12) \
    XX(player_info, 1) \
    XX(petal, 13) \
    XX(arena, 9) \
    XX(health, 5) 