#include <Shared/StaticData.h>

#include <math.h>
#include <stdio.h>

#include <Shared/Utilities.h>

// clang-format off
struct rr_petal_data RR_PETAL_DATA[rr_petal_id_max] = {
    {rr_petal_id_no_petal, rr_rarity_id_common, 0.0f, 0.0f, 0.0f, 0, 0, {0, 0, 0, 0, 0, 0, 0}},
    {rr_petal_id_basic, rr_rarity_id_common, 10.0f, 15.0f, 0.0f, 50, 0, {1, 1, 1, 1, 1, 1, 1}},
    {rr_petal_id_pellet, rr_rarity_id_common, 13.0f, 5.0f, 0.0f, 15, 0, {1, 2, 2, 3, 3, 5, 5}},
    {rr_petal_id_fossil, rr_rarity_id_common, 10.0f, 50.0f, 0.0f, 100, 0, {1, 1, 1, 1, 1, 1, 1}},
    {rr_petal_id_stinger, rr_rarity_id_common, 75.0f, 3.0f, 10.0f, 188, 0, {1, 1, 1, 1, 1, 3, 5}},
    {rr_petal_id_light, rr_rarity_id_rare, 8.0f, 5.0f, 15.0f, 20, 0, {1, 1, 1, 1, 1, 2, 2}},
    {rr_petal_id_shell, rr_rarity_id_rare, 3.5f, 8.0f, 15.0f, 38, 13, {1, 1, 1, 1, 1, 1, 1}},
    {rr_petal_id_peas, rr_rarity_id_rare, 20.0f, 8.0f, 8.0f, 13, 12, {4, 4, 4, 4, 4, 4, 5}},
    {rr_petal_id_leaf, rr_rarity_id_unusual, 8.0f, 12.0f, 8.0f, 25, 0, {1, 1, 1, 1, 1, 2, 2}},
    {rr_petal_id_egg, rr_rarity_id_unusual, 1.0f, 20.0f, 0.0f, 25, 75, {1, 1, 1, 1, 1, 1, 1}},
    {rr_petal_id_magnet, rr_rarity_id_rare, 2.0f, 15.0f, 0.0f, 38, 0, {1, 1, 1, 1, 1, 1, 1}},
    {rr_petal_id_uranium, rr_rarity_id_rare, 5.0f, 10.0f, 0.0f, 50, 25, {1, 1, 1, 1, 1, 1, 1}},
    {rr_petal_id_feather, rr_rarity_id_common, 1.0f, 3.0f, 0.0f, 25, 0, {1, 1, 1, 1, 1, 1, 1}},
    {rr_petal_id_azalea, rr_rarity_id_common, 5.0f, 10.0f, 0.0f, 75, 25, {1, 1, 1, 1, 1, 1, 1}},
    {rr_petal_id_bone, rr_rarity_id_common, 2.5f, 25.0f, 0.0f, 68, 0, {1, 1, 1, 1, 1, 1, 1}},
    {rr_petal_id_web, rr_rarity_id_common, 5.0f, 5.0f, 0.0f, 50, 13, {1, 1, 1, 1, 1, 1, 1}},
    {rr_petal_id_seed, rr_rarity_id_legendary, 1.0f, 20.0f, 0.0f, 63, 1, {1, 1, 1, 1, 1, 1, 1}},
    {rr_petal_id_gravel, rr_rarity_id_unusual, 15.0f, 10.0f, 0.0f, 25, 13, {1, 2, 2, 2, 3, 3, 4}},
    {rr_petal_id_club, rr_rarity_id_common, 3.5f, 300.0f, 0.0f, 250, 0, {1, 1, 1, 1, 1, 1, 1}},
    {rr_petal_id_crest, rr_rarity_id_rare, 0.0f, 0.0f, 0.0f, 0, 0, {0, 0, 0, 0, 0, 0, 0}},
    {rr_petal_id_droplet, rr_rarity_id_common, 15.0f, 5.0f, 0.0f, 50, 0, {1, 1, 1, 1, 1, 1, 1}},
    {rr_petal_id_beak, rr_rarity_id_unusual, 12.0f, 10.0f, 0.0f, 68, 0, {1, 1, 1, 1, 1, 1, 1}},
    {rr_petal_id_lightning, rr_rarity_id_unusual, 16.0f, 4.0f, 0.0f, 50, 25, {1, 1, 1, 1, 1, 1, 1}},
    {rr_petal_id_third_eye, rr_rarity_id_rare, 0.0f, 0.0f, 0.0f, 0, 0, {0, 0, 0, 0, 0, 0, 0}},
    {rr_petal_id_mandible, rr_rarity_id_common, 5.0f, 10.0f, 0.0f, 75, 0, {1, 1, 1, 1, 1, 1, 1}},
    {rr_petal_id_wax, rr_rarity_id_unusual, 5.0f, 10.0f, 10.0f, 75, 0, {2, 2, 2, 2, 2, 2, 2}},
};    

