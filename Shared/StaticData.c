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

#include <Shared/StaticData.h>

#include <math.h>
#include <stdio.h>

#include <Shared/Utilities.h>

// clang-format off
struct rr_petal_base_stat_scale const offensive[rr_rarity_id_max] = {
    {1.0, 1.0},
    {1.7, 2.0},
    {2.9, 4.0},
    {5.0, 8.0},
    {8.5,  16},
    {14.5, 48},
    {24.6,144},
    {42.0,432}
};

struct rr_petal_base_stat_scale const defensive[rr_rarity_id_max] = {
    {1.0, 1.0},
    {2.0, 1.7},
    {4.0, 2.9},
    {8.0, 5.0},
    {16,  8.5},
    {48, 14.5},
    {144,24.6},
    {432,42.0}
};

struct rr_petal_data RR_PETAL_DATA[rr_petal_id_max] = {
//   id                     min_rarity              scale        dmg      hp   clump   cd 2cd  count
    {rr_petal_id_none,      rr_rarity_id_common,    offensive,  0.0f,   0.0f,   0.0f,   0,  0, {0,0,0,0,0,0,0,0}},
    {rr_petal_id_basic,     rr_rarity_id_common,    offensive, 10.0f,  15.0f,   0.0f,  50,  0, {1,1,1,1,1,1,1,1}},
    {rr_petal_id_pellet,    rr_rarity_id_common,    offensive, 12.5f,   5.0f,   0.0f,  20,  0, {1,2,2,3,3,5,6,6}},
    {rr_petal_id_fossil,    rr_rarity_id_common,    offensive,  8.0f,  50.0f,   0.0f, 100,  0, {1,1,1,1,1,1,1,1}},
    {rr_petal_id_stinger,   rr_rarity_id_common,    offensive, 50.0f,   3.0f,  10.0f, 125,  0, {1,1,1,1,1,3,5,5}},
    {rr_petal_id_berry,     rr_rarity_id_rare,      offensive,  7.0f,   5.0f,  12.0f,  20,  0, {1,1,1,1,1,2,3,3}},
    {rr_petal_id_shell,     rr_rarity_id_rare,      offensive, 30.0f,  16.0f,   0.0f,  70, 10, {1,1,1,1,1,2,3,3}},
    {rr_petal_id_peas,      rr_rarity_id_rare,      offensive, 22.0f,  12.0f,   8.0f,  13, 12, {4,4,4,4,4,4,5,5}},
    {rr_petal_id_leaf,      rr_rarity_id_unusual,   offensive,  9.0f,  8.75f,   8.0f,  38,  0, {1,1,1,1,1,2,2,2}},
    {rr_petal_id_egg,       rr_rarity_id_unusual,   defensive,  1.0f,  50.0f,   0.0f,  25, 75, {1,1,1,1,1,1,1,1}},
    {rr_petal_id_magnet,    rr_rarity_id_rare,      defensive,  2.0f,  15.0f,   0.0f,  38,  0, {1,1,1,1,1,1,1,1}},
    {rr_petal_id_uranium,   rr_rarity_id_rare,      offensive,  6.0f,  10.0f,   0.0f,  50, 25, {1,1,1,1,1,1,1,1}},
    {rr_petal_id_feather,   rr_rarity_id_common,    defensive,  5.0f,   3.0f,   0.0f,  35,  0, {1,1,1,1,1,1,1,1}},
    {rr_petal_id_azalea,    rr_rarity_id_common,    defensive,  5.0f,  10.0f,   0.0f,  50, 25, {1,1,1,1,1,1,1,1}},
    {rr_petal_id_bone,      rr_rarity_id_common,    defensive,  2.5f,  25.0f,   0.0f,  68,  0, {1,1,1,1,1,1,1,1}},
    {rr_petal_id_web,       rr_rarity_id_rare,      defensive,  5.0f,   5.0f,   0.0f,  50, 13, {1,1,1,1,1,1,1,1}},
    {rr_petal_id_seed,      rr_rarity_id_epic,      defensive,  1.0f,  25.0f,   0.0f,  63,  1, {1,1,1,1,1,1,1,1}},
    {rr_petal_id_gravel,    rr_rarity_id_unusual,   offensive, 11.0f,  20.0f,   0.0f,  20, 10, {1,2,2,2,3,3,4,4}},
    {rr_petal_id_club,      rr_rarity_id_common,    defensive,  8.0f, 600.0f,   0.0f, 250,  0, {1,1,1,1,1,1,1,1}},
    {rr_petal_id_crest,     rr_rarity_id_rare,      offensive,  0.0f,   0.0f,   0.0f,   0,  0, {0,0,0,0,0,0,0,0}},
    {rr_petal_id_droplet,   rr_rarity_id_common,    offensive, 15.0f,   8.0f,   0.0f,  37,  0, {1,1,1,1,1,1,1,1}},
    {rr_petal_id_beak,      rr_rarity_id_unusual,   offensive,  7.0f,   5.0f,   0.0f,  55,  0, {1,1,1,1,1,1,1,1}},
    {rr_petal_id_lightning, rr_rarity_id_unusual,   offensive, 11.0f,   2.0f,   0.0f,  63,  0, {1,1,1,1,1,1,1,1}},
    {rr_petal_id_third_eye, rr_rarity_id_legendary, offensive,  7.0f,   8.0f,   0.0f,  50,  0, {1,1,1,1,1,1,1,1}},
    {rr_petal_id_mandible,  rr_rarity_id_common,    offensive,  5.0f,  10.0f,   0.0f,  75,  0, {1,1,1,1,1,1,1,1}},
    {rr_petal_id_wax,       rr_rarity_id_unusual,   offensive, 10.0f,  10.0f,  10.0f,  38,  0, {2,2,2,2,2,2,2,2}},
    {rr_petal_id_sand,      rr_rarity_id_common,    offensive, 15.0f,  10.0f,  10.0f,  37,  0, {4,4,4,4,4,4,4,4}},
    {rr_petal_id_mint,      rr_rarity_id_unusual,   offensive,  5.0f,  10.0f,  10.0f,  50, 25, {1,1,1,1,1,1,1,1}},
};    

