#pragma once

#include <stdint.h>

enum rr_rarity
{
    rr_rarity_common,
    rr_rarity_unusual,
    rr_rarity_rare,
    rr_rarity_epic,
    rr_rarity_max
};

enum rr_petal_id
{
    rr_petal_id_no_petal,
    rr_petal_id_basic,
    rr_petal_id_light,
    rr_petal_id_max
};

enum rr_mob_id
{
    rr_mob_id_baby_ant,
    rr_mob_id_max
};

// TODO: mob data
// will do later (not yet)

// struct rr_mob_data
// {
//     uint8_t id;
//     float health;
//     float damage;
//     float radius;
// };

struct rr_petal_data
{
    uint8_t id;
    float health;
    float damage;
    uint32_t cooldown;
};

extern struct rr_petal_data PETAL_DATA[rr_petal_id_max];
extern float rr_mob_rarity_scaling[rr_rarity_max];