char const *RR_PETAL_NAMES[rr_petal_id_max] = {
    "Secret", "Petal", "Pellet", "Fossil",   "Stinger",  "Light", "Shell",
    "Peas",   "Leaf",  "Egg",    "Magnet", "Uranium", "Feather", "Azalea",
    "Bone",   "Web",   "Seed",   "Gravel", "Club", "Crest", "Droplet",
    "Beak", "Lightning", "Third Eye", "Mandible", "Wax"};
    
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
    "Does more damage if target hp is below 50%",
    "Made by the bees"
};

struct rr_mob_data RR_MOB_DATA[rr_mob_id_max] = {
    {rr_mob_id_triceratops, rr_rarity_id_rare, 25, 15, 30.0f, {{rr_petal_id_leaf, 0.15},{rr_petal_id_fossil, 0.1}}},
    {rr_mob_id_trex, rr_rarity_id_epic, 20, 25, 32.0f, {{rr_petal_id_bone, 0.2},{rr_petal_id_fossil, 0.05},{rr_petal_id_egg, 0.05}}},
    {rr_mob_id_fern, rr_rarity_id_common, 10, 5, 24.0f, {{rr_petal_id_leaf, 0.1},{rr_petal_id_azalea, 0.25}}},
    {rr_mob_id_tree, rr_rarity_id_rare, 50, 5, 60.0f, {{rr_petal_id_leaf, 0.5},{rr_petal_id_peas, 0.25},{rr_petal_id_seed, 0.04}}},
    {rr_mob_id_pteranodon, rr_rarity_id_unusual, 30, 20, 20.0f, {{rr_petal_id_shell, 0.15},{rr_petal_id_beak, 0.15}}},
    {rr_mob_id_dakotaraptor, rr_rarity_id_unusual, 30, 10, 25.0f, {{rr_petal_id_crest, 1},{rr_petal_id_feather, 0.15}}},
    {rr_mob_id_pachycephalosaurus, rr_rarity_id_common, 20, 15, 20.0f, {{rr_petal_id_fossil, 0.15},{rr_petal_id_light, 0.1}}},
    {rr_mob_id_ornithomimus, rr_rarity_id_common, 10, 10, 20.0f, {{rr_petal_id_feather, 0.1},{rr_petal_id_droplet, 0.05}}},
    {rr_mob_id_ankylosaurus, rr_rarity_id_rare, 25, 10, 30.0f, {{rr_petal_id_club, 0.15},{rr_petal_id_gravel, 0.1}}},
    {rr_mob_id_meteor, rr_rarity_id_rare, 150, 8, 32.0f, {{rr_petal_id_magnet, 0.5},{rr_petal_id_uranium, 0.25}}},
    {rr_mob_id_quetzalcoatlus, rr_rarity_id_unusual, 45, 10, 28.0f, {{rr_petal_id_beak, 0.25},{rr_petal_id_fossil, 0.15}}},
    {rr_mob_id_edmontosaurus, rr_rarity_id_epic, 35, 10, 30.0f, {{rr_petal_id_peas, 0.15},{rr_petal_id_fossil, 0.1}}},
    {rr_mob_id_ant, rr_rarity_id_common, 15, 10, 20.0f, {{rr_petal_id_pellet, 0.1},{rr_petal_id_leaf, 0.1},{rr_petal_id_mandible, 0.05}}},
    {rr_mob_id_hornet, rr_rarity_id_common, 25, 25, 25.0f, {{rr_petal_id_stinger, 0.1},{rr_petal_id_crest, 0.05}}},
    {rr_mob_id_dragonfly, rr_rarity_id_common, 20, 10, 25.0f, {{rr_petal_id_pellet, 0.1},{rr_petal_id_third_eye, 0.05}}},
    {rr_mob_id_honeybee, rr_rarity_id_common, 10, 25, 22.0f, {{rr_petal_id_wax, 0.05},{rr_petal_id_stinger, 0.05}}},
    {rr_mob_id_beehive, rr_rarity_id_common, 0, 0, 45.0f, {{rr_petal_id_wax, 0.05},{rr_petal_id_azalea, 0.05}}},
    {rr_mob_id_spider, rr_rarity_id_common, 20, 25, 25.0f, {{rr_petal_id_web, 0.1},{rr_petal_id_magnet, 0.05}}},
};