char const *RR_PETAL_NAMES[rr_petal_id_max] = {
    "Secret", "Petal",     "Pellet",    "Fossil",   "Stinger", "Berry",   "Shell",
    "Peas",   "Leaf",      "Egg",       "Magnet",   "Uranium", "Feather", "Azalea",
    "Bone",   "Web",       "Seed",      "Gravel",   "Club",    "Crest",   "Droplet",
    "Beak",   "Lightning", "Third Eye", "Mandible", "Wax",     "Sand",    "Mint",
};
    
char const *RR_PETAL_DESCRIPTIONS[rr_petal_id_max] = {
    0,
    "It's just a petal",
    "Not the strongest, but there's lots",
    "It came from a dino",
    "Ow, that hurts",
    "Gives your other petals more energy",
    "Poor snail",
    "Like peas in a pod",
    "Heals you gradually",
    "These goobers can't wait to hatch",
    "Increases loot pickup radius. Does not stack",
    "Does low damage to mobs in a big range",
    "It's so light it increases your movement speed. Stacks diminishingly",
    "It heals you",
    "Gives the player armor. Does not stack",
    "It slows everything down",
    "What does this one do",
    "Tiny rocks that stay on the ground and trip dinos",
    "Heavy and sturdy",
    "Increases your FOV. Does not stack",
    "This mysterious petal reverses your petal rotation",
    "Stuns mobs and prevents them from moving",
    "A stunning display",
    "Helps your petals see further. Does not stack",
    "Does more damage if target hp is below 50%",
    "Made by the bees",
    "Very fine",
    "Remember to feed your pets"
};

