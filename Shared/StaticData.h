#pragma once

#include <stdint.h>

enum rr_rarity_id
{
    rr_rarity_id_common,
    rr_rarity_id_unusual,
    rr_rarity_id_rare,
    rr_rarity_id_epic,
    rr_rarity_id_legendary,
    rr_rarity_id_mythic,
    rr_rarity_id_ultra,
    rr_rarity_id_max
};

enum rr_petal_id
{
    rr_petal_id_no_petal,
    rr_petal_id_basic,
    rr_petal_id_light,
    rr_petal_id_rock,
    rr_petal_id_stinger,
    rr_petal_id_faster,
    rr_petal_id_missile,
    rr_petal_id_peas,
    rr_petal_id_leaf,
    rr_petal_id_egg,
    rr_petal_id_magnet,
    rr_petal_id_uranium,
    rr_petal_id_max
};

enum rr_mob_id
{
    rr_mob_id_triceratops,
    rr_mob_id_trex,
    rr_mob_id_stump,
    rr_mob_id_spinosaurus_head,
    rr_mob_id_spinosaurus_body,
    rr_mob_id_pteranodon,
    rr_mob_id_dakotaraptor,

    rr_mob_id_max
};

struct rr_loot_data
{
    enum rr_petal_id id;
    float loot_table[rr_rarity_id_max][rr_rarity_id_max + 1];
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
    uint8_t min_rarity; //minimum rarity petal can spawn at
    float damage;
    float health;
    float clump_radius;
    uint32_t cooldown;
    uint32_t secondary_cooldown; //for stuff like projectiles
    uint8_t count[rr_rarity_id_max];
};

struct rr_mob_rarity_scale
{
    float health;
    float damage;
    float radius;
};

extern struct rr_petal_data RR_PETAL_DATA[rr_petal_id_max];
extern char const *RR_PETAL_NAMES[rr_petal_id_max];
extern char const *RR_PETAL_DESCRIPTIONS[rr_petal_id_max];
extern struct rr_mob_data RR_MOB_DATA[rr_mob_id_max];
extern char const *RR_MOB_NAMES[rr_mob_id_max];
extern struct rr_mob_rarity_scale RR_MOB_RARITY_SCALING[rr_rarity_id_max];
extern float RR_PETAL_RARITY_SCALE[rr_rarity_id_max];
extern double RR_DROP_RARITY_COEFFICIENTS[rr_rarity_id_max + 1];
extern double RR_MOB_WAVE_RARITY_COEFFICIENTS[rr_rarity_id_max + 1];

extern uint32_t RR_RARITY_COLORS[rr_rarity_id_max];
extern char const *RR_RARITY_NAMES[rr_rarity_id_max];

void rr_static_data_init();