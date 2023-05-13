#pragma once

#include <stdint.h>

typedef uint16_t EntityIdx;
// most be multiple of 8 and not 0
#define MAX_ENTITY_COUNT (1024)
#define NULL_ENTITY (0)


#define FOR_EACH_COMPONENT \
    XX(physical, 0)
