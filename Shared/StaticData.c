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
    {rr_petal_id_none, rr_rarity_id_common, &offensive[0], 0.0f, 0.0f, 0.0f, 0, 0, {0,0,0,0,0,0,0,0}},
    {rr_petal_id_basic, rr_rarity_id_common, &offensive[0], 10.0f, 15.0f, 0.0f, 50, 0, {1,1,1,1,1,1,1,1}},
    {rr_petal_id_pellet, rr_rarity_id_common, &offensive[0], 15.0f, 5.0f, 0.0f, 20, 0, {1,2,2,3,3,5,6,6}},
    {rr_petal_id_fossil, rr_rarity_id_common, &offensive[0], 10.0f, 60.0f, 0.0f, 100, 0, {1,1,1,1,1,1,1,1}},
    {rr_petal_id_stinger, rr_rarity_id_common, &offensive[0], 72.0f, 3.0f, 10.0f, 150, 0, {1,1,1,1,1,3,5,5}},
    {rr_petal_id_light, rr_rarity_id_rare, &offensive[0], 8.0f, 5.0f, 15.0f, 20, 0, {1,1,1,1,1,2,3,3}},
    {rr_petal_id_shell, rr_rarity_id_rare, &offensive[0], 32.0f, 8.0f, 0.0f, 63, 13, {1,1,1,1,1,2,3,3}},
    {rr_petal_id_peas, rr_rarity_id_rare, &offensive[0], 15.0f, 8.0f, 8.0f, 13, 12, {4,4,4,4,4,4,5,5}},
    {rr_petal_id_leaf, rr_rarity_id_unusual, &offensive[0], 10.0f, 12.0f, 8.0f, 25, 0, {1,1,1,1,1,2,2,2}},
    {rr_petal_id_egg, rr_rarity_id_unusual, &defensive[0], 1.0f, 20.0f, 0.0f, 25, 75, {1,1,2,2,2,2,2,2}},
    {rr_petal_id_magnet, rr_rarity_id_rare, &defensive[0], 2.0f, 15.0f, 0.0f, 38, 0, {1,1,1,1,1,1,1,1}},
    {rr_petal_id_uranium, rr_rarity_id_rare, &offensive[0], 12.0f, 10.0f, 0.0f, 50, 25, {1,1,1,1,1,1,1,1}},
    {rr_petal_id_feather, rr_rarity_id_common, &defensive[0], 1.0f, 3.0f, 0.0f, 25, 0, {1,1,1,1,1,1,1,1}},
    {rr_petal_id_azalea, rr_rarity_id_common, &defensive[0], 5.0f, 10.0f, 0.0f, 50, 25, {1,1,1,1,1,1,1,1}},
    {rr_petal_id_bone, rr_rarity_id_common, &defensive[0], 2.5f, 25.0f, 0.0f, 68, 0, {1,1,1,1,1,1,1,1}},
    {rr_petal_id_web, rr_rarity_id_rare, &defensive[0], 5.0f, 5.0f, 0.0f, 50, 13, {1,1,1,1,1,1,1,1}},
    {rr_petal_id_seed, rr_rarity_id_legendary, &offensive[0], 1.0f, 20.0f, 0.0f, 63, 1, {1,1,1,1,1,1,1,1}},
    {rr_petal_id_gravel, rr_rarity_id_unusual, &offensive[0], 15.0f, 10.0f, 0.0f, 25, 13, {1,2,2,2,3,3,4,4}},
    {rr_petal_id_club, rr_rarity_id_common, &defensive[0], 7.0f, 300.0f, 0.0f, 200, 0, {1,1,1,1,1,1,1,1}},
    {rr_petal_id_crest, rr_rarity_id_rare, &offensive[0], 0.0f, 0.0f, 0.0f, 0, 0, {0,0,0,0,0,0,0,0}},
    {rr_petal_id_droplet, rr_rarity_id_common, &offensive[0], 15.0f, 5.0f, 0.0f, 37, 0, {1,1,1,1,1,1,1,1}},
    {rr_petal_id_beak, rr_rarity_id_unusual, &offensive[0], 5.0f, 5.0f, 0.0f, 55, 0, {1,1,1,1,1,1,1,1}},
    {rr_petal_id_lightning, rr_rarity_id_unusual, &offensive[0], 18.0f, 1.0f, 0.0f, 50, 0, {1,1,1,1,1,1,1,1}},
    {rr_petal_id_third_eye, rr_rarity_id_legendary, &offensive[0], 0.0f, 0.0f, 0.0f, 0, 0, {0,0,0,0,0,0,0,0}},
    {rr_petal_id_mandible, rr_rarity_id_common, &offensive[0], 5.0f, 10.0f, 0.0f, 75, 0, {1,1,1,1,1,1,1,1}},
    {rr_petal_id_wax, rr_rarity_id_unusual, &offensive[0], 5.0f, 10.0f, 10.0f, 75, 0, {2,2,2,2,2,2,2,2}},
    {rr_petal_id_sand, rr_rarity_id_common, &offensive[0], 15.0f, 10.0f, 10.0f, 37, 0, {4,4,4,4,4,4,4,4}},
    {rr_petal_id_mint, rr_rarity_id_unusual, &offensive[0], 5.0f, 10.0f, 10.0f, 50, 25, {1,1,1,1,1,1,1,1}},
};    

