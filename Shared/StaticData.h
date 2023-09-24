#pragma once

#include <stdint.h>

#define RR_SERVERBOUND_INPUT 0
#define RR_SERVERBOUND_PETAL_SWITCH 1
#define RR_SERVERBOUND_SQUAD_JOIN 2
#define RR_SERVERBOUND_SQUAD_READY 3
#define RR_SERVERBOUND_LOADOUT_UPDATE 4
#define RR_SERVERBOUND_NICKNAME_UPDATE 5
#define RR_SERVERBOUND_PRIVATE_UPDATE 6

#define RR_CLIENTBOUND_UPDATE 1
#define RR_CLIENTBOUND_SQUAD_UPDATE 2
#define RR_CLIENTBOUND_SQUAD_FAIL 3


#define RR_LEVELS_PER_EXTRA_SLOT 20
#define RR_BIOME_COUNT 2

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
    rr_petal_id_leaf,
    rr_petal_id_stinger,
    rr_petal_id_missile,
    rr_petal_id_faster,
    rr_petal_id_web,
    rr_petal_id_antennae,
    rr_petal_id_peas,
    rr_petal_id_rose,
    rr_petal_id_iris,
    rr_petal_id_grapes,
    rr_petal_id_oranges,
    rr_petal_id_max
};

enum rr_mob_id
{
    rr_mob_id_baby_ant,
    rr_mob_id_worker_ant,
    rr_mob_id_soldier_ant,
    rr_mob_id_bee,
    rr_mob_id_hornet,
    rr_mob_id_spider,
    rr_mob_id_centipede,
    rr_mob_id_ladybug,
    rr_mob_id_evil_centipede,
    rr_mob_id_max
};

struct rr_loot_data
{
    enum rr_petal_id id;
    float seed;
};

struct rr_mob_data
{
    uint8_t id;
    uint8_t min_rarity;
    float health;
    float damage;
    float radius;
    struct rr_loot_data loot[4];
};

struct rr_petal_data
{
    uint8_t id;
    uint8_t min_rarity; // minimum rarity petal can spawn at
    float damage;
    float health;
    float clump_radius;
    uint32_t cooldown;
    uint32_t secondary_cooldown; // for stuff like projectiles
    uint8_t count[rr_rarity_id_max];
};

struct rr_mob_rarity_scale
{
    float health;
    float damage;
    float radius;
};

struct rr_petal_rarity_scale
{
    float health;
    float damage;
};

extern struct rr_petal_data RR_PETAL_DATA[rr_petal_id_max];
extern char const *RR_PETAL_NAMES[rr_petal_id_max];
extern char const *RR_PETAL_DESCRIPTIONS[rr_petal_id_max];
extern struct rr_mob_data RR_MOB_DATA[rr_mob_id_max];
extern char const *RR_MOB_NAMES[rr_mob_id_max];
extern struct rr_mob_rarity_scale RR_MOB_RARITY_SCALING[rr_rarity_id_max];
extern struct rr_petal_rarity_scale RR_PETAL_RARITY_SCALE[rr_rarity_id_max];
extern double RR_DROP_RARITY_COEFFICIENTS[rr_rarity_id_ultra + 2];
extern double RR_MOB_LOOT_RARITY_COEFFICIENTS[rr_rarity_id_ultra + 1];
extern double RR_MOB_WAVE_RARITY_COEFFICIENTS[rr_rarity_id_ultra + 2];

extern uint32_t RR_MOB_DIFFICULTY_COEFFICIENTS[rr_mob_id_max];
extern double RR_HELL_CREEK_MOB_ID_RARITY_COEFFICIENTS[rr_mob_id_max];
extern double RR_OCEAN_MOB_ID_RARITY_COEFFICIENTS[rr_mob_id_max];

extern uint32_t RR_RARITY_COLORS[rr_rarity_id_max];
extern char const *RR_RARITY_NAMES[rr_rarity_id_max];

void rr_static_data_init();

double xp_to_reach_level(uint32_t);