#include <Shared/StaticData.h>

#include <math.h>
#include <stdio.h>

#include <Shared/Utilities.h>

// clang-format off
struct rr_petal_data RR_PETAL_DATA[rr_petal_id_max] = {
    {rr_petal_id_no_petal, rr_rarity_id_common, 0.0f, 0.0f, 0.0f, 0, 0, {0, 0, 0, 0, 0, 0, 0}},
    {rr_petal_id_basic, rr_rarity_id_common, 10.0f, 15.0f, 0.0f, 50, 0, {1, 1, 1, 1, 1, 1, 1}},
    {rr_petal_id_pellet, rr_rarity_id_common, 13.0f, 5.0f, 0.0f, 15, 0, {1, 2, 2, 3, 3, 5, 5}},
    {rr_petal_id_fossil, rr_rarity_id_common, 10.0f, 75.0f, 0.0f, 100, 0, {1, 1, 1, 1, 1, 1, 1}},
    {rr_petal_id_stinger, rr_rarity_id_common, 75.0f, 3.0f, 10.0f, 188, 0, {1, 1, 1, 1, 1, 3, 5}},
    {rr_petal_id_light, rr_rarity_id_rare, 8.0f, 5.0f, 15.0f, 20, 0, {1, 1, 1, 1, 1, 2, 2}},
    {rr_petal_id_shell, rr_rarity_id_rare, 3.5f, 8.0f, 15.0f, 38, 13, {1, 1, 1, 1, 1, 1, 1}},
    {rr_petal_id_peas, rr_rarity_id_rare, 20.0f, 8.0f, 8.0f, 13, 12, {4, 4, 4, 4, 4, 4, 5}},
    {rr_petal_id_leaf, rr_rarity_id_unusual, 8.0f, 12.0f, 8.0f, 25, 0, {1, 1, 1, 1, 1, 2, 2}},
    {rr_petal_id_egg, rr_rarity_id_unusual, 1.0f, 20.0f, 0.0f, 25, 75, {1, 1, 1, 1, 1, 1, 1}},
    {rr_petal_id_magnet, rr_rarity_id_rare, 2.0f, 15.0f, 0.0f, 38, 0, {1, 1, 1, 1, 1, 1, 1}},
    {rr_petal_id_uranium, rr_rarity_id_rare, 5.0f, 10.0f, 0.0f, 50, 0, {1, 1, 1, 1, 1, 1, 1}},
    {rr_petal_id_feather, rr_rarity_id_common, 1.0f, 3.0f, 0.0f, 25, 0, {1, 1, 1, 1, 1, 1, 1}},
    {rr_petal_id_azalea, rr_rarity_id_common, 5.0f, 10.0f, 0.0f, 75, 25, {1, 1, 1, 1, 1, 1, 1}},
    {rr_petal_id_bone, rr_rarity_id_common, 5.0f, 25.0f, 0.0f, 68, 0, {1, 1, 1, 1, 1, 1, 1}},
    {rr_petal_id_web, rr_rarity_id_rare, 5.0f, 5.0f, 0.0f, 50, 13, {1, 1, 1, 1, 1, 1, 1}},
    {rr_petal_id_seed, rr_rarity_id_legendary, 1.0f, 20.0f, 0.0f, 63, 1, {1, 1, 1, 1, 1, 1, 1}},
    {rr_petal_id_gravel, rr_rarity_id_unusual, 15.0f, 10.0f, 0.0f, 25, 13, {1, 2, 2, 2, 3, 3, 4}},
    {rr_petal_id_club, rr_rarity_id_common, 3.5f, 450.0f, 0.0f, 250, 0, {1, 1, 1, 1, 1, 1, 1}},
    {rr_petal_id_crest, rr_rarity_id_rare, 0.0f, 0.0f, 0.0f, 0, 0, {0, 0, 0, 0, 0, 0, 0}},
    {rr_petal_id_droplet, rr_rarity_id_common, 15.0f, 5.0f, 0.0f, 50, 0, {1, 1, 1, 1, 1, 1, 1}},
    {rr_petal_id_beak, rr_rarity_id_unusual, 12.0f, 10.0f, 0.0f, 68, 0, {1, 1, 1, 1, 1, 1, 1}},
    {rr_petal_id_lightning, rr_rarity_id_unusual, 16.0f, 4.0f, 0.0f, 50, 25, {1, 1, 1, 1, 1, 1, 1}},
    {rr_petal_id_third_eye, rr_rarity_id_rare, 0.0f, 0.0f, 0.0f, 0, 0, {0, 0, 0, 0, 0, 0, 0}},
    {rr_petal_id_mandible, rr_rarity_id_common, 5.0f, 10.0f, 0.0f, 75, 0, {1, 1, 1, 1, 1, 1, 1}},
};    