char const *RR_PETAL_NAMES[rr_petal_id_max] = {
    "Secret", "Petal", "Pellet", "Fossil",   "Stinger",  "Berries", "Shell",
    "Peas",   "Leaf",  "Egg",    "Magnet", "Uranium", "Feather", "Azalea",
    "Bone",   "Web",   "Seed",   "Gravel", "Club", "Crest", "Droplet",
    "Beak", "Lightning", "Third Eye", "Mandible", "Wax", "Sand", "Mint"};
    
char const *RR_PETAL_DESCRIPTIONS[rr_petal_id_max] = {
    0,
    "It's just a petal",
    "Low damage, but there's lots",
    "It came from a dino",
    "Ow that hurts",
    "Gives your other petals more energy",
    "Poor snail",
    "Splits in 4. Or maybe 5 if you're a pro",
    "Heals you gradually",
    "Spawns a pet dinosaur to protect you",
    "Increases loot pickup radius. Does not stack",
    "Does low damage to mobs in a small range",
    "It's so light it increases your movement speed. Stacks diminishingly",
    "It heals you",
    "Gives the player armor. Stacks diminishingly",
    "It slows everything down",
    "What does this one do",
    "Tiny rocks that stay on the ground and trip dinos",
    "Heavy and sturdy",
    "Increases your vision range. Does not stack",
    "This mysterious petal reverses your petal rotation",
    "Stuns mobs and prevents them from moving",
    "A stunning display",
    "Your petals hate it and want to move further away",
    "Does more damage if target hp is below 50%",
    "Made by the bees",
    "Very fine",
    "Remember to feed your pets"
};