struct rr_mob_data RR_MOB_DATA[rr_mob_id_max] = {
//   id                                     min_rarity  max_rarity              hp dmg    rad  loot
    {rr_mob_id_triceratops,        rr_rarity_id_common, rr_rarity_id_ultimate,  45, 15, 30.0f, {{rr_petal_id_leaf,    0.15},{rr_petal_id_fossil,    0.05}}},
    {rr_mob_id_trex,               rr_rarity_id_common, rr_rarity_id_ultimate,  40, 25, 32.0f, {{rr_petal_id_stinger, 0.05},{rr_petal_id_egg,       0.05}}},
    {rr_mob_id_fern,               rr_rarity_id_common, rr_rarity_id_ultimate,  10,  5, 24.0f, {{rr_petal_id_leaf,     0.1},{rr_petal_id_azalea,    0.25}}},
    {rr_mob_id_tree,               rr_rarity_id_common, rr_rarity_id_ultimate, 100,  5, 64.0f, {{rr_petal_id_leaf,     0.5},{rr_petal_id_peas,      0.25},{rr_petal_id_seed,       0.05}}},
    {rr_mob_id_pteranodon,         rr_rarity_id_common, rr_rarity_id_ultimate,  40, 15, 20.0f, {{rr_petal_id_shell,  0.025},{rr_petal_id_beak,      0.15}}},
    {rr_mob_id_dakotaraptor,       rr_rarity_id_common, rr_rarity_id_ultimate,  35, 10, 25.0f, {{rr_petal_id_crest,    0.1},{rr_petal_id_feather,    0.1},{rr_petal_id_pellet,    0.05}}},
    {rr_mob_id_pachycephalosaurus, rr_rarity_id_common, rr_rarity_id_ultimate,  35, 20, 20.0f, {{rr_petal_id_fossil,   0.1},{rr_petal_id_berry,      0.1},{rr_petal_id_web,       0.05}}},
    {rr_mob_id_ornithomimus,       rr_rarity_id_common, rr_rarity_id_ultimate,  25, 10, 20.0f, {{rr_petal_id_feather,  0.1},{rr_petal_id_droplet,   0.05},{rr_petal_id_pellet,     0.1}}},
    {rr_mob_id_ankylosaurus,       rr_rarity_id_common, rr_rarity_id_ultimate,  50, 10, 30.0f, {{rr_petal_id_club,    0.15},{rr_petal_id_gravel,     0.1}}},
    {rr_mob_id_meteor,             rr_rarity_id_common, rr_rarity_id_ultimate, 100, 10, 32.0f, {{rr_petal_id_magnet,   0.5},/*{rr_petal_id_uranium, 0.25}*/}},
    {rr_mob_id_quetzalcoatlus,     rr_rarity_id_common, rr_rarity_id_ultimate,  65, 20, 28.0f, {{rr_petal_id_beak,    0.05},{rr_petal_id_fossil,     0.1},{rr_petal_id_lightning, 0.01}}},
    {rr_mob_id_edmontosaurus,      rr_rarity_id_common, rr_rarity_id_ultimate,  50, 15, 30.0f, {{rr_petal_id_bone,   0.005},{rr_petal_id_fossil,     0.1},{rr_petal_id_third_eye, 0.05}}},
    {rr_mob_id_ant,                rr_rarity_id_common, rr_rarity_id_ultimate,  10, 10, 20.0f, {{rr_petal_id_pellet,   0.1},{rr_petal_id_leaf,       0.1},{rr_petal_id_mandible,  0.05}}},
    {rr_mob_id_hornet,             rr_rarity_id_common, rr_rarity_id_ultimate,27.5, 25, 25.0f, {{rr_petal_id_stinger,  0.1},{rr_petal_id_crest,     0.05}}},
    {rr_mob_id_dragonfly,          rr_rarity_id_common, rr_rarity_id_ultimate,  20, 10, 25.0f, {{rr_petal_id_pellet,   0.1},{rr_petal_id_magnet,    0.05}}},
    {rr_mob_id_honeybee,           rr_rarity_id_common, rr_rarity_id_ultimate,12.5, 25, 22.0f, {{rr_petal_id_wax,     0.05},{rr_petal_id_stinger,   0.05}}},
    {rr_mob_id_beehive,            rr_rarity_id_common, rr_rarity_id_ultimate,   0,  0, 45.0f, {{rr_petal_id_wax,     0.05},{rr_petal_id_azalea,    0.05}}},
    {rr_mob_id_spider,             rr_rarity_id_common, rr_rarity_id_ultimate,  20, 25, 25.0f, {{rr_petal_id_web,      0.1},{rr_petal_id_third_eye, 0.01}}},
    {rr_mob_id_house_centipede,    rr_rarity_id_common, rr_rarity_id_ultimate,  25, 10, 23.0f, {{rr_petal_id_peas,     0.1},{rr_petal_id_sand,      0.05}}},
    {rr_mob_id_lanternfly,         rr_rarity_id_common, rr_rarity_id_ultimate,  20, 10, 25.0f, {{rr_petal_id_mint,     0.1},{rr_petal_id_sand,      0.05}}},
};

char const *RR_MOB_NAMES[rr_mob_id_max] = {
"Triceratops","T-Rex","Fern","Tree","Pteranodon","Dakotaraptor",
"Pachycephalosaurus","Ornithomimus","Ankylosaurus","Meteor",
"Quetzalcoatlus","Edmontosaurus","Ant","Hornet","Dragonfly",
"Honeybee","Beehive","Spider","House Centipede","Lanternfly"
};

uint32_t RR_MOB_DIFFICULTY_COEFFICIENTS[rr_mob_id_max] = {
    3, //tric
    4, //trex
    1, //fern
    2, //tree
    5, //pter
    5, //dako
    3, //pachy
    2, //ornith
    4, //anky
    1, //meteor
    5, //quetz
    3, //edmo
};

