#pragma once

#include <stdint.h>

typedef uint16_t EntityIdx;
typedef uint32_t EntityHash;

#define RR_MAX_ENTITY_COUNT (16384)
#define RR_NULL_ENTITY (0)
#define RR_SQUAD_MEMBER_COUNT (4)

#define RR_MAX_CLIENT_COUNT (64)
#define RR_SQUAD_COUNT (RR_MAX_CLIENT_COUNT)
#define RR_MAX_COLLISION_COUNT (256)

struct rr_id_rarity_pair
{
    uint8_t id;
    uint8_t rarity;
};

#define RR_FOR_EACH_COMPONENT \
    XX(flower, 5) \
    XX(petal, 1) \
    XX(web, 8) \
    XX(arena, 9) \
    XX(player_info, 4) \
    XX(mob, 2) \
    XX(ai, 12) \
    XX(health, 3) \
    XX(drop, 10) \
    XX(centipede, 6) \
    XX(physical, 7) \
    XX(relations, 11) 