#pragma once

#include <stdint.h>

typedef uint16_t EntityIdx;
// must be multiple of 8 and not 0
#define RR_MAX_ENTITY_COUNT (512)
#define RR_NULL_ENTITY (0)

#define RR_FOR_EACH_COMPONENT \
    XX(physical, 1);          \
    XX(player_info, 2);       \
    XX(flower, 3)             \
    XX(arena, 4)              \
    XX(petal, 5)