struct rr_mob_data RR_MOB_DATA[rr_mob_id_max] = {
    {rr_mob_id_triceratops, rr_rarity_id_rare, 45, 15, 30.0f, {{rr_petal_id_leaf, 0.15},{rr_petal_id_fossil, 0.1}}},
    {rr_mob_id_trex, rr_rarity_id_epic, 30, 25, 32.0f, {{rr_petal_id_bone, 0.2},{rr_petal_id_fossil, 0.05}}},
    {rr_mob_id_fern, rr_rarity_id_common, 10, 5, 24.0f, {{rr_petal_id_leaf, 0.1},{rr_petal_id_azalea, 0.25}}},
    {rr_mob_id_tree, rr_rarity_id_rare, 50, 5, 60.0f, {{rr_petal_id_leaf, 0.5},{rr_petal_id_peas, 0.25},{rr_petal_id_seed, 0.04}}},
    {rr_mob_id_pteranodon, rr_rarity_id_common, 30, 20, 20.0f, {{rr_petal_id_shell, 0.15},{rr_petal_id_beak, 0.15}}},
    {rr_mob_id_dakotaraptor, rr_rarity_id_unusual, 35, 10, 25.0f, {{rr_petal_id_crest, 1},{rr_petal_id_feather, 0.15}}},
    {rr_mob_id_pachycephalosaurus, rr_rarity_id_common, 30, 15, 20.0f, {{rr_petal_id_fossil, 0.15},{rr_petal_id_light, 0.1}}},
    {rr_mob_id_ornithomimus, rr_rarity_id_common, 20, 10, 20.0f, {{rr_petal_id_feather, 0.1},{rr_petal_id_droplet, 0.05}}},
    {rr_mob_id_ankylosaurus, rr_rarity_id_rare, 40, 10, 30.0f, {{rr_petal_id_club, 0.15},{rr_petal_id_gravel, 0.1}}},
    {rr_mob_id_meteor, rr_rarity_id_rare, 200, 8, 32.0f, {{rr_petal_id_magnet, 0.5},{rr_petal_id_uranium, 0.25}}},
    {rr_mob_id_quetzalcoatlus, rr_rarity_id_unusual, 75, 10, 28.0f, {{rr_petal_id_beak, 0.25},{rr_petal_id_fossil, 0.15}}},
    {rr_mob_id_edmontosaurus, rr_rarity_id_epic, 50, 10, 30.0f, {{rr_petal_id_peas, 0.15},{rr_petal_id_fossil, 0.1}}},
    {rr_mob_id_ant, rr_rarity_id_common, 15, 10, 20.0f, {{rr_petal_id_pellet, 0.1},{rr_petal_id_leaf, 0.1},{rr_petal_id_mandible, 0.05}}},
    {rr_mob_id_hornet, rr_rarity_id_common, 30, 30, 25.0f, {{rr_petal_id_stinger, 0.1},{rr_petal_id_crest, 0.05}}},
    {rr_mob_id_dragonfly, rr_rarity_id_common, 15, 10, 25.0f, {{rr_petal_id_pellet, 0.1},{rr_petal_id_third_eye, 0.04}}},
    {rr_mob_id_honeybee, rr_rarity_id_common, 10, 25, 22.0f, {{rr_petal_id_pellet, 0.05},{rr_petal_id_stinger, 0.04}}},
};

// zeach's numbers from the pinned screenshot of the old scaling
struct rr_petal_rarity_scale RR_PETAL_RARITY_SCALE[rr_rarity_id_max] = {
    {1,   1},
    {1.5, 1.8},
    {2.4, 3.0},
    {3.5, 4.5},
    {6.0, 7.2},
    {12.0, 18.0},
    {25.0, 54.0},
};