struct rr_mob_data RR_MOB_DATA[rr_mob_id_max] = {
    {rr_mob_id_triceratops, rr_rarity_id_rare, rr_rarity_id_ultimate, 45, 15, 30.0f, {{rr_petal_id_leaf, 0.15},{rr_petal_id_fossil, 0.05}}},
    {rr_mob_id_trex, rr_rarity_id_epic, rr_rarity_id_ultimate, 40, 25, 32.0f, {{rr_petal_id_stinger, 0.05},{rr_petal_id_egg, 0.05}}},
    {rr_mob_id_fern, rr_rarity_id_common, rr_rarity_id_exotic, 10, 5, 24.0f, {{rr_petal_id_leaf, 0.1},{rr_petal_id_azalea, 0.25}}},
    {rr_mob_id_tree, rr_rarity_id_rare, rr_rarity_id_exotic, 100, 5, 64.0f, {{rr_petal_id_leaf, 0.5},{rr_petal_id_peas, 0.25},{rr_petal_id_seed, 0.1}}},
    {rr_mob_id_pteranodon, rr_rarity_id_rare, rr_rarity_id_ultimate, 40, 15, 20.0f, {{rr_petal_id_shell, 0.15},{rr_petal_id_beak, 0.15}}},
    {rr_mob_id_dakotaraptor, rr_rarity_id_unusual, rr_rarity_id_ultimate, 40, 10, 25.0f, {{rr_petal_id_crest, 0.1},{rr_petal_id_feather, 0.15},{rr_petal_id_pellet, 0.05}}},
    {rr_mob_id_pachycephalosaurus, rr_rarity_id_common, rr_rarity_id_ultimate, 35, 15, 20.0f, {{rr_petal_id_fossil, 0.1},{rr_petal_id_light, 0.1},{rr_petal_id_web, 0.05}}},
    {rr_mob_id_ornithomimus, rr_rarity_id_common, rr_rarity_id_ultimate, 25, 10, 20.0f, {{rr_petal_id_feather, 0.1},{rr_petal_id_droplet, 0.05},{rr_petal_id_pellet, 0.1}}},
    {rr_mob_id_ankylosaurus, rr_rarity_id_rare, rr_rarity_id_ultimate, 50, 10, 30.0f, {{rr_petal_id_club, 0.15},{rr_petal_id_gravel, 0.1}}},
    {rr_mob_id_meteor, rr_rarity_id_rare, rr_rarity_id_mythic, 100, 5, 32.0f, {{rr_petal_id_magnet, 0.5},{rr_petal_id_uranium, 0.25}}},
    {rr_mob_id_quetzalcoatlus, rr_rarity_id_rare, rr_rarity_id_ultimate, 65, 20, 28.0f, {{rr_petal_id_beak, 0.25},{rr_petal_id_fossil, 0.1},{rr_petal_id_lightning, 0.05}}},
    {rr_mob_id_edmontosaurus, rr_rarity_id_epic, rr_rarity_id_ultimate, 45, 15, 30.0f, {{rr_petal_id_bone, 0.15},{rr_petal_id_fossil, 0.1},{rr_petal_id_third_eye, 0.05}}},
    {rr_mob_id_ant, rr_rarity_id_common, rr_rarity_id_ultimate, 15, 10, 20.0f, {{rr_petal_id_pellet, 0.1},{rr_petal_id_leaf, 0.1},{rr_petal_id_mandible, 0.05}}},
    {rr_mob_id_hornet, rr_rarity_id_common, rr_rarity_id_ultimate, 25, 25, 25.0f, {{rr_petal_id_stinger, 0.1},{rr_petal_id_crest, 0.05}}},
    {rr_mob_id_dragonfly, rr_rarity_id_unusual, rr_rarity_id_ultimate, 20, 10, 25.0f, {{rr_petal_id_pellet, 0.1},{rr_petal_id_third_eye, 0.05}}},
    {rr_mob_id_honeybee, rr_rarity_id_common, rr_rarity_id_ultimate, 10, 25, 22.0f, {{rr_petal_id_wax, 0.05},{rr_petal_id_stinger, 0.05}}},
    {rr_mob_id_beehive, rr_rarity_id_rare, rr_rarity_id_ultimate, 0, 0, 45.0f, {{rr_petal_id_wax, 0.05},{rr_petal_id_azalea, 0.05}}},
    {rr_mob_id_spider, rr_rarity_id_rare, rr_rarity_id_ultimate, 20, 25, 25.0f, {{rr_petal_id_web, 0.1},{rr_petal_id_magnet, 0.01}}},
    {rr_mob_id_house_centipede, rr_rarity_id_common, rr_rarity_id_ultimate, 25, 10, 23.0f, {{rr_petal_id_peas, 0.1},{rr_petal_id_sand, 0.05}}},
    {rr_mob_id_lanternfly, rr_rarity_id_unusual, rr_rarity_id_ultimate, 20, 10, 25.0f, {{rr_petal_id_mint, 0.1},{rr_petal_id_sand, 0.05}}},
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
    3, //edmon
};