double RR_HELL_CREEK_MOB_ID_RARITY_COEFFICIENTS[rr_mob_id_max] = {
    45,   //tric
    100,  //trex
    15,   //fern
    0.25, //tree
    75,   //pter
    50,   //dako
    25,   //pachy
    40,   //ornith
    25,   //anky
    1,  //meteor
    75,   //quetz
    25,   //edmo
};
double RR_GARDEN_MOB_ID_RARITY_COEFFICIENTS[rr_mob_id_max] = {0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 1, 1, 1, 1, 1, 1, 10};

struct rr_petal_rarity_scale RR_PETAL_RARITY_SCALE[rr_rarity_id_max] = {
    {1,    240, 45,  0.2},
    {1.8,  120, 60,  0.3},
    {3.5,  60,  75,  0.4},
    {6.8,  30,  100, 0.5},
    {12.5, 15,  125, 0.6},
    {24.5, 7.5, 150, 0.7},
    {60,   2.5, 200, 0.8},
    {180,  0.5, 250, 0.9},
};

struct rr_mob_rarity_scale RR_MOB_RARITY_SCALING[rr_rarity_id_max] = {
    {1,      1,    1  },
    {2.4,    1.7,  1.2},
    {6,      2.9,  1.5}, 
    {14.4,   5,    2  },
    {40,     8.5,  2.8},
    {192,    14.5, 4  },
    {2560,   24.6, 5.5},
    {128000, 42,   14  },
};
// clang-format on

uint32_t RR_RARITY_COLORS[rr_rarity_id_max] = {
    0xff7eef6d, 0xffffe65d, 0xff4d52e3, 0xff861fde,
    0xffde1f1f, 0xff1fdbde, 0xffff2b75, 0xff2bffa3};

char const *RR_RARITY_NAMES[rr_rarity_id_max] = {
    "Common",    "Unusual", "Rare",   "Epic",
    "Legendary", "Mythic",  "Exotic", "Ancient"};

double RR_MOB_WAVE_RARITY_COEFFICIENTS[rr_rarity_id_max + 1] = {
    0, 1, 6, 10, 15, 25, 160, 1200, 250};

double RR_DROP_RARITY_COEFFICIENTS[rr_rarity_id_exotic + 2] = {
    0, 1, 8, 15, 40, 150, 500, 2500};
double RR_MOB_LOOT_RARITY_COEFFICIENTS[rr_rarity_id_max] = {2.5, 4,  6,   15,
                                                            35,  50, 125, 150};

static void init_game_coefficients()
{
    double sum = 1;
    double sum2 = 1;
    for (uint64_t a = 1; a < rr_rarity_id_max; ++a)
        RR_MOB_LOOT_RARITY_COEFFICIENTS[a] *=
            RR_MOB_LOOT_RARITY_COEFFICIENTS[a - 1];
    for (uint64_t a = 1; a <= rr_rarity_id_exotic; ++a)
    {
        sum += (RR_DROP_RARITY_COEFFICIENTS[a + 1] =
                    RR_DROP_RARITY_COEFFICIENTS[a] /
                    RR_DROP_RARITY_COEFFICIENTS[a + 1]);
    }
    for (uint64_t a = 1; a <= rr_rarity_id_exotic + 1; ++a)
    {
        RR_DROP_RARITY_COEFFICIENTS[a] = RR_DROP_RARITY_COEFFICIENTS[a] / sum +
                                         RR_DROP_RARITY_COEFFICIENTS[a - 1];
    }
    RR_DROP_RARITY_COEFFICIENTS[rr_rarity_id_exotic + 1] = 1;
    for (uint64_t a = 1; a <= rr_rarity_id_ultimate; ++a)
    {
        sum2 += (RR_MOB_WAVE_RARITY_COEFFICIENTS[a + 1] =
                     RR_MOB_WAVE_RARITY_COEFFICIENTS[a] /
                     RR_MOB_WAVE_RARITY_COEFFICIENTS[a + 1]);
    }
    for (uint64_t a = 1; a <= rr_rarity_id_ultimate + 1; ++a)
    {
        RR_MOB_WAVE_RARITY_COEFFICIENTS[a] =
            RR_MOB_WAVE_RARITY_COEFFICIENTS[a] / sum2 +
            RR_MOB_WAVE_RARITY_COEFFICIENTS[a - 1];
    }
    RR_MOB_WAVE_RARITY_COEFFICIENTS[rr_rarity_id_ultimate + 1] = 1;
    for (uint64_t mob = 1; mob < rr_mob_id_max; ++mob)
    {
        RR_HELL_CREEK_MOB_ID_RARITY_COEFFICIENTS[mob] +=
            RR_HELL_CREEK_MOB_ID_RARITY_COEFFICIENTS[mob - 1];
        RR_GARDEN_MOB_ID_RARITY_COEFFICIENTS[mob] +=
            RR_GARDEN_MOB_ID_RARITY_COEFFICIENTS[mob - 1];
    }
    for (uint64_t mob = 0; mob < rr_mob_id_max; ++mob)
    {
        RR_HELL_CREEK_MOB_ID_RARITY_COEFFICIENTS[mob] /=
            RR_HELL_CREEK_MOB_ID_RARITY_COEFFICIENTS[rr_mob_id_max - 1];
        RR_GARDEN_MOB_ID_RARITY_COEFFICIENTS[mob] /=
            RR_GARDEN_MOB_ID_RARITY_COEFFICIENTS[rr_mob_id_max - 1];
    }
}