char const *RR_MOB_NAMES[rr_mob_id_max] = 
{"Triceratops","T-Rex","Fern","Tree","Pteranodon","Dakotaraptor",
"Pachycephalosaurus","Ornithomimus","Ankylosaurus","Meteor",
"Quetzalcoatlus","Edmontosaurus","Ant","Hornet","Dragonfly",
 "Honeybee","Beehive","Spider"};

uint32_t RR_MOB_DIFFICULTY_COEFFICIENTS[rr_mob_id_max] = {9, 10, 2, 4, 20,
                                                          12, 9,  3, 10, 1, 8, 10, 8, 12, 8};
double RR_HELL_CREEK_MOB_ID_RARITY_COEFFICIENTS[rr_mob_id_max] = {50, 100, 30, 1, 25,
                                                       25, 20, 25, 25, 0.5, 75, 25};
double RR_GARDEN_MOB_ID_RARITY_COEFFICIENTS[rr_mob_id_max] = {0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 1, 1, 1, 1, 1, 10};

// zeach's numbers from the pinned screenshot of the old scaling
struct rr_petal_rarity_scale RR_PETAL_RARITY_SCALE[rr_rarity_id_max] = {
    {1,   1},
    {1.5, 2},
    {3.2, 4},
    {5.0, 8},
    {8.5, 16},
    {15.0, 40},
    {45.0, 75},
};

struct rr_mob_rarity_scale RR_MOB_RARITY_SCALING[rr_rarity_id_max] = {
    {1.0, 1.0, 1.0},
    {2.2, 2.5, 1.2},
    {7.5, 4.5, 1.5}, 
    {20,  7.5, 1.8},
    {75,  10,  2.5},
    {225, 25,  4.0},
    {1250, 80,  6.0},
};
// clang-format on

uint32_t RR_RARITY_COLORS[rr_rarity_id_max] = {
    0xff7eef6d, 0xffffe65d, 0xff4d52e3, 0xff861fde,
    0xffde1f1f, 0xff1fdbde, 0xffff2b75};
char const *RR_RARITY_NAMES[rr_rarity_id_max] = {
    "Common", "Uncommon", "Rare", "Epic", "Legendary", "Mythic", "Exotic"};
                                          
double RR_MOB_WAVE_RARITY_COEFFICIENTS[rr_rarity_id_ultra + 2] = {
    0, 1, 5, 10, 15, 30, 150, 1000};

double RR_DROP_RARITY_COEFFICIENTS[rr_rarity_id_ultra + 2] = {
    0, 1, 10, 25, 50, 200, 500, 1};
