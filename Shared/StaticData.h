#pragma once

#include <stdint.h>

#include <Shared/Entity.h>


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

#define RR_LEVELS_PER_EXTRA_SLOT (20)
#define RR_BIOME_COUNT (2)
#define RR_MAZE_DIM (42)
#define RR_BURROW_MAZE_DIM (4)
#define RR_MAZE_GRID_SIZE (1536)
#define RR_BURRON_GRID_SIZE (384)
#define RR_ARENA_LENGTH (RR_MAZE_GRID_SIZE * RR_MAZE_DIM)
#define RR_PLAYER_SPEED (4)

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
    rr_petal_id_pellet,
    rr_petal_id_fossil, //remove + replace
    rr_petal_id_stinger,
    rr_petal_id_light,
    rr_petal_id_shell,
    rr_petal_id_peas, //remove + replace
    rr_petal_id_leaf,
    rr_petal_id_egg,
    rr_petal_id_magnet,
    rr_petal_id_uranium, //remove
    rr_petal_id_feather,
    rr_petal_id_azalea,
    rr_petal_id_bone,
    rr_petal_id_web,
    rr_petal_id_seed,
    rr_petal_id_gravel,
    rr_petal_id_club,
    rr_petal_id_crest,
    rr_petal_id_droplet, //remove + replace
    rr_petal_id_beak,
    rr_petal_id_lightning,
    rr_petal_id_third_eye,
    rr_petal_id_mandible,
    rr_petal_id_wax,
    /*
    rr_petal_id_kelp,
    rr_petal_id_fish_egg,
    rr_petal_id_scales,
    */
    rr_petal_id_max
};

enum rr_mob_id
{
    rr_mob_id_triceratops,
    rr_mob_id_trex,
    rr_mob_id_fern,
    rr_mob_id_tree,
    rr_mob_id_pteranodon,
    rr_mob_id_dakotaraptor,
    rr_mob_id_pachycephalosaurus,
    rr_mob_id_ornithomimus,
    rr_mob_id_ankylosaurus,
    rr_mob_id_meteor,
    rr_mob_id_quetzalcoatlus,
    rr_mob_id_edmontosaurus,
    /*
    rr_mob_id_king_mackarel,
    rr_mob_id_sea_snail,
    rr_mob_id_seagull,
    rr_mob_id_kelp,
    */
    rr_mob_id_ant,
    rr_mob_id_hornet,
    rr_mob_id_dragonfly,
    rr_mob_id_honeybee,
    rr_mob_id_beehive,
    rr_mob_id_max
};

struct rr_loot_data
{
    uint8_t id;
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
extern double RR_GARDEN_MOB_ID_RARITY_COEFFICIENTS[rr_mob_id_max];


extern uint32_t RR_RARITY_COLORS[rr_rarity_id_max];
extern char const *RR_RARITY_NAMES[rr_rarity_id_max];

struct rr_maze_grid
{
    uint8_t value : 4;
#ifdef RR_SERVER
    uint8_t is_special : 1;
    uint8_t mob_count;
    uint8_t difficulty;
    uint8_t special_id;
#endif
};

#define RR_DECLARE_MAZE(name, size) \
extern uint8_t RR_MAZE_TEMPLATE_##name[size/2][size/2]; \
extern struct rr_maze_grid RR_MAZE_##name[size][size];

RR_DECLARE_MAZE(HELL_CREEK, RR_MAZE_DIM)
RR_DECLARE_MAZE(BURROW, RR_BURROW_MAZE_DIM)


void rr_static_data_init();

double xp_to_reach_level(uint32_t);