#define offset(a, b)                                                           \
    ((x + a < 0 || y + b < 0 || x + a >= size / 2 || y + b >= size / 2)        \
         ? 0                                                                   \
         : template[(y + b) * size / 2 + x + a])
#define maze_grid(x, y) maze[(y)*size + (x)]

static void init_maze(uint32_t size, uint8_t *template,
                      struct rr_maze_grid *maze)
{
    for (int32_t y = 0; y < size / 2; ++y)
    {
        for (int32_t x = 0; x < size / 2; ++x)
        {
            uint8_t this_tile = offset(0, 0);
#ifdef RR_SERVER
            maze_grid(x * 2, y * 2).difficulty = this_tile;
            maze_grid(x * 2 + 1, y * 2).difficulty = this_tile;
            maze_grid(x * 2, y * 2 + 1).difficulty = this_tile;
            maze_grid(x * 2 + 1, y * 2 + 1).difficulty = this_tile;
#endif
            this_tile = this_tile != 0;
            // top left
            uint8_t top = offset(0, -1);
            uint8_t bottom = offset(0, 1);
            if (this_tile)
            {
                if (top == 0)
                {
                    if (offset(-1, 0) == 0)
                        maze_grid(x * 2, y * 2).value = 7;
                    else
                        maze_grid(x * 2, y * 2).value = this_tile;
                    if (offset(1, 0) == 0)
                        maze_grid(x * 2 + 1, y * 2).value = 5;
                    else
                        maze_grid(x * 2 + 1, y * 2).value = this_tile;
                }
                else
                {
                    maze_grid(x * 2, y * 2).value = this_tile;
                    maze_grid(x * 2 + 1, y * 2).value = this_tile;
                }
                if (bottom == 0)
                {
                    if (offset(-1, 0) == 0)
                        maze_grid(x * 2, y * 2 + 1).value = 6;
                    else
                        maze_grid(x * 2, y * 2 + 1).value = this_tile;
                    if (offset(1, 0) == 0)
                        maze_grid(x * 2 + 1, y * 2 + 1).value = 4;
                    else
                        maze_grid(x * 2 + 1, y * 2 + 1).value = this_tile;
                }
                else
                {
                    maze_grid(x * 2, y * 2 + 1).value = this_tile;
                    maze_grid(x * 2 + 1, y * 2 + 1).value = this_tile;
                }
            }
            else
            {
                if (top)
                {
                    if (offset(-1, 0) && offset(-1, -1))
                        maze_grid(x * 2, y * 2).value = 15;
                    else
                        maze_grid(x * 2, y * 2).value = this_tile;
                    if (offset(1, 0) && offset(1, -1))
                        maze_grid(x * 2 + 1, y * 2).value = 13;
                    else
                        maze_grid(x * 2 + 1, y * 2).value = this_tile;
                }
                else
                {
                    maze_grid(x * 2, y * 2).value = this_tile;
                    maze_grid(x * 2 + 1, y * 2).value = this_tile;
                }
                if (bottom)
                {
                    if (offset(-1, 0) && offset(-1, 1))
                        maze_grid(x * 2, y * 2 + 1).value = 14;
                    else
                        maze_grid(x * 2, y * 2 + 1).value = this_tile;
                    if (offset(1, 0) && offset(1, 1))
                        maze_grid(x * 2 + 1, y * 2 + 1).value = 12;
                    else
                        maze_grid(x * 2 + 1, y * 2 + 1).value = this_tile;
                }
                else
                {
                    maze_grid(x * 2, y * 2 + 1).value = this_tile;
                    maze_grid(x * 2 + 1, y * 2 + 1).value = this_tile;
                }
            }
        }
    }
}