double RR_HELL_CREEK_MOB_ID_RARITY_COEFFICIENTS[rr_mob_id_max] = {
    50, //tric
    100,//trex
    15, //fern
    1,  //tree
    75, //pter
    50, //dako
    25, //pachy
    40, //ornith
    25, //anky
    0.5,//meteor
    75, //quetz
    25  //edmo
};
double RR_GARDEN_MOB_ID_RARITY_COEFFICIENTS[rr_mob_id_max] = {0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 1, 1, 1, 1, 1, 1, 10};

struct rr_petal_rarity_scale RR_PETAL_RARITY_SCALE[rr_rarity_id_max] = {
    {1.0, 240, 45},
    {1.8, 120, 60},
    {3.5, 60,  75},
    {6.8, 30,  100},
    {12.5,15,  125},
    {24.5,7.5, 150},
    {60.0,2.5, 200},
    {180, 0.5, 250}
};

struct rr_mob_rarity_scale RR_MOB_RARITY_SCALING[rr_rarity_id_max] = {
    {1.0, 1.0, 1.0},
    {2.4, 1.7, 1.2},
    {6.0, 2.9, 1.8}, 
    {16,  5.0, 2.4},
    {56,  8.5, 3.6},
    {320,14.5, 4.5},
    {48e2,24.6, 6.0},
    {240e3,42.0,7.5}
};
// clang-format on

uint32_t RR_RARITY_COLORS[rr_rarity_id_max] = {
    0xff7eef6d, 0xffffe65d, 0xff4d52e3, 0xff861fde,
    0xffde1f1f, 0xff1fdbde, 0xffff2b75, 0xfff70fb6};

char const *RR_RARITY_NAMES[rr_rarity_id_max] = {
    "Common",    "Uncommon", "Rare",   "Epic",
    "Legendary", "Mythic",   "Exotic", "Ultimate"};

double RR_MOB_WAVE_RARITY_COEFFICIENTS[rr_rarity_id_max + 1] = {
    0, 1, 6, 10, 15, 25, 160, 1200, 250};

double RR_DROP_RARITY_COEFFICIENTS[rr_rarity_id_exotic + 2] = {
    0, 1, 8, 15, 40, 250, 2500, 1600};
double RR_MOB_LOOT_RARITY_COEFFICIENTS[rr_rarity_id_max] = {
    2.5, 4, 6, 15, 50, 320, 160, 120};

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
#define maze_grid(x, y) maze[(y) * size + (x)]

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
#endif

#define RR_DEFINE_MAZE(name, size)                                             \
    struct rr_maze_grid RR_MAZE_##name[size][size];                            \
    uint8_t RR_MAZE_TEMPLATE_##name[size / 2][size / 2]
