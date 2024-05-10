// Copyright (C) 2024  Paul Johnson

// This program is free software: you can redistribute it and/or modify
// it under the terms of the GNU Affero General Public License as
// published by the Free Software Foundation, either version 3 of the
// License, or (at your option) any later version.

// This program is distributed in the hope that it will be useful,
// but WITHOUT ANY WARRANTY; without even the implied warranty of
// MERCHANTABILITY or FITNESS FOR A PARTICULAR PURPOSE.  See the
// GNU Affero General Public License for more details.

// You should have received a copy of the GNU Affero General Public License
// along with this program.  If not, see <https://www.gnu.org/licenses/>.

#pragma once

#include <stdint.h>

#include <Shared/Entity.h>

enum rr_animation_type
{
    rr_animation_type_default = 0,
    rr_animation_type_lightningbolt = 1,
    rr_animation_type_damagenumber = 2,
    rr_animation_type_chat = 3,
};

enum rr_serverbound_packet_header
{
    rr_serverbound_input,
    rr_serverbound_petal_switch,
    rr_serverbound_squad_join,
    rr_serverbound_squad_ready,
    rr_serverbound_squad_update,
    rr_serverbound_private_update,
    rr_serverbound_squad_kick,
    rr_serverbound_petals_craft,
    rr_serverbound_chat,
    rr_serverbound_dev_cheat,
};

enum rr_clientbound_packet_header
{
    rr_clientbound_update,
    rr_clientbound_animation_update,
    rr_clientbound_squad_dump,
    rr_clientbound_squad_fail,
    rr_clientbound_squad_leave,
    rr_clientbound_account_result,
    rr_clientbound_craft_result
};

enum rr_dev_cheat_type
{
    rr_dev_cheat_summon_mob,
    rr_dev_cheat_kill_mobs,
    rr_dev_cheat_flags,
    rr_dev_cheat_speed_percent,
    rr_dev_cheat_fov_percent
};

#define RR_SLOT_COUNT_FROM_LEVEL(level) (level < 100 ? 5 + (level) / 20 : 10)
#define RR_PLAYER_SPEED (4.0f)

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
    rr_rarity_id_exotic,
    rr_rarity_id_ultimate,
    rr_rarity_id_max
};

enum rr_petal_id
{
    rr_petal_id_none,      // 0
    rr_petal_id_basic,     // 1
    rr_petal_id_pellet,    // 2
    rr_petal_id_fossil,    // 3
    rr_petal_id_stinger,   // 4
    rr_petal_id_berry,     // 5
    rr_petal_id_shell,     // 6
    rr_petal_id_peas,      // 7
    rr_petal_id_leaf,      // 8
    rr_petal_id_egg,       // 9
    rr_petal_id_magnet,    // 10
    rr_petal_id_uranium,   // 11
    rr_petal_id_feather,   // 12
    rr_petal_id_azalea,    // 13
    rr_petal_id_bone,      // 14
    rr_petal_id_web,       // 15
    rr_petal_id_seed,      // 16
    rr_petal_id_gravel,    // 17
    rr_petal_id_club,      // 18
    rr_petal_id_crest,     // 19
    rr_petal_id_droplet,   // 20
    rr_petal_id_beak,      // 21
    rr_petal_id_lightning, // 22
    rr_petal_id_third_eye, // 23

    rr_petal_id_mandible,  // 24
    rr_petal_id_wax,       // 25
    rr_petal_id_sand,      // 26
    rr_petal_id_mint,      // 27

    rr_petal_id_max,       // 28
};

enum rr_mob_id
{
    rr_mob_id_triceratops,        // 0
    rr_mob_id_trex,               // 1
    rr_mob_id_fern,               // 2
    rr_mob_id_tree,               // 3
    rr_mob_id_pteranodon,         // 4
    rr_mob_id_dakotaraptor,       // 5
    rr_mob_id_pachycephalosaurus, // 6
    rr_mob_id_ornithomimus,       // 7
    rr_mob_id_ankylosaurus,       // 8
    rr_mob_id_meteor,             // 9
    rr_mob_id_quetzalcoatlus,     // 10
    rr_mob_id_edmontosaurus,      // 11

    rr_mob_id_ant,                // 12
    rr_mob_id_hornet,             // 13
    rr_mob_id_dragonfly,          // 14
    rr_mob_id_honeybee,           // 15
    rr_mob_id_beehive,            // 16
    rr_mob_id_spider,             // 17
    rr_mob_id_house_centipede,    // 18
    rr_mob_id_lanternfly,         // 19

    rr_mob_id_max,                // 20
};

struct rr_petal_base_stat_scale
{
    float health;
    float damage;
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
    uint8_t max_rarity;
    float health;
    float damage;
    float radius;
    struct rr_loot_data loot[4];
};

struct rr_petal_data
{
    uint8_t id;
    uint8_t min_rarity; // minimum rarity petal can spawn at
    struct rr_petal_base_stat_scale const *scale;
    float damage;
    float health;
    float clump_radius;
    uint32_t cooldown;
    uint32_t secondary_cooldown; // for stuff like projectiles
    uint8_t count[rr_rarity_id_max];
};

struct rr_petal_rarity_scale
{
    float heal;
    float seed_cooldown;
    float web_radius;
    float bone_reduction;
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
extern struct rr_petal_rarity_scale RR_PETAL_RARITY_SCALE[rr_rarity_id_max];
extern double RR_MOB_LOOT_RARITY_COEFFICIENTS[rr_rarity_id_max];
extern double RR_DROP_RARITY_COEFFICIENTS[rr_rarity_id_exotic + 2];
extern double RR_MOB_WAVE_RARITY_COEFFICIENTS[rr_rarity_id_max + 1];

extern uint32_t RR_MOB_DIFFICULTY_COEFFICIENTS[rr_mob_id_max];
extern double RR_HELL_CREEK_MOB_ID_RARITY_COEFFICIENTS[rr_mob_id_max];
extern double RR_GARDEN_MOB_ID_RARITY_COEFFICIENTS[rr_mob_id_max];

extern uint32_t RR_RARITY_COLORS[rr_rarity_id_max];
extern char const *RR_RARITY_NAMES[rr_rarity_id_max];

struct rr_maze_grid
{
#ifdef RR_SERVER
    uint8_t (*spawn_function)();
    float difficulty;
    uint32_t spawn_timer;
    uint32_t player_count;
    uint32_t grid_points;
    float local_difficulty;
    float overload_factor;
#endif
    uint8_t value;
};

struct rr_spawn_zone
{
    float x;
    float y;
};

struct rr_maze_declaration
{
    uint32_t maze_dim;
    float grid_size;
    struct rr_maze_grid *maze;
    struct rr_spawn_zone spawn_zones[4];
};

#define RR_DECLARE_MAZE(name, size)                                            \
    extern uint8_t RR_MAZE_TEMPLATE_##name[size / 2][size / 2];                \
    extern struct rr_maze_grid RR_MAZE_##name[size][size];

// RR_DECLARE_MAZE(HELL_CREEK, 54)
RR_DECLARE_MAZE(HELL_CREEK, 80)
RR_DECLARE_MAZE(BURROW, 4)

extern struct rr_maze_declaration RR_MAZES[rr_biome_id_max];

extern uint8_t RR_GLOBAL_BIOME;

extern double RR_BASE_CRAFT_CHANCES[rr_rarity_id_max - 1];
extern double RR_CRAFT_CHANCES[rr_rarity_id_max - 1];

void rr_static_data_init();

double xp_to_reach_level(uint32_t);
uint32_t level_from_xp(double);