struct rr_mob_rarity_scale RR_MOB_RARITY_SCALING[rr_rarity_id_max] = {
    {1.0, 1.0, 1.0},
    {3.2, 1.3, 1.2},
    {10.5, 1.6, 1.5}, 
    {30,  2.5, 1.8},
    {100,  4.0, 2.5},
    {250, 7.0, 4.0},
    {1000, 15,  6.0},
};
// clang-format on

uint32_t RR_RARITY_COLORS[rr_rarity_id_max] = {
    0xff7eef6d, 0xffffe65d, 0xff4d52e3, 0xff861fde,
    0xffde1f1f, 0xff1fdbde, 0xffff2b75};
char const *RR_RARITY_NAMES[rr_rarity_id_max] = {
    "Common", "Uncommon", "Rare", "Epic", "Legendary", "Mythic", "Exotic"};
char const *RR_PETAL_NAMES[rr_petal_id_max] = {
    "Secret", "Basic", "Pellet", "Fossil",   "Stinger",  "Light", "Shell",
    "Peas",   "Leaf",  "Egg",    "Magnet", "Uranium", "Feather", "Azalea",
    "Bone",   "Web",   "Seed",   "Gravel", "Club", "Crest", "Droplet",
    "Beak", "Lightning", "Third Eye", "Mandible"};
char const *RR_PETAL_DESCRIPTIONS[rr_petal_id_max] = {
    0,
    "It's just a petal",
    "Low damage, but there's lots",
    "It came from a dino",
    "Ow that hurts",
    "Makes your petals lighter so they spin faster",
    "Poor snail",
    "Splits in 4. Or maybe 5 if you're a pro",
    "Heals you gradually",
    "Spawns a pet dinosaur to protect you",
    "Increases loot pickup radius. Does not stack",
    "Does low damage to mobs in a large range. Slowly damages yourself",
    "It's so light it increases your movement speed. Does not stack",
    "It heals you",
    "Gives the player armor. Stacks with itself",
    "Web",
    "What does this one do",
    "Tiny rocks that stay on the ground and trip dinos",
    "Heavy and sturdy",
    "Decreases mob aggro range. Does not stack",
    "This mysterious petal reverses your petal rotation",
    "Stuns mobs and prevents them from moving",
    "A stunning display",
    "It allows you to see further away",
    "Does more damage if target hp is below 50%"
};

// CHANGE WHEN ADD MOB
char const *RR_MOB_NAMES[rr_mob_id_max] = {"Triceratops",
                                           "T-Rex",
                                           "Fern",
                                           "Tree",
                                           "Pteranodon",
                                           "Dakotaraptor",
                                           "Pachycephalosaurus",
                                           "Ornithomimus",
                                           "Ankylosaurus",
                                           "Meteor",
                                           "Quetzalcoatlus",
                                           "Edmontosaurus",
                                           "Ant",
                                           "Hornet",
                                           "Dragonfly",
                                           "Honeybee"};

uint32_t RR_MOB_DIFFICULTY_COEFFICIENTS[rr_mob_id_max] = {9,  10, 2, 4, 20,
                                                          12, 9,  3, 10, 1, 8, 10, 8, 12, 8};
double RR_HELL_CREEK_MOB_ID_RARITY_COEFFICIENTS[rr_mob_id_max] = {50, 100, 30, 1.5, 25,
                                                       25, 20, 25, 25, 0.5, 75, 25};
double RR_GARDEN_MOB_ID_RARITY_COEFFICIENTS[rr_mob_id_max] = {0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 1, 1, 1, 1};
//END                                            
double RR_MOB_WAVE_RARITY_COEFFICIENTS[rr_rarity_id_ultra + 2] = {
    0, 1, 5, 8, 15, 30, 100, 500};

double RR_DROP_RARITY_COEFFICIENTS[rr_rarity_id_ultra + 2] = {
    0, 1, 8, 12, 25, 50, 200, 500};
double RR_MOB_LOOT_RARITY_COEFFICIENTS[rr_rarity_id_ultra + 1] = {
    5, 2, 10, 12, 15, 18, 25};

