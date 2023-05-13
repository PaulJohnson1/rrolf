#pragma once

#include <stdint.h>

typedef uint16_t EntityIdx;
#define MAX_ENTITY_COUNT (768)
#define NULL_ENTITY (0)

#define FOR_EACH_COMPONENT \
    XX(Physical, 0)
