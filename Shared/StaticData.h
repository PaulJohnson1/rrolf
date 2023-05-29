#pragma once

#include <stdint.h>

enum rr_rarity_id
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
    rr_petal_id_stinger,
    rr_petal_id_faster,
    rr_petal_id_missile,
    rr_petal_id_peas,
    rr_petal_id_max
};

enum rr_mob_id
{
    rr_mob_id_baby_ant,
    rr_mob_id_worker_ant,
    rr_mob_id_centipede_head,
    rr_mob_id_centipede_body,
    rr_mob_id_max
};

struct rr_loot_data
{
    enum rr_petal_id id;
    float loot_table[rr_rarity_max][rr_rarity_max + 1];
};

struct rr_mob_data
{
    uint8_t id;
    float health;
    float damage;
    float radius;
    struct rr_loot_data loot[4];
};

struct rr_petal_data
{
    uint8_t id;
    float damage;
    float health;
    float clump_radius;
    uint32_t cooldown;
    uint8_t count[rr_rarity_max];
};

struct rr_mob_rarity_scale
{
    float health;
    float damage;
    float radius;
};

extern struct rr_petal_data RR_PETAL_DATA[rr_petal_id_max];
extern struct rr_mob_data RR_MOB_DATA[rr_mob_id_max];
extern struct rr_mob_rarity_scale RR_MOB_RARITY_SCALING[rr_rarity_max];
extern float RR_DROP_RARITY_COEFFICIENTS[rr_rarity_max + 1];

extern uint32_t RR_RARITY_COLORS[rr_rarity_max];
extern char const *RR_RARITY_NAMES[rr_rarity_max];

void rr_static_data_init();