// clang-format off
RR_DEFINE_MAZE(HELL_CREEK, 80) = {
{_,_,_,_,_,x,x,x,x,_,_,_,_,_,x,x,x,x,x,x,x,x,x,x,x,x,x,x,x,x,x,x,x,x,X,_,_,_,_,_},
{_,M,M,_,_,_,_,x,x,x,x,M,M,M,x,_,_,_,_,_,x,_,_,_,_,_,_,_,_,x,_,_,x,X,X,X,X,_,_,_},
{m,m,M,M,_,_,_,_,_,_,_,_,M,_,_,_,_,X,X,_,x,x,x,_,x,x,x,x,x,x,_,_,_,_,X,X,X,X,_,_},
{m,m,m,M,M,M,M,M,M,M,M,M,M,_,_,X,X,X,x,x,x,_,x,x,x,_,_,x,x,x,x,x,_,X,X,X,X,X,_,_},
{m,m,m,_,_,_,_,_,_,_,_,_,_,_,X,X,X,X,X,_,x,_,_,x,x,_,_,_,_,x,x,_,_,X,X,X,X,X,X,_},
{m,m,_,_,_,_,_,U,U,U,_,_,_,_,_,X,X,X,_,_,x,_,_,_,x,_,x,x,_,_,x,_,_,_,X,X,X,_,_,_},
{m,m,_,_,_,U,U,U,u,U,U,U,U,_,_,_,X,X,_,_,_,_,_,_,x,x,x,x,_,_,x,_,x,_,_,X,_,_,_,_},
{m,_,_,_,U,U,U,u,u,u,_,_,r,_,_,_,_,X,X,_,_,_,_,_,x,_,x,x,x,_,x,_,x,M,_,_,_,_,_,_},
{m,_,_,U,U,U,u,u,u,u,_,r,r,r,U,_,_,X,X,X,_,_,_,x,x,_,x,x,X,_,M,_,M,M,M,M,_,_,_,_},
{m,_,r,U,U,_,u,u,u,_,_,r,_,_,U,_,X,X,X,X,X,X,_,_,x,_,_,X,X,_,M,_,_,M,M,M,M,_,_,_},
{m,_,r,r,_,_,_,_,C,_,R,R,_,U,U,_,X,X,_,_,_,X,_,_,x,x,_,_,_,_,M,_,_,_,M,M,M,M,_,_},
{m,_,_,_,_,_,_,_,C,_,_,_,_,u,_,_,X,X,_,X,X,X,_,_,x,x,x,_,_,M,M,_,_,_,_,_,_,M,_,_},
{m,_,_,_,_,c,c,c,C,C,C,u,u,u,_,_,X,X,_,_,_,X,_,_,_,x,M,M,M,M,M,_,_,M,M,_,M,M,_,_},
{m,_,_,_,_,c,c,c,_,_,u,u,u,_,_,_,X,X,_,_,_,X,_,_,_,x,x,_,_,_,M,M,M,M,M,M,M,_,_,_},
{m,_,_,_,_,c,c,c,_,u,u,u,u,U,_,_,X,X,X,X,X,X,_,_,_,_,_,_,_,_,_,M,M,M,M,M,M,_,_,_},
{m,_,_,_,_,_,_,C,_,u,u,u,U,U,_,_,_,_,X,X,X,_,_,_,_,_,_,M,M,M,_,_,_,M,_,M,m,_,_,_},
{m,m,m,m,m,m,_,C,_,_,u,U,U,U,_,r,r,_,_,_,_,_,e,e,e,_,_,_,M,M,M,M,_,M,_,_,m,m,_,_},
{L,_,_,_,_,m,_,C,u,_,_,_,_,U,r,r,r,r,R,R,R,R,R,_,e,e,e,_,M,M,M,M,M,M,m,_,m,m,m,_},
{L,L,_,m,m,m,_,_,u,u,u,U,_,_,_,_,_,_,R,R,_,_,e,_,_,_,E,_,_,M,M,M,_,_,m,m,m,m,m,_},
{_,L,_,_,L,m,_,u,u,_,_,U,U,U,r,_,R,R,R,R,_,_,e,e,_,_,E,_,_,_,M,M,M,_,_,m,m,m,m,_},
{_,L,L,L,L,_,_,U,u,_,_,U,U,r,r,r,r,R,R,R,_,_,_,e,e,e,E,E,_,_,_,_,_,_,_,_,_,_,m,_},
{L,L,_,_,_,_,_,U,U,U,_,U,r,_,r,r,_,_,R,R,R,_,_,_,_,_,E,E,E,E,E,_,_,_,_,l,_,_,m,_},
{L,_,_,_,_,_,_,_,U,U,_,r,_,_,r,R,R,_,_,R,e,e,e,_,_,_,E,E,_,E,E,E,_,_,l,l,l,_,m,_},
{L,_,_,_,L,L,L,_,_,U,_,r,_,_,R,R,R,_,_,e,_,e,e,e,_,_,E,_,_,_,_,E,_,l,l,l,l,_,m,_},
{L,_,_,L,L,L,L,L,_,_,_,r,_,_,_,R,R,_,e,e,_,e,e,e,_,E,E,_,l,_,_,l,l,l,l,l,_,_,m,_},
{L,_,L,L,L,L,L,L,_,_,_,r,_,_,_,R,R,_,e,e,_,e,e,_,_,E,_,_,l,l,_,l,_,_,_,_,_,_,m,_},
{L,L,L,L,L,L,L,L,_,_,_,R,R,R,_,_,e,_,e,e,_,_,E,_,_,E,_,_,l,l,_,l,l,_,_,_,_,m,m,_},
{L,_,L,L,L,L,L,_,_,_,R,R,R,R,R,_,e,_,_,e,e,E,E,_,_,E,_,_,l,l,l,l,l,l,_,_,m,m,m,_},
{L,_,_,L,l,L,_,_,_,_,R,R,R,R,e,_,e,_,_,e,E,E,E,_,_,l,_,_,_,_,_,l,l,l,_,_,m,L,_,_},
{L,_,_,_,l,_,_,_,_,_,R,R,R,e,e,_,e,e,_,_,E,E,E,_,_,l,l,l,l,_,_,_,l,l,_,_,L,L,_,_},
{L,L,_,_,l,_,_,_,_,_,e,R,e,e,e,_,e,e,_,_,_,E,E,_,_,_,l,l,l,l,l,l,l,l,_,L,L,L,_,_},
{L,L,_,_,l,l,_,_,_,_,_,e,e,e,_,_,e,E,E,E,_,_,E,E,_,_,l,l,l,l,_,_,_,_,_,_,_,L,_,_},
{L,L,_,_,l,l,l,l,_,_,_,_,_,_,_,_,E,E,E,E,E,E,E,E,_,_,l,l,l,l,_,_,m,L,L,L,L,L,_,_},
{_,L,L,_,_,l,l,l,l,l,l,_,_,_,_,_,E,E,E,E,_,_,E,E,_,_,l,l,l,_,_,_,m,_,_,_,_,L,_,_},
{_,L,L,_,_,_,_,l,l,l,E,E,E,E,E,E,E,E,E,E,E,_,E,l,_,_,l,l,_,_,_,_,m,_,m,m,_,L,_,_},
{_,L,L,m,m,_,_,_,_,l,l,E,E,E,_,_,_,_,_,_,E,E,l,l,l,_,l,l,l,_,_,_,m,_,_,m,_,L,_,_},
{_,L,m,m,m,m,m,_,_,_,_,_,_,_,_,_,_,_,_,_,E,l,l,l,l,l,l,l,l,_,_,_,m,m,m,m,_,L,_,_},
{_,_,m,m,m,m,m,m,_,_,_,_,_,_,_,_,M,M,_,_,_,l,l,l,_,l,l,l,l,_,_,_,_,_,_,_,_,L,_,_},
{_,_,_,m,m,m,m,m,m,m,m,m,m,m,m,m,M,M,_,_,_,_,_,_,_,l,l,l,l,l,l,L,L,L,L,L,L,L,_,_},
{_,_,_,_,_,_,_,_,_,_,_,_,_,_,_,_,_,_,_,_,_,_,_,_,_,_,_,_,_,_,_,_,_,_,_,_,_,_,_,_}
};
// clang-format on
RR_DEFINE_MAZE(BURROW, 4) = {{1, 1}, {0, 1}};

#define MAZE_ENTRY(MAZE, GRID_SIZE)                                            \
    {                                                                          \
        (sizeof(RR_MAZE_##MAZE[0]) / sizeof(struct rr_maze_grid)), GRID_SIZE,  \
            &RR_MAZE_##MAZE[0][0], &RR_MAZE_TEMPLATE_##MAZE[0][0]              \
    }
struct rr_maze_declaration RR_MAZES[rr_biome_id_max] = {
    MAZE_ENTRY(HELL_CREEK, 1024),
    MAZE_ENTRY(HELL_CREEK, 1024),
    MAZE_ENTRY(BURROW, 512),
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
