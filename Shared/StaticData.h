#pragma once

#include <stdint.h>

#include <Shared/Entity.h>

enum rr_animation_type
{
    rr_animation_type_default = 0,
    rr_animation_type_lightningbolt = 1,
    rr_animation_type_damagenumber = 2,
};

enum rr_serverbound_packet_header
{
    rr_serverbound_input = 0,
    rr_serverbound_petal_switch = 1,
    rr_serverbound_squad_join = 2,
    rr_serverbound_squad_ready = 3,
    rr_serverbound_squad_update = 4,
    rr_serverbound_private_update = 5,
    rr_serverbound_squad_kick = 6,
    rr_serverbound_petals_craft = 7
};

enum rr_clientbound_packet_header
{
    rr_clientbound_update = 0,
    rr_clientbound_animation_update = 1,
    rr_clientbound_squad_update = 2,
    rr_clientbound_squad_fail = 3,
    rr_clientbound_squad_leave = 4,
    rr_clientbound_account_result = 5,
    rr_clientbound_craft_result = 6
};

#define RR_SLOT_COUNT_FROM_LEVEL(level) (level < 100 ? 5 + (level) / 20 : 10)
#define RR_PLAYER_SPEED (3.3)

enum rr_biome_id
{
    rr_biome_id_hell_creek,
    rr_biome_id_garden,
    rr_biome_id_beehive,
    rr_biome_id_max
};

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
    rr_petal_id_fossil,
    rr_petal_id_stinger,
    rr_petal_id_light,
    rr_petal_id_shell,
    rr_petal_id_peas, 
    rr_petal_id_leaf,
    rr_petal_id_egg,
    rr_petal_id_magnet,
    rr_petal_id_uranium,
    rr_petal_id_feather,
    rr_petal_id_azalea,
    rr_petal_id_bone,
    rr_petal_id_web,
    rr_petal_id_seed,
    rr_petal_id_gravel,
    rr_petal_id_club,
    rr_petal_id_crest,
    rr_petal_id_droplet,
    rr_petal_id_beak,
    rr_petal_id_lightning,
    rr_petal_id_third_eye,
    rr_petal_id_mandible,
    rr_petal_id_wax,
    rr_petal_id_sand,

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

    rr_mob_id_ant,
    rr_mob_id_hornet,
    rr_mob_id_dragonfly,
    rr_mob_id_honeybee,
    rr_mob_id_beehive,
    rr_mob_id_spider,
    rr_mob_id_house_centipede,
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
#ifdef RR_SERVER
    uint8_t (*spawn_function)();
    uint32_t grid_points;
    uint8_t player_count;
    uint8_t difficulty;
#endif
    uint8_t value;
};

struct rr_maze_declaration
{
    uint32_t maze_dim;
    float grid_size;
    struct rr_maze_grid *maze;
};

#define RR_DECLARE_MAZE(name, size) \
extern uint8_t RR_MAZE_TEMPLATE_##name[size/2][size/2]; \
extern struct rr_maze_grid RR_MAZE_##name[size][size];

RR_DECLARE_MAZE(HELL_CREEK, 56)
RR_DECLARE_MAZE(BURROW, 4)

extern struct rr_maze_declaration RR_MAZES[rr_biome_id_max];

extern uint8_t RR_GLOBAL_BIOME;

#ifdef RR_SERVER 
extern double RR_CRAFT_CHANCES[rr_rarity_id_max - 1];
#endif

void rr_static_data_init();

double xp_to_reach_level(uint32_t);
uint32_t level_from_xp(double);