static void print_chances(float difficulty)
{
    printf("-----Chances for %.0f-----\n", difficulty);
    uint32_t rarity_cap = rr_rarity_id_common + (difficulty + 7) / 8;
    if (rarity_cap > rr_rarity_id_ultimate)
        rarity_cap = rr_rarity_id_ultimate;
    uint32_t rarity = rarity_cap >= 2 ? rarity_cap - 2 : 0;
    for (; rarity <= rarity_cap; ++rarity)
    {
        float start =
            rarity == 0
                ? 0
                : pow(1 - (1 - RR_MOB_WAVE_RARITY_COEFFICIENTS[rarity]) * 0.3,
                      pow(1.5, difficulty));
        float end =
            rarity == rarity_cap
                ? 1
                : pow(1 - (1 - RR_MOB_WAVE_RARITY_COEFFICIENTS[rarity + 1]) *
                              0.3,
                      pow(1.5, difficulty));
        printf("%s: %.9f (1 per %.4f)\n", RR_RARITY_NAMES[rarity], end - start,
               1 / (end - start));
    }
}

double RR_BASE_CRAFT_CHANCES[rr_rarity_id_max - 1] = {0.5,  0.3,  0.15, 0.05,
                                                      0.03, 0.02, 0.015};
double RR_CRAFT_CHANCES[rr_rarity_id_max - 1];

static double from_prd_base(double C)
{
    double pProcOnN = 0;
    double pProcByN = 0;
    double sumNpProcOnN = 0;

    double maxFails = ceil(1 / C);
    for (uint32_t N = 1; N <= maxFails; ++N)
    {
        pProcOnN = fmin(1, N * C) * (1 - pProcByN);
        pProcByN += pProcOnN;
        sumNpProcOnN += N * pProcOnN;
    }
    return (1 / sumNpProcOnN);
}

static double get_prd_base(double p)
{
    if (p == 0)
        return 0;
    double Cupper = p;
    double Clower = 0;
    double Cmid = p / 2;
    double p1 = 0;
    double p2 = 1;
    while (1)
    {
        Cmid = (Cupper + Clower) / 2;
        p1 = from_prd_base(Cmid);
        if (fabs(p1 - p2) <= 0)
            break;

        if (p1 > p)
            Cupper = Cmid;
        else
            Clower = Cmid;
        p2 = p1;
    }
    return Cmid;
}