double RR_MOB_LOOT_RARITY_COEFFICIENTS[rr_rarity_id_ultra + 1] = {
    4, 5, 6, 10, 18, 15, 100};

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

#define offset(a,b) ((x + a < 0 || y + b < 0 || x + a >= size/2 || y + b >= size/2) ? 0 : template[(y+b)*size/2+x+a])
#define maze_grid(x,y) maze[(y) * size + (x)]

static void init_maze(uint32_t size, uint8_t *template, struct rr_maze_grid *maze)
{
    for (int32_t y = 0; y < size/2; ++y)
    {
        for (int32_t x = 0; x < size/2; ++x)
        {
            uint8_t this_tile = offset(0,0);
            #ifdef RR_SERVER
            maze_grid(x*2,y*2).difficulty = this_tile;
            maze_grid(x*2+1,y*2).difficulty = this_tile;
            maze_grid(x*2,y*2+1).difficulty = this_tile;
            maze_grid(x*2+1,y*2+1).difficulty = this_tile;
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
                        maze_grid(x*2,y*2).value = 7;
                    else
                        maze_grid(x*2,y*2).value = this_tile;
                    if (offset(1,0) == 0)
                        maze_grid(x*2+1,y*2).value = 5;
                    else
                        maze_grid(x*2+1,y*2).value = this_tile;
                }
                else
                {
                    maze_grid(x*2,y*2).value = this_tile;
                    maze_grid(x*2+1,y*2).value = this_tile;
                }
                if (bottom == 0)
                {
                    if (offset(-1,0) == 0)
                        maze_grid(x*2,y*2+1).value = 6;
                    else
                        maze_grid(x*2,y*2+1).value = this_tile;
                    if (offset(1,0) == 0)
                        maze_grid(x*2+1,y*2+1).value = 4;
                    else
                        maze_grid(x*2+1,y*2+1).value = this_tile;
                }
                else
                {
                    maze_grid(x*2,y*2+1).value = this_tile;
                    maze_grid(x*2+1,y*2+1).value = this_tile;
                }
            }
            else
            {
                if (top)
                {
                    if (offset(-1,0) && offset(-1,-1))
                        maze_grid(x*2,y*2).value = 15;
                    else
                        maze_grid(x*2,y*2).value = this_tile;
                    if (offset(1,0) && offset(1,-1))
                        maze_grid(x*2+1,y*2).value = 13;
                    else
                        maze_grid(x*2+1,y*2).value = this_tile;
                }
                else
                {
                    maze_grid(x*2,y*2).value = this_tile;
                    maze_grid(x*2+1,y*2).value = this_tile;
                }
                if (bottom)
                {
                    if (offset(-1,0) && offset(-1,1))
                        maze_grid(x*2,y*2+1).value = 14;
                    else
                        maze_grid(x*2,y*2+1).value = this_tile;
                    if (offset(1,0) && offset(1,1))
                        maze_grid(x*2+1,y*2+1).value = 12;
                    else
                        maze_grid(x*2+1,y*2+1).value = this_tile;
                }
                else
                {
                    maze_grid(x*2,y*2+1).value = this_tile;
                    maze_grid(x*2+1,y*2+1).value = this_tile;
                }
            }
        }
    }
}

/*
static void print_chances(float difficulty) {
    printf("-----Chances for %.0f-----\n", difficulty);
    uint32_t rarity_cap = rr_rarity_id_unusual + difficulty / 8;
    if (rarity_cap > rr_rarity_id_ultra)
        rarity_cap = rr_rarity_id_ultra;
    uint8_t rarity = 0;
    for (; rarity <= rarity_cap; ++rarity)
    {
        float start = rarity == 0 ? 0 : pow(1 - (1 - RR_MOB_WAVE_RARITY_COEFFICIENTS[rarity]) * 0.3,
                pow(1.45, difficulty));
        float end = rarity == rarity_cap ? 1 : pow(1 - (1 - RR_MOB_WAVE_RARITY_COEFFICIENTS[rarity + 1]) * 0.3,
                pow(1.45, difficulty));
        printf("%s: %.9f\n", RR_RARITY_NAMES[rarity], end - start);
    }
}
*/