static void init_game_coefficients()
{
    double sum = 1;
    double sum2 = 1;
    for (uint64_t a = 1; a <= rr_rarity_id_ultra; ++a)
    {
        sum += (RR_DROP_RARITY_COEFFICIENTS[a + 1] =
                    RR_DROP_RARITY_COEFFICIENTS[a] /
                    RR_DROP_RARITY_COEFFICIENTS[a + 1]);
        sum2 += (RR_MOB_WAVE_RARITY_COEFFICIENTS[a + 1] =
                     RR_MOB_WAVE_RARITY_COEFFICIENTS[a] /
                     RR_MOB_WAVE_RARITY_COEFFICIENTS[a + 1]);
        RR_MOB_LOOT_RARITY_COEFFICIENTS[a] *=
            RR_MOB_LOOT_RARITY_COEFFICIENTS[a - 1];
    }
    for (uint64_t a = 1; a <= rr_rarity_id_ultra + 1; ++a)
    {
        RR_DROP_RARITY_COEFFICIENTS[a] = RR_DROP_RARITY_COEFFICIENTS[a] / sum +
                                         RR_DROP_RARITY_COEFFICIENTS[a - 1];
        RR_MOB_WAVE_RARITY_COEFFICIENTS[a] =
            RR_MOB_WAVE_RARITY_COEFFICIENTS[a] / sum2 +
            RR_MOB_WAVE_RARITY_COEFFICIENTS[a - 1];
    }
    RR_DROP_RARITY_COEFFICIENTS[rr_rarity_id_ultra + 1] = 1;
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

static void init_maze(uint8_t (*template)[RR_MAZE_DIM/2], struct rr_maze_grid (*maze)[RR_MAZE_DIM])
{
    #define offset(a,b) \
    ((x + a < 0 || y + b < 0 || x + a >= RR_MAZE_DIM/2 || y + b >= RR_MAZE_DIM/2) ? 0 : template[y+b][x+a])

    for (int32_t y = 0; y < RR_MAZE_DIM/2; ++y)
    {
        for (int32_t x = 0; x < RR_MAZE_DIM/2; ++x)
        {
            uint8_t this_tile = template[y][x];
            #ifdef RR_SERVER
            maze[y*2][x*2].difficulty = this_tile;
            maze[y*2][x*2+1].difficulty = this_tile;
            maze[y*2+1][x*2].difficulty = this_tile;
            maze[y*2+1][x*2+1].difficulty = this_tile;
            #endif
            this_tile = this_tile != 0;
            //top left
            uint8_t top = offset(0,-1);
            uint8_t bottom = offset(0,1);
            if (this_tile)
            {
                if (top == 0)
                {
                    if (offset(-1,0) == 0)
                        maze[y*2][x*2].value = 7;
                    else
                        maze[y*2][x*2].value = this_tile;
                    if (offset(1,0) == 0)
                        maze[y*2][x*2+1].value = 5;
                    else
                        maze[y*2][x*2+1].value = this_tile;
                }
                else
                {
                    maze[y*2][x*2].value = this_tile;
                    maze[y*2][x*2+1].value = this_tile;
                }
                if (bottom == 0)
                {
                    if (offset(-1,0) == 0)
                        maze[y*2+1][x*2].value = 6;
                    else
                        maze[y*2+1][x*2].value = this_tile;
                    if (offset(1,0) == 0)
                        maze[y*2+1][x*2+1].value = 4;
                    else
                        maze[y*2+1][x*2+1].value = this_tile;
                }
                else
                {
                    maze[y*2+1][x*2].value = this_tile;
                    maze[y*2+1][x*2+1].value = this_tile;
                }
            }
            else
            {
                if (top)
                {
                    if (offset(-1,0) && offset(-1,-1))
                        maze[y*2][x*2].value = 15;
                    else
                        maze[y*2][x*2].value = this_tile;
                    if (offset(1,0) && offset(1,-1))
                        maze[y*2][x*2+1].value = 13;
                    else
                        maze[y*2][x*2+1].value = this_tile;
                }
                else
                {
                    maze[y*2][x*2].value = this_tile;
                    maze[y*2][x*2].value = this_tile;
                }
                if (bottom)
                {
                    if (offset(-1,0) && offset(-1,1))
                        maze[y*2+1][x*2].value = 14;
                    else
                        maze[y*2+1][x*2].value = this_tile;
                    if (offset(1,0) && offset(1,1))
                        maze[y*2+1][x*2+1].value = 12;
                    else
                        maze[y*2+1][x*2+1].value = this_tile;
                }
                else
                {
                    maze[y*2+1][x*2].value = this_tile;
                    maze[y*2+1][x*2+1].value = this_tile;
                }
            }
        }
    }
}

void rr_static_data_init()
{
    init_game_coefficients();
    init_maze(RR_MAZE_TEMPLATE_HELL_CREEK, RR_MAZE_HELL_CREEK);
}

double xp_to_reach_level(uint32_t level)
{
    //xp it takes from level - 1 to level
    if (level <= 60)
        return level * pow(1.18, level);
    double base = level * pow(1.18, 60);
    for (uint32_t i = 60; i < level; ++i)
    {
        base *= rr_fclamp(1.18 - 0.01 * (i - 60), 1.1, 1.18);
    }
    return base;
}

uint8_t RR_MAZE_TEMPLATE_HELL_CREEK[RR_MAZE_DIM/2][RR_MAZE_DIM/2] = {
    {1, 1, 1, 1, 1, 1, 1, 1, 1, 1, 1, 1, 0, 0, 0, 1, 1, 0, 1, 1, 0},
    {1, 0, 0, 0, 1, 0, 0, 0, 0, 0, 0, 1, 0, 0, 0, 1, 0, 0, 0, 1, 1},
    {1, 1, 0, 1, 1, 0, 0, 0, 0, 0, 1, 1, 1, 0, 0, 1, 0, 0, 0, 0, 1},
    {0, 1, 0, 0, 0, 0, 0, 0, 0, 0, 1, 0, 1, 1, 1, 1, 1, 1, 0, 0, 1},
    {0, 1, 0, 0, 0, 0, 0, 0, 1, 0, 1, 0, 0, 0, 0, 0, 0, 1, 0, 0, 1},
    {0, 1, 0, 0, 0, 0, 0, 0, 1, 0, 1, 1, 1, 1, 0, 0, 0, 1, 0, 0, 1},
    {0, 1, 0, 0, 0, 0, 0, 0, 1, 0, 0, 0, 0, 1, 1, 1, 1, 1, 0, 0, 1},
    {1, 1, 1, 1, 1, 1, 0, 1, 1, 0, 0, 0, 0, 0, 0, 0, 0, 1, 1, 1, 1},
    {1, 0, 0, 0, 0, 1, 0, 1, 0, 0, 0, 1, 1, 1, 1, 1, 0, 1, 0, 0, 0},
    {1, 0, 1, 1, 1, 1, 0, 1, 0, 0, 0, 1, 0, 0, 0, 1, 0, 1, 0, 0, 0},
    {1, 0, 1, 0, 0, 0, 0, 1, 1, 1, 1, 1, 1, 0, 0, 1, 0, 1, 1, 1, 1},
    {1, 0, 1, 1, 1, 1, 0, 0, 0, 0, 0, 0, 1, 1, 1, 1, 0, 1, 0, 0, 0},
    {1, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 1, 0, 0, 1, 1, 1, 0},
    {1, 1, 1, 1, 1, 0, 0, 1, 1, 1, 1, 0, 0, 0, 1, 0, 0, 1, 0, 1, 1},
    {0, 1, 0, 0, 1, 0, 0, 0, 0, 0, 1, 1, 0, 0, 1, 1, 1, 1, 0, 1, 1},
    {0, 1, 0, 0, 1, 1, 0, 0, 0, 0, 0, 1, 0, 0, 0, 0, 0, 1, 0, 0, 0},
    {0, 1, 0, 0, 0, 0, 0, 1, 1, 0, 0, 1, 0, 0, 0, 0, 0, 1, 0, 0, 0},
    {0, 1, 0, 0, 0, 0, 0, 1, 1, 0, 0, 1, 0, 0, 0, 0, 0, 1, 1, 1, 0},
    {0, 1, 0, 0, 0, 0, 0, 1, 0, 0, 0, 1, 1, 0, 1, 1, 1, 1, 0, 1, 0},
    {0, 1, 1, 1, 1, 1, 1, 1, 0, 0, 0, 0, 1, 0, 0, 1, 0, 0, 0, 1, 0},
    {0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 1, 1, 1, 1, 1, 1, 1, 1, 1, 1, 0},
};

struct rr_maze_grid RR_MAZE_HELL_CREEK[RR_MAZE_DIM][RR_MAZE_DIM] = {0};