#define init(MAZE)                                                             \
    init_maze(sizeof(RR_MAZE_##MAZE[0]) / sizeof(struct rr_maze_grid),         \
              &RR_MAZE_TEMPLATE_##MAZE[0][0], &RR_MAZE_##MAZE[0][0]);

void rr_static_data_init()
{
    for (uint32_t r = 0; r < rr_rarity_id_max - 1; ++r)
        RR_CRAFT_CHANCES[r] = get_prd_base(RR_BASE_CRAFT_CHANCES[r]);
    init_game_coefficients();
    init(HELL_CREEK);
    init(BURROW);
#ifdef RR_SERVER
    print_chances(52);
    print_chances(44);
    print_chances(40);
    print_chances(36);
    print_chances(32);
#endif
}

double xp_to_reach_level(uint32_t level)
{
    if (level <= 60)
        return (level + 5) * pow(1.175, level);
    double base = (level + 5) * pow(1.175, 60);
    for (uint32_t i = 60; i < level; ++i)
        base *= rr_fclamp(1.18 - 0.0075 * (i - 60), 1.1, 1.18);
    return base;
}

uint32_t level_from_xp(double xp)
{
    uint32_t level = 1;
    while (xp >= xp_to_reach_level(level + 1))
        xp -= xp_to_reach_level(++level);
    return level;
}

#ifdef RR_SERVER
#define _ 0
#define c 1
#define C 4
#define u 8
#define U 12
#define r 16
#define R 20
#define e 24
#define E 28
#define l 32
#define L 36
#define m 40
#define M 44
#define x 48
#define X 52
#define a 56
#else
#define _ 0
#define c 1
#define C 1
#define u 1
#define U 1
#define r 1
#define R 1
#define e 1
#define E 1
#define l 1
#define L 1
#define m 1
#define M 1
#define x 1
#define X 1
#define a 1
#endif

#define RR_DEFINE_MAZE(name, size)                                             \
    struct rr_maze_grid RR_MAZE_##name[size][size];                            \
    uint8_t RR_MAZE_TEMPLATE_##name[size / 2][size / 2]
// clang-format off
RR_DEFINE_MAZE(HELL_CREEK, 80) = {
// 1 2 3 4 5 6 7 8 9 101112131415161718192021222324252627282930313233343536373839
{_,_,_,_,_,_,_,_,_,_,_,_,_,_,_,_,_,_,_,_,_,_,_,_,_,_,_,_,_,_,_,_,_,_,_,_,_,_,_,_},//1
{_,_,_,_,x,x,x,x,X,X,X,X,X,_,X,X,X,_,_,_,X,X,X,X,X,_,_,X,X,X,X,X,_,_,X,X,X,a,_,_},//2
{_,_,_,_,x,_,_,_,_,_,_,X,X,_,X,_,X,_,_,X,X,X,_,X,X,X,_,a,_,_,_,X,_,X,X,_,_,X,_,_},//3
{_,_,_,_,x,_,X,X,X,X,X,X,_,_,X,_,X,X,X,X,X,_,_,X,X,X,_,_,_,X,X,X,X,X,X,X,X,X,_,_},//4
{_,_,_,x,x,_,X,X,X,X,X,X,X,X,X,_,_,_,X,X,_,_,_,_,_,X,X,X,X,X,_,_,_,_,_,_,_,_,_,_},//5
{L,L,_,_,l,l,_,_,_,_,_,X,X,X,_,_,e,E,E,E,_,_,E,E,_,_,l,l,l,l,_,_,_,_,_,_,_,_,_,_},//6
{L,L,_,_,l,l,l,l,_,_,_,_,_,_,_,_,E,E,E,E,E,E,E,E,_,_,l,l,l,l,_,_,m,L,L,L,L,L,_,_},//7
{_,L,L,_,_,l,l,l,l,l,l,_,_,_,_,_,E,E,E,E,_,_,E,E,_,_,l,l,l,_,_,_,m,_,_,_,_,L,_,_},//8
{_,L,L,_,_,_,_,l,l,l,E,E,E,E,E,E,E,E,E,E,E,_,E,l,_,_,l,l,_,_,_,_,m,_,m,m,_,L,_,_},//9
{_,L,L,m,m,_,_,_,_,l,l,E,E,E,_,_,_,_,_,_,E,E,l,l,l,_,l,l,l,_,_,_,m,_,_,m,_,L,_,_},//10
{_,L,m,m,m,m,m,_,_,_,_,_,_,_,_,_,_,_,_,_,E,l,l,l,l,l,l,l,l,_,_,_,m,m,m,m,_,L,_,_},//11
{_,_,m,m,m,m,m,m,_,_,_,_,_,_,_,_,M,M,_,_,_,l,l,l,_,l,l,l,l,_,_,_,_,_,_,_,_,L,_,_},//12
{_,_,M,m,m,m,m,m,m,m,m,m,m,m,m,m,M,M,_,_,_,_,_,_,_,l,l,l,l,l,l,L,L,L,L,L,L,L,_,_},//13
{_,_,M,_,_,m,_,m,m,_,_,_,_,M,M,M,_,m,_,L,_,l,l,l,_,_,_,_,_,_,_,_,l,l,E,_,E,E,_,_},//14
{_,_,M,_,m,m,_,m,_,_,M,M,_,_,_,M,_,m,_,L,_,_,l,l,_,_,_,_,l,l,l,l,l,E,E,E,E,E,_,_},//15
{_,_,M,_,_,_,_,m,_,M,M,M,M,_,_,M,_,m,_,_,_,_,l,l,l,l,l,l,l,l,l,l,_,_,_,_,E,E,_,_},//16
{_,_,M,_,_,_,m,m,_,M,_,_,M,_,M,M,_,m,_,_,l,l,l,_,_,_,_,_,_,_,_,_,_,_,E,E,E,E,_,_},//17
{_,_,M,_,_,_,m,_,_,M,_,_,M,M,M,_,_,m,_,_,l,_,_,_,R,R,R,R,e,e,e,e,e,e,E,_,_,E,_,_},//18
{_,_,M,_,_,_,m,_,M,M,_,M,M,M,_,_,m,m,_,_,L,_,R,R,R,R,_,_,e,e,e,_,e,E,E,_,_,E,_,_},//19
{_,_,M,_,_,_,m,_,M,M,_,_,_,_,_,_,m,_,_,L,L,_,R,R,R,R,R,_,e,e,e,_,_,_,_,_,l,l,_,_},//20
{_,_,M,_,_,_,m,_,_,M,M,M,m,_,_,m,m,_,L,L,L,_,_,_,r,r,R,_,_,_,e,E,E,_,l,l,l,l,_,_},//21
{_,_,M,_,_,_,m,m,_,_,_,_,m,m,m,m,_,_,L,_,_,_,U,r,r,r,r,R,R,_,_,_,E,_,_,l,l,_,_,_},//22
{_,_,M,_,_,_,_,m,m,m,L,_,_,_,_,_,_,L,L,_,U,U,U,U,r,_,_,R,R,R,R,_,E,E,_,_,l,_,_,_},//23
{_,_,M,M,M,M,_,_,_,_,L,L,L,L,L,L,L,L,_,_,U,U,U,U,U,r,_,r,_,_,R,_,_,E,E,_,l,_,_,_},//24
{_,_,_,M,M,M,M,M,M,_,_,_,_,L,_,_,_,m,_,U,U,u,U,U,U,U,r,r,r,_,e,e,_,E,E,_,l,_,M,_},//25
{_,_,_,M,_,_,_,_,M,M,_,L,L,L,_,U,_,_,_,_,u,u,u,_,_,r,r,r,r,_,_,R,_,e,_,_,l,_,M,M},//26
{_,_,_,M,M,M,_,M,M,M,_,_,L,L,_,u,u,u,u,_,u,u,u,u,_,_,_,_,R,R,R,R,_,e,_,l,l,_,m,m},//27
{_,_,_,M,_,M,_,_,_,M,M,_,m,L,_,_,_,_,C,_,_,u,u,u,_,U,U,_,_,R,_,_,_,e,_,l,l,_,m,m},//28
{_,_,M,M,_,M,M,_,M,M,_,_,m,_,_,u,u,C,C,_,C,C,u,u,u,u,U,U,_,R,R,e,e,e,_,l,_,m,L,L},//29
{_,_,M,_,_,M,M,_,_,M,_,m,m,_,u,u,u,_,C,C,C,_,u,u,_,_,_,U,_,_,_,e,_,_,_,l,l,l,_,L},//30
{_,_,M,M,_,M,M,M,_,M,_,m,m,_,U,_,_,_,c,c,c,_,_,u,_,r,r,U,_,e,e,e,_,l,L,L,l,l,L,L},//31
{_,_,M,M,_,_,_,M,_,M,_,m,_,U,U,U,_,c,c,c,c,_,_,U,_,_,r,r,_,e,_,_,_,l,L,L,l,_,l,_},//32
{_,_,_,M,M,M,M,M,_,M,_,m,_,U,U,U,_,c,c,c,c,_,U,U,U,U,r,_,_,E,E,E,_,_,l,l,l,_,l,_},//33
{_,_,_,M,_,_,_,M,M,M,_,m,_,e,e,e,_,_,C,c,_,_,U,U,_,_,r,_,_,E,E,E,E,_,_,_,l,_,l,l},//34
{_,_,_,M,M,_,_,_,_,M,_,m,_,e,e,e,_,u,u,_,_,_,r,U,r,_,_,_,_,E,_,_,E,E,E,_,l,_,l,_},//35
{_,_,_,M,M,_,m,m,_,_,_,m,_,e,e,R,U,U,R,R,r,r,r,r,r,r,_,_,E,E,_,_,E,E,E,l,l,_,l,E},//36
{_,_,_,_,m,m,m,m,m,m,m,m,_,_,e,_,_,_,_,R,R,_,_,r,r,r,R,_,E,E,E,E,E,_,_,_,_,E,l,_},//37
{_,_,m,m,m,m,m,m,_,_,_,_,_,_,_,_,M,x,_,_,_,l,l,l,_,R,R,R,R,_,_,_,_,_,_,_,_,E,E,_},//38
{_,_,_,m,m,m,m,m,m,m,m,m,M,M,M,M,M,M,_,_,_,_,_,_,_,R,R,R,e,e,e,E,E,E,E,E,E,E,_,_},//39
//12 3 4 5 6 7 8 9 10111213141516171819202122232425262728293031323334 3536373839
};
// clang-format on
RR_DEFINE_MAZE(BURROW, 4) = {{1, 1}, {0, 1}};

#define MAZE_ENTRY(MAZE, GRID_SIZE)                                            \
    (sizeof(RR_MAZE_##MAZE[0]) / sizeof(struct rr_maze_grid)), GRID_SIZE,      \
        &RR_MAZE_##MAZE[0][0]

struct rr_maze_declaration RR_MAZES[rr_biome_id_max] = {
    {MAZE_ENTRY(HELL_CREEK, 1024), {{6, 13}, {11, 15}, {16, 17}, {22, 23}}},
    {MAZE_ENTRY(HELL_CREEK, 1024), {{6, 13}, {11, 15}, {16, 17}, {22, 23}}},
    {MAZE_ENTRY(BURROW, 512), {{0}, {0}, {0}, {0}}},
};

uint8_t RR_GLOBAL_BIOME = rr_biome_id_hell_creek;
#undef c
#undef C
#undef u
#undef U
#undef r
#undef R
#undef e
#undef E
#undef l
#undef L
#undef m
#undef M
#undef x
#undef X