void rr_static_data_init()
{
    init_game_coefficients();
    init_maze(RR_MAZE_DIM, &RR_MAZE_TEMPLATE_HELL_CREEK[0][0], &RR_MAZE_HELL_CREEK[0][0]);
    init_maze(RR_BURROW_MAZE_DIM, &RR_MAZE_TEMPLATE_BURROW[0][0], &RR_MAZE_BURROW[0][0]);
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

#ifdef RR_SERVER
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
#else
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
#endif

#define RR_DEFINE_MAZE(name, size) \
struct rr_maze_grid RR_MAZE_##name[size][size]; \
uint8_t RR_MAZE_TEMPLATE_##name[size/2][size/2]

RR_DEFINE_MAZE(HELL_CREEK, RR_MAZE_DIM) = {
    {l, l, l, l, l, l, l, l, l, E, E, E, 0, 0, 0, R, e, 0, e, e, 0},
    {l, 0, 0, 0, L, 0, 0, 0, 0, 0, 0, e, 0, 0, 0, R, 0, 0, e, R, R},
    {l, l, 0, L, L, 0, 0, 0, 0, 0, e, e, e, 0, 0, R, 0, 0, 0, R, r},
    {0, L, 0, 0, 0, 0, 0, 0, 0, 0, R, 0, R, R, R, r, r, U, 0, 0, r},
    {0, L, 0, M, M, m, m, L, L, 0, R, 0, 0, 0, 0, 0, 0, U, 0, 0, r},
    {0, L, 0, x, M, 0, 0, 0, L, 0, R, r, r, r, 0, 0, 0, u, 0, 0, U},
    {0, L, 0, 0, 0, 0, 0, 0, l, 0, 0, 0, 0, U, U, U, u, u, 0, 0, U},
    {L, L, m, m, m, m, 0, l, l, 0, 0, 0, 0, 0, 0, 0, 0, C, u, u, u},
    {L, 0, 0, 0, 0, M, 0, E, 0, 0, 0, R, e, e, e, e, 0, C, 0, 0, 0},
    {m, 0, M, M, M, M, 0, E, 0, 0, 0, R, 0, 0, 0, R, 0, C, 0, 0, 0},
    {m, 0, M, 0, 0, 0, 0, E, e, e, e, R, R, 0, 0, R, 0, c, c, c, c},
    {m, 0, x, x, x, x, 0, 0, 0, 0, 0, 0, r, r, r, r, 0, C, 0, 0, 0},
    {m, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, U, 0, 0, C, u, u, 0},
    {m, m, m, M, M, 0, 0, x, x, M, M, 0, 0, 0, U, 0, 0, u, 0, U, U},
    {0, m, 0, 0, M, 0, 0, 0, 0, 0, M, M, 0, 0, U, u, u, u, 0, U, r},
    {0, m, 0, 0, M, x, 0, 0, 0, 0, 0, m, 0, 0, 0, 0, 0, U, 0, 0, 0},
    {0, m, 0, 0, 0, 0, 0, 0, 0, 0, 0, m, 0, 0, 0, 0, 0, U, 0, 0, 0},
    {0, m, 0, 0, 0, 0, M, M, 0, 0, 0, m, 0, 0, 0, 0, 0, r, r, R, R},
    {0, M, 0, 0, x, 0, 0, m, 0, 0, 0, L, L, 0, R, r, r, r, 0, 0, R},
    {0, M, M, M, x, x, 0, m, 0, 0, 0, 0, l, 0, 0, 0, 0, 0, 0, 0, e},
    {0, 0, 0, 0, x, 0, 0, m, L, L, l, l, l, l, E, E, E, E, e, e, e},
};

RR_DEFINE_MAZE(BURROW, RR_BURROW_MAZE_DIM) = {
    {1, 1},
    {0, 1}
};

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