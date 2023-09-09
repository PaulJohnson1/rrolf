#pragma once

#include <stdint.h>

typedef uint16_t EntityIdx;
#define RR_MAX_ENTITY_COUNT (16384)
#define RR_NULL_ENTITY (0)
#define RR_SQUAD_MEMBER_COUNT (4)
#ifdef RR_SERVER
#define RR_MAX_CLIENT_COUNT (64)
#define RR_SQUAD_COUNT (RR_MAX_CLIENT_COUNT)
#define RR_LOOT_SHARE_COUNT (4)
#define RR_MAX_COLLISION_COUNT (512)
#endif

struct rr_id_rarity_pair
{
    uint8_t id;
    uint8_t rarity;
};

#define RR_FOR_EACH_COMPONENT \
    XX(player_info, 3) \
    XX(petal, 11) \
    XX(web, 8) \
    XX(physical, 2) \
    XX(health, 9) \
    XX(drop, 10) \
    XX(centipede, 7) \
    XX(projectile, 12) \
    XX(arena, 6) \
    XX(mob, 1) \
    XX(ai, 13) \
    XX(flower, 4) \
    XX(relations, 5) 